# FX — Outline (`fx_off & 1`): qué dibuja, qué se emite ON/OFF, costo y arreglo propuesto

Investigación **SOLO LECTURA** (2026-11-12, snapshot 01:05). No se editó código del port, no se compiló y no se
lanzó el juego. Proyecto: `BT2-Recomp`. Log analizado: `BT2-test/logs/vivo/20261112-004130.log` (00:41–00:46),
`fx_off=31`, `scale=2` (1024x896 visibles), AMD RX 580 / Mesa 26.2.6.

> **Aviso de vigencia.** El árbol está siendo editado por otro agente mientras se escribe esto:
> `gs_draw.c` cambió a las 00:51 (gate de `native 4`, backup `backups/gs_draw.c.pre_fxgate`) y otra vez a las
> 00:59 (el gate pasó a bits `1+2+8`); `gs_gl.c` cambió a las 00:59 (contadores `blit4/5/6` y
> `BT2_GLTIME_FINISH`). El log es **anterior a todo eso**: mide el código donde la copia de alfa se emitía
> siempre. Los números de línea son los del snapshot; pueden haberse movido unos renglones.

---

## 0. Resumen

1. **El outline nativo (`native 1`) hoy no se dibuja nunca.** Nadie escribe el registro marcador `0x7F`
   (`gs_core.c:856` es el único camino a `GsGpu_Native`; no hay `Port_GsMarker` en el binario ni en el árbol;
   `docs/bugs_open.md:312` ya lo decía). Consecuencia: **el checkbox Outline no cambia la imagen**; lo único que
   hace hoy es habilitar/deshabilitar la copia de alfa. Si el juego muestra un contorno negro en los luchadores,
   no viene de este camino.
2. **La copia de alfa (`native 4`) no es el pase caro del log.** El juego llama `GfxPost_CopyAlphaToDepth` una
   vez por vista (`asm 0x1660C4`/`0x1661C0` → `port/eq/280E90.c` → `src/sys/gfxm_b_281758.c:63`), y los 16 strips
   se deduplican a **1 `native 4` por llamada** (2 en split screen, 1 en pantalla completa).
3. **`blit 615` del log son 615 copias en UN cuadro, no en 60.** `nBlit` es una variable local de `frame_end`
   (`gs_gl.c:900`), se incrementa por copia (`:1008`) y se imprime antes de reiniciar. 615 copias × 8,4 MB de
   tráfico ≈ 5,2 GB → los `swap 49.9 ms` del cuadro 2040. Por el tamaño y el conteo, **no pueden ser `native 4`**:
   el candidato es `native 5` (snapshot de alfa para `TEST.DATE`), con `native 6` (self-copy, RGBA8, 4× más caro)
   como segunda opción. El contador `blit4/blit5/blit6` que ya está en el árbol lo confirma en una corrida.
4. **El gate actual está bien planteado** (`gs_draw.c:521-522`: saltea la copia sólo si los tres lectores están
   apagados: bit 1 outline, bit 2 see-through, bit 8 glare/glow). Con `fx_off=31` la copia cuesta **0**, pero
   eso no toca los 49,9 ms porque la copia del outline eran 1-2 por cuadro, no 615.
5. **Costo con el outline prendido:** 1 copia R8 de 4,19 MB (8,4 MB de tráfico) + 1 triángulo full-screen ≈
   **0,2–0,3 ms**; aceptable. Hay un desperdicio de **4,57×** en *todas* las copias: se blitea la textura completa
   (2048×2048 a escala 2) cuando la imagen útil es 1024×896 (`GS_W/GS_H=1024`, visible 512×448; `uvScale` en
   `gs_gl.c:330`). Limitarla a 512×448×SCALE baja el pico de 615 copias de ~5 GB a ~1,1 GB.

---

## 1. Mapa del camino (archivo:línea, snapshot 01:05)

| Pieza | Dónde | Qué hace |
|---|---|---|
| Toggle | `port/full/gs/ui.cpp:382-392` | tabla `fx[0] = "Outline"`; bit 0 de `v.fxOff`; `on = !((v.fxOff>>i)&1)` |
| Aplicación | `ui.cpp:599,619` → `gs_draw.c:1250-1276` | `GsGpu_SetSettings`: `gsFxOff = v->fxOff & 31` (1257); guarda `fx_off` (1276) |
| Carga | `gs_draw.c:70`, `:1311` | `gsFxOff` global; `BT3_FX_OFF` o `Port_Setting("fx_off",0)` |
| Marcador nativo | `gs_core.c:856` (`case 0x7F`) → `GsGpu_Native` (`gs_draw.c:1107-1129`) | registro que **no existe** en el GS: es un marcador del port. **Nadie lo escribe.** |
| Gate del dibujo | `gs_draw.c:1117` | `if (effect != 1 || ... || (gsFxOff & 1)) return;` — `gsNative++` recién en 1120 (por eso `0 native effects` con el outline apagado no prueba nada) |
| Copia de alfa | `gs_draw.c:511-522` (`native 4`) | en un draw a la página de profundidad, `tpsm != 0x1B` ⇒ es `GfxPost_CopyAlphaToDepth`; target = `GsDraw_TargetGet(tbp/32,0)` (la vista actual: página 0 o 0x70) |
| Gate de la copia | `gs_draw.c:521-522` | `!((gsFxOff & 1) && (gsFxOff & 2) && (gsFxOff & 8))` (backup `pre_fxgate:511`: sin gate) |
| Replay GL | `gs_gl.c:989-1017` | `native 4/5/6` = `glBlitFramebuffer` **de la textura entera** (1006); `nBlit++` (1008); contadores `n4/n5/n6` (1010) |
| Pase nativo GL | `gs_gl.c:1045-1059`, `set_native` 680-702, programa 787 | un `glDrawArrays` full-screen con `sOutlineProg`, `sAuxCopy` como textura (1050-1051), blend `destination − source` |
| Replay Vulkan | `gs_gpu.c:723-742` (`native 4`), `:781-810` (efecto), `:799-800` | copia `SDL_CopyGPUTextureToTexture` de `GS_W*SCALE × GS_H*SCALE`; pipeline `sOutlinePipe`, `sAuxCopy` |
| Shader | `port/full/gs/shaders/outline.frag` → `kOutlineFragGlsl` (`build/full/gen/shaders.h:13`) | tabla `id<<3` (0 ⇒ 0x80, 255 ⇒ nada), compara con ±1 px en las 4 direcciones, devuelve `0x64/255` a **restar** |
| Lado juego: copia | `src/sys/gfxm_b_281758.c:63-133` | `GfxPost_CopyAlphaToDepth`: 16 strips de 32×448, `FRAME=GFX_ZBP`, `TEX0` = la vista actual (0x0/0x70), `ALPHA=0x44` |
| Lado juego: llamador | `port/eq/280E90.c:10-19`, asm `180EA8-180EC4` | pone `Dma_AddScissor(0,0x1FF,0,0x1BF)` y llama la copia; llamada desde el draw por vista `asm 0x1660C4`/`0x1661C0` |
| Lado juego: outline | `ObjOutline_Draw` **sigue en asm/relleno** (no hay C en `src/`, no hay reemplazo en `port/eq`) | sus pasadas PS2 (tabla `CBP 0x3E8C`, vistas de 16 bits) se descartan (`gs_draw.c:446-448`, `:526-536`) |

### Qué dibuja el efecto (según `outline.frag` y `include/sys/gfxm_a.h:13-15`)

La PS2 deja un **id por objeto en el alfa del frame** (lo escriben los modelos). El outline:
1. copia ese alfa al byte alto de la página de profundidad (`GfxPost_CopyAlphaToDepth` → `native 4`);
2. arma una **imagen de bordes** leyendo ese byte por una tabla, restándola consigo misma corrida 1 px
   (pasadas `depth_clut` `CBP 0x3E8C` y vistas de 16 bits — hoy descartadas);
3. mezcla un **rectángulo oscuro 0x64** por ese resultado.

El port reemplaza 2+3 por **un solo pase nativo** (`outline.frag`: 5 taps sobre `sAuxCopy`, blend
`destination − source`, máscara sólo RGB). Por eso el único consumidor del `native 4` en este camino es el
pase `native 1`.

### Por qué el pase nativo no corre

- `GsGpu_Native` sólo se invoca desde `Gs_RegWrite`/`reg_write` con `addr == 0x7F` (`gs_core.c:856`).
- Ese "registro" no es del GS; el juego no lo escribe. No hay ningún `GsGpu_Native(...)` ni `Gs_RegWrite(0x7F,...)`
  en `port/`, `src/` ni `include/`; `nm port/build/full/bt2full` no tiene un emisor (sí tiene el receptor
  `40a4f310 GsGpu_Native`, alcanzado sólo por el `jmp` del switch en `40a46e15`).
- `docs/bugs_open.md:312` (B5, 2026-10-30): "ningún código BT2 llama Port_GsMarker → outline nativo / alpha key
  nunca corren".

**Conclusión:** con el árbol actual, `fx_off & 1` no tiene nada que cortar del lado del dibujo. La línea 1117
es un gate defensivo para el día que se emita el marcador.

---

## 2. Estado: qué cambia con Outline ON vs OFF

| | Outline ON (`bit0=0`) | Outline OFF (`bit0=1`) |
|---|---|---|
| `GsGpu_Native(1)` | se encolaría (gate 1117 lo deja pasar) | se corta en 1117 |
| Lectores reales del marcador | **ninguno** (nadie llama) | ninguno |
| `native 1` en el replay | **0** | **0** |
| `native 4` (copia) | se emite si hay `CopyAlphaToDepth` (1 por vista) | se emite si bit 2 **o** bit 8 siguen prendidos |
| `native 4` con `fx_off=31` | — | **0** (los tres bits apagados) |
| Imagen | igual | igual |
| Costo GPU del outline | ~0,2–0,3 ms (1 copia + 1 pase) | 0 |

Es decir: **apagar Outline no ahorra nada medible hoy** (1-2 copias de 8,4 MB ≈ 0,1 ms), y **prenderlo no
dibuja el contorno**. La creencia "el `fx_off & 1` corta el dibujo pero no la copia" describe el código
**anterior al gate** (backup `pre_fxgate:511`, sin condición): en esa versión la copia se emitía siempre, con
todos los efectos apagados. Hoy la copia sí está gateada, pero por los **tres** lectores, no sólo el outline.

### ¿Por qué no alcanza con `gsFxOff & 1` para la copia?

Porque `sAuxCopy` (el destino del `native 4`) tiene tres lectores (comentario en `gs_draw.c:516-520`):
1. el pase nativo del outline (`gs_gl.c:1050`, `native 1`);
2. el tinte see-through (`native 3` con `src==1`, tabla `CBP 0x3E94`; `gs_draw.c:449` lo corta con bit 2);
3. los pases de tabla que arman el alfa del glare/glow (`native 3` `src==1`); el bit 8 apaga el *add-back*, no
   la tabla, así que mientras el bit 8 esté prendido la copia debe existir (aunque su salida se descarte).

Con `fx_off=31` los tres están apagados ⇒ copia 0. El gate con `&&` es conservador y correcto.

---

## 3. Evidencia del log (`20261112-004130.log`)

Configuración: `BT2-test/bt2_settings.txt` → `scale=2`, **`fx_off=31`**, `glow=60`. Log líneas 6-7:
`internal resolution 2x (1024 x 896)`, `AMD Radeon RX 580`.

| línea | contenido | lectura |
|---|---|---|
| 61272 | `GLTIME f=1800 ... blit 14/0.0 loop 15.4 swap 0.9 total 16.3` | cuadro normal: 14 copias, swap 0,9 ms |
| 64831 | `GLTIME f=1980 ... blit 15/0.0 loop 9.1 swap 0.7 total 9.8` | idem |
| 66051 | `gpu: frame 2040: 2049 draws ... 289 ... 0 native effects` | 0 efectos nativos (con el gate de 1117, esto es esperable con bit0=1) |
| 66052 | `gpu: dropped by site: 144 80 0 48 17 0` | 144 vistas 16-bit, 80 tabla, 48 stale, 17 add-back apagado por bits 8/16 |
| **66053** | **`GLTIME f=2040 ... blit 615/0.0 loop 17.6 swap 49.9 total 67.6`** | **615 copias en ese cuadro** |
| 66054-66056 | `slow: frame 2041: 79.1 ms ... display list 76.7 ... submitting the frame 67.6` | el costo está en la sumisión/GPU, no en el juego |
| 72053 | `GLTIME f=2280 ... blit 613/0.0 loop 35.8 swap 19.8 total 55.6` | segundo pico, 4 s después |
| 72051 | `gpu: frame 2280: 3067 draws ... 2271 textures` | cuadro cargado; el conteo de blits no escala con los draws |

Los 615/613 son **por cuadro** (`nBlit` local, `gs_gl.c:900`, impresión en 1278-1281). El cronómetro del blit
marca 0,0 ms porque `glBlitFramebuffer` sólo encola; el costo aparece en `swap` (medido después del present).

---

## 4. Costo

### 4.1 Cuánto copia cada `native 4/5/6`

- Texturas de render: `GS_W*SCALE × GS_H*SCALE` con `GS_W=GS_H=1024` (`gs_draw.h:16-17`, `gs_gl.c:490-496,567-572`).
  A `scale=2` ⇒ **2048×2048**.
- `native 4` y `native 5`: R8 ⇒ **4,19 MB** por copia (8,4 MB de tráfico leer+escribir).
- `native 6`: RGBA8 ⇒ **16,8 MB** (33,6 MB de tráfico).
- La imagen que usa el juego es **512×448 GS px** (a 2× = 1024×896 = 0,92 MB en R8). `gs_gl.c:330` lo confirma:
  `uvScale = 512/GS_W, 448/GS_H`. **Toda copia desperdicia 4,57×.**

### 4.2 Reparto medido

- Cuadro normal (f=1800/1980): 14-15 copias, `swap 0,7-0,9 ms`. Si todas fueran R8 de 4,19 MB, 14 × 8,4 MB =
  118 MB ⇒ ~0,6-1,2 ms a 100-200 GB/s. Consistente; **cada copia R8 cuesta ~0,05-0,07 ms**.
- Pico f=2040: 615 copias × 8,4 MB = **5,2 GB** ⇒ 26-52 ms según el ancho de banda efectivo. `swap 49.9 ms`
  encaja con ~105 GB/s. Si fueran `native 6` (RGBA8), serían ~21 GB ⇒ >100 ms: **no encaja**.
- El pase nativo del outline (si se emitiera) es 1 triángulo con 5 taps sobre 1024×896 px ⇒ ~0,1-0,2 ms.
  Con la copia, **~0,2-0,3 ms por cuadro** (0,4-0,6 ms en split screen).

### 4.3 Por qué el pico no es el outline

- `native 4` sale de `GfxPost_CopyAlphaToDepth`, llamada **una vez por vista** (`asm 0x1660C4` y `0x1661C0`).
  Los 16 strips de la función son consecutivos y el dedupe `last->native == 4` (`gs_draw.c:521`) los colapsa a 1.
- Para llegar a 615 haría falta que el juego llamara la copia 615 veces en un cuadro; no hay call sites para eso
  (`grep` de `func_0027F6D0`/`0x281758` en asm: sólo `180EC0`, dentro de `func_00280E90`).
- `native 5` (DATE) sí puede dispararse por draw: `date_snapshot` (`gs_draw.c:718-731`, llamadas en 766/956/1010/1050) agrega una copia al inicio de
  cada run de draws con `TEST.DATE`; si un efecto alterna draws con/sin DATE, hay una copia por draw. 615 runs en
  un cuadro de efecto es plausible (el cuadro 2280 tiene 3067 draws y 2271 texturas).

**Hipótesis principal:** el pico es `native 5` (R8, mismo tamaño que 4). **Segunda:** `native 6`.
Se descarta `native 4` por conteo de call sites + dedupe.

---

## 5. Diferencias con los otros informes

- `staging/FX_see_through.md` §4 estima ~0,9 MB por copia (1024×896). El código blitea **2048×2048** (textura
  completa): 4,19 MB. La conclusión (el pico no es el outline) no cambia; el número de bytes sí, y hace que el
  pico sea aún más explicable.
- `staging/FX_glare_glow.md` ya asigna el pico a `native 5`; este informe lo respalda con el conteo de call sites
  y el costo por copia, y agrega el desperdicio 4,57× y el gate de tres lectores.

---

## 6. Arreglo propuesto (NO aplicado)

### 6.1 Lo que ya está en el árbol (para no duplicar)

- Gate de la copia por lectores: `gs_draw.c:521-522` (bits 1+2+8). **Correcto; dejarlo.**
- Contadores `blit4/blit5/blit6` + `BT2_GLTIME_FINISH` (`gs_gl.c:900,1010,1195-1196,1279`). **Es exactamente el
  log mínimo que hacía falta** para atribuir el pico; no hay que agregar nada.

### 6.2 Arreglo de raíz del outline apagado (costo 0 garantizado)

Problema: el gate del registro usa los switches del usuario, pero el lector real es el *pase* que el juego
emite. Un frame de menú/cutscene sin outline paga la copia si el bit 2 u 8 están prendidos. Solución segura:
**eliminar la copia muerta en el replay**, donde la lista completa ya está grabada.

`port/full/gs/gs_draw.c` (helper nuevo, junto a `GsGpu_Native`):

```c
/* 1 si algún pase posterior lee sAuxCopy antes de que otra copia la pise. Lectores:
   el outline nativo (1), el alpha key (2) y los pases de tabla que indexan los ids (3, src 1). */
int GsGpu_AuxCopyNeeded(uint32_t n) {
    uint32_t k;
    for (k = n + 1; k < gsDrawCount; k++) {
        const GsDraw *r = &gsDraws[k];
        if (r->native == 4) { return 0; }                    /* otra copia la reemplaza */
        if (r->native == 1 || r->native == 2) { return 1; }
        if (r->native == 3 && r->src == 1) { return 1; }
    }
    return 0;
}
```

`port/full/gs/gs_gl.c:989` (y el equivalente `gs_gpu.c:723`), antes de elegir `dst`:

```diff
         if (d->native == 5 || d->native == 4 || d->native == 6) {
+            if (d->native == 4 && !GsGpu_AuxCopyNeeded(n)) { continue; } /* nadie lee los ids: copia muerta */
             GLuint dst = ...
```

Con esto, con `fx_off=31` **o** con cualquier combinación en la que el juego no emita ningún lector, la copia
cuesta 0 aunque el gate del registro se equivoque. Riesgo: bajo (sólo saltea trabajo cuyo resultado nadie lee);
el escaneo es acotado por la próxima copia.

### 6.3 Optimización válida con el outline prendido (y para todos los efectos)

Copiar sólo la imagen útil (4,57× menos tráfico). En `gs_gl.c:1006` (y `gs_gpu.c:699/719/739`):

```diff
-                glBlitFramebuffer(0, 0, GS_W * SCALE, GS_H * SCALE, 0, 0, GS_W * SCALE, GS_H * SCALE,
-                                  GL_COLOR_BUFFER_BIT, GL_NEAREST);
+                /* la imagen que usan los efectos es 512x448 GS px; el resto de la textura es direccionamiento
+                   de VRAM que nadie muestrea (el present usa uvScale 512/GS_W, 448/GS_H) */
+                glBlitFramebuffer(0, 0, 512 * SCALE, 448 * SCALE, 0, 0, 512 * SCALE, 448 * SCALE,
+                                  GL_COLOR_BUFFER_BIT, GL_NEAREST);
```

Efecto esperado en el pico: 615 × 1,75 MB ≈ 1,1 GB de tráfico en vez de 5,2 GB (swap ~50 ms → ~12-15 ms).
Con el outline prendido: 0,92 MB por copia (0,01-0,02 ms) + pase ~0,1-0,2 ms.

*Verificar antes de dar por bueno:* split screen (los dos views usan la misma textura; el present de cada uno
también recorta 512×448), y cualquier efecto que lea la copia fuera del rectángulo visible (no hay ninguno en
`gs_gl.c:1024/1050`, `dclut.frag`, `outline.frag`, `alphakey.frag`: todos usan `vUv` 0..1 del recorte visible).
Si se quisiera aún más fino, usar el scissor del momento de la copia (el juego lo pone en 0..511,0..447 antes de
`CopyAlphaToDepth`, asm `180EA8`), pero eso agrega el caso "scissor parcial" y no hace falta para el 4,57×.

### 6.4 (Opcional) dedupe por contenido

`native 4` es idempotente si no se dibujó nada en el target desde la última copia. Un contador por target
(`auxDirty[target]++` en cada draw, comparado contra el valor al copiar) elimina copias repetidas sin cambiar
la semántica. No es la causa del pico (615 no son `native 4`), pero es barato y cierra el caso "varias copias
por cuadro" que menciona el comentario del gate.

### 6.5 Lo que NO propongo

- Cablear el outline nativo (emitir el marcador desde `ObjOutline_Draw`) es otro bug (visual, B5), no de FPS.
  Si se hace, el costo es el de §6.3: ~0,2 ms.
- No tocar `date_snapshot`/`native 5` en este informe: es el sospechoso del pico, pero es el tema de
  FX_glare_glow / otro agente. Acá sólo se aporta la atribución y el contador.

---

## 7. Cómo confirmarlo (una corrida, sin adivinar)

1. **Atribuir el pico.** Compilar el árbol actual (ya trae `blit4/5/6`) e instalar; jugar/demo la misma pelea
   con `BT2_GLTIME=1` (y `BT3_GS_VERBOSE=1` para ver draws). En los cuadros de pico mirar:
   - `blit4` 0-2 y `blit5` ~600 ⇒ hipótesis de este informe (el outline no es el culpable; el gate no cambia el FPS).
   - `blit4` ~600 ⇒ la creencia del usuario; entonces el gate (bits 1+2+8) ya lo baja a 0 con `fx_off=31` y hay
     que buscar por qué se emiten 600 copias (call sites).
   - `blit6` ~600 ⇒ self-copies; el arreglo de §6.3 aplica igual (y hay que revisar el tamaño RGBA8).
2. **Separar CPU de GPU.** Una corrida con `BT2_GLTIME_FINISH=1`: el costo de las copias se mueve de `swap` a
   `loop`. Si `loop` sube ~50 ms en el pico, es GPU; si no, es espera del swap/driver.
3. **A/B del checkbox.** Misma escena y cámara, `fx_off=31` vs `fx_off=30` (sólo outline prendido), ventanas de
   60 cuadros: la diferencia de `total`/`swap` debe ser < 1 ms. Si es mayor, hay más copias de las previstas
   (medir `blit4`).
4. **Confirmar que el pase nativo está muerto.** Con `fx_off=0x1E` (todo apagado menos el outline), el log debe
   seguir diciendo `0 native effects`. Si dice > 0, existe un emisor del marcador 0x7F que este informe no
   encontró y hay que revisar el mapa.

---

## 8. Lo que NO está verificado

- Que los 615/613 sean `native 5`: es la hipótesis con mejor respaldo (tamaño R8 y call sites), no medida.
  Lo resuelve el punto 7.1 en una corrida.
- El ancho de banda efectivo de `glBlitFramebuffer` en esta RX 580/Mesa: se deduce de 14-15 copias ≈ 0,7-0,9 ms,
  con un margen de ±50 %.
- Que limitar la copia a 512×448×SCALE no rompa ningún efecto: los shaders leen el recorte visible, pero no se
  probó en split screen ni con el pan blur.
- Que el outline se vea hoy por otra vía (textura del modelo): no se comparó contra una captura de la PS2.
