# Rendimiento: por qué va a 15-22 fps (2026-10-12)

## Medición (no teoría)

Con `PS2X_FRAME_PROF=1` el present se descompone en sus tres partes:

```
[frame-prof] 0.6 fps | latch 1755.9 ms (n=2) | raylib 1.20 ms/frame
             | raster: 333 prim/s, 17.2 Mpix/s, texcache hit 100.0% (786 miss/s = 6 MB/s)
```

| Etapa | Costo | culpable |
|---|---|---|
| VSync del invitado | ~67 Hz | no |
| raylib (dibujar a la ventana) | **0.2 - 1.3 ms** | no |
| **`latch` (rasterizar el frame)** | **750 - 1800 ms** | **sí** |

Y el consumo por hilo (`top -H`) es inequívoco: **el hilo del GS se lleva 105.9 s de CPU al 100%**,
mientras los otros 8 hilos suman 2 s. La máquina está 68 % ociosa.

`latchHostPresentationFrame()` → `GSThreadedBackend::Present()` → `drain()`: el present **espera a que el
rasterizador por software termine la cola**.

## Qué se descartó

- **No es la GPU ni el vsync.** raylib dibuja a pantalla en ~1 ms. Se quitó además la doble espera de vsync
  (`FLAG_VSYNC_HINT` + `SetTargetFPS(60)`, ver `ps2_runtime.cpp`) y no cambió el número.
- **No es el bus de la imagen.** `TexturePageCache` está al **100 % de aciertos**, 786 fallos/s = 6 MB/s de
  `memcpy` de 8 KB: irrelevante.
- **No es lason's de bandas.** Con 12 núcleos hay 8 bandas configuradas, pero el worker del GS agarra un
  primitivo por vuelta (la cola llega de a uno), y `drawBanded` no parte nada por debajo de 8 primitivas.
  Forzar acumulación (esperar 200 µs a que se junten) **empeoró** (latch 1333 → 6800 ms): el lote crece y
  rasterizarlo de golpe cuesta más. Revertido.
- **El juego no dibuja triángulos, dibuja sprites**: el contador de triángulos daba 0 hasta que se
  instrumentó `DrawSprite`.

## La aritmética

- Carga real: **330 sprites/s**, **17 Mpix/s**, y **~30 M píxeles por frame mostrado** (unas 130 pantallas de
  overdraw).
- Para 60 fps hacen falta **~1.8 Gpix/s**.
- El rasterizador de software rinde **17 Mpix/s** en un core.
- **Faltan 100×.** Optimizar el rasterizador 10× sigue dejando 10× de轩diferencia; bajar la resolución a ¼ da
  68 fps pero son 128×112, injugable.

Conclusión: **la GPU no es una optimización, es la única forma de llegar a 60 fps.**

## El camino ya existe, a medias

`ps2xRuntime/include/runtime/gs/gs_gl_backend.h` **ya está escrito entero**: la clase `GSGlBackend` con el
diseño completo — `GLRecord` (grabación por primitiva, con la geometría ya resuelta a espacio de píxeles),
`buildRecord` / `supportedForGl`, replay en GPU, texturas con caché por clave, FBO que espeja el frame del GS,
shaders de blend/depth/alpha-test/fog/TEXA/TCC/TFX, y **fallback por primitiva al rasterizador de software
para los draws que GL no soporta**, preservando el orden.

Lo que falta:

1. **`src/lib/gs/gs_gl_backend.cpp` no existe.** Nunca se escribió la implementación.
2. **`makeDefaultRasterBackend()` en `gs_frontend.cpp` no lo instancia**: solo conoce `GSCpuBackend` y
   `GSThreadedBackend`, así que `PS2X_GS_GL=1` no hace nada.

O sea: el trabajo de diseño está hecho y hay que implementarlo. Es el mismo camino que siguió
Tenkaichi3Decomp (`gs_draw.c` + `gs_gl.c`), pero aquí el andamiaje ya existe.

## Instrumentación dejada (todo bajo variable de entorno)

| Variable | Qué |
|---|---|
| `PS2X_FRAME_PROF=1` | Descompone el frame en latch / raylib / raster, y agrega hit-rate del cache de texturas |
| `PS2X_GS_NOCACHE=1` | Lee texturas directo de VRAM (descarta el cache de 8 KB) |
| `PS2X_GS_GL=1` | (reservado) activa el backend OpenGL cuando exista el `.cpp` |

Contadores nuevos en `gs_cpu_backend.cpp`: `g_statTriangles`, `g_statPixels`; y en
`gs_texture_page_cache.h`: `g_pageHits`, `g_pageMisses`.