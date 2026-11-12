#!/usr/bin/env python3
"""Definicion compilada `void` cuyo asm, en algun `jr $ra`, deja en $v0 un valor puesto a proposito justo antes
(constante, copia de registro o carga) -> la funcion devuelve algo aunque nadie la llame directamente (callbacks)."""
import csv, re
from pathlib import Path

B2 = Path(__file__).resolve().parent.parent
ASM = B2 / "scratch/m2c_sweep"
INS = re.compile(r"\*/\s+(\S+)\s*(.*)$")
comp = [B2 / r["source"] for r in csv.DictReader(open(B2 / "port/build/gen/full/report.csv")) if r["status"] == "OK"]
DEF = re.compile(r"^(?:static\s+)?([A-Za-z_][\w \t\*]*?)\b(func_[0-9A-F]{8})\s*\(([^;{}()]*)\)\s*\{", re.M)
defs = {}
for f in comp:
    for m in DEF.finditer(re.sub(r"#if 0.*?#endif", "", f.read_text(errors="replace"), flags=re.S)):
        defs[m.group(2)] = (m.group(1).strip(), f)

SETV0 = re.compile(r"^(addiu|daddu|or|lw|lhu|lh|lbu|lb|li|slt|sltu|sltiu|slti|xori|andi|move|addu|subu|dsubu|lui)$")
for n, (r, f) in sorted(defs.items()):
    if not re.fullmatch(r"(static\s+)?void", r):
        continue
    p = ASM / f"{n[5:]}.s"
    if not p.exists():
        continue
    I = [(m.group(1), m.group(2).strip()) for m in map(INS.search, p.read_text(errors="replace").splitlines()) if m]
    hits = []
    for i, (op, a) in enumerate(I):
        if op != "jr" or a != "$ra":
            continue
        # el delay slot y hasta 4 instrucciones antes (saltando restauraciones de pila)
        win = I[max(0, i - 5):i + 2]
        for op2, a2 in reversed(win):
            d = a2.split(",")[0].strip()
            if op2 in ("jal", "jalr") or op2.startswith("b"):
                break
            if d == "$v0" and SETV0.match(op2):
                hits.append(f"{op2} {a2}")
                break
    if hits:
        print(f"{n} | {f.relative_to(B2)} | {' ; '.join(sorted(set(hits)))[:120]}")
