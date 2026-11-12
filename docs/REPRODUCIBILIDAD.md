# Reproducibilidad: BT2 y los otros proyectos de PS2 del equipo (relevado 2026-10-13)

Sólo documentación: no se cambió nada en los otros proyectos. Objetivo: que este trabajo se pueda repetir en otra
máquina (o con otro juego) y que una herramienta futura (`ps2-decomp-kit`) lo automatice.

## 1. Mapa de proyectos

| Proyecto | Ruta | Qué es | Estado / relación con BT2 |
|---|---|---|---|
| BT3-Decompiled | `~/Proyectos/BT3-Decompiled` (origin `github.com/z3xox/BT3-Decompiled`, `8cd96d6`) | Decomp matching de BT3 (~99 %), splat + ee-gcc 2.96 | **Fuente** de nombres/C/tipos para BT2 (mismo motor); su `build/SLUS_216.78.elf` y `build/DBZP.elf` los usa `scripts/bt3_names*.py` |
| Tenkaichi3Decomp | `~/Proyectos/Tenkaichi3Decomp` (fork `github.com/RexxColder/Tenkaichi3Decomp`, `6ae9ef3`); release en `~/Escritorio/Tenkaichi3Decomp` | Port nativo de BT3 sin runtime | **Modelo** de la etapa final de BT2: `port/src/plat_*`, `gs/` (GS+VIF1+VU1 interpretado), `ptr32.py`, `irfix.py`, `check_protos.py`, `link.py` |
| ps2-decomp-kit | `~/Proyectos/ps2-decomp-kit` (`37d0274`) | Kit general: scripts del decomp, toolchains, serie de parches de PS2Recomp, `docs/METHOD.md`, `docs/PORT_METHOD.md` | BT2 nació con él (`new_project.py`); BT2 lo usa por enlaces (`tools/binutils`, `tools/ee-gcc*`) |
| DownhillJam-Decompiled | `~/Proyectos/DownhillJam-Decompiled` (`97d5cff`) | Decomp matching (SN ProDG 2.95.3-136) + port con PS2Recomp | Segundo juego del kit; de ahí salieron los parches 0001–0009 de PS2Recomp |
| Outbreak-Decompiled | `~/Proyectos/Outbreak-Decompiled` (`da0eb74`) | Intento anterior sin terminar (según el usuario) | Aportó ideas a `fdiff.py` del kit |
| BT2-Recomp (viejo) | `~/Proyectos/BT2-Recomp` | Archivo viejo, **no tocar** | ¡Ver §4: la copia maestra todavía depende de él! |
| **BT2-Recomp (maestro)** | `~/Escritorio/BT2-Recomp` (git sin commits) | Este proyecto | — |
| BT2 en limpio | `~/Escritorio/Nueva carpeta/BT2-Port` | Copia ordenada (2026-10-12) | Snapshot, no se regenera solo |

## 2. Herramientas de la máquina (versiones usadas)

| Herramienta | Versión | Para qué |
|---|---|---|
| Arch Linux, kernel | 7.2.9-arch1-1 | — |
| Python | 3.14.8 (`.venv` del repo con splat64 0.50.0, m2c 0.1.0, spimdisasm 1.42.4, rabbitizer 1.16.2) | splat, m2c, scripts |
| clang / llvm (llc) | 23.1.1 (paquetes `clang`, `llvm`); bindings `clang.cindex` (libclang) | C nativo x86-64, `ptr32.py`, `irfix.py` |
| mips64-elf-binutils | 2.47-1 | linker del matching (`game.toml [toolchain] linker`) |
| binutils PS2 decompals | `~/Proyectos/ps2-decomp-kit/toolchain/binutils` | as/objdump/readelf de `fdiff.py` |
| ee-gcc | `ps2-decomp-kit/toolchain/ee-gcc2.96` (+ 2.9x/2.95.x/3.2, mwcps2) vía `wine` 11.19 | compilador del juego (BT2 = ee-gcc 2.96, `-O2 -G8`; `src/cri`, `src/menu` con `-G0`) |
| ninja, cmake, gdb, 7z | sistema | build y depuración |
| SDL3 | 3.4.18 | ventana/mando (raylib 5.5 sobre SDL3: `third_party/PS2Recomp/ps2xRuntime/cmake/raylib_sdl3.cmake` + `raylib_sdl3_gamepad.patch`) |
| PCSX2 con PINE + DebugServer | `/mnt/datos/Herramientas/pcsx2-src` (`99f5d76`), binario `build/bin/pcsx2-qt` | oráculo: `fn_diff.py`, MCP `pcsx2` |
| PS2Recomp | `third_party/PS2Recomp` rama `bt2`, base `ran-j/PS2Recomp 2c5fbb9` | build híbrido (temporal) |

## 3. Serie de parches de PS2Recomp: kit ↔ BT2

- `ps2-decomp-kit/third_party/patches/ps2recomp-0001..0009-*.patch` y `BT2-Port/runtime-patches/0001..0009-*.patch`
  tienen **el mismo contenido** (comparadas las líneas +/-, 0 diferencias; sólo cambian nombre de archivo y cabeceras).
- Lo de BT2 que el kit no tiene: `0010-bt2-wip-uncommitted.diff` (= `git diff` de `third_party/PS2Recomp` sobre la
  rama `bt2`: hoy 40 archivos, +1041/−152): VU0 vclip / vsqi/vsqd/vlqi/vlqd/vilwr/viswr, sombra de 64 KB
  (`ps2_identity.h`), overlay en el funcmap, raylib sobre SDL3, `PS2X_FULLSCREEN`, `PS2X_COVERAGE` (2026-10-13),
  guard de `reportMissingFunction`. Pendiente: convertirlo en parches numerados 0010+ como pide el método del kit
  (`git am` de la serie en un worktree limpio + `git format-patch`).
- El kit tiene en curso un 0010 propio de Downhill Jam (`_sceSifSendCmd`, MFC0 Count): numeración a reconciliar.

## 4. Dependencias frágiles encontradas (no corregidas: anotadas)

1. **`~/Escritorio/BT2-Recomp/gamedata` → `/home/rexx/Proyectos/BT2-Recomp/gamedata`** y
   **`tools/bin` → `/home/rexx/Proyectos/BT2-Recomp/tools/bin`** (vacío). La copia maestra lee los datos del juego
   desde el archivo viejo. Para reproducir: extraer el ISO a `gamedata/` del repo maestro (`7z x gamedata.iso`),
   reemplazar los enlaces y borrar `tools/bin`. Hashes de control: `SLUS_214.41` sha1
   `cf01d5b2023843eecf7cf8ccda8bcd102dd61db7`, `BIN/DBZP.BIN` sha1 `0463612b526e6e90a48636bb419720e212515ed1`.
2. `gamedata.iso` → ISO en `/mnt/datos/Rexx/Descargas/Roms/PS2/BT2/` (disco del usuario; correcto que no esté en git).
3. `tools/binutils` y `tools/ee-gcc*` → `~/Proyectos/ps2-decomp-kit/toolchain/` (bien, pero el kit tiene que existir).
4. Scripts con rutas absolutas: `scripts/bt3_names.py`, `bt3_names_ovl.py`, `xmatch.py`, `m2c_context.py` (BT3-Decompiled
   y `~/Escritorio/BT2-Recomp`); `docs/agents/*` asumen `~/Escritorio/BT2-Recomp` y `~/Escritorio/BT2-overlay-work`.
5. **El overlay vive en otro repo**: `~/Escritorio/BT2-overlay-work` (splat de `DBZP.BIN`, `asm/dbzp`, borradores,
   `fdiff.py` con soporte del overlay). Su `eq/` es un enlace a `port/eq/` del maestro. Falta integrarlo al maestro
   (`docs/OVERLAY_DECOMP.md` de ese repo lista los cambios a portar).
6. El repo maestro no tiene commits: no hay historia reproducible. El registro real es `docs/PORT_LOG.md`.
7. Generados que no se regeneran de forma trivial: `scratch/m2c_sweep/` (borradores + `.s` por función, `status.csv`),
   `scratch/protos/ctx.h` (`scripts/infer_protos.py`), `build_port/bt3_names*.csv`, `build_port/coverage/`.

## 5. Scripts: kit ↔ BT2 (`scripts/`)

- Iguales: `apply_names, cc_probe, elf_survey, leaf_sweep, names_from_strings, order_ld, permute, progress, set_eabi64,
  strip_func_pad, vtables, vuasm`.
- Divergen (BT2 los mejoró; volcar al kit, ver `docs/TOOL_BACKLOG.md` B01/B02): `fdiff.py` (+ borrar el objeto viejo
  antes de compilar: 2026-10-13), `funcmap.py`, `gamecfg.py` (clave linker), `gen_undefined.py`, `gen_yaml.py`, `recomp.py`, `sdk_names.py`.
- Sólo en BT2 (candidatos al kit, etapa "C equivalente + port sin runtime"):
  `infer_protos.py`, `m2c_sweep.py`/`m2c_fixsp.py`, `port_inplace.py` + `fn_diff.py` (verificación en PCSX2),
  `callgraph.py`, `native_triage.py`, `bt3_names.py` (cruce por bytes enmascarados con un juego hermano),
  `port/tools/gen_native.py` (híbrido), `port/tools/build_full.py` + `link_full.py` + `port/full/*` (ejecutable 100 %
  nativo: identidad de memoria, `jmp` por función, stubs), `release/make_test_build.sh`.

## 6. Receta (orden) para repetir BT2 o hacer otro juego del mismo tipo

1. Máquina: paquetes de §2; `ps2-decomp-kit` con `toolchain/`; PCSX2 con PINE/DebugServer.
2. Proyecto: `ps2-decomp-kit/kit/new_project.py` → `game.toml`, yaml de splat, `.venv`; extraer ISO a `gamedata/`.
3. Matching (kit `docs/METHOD.md`): bootstrap byte-idéntico, compilador por `cc_probe.py`, nombres
   (de un juego hermano: `bt3_names.py`), barrido m2c, agentes.
4. Overlays: un yaml de splat por overlay (ver `BT2-overlay-work`), función por función en el funcmap.
5. Prototipos: `scripts/infer_protos.py`.
6. C equivalente de lo que no matchea: agentes con `docs/agents/EQ_PROMPT.md` (instructivo único y compacto,
   reglas aprendidas: cvt.w.s trunca, pass-through de a0–a3, sin asm en línea, VU0 sobre `gVu0`...), cola ordenada
   por cobertura (`PS2X_COVERAGE` en el híbrido).
7. Port: `build_full.py` (clang + `ptr32.py` + `irfix.py`) → `link_full.py` → capa `port/full/plat_*` adaptada de
   Tenkaichi3Decomp → renderer `gs/` de Tenkaichi3Decomp → sonido/video.
8. Verificación: `fn_diff.py` en PCSX2 por función; comparación de RAM por frame; replay de pelea.
9. Mientras falte C: relleno temporal con el código de PS2Recomp (`docs/agents/FALLBACK_SPEC.md`), apagable y medido.

## 7. Pendiente para que sea 100 % reproducible
- Romper la dependencia de `~/Proyectos/BT2-Recomp` (§4.1).
- Integrar `BT2-overlay-work` en el maestro.
- Primer commit del maestro (cuando el usuario lo pida) y `0010` partido en parches numerados.
- Volcar al kit los scripts de §5 y este documento como `PORT_METHOD` etapa 3 ("C equivalente + sin runtime").
- Script `make_env.sh` que verifique versiones de §2 y hashes de §4.1.

## 8. Más material en `/mnt/datos/Proyectos` (relevado 2026-10-13, sólo lectura)

| Ruta | Qué es | Utilidad para BT2 / la herramienta futura |
|---|---|---|
| `ps2-tool/` (+ `ps2-tool.tar.gz`) | CLI C++ propia: parser ELF, Ghidra headless con el plugin Emotion Engine (`plugins/ghidra-emotionengine-reloaded.zip`, `ghidra_scripts/*.java`), **emparejamiento de SDK por SHA-1** contra `sce_flat.txt` (9217 firmas `sha1\|lib\|func\|size`), export de funcmap/TOML para PS2Recomp | La base de firmas SCE sirve para nombrar el SDK de BT2 (0x300000–0x33B5F8) sin depender de BT3; `scripts/sdk_names.py` hace algo parecido |
| `analisis/<juego>/` (Biohazard Outbreak 1 y File 2, Sims 2 Castaway, Sonic Riders ZG, Downhill Jam) | Por juego: `functions.csv` (funcmap estilo PS2Recomp, 4,8 k–17,7 k funciones), `config.toml` de PS2Recomp con stubs SDK, base `.db` de Ghidra/IDA, `*_KNOWLEDGE_BASE.md`, y `deep_analisis_results/` (RUNTIME_ANALYSIS, SYSCALL_MAP, THREADING_MODEL, MEMORY_MAP, RENDERING_PIPELINE, strings/xrefs CSV) | Plantilla de "análisis previo" de un juego nuevo: lo mismo que BT2 sacó a mano (funcmap, stubs, modelo de hilos) generado de forma uniforme |
| `Play-Debug/` (`source.tar.gz`, `COMPARISON_REPORT.md`) | Fork instrumentado del emulador Play! que registra syscalls, SIF RPC, DMA, escrituras GS, cambios de contexto, snapshots por VBlank y **funciones únicas llamadas** (8107 en 30 s de Sonic Riders) | Otra fuente de **cobertura** (qué funciones corre el juego) independiente de PS2Recomp; BT2 hoy usa `PS2X_COVERAGE` del híbrido |
| `ghpc/` | Port de Guitar Hero 1/2/80s con PS2Recomp: **fork** de ran-j/PS2Recomp (se mergea upstream, nunca rebase), C++ traducido reemplazado función a función por fuente (`ghpc/override/<Name>_0x<addr>.cpp`), `stub-denylist.txt`, `build.sh --from/--to`, `checkrun.sh` (verifica que el arranque sigue progresando), medición de techo (`GHPC_VU1_OFF=1`: el EE traducido va a 100 %, el costo es todo VU1) y plan de renderer nativo Vulkan "en la costura `Rnd`" | Mismo enfoque que el relleno temporal de BT2 (opción 2) y misma conclusión de rendimiento que Downhill Jam/BT3: VU1 interpretado es el cuello; el renderer nativo lo elimina. `checkrun.sh` = idea para una prueba de regresión del arranque de bt2full |
| `x360tool/`, `rexglue-sdk-*.tar.gz`, `EMULATED_VS_NATIVE_RENDERING.md`, `NATIVE_RENDERING_*.md` | Herramientas y guías de Xbox 360 (skate3recomp: renderer nativo D3D12/Vulkan sobre rexglue) | Guía de cómo pasar de render emulado a nativo (fases, costuras); aplicable conceptualmente a la etapa 5 |
| `play_source_indirect_jump_capture.zip` | Variante de Play! que captura saltos indirectos | Para encontrar funciones alcanzadas sólo por puntero (BT2 lo resolvió con funcmap + overlay) |

Conclusiones para reproducibilidad:
- Hay **tres** generadores de funcmap en el equipo (splat/`funcmap.py` del kit, `ps2-tool` vía Ghidra, IDA en `analisis/`) y
  dos fuentes de cobertura (`PS2X_COVERAGE`, Play-Debug). La herramienta futura debería elegir uno por defecto y
  poder comparar con los otros.
- `ghpc` confirma el patrón "recompilado como andamio, reemplazado por fuente sin que el build deje de correr";
  su regla de mantener PS2Recomp como fork mergeable (no rebase) conviene adoptarla para `third_party/PS2Recomp`
  de BT2 y del kit (hoy: rama `bt2` + diff sin commitear).

## 9. IDA Pro + Hex-Rays (descubierto 2026-10-13)
- `/mnt/datos/Herramientas/IDA Pro/` tiene `idat` (modo texto) y `plugins/hexmips.so` (decompilador MIPS). Ya se usó
  en agosto para BT3 y su overlay (`decompile_all.py`, `decompile_dbzp*.py` en esa carpeta; salida en una ruta
  `/mnt/Datos/...` que ya no existe). Las bases `analisis/*/<juego>.db` (SQLite: tablas `functions`, `decompiled`,
  `strings`, `xrefs`, `segments`, `analysis_docs`) traen el pseudocódigo Hex-Rays del 100 % de las funciones de cada juego.
- Para BT2: `scratch/hexrays/decompile_bt2.py` (límites de función desde `port/funcmap.csv`, salida JSON
  dirección→pseudocódigo). Uso: `idat -A -S"decompile_bt2.py <funcmap.csv> <out.json>" <elf> -L<log>`.
- Bloqueo al probarlo (2026-10-13), requiere al usuario una vez: **aceptar la licencia de IDA** (abrir IDA con interfaz
  una vez) y **`idapyswitch`** para elegir el Python 3 del sistema (`Python3TargetDLL` sin configurar).
