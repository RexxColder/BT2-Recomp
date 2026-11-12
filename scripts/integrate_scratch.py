#!/usr/bin/env python3
"""Moves a tool's verified scratch results into the build (the gate is still the judge).

Usage: scripts/integrate_scratch.py OK_LIST SRC_DIR DEST_DIR TAG [DATA_LIST]
  e.g. scripts/integrate_scratch.py scratch/jtbl/ok.txt scratch/jtbl/src auto "# jtbl" scratch/jtbl/data.txt

OK_LIST lines: `0xSTART 0xEND stem` (stem = file name in SRC_DIR without .c). Each file is copied to
src/DEST_DIR/<stem>.c and gets `START END DEST_DIR/stem  TAG` in config/c_files.txt, unless its range overlaps a
C file already listed. DATA_LIST lines (`.rodata 0xA 0xB <any path ending in stem>`, data_split.py's output)
go to config/data_files.txt under the new stem. Lines of a previous run with the same TAG are replaced.
"""

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402


def main():
    if len(sys.argv) < 5:
        sys.exit(__doc__)
    ok, src_dir, dest, tag = Path(sys.argv[1]), Path(sys.argv[2]), sys.argv[3], sys.argv[4]
    data = Path(sys.argv[5]) if len(sys.argv) > 5 else None
    cf = ROOT / "config/c_files.txt"
    lines = [l for l in cf.read_text().splitlines() if l.strip() and tag not in l]
    taken = sorted((int(l.split()[0], 16), int(l.split()[1], 16)) for l in lines)
    added, skipped = {}, 0
    for row in ok.read_text().splitlines():
        p = row.split()
        if len(p) < 3:
            continue
        s, e, stem = int(p[0], 16), int(p[1], 16), Path(p[2]).name.removesuffix(".c")
        if any(a < e and s < b for a, b in taken):
            skipped += 1
            continue
        (ROOT / "src" / dest).mkdir(parents=True, exist_ok=True)
        (ROOT / "src" / dest / f"{stem}.c").write_text((src_dir / f"{stem}.c").read_text())
        taken.append((s, e))
        added[stem] = f"0x{s:08X} 0x{e:08X} {dest}/{stem}  {tag}"
    cf.write_text("\n".join(sorted(lines + list(added.values()), key=lambda l: int(l.split()[0], 16))) + "\n")
    if data:
        df = ROOT / "config/data_files.txt"
        dl = [l for l in df.read_text().splitlines() if l.strip() and tag not in l] if df.exists() else []
        for row in data.read_text().splitlines():
            p = row.split()
            if len(p) >= 4 and Path(p[3]).name.removesuffix(".c") in added:
                dl.append(f"{p[0]} 0x{int(p[1], 16):08X} 0x{int(p[2], 16):08X} {dest}/{Path(p[3]).name.removesuffix('.c')}"
                          f"  {tag}")
        df.write_text("\n".join(sorted(dl, key=lambda l: int(l.split()[1], 16))) + "\n")
    print(f"{len(added)} files added, {skipped} overlap an existing C file")


if __name__ == "__main__":
    main()
