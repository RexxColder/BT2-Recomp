#!/usr/bin/env python3
"""Finds where a C file's own data (.rodata/.data/.sdata/.lit4/.lit8) sits in the original image.

Usage: scripts/data_split.py FILE.c START

The text of FILE.c is taken as linked at START (as in scripts/integrate_xfer.resolve). Every relocation of the
text against a data section symbol (`.rodata`, `.lit4`, ...: what a string literal, a float constant or a static
table becomes) is resolved against the original bytes, which gives the original address of that section's
start. A section is placed when all its relocations agree on one address, that address keeps the section's
alignment, and the original bytes there are the object's bytes (words the data section relocates itself,
pointer and jump tables, are not compared). The result is the subsegment splat needs, one line per section of
config/data_files.txt:

    .rodata 0x0026C200 0x0026C260 battle/foo_10A2F0

which scripts/gen_yaml.py cuts out of the asm data, BT3-Decompiled's `[0xOFFSET, .rodata, src]` form.
Exit 0 and print the lines when every data section of the object is placed; 1 with the reason otherwise.
"""

import re
import struct
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import BINUTILS, ROOT  # noqa: E402
import fdiff  # noqa: E402

SECTIONS = (".rodata", ".data", ".sdata", ".lit4", ".lit8")
GP = 0x0038BDF0


def readelf(*args):
    return subprocess.run([str(ROOT / (BINUTILS + "readelf")), *args], capture_output=True, text=True).stdout


def sections(obj):
    """name -> (size, align) of the allocated sections."""
    out = {}
    for line in readelf("-SW", str(obj)).splitlines():
        m = re.match(r"\s*\[\s*\d+\]\s+(\S+)\s+\S+\s+[0-9a-f]+\s+[0-9a-f]+\s+([0-9a-f]+)\s+\S+\s+\S*\s+\S+\s+\S+\s+(\d+)\s*$",
                     line)
        if m:
            out[m.group(1)] = (int(m.group(2), 16), int(m.group(3)))
    return out


def relocations(obj):
    """section -> [(offset, type, symbol)] for every .rel.<section>."""
    rels, cur = defaultdict(list), None
    for line in readelf("-rW", str(obj)).splitlines():
        m = re.match(r"Relocation section '\.rel(\S+)'", line)
        if m:
            cur = m.group(1)
            continue
        p = line.split()
        if cur and len(p) >= 5 and p[2].startswith("R_MIPS"):
            rels[cur].append((int(p[0], 16), p[2], p[4]))
    return rels


def section_bytes(obj, name):
    out = Path(str(obj) + name.replace(".", "_") + ".bin")
    subprocess.run([str(ROOT / (BINUTILS + "objcopy")), "-O", "binary", "--only-section", name, str(obj), str(out)],
                   check=True, capture_output=True)
    data = out.read_bytes()
    out.unlink()
    return data


def original_bytes(addr, size):
    words = fdiff.original_words(addr & ~3, (size + (addr & 3) + 3) & ~3)
    raw = b"".join(struct.pack("<I", w) for w in words)
    return raw[addr & 3:(addr & 3) + size]


def defined_data(obj, wanted):
    """symbol -> (section, offset) for the data symbols the object defines in the wanted sections."""
    names = {}
    for line in readelf("-SW", str(obj)).splitlines():
        m = re.match(r"\s*\[\s*(\d+)\]\s+(\S+)", line)
        if m:
            names[m.group(1)] = m.group(2)
    out = {}
    for line in readelf("-sW", str(obj)).splitlines():
        p = line.split()
        if len(p) == 8 and p[3] == "OBJECT" and names.get(p[6]) in wanted:
            out[p[7]] = (names[p[6]], int(p[1], 16))
    return out


def place(obj, start):
    """(lines, None) with one (section, start, end) per data section, or (None, reason)."""
    try:
        return _place(obj, start)
    except IndexError:
        # The object's text runs past the end of the original image (a longer function): nothing to place.
        return None, "text runs past the original image"


def _place(obj, start):
    secs = sections(obj)
    wanted = [s for s in SECTIONS if secs.get(s, (0, 0))[0]]
    if not wanted:
        return [], None
    text = fdiff.text_bytes(obj)
    mine = lambda off: struct.unpack_from("<I", text, off)[0]  # noqa: E731
    orig = lambda off: fdiff.original_words(start + off, 4)[0]  # noqa: E731
    sext = lambda v: v - 0x10000 if v & 0x8000 else v  # noqa: E731
    rels = relocations(obj)
    bases, pending_hi = defaultdict(set), defaultdict(list)
    named = defined_data(obj, wanted)
    for off, kind, sym in rels.get(".text", []):
        if sym not in wanted and sym not in named:
            continue
        # A named variable: its address less its offset in the section is the section's start.
        sec, delta = named.get(sym, (sym, 0))
        if kind == "R_MIPS_HI16":
            pending_hi[sym].append(off)
        elif kind == "R_MIPS_LO16" and pending_hi[sym]:
            hi_off = pending_hi[sym].pop(0)
            value = ((orig(hi_off) & 0xFFFF) << 16) + sext(orig(off) & 0xFFFF)
            addend = ((mine(hi_off) & 0xFFFF) << 16) + sext(mine(off) & 0xFFFF)
            bases[sec].add((value - addend - delta) & 0xFFFFFFFF)
        elif kind in ("R_MIPS_GPREL16", "R_MIPS_LITERAL"):
            bases[sec].add((GP + sext(orig(off) & 0xFFFF) - sext(mine(off) & 0xFFFF) - delta) & 0xFFFFFFFF)
    lines = []
    for sec in wanted:
        size, align = secs[sec]
        if len(bases[sec]) != 1:
            return None, f"{sec}: {len(bases[sec])} candidate addresses " + \
                ", ".join(f"{b:#x}" for b in sorted(bases[sec])[:4])
        base = next(iter(bases[sec]))
        if base % max(align, 1):
            return None, f"{sec}: {base:#x} is not {align}-aligned"
        data, ref = section_bytes(obj, sec), original_bytes(base, size)
        masked = {off for off, _, _ in rels.get(sec, [])}
        for i in range(0, size, 4):
            if i in masked:
                continue
            if data[i:i + 4] != ref[i:i + 4]:
                return None, f"{sec}: bytes differ at {base + i:#x}"
        lines.append((sec, base, base + size))
    return lines, None


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    src, start = Path(sys.argv[1]), int(sys.argv[2], 16)
    obj = fdiff.compile_src(src, "default")
    if obj is None:
        sys.exit(f"{src}: does not compile")
    lines, why = place(obj, start)
    if why:
        print(f"{src}: {why}")
        return 1
    stem = str(src.with_suffix("")).removeprefix("src/")
    for sec, a, b in lines:
        print(f"{sec} 0x{a:08X} 0x{b:08X} {stem}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
