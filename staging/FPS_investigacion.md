# FPS — ritmo/vblank: investigación (solo lectura, 2026-11-11)

Objetivo del bug: "Estandarizar el ritmo: vblank a 60 Hz exactos como la PS2 (el juego elige 60 en menús /
30 en pelea)". Clasificación: **PORT** (runtime). No se modificó ni compiló nada; este informe es una propuesta.

**Resumen en una línea:** el port no tiene un reloj de vblank, tiene un *frame limiter* de pared (`vblank_wait`)
que permite 55–58 Hz sostenidos y "recupera" tiempo corriendo en ráfaga después de un tirón (medido: ventanas a
130–222 cuadros/s del renderer). Además el ritmo sólo se aplica si hay GPU o `BT2_PACED`, y `jugar.sh` fuerza
`BT2_FPS=60` mientras el código y el reproductor de video usan 59.94. Eso es lo que hay que arreglar.

**Lo que NO pude fundamentar:** que en BT2 la pelea espere 2 vblanks. El asm del bucle de pelea de *este* binario
(0x102E80) llama a 0x2711E8, que espera **un** vblank, y la traducción C lo respeta. Los comentarios que dicen
`Gfx_EndFrame(2)` son de BT3 (`include/battle/battle.h`, `include/sys/movie.h`). No propongo forzar 30 sin una
captura de la PS2 que lo demuestre (ver §7).

---

## 1. Cadena de código del ritmo (archivo:línea)

| pieza | dónde | qué hace |
|---|---|---|
| reloj de vblank | `port/full/plat_gs.c:68-83` (`vblank_wait`) | `now_ns()` + `per = 1e9/BT2_FPS` (def. 16683350 ns = 59.94). Si está "tarde" (`t >= next`) **no duerme** y hace `next += per`; si está adelantado duerme hasta `next`. Si el desfase supera 100 ms, resetea `next = t + per`. |
| contador | `port/full/plat_sys.c:16` (`gPortVBlanks`), incrementado en `plat_gs.c:97` | es la columna `vblank` del fight.log y el reloj de los logs. |
| `Port_VBlank` | `port/full/plat_gs.c:84-126` | (a) arma watchpoint B25; (b) `if ((GsGpu_Enabled() || paced) && !BT2_UNCAPPED) vblank_wait();` (línea 96); (c) `gPortVBlanks++`; (d) fightlog/statelog; (e) `BT2_FPSLOG` (cada 60 vsyncs imprime vsync/s y gsframe/s, líneas 100-117); (f) `BT2_MAXFRAMES`; (g) **llama al handler de vsync del juego** (`sVsyncHandler`, línea 124). |
| entrada del juego | `sceGsSyncV` en `port/full/plat_gs.c:126` | `{ Port_VBlank(); return 0; }`. Es el único punto por donde el juego "espera un vblank" (más el checkpoint de abajo). |
| llamadores en el juego | `port/eq/2711E8.c:9-15`, `port/eq/271240.c:8-11`, `port/eq/271178.c` (`Gfx_SyncField`) | esperan **1** vblank y hacen `gGfx.field = sceGsSyncV(0)==0`, `gGfx.frame++` (`gGfx+0x234`). |
| bucle de pelea (C) | `port/eq/102E80.c:16-34` | `do { present(2711A0); …Battle_Update (102AA0); Battle_Draw (102C40); func_002711E8(); } while (!terminó);` → **un vblank por iteración**. |
| bucle de pelea (asm) | ELF `0x102E80`: `jal 0x2711e8` en `0x102F08` | confirma que el C es fiel: el binario espera 1 vblank. `0x2711E8` hace `sceGsSyncPath(0,0)` y `sceGsSyncV(0)` una vez (`0x271200`/`0x27120C`). |
| menús | `port/eq/3B4250.c`, `3BAFE8.c`, `3BC000.c`, etc. | mismo esquema: `2711A0` (swap+display) + `271240`/`2711E8` (1 vblank) por vuelta. |
| checkpoint del relleno | `port/full/recomp_shim.cpp:260-267` | cada `0x1FFFFF` iteraciones de un bucle recompilado llama `Port_VBlank()` "para no colgar". Es un **segundo** generador de vblanks, fuera del control del juego. |
| temporizadores EE | `port/full/mem.c:247-262` | hilo que cada 1 ms suma 576 a COUNT de T0..T3 (576 kHz cuantizado a 1 ms). Reloj **independiente** del vblank; los `while (T1_COUNT < 0x190)` del juego (comentario `mem.c:247`) miden con éste. |
| video | `port/full/plat_movie.c:168-179` | pacer propio: `nanosleep` fijo a **16683350 ns (59.94)** por pasada, sin usar `BT2_FPS`. Presenta con una cadena VIF1 vacía. |
| presupuesto "de pelea" | `port/full/gs/gs_core.c:1476,1499,1509` | el diagnóstico considera "presupuesto" 33.4 ms y comenta "33.4 in a fight, 16.7 in the menus"; `gs_core.c:1517` dice que el ritmo lo hace el vblank "60 per second, the game waits for one per menu frame and two per battle frame". Es una **expectativa** del runtime, no lo que hace el juego hoy. |

El paso `2.000` de las animaciones está en el fight.log (`anim x/largo paso 2.000`). Se ve en el binario:
`btl_cam_25C298.c:130` resta `0.033333333f` (1/30 s) por llamada a `CamShake_Tick`, y hay varios contadores de
"1/30 s" (`bobj_a_25F210.c:285`, `bobj_a_25FC68.c:320`, `bobj_a_26A1C0.c:261`). Eso sugiere que el update de pelea
*debería* correr a 30 Hz; el bucle real corre a 60. Queda como hipótesis a confirmar con captura (ver §7), no como
causa demostrada del "30 en pelea".

---

## 2. Medición de los logs (`BT2-test/logs/vivo`)

Fuente: líneas `fpslog: t=… vsync=… vsync/s=… gsframe/s=…` (cada 60 vblanks) y `time: frames lasted …` de
`BT3_GS_VERBOSE`; estado de escena de `*.fight.log` (`ESTADO fase MENU/BATALLA`) para partir menú vs pelea.
`gsframe/s` = cadenas VIF1 presentadas por segundo (≈ cuadros del renderer).

| sesión | tramo | ventanas | vsync/s mediana | vsync/s media | mínimo | ms/vblank medio del tramo | desvío vs 60 |
|---|---|---|---|---|---|---|---|
| 20261111-111320 | MENÚ | 130 | 60.00 | 59.37 | 22.30 | — (arranque 53.4) | hitches |
| 20261111-111320 | PELEA (v 5210–39903, 9.7 min) | 623 | 60.00 | 59.61 | 46.40 | **16.770** | **−0.62 %** |
| 20261107-014550 | PELEA (v 2009–7020, 88 s) | 84 | 60.00 | 58.37 | 25.10 | **17.605** | **−5.33 %** |
| 20261106-195412 | MENÚ (sin GPU/pacing) | 119 | **595.70** | 703.47 | 90.60 | — | **+893 %** |
| 20261106-195412 | PELEA (v 4926–6350) | 32 | **81.85** | 84.43 | 73.10 | 12.451 | **+33.9 %** |

- `gsframe/s` = `vsync/s` en todas las ventanas de las sesiones con GPU (60/60 en menú y en pelea). O sea: **un
  cuadro del renderer por vblank**, también en pelea.
- Peor cuadro individual: **124–175 ms** (`frames lasted … max`; 7–10 vblanks perdidos).
- Ráfagas: ventanas con `vsync/s` bajo pero `gsframe/s` alto, p.ej. `t=34.8 s vsync/s=41.8 gsframe/s=138.1`,
  `t=88.4 s 43.2/130.9`, `t=730.7 s 22.3/222.5`. Son "acelerones": el juego corre a 130–222 cuadros/s para
  recuperar el tiempo perdido. En pelea no aparecen en estas sesiones; sí en menús/cargas.
- `time: work per frame`: promedio 10.1 ms (014550) y 13.8 ms (111320), **muy por debajo del presupuesto de
  33.4 ms**; sólo 51 y 19 cuadros de ~46.000 pasaron el presupuesto. No es falta de rendimiento: es el reloj.
- Primer segundo: 52–54 vsync/s (arranque; no es régimen).
- La sesión 20261106-195412 (log de 25 MB, con pelea) corrió a **264–1900 vsync/s**: no había GPU o no estaba
  `BT2_PACED`, así que `Port_VBlank` no durmió nunca (línea 96). Es la "aceleración ad hoc" más grande que hay.

---

## 3. Cómo decide el juego 60 vs 30 (y qué hace el port)

- El juego **no le pide fps al port**: pide "esperá el próximo vblank" llamando `sceGsSyncV` por
  `func_002711E8`/`func_00271240`, y repite esa espera N veces por vuelta de su bucle. Quien elige 1 o 2 es el
  bucle del juego.
- En este binario: menús (3B4250/3BAFE8/3BC000/…) esperan **1**; pelea (0x102E80) también espera **1**
  (`port/eq/102E80.c:33`). El port no fuerza nada: `Port_VBlank` duerme **un** período por llamada.
- Consecuencia: el update de pelea avanza **2.00 unidades de animación por vblank** (fight.log: `2.00→4.00→6.00…`
  en vblanks consecutivos), y el renderer dibuja 60 cuadros/s. Si el original debía ser 30, esto es 2×; pero el
  asm de BT2 no muestra el 2 (ver §7).
- Los comentarios `Gfx_EndFrame(2)` / "two vertical blanks" (`include/battle/battle.h:32`, `include/sys/movie.h:23`)
  vienen de BT3 y **no** coinciden con el bucle real de este ELF. El video sí usa 2 vblanks por imagen conceptual
  (29.97 fps) y tiene su propio pacer.

---

## 4. Causa probable de la desviación

1. **`vblank_wait` no modela un vblank: modela un limitador de cuadros con crédito.**
   - Cuando el cuadro se pasa de 16.7 ms, `t >= next` → **no duerme** y `next += per`; la llamada siguiente
     vuelve a encontrar `t >= next` y tampoco duerme. Resultado: corre en ráfaga hasta "recuperar" todo el atraso
     (medido: 130–222 gsframe/s). La PS2 no recupera tiempo: si un cuadro se pasa, el `sceGsSyncV` espera el
     **próximo flanco** y el cuadro dura 2 vblanks (cae a 30), sin acelerón posterior.
   - Por eso una pelea que no llega a 60 da 56.8 Hz sostenidos (014550) en vez de cuantizar a 30/60.
   - El corte de 100 ms (`next = t + per`) pierde la fase después de un tirón grande.
2. **Pacing condicional y aceleración sin GPU:** `plat_gs.c:96` sólo duerme si `GsGpu_Enabled()` o `BT2_PACED`.
   Con `BT2_GS=none` o el renderer por software sin `BT2_PACED`, el juego corre a la velocidad que pueda
   (264–1900 vsync/s medido). Es la causa de las sesiones "raras" y de que las pruebas automáticas no sean
   comparables.
3. **Dos relojes de 60 que no coinciden:** `jugar.sh` exporta `BT2_FPS=60` (16.6667 ms) mientras el default del
   código es 59.94 (16.6834 ms) y `plat_movie.c:172` duerme 16683350 ns fijos. Menús/pelea van a 60.000 y el
   video a 59.94: 0.1 % de deriva entre los dos, y la fase del video no está atada al vblank.
4. **Segundo generador de vblanks:** el checkpoint de `recomp_shim.cpp:262` llama `Port_VBlank` desde bucles
   recompilados. Si un bucle del juego está esperando una bandera del handler de vsync, el checkpoint le da un
   vblank "de arriba"; con el pacer nuevo cada uno de esos llamados cuesta 16.7 ms. Hay que loguearlo (no hay
   ninguna línea `bucle de espera` en los logs actuales, así que hoy no parece estar disparando en pelea, pero no
   está verificado con `g_log`).
5. **Reloj de timers EE independiente:** `mem.c:247-262` (576 kHz en quanta de 1 ms) no está atado al vblank. Un
   `while (T1_COUNT < 0x190)` mide pared, no vblanks; con `BT2_FPS != 59.94` o con ráfagas, la lógica que usa T0..T3
   y la que usa vblanks se desfasan.

No encontré multiplicadores de tiempo ni `sleep` fijos en la lógica del juego. Los únicos `sleep` del runtime son:
`plat_gs.c:79` (vblank), `mem.c:254` (timer 1 ms), `plat_movie.c:174` (video).

---

## 5. Plan concreto (en orden, sin aplicar)

### Paso 0 — medir antes de tocar (30 min, sólo log)
Agregar a `Port_VBlank` (bajo `BT2_VLOG`) un log con `__builtin_return_address(0)` + `dladdr` la primera vez
que aparece cada PC y cada 600 vblanks: quién pide cada vblank (juego vs checkpoint), y en `gs_core.c` el delta
`gPortVBlanks` por cuadro presentado. Objetivo: confirmar que en pelea hay exactamente 1 `sceGsSyncV` por vuelta
de 0x102E80 y que el checkpoint no participa. Es la única forma de saber si el 2-vblank (si existiera) se pierde
en el juego o en el runtime.

### Paso 1 — `vblank_wait` como reloj libre (el arreglo de fondo)
`port/full/plat_gs.c:68-83`. Propuesta de diff (NO aplicado):

```diff
 static void vblank_wait(void) {
     static unsigned long long next, per;
     unsigned long long t = now_ns();
     if (!per) {   /* BT2_FPS=n: ritmo de vsync (por defecto 59.94) */
         const char *e = getenv("BT2_FPS");
         double hz = e ? atof(e) : 0.0;
         per = hz >= 1.0 ? (unsigned long long)(1e9 / hz) : 16683350ull;
     }
-    if (next != 0 && t >= next && t - next < 100000000ull) next += per;          /* tarde: sin esperar */
-    else if (next > t && next - t < 100000000ull) {
-        struct timespec ts = {0, (long)(next - t)};
-        nanosleep(&ts, NULL);
-        gPortSleptNs += now_ns() - t;
-        next += per;
-    } else next = t + per;
+    /* Un vblank por llamada, sobre una grilla libre: si llegamos tarde, se pierden los flancos
+       que pasaron (como en la PS2), no se corren cuadros de más para "recuperar". */
+    if (next == 0) next = t;
+    do { next += per; } while (next <= t);
+    { struct timespec ts = {0, (long)(next - t)};
+      nanosleep(&ts, NULL);
+      gPortSleptNs += now_ns() - t; }
 }
```

Efecto esperado:
- ritmo estable exactamente a `per` (60.000 o 59.94 según `BT2_FPS`), sin deriva acumulada;
- si un cuadro se pasa de 16.7 ms, el siguiente arranca en el flanco siguiente → el juego cuantiza a 30 como la
  PS2 (y no hay ráfagas de 130–222 cuadros/s);
- el desvío de −5.33 % de 014550 desaparece: o 60, o 30/60 intercalado según carga.

Riesgo: los tirones ahora se ven como "pausa y sigue" (un cuadro de 33 ms), no como acelerón. Es lo correcto,
pero hay que probarlo en pelea y en menús. No toca audio, video ni lógica: sólo la espera.

### Paso 2 — un solo reloj y pacing siempre
```diff
-    if ((GsGpu_Enabled() || paced) && !getenv("BT2_UNCAPPED")) vblank_wait();
+    if (!getenv("BT2_UNCAPPED")) vblank_wait();   /* BT2_UNCAPPED sólo para tests */
```
y en `BT2-test/jugar.sh` sacar `BT2_FPS=${BT2_FPS:-60}` (dejar el default 59.94 del código) **o**, si se decide
que el port va a 60.000 exactos, poner 60 en los dos lados. Lo importante: **un solo número**. Exponer
`Port_VBlankPeriodNs()` y usarlo en `plat_movie.c:172` en lugar del 16683350 literal.

Riesgos:
- **Audio ADX/SPU**: el tiempo del ADX sale del contador de vblank del juego (`D_0034AED8`, incrementado en el
  handler `func_001006D8 → func_002EF0D8`, `port/eq/2EF0D8.c:21`; `2F4960.c:46` lo usa como base de tiempo).
  Cambiar el ritmo cambia la velocidad del audio; con 60 vs 59.94 el cambio es 0.1 % (inapreciable), con el
  pacing nuevo en una pelea cargada el audio también cuantiza (igual que la PS2). Probar música + SE + voz.
- **Video**: el pacer propio de `plat_movie.c` va a 59.94; si el juego va a 60.000, el video queda 0.1 % lento
  (1 cuadro cada 1000). Unificar al mismo `per`.
- **Tests automáticos**: hoy corren 10–30× más rápido sin GPU. Con pacing siempre tardan lo real; dejar
  `BT2_UNCAPPED=1` explícito en los scripts de humo y documentarlo.
- **Timers T0..T3** (`mem.c`): si el juego hace busy-waits de 576 kHz, con el pacing nuevo siguen midiendo pared;
  no los toco en este paso. Verificar que no aparezcan "bucle de espera" nuevos.

### Paso 3 — sólo si se confirma el 30 en pelea
Si una captura de PS2 muestra que la animación `paso 2.000` tarda ~94 vblanks en llegar a 94 (y no ~47), entonces
el bucle de pelea debe esperar 2 vblanks. El cambio sería en el **juego**, no en el runtime:
```diff
--- a/port/eq/102E80.c
+++ b/port/eq/102E80.c
@@
-        func_002711E8();
+        func_002711E8();
+        func_002711E8();   /* 30 Hz: dos vblanks por cuadro de pelea (SOLO si la PS2 lo confirma) */
```
(y lo mismo en 0x102F30, el bucle de split-screen). Riesgo alto: baja la velocidad de toda la pelea a la mitad;
hay que auditar los contadores de 1/30 s y el audio. **No hacerlo antes de la captura.**

---

## 6. Descartes (y por qué)

- **"El port fuerza 30 en pelea"**: falso. No hay ningún `*2` ni divisor de tiempo; el renderer presenta un
  cuadro por vblank (gsframe/s = vsync/s = 60 en pelea).
- **"`BT2_FPS` es la causa principal"**: no; el desvío por 60 vs 59.94 es 0.1 %. La causa principal es la forma
  de esperar (crédito/ráfaga) y el pacing condicional.
- **"Falta de rendimiento"**: no. El trabajo por cuadro es 10–14 ms contra un presupuesto de 33.4 ms; sólo
  ~0.1 % de los cuadros se pasa. Los tirones son de texturas/pipelines/carga, no del bucle.
- **"El video marca el ritmo del juego"**: el video tiene su propio `nanosleep`, pero el bucle del juego no lo
  espera; no explica el ritmo de pelea.
- **"Vsync de SDL"**: no; `gs_gl.c:753` hace `SDL_GL_SetSwapInterval(0)` (vsync apagado) y el software usa
  `SDL_RenderPresent` sin vsync. Todo el ritmo depende de `vblank_wait`.
- **"Los comentarios de `Gfx_EndFrame(2)` son de BT2"**: no coinciden con el asm de este ELF (0x102E80 →
  0x2711E8, una sola espera). Son de BT3. No los uso como prueba.

---

## 7. Lo que NO está verificado / cómo cerrarlo

1. **30 vs 60 en pelea.** No hay evidencia en el binario de BT2 de una espera de 2 vblanks en el bucle de pelea.
   Prueba decisiva y barata: capturar en la PS2 (o PCSX2 con el mismo ISO) una animación de pelea y contar los
   vblanks entre `anim 2.00` y `anim 94.00`. Si son ~47 → 60 Hz es correcto y el bug es sólo el reloj; si son ~94
   → el bucle debe esperar 2 (Paso 3). Mientras tanto, no toco el bucle.
2. **Quién pide cada vblank en pelea.** Sin el log del Paso 0 no puedo afirmar si el checkpoint del relleno
   participa. No hay líneas `bucle de espera` en los logs actuales, pero el log está apagado.
3. **El "acelerón" de `gsframe/s` 138–222** aparece en ventanas de menú/carga. Supongo que es la cola del
   renderer threaded + el crédito del pacer, pero no lo medí con sonda por cuadro.
4. **Audio:** no probé si el ADX se acelera en las sesiones sin pacing (195412). La tabla de tiempo del ADX usa el
   contador de vblank (`2F4960.c`), así que debería; falta escucharlo.
