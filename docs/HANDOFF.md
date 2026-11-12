> **ACTUALIZADO 2026-10-21 noche: leer primero `docs/LEEME_PRIMERO.md`** (estado real, que falta, clases de bug, flujo de trabajo). Este HANDOFF es la version
> anterior del dia; donde difiera, manda LEEME_PRIMERO.md. Respaldo completo: `/mnt/datos/Proyectos/BT2-Port-FULL/`. Copia limpia de trabajo: `/mnt/datos/Proyectos/BT2-Clean/`.

# HANDOFF: retomar el port de DBZ Budokai Tenkaichi 2 (USA) en otro sistema

Actualizado 2026-10-21. Leer esto primero; el detalle historico esta en `docs/PORT_LOG.md` (686 lineas) y `docs/status.md`.

## Objetivo
Port nativo x86-64 de DBZ: Budokai Tenkaichi 2 USA (PS2, SLUS_214.41) como **C legible para todo el juego**, sin depender de
runtime recompilado (estilo Tenkaichi3Decomp pero para BT2). Idioma de trabajo con el usuario: espanol.

## Estado (2026-10-21)
- **Decompilacion a C equivalente (`port/eq/*.c`): COMPLETA.** Las 442 funciones que faltaban ya tienen fichero (6225 `.c` en `port/eq`).
  Cada una fue escrita por un agente a partir del asm MIPS (`scratch/m2c_sweep/<ADDR8>.s`) + Hex-Rays (`scratch/hexrays/f/`). Los logs por
  lista estan en `docs/agents/b12/done_NN.txt` (`0xADDR coincidencias/total nota`). La coincidencia de `scripts/fdiff.py` es baja a
  proposito (frames/registros distintos): NO indica error. La logica NO esta verificada contra el asm funcion por funcion.
- **Build completo** (`python3 port/tools/build_full.py --jobs 3`, 2026-10-21): 9708 OK, 18 `compile`, 7 `ptr32`.
  - 15 `src/auto/auto_*.c` + `src/battle/xe_293BE0.c` + `src/battle/eft_t_c_1B58D0.c`, `xd_2111E8`, `xd_242948`, `src/sys/randf_128580.c`,
    `vu0_a_c_c_128F30`: son los 22 `src/` con asm inline que no compilan para PC (conocido; el binario usa el fallback).
  - **Reales por arreglar (port/eq):** `port/eq/100008.c` (backend: "cannot lower memory intrinsic in address space 271" -> memcpy/memset
    de `__ptr32`), `port/eq/2D40B0.c` (declaracion sin tipos, ptr32 linea 33), `port/eq/2DF0A0.c` (`u8 * __ptr32 __uptr *` pasado a `u8 **`).
  - Detalle: `port/build/gen/full/report.csv`.
- **Tras el build NO se ha hecho todavia:** `python3 port/tools/link_full.py`, `check_protos`, test de 30 000 vsync, ni actualizar
  `BT2-test/bin/bt2full`. El binario de prueba en `BT2-test/bin/bt2full` es del 15-oct; el mas reciente esta en
  `BT2-test/bin/bt2full.new` (compilado 2026-10-20 21:44, antes de las ultimas ~30 funciones eq).
- Juego: llega a titulo, menu principal (Dragon Adventure / Tournament / Dueling) con GPU (GL y Vulkan) y software. Sin sonido real, sin videos
  (Sofdec no-op), SIF/SPU en stubs.

## Pendiente, por orden (el usuario pidio: primero decompilar, DESPUES crash y fixes)
1. Arreglar los 3 `port/eq` reales de arriba; `build_full.py` completo; `link_full.py`; `check_protos`; test 30 000 vsync; actualizar `BT2-test`.
2. Revisar dudas de agentes (ver abajo).
3. **Crash de la demo (attract)**: el overlay `func_003B9710` monta una pelea CPU-vs-CPU cuando el contador `O->0x4518` (O = D_004213B0) pasa de
   0x708. SIGSEGV en `func_00202DC0` <- BtlMember_GetActiveGauge <- ... <- Battle_Main (0x103000). Hay un guard temporal en
   `port/eq/1F3830.c` (EftVram_AddTex sin imagen) que hay que quitar al hallar la causa real. Notas: `docs/CUELGUE_DEMO.md`.
4. Fixes y juego: control del jugador, sonido, peliculas Sofdec, stubs SIF/SPU, `func_002B24C8` override, centrado Vulkan sin confirmar.
5. Integrar el overlay en el master y cortar la dependencia de `legacy-Proyectos-BT2-Recomp` (antes `~/Proyectos/BT2-Recomp`).
6. Los 22 `src/` con asm inline: reescribirlos como eq o dejarlos con fallback.

## Dudas de agentes (revisar)
- Funciones declaradas `void` cuando el original deja un `v0` residual (retornos "stale v0"); prototipos/aridad adivinados (marcados GUESS en
  `done_NN.txt`); constantes GIF de 64 bits decodificadas a mano; tablas folded desde jump tables.
- 256F10: ultimo `func_002984E0` se llama con a1=0 (el asm solo fija a0). 1C3208: omitido `bltz` de tamano negativo, `__fixunssfdi` modelado
  como 0 si x<=0, orden de args de `func_001C2878` distinto a Hex-Rays. 134BA0: ftoi/sqrt NaN sin saturacion. 1BE0D8: `Vec3_Scale(dst,src,s)`.
- 5 prototipos de 64 bits sin verificar: func_00115E70 a2, func_0012F178, func_00325370, func_00277E70, func_002814D0. Hay ~50 prototipos con
  retorno mas estrecho de lo debido (lista en PORT_LOG 2026-10-14). `docs/agents/b10/manual_todo.txt`, `b11/manual_todo.txt`.
- 28E330 (la funcion de 0x4420 bytes): 402 lineas, solo comprobada con fdiff (4009 instr), sin TODO.

## Estructura del arbol copiado
```
BT2-Port/
  BT2-Recomp/       repo principal (sin build/, .venv, scratch/ptest, shots, objetos)
  BT2-test/         build de prueba para el escritorio (bin/, gamedata/ 2.9G, scripts, saves, videos)
  BT2-overlay-work/ trabajo del overlay (>= 0x3B3100)
  ref/              BT3-Decompiled, Tenkaichi3Decomp(-src): guia de estilo y vu0_a.c / vu0_b.c
  legacy-Proyectos-BT2-Recomp/  repo antiguo PS2Recomp (ISO, gamedata.iso, asm_ovl): aun lo usan scripts del overlay
  extras/           INFORME, notas, backups, .desktop
```
Los scripts y docs mencionan `~/Escritorio/BT2-Recomp`, `~/Escritorio/BT2-overlay-work`, `~/Proyectos/BT2-Recomp`,
`~/Proyectos/BT3-Decompiled`, `~/Proyectos/Tenkaichi3Decomp`. En el sistema nuevo: o recrear esas rutas con symlinks, o ver
`docs/SETUP_NUEVO_SISTEMA.md`.

## Reglas de trabajo con el usuario
Responder en espanol. Maximo 4 agentes (sonnet para razonar/funciones largas). Trabajos pesados de uno en uno con
`scripts/capped.sh 12G <cmd>` (el PC casi muere por RAM). Sin commits salvo que los pida. Nunca tocar el repo antiguo. Cada informe:
tiempo restante, % restante y siguientes pasos. Tras un corte de limite no reanudar agentes: crear listas `_b/_c` con lo que falta y lanzar
agentes nuevos con briefs cortos. Evitar ediciones masivas con regex. Borrar = mover a `BT2-backups/`.
