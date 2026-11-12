#!/usr/bin/env python3
"""Prints symbol_addrs.txt entries for functions whose name appears in an error string they reference.

Only 1:1 cases are emitted: the function references exactly one name, and no other function
references that name. Run after a split, from the repo root.

Generalised from BT3-Decompiled (CRI middleware strings, "...(name)" / "E123 name:"): every data file
under asm/data/ and every code file under asm/ is read, and C++ "Class::Method" strings (Neversoft
engines print them in their debug messages) give `Class_Method` names.
"""

import collections
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import ROOT  # noqa: E402

# Strings that name something other than the function referencing them
# (a callee, a hardware register, a printf literal).
NOT_OWN_NAME = re.compile(r"^(sce\w+|BDEC|null)$")

# "...(name)" at the end, "E123 name: ..." at the start, ":name:" in the middle, or "Class::Method".
NAME_RE = re.compile(
    r"\(([A-Za-z_]\w{3,})\)\s*(?:\\n)?$"
    r"|^(?:E?\d+[: ]\s*)?([A-Za-z_]\w*_\w+)\s*:"
    r"|:([A-Za-z_]\w*_\w+):"
    r"|\b([A-Z]\w+::~?[A-Za-z_]\w*)\b"
)


def main():
    strings = {}
    for path in sorted((ROOT / "asm" / "data").rglob("*.s")):
        cur = None
        for line in open(path, errors="replace"):
            if m := re.match(r"dlabel (\S+)", line):
                cur = m.group(1)
            elif (m := re.search(r'\.asciz? "(.*)"', line)) and cur and cur not in strings:
                strings[cur] = m.group(1)

    names = collections.defaultdict(set)
    for path in sorted(p for p in (ROOT / "asm").rglob("*.s") if "data" not in p.parts):
        cur = None
        for line in open(path, errors="replace"):
            if m := re.match(r"glabel (\S+)", line):
                cur = m.group(1)
                continue
            for sym in re.findall(r"%(?:hi|lo|gp_rel)\((D_[0-9A-F]+)", line):
                for m in NAME_RE.finditer(strings.get(sym, "")):
                    names[cur].add(next(g for g in m.groups() if g).replace("::~", "_dtor_").replace("::", "_"))

    owners = collections.defaultdict(set)
    for func, ns in names.items():
        for n in ns:
            owners[n].add(func)

    for func, ns in sorted(names.items()):
        (name,) = ns if len(ns) == 1 else (None,)
        if name and len(owners[name]) == 1 and func.startswith("func_") and not NOT_OWN_NAME.match(name):
            print(f"{name} = 0x{func[5:]}; // type:func")


if __name__ == "__main__":
    main()
