#!/usr/bin/env python3
"""Tries m2c's output, as is, for every function still in assembly, and keeps the ones that match.

Usage: scripts/m2c_sweep.py [--range 0xLO 0xHI] [--max-insns 400] [--jobs 6] [--write]

For each function of asm/cod/*.s (the live split: what is not in C yet), in the game's code ranges:
 1. its glabel..endlabel lines go to a file of their own and m2c (--valid-syntax) decompiles that;
 2. output with an M2C_ macro other than M2C_FIELD/M2C_UNK/M2C_BITWISE (errors, carries, traps), or from a
    function with a jump table, is skipped;
 3. the C (include/m2c_macros.h + m2c's own externs + the function) is compiled and checked with fdiff.py;
 4. an object with data of its own (a float literal m2c wrote as a constant) is kept only when
    scripts/data_split.py places that data in the original.
Every try is listed in scratch/m2c_sweep/status.csv (OK, differs n/m, compile, data, m2c: ...), and the
m2c_XXXXXX.c drafts stay there: the near misses are where hand work starts. With --write each OK function becomes src/auto/m2c_XXXXXX.c, `START END auto/m2c_XXXXXX  # m2c` in
config/c_files.txt and its data lines in config/data_files.txt; scripts/gate_prune.py is the final judge.
"""

import argparse
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT, TARGETS  # noqa: E402
import data_split  # noqa: E402
import fdiff  # noqa: E402
import integrate_xfer  # noqa: E402
import m2c_fixsp  # noqa: E402

TAG = "# m2c"
WORK = ROOT / "scratch" / "m2c_sweep"
ALLOWED = {"M2C_FIELD", "M2C_UNK", "M2C_UNK8", "M2C_UNK16", "M2C_UNK32", "M2C_UNK64", "M2C_BITWISE"}


def functions(path):
    """(name, address, size, lines) per function of a splat .s file."""
    head, cur, size = [], None, 0
    for line in path.read_text().splitlines():
        if cur is None:
            if line.startswith("nonmatching "):
                p = line.split(",")
                size = int(p[1], 16) if len(p) > 1 else 0
            elif line.startswith("glabel "):
                cur = [line]
            elif not head or line.startswith((".include", ".set", ".section")):
                head.append(line)
            continue
        cur.append(line)
        if line.startswith("endlabel"):
            m = re.search(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ", cur[1]) if len(cur) > 1 else None
            if m and size:
                yield cur[0].split()[1], int(m.group(1), 16), size, head + [""] + cur
            cur = None


# m2c options tried in turn when the default output does not match: ee-gcc 2.96 allocates registers partly in
# declaration order, and m2c's temporaries/phis shape the expression trees.
VARIANTS = [[], ["--reg-vars", "saved"], ["--descending-regs"], ["--no-andor"],
            ["--reg-vars", "saved", "--descending-regs"]]
# With the prototypes scripts/infer_protos.py infers from the whole executable (callees' parameters and results,
# pass-through arguments included): with and without the function's own prototype (it can miss a parameter the
# body reads, and m2c then cannot read that register), under the EE's EABI target.
PROTOS = ROOT / "scratch" / "protos" / "ctx.h"
CTX_VARIANTS = [["@ctx"], ["@ctx-own"], ["@ctx", "--reg-vars", "saved"], ["@ctx-own", "--reg-vars", "saved"]]
_PROTO_LINES = None


def proto_lines():
    """name -> prototype line, from PROTOS."""
    global _PROTO_LINES
    if _PROTO_LINES is None:
        _PROTO_LINES = {}
        if PROTOS.exists():
            for line in PROTOS.read_text().splitlines():
                m = re.match(r"\w+\s+(\w+)\(", line)
                if m:
                    _PROTO_LINES[m.group(1)] = line
    return _PROTO_LINES


def with_protos(out, name, own):
    """m2c's C plus the inferred prototypes of what it calls (m2c leaves out the externs the context gives)."""
    protos = proto_lines()
    used = set(re.findall(r"\b(\w+)\s*\(", out))
    decl = [protos[f] for f in sorted(used) if f in protos and f != name
            and not re.search(rf"^[^\n;]*\b{re.escape(f)}\([^\n]*\);", out, re.M)]
    return ("\n".join(decl) + "\n\n" if decl else "") + out


# Compiler for this run (--cc): the SDK part of the image (sce* libraries) was built by Sony with another gcc.
CC_KEY = "default"


def fdiff_run(rel, name):
    cc = [] if CC_KEY == "default" else ["--cc", CC_KEY]
    return subprocess.run([sys.executable, str(ROOT / "scripts/fdiff.py"), *cc, str(rel), name], cwd=ROOT,
                          capture_output=True, text=True)


def attempt(name, s, c, opts):
    """(status, n_differing) of one m2c option set; the C is left in c."""
    rel = c.relative_to(ROOT)
    target, extra, ctx = "mips-gcc-c", [o for o in opts if not o.startswith("@")], None
    if any(o.startswith("@ctx") for o in opts):
        if not PROTOS.exists():
            return "no protos", 1 << 30
        target = "mipsee-gcc-c"
        ctx = c.with_suffix(".ctx.h")
        own = "@ctx-own" in opts
        pat = re.compile(r"\b(?:" + re.escape(name) + "|" + f"func_{int(s.stem, 16):08X}" + r")\(")
        ctx.write_text("".join(l + "\n" for l in PROTOS.read_text().splitlines() if own or not pat.search(l)))
        extra = ["--context", str(ctx)] + extra
    try:
        r = subprocess.run([str(ROOT / ".venv/bin/python"), "-c", "import m2c.main as m; m.main()",
                            "--target", target, "--valid-syntax", *extra, "-f", name, str(s)],
                           capture_output=True, text=True, timeout=120)
    finally:
        if ctx is not None:
            ctx.unlink(missing_ok=True)
    out = r.stdout
    if ctx is not None and out.strip():
        out = with_protos(out, name, "@ctx-own" in opts)
    if r.returncode or not out.strip():
        return "m2c failed", 1 << 30
    macros = set(re.findall(r"\bM2C_\w+", out))
    if macros - ALLOWED:
        return "m2c: " + ",".join(sorted(macros - ALLOWED)), 1 << 30
    # A global the original reaches with lui/addiu (%hi/%lo) that m2c declared small enough for $gp (-G8): an
    # explicit section keeps gcc off $gp for it.
    far = set(re.findall(r"%hi\((\w+)\)", s.read_text()))
    out = re.sub(r"^(extern [^;(]*?\b(\w+));$",
                 lambda m: f'{m.group(1)} __attribute__((section(".data")));' if m.group(2) in far else m.group(0),
                 out, flags=re.M)
    c.write_text('#include "m2c_macros.h"\n\n' + out)
    v = fdiff_run(rel, name)
    if "could not compile" in v.stdout + v.stderr:
        # m2c guesses each callee's parameters from one call: another call with fewer arguments does not
        # compile. Callees with no float parameter (an unprototyped call promotes float to double) lose theirs.
        relaxed = re.sub(r"^([^\n;(]*?\b\w+)\(([^;\n]*)\);( +/\* extern \*/)$",
                         lambda m: m.group(0) if re.search(r"\b(f32|f64|float|double)\b", m.group(2))
                         else f"{m.group(1)}();{m.group(3)}", c.read_text(), flags=re.M)
        if relaxed != c.read_text():
            c.write_text(relaxed)
            v = fdiff_run(rel, name)
    if "could not compile" in v.stdout + v.stderr:
        # The stack buffer at offset 0, `sp`, that m2c passes without declaring it (scripts/m2c_fixsp.py).
        fixed = m2c_fixsp.fix(c.read_text(), s.read_text())
        if fixed:
            c.write_text(fixed)
            v = fdiff_run(rel, name)
    if re.search(rf"^{re.escape(name)}: OK", v.stdout, re.M):
        return "OK", 0
    m = re.search(r"(\d+) of (\d+) instructions differ", v.stdout)
    return (f"differs {m.group(1)}/{m.group(2)}", int(m.group(1))) if m else ("compile", 1 << 29)


def void_unused(text):
    """Extern prototypes whose every call is a bare statement `f(...);` become `void f(...);`."""
    out = text
    for m in re.finditer(r"^([^\n;(]*?)\b(\w+)\(([^;\n]*)\);( +/\* extern \*/)$", text, re.M):
        ret, fn = m.group(1).strip(), m.group(2)
        if ret == "void":
            continue
        calls = len(re.findall(rf"\b{fn}\(", text)) - 1  # minus the prototype
        bare = len(re.findall(rf"^\s+{fn}\(.*\);$", text, re.M))
        if calls and calls == bare:
            out = out.replace(m.group(0), f"void {fn}({m.group(3)});{m.group(4)}", 1)
    return out


def try_one(job):
    name, addr, size, lines = job
    body = "\n".join(lines)
    if "jtbl" in body or re.search(r"\bjr\s+\$(?!ra)", body) or ".L" in body and "jlabel" in body:
        return name, addr, size, None, "jump table"
    s = WORK / f"{addr:08X}.s"
    s.write_text(body + "\n")
    c = WORK / f"m2c_{addr:06X}.c"
    best = None
    for opts in VARIANTS + CTX_VARIANTS:
        status, n = attempt(name, s, c, opts)
        if best is None or n < best[1]:
            best = (status, n, c.read_text() if c.exists() else "")
        if n == 0:
            break
    status, n, text = best
    if n and text:
        # A callee whose result the function never uses: declared `void` (m2c gives it a type from the
        # register it guessed, and ee-gcc then allocates the caller's registers differently).
        vtext = void_unused(text)
        if vtext != text:
            c.write_text(vtext)
            v = fdiff_run(c.relative_to(ROOT), name)
            if re.search(rf"^{re.escape(name)}: OK", v.stdout, re.M):
                status, n, text = "OK", 0, vtext
            else:
                m = re.search(r"(\d+) of (\d+) instructions differ", v.stdout)
                if m and int(m.group(1)) < n:
                    status, n, text = f"differs {m.group(1)}/{m.group(2)}", int(m.group(1)), vtext
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
    if c.exists() or text:
        c.write_text(text)  # the best draft stays for the agents
    if status != "OK":
        return name, addr, size, None, status
    rel = c.relative_to(ROOT)
    obj = fdiff.compile_src(rel, CC_KEY)
    sizes = integrate_xfer.section_sizes(obj)
    if sizes.get(".sbss_init", 0) or sizes.get(".bss", 0) or sizes.get(".sbss", 0):
        return name, addr, size, None, "bss"
    placed = []
    if any(sizes.get(sec, 0) for sec in data_split.SECTIONS):
        placed, why = data_split.place(obj, addr)
        if not placed:
            return name, addr, size, None, "data"
    return name, addr, size, (c.read_text(), placed), "OK"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--range", nargs=2, default=None)
    ap.add_argument("--max-insns", type=int, default=400)
    ap.add_argument("--jobs", type=int, default=6)
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--asm", type=Path, default=ROOT / "asm" / "cod")
    ap.add_argument("--cc", default="default",
                    help="compiler key (a tools/ee-gcc* folder); results are listed in config/cc_<key>.txt")
    ap.add_argument("--only", help="retry only the functions with this status in status.csv (e.g. compile)")
    a = ap.parse_args()
    global CC_KEY
    CC_KEY = a.cc
    lo, hi = (int(a.range[0], 16), int(a.range[1], 16)) if a.range else (0, 1 << 32)
    ranges = [tuple(r) for t in TARGETS for r in t.get("game_ranges", [t["image"]])]
    WORK.mkdir(parents=True, exist_ok=True)

    jobs = []
    for path in sorted(a.asm.glob("*.s")):
        for name, addr, size, lines in functions(path):
            if lo <= addr < hi and any(x <= addr < y for x, y in ranges) and 2 < size // 4 <= a.max_insns:
                jobs.append((name, addr, size, lines))
    prev = {}
    if (WORK / "status.csv").exists():
        prev = {int(r.split(",")[0], 16): r.rstrip().split(",", 3)[3]
                for r in (WORK / "status.csv").read_text().splitlines()[1:]}
    if a.only:
        jobs = [j for j in jobs if prev.get(j[1], "").startswith(a.only)]
    print(f"{len(jobs)} functions to try")
    results, why, status = [], {}, []
    with ThreadPoolExecutor(a.jobs) as ex:
        for i, (name, addr, size, res, reason) in enumerate(ex.map(try_one, jobs)):
            status.append(f"0x{addr:08X},{name},{size:#x},{reason}")
            reason = reason.split()[0]
            why[reason] = why.get(reason, 0) + 1
            if res:
                results.append((addr, size, name, res))
            if i % 200 == 199:
                print(f"  {i + 1}/{len(jobs)}: {why}", flush=True)
    # Every try, for the agents: a "differs n/m" draft is scratch/m2c_sweep/m2c_XXXXXX.c, a head start.
    # A partial run (--range, --only) updates its rows and keeps the others.
    merged = {int(r.split(",")[0], 16): r for r in ((WORK / "status.csv").read_text().splitlines()[1:]
                                                     if (WORK / "status.csv").exists() else [])}
    merged.update({int(r.split(",")[0], 16): r for r in status})
    (WORK / "status.csv").write_text("addr,name,size,status\n" + "\n".join(merged[k] for k in sorted(merged)) + "\n")
    print(f"OK: {len(results)} functions ({sum(r[1] for r in results):#x} bytes); {why}")
    if not a.write:
        return
    cf = ROOT / "config/c_files.txt"
    lines = [l for l in cf.read_text().splitlines() if l.strip()]
    df = ROOT / "config/data_files.txt"
    dlines = [l for l in df.read_text().splitlines() if l.strip()] if df.exists() else []
    for addr, size, name, (text, placed) in sorted(results):
        stem = f"auto/m2c_{addr:06X}"
        (ROOT / "src" / f"{stem}.c").write_text(text)
        lines.append(f"0x{addr:08X} 0x{addr + size:08X} {stem}  {TAG}")
        dlines += [f"{sec} 0x{x:08X} 0x{y:08X} {stem}  {TAG}" for sec, x, y in placed]
    cf.write_text("\n".join(sorted(lines, key=lambda l: int(l.split()[0], 16))) + "\n")
    df.write_text("\n".join(sorted(dlines, key=lambda l: int(l.split()[1], 16))) + "\n")
    if CC_KEY != "default" and results:
        # The build compiles these with the same compiler (gamecfg.alt_cc_files).
        ccl = ROOT / "config" / f"cc_{CC_KEY}.txt"
        have = set(ccl.read_text().split()) if ccl.exists() else set()
        add = [f"src/auto/m2c_{addr:06X}.c" for addr, _, _, _ in results]
        ccl.write_text("\n".join(sorted(have | set(add))) + "\n")
    print(f"wrote {len(results)} files")


if __name__ == "__main__":
    main()
