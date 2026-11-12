# Depth tint (`gsFxOff & 4`) — camino, estado y costo (solo lectura, 2026-11-12)

Investigación sin modificar ni compilar nada. Logs: `BT2-test/logs/vivo/20261112-004130.log`
(GL, scale=2, `bt2_settings.txt` con `fx_off=31`). Backup comparado: `backups/gs_draw.c.pre_fxgate`.

**Resumen**

1. **El gate de `depth_clut()` corta el pase de tinte por profundidad** (src=0 y escribe color, `gs_draw.c:441`), pero
   **no** corta los pases que sólo escriben alfa (src=0, `wm==0x00FFFFFF`, el byte del *glare*) ni los src=1 (tabla de
   ids: see-through / brillo de objetos). Eso son los 3-4 dclut que quedan con todo apagado.
2. **El `3/60` del log es un error de lectura**: `GLTIME f=2040 dclut 3/0.0 ms` significa **3 draws dclut en ese
   cuadro**, no 3 en 60. Los contadores (`nDclut`, `nBlit`) son locales a `frame_end()` y se resetean cada cuadro
   (`gs_gl.c:900`). En pelea hay 3-4 dclut **por cuadro** en todos los muestreos (48 con 3, 45 con 4, 52 con 0).
3. **El dclut no es el costo de FPS**: en el cuadro caro (`f=2040`, 67.6 ms) hay **2049 draws y 615 blits**, y el
   dclut aporta **3** draws de un triángulo de pantalla completa con 3 taps NEAREST (`glDrawArrays`, `gs_gl.c:1033`).
   El `0.0 ms` se mide alrededor de `glDrawArrays` = envío de CPU, no trabajo de GPU.
4. **El 49.9 ms de swap coincide con 615 `glBlitFramebuffer` de 1024x896** (copias alfa, `native 4`, `gs_gl.c:989-1012`),
   no con el dclut: 615 × 917.504 px × 4 B = 2.26 GB de lectura + 2.26 GB de escritura por cuadro. Ese dato es
   **anterior** al gate de `native 4` ya aplicado (`gs_draw.c:515-516`), que con `fx_off=31` ya los saltea.
5. **No hay que tocar la escala de z (B30) para el FPS**: B30 es un bug de *apariencia* del tinte (GL guarda
   `(z/zmax+1)/2`, `gs_gl.c:245`), ortogonal al tiempo de cuadro. Su fix está bocetado en `staging/F6_vulkan_revision.md`
   §7.A y sigue sin aplicar.

---

## 1. Estado

| bit (`fx_off`) | control UI (`ui.cpp:383-393`) | quién lo consume en `gs_draw.c` | estado |
|---|---|---|---|
| 1 | Outline | outline nativo + `native 4` (515) | fuera de alcance |
| 2 | See-through tint | `depth_clut` cbp `0x3E94` (449), `native 4` (515) | fuera de alcance |
| **4** | **Depth tint** | **`depth_clut` src=0 color (441)** | **gate existente, correcto para su caso** |
| 8 | Glare and glow | blend 0x68 (591), **y debería cortar dclut src=0 alfa** | **no gatea el dclut** |
| 16 | Distance blur | blend 0x54 (591) | fuera de alcance |

`fx_off=31` = los cinco apagados (`ui.cpp:391-392`: `v.fxOff |= 1 << i` con el checkbox en off).
Se persiste en `Port_SettingSave("fx_off", ...)` (`gs_draw.c:1270`) y se lee de `bt2_settings.txt`
(`fx_off=31`, mtime 00:41, la misma sesión del log) o de `BT3_FX_OFF` (`gs_draw.c:1305`).

## 2. Mapa del camino

| pieza | dónde | qué hace |
|---|---|---|
| bit | `ui.cpp:383-393` → `PortVideo.fxOff` | 5 checkboxes, bit i = efecto i apagado |
| global | `gs_draw.c:70`, seteada en `1234/1257/1270/1305` | `gsFxOff`, máscara de 31 |
| disparador | `gs_draw.c:538-542` | primitiva sprite con `tbp/32 == zbp` y `tpsm == 0x1B` (página de profundidad vista PSMT8H): es `GfxPost_DrawDepthClut` (16 strips del juego) |
| `depth_clut()` | `gs_draw.c:428-468` | colapsa los 16 strips en **un** `native 3` (`464-466` deduplica strips consecutivas) |
| fuente del byte | `gs_draw.c:438` + `502-506` | `src = gsDepthByteIsFog ? 0 : 1`; el flag lo fija el último relleno de la página de profundidad: `tpsm==0x1B` → rampa de niebla (0), otro → copia de ids (1) |
| gate | `gs_draw.c:441`, `445-452` | 441: `(gsFxOff & 4) && src==0 && wm!=0x00FFFFFF` → no se emite. 446: cbp `0x3E8C` (contorno) se descarta. 449: cbp `0x3E94` + bit 2 → no se emite |
| tabla | `gs_draw.c:453` (`clut_texture`) | CLUT de 256 entradas desde memoria GS por CBP |
| pipeline | `gs_draw.c:372-374`, `457` | `vu==4` → key con bit 22 (`fx`), sólo blend + write mask |
| shader | `shaders/dclut.frag:22-33` | `src=0`: `z = depthTex.r * u.p.y`; `idx = z>=65448 ? 0 : 255 - int(z/256)`. `src=1`: `idx = auxTex.r*255`. Luego `texelFetch(clutTex, idx)` y salida color+alfa |
| z máximo | `gs_draw.c:459` | según PSM del zbuf: `0xFFFFFFFF`, `0xFFFFFF` o `0xFFFF` |
| FBO sin depth | `gs_gl.c:464-466`, `752-757`, `1023` | `sTgFboNoDep`: color+aux, sin attachment de profundidad, para muestrear `sTgDep` sin feedback |
| draw | `gs_gl.c:1020-1052` | bind no-dep, `set_textures(sTgDep, 6, sAuxCopy, 6, clut)`, `glDrawArrays(GL_TRIANGLES,0,3)`; después `cur=-1` para volver al FBO con depth |
| programa | `gs_gl.c:665` | `p->fx ? sDclutProg : sMainProg[vu]` (creado en `789`) |
| sampler | `gs_gl.c:846-852` | índice 6 = `NEAREST` + clamp → el depth 32F se lee 1 tap, sin filtrado |
| vert | `shaders/fx.vert:5-8` | triángulo de pantalla completa, `vUv = (p.x, 1-p.y)` |

### Qué se emite con ON vs OFF

- **Depth tint ON (bit 4 en 0)** y el último relleno de la página fue la rampa de niebla: se emite **un** `native 3`
  (`src=0`, `wm != 0x00FFFFFF`, scissor del juego, blend y write mask del estado GS) que cubre la pantalla y escribe
  color. El juego sigue mandando sus 16 strips: se descartan como primitivas PS2-only (`540`) y el pase nativo las
  reemplaza.
- **Depth tint OFF (bit 4 en 1)**: con `wm != 0x00FFFFFF` el pase **no se emite** (441). No hay muestreo de
  profundidad ni escritura de color. El juego igual parsea sus strips (cuentan en `gsSkipped`/`gsSkipWhy[1]`) y el
  relleno de niebla de la página se descarta como primitiva (`521-537`); no queda trabajo de GPU por el tinte.
- **Excepción del gate**: si `wm == 0x00FFFFFF` (sólo alfa) el pase se emite aunque bit 4 esté en 1, porque ese byte
  lo consume el *glare* (`StgGlare_Draw`: "clears the frame's alpha, writes the CLUT alpha by depth, then the glow
  pass", `include/sys/gfxm_a.h:252`). Es trabajo muerto cuando bit 8 también está apagado, y `fx_off=31` lo tiene
  apagado.

## 3. Evidencia (log `20261112-004130.log`, GL, 1024x896)

| línea | contenido |
|---|---|
| 6-7 | `internal resolution 2x (1024 x 896)`, `AMD Radeon RX 580 (radeonsi)` |
| 61269 | `gpu: frame 1800: 2295 draws, 95364 vertices, 9 targets, 1263 textures, 25 pipelines` |
| 66050 | `gpu: frame 2040: 2049 draws, 88036 vertices, 9 targets, 1604 textures` |
| **66053** | **`GLTIME f=2040 dclut 3/0.0 ms blit 615/0.0 loop 17.6 swap 49.9 total 67.6`** |
| 66055-58 | `slow: frame 2041: 79.1 ms = game 3.1 + display list 76.7` · `submitting the frame 67.6 ms` · `average 53.7 ms, 59 of 60 over budget` |
| 72053 | `GLTIME f=2280 dclut 3/0.0 ms blit 613/0.0 loop 35.8 swap 19.8 total 55.6` |
| 61272-88000 | 48 muestreos con `dclut 3`, 45 con `dclut 4`; `blit` normal 14-20, picos 613/615 |
| (2.ª pelea, sólo como cota) | `gpu: frame 8160: 4336 draws` → `submitting 68.3 ms` (4 draws dclut) — no se usa para el diagnóstico |

Contraste que importa: en el mismo cuadro, **3 draws dclut vs 2049 draws y 615 blits**. El tiempo de dclut medido es
`SDL_GetTicksNS()` alrededor de `glDrawArrays` (`gs_gl.c:1031-1036`), o sea la sumisión; GL es asíncrono y con
`SwapInterval(0)` (`gs_gl.c:753`) el costo real aparece en `SDL_GL_SwapWindow` (`gs_gl.c:1194-1196`) = los 49.9 ms.
Aritmética de los blits: 615 copias de 1024x896x4 B = 2.26 GB leídos + 2.26 GB escritos en un cuadro; a ~150 GB/s
efectivos de la RX 580 son ~30 ms, del orden del swap observado. Los 3 dclut son 2.75 Mpx con 3 taps: < 1 ms.

## 4. Por qué quedan 3-4 dclut con todo apagado

El gate de 441 sólo cubre **una** de las cuatro clases de pase de tabla. Con `fx_off=31` sobreviven:

| clase | condición | gate actual | ¿debería estar? |
|---|---|---|---|
| A. depth tint (color desde profundidad) | `src=0`, `wm != 0x00FFFFFF` | 441 lo corta (bit 4) | no (bien) |
| B. byte del glare (alfa desde profundidad) | `src=0`, `wm == 0x00FFFFFF` | **ninguno** | no si bit 8 está apagado |
| C. see-through (ids) | `src=1`, `cbp == 0x3E94` | 449 (bit 2) | no (bien **si** el CBP es el de BT2) |
| D. brillo de objetos (ids) / resto src=1 | `src=1`, otro CBP | **ninguno** | no si bit 8 está apagado |

Hipótesis principal del conteo 3-4: **B + D + (C si el CBP no coincide)**. No se puede cerrar sin medir el CBP:
`0x3E8C/0x3E94` son constantes **heredadas de BT3** (`docs/bugs_open.md:313`: "Constantes BT3 fijas (CBP
0x3E8C/0x3E94…)"), y si el see-through de BT2 usa otro CBP el gate 449 no corta nada. Evidencia parcial en
`src/auto/m2c_280CD8.c:37-43` (inicialización de tablas): `func_002847E8(+0x2040, 0x3E94)` es un solo CLUT y
`func_0027F628(+0x2500, 0x3E90)` inicializa dos CLUT de doble búfer en `0x3E90`; ninguna de las dos se puede asignar
sin ambigüedad a un efecto desde el C (esas funciones viven en el relleno).

**Riesgo colateral del gate ya aplicado (`native 4`, 515-516):** el `native 4` es el único que escribe `sAuxCopy`
(`gs_gl.c:990`, destino `sAuxCopy`), y `dclut.frag` `src=1` lee `auxTex = sAuxCopy` (`gs_gl.c:1027`). Si el brillo de
objetos (bit 8) es un dclut `src=1`, con "Outline off + See-through off + Glare/glow ON" hoy se saltea la copia y ese
pase lee el alfa del cuadro anterior. Con `fx_off=31` no se nota; con bit 8 prendido sí. El contador propuesto dice si
existe ese lector.

## 5. Costo: cómo separar dclut del swap (TEMP mínimo, no aplicado)

Dos piezas, ambas activadas por variable de entorno para poder dejar el binario limpio:

1. **Atribución** (una línea por pase, sólo cada 60 cuadros) — dice qué clases quedan con todo apagado:

```c
/* TEMP depth-tint: qué pases de tabla quedan y con qué tabla (BT2_DCLUT=1) */
if (getenv("BT2_DCLUT") != NULL && gGsFrame % 60 == 0) {
    fprintf(stderr, "DCLUT f=%u src=%d cbp=%04x wm=%06x tgt=%d fx=%02x\n",
            gGsFrame, d.src, (unsigned)((gGs.tex0[ctx] >> 37) & 0x3FFF), wm, d.target, gsFxOff);
}
```

2. **A/B del costo real**: kill switch del pase, y comparar `loop`/`swap` del `GLTIME` en la misma pelea:

```c
    if (getenv("BT2_NO_DCLUT") != NULL) { return; }  /* TEMP: A/B del costo del pase */
```

Si con `BT2_NO_DCLUT=1` el `swap`/`loop` no cambia, el pase no es el problema (lo que ya dice la evidencia).
Para el número real de GPU de un pase (sacrificando el paralelismo, sólo test):

```c
    int fin = getenv("BT2_DCLUT_FINISH") != NULL;
    if (fin) glFinish();
    uint64_t td = SDL_GetTicksNS();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    if (fin) glFinish();
```

## 6. Descarte explícito

- **Shader/resolución/tabla**: no hay nada que optimizar. El pase es 1 triángulo, 3 taps `NEAREST` con clamp
  (`gs_gl.c:846-852`), CLUT de 256x1 ya subida. Bajarlo a media resolución o cachear la tabla no mueve la aguja
  frente a 2000 draws.
- **FBO sin depth / feedback**: ya resuelto (`sTgFboNoDep`, `gs_gl.c:752-757`); no hay serialización por muestrear un
  attachment adjunto. El costo de `cur=-1` (`gs_gl.c:1050`) son 3-4 binds de FBO por cuadro: irrelevante.
- **B30 (escala de z)**: afecta *cómo se ve* el tinte (tabla corrida ~128 entradas y, con z de 32 bits, índice
  saturado), no el tiempo. No lo toco: `staging/F6_vulkan_revision.md` §7.A ya tiene el diff y pide verificación
  visual. Sin capturas A/B no hay evidencia para aplicarlo.
- **El conteo 615 blits como "causa del FPS"**: es un pico de 2 cuadros de un contador de copias alfa, no de dclut;
  además quedó cubierto por el gate de `native 4` que ya está en el árbol.

## 7. Diff boceto (NO aplicado)

### 7.1 Gate completo por lector (`port/full/gs/gs_draw.c:436-457`)

```diff
     memset(&d, 0, sizeof(d));
     d.native = 3;
     d.src = gsDepthByteIsFog ? 0 : 1;
     d.target = GsDraw_TargetGet((uint32_t)(gGs.frame[ctx] & 0x1FF), 0);
-    /* switched off by the user: the passes that colour the picture (the ones that only write alpha feed the glow) */
-    if (d.target < 0 || ((gsFxOff & 4) && d.src == 0 && wm != 0x00FFFFFFu)) {
-        return;
-    }
     {
         uint32_t cbp = (uint32_t)((gGs.tex0[ctx] >> 37) & 0x3FFF);
+        unsigned own;
         if (cbp == 0x3E8C) {
             return; /* the outline's own passes: the outline is drawn natively at its marker (outline.frag) */
         }
-        if (cbp == 0x3E94 && (gsFxOff & 2)) {
-            return; /* the see-through tint, switched off */
-        }
+        /* which switch makes this pass dead: one pass, one reader.
+           src 0 + colour: the depth tint (4);  src 0 + alpha only: the glare's byte (8);
+           src 1 + the see-through's table (2);  any other src 1: the object glow's byte (8). */
+        own = d.src == 0 ? (wm != 0x00FFFFFFu ? 4u : 8u) : (cbp == 0x3E94u ? 2u : 8u);
+        if (d.target < 0 || (own != 0 && (gsFxOff & own) != 0)) {
+            return;
+        }
     }
```

Efecto esperado con `fx_off=31`: 0 dclut por cuadro (hoy 3-4). **No aplicar tal cual**: primero correr con
`BT2_DCLUT=1` y confirmar cuál CBP es el see-through en BT2; si es otro, la rama `src=1` tiene que usar ese número
(o el gate 449 actual no está apagando nada). Y confirmar si el brillo de objetos es `src=1` (si no lo es, `own=8`
para `src=1` es incorrecto).

### 7.2 Copia de ids: sumar el lector que falta (`gs_draw.c:511-517`)

```diff
-                /* The copy only feeds the outline (bit 1) and the see-through tint (bit 2): ... */
+                /* The copy feeds the outline (bit 1), the see-through tint (bit 2) and, if it is a src=1 table
+                   pass, the object glow (bit 8): ... */
                 if (c.target >= 0 && gsDrawCount < MAX_DRAWS && !(last != NULL && last->native == 4) &&
-                    !((gsFxOff & 1) && (gsFxOff & 2))) {
+                    !((gsFxOff & 1) && (gsFxOff & 2) && (gsFxOff & 8))) {
```

Condicional a lo mismo: sólo si el contador muestra un dclut `src=1` con bit 8 prendido.

## 8. Confirmación

Para el usuario, con el binario actual (que ya tiene el gate de `native 4`) y `BT2_GLTIME=1`:

1. Misma pelea, `fx_off=31`: esperar `blit` bajo (14-20, sin picos 615). Si el pico vuelve, el gate de `native 4` no
   está alcanzando todas las copias.
2. `BT2_NO_DCLUT=1` vs normal: si `loop`/`swap` no cambian, queda demostrado que el dclut no es el costo y no hay
   que optimizarlo. (No lo corrí: no puedo lanzar el juego.)
3. Con `BT2_DCLUT=1`, anotar `src`/`cbp`/`wm` de los 3-4 pases y cuáles desaparecen al apagar sólo el see-through y
   sólo el glare: eso decide 7.1 y 7.2.

**Sin verificar / límites:** no medí el costo real de GPU de un dclut (haría falta `BT2_DCLUT_FINISH`); no sé qué
CBP usa el see-through en BT2 (la constante `0x3E94` viene de BT3); no sé si el brillo de objetos emite un dclut
`src=1` (el relleno está compilado, sin fuente); no comparé el tinte visual ON/OFF contra la PS2 (eso es B30, §6).
