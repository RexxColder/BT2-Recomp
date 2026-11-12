#!/usr/bin/env python3
"""Calls whose argument count disagrees with what the callee reads (like Tenkaichi3Decomp's check_protos.py).

Reference arity of each function = the parameters in its Hex-Rays signature (scratch/hexrays/f/<ADDR6>.c, first
line), which IDA infers from the registers the function reads. Each port/eq and src C file is scanned for calls
`name(...)`; a call with FEWER arguments than the callee reads means the caller's C dropped one (usually a
pass-through argument), MORE is harmless on x86-64 but flags a wrong declaration. Writes
build_port/check_protos.csv (caller_file, callee, callee_addr, passed, reads) and prints a summary.
Usage: port/tools/check_protos.py [--only-fewer] [--hexrays-only]
"""
import csv, re, sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
HR = ROOT / "scratch/hexrays/f"
sys.path.insert(0, str(ROOT / "scripts"))
import fdiff  # noqa: E402

def hexrays_arity():
    out = {}
    for f in HR.glob("*.c"):
        lines = f.read_text(errors="replace").splitlines()
        sig = next((l for l in lines[1:4] if "(" in l), "")
        m = re.search(r"\((.*)\)\s*$", sig)
        if not m:
            continue
        ps = m.group(1).strip()
        if "..." in ps:
            continue
        out[int(f.stem, 16)] = 0 if ps in ("", "void") else ps.count(",") + 1
    return out

def ctx_arity():
    """Arity from scratch/protos/ctx.h (scripts/infer_protos.py, from the asm). A call is reported only when BOTH it
    and Hex-Rays say the callee reads more: on BT2 this kept 19 of 25 real cases and dropped 52 of 55 false ones
    (Hex-Rays over-counts registers a callee only passes on)."""
    out = {}
    f = ROOT / "scratch/protos/ctx.h"
    if f.exists():
        for l in f.read_text().splitlines():
            m = re.match(r"\w[\w\s\*]*?\b(\w+)\((.*)\);", l)
            if m:
                ps = m.group(2).strip()
                out[m.group(1)] = 0 if ps in ("", "void") else ps.count(",") + 1
    return out

def call_args(text, start):
    i, depth, n, empty = start, 1, 1, True
    while i < len(text) and depth:
        ch = text[i]
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        elif ch == "," and depth == 1:
            n += 1
        if depth and not ch.isspace():
            empty = False
        i += 1
    return 0 if empty else n

def main():
    only_fewer = "--only-fewer" in sys.argv
    ar = hexrays_arity()
    ctx = {} if "--hexrays-only" in sys.argv else ctx_arity()
    names = {n: a for n, a in fdiff.targets().items() if "." not in n}
    files = sorted((ROOT / "port/eq").glob("*.c"))
    rows, kinds = [], Counter()
    call_re = re.compile(r"\b((?:func|sub)_([0-9A-Fa-f]{6,8})|[A-Za-z_]\w*)\s*\(")
    for f in files:
        text = re.sub(r"/\*.*?\*/|//[^\n]*", "", f.read_text(errors="replace"), flags=re.S)
        own = int(f.stem, 16)
        for m in call_re.finditer(text):
            name = m.group(1)
            addr = int(m.group(2), 16) if m.group(2) else names.get(name)
            if addr is None or addr == own or addr not in ar:
                continue
            # skip declarations/definitions: preceded by a type word on the same statement start
            pre = text[max(0, m.start() - 40):m.start()]
            if re.search(r"(?:^|[;{}\n])\s*(?:extern\s+)?(?:static\s+)?[\w\s\*]+\s$", pre) and \
               re.search(r"\b(void|s32|u32|s16|u16|s8|u8|f32|s64|u64|int|char|float|long|unsigned)\s*\**\s*$", pre):
                continue
            n = call_args(text, m.end())
            want = ar[addr]
            if n == want:
                continue
            kind = "fewer" if n < want else "more"
            if kind == "fewer" and ctx and ctx.get(name, want) <= n:
                continue
            if only_fewer and kind == "more":
                continue
            kinds[kind] += 1
            rows.append((f.name, name, f"0x{addr:08X}", n, want))
    out = ROOT / "build_port/check_protos.csv"
    with open(out, "w", newline="") as fh:
        csv.writer(fh).writerows([("caller", "callee", "addr", "passed", "reads")] + sorted(set(rows)))
    callers = len({r[0] for r in rows if r[3] < r[4]})
    print(f"Hex-Rays arities: {len(ar)}; mismatching calls: {dict(kinds)}; caller files with too few args: {callers} -> {out}")

if __name__ == "__main__":
    main()
