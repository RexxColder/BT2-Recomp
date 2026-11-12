#!/usr/bin/env python3
"""Writes matching C for the simplest functions still in assembly, verifies it, and lists the ranges.

Usage: scripts/leaf_sweep.py [--cc KEY] [--range 0xLO 0xHI] [--max N] [--write]

Patterns (from RE Outbreak's tools/sweep_all.py): empty functions, getters/setters through an argument or a
global, constant/identity returns, syscall stubs, bare tail calls, tail-call and non-tail wrappers with simple
argument setup, buffer-fill wrappers. Every candidate is compiled in ONE scratch file and checked with fdiff.py;
only functions that print OK are kept. Consecutive OK functions (nothing in between but alignment) are grouped
into one C file per run, `src/auto/auto_XXXXXX.c`, because a C file must cover one contiguous range
(BT3-Decompiled's rule). Without --write it only reports.

With --write the files are written and their ranges appended to config/c_files.txt; then run
`scripts/gen_yaml.py && configure.py && ninja` (the byte-identical check is the final gate).
"""

import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT, TARGETS  # noqa: E402

INS = re.compile(r"/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]+ \*/\s+(.+?)\s*$")


def parse(path):
    """(name, address, instructions, size) per function of a splat .s file."""
    name = addr = None
    insns = []
    size = 0
    for line in open(path):
        if line.startswith("nonmatching "):
            parts = line.split(",")
            size = int(parts[1], 16) if len(parts) > 1 else 0  # data labels have no size
        elif line.startswith("glabel "):
            name, addr, insns = line.split()[1], None, []
        elif name and line.startswith("endlabel"):
            yield name, addr, insns, size
            name = None
        elif name:
            m = INS.search(line)
            if m:
                if addr is None:
                    addr = int(m.group(1), 16)
                insns.append(re.sub(r"\s+", " ", m.group(2).split("/*")[0]).strip())


def form(insns):
    """Return (ret, params, body, extern_decl) or None. Delay slot is preserved."""
    b = insns
    n = len(b)

    def ret_const(ins):
        m = re.match(r"addiu \$v0, \$zero, (-?0x[0-9A-Fa-f]+)$", ins)
        return f"return {int(m.group(1), 16):#x};" if m else None

    # syscall stub: addiu $v1,$zero,N ; syscall ; jr $ra ; nop
    if n == 4 and b[1].startswith("syscall") and b[2] == "jr $ra":
        m = re.match(r"addiu \$v1, \$zero, (-?0x[0-9A-Fa-f]+)$", b[0])
        if m:
            return ("void", "void", f'__asm__ volatile("addiu\\t$v1, $zero, {m.group(1)}\\n\\tsyscall");', None)

    # 2-insn: jr $ra ; <delay slot>
    if n == 2 and b[0].startswith("jr"):
        d = b[1]
        if d == "nop":
            return ("void", "void", "", None)
        m = re.match(r"(lw|lh|lhu|lb|lbu) \$v0, (-?0x[0-9A-Fa-f]+)\(\$(\w+)\)$", d)
        if m:
            ty = {"lw": "u32", "lh": "s16", "lhu": "u16", "lb": "s8", "lbu": "u8"}[m.group(1)]
            return (ty, "void *a0", f"return *({ty} *)((u8 *)a0 + {int(m.group(2), 16):#x});", None)
        m = re.match(r"(sw|sh|sb) \$(\w+), (-?0x[0-9A-Fa-f]+)\(\$(\w+)\)$", d)
        if m:
            ty = {"sw": "u32", "sh": "u16", "sb": "u8"}[m.group(1)]
            args = {"a0": 0, "a1": 1, "a2": 2, "a3": 3}
            if m.group(2) in args and m.group(4) in args:
                return ("void", "void *a0, u32 a1, u32 a2, u32 a3",
                        f"*({ty} *)((u8 *)a{args[m.group(4)]} + {int(m.group(3), 16):#x}) = a{args[m.group(2)]};", None)
        m = ret_const(d)
        if m:
            return ("u32", "void", m, None)
        if re.match(r"daddu \$v0, \$a0, \$zero$", d):
            return ("u32", "u32 a0", "return a0;", None)
        if re.match(r"daddu \$v0, \$zero, \$zero$", d):
            return ("u32", "void", "return 0;", None)
        m = re.match(r"addiu \$v0, \$a0, (-?0x[0-9A-Fa-f]+)$", d)
        if m:
            return ("u32", "u32 a0", f"return a0 + {int(m.group(1), 16):#x};", None)
        if re.match(r"addu \$v0, \$a0, \$a1$", d):
            return ("u32", "u32 a0, u32 a1", "return a0 + a1;", None)
        return None

    # 3-insn: <compute $v0> ; jr $ra ; <delay slot>
    if n == 3 and b[1].startswith("jr"):
        first = b[0]
        m = ret_const(first)
        if m:
            return ("u32", "void", m, None)
        if re.match(r"daddu \$v0, \$a0, \$zero$", first):
            return ("u32", "u32 a0", "return a0;", None)
        m = re.match(r"addiu \$v0, \$a0, (-?0x[0-9A-Fa-f]+)$", first)
        if m:
            return ("u32", "u32 a0", f"return a0 + {int(m.group(1), 16):#x};", None)
        m = re.match(r"lui \$(\w+), %hi\((\w+)\)$", first)
        if m:
            reg, sym = m.group(1), m.group(2)
            d = b[2]
            if re.match(rf"lw \$v0, %lo\(\w+\)\(\${reg}\)$", d):
                return ("u32", "void", f"return {sym}[0];", f"extern u32 {sym}[];")
            if re.match(rf"addiu \${reg}, \${reg}, %lo\(\w+\)$", d):
                return ("u32", "void", f"return (u32){sym};", f"extern u8 {sym}[];")
            m2 = re.match(rf"sw \$(\w+), %lo\(\w+\)\(\${reg}\)$", d)
            if m2 and m2.group(1) in ("a0", "a1", "a2", "a3"):
                return ("void", "u32 a0, u32 a1, u32 a2, u32 a3",
                        f"{sym}[0] = {m2.group(1)};", f"extern u32 {sym}[];")

    # getter returning a boolean compare: lw $v0,off($a0) ; jr $ra ; sltu $v0,$zero,$v0
    if n == 3 and b[1].startswith("jr"):
        m = re.match(r"lw \$v0, (-?0x[0-9A-Fa-f]+)\(\$(\w+)\)$", b[0])
        if m and re.match(r"sltu \$v0, \$zero, \$v0$", b[2]):
            off, base = int(m.group(1), 16), m.group(2)
            return ("u32", f"void *{base}", f"return *(u32 *)((u8 *){base} + {off:#x}) != 0;", None)
        if re.match(r"addu \$a0, \$a1, \$a0$", b[0]):
            m2 = re.match(r"(sb|sh|sw) \$(\w+), (-?0x[0-9A-Fa-f]+)\(\$a0\)$", b[2])
            if m2 and m2.group(2) == "a2":
                ty = {"sb": "u8", "sh": "u16", "sw": "u32"}[m2.group(1)]
                return ("void", "u32 a0, u32 a1, u32 a2",
                        f"*({ty} *)((u8 *)(a1 + a0) + {int(m2.group(3), 16):#x}) = a2;", None)
        if b[1].startswith("j "):
            m = re.match(r"lui \$(\w+), %hi\((\w+)\)$", b[0])
            m2 = re.match(r"lw \$a0, %lo\(\w+\)\(\$\w+\)$", b[2])
            if m and m2:
                sym = m.group(2)
                return ("u32", "void", f"return {b[1].split(None, 1)[1]}({sym}[0]);", f"extern u32 {sym}[];")

    # multi-field setter: <stores> ; jr $ra ; <store>
    if n >= 3:
        jr = next((i for i, x in enumerate(b) if x == "jr $ra"), None)
        if jr is not None:
            regs = ["a0", "a1", "a2", "a3"]
            stores = []
            for x in b[:jr] + b[jr + 1:]:
                m = re.match(r"(sw|sh|sb) \$(\w+), (-?0x[0-9A-Fa-f]+)\(\$(\w+)\)$", x)
                if m and m.group(2) in regs and m.group(4) in regs:
                    ty = {"sw": "u32", "sh": "u16", "sb": "u8"}[m.group(1)]
                    stores.append((ty, m.group(2), int(m.group(3), 16), m.group(4)))
                else:
                    stores = []
                    break
            if stores:
                used = sorted({s[1] for s in stores} | {s[3] for s in stores}, key=regs.index)
                body = " ".join(f"*({t} *)((u8 *){base} + {off:#x}) = {val};" for t, val, off, base in reversed(stores))
                params = ", ".join(f"u32 {r}" for r in regs if r in used)
                return ("void", params, body, None)

    # bare tail call: j T ; <delay>
    if n == 2 and b[0].startswith("j "):
        target = b[0].split(None, 1)[1]
        return ("u32", "void", f"return {target}();", None)

    def transform(setup):
        args = {"a0": "a0", "a1": "a1", "a2": "a2", "a3": "a3"}
        used = set()
        i = 0
        while i < len(setup):
            ins = setup[i]
            m = re.match(r"(lw|lh|lhu|lb|lbu) \$(\w+), (-?0x[0-9A-Fa-f]+)\(\$(\w+)\)$", ins)
            if m and m.group(2) in args and m.group(4) in args:
                ty = {"lw": "u32", "lh": "s16", "lhu": "u16", "lb": "s8", "lbu": "u8"}[m.group(1)]
                used.add(m.group(4))
                args[m.group(2)] = f"*({ty} *)((u8 *){args[m.group(4)]} + {int(m.group(3), 16):#x})"
                i += 1
                continue
            m = re.match(r"addiu \$(\w+), \$zero, (-?0x[0-9A-Fa-f]+)$", ins)
            if m and m.group(1) in args:
                args[m.group(1)] = str(int(m.group(2), 16))
                i += 1
                continue
            m = re.match(r"daddu \$(\w+), \$(\w+), \$zero$", ins)
            if m and m.group(1) in args:
                if m.group(2) == "zero":
                    args[m.group(1)] = "0"
                elif m.group(2) in args:
                    args[m.group(1)] = args[m.group(2)]
                    used.add(m.group(2))
                else:
                    return None
                i += 1
                continue
            m = re.match(r"lui \$(\w+), %hi\((\w+)\)$", ins)
            if m and i + 1 < len(setup) and re.match(r"addiu \$\w+, \$\w+, %lo\(\w+\)$", setup[i + 1]) \
               and m.group(1) in args:
                args[m.group(1)] = f"(u32){m.group(2)}"
                i += 2
                continue
            m = re.match(r"addiu \$(\w+), \$(\w+), (-?0x[0-9A-Fa-f]+)$", ins)
            if m and m.group(1) in args and m.group(2) in args:
                used.add(m.group(2))
                args[m.group(1)] = f"(u32){args[m.group(2)]} + {int(m.group(3), 16):#x}"
                i += 1
                continue
            return None
        return args, used

    def build_call(args, used, target):
        regs = ["a0", "a1", "a2", "a3"]
        hi = max((i for i, r in enumerate(regs) if args[r] != r or r in used), default=-1)
        call = ", ".join(args[r] for r in regs[:hi + 1])
        params = ", ".join(f"u32 {r}" for r in regs[:hi + 1] if args[r] == r or r in used) or "void"
        return params, f"{target}({call})"

    # tail-call wrapper: addiu sp ; [arg setup] ; ld ra ; j T ; addiu sp
    if n >= 5 and b[0].startswith("addiu $sp, $sp, -") \
       and b[-3].startswith("ld $ra,") and b[-2].startswith("j ") and b[-1].startswith("addiu $sp, $sp,"):
        target = b[-2].split(None, 1)[1]
        r = transform([x for x in b[1:-3] if not re.match(r"sd \$ra,", x)])
        if r:
            params, call = build_call(r[0], r[1], target)
            return ("u32", params, f"return {call};", None)

    # buffer-fill wrapper: addiu sp,-N ; [setup] ; jal T ; daddu a0,sp,zero ; <load v0,off(sp)> ; ld ra ; jr ra ; addiu sp,N
    if n >= 7 and b[0].startswith("addiu $sp, $sp, -") and b[-1].startswith("addiu $sp, $sp,") and b[-2] == "jr $ra":
        mN = re.match(r"addiu \$sp, \$sp, (-0x[0-9A-Fa-f]+)$", b[0])
        jal_idx = next((i for i, x in enumerate(b) if x.startswith("jal ")), None)
        ld_idx = next((i for i, x in enumerate(b) if x.startswith("ld $ra,")), None)
        if mN and jal_idx is not None and ld_idx is not None:
            frame = -int(mN.group(1), 16)
            target = b[jal_idx].split(None, 1)[1]
            delay = b[jal_idx + 1] if jal_idx + 1 < n else "nop"
            if delay == "daddu $a0, $sp, $zero":
                retload = None
                for x in b[jal_idx + 2:ld_idx]:
                    m = re.match(r"(lw|lh|lhu|lb|lbu) \$v0, (-?0x[0-9A-Fa-f]+)\(\$sp\)$", x)
                    if m:
                        retload = (m.group(1), int(m.group(2), 16))
                        break
                if retload:
                    ty = {"lw": "u32", "lh": "s16", "lhu": "u16", "lb": "s8", "lbu": "u8"}[retload[0]]
                    setup = [x for x in b[1:jal_idx] if not re.match(r"sd \$ra,", x)]
                    extra = {}
                    for x in setup:
                        m = re.match(r"addiu \$(a1|a2|a3), \$zero, (-?0x[0-9A-Fa-f]+)$", x)
                        if m:
                            extra[m.group(1)] = int(m.group(2), 16)
                    callargs = ["buf"] + [str(extra[r]) if r in extra else "0" for r in ("a1", "a2", "a3")]
                    while len(callargs) > 1 and callargs[-1] == "0":
                        callargs.pop()
                    bufsz = frame - 0x10
                    if bufsz <= 0:
                        bufsz = frame
                    return (ty, "void",
                            f"u8 buf[{bufsz:#x}]; {target}({', '.join(callargs)}); "
                            f"return *({ty} *)(buf + {retload[1]:#x});", None)

    # non-tail wrapper: addiu sp ; sd ra ; [setup] ; jal T ; [delay] ; [result] ; ld ra ; jr ra ; addiu sp
    if n >= 6 and b[0].startswith("addiu $sp, $sp, -") and b[-1].startswith("addiu $sp, $sp,"):
        jal_idx = next((i for i, x in enumerate(b) if x.startswith("jal ")), None)
        jr_idx = next((i for i, x in enumerate(b) if x == "jr $ra"), None)
        ld_idx = next((i for i, x in enumerate(b) if x.startswith("ld $ra,")), None)
        if jal_idx is not None and jr_idx is not None and ld_idx is not None and ld_idx < jr_idx:
            target = b[jal_idx].split(None, 1)[1]
            setup = [x for x in b[1:jal_idx] if not re.match(r"sd \$ra,", x)]
            if jal_idx + 1 < n and b[jal_idx + 1] != "nop":
                setup.append(b[jal_idx + 1])
            result = b[ld_idx + 1:jr_idx]
            r = transform(setup)
            if r:
                params, call = build_call(r[0], r[1], target)
                if not result:
                    return ("void", params, f"{call};", None)
                if len(result) == 1:
                    if result[0] == "daddu $v0, $zero, $zero":
                        return ("u32", params, f"{call}; return 0;", None)
                    m = re.match(r"(lw|lh|lhu|lb|lbu) \$v0, (-?0x[0-9A-Fa-f]+)\(\$v0\)$", result[0])
                    if m:
                        ty = {"lw": "u32", "lh": "s16", "lhu": "u16", "lb": "s8", "lbu": "u8"}[m.group(1)]
                        return ("u32", params, f"return *({ty} *)((u8 *){call} + {int(m.group(2), 16):#x});", None)
    return None


def externs(cands):
    """extern lines for the batch: the pattern's own, plus `extern u8 D_X[];` for any other global it uses."""
    decls = {r[3] for _, _, _, r in cands if r[3]}
    named = {re.search(r"(D_\w+)", d).group(1) for d in decls if re.search(r"(D_\w+)", d)}
    for _, _, _, r in cands:
        for sym in re.findall(r"\b(D_[0-9A-F]+)\b", r[2]):
            if sym not in named:
                decls.add(f"extern u8 {sym}[];")
                named.add(sym)
    return sorted(decls)


def render(name, res):
    ret, params, body, decl = res
    return (decl + "\n" if decl else "") + f"{ret} {name}({params}) {{ {body} }}\n"


def main():
    args = sys.argv[1:]
    cc = None
    lo, hi = 0, 1 << 32
    limit = None
    if "--cc" in args:
        cc = args[args.index("--cc") + 1]
    if "--range" in args:
        i = args.index("--range")
        lo, hi = int(args[i + 1], 16), int(args[i + 2], 16)
    if "--max" in args:
        limit = int(args[args.index("--max") + 1])
    ranges = [tuple(r) for t in TARGETS for r in t.get("game_ranges", [t["image"]])]

    cands = []
    for path in sorted((ROOT / "asm").rglob("*.s")):
        if "data" in path.parts or "nonmatchings" in path.parts:
            continue
        for name, addr, insns, size in parse(path):
            if addr is None or not lo <= addr < hi or not any(a <= addr < b for a, b in ranges):
                continue
            if any(x.startswith((".", "glabel")) for x in insns):
                continue
            res = form(insns)
            if res:
                cands.append((addr, name, size, res))
    if limit:
        cands = cands[:limit]
    print(f"candidates: {len(cands)}")

    # One scratch file holds every candidate: one compile + one fdiff run for the whole batch. Candidates the
    # compiler rejects (an implicit declaration clashing with a later definition) are dropped and it retries.
    scratch = ROOT / "src" / "auto" / "_sweep.c"
    scratch.parent.mkdir(parents=True, exist_ok=True)
    cmd = [sys.executable, str(Path(__file__).parent / "fdiff.py")] + (["--cc", cc] if cc else []) + \
        [str(scratch.relative_to(ROOT))]
    ok = set()
    for _ in range(20):
        decls = externs(cands)
        text = '#include "common.h"\n\n' + "\n".join(decls) + "\n\n"
        first = text.count("\n") + 1
        text += "".join(render(n, (r[0], r[1], r[2], None)) for _, n, _, r in cands)
        scratch.write_text(text)
        r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
        ok = set(re.findall(r"^(\w+): OK", r.stdout, re.M))
        bad_lines = {int(n) for n in re.findall(r"_sweep\.c:(\d+):", r.stderr)}
        if ok or not bad_lines:
            break
        cands = [c for i, c in enumerate(cands) if first + i not in bad_lines]
    scratch.unlink()
    good = [c for c in cands if c[1] in ok]
    print(f"verified OK: {len(good)} of {len(cands)}")

    # Group consecutive functions: the next one starts where this one ends (sizes include alignment).
    runs = []
    for c in sorted(good):
        if runs and runs[-1][-1][0] + runs[-1][-1][2] == c[0]:
            runs[-1].append(c)
        else:
            runs.append([c])
    print(f"runs (C files): {len(runs)}")
    if "--write" not in args:
        return
    lines = []
    for run in runs:
        start, end = run[0][0], run[-1][0] + run[-1][2]
        stem = f"auto/auto_{start:06x}"
        decls = externs(run)
        body = "".join(f"/* {c[1]} */\n" + render(c[1], (c[3][0], c[3][1], c[3][2], None)) for c in run)
        (ROOT / "src" / f"{stem}.c").write_text(
            '#include "common.h"\n\n' + ("\n".join(decls) + "\n\n" if decls else "") + body)
        lines.append(f"{start:#x} {end:#x} {stem}")
    cf = ROOT / "config" / "c_files.txt"
    old = cf.read_text() if cf.exists() else "# start end src (without extension); scripts/gen_yaml.py reads it\n"
    cf.write_text(old + "\n".join(lines) + "\n")
    if cc and cc != "default":
        print(f"note: list these files in config/cc_{cc}.txt so the build uses the same compiler")
    print(f"wrote {len(runs)} files, appended to config/c_files.txt")


if __name__ == "__main__":
    main()
