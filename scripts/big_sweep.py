#!/usr/bin/env python3
"""m2c sweep for the functions over 400 instructions that m2c_sweep.py never tried.

Usage: scripts/big_sweep.py [--jobs 2] [--min-insns 400] [--limit N] [--redo] [--report]

The functions come from scratch/asm_snap/cod/*.s, the ones not inside any range of config/c_files.txt. Each goes
through the same steps as scripts/m2c_sweep.py (m2c --valid-syntax with the VARIANTS option sets, the fixes to
m2c's output, fdiff.py, and scripts/data_split.py for an object with data), but in its own folder, scratch/big/,
with a 300 s m2c budget per function (all its variants together). The best variant (fewest differing
instructions) is kept.

Output, all in scratch/big/:
  <ADDR8>.s, m2c_<ADDR6>.c   input and best draft of each function
  status.csv                 addr,name,size,status (OK, differs n/m, compile, m2c: ..., jump table, data, bss,
                             m2c failed, m2c timeout)
  ok.txt                     0xSTART 0xEND m2c_<ADDR6> for each OK function
  data.txt                   the data lines of the OK functions that have data (data_split.place)
  state.json                 what the status, ok and data files are made from (a rerun skips the done functions)
  report.md                  --report: counts, bytes, n/m distribution and the 30 best candidates
"""

import argparse
import csv
import json
import re
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402
import data_split  # noqa: E402
import fdiff  # noqa: E402
import integrate_xfer  # noqa: E402
import m2c_fixsp  # noqa: E402
from m2c_sweep import ALLOWED, VARIANTS, fdiff_run, functions  # noqa: E402

WORK = ROOT / "scratch" / "big"
M2C_BUDGET = 300  # seconds of m2c per function, all variants together
NOMATCH = 1 << 30


def attempt(name, s, c, opts, deadline):
    """(status, n_differing) of one m2c option set; the C is left in c (copy of m2c_sweep.attempt)."""
    rel = c.relative_to(ROOT)
    left = deadline - time.monotonic()
    if left <= 0:
        return "m2c timeout", NOMATCH
    try:
        r = subprocess.run([str(ROOT / ".venv/bin/python"), "-c", "import m2c.main as m; m.main()",
                            "--target", "mips-gcc-c", "--valid-syntax", *opts, "-f", name, str(s)],
                           capture_output=True, text=True, timeout=left)
    except subprocess.TimeoutExpired:
        return "m2c timeout", NOMATCH
    out = r.stdout
    if r.returncode or not out.strip():
        return "m2c failed", NOMATCH
    macros = set(re.findall(r"\bM2C_\w+", out))
    if macros - ALLOWED:
        return "m2c: " + ",".join(sorted(macros - ALLOWED)), NOMATCH
    # A global the original reaches with lui/addiu that m2c declared small enough for $gp: explicit section.
    far = set(re.findall(r"%hi\((\w+)\)", s.read_text()))
    out = re.sub(r"^(extern [^;(]*?\b(\w+));$",
                 lambda m: f'{m.group(1)} __attribute__((section(".data")));' if m.group(2) in far else m.group(0),
                 out, flags=re.M)
    c.write_text('#include "m2c_macros.h"\n\n' + out)
    v = fdiff_run(rel, name)
    if "could not compile" in v.stdout + v.stderr:
        # Callees with no float parameter lose their m2c-guessed parameters (as in m2c_sweep.attempt).
        relaxed = re.sub(r"^([^\n;(]*?\b\w+)\(([^;\n]*)\);( +/\* extern \*/)$",
                         lambda m: m.group(0) if re.search(r"\b(f32|f64|float|double)\b", m.group(2))
                         else f"{m.group(1)}();{m.group(3)}", c.read_text(), flags=re.M)
        if relaxed != c.read_text():
            c.write_text(relaxed)
            v = fdiff_run(rel, name)
    if "could not compile" in v.stdout + v.stderr:
        fixed = m2c_fixsp.fix(c.read_text(), s.read_text())
        if fixed:
            c.write_text(fixed)
            v = fdiff_run(rel, name)
    if re.search(rf"^{re.escape(name)}: OK", v.stdout, re.M):
        return "OK", 0
    m = re.search(r"(\d+) of (\d+) instructions differ", v.stdout)
    return (f"differs {m.group(1)}/{m.group(2)}", int(m.group(1))) if m else ("compile", 1 << 29)


def try_one(job):
    """One function -> record {name, size, status, placed, text}; files left in WORK."""
    name, addr, size, lines = job
    deadline = time.monotonic() + M2C_BUDGET
    rec = {"name": name, "size": size, "status": "", "placed": [], "text": ""}
    body = "\n".join(lines)
    if "jtbl" in body or re.search(r"\bjr\s+\$(?!ra)", body) or ".L" in body and "jlabel" in body:
        rec["status"] = "jump table"
        return addr, rec
    s = WORK / f"{addr:08X}.s"
    s.write_text(body + "\n")
    c = WORK / f"m2c_{addr:06X}.c"
    best = None
    for opts in VARIANTS:
        if c.exists():
            c.unlink()  # so the draft kept below is this variant's own
        status, n = attempt(name, s, c, opts, deadline)
        text = c.read_text() if c.exists() else ""
        if best is None or n < best[1]:
            best = (status, n, text)
        if n == 0 or status.startswith(("m2c", "jump")):
            break
    status, n, text = best
    if n and text:
        # m2c steps a typed pointer by bytes (`p += 4` on an s32 *): in elements, and see if that matches.
        sizes = {"s8": 1, "u8": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "f32": 4, "s64": 8, "u64": 8,
                 "M2C_UNK": 4, "void *": 4}
        ptrs = {}
        for m in re.finditer(r"^\s+(s8|u8|s16|u16|s32|u32|f32|s64|u64|M2C_UNK|void \*) ?\*(\w+);$", text, re.M):
            ptrs[m.group(2)] = sizes[m.group(1)]

        def step(m):
            k = int(m.group(3), 0)
            sz = ptrs.get(m.group(1), 1)
            return m.group(0) if sz == 1 or k % sz else f"{m.group(1)} {m.group(2)}= {k // sz};"
        fixed = re.sub(r"\b(\w+) ([+-])= (0x[0-9A-Fa-f]+|\d+);", step, text)
        if fixed != text:
            c.write_text(fixed)
            v = fdiff_run(c.relative_to(ROOT), name)
            if re.search(rf"^{re.escape(name)}: OK", v.stdout, re.M):
                status, n, text = "OK", 0, fixed
    if text:
        c.write_text(text)  # the best draft stays for the agents
    rec["status"], rec["text"] = status, text
    if status != "OK":
        return addr, rec
    rel = c.relative_to(ROOT)
    obj = fdiff.compile_src(rel, "default")
    sizes = integrate_xfer.section_sizes(obj)
    if sizes.get(".sbss_init", 0) or sizes.get(".bss", 0) or sizes.get(".sbss", 0):
        rec["status"] = "bss"
        return addr, rec
    if any(sizes.get(sec, 0) for sec in data_split.SECTIONS):
        placed, why = data_split.place(obj, addr)
        if not placed:
            rec["status"] = "data"
            return addr, rec
        rec["placed"] = [list(p) for p in placed]
    return addr, rec


def c_file_ranges():
    out = []
    for line in (ROOT / "config/c_files.txt").read_text().splitlines():
        p = line.split()
        if len(p) >= 2 and p[0].startswith("0x") and p[1].startswith("0x"):
            out.append((int(p[0], 16), int(p[1], 16)))
    return out


def find_jobs(asm, min_insns):
    ranges, jobs = c_file_ranges(), {}
    for path in sorted(asm.glob("*.s")):
        for name, addr, size, lines in functions(path):
            if size // 4 > min_insns and not any(x <= addr < y for x, y in ranges):
                jobs.setdefault(addr, (name, addr, size, lines))
    return [jobs[a] for a in sorted(jobs)]


def save(state):
    """Rewrites status.csv, ok.txt and data.txt from state (addr -> record)."""
    (WORK / "state.json").write_text(json.dumps({f"{a:08X}": r for a, r in sorted(state.items())}, indent=1))
    with open(WORK / "status.csv", "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["addr", "name", "size", "status"])
        for a, r in sorted(state.items()):
            w.writerow([f"0x{a:08X}", r["name"], f"{r['size']:#x}", r["status"]])
    ok = sorted(a for a, r in state.items() if r["status"] == "OK")
    (WORK / "ok.txt").write_text("".join(f"0x{a:08X} 0x{a + state[a]['size']:08X} m2c_{a:06X}\n" for a in ok))
    data = []
    for a in ok:
        for sec, x, y in state[a]["placed"]:
            data.append(f"{sec} 0x{x:08X} 0x{y:08X} m2c_{a:06X}\n")
    (WORK / "data.txt").write_text("".join(data))


def category(status):
    if status.startswith("differs"):
        return "differs"
    if status.startswith("m2c: "):
        return "m2c: macro"
    return status


def report(state):
    rows = [(a, r) for a, r in sorted(state.items())]
    total_b = sum(r["size"] for _, r in rows)
    cats, byts = {}, {}
    for _, r in rows:
        k = category(r["status"])
        cats[k] = cats.get(k, 0) + 1
        byts[k] = byts.get(k, 0) + r["size"]
    diff = []
    for a, r in rows:
        m = re.match(r"differs (\d+)/(\d+)", r["status"])
        if m:
            n, t = int(m.group(1)), int(m.group(2))
            diff.append((n / t, n, t, a, r))
    diff.sort(key=lambda x: (x[0], x[1]))
    L = ["# big_sweep report", "", f"Functions tried: {len(rows)} ({total_b:#x} bytes)", "",
         "## Status", "", "| status | count | bytes |", "|---|---:|---:|"]
    for k in sorted(cats, key=lambda k: -cats[k]):
        L.append(f"| {k} | {cats[k]} | {byts[k]:#x} |")
    ok = [r for _, r in rows if r["status"] == "OK"]
    L += ["", f"OK: {len(ok)} functions, {sum(r['size'] for r in ok):#x} bytes "
          f"({sum(1 for r in ok if r['placed'])} with data)", ""]
    macros = {}
    for _, r in rows:
        if r["status"].startswith("m2c: "):
            macros[r["status"][5:]] = macros.get(r["status"][5:], 0) + 1
    if macros:
        L += ["m2c macros not allowed: " + ", ".join(f"{k} ({v})" for k, v in
                                                    sorted(macros.items(), key=lambda x: -x[1])), ""]
    L += ["## differs: n/m distribution", ""]
    nd = len(diff)
    L.append(f"{nd} functions with differs n/m")
    for lim in (0.05, 0.10, 0.20):
        k = sum(1 for x in diff if x[0] < lim)
        L.append(f"- under {int(lim * 100)}%: {k}")
    L.append("")
    L += ["## 30 best candidates (smallest n/m, then fewest n)", "",
          "| addr | name | size | status | draft |", "|---|---|---:|---|---|"]
    for ratio, n, t, a, r in diff[:30]:
        L.append(f"| 0x{a:08X} | {r['name']} | {r['size']:#x} | differs {n}/{t} ({ratio:.1%}) | "
                 f"scratch/big/m2c_{a:06X}.c |")
    (WORK / "report.md").write_text("\n".join(L) + "\n")
    print("\n".join(L))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--asm", type=Path, default=ROOT / "scratch" / "asm_snap" / "cod")
    ap.add_argument("--min-insns", type=int, default=400)
    ap.add_argument("--jobs", type=int, default=2)
    ap.add_argument("--limit", type=int, default=0, help="only the first N functions (a test)")
    ap.add_argument("--redo", action="store_true", help="retry the functions already in state.json")
    ap.add_argument("--report", action="store_true", help="only rewrite report.md from state.json")
    a = ap.parse_args()
    WORK.mkdir(parents=True, exist_ok=True)
    sf = WORK / "state.json"
    state = {int(k, 16): v for k, v in json.loads(sf.read_text()).items()} if sf.exists() else {}
    if a.report:
        report(state)
        return
    jobs = find_jobs(a.asm, a.min_insns)
    print(f"{len(jobs)} functions over {a.min_insns} instructions outside config/c_files.txt", flush=True)
    todo = [j for j in jobs if a.redo or j[1] not in state]
    print(f"{len(todo)} to try ({len(jobs) - len(todo)} already done)", flush=True)
    if a.limit:
        todo = todo[:a.limit]
    done = 0
    with ThreadPoolExecutor(a.jobs) as ex:
        for addr, rec in ex.map(try_one, todo):
            state[addr] = rec
            save(state)  # saved as you go: the session can be cut
            done += 1
            print(f"  {done}/{len(todo)} 0x{addr:08X} {rec['name']} {rec['size']:#x}: {rec['status']}", flush=True)
    counts = {}
    for r in state.values():
        counts[category(r["status"])] = counts.get(category(r["status"]), 0) + 1
    print(f"done: {counts}", flush=True)
    report(state)


if __name__ == "__main__":
    main()
