#!/usr/bin/env python3
"""bt3_names.py for the menu overlay: BT2 DBZP.BIN (raw, loaded at 0x3B3100) against BT3's DBZP.elf.
Same normalisation (jal targets, lui/addiu/ori/load/store immediates masked); exact sha1 match, then difflib
>= 0.90 among functions of similar length. Output build_port/bt3_names_ovl.csv (same columns)."""
import csv, difflib, hashlib, os, struct, sys
from collections import defaultdict
from pathlib import Path
ROOT = Path(__file__).resolve().parent.parent
BT3_ROOT = Path(os.environ.get("BT3_DECOMP", Path.home() / "Proyectos" / "BT3-Decompiled"))
sys.path.insert(0, str(ROOT / "scripts"))
import bt3_names as B

BIN = open(ROOT / "gamedata" / "BIN" / "DBZP.BIN", "rb").read()
BASE = 0x3B3100
bt2 = []
for r in list(csv.reader(open(B.BT2_MAP)))[1:]:
    a, e = int(r[1], 16), int(r[2], 16)
    if a >= BASE and e - BASE <= len(BIN):
        bt2.append((a, r[0], e - a, B.normalize(B.words_of(BIN[a - BASE:e - BASE]))))
elf = B.Elf(str(BT3_ROOT / "build" / "DBZP.elf"))
bt3 = []
for n, v, s, t, _ in elf.symbols():
    if t == 2 and s > 0:
        code = elf.read(v, s)
        if code:
            bt3.append((v, n, B.normalize(B.words_of(code))))
idx = defaultdict(list)
for v, n, w in bt3:
    idx[B.exact_key(w)].append((v, n))
rows, ex, fz = [], 0, 0
for a, n, sz, w in bt2:
    hit = idx.get(B.exact_key(w))
    if hit:
        names = sorted({x[1] for x in hit})
        rows.append((f"0x{a:08x}", n, sz, "|".join(names), f"0x{hit[0][0]:08x}", "exact", "1.000", len(names))); ex += 1
        continue
    if len(w) < 8:
        continue
    best = None
    for v, n3, w3 in bt3:
        if abs(len(w3) - len(w)) <= 0.1 * len(w):
            r = difflib.SequenceMatcher(None, w, w3, autojunk=False).ratio()
            if r >= 0.90 and (not best or r > best[0]):
                best = (r, v, n3)
    if best:
        rows.append((f"0x{a:08x}", n, sz, best[2], f"0x{best[1]:08x}", "fuzzy", f"{best[0]:.3f}", 1)); fz += 1
with open(ROOT / "build_port" / "bt3_names_ovl.csv", "w", newline="") as f:
    csv.writer(f).writerows([("bt2_addr", "bt2_name", "size", "bt3_name", "bt3_addr", "kind", "ratio", "ambiguous_count")] + rows)
print(f"BT2 {len(bt2)} BT3 {len(bt3)} exact {ex} fuzzy {fz}")
