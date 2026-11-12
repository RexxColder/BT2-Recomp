"""Rewrites an object's ELF e_flags to the value the rest of the link uses.

C output is assembled as o64 (see CC_AS_FLAGS in gamecfg.py); the code is identical but the
linker refuses to mix the two ABI tags, so the tag is patched after assembling. The value is
`e_flags` in game.toml's [toolchain] (the original executable's, `elf_survey.py` prints it).
"""

import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gamecfg import TC  # noqa: E402

E_FLAGS_OFFSET = 0x24
EABI64_FLAGS = TC.get("e_flags", 0x20924001)  # noreorder, 5900, eabi64, mips3

with open(sys.argv[1], "r+b") as f:
    f.seek(E_FLAGS_OFFSET)
    f.write(struct.pack("<I", EABI64_FLAGS))
