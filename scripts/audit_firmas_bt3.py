#!/usr/bin/env python3
"""Compara firmas BT2 (definicion + declaraciones de llamadores) contra BT3-Decompiled usando config/xmatch_bt3.csv.
Salida: CSV de discrepancias en argv[1]."""
import csv, os, re, sys
from pathlib import Path
from collections import defaultdict

B2 = Path(__file__).resolve().parent.parent
B3 = Path(os.environ.get("BT3_DECOMP", Path.home() / "Proyectos" / "BT3-Decompiled"))
OUT = Path(sys.argv[1])

DEF = re.compile(r"^(?:static\s+)?(?:inline\s+)?([A-Za-z_][\w \t\*]*?)\b(\w+)\s*\(([^;{}()]*)\)\s*\{", re.M)
DECL = re.compile(r"^(?:extern\s+)?([A-Za-z_][\w \t\*]*?)\b(\w+)\s*\(([^;{}()]*)\)\s*;", re.M)
SKIPRET = {"return", "else", "if", "while", "for", "switch", "do", "case", "goto", "sizeof"}

def strip(t):
    t = re.sub(r"/\*.*?\*/", "", t, flags=re.S)
    t = re.sub(r"//[^\n]*", "", t)
    return re.sub(r"#if 0.*?#endif", "", t, flags=re.S)

def cls_type(t):
    t = t.strip()
    if "*" in t or "[" in t: return "i"
    if re.search(r"\b(f32|float)\b", t): return "f"
    if re.search(r"\b(f64|double)\b", t): return "d"
    if re.search(r"\b(s64|u64|long\s+long|s128|u128|__int128)\b", t): return "w"
    return "i"

def sig(ret, params):
    ret = ret.strip()
    if any(w in ret.split() for w in SKIPRET): return None
    r = "v" if re.fullmatch(r"(static\s+)?(inline\s+)?void", ret) else cls_type(ret)
    p = params.strip()
    if p == "": return (r, None)          # sin prototipo
    if p == "void": return (r, "")
    if "..." in p: return (r, "...")
    parts = []
    for x in p.split(","):
        x = re.sub(r"\b\w+\s*$", "", x.strip()) if len(x.split()) > 1 or "*" in x else x
        parts.append(cls_type(x))
    return (r, "".join(parts))

# --- BT3: nombre -> firma de la definicion
b3 = {}
for f in (B3 / "src").rglob("*.c"):
    t = strip(f.read_text(errors="replace"))
    for m in DEF.finditer(t):
        s = sig(m.group(1), m.group(3))
        if s: b3.setdefault(m.group(2), (s, f.relative_to(B3)))

# --- BT2: definiciones y declaraciones por nombre
b2def, b2decl = {}, defaultdict(lambda: defaultdict(list))
files = list((B2 / "port/eq").glob("*.c")) + list((B2 / "src").rglob("*.c"))
for f in files:
    t = strip(f.read_text(errors="replace"))
    rel = str(f.relative_to(B2))
    for m in DEF.finditer(t):
        s = sig(m.group(1), m.group(3))
        if s and (m.group(2) not in b2def or rel.startswith("port/eq")): b2def[m.group(2)] = (s, rel)
    for m in DECL.finditer(t):
        s = sig(m.group(1), m.group(3))
        if s: b2decl[m.group(2)][s].append(rel)

rows = []
for r in csv.DictReader(open(B2 / "config/xmatch_bt3.csv")):
    a = int(r["bt2_addr"], 16)
    n2 = f"func_{a:08X}"
    names = {n2, r["bt2_name"]}
    ref = r["ref_name"]
    if ref not in b3: continue
    (r3, p3), src3 = b3[ref]
    if p3 in (None, "..."): continue
    d = next((b2def[n] for n in names if n in b2def), None)
    def cmp(s):
        r2, p2 = s
        issues = []
        if p2 is None or p2 == "...": return issues
        if len(p2) != len(p3): issues.append(f"aridad {len(p2)}!={len(p3)}")
        n = min(len(p2), len(p3))
        if p2[:n] != p3[:n]: issues.append(f"clases {p2}!={p3}")
        if r2 != r3:
            if r2 == "v" and r3 != "v": issues.append(f"RET_PERDIDO v!={r3}")
            elif r3 == "v": issues.append(f"ret_extra {r2}")
            else: issues.append(f"ret {r2}!={r3}")
        return issues
    if d:
        for i in cmp(d[0]):
            rows.append((r["bt2_addr"], ref, r["kind"], "DEF", d[1], f"{d[0][0]}({d[0][1]})", f"{r3}({p3})", i, 1, str(src3)))
    for n in names:
        for s, where in b2decl.get(n, {}).items():
            for i in cmp(s):
                rows.append((r["bt2_addr"], ref, r["kind"], "DECL", where[0], f"{s[0]}({s[1]})", f"{r3}({p3})", i, len(where), str(src3)))

with open(OUT, "w", newline="") as fo:
    w = csv.writer(fo)
    w.writerow(["bt2_addr", "bt3_name", "kind", "donde", "fichero", "firma_bt2", "firma_bt3", "problema", "n_ficheros", "bt3_src"])
    w.writerows(rows)
print(len(b3), "defs BT3;", len(b2def), "defs BT2;", len(rows), "discrepancias")
