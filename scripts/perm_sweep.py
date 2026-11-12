#!/usr/bin/env python3
"""Runs decomp-permuter, unattended, on m2c's near misses, and keeps what it gets to match.

Usage: scripts/perm_sweep.py [--max-ratio 0.1] [--max-insns 120] [--seconds 90] [--jobs 6] [--range LO HI]
                             [--write]

Candidates: rows of scratch/m2c_sweep/status.csv with `differs n/m`, n/m <= --max-ratio, m <= --max-insns, whose
address is not in config/c_files.txt. For each, build/permuter/sweep/<ADDR>/ gets
  base.c      the m2c draft (scratch/m2c_sweep/m2c_XXXXXX.c) preprocessed;
  target.o    the function's own .s (scratch/m2c_sweep/<ADDR8>.s) assembled with the prelude, checked against
              the original image like permute.py does;
  compile.sh, objdump.sh, settings.toml  as scripts/permute.py writes them,
and the permuter runs on it (one thread, --stop-on-zero) for at most --seconds. A score-0 output is checked
with fdiff.py (and data_split.py when it has data); the ones that pass become src/auto/perm_XXXXXX.c with
`START END auto/perm_XXXXXX  # perm` in config/c_files.txt (--write). The gate (gate_prune.py) is the judge.
Results per candidate: build/permuter/sweep/status.csv.
"""

import argparse
import csv
import re
import shutil
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402
import data_split  # noqa: E402
import fdiff  # noqa: E402
import integrate_xfer  # noqa: E402
import permute  # noqa: E402

PERMUTER = ROOT / "tools" / "decomp-permuter"
SWEEP = ROOT / "build" / "permuter" / "sweep"
DRAFTS = ROOT / "scratch" / "m2c_sweep"
TAG = "# perm"
SRC_KEY = "src/auto/x.c"  # the -G flags of src/auto (where the results go)


def setup(addr, name):
    work = SWEEP / f"{addr:08X}"
    shutil.rmtree(work, ignore_errors=True)
    work.mkdir(parents=True)
    permute.write_compile_sh(work / "compile.sh", SRC_KEY)
    permute.write_objdump_sh(work / "objdump.sh", name)
    draft = DRAFTS / f"m2c_{addr:06X}.c"
    r = permute.run([permute.CC, "-E", "-P", "-Iinclude", draft, "-o", work / "base.c"])
    if r.returncode:
        return None, "preprocess"
    s = DRAFTS / f"{addr:08X}.s"
    wrapper = work / "target.s"
    wrapper.write_text(s.read_text().replace('.include "macro.inc"', '.include "include/macro.inc"'))
    r = permute.run([permute.AS, "-EL", "-march=r5900", "-mabi=o64", "-Iinclude", "-I.",
                     fdiff.as_gflag(SRC_KEY), "-mno-pdr", "include/gcc_prelude.inc", wrapper,
                     "-o", work / "target.o"])
    if r.returncode:
        return None, "assemble: " + r.stderr.strip().splitlines()[-1][:80]
    (work / "settings.toml").write_text(
        f'func_name = "{name}"\ncompiler_type = "gcc"\n'
        f'objdump_command = "{work / "objdump.sh"}"\n\n[weight_overrides]\n{permute.WEIGHTS}')
    return work, None


def one(job, seconds):
    addr, name, size = job
    work, why = setup(addr, name)
    if not work:
        return addr, name, size, None, why
    try:
        subprocess.run([sys.executable, str(PERMUTER / "permuter.py"), str(work), "-j1", "--stop-on-zero",
                        "--best-only", "--quiet"], cwd=ROOT, capture_output=True, text=True, timeout=seconds)
    except subprocess.TimeoutExpired:
        pass
    outs = sorted(work.glob("output-0-*/source.c"))
    if not outs:
        scores = sorted(int(p.name.split("-")[1]) for p in work.glob("output-*"))
        return addr, name, size, None, f"best {scores[0]}" if scores else "no progress"
    for out in outs:
        c = work / f"perm_{addr:06X}.c"
        c.write_text(out.read_text())
        rel = c.relative_to(ROOT)
        v = subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), str(rel), name], cwd=ROOT,
                           capture_output=True, text=True)
        if not re.search(rf"^{re.escape(name)}: OK", v.stdout, re.M):
            continue
        obj = fdiff.compile_src(rel, "default")
        sizes = integrate_xfer.section_sizes(obj)
        if sizes.get(".bss", 0) or sizes.get(".sbss", 0) or sizes.get(".sbss_init", 0):
            continue
        placed = []
        if any(sizes.get(sec, 0) for sec in data_split.SECTIONS):
            placed, _ = data_split.place(obj, addr)
            if not placed:
                continue
        return addr, name, size, (c.read_text(), placed), "OK"
    return addr, name, size, None, "score 0 but fdiff differs"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-ratio", type=float, default=0.1)
    ap.add_argument("--max-insns", type=int, default=120)
    ap.add_argument("--seconds", type=int, default=90)
    ap.add_argument("--jobs", type=int, default=6)
    ap.add_argument("--range", nargs=2)
    ap.add_argument("--write", action="store_true")
    a = ap.parse_args()
    lo, hi = (int(a.range[0], 16), int(a.range[1], 16)) if a.range else (0, 1 << 32)
    taken = sorted((int(l.split()[0], 16), int(l.split()[1], 16))
                   for l in (ROOT / "config/c_files.txt").read_text().splitlines() if l.strip())
    jobs = []
    for r in csv.DictReader(open(DRAFTS / "status.csv")):
        m = re.match(r"differs (\d+)/(\d+)", r["status"])
        addr = int(r["addr"], 16)
        if not m or not lo <= addr < hi or any(x <= addr < y for x, y in taken):
            continue
        n, tot = int(m.group(1)), int(m.group(2))
        if n <= max(1, tot * a.max_ratio) and tot <= a.max_insns and (DRAFTS / f"m2c_{addr:06X}.c").exists():
            jobs.append((addr, r["name"], int(r["size"], 16)))
    print(f"{len(jobs)} candidates, {a.seconds}s each on {a.jobs} jobs: up to "
          f"{len(jobs) * a.seconds / a.jobs / 60:.0f} min", flush=True)
    SWEEP.mkdir(parents=True, exist_ok=True)
    results, status, why = [], [], {}
    with ThreadPoolExecutor(a.jobs) as ex:
        for i, (addr, name, size, res, reason) in enumerate(ex.map(lambda j: one(j, a.seconds), jobs)):
            status.append(f"0x{addr:08X},{name},{size:#x},{reason}")
            why[reason.split()[0]] = why.get(reason.split()[0], 0) + 1
            if res:
                results.append((addr, size, res))
            if i % 50 == 49:
                print(f"  {i + 1}/{len(jobs)}: {why}", flush=True)
    (SWEEP / "status.csv").write_text("addr,name,size,status\n" + "\n".join(sorted(status)) + "\n")
    print(f"OK: {len(results)} functions ({sum(r[1] for r in results):#x} bytes); {why}")
    if not a.write:
        return
    cf = ROOT / "config/c_files.txt"
    lines = [l for l in cf.read_text().splitlines() if l.strip()]
    df = ROOT / "config/data_files.txt"
    dlines = [l for l in df.read_text().splitlines() if l.strip()] if df.exists() else []
    for addr, size, (text, placed) in sorted(results):
        stem = f"auto/perm_{addr:06X}"
        (ROOT / "src" / f"{stem}.c").write_text(text)
        lines.append(f"0x{addr:08X} 0x{addr + size:08X} {stem}  {TAG}")
        dlines += [f"{sec} 0x{x:08X} 0x{y:08X} {stem}  {TAG}" for sec, x, y in placed]
    cf.write_text("\n".join(sorted(lines, key=lambda l: int(l.split()[0], 16))) + "\n")
    df.write_text("\n".join(sorted(dlines, key=lambda l: int(l.split()[1], 16))) + "\n")
    print(f"wrote {len(results)} files")


if __name__ == "__main__":
    main()
