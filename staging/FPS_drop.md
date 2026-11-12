# FPS: por qué la pelea corre a 40 y no a 60 (investigación, solo lectura, 2026-11-11)

Alcance: análisis del último log real de pelea, **OpenGL**, `BT2-test/logs/vivo/20261111-202229.log`
(20 MB, `BT3_GS_VERBOSE=1`, `jugar.sh`, escala interna **3x = 1536x1344**, `bt2_settings.txt` con `scale=3`).
No se modificó ni compiló nada. Los números de línea son de los archivos en este estado del árbol.

## 0. Resumen

**El juego no "perdió rendimiento": el número 40 sale de que el trabajo por cuadro (17–18 ms) está por
encima del período de vblank (16.7 ms), y el pacer nuevo —correcto— ya no deja "recuperar" el atraso.**
El trabajo sube porque, en GL, `GsGpu_FrameEnd` (lo que el log llama *"ending and submitting the frame"*)
cuesta **10–12 ms** en pelea a 3x, y la mitad de ese costo aparece cada 2 cuadros: la firma de
`BT2_RECORD` (lectura del framebuffer de 1536x1344 + tubería a ffmpeg, `jugar.sh:14`,
`BT2_RECORD_EVERY=2`), que sincroniza el pipeline GL y factura el trabajo de dos cuadros en uno.
Los picos de 331 ms **no son del renderer**: son las pulsaciones de F9 (volcado de 32 MB de RAM + volcado
detallado de la lista de dibujo al log).

## 1. Qué mide exactamente cada número

Todo el cronómetro está en `Port_GsVif1Chain` (`port/full/gs/gs_core.c:1448`), que se ejecuta una vez por
cadena VIF1 del cuadro (una por vuelta del bucle de pelea; `gsframe/s` cuenta esto):

| línea del log | dónde se mide | desde → hasta | incluye | NO incluye |
|---|---|---|---|---|
| `work per frame: average` | `gs_core.c:1467-1471`, acumulado en `1497` | `start` (fin de la llamada anterior a `Port_GsVif1Chain`, fijado en `1525`) → `t = now_ns()` después de `run_chain` | el resto del bucle del juego **y** `run_chain`, **menos** `gPortSleptNs` (todo lo dormido en `vblank_wait`/`Port_PacePresent` desde la llamada anterior) | el sueño del vblank |
| `game code` | `gs_core.c:1460` (`tChain`) menos `start`, menos lo dormido | fin de la cadena anterior → entrada de ésta | update/draw del juego y lo que corre entre present y present (`func_002711A0` … `func_002711E8`) | `run_chain` |
| `display list` | `gs_core.c:1467` menos `tChain` | dentro de `run_chain` | recorrido de la cadena DMA/VIF1/GIF + armado de `gsDraws` + `GsVu1_FrameEnd` (`1590`) + `GsGpu_FrameEnd` (`1591-1593`) + `Port_PacePresent` (`1594`) + `screenshot()` (`1595`) + `sFrame++` (`1155`) | el sueño del vblank |
| `texture decoding` | `gs_draw.c:250` (`gGpuTexNs`) | decodificación de texturas | — | — |
| `pipeline creation` | `gs_gpu.c:295` (`gGpuPipeNs`) | creación de pipelines | — | — |
| **`ending and submitting the frame`** | **`gs_draw.c:1309-1315` (`GsGpu_FrameEnd` → `gGpuEndNs`)** | entrada/salida de `GsGpu_FrameEnd` | **todo `frame_end()` del backend GL (`gs_gl.c:868-1236`) + `scale_apply()`** | `GsVu1_FrameEnd`, `Port_PacePresent`, `screenshot()` |
| `frames lasted min..max` | `gs_core.c:1520-1524` | `start` → `start` (intervalo entre cadenas, con sueño) | todo | — |
| `fpslog vsync/s` / `gsframe/s` | `plat_gs.c:109-125` | llamadas a `Port_VBlank()` por segundo / cadenas por segundo | — | no es el refresco del monitor |

Consecuencia importante: **`ending and submitting the frame` NO es el swap**. El nombre engaña: es la pasada
completa del backend GL. Arranca en `gs_gl.c:868` y adentro están:

- `903-910` subida de vértices (`glBufferSubData` de `gsVerts`/`gsVuVerts`);
- `911-931` subida de framebuffer a textura (pantalla de película, `gGsFbUploads`);
- `945-1072` **el bucle de todos los draws** (`glBindFramebuffer`, `set_pipe`, `set_textures`, `set_params`,
  `set_scissor`, `glDrawArrays` en `1047`);
- `1075-1148` present: `glClear`, triángulo de pantalla completa, overlays, `Ui_DrawGL()` (`1124`);
- `1149` **`SDL_GL_SwapWindow`**;
- `1150-1153` `glGetError()` (sólo con `BT3_GS_VERBOSE`);
- `1155-1193` `BT3_SHOT` (lectura de píxeles) — **apagado**;
- `1197-1224` **`BT2_RECORD`**: `glReadPixels` de 1536x1344 RGBA (8.26 MB) desde `sTgFbo[best]` y `fwrite` a
  la tubería de ffmpeg (`popen`, `1210-1211`, `1220-1222`).

Lo que **no** hay: ningún `glFinish()` por cuadro (`glFinish` sólo aparece en `scale_changed()`,
`gs_gl.c:564`), ni vsync de SDL (`SDL_GL_SetSwapInterval(0)` en `gs_gl.c:753`). `Port_PacePresent`
(`plat_gs.c:140-160`) duerme sólo si el cuadro llegó antes de 3/4 de período; con intervalos de 20-30 ms
en pelea no dispara.

## 2. Los 10–12 ms de "submitting": qué hay adentro

Cuentas del log (`time: frame 2941`, líneas 97439-97441):

```
work 18.3 ms = game 0.7 + display list 17.6
   de la lista: texturas 0.4, pipelines 0.0, ending and submitting 11.5
```

Es decir: de los 17.6 ms de `run_chain`, **11.5 son el backend GL y ~6 son el recorrido/armado de la lista**.
A 2x (`20261111-111320`, misma escena, mismos ~2400 draws y 100k vértices) el mismo número era
**8.5–9.4 ms** (`20261111-111320.log`, p.ej. `time: frame 3301`), y a 3x es 11.5–12.8. O sea que el 3x
agrega ~3 ms de trabajo de píxel, pero **el grueso de los ~8-9 ms está en ambos casos**: es la sumisión de
~2200-2400 draws con ~45 vértices cada uno (`gpu: frame 4410: 2404 draws, 100948 vertices, 9 targets`),
que en Mesa/radeonsi cuesta del orden de 3-4 µs por draw entre binds, uniform buffer, scissor y
`glDrawArrays`. No se ve un leak: el conteo de draws oscila con la escena (1366–2404) y no crece en la
sesión; texturas y pipelines nuevos = 0.

Dato que separa el costo fijo del variable: en **menú** a 3x, con 5 draws y 888 vértices, el mismo
"submitting" es **3.4–3.6 ms** (`time: frame 121`, línea 608). Ese piso fijo (present + swap + lectura de
`BT2_RECORD`/2 + UI) no cambia entre 2x y 3x; la diferencia pelea/menú es el bucle de draws y el trabajo de
GPU que arrastra.

## 3. Por qué 40 y no 60 (y por qué 40 y no 30)

- El bucle de pelea espera **un** vblank por vuelta (`port/eq/102E80.c:33` → `2711E8.c` → `sceGsSyncV` →
  `Port_VBlank`, `plat_gs.c:77-98`). Con el pacer de grilla libre, cada llamada duerme hasta el **próximo
  flanco** de 16.667 ms (`BT2_FPS=60`); si el cuadro se pasó, se pierde el flanco (no hay catch-up).
- El trabajo real por cuadro es **17.8 ms en promedio** (medido) y **bimodal**: los peores de cada ventana
  son 24.8–28.6 ms (`time: frame 2941/3001/3301…`), y el promedio 17.8 = mitad de cuadros livianos
  (~10 ms) y mitad pesados (~26 ms). Con esa distribución, unos cuadros entran en un período y otros
  pierden uno → mezcla de intervalos ~16.7/~33 ms → **exactamente ~40.0 vsync/s sostenido**.
- La bimodalidad cada 2 cuadros tiene un sospechoso con nombre: `BT2_RECORD_EVERY=2`. El `glReadPixels`
  es una **sincronización implícita**: espera que la GPU termine todo lo encolado (los draws de este cuadro
  y, en la práctica, los del anterior), y encima transfiere 8.26 MB y los escribe a la tubería. Por eso el
  cuadro grabado paga el trabajo de dos.
- Verificación de que el período del pacer es 16.7 y no otro: los **menús de la misma corrida** van a
  **60.0** con `frames lasted 16.1–17.3 ms` (`time: frame 121`, línea 608). Si `BT2_FPS` fuera 40, los
  menús también irían a 40.
- **El log miente en el presupuesto**: `gs_core.c:1476,1499` marca "slow"/"over budget" con
  **33.367 ms** (2 vblanks, herencia del supuesto "30 en pelea") y el comentario `1517-1518` dice
  "two per battle frame". Con el ritmo confirmado de 60 Hz el presupuesto es **16.683 ms**; contra ese
  número, la mitad de los cuadros está afuera, que es justo lo que se ve en el `vsync/s=40`.
- Antes el pacer con crédito no dormía cuando llegaba tarde y "recuperaba" (medido en el informe viejo:
  130–222 cuadros/s en menús y 59.61 Hz en pelea). Por eso el mismo trabajo se veía como 60. **El arreglo de
  ritmo no rompió el rendimiento: dejó de taparlo.** Ese es el "drop viejo" que queda.

## 4. Los picos de 331 ms: son F9, no el renderer

Evidencia en el log:

- `251275-251276`: `gs: dumping frame 3541 (F9 / trigger file)` + `RAM -> …_ram4_f3541.bin` (32 MB).
- Inmediatamente después, miles de líneas `dma tag at …`, `giftag …`, `prim …`, `reg …` (volcado detallado
  del cuadro, `gs_core.c:1560-1586`, y el volcado por primitiva en `217`, `702-1017`), y recién entonces
  `297047-297048`: `slow: frame 3542: 331.4 ms = game 7.4 + display list 330.3` con `submitting 47.6`.
- **La prueba de que el pico es el volcado y no el GL**: `display list` (330.3) menos `submitting`
  (GsGpu_FrameEnd, 47.6) = **282.7 ms** gastados en `run_chain` *fuera* del backend GL, que es exactamente
  el `fprintf` del volcado. Los mismos ~336 ms aparecen en 3453, 3455, 3457, 3459, 3461 y 553 ms en 3462
  (líneas 160319-160591, 208509), pegados a los F9 de `ram1 f3432`, `ram2 f3461`, `ram3 f3487`, `ram4 f3541`.
- La ventana `fpslog: t=66.8s … 3240` → `t=78.1s … 3300` (líneas 106067 y 208555) muestra **60 vblanks en
  11.3 s** (5.3/s): ahí cayeron los volcados de F9 (32 MB a disco + ~9 MB de log) y probablemente un tirón
  externo (ventana/foco). No es régimen.
- Cómo cazarlo (si hiciera falta): no hace falta, ya está cazado. Para picos futuros, `BT3_GS_DUMP=<frame>`
  hace lo mismo pero acotado a un cuadro; `BT2_DUMP_TRIGGER` permite dispararlo desde un script. Para medir
  sin ensuciar: **no usar F9** en la corrida de medición y no prender `BT3_GS_VERBOSE` (el log escribe una
  línea `gl: present window…` por cuadro).

## 5. Hipótesis y descartes

| hipótesis | veredicto | evidencia |
|---|---|---|
| vsync mal puesto (`SDL_GL_SetSwapInterval`) | **descartada** | `gs_gl.c:753` lo apaga; si estuviera en 1, iríamos a 60 o 30 clavados, no a 40 |
| `glFinish` por cuadro | **descartada** | sólo en `scale_changed()` (`gs_gl.c:564`), que corre al cambiar la escala |
| `BT3_SHOT` leyendo píxeles | **descartada** | `jugar.sh` no lo define; el bloque sólo corre con `BT3_SHOT>0` o `gGsDumpFrame>=0` (`gs_gl.c:1161`) |
| `Port_VBlank` durmiendo de más | **descartada como causa** | duerme como máximo hasta el flanco siguiente (`plat_gs.c:77-98`); si sumara un vblank siempre, daría 30 y da 40 |
| `Port_PacePresent` duplicando el pacer | **descartada en pelea** | sólo duerme si el intervalo < 12.5 ms (`plat_gs.c:148`); en pelea es 20-30 ms |
| decodificación de texturas / creación de pipelines | **descartada** | 0.0–0.7 ms y 0 pipelines nuevos por ventana |
| código del juego | **descartada** | `game code 0.7 ms` |
| `BT2_RECORD` (lectura + ffmpeg) | **principal sospechosa** | `jugar.sh:14`, cada 2 cuadros; `worst` 25-28 ms vs promedio 17.8 en TODAS las ventanas; 8.26 MB por lectura a 3x; x264 externo no es el límite (benchmark aparte: 139 fps a 1536x1344, ~0.9 ms de CPU por cuadro a 20 fps), pero el `glReadPixels` sincroniza la GPU |
| escala 3x | **coadyuvante** | `ending and submitting` 11.8 ms a 3x vs 8.9 ms a 2x (misma escena); +2.9 ms |
| draw count / estado por draw | **coadyuvante estructural** | ~2200-2400 draws de ~45 vértices; ~6-9 ms de sumisión; sin crecimiento (no hay leak) |
| picos de 331 ms | **son F9** | ver §4 |

## 6. Causa más probable (ordenada)

1. **Trabajo por cuadro apenas por encima del período**: 17.8 ms > 16.667 ms. Con la grilla libre, eso
   cuantiza a ~40 fps (mezcla de 1 y 2 flancos). No es "falta de rendimiento bruta": es un cuadro que no
   entra por 1-2 ms.
2. **`BT2_RECORD` es lo que lo empuja**: la lectura del framebuffer cada 2 cuadros serializa el GL y hace
   que el cuadro grabado cueste ~26 ms (peor caso de todas las ventanas). Sin eso, la estimación es
   10-12 ms por cuadro (sumisión CPU ~6-9 + GPU ~3) → 60 fps con margen.
3. **3x agrega ~3 ms** de píxel (y la lectura de 8.26 MB en vez de 3.67 MB). A 2x el mismo trabajo entraba
   (el run de 2x iba a 60 con el pacer viejo; el `ending` era 8.9 ms).

No puedo afirmar todavía el reparto exacto entre "sumisión CPU de draws" y "espera de GPU por la lectura":
los 11.5 ms son un solo cronómetro. Por eso el primer experimento es el A/B de abajo y, si no alcanza, los
tres cronómetros TEMP del §8.2.

## 7. Experimento A/B más corto (una sola variable por corrida)

Misma escena de pelea (entrenamiento o torneo), ~30 s cada una, sin tocar F9. `BT2_FPSLOG=1` ya imprime
`vsync/s`; con `BT3_GS_VERBOSE=1` además sale `work`/`submitting` (agrega una línea por cuadro, igual en
las dos ramas).

- **A (base, ya medida)**: escala 3 + `BT2_RECORD` ON → `vsync/s=40.0`, `work 17.8`, `submitting 11.5`.
- **B (la decisiva)**: escala 3 + `BT2_RECORD` OFF. Sin el diff de `jugar.sh` se corre `bin/bt2` a mano
  (sólo hay que omitir `BT2_RECORD`):

```bash
cd /home/rexx/Escritorio/BT2-Port/BT2-test
T=$(date +%Y%m%d-%H%M%S)
env BT3_GS=gpu BT3_GPU_API=gl BT2_SAVES="$PWD/saves" BT2_FPS=60 BT2_FPSLOG=1 BT2_STATELOG=1 \
    BT3_GS_VERBOSE=1 BT2_FIGHTLOG_OUT="/tmp/fight_$T.log" \
    sh -c "bin/bt2 > /tmp/fps_$T.log 2>&1"
```

  **Si B da 60.0 y `work` ~11-12 ms → causa confirmada** (la grabación). **Si B sigue en 40 → el costo es
  el bucle de draws y hay que ir al §8.3.**
- **C (reserva, barata)**: escala 2 + `BT2_RECORD` OFF (`BT3_SCALE=2` en el mismo comando). Mide el margen
  que compra bajar la resolución interna; sirve de plan B si el usuario no quiere sacrificar la grabación.

Después de B/C, repetir una vez con `BT2_RECORD` ON para confirmar que la diferencia es la grabación y no
el azar de la escena.

## 8. Arreglo propuesto (sin aplicar)

### 8.1. Diagnóstico: presupuesto correcto (1 línea de números, cero riesgo)

`port/full/gs/gs_core.c` — que el log no diga "0 de 60 fuera de presupuesto" mientras va a 40:

```diff
@@ gs_core.c:1476
-            if (work > 33366700ull && getenv("BT3_GS_VERBOSE") != NULL) {
+            /* un vblank a 59.94: el presupuesto de un cuadro de 60 Hz, no dos */
+            if (work > 16683350ull && getenv("BT3_GS_VERBOSE") != NULL) {
@@ gs_core.c:1499
-        if (work > 33366700ull) { over++; }
+        if (work > 16683350ull) { over++; }
@@ gs_core.c:1502-1503
-                fprintf(stderr, "time: frame %u: work per frame: average %.1f ms, worst %.1f ms, %u of 60 over the 33.4 ms budget\n",
+                fprintf(stderr, "time: frame %u: work per frame: average %.1f ms, worst %.1f ms, %u of 60 over the 16.7 ms budget\n",
```

(y borrar el comentario `1517-1518` que habla de "two per battle frame", que quedó de BT3).

### 8.2. Medir antes de optimizar: tres cronómetros TEMP en `frame_end`

`port/full/gs/gs_gl.c` (TEMP FPS, sacar al cerrar el bug), con `gpu_now`/`SDL_GetTicksNS`:

```diff
 static void frame_end(void) {
     ...
     glEnable(GL_SCISSOR_TEST);
+    uint64_t t_tmp, t_draw = 0, t_pres = 0, t_rec = 0;      /* TEMP FPS */
+    t_tmp = SDL_GetTicksNS();
     for (n = 0; n < gsDrawCount; n++) {
         ...
     }
+    t_draw = SDL_GetTicksNS() - t_tmp; t_tmp = SDL_GetTicksNS();   /* TEMP FPS */
     ... present ...
     SDL_GL_SwapWindow(sWindow);
+    t_pres = SDL_GetTicksNS() - t_tmp; t_tmp = SDL_GetTicksNS();   /* TEMP FPS */
     ... BT2_RECORD ...
+    t_rec = SDL_GetTicksNS() - t_tmp;                              /* TEMP FPS */
+    { static int k; if (++k % 60 == 0) fprintf(stderr, "TEMP FPS: draw %.1f ms, present/swap %.1f ms, record %.1f ms, %u draws\n",
+          t_draw/1e6, t_pres/1e6, t_rec/1e6, gsDrawCount); }       /* TEMP FPS */
```

Con eso se cierra la única duda abierta: cuánto es bucle de draws, cuánto swap y cuánto la lectura.

### 8.3. Si B confirma la grabación: que grabar sea opt-in (el arreglo real)

`BT2-test/jugar.sh:14`:

```diff
-     BT2_F9_RAM="$HERE/logs/vivo/$T" BT2_FIGHTLOG_OUT="$HERE/logs/vivo/$T.fight.log" BT2_RECORD="$HERE/logs/vivo/$T.mp4" BT2_RECORD_EVERY=2 \
+     BT2_F9_RAM="$HERE/logs/vivo/$T" BT2_FIGHTLOG_OUT="$HERE/logs/vivo/$T.fight.log" \
+     BT2_RECORD="${BT2_RECORD-$HERE/logs/vivo/$T.mp4}" BT2_RECORD_EVERY="${BT2_RECORD_EVERY-2}" \
```

Así `BT2_RECORD= ./jugar.sh` juega sin grabar y `./jugar.sh` sigue grabando como hoy. Si se quiere
mantener la grabación por defecto y aun así 60 fps, la alternativa es grabar a 2x (menos bytes) o mover la
lectura a un PBO con fence en otro hilo — más trabajo y más riesgo; primero medir con 8.2.

### 8.4. Si B NO confirma (el costo es la sumisión de draws)

Plan por orden de riesgo/beneficio, cada uno con su medición:
1. **Bajar a 2x** (ya probado: −2.9 ms en `ending`) y verificar 60 con el pacer nuevo.
2. **Fusionar draws consecutivos** con misma `target`/`pipeline`/`params`/`scissor`: hoy son ~2200 draws
   de ~45 vértices; una pasada de merge antes del bucle (`gs_gl.c:945`) puede bajar el número de llamadas
   GL a la mitad sin cambiar el resultado. Medir `TEMP FPS: draw` antes/después.
3. **`BT3_GS_THREAD=1`** (render en otro hilo, `gs_core.c:1398-1409`): solapa la sumisión con la espera del
   vblank. Es la solución de fondo (la PS2 también tenía el GS en paralelo) pero está marcado experimental
   por el bug de cámara (el juego toca datos que la lista todavía referencia); no recomendarlo sin resolver
   eso antes.

## 9. Lo que NO está verificado

- El reparto exacto de los 11.5 ms entre sumisión CPU, GPU y lectura de `BT2_RECORD` (hace falta §8.2 o el
  A/B del §7).
- Que el A/B dé 60: es la hipótesis fuerte, no un hecho medido. El margen estimado sin grabación es
  10-12 ms contra 16.7, pero el `work` histórico a 2x también marcaba 18 ms y andaba a 60 con el pacer
  viejo; hay un sesgo de medición de ±1-2 ms que el A/B va a despejar.
- La ventana de 11.3 s con 5.3 vsync/s: coincide con los F9 y el volcado de RAM, pero no puedo probar que
  no haya habido además un tirón externo (foco/ventana) porque el log no tiene hora por línea.
- Que el usuario juegue siempre con `BT3_GS_VERBOSE=1` (este run lo tenía; `jugar.sh` no lo pone). Si en
  sus partidas normales está apagado, el 40 podría ser algo mejor; conviene medir el A/B sin verbose.

## 10. Resultado (2026-11-11, aplicado y verificado)

A/B con `BT2_DEMO=1` (combate CPU vs CPU del propio juego, escala 3, GL, ~40 s de pelea por corrida):

| corrida | vsync/s | work/frame | "submitting" |
|---|---|---|---|
| A: `BT2_RECORD` ON | 40.0 | 14.2–14.8 ms | 9.5–9.7 ms |
| B: `BT2_RECORD` OFF | 60.0 | 9.4–10.0 ms | 5.2 ms |

La grabación cuesta ~4,5 ms por cuadro y era la causa del 40 sostenido. Aplicado:

- `BT2-test/jugar.sh`: `BT2_RECORD="${BT2_RECORD:-}"` → **opt-in** (`BT2_RECORD=/ruta.mp4 ./jugar.sh`).
- `port/full/gs/gs_core.c`: el presupuesto del log pasa a **16,7 ms (60 Hz)** en vez de 33,4, y los textos.
- Build `65a96a88…`, instalado.
- Verificación: demo CPU vs CPU, 32/39 muestras a **60.0**; los bajones (54.5/45.6/36.7) son decodificación de
  texturas nuevas al entrar efectos, no la grabación. `slow:` ahora cuenta los cuadros fuera de presupuesto
  (antes decía "0 de 60" con el juego a 40).

Sin verificar: una pelea real con todos los efectos (la demo es más liviana) y la grabación en Vulkan (no
existe). Si una pelea real sigue bajando de 60, el siguiente paso es §8.4.2 (fusionar draws) o bajar a 2x.
