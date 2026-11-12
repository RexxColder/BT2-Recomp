#!/usr/bin/env python3
"""Instalador de datos de BT2-Recomp (fase 1, sin dependencias).

Lee tu propia imagen de disco (ISO9660, sin montar ni 7z), verifica que sea la edición USA
(SLUS_214.41) y copia a `gamedata/` sólo lo que el port necesita (~2,98 GB):

    python3 setup/install.py --iso "/ruta/Dragon Ball Z - Budokai Tenkaichi 2 (USA).iso"
    python3 setup/install.py --iso ... --dest /otra/carpeta
    python3 setup/install.py --iso ... --eu-iso "/ruta/... (Europe).iso"   # multiidioma (F8)
    python3 setup/install.py --iso ... --check                            # sólo revisa
    python3 setup/install.py --iso ... --list                             # lista el disco

El repo no trae datos del juego: cada uno aporta su ISO. El instalador no toca el ISO y no
necesita root. Si ya hay archivos iguales en `gamedata/`, los saltea (se puede retomar).

El marcador `gamedata/.installed` se escribe al final; borralo (o usá --force) para reinstalar.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import shutil
import struct
import sys
import time
from pathlib import Path

SECTOR = 2048
ROOT = Path(__file__).resolve().parent.parent
ELF_NAME = "SLUS_214.41"
ELF_SHA1 = "cf01d5b2023843eecf7cf8ccda8bcd102dd61db7"  # SLUS_214.41 de la edición USA sin modificar
REQUIRED = [
    "SLUS_214.41",
    "SYSTEM.CNF",
    "BIN/DBZP.BIN",
    "DATA/ZS2US_1.AFS",
    "DATA/ZS2US_2.AFS",
    "DATA/ZS2US.DIR",
    "DATA/LOGO_O.SFD",
    "DATA/ZS2USOP.SFD",
    "DATA/ZS2USED.SFD",
]
# Carpetas completas que el port puede abrir (IRX hoy son stubs, pero se copian por fidelidad).
TREES = ("BIN/", "DATA/", "IRX/")
EU_AFS = "DATA/ZS2EU_1.AFS"


class IsoError(Exception):
    pass


class IsoFile:
    __slots__ = ("path", "extents", "size", "open_multi")

    def __init__(self, path: str, extents: list[tuple[int, int]]):
        self.path = path
        self.extents = extents
        self.size = sum(n for _, n in extents)
        self.open_multi = False


class Iso:
    """Lector ISO9660 mínimo: PVD en el sector 16, directorios con records, multi-extent."""

    def __init__(self, path: Path):
        self.path = path
        try:
            self.f = open(path, "rb")
        except OSError as e:
            raise IsoError(f"no se puede abrir {path}: {e.strerror}")
        self.size = os.fstat(self.f.fileno()).st_size
        self.files: dict[str, IsoFile] = {}
        pvd = self._read(16 * SECTOR, SECTOR)
        if len(pvd) < SECTOR or pvd[0] != 1 or pvd[1:6] != b"CD001":
            raise IsoError("este archivo no es una imagen de disco ISO9660 (.iso). "
                           "Los formatos comprimidos (.chd, .cso, .gz) hay que convertirlos a .iso primero.")
        root = pvd[156:190]
        extent = struct.unpack_from("<I", root, 2)[0]
        length = struct.unpack_from("<I", root, 10)[0]
        if extent * SECTOR >= self.size or length == 0:
            raise IsoError("el ISO tiene un directorio raíz inválido (imagen dañada).")
        self._walk(extent * SECTOR, length, "", 0)

    def _read(self, off: int, n: int) -> bytes:
        self.f.seek(off)
        return self.f.read(n)

    def _walk(self, off: int, length: int, prefix: str, depth: int) -> None:
        if depth > 8:
            return
        data = self._read(off, length)
        pos = 0
        pending: dict[str, IsoFile] = {}
        while pos < len(data):
            ln = data[pos]
            if ln == 0:  # los records no cruzan de sector: saltar al siguiente
                pos = (pos // SECTOR + 1) * SECTOR
                continue
            if pos + ln > len(data) or ln < 34:
                break
            rec = data[pos:pos + ln]
            ext = struct.unpack_from("<I", rec, 2)[0]
            size = struct.unpack_from("<I", rec, 10)[0]
            flags = rec[25]
            nlen = rec[32]
            raw = rec[33:33 + nlen]
            pos += ln
            if nlen == 1 and raw in (b"\x00", b"\x01"):
                continue
            name = raw.decode("latin-1").split(";", 1)[0].rstrip(".")
            if not name:
                continue
            path = f"{prefix}{name}"
            if flags & 2:  # directorio
                self._walk(ext * SECTOR, size, path + "/", depth + 1)
                continue
            ent = IsoFile(path, [(ext * SECTOR, size)])
            prev = pending.get(path)
            if prev is not None and prev.open_multi:  # multi-extent: el record anterior no era el final
                prev.extents.extend(ent.extents)
                prev.size += size
                prev.open_multi = bool(flags & 0x80)
            else:
                ent.open_multi = bool(flags & 0x80)
                pending[path] = ent
                self.files[path] = ent

    def find(self, wanted: str) -> IsoFile | None:
        key = wanted.upper().rstrip("/")
        for path, f in self.files.items():
            if path.upper() == key:
                return f
        return None

    def find_prefix(self, prefix: str) -> list[IsoFile]:
        key = prefix.upper()
        return [f for p, f in self.files.items() if p.upper().startswith(key)]

    def copy_out(self, f: IsoFile, dest: Path, progress=None) -> int:
        dest.parent.mkdir(parents=True, exist_ok=True)
        tmp = dest.with_name(dest.name + ".part")
        written = 0
        try:
            with open(tmp, "wb") as out:
                for off, n in f.extents:
                    self.f.seek(off)
                    left = n
                    while left:
                        buf = self.f.read(min(left, 4 << 20))
                        if not buf:
                            raise IsoError(f"fin de archivo inesperado copiando {f.path}")
                        out.write(buf)
                        left -= len(buf)
                        written += len(buf)
                        if progress:
                            progress(written)
        except OSError as e:
            tmp.unlink(missing_ok=True)
            raise IsoError(f"no se puede escribir {dest}: {e.strerror}. ¿Disco lleno o carpeta de sólo lectura?")
        os.replace(tmp, dest)
        return written


def sha1(path: Path) -> str:
    h = hashlib.sha1()
    with open(path, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def human(n: float) -> str:
    for unit in ("B", "KB", "MB", "GB"):
        if n < 1024 or unit == "GB":
            return f"{n:.1f} {unit}" if unit != "B" else f"{int(n)} B"
        n /= 1024
    return f"{n:.1f} GB"


def wanted_files(iso: Iso, dest: Path) -> list[IsoFile]:
    out = []
    for f in iso.files.values():
        p = f.path.upper()
        if p == ELF_NAME or p == "SYSTEM.CNF" or p.startswith(TREES):
            out.append(f)
    out.sort(key=lambda f: f.path)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description="Instala los datos de BT2-Recomp desde tu ISO (edición USA).")
    ap.add_argument("--iso", type=Path, help="imagen de disco (ISO9660) de la edición USA")
    ap.add_argument("--dest", type=Path, default=ROOT / "gamedata", help="carpeta destino (default: gamedata/)")
    ap.add_argument("--eu-iso", type=Path, help="ISO PAL opcional: copia DATA/ZS2EU_1.AFS para el multiidioma")
    ap.add_argument("--check", action="store_true", help="sólo revisa la ISO y el espacio; no copia")
    ap.add_argument("--list", action="store_true", help="lista el contenido de la ISO y sale")
    ap.add_argument("--force", action="store_true", help="vuelve a copiar todo (ignora archivos ya presentes)")
    a = ap.parse_args()

    if not a.iso:
        ap.error("falta --iso (tu propia imagen del juego)")
    if not a.iso.is_file():
        print(f"error: no existe {a.iso}", file=sys.stderr)
        return 1
    try:
        iso = Iso(a.iso)
    except IsoError as e:
        print(f"error: {e}", file=sys.stderr)
        return 1

    if a.list:
        for f in sorted(iso.files.values(), key=lambda x: x.path):
            print(f"{f.size:>12}  {f.path}")
        print(f"\n{len(iso.files)} archivos, {human(sum(f.size for f in iso.files.values()))}")
        return 0

    elf = iso.find(ELF_NAME)
    if elf is None:
        other = iso.find_prefix("SLES_")
        hint = f" (esta ISO parece la PAL: {other[0].path})" if other else ""
        print("error: esta no es la edición USA de Budokai Tenkaichi 2: no hay SLUS_214.41 en el disco"
              f"{hint}.\n       El port está hecho sobre la edición USA (SLUS-21441). Otras regiones no sirven "
              "para arrancar.", file=sys.stderr)
        return 1

    files = wanted_files(iso, a.dest)
    have = {f.path.upper() for f in files}
    missing = [p for p in REQUIRED if p not in have]
    if missing:
        print("error: a la ISO le faltan archivos que el port necesita:\n  " + "\n  ".join(missing), file=sys.stderr)
        return 1

    total = sum(f.size for f in files)
    if a.eu_iso:
        if not a.eu_iso.is_file():
            print(f"error: no existe {a.eu_iso}", file=sys.stderr)
            return 1
        eu = Iso(a.eu_iso)
        if eu.find(EU_AFS) is None:
            print(f"error: {a.eu_iso} no tiene {EU_AFS}; ¿es el disco PAL correcto?", file=sys.stderr)
            return 1
        total += eu.find(EU_AFS).size

    free = shutil.disk_usage(a.dest.parent if a.dest.parent.exists() else ROOT).free
    print(f"ISO: {a.iso.name} ({human(iso.size)})")
    print(f"Destino: {a.dest}  ·  a copiar: {human(total)}  ·  libre: {human(free)}")
    if free < total + (64 << 20):
        print("error: no hay espacio suficiente en el destino (hacen falta ~" + human(total) + ").", file=sys.stderr)
        return 1
    if a.check:
        print("ok: la ISO es la edición USA y hay espacio. Nada copiado (--check).")
        return 0

    a.dest.mkdir(parents=True, exist_ok=True)
    t0 = time.time()
    done_bytes = 0
    copied = skipped = 0
    elf = next(f for f in files if f.path == ELF_NAME)
    ordered = [elf] + [f for f in files if f.path != ELF_NAME]  # el programa primero: falla barato si no es el USA
    for i, f in enumerate(ordered, 1):
        dst = a.dest / f.path
        if not a.force and dst.is_file() and dst.stat().st_size == f.size:
            skipped += 1
            done_bytes += f.size
            print(f"[{i:>3}/{len(ordered)}] ya está: {f.path}")
        else:
            print(f"[{i:>3}/{len(ordered)}] {f.path} ({human(f.size)})", flush=True)
            iso.copy_out(f, dst)
            copied += 1
            done_bytes += f.size
        if f.path == ELF_NAME:
            print("verificando el programa (SHA-1) ...", flush=True)
            got = sha1(dst)
            if got != ELF_SHA1:
                print(f"error: el {ELF_NAME} extraído no es el de la edición USA sin modificar\n"
                      f"       esperado {ELF_SHA1}\n       obtenido {got}\n"
                      "       El port se construyó sobre la edición USA original; una imagen parcheada o dañada no sirve.",
                      file=sys.stderr)
                return 3
    if a.eu_iso:
        eu = Iso(a.eu_iso)
        dst = a.dest / EU_AFS
        f = eu.find(EU_AFS)
        if not (not a.force and dst.is_file() and dst.stat().st_size == f.size):
            print(f"[eu ] {EU_AFS} ({human(f.size)})", flush=True)
            eu.copy_out(f, dst)
            copied += 1
        else:
            skipped += 1
        done_bytes += f.size

    marker = {
        "version": 1,
        "elf_sha1": got,
        "eu_afs": bool(a.eu_iso),
        "files": copied + skipped,
        "bytes": done_bytes,
        "installed_at": time.strftime("%Y-%m-%dT%H:%M:%S"),
    }
    (a.dest / ".installed").write_text(json.dumps(marker, indent=2) + "\n")
    print(f"listo en {time.time() - t0:.1f} s: {copied} copiados, {skipped} ya estaban, "
          f"{human(done_bytes)} en {a.dest}")
    print("Ahora: ./port/build/full/bt2full   (Windows/macOS todavía no soportados)")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except IsoError as e:
        print(f"error: {e}", file=sys.stderr)
        sys.exit(1)
    except KeyboardInterrupt:
        print("\ncancelado.", file=sys.stderr)
        sys.exit(130)
