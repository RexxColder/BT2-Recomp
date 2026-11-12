# FX "Glare and glow" (bit 8): mapa, estado ON/OFF y costo — seguimiento del problema de FPS

Investigación **solo lectura** (2026-11-12). No se editó ni compiló nada.
Fuentes: `port/full/gs/gs_draw.c`, `port/full/gs/gs_gl.c`, `port/full/gs/gs_gpu.c`,
`port/full/gs/ui.cpp`, `include/sys/gfxm_a.h`, `src/sys/gfxm_a_279670.c`,
`BT2-test/bt2_settings.txt` y el log `BT2-test/logs/vivo/20261112-004130.log`
(pelea real, GL, escala 2x, `BT2_GLTIME=1`, `BT3_GS_VERBOSE=1`).

Líneas de código citadas = estado actual del árbol **al 2026-11-12 00:59** (el porter está
editando `gs_draw.c`/`gs_gl.c` en paralelo; si cambian, los números pueden correrse). El backup
`backups/gs_draw.c.pre_fxgate` difiere del actual en dos hunks del porter: el `TEMP FXSEE` de
`depth_clut` (hoy `gs_draw.c:467-472`, log opcional con `BT2_FXSEE=1`) y el gate de `native 4`,
que pasó a exigir bits 1+2+8 (`513-524`). No hay otros cambios de código.

---

## 0. Resumen

1. **El gate de glare/glow que puso el porter funciona**: con `fx_off=31` se descartan
   **17 primitivas por cuadro** en `gs_draw.c:597-601` (`gsSkipWhy[4]`), constantes en **187
   de los 187 cuadros de pelea muestreados** (`gpu: dropped by site: ... 17 0`).
   Ese 17 es el add-back final (16 tiras de 32x448 con ALPHA 0x68) + 1 del distance blur, que
   comparten contador.
2. **La premisa "blit 615/60 frames" está mal leída**: en `gs_gl.c` el contador `nBlit` es
   **local y se reinicia en cada `frame_end`** (`gs_gl.c:900`), y `GLTIME` se imprime en el
   mismo `frame_end` (`gs_gl.c:1276-1282`). `blit 615` significa **615 blits en el cuadro
   2040**, no 615 en 60 cuadros. Lo mismo `blit 613` en el cuadro 2280.
3. **`native 5` no es glare/glow** (dato del porter, confirmado en código): es el snapshot de
   alfa para `TEST.DATE` (`date_snapshot`, `gs_draw.c:718-731`). **No se debe gatear con
   `fx_off`**: rompería los recortes por máscara del HUD, las bandas de anuncios y capas del
   escenario. `native 4` sí está gateado (bits 1, 2 y 8 en el código actual) y con `fx_off=31`
   no se emite.
4. **El glow no puede generar las 615 copias**: su add-back se descarta entero (17
   primitivas/cuadro), el gate retorna **antes** de `date_snapshot`, y la cadena de work
   buffers (0x150/0x170/0x1F6/0x1F8) no se samplea a sí misma. Las 615 copias aparecen **sólo**
   en los cuadros del efecto (técnica/golpe: vblanks ~1951-1978 y 2000-2053, y ~2233-2313),
   mientras el glow se intenta **todos** los cuadros de pelea con el mismo 17. Se descarta como causa.
5. **Causa más probable de esos cuadros de 65-80 ms**: copias de alfa `native 5` (o `native 6`)
   a **pantalla completa 2048x2048** por copia (`gs_gl.c:1006`), ~615 por cuadro:
   615 x 4,19 Mpix = **2,58 Gpix**, que a los ~43 Gpix/s de ROPs de la RX 580 dan **~60 ms**.
   Coincide con `swap 49.9 ms` y con que el `loop` (CPU) sea sólo 17,6 ms. El arreglo va por
   **copiar menos área** (`512x448` en vez de `1024x1024`, 4,57x menos), no por apagar el glow.
6. El reparto exacto `native 5` vs `native 6` **no lo puede dar este log**; se propone un
   contador TEMP (§8) para cerrarlo.

---

## 1. Mapa de código

| Pieza | Dónde | Qué hace |
|---|---|---|
| Menú F1 → Effects | `port/full/gs/ui.cpp:387` (nombre), `391-392` (checkbox ↔ bit) | "Glare and glow" = índice 3 = **bit 8**. Tooltip: bloom + glare del cielo. |
| Bits | `port/full/gs/ui.h:13` | 1 outline, 2 see-through, 4 depth tint, **8 glare and glow**, 16 distance blur. |
| Carga/guardado | `gs_draw.c:1311` (`BT3_FX_OFF` o setting `fx_off`), `1263-1264` (UI), `1276-1277` (save) | `gsFxOff & 31`. |
| Gate del add-back | `gs_draw.c:597-601` | Descarta sprite con `target == gGsMainFbp`, `prim bit 6` y `ALPHA == 0x68` si `gsFxOff & 8`; `ALPHA == 0x54` si `& 16`. Suma a `gsSkipWhy[4]`. |
| Fuerza del glow | `gs_draw.c:853-861` | Si `gsGlowPercent != 100`, escala RGB de los vértices del add-back (0x68). Default 60 (`gs_draw.h:28`). Sólo actúa si el add-back se dibuja. |
| Cadena del glow (juego) | `src/sys/gfxm_a_279670.c:177-190` | 5 pasos: frame→0x150 (256x256), →0x170, →0x1F6 (64x64), blur entre 0x1F6/0x1F8, subida a 128 y 256, **add-back al frame con ALPHA 0x68**. |
| Pases del juego | `include/sys/gfxm_a.h:12-21` | "Every pass … GS sprites, 16 strips of 32x448"; work pages 0x150 (tbp 0x2A00) y 0x170. |
| Callers | `gfxm_a_279670.c:252-253` (StgGlare_Draw), `308` (ObjGlow_Draw) | StgGlare: limpia el alfa del frame, escribe el alfa del CLUT por depth y llama al glow. ObjGlow: sube la tabla de alfa por id y llama al glow. Ambos terminan en el mismo add-back 0x68. |
| Copia de alfa (DATE) | `gs_draw.c:718-731` (`date_snapshot`), llamadas en `766`, `956`, `1010`, `1050` | **native 5**: copia del alfa por cada run de primitivas con `TEST.DATE`. No consulta `gsFxOff`. |
| Copia de ids (outline/see-through/glow) | `gs_draw.c:513-524` | **native 4**: gateada por `(fx & 1) && (fx & 2) && (fx & 8)` (tres lectores; ver §2). |
| Copia de self | `gs_draw.c:596-612` | **native 6**: draw que samplea su propio target. |
| Copia real (GL) | `gs_gl.c:989-1014`, blit en `1006` | `glBlitFramebuffer(0,0,GS_W*SCALE,GS_H*SCALE, …)` → **2048x2048** con escala 2. |
| Copia real (Vulkan) | `gs_gpu.c:683-740` | `SDL_CopyGPUTextureToTexture(..., GS_W*SCALE, GS_H*SCALE, …)` para 6, 5 y 4. |
| Cronómetro | `gs_gl.c:900`, `1006-1009`, `1197-1199`, `1276-1282` | `nBlit`/`blitNs` (y `n4/n5/n6`, ya agregados por el porter) locales por cuadro; `loop` = fin del loop de draws + present; `swap` = `SDL_GL_SwapWindow`. |
| Uso del DATE | `port/full/gs/shaders/gs.frag:26-30` | `texelFetch(dateTex, ivec2(gl_FragCoord.xy))` → la copia tiene que estar a la misma resolución que el framebuffer (SCALE). |

---

## 2. Qué corta `fx_off & 8` y qué no

| Pase | ¿Lo corta el bit 8? | Evidencia |
|---|---|---|
| Add-back del glow al frame (16 tiras, ALPHA 0x68, prim + dest) | **Sí** | `gs_draw.c:597-601`; `gsSkipWhy[4] = 17` por cuadro de pelea. |
| Add-back del distance blur (ALPHA 0x54) | Sí, con bit 16 | misma condición; comparte `gsSkipWhy[4]`. |
| Cadena de work buffers del glow (0x150, 0x170, 0x1F6, 0x1F8) | **No** | sus targets no son `gGsMainFbp`; el gate exige target principal. |
| Preparación del alfa (depth CLUT / tabla de ids) | **No** | `depth_clut` sólo mira bit 4 (tint con write mask) y bit 2 (CBP 0x3E94): `gs_draw.c:440-451`. |
| Escalado por `glow` (%) | No aplica | sólo toca vértices del add-back (`853-861`), que con bit 8 no se generan. |
| `native 4` (sAuxCopy) | No depende del bit 8 solo | gate actual con bits **1, 2 y 8** (`516-523`): la copia alimenta outline (1), see-through (2) y los pases de tabla que sólo escriben alfa del glow (8). Con `fx_off=31` no se emite. |
| `native 5` (sDateCopy) | **No** | `date_snapshot` no lee `gsFxOff` (`718-731`). |
| `native 6` (sSelfCopy) | **No** | `596-612`. |

**Lo que NO hay que hacer**: meter `gsFxOff & 8` en `date_snapshot`/`native 5`. El alfa de
destino no es del glow: lo usan los recortes del HUD, las bandas y las capas del escenario.
Apagarlo dejaría esos recortes mal (y el efecto seguiría sin ser el culpable).

---

## 3. Qué se emite por frame (pelea, `fx_off=31`, escala 2x)

| Elemento | ON (bit 8 = 0) | OFF (bit 8 = 1) | Costo |
|---|---|---|---|
| Add-back glow (blanco/brillo sobre el frame) | 16 primitivas dibujadas (32x448 c/u ≈ 0,23 Mpix) | 16 descartadas antes de generar vértices | ON: ~0,23 Mpix de fill; OFF: 0 |
| Cadena de work buffers del glow | se emite igual | se emite igual | ~0,3-0,4 Mpix/frame (estimado por los tamaños 256²/128²/64²), unas pocas llamadas GL tras el merge |
| `native 3` (depth CLUT) | 3-4/cuadro | 3-4/cuadro | `dclut 3/0.0 ms` en el log |
| `native 4` (ids) | 1 por CopiaAlfaADepth (si outline/see-through/alfa del glow ON) | **0** (gate bits 1, 2 y 8) | 4,19 Mpix por copia |
| `native 5` (alfa DATE) | runs DATE del cuadro | runs DATE del cuadro | **14-20/cuadro normal; 615 en el cuadro 2040; 613 en 2280** |
| `native 6` (self) | si hay draw que se samplea | ídem | raro en pelea (radar: ~1/cuadro) |
| Present | 1 triángulo full-screen + swap | ídem | fijo |

El log no tiene contador de draws por target, así que **la cantidad exacta de la cadena de work
buffers no está medida**; sí está acotada por el código: como máximo ~80 primitivas antes del
merge (16+16+16+2·passes+4+8+16) y, tras `same_state`, unas pocas draw calls. Su fill es
despreciable frente a las copias.

---

## 4. Evidencia del log y corrección de la premisa

### 4.1 El contador es por cuadro

```c
/* gs_gl.c:900 */
unsigned nDclut = 0, nBlit = 0;
/* ... gs_gl.c:1276-1282, dentro del mismo frame_end */
if (getenv("BT2_GLTIME") != NULL && (gGsFrame % 60 == 0 || dclutNs > 20000000ull)) {
    fprintf(stderr, "GLTIME f=%u dclut %u/%.1f ms blit %u/%.1f loop %.1f swap %.1f total %.1f\n", ...);
}
```

`nBlit` arranca en 0 en **cada** `frame_end` y se imprime antes de reiniciar. Por eso:

- `GLTIME f=2040 … blit 615/0.0 … swap 49.9 total 67.6` (log línea 66053) = **615 blits en el
  cuadro 2040**.
- `GLTIME f=2280 … blit 613/0.0 … swap 19.8 total 55.6` (línea 72053) = **613 en el cuadro 2280**.
- En todos los demás cuadros muestreados: **14-21 blits**.

Además, como sólo imprime en `f % 60 == 0` (o si `dclutNs > 20 ms`), un pico en un cuadro que
no sea múltiplo de 60 **no se ve**. Por eso el §8 propone imprimir también con `nBlit > 100`.

### 4.2 Configuración de la corrida

`BT2-test/bt2_settings.txt`: `scale=2`, **`fx_off=31`**, `glow=60`.
Log líneas 8-9: `internal resolution 2x (1024 x 896)`, `AMD Radeon RX 580 Series`.

### 4.3 El gate del glow está activo y es constante

En los cuadros de pelea, `gpu: dropped by site` da, según la ventana:

- `144 96 0 48 17 0` (88 veces)
- `144 80 0 48 17 0` (96 veces)
- `144 80 1 48 17 0` (3 veces)

(el 144/96/80 y 48 son otros descartes, sitios 0/1/3). **`gsSkipWhy[4] = 17` siempre**, o sea que
el add-back del glow (y el mix del blur) se intenta y se descarta **todos los cuadros de pelea**,
incluido el 2040 (log línea 66051). Dato clave: si el glow fuera el que genera las 615 copias,
también habría 615 copias en los cuadros normales, y hay 14-20.

### 4.4 La ventana pesada es una técnica/golpe, no el renderer en reposo

Cuadros 1951-1978 y 2000-2053 (log 64205-66352), y 2233-2313: la mayoría 58-80 ms, casi todos
con **0 texturas nuevas y 0 pipelines** (las pocas que hay son de 4-70 KB y no explican 60 ms).
El `game` es 2-17 ms (no es código del juego). El fight log muestra el efecto: en el vblank 1948
J2 arranca una acción (`acc 9D→3A`, anim 2/69), en el 1998 hay `GOLPE` y `PTCL-COLOR/QUAD`
(líneas 1335-1346 del `.fight.log`), y el cuadro 2040 cae dentro de esa reacción.
A las 2280 hay otra acción de J1 y otra ventana pesada. **No es un estado permanente.**

### 4.5 No es la cantidad de draws

| cuadro | draws | vértices | work (ms) | blit |
|---|---|---|---|---|
| 2010 | 2009 | 85.303 | 68,3 | (no impreso) |
| 2040 | 2049 | 88.036 | 64,7 | **615** |
| 2070 | 2435 | 116.959 | ~28 | (no impreso) |
| 2280 | 3067 | 119.180 | 72,1 | **613** |

El 2070 tiene **más** draws que el 2040 y va a ~28 ms; el 2280 tiene 3067 draws y 613 blits y va
a 72 ms. La diferencia no son los draws: son los blits.

### 4.6 La cuenta que cierra

- Blit actual: `GS_W*SCALE x GS_H*SCALE` = **2048x2048 = 4.194.304 px** por copia
  (`gs_gl.c:1006`; en Vulkan `gs_gpu.c:683-740`, lo mismo).
- 615 copias → **2.579.496.960 px ≈ 2,58 Gpix**.
- RX 580 (Polaris 20): 32 ROPs @ ~1,34 GHz ≈ **42,9 Gpix/s**.
- 2,58 Gpix / 42,9 Gpix/s ≈ **60 ms**. El GLINE del cuadro 2040 da 67,6 ms
  (`loop 17,6 + swap 49,9`; el `slow: frame 2040` del mismo cuadro mide 64,7 ms porque arranca
  en otro punto). Los blits explican el `swap` casi exacto.
- Memoria: el aux es `GL_R8` (`gs_gl.c:569`), 4,19 MB por copia leída + 4,19 escrita;
  615 copias = **5,16 GB/cuadro** (~76 GB/s a 67,6 ms). No es el límite principal, pero suma.
- `blitNs` mide sólo el **CPU** del `glBlitFramebuffer` (asíncrono): por eso da 0,0 ms y el costo
  aparece en `swap` (espera de GPU). Consistente con `slow: frame 2041 … submitting 67.6`.

---

## 5. ¿El glow puede generar las 615 copias? **No**

1. El add-back son **16 primitivas** (header `gfxm_a.h:12`: 16 tiras de 32x448) y el gate las
   descarta **antes** de `date_snapshot` (`GsGpu_Draw` llama `draw_state` y, si devuelve 0,
   retorna: `gs_draw.c:746-748`). Una primitiva descartada no inserta `native 5`.
2. Los pasos 1-4 de la cadena van a work buffers (0x150/0x170/0x1F6/0x1F8); ninguno se samplea
   a sí mismo (el blur alterna 0x1F6/0x1F8, el downscale lee el frame y escribe 0x150). No
   generan `native 6`.
3. La cadena se ejecuta **todos** los cuadros de pelea, pero las 615 copias aparecen **sólo** en
   los cuadros del efecto (1951-1978 y 2000-2053, 2233-2313). Si el glow fuera la fuente, el
   conteo sería alto siempre.
4. El propio dato del porter: `native 5` = `TEST.DATE`. El glow **no** hace un test por píxel
   contra el alfa copiado: el alfa de destino entra en la **ecuación de blend** (ALPHA 0x68) y
   la máscara la prepara antes un pase de depth CLUT. Apagarlo no cambia el número de copias.

**Conclusión**: las 615 son copias de `native 5` (DATE) o, en menor medida, `native 6`. Por el
contexto (técnica con cientos de primitivas ordenadas por OT, intercaladas con otras), lo más
probable es **`native 5`: un run DATE nuevo cada vez que una primitiva con DATE queda separada
de la anterior por una sin DATE**. El log no puede separar 5 de 6; el §8 lo resuelve.

---

## 6. Por qué NO se toca `native 5`

`date_snapshot` (`gs_draw.c:718-731`) se dispara con `TEST.DATE` (`d->misc[1]`), que el juego usa
para recortar por el alfa ya escrito: barras de HUD cortadas por máscara, bandas de anuncios,
capas del escenario. Gatearlo con `fx_off`:

- no ahorraría el costo del glow (no es glow);
- rompería esos recortes (se verían barras completas, bandas cuadradas, capas de más);
- y el costo real seguiría en los cuadros del efecto.

La optimización correcta de `native 5` es **copiar menos área**, no dejar de copiar (§9.2).

---

## 7. Costo CPU/GPU medido

- `dclut 3/0.0 ms`: los pases de tabla (glow/glare) no cuestan CPU medible.
- `blit 615/0.0 ms`: el CPU de las 615 copias es < 1 ms; el costo es GPU.
- `loop 17.6 ms`: loop de draws + present (≈2050 draws; en cuadros normales el mismo loop da
  ~10-18 ms con 2000-2500 draws). No explica el cuadro.
- `swap 49.9 ms`: espera del swap a que la GPU termine lo encolado. Es donde cae el fill de los
  blits (la cuenta del §4.6 da ~60 ms).
- El glow en sí (ON) son 0,23 Mpix de fill + la cadena (~0,4 Mpix): **< 1 ms**. Apagarlo no
  cambia el problema de FPS; con `fx_off=31` ya está apagado y el cuadro sigue en 67 ms.

---

## 8. Instrumentación TEMP propuesta (sin aplicar)

Objetivo: separar `native 4/5/6`, medir píxeles copiados y cazar los picos en cuadros que no son
múltiplo de 60. Sacar todo al cerrar el bug.

### 8.1 Contadores en `gs_draw.c`

```diff
--- a/port/full/gs/gs_draw.c
+++ b/port/full/gs/gs_draw.c
@@ unsigned gsNative;
+unsigned gsDatePrims, gsDateRuns;   /* TEMP FX: primitivas con TEST.DATE y copias native 5 */
@@ static void date_snapshot(const GsDraw *d) {
     ...
-    if (d->misc[1] == 0.0f || (prev != NULL && !prev->native && prev->misc[1] != 0.0f && prev->target == d->target)) {
+    if (d->misc[1] == 0.0f) {
         return;
     }
+    gsDatePrims++;                  /* TEMP FX */
+    if (prev != NULL && !prev->native && prev->misc[1] != 0.0f && prev->target == d->target) {
+        return;
+    }
+    gsDateRuns++;                   /* TEMP FX */
     memset(&c, 0, sizeof(c));
```

Resetear `gsDatePrims = gsDateRuns = 0` junto a `gsSkipped` (`gs_gl.c:1291-1293` y
`gs_gpu.c:1137-1139`).

### 8.2 Contadores y print en `gs_gl.c`

**Ojo**: el porter ya agregó, mientras corría esta investigación, `n4/n5/n6` en el mismo bloque
de blits y en el `GLTIME` (`gs_gl.c:900`, `1009`, `1279`). El log `20261112-004130` es anterior a
ese cambio, por eso no trae `blit4/5/6`. Lo que falta para cerrar el diagnóstico:

```diff
-    unsigned nDclut = 0, nBlit = 0, n4 = 0, n5 = 0, n6 = 0;
+    unsigned nDclut = 0, nBlit = 0, n4 = 0, n5 = 0, n6 = 0;
+    uint64_t blitPx = 0;                                                /* TEMP FX */
...
                 nBlit++;
+                blitPx += (uint64_t)GS_W * SCALE * GS_H * SCALE;          /* TEMP FX */
                 blitNs += dt;
...
-    if (getenv("BT2_GLTIME") != NULL && (gGsFrame % 60 == 0 || dclutNs > 20000000ull)) {
-        fprintf(stderr, "GLTIME f=%u dclut %u/%.1f ms blit %u/%.1f blit4 %u blit5 %u blit6 %u loop %.1f swap %.1f total %.1f\n",
-                gGsFrame, nDclut, (double)dclutNs / 1e6, nBlit, (double)blitNs / 1e6, n4, n5, n6, ...);
+    if (getenv("BT2_GLTIME") != NULL && (gGsFrame % 60 == 0 || nBlit > 100 || dclutNs > 20000000ull)) {
+        fprintf(stderr, "GLTIME f=%u dclut %u/%.1f ms blit %u/%.1f (4:%u 5:%u 6:%u, %.1f Mpix) "
+                        "date %u/%u loop %.1f swap %.1f total %.1f\n",
+                gGsFrame, nDclut, (double)dclutNs / 1e6, nBlit, (double)blitNs / 1e6, n4, n5, n6,
+                (double)blitPx / 1e6, gsDatePrims, gsDateRuns, ...);
     }
```

El `nBlit > 100` es importante: hoy un pico en un cuadro que no sea múltiplo de 60 no se imprime
(§4.1).

Con `n4/n5/n6` (ya presentes) más `gsDatePrims/gsDateRuns`, en el cuadro del efecto se lee
directo si los 615 son `5:` o `6:` y si los runs DATE acompañan. **No requiere otra corrida
distinta a la que ya se hace con `BT2_GLTIME=1`.**

---

## 9. Arreglo propuesto (diff boceto, SIN aplicar)

### 9.1 Glow: el gate actual ya es el arreglo; no agregar otro

Verificado con datos (§4.3): `gsSkipWhy[4] = 17` en todos los cuadros de pelea. **No hay que
cambiar `gs_draw.c:597-601`** ni tocar `native 5`.

Si en el futuro se quiere apagar también la cadena de work buffers (hoy se ejecuta igual y no
aporta nada con el add-back apagado), el único lugar seguro sin marker del juego son las páginas
**exclusivas** del glow de 64x64 (0x1F6/0x1F8). No recomiendo hacerlo ahora: el ahorro es
~0,01 Mpix/frame y 0x150/0x170 se comparten con el pan blur (bit 16). Boceto sólo como referencia:

```diff
--- a/port/full/gs/gs_draw.c
+++ b/port/full/gs/gs_draw.c
     d->target = GsDraw_TargetGet((uint32_t)(gGs.frame[ctx] & 0x1FF), 1);
     if (d->target < 0) {
         return 0;
     }
+    /* FX: las páginas 64x64 del blur del glow sólo las lee el pase que el bit 8 descarta */
+    if ((gsFxOff & 8) && (gsFxOff & 16) &&
+        (gsTargets[d->target].fbp == 0x1F6 || gsTargets[d->target].fbp == 0x1F8)) {
+        gsSkipped++; gsSkipWhy[6]++;
+        return 0;
+    }
```

(No aplicarlo sin medir: primero el contador por target del §8.2.)

### 9.2 FPS: copiar sólo el área de imagen en `native 5`/`6` (y `4` si algún día se usa)

El juego sólo dibuja y samplea los **512x448** GS píxeles de la imagen; `GS_W/GS_H = 1024` existen
sólo para dimensionar la textura. Copiar 2048x2048 es 4,57x más área de la necesaria.

`port/full/gs/gs_draw.h` (junto a `GS_W/GS_H`):

```diff
 #define GS_W 1024
 #define GS_H 1024
+#define GS_PIC_W 512   /* the picture the game actually draws: GS_W/GS_H only size the texture */
+#define GS_PIC_H 448
```

`port/full/gs/gs_gl.c:1006`:

```diff
-                glBlitFramebuffer(0, 0, GS_W * SCALE, GS_H * SCALE, 0, 0, GS_W * SCALE, GS_H * SCALE, GL_COLOR_BUFFER_BIT, GL_NEAREST);
+                glBlitFramebuffer(0, 0, GS_PIC_W * SCALE, GS_PIC_H * SCALE, 0, 0, GS_PIC_W * SCALE, GS_PIC_H * SCALE, GL_COLOR_BUFFER_BIT, GL_NEAREST);
```

`port/full/gs/gs_gpu.c` (tres copias, `native 6`/`5`/`4`; ej. líneas 683-740):

```diff
-            SDL_CopyGPUTextureToTexture(cp, &from, &to, GS_W * SCALE, GS_H * SCALE, 1, false);
+            SDL_CopyGPUTextureToTexture(cp, &from, &to, GS_PIC_W * SCALE, GS_PIC_H * SCALE, 1, false);
```

No hace falta tocar el shader: `dateTex` sigue midiendo `GS_W*SCALE` y el `texelFetch` por
`gl_FragCoord` no cambia; sólo se refresca la región que el juego puede leer/escribir.

Números esperados (misma escena, 615 copias): 615 x 0,917 Mpix = **0,564 Gpix** → ~13 ms de ROP
en vez de ~60 ms. El cuadro del efecto debería bajar de ~67 ms a ~25-30 ms; los normales no
cambian (14-20 copias).

**Segundo paso, opcional y con más riesgo**: copiar sólo el scissor del primer draw del run
(`d->scissor`) y cortar el run si un draw posterior se sale del rectángulo copiado. Para barras
de HUD recortadas el ahorro sería de otro orden (10-100x), pero hay que garantizar la
correctitud del run; no lo propongo para el primer intento.

### 9.3 Lo que NO hay que hacer

- **"Una copia por frame"** para `native 5`: inválido. El alfa cambia durante el cuadro; el test
  debe ver el valor de ese momento. Reusar la copia del cuadro anterior rompe los recortes.
- **Gatear `native 5` con `fx_off & 8`**: ver §6.

---

## 10. Cómo confirmarlo (una variable por corrida)

1. **Confirmar que las 615 no son glow** (no requiere rebuild): misma pelea, `BT2_GLTIME=1`,
   `BT3_GS_VERBOSE=1`, con `fx_off=31` y después con `fx_off=23` (glow ON; los otros bits
   siguen apagados). Esperado: `blit` idéntico en ambas (incluidos los picos), `site 4` pasa de
   17 a 0, y el `swap` del cuadro pesado cambia < 1 ms. Si el `blit` cambia, revisar el mapa.
2. **Separar 5 de 6**: el build del porter ya imprime `blit4/blit5/blit6` en `GLTIME`
   (`gs_gl.c:900,1009,1279`); el log viejo no los tiene. Con eso (y los `date prims/runs` del
   §8.1) el cuadro del efecto tiene que mostrar `blit 615 (4:0 5:6xx 6:y)` y `date ≈ 5`. Si `5:`
   no acompaña a `blit`, el culpable es `native 6` y el arreglo de área igual sirve (es el mismo
   blit), pero cambia la explicación.
3. **Confirmar que el cuadro pesado es fill-bound**: correr la misma escena a `BT3_SCALE=1`. El
   blit pasa de 2048² a 1024² (4x menos), pero **también** baja 4x todo el resto del fill; sirve
   para confirmar que el cuadro escala con los píxeles, no para aislar la copia. El aislamiento
   lo da el paso 4 (misma escala, menos área copiada).
4. **Aplicar §9.2** (build + install) y repetir 1 y 3: el `blit` sigue en 615 pero
   `Mpix` baja de ~2.580 a ~564 y el `swap` del cuadro pesado debe caer a la mitad o menos.
5. Cuidado con el ruido: no usar F9 ni `BT2_RECORD` en estas corridas (ver `staging/FPS_drop.md`
   §4 y §10), y comparar la **misma** técnica/golpe.

---

## 11. Lo que no está verificado

- Que las 615 sean exactamente `native 5` y no una mezcla con `native 6`: el log no los separa.
  El contador del §8 lo cierra.
- La cantidad exacta de primitivas/draws de la cadena de work buffers del glow y su fill real
  (estimado por código, sin contador por target).
- **Riesgo del gate nuevo de `native 4`**: con `fx_off=31` se saltea la copia (bits 1+2+8), pero
  los pases de tabla que sólo escriben alfa del glow siguen corriendo (el gate del bit 8 sólo
  actúa en el add-back). Si esos pases leen `sAuxCopy`, leen la copia vieja; no se ve en el log y
  el add-back está apagado, pero convendría confirmar que no ensucian el alfa que después usan
  los `TEST.DATE` del HUD. Es del cambio del porter, no de este informe.
- Que las 16 tiras del add-back sean 16 y no otra cantidad en esta escena: `gsSkipWhy[4]=17` es
  compatible con 16 tiras + 1 del blur, pero el contador no separa los dos gates.
- Que `fx_off=23` en la corrida de control no altere el timing por otras razones (texturas,
  pipelines): hay que mirar `slow:` y `new textures` en ambas ramas.
- El efecto exacto que dispara los runs DATE (partículas del golpe vs. capas del escenario):
  el `.fight.log` muestra el golpe en 1998 y la ventana pesada, pero no hay traza por primitiva
  con DATE en este log.
