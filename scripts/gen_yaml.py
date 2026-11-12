#!/usr/bin/env python3
"""Rewrites the `segments:` block of each target's splat yaml from the ELF's sections plus config/c_files.txt.

Usage: scripts/gen_yaml.py

The base layout is one subsegment per allocated ELF section (elf_survey.yaml_segments, the way BT3-Decompiled
started). Every `start end src` line of config/c_files.txt (src without extension; `.cpp` is used when that file
exists) cuts its range out of the `asm` subsegment holding it: `[start, c, src]`, and the rest of the assembly
continues as `[end, asm, cod/END]`. Running it again gives the same yaml, so c_files.txt is the one list to edit.

A C file's own data comes from config/data_files.txt (`.rodata start end src`, scripts/data_split.py): each
line cuts its range out of the data subsegment of that kind as `[start, .rodata, src]` (BT3's yaml form), the
rest continuing as `[end, rodata, cod/END]`. Flattened ELFs (no sections) are not handled here:
RE Outbreak's tools/gen_yaml.py does that from a Ghidra function map.
"""

import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT, TARGETS  # noqa: E402
import elf_survey  # noqa: E402


def c_ranges(base):
    path = ROOT / "config" / "c_files.txt"
    out = []
    if path.exists():
        for line in path.read_text().splitlines():
            line = line.split("#", 1)[0].strip()
            if line:
                a, b, src = line.split()
                kind = "cpp" if (ROOT / "src" / f"{src}.cpp").exists() else "c"
                out.append((int(a, 16) - base, int(b, 16) - base, kind, src))
    return sorted(out)


DATA_KINDS = {".rodata": "rodata", ".data": "data", ".sdata": "sdata", ".lit4": "lit4", ".lit8": "lit8"}


def data_ranges(base):
    """kind -> [(start, end, ".kind", src)] from config/data_files.txt."""
    path = ROOT / "config" / "data_files.txt"
    out = {}
    if path.exists():
        for line in path.read_text().splitlines():
            line = line.split("#", 1)[0].strip()
            if line:
                sec, a, b, src = line.split()
                out.setdefault(DATA_KINDS[sec], []).append((int(a, 16) - base, int(b, 16) - base, sec, src))
    return {k: sorted(v) for k, v in out.items()}


def splice(lines, ranges, data=None):
    """Cut each C range out of the asm subsegment that holds it, and each data range out of its data kind."""
    data = data or {}
    sub = re.compile(r"^(\s+- )\[(0x[0-9A-Fa-f]+), (\w+), ([\w/]+)\](.*)$")
    entries = []
    for line in lines:
        m = sub.match(line)
        entries.append([int(m.group(2), 16), m.group(3), m.group(4), m.group(5)] if m else line)
    starts = [e[0] for e in entries if isinstance(e, list)] + [1 << 32]
    out = []
    for e in entries:
        if not isinstance(e, list) or (e[1] != "asm" and e[1] not in data):
            out.append(e)
            continue
        lo = e[0]
        hi = min(s for s in starts if s > lo)
        cur = [lo, e[1], e[2], e[3]]
        for a, b, kind, src in (ranges if e[1] == "asm" else data[e[1]]):
            if not lo <= a < hi:
                continue
            if b > hi:
                sys.exit(f"{src}: range ends past its section")
            if a > cur[0]:
                out.append(cur)
            out.append([a, kind, src, ""])
            cur = [b, e[1], f"cod/{b:06X}", ""]
        if cur[0] < hi:
            out.append(cur)
    return [e if isinstance(e, str) else f"      - [{e[0]:#08X}, {e[1]}, {e[2]}]{e[3]}".replace("0X", "0x")
            for e in out]


def main():
    for t in TARGETS:
        if t["flatten"] or "elf" not in t:
            print(f"{t['name']}: skipped (flattened or not an ELF target)")
            continue
        base = t["image"][0]
        segs = elf_survey.yaml_segments(ROOT / t["elf"]).splitlines()
        segs = splice(segs, c_ranges(base), data_ranges(base))
        path = ROOT / t["yaml"]
        head = path.read_text().split("\nsegments:", 1)[0]
        path.write_text(head + "\n" + "\n".join(segs) + "\n")
        print(f"{t['name']}: {sum(1 for s in segs if ', c,' in s or ', cpp,' in s)} C subsegments")


if __name__ == "__main__":
    main()
