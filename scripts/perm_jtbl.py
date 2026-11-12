#!/usr/bin/env python3
"""Runs decomp-permuter on the jump-table near misses of scratch/jtbl/near.txt (scripts/jtbl_sweep.py).

Usage: scripts/perm_jtbl.py [--seconds 120] [--jobs 2] [--only 0x00120E98,...]

Per row of scratch/jtbl/near.txt, build/permuter/jtbl/<ADDR8>/ gets (as scripts/perm_sweep.py's setup does):
  base.c      scratch/jtbl/src/jt_<ADDR6>.c preprocessed (its switch, so the jump table, is in the C);
  target.o    scratch/jtbl/asm/<ADDR8>.s (the function and its .rodata table) assembled with the prelude;
  compile.sh, objdump.sh, settings.toml  as scripts/permute.py writes them.
The permuter runs -j1 --stop-on-zero --best-only --quiet for at most --seconds. A score-0 output counts only when
scripts/fdiff.py says OK and scripts/data_split.py places its .rodata; then it replaces scratch/jtbl/src/jt_<ADDR6>.c
(the draft is restored otherwise) and goes to scratch/jtbl/ok.txt and data.txt in the jtbl_sweep formats.
Every row is listed in scratch/jtbl/perm_status.csv (addr,name,status: OK, `best N` or `score 0 but fdiff differs`).
The permuter subprocess runs in its own process group, so a timeout kills all of its children.
"""

import argparse
import csv
import os
import re
import shutil
import signal
import subprocess
import sys
import threading
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402
import data_split  # noqa: E402
import fdiff  # noqa: E402
import integrate_xfer  # noqa: E402
import permute  # noqa: E402

PERMUTER = ROOT / "tools" / "decomp-permuter"
WORK = ROOT / "build" / "permuter" / "jtbl"
SCRATCH = ROOT / "scratch" / "jtbl"
SRC_KEY = "src/auto/x.c"  # the -G flags of src/auto, as perm_sweep uses
LOCK = threading.Lock()


def setup(addr, name):
    """(work dir, None) or (None, reason): the permuter directory of one function."""
    work = WORK / f"{addr:08X}"
    shutil.rmtree(work, ignore_errors=True)
    work.mkdir(parents=True)
    permute.write_compile_sh(work / "compile.sh", SRC_KEY)
    permute.write_objdump_sh(work / "objdump.sh", name)
    draft = SCRATCH / "src" / f"jt_{addr:06X}.c"
    if not draft.exists():
        return None, "no draft"
    r = permute.run([permute.CC, "-E", "-P", "-Iinclude", draft, "-o", work / "base.c"])
    if r.returncode:
        return None, "preprocess"
    s = SCRATCH / "asm" / f"{addr:08X}.s"
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


def run_permuter(work, seconds):
    """The permuter for `seconds`, in its own process group; the group is killed at the timeout.
    Its output goes to work/permuter.log (not --quiet: the score lines are the only record of the best score).
    Returns the lowest score it printed (None if none)."""
    log = work / "permuter.log"
    with log.open("w") as f:
        p = subprocess.Popen([sys.executable, str(PERMUTER / "permuter.py"), str(work), "-j1", "--stop-on-zero",
                              "--best-only"], cwd=ROOT, stdout=f, stderr=subprocess.STDOUT, start_new_session=True)
        try:
            p.wait(timeout=seconds)
        except subprocess.TimeoutExpired:
            os.killpg(p.pid, signal.SIGTERM)
            p.wait()
    scores = [int(x) for x in re.findall(r"score = (\d+)", log.read_text(errors="replace"))]
    return min(scores) if scores else None


def check(addr, name, cpath):
    """(ok_line, data_lines) when fdiff and data_split pass for the C at cpath, else None."""
    rel = cpath.relative_to(ROOT)
    v = subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), str(rel), name], cwd=ROOT,
                       capture_output=True, text=True)
    if not re.search(rf"^{re.escape(name)}: OK", v.stdout, re.M):
        return None
    obj = fdiff.compile_src(rel, "default")
    sec = integrate_xfer.section_sizes(obj)
    if sec.get(".bss", 0) or sec.get(".sbss", 0) or sec.get(".sbss_init", 0):
        return None
    r = subprocess.run([sys.executable, str(ROOT / "scripts/data_split.py"), str(rel), f"0x{addr:08X}"],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        return None
    return r.stdout.splitlines()


def record(addr, name, size, status, data_lines):
    """Writes one row to perm_status.csv and, on a pass, to ok.txt and data.txt (under LOCK)."""
    with LOCK:
        tag = f"jt_{addr:06X}"
        p = SCRATCH / "perm_status.csv"
        rows = {}
        if p.exists():
            for line in p.read_text().splitlines()[1:]:
                if line.strip():
                    rows[int(line.split(",")[0], 16)] = line
        rows[addr] = f"0x{addr:08X},{name},{status}"
        p.write_text("addr,name,status\n" + "\n".join(rows[k] for k in sorted(rows)) + "\n")
        if data_lines is None:
            return
        for fname, new, col in (("ok.txt", [f"0x{addr:08X} 0x{addr + size:08X} {tag}"], 0),
                                ("data.txt", data_lines, 1)):
            f = SCRATCH / fname
            keep = []
            if f.exists():
                keep = [l for l in f.read_text().splitlines() if l.strip() and not l.split()[-1].endswith(tag)]
            keep += new
            keep.sort(key=lambda l: int(l.split()[col], 16))
            f.write_text("\n".join(keep) + "\n")


def one(job, seconds):
    addr, name, size = job
    work, why = setup(addr, name)
    if not work:
        record(addr, name, size, why, None)
        return addr, why
    best = run_permuter(work, seconds)
    outs = sorted(work.glob("output-0-*/source.c"))
    if not outs:
        status = f"best {best}" if best is not None else "no score"
        record(addr, name, size, status, None)
        return addr, status
    draft = SCRATCH / "src" / f"jt_{addr:06X}.c"
    original = draft.read_text()
    for out in outs:
        draft.write_text(out.read_text())
        data = check(addr, name, draft)
        if data is not None:
            record(addr, name, size, "OK", data)
            return addr, "OK"
    draft.write_text(original)
    record(addr, name, size, "score 0 but fdiff differs", None)
    return addr, "score 0 but fdiff differs"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--seconds", type=int, default=120)
    ap.add_argument("--jobs", type=int, default=2)
    ap.add_argument("--only", help="comma-separated function addresses (0x...)")
    a = ap.parse_args()
    WORK.mkdir(parents=True, exist_ok=True)
    jobs = []
    for line in (SCRATCH / "near.txt").read_text().splitlines():
        p = line.split()
        if len(p) < 2:
            continue
        addr = int(p[0], 16)
        if a.only and addr not in {int(x, 16) for x in a.only.split(",")}:
            continue
        jobs.append((addr, p[1]))
    jobs = [(addr, name, size_of(addr)) for addr, name in jobs]
    print(f"{len(jobs)} near candidates, {a.seconds}s each on {a.jobs} jobs", flush=True)
    results = []
    with ThreadPoolExecutor(a.jobs) as ex:
        for i, (addr, res) in enumerate(ex.map(lambda j: one(j, a.seconds), jobs)):
            results.append(res)
            print(f"  {i + 1}/{len(jobs)} 0x{addr:08X}: {res}", flush=True)
    ok = [j for j, r in zip(jobs, results) if r == "OK"]
    print(f"OK: {len(ok)} functions ({sum(j[2] for j in ok):#x} bytes); " + ", ".join(
        f"0x{j[0]:08X} {r}" for j, r in zip(jobs, results) if r != "OK"))


def size_of(addr):
    """Size in bytes of the function at addr, from its `nonmatching` line in asm_snap/cod."""
    tag = f"{addr:08X}"
    for path in sorted((ROOT / "scratch" / "asm_snap" / "cod").glob("*.s")):
        text = path.read_text()
        m = re.search(rf"^nonmatching (\w+), 0x([0-9A-Fa-f]+)\n\nglabel \1\n    /\* [0-9A-F]+ {tag} ", text, re.M)
        if m:
            return int(m.group(2), 16)
    return 0


if __name__ == "__main__":
    main()
