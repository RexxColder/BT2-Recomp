# Investigación previa: recomps de PS2, metodología y deadlocks (2026-10-08)

Objetivo: port nativo de PC de **Dragon Ball Z: Budokai Tenkaichi 2 (USA)**, ejecutable `SLUS_214.41`
(no `.40`; el Greatest Hits usa el mismo serial; PAL `SLES_541.64`, JP *Sparking! NEO* `SLPS_256.90`),
por recompilación estática con PS2Recomp. No hay ningún decomp/recomp público de BT2 (búsqueda 2026-10-08).

## 1. Proyectos de referencia

| Proyecto | Juego | Qué aporta |
|---|---|---|
| [z3xox/BT3-Recomp](https://github.com/z3xox/BT3-Recomp) (clon de lectura en `research/BT3-Recomp`) | BT3 USA `SLUS_216.78`, **mismo motor de Spike** | El más avanzado: jugable, ~30 fps. VU1 traducido a C++, IOP nativo, HLE de `sdrdrv` (driver de sonido de Spike), bombeo de interrupciones, guardas de deadlock. |
| Tu `ps2-decomp-kit` + `DownhillJam-Decompiled` | THDJ `SLES_547.15` | La serie de parches 0001-0009, el método reproducible (`PORT_METHOD.md`), diff contra PCSX2 por DebugServer. |
| [KIexster/god-of-war-recomp](https://github.com/KIexster/god-of-war-recomp) | GoW `SCUS_973.99` | IRX originales en el intérprete R3000 (989snd, libsd); fix de cadenas DMA del scratchpad; parches ordenados sobre `c5a9d02`. |
| [InitialDad/PS2Recomp-WoS-Findings](https://github.com/InitialDad/PS2Recomp-WoS-Findings) | Way of the Samurai | Método: verificar cada hallazgo contra PCSX2 (snapshot diff), niveles de evidencia, registro de callejones sin salida. |
| Issues de Ridge Racer V en upstream (#257-#260) | RRV `SLUS_200.02` | Cuatro bugs genéricos del runtime/recompilador que cuelgan juegos (ver §3). |
| [phmdacosta/ps2recomp-workbench](https://github.com/phmdacosta/ps2recomp-workbench), Dark Cloud 2 (#121), DMC, UFE3, SH Origins/VCS | varios | Flujo ISO→ELF→Ghidra→C++; cuelgue esperando el inicio de un vídeo (DC2). |

## 2. Metodología validada (lo que se repite en todos los ports que avanzan)

1. **Mapa de funciones completo antes de traducir.** El fallo nº 1 de BT3-Recomp fue un análisis de límites
   de función truncado: funciones a las que sólo se llega por vtable (p. ej. el borrado de pulsos por frame
   en `0x158690`, vía `0x2C3910+0x18`) quedaron como código muerto. Recorrer vtables y tablas de punteros y
   declararlas como entradas (`PORT_METHOD` §7.1/§19; GoW hace lo mismo con "vtable-only virtual methods").
2. **Diferencial contra PCSX2 como oráculo.** Comparar RAM/registros en el mismo punto (DebugServer TCP 21512,
   MCP `pcsx2`, `tools/pcsx2_diff/` de THDJ). Ningún arreglo se acepta por "no crashea".
3. **Arreglar la causa sistémica, no el sitio del cuelgue.** WoS: cinco sitios de cuelgue eran síntomas de un
   solo fallo del asignador. Parchear sitios de espera uno a uno es la trampa.
4. **Cambios del runtime en parches numerados; cambios del juego tras un descriptor/overrides.** Nunca código
   generado en git; los pocos parches dentro del código generado van en un script idempotente que falla si el
   ancla no aparece (BT3 `apply_patches.py`).
5. **Regresión exacta para cambios de rendimiento** (tu `PS2X_VU1_RECORD`/`ps2x_vu1_replay`).
6. **Registrar los callejones sin salida** (WoS `dead_ends.json`) además de los pasos que funcionan.

## 3. Catálogo de deadlocks / cuelgues y estado en nuestro árbol

Estado frente a `third_party/PS2Recomp` rama `bt2` = `2c5fbb9` + parches 0001-0009 del kit.

| # | Causa | Síntoma | Fuente | Estado aquí |
|---|---|---|---|---|
| D1 | `D_ENABLEW` (0x1000F590) no se refleja en `D_ENABLER` (0x1000F520) | espera infinita al suspender el DMAC | upstream #257 (RRV) | **falta** → parche 0010 |
| D2 | Pilas de invocaciones asíncronas (INTC/DMAC/alarmas) solapan la pila del hilo principal (`0x01FFFFF0`) | `$ra` = 0, el bucle del juego "vuelve", `Exit` | #258 | **cubierto** por 0003 (pilas en RAM del kernel) |
| D3 | `GuestThread::stack` es base en `CreateThread` y tope en `SetupThread` | cálculos de extensión de pila erróneos | #259 | revisar al tocar D2 |
| D4 | Resume en el delay slot de un `b`/`beq $0,$0` incondicional cae por debajo en vez de saltar | el bucle principal sale y el juego termina | #260 (5/343 `b` afectados) | **falta** → parche 0010 |
| D5 | Thunk de función que sólo es `b target` emite `pc=target; return` | control perdido | #86 (cerrado) | comprobar en 2c5fbb9 |
| D6 | ABBA: hilo despertado tiene el mutex del objeto de espera y pide el de ejecución del guest; el que corre al revés | bloqueo total del host | BT3 `Kernel/Syscalls/Helpers/Runtime.h:24` | no aplica tal cual: desde #184 upstream usa un único `EeScheduler` (`Kernel/EeScheduler.cpp`) sin mutex global del guest; vigilar los cv propios (`m_vif1Cv` de 0009, colas GS de 0008) |
| D7 | ABBA en `sceMpegGetPicture` (hilo 5) | cuelgue en vídeo MPEG | BT3 `Kernel/Stubs/MPEG.cpp:1997` | relevante si BT2 usa IPU/MPEG para FMV |
| D8 | Un hilo del guest bloqueado no cede el *token* del planificador / el token se queda en un hilo muerto | inanición de todos los hilos | BT3 `game_overrides.cpp:1116-1136` | BT3 parte de antes de #184; en el `EeScheduler` el equivalente es un hilo que no vuelve al planificador (ver D9) |
| D9 | El driver CDVD espera en bucles anidados que nunca vuelven al `dispatchLoop`: el bombeo de interrupciones arriba del bucle no corre | lecturas que nunca terminan, carga infinita | BT3 `ps2_runtime.cpp:4008` (`PS2X_TICKPUMP`) | **probable en BT2** (mismo motor) |
| D10 | Lectura CD asíncrona que nunca señala "read complete" | minijuego de carga gira para siempre | BT3 `game_overrides.cpp:3496` | **probable en BT2** |
| D11 | Flag de reentrada puesto con set/clear manual alrededor de código guest que lanza `ThreadExitException` | flag atascado → estado de partición queda en 2 ("leyendo") | BT3 `game_overrides.cpp:1025` | regla: RAII en todo bombeo |
| D12 | Sólo se cuenta el timer T0; esperas de tiempo con T1/T2/T3 | cuelgue tras el banner de arranque | BT3 `ps2_memory.cpp:3482` (`PS2X_EETIMERS`) | **cubierto** upstream (#203: T0-T3 en `kEeTimerBases`, `ps2_memory.cpp:148`) |
| D13 | `MFC0 Count` congelado a 0 | relojes de middleware (Bink) parados | THDJ (sin commitear, para 0010) | **falta en la serie** → 0010 |
| D14 | `_sceSifSendCmd` aliasado a `sceSifSendCmd` (otro ABI) | respuestas SIF perdidas | THDJ (sin commitear, para 0010) | **falta en la serie** → 0010 |
| D15 | Audio de streaming: el guest espera crédito de reproducción mientras el host espera colchón que nunca llega | BGM sin arrancar / silencio | BT3 `ps2_audio.h:129` (`bgmstall`) | probable (sdrdrv de Spike) |
| D16 | Pool de nodos de stream que se pierde; canales L/R estéreo desincronizados | BGM muda o desfasada | BT3 `game_overrides.cpp:3064` | probable (sdrdrv) |
| D17 | Punteros a función en forma kseg0 (`0x8026cbc8`) no se encuentran en las tablas → intérprete sin `lq/sq` | carga colgada con `$ra` basura | BT3 `ps2_runtime.cpp:2165` (`[ksegfn]`) | **comprobar**: enmascarar `& 0x1FFFFFFF` en la búsqueda |
| D18 | Guarda de seguridad del runtime rechaza una carga legítima | render se para | WoS | regla: los guardas registran, no bloquean |
| D19 | Esperar que un vídeo "haya empezado" sin que el IOP lo avance | cuelgue en intro | upstream #121 (DC2) | relevante para FMV |
| D20 | Carrera EE↔IOP pendiente | — | `PORT_METHOD` §23 | abierta en THDJ |
| D21 | `_sceSifLoadModuleBuffer` enlazado al handler público: lee el IRX de la RAM del EE (el SDK pasa una dirección del IOP) y no escribe `*modres` | `main` vuelve y el juego sale (`sceChk01`) | **BT2**, `PORT_LOG` §6 | **abierto** |

## 4. Rendimiento: lo que ya funciona en BT3 y nos falta

- **VU1 traducido estáticamente** (`games/bt3/vu1_programs.json` + `ps2xRuntime/tools/gen_vu1.py` +
  `ps2_vu1_native.cpp`). En THDJ el 65 % del hilo del juego está en el intérprete de VU1. Es lo de mayor
  impacto para BT2.
- VIF/VU1+GIF en un hilo trabajador (`PS2X_ASYNC_KICK`), sin que el guest vea los DMA completarse al
  instante: tu 0009 es equivalente.
- Backends GS por GPU (OpenGL y paraLLEl-GS en Vulkan). El rasterizador por software basta para arrancar.

## 5. Plan para BT2

1. Disco: `SLUS_214.41` (copia propia del usuario) → `7z x`, `SYSTEM.CNF`, IRX en `IOP/`.
2. Bootstrap con el kit (`new_project.py`): split splat byte-idéntico. Es lo que necesita `funcmap.py`.
   Recorrer las vtables desde el principio (§2.1).
3. `sdk_names.py` → `recomp.py` → `port/` (CMake) con la serie 0001-0010.
4. Antes del primer arranque: aplicar D1, D4, D13, D14 (parche 0010) y revisar D6, D8, D12, D17.
5. Primer objetivo: logos y menú. Diff contra PCSX2 en cada cuelgue. Atajos: BT3-Decompiled y los
   overrides de BT3-Recomp (las direcciones cambian pero el motor no, así que se buscan por firma).
