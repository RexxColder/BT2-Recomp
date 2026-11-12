# Plan de publicación (BT2) — dos repos, modelo BT3

Fecha: 2026-11-06. Informe de solo lectura (no se tocó nada del árbol). Cifras sacadas de
`port/build/full/report.json`, `port/full/FALLBACK_AUTO.txt`, `docs/audit/fallback_used_fight.txt`, `du`, `grep`.

## 0. Modelo a imitar (BT3)

| Repo BT3 | Qué tiene | Licencia |
|---|---|---|
| `BT3-Decompiled` | `src/ include/ config/ configure.py scripts/ docs/` + `tools/` ignorado; `.gitignore` excluye `*.iso disc/ asm/ assets/ build/ tools/ .venv/ build.ninja` | CC0 |
| `Tenkaichi3Decomp` (port) | **copia** de `src/` e `include/` del decomp (cambios de PC dentro de `#ifdef PORT`), `port/`, `install.py` (asistente: requisitos → ISO verificada por SHA1 → extraer datos → splat del ELF → build → autoprueba), `play.sh`, README | MIT |

No usan submódulo: el port lleva una copia del C, y los arreglos se pasan a mano. Para BT2 se propone lo mismo
pero con un script de sincronización (ver 3.3).

## 1. Desconexión de PS2Recomp

### 1.1 Qué viene hoy de PS2Recomp
| Pieza | Dónde | Peso |
|---|---|---|
| Fuente del recompilador y runtime completo | `third_party/PS2Recomp/` (ps2xRecomp, ps2xRuntime, ps2xAnalyzer, ps2xStudio, IOP, tests; `out/` = 1,2 GB de build) | 1,3 GB, **GPL** |
| C++ generado por el recompilador (una función por archivo) | `port/build/recomp/*_0x*.cpp` | 11 701 archivos, 175 MB |
| Configuración del recompilador | `port/recomp.toml`, `port/recomp_extra.toml`, `port/sdk_stubs.toml` | 20 KB |
| Runtime mínimo propio que imita el de PS2Recomp | `port/full/recomp_shim/*.h` (`ps2_runtime.h`, `ps2_runtime_macros.h`, `ps2_stubs.h`, `ps2_syscalls.h`, …) + `port/full/recomp_shim.cpp` (301 líneas: bucle de despacho, adaptador de ABI, `bt2_fb_entry`) | código nuestro pero derivado de las cabeceras de PS2Recomp (revisar si hereda GPL) |
| Generación del relleno en el enlace | `port/tools/link_full.py`: `build_fallback()` (compila los .cpp con g++, genera `fallback_tbl.cpp`), `libc_addr` (mapea memset/strlen… por los nombres de los .cpp de PS2Recomp), `-DBT2_FALLBACK` | — |
| Listas regeneradas | `port/full/FALLBACK_AUTO.txt` (633), `TEMP_STUBS_AUTO.txt` (258), `TEMP_STUBS.txt` | — |

`src/` e `include/` **no** incluyen nada de PS2Recomp (grep de `ps2_runtime`/`recomp_shim`: 0). La dependencia
está toda en el enlace del port.

### 1.2 Números del último enlace
- **relleno = 633** funciones corren con C++ de PS2Recomp: **620 del SDK/libc** (0x300000–0x33B5F8) y **13 del
  overlay** (0x3D6728–0x3D6788, trampolines de 8 bytes). **0 del juego** (<0x2D0000; las 4 de 25FE30.. ya no se ejecutan).
- `relleno_reenviadores = 33`: adaptadores generados para saltos de cola C++→C nativo (desaparecen solos).
- `relleno_fallo_compilar = 9`: .cpp que g++ no compila; hoy caen a stub.
- `sin_relleno_thunk_de_runtime_PS2Recomp = 96`: PS2Recomp no las recompiló (sceSif*, sceVu0*…) sino que llaman
  a `ps2_stubs::`; quedan como stub. Necesitan `plat_*` propio o confirmar que no se usan.
- `sdk_con_stub_que_corta = 178`: SDK con syscall/registros de hardware, stub que devuelve 0. Ídem.
- Total a resolver para no necesitar PS2Recomp: **633 + 9 + 96 → ~640 funciones distintas** (las 178 y 96 se
  solapan; ninguna usa PS2Recomp en tiempo de ejecución, solo en el build vía nombres). Del juego propiamente dicho: 0.

### 1.3 Las más usadas en juego
No hay rastro FALLBACK en `../BT2-test/logs/vivo` (sólo `.log/.fight.log/.trace.bin/.mp4`; el grep por
`FALLBACK|relleno` no dio nada). El único conteo es `docs/audit/fallback_used_fight.txt` (sesión completa con
`BT2_FALLBACK_LOG=1`): **50 funciones ejecutadas**. Las 13 del juego que aparecían allí (WrapAngle, StgRigid*,
ColSphere*, Vec3_Dist, 29DFD0, 293BE0) ya están en C. Quedan ~37 del rango 0x300000–0x30AA00 y 0x325830–0x336E50:
`300898 300DD0 301A98 302278 3025A0 303B48(Hud_Term) 303C78(BtlPause_Term) 304690 305440 305568 305878 305C50
306560 306850 306AA8 306CB8 306E08(BtlEvent_SetWaitOff) 306E68 3070D0 3073E0 307590 307600 307700 307798 3077D8
3077F0 307808 307AF8 30A450 30A9B0 325830 326980 326A80 32A940 32AB50 32B168 336E50`.
Ojo: 0x300000–0x30C7B8 está **debajo de GAME_END** en `link_full.py` pero `region()` la etiqueta "SDK": varias
(Hud_Term, BtlPause_Term, BtlEvent_SetWaitOff) son **código del juego** mal clasificado. Hay que corregir la
frontera antes de contar.

### 1.4 Orden de trabajo
1. Volver a medir: correr una sesión larga con `BT2_FALLBACK_LOG=1` en todos los modos (menús, historia, torneo,
   Ultimate Battle) y guardar el listado en `docs/audit/`. Esfuerzo: 1 sesión.
2. Corregir la frontera juego/SDK (0x300000–0x30C7B8) en `region()`. 0,5 h.
3. Traducir a C las ~37 ejecutadas (prioridad: las de pelea y menú). Muchas son del juego (tareas Term/Init). 2–4 días.
4. libc/libm (memset, sprintf_r, strlen, math): mapear al host por dirección con una tabla propia en
   `config/` (reemplaza `libc_addr`, que hoy depende de los nombres de los .cpp de PS2Recomp). 1 día.
5. Resto del SDK (sce*): cada uno → `plat_*` en `port/full/plat_sdk.c` o stub explícito documentado
   (`TEMP_STUBS.txt`). Incluye las 96 thunks, 178 que cortan y 9 que no compilan. 3–5 días.
6. Overlay 3D6728..3D6788 (13 trampolines): C de una línea o alias en `link.ld`. 1 h.
7. `link_full.py --no-fallback` por defecto; build sin `port/build/recomp`, sin `recomp_shim*`, sin g++ del
   relleno, sin `-DBT2_FALLBACK`. Probar todos los modos. 1–2 días.
8. Borrar del repo nuevo `third_party/PS2Recomp`, `port/recomp*.toml`, `port/sdk_stubs.toml` (si ya no se usa),
   `recomp_shim/`. Licencia: sin código GPL, el port puede ser MIT.

Total estimado: **1,5–2,5 semanas**.

Riesgos: (a) funciones de SDK que se ejecutan raramente (memoria de tarjeta, sonido IOP) y hoy "funcionan" por
relleno — sólo aparecen al probar ese modo; (b) cambios de ABI (64 bits en registros, branch-likely, clase 11)
al pasar a C; (c) los 178 stubs que cortan pueden estar ocultando bugs actuales; (d) `funcmap.csv` (452 KB) se
generó con el analizador de PS2Recomp: hay que regenerarlo desde splat/símbolos propios o declararlo dato
derivado (no es código de PS2Recomp, pero conviene un generador propio).

## 2. Preparación de los repos

### 2.1 Repo DECOMP (`BT2-Decompiled`, CC0 como BT3)
Entra: `src/` (23 MB, 4023 .c; incluye `src/auto` 12 MB / 2889 archivos — revisar si son salida m2c sin limpiar
o subirlas marcadas), `include/` (2,2 MB), `config/` (1,7 MB: yaml de splat, `symbols/`; las tablas `xmatch_bt3*.csv`
son de trabajo, decidir), `configure.py`, `scripts/` útiles (792 KB, filtrar), `docs/` técnicas (decomp_guide,
clases de bug, lessons_bt3_upstream), `README.md`, `LICENSE`.
No entra: `asm/` (44 MB), `build/` (217 MB), `tools/` (168 MB: compiladores ee-gcc/mwcps2 → se descargan),
`disc/`, `gamedata*`, `reference/`, `.venv`, `build.ninja`, `.ninja_log`, `src_dropped/`, `BT2-backups/` (155 MB),
`scratch/` (6 GB), `patches/` (revisar), `*.pre_*` backups.

### 2.2 Repo PORT (`Tenkaichi2Decomp`, MIT como BT3 si se elimina PS2Recomp)
Entra: copia de `src/` + `include/` (con `#ifdef PORT`/`__mips__` ya presentes), `port/full/` (792 KB, sin
`recomp_shim*` tras la fase 1), `port/eq/` (27 MB, 6252 equivalentes nativos), `port/tools/` (sin `__pycache__`),
`port/src`, `port/include`, `port/funcmap.csv`, `port/third_party/imgui` (MIT) y `xxhash` (BSD-2), `config/`,
`configure.py`, `install.py` nuevo, `play.sh`, `game.toml` (revisar), docs del port, README, LICENSE.
No entra: `port/build/` (1,3 GB), `build_port/` (108 MB), `third_party/PS2Recomp`, `gamedata`, `saves`, `mc0/mc1`,
`*.mp4`, capturas, logs, `bt3_pipelines.txt`, `COPIA.md`, `docs/MEMORIA_CLAUDE.md`, `docs/claude_memory/`,
`docs/agents/`, `docs/HANDOFF.md`/`RETOMAR.md` (internas).

### 2.3 .gitignore propuesto (ambos)
```
*.iso
*.rvz
*.bin
*.elf
*.mp4
*.png
*.pre_*
/disc/
/asm/
/assets/
/build/
/build_port/
/tools/
/.venv/
/gamedata*
/saves/
/mc0/
/mc1/
/reference/
/scratch/
/BT2-backups/
/src_dropped/
/third_party/
/port/build/
__pycache__/
*.o
.splache
/build.ninja
.ninja_*
*.log
*.trace.bin
bt3_pipelines.txt
bt2_settings.txt
install.log
```

### 2.4 Rutas absolutas
Sin rutas absolutas: `port/tools/*`, `configure.py`, `play.sh`, `config/`, `src/`, `include/`, `port/full`, `port/eq`.
Con `/home/rexx`, `/run/media` o `/mnt/datos`: `scripts/bt3_names.py`, `scripts/bt3_names_ovl.py`,
`scripts/fn_diff.py`, `scripts/ps2_boot_test.py`, `scripts/audit_void_con_retorno.py`, `scripts/audit_ret_perdido.py`,
`scripts/audit_firmas_bt3.py`, `scripts/setup_symlinks.sh`. Son de auditoría: dejarlas afuera o pasarlas a
argumentos/variables de entorno. Además `link_full.py` usa `scripts/capped.sh` (incluirlo) y `gcc/g++` fijos
(usar `$CC/$CXX`).

### 2.5 Logs TEMP y sondas
| Marcador | Archivos | Líneas | Dónde |
|---|---|---|---|
| TEMP | 44 | 87 | `port/full/temp_stubs.c`, `mem.c`, `gs/gs_gl.c`, `gs_core.c`, `gs_draw.c`, `src/battle/xc_1BC230.c`, … |
| BEAM | 8 | 19 | port/eq + gs |
| TEX0TRUNC | 19 | 22 | casi todo en `port/eq/*.c` (12C468, 137F58, 188218…) |
| CHKREG | 1 | 4 | — |
| B10 | 5 | 9 | — |
| B12 | 1 | 1 | — |
Listado: `grep -rnw 'TEMP\|BEAM\|TEX0TRUNC\|CHKREG\|B10\|B12' src port/full port/eq`. Quitar o dejar detrás de
`BT2_TRACE` (`plat_trace.c` ya existe; el build `full_trace` es la opción).

### 2.6 Blobs binarios embebidos
Barrido con Python: inicializadores `= { ... }` con ≥256 números en `src include port/full port/eq` → **0 casos**.
Tampoco hay líneas con ≥8 literales hex seguidos. Los datos van por `D_xxxx` absolutos de `link.ld` (6230
símbolos) leídos del ELF del usuario. Pendiente revisar a mano: `port/build/vu1_micro.bin`/`vu1_mem.bin` (son
del juego: se generan, no se suben) y `port/full/gs/` heredado de Tenkaichi3Decomp (shaders propios, OK).

### 2.7 Licencias de third_party
- `third_party/PS2Recomp`: **GPL** → no subir; motivo central de la fase 1.
- `port/third_party/imgui`: MIT (LICENSE.txt). OK.
- `port/third_party/xxhash`: BSD-2 (LICENSE). OK.
- Renderer `port/full/gs/*` viene de Tenkaichi3Decomp (MIT): conservar aviso de copyright.
- Código "from BT3-Decompiled" (CC0): sin restricción, pero auditar (pendiente de RETOMAR).

## 3. Dos repos y sincronización

### 3.1 Reparto
- DECOMP: el C de las funciones del juego, compilable para PS2 con splat + ee-gcc (objetivo matching/no-matching
  como BT3-Decompiled).
- PORT: copia de `src/include/config` + runtime, renderer, plataforma, `port/eq`, build nativo, `install.py`.

### 3.2 Opciones de compartir el C
1. Submódulo (`port` incluye `decomp/` como submódulo): sin duplicación, pero clonar es más torpe y BT3 no lo hace.
2. **Copia sincronizada por script (recomendado, igual que BT3 pero automatizado)**: `scripts/sync_decomp.py`
   que copia `src/ include/ config/` del decomp al port (o al revés para arreglos hechos en el port), muestra el
   diff y falla si un cambio fuera de `#ifdef PORT` no existe en el otro lado.
3. subtree: historia compartida, más complejo.

### 3.3 Mantener arreglos
- Regla: todo arreglo de lógica del juego va al DECOMP primero; el port solo agrega `#ifdef PORT`/`__mips__`.
- Commit en ambos con la misma referencia (`B21`, `clase 12`…), `CHANGELOG` de bugs confirmados.
- CI simple en el port: `sync_decomp.py --check` contra el tag del decomp.

### 3.4 Lo que falta portear antes de publicar (de bugs_open.md, PIEZAS_FALTANTES.md, RETOMAR.md)
1. B24 HUD de zeni del mapa del mundo; B14 rayos de Ultimates (arreglo aplicado, falta probar).
2. B25 rayas al cruzar el borde norte (niebla).
3. B20 mapas que se rompen al empezar; B21 agua (arreglado clase 12, falta probar).
4. B18/B19 Ultimate Battle (arreglado/mitigado, falta probar); B15 vista previa del mapa; B13 cielo con Genkidama.
5. Clase 6 (4 revertidas + 37 multi-función), clase 11 (branch-likely).
6. Trabones progresivos (sesión 20261106-094032, torneo/duelo).
7. Audio de los videos (PIEZAS §1), resto de sonido (§2).
8. Recorrer todos los menús/modos sin crash (próxima fase del 04-11), Dragon Tournament.
9. Auditoría de archivos "from BT3-Decompiled".
10. Fase 1 de este documento (sin PS2Recomp) y quitar sondas.

## 4. Build de un comando

Objetivo `python3 install.py --iso <iso>` (mismo esquema que Tenkaichi3Decomp):
1. Requisitos: clang/gcc, ninja, python ≥3.11, SDL3, ffmpeg (libav*), splat (`splat64[mips]` fijado) en `.venv`.
2. ISO: verificar SHA1 de `SLUS_214.41` y `DBZP.BIN` (constantes en `install.py`); sin ISO no hay build.
3. Extraer datos del disco → `gamedata/` (hoy `gamedata` es un enlace y `gamedata.iso`: reemplazar por extractor ISO9660 en Python).
4. splat con `config/SLUS_214.41.yaml` → `asm/`, datos del ELF → `port/build/` (`combined.elf/.ovltext/.ovldata`,
   `vu1_*.bin`), todo derivado del ISO del usuario.
5. Generar: `port/tools/gen_native.py`, `gen_shaders.py`, `irfix.py`, `ptr32.py` (revisar que tomen rutas relativas
   a `ROOT`; hoy sí).
6. Compilar: `build_full.py` (usa `scripts/capped.sh`: incluirlo o hacerlo opcional).
7. Enlazar: `link_full.py --no-fallback` (tras fase 1). Quitar `objcopy`/`gcc` fijos → `$CC`.
8. Autoprueba: demo sin ventana (ver `plat_demo.c`).
Cosas a sacar: `scripts/setup_symlinks.sh`, referencias a bt2-old/BT2-test, contenedores (no se encontraron en
`build_full.py`/`configure.py`/`play.sh`). Esfuerzo: 2–3 días + 1 día de prueba en sistema limpio (VM Arch y Ubuntu).

## 5. Resumen de esfuerzo
| Etapa | Esfuerzo |
|---|---|
| Fase 1 sin PS2Recomp | 1,5–2,5 semanas |
| Pendientes de juego (3.4 puntos 1–9) | abierto (semanas) |
| Limpieza repo (TEMP, scripts, .gitignore, docs) | 2–3 días |
| install.py de un comando | 2–3 días |
| Separar dos repos + sync script + README/LICENSE | 1–2 días |
| Prueba desde cero | 1 día |
