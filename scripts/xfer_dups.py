#!/usr/bin/env python3
"""Gives BT3's C to the second copies: BT2 functions with the same code as a BT3 function whose name is taken.

Usage: scripts/xfer_dups.py [--ref DIR] [--dry]

BT2 repeats some code (each module has its own Vec4_*/Mtx_* helpers, VU0 wrappers, ...). transplant.py gives a
reference name to the first copy only (one name, one address); the other copies stay in asm. Here each of them
is transplanted under the name a symbol file gives its address, else splat's own func_XXXXXXXX (no symbol file
entry needed), in runs of
consecutive copies from one reference file, as integrate_xfer.py does. Each file is then
 - checked with fdiff (every function OK),
 - retargeted with fix_targets.py --write (the copy calls its own module's helpers, not the first copy's),
 - placed with data_split.py when it has data of its own (config/data_files.txt).
Kept files get `START END src  # bt3 copy` in config/c_files.txt (lines of a previous run replaced); the build
gate (gate_prune.py) is the judge, as for the other machine-made files.
"""

import argparse
import csv
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402
import data_split  # noqa: E402
import fdiff  # noqa: E402
import integrate_xfer  # noqa: E402
import transplant  # noqa: E402

TAG = "# bt3 copy"


def in_c(lines):
    rng = sorted((int(l.split()[0], 16), int(l.split()[1], 16)) for l in lines)
    return lambda a: any(s <= a < e for s, e in rng)


def fdiff_ok(src, wanted):
    r = subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), str(src), *wanted], cwd=ROOT,
                       capture_output=True, text=True)
    verdicts = [l for l in r.stdout.splitlines() if re.match(r"\w+: ", l)]
    return r.returncode == 0 and verdicts and all(": OK" in l for l in verdicts)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--ref", type=Path, default=Path.home() / "Proyectos/BT3-Decompiled")
    ap.add_argument("--csv", type=Path, default=ROOT / "config/xmatch_bt3_strict.csv")
    ap.add_argument("--dry", action="store_true")
    a = ap.parse_args()

    cf = ROOT / "config/c_files.txt"
    old = [l for l in cf.read_text().splitlines() if l.strip()]
    for l in old:  # files of a previous run are rebuilt
        if TAG in l and (ROOT / "src" / (l.split()[2] + ".c")).exists():
            (ROOT / "src" / (l.split()[2] + ".c")).unlink()
    old = [l for l in old if TAG not in l]
    taken = in_c(old)

    names = transplant.load_names(a.csv)
    first_addr = {int(r["bt2_addr"], 16) for r in names.pairs}
    rows = [r for r in csv.DictReader(open(a.csv)) if r["kind"] == "exact" and r["ref_src"]
            and int(r["bt2_addr"], 16) < 0x3B3100 and int(r["bt2_addr"], 16) not in first_addr
            and not taken(int(r["bt2_addr"], 16))]
    copy = {int(r["bt2_addr"], 16): r for r in rows}
    # An address a symbol file already names (a name some C or asm uses) keeps that name.
    named = {}
    for path in sorted((ROOT / "config").glob("symbol_addrs*.txt")) + sorted((ROOT / "config/symbols").glob("*.txt")):
        for m in re.finditer(r"^(\w+) = 0x([0-9A-Fa-f]+);", path.read_text(), re.M):
            named.setdefault(int(m.group(2), 16), m.group(1))
    fmap = [(int(r.split(",")[1], 16), int(r.split(",")[2], 16)) for r in
            (ROOT / "port/funcmap.csv").read_text().splitlines()[1:]]
    ends = dict(fmap)
    runs, cur = [], []
    for s, _ in fmap:
        r = copy.get(s)
        # One reference function once per file: a run never holds two copies of the same function.
        if r and cur and r["ref_src"] == copy[cur[-1]]["ref_src"] and \
                r["ref_name"] not in {copy[c]["ref_name"] for c in cur}:
            cur.append(s)
            continue
        if cur:
            runs.append(cur)
        cur = [s] if r else []
    if cur:
        runs.append(cur)

    kept, data_lines, why = [], [], {}
    for run in runs:
        src_ref = copy[run[0]]["ref_src"]
        local = transplant.Names(names)
        local.addr_map, local.pairs = names.addr_map, names.pairs
        for s in run:
            local[copy[s]["ref_name"]] = named.get(s, f"func_{s:08X}")
        wanted = {copy[s]["ref_name"] for s in run}
        dest = Path(src_ref).with_name(f"{Path(src_ref).stem}_c{run[0]:06X}.c")
        path = ROOT / dest
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(transplant.build_file(a.ref, src_ref, wanted, local))
        fnames = [named.get(s, f"func_{s:08X}") for s in run]
        if not fdiff_ok(dest, fnames):
            why["fdiff"] = why.get("fdiff", 0) + 1
            path.unlink()
            continue
        subprocess.run([sys.executable, str(ROOT / "scripts/fix_targets.py"), str(dest), f"{run[0]:x}", "--write"],
                       cwd=ROOT, capture_output=True)
        obj = fdiff.compile_src(dest, "default")
        stem = str(dest.with_suffix("").relative_to("src"))
        sizes = integrate_xfer.section_sizes(obj) if obj else {}
        if obj is None or sizes.get(".sbss_init", 0):
            why["compile"] = why.get("compile", 0) + 1
            path.unlink()
            continue
        if any(sizes.get(sec, 0) for sec in data_split.SECTIONS):
            placed, reason = data_split.place(obj, run[0])
            if not placed:
                why["data"] = why.get("data", 0) + 1
                path.unlink()
                continue
            data_lines += [(sec, x, y, stem) for sec, x, y in placed]
        kept.append((run[0], ends[run[-1]], stem))
    nfun = sum(1 for s, e, _ in kept for f, _ in fmap if s <= f < e)
    print(f"{len(rows)} second copies in {len(runs)} runs: kept {len(kept)} files ({nfun} functions); left out {why}")
    if a.dry:
        for _, _, stem in kept:
            (ROOT / "src" / (stem + ".c")).unlink()
        return
    new = old + [f"0x{s:08X} 0x{e:08X} {stem}  {TAG}" for s, e, stem in kept]
    cf.write_text("\n".join(sorted(new, key=lambda l: int(l.split()[0], 16))) + "\n")
    df = ROOT / "config/data_files.txt"
    dold = [l for l in df.read_text().splitlines() if l.strip() and TAG not in l] if df.exists() else []
    dnew = dold + [f"{sec} 0x{x:08X} 0x{y:08X} {stem}  {TAG}" for sec, x, y, stem in data_lines]
    df.write_text("\n".join(sorted(dnew, key=lambda l: int(l.split()[1], 16))) + "\n")


if __name__ == "__main__":
    main()
