"""Reads game.toml, the one file that says what is game-specific in a project built with ps2-decomp-kit.

Every kit script imports this instead of carrying the game's paths and addresses as constants (which is what
BT3-Decompiled's scripts did). The project root is the nearest folder, from this file upward, holding game.toml.
"""

try:
    import tomllib
except ModuleNotFoundError:  # Python < 3.11 (contenedor del AppImage)
    import tomli as tomllib
from pathlib import Path


def find_root():
    for d in [Path(__file__).resolve().parent, *Path(__file__).resolve().parents]:
        if (d / "game.toml").exists():
            return d
    raise SystemExit("game.toml not found above " + str(Path(__file__).resolve().parent))


ROOT = find_root()
CFG = tomllib.loads((ROOT / "game.toml").read_text())

GAME = CFG["game"]
TC = CFG["toolchain"]
BINUTILS = TC.get("binutils", "tools/binutils/mips-ps2-decompals-")
# The linker can be another build: binutils 2.40's ld matches every script statement against every input
# section, which grows with the square of the number of objects (10 min at 4500 objects, ~1 h at 5200); 2.47's
# links the same script in seconds. Its output is checked byte for byte like everything else.
LINKER = TC.get("linker", BINUTILS + "ld")
CC = TC.get("cc", "tools/ee-gcc2.96/bin/ee-gcc")
CC_FLAGS = TC.get("cc_flags", "-O2 -fno-strict-aliasing -Iinclude")
CXX_FLAGS = TC.get("cxx_flags", CC_FLAGS)
G_DEFAULT = TC.get("g_default", "-G8")
# Keys are path prefixes (a directory with its slash, or the stem of a group of files).
G_FLAGS = TC.get("g_flags", {})
AS_G_FLAGS = TC.get("as_g_flags", {})
# Other compilers, chosen per source file by config/cc_<key>.txt (one src path per line, '#' comments).
ALT_CC = TC.get("alt_cc", {})
# Every ee-gcc build under tools/ is also an alt compiler named after its folder (ee-gcc2.95.3-136 ...), so
# `fdiff.py --all-cc` can identify the original compiler; Win32 builds run under wine.
for _d in sorted((ROOT / "tools").glob("ee-gcc*")):
    for _exe in ("ee-gcc", "ee-gcc.exe"):
        if (_d / "bin" / _exe).exists():
            _cmd = f"tools/{_d.name}/bin/{_exe}"
            ALT_CC.setdefault(_d.name, f"env WINEDEBUG=-all wine {_cmd}" if _exe.endswith(".exe") else _cmd)
            break
# Post-processing of compiler output per alt compiler key (e.g. ee-gcc 2.9's trailing .p2align).
STRIP_PAD = set(TC.get("strip_func_pad", []))
AS_FLAGS = TC.get("as_flags", "-EL -march=r5900 -mabi=eabi -G0 -no-pad-sections -Iinclude")
# Compiler output is assembled as o64 so 32-bit pointer arithmetic expands to addiu/addu, as Sony's assembler did.
CC_AS_FLAGS = TC.get("cc_as_flags", "-EL -march=r5900 -mabi=o64 -no-pad-sections -mno-pdr -Iinclude")

TARGETS = CFG["target"]
for _t in TARGETS:
    _t.setdefault("subdir", None)
    _t.setdefault("src_subdir", None)
    _t.setdefault("yaml", f"config/{_t['name']}.yaml")
    _t.setdefault("built", f"build/{_t['name']}.rom")
    _t.setdefault("elf_out", f"build/{_t['name']}.elf")
    pre = f"{_t['subdir']}_" if _t["subdir"] else ""
    _t.setdefault("undef_funcs", f"build/{pre}undefined_funcs_auto.txt")
    _t.setdefault("undef_syms", f"build/{pre}undefined_syms_auto.txt")
    _t.setdefault("extern_syms", f"build/{_t['name']}_extern_syms.ld")
    _t.setdefault("ld_extra", [])
    _t.setdefault("flatten", False)
    if "elf" in _t:
        _t.setdefault("original", f"disc/{_t['name']}.rom")
    _t["ld_scripts"] = [f"build/{_t['name']}.ld", _t["undef_funcs"], _t["undef_syms"], _t["extern_syms"],
                        *([] if _t["flatten"] else [f"build/{_t['name']}_provide.ld"]), *_t["ld_extra"]]
SUBDIRS = {t[k] for t in TARGETS for k in ("subdir", "src_subdir") if t[k]}


def rom_size(target):
    """Bytes of a target's flat image: `rom_size` from game.toml, else elf_survey.image_size (first PT_LOAD to
    the end of the last one's file data, rounded up to 128)."""
    if "rom_size" in target:
        return target["rom_size"]
    import elf_survey  # same folder as this file
    _data, _entry, phdrs, _sections = elf_survey.read_elf(ROOT / target["elf"])
    return elf_survey.image_size(phdrs)


def alt_cc_files():
    """src path -> alt compiler key, from config/cc_<key>.txt."""
    out = {}
    for key in ALT_CC:
        path = ROOT / "config" / f"cc_{key}.txt"
        if path.exists():
            for line in path.read_text().splitlines():
                line = line.split("#", 1)[0].strip()
                if line:
                    out[line] = key
    return out


def gflag(src):
    return next((g for d, g in G_FLAGS.items() if str(src).startswith(d)), G_DEFAULT)


def as_gflag(src):
    return next((g for d, g in AS_G_FLAGS.items() if str(src).startswith(d)), gflag(src))


def target_for(addr):
    """The target whose image holds addr (the first one if none does)."""
    return next((t for t in TARGETS if t["image"][0] <= addr < t["image"][1]), TARGETS[0])
