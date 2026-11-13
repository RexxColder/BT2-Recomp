#!/usr/bin/env python3
"""Builds the native C of verified functions into the hybrid PC build (port/build/native).

Usage: port/tools/gen_native.py --list FILE [--out port/build/gen]

Each address of FILE is a function whose C (the m2c draft scratch/m2c_sweep/m2c_XXXXXX.c) scripts/fn_diff.py
found EQUAL to the original inside PCSX2. For each one:
  1. the draft is preprocessed for the host (clang -E, include/ with port/include/native_compat.h forced in);
  2. port/tools/ptr32.py (from Tenkaichi3Decomp) rewrites every pointer of it to 4 bytes (`* __ptr32 __uptr`), so
     structures, globals and locals keep the PS2's layout; guest RAM is at its own host addresses
     (PS2X_IDENTITY_RDRAM=1), so a 4-byte pointer the game stored is a valid host pointer;
  3. clang compiles it (x86-64, -fms-extensions, not position-independent: the game's globals are absolute
     symbols at their PS2 addresses, given to the linker from the symbol files) into libbt2native.a;
  4. a wrapper (native_wrappers.cpp) takes the arguments from the R5900 context as the EE's EABI passes them
     (scratch/protos/ctx.h: a0-a3,t0-t3 / f12-f19), calls the C, puts the result in v0 or f0 and returns to ra;
     installNativeFunctions() puts the wrappers over the recompiled functions in the runtime's function table
     (PS2Runtime::replaceFunction); every jal goes through it. Functions reached by a direct C++ tail call in the
     recompiled code are left out (they would be bypassed).
A game function the C calls is reached through a bridge (bt2g_<name>, in native_wrappers.cpp): it puts the
arguments in the context as the EABI does (from the C's own declaration of the callee: the one ee-gcc compiled
when scripts/fn_diff.py checked it), sets ra to a sentinel and runs the recompiled code, resuming it from ctx->pc
after every checkpoint, until it returns to the sentinel. The C runs on a stack below 2 GB (MAP_32BIT), so a
pointer to one of its locals survives the 4-byte pointers. A guest thread switch can not happen inside: the list
should hold only functions that never block (scripts/callgraph.py --check); one that does anyway is fatal.
"""

import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "scripts"))
import fdiff  # noqa: E402

DRAFTS = ROOT / "scratch" / "m2c_sweep"
COMPAT = ROOT / "port" / "include" / "native_compat.h"


def matched_sources():
    """address -> C file the agents made match the original (docs/agents/*_files.txt, fdiff OK): correct by
    construction, preferred over the m2c draft; then the agents' equivalent C verified in PCSX2. Only agent files
    holding exactly one function (start..end = the
    function's bounds in port/funcmap.csv): the others' functions would collide with their absolute symbols."""
    bounds = {int(r.split(",")[1], 16): int(r.split(",")[2], 16)
              for r in (ROOT / "port/funcmap.csv").read_text().splitlines()[1:]}
    out = {}
    for lst in sorted((ROOT / "docs/agents").glob("*_files.txt")):
        for line in lst.read_text().splitlines():
            parts = line.split()
            if len(parts) == 3 and parts[0].startswith("0x"):
                lo, hi = int(parts[0], 16), int(parts[1], 16)
                c = ROOT / "src" / f"{parts[2]}.c"
                if bounds.get(lo) == hi and c.exists():
                    out[lo] = c
    # Equivalent (not matching) C from the agents (port/eq/<ADDR6>.c) that scripts/fn_diff.py found EQUAL to the
    # original inside PCSX2 (build_port/eq/fn_diff.csv).
    res = ROOT / "build_port/eq/fn_diff.csv"
    if res.exists():
        for line in res.read_text().splitlines():
            parts = line.split(",")
            c = ROOT / "port/eq" / f"{int(parts[0], 16):06X}.c"
            if len(parts) > 1 and parts[1] == "EQUAL" and c.exists():
                out.setdefault(int(parts[0], 16), c)
    # BT2_NATIVE_ALL_EQ=1: every port/eq file, verified or not (test builds: a bad one is found by running the
    # game and switching it off with BT2_NATIVE_SKIP, see docs/PORT_LOG.md).
    if os.environ.get("BT2_NATIVE_ALL_EQ") == "1":
        for c in sorted((ROOT / "port/eq").glob("*.c")):
            out.setdefault(int(c.stem, 16), c)
    return out


def tail_targets():
    """Functions the recompiled code reaches by a direct C++ call (a `j` tail jump), not through the function
    table: a native version of them would be bypassed there."""
    out = set()
    for f in (ROOT / "port/build/recomp").glob("*_0x*.cpp"):
        own = f.stem.rsplit("_0x", 1)[1]
        for m in re.finditer(r"\b\w+_0x([0-9a-f]+)\(rdram, ctx, runtime\)", f.read_text()):
            if m.group(1) != own:
                out.add(int(m.group(1), 16))
    return out


def protos():
    out = {}
    for line in (ROOT / "scratch/protos/ctx.h").read_text().splitlines():
        m = re.match(r"(\w+)\s+(\w+)\((.*)\);", line)
        if m:
            args = [] if m.group(3) in ("", "void") else [x.strip().split()[0] for x in m.group(3).split(",")]
            out[m.group(2)] = (m.group(1), args)
    return out


def decl_params(c, name):
    """(float flags of the parameters, returns float) of `name`'s declaration in the C, or None when there is
    none usable (no declaration, varargs, double, more than 8 of a kind)."""
    m = re.search(rf"^[^;{{}}()]*?\b(\w[\w\s*]*?)\s*\b{re.escape(name)}\s*\(([^)]*)\)\s*;", c, re.M)
    if not m:
        return None
    ret, ps = m.group(1), m.group(2).strip()
    if "..." in ps or "double" in ps or "f64" in ps or "double" in ret or "f64" in ret:
        return None
    if ps == "":
        return "unspecified"  # `f()` in C: parameters not given, not zero of them
    flags = [] if ps == "void" else [bool(re.search(r"\b(f32|float)\b", x) and "*" not in x) for x in ps.split(",")]
    if flags.count(True) > 8 or flags.count(False) > 8:
        return None
    return flags, bool(re.search(r"\b(f32|float)\b", ret)) and "*" not in ret


def call_arg_counts(c, name):
    """Numbers of arguments at each call of name in the C text."""
    out = []
    for m in re.finditer(rf"\b{re.escape(name)}\s*\(", c):
        i, depth, n, empty = m.end(), 1, 1, True
        while i < len(c) and depth:
            ch = c[i]
            if ch in "([":
                depth += 1
            elif ch in ")]":
                depth -= 1
            elif ch == "," and depth == 1:
                n += 1
            if depth and not ch.isspace():
                empty = False
            i += 1
        out.append(0 if empty else n)
    return out


# Flags shared by both paths below. -mno-sse matters on the IR path: with 4-byte pointers (address space 271) and
# SSE vector memory operands clang emits IR the x86-64 backend cannot select.
CLANG_FLAGS = ["-O2", "-m64", "-fno-pic", "-fno-pie", "-fms-extensions", "-fno-strict-aliasing", "-fwrapv",
               "-fno-stack-protector", "-w", "-Wno-int-conversion", "-Wno-incompatible-pointer-types",
               "-Wno-incompatible-function-pointer-types", "-Wno-implicit-function-declaration", "-Wno-implicit-int"]

# BT2_TARGET=win: el C del juego para el PE de Windows (mingw-w64; ver port/full/win/ y port/tools/link_full.py).
# -mno-ms-bitfields: los structs del juego con bitfields quedan con el layout de GCC/PS2, no el de MSVC.
WIN = os.environ.get("BT2_TARGET") == "win"
# (en las tres etapas: preprocesado, ptr32.py y compilación; sin __CRT__NO_INLINE los headers de mingw definen
# __debugbreak y otros builtins inline, y el layout que mide ptr32.py tiene que ser el mismo que el del compilador)
TARGET_FLAGS = ["--target=x86_64-w64-mingw32", "-fms-extensions", "-mno-ms-bitfields", "-D__CRT__NO_INLINE"] if WIN else []
if WIN:
    CLANG_FLAGS = TARGET_FLAGS + CLANG_FLAGS

if os.environ.get("BT2_TRACE_BUILD"):   # traza de llamadas: port/full/plat_trace.c
    CLANG_FLAGS = CLANG_FLAGS + ["-finstrument-functions"]

# The errors only the IR path can fix: a call through a 4-byte pointer, or a memcpy/memset on one, are emitted as
# IR that LLVM's x86-64 backend has no instruction sequence for. port/tools/irfix.py (from Tenkaichi3Decomp)
# rewrites that IR, so the object comes from llc instead of clang's own backend.
IR_ONLY_ERRORS = ("X86ISD::CALL", "X86ISD::TC_RETURN", "address space 271", "X86ISD::")

# The IR path (clang -emit-llvm -> irfix.py -> llc) fixes 12 of our compile errors, but the objects it produced
# crashed the game at startup (a rewritten call-through-pointer ended up jumping into guest RAM as host code), so
# it is OFF: those 12 stay recompiled. irfix.py came from Tenkaichi3Decomp, whose ptr32/IR shape is not identical to
# ours, so it needs adapting before it can be trusted. Enable with BT2_IRFIX=1 once it has been debugged.
IRFIX_ENABLED = os.environ.get("BT2_IRFIX", "1") != "0"   # activado por defecto (sin el, 8 eq fallan: ver docs/LEEME_PRIMERO.md sec. 8)


def canary_flags(c):
    """BT2_CANARY=sub1,sub2,...: si alguna subcadena aparece en la ruta del .c, se recompila con
    -fstack-protector-all. Va despues de CLANG_FLAGS para pisar su -fno-stack-protector."""
    spec = os.environ.get("BT2_CANARY", "")
    if spec and any(k and k in str(c) for k in spec.split(",")):
        return ["-fstack-protector-all"]
    return []


def compile_c(c, o):
    r = subprocess.run(["clang", "-c"] + CLANG_FLAGS + canary_flags(c) + ["-x", "c", str(c), "-o", str(o)],
                       capture_output=True, text=True)
    if r.returncode == 0 or not IRFIX_ENABLED or not any(e in r.stderr for e in IR_ONLY_ERRORS):
        return r
    return compile_c_via_ir(c, o, r.stderr)


def compile_c_via_ir(c, o, clang_err):
    """clang -S -emit-llvm -> irfix.py -> llc -filetype=obj. Slower, so it only runs when the direct compile hit
    one of the errors above (port/tools/irfix.py, taken from Tenkaichi3Decomp's port/tools/irfix.py)."""
    ir = o.with_suffix(".ll")
    fixed = o.with_suffix(".fixed.ll")
    r = subprocess.run(["clang", "-S", "-emit-llvm"] + CLANG_FLAGS + canary_flags(c) + ["-x", "c", str(c), "-o", str(ir)],
                       capture_output=True, text=True)
    if r.returncode:
        return subprocess.CompletedProcess(r.args, r.returncode, r.stdout, clang_err)
    r = subprocess.run([sys.executable, str(ROOT / "port/tools/irfix.py"), str(ir), str(fixed)],
                       capture_output=True, text=True)
    if r.returncode:
        return subprocess.CompletedProcess(r.args, r.returncode, r.stdout,
                                           clang_err + "\nirfix: " + r.stderr.strip())
    # -relocation-model=static: the game's globals are absolute symbols at their PS2 addresses (native_syms.ld),
    # which only works without PIC.
    r = subprocess.run(["llc", "-O2", "-relocation-model=static", "-filetype=obj"]
                       + (["-mtriple=x86_64-w64-windows-gnu"] if WIN else []) + [str(fixed), "-o", str(o)],
                       capture_output=True, text=True)
    if r.returncode:
        return subprocess.CompletedProcess(r.args, r.returncode, r.stdout,
                                           clang_err + "\nllc: " + r.stderr.strip())
    return subprocess.CompletedProcess(r.args, 0, "", "")


def undefined(o):
    nm = subprocess.run(["nm", str(o)], capture_output=True, text=True).stdout
    return [l.split()[1] for l in nm.splitlines() if l.split()[:1] == ["U"]]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--list", type=Path, required=True)
    ap.add_argument("--out", type=Path, default=ROOT / "port/build/gen")
    a = ap.parse_args()
    src_dir = a.out / "src" / "native"   # under port/build/gen/src: ptr32.py treats it as game text
    obj_dir = a.out / "obj"
    src_dir.mkdir(parents=True, exist_ok=True)
    obj_dir.mkdir(parents=True, exist_ok=True)
    pr = protos()
    names = {v: n for n, v in fdiff.targets().items() if "." not in n}
    starts = {int(r.split(",")[1], 16) for r in (ROOT / "port/funcmap.csv").read_text().splitlines()[1:]}
    status = (DRAFTS / "status.csv").read_text().splitlines()[1:]
    name_of = {int(l.split(",")[0], 16): l.split(",")[1] for l in status}

    built, syms, wrappers, failed, bridges = [], {}, [], [], {}
    tails = tail_targets()
    matched = matched_sources()
    for addr in [int(x, 16) for x in a.list.read_text().split()]:
        if addr in tails:
            failed.append((addr, "reached by a direct tail call in the recompiled code"))
            continue
        name = name_of.get(addr, names.get(addr, f"func_{addr:08X}"))
        draft = matched.get(addr, DRAFTS / f"m2c_{addr:06X}.c")
        pre = src_dir / f"nat_{addr:06X}.i"
        # Preprocessed from a copy under port/build/gen/src: ptr32.py rewrites the pointers only of text whose
        # line markers name the game's own files (the draft's own path, scratch/, would leave them 8 bytes).
        src = src_dir / f"m2c_{addr:06X}.c"
        src.write_text(draft.read_text())
        r = subprocess.run(["clang", "-E", "-m64", "-I", str(ROOT / "include"), "-include", str(COMPAT),
                            "-D__ptr32=", "-D__uptr=", str(src), "-o", str(pre)], capture_output=True, text=True)
        if r.returncode:
            failed.append((addr, "preprocess: " + r.stderr.strip().splitlines()[-1][:100]))
            continue
        r = subprocess.run([sys.executable, str(ROOT / "port/tools/ptr32.py"), str(pre), "-m64", "-fms-extensions",
                            "-w", "-Wno-int-conversion", "-Wno-incompatible-pointer-types",
                            "-Wno-incompatible-function-pointer-types", "-Wno-implicit-function-declaration",
                            "-Wno-implicit-int"], capture_output=True, text=True)
        if r.returncode:
            failed.append((addr, "ptr32: " + (r.stderr.strip().splitlines() or ["?"])[-1][:100]))
            continue
        c = src_dir / f"nat_{addr:06X}.c"
        # The C name is the game's name plus a prefix: the recompiled functions keep theirs.
        # The C may define it under the symbol files' name or under its auto name (func_XXXXXXXX): both become
        # nat_<name> (the wrapper calls that).
        text = re.sub(rf"\b{re.escape(name)}\b", f"nat_{name}", r.stdout)
        if name != f"func_{addr:08X}":
            text = re.sub(rf"\bfunc_{addr:08X}\b", f"nat_{name}", text)
        c.write_text(text)
        o = obj_dir / f"nat_{addr:06X}.o"
        r = compile_c(c, o)
        if r.returncode:
            failed.append((addr, "compile: " + r.stderr.strip().splitlines()[0][:100]))
            continue
        # A non-void function that falls off its end (matching C may leave the callee's v0 as the result):
        # clang gives no such guarantee.
        if "does not return a value" in subprocess.run(["clang", "-fsyntax-only", "-m64", "-fms-extensions",
                                                        "-Wreturn-type", "-Wno-int-conversion", "-x", "c", str(c)],
                                                       capture_output=True, text=True).stderr:
            failed.append((addr, "non-void function without a return on some path"))
            continue
        und = undefined(o)
        bad = [u for u in und if u not in fdiff.targets() and not re.fullmatch(r"(D|func)_[0-9A-F]{8}", u)]
        if bad:
            failed.append((addr, f"names: {bad[:3]}"))
            continue
        target = {u: fdiff.targets().get(u, None) for u in und}
        target = {u: v if v is not None else int(u.split("_")[1], 16) for u, v in target.items()}
        # Hardware (GS/DMA/VIF registers 0x10000000-, scratchpad 0x70000000, uncached mirrors 0x20000000-): the
        # recompiled code reaches them through the runtime's I/O, a host pointer there is unmapped. Those go
        # native later through a port/ layer (Tenkaichi3Decomp's plat_*), not now.
        hw = [u for u in und if target[u] >= 0x02000000] + \
             [x for x in re.findall(r"\(\s*[\w\s]+\*[\w\s]*\)\s*\(?\s*(0x[0-9A-Fa-f]+)", text) if int(x, 16) >= 0x02000000]
        if hw:
            failed.append((addr, f"hardware access: {hw[:3]}"))
            continue
        # Game functions it calls: through the bridges, renamed so no host library name (memcpy...) answers.
        # (a function only taken as an address, `&EftMod1CC_Update`, stays an absolute symbol: the guest's value)
        calls = [u for u in und if target[u] in starts and re.search(rf"\b{re.escape(u)}\s*\(", text)]
        sig = {u: decl_params(text, u) for u in calls}
        for u in calls:
            # Called without a declaration (C's implicit int): the inferred prototype, when it has no float.
            p = pr.get(u)
            if sig[u] == "unspecified" and (not p or "f32" not in p[1]):
                # the caller loads as many registers as it passes; the inferred count can be short (VU0 code)
                n = max([len(p[1]) if p else 0] + call_arg_counts(text, u)[1:])
                sig[u] = ([False] * n, bool(p) and p[0] == "f32") if n <= 8 else None
            elif sig[u] == "unspecified":
                sig[u] = None
            if sig[u] is None and p and p[0] != "f32" and "f32" not in p[1] and len(p[1]) <= 8 and \
                    not re.search(rf"^[^;{{}}]*\b{re.escape(u)}\b[^;]*;", text, re.M):
                sig[u] = ([False] * len(p[1]), False)
        if any(v is None for v in sig.values()):
            failed.append((addr, "callee declaration: " + " ".join(u for u, v in sig.items() if v is None)[:100]))
            continue
        # A callee given fewer arguments than it reads (scripts/infer_protos.py): the draft dropped a pass-through
        # argument (m2c's known bug), and the original's register leaked through when fn_diff ran it on the EE.
        short = [u for u in calls if u in pr and
                 (sig[u][0].count(False) < sum(t != "f32" for t in pr[u][1]) or
                  min(call_arg_counts(text, u)[1:] or [99]) < len(pr[u][1]) or
                  sig[u][0].count(True) < sum(t == "f32" for t in pr[u][1]))]
        if short and addr not in matched:  # matching C passes what the original passes
            failed.append((addr, "passes fewer arguments than the callee reads: " + " ".join(short)[:100]))
            continue
        # One bridge per callee and declaration (drafts may declare a callee with other parameter counts).
        bname = {u: f"bt2g_{u}__{''.join('f' if x else 'i' for x in sig[u][0])}_{'f' if sig[u][1] else 'i'}" for u in calls}
        if calls:
            text = re.sub(r"\b(" + "|".join(map(re.escape, calls)) + r")\b", lambda m: bname[m.group(1)], text)
            c.write_text(text)
            r = compile_c(c, o)
            if r.returncode:
                failed.append((addr, "compile (bridged): " + r.stderr.strip().splitlines()[0][:100]))
                continue
        for u in calls:
            bridges[bname[u]] = (target[u], sig[u])
        for u in und:
            if u not in calls:
                syms[u] = target[u]
        ret, args = pr.get(name, pr.get(f"func_{addr:08X}", ("s32", ["s32"] * 4)))
        built.append(o)
        wrappers.append((addr, name, ret, args))

    # Wrappers: EABI arguments from the context.
    lines = ['// generated by port/tools/gen_native.py', '#include "ps2_runtime.h"', '#include "ps2_runtime_macros.h"',
             '#include <cstdint>', '#include <cstdio>', '#include <cstdlib>', '#include <cctype>', '#include <cstring>', '#include <mutex>', '#include <string>',
             '#include <sys/mman.h>', '#include <type_traits>', '#include <unordered_set>', '', 'extern "C" {']
    for addr, name, ret, args in wrappers:
        # Integer and pointer arguments travel as 64-bit values zero-extended from the 32-bit guest register:
        # ptr32.py keeps a parameter's outermost pointer 8 bytes wide, and an int callee reads the low half.
        ctype = {"void": "void", "s32": "uint64_t", "f32": "float"}[ret]
        ps = ", ".join("float" if t == "f32" else "uint64_t" for t in args) or "void"
        lines.append(f"{ctype} nat_{name}({ps});")
    lines += ['uint32_t bt2CallGuest(uint32_t addr, const uint32_t *ia, int ni, const float *fa, int nf, float *f0);']
    for u, (v, (flags, fret)) in sorted(bridges.items()):
        ps = ", ".join(f"float p{i}" if fl else f"uint64_t p{i}" for i, fl in enumerate(flags)) or "void"
        ia = [f"static_cast<uint32_t>(p{i})" for i, fl in enumerate(flags) if not fl]
        fa = [f"p{i}" for i, fl in enumerate(flags) if fl]
        args = (f"{{{', '.join(ia)}}}" if ia else "{0u}", len(ia), f"{{{', '.join(fa)}}}" if fa else "{0.0f}", len(fa))
        if fret:
            lines.append(f"float {u}({ps}) {{ const uint32_t ia[] = {args[0]}; const float fa[] = {args[2]}; float f0; "
                         f"bt2CallGuest(0x{v:08X}u, ia, {args[1]}, fa, {args[3]}, &f0); return f0; }}")
        else:
            lines.append(f"uint64_t {u}({ps}) {{ const uint32_t ia[] = {args[0]}; const float fa[] = {args[2]}; "
                         f"return bt2CallGuest(0x{v:08X}u, ia, {args[1]}, fa, {args[3]}, nullptr); }}")
    lines += [
        '// Runs fn(arg) on the stack at top (16-byte aligned); CFI keeps it walkable for C++ exceptions.',
        'void bt2_stack_call(void (*fn)(void *), void *arg, void *top);',
        '}',
        'asm(R"(',
        '    .text',
        '    .globl bt2_stack_call',
        '    .type bt2_stack_call, @function',
        'bt2_stack_call:',
        '    .cfi_startproc',
        '    push %rbp',
        '    .cfi_def_cfa_offset 16',
        '    .cfi_offset %rbp, -16',
        '    mov %rsp, %rbp',
        '    .cfi_def_cfa_register %rbp',
        '    mov %rdx, %rsp',
        '    and $-16, %rsp',
        '    mov %rdi, %rax',
        '    mov %rsi, %rdi',
        '    call *%rax',
        '    mov %rbp, %rsp',
        '    pop %rbp',
        '    .cfi_def_cfa %rsp, 8',
        '    ret',
        '    .cfi_endproc',
        '    .size bt2_stack_call, .-bt2_stack_call',
        ')");',
        '',
        'namespace {',
        'constexpr uint32_t kSentinel = 0x00000008u; // no function there: the bridged call is over when pc reaches it',
        'constexpr size_t kLowStack = 16u << 20;',
        'struct NativeEnv { uint8_t *rdram; R5900Context *ctx; PS2Runtime *rt; uint8_t *stackTop; int depth; };',
        'thread_local NativeEnv t_env;',
        '',
        '// Runs f with the environment of this guest call, on the low stack (pointers to C locals fit in 4 bytes).',
        'template <class F> void runNative(uint8_t *rdram, R5900Context *ctx, PS2Runtime *rt, uint32_t addr, F &&f) {',
        '    NativeEnv saved = t_env;',
        '    t_env.rdram = rdram; t_env.ctx = ctx; t_env.rt = rt;',
        '    struct Restore { NativeEnv &e; NativeEnv s; ~Restore() { e.rdram = s.rdram; e.ctx = s.ctx; e.rt = s.rt; } } restore{t_env, saved};',
        '    try {',
        '        if (t_env.depth > 0) { f(); return; }',
        '        if (!t_env.stackTop) {',
        '            void *p = mmap(nullptr, kLowStack, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT | MAP_NORESERVE, -1, 0);',
        '            if (p == MAP_FAILED) { std::fprintf(stderr, "[native] no low stack\\n"); std::abort(); }',
        '            t_env.stackTop = static_cast<uint8_t *>(p) + kLowStack;',
        '        }',
        '        struct Depth { int &d; Depth(int &x) : d(x) { ++d; } ~Depth() { --d; } } depth{t_env.depth};',
        '        using G = std::remove_reference_t<F>;',
        '        bt2_stack_call(+[](void *p) { (*static_cast<G *>(p))(); }, &f, t_env.stackTop);',
        '    } catch (...) {',
        '        // A guest thread switch (EeDispatcherTransfer) through a C frame: the C can not be resumed.',
        '        std::fprintf(stderr, "[native] FATAL: 0x%08x left by an exception (blocked inside native C)\\n", addr);',
        '        std::abort();',
        '    }',
        '}',
        '} // namespace',
        '',
        '// The C calling a game function: EABI registers, ra = sentinel, run the recompiled code to the sentinel.',
        'extern "C" uint32_t bt2CallGuest(uint32_t addr, const uint32_t *ia, int ni, const float *fa, int nf, float *f0) {',
        '    NativeEnv &e = t_env;',
        '    R5900Context *ctx = e.ctx;',
        '    const uint64_t ra = GPR_U64(ctx, 31);',
        '    for (int i = 0; i < ni; ++i) SET_GPR_U32(ctx, 4 + i, ia[i]);',
        '    for (int i = 0; i < nf; ++i) std::memcpy(&ctx->f[12 + i], &fa[i], 4);',
        '    SET_GPR_U32(ctx, 31, kSentinel);',
        '    ctx->pc = addr;',
        '    while (ctx->pc != kSentinel) {',
        '        if (e.rt->isStopRequested()) break;',
        '        if (!e.rt->hasFunction(ctx->pc)) {',
        '            std::fprintf(stderr, "[native] FATAL: bridged call 0x%08x reached 0x%08x, no function\\n", addr, ctx->pc);',
        '            std::abort();',
        '        }',
        '        e.rt->lookupFunction(ctx->pc)(e.rdram, ctx, e.rt);',
        '    }',
        '    SET_GPR_U64(ctx, 31, ra);',
        '    if (f0) std::memcpy(f0, &ctx->f[0], 4);',
        '    return getRegU32(ctx, 2);',
        '}',
        '',
        'namespace {', 'inline float fregF(R5900Context *c, int i) { float f; std::memcpy(&f, &c->f[i], 4); return f; }',
              'inline void setF0(R5900Context *c, float v) { std::memcpy(&c->f[0], &v, 4); }',
              'inline void firstCall(uint32_t addr) {',
              '    static const bool log = std::getenv("BT2_NATIVE_LOG") != nullptr;',
              '    static std::unordered_set<uint32_t> seen; static std::mutex m;',
              '    if (!log) return;',
              '    std::lock_guard<std::mutex> g(m);',
              '    if (seen.insert(addr).second) std::fprintf(stderr, "[native] first call 0x%08x\\n", addr);',
              '}']
    for addr, name, ret, args in wrappers:
        ia, fa, call = 0, 0, []
        for t in args:
            if t == "f32":
                call.append(f"fregF(ctx, {12 + fa})")
                fa += 1
            else:
                call.append(f"static_cast<uint64_t>(getRegU32(ctx, {4 + ia}))")
                ia += 1
        body = f"nat_{name}({', '.join(call)})"
        if ret == "void":
            body += ";"
        elif ret == "f32":
            body = f"setF0(ctx, {body});"
        else:
            body = f"SET_GPR_U32(ctx, 2, static_cast<uint32_t>({body}));"
        # First call of each native function is logged (BT2_NATIVE_LOG=1): proof that the game reached it.
        # Installed over the translation in the function table (installNativeFunctions).
        lines.append(f"}} void native_{addr:08X}(uint8_t *rdram, R5900Context *ctx, PS2Runtime *rt) {{ firstCall(0x{addr:08X}u); "
                     f"const uint32_t ra = getRegU32(ctx, 31); runNative(rdram, ctx, rt, 0x{addr:08X}u, [&] {{ {body} }}); "
                     f"ctx->pc = ra; }} namespace {{")
    lines += ['} // namespace', '',
              '// BT2_NATIVE_SKIP=0xADDR,0xADDR...: those stay recompiled (bisecting a bad native without a rebuild).',
              '// BT2_NATIVE_SKIP_FILE=path: the same, one address per line (bisecting long lists).',
              '// BT2_NATIVE_LIMIT=N: only the first N of the list (halving a bad batch).',
              'int installNativeFunctions(PS2Runtime &rt)', '{', '    int n = 0;',
              '    std::string skipAll;',
              '    if (const char *e = std::getenv("BT2_NATIVE_SKIP")) skipAll = e;',
              '    if (const char *f = std::getenv("BT2_NATIVE_SKIP_FILE")) {',
              '        if (FILE *fp = std::fopen(f, "r")) { char line[64]; while (std::fgets(line, sizeof line, fp)) { skipAll += ","; skipAll += line; } std::fclose(fp); }',
              '    }',
              '    for (auto &c : skipAll) if (c == \'\\n\' || c == \'\\r\' || c == \' \') c = \',\';',
              '    const char *skip = skipAll.empty() ? nullptr : skipAll.c_str();',
              '    long limit = -1; if (const char *l = std::getenv("BT2_NATIVE_LIMIT")) limit = std::strtol(l, nullptr, 0);',
              '    long index = 0;',
              '    auto use = [skip](uint32_t a) {',
              '        char key[16]; std::snprintf(key, sizeof key, "%x", a);',
              '        if (!skip) return true;',
              '        std::string s(skip); for (auto &c : s) c = std::tolower(static_cast<unsigned char>(c));',
              '        size_t p = 0;',
              '        while ((p = s.find(key, p)) != std::string::npos) {',
              '            bool l = p == 0 || !std::isxdigit(static_cast<unsigned char>(s[p - 1])) || (p >= 2 && s[p - 1] == \'x\' && s[p - 2] == \'0\') || s[p - 1] == \'0\';',
              '            size_t e = p + std::strlen(key);',
              '            if (l && (e == s.size() || !std::isxdigit(static_cast<unsigned char>(s[e])))) return false;',
              '            p = e;',
              '        }',
              '        return true;',
              '    };']
    for addr, *_ in wrappers:
        lines.append(f"    if ((limit < 0 || index++ < limit) && use(0x{addr:08X}u)) n += rt.replaceFunction(0x{addr:08X}u, native_{addr:08X}) ? 1 : 0;")
    lines += ['    return n;', '}', '']
    (a.out / "native_wrappers.cpp").write_text("\n".join(lines))
    # The game's globals and functions the C reaches: absolute symbols at their PS2 addresses.
    (a.out / "native_syms.ld").write_text("".join(f"{s} = 0x{v:08X};\n" for s, v in sorted(syms.items())))
    lib = a.out / "libbt2native.a"
    lib.unlink(missing_ok=True)
    if built:
        subprocess.run(["ar", "rcs", str(lib), *map(str, built)], check=True)
    (a.out / "native_list.txt").write_text("".join(f"0x{x:08X}\n" for x, *_ in wrappers))
    (a.out / "native_failed.txt").write_text("".join(f"0x{x:08X} {why}\n" for x, why in failed))
    print(f"{len(built)} native functions, {len(bridges)} bridged callees, {len(syms)} absolute symbols, "
          f"{len(failed)} failed -> {a.out}")


if __name__ == "__main__":
    main()
