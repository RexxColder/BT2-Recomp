# Auditoría: ventanas/grupos de texto (globo + botón X)

Fecha: 2026-11-06. Solo lectura sobre el proyecto. Fuentes: `port/eq/*.c`, `src/auto/*.c`,
`port/build/recomp/*.cpp`, `tools/sesion_2026-11-06/asm/dis.txt` (asm del ejecutable principal),
volcados F9 y videos de `BT2-test/logs/vivo/` (sesiones 20261106-203244 y 20261106-200837).

## Resumen ejecutivo

- **No existe una llamada común de posicionamiento del grupo `mc_textwindow`.** Todas las
  funciones de ventana que audité obtienen el handle y dibujan el texto (`func_249FB8`), pero
  **ninguna llama `func_26EEC8` sobre ese handle**. `func_26EEC8` solo se usa para cursores,
  placas, flechas y sub-elementos.
- El globo de la intro **no es el clip `mc_textwindow`**: es un sprite GS con textura dinámica
  `tbp 2a00 psm 14 512x256 cbp 2dc0` (`tex0 2005b80625422a00`). El texto se dibuja aparte con
  la fuente del juego (`2A38C0`/`249FB8`).
- La conclusión de trabajo “el padre está en (0,0) en la intro y en (213,306) en el modo
  historia” **no está probada y la evidencia la contradice**: los dos volcados comparados
  (frame 4595 intro vs 9452 historia) no son el mismo cuadro de animación (distinto `st` y
  distinta escala). Además, el mismo dibujo aparece exactamente en (-489.0,-129.7) en *las dos*
  sesiones (frames 4217 y 3532), lo que descarta un offset fijo de padre de (213,306).
- Lo que sí muestra el video: en la intro de pelea el globo + botón X quedan **quietos en el
  offset inicial de la transición de página** (X arriba a la izquierda, globo fuera de pantalla)
  y el texto se dibuja igual; en el mapa/historia el mismo globo llega a (-1,223) con el texto
  adentro y la X abajo a la derecha. **Causa probable: el layer/sprite del globo no se avanza
  por cuadro en la intro de pelea (timeline/keyframe), no un argumento perdido de posición.**

## 1. Funciones que crean o posicionan ventanas y sus grupos

`EEC8` = `func_26EEC8` (set position, ver `port/eq/270568.c`: escribe `x` en nodo+0x4C,
`y` en nodo+0x50, flag +0x48|=2). `EBC0` = buscar clip por nombre. `EC48` = rect/uv.
`EFC8` = visibilidad. `EB20` = frame/scroll del layer (`+0xC`/`+0x10`), **no** es x/y.

| Función / archivo | Qué ventana/grupo toma | Cómo lo posiciona | ¿Posiciona el `mc_textwindow`? |
|---|---|---|---|
| `func_00244708` (`port/eq/244708.c`, tienda) | `mc_textwindow` (L74) | texto con `249FB8(0,0)`; sub-elementos con EEC8: (0,0), (15,45), (50*TAB,0), flechas (0,36*(CUR-SCROLL)) | **No** |
| `func_003CBE58` (`3CBE58.c`, modo torneo) | `mc_textwindow` (L55) | texto; EEC8 solo en placas/sub-elementos (0,60*MODE), (17*LEVEL,33*LEVEL) | **No** |
| `func_003D4518` (`3D4518.c`, torneo/match card) | `mc_textwindow` (D_00425F98), `mc_button_icon` | texto; EEC8/EB20 solo para frames de luchadores y flechas (L108, L280, L319) | **No** |
| `func_003D9098` (`3D9098.c`, potara) | `mc_textwindow` (D_00426458) | texto; EEC8 en cursor/categoría/barra/yes-no (L208,297,321,381) | **No** |
| `func_003EDA48` (`3EDA48.c`, entrenamiento) | `mc_textwindow` (D_00429B20) | texto; EEC8 en pestañas/placas (L117,120,129,139,219) | **No** |
| `func_003E0040` (`3E0040.c`, zukan) | `mc_textwindow` | texto; EEC8 solo pestaña (L91) | **No** |
| `func_003DF028` (`3DF028.c`, **menú de páginas/libro**) | `mc_yazirusi_t_z`, `mc_page_title`, `mc_page_namber`, `mcGuideEye/Mouth`, `mc_textwindow` | EFC8/EC48; **no hay ningún EEC8 en la función** | **No** |
| `func_00403420` (`403420.c`, opciones) | `mc_textwindow` (L61) | texto; EEC8 en resaltado y filas con `xoff/yoff` (L66,156,178,180,199,228,232) | **No** |
| `func_0041DBB0` (`41DBB0.c`, logros) | `mc_textwindow`, `mc_button_icon2` | texto; EEC8 en placas/selección (L166,170,206) | **No** |
| `func_0029C1E8` (`29C1E8.c`, placa general de pelea) | `mc_general_plate_text_on` | EEC8(sel*0x96,0) (L104) | No aplica (no es textwindow) |
| `func_003B8E88` (`3B8E88.c`, mapa/puntos) | objetos de mapa | EEC8(s3,s3) y EEC8(obj+0x4590+s3, obj+0x4594+s3) (L160,164,211,222) | No aplica |
| `func_003F9B80` (`3F9B80.c`) | lista/placa | EEC8(0,70*v) (L76) | No aplica |
| `func_00406CA0` (`406CA0.c`) | placas/anim | EEC8 y EB20 para placas y animaciones (L120,123,167,176,202,236,253) | No aplica |
| `func_002A38C0` (`2A38C0.c`, **texto de pelea**) | registros `D_003B0F7C` (0x68 bytes) | dibuja texto con `Font_PrintAt(var_s2,var_s0,...)`; x/y salen de +0x50/+0x54, +0x58/+0x5C, +0x60/+0x64 según lado (+3/+6) | **No toca Flash** |
| `func_002A3EA8` (`2A3EA8.c`) | registro + plantilla `D_003B1F98` | copia 0x58 bytes de `D_003B1F98` a `r+0x10`; llama `2A42C8/2A4148/2A4420` | **No toca Flash** |
| `func_002A4148` (`2A4148.c`) | sprite de 128x256 por lado | calcula s1=-2 (lado <0) o 386 (lado 1), s2=200 y llama `2A4CF0`; es retrato/sprite, no el globo 512x256 | **No** |

Conclusión de la tabla: **no hay un punto único de posición de la ventana**. El único API de
posición (`EEC8`→`270568`) se usa para elementos hijos, nunca para el contenedor de la ventana.
Por eso “arreglar la llamada EEC8 que falta” no es una opción: no existe tal llamada.

## 2. La intro de pelea: qué se midió de verdad

Dibujo del globo en los F9 (misma textura, mismo tamaño):

- `20261106-203244.log:157809` (F9 frame 4217):
  `(-489.0,-129.7)-(31.0,130.3)` `uv (0,0)-(512,256)` `st (0.000,0.000)`.
- `20261106-203244.log:183355` (F9 frame 4595, intro Piccolo/Broly):
  `(-214.0,-83.0)-(310.0,179.0)` `st (0.000,0.000)`.
- `20261106-200837.log:136530` (F9 frame 3532, historia):
  `(-489.0,-129.7)-(31.0,130.3)` **exactamente igual** al de la intro.
- `20261106-200837.log:160988` (F9 frame 3828): `(-217.0,-84.0)-(313.0,180.0)` (casi igual al de 4595).
- `20261106-200837.log:448257` (F9 frame 9452, globo asentado):
  `(-1.0,223.0)-(513.0,479.0)` `st (0.016,0.000)`.
- `20261106-200837.log:197738` (F9 frame 4029): `(-256.0,1401.0)-(256.0,1657.0)` (otra página).

Lo importante: **(-489,-129.7) es idéntico en las dos sesiones**. Si el padre de la intro
estuviera en (0,0) y el de historia en (213,306), ese mismo cuadro de animación no podría caer
en el mismo píxel. Además los cuadros comparados por el usuario tienen `st` y escala distintos
(524/512 = 1.0234 en la intro vs 514/512 = 1.0039 en 9452): son **cuadros distintos de una
animación**, no la misma ventana con distinto padre.

Video (recortes en `/tmp/opencode/`):

- `20261106-203244.mp4` a 74/76/78 s: se ve el texto (“Who are you? Tell me!”, “Hehehe…”) y
  **el botón X arriba a la izquierda**, sin globo detrás. El grupo está en el offset inicial
  de la página, no en la posición final.
- `20261106-200837.mp4` a 157 s: el mismo globo está abajo, con el texto adentro y la X abajo
  a la derecha. Es el estado asentado.

Esto confirma el síntoma (globo y X corridos juntos), pero **no** confirma la causa “padre en
(0,0)”. El grupo está en el frame inicial de la transición y no avanza.

## 3. Candidatos de causa (a/b/c/d)

- **(a) el grupo nunca recibe posición**: parcialmente cierto, pero no hay una llamada común
  que falte: no existe EEC8 sobre el contenedor en ninguna ventana. La posición sale del
  timeline/recurso del layer, no de código de layout.
- **(b) argumento perdido (clase 6)**: **descartado** para la posición. Los wrappers nativos
  `src/auto/m2c_26EEC8.c`, `m2c_26EC48.c`, `m2c_26EC18.c` ya reenvían los 4/3 argumentos y el
  asm de `26EEC8` es `lw a0,0x1C(a0); j 270568` con `a1..a3` intactos. Además **no hay ningún
  llamador de `26EEC8` en la ruta de pelea 0x2A/0x2B** (ni en `port/eq` ni en
  `port/build/recomp`; solo aparecen 244708, 24AB10, 24DFF8, 2518F0, 254BD0, 2565E0, 29C1E8,
  3B8E88, 3BED00, 3C0FD0, 3C38A8, 3C7AE8, 3CBE58, 3D4518, 3D9098, 3DBC08, 3DD160, 3E0040,
  3E0EC8, 3E23E8, 3E4218, 3E6E10, 3E8948, 3EDA48, 3F16E0, 3F9B80, 403420, 406CA0, 40C530,
  413D28, 41AE58, 41DBB0).
  Hay un desajuste de aridad en `func_26EF88` (declarado con 3 args en los llamadores,
  definido con 5 en `port/eq/26EF88.c`), pero es **escala**, no posición, y `2708C8` no usa
  a2/a3; no explica el globo.
- **(c) ventana 0 vs 1 (`BtlScriptWork.windows[2]`)**: no hay evidencia. El texto de ambos lados
  se dibuja (registros con lado -1/0/1) y el globo es un sprite aparte, no una ventana del
  script de pelea.
- **(d) el Flash player no aplica la matriz del padre**: no se puede confirmar; el mismo
  renderer dibuja bien el globo en historia. Lo que cambia entre las dos sesiones es el
  **tiempo/estado de la animación**, no una matriz de padre distinta.

**Hipótesis con más sustento (no probada en código):** el layer/sprite que contiene globo+X
se dibuja pero no se *avanza* por cuadro en la intro de pelea. El estado queda en el frame
inicial de la transición de página, por eso el globo está fuera de pantalla y la X arriba a la
izquierda. En historia el mismo layer sí se avanza y llega a (-1,223).

## 4. Punto de arreglo común propuesto

**No agregar EEC8 por ventana.** El punto común correcto es el **avance por cuadro del layer
del globo** (timeline/keyframe), no la posición:

- Si el globo es un layer Flash: el patrón que usan las pantallas que funcionan es
  `func_26E9E8(layer)` (avanza) + `func_26EA58(layer)` (dibuja), como en
  `port/eq/24C060.c:18-27`, `3DF4A8.c`, `29C1E8.c` y `3D8F48.c`.
- Si es un sprite de script (no Flash): avanzar su tiempo/keyframe con la misma velocidad que
  en el mapa/historia.

**Diff propuesto (diagnóstico, no arreglo a ciegas).** Agregar TEMP en el avance de layers para
identificar cuál es el del globo y si se llama o no durante la intro:

```diff
--- a/src/auto/m2c_26E9E8.c
+++ b/src/auto/m2c_26E9E8.c
@@
 void func_0026E9E8(void *arg0) {
+    /* TEMP globo: capa, flags, frame y primer nodo */
+    {
+        extern int fprintf(void *, const char *, ...);
+        extern void *stderr;
+        extern unsigned int D_003B0F7C[];
+        unsigned int *w = *(unsigned int **)((unsigned char *)arg0 + 0x1C);
+        unsigned int *n = w ? (unsigned int *)*w : 0;
+        fprintf(stderr, "TEMP globo 26E9E8 layer=%p flags=%08x f=%d n0=%p n0xy=%08x/%08x\n",
+                arg0, *(unsigned int *)((unsigned char *)arg0 + 0x14),
+                *(int *)((unsigned char *)arg0 + 8),
+                n,
+                n ? *(unsigned int *)((unsigned char *)n + 0x4C) : 0,
+                n ? *(unsigned int *)((unsigned char *)n + 0x50) : 0);
+    }
```

Correr la intro de pelea y el mapa/historia con ese log; comparar qué `layer` aparece en cada
uno y si el de la intro recibe `26E9E8` todos los cuadros. **Recién después** el arreglo de una
línea es del tipo:

```diff
  /* en la función de update del path de intro de pelea */
+ func_26E9E8(globo_layer);   /* mismo avance que el path de historia */
  func_26EA58(globo_layer);
```

Riesgos del arreglo real:
- Llamar `26E9E8` dos veces acelera la animación al doble.
- Si el layer es compartido con otros elementos de UI, se mueven todos.
- Si el globo se anima a propósito por página, forzar el avance puede desincronizar el texto.
- No hay que “clavar” (EEC8) el globo en (-1,223): en historia el globo tiene animación de
  entrada/salida por página; fijarlo rompería las transiciones.

## 5. Qué falta para confirmar

1. Un F9 en la **misma sesión 203244 después de la intro** (por ejemplo frame 4800-5000) para
   ver si el globo llega a (-1,223) o queda en (-214,-83). Si queda, se confirma “no avanza”.
2. Un F9 con **el mismo `st` y escala** en las dos sesiones (hoy 4595 tiene st 0.000 y 9452
   st 0.016). Sin eso, la resta (-213,-306) no mide un padre.
3. Captura de PCSX2 **en el mismo frame del video** de la intro: si en el original el globo ya
   está abajo, es bug del port; si en el original también está entrando, no hay bug.
4. Con el log TEMP del punto 4: nombre/dirección del layer del globo y confirmación de que
   `26E9E8` no se llama en el path de intro.

## 6. Correcciones a premisas del pedido

- `3DF028` **no es el diálogo del modo historia**: sus strings son
  `mc_yazirusi_t_z/mc_yazirusi_l_z/mc_page_title/mc_page_namber/mc_main_dummy/mcGuideEye/
  mcGuideMouth/mc_textwindow` (offset DBZP 0x74420.., base de overlay 0x3B3100). Es un menú de
  páginas/libro y no posiciona la ventana.
- `249FB8` es el dibujo de una línea de texto (fuente), no el globo.
- El único uso del literal `mc_textwindow` en el ejecutable principal es la tienda
  (`func_00244708`, `D_00372128`). Las ventanas de menú usan las copias del overlay DBZP.

## Evidencia cruda usada

- `tools/sesion_2026-11-06/asm/dis.txt`: `2a38c0` (L427220), `2a3dd8`, `2a3ea8` (L427598),
  `2a7308`, `2a4148` (L427764), `26eec8` (L? recomp), `270568`, `270270`, `26c7a8`.
- `port/eq/270568.c` (x/+0x4C, y/+0x50, flag+0x48), `270438.c` (rect), `26EF88.c`,
  `26EB20` (`src/auto/auto_26eb20.c`).
- Logs: `BT2-test/logs/vivo/20261106-203244.log` líneas 157809 y 183355;
  `20261106-200837.log` líneas 136530, 160988, 197738, 448257.
- Dumps RAM: `20261106-203244_ram3_f4595.bin`, `20261106-200837_ram5_f9452.bin`.
  En ambos, `D_003B1F98+0x40` = 300,351 y +0x48 = 213,351 (plantilla de texto), pero **no
  aparecen floats 213/306 ni el par (213,306) en ningún nodo/estructura de posición**.
- Videos: `20261106-203244.mp4` 74-78 s (texto sin globo, X arriba izq.);
  `20261106-200837.mp4` 157 s (globo abajo, texto adentro, X abajo der.).
