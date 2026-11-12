# Bugs abiertos (BT2 native) — actualizado 2026-10-30
Escenario de prueba: Dueling, Goku vs Kid Gohan, Dying Namek. Preferido COM vs COM; ahora tambien J1 vs J2 con scripts
(BT3_PAD/BT3_PADFILE = J1, BT3_PAD2/BT3_PADFILE2 = J2) para sesiones identicas contra PCSX2.

| id | sintoma | estado | pista |
|----|---------|--------|-------|
| B1 | el oponente no conecta golpes | CERRADO (usuario, 2026-10-30) | |
| B2 | oponente golpeado queda en hit-stun con inercia | CERRADO (usuario, 2026-10-30) | |
| B3 | especiales: solo sale el primero, después ninguno | CERRADO (confirmado jugando, 2026-10-30) | sección B3 |
| B3b | el rayo queda en el aire y no impacta | CERRADO (confirmado jugando, 2026-10-30) | sección B3b |
| B4 | al salir de la pelea el menu no dibuja sprites | CERRADO 2026-10-29 (29E6D0 devuelve puntero) | |
| B5 | texturas de golpe: chispas/impactos como cuadrados duros | CERRADO (cld0-054839) | sección "Efectos de golpe" |
| B6 | crash Vu0Screen/Vu0Clip_StoreMtx (0xB0/0xF0): pelea COM vs COM y al cargar tras la Item Shop | arreglado 30-oct (29EE90 devuelve el paquete) -> reprobar | sección "CRASH Item Shop" |
| B7 | L2+Círculo / L2+Arriba+Círculo: crash al usarlo (sesión 20261029-212852) | CERRADO (confirmado jugando por el usuario, 2026-10-30) | sección B7 |
| B8 | el Ultimate del oponente nunca golpea al J1 | CERRADO (confirmado jugando por el usuario, 2026-10-30) | ver "MAPEO J1/J2" |
| B9 | los tres L2+Triángulo quedan colgados y bloquean el siguiente | CERRADO (confirmado jugando, 2026-10-30) | mismo origen que B3/B3b |
| B10 | técnicas de varios disparos (Gekiretsu Madan de Gohan niño): no disparaban / crash | CERRADO (confirmado jugando por el usuario, 2026-10-30) | sección B10 |
| B11 | crash al entrar a Opciones de Dueling | CERRADO (confirmado por el usuario, 2026-10-30): 402E58 desreferenciaba de más | sección B11 |
| B12 | Free Battle 5 vs 5: cuelgue con pantalla negra (índice de archivo basura) | NO REAPARECIÓ (usuario); sin verificar, puede volver | sección B12 |
| B13 | cielo/escenario corrompido con la preparación de la Genkidama ("Give Me Energy") | CERRADO de momento (usuario, 2026-11-06: no se ve) | sección B13 |
| B14 | rayos/bolas de ki de Ultimates no se ven viajar | WIP: objeto del rayo ya se crea; matriz NaN en 18A2C8 (ver "B14 — avance" y RETOMAR) | sección B14 |
| B15 | selección de mapa: falta la vista previa grande del escenario | WIP | sección B15 |
| B16 | choque de rayos infinito (acción 0xE0) | arreglado (20F9D8 pasa el estado) -> reprobar | sección B14/B16 |
| VB | vida baja (franja roja) y Max Power (bloques) | CERRADO (confirmado por el usuario, 2026-10-30): buffer de CLUT + AFAIL | sección CLUT |
| CH | chispas/partículas que quedan quietas en el aire | CERRADO de momento (usuario, 2026-11-06) | sección "Rayo largo y chispas" |
| BL | pantallas blancas (brillo aditivo) en Kamehameha/Masenko | CERRADO de momento (usuario, 2026-11-06) | sección B14 |
| B17 | nivel de poder: letras blancas al llegar al máximo | ARREGLADO, falta que lo vea el usuario | sección B17 |
| B18 | Ultimate Battle: se traba tras completar una misión | ARREGLADO, falta probar en juego | sección B18 |
| B19 | Ultimate Battle: 2.ª pelea = bloques de color y 7-10 s por cuadro | mitigado, falta probar | sección B19 |
| B20 | mapas que se rompen al empezar la pelea | CERRADO (confirmado por el usuario, 2026-11-06) | sección B20 |
| B21 | corrupción bajo el agua (rayas) | CERRADO (confirmado por el usuario, clase 12) | sección B21 |
| B22 | freeze de 10 s por cuadro tras un ultimate | ARREGLADO | sección B22 |
| B23 | UB: el mando se desconecta al cambiar la dificultad | CERRADO (confirmado por el usuario) | sección B23 |
| B24 | mapa del mundo: HUD del zeni roto | CERRADO (confirmado por el usuario, 2026-11-06): gs_gl.c, parámetros del shader reutilizados tras un pase nativo | sección B24 |
| B25 | mapa del mundo: rayas al cruzar el borde norte | WIP (a implementar): salto -300 en Z encontrado; falta función llamadora (ver RETOMAR) | sección B25 |
| TR | trabones progresivos (sesión 20261106-094032) | CERRADO de momento (usuario, 2026-11-06) | sección "trabones progresivos" |
| B26 | modo historia: el TEXTO del diálogo sale más abajo de lo que debe (el globo está bien, usuario) | WIP: texto del diálogo mal centrado (código del juego) | sección B26 |
| B27 | Maestro Roshi: falla en su Ultimate (síntoma a describir) | WIP: síntoma a anotar | sección B27 |
| B28 | Piccolo: falla en su Ultimate (síntoma a describir) | WIP: F9 del Ultimate en la sesión 20261106-152736 (según el usuario) | sección B28 |
| C1 | clase "arg perdido": thunks auto_*/m2c_* y llamadas `F()` sin args | corregido ~900 sitios | /tmp/emp.py (reenvio a0), fixfwd.py |
| C2 | clase "ret perdido": funcion void cuyo valor se usa (ej. 0029E6D0) | CERRADO: los 149 restantes son falsos positivos (ningún llamador lee v0) | docs/agents/b12/check_calls_report.txt |
| C4 | relleno PS2Recomp: código del JUEGO | CERRADO: 0 funciones del juego en el relleno (2026-10-30); queda biblioteca C/SDK | sección Relleno |
| C3 | UB: variables sin inicializar en perm_*.c | 6 corregidos | clang -Wuninitialized sobre port/build/gen/full/src/*.nat.c |

## 2026-10-23 B4: prueba con build de trazas (full_trace)
- Pelea COM vs COM (Goku vs Kid Gohan) -> pausa -> Return to Main Menu -> EXIT? Yes -> menu principal: el menu SI dibuja
  (titulo, items, caja de texto, botones). B4 NO se reproduce por esta ruta en el build de trazas.
- Pendiente: probar "Return to Character Select" y "Fight Again", y el build normal (sin instrumentacion).
- Nota de pruebas: el build de trazas va a ~9 fps; una pulsacion de 0.08 s se pierde. Usar 0.12 s en ese build.
- Para comparar menus: grabar con BT2_TRACE_FROM al llegar al primer menu, o BT2_TRACE_RING=67108864; el anillo por defecto
  (16M eventos) se pisa durante la pelea (20k eventos por vblank).

## Estado de ediciones (2026-10-23)
- Hecho: reenvio de arg0 en ~420 archivos (backups BT2-backups/m2c_pre_emp, src_pre_emp2), protos/retornos corregidos
  (ver docs/audit/*.md), perm_* sin UB (278D40, 1EDCB8, 2998B0, 2A4118, 3029C8, 2F2038), ultra logging
  (port/full/plat_trace.c, scripts/trace_sym.py), soporte J1/J2 en gs_input.c (SIN COMPILAR NI PROBAR).
- Pendiente: quitar dprintf de port/eq/26D6A0.c (original en BT2-backups/26D6A0.c.pre_dbg); probar build normal en juego;
  B1-B3 y B5 sin reprobar; entradas MEDIA/BAJA de docs/audit; hallazgos de particulas (port/eq/14FF78.c, 150990.c).

## B6 (antes anotado como B5) — crash intermitente en Vu0Screen_StoreMtx (29-oct); causa: ver "CRASH Item Shop"
- cvc-091058: señal 11 con arg0 = 0xB0 (puntero nulo + 0xB0), unos 2 min de pelea COM vs COM. No se repitió en cvc-092008 (7 min, 22184 frames).
- 29D920.c ahora ignora punteros < 0x1000 y anota `NULO Vu0Screen_StoreMtx arg0 .. desde ..` en el fight log (backup BT2-backups/29D920.c.pre_guard). Cuando aparezca, el "desde" dice qué llamador pasa la estructura nula.

## Radar — RESUELTO en el renderer (29-oct)
El juego dibuja el radar en un buffer de 128x128 en la memoria del z-buffer (FRAME = ZBUF = 0xE0, ZMSK=1, FBMSK=0)
cuando ya terminó el 3D, y después lo pega en pantalla (ALPHA 0x54, textura tbp 0x1C00). gs_draw.c descartaba las dos
cosas como "dibujar en / leer de la memoria de profundidad". Ahora:
- `zcolour`: FRAME == ZBUF con píxel entero (FBMSK 0) y ZMSK = dibujo de color normal; el target queda marcado ese frame
  y se puede samplear (se limpia en cada fin de frame, gs_gpu.c / gs_gl.c).
- Dibujo que samplea su propio target (el disco toma la imagen de abajo): draw nativo 6 = copia del color antes
  (sSelfCopy, Vulkan y GL).
Probado: GL offscreen, se ven disco amarillo, flechas y cono como en la referencia. Backups en BT2-backups/pre_selfcopy/.
Para regenerar shaders: glslang instalado en bt2-old, `python3 port/tools/gen_shaders.py` (build_full no lo corre).
Referencia: frames del video "DBZ BT2_ Ultimate Gohan 1v3 Duel" en BT2-test/referencia/.

## Efectos de golpe (chispas) — en curso (29-oct)
Comparando con la referencia (BT2-test/referencia/): faltan las chispas naranja/blancas con anillo en cada golpe.
- El juego SÍ las crea: func_001A5EF0 (spawner genérico) recibe tipos 0/3/4/8/0x10 durante la pelea, y la init de la
  tarea (1A55E0, descriptor D_00342560 = 1A5920 update / 1A55E0 init / 1A5A40 vacío en el original / 1A59A8 / 1A5A00)
  calcula escalas y texturas no nulas.
- El renderer no las descarta (contadores por sitio en BT3_GS_VERBOSE: solo pasadas de profundidad).
- Las chispas son partículas EftPtcl3 (1A5B60 -> EftPtcl3_Create). EftPtcl3_Draw se llama ~32000 veces en 30 s,
  ninguna oculta, shape 0 -> func_001BAD80 (tira PRIM 0x5C REGLIST, STQ, ALPHA 0x44/0x48). Cotejados con el asm y
  sin diferencias: 1A55E0, 1A5B60, 1267E8, 1BAD80 (paquete y color), 1BA518 (fundidos), 129D40.
- En el volcado GS del frame 7200 las tiras llegan con alfa de vértice 0; los logs de 1BA518 muestran alfas 5..41
  (escala 0..255) que bajan a 0 al apagarse. Falta: volcar justo el frame de un IMPACTO y ver la textura
  (tbp 2b00/2b10, PSMT4/PSMT8 con CLUT de alfa baja 0x00..0x16) y si el aditivo (0x48) se dibuja.
Logs temporales: EFECTO-1A5EF0 (1A5EF0.c), CHISPA-INIT (1A55E0.c), PTCL3-DRAW (src/battle/xc_1BC230.c), PTCL-COLOR (1BA518.c); backups .pre_log en BT2-backups/.
Pruebas en bin/bt2full_cvc (bt2full_c23 queda para el usuario).
- (29-oct, tarde) Disparador nuevo: `BT3_GS_DUMP=hit` vuelca el frame GS 2 frames después del primer IMPACTO
  (plat_fightlog.c pone gGsDumpOnHit, gs_core.c lo toma). Volcado cvc-114055 frame 8868.
- Hallazgo visual: en el momento del golpe aparece un CUADRADO OSCURO translúcido (~50 px, bordes duros) alrededor
  de la víctima, en lugar de la chispa. Es el mismo "rectángulo gris alrededor de los personajes" de la lista.
  Sigue con BT3_FX_OFF=31, así que no es un post-efecto del renderer: es un dibujo normal. Oscurece, así que no es
  el aditivo (0x48) de las partículas.
- Descartado: TBW=0 (el renderer lo trata como 1; 32x32 no cruza páginas), las tiras de partículas (alfa de vértice
  0..0x52, chispas con CLUT de alfa baja: normales), la sombra negra tbp 2b18, la niebla de profundidad (psm 1b).
- Siguiente: BT3_GPU_CUT=<frame>:<n> sobre el frame exacto donde se ve el cuadrado, para bisecar qué dibujo lo pinta.
- Log temporal nuevo: PTCL-QUAD (1BAD80.c, backup .pre_log).
- (29-oct, noche) Descartado por eliminación (BT3_SKIP_TBP, temporal en gs_draw.c): el cuadrado sigue sin las texturas
  2b00..2c00 (todas las de partículas), sin 2a20..2ab0 y sin 2bc0..2bec. No es una partícula ni un sprite de brillo.
  Tampoco son las tiras sin textura (son las barras del HUD). El volcado GS solo ve lo que entra por GIF: lo de VU no.
- Sonda por dibujo (temporal en gs_gl.c, BT3_PROBE_FROM=<frame> o tras el primer impacto): lee el buffer antes y
  después de cada dibujo y anota los que rellenan un recuadro de 20..160 px. Con todos los dibujos va a <1 fps.
- Buffer de paleta del GS (CLD) implementado en gs_core.c (clut_load / Gs_ClutRead / Gs_ClutHash): la paleta se copia
  al escribir TEX0/TEX2 con CLD, como en la PS2. Backups *.pre_clutbuf. Las paletas de efectos (2a00, 2a04: rampas de
  alfa) resultaron correctas; no era la causa. Se deja por ser lo que hace el hardware; revertir si algo empeora.
- Datos de las chispas sanos: color naranja (222,22,8), alfa 0..150, vida 6..17 frames.
- Nuevo: F9 o el archivo $BT2_DUMP_TRIGGER vuelcan el frame siguiente (cvc.sh: DUMPAT=<s> hace 8 volcados cada 2 s).
  El volcado imprime, por textura con paleta, TEX0/CLD y la paleta en hex (buffer y memoria) y cada carga de paleta.
- Visto en video: durante el Masenko el brillo de carga sale como rectángulo amarillo de bordes duros (misma familia).
- **PENDIENTE (aparcado 29-oct a pedido del usuario)**: cuadrado oscuro en los golpes y rectángulo del brillo de ki.
  Para retomar: acotar la sonda de gs_gl.c a los dibujos vu != 0 (camino VU, que el volcado GIF no ve) y cruzarla con
  el video en el frame exacto. Herramientas temporales que siguen en el código: BT3_SKIP_TBP (gs_draw.c),
  sonda probeOn (gs_gl.c, backup BT2-backups/gs_gl.c.pre_hitprobe), logs PTCL-*/EFECTO/CHISPA (backups .pre_log).
  Ver también Tenkaichi3Decomp/docs/port/README.md (contorno = rectángulo oscuro por alfa; BT3_GPU_CUT).

## B3 especiales que no se repiten — sesión del usuario user-205750 (29-oct, jugando a mano con logs)
- Ki blast (Triángulo): acción 0x88 dura 1 frame y vuelve a 6, pero en el video los disparos SÍ salen: 0x88 es solo el
  disparo. No es un bug.
- L2+Triángulo (Kamehameha, acción 0xAF): salió UNA vez (frame 2845, ELIGE-ATAQUE -> AF0018). Después, con la misma
  entrada exacta (acc 2D, mascara 063407C2, +48 00001100, +4C 00001000 = Triángulo recién apretado, flags0 00402003),
  23BDA8 devuelve FFFFFFFF (frames 3337, 4380, 5239, ...): decide con un estado que el log no muestra.
- El usuario vio que el disparo del Kamehameha queda en el aire después de terminar y no impacta. En toda la sesión no
  hubo COLL-HIT de tipo 2..4 (solo -99, golpes). Hipótesis: el proyectil no termina ni colisiona, el especial queda
  "en curso" y 23BDA8 no permite otro. Coincide con la nota vieja "especiales nunca llaman a 201B90/201568".
- Siguiente: leer 23BDA8 (y su equivalente en BT3/T3, combat.md: técnicas 0x105..0x132) para ver qué campo bloquea,
  agregarlo al ELIGE-ATAQUE y seguir el ciclo de vida del proyectil (creación, update, colisión, fin).
- También visto en esta sesión: chispas de golpe como rombos/cuadrados naranjas de bordes duros (ver PENDIENTE).
- **B3 RESUELTO (29-oct, noche)**: func_00212320 (índice de técnica 0..4 de la animación actual) probaba los bits
  0x04000000..0x40000000 sobre v = func_00217488 (la acción) en vez de sobre el resultado de func_001FA3A8 ($s1 en el
  asm). Devolvía -1 en toda técnica; func_00231300 hace `gauge[0x30 + idx*4]++` y con -1 incrementaba gauge+0x2C,
  que 23D4E0 / 23D9D0 / 23DAE8 / 1F8420 / 225FF8 leen como "no se puede usar técnica". Encontrado con un watchpoint por
  software (mem.c bt2_watch_byte, BT2_WATCH2C=<chr>). Arreglado en port/eq/212320.c (backup BT2-backups/212320.c.pre_b3fix).
  Probado con scripts/p1.sh (scratchpad): Kamehameha sale en 6049, 7317, 8407; gauge+0x2C queda en 0.
  212320 la usan también 235F38 y otros: costo/contadores de técnicas ahora usan el índice correcto.
- PENDIENTE B3b: el rayo del especial queda en el aire y no impacta (ningún COLL-HIT tipo 2..4 en las sesiones).
- Herramientas temporales nuevas: logs TECNICA-ESTADO/TECNICA-PASOS (23BDA8.c, backup .pre_b3log), B3 MARCA/BIT2
  (235F38, 22C9B8, 224130, 21C5F8; backups .pre_b3log), watchpoint en mem.c (backup mem.c.pre_watch).
  Script de prueba 1P vs COM con L2+Triángulo: scratchpad p1.sh (1P VS COM es la primera opción de Dueling).

## B3b RESUELTO (2026-10-29): los rayos/técnicas no impactaban

- Síntoma: el rayo (Kamehameha) quedaba en el aire y nunca registraba impacto (ningún COLL-HIT tipo 2..4).
- Camino: 11B3C0 (pase registro vs luchador) -> prueba por kind (tabla D_0036CBD0: 0->11ADA0, 1->11AF68,
  2..6->11B138 que en el original es `return 0`) -> 11AF68 -> ColSphere_SweepSphere (0x293DD8).
- Causa: ColSphere_SweepSphere corre desde el recomp (fallback), no desde src/battle/xe_293BE0.c. El traductor de
  PS2Recomp emitía SQRT.S con el campo fs; en el R5900 el operando va en ft. Calculaba sqrt(qb²) en vez de
  sqrt(disc) -> t = (-qb - |qb|)/qa = 0 siempre -> el llamador hacía la prueba estática y fallaba por distancia.
- Arreglo: third_party/PS2Recomp/ps2xRecomp/src/lib/fpu_translator.cpp: SQRT.S usa ft; RSQRT.S = fs/sqrt(ft).
  Backup: BT2-backups/fpu_translator.cpp.pre_sqrtfix (+ ps2_recomp.pre_sqrtfix, libps2_recomp_lib.a.pre_sqrtfix).
  El binario corregido del traductor está en el scratchpad (recompbuild/ps2_recomp); no hay cmake/ninja en los
  contenedores, se recompiló a mano solo fpu_translator.cpp (ver historial de la sesión).
- Regeneración controlada: se regeneró todo en un directorio aparte con el traductor viejo (idéntico a
  port/build/recomp -> reproducible) y con el nuevo: difieren 59 archivos / 110 líneas, todas FPU_SQRT_S.
  Solo esos 59 se copiaron a port/build/recomp; originales en BT2-backups/recomp_pre_sqrtfix/.
  De esas, hoy corren desde fallback 0x293DD8, 0x293C60 y 0x2429D8 (el resto tiene C nativo).
- Verificado: run p1-204612: SweepSphere da t≈0.98; 3 COLL-HIT tipo 2 de J2 sobre J1 con resultado 1; sin crash.
- Logs temporales B3B todavía en port/eq/11B3C0.c (backup .pre_b3blog) y port/eq/11AF68.c (backup .pre_b3blog).

## Lista de auditoría (2026-10-29, subagentes de solo lectura; reportes en el scratchpad audit_*.md)
Atacar de a uno, con backup y prueba cada uno:
1. HECHO: SQRT/RSQRT en el traductor (arriba).
2. HECHO (2026-10-30, backup BT2-backups/11FFD0.c.pre_typo; prueba p1-210204 sin crash, 13139 frames; las
   condiciones no tienen log, así que su efecto no está medido directo): port/eq/11FFD0.c líneas 305-326: llamadas a func_0011F78/F88/F98/FA8 (falta una F) -> stub que devuelve 0;
   condiciones 119-126 de la IA del CPU nunca se cumplen. Declaraciones (líneas 27-30) correctas.
3. HECHO (2026-10-30, backup BT2-backups/200680.c.pre_angfix; prueba p1-210916 sin crash, 11436 frames, 16 COLL-HIT
   tipo 4; la rama no tiene log): port/eq/200680.c: rama del chequeo de ángulo invertida (asm 0x2006FC-0x20070C: si |w| < D_0038589C -> return 0).
4. HECHO (2026-10-30, backups BT2-backups/3C1B90.c.pre_name, 3E4CF8.c.pre_name; stub eliminado de stubs.c;
   prueba p1-211743 sin crash, 15461 frames): port/eq/3C1B90.c y 3E4CF8.c llaman EftShotFx_Update_002494A0 (no existe) en vez de EftShotFx_Update_2494A0.
5. port/eq/206450.c: redondeo al par en vez de truncado (cvt.w.s del EE).
6. Herramienta: link_full.py debería avisar de full_stub_game con dirección < 0x100000.

### Nota (2026-10-30): el scratchpad de la sesión se vació
- Se perdió el binario corregido del traductor (recompbuild/ps2_recomp) y los árboles recomp_old/recomp_fix. Lo que
  importa está en el proyecto: la fuente corregida (fpu_translator.cpp) y los 59 .cpp ya copiados a port/build/recomp.
- Para reconstruir ps2_recomp sin cmake/ninja (dentro de bt2-old): compilar ps2xRecomp/src/lib/fpu_translator.cpp y
  src/runner/main.cpp con los -I de out/build/compile_commands.json (cambiando /home/rexx/Escritorio/BT2-Recomp/third_party
  por BT2-Clean/BT2-Recomp/third_party), `ar d` + `ar rs` del objeto en una copia de libps2_recomp_lib.a (NO hacer `ar x`
  antes: pisa el objeto nuevo), y enlazar main.cpp.o + lib + libfmt.a + libdwarf.a + /usr/lib64/libz.so.1 +
  /usr/lib64/libzstd.so.1 + librabbitizer.a. Regenerar siempre en un directorio aparte y comparar antes de copiar.
- Los scripts de prueba ahora viven en BT2-test/pruebas/ (p1.sh). cvc.sh se perdió; rehacerlo ahí cuando haga falta.

## CRASH Item Shop -> carga (sesión del usuario 20261029-211303, 2026-10-30)
- Señal 11 en Vu0Clip_StoreMtx con dirección 0xF0 (Vu0Screen_StoreMtx con 0xB0) desde func_002729D0 (dibujo del
  escenario), en la pantalla NOW LOADING después de la Item Shop.
- Causa: port/eq/29EE90.c Vu1Pkt_LoadProg8 estaba declarada void y no devolvía el paquete; el original deja el
  resultado de Dma_Alloc(0x140) en v0 hasta jr ra. 2729D0 usaba basura del registro de retorno (a veces 0).
- Arreglo: devuelve u8* (return v). Backup BT2-backups/29EE90.c.pre_ret.

## B7 — crash al usar L2+Círculo (sesión del usuario 20261029-212852, 2026-10-30)
- Señal 11, dirección 0x40, en func_00174A70 llamada desde EftTechEvtTask_UpdateNormal (0x174598).
- Causa: en la rama con el flag +0x18 activo, el original toma la tabla de halfwords de *(*(arg0) + 0x20)
  (delay slot `lw a2,32(s0)` en 0x174A90, antes del bnez); el C de port/eq/174A70.c usaba el parámetro arg2,
  que el llamador no carga -> 0 -> lh en 0x3E/0x40 -> crash.

## B10 — especiales de varios disparos no disparan (usuario, 2026-10-30)
- Los ultimates (L2+Triángulo) ya funcionan. Fallan las técnicas que disparan varias ondas de ki en un solo ataque:
  animación de disparo sin proyectiles, sin daño, y la técnica dura más de lo normal. Algunos otros especiales no
  funcionan o rompen el juego.
- Pistas (doc T3, effects_stage.md): tipos de efecto de técnica 1 volley, 2 shots, 4 ring shot (`EftRingShot*`,
  hasta 20 objetos blast en anillos o volea, usa BtlScene_RandF y reinicia el timer de la técnica), 5 multi.
  El final de la técnica lo marca el efecto con los held flags 0xA8/0xA9; si el efecto no corre, el handler
  espera su tope de 150 frames -> "tarda más en terminar".
- Personajes donde se ve (usuario): Androide 19 y Vegeta sin Scouter, no la versión Scouter (técnica exacta sin precisar); Gohan niño con L2+Arriba+Triángulo.
- REPRODUCIDO (2026-10-30): BT2-test/pruebas/tec.sh con MODO=train J1=right CMD="l2 up triangle" (Ultimate Training ->
  Practice, ki lleno, Gohan niño vs Gohan niño) -> run gohan-tr-l2ut-223120. Sale "Gekiretsu Madan": cielo oscuro, pose ~3 s,
  cámara a la loma ~3 s, NINGUNA onda visible, sin daño; luego la pelea sigue. Ojo: en ese log "J2" = el jugador
  (chr 017E7550) y "J1" = el COM. Los únicos registros de proyectil (kind 1, 2 COLL-HIT tipo 2) son de otras técnicas.
- Pendiente: reproducir con un personaje concreto y ver qué tipo de efecto usa y si se crean objetos blast.
- AVANCE (2026-10-30, logs B10 en 148670.c / 191600.c / 1F49E8.c, backups .pre_b10log):
  - El Madan es la acción 0xAD del jugador (340 frames). En ese tramo NO hay SHOT-PIDE (func_00148670) ni
    EftBlastObj_Create. En la misma pelea el Masenko (0xAC, slot 2, tipo 53) sí pide disparo y dispara.
  - Tabla de acciones BT2: D_003438E0, 16 bytes/acción (enter, run, decide, leave). 0xAC/0xAD/0xAE (clases 2/3/4)
    comparten 0x231300 / 0x2314F8 / 0x231B58 / 0x231C90 -> la diferencia depende de datos de la técnica.
  - 2314F8: switch por animación - 0x11C (clases separadas 0x22); caso 3/37/71 = bucle de disparo con tope 0x97
    (por eso "tarda más"); caso 2/36/70 lanza el disparo vía func_00230D30 / func_002310B8.
  - func_001F49E8 / 1F4308 (tareas por id 0x28E..0x297) coinciden con el asm y no se usan en estas técnicas.
  - Comparación detallada de la cadena de disparo delegada a un agente de solo lectura -> BT2-test/pruebas/audit_b10.md
- CAUSA HALLADA (agente, verificada): port/eq/231300.c (enter de 0xAC/0xAD/0xAE) llama func_00206958(o, 0) en las tres
  ramas; el original pasa 1<<53 / 1<<54 / 1<<55 (li a1,0x8000; dsll32 a1,a1,6/7/8 en 0x2313A8 / 0x2313D4 / 0x231418).
  func_00206958 hace *(u64*)(o+0x338) |= a1; func_00204478 (cada frame, desde 0x20699C) toma el bit más alto de 51..55
  como nivel y solo entonces llama func_00147FE8 -> func_00148670 (pedido de disparo). Sin el bit 54 el Madan nunca
  dispara. m2c perdió la constante (el .c generado también tiene 0). Ninguna otra llamada a 206958 en port/eq pasa 0.
  Pendiente aclarar por qué el Masenko (0xAC) igual dispara sin el bit 53 (otro camino lo pone).
- ARREGLO APLICADO (2026-10-30): 231300.c pasa 1LL<<53 / <<54 / <<55 (backup BT2-backups/231300.c.pre_bits).
  Prueba b10fix2-230215: el Madan AHORA pide el disparo (SHOT-PIDE slot 3 tipo 236 clase 0x341500, frame 6603)...
  ...y 33 frames después CRASH NUEVO (código que antes nunca corría):
  - señal 11, dirección 0x1, en func_001513D0 (despacha una entrada de efecto por tipo 0..14). Llamador real:
    func_0014C398 (verificado contra el asm: los 11 argumentos coinciden).
  - 1513D0 lee *(p0) y *(p0+0x20) sin condición, igual que el original (0x1514D4 / 0x1514E0) -> la función está
    bien; el dato está mal: p0 = *(s1+0xB0) con s1 = *(arg1+0x38) (objeto de efecto) vale 1 en vez de un puntero.
  - Siguiente paso: averiguar quién escribe +0xB0 de ese objeto de efecto (tipo 236 / clase 0x341500).
  - bt2full_c23 NO se actualizó con este arreglo: hoy el Madan crashea en vez de no disparar (peor para jugar).
- SESIÓN DEL USUARIO 20261029-232053 (bt2full_c23 con el arreglo de bits): el Madan pide el disparo (frame 4514, obj 0
  slot 3 tipo 236) y a los 5 frames CRASH distinto al de b10fix2:
  - señal 11, dirección 0xFB611EB0, en func_0018D4F0 (dibujo, desde BtlTaskList_Draw): recorre la lista de grupos de
    partículas de arg0+0x158 (next en +0xF4) y llega a un nodo basura (0xFB611DC0) -> lee +0xF0.
  - Justo antes 1513D0 despachó tipos 1, 5, 6 y 11 (slots 0 y 1) con punteros de entrada válidos.
  - 18D4F0, 18D730 (insertar: no pone next=0, igual que el original) y 18D760 (desenganchar) coinciden con el asm.
  - Descartado: el retorno de 150990 (ítem ALTA de docs/audit/ret_used_but_void.md) no lo usa 1513D0 en el original.
  - Siguiente: quién crea los nodos de esa lista (inicializa +0xF4) y en qué tipo de partícula falla (10/11 = Ptcl3).

## MAPEO J1/J2 en los fight logs (CORRECCIÓN 2026-10-30)
- J1 = jugador = chr 017E6000 = obj 0; J2 = COM = chr 017E7550 = obj 1 (verificado: la acción que elige ELIGE-ATAQUE
  aparece en ese J al frame siguiente; el pad solo aparece en J1). Notas anteriores que decían "J2 = jugador" estaban
  al revés: el Madan de 340 frames de las corridas automáticas en Practice lo hacía el COM (también Gohan niño);
  los TECNICA-* con chr 017E7550 son del COM; L2+Círculo -> 0xDA sí fue del jugador.
- Consecuencias: todos los COLL-HIT de técnica vistos son del COM sobre el jugador (B8 parece resuelto). En las corridas
  con script el jugador casi nunca completa una técnica: en b10c-231610 pidió dos veces el Madan (ELIGE -> AD0018 =
  acción 0x18 con 0xAD en cola), pero el J1 pasa por 0x18 y luego 0x97/0xA6/0x20 o 0x90 y la cola se pierde
  (parece un golpe del COM; sin confirmar). Para probar técnicas del jugador conviene un rival quieto.
- En la sesión del usuario 20261029-232053 el disparo que precede al crash de partículas es del jugador (obj 0).

## Clase C2 (RET_USED_BUT_VOID) — estado 2026-10-30
- De las 154 entradas de docs/agents/b12/check_calls_report.txt, 77 siguen con la función llamada definida void (o sin
  definición en port/eq/src): 31 con llamador en combate (0x1F0000-0x245000), 22 en efectos (0x120000-0x1C0000), 24 en
  otras zonas. Casos confirmados y arreglados de esta clase: 29E6D0 (B4) y 29EE90 (B6). Muchas pueden ser falsos
  positivos (v0 reutilizado); cada una se confirma contra el asm del llamador antes de tocarla.
- RESULTADO (agente, 2026-10-30; BT2-test/pruebas/audit_c2.md): las 53 vigentes de combate/efectos son FALSOS POSITIVOS
  (tail-calls que pisan v0, retornos float ya bien tipados, o callbacks de tarea cuyo v0 descarta el dispatcher en
  0x1F2D68/0x1F2E0C). Otras 69 ya no son void hoy (BtlAnim_SetBlend, func_00123530, BtlTaskList_AddTail). Muestra
  verificada a mano: 21DA50 -> jal 0x1F9AC8 en 0x21DA60, v0 no se lee. Quedan sin revisar las 24 de "otras zonas".
- CAUSA PROBABLE del crash de partículas (agente, BT2-test/pruebas/audit_b10_lista.md; verificado el tamaño):
  la lista es del emisor de quads EftQuad (clase 0x341FB8; solo la usa el tipo 6 de 1513D0 vía spawner 0x1503E0).
  port/eq/18D7C8.c (dibuja un nodo, llamado por 18D4F0) tiene `u8 sp[0x300]` y usa sp+0x170 como buffer de hasta 9
  vértices (0x1B0 bytes -> hasta sp+0x320); el original reserva 0x370 con registros desde 0x320 (locales hasta 0x320).
  Con 8-9 vértices tras el recorte (quads grandes pegados a la cámara, como el Madan) se escriben 0x20 bytes fuera y se
  pisa la pila nativa, incluido el s0 (nodo actual) de 18D4F0 -> el "siguiente" sale basura. La lista en memoria del
  juego está bien (el update la recorre antes y no falla). Precedente: 18A9C0.c ya se agrandó a sp[0x400].
  Mismo desborde (sin relación probada con este crash): 1866A8.c y 18FCF0.c (sp[0x300]), 1C6278.c (sp[0x340], 0x60 de más).
  CERRADO (2026-10-30): 1866A8.c y 18FCF0.c -> sp[0x400] (backups .pre_pila, probados limpios: p18fc-235637, copiados a c23);
  1C6278.c -> sp[0x480] (original 0x450; backup .pre_pila; probado limpio p1c62-000120, copiado a c23).
- ARREGLO PILA APLICADO (2026-10-30): 18D7C8.c sp[0x300] -> sp[0x400] (backup .pre_pila). Prueba pila-233451: el jugador
  lanza el Madan (obj 0) y 33 frames después crashea en 1513D0 con p0 = NULL (log B10 1513D0: "p0 (nil)").
- CAUSA de los crashes en 1513D0 (verificada contra el asm): port/eq/182380.c línea ~100 llama
  func_001513D0(*(void **)s7, ...) pero el original pasa a0 = s7 sin desreferenciar (0x182540 move a0,s7 antes del
  jal 0x1513D0 en 0x182568; s7 = *(s2+0x28) en 0x1823C8 y no cambia). *(s7) es el id del luchador: 0 (jugador) -> p0 NULL;
  1 (COM) -> p0 = 0x1 (el crash "dirección 0x1" de b10fix2). La llamada a 182368 sí usa *(s7) (0x1824EC), y el C ahí está bien.
- ARREGLO s7 APLICADO (2026-10-30, 182380.c backup .pre_s7). Prueba s7-234109: el Madan del COM dispara y CONECTA
  (primer COLL-HIT tipo 3), sin crash en 1513D0. Al terminar la técnica, CRASH siguiente en la cadena:
  - señal 11, dirección 0xAC0, en func_00182B10 (lee *(arg0+0x38)+0xA80) desde 14CE78: la lista st+0xAB0 tiene basura.
  - CAUSA (verificada): port/eq/182A80.c es void pero el original devuelve el resultado de BtlTaskList_AddTail (v0 intacto
    hasta jr ra, 0x182A94-0x182AAC). 14C580 guarda ese retorno en ctx+0xAB0+n*4 -> guarda basura. Clase C2; el agente de
    C2 no lo cubrió porque se le excluyó 0x180000-0x192000.
  - Mientras tanto se lanzó un agente de mapeo global del patrón "*(void **)x vs x" -> BT2-test/pruebas/audit_deref.md
- ESCANEO GLOBAL patrón "*(void **)x vs x" (agente, 2026-10-30; BT2-test/pruebas/audit_deref.md): 0 casos confirmados.
  997 argumentos en 265 funciones (851 en 0x120000-0x245000) contrastados con el asm; 14 discrepancias del script, todas
  falsos positivos verificados a mano. No cubre: desreferencias con offset != 0, expresiones anidadas, args por pila,
  llamadas por puntero (jalr). El caso de 182380.c era único.
- ARREGLO 182A80 APLICADO (backup .pre_ret): devuelve la tarea. Prueba ret182-234741: el jugador lanza el Madan 2 veces,
  20 COLL-HIT tipo 3 del jugador sobre el COM, 12005 frames sin crash. Binario copiado a bt2full_c23 (anterior: .pre_madan).

## CAPÍTULO PELEAS CERRADO (usuario, 2026-10-30)
El usuario confirma jugando: L2+Círculo y todas las variantes de Ultimate (L2+Triángulo / Arriba / Abajo) funcionan, sin
errores en pelea. Abierto en el área: B5 (texturas de golpes y de Ultimates). Siguiente foco: texturas.

## B5 — retomado (2026-10-30): pista del port de BT3
Tenkaichi3Decomp/docs/port/README.md (líneas ~470-510, 590-600, 690-700) describe síntomas como los nuestros:
- Contorno de luchadores: el juego deja en el ALFA del frame un id por parte del cuerpo y mezcla un RECTÁNGULO OSCURO
  (0x64 por canal) a través de una imagen de bordes derivada de ese alfa. Si el alfa del render target no es exacto
  (allá: alfa reescalado 1.0=0x80 y recortado, ids > 0x80 perdidos), el rectángulo oscuro se ve entero = nuestro
  "cuadrado oscuro translúcido de bordes duros alrededor de la víctima".
- Glare / brillo de objetos: también usan escrituras de alfa -> candidato para el rectángulo amarillo del Masenko.
- También necesitaron: rectángulos dibujados en la memoria de paletas ejecutados en memoria GS, y alfa de textura > 0x80
  sin recortar al subir la textura.
Plan: (1) revisar cómo nuestro renderer guarda el alfa del frame (¿reescalado/recortado?) y la copia en el byte alto de
la página de profundidad; (2) log hex de texturas (pedido / carga / servido) en los frames de impacto; (3) camino VU.

### B5 — hallazgos del agente de alfa (2026-10-30, informe BT2-test/pruebas/b5_alfa.md)
- Ya heredado de BT3: canal aux R8 de alfa exacto, DATE/DATM, FBA, alfa de textura > 0x80, rects en memoria de paletas.
- Falta: ningún código BT2 llama Port_GsMarker -> outline nativo / alpha key nunca corren, y las pasadas PS2 de bordes se
  descartan (gs_draw.c:513-528) -> rectángulo 0x64 se mezcla contra máscara vacía. Constantes BT3 fijas (CBP 0x3E8C/0x3E94,
  ALPHA 0x68/0x54, gs_draw.c:441-447, 562-566). AFAIL!=KEEP ignorado (gs_draw.c:641), FBMSK parcial, PABE no implementados.
- Siguiente: volcado GS en el frame de impacto con probeOn dentro del cuadrado para identificar la primitiva.
### B5 — hallazgos del agente de render (2026-10-30, informe BT2-test/pruebas/b5_render.md)
- Partículas/chispas NO pasan por VU1: EftPtcl3_Draw -> 1BAD80 arma GIF REGLIST -> Gs_Gif; el volcado GS las ve.
- Caché de texturas (texture_get gs_draw.c:137) parece correcta. Riesgos: (1) buffer de paleta de una entrada y CSA
  ignorado (clut_load gs_core.c:192, Gs_ClutRead :214) -> alfa ~0x80 en todo el sprite; (2) gsWhite silencioso
  (gs_draw.c:178/204/258); (3) REGION_CLAMP/REPEAT solo para FB-como-textura (gs_draw.c:603-618).
- Pruebas baratas: GL vs Vulkan, BT3_VU_INTERP=1, comparar con backups *.pre_clutbuf. Diseño log TEXHEX en el informe.
### B5 — mediciones (2026-10-30)
- El cuadrado: rectángulo oscuro translúcido del tamaño del cuerpo de la víctima (sigue al luchador aunque esté lejos).
  Descartado (BT3_SKIP_TBP / BT3_SKIP_VU temporales en gs_draw.c): tbp 2a20, 2ab0/2ac0/2c1c, capas VU 1, 2, 3, 4, 5.
  Sin tbp 2e00 (desenfoque de pantalla completa) el cuadrado queda NEGRO sólido: se dibuja antes y el desenfoque lo aclara.
  Sin programa VU4 (escenario) no se ve (no concluyente: fondo negro).
- Intento AFAIL RGB_ONLY/FB_ONLY como alpha test cuando hay Z (gs_draw.c mode[3]): NO lo arregla y mete puntos negros en
  bordes de rocas -> revertido (backup .pre_afail).
- Hipótesis vigente: pasada tipo contorno de BT3 (rectángulo sobre el bbox del luchador, máscara desde alfa del frame
  armada con vistas de 16 bits que descartamos). Siguiente: GPU_CUT/GPU_TAIL sobre un frame con cuadrado, capa VU 0 y 's'.
- ACTUALIZACIÓN: el programa 6 (sombra de suelo) NO se dibuja en estas peleas (log VU6 vacío): la corrida "sin s" sin
  cuadrados fue casualidad. El cuadrado es INTERMITENTE -> una corrida contra otra no descarta nada; los descartes de
  arriba (2a20, 2ab0/2ac0/2c1c, VU 1-5) son débiles salvo donde el cuadrado se vio igual. BT3_P6_INTERP no sirve (el
  intérprete no termina el programa 6 y manda PRIM basura). Interruptores TEMP quitados (gs_draw.c restaurado de
  .pre_skipvu, gs_vu1.c de .pre_p6interp). Hace falta un detector reproducible: volcado (BT2_DUMP_TRIGGER) en un frame
  donde el cuadrado se vea, con BT3_GS_PROBE dentro del cuadrado.

### B5 — CERRADO (2026-10-30)
Causa: los brillos de golpe / aura de ki (quads tbp 2be0..2bec, PSMT8/PSMT4, TCC 0) escriben TEX0 con CBP 0 y CLD 0
después de cargar su paleta (cbp 2a04). El GS real con CLD 0 usa el buffer de paleta sin mirar CBP; el port leía la
paleta de memoria en CBP 0 (todo ceros) -> textura negra modulada por alfa 0x23 = cuadrado oscuro translúcido.
Se encontró con volcados periódicos + captura del mismo frame (TEMP en gs_gl.c: guarda gpu_N.ppm del frame volcado;
gs_core.c: sDumpFrame pasó a global gGsDumpFrame).
Arreglo: gs_draw.c texture_get: con CLD 0 y paleta de 8/4 bits usa CBP/CPSM del buffer (Gs_ClutBuffer en gs_core.c).
Backups *.pre_cld0. Prueba cld0-054839 (MODO duel, square x40, 25 volcados): sin cuadrados, auras de ki correctas, sin crash.
Pendiente menor: el trapecio oscuro del frame 8833 y una franja rojiza arriba a la izquierda del HUD (no reprobados).

### Gráficos de vida baja / Max Power (2026-10-30)
- Vida baja (franja roja sobre el panel del J1): el parpadeo es un rectángulo rojo (rgba ff000019, ctx 1, TEST 0x3c000 =
  DATE+DATM, FBMSK protege alfa) que pinta donde el alfa del frame tiene bit 7. La máscara la arma la pasada anterior
  (tbp 2a70, TEST 0x33539: ATE EQUAL 0x53, AFAIL RGB_ONLY). El port ignoraba el test con AFAIL != KEEP -> la máscara
  cubría todo el rectángulo. Arreglo (gs_draw.c GsGpu_Draw, solo camino GIF): pasada 1 con el test, pasada 2 con el
  test invertido y la máscara de escritura de AFAIL. Backup gs_draw.c.pre_afail2. En c23 (backup bt2full_c23.pre_afail2),
  SIN verificar con vida baja (la corrida afail2-063109 no llegó a vida baja). Los caminos VU siguen con la regla vieja
  (el intento global anterior dejó puntos negros en rocas).
- Max Power (ki al máximo): no capturado todavía. Lógica en 223AA8.c (BtlMember_AddMaxPower / IsMaxPowerFull), 2142A8.c.
  Falta un volcado F9 en ese estado.
- Ojo B5: con el arreglo CLD 0, los brillos de golpe toman la paleta que haya en el buffer; en afail2-063109 frame 7809 el
  buffer tenía la paleta de 256 de cbp 2a04 (colores de escenario) y el brillo salió como recuadro amarillo/oscuro.
  O el orden de cargas de paleta difiere del PS2, o la paleta correcta (rampa blanca 2a08 n16) se pisa antes. Abierto.
- C2 (149 RET_USED_BUT_VOID, check_calls regenerado): ninguno lee v0 en el asm del llamador (128 lo dejan pasar al
  retorno sin que nadie lo use, 9 tail calls, 12 saltan a retorno/otra llamada). Falsos positivos: no se toca nada.
- B5 recuadros (c7809, confirmado por el usuario como el efecto del golpe): brillo tbp 2bb4/2bbc/2bc0, TCC 0, CLD 0, CBP 0.
  Toma la paleta que esté en el buffer. Frame 9713: rampa blanca (correcto). Frame 7809: entre la carga de la rampa
  (tbp 2b20, cbp 2a08 n16, línea 53581) y el brillo, un dibujo tbp 2b10 cargó cbp 2a04 n256 (colores de escenario):
  los dos recuadros tintados. Hipótesis: en PS2 el orden de esos paquetes difiere (otro PATH / otra lista), o el
  brillo debería usar la última paleta de 16 colores (la CSA/zona de 16 no la pisa una carga de 256 en el GS real?).
  Siguiente: verificar en la doc del GS si una carga de 256 colores pisa entradas 0-15 (sí debería) y ver en el asm
  quién emite el paquete 2b10 y en qué orden respecto del brillo.
  CORRECCIÓN: el TEX0 de 2b10 (REGLIST 0x460bc8) y el del brillo (0x460c48) están en el MISMO paquete, consecutivos:
  en PS2 el orden es igual. Descartado "orden distinto". Queda: (a) qué guarda realmente la textura 2bbc (32x2 PSMT8:
  si sus índices son 0..15, en PS2 usa las entradas 0-15 del buffer) y cómo el GS real arma el buffer en una carga de
  256 con CSM1 (orden de entradas 8-15/16-23 intercambiadas); (b) el alfa por vértice (el volcado muestra alfa 0 en el
  primer vértice: el resto del strip no se imprime).
- REGRESIÓN del arreglo CLD 0 (sesión del usuario 20261030-063807, Namek): escenario en bloques de colores. Las texturas
  del escenario (camino VU4) usan CLD 0 con su CBP, y nuestro buffer no se actualiza en ese camino: tomar el buffer para
  todo CLD 0 les daba otra paleta. Arreglo: sólo con CBP 0 (el caso del brillo). Backup gs_draw.c.pre_cld0cbp0,
  c23 actualizado (backup bt2full_c23.pre_cld0cbp0). Sin reprobar.
- CLUT (informe del agente, 2026-10-30): todos los caminos (GIF, VU0/4/6/7/8) sí llaman clut_load. El modelo era el que
  fallaba: Gs_ClutRead leía MEMORIA cuando el CBP del dibujo no coincidía con la última carga, y una carga de 16 borraba
  la identidad de una de 256. El GS real dibuja siempre del buffer. Cambio: Gs_ClutRead / Gs_ClutHash usan siempre el
  buffer (memoria sólo antes de la primera carga); una carga de 16 pisa sólo su bloque; hash sobre las 256 entradas.
  Quitado el parche "CBP 0" de texture_get. Backups *.pre_clutbuf (gs_core.c, gs_draw.c, bt2full_c23). Pendiente: CSA
  (se ignora al cargar y al dibujar) y CPSM16. Sin probar: lo prueba el usuario (Namek, golpes, Max Power).
- Prueba maxpow-064722 (Práctica): el menú COM se abrió pero el rival siguió peleando; frame 8945 muestra el brillo de
  golpe como recuadros enormes (mismo problema de paleta). Con vida baja del J1 (frame 9180) no se vio rectángulo rojo.

### B11 — crash al entrar a una opción del menú (sesión del usuario 20261030-065225, 2026-10-30)
- señal 11 en func_002B24C8+0x169, dirección 0x42000000 (tope de la pila del juego; rsp 0x41FFFBF0). Pila: overlay
  func_003B7FA8 (despachador de modos) <- func_00100388.
- 2B24C8.c es un descompresor por pares de bytes (sp[0x300]: tabla de pares + pila de expansión en sp+0x200); el C
  coincide con el asm (mismo marco 0x320). El desborde viene de los DATOS: entrada inválida (puntero o archivo no
  cargado) hace crecer la pila de expansión hasta pasar el tope de la pila. Causa real: el llamador (20 sitios:
  243E38, 248068, 24BED8, 24CDD0, 24CF78, 250BF0, 251100, 253EC8, 2542F0, 256360, 256F10, 258418, 259378,
  25EF60, 25FAF0, 29BB88, 3B3100, 3BBEF8, 3BE778, ...). Falta saber qué opción del menú era para acotarlo.
- Nota: el log marca 2041 texturas en la caché del GPU en el menú (cerca del máximo): revisar aparte.
- Pendiente CLUT: CSA ignorado (carga y dibujo) y CPSM16. Low health y Max Power: CONFIRMADOS por el usuario tras el
  arreglo del buffer de paleta.
- B11 CAUSA: func_00402E58 (pantalla de opciones de Dueling, overlay) pasaba al descompresor *(*g) (la primera palabra
  de la entrada) en vez de *g (la dirección de la entrada): src 0x282380, tamaños basura. Corregido en 402E58.c
  (backup 402E58.c.pre_b11). Logs TEMP quitados (2B24C8.c y 3BE778.c restaurados). c23 actualizado. Lo prueba el usuario.
- Bloques de colores persistentes (usuario: aparecen tras un efecto de pantalla completa al recibir daño y siguen en
  otras peleas/escenarios). Sospecha: gs_core.c, sprites a buffers de 64 de ancho se ejecutan por SOFTWARE en memoria GS
  si la página tuvo subidas (gGsPageGen[fb] != 0) o si parecen copia de paletas; esa ruta incrementa gGsPageGen de la
  página dibujada, así que una vez que cae ahí queda pegado. Los buffers del brillo (1f6/1f8/1fa/1fc, 64x64) pueden
  caer y escribir el brillo en páginas de texturas. Cambio: no ir por software si la fuente es un render target del
  GPU. Backup gs_core.c.pre_swsprite / bt2full_c23.pre_swsprite. Lo prueba el usuario.

### B12 — Free Battle 5 vs 5: cuelgue con pantalla negra (sesión 20261030-070956)
- A t=96.8 s el juego deja de avanzar; el hilo del juego repite ADXF_OpenAfs(1, 752167) "fuera de rango" sin fin
  (15 M líneas, log de 546 MB). Llega por func_00100D58 (cargador de archivos de menú; índice >= 0x33B2 va a la
  partición 1, 752167 + 0x33B2 = 0xBADD9): un llamador pasa un índice basura y el bucle de espera nunca termina.
- TEMP: log "B12:" en 100D58.c (backup 100D58.c.pre_log) con el índice y la dirección del llamador. En bt2full_cvc;
  falta copiarlo a c23 y reproducir.

### B13 — cielo/escenario corrompido con la preparación de la Genkidama (usuario, 20261030-071259, frame 4445)
- ACLARACIÓN DEL USUARIO: la provoca "Give Me Energy" (Goku, L2 + Círculo): prepara la Genkidama, una bola de ki
  ESTÁTICA en el escenario que crece hasta que el jugador la lanza. Mientras está, se corrompe el fondo y el cielo.
  Según el usuario es el único ataque de este tipo. NO prioritario por ahora; anotado para diferenciarlo de los
  problemas de rayos/bolas de ki (B14).
- Captura: el cielo sale blanco quemado, el suelo y los árboles casi negros, y hay un borde vertical a x~130.
- El oscurecimiento de escena es del juego: sprite 50505080 con ALPHA 0x52 (Cd - Cs*Ad), o sea que oscurece según el
  ALFA DE DESTINO. Ese alfa lo escriben antes pasadas que leen el buffer 0x150 (tbp 2a00) como PSMCT16 (psm 02, vista
  de 16 bits de un buffer de 32: el "channel shuffle" de BT3) con FBMSK solo-alfa y TEST 0x3000f. El GPU descarta las
  vistas de 16 bits, así que el alfa queda con lo que tenía (cielo ~0, escenario alto) y el oscurecimiento y el brillo
  aditivo (ALPHA 0x68 desde 2a00) quedan invertidos o desparejos. Arreglo probable: implementar el shuffle de 16 bits
  como pasada nativa (como BT3 hizo con el contorno), o reproducir el alfa resultante. Pendiente de diseño.
- Kamehameha: la textura del rayo queda quieta en el aire y no viaja, aunque el impacto llega (pendiente, sin investigar).
- Free Battle 5 vs 5 (B12): el usuario no lo volvió a ver; no dar por verificado.

### B14 — rayos y bolas de ki de los Ultimates no se ven viajar (usuario, 2026-10-30)
- Kamehameha (y otros Ultimates): la textura queda quieta en el aire y no llega al rival, aunque el impacto sí llega.
- Gekiretsu Madan: impacta; pero las bolas de ki no se ven llegar (físicamente sí).
- Masenko: el usuario pasó capturas con corrupción al lanzarlo: error grave de textura o de CLUT.
- Plan: 1) mirar en BT2-test/referencia/ cómo debe verse un Ultimate de ki; 2) comparar con el Kamehameha nuestro.

### B15 — Selección de mapa: falta la vista previa grande del escenario (usuario, 2026-10-30)
- Referencias (PS2): BT2-test/referencia/mapsel_ref1.png, mapsel_ref2.png: a la izquierda, una vista previa grande del
  escenario elegido (imagen del mapa) detrás del panel; a la derecha la columna de miniaturas.
- Nuestro port: mapsel_port.png: la columna de miniaturas sale, pero la vista previa de la izquierda falta o sale como
  una franja borrosa.
- Es la misma pantalla donde el usuario vio FPS disparados / control acelerado (no prioritario por ahora).
- B14 HALLAZGO (volcado del usuario 20261030-072755, frame 4487, Kamehameha): cientos de quads de efecto (tbp 2bc4,
  2c1c, 2bc8; PSMT8; ALPHA 0x48; REGLIST e400000000008001 / regs 0x0042142142142160) tienen los 4 vértices en el MISMO
  punto de pantalla (200.7,107.2), Z 0xffffd0, Q ~5.8e-8: proyectados casi en el infinito, colapsan en un punto de
  fuga. No es paleta ni renderer: es el cálculo de posiciones del efecto en el código del juego. Agente investigando
  el emisor (candidatos 131A18, 1B1A20, 1B4C18, 1B6320, 1BAD80, 1BE0D8, 1BF030, 1C3208, 1C3BE8, 1C4750). Volcado
  copiado a BT2-test/pruebas/dump_kame_4487.txt.
- Pantalla blanca en el Kamehameha y en su choque con el Masenko (frames 4487, 5232): pasadas aditivas (ALPHA 0x68)
  desde el buffer 0x150 más las vistas de 16 bits (psm 02) que el GPU descarta. Relacionado con B13.
- B16: choque de rayos infinito: los dos luchadores quedan en la acción 0xE0 desde el frame 4312 y la animación se
  repite sin fin. Agente investigando el equivalente de BtlClash_Update.
- B16 CAUSA (agente): port/eq/20F9D8.c (driver del choque, estado en roster+0x30) declaraba func_0020F218(void) y
  func_0020F7A8(void) y los llamaba sin argumento; el asm pasa el estado en a0. F218 (clash A: 106 frames, desempate,
  empuje, banderas 7/0x800 y 7/0x1000 al ganador/perdedor) recibía basura y nunca llegaba al estado 5, así que la acción
  0xE0 (handlers 22FF18/22FFC8/2303F0/230488) no terminaba. Arreglado: se pasa `st`. Backup 20F9D8.c.pre_state.
- B14 lateral (agente): 1B45E0.c declaraba func_001B4C18 y func_001B4AA0 con otro orden/tipos; el último argumento
  (gEftRay, un PUNTERO) iba como s32 por la pila (en x86-64 la mitad alta queda basura). Prototipos y llamadas
  corregidos según las definiciones. Backup 1B45E0.c.pre_proto.
- Mismo patrón en todo el código: 53 candidatos (prototipo local (void) de una función que recibe argumentos, llamada
  sin argumentos) en docs/audit/void_proto_candidates.txt. Revisar uno por uno contra el asm (si el llamador setea
  a0..a3 antes del jal es bug; si los hereda de su propio a0 puede no serlo).
- TEMP: log "B14:" en 1B1A20.c (segmentos de la cinta antes de proyectar; backup 1B1A20.c.pre_log).
- B14 CAUSA RAÍZ (2026-10-30): log en 1B1A20/1B1380: 333 de 400 segmentos de la cinta con posición NaN; el NaN nace en
  la rotación (Mtx_RotateX/Y) del último nodo. func_001286B8 (Vu0_SinCos: vf12 = (sin, cos)) NO tenía C y corría por
  el relleno de PS2Recomp, cuyos registros VU0 NO son gVu0: las rotaciones en C leían un vf12 viejo -> NaN -> todos
  los quads del efecto en un punto. Escrito port/eq/1286B8.c (igual a Vu0_SinCos de BT3, con sqrt(|x|) como vsqrt).
  Resultado (kame6-083432): 0 NaN; se ven auras, ráfagas, explosiones, humo, polvo. Quedan pantallas blancas (brillo,
  B13), una nube negra y las cruces azules fijas.
- Revisado el riesgo sistémico: de las 688 funciones del relleno (600 con asm a mano) solo 4 usan VU0: 1286B8 (ya en C)
  y 1407A0 / 177510 / 1B7788, idénticas (largo de un vector: lqc2, vmul, vadd, vsqrt, devuelve en f0). Esas tres no
  dejan estado en registros VU0 que otro lea: no tienen el desfase con gVu0. 88 funciones del relleno no tienen asm
  a mano para revisar.
- 1B45E0.c ahora compila (antes caía al relleno): su C corre por primera vez.
- VU0 del relleno pasado a C (2026-10-30): de las funciones del relleno con VU0 (desensambladas con el objdump del EE
  dentro del contenedor), las que leían estado guardado: Rand_Float01 128580 + Rand_FloatRange 1285D0 (registro R:
  la semilla de 128570, ya en C, nunca llegaba al generador), Vu0Cur_GetStackDepth 128F30 + IsStackUsed 128F58 (vi15),
  129E08 / 129E50 (largo y distancia con vf15.x). Archivos en port/eq. build_full.py: un archivo de port/eq gana sobre
  un src/ cuyas funciones define todas (src/ tiene asm MIPS en línea que no compila en PC); símbolos leídos una vez.
  Las demás VU0 del relleno solo usan sus argumentos (largo, normal de triángulo): sin desfase. Relleno: 682 funciones.
  Prueba vu0c-090941: pelea con Kamehameha sin crash. c23 actualizado (backup bt2full_c23.pre_vu0c).
- Auditoría de los 53 prototipos (void) (docs/audit/void_proto_audit.txt): en los 51 con asm, ningún a0..a3 se carga
  entre la llamada anterior y el jal (el compilador nunca cuenta con que sobrevivan a una llamada): en el original
  también se llamaban sin argumentos. Ninguno es bug. (El de 20F9D8 no estaba en la lista: ahí a0 se cargaba con lw
  antes de un salto.) Los 2 restantes no tienen jal directo.
- check_calls ARITY_LESS/HIGH (4): 200EF8.c llamaba BtlKiBlast_GetReactS4000Of_240848(hit) y GetReactS200Of_2408F0(hit)
  sin el `kind` (asm: a1 = 2): elegían otro registro de ki para la reacción al impacto de ráfagas. Arreglado (hit, 2).
  2A4F50.c llamaba BtlFacade_PulseCtrl10D() sin el lado (asm: a0 = s0 = b). Arreglado. 2F77B8 -> func_002F1480: el
  callee solo usa a0/a1: inofensivo. Backups *.pre_arity. Prueba kiblast (Triángulo x20): 44 impactos, sin crash.
  c23 actualizado (backup bt2full_c23.pre_arity).

## Relleno (PS2Recomp) — mapa para llegar a 100 % C (2026-10-30)
- 682 funciones en el relleno: ~620 están en 0x300000+ (biblioteca C y SDK de Sony: _sprintf_r, sceSif*, etc.) y ~62
  son del juego propiamente dicho (< 0x300000).
- BT2_FALLBACK_LOG=1 en una sesión completa (arranque, menús, pelea con especiales; fblog-091903): solo 50 se ejecutan
  (docs/audit/fallback_used_fight.txt). Del juego: BtlUtil_WrapAngle 2111E8, StgRigid_Init 242F60, StgRigidList_*
  (242AD0..242EA8: física de objetos del escenario), ColSphere_TestSphere / SweepSphere (293C00 / 293DD8), 293BE0,
  Vec3_Dist 29E000, 29DFD0. El resto, del 0x300000+ (biblioteca/SDK).
- Orden propuesto: 1) las del juego que se ejecutan en pelea; 2) el resto del juego (~62); 3) la biblioteca/SDK
  (reemplazar por equivalentes del host donde se pueda).
- Avance (2026-10-30): 4 archivos de src/ del juego no compilaban en PC y TODAS sus funciones caían al relleno:
  xd_2111E8 (WrapAngle), xd_242948 (física de objetos del escenario, 13), xe_293BE0 (colisión de esferas, 4),
  eft_t_c_1B58D0. Arreglado con guardas __mips__ (el build de PS2 no cambia): LIT4 en include/sys/xd_lit.h y
  xd_2111E8.c (en PC lee la constante), ColB_Vec3LengthSq en C, y la asignación a cast de gEftShotFx por un ayudante.
  Además 9 funciones puras de largo/distancia en port/eq (29DFD0, Vec3_Dist 29E000, 1B7788, 1407A0, 177510, 1DF2B0,
  121610, 123140, 121648 = distancia en el plano XZ). Backups *.pre_host.
  Relleno del JUEGO: 49 -> 20 funciones (docs/audit/fallback_game_left.txt). Sesión completa len9-092856 (arranque,
  menús, pelea con especiales): NINGUNA función del juego corre por el relleno; solo biblioteca/SDK (0x300000+).
  c23 actualizado (backup bt2full_c23.pre_src4).
- Relleno del juego 20 -> 4 (2026-10-30): en C 1FD1D8/1FD1E0/1FD1E8 (devuelven 1/0/0), 2B3C60 (1), 2D5A48..2D5A78
  (frecuencias MPEG 24000..60000), 12D8D0 (normal de triángulo), 145AA8 y ColB_Vec3Dist 294750 (distancia),
  1DBC80 (raíz de producto punto), Rigid_CheckRest 296F70 (igual que BT3 rigid.c; constantes de BT2 verificadas en
  gp 0x38BDF0-0x4C28.. y 0.25 por lui 0x3E80). Quedan 25FE30/38/40/48: devuelven t5/t3/t2/t4 del llamador, solo
  referenciadas desde la tabla de punteros 0x3764D0 (jalr); sin equivalente C sin el llamador; no se ejecutan.
- Usuario (20261030-121104, frames 6761..7477): partículas amarillas quedan quietas en el aire y no se apagan; un
  rectángulo blanco; el Masenko no dibuja la estela continua hasta el rival (referencia sheet_06 fila 1 col 6). Agente
  investigando el camino del rayo (1B45E0 recién en C) y la vida de las partículas.

## Limpieza fuera del proyecto (2026-10-30)
Movido (mismo disco, renombre; se puede devolver) a BT2-backups/viejos_2026-10-30/:
- Proyectos/BT2-Port (19 GB), Proyectos/BT2-Port-FULL (45 GB): copias viejas del port. Solo las usaban
  scripts/bisect_0037.py, restore_0037.py y setup_symlinks.sh (recuperación puntual vieja).
- Proyectos/PS2Recomp (11 GB): el build usa third_party/PS2Recomp (tools/PS2Recomp es un enlace a esa copia).
- Descargas/Tenkaichi3Decomp (3 GB, una instalación release) y 5 zips Tenkaichi3Decomp-*.zip.
No tocado: ~/Proyectos/BT2-Recomp (regla), ~/Proyectos/Tenkaichi3Decomp (referencia BT3 en uso), la ISO .7z y el
video de referencia en Descargas, BT3-Decompiled y los demás proyectos ajenos.

## Rayo largo y chispas (informe del agente, 2026-10-30)
- 1B45E0 coincide con el asm: es el destello (flare) de la mano, no el cuerpo del rayo. El cuerpo sería el módulo
  EftBlast de BT2 (EftBlastObj_Create 0x191600 .. IsAlive 0x194E30, port/eq/1940F0..194FA8): auditar el avance de la
  cabeza (pos += dir*speed, vida = s*30). Pendiente.
- Chispas que no se apagan: EftPtcl3_Update (src/battle/xc_1BC010.c) solo llama Step (1BAC28) si
  BtlScene_IsEffectStopped (126748) da 0; la traducción de la vida (1BA518, 1B9470) está bien. Hipótesis: Step no corre
  (126748 != 0 persistente o otra copia del emisor) o prototipos s32 con punteros (1BAC28.c, 1BAAF8.c) si la memoria
  emulada está sobre 4 GB. Pendiente: un log en EftPtcl3_Update.

## Limpieza dentro del proyecto (2026-10-30)
Movido a BT2-backups/limpieza_proyecto_2026-10-30/ (17 GB, mismo disco):
- scratch/: todo lo que ninguna herramienta usa (ptest 2,9 GB, shots 1 GB, native*/vclip*/shadow*/ident*, etc.).
  Quedan m2c_sweep (asm para check_calls y auditorías), hexrays, asm_snap, protos, vu0.
- port/build/shots_png y las imágenes de port/build/shots y shots2 (las carpetas quedan).
- BT2-test/logs/vivo: las corridas anteriores al 2026-10-30 (quedan las de hoy, 7,2 GB).
- BT2-test/port/build/shots (capturas de volcados), el archivo suelto BT2-Recomp/0.
Verificado: build + link OK y el binario sale idéntico a bt2full_c23.
- 25FE30/38/40/48 NO eran funciones: son las ramas del switch(arg3) de func_0025FD60 (jump table 0x3764D0, leída en
  0x25FE1C); PS2Recomp las cortó como funciones aparte. func_0025FD60 ya está entera en C. Corregido port/funcmap.csv
  (25FD60 hasta 0x25FE58; backup funcmap.csv.pre_25fd60). Relleno del JUEGO: 0 funciones. Prueba c100-122528 sin crash;
  c23 actualizado (backup bt2full_c23.pre_c100). Queda en el relleno solo biblioteca C / SDK (0x300000+).

## B14 avance (2026-11-03)
- El rayo de BT2 (equivalente de EftBlast_Update de BT3) es func_0014A968; coincide con el asm (jtbl 0x36DEC0
  incluida), igual que 14A6D0 (bucle de partes) y 1513D0 (despachador de 15 tipos). La cabeza avanza bien.
- ARREGLADO: 1501C0.c (generador tipo 5) declaraba 3 floats; los llamadores (1513D0, 14D6F0) pasan 4 (f12 sin usar)
  -> todos corridos uno (escala y tiempos errados). Se agregó el f12. Backup BT2-backups/1501C0.c.pre_f12; c23
  actualizado (backup bt2full_c23.pre_1501c0). Prueba sin ventana sin crash. Falta que el usuario lo mire.
- Ninguna partícula guarda puntero a la cabeza: la estela (14FB50) y el objeto rayo (150C68 -> 18BB50/18BDE0/18BE48)
  copian la posición cada frame con flag 8. Pendiente: log de flags/tipo por frame en 1513D0 para ver si flag 8 llega
  después del spawn; revisar el resto de 188218, 1890C8, 1C7150 (EftRibbon_Update), 14EFA8 y 14F2B8.
- TEMP: 1513D0.c tiene un log "B10" por llamada (quitar).
- LOG ULTI (2026-11-03, run ulti-202523, logs TEMP "ULTI" en 14A968/14FB50/150C68, backups *.pre_ultilog):
  14A968 (EftBlast_Update) NO corre en estos ultis; el Masenko/ulti (acción 0xAF) crea el objeto rayo 150C68 (tipo 12)
  y la estela 14FB50 (tipo 2) y les llega flag 8 cada frame (descartado "flag 8 no llega"). Siguiente sospechoso: el
  update del objeto rayo (resto de 188218, 1890C8, 18A2C8/189FD8) y EftRibbon_Update 1C7150. Pantalla blanca encima
  del disparo (B13/brillo) tapa el rayo en el video.
- Auditoría (agente, 2026-11-03): resto de 188218, 18A2C8, 189FD8 coinciden con el asm. Latente: src/auto/m2c_1890C8.c
  llama 1889F8()/188D68() sin el a0 (funciona por suerte, rdi intacto). 1C7150 es EftRibbon_Create, no el update.
  Sin auditar: 1889F8 / 188D68 (alta de nodos del cuerpo del rayo), EftRibbon_Update (clase 0x342998), 1C5320,
  dibujo 1C55B8 / 1C6278 (desensamblar con tools/binutils dentro del contenedor; no hay .s de 1C7xxx).
- VIDEO DEL USUARIO (20261103-203655.mp4, frames extraídos 0:49-0:54, 1:03-1:05, 1:06-1:08, 1:09.5-1:11):
  * Carga del Kamehameha (1:06.6..1:08) y su disparo (1:09.6..): los sprites de la carga/cuerpo SÍ se dibujan y se
    mueven, pero como CUADRADOS planos blancos/celestes de borde duro (sin la forma circular/alfa de la textura).
  * 1:07.67-1:07.70 y 1:10.13-1:10.30: cuadrados con textura basura (rayas de colores / ruido) -> textura leída de
    VRAM equivocada o formato errado (psm/tbp/CLUT).
  * Golpes (0:51-0:53): chispas de impacto como cuadrados naranja/amarillos; destello de teletransporte como cuadrado
    blanco rotado grande (0:53.47-0:53.57).
  * Masenko (1:03): flash amarillo de pantalla completa y luego el disparo se ve solo como un punto chico.
  => El problema dominante es de RENDER de texturas de efecto (alfa/CLUT/textura), no de geometría: la geometría
     existe y viaja. Siguiente paso: volcado GS (F9) en plena carga del Kamehameha y revisar psm/tbp/cbp/TEX0/ALPHA
     de esos quads.

## CH CAUSA HALLADA (2026-11-04): comparación de clase con la dirección de PC
- Las interfaces por handle de los efectos verifican el task con `task->cls[0] == (void *)Xxx_Update`. La tabla de
  clases guarda la dirección PS2 (EftPtcl3_Update = 0x1BC188) y en el port el símbolo es de PC (0x402E59D0): la
  comparación NUNCA da cierto -> Stop/Kill/IsAlive/SetPos/SetDir/SetTexture... no hacen nada. Verificado con log:
  22 Stop con cls0 1BC188 vs 402E59D0, sin efecto; emisores fl 9/19 vivos para siempre en el mismo lugar.
- ARREGLADO para EftPtcl3 (8 usos): IS_PTCL en xc_1BC010/1BC230/1BC440/1BC840/1BC970 (original bajo #ifdef __mips__)
  y 1BC688/1BC778/1BC918 comparan con 0x1BC188. Backups *.pre_isptcl. Prueba: los emisores reciben el apagado y
  mueren (fl B/1B/F -> 7). c23 actualizado (backup bt2full_c23.pre_isptcl). Falta que el usuario lo vea.
- PENDIENTE, MISMO BUG en los demás módulos (uno por vez): grep "cls\[0\] ==" en src/battle: xa_1437D0 (EftSmoke),
  xc_1B3378/1B3630/1B37D0/1B3C98, xc_1C0488/1C06A0/1C08B8/1C0B30 (EftPtcl4), xc_1C6E20/1C6F90/1C7150 (EftRibbon:
  la ESTELA de los rayos), xc_1CAF98/1CB140/1CB350/1CC590; y comparaciones equivalentes en port/eq.
- Logs TEMP ULTI y PTCL quitados.

## CRASH EftBurst (usuario, 2026-11-04, partida 20261103-211014, rc=139 vblank 12138, acción J1 0xAE / Genkidama)
- Señal 11 en func_00135DA0 (bucle de dibujo de las 350 partículas EftBurst): rbx (puntero de partícula, registro
  preservado) llegó con un float -> un callback pisó la pila. func_00134280 (callback +0x58) declaraba u8 sp[0x80]
  pero escribe la matriz de 64 bytes en sp+0x70 (hasta 0xB0) y usa sp+0xB0/0xB4. Frame asm 0x120, locales 0..0xBF.
- ARREGLADO: sp[0xC0] alineado a 16 (backup 134280.c.pre_sp). Prueba sin crash. c23 actualizado (backup
  bt2full_c23.pre_sp134280). Pendiente: buscar el mismo patrón (buffer local menor que el frame) en otros archivos
  (docs/audit/sweep_check_stack.txt tiene un barrido previo).
- Capturas de esa partida: carga del Kamehameha = cuadrado blanco; cuadros con rayas blancas junto al rayo; cielo
  blanco en la Genkidama (B13); rectángulos blancos junto al HUD.
- (2026-11-04) Usuario: el aura ya se apaga; las chispas siguen fijas en el mapa (se animan pero no siguen).
  ARREGLADO EftPtcl4 (mismo bug de clase, 0x1C05F8): IS_PTCL4 en xc_1C0488/1C06A0/1C08B8/1C0B30 y 1C0A68. Backups
  *.pre_isptcl4; prueba sin crash; c23 actualizado (backup bt2full_c23.pre_isptcl4). Falta que el usuario lo vea.
- Barrido con 3 agentes de solo lectura: comparaciones de clase restantes, buffers de pila chicos, floats corridos.
- (2026-11-04) Comparaciones de clase ARREGLADAS además de Ptcl3/Ptcl4: Ribbon (estela, 0x1C6E40), Smoke 0x143C38,
  Geyser 0x131760, Steam 0x13A8B8, Trail 0x1A68A8, Struggle 0x1A7FA0, Chain2 0x1B2FD0, Ray 0x1B3E68, Mod1CB 0x1CB078,
  Mod1CC 0x1CC770 (direcciones de port/build/full/tables.c). Backups *.pre_isribbon / *.pre_iscls. Además, 1BC918,
  1C74A0, 1B3778, 1CCAC8, 1CCC68 comparaban el campo +0x28 sin leer cls[0] (el asm hace lw 0x28; lw 0x0): corregido.
  c23 actualizado (backups bt2full_c23.pre_isribbon / pre_iscls).
- PENDIENTE (mismo bug, clases sin nombre; revisar la forma con el asm): func_00182728, 183228, 191238 (191890/
  1918F8/191960), 194948 (194E70/195128), 19C868, 19FFA8, 1A45B0, 1AC650, 1B5400, 1DDA10, 1E9428, 1EB270.
- Barrido de pila: 2FB048 memset 0x14 sobre s32 sp[4] -> sp[8] (backup .pre_sp). Barrido de floats: sin nuevos
  confirmados; dudoso func_001770B8 (solo por tabla, f13/f14).

## PUNTO ESTABLE 2026-11-04 (confirmado por el usuario: los efectos ya no quedan flotando, desaparecen)
- Backup completo: BT2-backups/estable_2026-11-04/ (fuentes.tar con src, port/eq, port/full, port/tools, funcmap,
  include, docs; bt2full_c23 y bt2full_cvc). Todo lo posterior es EXPERIMENTAL hasta que el usuario lo pruebe.
- Auditorías lanzadas (4 agentes, solo lectura): 1) clases sin nombre + niveles de indirección; 2) paquetes GS /
  TEX0 / CLUT en el código del juego (cuadrados blancos); 3) anchos y signos de lecturas/escrituras y casts
  float->u8; 4) supuestos de direcciones PS2 vs PC (DMA, espejos, tablas).
- Auditoría 4 (direcciones PS2 vs PC, pasada superficial): sin confirmados. Dudosos: tags DMA con `& 0x0FFFFFFF`
  (29E770/29E898/29EE10/29EF08) y espejos uncached (2CB3D0/2CC168/2CB748) romperían si reciben un buffer definido en
  C (no se halló ninguno); plat_sdk.c:128 dma_phys es un ternario sin efecto; callbacks de PC guardados en datos
  (10B0C8 +0x1350 ok; sin trazar 2A86E8, 11CB18, 2A16A8).

## CUADRADOS BLANCOS: CAUSA HALLADA (2026-11-04, confirmado por el usuario)
- 18DCB8.c y 1A43C8.c declaraban localmente `s32 EftVram_AddImage(...)`; la función real devuelve el TEX0 entero
  (64 bits). En x86-64 el valor se truncaba a 32 bits y se extendía el signo: se perdían TH/TCC/TFX (alfa de la
  textura -> cuadrado opaco) y entraba basura en CBP/CPSM/CSA/CLD (paleta/rayas). Arreglo: prototipos s64/u64 y la
  variable local s1 a s64. Backups *.pre_s64; c23 (backup bt2full_c23.pre_tex0s64).
- Usuario: donde había cuadrados blancos y falta de textura, en varias zonas ya no los hay. La carga del Kamehameha
  ahora es una bola con textura, pero FALTA EL HAZ (el rayo es un barrido tipo láser hasta el rival, no una bola).
- Lección: buscar en todo el juego valores de 64 bits (registros GS, TEX0, tags GIF/DMA) que pasen por s32/u32
  (prototipos, locales, argumentos, campos, stores de 32 bits donde el asm hace sd).

## Lote clases sin nombre (EXPERIMENTAL, 62 archivos, backups *.pre_iscls2): CRASH en BtlTaskList_Draw (nulo)
- Bisección: con 1E9428+1EB270+1DDA10+1B5400+1AC650+1A45B0 revertidas no crashea; con 1E9428+1EB270 revertidas
  tampoco; con solo 1EB270 revertida tampoco. En curso: confirmar 1EB270. NO está en c23.
- (2026-11-04, tarde) Volcados del usuario 7630/8337/8375: sigue un cuadrado blanco en el inicio de la carga del
  Kamehameha y en la bola lejana. FIRMA: TEX0 con los 32 bits altos en CERO (0000000099302c20, ...2c44, ...2c54,
  0000000055302c5c, 00000000dd30abe0): truncado sin signo -> TCC/CBP/TH perdidos. Paquete REGLIST
  c400000000008001/0000f42142142160, PRIM 0x5B, PSMT8. Constructores con ese tag: 12C468, 12E158, 12DA70, 13A070,
  139390, 141628, 137F58, 142180, 178440, 181040, 1308C8, 13AD28, 138C90, 1448C8, 139AA8 (reciben tex u64). SIGUIENTE:
  ver quién llama a cada uno y con qué tipo pasa el TEX0 (prototipos locales con s32/u32, o un TEX0 guardado en un campo
  s32 antes). Los prototipos de 136A00/178308/144EE0/140D18 revisados están bien o pasan punteros.
- Lote clases sin nombre: el crash viene de la clase 1EB270 (bisección confirmada). 1EB270 revertida en el árbol; las
  otras 12 clases quedan aplicadas en el árbol (experimental, NO en c23, sin build final). El haz sigue faltando:
  próximo paso, log en 18BBC0 (D_003877B4, obj+0x1D8, s2+0xA4, obj+0x1E0, ratio, +0xB4).
- (2026-11-04, noche) Rastreo del TEX0 truncado (alto en cero):
  * Logs TEMP "TEX0TRUNC" en 11 constructores REGLIST (137F58, 142180, 178440, 13AD28, 1448C8, 139AA8, 139390,
    12C468, 181040, 141628, 138C90; backups *.pre_tex0log): NINGUNO recibió el TEX0 truncado en una corrida N=3.
  * 12DA70/12E158 lo reciben de 12D170 (de 1A6A48: *(s64*)(w+0x200+seg*8)), 1B5150 (de 1B4AA0: *(s64*)arg10) y
    12C250 (de 1C55B8 = dibujo de la ESTELA: *(s64*)(rib+0x160); y de 1E9B80). Toda la cadena es de 64 bits ->
    el TEX0 YA ESTÁ truncado en memoria. SIGUIENTE: quién escribe rib+0x160 (EftRibbon), w+0x200 (1A6A48) y el arg10
    de 1B4AA0; buscar escrituras de 32 bits o la mitad alta (+4) que falte.
  * Los logs TEX0TRUNC siguen en el árbol (cvc), quitar al terminar. c23 no los tiene.
- CRASH INTERMITENTE (no es del lote): BtlTaskList_Draw con puntero nulo (frames 6605/7032/8909) y una vez
  func_001F3758+2 (lee arg+0x20 nulo; llamado desde 14A968). Aparece en corridas N=3, también con el c23 actual (1 de 3
  corridas); el estable de la mañana pasó 1 de 1. El lote de clases sin nombre está REVERTIDO entero en el árbol
  (backups *.pre_iscls2 contienen la versión original; la versión con arreglos se puede regenerar con el script).
- (2026-11-04) EftVram_AddImage (1F3918), EftRibbon_SetTexPair (1C4F00) y la carga de TEX0 de la estela (1C6B28)
  coinciden con el asm / son de 64 bits. AddImage SIEMPRE pone TCC (arg1<<34): los TEX0 truncados (TCC=0) nunca
  pasaron por AddImage -> vienen de una tabla de texturas copiada/armada en otro lado. Logs TEX0TRUNC agregados también
  en 12DA70/12E158 (con dirección de retorno). La prueba automática (Gohan) NO dispara el caso; build instrumentado
  copiado a c23 (backup bt2full_c23.pre_tex0log) para que el usuario haga el Kamehameha de Goku y revisar
  "TEX0TRUNC" en el .fight.log.
- (2026-11-04 mañana) Partida del usuario 20261104-110414 (Kamehameha de Goku): 0 TEX0TRUNC en los 13 constructores
  instrumentados, pero el volcado 13262 tiene 20 dibujos con TEX0 de alto cero (99302bcc, dd30ab8c, 55302b88), en
  paquetes REGLIST contiguos cada 0x70 (0x4520e8..), PRIM 0x5B. -> los arma otro constructor (src/ con estructuras
  o constante leída de datos). EftVram_AddTex (1F3830) revisado: correcto. Log TEMP "TEX0ADDTEX" agregado en
  AddTex (TEX0 con alto cero + dirección de retorno). c23 = build con todos los logs TEX0 (backup .pre_tex0log).
- (2026-11-04) CRASH BtlTaskList_Draw (también lo tuvo el usuario, partida 20261104-111509, frame 3034): un task de
  la lista con cls NULL (liberado por un callback de dibujo mientras se recorre; probablemente expuesto porque ahora
  Kill/Stop funcionan). En PS2 la lectura por NULL cae en RAM baja y el callback sale nulo; en PC la página cero no
  está mapeada. Arreglo: guarda `#ifndef __mips__` en BtlTaskList_Draw (src/battle/eft_ae_1F2D30.c) que saltea tasks
  con cls NULL. Backup .pre_nullcls. 2 corridas N=3 sin crash; c23 actualizado (backup bt2full_c23.pre_nullcls).
  Pendiente: el otro crash visto una vez (func_001F3758+2, desde 14A968) y averiguar qué callback libera el task.
- (2026-11-04) Partida 20261104-113211 (Kamehameha, 10 volcados F9): siguen TEX0 de alto cero (99302c48, ...c4c,
  ...c64, ...c68, 99402c58, 55302c60...). 0 avisos en AddTex ni en los 13 constructores. La textura 2c48 ni siquiera
  se sube en ese frame -> TEX0 VIEJO cacheado de otro frame y guardado sin la mitad alta. Búsqueda en el asm de la
  constante 0xF421...: 18 funciones; 6 sin instrumentar (12C9E8, 13A070, 1E5570, 1E5D00, 1EDD98, 1EE8B0) ->
  log TEX0TRUNC agregado (con dirección de retorno).

### B17 — Nivel de poder: letras blancas raras al llegar al nivel máximo (usuario, 2026-11-04)
- Al subir el contador de nivel de poder (1, 2, 3, ...) y llegar al nivel superior aparecen unas letras blancas que
  no son del juego y el contador se pone en blanco. Está en los volcados F9 de la partida 20261104-113211. Probable
  misma familia (TEX0/paleta del HUD). Pendiente.
- B17 visto en volcados 4298/4377 (contador "5" amarillo, bien) vs 4408/4658 (recuadro del contador vacío y trozos
  blancos pegados al borde izquierdo de la pantalla: las "letras" se dibujan desplazadas). Pendiente: volcado de esos
  frames buscando los sprites del contador (posición x negativa/0, TEX0 de la fuente del HUD).
- B17 (franja izquierda completa, idea del usuario): columna de dígitos del contador ("5","2","7"... blancos en 4408,
  naranjas en 4658) de arriba a abajo en x≈0-8. En el volcado 4407, en x 0..32 sólo hay pasadas de pantalla completa
  por columnas de 32 px que leen como PSMT8H (psm 0x1B, cbp 3e64/3e80/3e88; tbp 0e00/1c00) = channel shuffle, misma
  familia que B13 / pantallas blancas. Hipótesis: la primera columna lee una zona de VRAM donde está la fuente del
  HUD. Atacar junto con B13 (implementar el shuffle 8H/16 bits en el renderer).

## CLASE DE BUG: valor de 64 bits que pasa por un tipo de 32 (2026-11-04)
Regla: en el PS2 los registros y los argumentos en pila son de 64 bits (sd/ld). Si el C declara un parámetro,
variable, campo o prototipo como PUNTERO (u8 *, que en este port mide 32 bits por ptr32) o como s32/u32, y el valor
real es de 64 bits (TEX0 y otros registros del GS, tags GIF/DMA), la mitad alta se pierde en silencio.
Casos confirmados:
- 18DCB8 / 1A43C8: prototipo local `s32 EftVram_AddImage` (TEX0 truncado con signo) -> cuadrados blancos.
- 1E6400 (+ llamadores 1E4760, 1E4258, 1E3AC8): parámetro arg9 declarado `u8 *` (32 bits) recibía el TEX0; los
  llamadores además hacían `(u8 *)(u32)valor`. Firma en el volcado: TEX0 con los 32 bits altos en cero
  (00000000993xxxxx). Encontrado con logs TEMP TEX0TRUNC (10 576 avisos, todos de 1E5D00 llamado desde 1E6400).
  Arreglo: u64 en definición, prototipos y llamadas. Backups *.pre_tex0arg. 0 avisos después.
Señales para buscar: asm del llamador que guarda el argumento con `sd` en 0x0/0x8(sp) o lo arma con dsll32/ld,
mientras el C lo declara u8 * / s32; casts `(u8 *)(u32)x` o `(s32)x` sobre valores s64/u64.

## CRASH por desborde: 1A6A48 (dibujo del trail), 2026-11-04
- Tras activar el trail (comparación de clase arreglada) apareció crash en el ret de 1A6A48 (rbp con floats).
  `f32 vtx[36]` (144 bytes) vs asm sp+0x20..0x1EF (0x1D0 bytes): 12D170 recorta el triángulo y escribe vértices de
  más en ese buffer. Arreglo: vtx[116] alineado (backup 1A6A48.c.pre_vtx). 2 corridas N=3 sin crash; c23 actualizado
  (backup bt2full_c23.pre_tex0arg). Ojo: otros llamadores de 12D170 / 12C250 (clip) pueden tener el mismo problema.
- Barrido "64 bits por tipo de 32" (agente, port/eq completo, lado llamado y lado llamador + casts (u8 *)(u32)):
  sin casos nuevos confirmados; el único real era 1E3AC8->1E6400 (ya arreglado). Falta: src/**/*.c, campos/locales,
  y retornos de 64 bits declarados s32/puntero (además de AddImage).

## CERRADO: CUADRADOS BLANCOS (confirmado por el usuario, 2026-11-04)
"Ya no queda ningún rastro de cuadrado blanco." Causas: TEX0 truncado a 32 bits en 18DCB8/1A43C8 (prototipo s32)
y en 1E6400 + llamadores (parámetro u8 *). Backup estable: BT2-backups/estable_2026-11-04b/ (incluye logs TEMP TEX0
todavía; quitar).
REMANENTES (usuario): 1) B17 contador de nivel de poder: al llegar al 6 desaparece y aparecen caracteres raros en
la columna izquierda. 2) El haz de los rayos (Kamehameha, Masenko y similares) sale como bola flotante en vez de
un rayo láser continuo entre los dos jugadores. Después: pulir mecánicas.
- B17 CAUSA VISUAL (volcados 5379 bien / 5402 mal, partida 20261104-113828): en el frame malo el dígito del J1 se
  dibuja con OTRA textura (tbp 2a00 PSMT4 cbp 2c80 en vez de 2bc0 PSMT8 cbp 2caf) y medidas erróneas:
  pos (-48,42)-(16,370) = 64x328 (debería 32x32 en (16,42)), uv (0,32)-(64,360), z fffffffc. La "columna de
  caracteres" es la tira entera de la fuente estirada. Agente buscando el código del contador.
- Agentes en curso (2026-11-04): haz de los rayos; mapa de crashes (buffers chicos, recorridos de listas con nulos);
  B17 contador.

## B17 ARREGLADO (falta que lo vea el usuario), 2026-11-04
- func_0010EBF0 (port/eq/10EBF0.c) copiaba la tabla de dígitos del contador con memcpy 0x40; el asm copia 0x50
  (8 registros de 10 bytes: bucle de 0x40 + cola de 0x10 en 0x10ECC0). El registro del nivel 6 quedaba con basura
  de la pila (alto 328, x -48, índice de textura vacío -> tbp 2a00). Arreglo: 0x50. Backup 10EBF0.c.pre_0x50.
  c23 actualizado (backup bt2full_c23.pre_b17).

## Crashes: más arreglos (agente de mapa de crashes), 2026-11-04
- 1C55B8 (dibujo de la ESTELA): f32 tri[84] vs asm sp+0x280..0x42F (0x1B0): 12C250 recorta dentro -> tri[108].
  Backup .pre_tri.
- BtlTaskList_Update / PostUpdate / Reset (src/battle/eft_ae_1F2D30.c): misma guarda PC para tasks con cls NULL
  que BtlTaskList_Draw; en Update además re-chequeo de cls tras el callback. Backup .pre_nullcls2.
- 2 corridas N=3 sin crash. Pendiente del agente: callers de 1294B0, resto de arrays de 1C55B8, barrido general B,
  recorredores de listas en eft_b_1312C8 / eft_e_13EC30 / eft_c_c146D00 y EftOt_*.

## Haz de los rayos (agente, 2026-11-04)
- 189F50, 189EB8, 189EE8, 1889F8, 188D68, 1890C8 coinciden con el asm. Pista fuerte: 188D68 devuelve 0 si
  obj+0xC4 / obj+0xB4 < 1.0 (largo < espaciado) -> nunca crea nodos -> obj+0x1E0 NULL -> 18BBC0 no arma quads ->
  solo la bola. Siguiente: logs en 188D68:34 (C4, B4, ratio, s4+0xA4, obj+0x1E0), 18BBC0:34 (D_003877B4, +0x1D8,
  s2+0xA4, +0x1E0, nodos), 189F50 (pool agotado) y quién escribe obj+0xC4 (188218 / crecimiento).

## PRÓXIMA FASE (usuario, 2026-11-04): recorrer los menús
- Modo historia funciona, pero crashea en algunas viñetas. Torneo: faltantes en el menú y crash al iniciar
  cualquier torneo. Duelo, práctica, historia funcionan parcialmente. Plan: un agente con copia independiente
  del binario recorriendo todos los menús/modos y registrando crashes y faltantes, después de cerrar los remanentes.
- B17 CERRADO (usuario 2026-11-04): el contador llega a 7 y no imprime basura.
- (2026-11-04) BEAM, logs TEMP "BEAM" (188218, 188D68, 18BBC0, 188850; backups *.pre_beamlog):
  * Hay dos objetos rayo. El del haz largo (A4 3A4A) SÍ arma segmentos: hasta 25 nodos, largo C4 ~840.
  * La clase del objeto rayo está en 0x341F78: update 188218, init 187EC0, term 1889F0, postUpdate 188838,
    reset 188978, draw 188850. 18BBC0 no tiene referencias (código muerto o mal cortado).
  * El draw 188850 SÍ se llama cada frame con los nodos -> 1899F0 (A4 & 2 y & 8) -> por nodo 18A5A0 (quads),
    Vu0Screen_StoreMtx y 18A9C0 -> 12C250 con *arg7 = TEX0 (64 bits, bien).
  * Conclusión parcial: la geometría y la llamada de dibujo existen; el haz se emite pero no se ve (alfa/z/
    recorte/pantalla). Siguiente: volcado GS justo en el frame del haz (vive ~7275-7298 en la prueba; el
    BT3_GS_DUMP=hit volcó tarde, 7831) y revisar los prims de 12C250 de ese frame.
  * 1899F0.c tiene macros de depuración viejas (CHKREG/RB, fprintf a stderr): quitar.
- PROPUESTA DEL USUARIO (2026-11-04): log por estado del juego. Detectar en qué estado/escena entra el juego
  (menú, combate, etc.) y activar categorías de log según el estado, para tener un log total de cada pelea y
  después extenderlo a todos los menús (fase de menús).
- (2026-11-04, tarde) BEAM más logs:
  * Los 25 segmentos esperan ~4 frames (node+0xB4) y se activan; los que esperan tienen esquinas 0 y alfa 0 (normal).
    El primer volcado (colapso a un punto) se tomó con casi todos en espera: no era el bug.
  * 18A2C8 calcula las esquinas bien (coordenadas de mundo ~765,-79,-420); la matriz de pantalla (Vu0Screen_StoreMtx)
    es sana. 18A9C0 va por 12C250 (arg6 0) con TEX0 200546c5dd30ab8c; color del segmento ~(140..180,120..127,
    126..160) y alfa ~114-119 en los activos.
  * SOSPECHA ACTUAL: el ancho del haz es ínfimo. Media anchura de esquina = node+0x88*0.5 ≈ 0.57; escala
    obj+0x88*obj+0x80 ≈ 0.8..0.95 (obj+0x88 1.6->1.9) para un largo de ~840 -> línea finísima. Revisar el
    crecimiento de node+0x88 (fl&1: +0x90; fl&8: +0x94) y obj+0x88 (+0x8C/+0x90 según fase s3+0xA8/0xAC*30), y de
    dónde salen esos incrementos (creación del nodo 1890F8/188C48 y init 187EC0) contra el asm y BT3.
  * Logs TEMP BEAM en 188218, 188D68, 18BBC0, 188850, 1899F0, 18A2C8, 18A9C0 (backups *.pre_beamlog). 1899F0 y
    18A9C0 traen además diagnósticos viejos (CHKREG, patrón 0xCD de desborde) a limpiar.
- (2026-11-04) BEAM: agente de ancho sin diferencias (189F50/1890F8/187EC0/188218/18A2C8 OK). El objeto 1 (A4 3A4A,
  bits 2+8) dibuja quads cartel (bola/brillos). El CUERPO es el objeto 2 (A4 3A45, bits 1+4): 188D68 reparte nodos
  cada ~35 unidades a lo largo de C4 (crece ~26/frame), vida ~4 frames, quads por 189530 (update) y dibujo 1895D8.
  Ese objeto aparece SOLO en 1 de 5 corridas (beamdump3-125259) y vive ~20 frames. Siguiente: auditar 189530 /
  1895D8 y por qué el objeto cuerpo no siempre se crea (150C68 tipo 12, 187EC0).

## LOG POR ESTADO: mapa de escenas (agente, 2026-11-04)
- Game_Main = 100388: bucle Overlay_Load(0) -> Progress_Main (func_3B7FA8, menús) -> si gProgress+0x18 & 0x200
  func_002A8A38 (alternativo) si no Battle_Main (func_00103000).
- gProgress = *(u32*)0x3876A4. +0x1C = modo actual (1..64), +0x18 flags, +0x464 tipo de torneo.
  D_003876A0+0x480/+0x484: retorno tras la pelea.
- Modos: 1 título, 2 memory card, 4 menú principal (cursor en g+0xE8, func_003B3F38), 5 opciones?, 6-8 duelo?,
  10-16 ultimate battle?, 24-27 dragon adventure?, 30-35 torneo mundial, 38-41 evolution Z?, 43-47 data center?,
  48-51 / 53-58 submenús?, 61-64 entrenamiento. Cursor del menú principal: 0->6/7, 1->0xA, 2->0x18, 3->0x1E,
  4->0x3D, 5->0x35, 6->5, 7->0x26, 8->0x30, 9->0x2B.
- Plan: port/full/plat_statelog.c con bt2_statelog_frame() llamado junto a bt2_fightlog_frame (plat_gs.c:89).
- LOG POR ESTADO IMPLEMENTADO (2026-11-04): bt2_statelog_frame() en port/full/plat_fightlog.c, llamado cada vblank
  desde Port_VBlank (plat_gs.c). Activo con BT2_STATELOG=1 o BT2_FIGHTLOG. Anota en stderr (y en el fight.log) cada
  cambio de fase (MENU/BATALLA) y de modo (gProgress+0x1C) con nombre. Expone gBt2InBattle. Prueba: titulo(1) ->
  menu_principal(4) -> entrenamiento(61, 63) -> BATALLA. Backups plat_fightlog.c / plat_gs.c .pre_statelog.
- BEAM cuerpo (agente): 189530, 1895D8, 18AE98, 18B3D0, creación en 150C68/18BA90, reset 188978: coinciden con el
  asm. El cuerpo NO es un quad estirado: 1895D8 -> 18AE98 dibuja un sprite en pantalla por nodo y lo DESCARTA si
  hw<2 || hh<2 (hw = size*step>>12, step = 0x1000*camScale/w). Log TEMP en 18AE98 (backup .pre_beamlog).
  Hipótesis de "1 de 5": handle viejo en *objp (sólo se limpia con flags&4) — fiel al PS2, sin probar.

## B18 — Ultimate Battle: se traba tras completar una misión (2026-11-04) — ARREGLADO, falta probar en juego
- Síntoma: al volver de la pelea, el menú de misiones (func_003FD990 / 3FD328) espera que el script de mensajes en G+0x60
  ponga el bit 1 de +0x14 ("end"); nunca llega y la pantalla queda fija.
- Causa: **clase 6 — argumento perdido en una cadena de saltos (tail call)**. En el asm, 0x26EB78/0x26EB90 hacen
  `a0 = obj->0x18; j 26E1F0/26E238` y 26E1F0/26E238 pasan a1 sin tocar a func_0026CD98(script, etiqueta). El C
  (src/auto/auto_26eb70.c, m2c_26E1F0.c, perm_26E238.c) declaraba un solo argumento: la etiqueta llegaba como basura y el
  script nunca saltaba. 338 llamadas en todos los menús usan func_0026EB78: puede explicar otros cuelgues de menús.
- Arreglo: los tres archivos pasan a1. Backups `BT2-backups/*.pre_label`.
- Barrido clase 6 (2026-11-04, solo lectura; lista completa en scratchpad short.txt, 538 candidatos heurísticos).
  Confirmados contra asm: m2c_26EC48.c (pierde a1,a2 hacia 270438; UI de texto, 244708.c:169); auto_272cb0.c
  (0 args -> 276B00 usa 3); llamadas K&R func_002411A0() en ~24 m2c_241*.c (necesita a1); ~114 thunks auto_*.c sin
  parámetros con `j callee` (BtlTask_SetDead x70, func_002C2FF0, 260638, 2E0A98...) — en x86 suelen andar de casualidad.
  Sin verificar: Rand_Range con 1 arg (209 sitios), 3F9300 -> 3F5610 (1 vs 4), 2651B8/2655C0/2748B8, 3B4250, 24BE18.
  Orden propuesto: 26EC48, 272cb0, callers de 2411A0, thunks auto_* como clase (reenviar a0..a3).
- B18, causa real (el arreglo de la etiqueta solo no alcanzaba): port/eq/3FD610.c acumulaba el desplazamiento del bucle
  (p = p + off) y actualizaba G+0x10/0x38/0x88; el asm recarga G en cada vuelta (G+0x10/0x38/0x60). El script en G+0x60
  nunca corría. **Clase 7: bucles con puntero base recargado traducidos como acumulados**, a menudo marcados "GUESS".
  Backup `3FD610.c.pre_off`. Asm de overlays 0x3Fxxxx: no está en SLUS ni asm/cod; se lee de la memoria del proceso.
- Barrido clase 7 (2026-11-04): sin otros casos de "doble avance" (solo formas += / x = x + y). GUESS de menús revisados:
  ninguno toca bucles; para chequear contra asm: 3C0370.c:40 (s2 = 1 en un camino que no lo escribe) y 3F7CA8.c:12
  (base X+0x88 supuesta). ~120 archivos con GUESS fuera de menús sin triar.

## B19 — Ultimate Battle: 2.ª pelea seguida = bloques de color y 7-10 s por cuadro (2026-11-04) — mitigado, falta probar
- Log 20261104-160656: desde el cuadro ~12016, 0 GIF tags con 154925 escrituras de registro: el parser GIF (Gs_Gif,
  estáticas) quedó en medio de un paquete PACKED eterno; texturas basura (1e9 píxeles/cuadro). Disparo probable: el
  programa VU1 de 94 instrucciones (hle_program78) no matcheó, cayó al intérprete (pc 47, tope 500k) y dejó un tag abierto.
- Arreglo 1 (gs_core.c): estado del GIF a nivel archivo + gif_reset() al empezar cada lista (run_chain), con aviso
  "GIF packet left open". Backup gs_core.c.pre_gifreset. Pendiente si persiste: validar el tag A+D en top+0 en
  hle_program78 y demás; identificar programas VU1 por hash y no solo por tamaño; ver por qué el 94 no matcheó.

## Clase 6 masiva + build de traza funcionando (2026-11-04)
- El build instrumentado (BT2_TRACE_BUILD, -finstrument-functions) crasheaba en el vblank 27: pisa registros que el
  build normal deja intactos, y así expone cada argumento perdido (clase 6) que andaba "de casualidad".
- Arreglos (todos verificados contra el asm, automáticos con scripts en el scratchpad: kr.py, kr_apply.py, short.py):
  - a mano: 26C7A8 (3er arg a 26F930), m2c_26C6F8, m2c_26EC48 + hermanos 26EEC8/26F118/26F0E8/26EC18 (lw a0,0x1c; j).
  - 279 thunks auto_*.c `u32 f(void){return g();}` (asm: salto puro) -> reenvían los 8 registros de argumento.
    Backup BT2-backups/auto_thunks_pre_fwd/.
  - llamadas vacías `g()` cuyo asm deja a0.. intactos -> pasan los parámetros del llamador (kr/kr2/kr3, ~340 sitios),
    y definiciones `f(void)` que reciben y reenvían a0.. (42+). Backups kr*_pre_fwd/. Archivos con varias funciones se
    revirtieron (pendiente a mano).
  - llamadas cortas (menos args que la aridad; aridad del SDK deducida del asm) -> 34 sitios. Backup short_pre_fwd/.
- Resultado: normal pasa entrenamiento y duelo; el build de traza juega la pelea entera y vuelca la traza.
- `Rand_Range` (0x2BC568) es en realidad un printf de depuración (fmt, ...), mal nombrado.

## Dragon Tournament (2026-11-04)
- Crash al entrar (diálogo de Roshi): port/eq/3CABA8.c sin parámetro llamaba func_003C6CC0() vacío; el overlay (asm leído
  de la memoria del proceso) reenvía a0 = índice del paquete (3CB1D0 pasa 1). Arreglado (backup 3CABA8.c.pre_arg).
- Clase 8 (void que devuelve valor): port/eq/109C60.c (callback de la secuencia de batalla; el valor es el próximo
  estado en 105860; case 6 devuelve 1 por la jtbl 0x36C528). Arreglado: crash al entrar a pelea en UB con el build TOTAL.
- PENDIENTE: el menú no dibuja la caja de "How many entrants" ni el menú de niveles (Novice/Adept/Advanced/Master con
  Androide 18): pantalla negra / ausente, pero las teclas avanzan. El modo 24 es el torneo (la etiqueta de STATELOG
  "dragon_adventure?" es incorrecta). Overlay de menús: volcado en scratchpad ov3b.bin (0x3B0000..0x420000).
- ARREGLADO: menú del torneo sin recuadro/Androide 18/opciones. port/eq/3CBE58.c dibujaba 3 capas de script en vez de 4
  (asm 0x3CCE04: `li s1,3` + `addiu s1,-1` + `bgezl s1` = 4 vueltas). La capa G+0x88 (mc_textwindow, mc_Guide_* de 18,
  placas de nivel) nunca se dibujaba; la entrada sí avanzaba porque 3CCEE0 actualiza las 4. Clase 9: contador de bucle
  `bgez` traducido con una vuelta menos. Backup 3CBE58.c.pre_loop4.
- Clase 9, barrido: también 3F6778.c (4 capas, menú 0x3F) y 3FA8F0.c (5 vueltas de borrado). 173 bucles sin revisar (scratchpad f2.txt).
- Clase 9, revisión manual de los 173 bucles restantes (4 agentes): 0 errores. 1B2E68.c y 1D5548.c (marcadas como
  "incompletas" por un agente) se compararon contra el asm: están completas y coinciden. Falsa alarma.

## Regresión 3D negro en pelea (2026-11-05) — ARREGLADA
- Causa: la conversión de los 279 thunks auto_*.c a `u32 f(8 args){return g(8 args);}`. El asm es `j callee` (salto
  puro): pasa también argumentos de pila y flotantes; el envoltorio C los perdía (3D negro en pelea, HUD bien).
  Confirmado revirtiendo: sin la conversión el 3D vuelve.
- Arreglo: cada thunk es ahora un `jmp` crudo en asm (top-level __asm__), idéntico al original. Backups:
  auto_thunks_pre_fwd/ (original void) y auto_thunks_post_fwd/ (versión C rota).
- También: m2c_2188C8.c pasaba func_0023FCA8() sin a0 (crash UB, vblank 3608); detector extendido con aridad deducida
  del asm para funciones sin C (kr4/sh4: +57 llamadas; multi-función revertidas).
- Verificado: entrenamiento y Ultimate Battle (build TOTAL) se ven bien y no crashean.
- Regresiones (cámara trabada, CPU quieta en bucle de animación, spark del Kamehameha del lado del rival): el aplicador
  automático verificaba solo la PRIMERA llamada de cada función por archivo pero cambiaba todas. Verificador por llamada
  (scratchpad verify.py: cada llamada contra su propio jal, con registros escritos dentro de bucles) -> 12 archivos con
  args incorrectos, revertidos (backup verify_reverted/): 0023FF80 x2, 1F9530/1F9670 x3, 24BE18, BtlTask_SetDead
  (1355E0), Battle_GetSetup (23ED70), 2DCA68/2DDD70/2E1C98/2C2FF0. Prueba UB: CPU se mueve y ataca, cámara normal.
- Corrección del verificador: tomaba `break 0x0,0x7` (trampa de división) como salto hacia atrás -> 7 de los 12
  revertidos eran correctos (1F97A8/1F97F8/1F9848 -> 1F9530/1F9670, 240148/2402A8 -> 23FF80, 23ED70 -> Battle_GetSetup,
  1355E0 -> BtlTask_SetDead); re-aplicados. Malos de verdad (revertidos): 24BEA8, 2DCA68, 2DDD70, 2E1C98, perm_2C2FF0.
  El crash de TOTAL al empezar la pelea (1F9848 -> 1F9670 sin a0) queda arreglado.
- Pendiente: en el build TOTAL la CPU queda quieta (normal: se mueve). Otra llamada vacía que en TOTAL recibe basura.
- 200680 -> 2402A8: el original pasa en a0 el puntero al personaje que dejó 240040 (registro reutilizado); con eso
  2402A8 lee *(chr+0x68)=0x800 -> 0x810, memoria baja que en PS2 existe (basura inofensiva) y en PC es página cero:
  crash. Se deja el C original (pasa arg1). REVERTIDO; c23 restaurado desde bt2full_c23.pre_200680.
- El build TOTAL (instrumentado) no sirve para jugar: cambia qué queda en registros y rompe la IA/cámara por llamadas
  que en el normal funcionan de casualidad. Uso: detector. El acceso "modo debug" normal ahora incluye BT2_STATELOG,
  BT2_PADLOG, BT2_VULOG y BT3_VU_CALLS (todo menos la traza).
- B19, datos (log 20261105-204858, modo debug con BT2_VULOG): la 1.ª pelea nunca sube el microprograma de 94
  instrucciones (188 palabras, hash 1e5c688a = hle_program78 capa 3); la 2.ª lo sube ~400 veces. Con él,
  hle_program78 rechaza el lote (cantidad inválida en top+2) y el intérprete no termina (contador vi03=0x68ab/0x7fff):
  los DATOS del lote vienen mal, no el microcódigo. Más tarde aparece un MPG basura (addr 17251) como consecuencia.
  Un duelo normal (Goku vs COM) tampoco usa el 94. Siguiente paso: traza TOTAL de dos peleas UB y `trace_sym diff`.
- B19 CAUSA (traza en vivo con kill -USR1 durante la 2.ª pelea): el escenario con agua dibuja con el programa 8 (94
  instr). port/eq/29EE10.c Vu1Pkt_CallProg8 era void pero el asm devuelve el paquete de Dma_Alloc; Vu1Node_Draw
  escribía las matrices del lote a través de basura -> cabecera vieja -> VU1 en bucle -> GIF abierto. Arreglado
  (devuelve el paquete). También 272510.c (void -> devuelve el resultado de 272268, prueba de recorte que 2729D0 usa).
  Backups *.pre_ret. Falta probar en el escenario con agua.
- B19 causa real: el atajo de BT3 para "programa de 94" (hle_program78, entrada pc 15, MSCAL ignorado) se aplicaba al programa del agua de BT2 (mismo tamaño). Ahora se distingue por hash (1e5c688a) y va al intérprete desde la dirección real. Backup gs_vu1.c.pre_water.

## B20 — mapas que se rompen al empezar la pelea (2026-11-06, reportado por el usuario)
- Mismo error (pantalla de bloques, VU1 en bucle con el programa de 94 instr, GIF abierto): **Kame House**, **Atalaya de
  Kami-sama** y **Torneo de Artes Marciales** (el MAPA, no el modo). No depende del modo: en Dueling también falla
  (la 2.ª pelea de UB era en Kame House). Antes se llamaba B19.

## B21 — corrupción al meterse bajo el agua (2026-11-06, reportado por el usuario; video grabado)
- Glaciar e Islas se ven bien hasta que el personaje entra bajo el agua; ahí se corrompe, de otra forma que B20.
  Bug separado. Falta probar más mapas.
- B20 CAUSA RAÍZ (volcado F9 + VU94 log): Vu1Pkt_LoadProg8 sube el microprograma del agua con
  Dma_AddRef(D_002C3080, D_002C3380 - D_002C3080). En PS2 la resta = 0x300; en PC los dos arreglos no son contiguos ->
  REF qwc 30703: el VIF lee ~480 KB de memoria como comandos (MSCAL basura, programas en bucle, GIF abierto).
  Arreglo: tamaño 0x300 (port/eq/29EE90.c, backup .pre_size). **Clase 10: tamaños calculados como diferencia de
  etiquetas de datos** (otros Dma_AddRef en 29E7E8/29E938/29EF80/29E6D0 usan el patrón; hoy suben bien, revisar).

## B22 — "freeze" (10 s por cuadro) tras un ultimate (2026-11-06) — ARREGLADO
- No era un cuelgue: un log TEMP del haz (port/eq/188218.c) pedía un volcado GS al tener 18 nodos activos; el volcado
  ponía gGsDumpOnHit=2 y eso activaba un sondeo TEMP de gs_gl.c (cuadrados blancos) que lee el framebuffer entero dos
  veces por dibujo durante 400 cuadros. Quitado el pedido de volcado y el sondeo queda solo con BT3_PROBE_HIT.
  Backups 188218.c.pre_nodump, gs_gl.c.pre_probe. Pendiente general: limpiar los logs TEMP restantes.
- B21 análisis (video 20261105_230403 + log 20261105-230430, Islas): bajo el agua TODA la vista 3D se vuelve rayas
  verticales azul/violeta (cada columna un color; HUD bien); alterna limpio al cruzar la superficie. Contadores GS/GPU
  planos: la pasada de "bajo el agua" no se descarta, se dibuja mal (UV vertical colapsada). Mirar: pasada de
  framebuffer sobre sí mismo en gs_draw.c (selfCopy / targetColor, ~545-600, reescala 512x512, ST/Q, CLAMP), y los
  Dma_AddRef con resta de etiquetas (clase 10). Siguiente: F9 bajo el agua y comparar con un cuadro sobre el agua.
  Imágenes: scratchpad/agua/{sheet1,sheet2,dense}.png

## B23 — Ultimate Battle: el mando "se desconecta" al cambiar la dificultad (2026-11-06) — ARREGLADO Y CONFIRMADO POR EL USUARIO
- El juego seguía leyendo el pad; el menú (func_003F7F98) deja de procesar botones cuando X->0x194 != 0. En el selector
  de dificultad, 3F7CA8 guardaba X+0x88 (GUESS) en vez de 1 (asm 0x3F7ECC: sw a0 con a0 = X->0x198 = 1). 3F7710 es una
  máquina de estados sobre 0x194 que solo arranca con 1 -> el menú quedaba esperando sin leer botones.
  Arreglo port/eq/3F7CA8.c (backup .pre_194). Otro GUESS confirmado como bug.

## Referencias del original (PCSX2, video del usuario 20261105_234724) — BT2-test/referencia/pcsx2/
- 28 PNG recortados (crop 850:640:255:100): kamehameha_carga_1..4, kamehameha_disparo_1..7 (cuerpo largo del haz,
  flash blanco, impacto), skills_0..9 (menú de pausa "Look at Skill List": panel azul marino con borde claro, barras
  doradas por categoría con ícono de esfera, nombres con viñeta, íconos de botones PS2, texto celeste/rojo, barra de
  scroll), historia_1..7 (menú principal, Dragon Adventure, mapa del mundo con HUD de zeni y esferas, Northern Capital).
- Haz original: núcleo blanco muy brillante + halo celeste, gran destello dentado en las manos (~1/3 de la pantalla),
  cuerpo recto y de ancho constante hasta el rival, mancha brillante en el impacto; sin bola flotante al frente.
  El port solo dibuja la bola: faltan el cuerpo y el destello de las manos (B14).

## B24 — Modo historia, mapa del mundo: HUD de zeni roto (2026-11-06, captura del usuario)
- El contador de zeni muestra basura ("'((( 0") en vez de dígitos, y detrás del HUD de zeni/esferas se ve un
  rectángulo gris opaco. Referencia correcta: BT2-test/referencia/pcsx2/historia_4_mapa_mundo.png. Parecido al bug
  viejo del contador del power level (B17: tabla de dígitos con memcpy corto).

- B21 avance (F9 del usuario en Glaciar, log 20261105-235039, cuadros 5873 sobre / 6009 bajo el agua): la pasada bajo
  el agua es 1) sprites de 32->16 px que copian la imagen principal (tbp 0e00 = fbp 070) a un búfer de mitad de
  tamaño fbp 150 (256x256), 2) 90 tiras (prim 4, fst=1) sobre la pantalla que leen ese búfer (tbp 2a00, tw/th 512,
  UV a media escala con ondulación). Revisar en gs_draw.c (~560-620, textura = render target) la normalización de UV
  (us = tw/GS_W) y el contenido del búfer 0x150 tras la copia.

## B25 — Mapa del mundo (Dragon Adventure): al cruzar el borde norte, rayas verticales (2026-11-06, videos del usuario)
- Original (PCSX2): océano con horizonte y niebla celeste, cruce suave. Port: relleno celeste plano con rayas verticales
  claras, un cuadro con franja gris arriba; posición/cámara correctas (es de dibujo, no de lógica). Mismo aspecto que
  B21: probable búfer leído con otro TBW que su FBW. Imágenes: BT2-test/referencia/borde/{original,port}_*.png.
- B21/B25 arreglo intentado (2026-11-06): GsTarget.fbw + remapeo por páginas PSMCT32 64x32 en gs.frag cuando
  TEX0.TBW != FBW del búfer (gs_draw.c, gs_draw.h, shaders/gs.frag; backups *.pre_tbw).

## Pendiente clase 6 — 4 llamadas revertidas por un falso positivo del verificador (2026-11-06)
- El verificador recorría el asm en línea recta: en un if/else, el jal de una rama "pisaba" a1 para la otra. En el asm
  real a1 (= arg1) llega intacto a las DOS llamadas. Arreglo pendiente (pasar arg1 en ambas llamadas, prototipo `()`):
  src/auto/m2c_2DCA68.c -> func_002DCAB8(x, arg1); m2c_2DDD70.c -> func_002DDDC0(x, arg1);
  m2c_2E1C98.c -> func_002E1CE8(x, arg1); perm_2C2FF0.c -> func_002C3060(x, arg1) (verificar contra el asm).
  m2c_24BEA8.c (func_0024BE18 x3) revisar a mano.
- B21 estado al cerrar 2026-11-06: el remapeo TBW/FBW (c23 actual) NO lo arregló. F9 nuevos del usuario (log
  20261106-000321, cuadros 8236/8562/8749; copias en BT2-test/referencia/agua_f9/): con el juego EN PAUSA bajo el agua
  las rayas siguen -> el contenido del búfer ya está mal, no es un cuadro suelto. Ese log no trae el volcado de dibujos
  (solo PPM). Volcados detallados útiles: log 20261105-235039 (cuadros 5873 sobre / 6009 bajo, copias d_above/d_under en
  tools/sesion_2026-11-06/). Próximo paso: confirmar con BT3_GS_VERBOSE/volcado que el remapeo se activa (orig.x>0 en las
  90 tiras de tbp 2a00); si se activa, revisar la copia 0e00->150 (sprites 32->16) y el orden de páginas; si no, ver por qué
  gsTargets[src].fbw no es 4. Si empeora algo, revertir con los backups *.pre_tbw.
- B25 explicación del usuario (2026-11-06): al pasar el borde del mapa del mundo el juego "lupea" y te devuelve al
  inicio; la PS2 lo disimula con distancia/límite de dibujado (o niebla). El port no tiene ese límite y se ve el
  salto. PENDIENTE (posterior): agregar niebla o límite de dibujado en el mapa del mundo; buscar el punto de inserción
  (dónde el juego fija la distancia de dibujo / fog del overworld). No es prioridad.
- B21 análisis del agente (2026-11-06): la pasada bajo el agua copia la pantalla a fbp 150 con FBW 8 (512x224, media
  altura) y la lee con TBW 8: no hay cambio de ancho (el remapeo TBW/FBW no aplica). Causa probable: CLAMP modo 3
  (REGION_REPEAT: v = (v & MINV) | MAXV) tratado como REGION_CLAMP en gs_draw.c (~607-614) -> clamp con min > max en
  gs.frag -> una sola fila -> rayas. El sampler por software ya maneja el modo 3 (gs_core.c ~337).
- B21 arreglo aplicado (2026-11-06, falta probar): gs_draw.c solo usa el rango de CLAMP en modo 2; el modo 3 se trata
  como toda la textura, y nunca se pasa min > max al shader. Backup gs_draw.c.pre_clamp3.
- B24 causa y arreglo (2026-11-06, falta probar): los F9 del usuario (log 20261106-000321, cuadros 6678 malo / 6767
  bueno durante la acometida) muestran los dígitos del zeni con parámetros IDÉNTICOS (tbp 3000 psm 13). El port tomaba
  tbp 0x3000 como el búfer de dibujo fbp 0x180 que quedó de otra pantalla (regla "textura = búfer" sin antigüedad);
  la acometida agrega un búfer nuevo (16c), la tabla de búferes (24) descarta el viejo y el HUD se arregla. Arreglo:
  GsTarget.drawn; un búfer solo sustituye a una textura si se dibujó en los últimos 60 cuadros. Backup
  gs_draw.h.pre_stale. Imágenes: BT2-test/port/build/shots/gpu_06600/06678/06767.ppm.
- 2026-11-06 resultado de prueba del usuario (c23 con clamp3 + stale): B24 y B25 SIGUEN IGUAL (B25 no se tocó, solo
  documentado). La teoría "búfer viejo en 0x3000" de B24 no cierra (psm 13 con búfer -> el port SALTEA el dibujo, no
  muestra basura) y la caché de texturas valida por contenido (hash de páginas + paleta), así que la MEMORIA en 0x3000
  realmente tiene otros glifos en los cuadros malos. Hipótesis siguientes: (a) el juego sube los glifos del número a
  0x3000 y el C que elige los glifos está mal (como B17), o (b) la acometida usa otro camino de dibujo del HUD.
  Necesita el overlay del modo historia: volcarlo con el juego abierto en el mapa del mundo (/proc/<pid>/mem desde
  0x3B0000) y buscar quién escribe/sube a tbp 0x3000 (traza TOTAL en el mapa + `trace_sym first`). La regla de
  antigüedad de búferes (gs_draw.c, GsTarget.drawn) quedó: es inofensiva; revertir con gs_draw.h.pre_stale si molesta.
- B21: falta el resultado de la prueba con el arreglo de CLAMP modo 3.
- B14 (agente 2026-11-06): la creación del rayo (1513D0 caso 12 -> 150C68 -> 18BA90 -> 187EC0) coincide con el asm.
  Distinguir "objeto 2 nunca creado" (handle viejo en pass+a10*4+0x324) de "creado sin largo" (p4 == vTmp ->
  vector o+0x70 nulo): loguear *objp antes/después del caso 12 y |p4 - vTmp|. Menores: 18B960 void (clase 8, sin
  llamadores). El destello de las manos no se identificó (otro tipo del despachador 1513D0 o 195250 -> 18BA90).
- B14 log BEAMPOS (2026-11-06, en c23): 1513D0 caso 12 anota "BEAMPOS crear fl handle antes -> después, origen,
  destino, largo"; 187EC0 anota "BEAMPOS init obj id inicio dir largo". Sirve para ver si el cuerpo no se crea
  (handle sin cambio), si se crea con largo 0 o con origen/dirección equivocados. Se lee en logs/vivo/<fecha>.fight.log
  (acceso "modo debug"). Backups 1513D0.c.pre_beampos, 187EC0.c.pre_beampos. Quitar cuando se resuelva (TEMP).
- B14 hallazgo (log 20261106-091057, 2 Kamehameha visibles en el video con el destello de las manos y una bola chica):
  1513D0 recibió tipos 0,1,2,3,5,8,10,11 y NUNCA el 12; los logs TEMP de la clase 0x341F78 (188218...) no salieron:
  el objeto del haz (bola + cuerpo) NUNCA se creó. Lo que se ve lo dibujan otros efectos. El problema está ANTES de la
  creación: quien recorre la lista de efectos de la técnica y llama a 1513D0 no llega a la entrada tipo 12 (agente
  investigando: bucles, tablas, offsets, condiciones).
- B14 CAUSA RAÍZ (agente 2026-11-06, verificado en el asm de los 4): en 14B078/1535A0/165488/165F60 el C elegía el
  camino con `(type == 2) ? a3 : type`, pero el asm tiene `lw v0,20(sp)` (a3) en el HUECO DE RETARDO del
  `bne v0,s8` -> se ejecuta siempre: el camino lo decide a3. Con el C, las entradas con disparo 1/3/4/5 (eventos del
  disparo) iban a 0x14F2B8 y nunca a 0x14EFA8 -> la fila del haz (tipo 12) nunca se creaba. Arreglado (sel = a3).
  Backups *.c.pre_delayslot. **Clase 11: instrucción en el hueco de retardo (delay slot) ignorada por la traducción.**
  Pendiente: buscar el mismo patrón (`bne ...` + `lw v0,..(sp)` en el slot) en los ~45 llamadores de 1513D0 y en
  todo el código.
- B24 (agente, RAM en vivo 2026-11-06): el HUD del zeni es func_00259740 (main exe; el comentario dice "memory-card
  map" y está mal: es el HUD del mapa del mundo, clips mc_zeni_%d, mc_db_%d, mc_mappoint_*, mc_dummy_font).
  259740/24A8A0 (dígitos)/24AB10 (Num_DrawDigits) coinciden con el asm; la tabla de rectángulos en RAM es correcta.
  O sea, el juego elige bien las celdas: lo que está mal es el CONTENIDO de la memoria de video en tbp 0x3000 (otra
  imagen, probablemente una fuente subida encima). Siguiente: log de subidas/copias a 0x3000..0x3100 (BT3_UPLOG ahora
  incluye copias GS->GS y la dirección de origen; activado en jugar_debug.sh) y revisar el asignador de VRAM de las
  texturas Flash (26EBC0/26EC48) y la subida de fuentes.
- Clase 11, barrido 0x100000-0x200000 (agente 2026-11-06): ~440 candidatos, 17 de forma riesgosa revisados a mano:
  solo los 4 ya arreglados (14B078, 1535A0, 165488, 165F60) estaban mal; 16F118, 174E40, 154260, 190CA8, 1513D0,
  145DF0, 1488F8, 17A838, 1A9748 y los de 1A4404/1A7274 coinciden. Sospechoso aparte (no clase 11): port/eq/11BCD0.c
  ~43-64 (despacho de colisiones: el asm tiene un camino X==1, s1_70==0, s2_70!=1 que llama 11BA90 y aplica el golpe
  0x34 a otro objeto, que el C no parece reproducir). Pendiente: barrer 0x200000+ y los branch-likely.
- Clase 11, barrido 0x200000-0x340000 (agente 2026-11-06): 1 bug confirmado y arreglado: port/eq/266C20.c (sistema de
  scripts de interfaz; el último caso comparaba el tipo de tabla en vez del estado o->0x10 cargado en el hueco de
  retardo; backup .pre_delayslot). 11BCD0 (colisiones) REFUTADO: el C coincide (el bloque sospechoso es inalcanzable).
  Branch-likely: 1208 sitios listados, 1 revisado; sin revisar: 100FC8, 107860, 10E268, 10AF9C y los demás.
- B14 (2026-11-06, RAM en vivo, Goku en práctica, c23 CON el arreglo del hueco de retardo): sigue sin tipo 12. La tabla
  de efectos que recorre 14B078 (base *(ctx), filas 0x110, contador + entradas 0x20) tiene la FILA 12 VACÍA (filas
  con datos: 0,1,2,3,5,8,10,11 = los tipos del log). El cuerpo del rayo sale de OTRO camino: probablemente EftBlast
  (EftBlastObj_Create 0x191600 .. 194FA8) o 195250 -> 18BA90. Agente investigando. El arreglo de 14B078 & co. queda
  (es correcto según el asm).
- B24 (uplog en vivo 2026-11-06): CADA cuadro, desde el arranque, se sube una imagen PSMCT32 256x64 (dbw 4) a dbp
  0x3000; los dígitos del zeni se leen de tbp 0x3000 como PSMT8 256x64. Esa subida es la que pisa los dígitos. Falta
  saber quién la hace (¿una textura dinámica: fuente/"mc_dummy_font", video?) y si en el original va a otra dirección.
- F9 ahora incluye "clamp" y "tex0" completos en cada línea de prim (gs_core.c, backup .pre_dumpclamp): sirve para
  confirmar B21 (modo de CLAMP de las tiras bajo el agua).

## Hallazgo 2026-11-06: B21 (agua) y B24 (zeni) probablemente comparten causa — ORDEN DE PATH3
- B24: en el mapa del mundo el juego usa tbp 0x3000 como área de paso: ~11 subidas por cuadro (128x32 x6, 64x128,
  128x16, 128x64, 256x64...; uplog con BT3_UPLOG=3000,3100), cada una para dibujar un elemento del HUD. En el volcado F9
  los dibujos que leen tbp 3000 usan 5 texturas distintas (256x128, 256x64 x12, 256x32, 128x256, 512x256), pero
  NINGUNA de esas subidas está dentro de la cadena VIF1 del cuadro: llegan por el canal GIF directo (PATH3,
  Port_GsGifChannel, gs_core.c ~1307) y el port las procesa en el momento del kick -> todos los dibujos leen la última.
  En la acometida cambia el orden y se ve bien. F9 del usuario: log 20261106-092611, cuadros 2043/2679 (malos) y
  2820/3237 (buenos).
- B21: las 270 tiras bajo el agua (tbp 2a00) usan CLAMP_1 = 0x380080000a = REGION_CLAMP (2) en u y v, MINV 0 MAXV 14:
  v (0..224) queda recortada a 0..14 -> rayas verticales. La pasada bajo el agua no escribe CLAMP: hereda el de un
  dibujo anterior (14 filas: típico de un glifo/elemento del HUD). Con otro orden de dibujos (como en la PS2) heredaría
  otro. Log 20261106-092611, cuadros 9570/9636/10042/10065 (Glaciar). El arreglo del modo 3 (gs_draw.c) no aplica.
- Siguiente: estudiar cómo sincroniza el juego PATH3 con PATH1/2 (MSKPATH3, FLUSHA, kicks del canal GIF vs la cadena
  VIF1 del cuadro) y hacer que Port_GsGifChannel respete ese orden (encolar y ejecutar en el punto correcto) en vez de
  ejecutar al instante. Es un cambio de arquitectura en gs_core.c: hacerlo con cuidado y probar menús, HUD y peleas.

## B14 — arreglo aplicado 2026-11-06 (falta probar)
- El cuerpo del Kamehameha es un objeto del módulo EftBlast (clase update 0x194948), creado por 150E90 (desde 1513D0,
  0x151E3C) con 0x194D18. Sus funciones de configuración (posición, dirección, largo, matriz) comparaban la clase contra
  la dirección de la PC (func_00194948) -> nunca coincidía -> el objeto quedaba sin posición/dirección (bola sola).
  Clase 1. Arreglado en 194FA8, 1951D0, 195180, 194EC8, 194D90, 194DE0, y además 194E70/195128 (faltaba una
  desreferencia). Backups *.pre_cls194948. Pendiente: el módulo 0x191238 (191688, 1916D8, 191728, 191890, 1918F8,
  191960, 191768, 1917B0, 191838) tiene el mismo error (no está en el camino del Kamehameha).
- B14 (2026-11-06, F9 2947-2968 del usuario): destello de manos e impacto OK; falta solo el CUERPO. Tipos 12 y 13
  nunca llegan (ni 0x341F78 ni EftBlast se crean). Los descartes de GPU no cambian (272/cuadro): el juego no dibuja el
  cuerpo. Re-aplicado el lote de clases sin nombre (clase 1) en 28 archivos (comparaciones (s32)func_X / &func_X ->
  literal PS2; se excluye 0x1EB270, la que se asoció a un crash). Backups iscls3_pre/; c23 backup .pre_iscls3.

## B14 — CAUSA PROBABLE ENCONTRADA 2026-11-06 (arreglado, falta probar)
- 0x1957D8 estaba mapeado (config/c_files*.txt, "from BT3-Decompiled") a src/sys/mem_read_1957D8.c como
  `Mem_ReadU16(p) { return Mem_LoadHalf(p); }` (lectura de memoria de BT3). En BT2, 0x1957D8 es un puente puro a
  0x195250 (en el port llamado "Mem_LoadHalf", pero es el CREADOR DEL RAYO de la técnica: crea el cuerpo vía 18BA90
  cuando a1 == 0). Lo llama 195738 (`Mem_ReadU16(t, 0)` cuando el personaje está en técnica). El puente pasaba 1 solo
  argumento -> a1 basura -> 195250 volvía sin crear nada -> nunca hubo cuerpo del Kamehameha.
- Arreglo: Mem_ReadU16 = `jmp Mem_LoadHalf` en asm (reenvía todos los registros). Backup mem_read_1957D8.c.pre_beam.
- LECCIÓN: funciones importadas de BT3 por dirección pueden ser OTRA función en BT2 (nombres engañosos). Revisar los
  demás archivos de config/c_files*.txt marcados "from BT3-Decompiled" contra el asm de BT2.
- Los otros arreglos de B14 del día (14B078 & co. hueco de retardo, clase 1 en el módulo 194948, lote de clases sin
  nombre) son correctos según el asm pero no eran la causa del rayo; se dejan.

## 2026-11-06 (cierre) — hipótesis PATH3 REFUTADA (agente)
- En el juego no hay tráfico por el canal GIF (PATH3): las subidas del HUD a tbp 0x3000 van DENTRO de la cadena VIF1
  (CNT con FLUSHE+DIRECT -> BITBLTBUF; REF con TRXPOS/TRXREG/TRXDIR+IMAGE; paleta a 3080; TEX0; dibujo) en orden, y el
  port las procesa en ese orden (run_chain -> Gs_Gif -> transfer_data; texture_get con hash de contenido). Cuadro malo
  2043 y bueno 2820 tienen el mismo orden; difieren en CONTENIDO (el malo dibuja 6 elementos a fbp 000 en vez de 070).
- B24 candidatos: (1) la reinterpretación de datos subidos en 32 bits (128x32 psm 00) leídos como 8 bits (256x64 psm
  13): swizzle de bloques/columnas en Gs_VramRead/Gs_BlockPtr; (2) la paleta 3080 (16x16 32 bits, CLD 1); (3) estado del
  juego (en el cuadro malo el HUD va a fbp 000). Prueba barata: en el cuadro 2043, comparar texel y bytes subidos.
- B21: el CLAMP_1 0x380080000a no viene de PATH3; buscar el último "reg 08" (o CLAMP en REGLIST/PACKED o XGKICK de
  VU1) antes de las 270 tiras; ojo: el volcado 9570 muestra clamp 3fc003fc00a en las tiras de 2a00 (verificar qué
  cuadro tiene el valor malo). Revisar también confusión de contexto 1/2 (PRMODECONT/PRMODE) al elegir CLAMP.
- Sugerencia: agregar al volcado F9 las escrituras A+D a 0x50-0x53 y 0x08/0x09 (gs_core.c ~919).
- Archivos del agente: tools/sesion_2026-11-06/asm/dis.txt (desensamblado completo) y f9570.txt.

## 2026-11-06 (cierre) — trabones progresivos en la sesión 20261106-094032 (torneo/duelo, c23 con el puente 1957D8)
- Cuadro 3469: 3,3 s en la lista de dibujo; cuadro 3483: 7,8 s en el CÓDIGO DEL JUEGO; fps 4,9 en t=79 s. Sin F9 en
  esa sesión (no son volcados). El Kamehameha sigue igual.
- Sospechas: (a) el arreglo nuevo de 0x1957D8 hace que 195738 (llamada CADA cuadro durante una técnica) ejecute el
  creador 195250 -> si crea objetos/tareas sin liberar, la lista crece y cada cuadro es más lento ("cada vez más");
  (b) volumen de logs del modo debug (MPG ~10 líneas/cuadro, uplog ~11, vucalls, fight.log) en disco.
- Para probar (a): revertir src/sys/mem_read_1957D8.c desde BT2-backups/mem_read_1957D8.c.pre_beam (o c23 desde
  bt2full_c23.pre_beamthunk) y ver si el trabón desaparece; si es (a), revisar qué crea 195250 por cuadro (EftPtcl3_Create
  y 18BA90) y cómo lo libera el original (manejadores, banderas) contra el asm.

## B21 — CAUSA ENCONTRADA 2026-11-06 (arreglado, falta probar): CLASE 12 — literal de 64 bits con un dígito de más/menos
- Las tiras bajo el agua usan CLAMP_1 = 0x380080000a (MAXV 14). Lo escribe port/eq/285028.c:177 (efecto submarino,
  traducción a mano): `(H << 14) | 0x3800000000ULL | 0xA`. El asm (0x285738: ori 0xE000; dsll 26) da 0x38000000000
  (MAXV 224). Al literal le faltaba un 0 -> v recortada a 0..14 -> rayas verticales.
- Mismo error en el gemelo port/eq/282640.c:94 (0x6FC0000000 -> 0x6FC00000000, asm 0x2828A4 ori 0xDF80; dsll 27) y
  :238 (0x37C0000000 -> 0x37C00000000, asm 0x282E90 ori 0xDF00; dsll 26), y al revés en port/eq/27FD28.c:38
  (0x700000000000 -> 0x70000000000, asm 0x27FE48 ori 0xE000; dsll 27).
- Backups: BT2-backups/{285028,282640,27FD28}.c.pre_clampmaxv; c23 anterior: bt2full_c23.pre_clampmaxv.
- Clase 12 (nueva): constantes de registros GS escritas a mano con un dígito hexa de más o de menos. Verificar
  siempre contra la secuencia lui/ori/dsll/dsll32 del asm. Barrido general con agente en curso.
- B24 (zeni): descartado el swizzle 32->8 bits (vram_rw/Gs_BlockPtr PSMT8 = tabla de bloques de PCSX2, bw/2 páginas
  por fila). Síntoma "'((( 0": los glifos salen corridos 8 lugares ('0' 0x30 -> '(' 0x28), 128 px en una fuente de
  16 px = un ancho de página PSMT8; pendiente del barrido de clase 12 (HUD 259740, 24AB10, 249A98, 26E*).
- B14 (Kamehameha, cuerpo del rayo): queda como TRABAJO EN CURSO (WIP), prioridad baja por decisión del usuario
  (2026-11-06). El puente 0x1957D8 NO era la causa de los trabones progresivos (confirmado por el usuario).
- Barrido clase 12 (agente, todos los port/eq con asm): 1 caso más, port/eq/285028.c:143 ZBUF_1 0x13100000E0 ->
  0x1310000E0 (asm 0x28556C..7C). Arreglado (backup 285028.c.pre_zbuf). No hay otros; el zeni no viene de esta clase.
- 2026-11-06: B21 (agua) CONFIRMADO ARREGLADO por el usuario (clase 12, c23 con los 5 arreglos).

## 2026-11-06 (tarde, sistema Arch) — hallazgos del usuario con la ventana por software (jugar_software.sh)
- B24 zeni: con el renderer por SOFTWARE el HUD del zeni se ve BIEN -> el juego, la subida a tbp 0x3000 y la memoria
  de video son correctos; el fallo está en el camino de GPU (OpenGL). Verificado además: las dos texturas de 0x3000 que
  decodifica la GPU (panel y atlas de dígitos) salen correctas con fondo transparente; caché, estado y mezcla coinciden.
  Síntoma real: los 5 dígitos son sprites de 32 px cada 14 px (se superponen) y se ven con fondo opaco.
- B14 Kamehameha: con el renderer por SOFTWARE TAMBIÉN es una bola flotante (usuario). No es del renderer: vuelve la
  teoría de que es el CÓDIGO DEL JUEGO (creación/actualización del cuerpo del rayo). Sigue WIP, prioridad baja.
- Nueva herramienta: ventana para el renderer por software (BT3_SW_WINDOW=1, gs_core.c sw_window_present; teclado y
  mando habilitados en gs_input.c). Base para comparar GPU vs software y para el futuro back end Vulkan.

## B24 — CAUSA Y ARREGLO (2026-11-06, en c23; backup bt2full_c23.pre_b24fix)
- Backend OpenGL (gs_gl.c, bucle de frame_end): los dibujos comunes suben sus parámetros de shader (mode/misc/rect/orig)
  a un búfer uniforme compartido y lo SALTEAN si son iguales a los del dibujo anterior (lastFu/haveFu). Los pases
  nativos (native 3 = niebla por profundidad/tabla, y los demás efectos nativos) escriben OTROS números en ese mismo
  búfer (set_params(params, 16)) sin invalidar lastFu. El primer dibujo del HUD después de un pase nativo, con los mismos
  parámetros que el último dibujo común, no los volvía a subir: el shader leía los números del efecto como modo de textura
  y alfa -> fondo opaco (dígitos de 32 px cada 14 px tapándose: "'((( 0"; recuadro gris del panel). Depende del orden de
  dibujo (la acometida lo cambia y "lo arreglaba"); el renderer por software no tiene ese búfer (se veía bien).
- Arreglo: haveFu = 0 después de cada pase nativo que llama set_params. Verificado sin ventana: "10000 Zeni" correcto.
- Cómo se encontró: ventana por software (BT3_SW_WINDOW, usuario confirmó que ahí se ve bien) -> texturas leídas desde la
  GPU correctas -> sonda por dibujo (BT3_PROBE_FROM) mostró que el panel cambiaba TODOS los píxeles de su rectángulo.
- Pendiente: revisar si el back end Vulkan (gs_gpu.c) reutiliza parámetros del mismo modo.
- Hipótesis descartadas: PATH3, swizzle 32->8, clase 12, caché de texturas (2 texturas correctas: panel y atlas), mezcla GL.

## B26 — modo historia: globo de diálogo corrido hacia abajo (2026-11-06, F9 del usuario)
- Sesión 20261106-152146, F9 10732 (Eastern Capital) y 12275 (Northern Capital): el globo blanco arranca a y~265 y se
  sale por el borde inferior; el texto queda abajo (4.ª línea pegada al borde). El globo se ve semitransparente.
- Volcado: el TEXTO y el botón los manda el juego en esas coordenadas (letras en y 346..420, botón en 420,395, fbp 070,
  tbp 2a08): el renderer dibuja donde el juego dice -> la posición sale del CÓDIGO DEL JUEGO (layout del diálogo) o de
  un parámetro (alto de pantalla, modo entrelazado 224/448, posición de cámara). Falta referencia del original
  (captura de PCSX2 del mismo diálogo) para medir cuánto está corrido.
## B27 / B28 — Ultimates de Maestro Roshi y de Piccolo (2026-11-06, reportado por el usuario): síntomas a anotar al probar.
- B26 CORRECCIÓN DEL USUARIO: el globo está bien puesto; lo que se corre hacia abajo es el TEXTO.
- Medido en los volcados (coordenadas del juego, 448 de alto): renglones cada 25 px. Con 3 renglones el primero
  empieza en y 346 (346/371/396); con 4 renglones en y 343 (343/368/393/418). Agregar un renglón sube el bloque solo
  3 px (si se centrara verticalmente subiría ~12,5): el centrado vertical del bloque de texto está mal calculado, o
  el origen Y que recibe la función de texto. Es del CÓDIGO DEL JUEGO (el renderer dibuja donde el juego manda). Fuente:
  tbp 2a08 psm 14 512x128, sombra rgba 40404040 a +1,+2. Siguiente: ubicar la función que arma los renglones del
  diálogo (llamadas que suben el bloque de letras a tbp 2a08) y revisar el cálculo de Y (clases 6/9/12, floats).

## B14 — avance 2026-11-06 (sesión del usuario 20261106-152736, F9 15383-15562)
- Con el arreglo del puente 0x1957D8 el OBJETO DEL CUERPO DEL RAYO YA SE CREA (BEAM 188218 obj, 188D68 36 nodos, 188850
  dibuja hasta 64 nodos). No se ve porque port/eq/18A2C8.c (matriz de cada tramo) da NaN: "BEAM 18A2C8 pre ... M0 nan" —
  la matriz ya es NaN antes de transformar los vértices; el medio ancho y f12 están bien.
- Sospecha: diferencia de FPU (la PS2 no tiene NaN/Inf: asin de |x|>1 por redondeo, sqrt de negativo, 0/0 dan números
  finitos en consola). Candidatos: Mathf_Asin(-dir.y) (0x30D610, libm), atan2f, o la matriz copiada de arg1.
- Log ampliado (TEMP BEAM en 18A2C8: dir, asin, atan, arg1, f13/f14; backup 18A2C8.c.pre_nanlog) en bt2full_cvc:
  falta UN Kamehameha del usuario con ese binario para cerrar la causa.

## Cierre de sesión 2026-11-06 (noche): todos los remanentes quedan en WIP (decisión del usuario). Ver docs/RETOMAR.md.
- B14 (agente): el C de 18A2C8 es fiel al asm. Cadena probable del NaN: Mathf_Asin (0x30D610) -> __ieee754_asinf
  (0x30DAB0) = asinf del host (plat_sdk.c:106); para |x|>1 la consola hace 0/0 y la FPU PS2 da +Fmax, el host NaN;
  EftMath_WrapAngle (src/battle/xa_12AEE0.c:367) deja pasar el NaN. Falta el dato dir.y (log "BEAM 18A2C8 dir" ya en
  bt2full_cvc). BUG APARTE confirmado por asm: port/eq/128C58.c escala m[0],m[4],m[8] y el asm escala la diagonal
  m[0],m[5],m[10] (vmulx.x/.y/.z) -> deforma la escala del tramo. Sin aplicar.
- B14 2026-11-06 (usuario, c23 con 128C58 diagonal + asin acotado en 18A2C8): SIGUE IGUAL. El asin NO es la causa.
  Contención de 18A2C8 revertida (backup 18A2C8.c.contencion_descartada); 128C58 (diagonal) se queda: es fiel al asm.
  Siguiente: correr un Kamehameha y leer "BEAM 18A2C8 dir" (dir y arg1) para ver qué entra ya en NaN.
