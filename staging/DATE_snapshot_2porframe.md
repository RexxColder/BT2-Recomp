# DATE: dos snapshots full-frame por target y frame (2026-11-12)

## Síntoma
El build `29f4a10f` arregló el FPS (`blit5` 607 → 0, `loop 8.3 ms`) con `gsDateLiveAux = 1` (el DATE lee el
alfa vivo del target sin copia) y, antes de eso, con snapshots `native 5` por rectángulo reusados. El HUD dejó
de actualizarse en tiempo real: barras, medidores y anuncios mostraban el alfa del cuadro anterior.

## Arreglo
- `port/full/gs/gs_gl.c`: `gsDateLiveAux = 0` en `gl_init` (queda inactivo el FBO no-aux, como estaba previsto).
- `port/full/gs/gs_draw.c` `date_snapshot`: se eliminó el reuso por rectángulo (`rect_holds`/`rect_touches`).
  Ahora, por target, se crea un snapshot `native 5` **full-frame** (`scissor = 0,0,GS_PIC_W*SCALE,GS_PIC_H*SCALE`)
  en el primer DATE del cuadro y otro en el segundo; del tercero en adelante todos reusan la última copia.
  El contador se resetea con `sDateFrame != gGsFrame` (independiente de los resets de `gsDrawCount` de cada backend).
- El `glCopyImageSubData`/blit y el gate `native 4`/efectos no se tocaron.

Costo: ~2 copias full-frame por target y cuadro (en la demo: `blit5 2`, `loop 6.4-8.1 ms`). El HUD se actualiza
una vez por cuadro (60 Hz), no una vez por frame de copia vieja.

## Prueba de humo (offscreen, demo CPU vs CPU)
`BT2_DEMO=1 BT3_GS=gpu BT3_GPU_API=gl BT2_GLTIME=1 BT2_GLTIME_FINISH=1` → `blit5 2`, `blit4 1` (contorno),
`loop 6.4-8.1 ms`, `battle finished (2113 vsyncs)`. No verifica el HUD: eso lo prueba el usuario en pelea real.
