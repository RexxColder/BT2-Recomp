#!/usr/bin/env python3
"""Adds the gameplay overlay DBZP.BIN to the translation: its functions to port/funcmap.csv and its bytes to an
ELF the recompiler reads (port/build/combined.elf). Run by scripts/recomp.py after funcmap.py.

Usage: scripts/overlay.py            (needs `splat split config/overlay/DBZP.yaml` done once -> asm_ovl/)

PS2Recomp has no interpreter: a jump into code it did not translate is an error. The game loads DBZP.BIN raw
at a fixed address (func_001002D8, always index 0 = cdrom0:\\BIN\\DBZP.BIN), so it is translated ahead of time
like the boot ELF: one combined ELF, one function table. At run time the runtime still loads the original
SLUS_214.41 and the game reads DBZP.BIN itself; the combined ELF is only the recompiler's input.
"""

import re
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import BINUTILS, ROOT, TARGETS  # noqa: E402

BIN = ROOT / "disc/DBZP.BIN"
BASE = 0x3B3100
TEXT_END = 0x421300  # last `jr $ra` at 0x4212F8; data after it (splat yaml: data subsegment at 0x6E200)
GLABEL = re.compile(r"^glabel (\w+)\n(?:.*\n){0,3}?\s+/\* [0-9A-F]+ ([0-9A-F]{8}) ", re.M)
COMBINED = ROOT / "port/build/combined.elf"


def main():
    image = BIN.read_bytes()

    def word(addr):
        off = addr - BASE
        return struct.unpack_from("<I", image, off)[0] if 0 <= off <= len(image) - 4 else None

    starts = {}
    for path in sorted((ROOT / "asm_ovl").rglob("*.s")):
        if "data" in path.parts:
            continue
        for m in GLABEL.finditer(path.read_text()):
            starts[int(m.group(2), 16)] = m.group(1)
    found = len(starts)
    # Pointers in the overlay's data to a function start (same test as funcmap.py: frame-allocating prologue or
    # right after a `jr $ra` + delay slot): callbacks, vtables and state tables splat cannot see.
    for a in range(TEXT_END, BASE + len(image) - 3, 4):
        p = word(a)
        if p is None or p % 4 or not BASE <= p < TEXT_END or p in starts:
            continue
        ins = word(p)
        if (ins >> 16 == 0x27BD and ins & 0x8000) or word(p - 8) == 0x03E00008:
            starts[p] = f"func_{p:08X}"
    print(f"overlay: {found} functions from splat, {len(starts) - found} through data pointers")

    fm = ROOT / "port/funcmap.csv"
    have = [r for r in fm.read_text().splitlines() if r and r[0] != "N" and BASE <= int(r.split(",")[1], 16) < TEXT_END]
    if not found and have:
        # No splat output (asm_ovl/ gone): the map's overlay rows stay; data pointers alone find a few dozen of
        # its ~500 functions, and losing the rest leaves jals into the overlay without a translation.
        print(f"overlay: no asm_ovl/, keeping the {len(have)} overlay functions already in port/funcmap.csv")
        starts = {}
    rows = [r for r in fm.read_text().splitlines() if r and not (r[0] != "N" and BASE <= int(r.split(",")[1], 16) < TEXT_END)]
    if not starts:
        rows = fm.read_text().splitlines()
    order = sorted(starts)
    for i, addr in enumerate(order):
        end = order[i + 1] if i + 1 < len(order) else TEXT_END
        rows.append(f"{starts[addr]},0x{addr:08X},0x{end:08X},{end - addr}")
    fm.write_text("\n".join(rows) + "\n")

    COMBINED.parent.mkdir(parents=True, exist_ok=True)
    text = COMBINED.with_suffix(".ovltext")
    data = COMBINED.with_suffix(".ovldata")
    text.write_bytes(image[:TEXT_END - BASE])
    data.write_bytes(image[TEXT_END - BASE:])
    subprocess.run([str(ROOT / (BINUTILS + "objcopy")), str(ROOT / TARGETS[0]["elf"]), str(COMBINED),
                    "--add-section", f".text.ovl={text}",
                    "--set-section-flags", ".text.ovl=alloc,load,readonly,code",
                    "--change-section-address", f".text.ovl=0x{BASE:X}",
                    "--add-section", f".data.ovl={data}",
                    "--set-section-flags", ".data.ovl=alloc,load,data",
                    "--change-section-address", f".data.ovl=0x{TEXT_END:X}"], check=True)
    print(f"overlay: {len(order) or len(have)} functions -> port/funcmap.csv; {COMBINED.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
