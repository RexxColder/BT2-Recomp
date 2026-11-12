#!/usr/bin/env python3
"""Infers every function's prototype from the original code, for m2c's --context.

Usage: scripts/infer_protos.py [--out scratch/protos/ctx.h]

m2c guesses a callee's parameters from one call site, and a parameter the caller only passes through (a0 handed
to the callee untouched) is then lost: the draft shifts its arguments, looks almost identical and is wrong
(func_00208DE8). Here every function of port/funcmap.csv is read from the original executable once:
- parameters: the integer argument registers (a0-a3, t0-t3: the EE's EABI passes eight) and float ones
  (f12-f19, counted apart, as the EABI does) read before written; a register live at a call that the callee
  takes as a parameter counts as read there, so pass-through parameters propagate up the call graph (fixed point);
- result: v0 (f0 for float) is written by the function and some caller reads it after the call; otherwise void.
The scan is linear in address order (a register written on one path and read on another is taken as written),
which can only make a parameter list shorter, never invent one. Output: one prototype per function, under the
name the symbol files give it (else func_XXXXXXXX), as C m2c and ee-gcc both accept.
"""

import argparse
import collections
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import BINUTILS, ROOT  # noqa: E402
import fdiff  # noqa: E402

INT_ARGS = ["a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3"]
FLT_ARGS = [f"$f{i}" for i in range(12, 20)]
NOREAD = {"jal", "j", "b", "lui", "li", "nop", "syscall", "sync", "break", "eret", "di", "ei"}
# First operand is read, not written (stores, branches, compares writing nothing, moves to coprocessors).
FIRST_READ = re.compile(r"^(s[bhwdq]|sw[lr]|sd[lr]|swc1|sdc1|sqc2|b\w*|j[r]?|jalr|mthi|mtlo|mthi1|mtlo1|teq|tne|t\w+|c\.\w+|mult\w*|div\w*|madd\w*|msub\w*)$")


def disasm(elf):
    out = subprocess.run([str(ROOT / (BINUTILS + "objdump")), "-d", "-z", "--no-show-raw-insn", "-M", "no-aliases=0",
                          str(elf)], capture_output=True, text=True).stdout
    ins = {}
    for line in out.splitlines():
        m = re.match(r"\s*([0-9a-f]+):\s+(\S+)\s*(.*)$", line)
        if m:
            ins[int(m.group(1), 16)] = (m.group(2), [o.strip() for o in m.group(3).split("<")[0].split(",") if o.strip()])
    return ins


def regs(op):
    """Registers in an operand (`0x10(sp)` -> sp)."""
    return re.findall(r"\$f\d+|\b(?:zero|at|v[01]|a[0-3]|t\d|s[0-8]|k[01]|gp|sp|fp|ra)\b", op)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", type=Path, default=ROOT / "scratch" / "protos" / "ctx.h")
    a = ap.parse_args()
    funcs = [(int(r.split(",")[1], 16), int(r.split(",")[2], 16)) for r in
             (ROOT / "port/funcmap.csv").read_text().splitlines()[1:]]
    starts = {s for s, _ in funcs}
    ins = disasm(ROOT / "disc/SLUS_214.41")
    # name by address: symbol files, else splat's label
    names = {}
    for n, v in fdiff.targets().items():
        if "." in n:
            continue
        if v in starts and (v not in names or re.fullmatch(r"func_[0-9A-F]{8}", names[v])):
            names[v] = n

    info = {}
    CLOBBER = {"v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9", "at"} | \
        {f"$f{i}" for i in range(20)}

    def step(a_, defined, reads_before, pending, flags):
        mn, ops = ins[a_]
        rs = [r for o in ops for r in regs(o)]
        if mn in ("mtc0", "mtc1", "dmtc1", "ctc1", "ctc2", "qmtc2", "mtsab"):
            rd, src = rs[1:2], rs[:1]  # move TO a coprocessor: the second operand is written
        elif mn.startswith(("mult", "madd", "msub")) and len(ops) == 3:
            rd, src = rs[:1], rs[1:]  # R5900 three-operand form writes rd
        elif FIRST_READ.match(mn) or mn in NOREAD:
            rd, src = [], rs
        else:
            rd, src = rs[:1], rs[1:]
        for r in src:
            if r not in defined:
                reads_before.add(r)
            if pending is not None and r not in pending[2]:
                pending[1].add(r)
        for r in rd:
            defined.add(r)
            if r == "v0":
                flags["wv0"] = True
            if r == "$f0":
                flags["wf0"] = True
            if pending is not None:
                pending[2].add(r)

    for s, e in funcs:
        defined, reads_before, flags = set(), set(), {"wv0": False, "wf0": False}
        calls, after_call, pending = [], [], None
        a_ = s
        while a_ < e:
            if a_ not in ins:
                a_ += 4
                continue
            mn, ops = ins[a_]
            if mn in ("jal", "j") and ops:
                tgt = int(ops[0], 16) if re.fullmatch(r"(?:0x)?[0-9a-f]+", ops[0]) else None
                # The delay slot runs before the call (it usually loads an argument).
                if a_ + 4 in ins and a_ + 4 < e:
                    step(a_ + 4, defined, reads_before, pending, flags)
                if tgt in starts:
                    calls.append((tgt, set(defined), mn == "j"))
                    if mn == "jal":
                        pending = [tgt, set(), set()]  # callee, read after, written after
                        after_call.append(pending)
                        defined |= CLOBBER  # the callee clobbers the caller-saved registers
                a_ += 8
                continue
            step(a_, defined, reads_before, pending, flags)
            a_ += 4
        info[s] = dict(reads=reads_before, calls=calls, after=after_call, wv0=flags["wv0"], wf0=flags["wf0"])

    # Parameters: fixed point over the call graph.
    params = {s: {r for r in v["reads"] if r in INT_ARGS or r in FLT_ARGS} for s, v in info.items()}
    for _ in range(20):
        changed = False
        for s, v in info.items():
            for callee, defs, _tail in v["calls"]:
                for r in params.get(callee, ()):
                    if r not in defs and r not in params[s]:
                        params[s].add(r)
                        changed = True
        if not changed:
            break
    # Results: a caller reads v0/f0 after the call (a tail call passes the caller's own result through).
    used_v0, used_f0 = collections.Counter(), collections.Counter()
    for s, v in info.items():
        for callee, read, _ in v["after"]:
            if "v0" in read:
                used_v0[callee] += 1
            if "$f0" in read:
                used_f0[callee] += 1

    lines = ["/* generated by scripts/infer_protos.py: prototypes inferred from the original code (EE EABI) */", ""]
    stats = collections.Counter()
    for s, _ in funcs:
        if s < 0x100000 or s >= 0x3B3100:
            continue
        p = params[s]
        ni = max((INT_ARGS.index(r) + 1 for r in p if r in INT_ARGS), default=0)
        nf = max((FLT_ARGS.index(r) + 1 for r in p if r in FLT_ARGS), default=0)
        # A caller reading v0/f0 right after the call is the evidence (v0 is clobbered by every call); the callee
        # may produce it through a tail call, so its own writes are not required.
        ret = "f32" if used_f0[s] else "s32" if used_v0[s] else "void"
        args = [f"s32 arg{i}" for i in range(ni)] + [f"f32 farg{i}" for i in range(nf)]
        name = names.get(s, f"func_{s:08X}")
        lines.append(f"{ret} {name}({', '.join(args) or 'void'});")
        stats[ret] += 1
        stats["args"] += ni + nf
    a.out.parent.mkdir(parents=True, exist_ok=True)
    a.out.write_text("\n".join(lines) + "\n")
    print(f"{sum(stats[k] for k in ('void', 's32', 'f32'))} prototypes -> {a.out}: {dict(stats)}")


if __name__ == "__main__":
    main()
