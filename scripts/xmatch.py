#!/usr/bin/env python3
"""Finds BT2 functions that are the same code as a function of another decomp of the same engine (BT3-Decompiled).

Usage: scripts/xmatch.py [--ref ~/Proyectos/BT3-Decompiled] [--fuzzy 0.90] [--out config/xmatch_bt3.csv]

Each function is reduced to its instruction shape: the opcode and registers stay, everything that depends on where
the code and data were linked goes (the 26-bit target of j/jal, the 16-bit immediate of loads, stores, lui and
addiu, which hold %hi/%lo/%gp_rel parts). Branch offsets stay: they are relative and only move if the code changed.
Two functions with the same shape compiled from the same C with the same compiler; the reference decomp's C for
that function is then a candidate for ours, checked by scripts/fdiff.py like any other C.

Output CSV: bt2_addr,bt2_name,kind,score,ref_addr,ref_name,ref_src (ref_src = the .c that holds it in the
reference, empty when it is still INCLUDE_ASM there). kind = exact | fuzzy.
"""

import argparse
import difflib
import re
import struct
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import BINUTILS, ROOT  # noqa: E402

BRANCH_OPS = {1, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17}
STRICT = "--strict" in sys.argv


def shape(word):
    op = word >> 26
    if op in (2, 3):                      # j / jal: target is an address
        return op << 26
    if op == 0 or op in BRANCH_OPS or op in (0x10, 0x11, 0x12, 0x1C):  # special, branches, cop0/1/2, mmi
        return word
    return word & 0xFFFF0000              # i-type: the immediate may be an address part


def elf_loader(path):
    """addr -> bytes reader for an ELF's PT_LOAD segments."""
    data = path.read_bytes()
    phoff, = struct.unpack_from("<I", data, 0x1C)
    phentsize, phnum = struct.unpack_from("<HH", data, 0x2A)
    segs = []
    for i in range(phnum):
        p_type, off, vaddr, _, filesz = struct.unpack_from("<IIIII", data, phoff + i * phentsize)
        if p_type == 1 and filesz:
            segs.append((vaddr, off, filesz))

    def read(addr, size):
        for vaddr, off, filesz in segs:
            if vaddr <= addr and addr + size <= vaddr + filesz:
                return data[off + addr - vaddr: off + addr - vaddr + size]
        return None
    return read


def raw_loader(path, base):
    data = path.read_bytes()
    return lambda addr, size: data[addr - base: addr - base + size] if 0 <= addr - base <= len(data) - size else None


def shapes(read, start, end):
    raw = read(start, end - start)
    if raw is None or len(raw) < 8:
        return None
    words = struct.unpack_from(f"<{len(raw) // 4}I", raw)
    # Trailing alignment nops differ with the next function's alignment: drop them.
    n = len(words)
    while n > 1 and words[n - 1] == 0 and words[n - 2] != 0x03E00008:
        n -= 1
    if not STRICT:
        return tuple(shape(w) for w in words[:n])
    # Strict: an i-type immediate is an address part only when its base is $gp or a register a `lui` loaded
    # (%hi/%lo pair); otherwise it is a struct offset or a constant and must be equal, so structs that changed
    # layout between the games do not pair.
    out, hi = [], set()
    for w in words[:n]:
        op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        s = shape(w)
        if op == 0x0F:                       # lui
            hi.add(rt)
        elif s != w and rs != 28 and rs not in hi and op not in (2, 3):
            s = w                            # keep the offset/constant
        if op not in (2, 3, 0x0F) and op not in BRANCH_OPS and op != 0 and rt in hi and rt != rs and op < 0x28:
            hi.discard(rt)                   # a load/addi into the register ends its %hi life
        out.append(s)
    return tuple(out)


def nm_functions(elf):
    """[(addr, size, name)] of the defined functions (nm -S) of a linked ELF."""
    out = subprocess.run([str(ROOT / (BINUTILS + "nm")), "-S", "-n", str(elf)], capture_output=True, text=True).stdout
    funcs = []
    for line in out.splitlines():
        p = line.split()
        if len(p) == 4 and p[2] in "Tt" and not p[3].endswith(".NON_MATCHING") and not p[3].startswith((".", "$")):
            funcs.append((int(p[0], 16), int(p[1], 16), p[3]))
    return funcs


def ref_sources(ref):
    """name -> src path for every function the reference has in C (not INCLUDE_ASM)."""
    names = {}
    for c in sorted((ref / "src").rglob("*.c")):
        text = c.read_text(errors="replace")
        asm = set(re.findall(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)", text))
        for m in re.finditer(r"^[A-Za-z_][\w\s\*]*?\b(\w+)\s*\([^;{]*\)\s*\{", text, re.M):
            if m.group(1) not in asm:
                names.setdefault(m.group(1), str(c.relative_to(ref)))
    return names


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--ref", type=Path, default=Path.home() / "Proyectos/BT3-Decompiled")
    ap.add_argument("--fuzzy", type=float, default=0.90)
    ap.add_argument("--strict", action="store_true")
    ap.add_argument("--out", type=Path, default=ROOT / "config/xmatch_bt3.csv")
    a = ap.parse_args()

    # Reference: main executable + overlay, function extents from the linked rebuild, bytes from the disc.
    ref_funcs = []
    for elf, disc, base in [("build/SLUS_216.78.elf", "disc/SLUS_216.78", None),
                            ("build/DBZP.elf", "disc/BIN/DBZP.BIN", 0x334C00)]:
        if not (a.ref / elf).exists():
            continue
        read = elf_loader(a.ref / disc) if base is None else raw_loader(a.ref / disc, base)
        for addr, size, name in nm_functions(a.ref / elf):
            s = shapes(read, addr, addr + size)
            if s:
                ref_funcs.append((addr, name, s))
    src_of = ref_sources(a.ref)
    by_shape = defaultdict(list)
    for f in ref_funcs:
        by_shape[f[2]].append(f)

    # BT2: the function map the port uses (boot ELF + overlay).
    read_main = elf_loader(ROOT / "disc/SLUS_214.41")
    read_ovl = raw_loader(ROOT / "disc/DBZP.BIN", 0x3B3100)
    ours = []
    for row in (ROOT / "port/funcmap.csv").read_text().splitlines()[1:]:
        name, start, end, _ = row.split(",")
        start, end = int(start, 16), int(end, 16)
        s = shapes(read_ovl if start >= 0x3B3100 else read_main, start, end)
        if s and len(s) >= 4:
            ours.append((start, name, s))

    rows, fuzzy_pool = [], defaultdict(list)
    for f in ref_funcs:
        fuzzy_pool[len(f[2]) // 8].append(f)
    exact = fuzzy = 0
    for addr, name, s in ours:
        hit = by_shape.get(s)
        kind, score = "exact", 1.0
        if hit:
            # Several reference functions with one shape (wrappers): prefer one that is in C.
            ref = next((h for h in hit if h[1] in src_of), hit[0])
            exact += 1
        else:
            ref, score = None, 0.0
            if len(s) >= 12:
                for bucket in range(len(s) * 9 // 80, len(s) * 11 // 80 + 1):
                    for cand in fuzzy_pool.get(bucket, ()):
                        sm = difflib.SequenceMatcher(None, s, cand[2], autojunk=False)
                        if sm.real_quick_ratio() < a.fuzzy or sm.quick_ratio() < a.fuzzy:
                            continue
                        r = sm.ratio()
                        if r > score:
                            ref, score = cand, r
            if not ref or score < a.fuzzy:
                continue
            kind = "fuzzy"
            fuzzy += 1
        rows.append(f"0x{addr:08X},{name},{kind},{score:.3f},0x{ref[0]:08X},{ref[1]},{src_of.get(ref[1], '')}")
    a.out.parent.mkdir(parents=True, exist_ok=True)
    a.out.write_text("bt2_addr,bt2_name,kind,score,ref_addr,ref_name,ref_src\n" + "\n".join(rows) + "\n")
    in_c = sum(1 for r in rows if r.split(",")[6])
    print(f"{len(ours)} BT2 functions, {len(ref_funcs)} reference functions ({len(src_of)} in C)")
    print(f"exact {exact}, fuzzy>={a.fuzzy} {fuzzy}; with reference C: {in_c} -> {a.out}")


if __name__ == "__main__":
    main()
