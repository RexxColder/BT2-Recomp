# B15 — Map Select: por qué falta la imagen del escenario (las dos capas) y arreglo propuesto

Investigación de **solo lectura** (subagente investigador, 2026-11-11). No se modificó ni compiló nada, no se
lanzó el juego, no se tocó `/mnt/datos2/BT2-Decomp`.

**Diagnóstico: (b) el draw.** La pantalla *sí* se dibuja con las dos capas del escenario, pero en el port el
**alfa** con el que se emiten las dos capas sale **0** por un error de traducción en el C equivalente (se lee una
función `void` como si devolviera `float`). No es el loader (a) ni el estado (c).

Arreglo: 2 líneas por archivo en `port/eq/418E78.c` y `port/eq/418CC8.c`. Diff al final, sin aplicar.

---

## 1. Qué código dibuja esta pantalla en el port

El video/estado es **Ultimate Training** (modo 61/63), no el char select de versus. Cadena verificada
archivo:línea en el port:

| paso | archivo:línea | qué hace |
|---|---|---|
| modo 60..63 → `func_003EC690` | `port/eq/3B7FA8.c:233-237` (dispatch) | bucle del submenú de entrenamiento |
| estado 0x40 → `func_0041A5D8(4)` | `port/eq/3EC690.c:82-91` | pantalla de mapa + música |
| loop: `func_00419820()` cada frame | `port/eq/41A5D8.c:65` | layout del map screen (Flash + previa) |
| elige el draw de la previa | `port/eq/419820.c:105-110` | `if (G->0xC4 != 2 || (G->0xD0 & 4)) func_00418E78(); else func_00418CC8();` |
| **draw de las 2 capas** | `port/eq/418E78.c:30-36` | sube 2 texturas y emite 2 quads (DMA directo) |
| armado del quad / RGBAQ | `port/eq/418808.c:69-81`, `port/eq/4186B8.c:24-27` | `A = (int)((float)*(u32*)(blk+0x34) * f12) << 24` |
| de dónde sale ese `f12` | `port/eq/26F148.c` + `port/eq/270F40.c` | alfa del clip Flash (0..1) |

El overlay DBZP.BIN **sí está** en el port: se carga en `0x3B3100` (`config/overlay/DBZP.yaml`, `port/full/mem.c:35`)
y de sus 507 funciones, **494 tienen C** en `port/eq` (las 13 que faltan son 8 bytes de datos mal marcados en
`0x3D6728..`). La pantalla de este bug (`0x418E78`, `0x419820`, `0x41A5D8`) está traducida y en C.

> Nota sobre la investigación previa (`B15_investigacion_stage_select.md`): buscó `0x34xxxx` en `funcmap.csv`.
> Eso no prueba nada: `0x34xxxx` es el espacio de direcciones del **proyecto de decomp**, no el del port. En el
> port el overlay vive en `0x3B3100` (comprobado con los strings: `fr_menu_chrsel` en `RAM 0x4278C0` =
> `DBZP.BIN + 0x747C0` con base `0x3B3100`). El `CharSel` de versus de las cabeceras `menu_c/menu_d/menu_e` es
> **otra pantalla** (los modos versus `func_003F9300`), no la del video.

---

## 2. Evidencia de los volcados (F9/F10)

Los dos dumps son la **pantalla de mapa**, no la pelea:
`20261111-121635.log:136205` ("gs: dumping frame 3752", F9) y `:162756` ("RAM dump (F10) frame 4116") están entre
`ESTADO ... modo 63 (entrenamiento)` (`:36393`) y `ESTADO ... BATALLA modo 63` (`:12876136`, vblank 2032). El
`fight.log` confirma: vblank 1962 = `RAMDUMP f4116` (los frames del nombre son del renderer, no vblanks).

Objeto del map screen **G = `D_0042BB80` = `0x00CBCFC0`** (idéntico en `ram1_f3752` y `ramkey1_f4116`):

| campo | dirección | valor | lectura |
|---|---|---|---|
| `G->0xD4` (índice de mapa) | `0xCBD094` | `0` | primer mapa de la lista = **Wasteland** (coincide con la banda morada) |
| `G->0xFC[0]` (lista de mapas) | `0xCBD0BC` | `0` | id de archivo de mapa |
| `G->0x13C` | `0xCB…FC` | `16` | 16 mapas desbloqueados (`0x41A5D8` rota sobre ellos) |
| `G->0x140` / `G->0x144` | `0xCB…` / `0xCB…` | `0x00EC7CC4` / `0x22` | lista de música (34 entradas) |
| `G->0xCC` (lista de texturas) | `0xCBD08C` | `0x00E10E40` | registros de 0x40 en `0x00E10E60` |
| `G->0xCC` rec. 0 | | data `0xE112A0` (0x4080), TEX0 0x8080 | subida a `0x3000/0x3040` |
| **`G->0xCC` rec. 1** (índice = `G->0xFC[G->0xD4]+1` = 1) | | data `0xE153E0` (0x3188, **12585 bytes ≠ 0**), CLUT `0xE1D460` | subida a **`0x3041/0x30C1`** |
| `G->0xC0` (objeto de escena) | `0xCBD080` | `0x00FEF1A0` | ver abajo |
| `G->0xC4` | `0xCBD084` | **`3`** | ⇒ `419820` toma la rama `func_00418E78` |
| `G->0xD0` | `0xCBD090` | `0` | sin flags |

Objeto de escena (`0xFEF1A0` = `D_00421384+0x20`, `D_00421384` = `0xFEF180`):
`+0xC0` = `0x40DE4350` (handle nativo del port), `+0xC4` = 0 (marca de archivo), `+0x1AC` = `0x55B` (id de archivo
del mapa 0), `+0x1B0`/`+0x1B8` = 0, `+0xC8` = 1, `+0xCC` = 2.

**El loader corrió y la textura se sube todos los frames.** En el log, entre la entrada al modo 63 (`:36393`) y el
F10 (`:162756`) hay **1550** `uplog: frame N dir 0 sbp 0000 dbp 3040 ... size 8x2`, **1550** `dbp 3041 dbw 2 psm 00
size 128x64` y **1550** `dbp 30c1 ... size 16x16`: son exactamente las tres llamadas a `TexFile_UploadOne` de
`func_00418E78` (`418E78.c:31-33`). O sea: **el draw se llama y la textura está en VRAM**.

Renderer: en el frame 3750 `gpu: frame 3750: 38 draws, 240 vertices, 2 targets, 366 textures` y
`gpu: dropped by site: 0 0 0 0 0 0` — el GS no descarta nada. Los quads del preview van por **DMA directo**
(`Dma_BeginDirect/Dma_EndDirect`), que no aparecen en ese contador; no hay señal de descarte.

---

## 3. Causa: el alfa `f20` sale 0 (bug de traducción)

En el asm original (`/tmp/opencode/ovl.dis`, overlay en `0x3B3100`):

```
  418f8c: jal 0x26f148          ; f20 = func_26F148(layer, record)  -> alfa del clip (0..1)
  418fac: jal 0x286768          ; TexFile_UploadOne(...)
  418fb0: mov.s $f20,$f0        ; <-- DELAY SLOT: f20 = retorno de func_26F148
  418ff0: mov.s $f12,$f20       ; 1er pase:  t0=0, f12=f20
  419010: li    t0,1
  419014: jal 0x418808          ; 2do pase:  t0=1, f12=f20
```
(`0x26F148` = `f32 func_0026F148` → `port/eq/26F148.c` → `func_00270F40`, que devuelve `(i/128)`; es el alfa del
nodo Flash. El mismo patrón correcto está en `port/eq/3EA470.c:40-41`, y `docs/agents/b11/done_014.txt:2` lo
describe: *"f20 from func_26F148, (s32)(f20*128) alpha"*.)

El C del port hace otra cosa (`port/eq/418E78.c:30-31`, igual en `418CC8.c:31-32`):

```c
    func_26F148(D_0042BB80 + 0x30, frame + 0xB0);                       // declara void -> descarta el alfa
    f20 = TexFile_UploadOne(*(s32 *)(D_0042BB80 + 0xCC), 0, 0x3000, 0x3040);  // declara f32, pero es void
```

`TexFile_UploadOne` (= `0x286768`) **no devuelve float** (asm sin `$f0`; `port/eq/286768.c` es `void`), así que
`f20` queda con lo que haya en `xmm0`. En el objeto compilado se ve:

```
  94: callq  TexFile_UploadOne
  99: movss  %xmm0, 0xc(%rsp)        # f20 = basura (no es el retorno de func_26F148)
  e5: movss  0xc(%rsp), %xmm0        # f12 = f20
  eb: xorl   %r8d, %r8d              # t0 = 0
 101: movss  0xc(%rsp), %xmm0
 107: movl   $0x1, %r8d              # t0 = 1
```
(`llvm-objdump port/build/gen/full/obj/port__eq__418E78.o`)

Con eso, en el quad (`port/eq/4186B8.c:24-27`):
`A = (int)( (float)*(u32*)(blk+0x34) * f12 ) << 24` en el RGBAQ. Con `f12≈0` → **A=0**. El PRIM es `0x156`
(bit7 ABE=1, blending activo) y RGB=0x808080 (1.0): **las dos capas se pintan con alfa 0 = invisibles**, y detrás
queda el fondo nube del movie Flash (lo que se ve hoy). Los dos quads son justo las dos capas del pedido:

* pase `t0=0`, bloque `D_0042EE28[0]`, `+0x34 = 0x48 (72)` → **fondo a pantalla completa, alfa 0x48 ≈ 56 %**
  (por eso en la referencia se ve *velado* por encima de las nubes, y al agrandar una textura chica queda
  *desenfocado*);
* pase `t0=1`, bloque `+0x38`, `+0x34 = 0x80 (128)` → **cuadro nítido, alfa 0x80 = opaco**.

Con `f12=0` los dos salen con A=0. Nada más en esa función depende de `f20` (las coordenadas salen del bloque
`D_0042EE28` y de la posición del nodo Flash vía `func_26F118`), así que es exactamente "falta solo la imagen".

Ya estaba detectado como declaración sospechosa en `docs/agents/b12/check_decls_report.txt:980-981`
(`RET_VOID_DEF TexFile_UploadOne ... el llamador lee basura`).

### Descartado y por qué

* **(a) loader** — descartado: el objeto del map screen está armado en RAM, su lista de texturas (`0xE10E40`) tiene
  los registros, el registro del mapa 0 está cargado (12.585 bytes ≠ 0) y `TexFile_UploadOne` corre **1550 veces**
  en la pantalla (`uplog ... dbp 3041`).
* **(c) estado** — descartado: `G->0xD4 = 0`, `G->0xFC[0] = 0` (Wasteland), `G->0x13C = 16`, `G->0xD0 = 0`,
  `G->0xCC` válido. El HUD coincide con la referencia.
* **renderer/GS** — sin evidencia: `dropped by site: 0 0 0 0 0 0` en el frame 3750 y los quads van por DMA directo
  (el mismo camino que usa el resto del HUD, que sí se ve).
* **Geometría/posición** — no se toca: sale de `D_0042EE28` + `func_26F118` (nodo Flash), que el port ya usa bien
  para las otras capas de la pantalla.

---

## 4. Arreglo propuesto (mínimo, NO aplicado)

Restaurar la semántica del delay slot: **`f20` = retorno de `func_26F148`** y no de `TexFile_UploadOne`.

```diff
--- a/BT2-Recomp/port/eq/418E78.c
+++ b/BT2-Recomp/port/eq/418E78.c
@@ -8,11 +8,11 @@
 void *memcpy(void *dst, const void *src, u32 n);
 void func_26EBC0(u8 *a0, u8 *a1, u8 *a2);
 void func_26F118(u8 *a0, u8 *a1, s32 *a2, s32 *a3);
-void func_26F148(u8 *a0, u8 *a1);
-f32 TexFile_UploadOne(s32 a0, s32 a1, s32 a2, s32 a3);
+f32 func_26F148(s32 a0, s32 *a1);
+void TexFile_UploadOne(s32 a0, s32 a1, s32 a2, s32 a3);
 void *Dma_BeginDirect(void);
 void *func_00418808(void *a0, u8 *a1, s32 a2, s32 a3, f32 f12, s32 t0);
 void Dma_EndDirect(void *a0);
@@ -27,8 +27,8 @@
-    func_26F148(D_0042BB80 + 0x30, frame + 0xB0);
-    f20 = TexFile_UploadOne(*(s32 *)(D_0042BB80 + 0xCC), 0, 0x3000, 0x3040);
+    f20 = func_26F148(D_0042BB80 + 0x30, (s32 *)(frame + 0xB0));
+    TexFile_UploadOne(*(s32 *)(D_0042BB80 + 0xCC), 0, 0x3000, 0x3040);
     TexFile_UploadOne(*(s32 *)(D_0042BB80 + 0xCC),
                       *(s32 *)(D_0042BB80 + (*(s32 *)(D_0042BB80 + 0xD4) << 2) + 0xFC) + 1, 0x3041, 0x30C1);
     p = Dma_BeginDirect();
```

```diff
--- a/BT2-Recomp/port/eq/418CC8.c
+++ b/BT2-Recomp/port/eq/418CC8.c
@@ -8,11 +8,11 @@
 void *memcpy(void *dst, const void *src, u32 n);
 void func_26EBC0(u8 *a0, u8 *a1, u8 *a2);
 void func_26F118(u8 *a0, u8 *a1, s32 *a2, s32 *a3);
-void func_26F148(u8 *a0, u8 *a1);
-f32 TexFile_UploadOne(s32 a0, s32 a1, s32 a2, s32 a3);
+f32 func_26F148(s32 a0, s32 *a1);
+void TexFile_UploadOne(s32 a0, s32 a1, s32 a2, s32 a3);
 void func_003B4C20(s32 a0, s32 a1);
 void *Dma_BeginDirect(void);
 void *func_00418A68(void *a0, u8 *a1, s32 a2, s32 a3, f32 f12, s32 t0);
@@ -28,7 +28,7 @@
-    func_26F148(D_0042BB80 + 0x30, frame + 0xB0);
-    f20 = TexFile_UploadOne(*(s32 *)(D_0042BB80 + 0xCC), 0, 0x3000, 0x3040);
+    f20 = func_26F148(D_0042BB80 + 0x30, (s32 *)(frame + 0xB0));
+    TexFile_UploadOne(*(s32 *)(D_0042BB80 + 0xCC), 0, 0x3000, 0x3040);
     func_003B4C20(*(s32 *)(D_0042BB80 + 0xC0), 0x3041);
     p = Dma_BeginDirect();
```

`func_26F148` es alias de `func_0026F148` (`port/build/full/bt2full.map:32158`) y su definición ya es
`f32 func_0026F148(void *arg0, s32 *arg1)` — no hay que tocar más.

Compilar/instalar (cuando se decida aplicar, según `AGENTS.md`):
`BT2_IRFIX=1 scripts/capped.sh 8G python3 port/tools/build_full.py --jobs 2 --only 418E78` y `--only 418CC8`,
después `scripts/capped.sh 8G python3 port/tools/link_full.py`, backup del binario y copiar a `BT2-test/bin/bt2`.

**Qué probar (usuario):** Menú → Ultimate Training → Training → elegir personaje → pantalla **Map Select**
(Wasteland). Deben aparecer el fondo velado a pantalla completa y el cuadro nítido arriba a la izquierda.

---

## 5. Lo que NO pude fundamentar / riesgos

1. **No pude ejecutar** el juego (regla de esta investigación): que `f20` valga efectivamente ~0 en runtime es
   inferido (la C ABI deja `xmm0` indefinido tras una función `void`, y el preview nunca aparece en los cuadros
   del usuario). El asm original sí prueba cuál *debería* ser el valor.
2. **El alfa del nodo** (`func_26F148` → `func_00270F40`) no lo pude leer del dump: el registro del nodo Flash vive
   en la pila del juego en `0x4180xxxx`, que está **fuera de los 32 MB volcados** (el port pone la pila del juego
   en `0x41800000`, `20261111-121635.log:4`). Se espera ~1.0 porque la referencia muestra el preview visible; si
   viniera 0, el fix no alcanzaría.
3. **Posible segundo problema (state 0xC4 = 3, no 2):** con `G->0xC4 == 3` el port usa siempre `func_00418E78`
   (textura pre-renderizada). La rama `func_00418CC8` (que renderiza la **escena live** a `0x3041` con
   `func_003B4C20`) sólo se usa si `func_2B8328(handle) == 2`. No pude determinar cuál de las dos usa el original
   en esta pantalla (el visor midió *paralaje* en el paneo, lo que sugeriría la escena live). Si el original usa la
   escena live, después de este fix el port mostrará la imagen pre-renderizada: **imagen sí, pero quizá sin el
   paneo/encuadre exacto** — sería un bug aparte del estado de la escena (`0x2B8328` / `0x2B73C0`, sin C en
   `port/eq`, corre recompilado).
4. **El paneo/animación** del preview (que la referencia tiene) no está verificado: depende del movie Flash y del
   camino que finalmente use el port.
5. **Modos versus (`func_003F9300`, el `CharSel` de las cabeceras)** no los investigué: el video es entrenamiento.
   Si el mismo síntoma aparece en Dueling, la cadena puede ser otra (`CharSel_Draw` con `bg[0]/bg[1]`).
6. Cosméticos detectados y **no** tocados (no afectan el síntoma): el `memcpy(frame, ..., 0xA8)` del port copia 8
   bytes de más (el original copia `0xA0`; cae dentro de la misma data, `D_0042EE18`), y el prototipo de
   `func_00418808`/`func_00418A68` está en distinto orden en la definición y en el llamador (el mapeo de
   registros a0..a3/t0/f12 coincide igual: `t0` recibe 0/1 y `f12` recibe `f20`).
