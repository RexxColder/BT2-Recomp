# Plan: BT2 al estado de Tenkaichi3Decomp (2026-10-13)

Modelo: `~/Proyectos/Tenkaichi3Decomp` = C del juego compilado para PC + capa `port/src` (~11 k líneas:
plat_mem/file/mc/movie/mpeg2/sys/stub, gs/ = GS + VIF1 + **intérprete VU1** que corre los microprogramas
originales, snd_adx/snd_se, input, ventana de ajustes). Sin emulador, sin PS2Recomp.

## Qué cambia respecto del plan anterior
- **No hacen falta fibras.** BT3 corre el juego en un solo hilo: los hilos del EE en BT2 los crea el
  middleware CRI (0x2EE404..: 6 `StartThread`) y el SDK (pad/mc/sif). Al reemplazar CRI ADX y el SDK por la
  capa del port, la lógica del juego es un único hilo; esperar VSync = presentar frame. Las 5740 funciones
  "que bloquean" sólo bloquean a través de SDK/CRI.
- **El renderer es reutilizable casi tal cual**: es genérico (paquetes GIF, VIF1 UNPACK/MPG/MSCAL, VU1
  interpretado), mismo motor.

## Arquitectura del ejecutable nativo de BT2
1. Todo el C (`src/` matching + `port/eq/`) compilado con clang x86-64 + `ptr32.py` (ya probado en 1566+).
2. Datos: secciones .data/.rodata/.bss del ELF original cargadas en sus direcciones (identidad, ya funciona en
   el híbrido: `ps2_identity.h`, sombra de 64 KB). El código nativo se enlaza no-PIE en 0x20000000.
3. **Punteros a función**: en cada dirección original de función se escribe un `jmp rel32` x86 a su versión
   nativa (RAM mapeada RWX, código a <2 GB). Así las tablas de punteros del juego y los `(*(s32*)(p+0x58))()`
   funcionan sin reescribir datos. Al cargar el overlay DBZP.BIN se re-escriben los saltos de su rango.
4. SDK/CRI: nombres por cruce con BT3 (`scripts/bt3_names.py` → `build_port/bt3_names.csv`) y luego la capa de
   Tenkaichi3Decomp (plat_* + gs/ + snd_*) con esos nombres; lo que falte, stub que imprime y sale.
5. Bucle de trabajo igual que BT3: enlazar con stubs → correr → implementar el stub que aparece.
6. Verificación: el híbrido (PS2Recomp) y PCSX2 quedan como oráculo (fn_diff, comparación de RAM por frame,
   replay de pelea como BT3).

## Etapas
| # | Etapa | Hecho cuando |
|---|---|---|
| 1 | Nombres SDK/CRI/juego desde BT3 | bt3_names.csv revisado |
| 2 | Compilar todas las funciones nativas | lista de errores = 0 o justificados |
| 3 | Loader (ELF→identidad, jmp por función, overlay) + enlace con stubs | `main` corre hasta el primer stub |
| 4 | Capa plat_* de BT3 adaptada (mem, file, sys, mc, pad) | llega al título sin gráficos (headless) |
| 5 | gs/ de BT3 (GS+VIF1+VU1) | título y demo dibujados |
| 6 | Sonido (snd_adx/snd_se), video (plat_mpeg2) | intro y música |
| 7 | Demo/pelea completa, comparación contra PCSX2/híbrido | pelea jugable |
| 8 | Build de lanzamiento + C legible (structs/nombres de BT3) | |

## Pendiente detectado durante el batch 10
- **Prototipos inconsistentes**: callers pasan más argumentos de los que declara el C del callee (p. ej.
  func_00211310: 5 vs 3, func_00180440: 6 vs 2). En x86-64 los sobrantes se ignoran, pero si el callee REALMENTE los
  lee, su C está mal. Hace falta un `check_protos.py` como el de Tenkaichi3Decomp (declaraciones vs definición vs
  asm) antes de depurar el juego en serio.

## Adelantado mientras corren los agentes (2026-10-13)
- Hex-Rays (IDA 9.3, `scratch/hexrays/decompile_bt2.py`): pseudocódigo de 11 045/11 192 funciones del ejecutable y
  490/507 del overlay (cargado encima del ELF) en `scratch/hexrays/f/<ADDR6>.c`; los agentes lo usan como borrador.
- `port/tools/check_protos.py`: aridad de cada función según Hex-Rays vs llamadas en `port/eq` →
  `build_port/check_protos.csv`. **362 llamadas pasan MENOS argumentos de los que el callee lee (265 archivos)**:
  cola de corrección para agentes (ej. confirmado: 1B4278 → func_00129C28, ya estaba en manual_todo). Las 3450 "de
  más" son mayormente ruido (Hex-Rays no ve argumentos que una función pasa sin tocar a su callee).
- `build_port/sce_names.csv`: SHA-1 exacto contra `ps2-tool/sce_flat.txt` → 230 nombres SCE únicos (195 en el SDK,
  181 nuevos); 618 ambiguos (funciones chicas).
- Cobertura del demo (`build_port/coverage/auto_demo.txt`, 2497 funciones) → `docs/agents/b10|b11/prio_*.txt`.
- Renderer de BT3 preparado y compilando en x86-64: ver `docs/RENDERER_PLAN.md` § Adelantado.

## Relleno temporal (2026-10-13)
`bt2full` ejecuta las funciones que aún no tienen C con el C++ de PS2Recomp (`port/full/recomp_shim.cpp`). Es TEMPORAL: el C
nativo (src/ y port/eq) siempre gana, y la cifra de `port/full/FALLBACK_AUTO.txt` (1920 hoy) tiene que bajar a 0. Se apaga con
`scripts/capped.sh 6G python3 port/tools/link_full.py --no-fallback`; se mide con `BT2_FALLBACK_LOG=1` (primera ejecución de cada
función = qué C escribir primero). Ver PORT_LOG 2026-10-13 (noche).
