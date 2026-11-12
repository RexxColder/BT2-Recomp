#!/usr/bin/env python3
"""Splits the patched functions by how their C differs from the original, to order the boot tests.

Usage: scripts/port_classify.py   (reads build_port/SLUS_214.41.list, writes build_port/class_<A|B|C>.txt)

A: the same operations with the same constants, only registers and order differ (register allocation or
   scheduling: almost certainly equivalent); B: same operation counts but some constant differs; C: different
   operations. Instructions are compared with registers removed and branch/jump targets masked.
"""

import collections
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import BINUTILS, ROOT  # noqa: E402

OUT = ROOT / "build_port"
REG = re.compile(r"\$?\b(zero|at|v[01]|a[0-3]|t\d|s[0-8]|k[01]|gp|sp|fp|ra|f\d+|\$\d+)\b")


def norm(text):
    ops = []
    for line in text.splitlines():
        p = line.split("\t")
        if len(p) < 3 or not re.match(r"\s*[0-9a-f]+:", p[0]):
            continue
        ins = " ".join(p[2:]).split("<")[0].strip()
        mn = ins.split()[0] if ins else ""
        if mn in ("nop",):
            continue
        if mn.startswith(("b", "j")) and mn not in ("jr", "jalr"):
            ins = mn  # target masked
        ops.append(REG.sub("R", ins))
    return ops


def dis(path, start, size):
    return subprocess.run([str(ROOT / (BINUTILS + "objdump")), "-d", "-z", f"--start-address={start:#x}",
                           f"--stop-address={start + size:#x}", str(path)], capture_output=True, text=True).stdout


def main():
    rows = [l.split() for l in (OUT / "SLUS_214.41.list").read_text().splitlines() if l.strip()]
    cls = {"A": [], "B": [], "C": []}
    for addr, _name, size in rows:
        a, n = int(addr, 16), int(size, 16)
        if a >= 0x300000:
            continue
        o, m = norm(dis(ROOT / "disc/SLUS_214.41", a, n)), norm(dis(OUT / "SLUS_214.41", a, n))
        if collections.Counter(o) == collections.Counter(m):
            cls["A"].append(addr)
        elif collections.Counter(x.split()[0] for x in o) == collections.Counter(x.split()[0] for x in m):
            cls["B"].append(addr)
        else:
            cls["C"].append(addr)
    for k, v in cls.items():
        (OUT / f"class_{k}.txt").write_text("\n".join(v) + "\n")
        print(k, len(v))


if __name__ == "__main__":
    main()
