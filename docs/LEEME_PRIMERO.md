# LEER PRIMERO (para el Claude que retome este proyecto en un sistema nuevo)

Actualizado 2026-10-21 (noche). Usuario: habla español rioplatense (responder en español). Proyecto: **port nativo x86-64 de Dragon Ball Z: Budokai
Tenkaichi 2 (USA, PS2, SLUS_214.41)** como **C legible para todo el juego**, estilo Tenkaichi3Decomp, sin depender del runtime de PS2Recomp.

Orden de lectura: este fichero -> `docs/MEMORIA_CLAUDE.md` (reglas del usuario) -> `docs/HANDOFF.md` -> `docs/PIEZAS_FALTANTES.md` ->
`docs/SETUP_NUEVO_SISTEMA.md` -> `docs/PORT_LOG.md` (diario; las entradas de 2026-10-21 al final son las importantes).

## 1. Que hay y donde (respaldo en `/mnt/datos/Proyectos/BT2-Port-FULL/`)
| Carpeta del respaldo | Es | Notas |
|---|---|---|
| `home-Escritorio/BT2-Recomp` | **REPO MAESTRO** (era `~/Escritorio/BT2-Recomp`) | todo: `port/eq` (6.2k funciones en C), `port/full` (capa de plataforma + renderer), `src/` (codigo viejo m2c/Hex-Rays/BT3), `scratch/` (asm, drafts, shots), `port/build` (objetos, `bt2full`), `third_party/PS2Recomp` |
| `home-Escritorio/BT2-test` | build de prueba para jugar | `bin/bt2full` (binario), `gamedata/` (disco extraido, 2.9 GB), `jugar.sh`, `menu.sh`, `saves/`, `logs/` |
| `home-Escritorio/BT2-overlay-work` | trabajo del overlay (>= 0x3B3100) | `eq/` es un symlink a `BT2-Recomp/port/eq` (ojo al restaurar) |
| `home-Escritorio/{BT2-Recomp-decomp,Nueva carpeta,notas,BT2-backups,BT3-Decompiled-up,Tenkaichi3Decomp*}` | copias antiguas / referencias | `BT2-backups` tiene el estado previo de cosas que se arreglaron (narrow_ret, agent_botched, stray_eq) |
| `home-Proyectos/BT2-Recomp` | **repo ANTIGUO PS2Recomp** (ISO, `gamedata.iso`, `game.toml`, `build-recomp.log`) | NO modificar; el overlay y algunos scripts aun lo leen |
| `home-Proyectos/{BT3-Decompiled,Tenkaichi3Decomp,ps2-decomp-kit}` | referencias: BT3 decompilado con nombres, kit de decompilacion | guia de estilo + `vu0_a.c/vu0_b.c` |
| `claude/-home-rexx` | memoria y transcripciones de Claude Code | contexto historico completo (jsonl) |
| `config` | `bt2-test.env` etc. | |
Hay una segunda copia mas pequena (sin builds) en `/mnt/datos/Proyectos/BT2-Port/` (`BT2-Recomp`, `BT2-test`, `ref`, `legacy-...`): la de FULL es la completa.

### "El codigo recompilado" (ojo, son dos cosas)
1. **El C nativo** (`port/eq/*.c` + `src/**/*.c` + `port/full/*.c`): ESTE es el port. Se compila con `port/tools/build_full.py` + `link_full.py` -> `port/build/full/bt2full`.
2. **El codigo PS2Recomp** (MIPS->C++ traducido por el recompilador, `port/build/recomp/*.cpp`, 11 701 ficheros, y `third_party/PS2Recomp`, que tiene
   **modificaciones sin commitear** (45 ficheros, rama `bt2`): guardadas ademas como `patches/uncommitted/PS2Recomp_working_tree.patch` + `PS2Recomp_untracked_files.txt`).
   Rellena las ~700 funciones sin C propio (SDK libc/libm/etc.) y es el respaldo de `bt2full`. No borrar `port/build/recomp` ni `third_party/PS2Recomp`.

## 2. Como reconstruir y jugar (detalle en SETUP_NUEVO_SISTEMA.md)
```
cd BT2-Recomp
BT2_IRFIX=1 scripts/capped.sh 12G python3 port/tools/build_full.py --jobs 3     # ~10-25 min (BT2_IRFIX=1 es OBLIGATORIO, ver seccion 8)
scripts/capped.sh 8G  python3 port/tools/link_full.py                # -> port/build/full/bt2full
# una funcion:  scripts/capped.sh 8G python3 port/tools/build_full.py --jobs 2 --only <ADDR6> ; link_full.py
python3 scripts/fdiff.py port/eq/<ADDR6>.c                           # el eq compila? (matches bajos = normal)
cp port/build/full/bt2full ../BT2-test/bin/bt2full ; cd ../BT2-test ; ./jugar.sh   # juega en TU pantalla con strace + video + fps
```
Resultado esperado del build completo: `OK ~9700, compile 17, ptr32 5` (los 22 `src/` con asm inline que no compilan en PC; usan el fallback; ver 4).
Dependencias: clang/gcc, python3, SDL3, ffmpeg dev (libavformat/libavcodec/libswscale/libavutil), Vulkan/GL, xvfb (pruebas), systemd-run, rsync, gdb.
Rutas absolutas `~/Escritorio/BT2-Recomp` etc.: recrear con symlinks (SETUP_NUEVO_SISTEMA.md).

## 3. Estado (2026-10-21)
- **Decompilacion a C equivalente: COMPLETA** (6 225 `port/eq`). La logica NO esta verificada funcion a funcion: los bugs salen jugando. fdiff "N de M differ" alto es normal.
- **Juego**: titulo, menus, dialogo memory card, seleccion de personajes/escenario, **pelea 3D real** (personajes con textura, escenario, HUD de vida/ki/carga),
  **video de intro** (libavcodec, `port/full/plat_movie.c`) y **audio** (ADX/SE por SDL, `plat_snd_adx.c`, `plat_snd_se.c`; `docs/AUDIO_PLAN.md`) funcionan.
- **Herramientas de diagnostico**: `BT2-test/jugar.sh` (strace + `BT2_RECORD` mp4 + `BT2_FPSLOG`), `BT3_SHOT/BT3_GS_DUMP/BT3_TEXLOG/BT3_UPLOG`, `BT2_AUDIO_DUMP=wav`, `BT2_MC_LOG`, `BT2_STUB_LOG`.

## 4. Que FALTA / bugs conocidos (por prioridad)
1. **Radar del HUD ausente** en pelea (aparece un marco gris abajo a la derecha sin contenido). Agente cortado sin informe; ver `docs/agents/b12/radar_fixes.txt` si existe. Pistas: HUD en 0x10B000-0x115000 (`HudGfx_*`, `HudTeam_*`), comparar con BT3.
2. **Camara**: arreglado `1FCD80` (ChrCam_EndCut, offsets +0x2A0/+0x298; antes dejaba la camara fija tras el ataque especial y ponia yaw=0 -> vista lateral inicial). **Sin probar**. Si sigue lateral: `1F71B0` (reset del luchador, yaw en obj+0x150) y `1FB830`.
3. **"Posiciones malas" en peleas y glitches graficos** (reportados por el usuario, sin analizar): grabar con `jugar.sh` y mirar el mp4; candidatos: matrices/skinning (eq de animacion), VU1 ("vu1: unimplemented" al final del log), GS.
4. **Selector de escenario: fps se disparan** (sin analizar; `fpslog` en el log). En videos ya se limito la presentacion a 60 Hz (`plat_movie.c`); el selector puede ser igual (bucle sin esperar vsync).
5. **Sin verificar** tras reconstruir: crash en `EftMod1CC_Init` (arreglado `14F8E0`: bloque de pila de 0x40), freeze `ADXF_OpenAfs(1,132962)` (arreglado con retornos estrechos -> s32).
6. 22 ficheros `src/` con asm inline (15 `auto_*`, `xe_293BE0`, `eft_t_c_1B58D0`, `xd_2111E8`, `xd_242948`, `randf_128580`, `vu0_a_c_c_128F30`): reescribir como eq o dejar el fallback.
7. Overrides temporales: `func_002B24C8` (descompresor) en `plat_sdk.c`; guard de `1F3830` (EftVram_AddTex sin imagen); 9 funciones SDK del relleno C++ que no compilan (SIF/alarm/TLB, stubs).
8. Integrar el overlay en el maestro y cortar la dependencia de `~/Proyectos/BT2-Recomp` (repo antiguo).
9. Barridos de calidad **a medias** (agentes cortados): `docs/agents/b12/check_decls_report.txt`/`check_decls_high.txt` (880 hallazgos de ABI en prototipos: parametros f32 vs entero, 64 bits, retornos), y `check_stack_report.txt` (bloques de pila mas pequenos que lo que usa el asm). Ver `check_*_fixes.txt` para lo ya corregido. Scripts: `scripts/check_calls.py`, `check_decls.py`, `check_stack.py`, `widen_narrow_returns.py`.
10. Vulkan: centrado sin confirmar. SIGSEGV intermitente en `func_002EC6B0` al arrancar bajo xvfb (1 de ~4).

## 5. CLASES DE ERROR de decompilacion ya encontradas (buscarlas primero ante un crash)
1. **Argumentos fijados en el delay slot del `jal`** perdidos/cambiados (`41A988`: `func_0028C4B8(1)`; `405C98`: a2/a3 al reves). Hex-Rays y los agentes los pierden.
2. **`movaps` sobre dato no alineado a 16**: `extern u8 D[45]` + memcpy -> clang asume alineacion 16 -> SIGSEGV GP (si_addr 0, SI_KERNEL). Arreglo: `__attribute__((aligned(1)))`. Se verifica con `objdump | grep movaps` (ver PORT_LOG 2026-10-21).
3. **Retornos estrechos** (s8/u8/s16/u16): x86-64 no define los bits altos de eax; el llamador que declara s32 lee basura. Arreglo: definiciones a `s32` con `return (T)(x)`.
4. **Globales con nombre inventado** (`gEftAuraCfg` en vez de `D_0038777C`): el linker lo resuelve a otro simbolo. Usar siempre `D_<addr>` o un nombre de `config/symbols`.
5. **Prototipos de otra clase** (f32 vs entero, 64 bits, void vs valor): ABI x86-64 distinto al MIPS. `scripts/check_decls.py`.
6. **Bloques de pila/struct por valor** mas pequenos que lo que el asm copia (`14F8E0`: blk[48] vs 0x40).
7. **Offsets mal copiados** (`1FCD80`) y **cvt.w.s redondeado** en vez de truncado (R5900 trunca).
8. Un agente con regex masivos corrompio ficheros (`long long long`): NO hacer ediciones masivas por regex; siempre puntuales.

## 6. Flujo de trabajo pactado con el usuario
- El usuario **juega** (`./jugar.sh`) y avisa de crashes/bugs; el monitor (`Monitor` tool con `tail -F` sobre `logs/vivo/<fecha>.log`) avisa de señales/fps. Tu: log + `.strace` + mp4 -> causa -> arreglo -> `build_full --only` + `link_full` -> copiar `bt2full` a `BT2-test/bin`.
- No lanzar corridas automaticas largas ni "tours" de menu con guion de botones (perdieron 2 h). Para ver la imagen: `BT2_RECORD=<mp4>` o `BT3_SHOT=n`.
- Max 4 agentes (sonnet para razonar). Trabajos pesados de uno en uno con `scripts/capped.sh`. Sin git commits salvo que se pida. Nunca tocar `~/Proyectos/BT2-Recomp`.
- Cada informe termina con: tiempo restante, % restante, siguientes pasos. Tras un corte de cuota, no reanudar agentes: lanzar nuevos con briefs cortos.
- Borrar = mover a `BT2-backups/`.

## 7. Symlinks externos y datos que NO estan dentro del repo (importante al formatear)
- **La ISO del juego** (`DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).iso`, 3 GB) es un symlink a `/mnt/datos/Rexx/Descargas/Roms/PS2/BT2/` (el HDD de datos, NO el NVMe).
  `gamedata.iso` -> la misma ISO. Si ese directorio se pierde, no se puede regenerar `gamedata/` ni `BT2-test/gamedata` (2.9 GB, ya extraido y copiado en BT2-Clean/BT2-test/gamedata).
  Copia extra de la ISO: `/mnt/datos/Proyectos/BT2-Port-FULL/ISO/`.
- `BT2-Recomp/gamedata` y `BT2-overlay-work/{gamedata,tools/bin}` son symlinks a `~/Proyectos/BT2-Recomp/...` (repo antiguo, respaldado en `BT2-Port-FULL/home-Proyectos/BT2-Recomp`).
- `BT2-overlay-work/tools/{ee-gcc*,binutils,mwcps2*}` -> `~/Proyectos/ps2-decomp-kit/toolchain/` (compiladores EE: solo hacen falta para la decompilacion byte-exacta vieja, NO para el port nativo).
- `scripts/setup_symlinks.sh` recrea `~/Escritorio/BT2-*` y `~/Proyectos/*` apuntando al respaldo. Para resolver los symlinks relativos al repo antiguo,
  tras restaurar: `ln -sfn <ruta>/BT2-Port-FULL/home-Proyectos/BT2-Recomp/gamedata BT2-Recomp/gamedata` (y analogos).
- El port nativo en si (build_full/link_full) solo necesita: `port/eq`, `src`, `port/full`, `include`, `config`, `port/build/recomp`, `third_party/PS2Recomp`, `scratch/m2c_sweep` (asm de referencia) y `BT2-test/gamedata` para jugar.

## 8. REPRODUCIBILIDAD DEL BUILD (descubierto al hacer la copia limpia, 2026-10-21) - IMPORTANTE
`build_full.py` es INCREMENTAL por fecha (si `port/build/gen/full/obj/<clave>.o` es mas nuevo que el fuente, no recompila). En el arbol original hay objetos viejos
(del 13 oct) que la herramienta actual ya no sabe regenerar; una compilacion desde cero en un sistema nuevo dio 25 `compile` + 19 `ptr32` fallos en vez de 17 + 5. Causas:
1. **`BT2_IRFIX=1`**: sin esta variable de entorno, `gen_native.compile_c` no usa `irfix.py` y 8 ficheros (`port/eq/14EAE8, 182380, 243BD8, 24A9D0, 2690C0` ...) fallan con
   "cannot lower memory intrinsic in address space 271". **Siempre compilar con `BT2_IRFIX=1`**: `BT2_IRFIX=1 scripts/capped.sh 12G python3 port/tools/build_full.py --jobs 3`.
2. **14 ficheros con "changes address space of nested pointer"** (`src/auto/m2c_2B45F0, m2c_2BC0A8, m2c_2F59D8, perm_2ED758`, `src/battle/xf_2CDAB8`, `port/eq/2BBFF8, 2BDC28, 2C0448, 2C4470, 2DDDF8, 2EBF28,
   2F22F0, 2F6BE8, 2F8710`): `port/tools/ptr32.py` (modificado el 14 oct 22:20) es mas estricto que cuando se compilaron. Sus objetos buenos estan en
   `BT2-Clean/BT2-Recomp/port/build/gen/full/obj/` (copiados del arbol original) y en `BT2-Port-FULL/home-Escritorio/BT2-Recomp/port/build/gen/full/obj/`. **NO borrar ese directorio `obj`** (o regenerar
   arreglando esos 14 ficheros: declarar los `void **` como `u8 *`/`s32` o ajustar ptr32.py). Mientras estan en cache, el build da `OK ~9711, compile 17, ptr32 5`.
3. Los 22 `src/` con asm inline (17 compile + 5 ptr32 propios) no compilan nunca: el binario usa el relleno C++ de PS2Recomp (`port/build/recomp`).
4. La copia limpia (`BT2-Clean`) YA incluye ese cache (`port/build/gen/full/obj`) y verifica: build completo + link OK + arranque 2500 vsync sin errores.

## 9. BASE ACTUAL (2026-10-28): codigo del 23-oct 00:37 compilado con clang 23
- Los cambios del 23-oct por la tarde (reenvio de args, arity, emp, emp2; ~2300 ficheros) rompian la pelea. El arbol se
  reconstruyo al estado del binario que funcionaba (23-oct 00:37) con `scripts/restore_0037.py` (copias en
  `BT2-backups/pre_restore_0037/`). `scripts/bisect_0037.py PASADA [--files N0:N1] --apply` reaplica pasadas para bisecar.
- **Ese codigo depende de valores que sobreviven en registros** (args no pasados en C): solo funciona compilado con
  **clang 23** y **sin** `BT2_TRACE_BUILD` (la instrumentacion cambia los registros). Con clang 22 crashea en menus
  (`26F930`, `26F8B8`) y en colisiones (`StgCol_InitSegCtx`).
- Build: distrobox Fedora rawhide `bt2-old` (clang 23.1.4, ffmpeg 9): `export CPATH=/usr/include/ffmpeg BT2_IRFIX=1;
  build_full.py --jobs 4 && link_full.py` -> `BT2-test/bin/bt2full_c23` (corre dentro de `bt2-old`: `jugar_debug.sh`).
- 13 ficheros de la zona CRI con `void **` en punteros a funcion se ajustaron para `ptr32.py` (solo el tipo del cast;
  originales en `BT2-backups/pre_ptr32fix/` y `*.pre_ptr32fix`).
- Verificado: pelea J1 vs COM scriptada sin ventana, 3 min sin crash (`BT3_GS=none BT3_PADFILE=...`).
- Pendiente: el bug original de inercia en el hit-stun; bisecar que pasadas de la tarde son arreglos reales.

### 2026-10-29: arreglos de pelea y pendientes
- Arreglado 201F90 (bucle salteaba al ultimo luchador: CPU trabado en la reaccion con inercia) y 212820 ("puede actuar"
  invertido: no golpeaba con Cuadrado estando quieto). Respaldos en BT2-backups/*.pre_loopfix / *.pre_fix.
- Logging: plat_fightlog.c registra chr+0x48/0x4C/0x50 y 23BDA8 escribe ELIGE-ATAQUE (mascara y resultado).
- BT2_FPS=n fija el ritmo de vsync (jugar_debug.sh usa 30 por defecto).
- PENDIENTE crash en pelea (run 20261028-233119, vblank 3774): SIGSEGV en func_0025B738 llamado desde
  func_00273B80 <- func_002746C0 (dibujado), puntero nulo de la pagina cero del PS2.
- PENDIENTE: Gohan quedo cabeza abajo en un momento; doble especial sin probar.
- PENDIENTE crash (run 20261028-234014): SIGSEGV en func_00188850 desde BtlTaskList_Draw (dibujado de efectos).
- PENDIENTE especiales: nunca llaman a 201B90/201568 (AB0 siempre 0); BtlColl_Hit coincide con el asm. Log COLL-HIT
  agregado en 202AA8 para ver si los especiales llegan con tipo 2..4.
- Arreglado 273B80/2746C0 (faltaba el puntero a0 hacia 25B738: crash de dibujado en pelea). La version de la tarde del
  23-oct (BT2-backups/pre_restore_0037) ya lo tenia: esa pasada "eq" tiene arreglos reales para recuperar de a uno.
- 18A9C0: buffer de pila agrandado a 0x1000 con deteccion DESBORDE (el crash de efectos del especial no se repitio).

## Pendientes de la build (lista del usuario, 2026-10-29)
1. **Radar.** Restaurada la llamada 11A5F8 -> 11A3B0 (indicador de boton, grupo 0xF). El disco/flecha lo dibuja
   117488 -> 1172C8 -> 116A90 (coincide con el asm) con paquetes GS directos: 114728 dibuja un sprite (PRIM 0x116)
   que TOMA COMO TEXTURA el frame buffer (TEX0 TBP0 0x0000 / 0x0E00 segun la paridad D_003B0A84) y encima 114890
   (grilla), 114CB0 (puntos) y 114B10 (flecha, angulo de 20C108). Sospecha: limitacion del renderer GPU
   (gs_draw.c: "Not handled yet: a target sampled while it is being drawn to"), no del codigo del juego. Verificar
   con un volcado de las primitivas de ese bloque.
2. **Efectos de batalla.** Rectangulos grises semitransparentes en algunos golpes (efecto sin textura?), columna de
   caracteres en el borde izquierdo.
3. **Batalla completa funcional.** Especiales de ambos lados con impacto, sin crashes (crashes de dibujado
   arreglados: 273B80, 18A9C0 + 57 buffers de pila; seguir con COM vs COM: script en el scratchpad cvc.sh).
4. **Volver al character select / menu desde la batalla** sin que el menu se construya mal (arreglos B4 aplicados,
   sin probar).
5. **Probar todo el juego:** modo torneo, modo historia (Dragon Adventure), entrar y salir sin crash, y jugar sus
   combates. (El mensaje del usuario quedo cortado en "con los combates de la ...".)

### 2026-10-29 (cont.)
- Arreglado 41CD90 y 3E92E8: el m2c habia inventado simbolos (D_0042FAE8, D_00427AD4) leyendo mal `lui sX,%hi(D)` +
  `addiu sX,-0x28C`; eran D_0042FD74 / D_004279D4. 41CD90 crasheaba al salir de la pelea.
- Arreglado 2B0F78: argumentos invertidos a 2B0DB0 (crash al cargar la pelea del modo historia).
- B4 confirmado en COM vs COM: tras la pelea, ni la seleccion de personajes ni el menu principal arman su interfaz
  (la logica si corre: se puede elegir y arranca otra pelea). El juego manda 9 / 1 draws en vez de ~38.
  Biseccion automatica sobre los 1226 cambios de la tarde: scripts/bisect_b4.py (log en BT2-backups/bisect_b4/).
- Otro bug visual: el titulo de la lista de tecnicas en la pausa sale "$0Blast 1" (codigo de formato sin reemplazar).
- B4 RESUELTO: port/eq/29E6D0.c era `void` y el original devuelve el puntero (retorno perdido, clase C2). La biseccion
  (scripts/bisect_b4.py, 11 vueltas) lo aislo entre 1226 cambios. Probado: pelea -> Return to Versus Mode -> Dueling,
  seleccion, mapa y otra pelea, todo dibujado. Respaldo BT2-backups/29E6D0.c.pre_ret.
  Quedan 154 casos RET_USED_BUT_VOID listados en docs/agents/b12/check_calls_report.txt: candidatos a revisar uno a uno.
