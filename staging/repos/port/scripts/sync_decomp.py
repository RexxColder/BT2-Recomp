#!/usr/bin/env python3
"""Sincroniza el C compartido (src/, include/, config/) del repo del port con el repo de la decompilación.

El port lleva una COPIA del C del decomp (modelo BT3: Tenkaichi3Decomp <- BT3-Decompiled). Los cambios propios
de PC van dentro de `#ifdef PORT` / `#ifndef __mips__`; fuera de esos bloques los dos árboles deben ser iguales.

    python3 scripts/sync_decomp.py --decomp ../BT2-Decompiled --check     informa diferencias (código 1 si hay)
    python3 scripts/sync_decomp.py --decomp ../BT2-Decompiled --to-decomp copia port -> decomp (sin bloques PORT)
    python3 scripts/sync_decomp.py --decomp ../BT2-Decompiled --from-decomp  trae del decomp lo que no tiene PORT

Sin rutas absolutas: el repo del port es el padre de scripts/; el del decomp se pasa con --decomp o $BT2_DECOMP.
Por defecto solo muestra lo que haría (--write para escribir)."""
import argparse, difflib, os, pathlib, re, sys

PORT = pathlib.Path(__file__).resolve().parents[1]
SHARED = ["src", "include", "config"]
EXTS = {".c", ".h", ".inc", ".yaml", ".txt"}
PORT_ONLY = re.compile(r"^\s*#\s*if(?:def\s+PORT\b|ndef\s+__mips__\b|\s+.*defined\s*\(\s*PORT\s*\)|\s+!\s*defined\s*\(\s*__mips__\s*\))")


def strip_port(text):
    """Quita los bloques solo-PC (#ifdef PORT ... #else/#endif), conservando la rama #else (la del PS2)."""
    out, stack = [], []   # stack: por cada #if abierto, (es_port, en_else)
    for line in text.splitlines(keepends=True):
        s = line.strip()
        if re.match(r"#\s*if", s):
            stack.append([bool(PORT_ONLY.match(line)), False])
            if stack[-1][0]:
                continue
        elif re.match(r"#\s*else", s) and stack and stack[-1][0]:
            stack[-1][1] = True; continue
        elif re.match(r"#\s*endif", s) and stack:
            if stack.pop()[0]:
                continue
        if any(p and not e for p, e in stack):
            continue
        out.append(line)
    return "".join(out)


def has_port(text):
    return any(PORT_ONLY.match(l) for l in text.splitlines())


def files(root):
    for top in SHARED:
        for p in sorted((root / top).rglob("*")):
            if p.is_file() and p.suffix in EXTS:
                yield p.relative_to(root).as_posix()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--decomp", default=os.environ.get("BT2_DECOMP", str(PORT.parent / "BT2-Decompiled")))
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--check", action="store_true")
    g.add_argument("--to-decomp", action="store_true")
    g.add_argument("--from-decomp", action="store_true")
    ap.add_argument("--write", action="store_true", help="escribe de verdad (si no, solo informa)")
    ap.add_argument("--diff", action="store_true", help="muestra el diff unificado")
    a = ap.parse_args()
    dec = pathlib.Path(a.decomp).resolve()
    if not (dec / "src").is_dir():
        sys.exit(f"no encuentro el repo del decomp en {dec} (usá --decomp o BT2_DECOMP)")

    pf, df = set(files(PORT)), set(files(dec))
    differ, only_port, only_dec = [], sorted(pf - df), sorted(df - pf)
    for rel in sorted(pf & df):
        pt = (PORT / rel).read_text(errors="replace")
        dt = (dec / rel).read_text(errors="replace")
        if strip_port(pt) != dt:
            differ.append(rel)
            if a.diff:
                sys.stdout.writelines(difflib.unified_diff(dt.splitlines(True), strip_port(pt).splitlines(True),
                                                           f"decomp/{rel}", f"port/{rel} (sin PORT)"))

    if a.to_decomp:
        for rel in differ + only_port:
            print(("copio " if a.write else "copiaría ") + rel)
            if a.write:
                d = dec / rel; d.parent.mkdir(parents=True, exist_ok=True)
                d.write_text(strip_port((PORT / rel).read_text(errors="replace")))
    elif a.from_decomp:
        for rel in differ + only_dec:
            src = PORT / rel
            if src.exists() and has_port(src.read_text(errors="replace")):
                print(f"A MANO (tiene bloques PORT): {rel}"); continue
            print(("traigo " if a.write else "traería ") + rel)
            if a.write:
                src.parent.mkdir(parents=True, exist_ok=True)
                src.write_text((dec / rel).read_text(errors="replace"))

    print(f"distintos={len(differ)} solo_port={len(only_port)} solo_decomp={len(only_dec)}")
    for tag, lst in (("DIF", differ), ("PORT", only_port), ("DECOMP", only_dec)):
        for rel in lst[:50]:
            print(f"  {tag:6} {rel}")
        if len(lst) > 50:
            print(f"  ... y {len(lst) - 50} más")
    sys.exit(1 if a.check and (differ or only_port or only_dec) else 0)


if __name__ == "__main__":
    main()
