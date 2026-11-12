#!/usr/bin/env python3
"""Measures what m2c --context (scratch/m2c_ctx/ctx.h, from scripts/m2c_context.py) adds to the sweep.

Usage: .venv/bin/python scripts/m2c_ctx_trial.py [--n 150] [--seed 1] [--jobs 4] [--ctx scratch/m2c_ctx/ctx.h]

A sample of scratch/m2c_sweep/status.csv (--n rows with status "differs ..." and --n rows "compile", fixed seed)
is decompiled twice with the same m2c options (the default ones): without and with --context. Each draft is
compiled and checked with scripts/fdiff.py, after the same two repairs the sweep makes (the implicit-parameter
relaxation and the stack-pointer fix, scripts/m2c_sweep.py), so the two columns differ only by the context.

Drafts: scratch/m2c_ctx/c/<ADDR6>_{old,new}.c. Preamble of each: `#include "m2c_macros.h"` (old) and that plus
`#include "../ctx.h"` (new). Results: scratch/m2c_ctx/results.csv (addr,name,old_status,new_status,sweep_status)
and scratch/m2c_ctx/summary.txt.
"""

import argparse
import csv
import random
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import m2c_fixsp  # noqa: E402

SWEEP = ROOT / "scratch/m2c_sweep"
WORK = ROOT / "scratch/m2c_ctx"
ALLOWED = {"M2C_FIELD", "M2C_UNK", "M2C_UNK8", "M2C_UNK16", "M2C_UNK32", "M2C_UNK64", "M2C_BITWISE"}
PREAMBLE_OLD = '#include "m2c_macros.h"\n\n'
PREAMBLE_NEW = '#include "m2c_macros.h"\n#include "../ctx.h"\n\n'


def run_m2c(name, s, ctx):
    cmd = [str(ROOT / ".venv/bin/python"), "-c", "import m2c.main as m; m.main()", "--target", "mips-gcc-c",
           "--valid-syntax"]
    if ctx:
        cmd += ["--context", str(ctx)]
    cmd += ["-f", name, str(s)]
    r = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
    return r.stdout if r.returncode == 0 and r.stdout.strip() else None


def fdiff(c, name):
    r = subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), str(c.relative_to(ROOT)), name],
                       cwd=ROOT, capture_output=True, text=True)
    return r.stdout + r.stderr


def judge(c, name, s, text):
    """(status, n_differing) after the sweep's two repairs."""
    if text is None:
        return "m2c failed", 1 << 30
    macros = set(re.findall(r"\bM2C_\w+", text))
    if macros - ALLOWED:
        return "m2c: " + ",".join(sorted(macros - ALLOWED)), 1 << 30
    far = set(re.findall(r"%hi\((\w+)\)", s.read_text()))
    text = re.sub(r"^(extern [^;(]*?\b(\w+));$",
                  lambda m: f'{m.group(1)} __attribute__((section(".data")));' if m.group(2) in far else m.group(0),
                  text, flags=re.M)
    head = PREAMBLE_NEW if c.name.endswith("_new.c") else PREAMBLE_OLD
    c.write_text(head + text)
    out = fdiff(c, name)
    if "could not compile" in out:
        relaxed = re.sub(r"^([^\n;(]*?\b\w+)\(([^;\n]*)\);( +/\* extern \*/)$",
                         lambda m: m.group(0) if re.search(r"\b(f32|f64|float|double)\b", m.group(2))
                         else f"{m.group(1)}();{m.group(3)}", c.read_text(), flags=re.M)
        if relaxed != c.read_text():
            c.write_text(relaxed)
            out = fdiff(c, name)
    if "could not compile" in out:
        fixed = m2c_fixsp.fix(c.read_text(), s.read_text())
        if fixed:
            c.write_text(fixed)
            out = fdiff(c, name)
    if re.search(rf"^{re.escape(name)}: OK", out, re.M):
        return "OK", 0
    m = re.search(r"(\d+) of (\d+) instructions differ", out)
    if m:
        return f"differs {m.group(1)}/{m.group(2)}", int(m.group(1))
    return "compile", 1 << 29


def trial(row, ctx):
    addr, name, sweep = row["addr"], row["name"], row["status"]
    a6 = f"{int(addr, 16):08X}"
    s = SWEEP / f"{a6}.s"
    if not s.exists():
        return addr, name, "no asm", "no asm", sweep
    cdir = WORK / "c"
    cdir.mkdir(parents=True, exist_ok=True)
    res = []
    for tag, use in (("old", None), ("new", ctx)):
        c = cdir / f"{a6[-6:]}_{tag}.c"
        status, _ = judge(c, name, s, run_m2c(name, s, use))
        res.append(status)
    return addr, name, res[0], res[1], sweep


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--n", type=int, default=150)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--ctx", type=Path, default=WORK / "ctx.h")
    a = ap.parse_args()
    rows = list(csv.DictReader((SWEEP / "status.csv").read_text().splitlines()))
    differs = [r for r in rows if r["status"].startswith("differs")]
    compile_ = [r for r in rows if r["status"] == "compile"]
    rng = random.Random(a.seed)
    sample = rng.sample(differs, min(a.n, len(differs))) + rng.sample(compile_, min(a.n, len(compile_)))
    ctx = a.ctx.resolve()
    with ThreadPoolExecutor(max_workers=min(a.jobs, 4)) as ex:
        results = list(ex.map(lambda r: trial(r, ctx), sample))
    with (WORK / "results.csv").open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["addr", "name", "old_status", "new_status", "sweep_status"])
        w.writerows(results)

    def n_of(st):
        m = re.match(r"differs (\d+)/", st)
        return int(m.group(1)) if m else None

    total = len(results)
    ok_old = sum(r[2] == "OK" for r in results)
    ok_new = sum(r[3] == "OK" for r in results)
    comp_old = sum(r[2] != "compile" and not r[2].startswith(("m2c", "no asm")) for r in results)
    comp_new = sum(r[3] != "compile" and not r[3].startswith(("m2c", "no asm")) for r in results)
    became = sum(r[2] == "compile" and r[3] not in ("compile",) and not r[3].startswith(("m2c", "no asm"))
                 for r in results)
    fail_m2c = sum(r[3].startswith("m2c") for r in results)
    reduced = sum(1 for r in results if n_of(r[2]) is not None and n_of(r[3]) is not None
                  and n_of(r[3]) < n_of(r[2]))
    worse = sum(1 for r in results if n_of(r[2]) is not None and n_of(r[3]) is not None
                and n_of(r[3]) > n_of(r[2]))
    lost = sum(1 for r in results if r[2] not in ("compile",) and not r[2].startswith(("m2c", "no asm"))
               and r[3] == "compile")
    lines = [f"sample: {total} ({min(a.n, len(differs))} differs, {min(a.n, len(compile_))} compile), seed {a.seed}",
             f"OK without context: {ok_old}   with context: {ok_new}",
             f"compiling (any draft that builds) without: {comp_old}   with: {comp_new}",
             f"compile -> compiling: {became}",
             f"differs count reduced: {reduced}   increased: {worse}   compiling -> not compiling: {lost}",
             f"m2c errors with context: {fail_m2c}"]
    (WORK / "summary.txt").write_text("\n".join(lines) + "\n")
    print("\n".join(lines))


if __name__ == "__main__":
    main()
