# FPS — selección de escenario (Map Select): investigación de solo lectura

Fecha: 2026-11-12. No se modificó ni compiló nada; no se lanzó el juego (la corrida `015643` la hizo la sesión
principal al cambiar `jugar.sh`). Todo lo que sigue sale de leer el árbol y de dos logs reales:

- `BT2-test/logs/vivo/20261112-015417.log` — build del reporte, `BT2_FPS=45` para pelea **y** menú.
- `BT2-test/logs/vivo/20261112-015643.log` — misma base, `jugar.sh` ya con `BT2_FPS_MENU=65` /
  `BT2_FPS_FIGHT=45` (lo aplicó la sesión principal a las 01:56; el `ritmo:` de la línea 94 lo confirma).

## 0. Resumen en una línea

La pantalla **no está por debajo del tope: está clavada en el tope**. Corre a 45 cadenas/s con el menú a 45 Hz y a
65.1 cadenas/s con el menú a 65 Hz, con ~2–4 ms de trabajo por cadena, así que el renderer tiene de sobra. El
detalle que importa: en el Map Select se presentan **dos cadenas VIF1 por vuelta** (la del menú 2D y la cadena
vacía que agrega el HLE del video en `mwPlyGetStat`), y **las dos llaman a `Port_PacePresent`**. Por eso la vuelta
del juego va a **la mitad** de `gsframe/s`: ~22.5/s con menú 45 y ~32.5/s con menú 65. Subir el menú a 65 da
exactamente los ~10 fps pedidos; para 60 de verdad hace falta que la cadena extra del video no consuma un flanco.

## 1. Mapa del camino (qué corre por frame con la preview visible)

Es el objeto `D_0042BB80` ("map screen", selección de escenario de los versus / torneo):

| archivo:línea | qué hace por vuelta |
|---|---|
| `port/eq/41A5D8.c:56-67` | bucle exterior del Map Select. `3B46D0` (swap), **`28B090` (manda la cadena VIF1 del menú 2D)**, `271610` (DMA), `419E80` (update + video), `419820` (layout 2D → `418CC8`/`418E78`), `3B4718` (`sceGsSyncPath` + `EndStageSwap` + `gGfx.frame++`). **No llama a `2711E8`/`271240`: esta pantalla no espera vblank.** |
| `port/eq/419E80.c:22-37` | estado del reproductor: countdown, `3B4B90`, `3B5128` y `3B4FF8` cuando toca. |
| `port/eq/419040.c:11-19` | `buf[0] = 0x55B + stage` (el id del video del escenario sale de `D_0042BB80->0xFC[0xD4]`), crea el player (`3B4780`) y lo arranca (`3B4FF8`). |
| `port/eq/3B4780.c:20-56` | crea el handle CRI (`3B4B58`), copia el récord de 0x18 bytes, fija estado 2, y arma las matrices (filas 0..3 y 128.0 x16). Una vez por cambio de escenario. |
| `port/eq/3B4FF8.c:8-20` | si `0x1B8 != 0` → `2BB038` (rama AFS en bucle); si no → `2B73C0`. |
| `port/eq/2BB038.c:13-17` | HLE: `Port_MovieStartAfs(ptid=arg1, flid=arg2)` — no hay CRI. |
| `port/full/plat_movie.c:229-243` | `start_afs`: lee el bloque AFS completo (~6.7 MB, `Port_ReadAudioFile`), lo abre en memoria (`open_afs_movie`), `512x256`, `loop=1`, `live=1`. |
| `port/full/plat_movie.c:172-186` | `next_frame`: `avcodec_receive_frame` + `sws_scale` BILINEAR a **512x256 RGBA (1:1, sin upscale)** + copia a "tiras" con alfa 0x80. Solo cuando vence el reloj del video (29.97 fps). |
| `port/full/plat_movie.c:252-268` | `mwPlyGetFrame`: decodifica lo que toque por reloj y devuelve `strips`. Marca `sPresent=1`. |
| `port/eq/418CC8.c:32-37` y `418E78.c` | por frame: `TexFile_UploadOne` (texturas del menú), **`3B4C20` → GetFrame + GetStat**, y después `Dma_BeginDirect`/`Dma_EndDirect` (cadena del menú 2D). **Las dos cosas en la misma vuelta.** |
| `port/full/plat_movie.c:271-287` | `mwPlyGetStat`: si hubo `GetFrame`, duerme hasta 16.68 ms fijos y llama **`Port_GsVif1Chain(sEndTag)`** = presentación de una cadena vacía. |
| `port/full/gs/gs_core.c:1594` | **toda** cadena termina llamando `Port_PacePresent`. |
| `port/full/plat_gs.c:153-174` | `Port_PacePresent`: topo por `vblank_period()`, que en `plat_gs.c:88` es `Port_EnPelea() ? pelea : menú`. En el Map Select `Port_EnPelea()` = 0 (la lista de luchadores no está montada todavía), así que usa **`BT2_FPS_MENU`**. |
| `port/full/plat_fightlog.c:72-78` | `Port_EnPelea`: memoria de `D_00387930`. |

Las texturas 2D del menú se suben por frame (`TexFile_UploadOne`, `uplog ... dir 0`), pero no se re-decodifican
(`dclut 0`); el widescreen/aspect sólo entra en el present (`scale_apply`). Nada de DATE en esta pantalla:
`blit5 = 0` (el copiado por scissor de `date_snapshot`, `gs_draw.c:732`, es de la pelea).

## 2. Evidencia y números

### 2.1 El tope, no el rendimiento

```
015417 (menú 45):   bt2: ritmo: pelea 45.00 Hz, menu 45.00 Hz (iguales: sync)      [línea 94]
015643 (menú 65):   bt2: ritmo: pelea 45.00 Hz, menu 65.00 Hz                       [línea 94]
```

Ventana de selección de escenario (la pantalla que no llama `sceGsSyncV`; en el medio se cargan los videos
`0x55B..0x56A`, 20 cargas de ~6.7–7.3 MB con `[movie] AFS ptid 0 flid 0x55X -> ... bytes`):

| corrida | ventana | vsync/s | **gsframe/s** | GLP `loop`/`total` | `work per frame` | `blit5` |
|---|---|---|---|---|---|---|
| 015417, menú 45 | t=29.4→34.7 s, vsync 1320→1380 | **11.4** (no hay vblank en esta pantalla) | **45.0** | 0.7–0.8 ms | 2.2 ms (f=1321), peor 3.1 | **0** |
| 015643, menú 65 | t=22.3→36.8 s, vsync 1440→1500, 14.5 s | **4.1** (idem) | **65.1** | 0.2–1.2 ms | 2.4–4.3 ms | **0** |

- `vsync/s` bajo **no es un bajón**: en esta pantalla el juego no llama `sceGsSyncV`; el reloj de vblank no avanza
  y el único pacer es `Port_PacePresent` (`gs_core.c:1594`). El número que vale es `gsframe/s`.
- `gsframe/s` = exactamente el período configurado (45.0 / 65.1) en todas las ventanas, sin caídas. Para comparar,
  el título/menú sin video de la misma corrida 015643 da `vsync/s=65.0 gsframe/s=65.0` (1 cadena por vuelta:
  ahí sí hay vblank y el número coincide).
- Peor cuadro durante la exploración de escenarios: `slow: frame 2072: 17.4 ms = game 17.0 ms + display list 0.4`
  (cargar el próximo bloque AFS). A 65 Hz el presupuesto es 15.38 ms: se pierde **1 cuadro por cambio de
  escenario**. El resto, 2.4–4.3 ms por cadena.

### 2.2 Dos cadenas por vuelta (por qué el menú va a la mitad)

En la misma pasada `418CC8`/`418E78` hace `3B4C20` (que en `3B4C20.c:16-23` llama `2B4FD0` y `2B8328`) **y**
`Dma_BeginDirect/EndDirect` (cadena 2D que después manda `28B090` en `41A5D8.c:59`). Con la preview viva:

- `GetStat` → `Port_GsVif1Chain(sEndTag)` = una cadena **vacía** (evidencia directa: `gs: frame 1680: 1 DMA tag,
  0 vertices, 0 image qwords`).
- `28B090` → la cadena del menú con los draws/upload (`gs: frame 1620: ... 134 vertices, 76004 image qwords`).

`Port_PacePresent` se ejecuta al final de **las dos** (`gs_core.c:1594`), y las dos duermen a la misma grilla de
`vblank_period()`. Resultado: dos flancos por vuelta.

- 015417: 45 cadenas/s ÷ 2 = **~22.5 vueltas/s**.
- 015643: 65.1 cadenas/s ÷ 2 = **~32.5 vueltas/s**.

Corrobora el número: el pacer propio del video (`plat_movie.c:278`) capa a 59.94 Hz **solo** las cadenas con
`GetFrame`; si hubiera una sola cadena por vuelta, `gsframe/s` no podría pasar de 59.94, y se midió 65.1. Y el
pedido del usuario ("~10 fps") coincide exacto: 22.5 → 32.5 con el menú a 65. Además, la preview nativa es
29.97 fps: a 22.5 vueltas/s se tiraban ~7.5 cuadros/s de video (de ahí lo "lenta"); a 32.5 entra completa.

## 3. Separación CPU / GPU / pacing

- **CPU (decode+upload):** no es el límite. `next_frame` escala 512x256→512x256 (sin upscale) y decodifica a
  29.97 fps; el `work` total por cadena es 2.4–4.3 ms y el `game code` en esta pantalla es de décimas de ms. El
  único costo visible es la lectura+open del bloque AFS al cambiar de escenario (17.0 ms en un cuadro).
- **GPU:** no es el límite. `GLTIME loop` 0.2–1.2 ms, `dclut 0`, `swap 0`, `blit5 0`. El present con
  aspect 1600 y scale 2 está incluido en ese `total`.
- **Pacing:** acá está todo. Pantalla sin `sceGsSyncV` → `Port_PacePresent` con `BT2_FPS_MENU`; y **dos** chains
  por vuelta comparten ese pacer. `vblank_wait` no participa.

## 4. Hipótesis (y descartes)

| hipótesis | veredicto | evidencia |
|---|---|---|
| decode MPEG2 + `sws_scale` + upload por frame | **real pero barato** | 2.4–4.3 ms/cadena; 65.1 cadenas/s sostenidas con 20 cargas de preview |
| preview a resolución completa / upscale | **descartada** | `movie_init("afs", 512, 256)` (`plat_movie.c:168`), origen 512x256; `sws_scale` es 1:1 |
| loop/seek por frame | **descartada** | seek/flush sólo al cambiar de escenario (`plat_movie.c:191-198`) |
| texturas del menú re-subidas | **real pero barato** | `uplog dir 0` por frame, pero `dclut 0` y `loop` ≤1.2 ms |
| 2D/widescreen | **descartada** | aspect 1600/scale 2 dentro de `total` 0.2–1.2 ms |
| cap 200 de DATE / copia por scissor | **no aplica** | `blit5 = 0` en todo el Map Select; el DATE es de la pelea |
| efectos ON (`fx_off=0`) | **no implicado** | la pantalla no tiene pases 3D; el trabajo es mínimo |
| `BT2_FPS_MENU` / doble pacer | **causa** | 45.0 vs 65.1 exactos; 2 chains/vuelta (§2.2) |

## 5. Fix propuesto (sin aplicar)

### Opción A — cero código (ya está en el árbol, y da los +10)

`BT2-test/jugar.sh:13` ya tiene `BT2_FPS_MENU=${BT2_FPS_MENU:-65}` y `BT2_FPS_FIGHT=${BT2_FPS_FIGHT:-45}`.
Medido: la vuelta del Map Select pasó de ~22.5 a ~32.5/s (los ~10 fps pedidos) y la pelea siguió en 45
(`015643`: tras la BATALLA, `fpslog` vuelve a 45.0). Es la opción de mínimo riesgo.

### Opción B — 60 fps reales en el Map Select (diff boceto)

Que la cadena vacía del preview no gaste un flanco; la cadena del menú de la misma vuelta es la que pacea.
Mantener el `nanosleep` de 16.68 ms del video o quitarlo es indiferente (la vuelta ya va a 60–65).

```diff
--- a/port/full/plat_gs.c
+++ b/port/full/plat_gs.c
@@ -150,6 +150,11 @@
  * flanco; si llega tarde, no se recupera despues (igual que la PS2). No hace nada sin GPU ni con BT2_UNCAPPED. */
+static int sPaceSkip;   /* la cadena extra del preview no consume un flanco de esta vuelta */
+void Port_PaceSkipNext(void) { sPaceSkip = 1; }
+
 void Port_PacePresent(void) {
     static int paced = -1;
     static unsigned long long last;
     unsigned long long per, t;
 
+    if (sPaceSkip) { sPaceSkip = 0; last = now_ns(); return; }
     if (paced < 0) paced = getenv("BT2_PACED") != NULL;
```

```diff
--- a/port/full/plat_movie.c
+++ b/port/full/plat_movie.c
@@ -247,6 +247,7 @@
 extern void Port_GsVif1Chain(u32 tadr, int tte);
+extern void Port_PaceSkipNext(void);
@@ -283,6 +284,8 @@
         last = t;
         sPresent = 0;
+        if (M.loop && M.live)   /* AFS del Map Select: el menu ya manda su propia cadena en esta vuelta */
+            Port_PaceSkipNext();
         Port_GsVif1Chain((u32)(uintptr_t)sEndTag, 0);
```

Con eso, `BT2_FPS_MENU=60` daría ~60 vueltas/s (y 120 cadenas/s; el present extra cuesta ~0.2 ms). Dejar 65
también sirve (65 vueltas/s).

**Riesgo a probar:** `M.loop && M.live` es el camino exclusivo de `Port_MovieStartAfs` → `2BB038` → Map Select
(no lo usa el player de apertura/ending, que va por `func_002B6E50`/`open_movie`). Si algún otro menú usara el
AFS **sin** cadena propia, quedaría sin tope; hay que verlo con el log (`gsframe/s` > 65) antes de cerrar.

### Descartado como fix
- Cachear cuadros decodificados / decodificar sólo al cambiar / bajar resolución: el decode ya corre a 29.97 fps
  y el trabajo es 2.4–4.3 ms; no mueve el número porque el límite es el pacer.
- Sacar `Port_GsVif1Chain` de `GetStat` directamente (sin skip): más limpio en teoría, pero es justo lo que la
  B15 agregó para que la preview se viera; no hay evidencia de que la cadena del menú alcance sola en todas las
  ramas. El skip deja el present y sólo evita el doble tope.

## 6. Qué queda sin verificar

- No hay un contador independiente de vueltas del juego (no se pudo instrumentar en esta tarea). "2 cadenas por
  vuelta" se deriva del código (`418CC8` llama `3B4C20` **y** arma la cadena 2D; `gs_core.c:1594` pacea toda
  cadena) y de que `gsframe/s = 65.1` supera el tope de 59.94 del pacer del video, lo que descarta 1 cadena por
  vuelta. El valor exacto de la vuelta (~32.5) es derivado, no contado con un hook.
- El efecto de la opción B sobre otras pantallas que usen `Port_MovieStartAfs` no está probado (sólo el Map Select
  aparece en los logs con `0x55B..0x565`).
- El "17.4 ms" al cambiar de escenario es lectura/open del AFS; si molesta, se puede precargar, pero es 1 cuadro
  por cambio, no el FPS sostenido.

## 7. Confirmación

- 015417 (menú 45): ventana del Map Select a **45.0 gsframe/s** = tope, 0 cuadros perdidos respecto del tope;
  ~22.5 vueltas/s.
- 015643 (menú 65, mismo binario, sólo cambia el env): misma pantalla, 20 cargas de preview, **65.1 gsframe/s**
  = ~32.5 vueltas/s (+10), trabajo 2.4–4.3 ms/cadena, `blit5 0`. La pelea posterior sigue en **45.0**.
- Conclusión: los ~10 fps se recuperan subiendo `BT2_FPS_MENU` (ya aplicado). Para llevar la pantalla a 60
  vueltas/s hace falta el skip del pacer en la cadena del video (opción B).
