#!/usr/bin/env python3
"""Puts the transplanted functions that fdiff found identical (config/xfer_results.csv, status OK) into the build.

Usage: scripts/integrate_xfer.py [--ref DIR] [--dry]

1. Runs: OK functions that follow each other in port/funcmap.csv and come from the same reference file become
   one source file src/<ref dir>/<ref name>_<START>.c (same preamble as the trial file, only those functions).
2. Each run is compiled; a run whose object has data of its own (.rodata/.data/.sdata/.lit4/.lit8: string
   literals, float constants, tables) goes in with its data subsegments (config/data_files.txt) when
   scripts/data_split.py places every section, and is left out otherwise.
3. Symbols: every relocation of the run objects is resolved against the original bytes at the same place
   (%hi/%lo pairs, %gp_rel, jal targets), giving each name the reference C uses its BT2 address ->
   config/symbols/bt3_data.txt (only names BT2 does not have yet; a name seen at two addresses is dropped).
4. config/c_files.txt gets `START END src` for each run (other lines kept).
Then: scripts/gen_yaml.py && .venv/bin/python configure.py && ninja (the byte-identical check is the gate).
"""

import argparse
import csv
import re
import struct
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import BINUTILS, ROOT, TARGETS  # noqa: E402
import fdiff  # noqa: E402
import transplant  # noqa: E402
import data_split  # noqa: E402

DATA_SECTIONS = (".rodata", ".data", ".sdata", ".lit4", ".lit8", ".sbss_init")
GP = 0x0038BDF0


def section_sizes(obj):
    out = subprocess.run([str(ROOT / (BINUTILS + "readelf")), "-SW", str(obj)], capture_output=True, text=True).stdout
    sizes = {}
    for line in out.splitlines():
        m = re.match(r"\s*\[\s*\d+\]\s+(\S+)\s+\S+\s+[0-9a-f]+\s+[0-9a-f]+\s+([0-9a-f]+)", line)
        if m:
            sizes[m.group(1)] = int(m.group(2), 16)
    return sizes


def relocations(obj):
    """[(text offset, type, symbol)] of .rel.text."""
    out = subprocess.run([str(ROOT / (BINUTILS + "readelf")), "-rW", str(obj)], capture_output=True, text=True).stdout
    rels, cur = [], False
    for line in out.splitlines():
        if line.startswith("Relocation section"):
            cur = "'.rel.text'" in line
            continue
        p = line.split()
        if cur and len(p) >= 5 and p[2].startswith("R_MIPS"):
            rels.append((int(p[0], 16), p[2], p[4]))
    return rels


def resolve(obj, start, symbols):
    """Adds name -> BT2 address for the relocations of obj, whose .text is linked at `start`."""
    text = fdiff.text_bytes(obj)
    mine = lambda off: struct.unpack_from("<I", text, off)[0]  # noqa: E731
    orig = lambda off: fdiff.original_words(start + off, 4)[0]  # noqa: E731
    sext = lambda v: v - 0x10000 if v & 0x8000 else v  # noqa: E731
    rels = relocations(obj)
    pending_hi = {}
    for off, kind, sym in rels:
        if sym.startswith("."):
            continue
        if kind == "R_MIPS_26":
            target = ((start + off) & 0xF0000000) | ((orig(off) & 0x03FFFFFF) << 2)
            symbols[sym].add(target - ((mine(off) & 0x03FFFFFF) << 2))
        elif kind == "R_MIPS_HI16":
            pending_hi.setdefault(sym, []).append(off)
        elif kind == "R_MIPS_LO16" and pending_hi.get(sym):
            hi_off = pending_hi[sym].pop(0)
            value = ((orig(hi_off) & 0xFFFF) << 16) + sext(orig(off) & 0xFFFF)
            addend = ((mine(hi_off) & 0xFFFF) << 16) + sext(mine(off) & 0xFFFF)
            symbols[sym].add((value - addend) & 0xFFFFFFFF)
        elif kind in ("R_MIPS_GPREL16", "R_MIPS_LITERAL"):
            symbols[sym].add((GP + sext(orig(off) & 0xFFFF) - sext(mine(off) & 0xFFFF)) & 0xFFFFFFFF)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--ref", type=Path, default=Path.home() / "Proyectos/BT3-Decompiled")
    ap.add_argument("--csv", type=Path, default=ROOT / "config/xmatch_bt3_strict.csv")
    ap.add_argument("--dry", action="store_true")
    a = ap.parse_args()

    # The symbols of previous runs were confirmed by a byte-identical build and other files use them: kept, and
    # this run only adds to them. They must not count as known while resolving (they are rewritten at the end).
    bt3_data = ROOT / "config/symbols/bt3_data.txt"
    prev = re.findall(r"^(\w+) = 0x([0-9A-Fa-f]+);", bt3_data.read_text(), re.M) if bt3_data.exists() else []

    ok = {int(r["bt2_addr"], 16): r for r in csv.DictReader(open(ROOT / "config/xfer_results.csv"))
          if r["status"] == "OK"}
    pair = {int(r["bt2_addr"], 16): r for r in csv.DictReader(open(a.csv)) if r["kind"] == "exact"}
    fmap = [(int(r.split(",")[1], 16), int(r.split(",")[2], 16)) for r in
            (ROOT / "port/funcmap.csv").read_text().splitlines()[1:]]
    ends = dict(fmap)
    order = [s for s, _ in fmap]

    # Only the copy that owns the reference name (the others are xfer_dups.py's, under their own names).
    names = transplant.load_names(a.csv)
    firsts = {int(r["bt2_addr"], 16) for r in names.pairs}
    ok = {k: v for k, v in ok.items() if k in firsts}
    # Functions another C file (leaf sweep, agents, copies) already covers stay with it.
    cf_lines = [l for l in (ROOT / "config/c_files.txt").read_text().splitlines()
                if l.strip() and "from BT3-Decompiled" not in l]
    other = sorted((int(l.split()[0], 16), int(l.split()[1], 16)) for l in cf_lines)
    ok = {k: v for k, v in ok.items() if not any(x <= k < y for x, y in other)}
    runs, cur = [], []
    for s in order:
        r = ok.get(s)
        if r and cur and r["ref_src"] == ok[cur[-1]]["ref_src"]:
            cur.append(s)
            continue
        if cur:
            runs.append(cur)
        cur = [s] if r else []
    if cur:
        runs.append(cur)

    symbols = defaultdict(set)
    kept, skipped_data, data_lines = [], 0, []
    for run in runs:
        src_ref = ok[run[0]]["ref_src"]
        wanted = {pair[s]["ref_name"] for s in run}
        dest = Path(src_ref).with_name(f"{Path(src_ref).stem}_{run[0]:06X}.c")
        text = transplant.build_file(a.ref, src_ref, wanted, names)
        (ROOT / dest).parent.mkdir(parents=True, exist_ok=True)
        (ROOT / dest).write_text(text)
        # Calls and loads aimed at the copy the original uses (BT2 repeats helpers per module).
        subprocess.run([sys.executable, str(ROOT / "scripts/fix_targets.py"), str(dest), f"{run[0]:x}", "--write",
                        "--keep-unknown"],
                       cwd=ROOT, capture_output=True)
        obj = fdiff.compile_src(dest, "default")
        sizes = section_sizes(obj)
        stem = str(dest.with_suffix("").relative_to("src"))
        if any(sizes.get(sec, 0) for sec in DATA_SECTIONS):
            # Its own data goes in too when scripts/data_split.py finds every section at one original address.
            placed, _ = data_split.place(obj, run[0])
            if not placed or sizes.get(".sbss_init", 0):
                skipped_data += len(run)
                (ROOT / dest).unlink()
                continue
            data_lines += [(sec, a2, b2, stem) for sec, a2, b2 in placed]
        resolve(obj, run[0], symbols)
        kept.append((run[0], ends[run[-1]], stem))

    # Symbol files only: the linked ELF still has the names of the bt3_data.txt this run is replacing.
    elf = ROOT / TARGETS[0]["elf_out"]
    stale = elf.with_suffix(".elf.stale")
    if elf.exists():
        elf.replace(stale)
    # Nor the bt3_data.txt names: they are this script's own, re-added below from `prev`.
    side = bt3_data.with_suffix(".prev")
    if bt3_data.exists():
        bt3_data.replace(side)
    known = fdiff.targets()
    if side.exists():
        side.replace(bt3_data)
    if stale.exists():
        stale.replace(elf)
    # Addresses that already carry a real name (symbol files); splat's auto names (func_/D_XXXXXXXX) give way.
    used = set()
    for path in sorted((ROOT / "config").glob("symbol_addrs*.txt")) + sorted((ROOT / "config/symbols").glob("*.txt")):
        if path.name == "bt3_data.txt":
            continue
        used |= {int(m, 16) for m in re.findall(r"^\w+ = 0x([0-9A-Fa-f]+);", path.read_text(), re.M)}
    known = {k: v for k, v in known.items() if not re.fullmatch(r"(func|D|jtbl)_[0-9A-F]{8}", k)}
    lines, dropped = [], 0
    for sym, addr in prev:
        if sym not in known and int(addr, 16) not in used:
            used.add(int(addr, 16))
            lines.append(f"{sym} = 0x{int(addr, 16):08X};")
    have = {l.split()[0] for l in lines}
    for sym, addrs in sorted(symbols.items()):
        if sym in known or sym in have:
            continue
        # Two names for one address: the reference C calls it by another name (an alias, or two BT3 functions
        # that BT2 merged). splat allows one: such a file needs that name changed by hand, so leave it out.
        if len(addrs) != 1 or next(iter(addrs)) in used:
            dropped += 1
            continue
        addr = addrs.pop()
        used.add(addr)
        lines.append(f"{sym} = 0x{addr:08X};")
    # Files that use a name nothing resolves (ambiguous or dropped above) cannot link: leave them out, and again
    # for the names those files defined, until the set is closed.
    defined = set(known) | {l.split()[0] for l in lines}
    undef = {}
    for k in kept:
        o = fdiff.compile_src(Path("src") / (k[2] + ".c"), "default")
        nm = subprocess.run([str(ROOT / (BINUTILS + "nm")), str(o)], capture_output=True, text=True).stdout
        undef[k] = {p[1] for p in (l.split() for l in nm.splitlines()) if len(p) == 2 and p[0] == "U"}
        defined |= {p[2] for p in (l.split() for l in nm.splitlines()) if len(p) == 3 and p[1] == "T"}
    gone = 0
    while True:
        bad = [k for k in kept if undef[k] - defined]
        if not bad:
            break
        for k in bad:
            kept.remove(k)
            (ROOT / "src" / (k[2] + ".c")).unlink()
            gone += 1
        defined = set(known) | {l.split()[0] for l in lines}
        for k in kept:
            o = scratch_obj = fdiff.scratch(Path("src") / (k[2] + ".c"), "default") / (Path(k[2]).name + ".o")
            nm = subprocess.run([str(ROOT / (BINUTILS + "nm")), str(o)], capture_output=True, text=True).stdout
            defined |= {p[2] for p in (l.split() for l in nm.splitlines()) if len(p) == 3 and p[1] == "T"}
    print(f"{gone} files left out: they use a name with no single BT2 address")
    nfun = sum(1 for s, e, _ in kept for a2 in order if s <= a2 < e)
    print(f"{len(runs)} runs; kept {len(kept)} files ({nfun} functions), {skipped_data} functions left out "
          f"(their file has its own data); {len(lines)} new symbols, {dropped} ambiguous")
    if a.dry:
        return
    bt3_data.write_text("\n".join(sorted(lines)) + "\n")
    cf = ROOT / "config/c_files.txt"
    old = [l for l in cf.read_text().splitlines() if l.strip()] if cf.exists() else []
    mine = {k[2] for k in kept}
    # Lines of a previous run of this script are replaced, and their files removed when no longer kept.
    for l in old:
        if "from BT3-Decompiled" in l and l.split()[2] not in mine:
            stale = ROOT / "src" / (l.split()[2] + ".c")
            if stale.exists():
                stale.unlink()  # machine-made: regenerated from BT3 on each run
    old = [l for l in old if "from BT3-Decompiled" not in l]
    new = old + [f"0x{s:08X} 0x{e:08X} {src}  # from BT3-Decompiled" for s, e, src in kept]
    cf.write_text("\n".join(sorted(new, key=lambda l: int(l.split()[0], 16))) + "\n")
    # Their data subsegments (config/data_files.txt, read by gen_yaml.py), same tagging.
    df = ROOT / "config/data_files.txt"
    dold = [l for l in df.read_text().splitlines() if l.strip() and "from BT3-Decompiled" not in l] if df.exists() else []
    alive = {k[2] for k in kept}
    dnew = dold + [f"{sec} 0x{a2:08X} 0x{b2:08X} {st}  # from BT3-Decompiled" for sec, a2, b2, st in data_lines
                   if st in alive]
    df.write_text("\n".join(sorted(dnew, key=lambda l: int(l.split()[1], 16))) + "\n")


if __name__ == "__main__":
    main()
