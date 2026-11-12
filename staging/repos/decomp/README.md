# BT2-Decompiled (borrador)

Decompilación a C de **Dragon Ball Z: Budokai Tenkaichi 2** (PS2, USA, SLUS-21441). Hermano de
[BT3-Decompiled]; mismo motor (Spike), misma organización.

**No incluye datos del juego.** Necesitás tu propia imagen del disco USA.

## Contenido
- `src/` C traducido (incluye `src/auto/`: salida automática aún sin limpiar — TODO decidir).
- `include/` cabeceras · `config/` yaml de splat y símbolos · `configure.py`, `game.toml`, `scripts/`.

## Requisitos
Linux, Python 3.11+, `7z`, binutils MIPS (`mips64-elf-ld`), ninja, splat (`pip install splat64[mips]`),
compiladores ee-gcc en `tools/` (no se distribuyen aquí; TODO: script de descarga).

## Compilar
```
cp /ruta/a/tu/BT2.iso "DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).iso"
python3 configure.py      # extrae el ELF, verifica SHA1 (config/SLUS_214.41.yaml) y hace el split
ninja
```

## Estado
TODO: % de funciones en C / matching (scripts/progress.py).

## Licencia
CC0 1.0 (ver LICENSE). El juego es propiedad de sus dueños.
