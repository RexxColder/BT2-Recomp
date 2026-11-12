# FX — See-through tint (bit `fx_off & 2`): estado, costo y gate propuesto

Investigación SOLO LECTURA (2026-11-12). No se editó código, no se compiló y no se lanzó el juego.
Proyecto: `BT2-Recomp`. Log analizado: `BT2-test/logs/vivo/20261112-004130.log`.

Contexto medido: `BT2-test/bt2_settings.txt` tiene `fx_off=31` (los 5 switches apagados) y `scale=2`
(1024x896). GPU del log: AMD RX 580, Mesa 26.2.6.

Aviso de vigencia: el log es de las 00:41–00:46; el gate de `native 4`
(`backups/gs_draw.c.pre_fxgate`, 00:51) y el binario `backups/bt2.pre_fxgate` (00:52) son POSTERIORES.
**El log NO mide el gate actual**: mide el código previo, donde la copia de alfa se emitía siempre.

---

## 1. Tabla de estado

| Pieza | Dónde | Estado con `fx_off=31` | Evidencia |
|---|---|---|---|
| Switch "See-through tint" | `port/full/gs/ui.cpp:385,392` | bit 1 (`2`) apagado | `fx[1]`; `on = !((v.fxOff>>i)&1)` |
| `gsFxOff` | `gs_draw.c:70`, set `1257`/`1305` | `31` (máscara `&31`) | settings + `Port_Setting("fx_off",0)` |
| Pase dclut de see-through | `gs_draw.c:428-468` | **cortado** por `cbp==0x3E94 && (gsFxOff&2)` (línea 449) | el pase no debería ni encolarse |
| Byte de profundidad/alfa | `gs_draw.c:438`, `505` | `gsDepthByteIsFog=0` ⇒ `d.src=1` | lo fija `CopyAlphaToDepth` (tpsm != 0x1B) |
| Copia de alfa `native 4` | `gs_draw.c:506-519` | **no se emite** con outline y see-through apagados | gate `!((gsFxOff&1)&&(gsFxOff&2))`, línea 515-516 |
| Blit GL de la copia | `gs_gl.c:989-1017` (`dst=sAuxCopy` línea 990) | si hubiera `native 4`, se blitearía | `glBlitFramebuffer` 1006 |
| Consumo de la copia por dclut | `gs_gl.c:1024`, `dclut.frag:27-29` | `src=1` muestrea `sAuxCopy` | `set_textures(sTgDep..., sAuxCopy..., tex)` |
| dclut restantes | — | **3 por frame** (no son el see-through) | ver §3 |
| `native 5` (DATE snapshot) | `gs_draw.c:712-724`, llamadas 760/950/1004/1044 | independiente de los switches FX | copia alfa para TEST.DATE (HUD/partículas) |
| Timer GLP TIME | `gs_gl.c:898-901, 1004-1011, 1032-1039, 1195-1196, 1275-1279` | mide CPU de encolado, no GPU | ver §4 |

---

## 2. Mapa del camino y qué se emite ON vs OFF

Cadena:

1. `ui.cpp:392` → `PortVideo.fxOff` → `GsGpu_SetSettings` → `gs_draw.c:1257` `gsFxOff`.
2. El juego arma 16 strips de "dibujar el byte alto de la página de profundidad por una tabla"
   (`GfxPost_DrawDepthClut`, `src/sys/gfxm_b_281758.c:60`). El renderer los detecta en
   `draw_state` (`gs_draw.c:538-542`: `tme && sprite && tpsm==0x1B && tbp/32==zbp`) y llama
   `depth_clut()`.
3. `depth_clut` (`gs_draw.c:428`):
   - `d.native=3`, `d.src = gsDepthByteIsFog ? 0 : 1` (438),
   - gate de tinte por profundidad: `(gsFxOff&4) && src==0 && wm!=0x00FFFFFF` (441),
   - gate outline: `cbp==0x3E8C` → return (446-448),
   - gate see-through: `cbp==0x3E94 && (gsFxOff&2)` → return (449-451),
   - dedupe de los 16 strips (464-466) y push de **un** `GsDraw native 3`.
4. Backend GL (`gs_gl.c:1019-1043`, programa `sDclutProg` creado en 789): bind sin depth,
   `set_textures(sTgDep[target], sAuxCopy, tabla)`, `glDrawArrays(GL_TRIANGLES,0,3)`.
5. `dclut.frag:24-29`: `src=0` deriva el índice de la profundidad; `src=1` lo lee de
   `auxTex` (la copia de alfa). Tabla 256x1 (`clutTex`).

El byte de la página de profundidad lo llenan dos pasadas del juego, distinguidas en
`gs_draw.c:502-520`:
- `GfxDepthFog_Draw` (tpsm `0x1B`) → `gsDepthByteIsFog=1` → dclut con `src=0`;
- `GfxPost_CopyAlphaToDepth` (tpsm != `0x1B`) → `gsDepthByteIsFog=0` → se emite `native 4`
  (copia `sTgAux[target]` → `sAuxCopy`) y los dclut posteriores usan `src=1`.

| | See-through ON (`fx_off & 2 == 0`) | See-through OFF (`fx_off & 2 != 0`) |
|---|---|---|
| dclut `cbp 0x3E94` | 1 pase full-screen `native 3`, `src=1` (en pelea, porque el byte es alfa) | **no se encola** (return en 449) |
| Copia `native 4` | se emite (la necesita el tint y el outline) | se emite **sólo si el outline sigue prendido** (bit 0); con bit0 y bit1 apagados se saltea (515) |
| Lectura de `sAuxCopy` | `gs_gl.c:1024` | nadie la lee por el tint; sí el outline nativo (`gs_gl.c:1050`) |
| Costo esperado | 1 dclut + hasta 1 copia por `CopyAlphaToDepth` | 0 dclut del tint; copia sólo si outline ON |

**Respuesta corta:** con See-through ON se emite **un pase dclut `src=1` por frame** que indexa la
tabla `0x3E94` con los ids de alfa copiados; con OFF ese pase no existe (la línea 449 lo corta
antes de `clut_texture`/push). La copia `native 4` **no** es exclusiva del tint: la comparten el
outline nativo y los dclut de alfa; por eso apagar sólo See-through no alcanza para sacarla.

---

## 3. ¿Por qué quedan 3 dclut por frame con todo apagado?

Con `fx_off=31`, TODO pase que llegue a `depth_clut` con `cbp==0x3E94` retorna en 449 y todo
`cbp==0x3E8C` en 446. Por lo tanto **los 3 dclut que cuenta GLP TIME no son el see-through**
(tampoco el outline). Quedan sólo dos familias:

1. `src==0` con `wm == 0x00FFFFFF` (máscara que escribe **sólo alfa**): la condición 441 los
   **deja pasar a propósito** ("las que sólo escriben alfa alimentan el glow").
2. `src==1` con cualquier `wm`: la condición 441 ni los mira (sólo aplica a `src==0`).

Ambas familias son *productores* que alimentan el glare/glow; el switch de glow (bit 3, valor 8)
se aplica recién al **pase final** que compone el brillo sobre la pantalla
(`gs_draw.c:588-595`, alfas `0x68`/`0x54`), no al dclut que prepara su alfa. Con glow apagado
esos 3 pases son trabajo tirado (y con la copia `native 4` salteada, si fueran `src=1` leen un
`sAuxCopy` viejo).

No se pudo determinar por código cuál de las dos familias son los 3 (el CBP de cada pasada la fija
el código de escena, en runtime). El contador TEMP de §5 lo resuelve en una corrida. Lo que sí es
demostrable: **no son `0x3E94`**; el gate del see-through funciona.

Nota importante: GLP TIME imprime cada 60 frames, pero `nDclut`/`nBlit` se reinician en cada
`frame_end` (gs_gl.c:899-901). "dclut 3/60" significa **3 dclut en ese frame**, no 3 en 60.

---

## 4. Costo: el timer miente (o mide otra cosa)

Evidencia del log:

```
61272:GLTIME f=1800 dclut 3/0.0 ms blit 14/0.0  loop 15.4 swap 0.9  total 16.3
66053:GLTIME f=2040 dclut 3/0.0 ms blit 615/0.0 loop 17.6 swap 49.9 total 67.6
67536:GLTIME f=2100 dclut 3/0.0 ms blit 18/0.0  loop 15.7 swap 1.4  total 17.2
72053:GLTIME f=2280 dclut 3/0.0 ms blit 613/0.0 loop 35.8 swap 19.8 total 55.6
```

y en f=2041: `slow: 79.1 ms = game 3.1 ms + display list 76.7 ms`, `submitting the frame 67.6 ms`.

- `blit 615/0.0 ms` es imposible como trabajo real: 615 `glBlitFramebuffer` de 1024x896 R8
  (~0.9 MB c/u, ~0.55 GB en el frame) no cuestan 0.0 ms. El driver **encola** y el costo aparece
  al final, en `SDL_GL_SwapWindow` (`tSwap`, gs_gl.c:1195). Aun con `SDL_GL_SetSwapInterval(0)`
  (777), el swap espera/resuelve el trabajo pendiente y los cambios de FBO.
- Lo mismo vale para dclut: el timer (`SDL_GetTicksNS` alrededor de `glDrawArrays`, 1032-1039)
  mide **envío de comando**, no ejecución GPU. `dclut 0.0 ms` no dice que sea gratis.
- 3 dclut full-screen en una RX 580 a 1024x896 son baratos (del orden de <1 ms en total); el
  see-through no explica `swap 49.9`. El pico de swap coincide con el pico de **615 blits**
  (no con los 3 dclut, que están en todos los frames).
- Los 615 blits son casi seguro `native 5` (DATE snapshot, `gs_draw.c:712-724`), no `native 4`:
  `native 4` se emite una vez por `CopyAlphaToDepth` (unas pocas por frame, y deduplicado si es
  consecutivo), mientras que `native 5` se emite **una vez por corrida** de draws con TEST.DATE;
  un frame de impacto con cientos de partículas/HUD que alternan DATE genera cientos de copias.
  Esto es una hipótesis fuerte pero **no medida**: hace falta separar el contador por tipo.

Conclusión para el FPS: apagar See-through (o gatear `native 4`) **no va a mover el pico de
swap 49.9** de ese log; el pico son las copias DATE (`native 5`), ajenas a los switches FX.
Y ojo: **no hay que gatear `native 5` con bits de FX** — rompería las barras de HUD y los textos
recortados por máscara (comentario en `gs_draw.c:706-711`).

---

## 5. Contador TEMP mínimo propuesto (NO aplicado)

Tres agregados baratos, todos detrás de env:

1. Separar blits por tipo (en `gs_gl.c`, junto a `nBlit`):
```c
/* TEMP fxsee */
unsigned nCopy[7] = {0};
...
nBlit++; nCopy[d->native]++;      /* en el bloque 989-1017 */
...
fprintf(stderr, "GLTIME f=%u dclut %u/%.1f ms blit %u/%.1f (4:%u 5:%u 6:%u) loop %.1f swap %.1f total %.1f\n",
        gGsFrame, nDclut, (double)dclutNs / 1e6, nBlit, (double)blitNs / 1e6,
        nCopy[4], nCopy[5], nCopy[6],
        (double)(tLoop - tFrame) / 1e6, (double)(tSwap - tLoop) / 1e6, (double)(tEnd - tFrame) / 1e6);
```
2. Identificar los 3 dclut (en `gs_draw.c`, justo antes de `gsDraws[gsDrawCount++] = d;`, línea 467,
   o sea después del dedupe: 1 línea por pase, no por strip):
```c
/* TEMP fxsee */
if (getenv("BT2_FXSEE") != NULL) {
    fprintf(stderr, "DCLUT f=%u src=%d cbp=%04x wm=%08x tgt=%d\n", gGsFrame, d.src,
            (unsigned)((gGs.tex0[ctx] >> 37) & 0x3FFF), (unsigned)(gGs.frame[ctx] >> 32), d.target);
}
```
3. Atribuir GPU vs CPU (en `gs_gl.c`, antes de `tLoop = SDL_GetTicksNS();`, línea 1192):
```c
/* TEMP fxsee */
if (getenv("BT2_GLTIME_FINISH") != NULL) {
    uint64_t tf = SDL_GetTicksNS();
    glFinish();
    fprintf(stderr, "FINISH f=%u %.1f ms\n", gGsFrame, (double)(SDL_GetTicksNS() - tf) / 1e6);
}
```
Con (3) el trabajo GPU sale de `swap` y aparece en `loop`; si además se pone otro `glFinish` sólo
alrededor del `glDrawArrays` de dclut bajo un env más fuerte, se obtiene el costo real del pase.

Corrida: pelea 1, `BT2_GLTIME=1 BT2_FXSEE=1`, primero `fx_off=31` y después con See-through ON.
Se espera ver `DCLUT ... cbp=3e94` sólo en el segundo caso y `4:` en 0 con todo apagado.

---

## 6. Fix propuesto (boceto, sin aplicar)

Dos correcciones independientes. La primera es la que pide el ticket; la segunda evita un bug de
correctitud del gate recién agregado.

### 6.1 Gate real de los consumidores y de la copia

`port/full/gs/gs_draw.c` — `depth_clut`, después de la línea 451:

```diff
         if (cbp == 0x3E94 && (gsFxOff & 2)) {
             return; /* the see-through tint, switched off */
         }
+        /* The only other table passes that survive with the tint/outline off are alpha feeds for the
+           glow (src==1 reads the alpha copy; src==0 with wm 0x00FFFFFF writes alpha only). With the
+           glow off they have no reader: drop them instead of running a full-screen pass per frame.
+           (Confirm the exact set with BT2_FXSEE before applying.) */
+        if (wm == 0x00FFFFFFu && (gsFxOff & 8)) {
+            return; /* alpha-only table pass: feeds the glow */
+        }
+        if (d.src == 1 && (gsFxOff & 2) && (gsFxOff & 8)) {
+            return; /* the alpha ids through a table: see-through tint (off) and glow (off) */
+        }
```

`port/full/gs/gs_draw.c:515-516` — la copia debe sobrevivir si **cualquier** lector vive:

```diff
-                if (c.target >= 0 && gsDrawCount < MAX_DRAWS && !(last != NULL && last->native == 4) &&
-                    !((gsFxOff & 1) && (gsFxOff & 2))) {
+                if (c.target >= 0 && gsDrawCount < MAX_DRAWS && !(last != NULL && last->native == 4) &&
+                    !((gsFxOff & 1) && (gsFxOff & 2) && (gsFxOff & 8))) {
                     gsDraws[gsDrawCount++] = c;
                 }
```

Por qué: los lectores de `sAuxCopy` son (a) el outline nativo (`gs_gl.c:1050`, bit 0),
(b) el dclut `0x3E94` `src=1` (bit 1) y (c) los dclut de alfa del glow (bit 3). El gate actual
sólo mira (a) y (b): con `fx_off=3` (outline y tint apagados, **glow prendido**) saltea la copia y
el glow lee alfa vieja. Eso es un bug de correctitud, no una optimización.

Costo esperado del cambio: con `fx_off=31`, 3 dclut → 0 y 0 copias `native 4`; con los efectos
prendidos, 1 dclut + 1 copia (costo aceptable y acotado). No toca `native 5`.

### 6.2 (Opcional, segunda etapa) Reutilizar el snapshot

Hoy `native 4` se deduplica sólo si es **consecutivo** (`gs_draw.c:515`). Si entre dos
`CopyAlphaToDepth` no hubo ningún draw que escriba alfa, la segunda copia es redundante. Se puede
llevar en `GsTarget` una generación de alfa (`auxgen`, incrementada en cada primitiva que escribe
alfa según FBMSK) y guardar en el `native 4` la generación copiada; si coincide, no emitir. Es un
cambio más invasivo; no hace falta para cerrar este ticket y conviene medirlo antes con §5.

---

## 7. Qué se descartó y por qué

- **"Los 3 dclut son el see-through"**: descartado. Con `gsFxOff&2` la línea 449 retorna antes del
  push para todo `cbp==0x3E94`; los 3 tienen otro CBP (o no son `src=1`).
- **"La copia `native 4` es sólo del see-through"**: descartado. El outline nativo la lee
  (`gs_gl.c:1050`) y los dclut de alfa del glow también; apagar sólo el tint no la elimina.
- **"El pico de 615 blits es la copia del see-through"**: descartado por conteo. `native 4` es una
  por llamada a `CopyAlphaToDepth` (pocas por frame); 615 copias de 0.9 MB se explican por
  `native 5` (DATE), que se emite por corrida de draws DATE. Falta confirmarlo con §5.1.
- **"dclut 0.0 ms ⇒ el pase es gratis"**: descartado. El timer mide encolado; el costo real está
  en `swap` (49.9 ms con 615 blits), no atribuible a dclut sin `glFinish`/timer query.
- **Gatear `native 5` con bits FX**: descartado de entrada. DATE no es un efecto de los switches;
  gatearlo rompe HUD/textos (comentario en `gs_draw.c:706-711`).
- **"El log actual refleja el gate"**: descartado por fechas (log 00:41–00:46; gate 00:51,
  binario 00:52). Cualquier conclusión de FPS del log es del código previo.

## 8. Confirmación propuesta (cuando el porter aplique)

1. Compilar e instalar el binario; en pelea 1 con `fx_off=31` y
   `BT2_GLTIME=1 BT2_FXSEE=1`: esperar `dclut 0` y `(4:0 ...)`.
2. Repetir con See-through ON: esperar `dclut +1`, con `DCLUT ... cbp=3e94 src=1`, y `4:` > 0.
3. Caso de regresión del gate actual: Outline OFF + See-through OFF + **Glow ON**
   (`fx_off = 1|2 = 3`). El brillo debe verse igual que antes del gate; con el código actual
   probablemente lea `sAuxCopy` vieja.
4. Mirar el FPS con los 3 casos. Si con `fx_off=31` sigue el pico de `swap`, el culpable no es el
   see-through: pasar a `native 5` con los contadores de §5.1.

Sin verificar: identidad exacta de los 3 dclut, reparto real `native 4` vs `native 5` en el pico de
615 blits, y costo GPU del pase dclut (todo requiere la instrumentación de §5 y una corrida).
