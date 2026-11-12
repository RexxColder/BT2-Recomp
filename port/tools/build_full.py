#!/usr/bin/env python3
"""Compiles ALL of the game's C for the fully native PC build (docs/PLAN_NATIVO.md), no runtime bridge.

Usage: port/tools/build_full.py [--jobs 3] [--only SUBSTR]

Sources: every src/**/*.c (matching decomp; INCLUDE_ASM functions drop out under native_compat.h) and every
port/eq/<ADDR6>.c whose address no src/ file defines. Each goes the gen_native.py way: clang -E with
native_compat.h forced in -> port/tools/ptr32.py (4-byte pointers, PS2 layout) -> clang x86-64 -> object in
port/build/gen/full/obj. Prepared copies live under port/build/gen/full/src (ptr32.py treats port/build/gen as game
text). Writes port/build/gen/full/report.csv (source,status,first error) and prints a summary; the link
(port/tools/link_full.py, next step) takes the objects.
"""

import argparse
import csv
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "port/tools"))
import gen_native as G  # noqa: E402

TRACE = bool(os.environ.get("BT2_TRACE_BUILD"))   # build instrumentado (port/full/plat_trace.c), directorios aparte
OUT = ROOT / ("port/build/gen/full_trace" if TRACE else "port/build/gen/full")
DEF_RE = re.compile(r"^(?!static\b)[A-Za-z_][\w \t\*]*?\b(\w+)\s*\([^;{}]*\)\s*\{", re.M)


def linked_srcs():
    """The C files the matching build links (c subsegments of the splat yamls, as configure.py reads them); the
    other files under src/ are drafts and permuter copies."""
    out = set()
    for y in [ROOT / "config/SLUS_214.41.yaml"] + sorted((ROOT / "config/overlay").glob("*.yaml")):
        for kind, name in re.findall(r"\[0x[0-9A-Fa-f]+, (c|cpp), \"?([\w/]+)\"?\]", y.read_text()):
            out.add(ROOT / "src" / f"{name}.{kind}")
    return sorted(p for p in out if p.exists())


_TARGETS = None


def src_defined_addrs(files):
    """Addresses the files define (by func_XXXXXXXX name or a symbol-file name)."""
    global _TARGETS
    if _TARGETS is None:
        sys.path.insert(0, str(ROOT / "scripts"))
        import fdiff
        _TARGETS = fdiff.targets()
    t = _TARGETS
    out = set()
    for f in files:
        text = re.sub(r"#if 0.*?#endif", "", f.read_text(errors="replace"), flags=re.S)
        for m in DEF_RE.finditer(text):
            n = m.group(1)
            mm = re.fullmatch(r"func_([0-9A-F]{8})", n)
            a = int(mm.group(1), 16) if mm else t.get(n)
            if a is not None:
                out.add(a)
    return out


def sources():
    srcs = linked_srcs()
    # A port/eq file wins over a src/ file whose functions it ALL defines (src/ is the PS2 matching source; some of
    # it is inline MIPS asm the host cannot build, e.g. the VU0 random generator, and would fall back to the
    # recompiler, whose VU0 registers are not gVu0).
    eq_addrs = set()
    for p in (ROOT / "port/eq").glob("*.c"):
        if re.fullmatch(r"[0-9A-Fa-f]{6}", p.stem):
            eq_addrs |= src_defined_addrs([p])
    srcs = [f for f in srcs if not (src_defined_addrs([f]) and src_defined_addrs([f]) <= eq_addrs)]
    have = src_defined_addrs(srcs)
    eqs = [p for p in sorted((ROOT / "port/eq").glob("*.c")) if re.fullmatch(r"[0-9A-Fa-f]{6}", p.stem) and int(p.stem, 16) not in have]
    return srcs + eqs


def build(path):
    rel = path.relative_to(ROOT)
    key = str(rel).replace("/", "__")[:-2]
    src = OUT / "src" / f"{key}.c"
    pre = OUT / "src" / f"{key}.i"
    c = OUT / "src" / f"{key}.nat.c"
    o = OUT / "obj" / f"{key}.o"
    if o.exists() and o.stat().st_mtime > path.stat().st_mtime:
        return str(rel), "OK", "cached"
    # permuter outputs carry their own `asm(".include \"labels.inc\"")` for the MIPS assembler: not for the PC
    text = re.sub(r'^\s*(__)?asm(__)?\s*\(\s*"\.include[^;]*;+', "", path.read_text(errors="replace"), flags=re.M)
    # esperas de hardware en asm MIPS (bc0f / bc2t sobre las condiciones del COP0/COP2): sin hardware no hay nada que
    # esperar (2026-10-13, etapa 4: Dma_WaitCond / Dma_WaitVu1 de src/sys/dma_28B290.c)
    text = re.sub(r'__asm__\s+volatile\s*\(\s*"\.set noreorder\\n"\s*"0:\\n"(?:\s*"[^"]*")*?\s*"bc[02][ft] 0b\\n"(?:\s*"[^"]*")*?\s*\)\s*;',
                  "/* espera de hardware omitida en el host */", text)
    src.write_text(text)
    r = subprocess.run(["clang", "-E", "-m64", "-I", str(ROOT / "include"), "-include", str(G.COMPAT),
                        "-D__ptr32=", "-D__uptr=", str(src), "-o", str(pre)], capture_output=True, text=True)
    if r.returncode:
        return str(rel), "preprocess", (r.stderr.strip().splitlines() or ["?"])[-1][:160]
    r = subprocess.run([sys.executable, str(ROOT / "port/tools/ptr32.py"), str(pre), "-m64", "-fms-extensions", "-w",
                        "-Wno-int-conversion", "-Wno-incompatible-pointer-types",
                        "-Wno-incompatible-function-pointer-types", "-Wno-implicit-function-declaration",
                        "-Wno-implicit-int"], capture_output=True, text=True)
    if r.returncode:
        return str(rel), "ptr32", (r.stderr.strip().splitlines() or ["?"])[-1][:160]
    c.write_text(r.stdout)
    r = G.compile_c(c, o)
    if r.returncode:
        err = [l for l in r.stderr.splitlines() if "error" in l] or r.stderr.splitlines() or ["?"]
        return str(rel), "compile", err[0][:160]
    return str(rel), "OK", ""


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--jobs", type=int, default=3)
    ap.add_argument("--only")
    a = ap.parse_args()
    (OUT / "src").mkdir(parents=True, exist_ok=True)
    (OUT / "obj").mkdir(parents=True, exist_ok=True)
    todo = [p for p in sources() if not a.only or a.only in str(p)]
    print(f"{len(todo)} sources", flush=True)
    rows, counts = [], {}
    with ThreadPoolExecutor(a.jobs) as ex:
        for i, row in enumerate(ex.map(build, todo)):
            rows.append(row)
            counts[row[1]] = counts.get(row[1], 0) + 1
            if i % 500 == 499:
                print(f"  {i + 1}/{len(todo)} {counts}", flush=True)
    if a.only and (OUT / "report.csv").exists():   # --only actualiza las filas, no pisa el informe entero
        old = {r[0]: r for r in list(csv.reader((OUT / "report.csv").open()))[1:]}
        old.update({r[0]: r for r in rows})
        rows = list(old.values())
    with open(OUT / "report.csv", "w", newline="") as f:
        csv.writer(f).writerows([("source", "status", "error")] + rows)
    print(counts)


if __name__ == "__main__":
    main()
