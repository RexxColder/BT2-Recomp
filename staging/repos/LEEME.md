# staging/repos — qué hay y qué falta decidir

Nada publicado ni inicializado (sin git init). Solo borradores.

- `decomp/` .gitignore, MANIFEST.txt, README.md, LICENSE (CC0)
- `port/` .gitignore, MANIFEST.txt, README.md, LICENSE (MIT propuesta), install.py, scripts/sync_decomp.py
- `make_manifest.py` regenera los manifiestos (solo lectura): `python3 staging/repos/make_manifest.py decomp|port`

## Falta decidir
1. **PS2Recomp (GPL)**: `port/tools/link_full.py` todavía depende de `port/build/recomp/*.cpp`, `port/full/recomp_shim*`
   y g++ (relleno, 633 funciones). Hasta la fase 1 de PLAN_PUBLICACION, el port NO puede ser MIT. Opciones: esperar,
   o publicar GPL temporalmente.
2. `link_full.py` lee `build_port/bt3_names.csv` (excluido): generarlo en el build o subirlo a `config/`.
3. `src/auto/` (2889 archivos, salida automática): ¿suben marcados o se limpian antes?
4. `config/xmatch_bt3*`, `c_files.v2/v3.txt`, `scripts/dev/` y scripts de trabajo (agents, bisect, sweep): excluidos en el
   manifiesto; revisar una por una. `scripts/` entra entero en decomp: filtrar.
5. `port/funcmap.csv` generado con el analizador de PS2Recomp: regenerar con herramienta propia o declararlo dato derivado.
6. `gen_native.py` llama a `clang` fijo: hacer que respete `$CC` (install.py ya exporta CC).
7. Toolchain MIPS (`tools/`, ee-gcc, binutils) y `game.toml` con `/usr/bin/mips64-elf-ld` absoluto: script de descarga
   y quitar la ruta absoluta.
8. ¿El runtime sigue leyendo la ISO (`gamedata.iso`) o se extrae `gamedata/`? install.py crea un symlink local por ahora.
9. Versión exacta de splat (install.py pone 0.50.0 como en BT3; confirmar).
10. Docs: cuáles van a cada repo (manifiesto incluye una selección técnica; internas como RETOMAR/HANDOFF/MEMORIA fuera).
11. Barrer el C buscando blobs binarios copiados (fuentes, paletas, tablas) antes de publicar.
12. Logs TEMP / sondas / traza (`plat_trace.c`, `BT2_TRACE_BUILD`): quitar o dejar detrás de opción.
13. Nombre del repo del port (Tenkaichi2Decomp?) y licencia final.
