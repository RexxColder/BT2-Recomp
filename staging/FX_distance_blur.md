# FX — Distance blur (`fx_off & 16`): camino, estado y costo (solo lectura, 2026-11-12)

Investigación sin editar, compilar ni lanzar el juego. Proyecto: `BT2-Recomp`.
Logs usados: `BT2-test/logs/vivo/20261112-005253.log` (build con gate de efectos, sin contadores por
tipo de blit) y `BT2-test/logs/vivo/20261112-010217.log` (build posterior, ya con `blit4/blit5/blit6`).
Settings de la sesión: `scale=2` (1024x896), `fx_off=31`, `glow=60`.

Nota: en `staging/` al momento de escribir sólo estaban `FX_see_through.md` y `FX_depth_tint.md`
(no `FX_outline.md` ni `FX_glare_glow.md`). No los repito; sólo uso el contraste necesario.

**Resumen (5 puntos)**

1. **El bit 16 corta sólo el pase final**, el que mezcla el buffer de trabajo sobre la pantalla con
   `ALPHA 0x54` (`gs_draw.c:605-609`). La copia del frame al buffer de trabajo y el resto de la cadena
   se siguen emitiendo con el efecto apagado.
2. **No produce copias `native 4/5/6`.** Esa cadena sólo lee un work buffer y escribe en el frame
   principal (targets distintos), no usa `TEST.DATE` y no se muestrea a sí misma. No toca `sDateCopy` ni
   `sAuxCopy`.
3. **No es la causa de los 615 blits.** El log posterior con contadores lo cierra:
   `blit 614 = blit4 0 + blit5 614 + blit6 0` (f=1800, 2040, 2700, 5160). El pico es **100 % `native 5`**
   (snapshots DATE de HUD/partículas/textos), ajeno a los switches FX.
4. **Costo propio: ~2 draws** (la copia y el compuesto; los 16 strips de cada uno se colapsan en el
   renderer). Con OFF se ahorra **1 draw** (el compuesto); la copia sigue. En un frame de 3001 draws es
   despreciable y no explica `loop 22` / `swap 28` ms.
5. **Para que OFF cueste 0** habría que borrar también la copia que alimenta al compuesto. Es posible
   (pop del run inmediatamente anterior en la lista de draws), pero la página 0x150 se comparte con
   glare/glow y pan blur: **no aplicarlo sin un contador TEMP que confirme que no hay otro lector**. El
   diff queda bocetado en §7; la recomendación es dejar el gate actual y no perseguir el FPS por acá.

---

## 1. Tabla de estado

| Pieza | Dónde | Estado / qué hace |
|---|---|---|
| Switch "Distance blur" | `port/full/gs/ui.cpp:383-393` (índice 4 → bit 16) | `on = !((v.fxOff >> 4) & 1)`; off escribe `1 << 4` |
| Comentario del bit | `port/full/gs/ui.h:13` | `16 distance blur` |
| Global `gsFxOff` | `port/full/gs/gs_draw.c:70`, set `1240/1263/1276/1311` | máscara `& 31`; `BT3_FX_OFF` o `fx_off` persistido |
| Gate del pase final | `gs_draw.c:605-609` | sprite sobre el frame principal, `ABE` set y `(gGs.alpha[ctx] & 0xFF) == 0x54` + bit 16 → `return 0` (no se encola) |
| Pase del juego | `func_0027FD28` (`asm/cod/17FD28.s:11-525`) | dos pasadas: copia el frame a la página 0x150 y después dibuja 0x150 sobre el frame con `ALPHA_1 = 0x54` |
| Llegada al pase | `func_00280500` → `func_00280480` → tail `func_0027FD28` (`asm/cod/180E30.s:196`, `asm/cod/17FD28.s:564`) | se llama desde el bloque de efectos de escena |
| Buffer de trabajo | `tbp 0x2A00` = página `0x150` (FRAME `0x80150`, FBW 8) | la copia se hace en `func_0027FD28` (0x27FE64/0x27FE94) |
| Compuesto | `TEX0 tbp 0x2A00`, `FRAME_1 = 0x80000/0x80070`, `ALPHA_1 = 0x54`, 16 strips | `asm/cod/17FD28.s:0x280048`, `0x280064..0x280094`, `0x2800E0-0x2800F0` |
| Defaults del efecto | `func_0027F968(0x3E9C)` (`src/auto/m2c_280CD8.c:41`), `func_0027F898` (`asm/cod/17F6E4.s:138-197`) | 2 vistas de 0xBC0 bytes; ancho 12, alto 32, RGBA 0x80/0x80/0x80/0xC0, fuerza 1.0 |
| Copias `native 4/5/6` | `gs_draw.c:513-531` (4), `727-763` (5), `610-627` (6) | la cadena del blur no dispara ninguna |
| `sDateCopy` | `gs_gl.c:990`, `gs_draw.c:727-763` | snapshot DATE; el blur no lo pide (`TEST = 0x30000`, sin bit 14) |
| `sAuxCopy` | `gs_gl.c:990/1024`, `gs_draw.c:517-531` | copia de ids/alfa para outline y dclut `src=1`; el blur no la usa |
| Costo del pase | `gs_gl.c:1030-1041` (draw normal) | 1 compuesto full-screen; la copia ya existía |

Con `fx_off=31` (los cinco apagados) los 5 gates comparten el mismo sitio de descarte:
`gsSkipWhy[4]` ("effect switch", `gs_draw.h:117`). En el frame caro ese sitio vale **17**
(`005253:74197`); el compuesto de Distance blur es **como máximo 1** de esos 17.

---

## 2. Mapa del camino y qué se emite ON vs OFF

Cadena del renderer:

1. `ui.cpp:390-392` → `PortVideo.fxOff` → `GsGpu_SetSettings` → `gs_draw.c:1263` `gsFxOff`.
2. El juego llama a `func_0027FD28` (vía `func_00280500`/`func_00280480`, `asm/cod/180E30.s:196` y
   `asm/cod/17FD28.s:564`).
3. Primera pasada de `func_0027FD28`: `FRAME_1 = 0x80150` (`0x27FE64/0x27FE94`) y `TEX0` con
   `tbp 0xE00` (página 0x70, el frame que se muestra), o sea **copia el frame a la página 0x150**
   (buffer de trabajo de 256x256).
4. Segunda pasada: `TEX0 tbp 0x2A00` (página 0x150, `0x280048`), `FRAME_1 = 0x80000/0x80070`
   (`0x280064..0x280094`) y `ALPHA_1 = 0x54` (`0x2800E0-0x2800F0`), 16 strips con RGBA por strip
   tomado de `+0x61C`. Es el **compuesto que el switch apaga**.
5. En el renderer, ese compuesto es un sprite (`type == 6`) sobre `gGsMainFbp`, con `ABE` (`prim >> 6`)
   y `gGs.alpha[ctx] & 0xFF == 0x54`. El gate de `gs_draw.c:605-609` lo descarta antes de encolarlo.
6. La copia del paso 3 **no** pasa por ese gate: es un draw normal hacia la página 0x150, con
   `target != gGsMainFbp`, y se sigue encolando.

`ALPHA 0x54` = `A=Cs, B=Cd, C=Ad, D=Cd` ⇒ `(Cs - Cd) * Ad / 128 + Cd`: mezcla el buffer copiado
sobre el frame **por el alfa de destino** (el alfa que ya tenía la escena). No hay un pase dclut de
profundidad para este efecto en los logs: de 15 302 líneas `DCLUT` juntadas en `logs/vivo/`, los CBP
vistos son `3e84`, `3e88`, `3e90` y `3e98`; **`3e9c` (el CLUT que inicializa `func_0027F968`) no
aparece nunca**. El alfa que usa el 0x54 es el de la escena, no una tabla de profundidad del blur.

| | Distance blur ON (`fx_off & 16 == 0`) | Distance blur OFF (`fx_off & 16 != 0`) |
|---|---|---|
| Copia frame → 0x150 | 1 draw (16 strips colapsados) | **se sigue emitiendo** |
| Compuesto 0x150 → frame (`0x54`) | 1 draw | **no se encola** (`605-609`) |
| `native 4` (CopyAlphaToDepth) | no | no |
| `native 5` (DATE) | no | no |
| `native 6` (self-copy) | no | no |
| dclut de profundidad propio | no | no |
| Draws del efecto | ~2 | ~1 (sólo la copia) |

---

## 3. Evidencia de costo y de que no son los 615

Frame caro de la 1.ª pelea, build con gate (`005253`):

```
74196: gpu: frame 2640: 3001 draws, 96785 vertices, 9 targets, 2896 textures, 28 pipelines,
       289 primitives of PS2-only passes dropped, 0 native effects
74197: gpu: dropped by site: 144 80 0 48 17 0
74199: GLTIME f=2640 dclut 3/0.0 ms blit 616/0.0 loop 22.8 swap 28.4 total 51.1
75627: gpu: frame 2700: 3043 draws, ... 0 native effects
75630: GLTIME f=2700 dclut 3/0.0 ms blit 615/0.0 loop 22.1 swap 27.3 total 49.4
77044: GLTIME f=2760 dclut 4/0.0 ms blit 14/0.0  loop 25.7 swap 1.8  total 27.5   (el pico pasa)
```

Atribución con los contadores nuevos (`010217`, mismo `fx_off=31`):

```
57354: GLTIME f=1800 dclut 3/0.0 ms blit 614/0.0 blit4 0 blit5 614 blit6 0 loop 80.9 swap 0.0
63545: GLTIME f=2040 dclut 4/0.0 ms blit 613/0.0 blit4 0 blit5 613 blit6 0 loop 81.1 swap 0.1
79900: GLTIME f=2700 dclut 3/0.0 ms blit 613/0.0 blit4 0 blit5 613 blit6 0 loop 80.8 swap 0.0
139577: GLTIME f=5160 dclut 3/0.0 ms blit 615/0.0 blit4 0 blit5 615 blit6 0 loop 82.1 swap 0.0
```

**El pico de ~615 copias es 100 % `native 5` (DATE), no `native 4` ni `native 6`.** El distance blur
no aporta ninguna de esas copias, así que no puede ser el costo del `swap`/`loop` del frame caro. La
coincidencia temporal (impacto con cientos de partículas/HUD que alternan `TEST.DATE`) es la que
explica el pico, no este efecto.

Por qué la cadena no puede producir `native 5/6`:

- `native 5` sale de `date_snapshot()` (`gs_draw.c:727-763`) sólo si `d->misc[1] != 0` (DATE/DATM).
  `func_0027FD28` escribe `TEST_1 = 0x30000` (bits 16-17, `ZTE`/`ZTST`) y **no** el bit 14 de DATE.
- `native 6` sale sólo si `src == d->target` (`gs_draw.c:610`). Acá `src` es la página 0x150 (o el
  frame en la copia) y el target es el otro: nunca coinciden.
- `native 4` sale sólo en el bloque `fbp == zbp && tpsm != 0x1B` de `GfxPost_CopyAlphaToDepth`
  (`gs_draw.c:513-531`); el blur no toca la página de profundidad.
- `sAuxCopy` lo leen el outline nativo y el dclut `src=1` (`gs_gl.c:1024/1050`); el compuesto 0x54 lee
  `targetColor(0x150)`, no `sAuxCopy`.
- `sDateCopy` se enlaza como unidad 1 en todo draw normal (`gs_gl.c:1086`), pero el shader sólo la
  muestrea cuando el draw tiene modo DATE; el blur no.

---

## 4. ¿El gate corta el pase o sólo el draw final?

Sólo el draw final. La condición está dentro de `draw_state`, en la rama `tme` que ya resolvió
`src`/`target`, y hace `return 0` antes de `gsDraws[...] = d` (`gs_draw.c:605-609`). Las pasadas
anteriores de la cadena no llevan `ALPHA 0x54` ni target principal, así que no las ve.

Consecuencia práctica: **apagar Distance blur ahorra 1 draw (el compuesto), no la copia ni el resto de
la cadena**. Visualmente el efecto desaparece (el buffer de trabajo no se vuelca); en tiempo de frame
el ahorro es despreciable.

**¿Comparte el snapshot DATE con glare/glow?** No. El snapshot DATE es global y lo disparan los draws
del juego con `TEST.DATE` (HUD, textos, partículas), no este efecto. El blur tampoco comparte
`sAuxCopy` con el outline/see-through. Lo que sí comparte es la **página de trabajo 0x150**: el glow
la usa en el paso 1 de `GfxPost_DrawGlow` ("clear the 256x256 work page (0x150) and draw the frame into
it", `src/sys/gfxm_a_2799F8.c:229-243`) y el pan blur también copia ahí
(`src/sys/gfxm_a_2799F8.c:219-223`). Por eso **no se puede gatear "todo draw a 0x150"** con el bit 16:
rompería glow/pan blur.

---

## 5. Hipótesis de costo

- ON: 1 copia (frame → 0x150) + 1 compuesto (0x150 → frame, 16 strips).
  Cada uno se graba como 16 primitivas, pero `same_state` (`gs_draw.c:714-720`) las colapsa en **1
  draw** porque target/tex/pipeline/scissor son iguales (los UV/posiciones van en los vértices).
- OFF: el compuesto se descarta; la copia queda. Costo residual ~1 draw.
- 1 draw full-screen a 1024x896 en una RX 580 es del orden de décimas de ms; no explica `loop 22.8`
  ni `swap 28.4`. Los 615 `native 5` sí son GB de copias y explican el pico.

Si se quiere que OFF cueste exactamente 0, hay que borrar la copia. La copia es el run de draws
inmediatamente anterior al compuesto en la lista (mismo target 0x150, source = frame principal), y en
este efecto no hay nada entre medio. Pero la página 0x150 es compartida por glow y pan blur, así que
la condición segura es: borrar el run **sólo si** el contador TEMP demuestra que (a) es un solo draw
colapsado, (b) está inmediatamente antes del compuesto y (c) ningún otro lector de 0x150 aparece entre
la copia y el compuesto. Sin esa medición, no lo aplicaría.

---

## 6. Qué descarté y por qué

- **"El distance blur son los 615 blits"**: descartado por atribución. `010217` da
  `blit4 0 / blit5 613-615 / blit6 0`; el blur no emite ninguna copia.
- **"El gate &16 corta todo el efecto"**: descartado. Sólo corta el compuesto (`605-609`); la copia
  frame→0x150 se sigue emitiendo.
- **"Produce `native 5`/`native 6`"**: descartado por código y por el `TEST` del pase. No hay DATE ni
  self-sampling en `func_0027FD28`.
- **"Comparte el snapshot DATE con glare/glow"**: descartado. El snapshot lo disparan los draws con
  DATE del HUD/partículas; el blur no lo pide.
- **"Su dclut de profundidad (CBP 0x3E9C) está en el frame"**: descartado para estos logs. No aparece
  `DCLUT ... cbp=3e9c` en 15 302 líneas; el 0x54 mezcla por el alfa de escena, no por una tabla de
  profundidad propia.
- **"Gatear la página 0x150 con bit 16"**: descartado como fix directo. 0x150 también la usan el glow
  (`gfxm_a_2799F8.c:229-243`) y el pan blur (`219-223`); hay que medir antes.

---

## 7. Diff boceto (NO aplicado)

### 7.1 TEMP recomendado: contar copia y compuesto (sin riesgo)

En `port/full/gs/gs_draw.c`, junto al gate de `605-609`; y en el camino normal, cuando se encola un
draw hacia la página 0x150 leyendo el frame principal:

```diff
@@ static int draw_state(...)
+    /* TEMP fxblur: cuántos draws propios tiene el distance blur y cuántos corta el switch (BT2_FXBLUR=1) */
+    static unsigned sFxBlurCopy, sFxBlurDrop;
...
             if (sprite && (uint32_t)(gGs.frame[ctx] & 0x1FF) == (uint32_t)gGsMainFbp && ((prim >> 6) & 1) &&
                 ((((gGs.alpha[ctx] & 0xFF) == 0x68) && (gsFxOff & 8)) || (((gGs.alpha[ctx] & 0xFF) == 0x54) && (gsFxOff & 16)))) {
+                if ((gGs.alpha[ctx] & 0xFF) == 0x54 && getenv("BT2_FXBLUR") != NULL) {
+                    sFxBlurDrop++;
+                    fprintf(stderr, "FXDIST f=%u drop=1 src=%d tbp=%04x total=%u\n",
+                            gGsFrame, src, (unsigned)(t0 & 0x3FFF), sFxBlurDrop);
+                }
                 gsSkipped++; gsSkipWhy[4]++;
                 return 0;
             }
```

Y, para ver la copia, en el bloque donde ya se sabe que `d->target` es 0x150 y `d->tex_is_target`
(después de `d->tex = ...`, `gs_draw.c:635`), una línea por draw con `BT2_FXBLUR=1`. Con eso se
confirma en una corrida si el efecto son 2 draws (ON) / 1 (OFF) y si la copia es un run único.

### 7.2 Opcional para "OFF = 0": borrar la copia que alimenta al compuesto

Sólo después de que 7.1 confirme que el run es único, inmediatamente anterior y sin otro lector de
0x150 entre medio:

```diff
             if (sprite && (uint32_t)(gGs.frame[ctx] & 0x1FF) == (uint32_t)gGsMainFbp && ((prim >> 6) & 1) &&
                 ((((gGs.alpha[ctx] & 0xFF) == 0x68) && (gsFxOff & 8)) || (((gGs.alpha[ctx] & 0xFF) == 0x54) && (gsFxOff & 16)))) {
+                /* La copia que alimentaba este compuesto también queda muerta.
+                   Es el run inmediatamente anterior, todo hacia el mismo target `src`; los 16 strips
+                   se colapsan en un draw (same_state). Sólo borrarlo si es un único draw y no hubo
+                   otro draw hacia `src` entre la copia y este compuesto (ver TEMP 7.1). */
+                if ((gGs.alpha[ctx] & 0xFF) == 0x54 && gsDrawCount > 0) {
+                    GsDraw *prev = &gsDraws[gsDrawCount - 1];
+                    if (!prev->native && prev->target == src) {
+                        gsDrawCount--;
+                    }
+                }
                 gsSkipped++; gsSkipWhy[4]++;
                 return 0;
             }
```

**Riesgo**: si el último draw hacia `src` no es la copia del distance blur sino un paso de otro
efecto (glow/pan blur) que después se lee, este pop lo borra. Por eso 7.2 no va sin el contador y sin
una prueba A/B; la copia de 0x150 es compartida. **No aplicarlo tal cual.**

---

## 8. Confirmación propuesta (cuando el usuario/porter pruebe)

1. Con el binario actual y `BT2_GLTIME=1 BT2_FXBLUR=1`, en la 1.ª pelea:
   - `fx_off=31`: esperar `blit4 0 / blit5 613-615 / blit6 0` (ya visto en `010217`) y **1 compuesto
     FXDIST por frame** como máximo, más la copia.
   - `fx_off=15` (sólo Distance blur ON): el `FXDIST drop` baja a 0 y aparecen 2 draws del efecto; el
     `blit5` debe seguir igual (613-615) — si cambia, la atribución está mal.
2. A/B de tiempo: `fx_off=15` vs `fx_off=31` en el mismo frame/pelea. Si `loop`/`swap` no cambian, el
   efecto no es el costo (lo que ya dice la evidencia).
3. Visual: OFF no debe dejar el "soft focus"; ON debe verse como la PS2. Si OFF deja un borde o un
   buffer viejo, el pop de 7.2 no es seguro.
4. Los 615 hay que atacarlos por `native 5` (DATE), no por este switch: el contador del porter ya lo
   separa.

**Sin verificar / límites:** no corrí el juego ni el build; no medí el costo GPU real del compuesto
(haría falta `glFinish` o timer query); no confirmé con un volcado que el compuesto 0x54 de
`func_0027FD28` sea exactamente el que cae en `gsSkipWhy[4]` en ese frame (sólo lo infiero del gate y
del `ALPHA`); no sé si `func_0027FD28` es el único emisor de `ALPHA 0x54` sobre el frame principal en
BT2 (podría haber otro); y no sé si el CLUT 0x3E9C se usa en escenas que no están en estos logs.
