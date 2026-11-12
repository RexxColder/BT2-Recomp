#!/usr/bin/env python3
"""Retorno perdido seguro: definicion COMPILADA void + el asm original de un llamador usa $v0/$f0 tras el jal + el C de
ese llamador lee el valor. Indice de llamadores precalculado (una pasada sobre el asm)."""
import csv, re
from pathlib import Path
from collections import defaultdict

B2 = Path(__file__).resolve().parent.parent
ASM = B2 / "scratch/m2c_sweep"
INS = re.compile(r"\*/\s+(\S+)\s*(.*)$")

idx = defaultdict(list)   # callee -> [(caller, usa_v0, usa_f0)]
for s in ASM.glob("00*.s"):
    I = [(m.group(1), m.group(2).strip()) for m in map(INS.search, s.read_text(errors="replace").splitlines()) if m]
    for i, (op, a) in enumerate(I):
        if op != "jal" or not a.startswith("func_"):
            continue
        res = {}
        for reg in ("$v0", "$f0"):
            used = False
            for op2, a2 in I[i + 2:i + 40]:
                regs = [x.strip() for x in a2.replace("(", ",").replace(")", "").split(",")]
                if reg in regs[1:] or (op2.startswith(("s", "b", "jr")) and reg in regs):
                    used = True
                    break
                if regs and regs[0] == reg:
                    break
                if op2 in ("jal", "jalr", "jr", "j") or op2.startswith("b"):
                    break
            res[reg] = used
        idx[a].append((s.stem, res["$v0"], res["$f0"]))

comp = [B2 / r["source"] for r in csv.DictReader(open(B2 / "port/build/gen/full/report.csv")) if r["status"] == "OK"]
DEF = re.compile(r"^(?:static\s+)?([A-Za-z_][\w \t\*]*?)\b(func_[0-9A-F]{8})\s*\(([^;{}()]*)\)\s*\{", re.M)
defs, text = {}, {}
for f in comp:
    t = re.sub(r"#if 0.*?#endif", "", f.read_text(errors="replace"), flags=re.S)
    text[f] = t
    for m in DEF.finditer(t):
        defs[m.group(2)] = (m.group(1).strip(), f)

voids = {n for n, (r, f) in defs.items() if re.fullmatch(r"(static\s+)?void", r)}
for n in sorted(voids):
    users = sorted({c for c, v, fl in idx.get(n, []) if v or fl})
    if not users:
        continue
    readers = []
    for c in users:
        t = text.get(B2 / "port/eq" / f"{c[2:]}.c")
        if t and re.search(rf"(=|\(|!|&&|\|\||return|[<>+\-*/,?:])\s*(\([^()]*\)\s*)?{n}\s*\(", t):
            readers.append(c)
    if readers:
        print(f"{n} | def {defs[n][1].relative_to(B2)} | asm usa {len(users)}/{len(idx[n])} | C lee: {' '.join(readers[:6])}")
