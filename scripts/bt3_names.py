#!/usr/bin/env python3
"""Cruza funciones BT2 con BT3 por bytes de instruccion normalizados.

Normalizacion por palabra de 32 bits (little endian):
  - j/jal (op 0x02/0x03): se conserva solo el opcode (destino a 0).
  - lui 0x0F, addiu 0x09, ori 0x0D, loads/stores 0x20-0x3F y lq/sq 0x1E/0x1F:
    el inmediato de 16 bits se pone a 0.
  - el resto se conserva tal cual (branches incluidos).

Pasada 1 (exacta): sha1 de la secuencia normalizada (+ longitud).
Pasada 2 (fuzzy): BT2 sin match exacto y >= 8 instrucciones; candidatos BT3 de
longitud +-10 %, prefiltrados por histograma de opcodes (top 50), luego
difflib.SequenceMatcher(autojunk=False) con ratio >= 0.90. Si la pasada fuzzy
supera 15 min se descarta y solo queda el exacto.

Uso:
  python3 bt3_names.py [--no-fuzzy]
"""
import csv
import difflib
import hashlib
import os
import re
import struct
import sys
import time
from collections import defaultdict

import numpy as np

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BT3_ROOT = os.environ.get("BT3_DECOMP", os.path.expanduser("~/Proyectos/BT3-Decompiled"))
BT2_ELF = os.path.join(ROOT, "gamedata", "SLUS_214.41")
BT2_MAP = os.path.join(ROOT, "port", "funcmap.csv")
BT3_ELF = os.path.join(BT3_ROOT, "build", "SLUS_216.78.elf")
OUT_CSV = os.path.join(ROOT, "build_port", "bt3_names.csv")

FUZZY_BUDGET_S = 15 * 60
FUZZY_MIN_INSNS = 8
FUZZY_LEN_TOL = 0.10
FUZZY_TOP_K = 50
FUZZY_MIN_RATIO = 0.90
GENERIC_RE = re.compile(r"^func_[0-9A-Fa-f]{8}$")
REGIONS = [
    ("<0x2D0000", 0x0, 0x2D0000),
    ("0x2D0000-0x300000", 0x2D0000, 0x300000),
    ("0x300000-0x33B5F8", 0x300000, 0x33B5F8),
    ("resto", 0x33B5F8, 1 << 32),
]


class Elf:
    def __init__(self, path):
        with open(path, "rb") as f:
            self.data = f.read()
        d = self.data
        assert d[:4] == b"\x7fELF" and d[4] == 1 and d[5] == 1, "se espera ELF32 LE"
        (e_phoff,) = struct.unpack_from("<I", d, 0x1C)
        (e_shoff,) = struct.unpack_from("<I", d, 0x20)
        e_phentsize, e_phnum = struct.unpack_from("<HH", d, 0x2A)
        e_shentsize, e_shnum, _ = struct.unpack_from("<HHH", d, 0x2E)
        # PT_LOAD con datos en archivo: (vaddr, filesz, offset)
        self.segs = []
        for i in range(e_phnum):
            p = struct.unpack_from("<8I", d, e_phoff + i * e_phentsize)
            p_type, p_offset, p_vaddr, _, p_filesz = p[0], p[1], p[2], p[3], p[4]
            if p_type == 1 and p_filesz > 0:
                self.segs.append((p_vaddr, p_filesz, p_offset))
        self.shdrs = [
            struct.unpack_from("<10I", d, e_shoff + i * e_shentsize) for i in range(e_shnum)
        ]

    def symbols(self):
        """Yield (name, value, size, type, bind) de .symtab."""
        d = self.data
        for s in self.shdrs:
            if s[1] != 2:  # SHT_SYMTAB
                continue
            strsh = self.shdrs[s[6]]
            stroff, strsz = strsh[4], strsh[5]
            strtab = d[stroff:stroff + strsz]
            for off in range(s[4], s[4] + s[5], 16):
                st_name, st_value, st_size, st_info, _, _ = struct.unpack_from("<IIIBBH", d, off)
                end = strtab.index(b"\0", st_name)
                name = strtab[st_name:end].decode("latin-1")
                yield name, st_value, st_size, st_info & 0xF, st_info >> 4

    def read(self, addr, size):
        """Bytes de [addr, addr+size) si caen enteros dentro de un segmento con archivo."""
        for vaddr, filesz, off in self.segs:
            if vaddr <= addr and addr + size <= vaddr + filesz:
                o = off + (addr - vaddr)
                return self.data[o:o + size]
        return None


def normalize(words):
    out = []
    for w in words:
        op = w >> 26
        if op in (0x02, 0x03):
            w &= 0xFC000000
        elif op in (0x0F, 0x09, 0x0D, 0x1E, 0x1F) or 0x20 <= op <= 0x3F:
            w &= 0xFFFF0000
        out.append(w)
    return out


def words_of(code):
    n = len(code) // 4
    return struct.unpack("<%dI" % n, code[:n * 4])


def exact_key(norm):
    b = struct.pack("<%dI" % len(norm), *norm)
    return (hashlib.sha1(b).hexdigest(), len(norm))


def opcode_hist(words):
    h = np.zeros(64, dtype=np.int32)
    for w in words:
        h[w >> 26] += 1
    return h


def is_generic(name):
    return bool(GENERIC_RE.match(name))


def region_of(addr):
    for label, lo, hi in REGIONS:
        if lo <= addr < hi:
            return label
    return "resto"


def main():
    use_fuzzy = "--no-fuzzy" not in sys.argv
    t0 = time.time()

    # ---- BT2 ----
    bt2_elf = Elf(BT2_ELF)
    bt2 = []  # dicts
    skipped_bt2 = defaultdict(int)
    seen_addr = set()
    with open(BT2_MAP, newline="") as f:
        for row in csv.DictReader(f):
            start = int(row["Start"], 16)
            end = int(row["End"], 16)
            size = end - start
            if start >= 0x01000000:
                skipped_bt2["start>=0x01000000"] += 1
                continue
            code = bt2_elf.read(start, size) if size > 0 else None
            if code is None:
                skipped_bt2["fuera de segmento con archivo"] += 1
                continue
            if size % 4:
                skipped_bt2["tamano no multiplo de 4 (truncado)"] += 1
            if start in seen_addr:
                skipped_bt2["direccion duplicada"] += 1
                continue
            seen_addr.add(start)
            words = words_of(code)
            norm = normalize(words)
            bt2.append({
                "addr": start, "name": row["Name"], "size": size,
                "words": words, "norm": norm, "n": len(words),
            })
    print(f"BT2 consideradas: {len(bt2)}  omitidas: {dict(skipped_bt2)}", file=sys.stderr)

    # ---- BT3 ----
    bt3_elf = Elf(BT3_ELF)
    raw_syms = [s for s in bt3_elf.symbols() if s[3] == 2 and s[2] > 0]  # STT_FUNC, size>0
    print(f"BT3 simbolos FUNC size>0: {len(raw_syms)}", file=sys.stderr)

    # Un nombre por direccion (aliases): prefiere no genérico, luego global.
    by_addr = {}
    alias_count = 0
    for name, value, size, _, bind in raw_syms:
        if value in by_addr:
            alias_count += 1
            prev = by_addr[value]
            cand = (not is_generic(name), bind == 1, name)
            cur = (not is_generic(prev[0]), prev[4] == 1, prev[0])
            if cand > cur:
                by_addr[value] = (name, value, size, 2, bind)
            continue
        by_addr[value] = (name, value, size, 2, bind)
    bt3 = []
    skipped_bt3 = 0
    for name, value, size, _, _ in by_addr.values():
        code = bt3_elf.read(value, size)
        if code is None or size % 4:
            skipped_bt3 += 1
            continue
        words = words_of(code)
        bt3.append({"addr": value, "name": name, "n": len(words),
                    "norm": normalize(words), "words": words})
    print(f"BT3 funciones tras dedupe por direccion: {len(bt3)} "
          f"(aliases {alias_count}, sin datos/tamano invalido {skipped_bt3})", file=sys.stderr)

    # ---- Pasada exacta ----
    by_hash = defaultdict(list)
    for fn in bt3:
        by_hash[exact_key(fn["norm"])].append(fn)

    results = {}  # bt2 addr -> row dict
    for fn in bt2:
        cands = by_hash.get(exact_key(fn["norm"]))
        if not cands:
            continue
        names = sorted({c["name"] for c in cands})
        addrs = [c["addr"] for c in sorted(cands, key=lambda c: (c["name"], c["addr"]))]
        rows_name = [c["name"] for c in sorted(cands, key=lambda c: (c["name"], c["addr"]))]
        results[fn["addr"]] = {
            "bt2_addr": fn["addr"], "bt2_name": fn["name"], "size": fn["size"],
            "bt3_name": "|".join(rows_name), "bt3_addr": "|".join("0x%08x" % a for a in addrs),
            "kind": "exact", "ratio": "1.000", "ambiguous_count": len(names),
        }
    n_exact = len(results)
    print(f"Exactos: {n_exact}  ({time.time() - t0:.1f}s)", file=sys.stderr)

    # ---- Pasada fuzzy ----
    n_fuzzy = 0
    fuzzy_status = "desactivada"
    if use_fuzzy:
        tf = time.time()
        bt3_len = np.array([c["n"] for c in bt3], dtype=np.int32)
        bt3_hist = np.stack([opcode_hist(c["words"]) for c in bt3]) if bt3 else np.zeros((0, 64))
        # ordenar BT3 por longitud para busqueda por rango
        order = np.argsort(bt3_len, kind="stable")
        sorted_len = bt3_len[order]
        fuzzy_rows = {}
        timed_out = False
        for i, fn in enumerate(bt2):
            if fn["addr"] in results or fn["n"] < FUZZY_MIN_INSNS:
                continue
            if time.time() - tf > FUZZY_BUDGET_S:
                timed_out = True
                break
            n = fn["n"]
            lo = int(np.ceil(n * (1 - FUZZY_LEN_TOL)))
            hi = int(np.floor(n * (1 + FUZZY_LEN_TOL)))
            a = np.searchsorted(sorted_len, lo, side="left")
            b = np.searchsorted(sorted_len, hi, side="right")
            if b <= a:
                continue
            idx = order[a:b]
            h2 = opcode_hist(fn["words"])
            score = np.minimum(bt3_hist[idx], h2).sum(axis=1)
            top = idx[np.argsort(-score, kind="stable")[:FUZZY_TOP_K]]
            seq2 = fn["norm"]
            best = None
            for j in top:
                c = bt3[j]
                sm = difflib.SequenceMatcher(None, seq2, c["norm"], autojunk=False)
                if sm.real_quick_ratio() < FUZZY_MIN_RATIO or sm.quick_ratio() < FUZZY_MIN_RATIO:
                    continue
                r = sm.ratio()
                if r < FUZZY_MIN_RATIO:
                    continue
                key = (-r, abs(c["n"] - n), c["name"])
                if best is None or key < best[0]:
                    best = (key, c, r)
            if best is not None:
                _, c, r = best
                fuzzy_rows[fn["addr"]] = {
                    "bt2_addr": fn["addr"], "bt2_name": fn["name"], "size": fn["size"],
                    "bt3_name": c["name"], "bt3_addr": "0x%08x" % c["addr"],
                    "kind": "fuzzy", "ratio": "%.3f" % r, "ambiguous_count": 1,
                }
            if i % 1000 == 0:
                print(f"  fuzzy {i}/{len(bt2)} ({time.time() - tf:.0f}s)", file=sys.stderr)
        if timed_out:
            fuzzy_status = "CORTADA por tiempo (>15 min): solo exacto"
            print("Pasada fuzzy cortada por tiempo; se descartan sus resultados.", file=sys.stderr)
        else:
            fuzzy_status = f"completa ({time.time() - tf:.0f}s)"
            results.update(fuzzy_rows)
            n_fuzzy = len(fuzzy_rows)

    # ---- CSV ----
    os.makedirs(os.path.dirname(OUT_CSV), exist_ok=True)
    cols = ["bt2_addr", "bt2_name", "size", "bt3_name", "bt3_addr", "kind", "ratio", "ambiguous_count"]
    out_rows = sorted(results.values(), key=lambda r: r["bt2_addr"])
    with open(OUT_CSV, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=cols)
        w.writeheader()
        for r in out_rows:
            w.writerow({**r, "bt2_addr": "0x%08x" % r["bt2_addr"]})

    # ---- Informe ----
    print("=== INFORME ===")
    print(f"BT2 consideradas: {len(bt2)}")
    print(f"BT3 funciones: {len(bt3)}")
    print(f"Exactos: {n_exact}  Fuzzy: {n_fuzzy}  Total filas: {len(out_rows)}  Fuzzy: {fuzzy_status}")
    ex = [r for r in out_rows if r["kind"] == "exact"]
    amb = [r for r in ex if r["ambiguous_count"] > 1]
    real_ex = [r for r in ex if any(not is_generic(x) for x in r["bt3_name"].split("|"))]
    print(f"Exactos con nombre real (algun candidato no func_): {len(real_ex)}  "
          f"solo func_: {len(ex) - len(real_ex)}")
    print(f"Ambiguos (exact con >1 nombre distinto): {len(amb)}")
    fz = [r for r in out_rows if r["kind"] == "fuzzy"]
    print(f"Fuzzy con nombre real: {sum(not is_generic(r['bt3_name']) for r in fz)}  "
          f"solo func_: {sum(is_generic(r['bt3_name']) for r in fz)}")
    print("\nDesglose por region BT2 (total consideradas / exacto / ambiguo / fuzzy):")
    for label, lo, hi in REGIONS:
        tot = sum(1 for fn in bt2 if lo <= fn["addr"] < hi)
        re_ = [r for r in ex if lo <= r["bt2_addr"] < hi]
        rf = [r for r in fz if lo <= r["bt2_addr"] < hi]
        ra = [r for r in re_ if r["ambiguous_count"] > 1]
        print(f"  {label}: {tot} / {len(re_)} / {len(ra)} / {len(rf)}")
    print("\nEjemplos con nombre real (BT2 -> BT3, exacto):")
    for label, lo, hi in REGIONS:
        exs = [r for r in ex if lo <= r["bt2_addr"] < hi
               and any(not is_generic(x) for x in r["bt3_name"].split("|"))][:10]
        print(f"  [{label}]")
        for r in exs:
            print(f"    {r['bt2_name']} -> {r['bt3_name']}")
    print(f"\nTiempo total: {time.time() - t0:.1f}s")
    print(f"CSV: {OUT_CSV}")


if __name__ == "__main__":
    main()
