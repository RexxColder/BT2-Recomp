#!/usr/bin/env python3
"""Genera una ISO9660 sintética para probar el instalador sin usar una ISO real.

Uso:
  python3 setup/tests/make_test_iso.py salida.iso /ruta/SLUS_214.41 /ruta/BIN/DBZP.BIN [--bad-elf]

La ISO de prueba contiene los archivos requeridos por el instalador; los AFS/SFD son rellenos chicos y el
ELF/DBZP se copian de la copia local del usuario. NO se commitea: los datos del juego no van al repo.
Sirve para verificar el rechazo por SHA-1 (--bad-elf), el progreso, el marcador y la GUI en segundos.
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

SECTOR = 2048
DATE = bytes([126, 1, 1, 0, 0, 0, 0])  # 2026-01-01


def both16(v: int) -> bytes:
    return struct.pack("<H", v) + struct.pack(">H", v)


def both32(v: int) -> bytes:
    return struct.pack("<I", v) + struct.pack(">I", v)


def record(name: bytes, extent: int, size: int, flags: int = 0) -> bytes:
    n = len(name)
    length = 33 + n
    if length % 2:
        length += 1
    b = bytearray(length)
    b[0] = length
    b[1] = 0
    b[2:6] = struct.pack("<I", extent)
    b[6:10] = struct.pack(">I", extent)
    b[10:14] = struct.pack("<I", size)
    b[14:18] = struct.pack(">I", size)
    b[18:25] = DATE
    b[25] = flags
    b[26] = 0
    b[27] = 0
    b[28:30] = struct.pack("<H", 1)
    b[30:32] = struct.pack(">H", 1)
    b[32] = n
    b[33:33 + n] = name
    return bytes(b)


def dir_block(entries: list[bytes]) -> bytes:
    out = bytearray(SECTOR)
    pos = 0
    for e in entries:
        if pos + len(e) > SECTOR:
            raise SystemExit("directorio de prueba demasiado grande")
        out[pos:pos + len(e)] = e
        pos += len(e)
    return bytes(out)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("out", type=Path)
    ap.add_argument("elf", type=Path)
    ap.add_argument("dbzp", type=Path)
    ap.add_argument("--bad-elf", action="store_true", help="cambia un byte del ELF para probar el rechazo por SHA-1")
    a = ap.parse_args()

    elf = bytearray(a.elf.read_bytes())
    if a.bad_elf:
        elf[len(elf) // 2] ^= 0xFF
    dbzp = a.dbzp.read_bytes()
    files: dict[str, bytes] = {
        "SLUS_214.41": bytes(elf),
        "SYSTEM.CNF": b"BOOT2 = cdrom0:\\SLUS_214.41;1\nVER = 1.00\n",
        "BIN/DBZP.BIN": dbzp,
        "DATA/ZS2US_1.AFS": b"AFS\0" + struct.pack("<I", 0) + bytes(4096),
        "DATA/ZS2US_2.AFS": b"AFS\0" + struct.pack("<I", 0) + bytes(8192),
        "DATA/ZS2US.DIR": bytes(64),
        "DATA/ZS2US_1.ALG": bytes(26),
        "DATA/ZS2US_2.ALG": bytes(26),
        "DATA/LOGO_O.SFD": bytes(1000),
        "DATA/ZS2USOP.SFD": bytes(2000),
        "DATA/ZS2USED.SFD": bytes(3000),
        "IRX/TEST.IRX": bytes(128),
    }
    dirs = ["", "BIN", "DATA", "IRX"]
    dir_sector = {name: 18 + i for i, name in enumerate(dirs)}
    next_sector = 18 + len(dirs)
    extents: dict[str, tuple[int, int]] = {}
    for name, data in files.items():
        sectors = (len(data) + SECTOR - 1) // SECTOR
        extents[name] = (next_sector, len(data))
        next_sector += sectors
    total_sectors = next_sector

    def entries_for(dirname: str) -> list[bytes]:
        paths = [p for p in files if (p.rsplit("/", 1)[0] if "/" in p else "") == dirname]
        names = [p.rsplit("/", 1)[-1] for p in paths]
        out = [record(b"\x00", dir_sector[dirname], SECTOR, 2), record(b"\x01", dir_sector[dirname], SECTOR, 2)]
        for sub in dirs:
            parent = sub.rsplit("/", 1)[0] if "/" in sub else ""
            if sub and parent == dirname and sub != dirname:
                out.append(record(sub.rsplit("/", 1)[-1].encode(), dir_sector[sub], SECTOR, 2))
        for name in sorted(names):
            key = f"{dirname}/{name}" if dirname else name
            ext, size = extents[key]
            out.append(record((name + ";1").encode(), ext, size))
        return out

    pvd = bytearray(SECTOR)
    pvd[0] = 1
    pvd[1:6] = b"CD001"
    pvd[6] = 1
    pvd[8:40] = b" " * 32
    pvd[40:72] = b"BT2TEST".ljust(32)
    pvd[80:88] = both32(total_sectors)
    pvd[120:124] = both16(1)
    pvd[124:128] = both16(1)
    pvd[128:132] = both16(SECTOR)
    pvd[132:140] = both32(10)
    pvd[156:190] = record(b"\x00", dir_sector[""], SECTOR, 2)
    pvd[881] = 1

    term = bytearray(SECTOR)
    term[0] = 255
    term[1:6] = b"CD001"
    term[6] = 1

    data = bytearray()
    data += bytes(16 * SECTOR)
    data += pvd
    data += term
    for d in dirs:
        block = dir_block(entries_for(d))
        data += block
    for name in files:
        blob = files[name]
        data += blob
        pad = (-len(blob)) % SECTOR
        data += bytes(pad)
    if len(data) != total_sectors * SECTOR:
        raise SystemExit(f"tamaño inconsistente: {len(data)} vs {total_sectors * SECTOR}")
    a.out.write_bytes(data)
    print(f"ISO de prueba: {a.out} ({len(data)} bytes, {len(files)} archivos)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
