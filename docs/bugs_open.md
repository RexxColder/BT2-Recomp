# Bugs abiertos (BT2 native) — actualizado 2026-10-23
Escenario de prueba: Dueling, Goku vs Kid Gohan, Dying Namek. Preferido COM vs COM; ahora tambien J1 vs J2 con scripts
(BT3_PAD/BT3_PADFILE = J1, BT3_PAD2/BT3_PADFILE2 = J2) para sesiones identicas contra PCSX2.

| id | sintoma | estado | pista |
|----|---------|--------|-------|
| B1 | el oponente no conecta golpes | abierto | args perdidos en thunks/m2c corregidos (2026-10-23), reprobar |
| B2 | oponente golpeado queda en hit-stun con inercia | abierto | idem, 2F7D68->2F03E0 arreglado |
| B3 | tras el primer especial no se puede golpear; ki/ondas solo una vez o solo durante acometida | abierto | 218C18->23F918 arreglado, reprobar |
| B4 | al salir de la pelea el menu no dibuja sprites (constructores dejan de correr) | RESUELTO 2026-10-29 (29E6D0 devuelve puntero) | UB en perm_278D40 (teardown) corregido; reprobar con trace build |
| B5 | texturas corruptas | abierto | |
| C1 | clase "arg perdido": thunks auto_*/m2c_* y llamadas `F()` sin args | corregido ~900 sitios | /tmp/emp.py (reenvio a0), fixfwd.py |
| C2 | clase "ret perdido": funcion void cuyo valor se usa (ej. 0029E6D0) | 1 corregido, quedan RET_USED_BUT_VOID 154 | docs/agents/b12/check_calls_report.txt |
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

## B5 — crash intermitente en Vu0Screen_StoreMtx (29-oct)
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
Referencia: frames del video "DBZ BT2_ Ultimate Gohan 1v3 Duel" en el scratchpad de la sesión (ref/).
