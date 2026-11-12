#!/usr/bin/env python3
"""Lee el volcado binario de la traza de llamadas (port/full/plat_trace.c) y lo resuelve con nm.

  scripts/trace_sym.py TRACE.bin EXE text [--from N] [--to N] [--depth D] [--grep RX]   eventos como texto
  scripts/trace_sym.py TRACE.bin EXE first                                             primera llamada y cuenta por funcion
  scripts/trace_sym.py TRACE.bin EXE frames                                            eventos y funciones distintas por vblank
  scripts/trace_sym.py TRACE.bin EXE diff A0 A1 B0 B1                                  funciones en vblanks [A0,A1] y no en [B0,B1]
  scripts/trace_sym.py TRACE.bin EXE never                                             funciones del exe (func_*) que nunca se llamaron

EXE es el mismo bt2full con el que se grabo (port/build/full_trace/bt2full). Las direcciones del llamador son sitios de
retorno: se muestran como funcion+offset.  Uso: BT2_ULTRALOG=1 BT2_TRACE_OUT=/tmp/trace/t ./bt2full ; kill -USR1 <pid>."""
import bisect
import re
import struct
import subprocess
import sys
from collections import Counter, defaultdict


def load_syms(exe):
    out = subprocess.run(["nm", "-n", "--defined-only", exe], capture_output=True, text=True).stdout
    addrs, names = [], []
    for ln in out.splitlines():
        p = ln.split()
        if len(p) == 3 and p[1] in "TtWw":
            addrs.append(int(p[0], 16)); names.append(p[2])
    return addrs, names


def sym(a, S):
    addrs, names = S
    i = bisect.bisect_right(addrs, a) - 1
    if i < 0 or a - addrs[i] > 0x10000:
        return "0x%08X" % a
    off = a - addrs[i]
    return names[i] + ("+0x%X" % off if off else "")


def load(path):
    d = open(path, "rb").read()
    magic, n, vb, nseen = struct.unpack_from("<4I", d, 0)
    assert magic == 0x54325442, "no es un volcado de plat_trace"
    ev = list(struct.iter_unpack("<IIIi", d[16:16 + 16 * n]))
    seen = list(struct.iter_unpack("<IIII", d[16 + 16 * n:16 + 16 * n + 16 * nseen]))
    return ev, seen, vb


def opt(args, name, default=None):
    return int(args[args.index(name) + 1]) if name in args else default


def main():
    if len(sys.argv) < 4:
        sys.exit(__doc__)
    path, exe, cmd, args = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4:]
    ev, seen, vb = load(path)
    S = load_syms(exe)
    if cmd == "text":
        lo, hi, dep = opt(args, "--from", 0), opt(args, "--to", 1 << 31), opt(args, "--depth", 1 << 30)
        rx = re.compile(args[args.index("--grep") + 1]) if "--grep" in args else None
        for f, fn, c, d in ev:
            if lo <= f <= hi and d <= dep:
                line = "%u %s%s <- %s" % (f, " " * min(d, 40), sym(fn, S), sym(c, S))
                if not rx or rx.search(line):
                    print(line)
    elif cmd == "first":
        print("# vblank_primera_llamada llamadas funcion  (%d funciones, vblank final %d)" % (len(seen), vb))
        for fn, fr, lo, hi in sorted(seen, key=lambda r: r[1]):
            print(fr, lo | hi << 32, sym(fn, S))
    elif cmd == "frames":
        per = defaultdict(set); cnt = Counter()
        for f, fn, c, d in ev:
            per[f].add(fn); cnt[f] += 1
        for f in sorted(per):
            print(f, cnt[f], len(per[f]))
    elif cmd == "diff":
        a0, a1, b0, b1 = map(int, args[:4])
        A = {fn for f, fn, c, d in ev if a0 <= f <= a1}
        B = {fn for f, fn, c, d in ev if b0 <= f <= b1}
        print("# en [%d,%d] y no en [%d,%d]: %d funciones" % (a0, a1, b0, b1, len(A - B)))
        for fn in sorted(A - B):
            print(sym(fn, S))
    elif cmd == "never":
        called = {fn for fn, *_ in seen}
        addrs, names = S
        for a, n in zip(addrs, names):
            if re.match(r"func_[0-9A-F]{8}$", n) and a not in called:
                print(n)
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
