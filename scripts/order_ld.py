#!/usr/bin/env python3
"""Reorder the generated linker script so all objects are placed in address order.

splat groups input sections by type (.text/.data/.rodata); the retail image is a
single flattened section, so the objects must be placed in their original address
order instead. The object list is rebuilt from the yaml subsegments, which are in
address order.

Usage: order_ld.py build/<name>.ld config/<name>.yaml
"""
import re
import sys
from pathlib import Path

if len(sys.argv) != 3:
    sys.exit(__doc__)
ld = Path(sys.argv[1])
yaml = Path(sys.argv[2])

text = ld.read_text()

# object reference for each subsegment kind
objs = []
for off, kind, name in re.findall(r"\[0x([0-9A-Fa-f]+), (\w+), ([\w/]+)\]", yaml.read_text()):
    if kind == "asm":
        objs.append((int(off, 16), f"build/asm/{name}.o(.text*)"))
    elif kind == "data":
        objs.append((int(off, 16), f"build/asm/data/{name}.data.o(.data*)"))
    elif kind == "c":
        objs.append((int(off, 16), f"build/src/{name}.o(.text* .rodata* .data*)"))
objs.sort(key=lambda x: x[0])

start = text.index("cod_TEXT_START = .;")
end = text.index("cod_RODATA_END = .;") + len("cod_RODATA_END = .;")

new = ["cod_TEXT_START = .;"]
new += [f"        {o}" for _, o in objs]
new += [
    "        cod_TEXT_END = .;",
    "        cod_TEXT_SIZE = ABSOLUTE(cod_TEXT_END - cod_TEXT_START);",
    "        cod_DATA_START = .;",
    "        cod_DATA_END = .;",
    "        cod_DATA_SIZE = 0;",
    "        cod_RODATA_START = .;",
    "        cod_RODATA_END = .;",
    "        cod_RODATA_SIZE = 0;",
]
text = text[:start] + "\n".join(new) + text[end:]
# SUBALIGN(16) pads every input section to 16 bytes; the retail image packs them contiguously.
text = text.replace(".cod 0x100000 : AT(cod_ROM_START) SUBALIGN(16)",
                    ".cod 0x100000 : AT(cod_ROM_START)")
ld.write_text(text)
print(f"ordered {len(objs)} objects by address")
