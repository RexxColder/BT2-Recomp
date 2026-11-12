# Tenkaichi2 — port a PC (borrador)

Port nativo a PC de **Dragon Ball Z: Budokai Tenkaichi 2** (PS2, USA, SLUS-21441): el C de la decompilación
compilado a x86-64 con un runtime propio (renderer OpenGL del GS, sonido, tarjeta de memoria, entrada).

**No incluye datos del juego.** Se usa tu propia imagen del disco USA, que queda en tu máquina.

## Requisitos
Linux x86-64 (probado en Arch), `clang`/`llc` (LLVM 17+; probado con clang 23), Python 3.11+, `7z`,
binutils MIPS, SDL2/OpenGL. Mientras exista el relleno temporal: `g++`.

## Compilar (un comando)
```
python3 install.py --iso /ruta/a/tu/BT2.iso
./play.sh
```
`install.py` verifica la ISO por SHA1, extrae el ejecutable, corre splat, genera shaders y llama a
`port/tools/build_full.py` y `port/tools/link_full.py`. Se puede elegir compilador con `CC=...`.

## Relación con BT2-Decompiled
`src/` e `include/` son una copia del repo de la decompilación; los cambios de PC van en `#ifdef PORT`.
`python3 scripts/sync_decomp.py --decomp ../BT2-Decompiled --check` informa diferencias.

## Estado
Jugable en menús y peleas. TODO: completar con lo que se pruebe en todos los modos.

## Bugs conocidos
Ver `docs/bugs_open.md` (TODO: resumir los abiertos: niebla B25, zeni B24, Kamehameha B14, clase 6/11).

## Licencia
MIT (ver LICENSE) — **condicionado** a quitar el uso de PS2Recomp (GPL) en el enlace. Hasta entonces, un build
que incluya código de PS2Recomp no puede distribuirse como MIT.
