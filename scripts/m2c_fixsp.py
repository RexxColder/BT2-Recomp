#!/usr/bin/env python3
"""Declares m2c's undeclared `sp` (the stack buffer at offset 0 the function passes to callees).

Usage: scripts/m2c_fixsp.py DRAFT.c FUNC.s   (rewrites DRAFT.c in place; exit 1 when there is nothing to do)

m2c names the frame slot at offset 0 `sp` and passes it (`Mtx_StoreIdentity(sp)`, `memset(sp, 0, 0x40)`) without
declaring it. It becomes `s32 sp[N]` at the top of the function, N words up to the first stack variable m2c did
declare (spXX) or the first register save in the prologue (sd/sq/swc1 ..($sp)), whichever comes first.
"""

import re
import sys
from pathlib import Path


def fix(text, asm):
    # Already declared: a local declaration line `<type> sp;` / `<type> sp[N];` (a use like `x = sp;` is not).
    if not re.search(r"\bsp\b", text) or re.search(r"^\s+(?:const\s+)?[A-Za-z_]\w*[\s*]+sp\s*(\[[^\]]*\])?;", text, re.M):
        return None
    offs = [int(x, 16) for x in re.findall(r"^\s+[\w ]+?\*?\s*sp([0-9A-F]+)(?:\[\w+\])?;", text, re.M)]
    saves = [int(x, 16) for x in re.findall(r"\b(?:sd|sq|sw|swc1)\s+\$(?:s\d|ra|fp|f2\d|f3\d), (0x[0-9A-F]+)\(\$sp\)",
                                            asm)]
    end = min(offs + saves + [0x100])
    if end <= 0:
        return None
    decl = f"    s32 sp[{max(1, end // 4)}];\n"
    m = re.search(r"^[^\s#][^;\n]*\)\s*\{\n", text, re.M)
    if not m:
        return None
    return text[:m.end()] + decl + text[m.end():]


def main():
    draft, asm = Path(sys.argv[1]), Path(sys.argv[2]).read_text()
    out = fix(draft.read_text(), asm)
    if out is None:
        return 1
    draft.write_text(out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
