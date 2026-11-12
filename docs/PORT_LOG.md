# Registro del port (BT2, SLUS_214.41)

## 0. Entorno (2026-10-08)

- `git clone --recursive https://github.com/ran-j/PS2Recomp third_party/PS2Recomp`: HEAD de upstream =
  `2c5fbb9`, el mismo commit base del kit, así que la serie entra limpia.
- `git checkout -b bt2 && git am ~/Proyectos/ps2-decomp-kit/third_party/patches/ps2recomp-000*.patch`:
  0001-0009 aplicados sin conflictos.
- `cmake -S . -B out/build -G Ninja -DCMAKE_BUILD_TYPE=Release -DPS2X_BUILD_TEST=OFF -DPS2X_BUILD_STUDIO=OFF`
  y `ninja -j6 -C out/build ps2_recomp ps2_analyzer` (-j6: con -j12 la máquina se colgó una vez).
- `research/BT3-Recomp`: `git clone --depth 1` de z3xox/BT3-Recomp, sólo para leer.
- **Bloqueante:** no hay ninguna imagen de BT2 en el disco (buscado en `/`, 2026-10-08).
  Hace falta la copia propia `SLUS_214.41` → `ln -s <iso> gamedata.iso`.
- (Resuelto) El usuario aportó `~/Descargas/DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).7z` → extraído
  a `~/Descargas/Roms/PS2/BT2/` (ISO de 2 998 829 056 bytes, sha1 `0b11f7a2a4c178b555c45a58ce8ee725e57a1423`).
  `SYSTEM.CNF`: `BOOT2 = cdrom0:\SLUS_214.41;1`, NTSC. Disco: overlay `BIN/DBZP.BIN` (como BT3),
  `DATA/*.AFS`, vídeos CRI Sofdec `DATA/*.SFD`, IRX: `CRI_ADXI`, `SDRDRV`, `DBCMAN`, `CDVDSTM`, `MODHSYN`/
  `MODMIDI`/`MODSESQ*`, `LIBSD`, `MCMAN/MCSERV`, `SIO2MAN/SIO2D`, `DS2O_D/DS2U_D`, `SOUNDS`, `IOPRP300.IMG`.

## 1. Bootstrap con el kit (byte-idéntico)

- `kit/new_project.py BT2-Recomp <iso> SLUS_214.41 --name "Dragon Ball Z: Budokai Tenkaichi 2 (USA)" --venv`
  (el proyecto se creó vacío y luego se movieron dentro `third_party/`, `research/` y `docs/`).
- Fallo 1: `splat` → `yaml.scanner.ScannerError`: el `name:` del yaml no iba entre comillas y lleva `:`.
  **Arreglado en el kit** (`kit/new_project.py:166`, ahora `name: "…"`).
- Fallo 2: `CHECK` distinto desde el byte 293 (100 851 bytes). `_start` carga `0x387f00` en vez de
  `0x387e80`: secciones desplazadas `0x80`. Causa: el ELF de BT2 tiene `.text_nop`, `.ctors`, `.dtors` y
  `.reginfo` (`0x33f350-0x33f390`) **entre `.vutext` y `.data`**. Como subsegmentos `data`, el linker script
  de splat los lleva a la sección de datos y cambia el orden. `flatten = true` no sirve (deja 3 símbolos
  `D_` sin definir). Solución: un único subsegmento `[0x23F350, textbin]` que cubre ese tramo hasta `.data`.
  → `CHECK` pasa (0 bytes distintos). *Pendiente para el kit*: que `elf_survey.py --yaml` haga esto solo
  cuando hay secciones de datos antes de `.data` y dentro del segmento de texto.
- Compilador (pista de `elf_survey`): prólogo `sd8` → primera suposición ee-gcc 2.96 (el mismo que BT3).
  Sin confirmar con `cc_probe.py` (no hace falta para el recomp).

## 2. Funciones del SDK

- `python3 scripts/sdk_names.py` → 577 nombres (`config/symbols/sdk.txt`), 234 stubs del runtime
  (`port/sdk_stubs.toml`). Fallo: no creaba `config/symbols/`. **Arreglado en el kit** (`mkdir`).
- `configure.py && ninja` otra vez para que los nombres entren en el ELF reconstruido (sigue byte-idéntico).

## 3. Traducción

- `python3 scripts/recomp.py` → `port/funcmap.csv` con 11 192 funciones (15 por punteros en datos, 1 por
  `lui/addiu`). PS2Recomp: 11 191 procesadas, 10 957 recompiladas, 234 stubs, 0 skipped, **0 decode failures**.
- **Falta**: `DBZP.BIN` (overlay de juego, 513 167 bytes; como BT3 `dbzp_*.csv`) no está traducido.
  Dirección de carga: **`0x3B3100`** (justo tras `.bss`, que acaba en `0x3B3038`). La carga está en
  `func_001002D8`: tabla de rutas `D_0033F404` → `func_00333DB0` (open, reintenta mientras < 0),
  `func_003341B8` (lseek fin/inicio = tamaño) y `func_003343F8` (read en bucle hasta leerlo todo).
  BT3 lo carga en `0x334C00` (`research/BT3-Recomp/games/bt3/gen_overlay.py`: lo envuelve en un ELF mínimo,
  lo traduce con su propio mapa y añade puntos de reentrada de callbacks/jump tables). Las vtables (`scripts/vtables.py`) todavía no se han recorrido.

## 4. Ejecutable nativo

- `port/CMakeLists.txt` y `port/src/main.cpp` copiados de THDJ (`HEAD`), con `THDJ_*` → `BT2_*` y el reloj
  del guest a NTSC (`/ 60`). `tools/PS2Recomp -> ../third_party/PS2Recomp`. `gamedata/` = disco extraído,
  `gamedata/IOPModules -> IRX`, `gamedata.iso` -> la ISO.
- `cmake -S port -B port/build/native -G Ninja -DCMAKE_BUILD_TYPE=Release && ninja -j6 -C port/build/native`
  → enlaza (`exit=0`, 283 unidades, ~25 min con -j6).

## 5. Primer arranque (2026-10-08)

- `BT2_WATCH=10 timeout 40 xvfb-run -a port/build/native/bt2 gamedata/SLUS_214.41 gamedata.iso`
- Bien: ELF cargado, `SifInitRpc`, los **13 IRX** cargan en el IOP emulado (SIO2MAN, MCMAN, MCSERV, DBCMAN,
  SIO2D, DS2U_D, LIBSD, SDRDRV "SDR driver version 4.0.1", MODHSYN, MODSESQ2, CDVDSTM, SOUNDS, CRI_ADXI
  "CRI ADX Driver Ver.9.71"). 2 hilos EE, 7 semáforos.
- Cuelgue: hilo 1 girando en `pc 0x31f128` = `sceCdLayerSearchFile` (0x31F088). Es el mismo caso que THDJ:
  el runtime tiene HLE de `sceCdSearchFile` (0x31F388, que sólo reenvía capa 0), pero el juego
  (`func_002FD318`) llama directamente a la versión por capa, que espera el RPC de CDVDFSV.
- Arreglo (`port/recomp_extra.toml`): `sceCdSearchFile@0x0031F088` (mismo ABI en a0/a1; a2 = capa sobra, el
  disco es de una capa) y `unstub` de `sceSdRemoteInit`/`sceSdRemote` (el juego carga SDRDRV+LIBSD reales,
  como THDJ). → 233 stubs, 10 958 funciones recompiladas.
- *Para el kit*: `sdk_names.py` podría emitir este alias solo cuando encuentra `sceCdLayerSearchFile`
  (ya van dos juegos).

## 6. Segundo arranque: `main` vuelve (2026-10-08, abierto)

- Con el paso 5 el juego avanza: `sceCdSearchFile` encuentra `ZS2US.DIR`, `ZS2US_1/2.AFS`, `ZS2USOP/ED.SFD`,
  `LOGO_O.SFD`; la tarjeta de memoria responde; registra su servidor RPC `0x80000704`. Luego
  `Game thread returned. PC=0x100240`: `_start` (0x100238) llamó a `main` (`func_00100388`), que volvió, y salta
  a `Exit`.
- `main` sale en `0x10063C/0x100648` si `sceChk01` (`func_00320580`) devuelve <0 o deja `*res & ~3 != 0`. Justo
  después está el bucle principal (`0x100680`: carga `DBZP.BIN` y llama a `func_3B7FA8`, en el overlay).
- `sceChk01`: `sceSifAllocIopHeap` → `func_0032F020`/`func_0032F000` (sceSifSetDma/DmaStat, **sin nombre**: se
  traduce el código real) → `_sceSifLoadModuleBuffer(iop_addr, 0, 0, &res)` de un **IRX embebido en el ELF**
  (`D_00369F90`-`D_0036A2E9`, 857 bytes, módulo `ck01`, importa `cdvdman`). El módulo llama a `sceCdSC(-9, …)`
  (versión de cdvdman) y devuelve 5 si vale 1, si no 1 (`NO_RESIDENT_END`). Nuestro `sceCdSC(-9)` = `0x226`:
  el módulo pasaría.
- Causa probable (mismo tipo que `_sceSifSendCmd` en THDJ, catálogo D14): el recompilador enlaza
  `_sceSifLoadModuleBuffer@0x3373F0` con el handler `ps2_syscalls::sceSifLoadModuleBuffer`, que (a) lee el ELF
  de la **RAM del EE** (`IopModuleLoader::readElfFromGuest` → `host.readGuest`), pero en el SDK de Sony la
  dirección es de la **RAM del IOP** (ya copiada por SIF DMA); (b) no escribe `*modres` (a3). → devuelve -1.
- Siguiente paso (elegir):
  1. runtime (parche 0010): `_sceSifLoadModuleBuffer` propio que lea de la RAM del IOP y escriba `*a3`. Antes hay
     que comprobar que el SIF1 DMA de `func_0032F020` traducido llega a la RAM del IOP;
  2. override del juego: `sceChk01` → `*a0 = 1; return id>0` (lo que hace el módulo en consola). Rápido, pero
     no arregla la causa.

## 7. Parche 0010 (en curso) y overlay (2026-10-08)

Objetivo fijado por el usuario: llegar al vídeo de intro y a un combate jugable.

- **Base 0010**: el árbol del kit (`ps2-decomp-kit/third_party/PS2Recomp`) tenía 0001-0009 aplicados con
  `git apply` más el trabajo sin commitear de THDJ. `rsync` de ese árbol sobre la rama `bt2` (que ya tiene
  0001-0009 como commits): el diff restante es sólo ese trabajo. Contiene `_sceSifSendCmd` (D14), `MFC0 Count`
  (D13), `SetAlarm/CancelAlarm` del IOP, argv de `start()` como MODLOAD, el lector de IRX desde la RAM del IOP
  (`PS2X_IOP_RAM_MODULES`), IOP en porciones al entregar ciclos acumulados y `PS2X_VIF1_THREAD` apagado por
  defecto.
- **D21** (`sceChk01`): handler propio `ps2_syscalls::_sceSifLoadModuleBuffer`
  (`Kernel/Syscalls/System.cpp`, `X(_sceSifLoadModuleBuffer)` en `ps2_call_list.h`) que escribe `*modres`
  (a3) con el resultado de `start()`. La lectura desde la RAM del IOP pasa a estar **activada por defecto**
  (`PS2X_IOP_RAM_MODULES=0` la apaga). La copia EE→IOP previa ya existía: syscall `0x77` → `sceSifSetDma`.
- **D1**: `PS2Memory::writeIORegister` refleja `D_ENABLEW` (0x1000F590) en `D_ENABLER` (0x1000F520).
- **D4**: `ControlFlowEmitter::emitResumeFromDelaySlotEntry` sigue al destino si el salto es siempre tomado
  (`beq/beql $0,$0`, `bgez/bgezl $0`, `j` interno).
- **Overlay `DBZP.BIN`**: PS2Recomp **no tiene intérprete** (`lookupFunction` → "No exact recompiled function"),
  así que se traduce de antemano:
  - `config/overlay/DBZP.yaml` (splat, `asm_ovl/`): código `0x3B3100-0x421300` (último `jr $ra` en 0x4212F8),
    datos hasta 0x43048F. 494 funciones de splat + 13 por punteros en datos = 507. `func_003B7FA8` (la que
    llama el bucle de `main`) está entre ellas.
  - `scripts/overlay.py` (llamado por `recomp.py`): añade esas funciones a `port/funcmap.csv` y escribe
    `port/build/combined.elf` = ELF original + `.text.ovl`/`.data.ovl` (`objcopy --add-section`). El
    traductor lee secciones (`ElfParser::isExecutableSection`), no segmentos. En ejecución se sigue cargando el
    ELF original y el juego lee `DBZP.BIN` él mismo.
- **Vídeo**: `.SFD` = CRI Sofdec, que en la consola decodifica con la IPU; la IPU del runtime es un esqueleto
  (`Kernel/Stubs/IPU.cpp`, 108 líneas). `ffprobe`: MPEG-PS con mpeg2video 512x448 a 29,97 fps y adpcm_adx a
  48 kHz → FFmpeg lo decodifica tal cual. Plan: HLE del reproductor (`mwPly*`) con FFmpeg en el host (BT3-Recomp
  hace algo parecido en `ps2_fmv_override.cpp`) en vez de emular la IPU.

## 8. Logos, vídeos, título y menú (2026-10-08)

- **IOP heap**: `PS2RNA_Init` (CRI) se paraba a propósito (`E02041101: Failed, sceSifAllocIopHeap(16448)`, bucle
  en 0x302488). Dos causas en `ps2xIOP/src/emulator/core/iop_memory.*`: (1) `allocate` empezaba en el cursor de
  máximo y nunca reutilizaba bloques liberados → ahora *first fit* desde `HeapBase`; (2) heap de sólo 832 KB
  (`0x120000-0x1F0000`), con 81 KB + 260 KB de CRI y 21 bloques → `HeapBase = 0xA0000` (los 14 módulos acaban
  ~0x8F000). Traza: `PS2X_IOP_HEAP_TRACE=1`. `sceSifAllocIopHeap` avisa por stderr al fallar.
- **Vídeo**: `port/src/movie.cpp` sustituye `func_0024BA78(name)` (`replaceFunction`): FFmpeg abre
  `gamedata/DATA/<NAME>.SFD`, escala a 512x448 RGBA, lo escribe en VRAM FBP 0 y fija PMODE/DISPFB1/DISPLAY1.
  Un fotograma por llamada: deja `ctx->pc = 0x24BA78` y espera VBlank con `waitVSync` (lanza y reanuda). Start o
  Cross lo saltan (`padBackend()` + `g_bt2ScriptedButtons`); `BT2_SKIP_MOVIES=1` los salta todos. Sin audio
  (ADX del .SFD no se reproduce todavía).
- Resultado (capturas con `scripts/drive.sh`): logos del juego renderizados por el motor (Atari, Funimation,
  Okratron, Bandai Namco, Spike, Sofdec/ADX), `LOGO_O.SFD` 151 fotogramas, apertura `ZS2USOP.SFD`, **pantalla de
  título "PRESS START button"** y **menú principal** ("New Game", diálogo Yes/No) respondiendo al mando.
- Velocidad: ~0,45x tiempo real (37 s de guest en ~80 s).
- `scripts/drive.sh <dir> <s> t:boton t:shot …` maneja el juego sin pantalla por FIFO; `play.sh` lo abre en
  ventana (teclado + mandos). Teclado: flechas/WASD, X/Espacio = Cruz, C/Esc = Círculo, Z = Cuadrado,
  V = Triángulo, Q/E = L1/R1, Shift izq/der = L2/R2, Enter = Start, Tab = Select.
- `BT2_SHOT` ahora captura `FBW*64 x 448` (antes 640x512, que mezclaba el otro búfer).

## 9. Cambio de estrategia: decompilación completa reutilizando BT3-Decompiled (2026-10-08/09)

Pedido del usuario: portear decompilando todo el juego, como z3xox con BT3 (BT3-Decompiled → Tenkaichi3Decomp).
El port por recompilación (§1-8) se conserva como respaldo jugable: logos, vídeos, título y menú funcionan
(`play.sh`).

- **Referencia**: `~/Proyectos/BT3-Decompiled` compilado localmente (sólo `build/` y `tools/`, que git ignora:
  `tools/ee-gcc2.96 -> kit`, `tools/binutils -> kit` 2.40; sus binutils 2.47 rechazan `sq $t7,..($k0)` y quedaron
  en `tools/binutils.247`). Su ROM difiere en 6 bytes, todos en `ObjSeam_TransformVtx` (trabajo NON_MATCHING del
  port); el resto es byte-idéntico, así que sus símbolos y su C son fiables.
- **`scripts/xmatch.py`**: compara la "forma" de cada función de BT2 (`port/funcmap.csv`, ELF + overlay) con las
  10 990 de BT3 (ELF + DBZP), con destinos de `j/jal` e inmediatos de direcciones enmascarados.
  - Sin `--strict`: 4115 idénticas (2119 con C en BT3), pero se cuelan cambios de layout de structs (`Heap_Alloc`:
    `lw v1,36(v0)` en BT2 frente a `20` en BT3).
  - **`--strict`** (los offsets se conservan salvo base `$gp` o un registro cargado con `lui`): **3548 idénticas,
    1530 con C en BT3** → `config/xmatch_bt3_strict.csv`. (`config/xmatch_bt3.csv` = pasada difusa ≥0,85.)
- **`scripts/transplant.py`**: por cada `.c` de BT3, escribe `scratch/xfer/<ruta>` con sólo las funciones
  emparejadas (el resto como prototipos, sin `INCLUDE_ASM`), los nombres auto de BT3 traducidos a direcciones de
  BT2, y corre `fdiff.py`. Un nombre sólo puede ir a una dirección: si BT2 tiene el mismo código dos veces sólo la
  primera copia lo recibe; los nombres que BT2 ya tiene (SDK) no se mueven.
  - Antes de deduplicar: 1524 funciones → **1481 OK**, 43 DIFF, 0 NOCOMPILE. Tras deduplicar: 818 → **790 OK**,
    28 DIFF (`config/xfer_results.csv`). En 4,5 s.
  - `config/symbols/bt3_funcs.txt`: nombres de BT3 para las direcciones de BT2.
- **`scripts/integrate_xfer.py`**: agrupa las OK contiguas del mismo `.c` en `src/<dir>/<nombre>_<INICIO>.c`, deja
  fuera las que generan datos propios (.rodata/.data/.sdata/.lit4: el split mantiene los datos en asm), resuelve
  los símbolos de datos contra los bytes originales (`%hi/%lo`, `%gp_rel`, `jal`) → `config/symbols/bt3_data.txt`,
  y escribe `config/c_files.txt` (copia: `config/c_files.v2.txt`). Último: 282 archivos, 529 funciones, 261 fuera
  por datos propios, 49 símbolos nuevos, 28 ambiguos.
- Headers de BT3 copiados a `include/{sys,battle,cri,menu}/` y `include/main.h` (los base son idénticos al kit).
  `game.toml`: `-G0` para `src/cri/`, `src/menu/`, `src/sys/late_a` (como BT3).
- yaml: `symbol_addrs_path` ahora incluye `config/symbols/{sdk,bt3_funcs,bt3_data}.txt`.
- Primer gate (antes de deduplicar): los 707 `.c` compilaban; el link falló con 1115 símbolos sin definir porque
  splat no leía los archivos de símbolos. Tras añadirlos, splat rechazó un nombre duplicado
  (`BattleResult_GetFlags` en 0x23EFB8 y 0x2D8DA0): de ahí la deduplicación. **Siguiente**: `configure.py`
  vuelve a fallar (cfg=1); revisar el error de splat.
- Herramientas que aportó el usuario por si hacen falta: `/mnt/datos/Proyectos/ps2-tool` (scripts de Ghidra,
  `functions.csv`, `sce_flat.txt` = firmas del SDK), `/mnt/datos/Herramientas/Ghidra`.

## 10. Primer gate byte-idéntico con C (2026-10-09)

- Problemas resueltos para llegar al link:
  1. `integrate_xfer.py` acumulaba líneas viejas en `c_files.txt` → ahora reescribe las suyas (etiqueta
     `from BT3-Decompiled`) y borra sus archivos viejos; `bt3_data.txt` se vacía al empezar.
  2. Los nombres automáticos de splat (`func_/D_XXXXXXXX`) contaban como "ya nombrados" e impedían poner el nombre
     de BT3 → sólo cuentan los de los archivos de símbolos.
  3. Nombres sin una única dirección en BT2 (40) → pase de cierre: fuera los archivos que los usan (y repetir).
  4. Bloques `__asm__(".globl …")` de nivel superior (VU0 de BT3) se copiaban en cada trozo → `transplant.py` sólo
     conserva el bloque de una función pedida.
  5. **`gen_yaml.py` deshacía el arreglo del §1** (`.text_nop/.ctors/.dtors/.reginfo` como `data` → `.bss`
     desplazado 0x80). `elf_survey.yaml_segments` (proyecto y kit) ahora las deja como un `textbin` en el código.
  6. Envoltorios con la misma forma que en BT3 pero que llaman a otra función (la forma estricta enmascara el
     destino del `jal`): **`scripts/gate_prune.py`** compila, compara la ROM y quita los archivos máquina
     (`from BT3-Decompiled` o `auto/`) que contienen bytes distintos, en bucle hasta byte-idéntico
     (`config/xfer_dropped.txt`). Ronda 0: 203 bytes, 11 archivos; ronda 1: idéntico.
- **Byte-idéntico con 195 archivos de BT3** (~370 funciones), y luego con `leaf_sweep.py --write`: +980 archivos
  (1451 funciones simples verificadas de 1797 candidatas). `leaf_sweep.py` (proyecto y kit): los `nonmatching` de
  datos no tienen tamaño (arreglado).
- **Estado: 1175 archivos C, ROM byte-idéntica, 2,11 % de los bytes del código del juego en C** (9750 funciones
  siguen en asm). `config/c_files.v2.txt`/`v3.txt` = copias antes de cada tanda.
- Candidatos de BT3 pendientes: 261 funciones con datos propios (.rodata/.lit4: falta partir los datos para ellas),
  28 DIFF, y 891 pares no estrictos/difusos con C en BT3 (529 exactos por forma pero con offsets de struct
  distintos, 362 difusos ≥0,85): el C de BT3 sirve de borrador.
- `m2c` instalado en `.venv` (`python -c "import m2c.main as m; m.main()" --target mips-gcc-c --valid-syntax`):
  decompila MIPS normal; las macros VU0 (`lqc2`, `vmul…`) salen como `M2C_ERROR` (BT3 las escribió como
  `__asm__` de nivel superior, ver `src/sys/vu0_a_c_*.c`).

## 11. Tanda 1 de agentes (2026-10-09, en curso)

- 6 agentes en paralelo (A-F) sobre el código del juego del ejecutable principal, partido en 6 rangos de igual
  cantidad de bytes aún en asm: A 0x100000-0x158EB0, B -0x1B0298, C -0x207BF0, D -0x25DF98, E -0x2B7B38,
  F -0x30FDC0 (incluye CRI). Brief común: `docs/agents/BRIEF.md` (sobre `docs/agent_rules.md` del kit).
- Cada uno recibe `docs/agents/bt3_candidates_<x>.csv` (pares con BT3 aún no integrados: strict con su resultado
  de transplante, shape-only, fuzzy): 261/355/267/195/382/148.
- Asm congelado para ellos: `scratch/asm_snap/` (+ `scratch/SLUS_214.41.snap.elf`). Mientras corren **no** se
  borra `build/` (fdiff busca los `func_XXXX` en `build/SLUS_214.41.elf`).
- Regla de datos de esta tanda: objetos sin datos propios (strings/floats como `extern` de las `D_` existentes);
  funciones con jump table en archivo aparte.
- Integración: `scripts/integrate_agents.py` (lee `docs/agents/<X>_files.txt` y `config/symbols/agent_<X>.txt`,
  añade al yaml, corre `gate_prune.py`, que ahora también puede quitar archivos `# agent`).
- Las 6 primeras ejecuciones se cortaron por el límite de sesión (A además se paró a mano y se relanzó). Dejaron
  poco listado: rescatados con `fdiff` 6 archivos limpios (xb_179D00, xd_242948, xf_2B7B58/2B7C38/2B7CB8/2B7E68,
  más xb_178940 ya listado) → **byte-idéntico con 1182 archivos**. Pendientes en disco: xa_13D298 (OK pero con
  .lit4 propio), xc_1B3378 (23/27), xf_2B82B0 (29/30), xd_243680 (0/1).
- Pedido del usuario: **tandas de 3 agentes** para no chocar con el límite. Tanda 1b: A, B, C (sección "Batch 1b" del
  brief: guardar cada archivo terminado en la lista al momento). Después: D, E, F. Snapshot de asm renovado.

## 12. Reanudación en la copia de trabajo `~/Escritorio/BT2-Recomp` (2026-10-09)

Pedido del usuario: prioridad al **port por recompilación con PCSX2**, pero dejando la decomp al día.

- **Importado desde `~/Proyectos/BT2-Recomp`** (sólo lectura allí): los 9 ficheros de la tanda 2 sin integrar
  (`xd_207BF0.c`, `xd_207D40.c`, `xe_292750.c`, `xf_2B81D8/8248/8280/82B0/89D8/9178/92B0.c`),
  `config/symbols/agent_D.txt` (+13 nombres) y las entradas nuevas de `F_files.txt`.
- **Bootstrap del gate en esta copia** (no había `asm/` ni `build/`): `.venv/bin/python configure.py && ninja` →
  byte-idéntico, 5,5 min. `scratch/asm_snap/` congelado (43 MB). Línea base: 3,21 %.
- Verificados con `fdiff`: los 11 CRI y `xd_207BF0` (9/9 OK). Añadido `0x207BF0 0x207D40 battle/xd_207BF0`
  a `D_files.txt`.
- **`scripts/integrate_agents.py`** → ronda 0 tiró 10 ficheros con referencias sin definir, ronda 1:
  **byte-idéntico con 1254 ficheros C (3,38 %)**. Los 10 se apartaron a `docs/agents/pending_names.md`
  (causa: llaman a nombres que no están en ningún `config/symbols/*.txt`, p. ej. `Mtx_MulVec4`, `Vec4_Copy`,
  `Battle_GetWork`, `EftPtcl3_*`; y las tablas de saltos `.L00XXXXXX` de `xb_17D218`/`xb_17D2D8`).
  Quitados de las listas para no quemar una ronda de gate en cada integración.
- Sin integrar por la **regla de datos propia**: `xe_292750.c` (agente E, 42 funciones OK, pero el objeto trae
  `.sdata` con el 0x7F7FFFFE de `CP_FLT_MAX` y `.lit4`); `xd_207D40.c` (jump table `jtbl_0036F960`, 42/65 diff).
- **Oráculos levantados** (receta completa en `docs/ORACLES.md`):
  - PCSX2 propio `~/pcsx2-src/build/bin/pcsx2-qt`, datapath aislado en `/tmp/opencode/pcsx2-bt2`, con
    DebugServer (TCP 21512) y Pine (socket `$XDG_RUNTIME_DIR/pcsx2.sock`); MCP conectado y verificado.
    `PCSX2_EE_COVERAGE=1` → mapa de **cobertura de código EE** (`coverage_stats` / `get_coverage` /
    `clear_coverage`), comandos que el MCP **no** expone: cliente `tools/pcsx2_diff/dbg.py`.
  - Ghidra 12.1.2 **headless** con `GhidraMCPHeadlessServer` (puerto 8089): ELF importado y analizado
    (9.541 funciones), `decompile_function` / xrefs funcionando por MCP.
  - Incidencia: la primera instancia de PCSX2 se apagó sola a los ~14 min (apagado ordenado, sin crash).
    Relanzada con breakpoint en `exit` (0x324398); no ha vuelto a ocurrir.
- **Port**: `third_party/PS2Recomp/out/build` configurado; construir el runtime **sólo** desde `port/`
  (`-msse4.1` lo pone `port/CMakeLists.txt`; `ninja ps2_runtime` suelto falla con los intrínsecos SSE4.1).

## 13. Tanda 3: D, E, F en Haiku (2026-10-10)

- La copia del escritorio pasa a ser la **copia maestra** (`~/Proyectos/BT2-Recomp` queda como archivo: el agente
  de integración Haiku que se paró a mano lo dejó a medias, 1253 líneas en `c_files.txt`, sin verificar).
- Pedido del usuario: decomp completa con D, E, F; la ejecución va al modelo más barato (Haiku), la planificación y
  revisión se quedan en el modelo principal; máximo 3 agentes a la vez.
- Brief: ruta de la copia maestra, sección "Batch 3" (leer `docs/lessons_bt3_upstream.md`; comprobar cada nombre
  usado en `config/symbols/` antes de listar; no meter funciones con jump table; terminar `xe_292750.c`).
- Snapshot `scratch/asm_snap/` renovado desde el build byte-idéntico de 1254 archivos.

## 14. Integración tanda 3 y la causa sistémica (2026-10-10)

- Integración (Haiku, 27 min): ronda 0 link (6 fuera), ronda 1 38 bytes (8 fuera), ronda 2 **byte-idéntico con
  1325 archivos, 3,75 %** (9398 funciones en asm). Tanda 3: D +58 funciones, E +53 (colisión `col_b`), F +77.
- **Pérdida**: `gate_prune.py` borraba los archivos que quitaba por bytes distintos y vaciaba `build/` entero
  (con el scratch de los agentes). Se perdieron 8 archivos (D: `xd_25A468`, `xd_25C770`; E: `xe_274E68`,
  `xe_294628` [18 funciones de colisión], `xe_295F80` [rigid, 8], `xe_298130`, `xe_29B550`, `xe_2B4DC0`), sin
  snapshot ni git. Arreglado: los archivos quitados se **mueven a `src_dropped/`** y el gate sólo borra lo que
  regeneran splat/ninja (`asm/`, `build/{asm,src}`, ELF/ROM/ld), no `build/fdiff` ni `build/scratch_*`.
- **Causa sistémica** de casi todos los descartes (informes de D, E, F): BT2 tiene **varias copias** de los
  helpers VU0/`Vec4_*`/`Mtx_*` y cada módulo llama la suya; con un nombre por dirección el C (de BT3 o de un
  agente) compila a la forma correcta (`fdiff` enmascara `jal`) pero enlaza contra otra copia.
  **`scripts/fix_targets.py FILE START [--write]`**: compila, resuelve cada relocación contra los bytes originales
  y, si el nombre apunta a otra dirección, añade `#define Nombre nombre_en_esa_dirección` arriba del archivo
  (antes de los includes, así el prototipo del header también sigue). Probado con los 12 archivos descartados por
  link: todos re-verificados OK con `fdiff`. `integrate_agents.py` lo corre ahora sobre cada archivo antes del gate.
- Primer intento con `fix_targets`: un `#define` chocó con un prototipo del header (`xd_23EFB8`, compile error,
  ninja parado). Arreglos: `fix_targets` re-verifica con `fdiff` tras escribir y revierte si ya no da OK; usa los
  archivos de símbolos y `funcmap.csv` cuando no hay ELF enlazado; `gate_prune` también quita archivos que no
  compilan. Los 8 perdidos pasan a `docs/agents/LOST.txt` (regenerar desde BT3).
- **Byte-idéntico con 1334 archivos, 3,93 %** (9371 funciones en asm). De los 12 recuperados con `fix_targets`
  sólo 3 cayeron (2 link, 1 bytes; `src_dropped/auto/auto_2e07f0.c`).

## §15 (2026-10-10) Own data, second copies, m2c sweep: 3.93% → 8.26%

- `scripts/data_split.py FILE START`: places each data section of a C object (.rodata/.lit4/.sdata/...) in the
  original by resolving the text's relocations against it (named variables via their section offset) and
  comparing bytes. Lines go to `config/data_files.txt`; `gen_yaml.py` cuts them out of the asm data as
  `[addr, .lit4, src]` (BT3's form). `integrate_xfer.py`, `xfer_dups.py`, `m2c_sweep.py`, `integrate_agents.py`
  (`docs/agents/<X>_data.txt`) all use it; `gate_prune.py` counts data ranges as their file's.
- `scripts/xfer_dups.py`: BT3 C for the second copies of duplicated helpers, under the address's symbol-file name
  or `func_XXXXXXXX`, retargeted by `fix_targets.py` (tag `# bt3 copy`). 195 files.
- `scripts/m2c_sweep.py`: m2c output as is, per function, fdiff-checked (+data_split); 1431 functions with no
  hand work (tag `# m2c`, `src/auto/m2c_*.c`). Drafts and per-function status for agents in
  `scratch/m2c_sweep/` (`status.csv`: OK / differs n/m / compile / m2c: ERROR / jump table).
- Link fixes: `build/<name>_provide.ld` (gen_undefined `--provide`: names no object defines, bound to their
  address) and `PROVIDE()` of every in-image symbol-file name in the extern_syms script, so a C file can call a
  name whose C defines it under splat's label (and vice versa).
- **Incident**: `integrate_xfer` cleared `bt3_data.txt` and, with the ELF of a failed round, `fix_targets`
  renamed BT3 names to `D_` labels; the next link cascade-dropped ~100 agent/auto files (moved to src_dropped/,
  restored from `~/Escritorio/BT2-backups/`). Fixes: bt3_data names kept across runs, `fix_targets
  --keep-unknown`, gate stops when >10 agent/auto files would go at once. Backups: tarballs in
  `~/Escritorio/BT2-backups/` before each big run.
- BT3 macros that define functions (`STG_LIST_GETTER(Name, ...)`) are now handled by transplant.build_file.
- Result: byte-identical with 2993 C files, 0x35838 / 0x287e80 = **8.26%**, 8400 functions left in asm.

## §16 (2026-10-10) Linker, m2c variants, permuter: 8.26% → 9.30%+

- **Linker**: binutils 2.40's ld is quadratic in the object count (link 10 min at ~4500 objects, ~56 min at
  5226: it looked hung). `game.toml [toolchain] linker = "/usr/bin/mips64-elf-ld"` (package mips64-elf-binutils
  2.47; `gamecfg.LINKER`, configure.py's `ld`): 4 s, output still byte-identical. The assembler stays 2.40.
- `m2c_sweep.py`: option variants (`--reg-vars saved`, `--descending-regs`, `--no-andor`), relaxed callee
  prototypes, `section(".data")` on externs the original reaches with %hi/%lo (else -G8 puts them on $gp),
  pointer steps in elements (`p += 4` on an `s32 *` → `p += 1`). +327 functions.
- `scripts/perm_sweep.py`: decomp-permuter (tools/decomp-permuter, needs `toml` in .venv) unattended on the
  m2c near misses, one thread and N seconds each, score-0 outputs fdiff-checked (tag `# perm`,
  `src/auto/perm_*.c`). First pass (≤10% differing, ≤120 insns, 60 s): 41 of 192.
- Agents (haiku, A/B/F on m2c near misses): ~50 functions for ~450k tokens: the scripts give far more per token.
  Their symbol-file comments containing `:` broke splat (rule added to the brief).
- Result before the permuter files: byte-identical with 3357 C files, 0x3c458 / 0x287e80 = **9.30%**.

## §17 (2026-10-10 night) New goal: C for the whole game, PC port like Tenkaichi3Decomp

The user's goal: a source reconstruction that builds a native PC port (no recompiler runtime, human-readable C),
like z3xox's Tenkaichi3Decomp (built on the ~99% matching BT3-Decompiled + a port/ platform layer). For BT2 the
matching decomp is at ~40% of functions / ~10% of bytes (the rest are big functions automation does not match),
so the port needs non-matching C proven equivalent by other means.

Tools (all unattended):
- `scripts/infer_protos.py` -> `scratch/protos/ctx.h`: every function's prototype from the original code
  (int/float args under the EE EABI, pass-through args propagated over the call graph, result = some caller reads
  v0/f0 after the call). Found because m2c drafts dropped pass-through arguments (func_00208DE8: a1/a2 shifted to
  a0/a1; looks "registers only", is wrong). Fixed bugs on the way: delay slot of jal runs before the call,
  callee clobbers caller-saved regs, `mtc1` writes its 2nd operand, R5900 3-operand mult.
- `scripts/m2c_sweep.py`: CTX_VARIANTS (m2c --context with the inferred prototypes, target mipsee, with and
  without the function's own prototype). Sample: OK 0 -> 8 of 160, compile failures 50 -> 36-45.
- `scripts/port_inplace.py`: the original ELF with C written over functions IN PLACE (linked at the original
  address, rest of the slot nops): every address stays, so data, pointer tables and the overlay keep working.
  2716 of 3667 game drafts fit (508 KB).
- `scripts/ps2_boot_test.py` + `scripts/pine.py`: PCSX2 (local build with PINE on TCP 28011, DebugServer on 21512)
  boots an ELF at unlimited speed; PASS = demo fight starts (gBtlScene 0x387700) and keeps changing. Original:
  PASS at 70 s. On failure it samples backtraces (suspect functions).
- `scripts/port_bisect.py`: group testing by boots (~2 min each): too slow for thousands of functions.
- `scripts/fn_diff.py`: function-level differential testing inside PCSX2: base savestate in the demo fight;
  for each F: breakpoint at entry, savestate, run the ORIGINAL to the return (bp on ra with same sp), read result
  register + 31 MB of RAM; reload, write the C over F, run to the same return, compare (F's own code and the
  stack frame below sp excluded; result register by the inferred return type). ~10 s per function, exact culprit.
  `--coverage N`: which candidates run within N s of the demo (547 of 2708).
- First results: 57 EQUAL / 9 DIFF of 76 checked.

Next: functions that never run in the demo need other entry points (menus, other modes: savestates there);
DIFF ones go back to fixing (m2c variants with protos, agents); the PC layer from Tenkaichi3Decomp's port/.

## §18 (2026-10-11) Hybrid PC build: native C inside the recompiled game

fn_diff over the 547 covered candidates: 367 EQUAL, 118 DIFF, 42 NOT REACHED, 17 NO RETURN, 3 CRASH.

The native C runs inside the PS2Recomp build, sharing guest memory, and replaces translations one at a time:
- Guest RAM at its own host addresses (third_party PS2Recomp patch 0011, `PS2X_IDENTITY_RDRAM=1`: mmap at
  0x10000, rdram == nullptr, `ps2RdramMissing()` instead of the 41 null checks). The first 64 KB can't be mapped
  on the host; the only reader, the SDK's kFindAddress (0x338388), runs on a shadow (`port/src/identity.cpp`).
  Boots to the title screen this way.
- `port/tools/gen_native.py`: draft -> clang -E -> Tenkaichi3Decomp's ptr32.py (4-byte pointers, PS2 layout) ->
  clang x86-64, non-PIE at 0x40000000; game data = absolute symbols at their PS2 addresses.
- Wrappers take EABI args from the context; `installNativeFunctions()` puts them in the runtime's function table
  (`replaceFunction`). Every jal goes through `dispatchGuestBranch` -> the table, so the recompiler's output does
  not change with the native set (first attempt skipped them in the recompiler: every change of the set = full
  ~2 h rebuild, since ps2_recompiled_stubs.h is included everywhere). Functions reached by a direct C++ tail call
  (`j`, 3166 sites) are left out.
- Call bridge, native C -> game function (`bt2g_<name>__<sig>` -> `bt2CallGuest`): EABI registers from the C's own
  declaration of the callee (the one ee-gcc compiled when fn_diff checked it; implicit ones from ctx.h), ra = a
  sentinel (8), then runs the recompiled code resuming from ctx->pc after every checkpoint until pc == sentinel.
  Functions only taken as an address (`&EftMod1CC_Update`) stay absolute symbols (the guest value).
- The runtime's guest threads are cooperative: blocking throws EeDispatcherTransfer and resumes by ctx->pc, which
  a C frame can't be. `scripts/callgraph.py --check`: only functions that never block (no syscall, no jalr, no
  runtime stub, transitively) go native: 206 of the 367 EQUAL; 202 generate. One that blocks anyway aborts with
  `[native] FATAL`.
- The C runs on a 16 MB MAP_32BIT stack (`bt2_stack_call`, CFI so exceptions can walk it): pointers to C locals
  fit in the 4-byte pointers.
- Bug caught on the way: the first "leaf" list had 0x18E030, whose C calls BtlTaskList_AddTail; as an absolute
  symbol that is a host jump into MIPS bytes.

Toward no runtime: once the set is large, threads become host fibers (no unwinding), the bridge then calls C
directly, and the PS2Recomp runtime shrinks to the Tenkaichi3Decomp-style port/ layer (gs, sound, pad, files).

First hybrid runs (2026-10-11 06:3x): 169 native functions installed; crash in PS2Runtime::reportMissingFunction
(read guest 0x0..: unmapped in identity mode; guarded). The missing target 0x3B7FA8 was the overlay:
`asm_ovl/` is gone from the master copy, so scripts/overlay.py found 0 functions from splat, rewrote the map
with only 13 overlay functions (data pointers) and the ~500 others lost their translation. overlay.py now keeps
the map's overlay rows when asm_ovl/ is missing; port/funcmap.csv restored (11700 rows) from scratch/funcmap.csv.bak.

Hybrid runs, cont. (2026-10-11 07-09h). Each crash was a class of bad draft that fn_diff can not see, now
filtered by gen_native.py (failed list with the reason):
- hardware access (0x2712B0 writes GS registers 0x12000000 directly): a host pointer there is unmapped;
- the draft's own path outside port/build/gen*: ptr32.py left its pointers 8 bytes (gDmaCur read as 64-bit);
  drafts are now copied under port/build/gen/src before preprocessing;
- `f()` declarations (parameters unspecified) taken as zero arguments: now the inferred count, or the call's;
- a callee given fewer arguments than it reads (m2c dropped a pass-through argument; on the EE the original
  register leaked through, so fn_diff said EQUAL): 76 drafts rejected (0x21FAA8, 0x1FD300...).
Result: 91 native functions, 45 run within 7 min, no crash. `BT2_NATIVE_SKIP=0xA,0xB` leaves some recompiled
(scripts/native_bisect.py halves the called ones by screenshots).
Title screen, then a flat gray screen from ~frame 340 on, frame for frame the same with and without natives
(identity mode), and also in normal mode (no identity, no natives): the recompiled build never loads the
attract demo after the title; a runtime gap, not the port. The natives do not change it.

Gray screen after the title (all modes) = PS2Recomp VU0 translator bug: `vclipw` built the CLIP flags with
-axis in the low bit of each pair and compared against w, not |w| (ps2xRecomp vu_translator.cpp). The game's
func_00145DF0 nudges a point by -80/+80 per axis by those flags until func_00145A80 (vclipw + cfc2 $vi18)
returns 0: swapped bits push it the wrong way forever (thread 1 READY at 0x146140, GS kicks frozen). Fixed:
bit 0 = x > +|w|, bit 1 = x < -|w|, same for y/z (the VU1 interpreter, ps2_vu1_upper.cpp CLIP, already did so).

2026-10-11 ~10:30. After the vclip fix the attract demo renders (stage floor, logo). Next crash, with and
without natives: func_00128EF0, `vsqi.xyzw $vf16, ($vi15++)` translated as store vf15 at vi16*16 in MAIN RAM
(segfault at 0x1B60 in identity mode; in normal mode it silently overwrote the EE kernel area). PS2Recomp
vu_translation_helpers.cpp: VSQI/VSQD had fs/it swapped (fs = rd is the vector, it = rt the address);
VLQI/VLQD/VSQI/VSQD/VILWR/VISWR addressed main RAM at vi*16 (or vi*4) instead of VU0 data memory
0x11004000 + (vi & 0xFF)*16 (+ field word for the integer ones). All fixed.
Agents batch 7 (U/V/W, haiku): 104 functions matched (U 24, V 52, W 27 + 1); gen_native.py now prefers an
agent's matching C over the m2c draft (one-function files only) and skips the ctx.h arity check for it; a
non-void C function without a return on some path is refused (clang does not keep the callee's v0).
137 natives (91 before).

2026-10-11 ~11:20. Demo crash in func_00266938: a guest read at address 0 (null pointer; on the PS2 it reads the
kernel area). Identity mode can't map the host's first 64 KB, so the runtime's fast paths (ps2_runtime_macros.h
Ps2FastRead*/Write*) now go through Ps2FastPtr(): rdram == nullptr && offset < 0x10000 -> g_ps2LowShadow
(ps2_identity.h, defined in ps2_memory.cpp; identity.cpp's kFindAddress uses the same shadow). Normal mode: same
code, the compare is false.
Batch 8 (equivalent C, port/eq/): P 30, Q 34 of 76; port_inplace.py --src-dir port/eq builds 66 of 80 in place
(14 larger than the original slot) -> build_port/eq/SLUS_214.41, objects for fn_diff.

2026-10-11 ~13:00. With the low shadow the demo no longer crashes (10 min, natives on, rc=timeout); it renders
the stage floor (no characters) and the EE stalls at ~538 s: cycle counter frozen, thread 1 "RUN" inside the
recursive tree walk func_0028DAA8 (children at +0x18/+0x1C). Checking whether natives matter (shadow1_off).
Batch 9 queue: lists 001-017 done (680 functions, 0 skipped) in port/eq/; 018-023 running.

Demo stall (all modes, ~500 s): func_002748B8's loop `for (i < s2->count)` with s2 = 0x0028E204 (a CODE
address; count read from code = huge). s2 = *(G+0x5C) + 4 * *(G+0x48), G = *(0x387AB0) (heap block). In PCSX2 at
the same point: G+0x5C = G (self), G+0x48 = 0x17874C -> s2 = 0x1519730 (heap). So G+0x48/+0x5C is corrupted in
the recomp: hardware watchpoint run (gdb, scratchpad watch.gdb) to catch the writer.
Watchpoint run 1 (G+0x48 out of range): never fired; at 560 s G+0x48 = 0 and G+0x5C = 0x0028DAD4, a code
address inside func_0028DAA8 (the recursive tree walk the native run hung in). So +0x5C is the corrupted field
(PCSX2: +0x5C = G itself). Run 2 watches writes of a code address (0x100000..0x400000) into G+0x5C.
Watchpoint run 2: the code address in G+0x5C is written by func_0028D968 (+646, called from func_0028DAA8):
0x0028DAD4 is the return address of 28DAA8's `jal 0x28d968`, i.e. an `sd ra` of a stack frame. The stack has
grown down into the heap: infinite recursion of func_0028DAA8, a BVH walk (node = arr + idx*32, visibility
test 28D968 -> 28D520, leaf test 28D260 = node+0x1C == -1, children idx at +0x18/+0x1C; entry 28DA48 with
arr = *(0x387D70) + 4 * a2[3]). The leaf test translates correctly (lw sign-extends). So the tree data differs
(a cycle), or a child index is read wrong upstream. PCSX2 does not call 28DA48 within 20 s of its demo fight
(the recomp is still on the title's 3D stage), so no direct comparison yet. Next: dump the recomp's tree at the
first 28DA48 call (gdb) and look for the cycle; then find who built that node.

2026-10-11 ~13:30. Batch 9 (equivalent C by haiku agents, port/eq/): 53 lists = 2120 functions written, 0
skipped. First verification round in PCSX2 (scripts/fn_diff.py --csv build_port/eq/fn_diff.csv): 1092 of the
first 1485 fit their original slot (port_inplace.py --src-dir port/eq), 178 run within 40 s of the demo; of the
104 that ran to their return, 93 EQUAL (89%), 10 DIFF, 1 CRASH. gen_native.py now takes verified port/eq C too:
186 native functions (137 before); 5 min run with natives, no crash.
Remaining work queue: lists 054-096 (agents), DIFF ones back to fixing, NOT REACHED ones need savestates
elsewhere (menus, fights), and the BVH recursion (func_0028DAA8) that stalls the recompiled demo at ~500 s.

2026-10-11 ~23:30. Batch 9 queue COMPLETE: every non-SDK function still in asm (3815) has equivalent C in
port/eq/<ADDR6>.c (3892 files incl. batch 8), written by haiku agents from docs/agents/b9/PROMPT.md +
PROMPT_EXTRA.md (lessons accumulated per list; lists shrank 40 -> 20 -> 10 -> 5 as functions grew to 400 insns).
Left for hand work: docs/agents/b9/manual_todo.txt (4 skipped: 0x2DD200 / 0x2DF0A0 bit-stream decoders,
0x2748B8 demo-stall loop, 0x2D7DA0 stack args; plus review notes).
Verification: port_inplace.py --src-dir port/eq (any m2c status) fits 2640 in their slots; the other 1227 are
linked at 0x90000 (port_inplace.py --far, fn_diff.py --far: C at FAR, `j FAR` at F's entry; still to confirm in
PCSX2 that 0x82000-0xFFFFF stays unused). fn_diff so far: 109 EQUAL, 10 DIFF, 1 CRASH, 83 NOT REACHED (8 s wait;
rerun those with a longer --wait). Most functions never run in the demo: savestates in menus/fights needed.

2026-10-12. Test build for the user: ~/Escritorio/BT2-test (double click BT2-test.desktop).
- raylib on SDL3 (PS2X_HOST_SDL3=ON: cmake/raylib_sdl3.cmake patches raylib 5.5's PLATFORM=SDL to SDL3, and
  raylib_sdl3_gamepad.patch fixes its SDL3 gamepad code: SDL3 opens pads by joystick instance ID and events carry
  the ID, raylib used indexes, so it opened js0 (keyd virtual pointer) and missed the Xbox pad on js1).
- PS2X_FULLSCREEN=1; Esc no longer closes the window (it is CIRCLE).
- release/bt2-launch.sh (env: BT2_NATIVE, BT2_LOG 0/1/2, BT2_SKIP_MOVIES, BT2_FULLSCREEN, PS2X_*_TRACE; logs in
  BT2-test/logs, ultimo.log), release/make_test_build.sh copies the current bt2 and updates VERSION/CHANGELOG:
  run it after every build that adds native C.

2026-10-13. Objetivo nuevo: BT2 al estado de Tenkaichi3Decomp (docs/PLAN_NATIVO.md: un solo hilo, capa plat_*
+ gs/ de BT3, sin PS2Recomp). scripts/bt3_names.py (cruce por bytes enmascarados contra el ELF de BT3) ->
build_port/bt3_names.csv: 2866 exactos (1072 sin ambigüedad), 1692 fuzzy; nombres adxf_*/CRI/SDK identificados.
CORRECCIÓN: el batch 9 no cubría todo. 1502 funciones del juego fuera del SDK (~866 KB) no tienen C en src/ ni
port/eq/: la cola se armó con las funciones que tenían borrador m2c; las que m2c no pudo (M2C_ERROR, jump table,
sin estado) quedaron afuera. 1416 tienen asm en asm/cod (extraído a scratch/m2c_sweep/<ADDR8>.s); 86 no
aparecen en asm/cod (probablemente dentro de rangos de src/ con otro nombre: lo dirá el enlace). Batch 10:
docs/agents/b10/ (195 listas, PROMPT.md, pista del C de BT3 cuando existe: 77).

2026-10-13 (etapa 3, enlace nativo). `port/tools/link_full.py` + `port/full/{mem.c,compat.c}` -> `port/build/full/bt2full`.
Comandos: `scripts/capped.sh 6G python3 port/tools/link_full.py` (regenera todo: obj2/, link.ld, stubs.c, tables.c,
report.json, link.log; tolera objetos nuevos) y `timeout 20 port/build/full/bt2full` (desde la raiz del repo).
- Entrada: 7659 objetos OK de build_full.py (el informe ya no coincide con "3512": ahora hay src/ + eq/ completos).
  8462 simbolos globales definidos; solo 2 duplicados (EftAura_Request/Stop en xb_17CE20 y xb_17D2D8; gana el primero
  por orden, se debilita el otro); ningun objeto define datos con nombre/direccion (los datos del juego son todos
  extern: el C no define D_XXXXXXXX), solo gOldPassMtIndex (.bss, sin direccion conocida) queda donde lo ponga el linker.
- Resolucion de indefinidos (9037 distintos; 8461 funciones canonicas con direccion): 51 alias (X = Y), 3552
  absolutos (X = 0xADDR; 3544 en el rango de datos >=0x33B5F8), 1199 stubs referenciados (juego<2D0000: 780, 2D0000-300000: 108,
  SDK 300000-33B5F8: 308, overlay: 2) + 1538 stubs extra solo en la tabla (todo inicio de funcion de funcmap sin C), 25 del host
  (libc/libm + helpers de port/full/compat.c: __divdi3, __muldi3, __floatdisf), 1 sin direccion (gVu0).
- Choques con el host: el C del juego define `malloc`, `free`, `kill`, `atan2f`, `sqrtf` y `main`; pisarian a libc
  del host. Se renombran a `game_X` en definicion y referencias (objcopy --redefine-sym).
- mem.c: memfd 32 MB en 0x10000, espejos 0x20000000/0x30000000, scratchpad, registros; PT_LOAD del ELF; `jmp rel32`
  en cada funcion (full_patch_range(lo,hi); el overlay 0x3B3100..0x421300 se parchea al cargarlo, aun no); pila de
  1 MB MAP_32BIT con makecontext; SIGSEGV con direccion + backtrace. Nativo en 0x40000000. _start (0x100008)
  solo pone bss a cero (hecho al cargar), llama dos funciones del CRT (0x338520, 0x32EEE0) y salta a func_00100388
  (NO a `main`=0x11A5F8 de los simbolos de BT3): se llama a esa con (0, argv).
- Exploracion (solo con variables de entorno, por defecto el primer stub corta con exit(3)): BT2_STUB_RET0=1 hace que
  los stubs devuelvan 0 (imprime cada uno la primera vez), BT2_STUB_ONE=a,b que a y b devuelvan 1.
  Primer stub: func_00321E50. Con RET0 + ONE=sceSifRebootIop,sceSifSyncIop: func_00321E50, sceSifInitRpc, sceCdInit,
  sceCdMmode, sceSifRebootIop, sceSifSyncIop, func_00100258, sceFsReset, func_00337C28, sceSifInitIopHeap, sceChk01,
  Dma_InitController, sceGsResetPath, sceGsResetGraph, Dma_SendGif, func_0032EB50, func_0032EAF0, func_0032ECA0,
  _malloc_r, __malloc_unlock, _free_r, func_0028AFA0, _memalign_r, func_00102360; luego SIGSEGV en func_002982E8
  (memset sobre puntero NULL: el malloc del juego devuelve 0 porque Heap_Create aun no tiene heap).
- Pendiente: heap del juego (malloc propio, BT3 Port_Malloc), capa plat_* (SDK/CRI), overlay (full_patch_range),
  paginas 0..0xFFFF del PS2 (inmapeables: accesos nulos del juego dan SIGSEGV informado), gVu0.

2026-10-13 (etapa 4, capa de plataforma `port/full/plat_*.c`). Resultado: `timeout 20 port/build/full/bt2full` ejecuta TODA la
inicializacion de `main` (0x100388) sin ventana, carga el overlay `BIN/DBZP.BIN` en 0x3B3100 y llega a `Progress_Main`
(0x3B7FA8, entrada del overlay); ahi se detiene (informe, exit 0) porque el overlay (507 funciones) no tiene C. 1 vsync contado
(Gfx_SyncField). NO se llega a logos/titulo: viven en el overlay. Decision pendiente: ver "Bloqueo".
- Comandos: `scripts/capped.sh 6G python3 port/tools/link_full.py` y `timeout 20 port/build/full/bt2full`. Variables nuevas:
  `BT2_SYSLOG=1` (syscalls sin implementar, WaitSema bloqueantes, RPC), `BT2_FILELOG=1` (archivos AFS/disco), `BT2_STUB_LOG=1`
  (stubs del juego que se llaman), `BT2_STUB_STRICT=1` (un stub del juego corta), `BT2_STUB_BT=1` (quien llama a cada stub),
  `BT2_MAXFRAMES=n` (corta tras n vsyncs), `BT2_DATA` (raiz de datos). `BT2_STUB_RET0/ONE` siguen valiendo para stubs de SDK.
- link_full.py: todo `port/full/plat_*.c` define simbolos "del host" (ganan a stubs y a cualquier C que defina lo mismo: se
  debilita el del objeto); `port/full/temp_stubs.c` define funciones DEL JUEGO sin C como DEBILES (las pisa el C real en cuanto
  exista); un indefinido cuyo nombre es otro nombre de la misma direccion que un simbolo del host se convierte en alias
  (p. ej. FlushCache = func_0032EEE0). Los stubs de funciones del juego/CRI (< 0x30C7B8 y overlay) ya NO cortan: devuelven 0
  (`full_stub_game`) y se listan en `port/full/TEMP_STUBS_AUTO.txt` (2178 funciones, 923 referenciadas, regenerado en cada
  enlace); los de SDK siguen cortando con exit(3). Los stubs devuelven ahora `long` (antes `void`).
- build_full.py: (a) quita del texto las esperas de hardware en asm MIPS `bc0f/bc2t` (Dma_WaitCond/Dma_WaitVu1; src/sys/dma_28B290.c
  no compilaba y arrastraba todo Dma_*); (b) ignora nombres raros en port/eq (hay 3 archivos `275FB8 00376AC0 00275FB8.c`
  de otro agente que rompian `int(p.stem, 16)`); (c) `--only` actualiza filas en vez de pisar report.csv.
  include/sys/dma.h: bajo `#ifdef PORT`, `D1_CHCR`/`D2_CHCR` pasan por `Port_DmaChcr(n)` (como BT3: la transferencia pendiente se
  completa al leer o escribir CHCR y el bit 0x100 baja; los datos se descartan). Los objetos con dma.h se recompilaron.
- plat_mem.c: heap del juego. El juego trae newlib en C (malloc/free/memalign) pero `_malloc_r/_free_r/_memalign_r` (sbrk) no
  tienen C: los sirve el host con un first-fit sobre [0x430590, 0x1EFE000) (D_43058F+1 .. fin que usa func_0028BA70), metadatos
  fuera de la RAM del PS2. TODO el reparto del juego va por memalign(0x40) + func_0028BAA8. No imita las direcciones exactas de la
  consola (si se quieren comparar volcados con PCSX2 habra que fijar la primera direccion; BT3 la leyo de un savestate).
- plat_syscalls.c (generado una vez del ELF, 138 envoltorios `li v1,N; syscall` de 0x32E840..0x32F0D0) -> `Port_Syscall(N,...)` en
  plat_sys.c: un hilo; CreateThread da ids, Start/Wakeup/Sleep no hacen nada, semaforos con cuenta (WaitSema sin cuenta no bloquea,
  lo avisa con BT2_SYSLOG), GetThreadId=1, FlushCache vacio, SetupThread/EndOfHeap con valores plausibles.
- plat_sys.c: sceSifInitRpc/RebootIop/SyncIop/LoadModule(func_00337C28)/FsReset/InitIopHeap/AllocIopHeap, sceCdInit/Mmode/Sync/
  Status, sceChk01 (*res=0, devuelve 0: main sale si <0 o *res!=0), BindRpc/CallRpc/CheckStatRpc (el bind responde al instante),
  GetTimerSystemTime, func_00331710 (printf del SDK: mudo). plat_gs.c: sceGs* vacios, sceGsSyncV = un frame (`Port_VBlank`:
  `gPortVBlanks++` y llama al handler de sceGsSyncVCallback), sceDma* completados, pad (scePad2Read: nada pulsado, palancas 0x80),
  tarjeta (sceMc*: -10 = sin tarjeta), sceSdRemote*.
- plat_file.c: BT2 lee por ADXF de CRI dos particiones AFS: `DATA/ZS2US_1.AFS` (ptid 0, 13234 archivos) y `ZS2US_2.AFS` (ptid 1, 32245),
  formato `AFS\0, n, {offset,size}[n]`, en sectores de 2048. Sustituidas las funciones del juego (nombres por direccion, identificadas
  leyendo port/eq/100708.c, 100C40.c, 100CB8.c, 100D58.c...): 0x2EA588 LoadPartitionNw(ptid,nombre,dir,info), 0x2EAFA8 GetPtStat,
  0x2EB9B0 OpenAfs(ptid,idx), 0x2EBB08 Close, 0x2EC0C8 ReadNw(h,nsct,buf), 0x2EC6B0 GetFsizeSct, 0x2EC990 GetStat, 0x2EF218
  ADXM_ExecMain. Los ids globales >= 0x33B2 son de la particion 1 (idx = id-0x33B2). OJO: bt3_names.csv NO sirve para estas (ADXF_*
  salen con 11-68 candidatos). Faltan por implementar (aun no se llaman): Seek/Tell/Stop, ADXF_Open por nombre, SFD (peliculas) y ADXT.
  E/S de disco del SDK: sceOpen/Lseek/Read/Close sobre gamedata (rutas `cdrom0:\BIN\DBZP.BIN;1`, sin distinguir mayusculas);
  un sceRead que cae en 0x3B3100..0x421300 llama `full_patch_range` (se reescriben los jmp del overlay). Ojo con el cargador: el C
  del juego pasa `MainMenu_StartBallLoops` (funcion nativa) como direccion de carga; `full_native_to_ps2()` (mem.c) la traduce.
- Funciones del juego a mano en temp_stubs.c (del asm, debiles): func_00100258, func_0028AFA0, func_0028BC08, func_00102360 + el
  fin controlado de func_3B7FA8. Detalle y las 25 de CRI alcanzadas en `port/full/TEMP_STUBS.txt`.
- Bloqueo / decision: el bucle principal es `Overlay_Load(0); Progress_Main (overlay) ; Battle_Main(0)`; sin C del overlay no hay
  menus, logos ni titulo, y llamar a Battle_Main sin batalla montada revienta (D_003876B4 nulo). Opciones: (1) pasar el overlay por
  la misma tuberia (asm_ovl se perdio; hay que regenerarlo con splat desde config/overlay/DBZP.yaml, 507 funciones, y m2c/eq);
  (2) un headless.c a la BT3 que monte una batalla de demo (necesita las funciones BattleSetup_* de BT2, que parecen estar en el
  overlay o sin C). Pendiente de SDK que se vera al avanzar: sceVu0* (matematica VU0, 40 funciones), __ieee754_*f, fptodp/dp*,
  sceMpeg*, sceIoctl, sceSifRegisterRpc/RpcLoop, signal/strtol/strtod de newlib (_r), DIntr/InitAlarm/InitTimer.

2026-10-13 (tarde). Etapa 4 llega al overlay: el build nativo corre main entero headless (IOP, SIF/CD, GS, heap,
ADX, AFS, pad, mc), carga DBZP.BIN y para en Progress_Main (0x3B7FA8), que no tiene C. Decisión: dar C al overlay.
scripts/bt3_names_ovl.py: sólo 19 exactos contra el DBZP.elf de BT3 (menús distintos). Batch 11
(docs/agents/b11/): 31 C byte-idénticos del overlay copiados a port/eq; 463 funciones en 81 listas; los agentes
trabajan desde ~/Escritorio/BT2-overlay-work (asm, borradores y fdiff del overlay), con `eq` como enlace a
port/eq. 13 funciones del overlay sin asm (0x3D6728.. de 8 bytes). Archivos sueltos de port/eq movidos a
~/Escritorio/BT2-backups/eq_stray/; 002621B8.c -> 2621B8.c.

2026-10-13. CORRECCIÓN de regla: en el EE `cvt.w.s` TRUNCA hacia cero y satura (PCSX2 pcsx2/FPU.cpp CVT_W:
`(s32)fs` si el exponente cabe, si no 0x7FFFFFFF/0x80000000). La regla de los batches 8/9 ("redondea al par") era
falsa. Corregida en docs/agents/BRIEF.md, b9/PROMPT.md, b9/PROMPT_EXTRA.md; ~100 archivos de port/eq que la
aplicaron (docs/agents/cvtw_fix_list.txt) se corrigen a `(s32)` (registro en docs/agents/cvtw_fix_done.txt).
El C nativo del PC debe además saturar: (s32) de un float fuera de rango en x86 da 0x80000000 siempre;
pendiente un helper ps2_cvtws() para los casos que puedan desbordar.

2026-10-13 (tarde 2). Corte por límite de uso: 3 agentes cortados (b10 059-060, b11 021-023, b10 061-062); se
relanzaron con lo que faltaba (list_059b, list_023b). Un agente nombró 27 archivos con 8 dígitos (003CD988.c):
renombrados a 6 (3CD988.c). Reglas acumuladas en docs/agents/b10/COMMON_RULES.md. 23 archivos con asm en línea
reescritos en C (docs/agents/asm_rewrite_done.txt). build_full: 8506/8535 OK (99,7 %); fallan 16 auto_33xxxx
(asm del SDK: los reemplaza plat_*), 6 de src/ con asm VU0/FPU (randf, vu0_a_c_c, xd_2111E8, xd_242948,
eft_t_c_1B58D0, xe_293BE0), 4 eq con tablas locales de punteros inicializadas (1061B8, 1E1328, 266950, 2874C0:
clang no hace addrspacecast en inicializadores constantes; reescribir a mano), 3 errores de backend (2DC8C0,
2DFFD8, 2E1558).

2026-10-13 (noche). Relleno temporal (docs/agents/FALLBACK_SPEC.md): bt2full corre las funciones SIN C ejecutando el C++ de PS2Recomp.
- Qué es: `port/full/recomp_shim.cpp` + `port/full/recomp_shim/` (R5900Context/PS2Runtime mínimos propios, copia de las macros de
  PS2Recomp con `cvt.w.s` truncando+saturando, rdram=nullptr/identidad). `link_full.py --fallback` (por defecto; `--no-fallback`
  vuelve a stubs y a func_3B7FA8 que corta) compila con g++ -O0 (BT2_FB_OPT=-O1) en `port/build/full/fallback/` (cache por fecha;
  ~20 min la primera vez, 2 procesos de 3 GB vía capped.sh) y enlaza. Lista: `port/full/FALLBACK_AUTO.txt`.
- El C nativo siempre gana: la tabla de relleno sólo tiene direcciones sin C. Recompilado -> otra dirección: si está en el relleno se
  llama directo; si no, adaptador de ABI al nativo (tabla full_funcs, a0-a3/t0-t3 -> rdi.., f12-f19 -> xmm0-7). Nativo -> sin C:
  adaptador asm generado en stubs.c (`movl $dir,%r11d; jmp bt2_fb_entry`). Llamadas C++ directas (saltos de cola) a funciones con C
  -> reenviadores generados (137). Un único contexto, pila del EE en 0x1FFEF00, gp=0x38BDF0. Saltos de cola con bucle de despacho.
- Extras: libc/libm del SDK con nombre conocido se mapean al host (envoltorios bt2l_*); eeCheckpointDue fuerza un vsync cada 2M
  chequeos (bucles de espera); timers T0-T3 (hilo del host en mem.c) para `func_0028C790`; servidor DTX (id 0x90000200) del IOP
  responde handle 1 en plat_sys.c (si no, SJX_Init falla y el juego se cuelga a propósito en 0x306BA8); pila de bt2full 8 MB.
- Informe (BT2_FALLBACK_LOG=1 imprime la primera ejecución de cada una; =2 también recompilado->nativo):
  1920 funciones por relleno: juego<2D0000 976, 2D0000-300000 85, SDK 300000-33B5F8 653 (libc/libm puras), overlay 206.
  Sin relleno (siguen como antes): 147 thunks de ps2_stubs de PS2Recomp (sceSif*, sceVu0*, malloc...) + 9 que no compilan (InitTLB...)
  -> SDK con stub que corta (229 referencias). Ejecutadas en 6000 vsyncs: 63 (juego 15, 2D-300 4, SDK 43, overlay 1: Progress_Main).
- Resultado: `BT2_STUB_RET0=1 BT2_MAXFRAMES=6000 port/build/full/bt2full` pasa Progress_Main (0x3B7FA8) y cuenta 6000 vsyncs headless.
  Sin BT2_STUB_RET0 corta en el primer stub de SDK (sceCdLayerSearchFile 0x31F088, luego 0x329198, 0x32F4B0, 0x32F5F0, 0x320678,
  0x32B820). Con 30000 vsyncs: bucle de espera en func_002A2420 (0x2A2698) y SIGSEGV en func_0026C7A8 (recompilada).

2026-10-14. Etapa 5 cableada: bt2full sin BT2_STUB_RET0 y con renderer (port/full/gs/*) en tres modos.
- link_full.py: `build_renderer()` compila gs/*.c + ui.cpp + imgui (cache en port/build/full/gs_obj; sin snd_adx/snd_se hasta etapa 6;
  BT2_NO_GS=1 los omite), enlaza SDL3. gs_sony.c (sceGsSetDefDBuff/Put/Swap) cuenta como capa plat_*. Las variables BT3_* del renderer
  se leen tambien como BT2_* (Port_GetEnv en gs_core.c). Capturas software: port/build/shots2/frame_NNNNN.ppm (BT2_SHOT=n);
  GPU: port/build/shots/gpu_NNNNN.ppm. gs_input.c: sin ventana vale el guion BT2_PAD=frame:boton,...
- plat_gs.c: DMA canal 1 (VIF1, cadena) y 2 (GIF) -> Port_GsVif1Chain / Port_GsGifChannel; sceGsSetDefLoadImage/ExecLoadImage reales;
  Port_VBlank con ritmo 59,94 Hz si hay ventana (BT2_PACED=1 lo fuerza, BT2_UNCAPPED=1 lo quita); Port_AspectMilli (BT2_ASPECT/WIDE/WINDOW).
  mem.c full_dma_addr(): el juego pasa a DMA direcciones & 0x0FFFFFFF; un buffer en la pila del host (0x4xxxxxxx) pierde el nibble alto.
- SDK nuevo: plat_sdk.c (sceCdLayerSearchFile+sceCdRead+sceCdSeek sobre gamedata, cache _sceSDC/_sceIDC & co, sceVibGetProfile, newlib _r
  (mbtowc/strtol/strtoul/strtod/setlocale/signal/raise), __ieee754_*f, __register_frame_info*, libdma (sceDmaSend/N/I/Recv*), libmpeg
  sin decodificador, vsprintf EE por direccion 0x329198 (va_list de ranuras de 8 bytes)); plat_mc.c (tarjeta de memoria = carpeta
  saves/card1, BT2_SAVES, adaptado de plat_mc.c de BT3; los nombres del C del juego func_002A.. son de BT3, las del SDK de BT2 son sceMc* en 0x31D248..).
- Peliculas: el juego usa el reproductor CRI Sofdec (mwPly*, func_002B4038...), no sceMpeg. TEMPORAL en plat_sdk.c: la pelicula termina al
  instante (GetStat=4). Hace falta reproductor real (etapa 6).
- Workaround TEMPORAL: func_002B24C8 (descompresor) reimplementada en plat_sdk.c; el llamador func_003BBEF8 (eq/clang) lo llama con rdx basura
  (0x18) en lugar de 0 -> SIGSEGV. Revisar el codegen/ptr32 de ese eq y borrar el override.
- Resultado: BT2_GS=1 y BT2_GS=gpu (GL y Vulkan, xvfb) muestran Spike, Atari, Bandai Namco, Sofdec/ADX y el texto legal; luego un fondo
  morado/azul con texturas mal (circulos azules a los lados, 3000 vsyncs) = pantalla tras los logos (titulo/menu) con texturas incorrectas: sin verificar.
  Memoria: el mensaje "No memory card" se pasaba con plat_mc.
- Pendiente: sceVu0* (matematica), sceSifRegisterRpc/RpcLoop, sceIoctl, DIntr/InitAlarm/InitTimer..., sonido, pelicula real, textura del titulo.

## 2026-10-14 - Revision of DISPLAY/DISPFB crop ("shifted left, black band right"): not reproduced, no code change
- The log's last values: DISPFB1/2 = FBP 0/0x70, FBW 8 (512 px), DISPLAY1 = 0x1bf9ff0203327c: DX 636, MAGH 4 (x5), DW 2559 -> 2560/5 = 512 px,
  i.e. the display area is exactly the 512x448 buffer. gs_core/gs_gpu/gs_gl never read DISPLAY/DISPFB: they show the draw target
  (gGsMainFbp) at full 512x448 (FBW*64 wide), scaled to the aspect rectangle. So there is no crop/DX offset to fix.
- Headless runs (BT2_MAXFRAMES=1000, BT3_SHOT=100) give full-width 512x448 frames (Sofdec/ADX logos centred, memory card dialog centred).
  Old port/build/shots/*.ppm (640 wide, FBW 10) and gpu_01200 (picture only in the top-left) are broken contents, not a display shift.
- If the band reappears, check the frame's FRAME.FBW/fbp (gs.frame) and the game's actual DX/DW, not the present code.

2026-10-14. Diagnostico del "cuelgue al pulsar Start" (BT2-test).
- NO es un cuelgue: el juego sigue vivo (gdb: SIGINT cae en el rasterizador software, vram_rw/draw_sprite, no en una espera). Tras (1,51) no hay mas
  lecturas porque ya esta en el menu de inicio; gColorFade avanza (flags=4 InDone) y func_003BAFE8 itera frames normalmente.
  Con BT2_GS=1 (rasterizador software) corre a ~9 fps (4200 vsyncs ~450 s), asi que parece colgado; con ventana/GPU no se ha medido.
- Secuencia observada (BT3_SHOT=150, ppm en <cwd>/port/build/shots2): Start -> dialogo "MEMORY CARD slot 1 / Do you wish to create a save file
  on the memory card (PS2)?" (Yes/No) -> con cross sobre "No": "Start a new game without saving?" -> pantalla de menu principal sobre fondo azul.
  El dialogo espera pad: el guion de la peticion (cross a 2400) llegaba antes de que apareciera (~2500). Frames: shots_png/sw_memcard_03000.png, sw_menu_04050.png.
- Proximo bloqueante: texturas/CLUT erroneas en el menu principal (banda verde plana con texto roto, circulos de los lados, fondo liso; los
  botones Yes/No del dialogo tambien con glifos rotos): formato de textura/CLUT (PSMT4/8?) o sampling en gs_core.c. plat_vu0.c/gs_core.c se
  conservan sin cambios (compilan; el binario es posterior). No se toco codigo en esta sesion.

## 2026-10-14 - Texturas rotas del dialogo/menu: causa = TEX0 truncado a 32 bits en func_0026E6D8/0026E310/0026E468 (eq)
- Causa: el constructor de paquetes de la UI (port/eq/26E6D8.c) declaraba func_0026E310 (devuelve s64: el TEX0 con CBP/CSA/TH en los bits altos)
  como s32 y pasaba el valor a func_0026E468 como s32 (q[4] = (u64)(s64)arg2): TEX0 llegaba como 0xffffffff99303000 / 0x25323000 (TW/TH/TCC/CBP/CPSM
  perdidos) -> texturas de tamano/CLUT erroneos (glifos rotos, banda verde, circulos, panel y botones ausentes en GPU). Arreglo: s64 en 26E6D8.c y
  26E468.c. Hay 40 funciones eq con retorno s64/u64 y ~50 prototipos de otros ficheros con retorno mas estrecho (lista en la sesion: 002E0A98,
  0014F0A8, 002D2750, 002F4D68... revisar si alguna devuelve valores GS de 64 bits).
- Reconstruir un eq: `python3 port/tools/build_full.py --jobs 2 --only <ADDR6>` (link_full.py NO regenera port/build/gen), luego link_full.py.
- GPU (xvfb, BT3_GS=gpu): frames 1800..2300 muestran dialogo de memoria con panel y botones, "Load successful" y el menu principal (Dragon Adventure /
  Dragon Tournament / Dueling) con fondo, texto y sprites correctos: shots_png/gpu_memcard_load_02000.png, gpu_menu_02200.png, gpu_menu_02300.png.
  El guion BT3_PAD (cross a 2200) avanza el dialogo: la entrada llega al juego. La ruta software usa el mismo gs_core (sin recapturar: ~9 fps).
- Entrada: teclado K=X, L=O, J=cuadrado, I=triangulo, Enter=START, flechas=cruceta (gs_input.c kActions); LEEME.txt tenia las teclas de la build PS2Recomp, corregido.
- gs_core.c: con BT3_GS_DUMP=<frame> ahora imprime tambien las escrituras TEX0/TEX2 y los TEX0 A+D/REGLIST. Visto: SIGSEGV intermitente (1 de ~4 arranques)
  en func_002EC6B0 al arrancar bajo xvfb, sin investigar.

## 2026-10-14 - titulo de ventana y centrado del cuadro 4:3
- Titulo de la ventana: "Dragon Ball Z Budokai Tenkaichi 2" (gs_draw.c; no hay mas cadenas de app id/icono).
- Vulkan (gs_gpu.c): el rectangulo del cuadro se centra con el tamano en pixeles de la VENTANA (SDL_GetWindowSizeInPixels) y se
  escala proporcionalmente al swapchain, en vez de centrar en el tamano del swapchain (en Wayland/KDE puede ir retrasado tras un
  resize y dejaba el cuadro a la izquierda con banda negra a la derecha). GL ya centraba bien (verificado en X11 y KDE Wayland).
- BT3_GS_VERBOSE=1 imprime "vk:/gl: present window ... -> picture WxH at (x,y)". Verificado: ventana 1194x896, resize a 1600x900
  (cuadro 1200x900 en x=200), fullscreen 1440x900 en KDE Wayland (1200x900 en x=120). Vulkan no presenta bajo xvfb (sin DRI3).
- En las pruebas: el selector es BT3_GS=gpu + BT3_GPU_API=gl|vulkan (BT2_GS=gl solo no basta con la ruta directa); SDL_VIDEODRIVER=x11 en xvfb.

## 2026-10-21 - Personajes negros en la pelea demo: causa = CLUT sin construir en VRAM (gs_core.c)
- Los fighters usan PSMT4 con TEX0.CBP=0x3C00+i. El juego arma esa CLUT con dos sprites 64x64 en el frame 0x1E0; gs_core.c solo escribia
  sprites en la memoria GS si la pagina destino ya tenia una subida (gGsPageGen != 0): la 0x1E0 nunca se sube, asi que iban al render target
  GPU y la CLUT quedaba a 0 (siluetas negras). Arreglo: sprites <=64x64 que leen una pagina subida se escriben en memoria GS aunque la destino
  no tenga subida (los buffers de brillo siguen a la GPU). Nuevas variables de depuracion: BT3_UPLOG=lo,hi, BT3_TEXLOG=<frame>, BT3_VU_SAVE=<dir>,
  BT3_VU_SKIP=<tam>; BT3_VU_DUMP ahora "desde ese frame". Los "vu1: unimplemented ..." no los usan los 4 programas cargados (no hay modelo MAC/status).
- Crash de la demo: func_0028C4B8 se llamaba sin argumento en port/eq/41A988.c (el asm pone a0=1); corregido. EftAura_SpawnFlame usaba un global
  inventado (gEftAuraCfg) en vez de D_0038777C; corregido. Prototipos corregidos en 21 ficheros (docs/agents/b12/verif_protos.txt).
- Pendiente: dialogo "Save data already exists" de la memory card no responde; videos (docs/PIEZAS_FALTANTES.md).

## 2026-10-21 - SIGSEGV (GP fault) en func_00405C98 al cargar partida: movaps sobre dato no alineado a 16
- Los arrays `extern u8 D[45]` / `s32 D[N]` que el eq copia con __builtin_memcpy: clang asume alineacion 16 (arrays >=16 bytes) y emite movaps;
  el dato real esta en 0x42D928 (alineado 8) -> fallo de proteccion general (SIGSEGV con si_addr NULL, si_code SI_KERNEL). Arreglo: `__attribute__((aligned(1|4)))`
  en la declaracion (405C98, 3C6CC0, 3C7AE8, 3EABC0, 3F4318, 412C18). Comprobacion: objdump de bt2full buscando movaps/movdqa con rip-relativo no alineado a 16.
- Ojo al desensamblar un crash: usar el binario con que se corrio (BT2-test/bin/bt2full), no port/build/full/bt2full (otro agente lo reenlaza).

## 2026-10-21 - SIGSEGV (addr 0x58) en func_00248708 llamada desde func_00405C98: argumentos a2/a3 intercambiados
- 405C98.c llamaba func_00248708(g+0x268, g+0x26C, g+0x260, g+0x25C); el asm (jal en 0x40687C, a2 en el delay slot 0x406880) pasa a2=g+0x25C (contador), a3=g+0x260 (puntero).
  El callee lee el puntero en a3 -> con los argumentos cambiados `in` era 0. Los otros 7 llamadores (24CF78, 3C6CC0, 3CFDD0, 3F0BF8, 4055B8, 412C18, 40B440) usan el orden correcto.
- Patron a vigilar: argumentos fijados en el delay slot del jal (Hex-Rays los pierde, y los agentes tambien).

## 2026-10-21 - Freeze (ADXF_OpenAfs(1,132962) en bucle) = retornos estrechos (s8/u8/s16/u16) leidos como s32
- func_00104570 pide el id de fichero x*2+0x3B16 con x = func_002085C8() que devuelve func_00241BE0() (def. `s16`, valor -1). clang devuelve un s16 con
  `movzx eax, word` (los bits altos de eax NO estan definidos en el ABI x86-64 para retornos estrechos) y el llamador, que lo declara s32, lee 0xFFFF
  en vez de -1 -> id 146196 -> func_00100ED0 reintenta para siempre (do/while hasta que abra) y el log crece (959 000 lineas).
- Arreglo en el origen: scripts/widen_narrow_returns.py cambia las 134 definiciones con retorno s8/u8/s16/u16 (src/** y port/eq) a `s32` con
  `return (T)(expr);` (backups en BT2-backups/narrow_ret). Los llamadores que declaraban s32 ya son correctos; los que declaraban estrecho tambien.
- Barrido general: scripts/check_decls.py compara cada declaracion con su definicion (RET_FLOAT, PARAM_FLOAT_*, PARAM_INT_WIDTH, RET_WIDE, RET_VOID_DEF,
  PARAM_INT_COUNT); informe en docs/agents/b12/check_decls_report.txt.

## 2026-10-21 - Camara de pelea: ChrCam_EndCut con offsets mal (1FCD80) + conversiones float->int que redondeaban
- port/eq/1FCD80.c (func_001FCD80 = ChrCam_EndCut) usaba p+0x150/p+0x148 en vez de p+0x2A0/p+0x298: al acabar un "corte" de camara (ataque especial) los flags
  (0x2A0, incluido 0x80 = HOLD) nunca se borraban -> ChrCam_Update seguia viendo "corte activo" y la camara quedaba fija en el atacante; ademas escribia 0 en
  obj+0x150 (yaw de camara) -> vista lateral al empezar la pelea. Corregido (agente de camara; docs/agents/b12/camara_fixes.txt).
- cvt.w.s del R5900 TRUNCA hacia cero (FCR31 sin modos de redondeo). 4 ficheros lo hacian a 'redondear al par' (macro CVT_W_S en 123530, 1AB510, 1B45E0 y
  1FC880; rintf en 3B5940): ahora `(s32)(x)`. Los demas CVT_W_S ya eran `(s32)`.
- HUD: falta el radar (agente ae07/af92 en marcha). Pendiente de probar: camara inicial detras del personaje, fin del corte de especial.

## 2026-10-21 (noche) - Copia limpia y respaldo completo para formatear el sistema
- Respaldo total: /mnt/datos/Proyectos/BT2-Port-FULL (42 GB). Copia limpia: /mnt/datos/Proyectos/BT2-Clean (BT2-Recomp sin artefactos, BT2-test, BT2-overlay-work). Entrada: docs/LEEME_PRIMERO.md.
- Build desde cero de la copia limpia: obliga a BT2_IRFIX=1 y al cache de objetos viejos (ver LEEME_PRIMERO sec. 8). Verificado: 9711 OK / 17 compile / 5 ptr32, link OK, arranque 2500 vsync.
- Agentes cortados a mitad (declaraciones/pila/radar) dejaron 8 ficheros port/eq rotos ("long long long", s64 mal puesto): revertidos a la ultima copia buena (originales rotos en BT2-backups/agent_botched).
