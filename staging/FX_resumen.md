# FPS en pelea — resumen consolidado de los 5 efectos (2026-11-12)

Investigación read-only, un agente por efecto. La pregunta era si los toggles de F1 provocaban el drop
(615 copias + `swap` 50 ms). **Ninguno lo provoca**: la causa común es el snapshot **DATE** (`native 5`).

## Los 5 efectos

| Efecto | Bit `fx_off` | Camino | ¿Causa el pico? | Nota |
|---|---:|---|---|---|
| Outline | 1 | `GsGpu_Native(1)` + `sOutlineProg`; copia `native 4` | **No** | `GsGpu_Native(1)` **no tiene emisor**: el checkbox no cambia la imagen. La copia es 1-2/frame y está gateada. |
| See-through tint | 2 | `depth_clut()` `src=1` (`cbp 0x3E94` heredado de BT3) + `sAuxCopy` | **No** | 1 dclut/frame; `dclut 0.0 ms` es sólo el envío. El `cbp` de BT2 puede no ser `0x3E94`; el gate actual no cubre todos los `src=1`. |
| Depth tint | 4 | `depth_clut()` `src=0` (depth32F) | **No** | El gate `&4` corta el tinte de color; los 3 dclut que quedan son alfa-only (`wm=0x00FFFFFF`, para el glow). Costo real en el swap, no en el draw. |
| Glare and glow | 8 | add-back 16 tiras ALPHA 0x68 + work buffers | **No** | El add-back se descarta **antes** de `date_snapshot`; el glow no genera copias. No gatear `native 5` (es DATE/HUD). |
| Distance blur | 16 | compuesto final ALPHA 0x54; copia frame→0x150 | **No** | El gate corta el draw final, no la copia; no genera `native 4/5/6`. 0x150 la comparten glow/pan blur: no gatear la página entera. |

## Causa real: snapshot DATE (`native 5`)

Logs:
- `005253` con gate de efectos: `GLTIME f=2640 blit 616 blit4 0 blit5 616 blit6 0 loop 22.8 swap 28.4`.
- `010217` con contadores + `glFinish`: `f=1800 blit 614 = blit4 0 + blit5 614 + blit6 0; loop 80.9 swap 0.0`.
- `011220` con coalescing: `f=4680 blit5 610; loop 80.9`.

Los contadores son **por frame**: son **610-615 snapshots DATE en un solo frame**, no 615 cada 60. Cada
`native 5` copia la textura completa (2048×2048, 4,19 MB R8) aunque la imagen útil sea menor (~4,57× de
desperdicio). `blit4/6 = 0`: no son los efectos, ni el outline, ni el glow.

`date_snapshot()` (`gs_draw.c:712`) crea una copia por corrida DATE. El primer coalescing por write-mask de
alfa no redujo el conteo en pelea: el alfa cambia entre draws DATE, así que la copia se considera necesaria.
El demo no reproduce el caso (allí `blit5` ≤ 2).

## Fix en curso (porter)

1. **DATE sin copia**: FBO sin aux (`sTgFboNoAux`) para los draws DATE, muestreando `sTgAux[target]` directo
   en vez de `sDateCopy`. Elimina los 610 `native 5`. Si el pipeline DATE escribe aux, no es viable.
2. **Fallback**: copiar sólo el área de imagen (`GS_PIC_W*SCALE × GS_PIC_H*SCALE`) en el blit `native 5`
   (4,57× menos) y, si se puede, el scissor del run.
3. Gate de `native 4` corregido: saltar sólo si outline, see-through **y** glow están apagados
   (`!((fxOff&1)&&(fxOff&2)&&(fxOff&8))`), porque el glow lee `sAuxCopy`.

## Higiene pendiente

- Con `fx_off=31` quedan 3 dclut alfa-only (`src=0 cbp=3e84/3e88`, `src=1 cbp=3e90`, `wm=00ffffff`); son
  baratos, pero podrían leer `sAuxCopy` vieja si el gate saltea la copia. Gatearlos por bit (4/8/2) después
  del fix de FPS.
- Los builds externos de `/mnt/datos2/BT2-Matching` (splat/permuter/fdiff) contaminan el `loop` CPU; para
  medir, correr con esos procesos quietos.

## Evidencia y detalle

`staging/FX_outline.md`, `FX_see_through.md`, `FX_depth_tint.md`, `FX_glare_glow.md`,
`FX_distance_blur.md`; logs `BT2-test/logs/vivo/20261112-*`; instrumentación `GLTIME`/`blit4/5/6`,
`BT2_GLTIME_FINISH`, `BT2_FXSEE`.

## Regresión del HUD y fix de 2 snapshots (2026-11-12, en curso)

- El build `29f4a10f` (DATE sin copia/scissor/aux vivo) arregló el FPS: el frame con **607 `blit5`** pasó de
  `loop 81 ms` a **`loop 8,3 ms`**, sin errores GL/FBO. Pero **el HUD dejó de actualizarse en tiempo real**:
  el camino `gsDateLiveAux`/scissor/reuso por rect dejó al HUD leyendo un alfa viejo.
- Propuesta del usuario: **1 o 2 actualizaciones del snapshot DATE por frame**, no 600. Es el punto medio:
  un snapshot full-frame 2×/frame cuesta ~2 copias (baratas con `glCopyImageSubData`) y el HUD se refresca a
  60 Hz.
- Fix en curso: `date_snapshot()` simple (sin live-aux/scissor): `native 5` full-frame como máximo **2 veces
  por target por frame**, reset por `gGsFrame`; `gsDateLiveAux = 0`. Se mantiene el resto del build de FPS.
- Verificación pendiente: pelea real con HUD/barras/anuncios actualizándose y `blit5 <= 2`.
- Fallback: `bt2.pre_noaux` (`f4b1f659`, coalescing con 610/81 ms) y las fuentes `*.pre_noaux`/`*.pre_datecap`.
