# Estado del port (2026-11-11)

Resumen público del estado de **BT2-Recomp**. El detalle línea por línea (bugs con causa, features con plan,
historial de builds) vive en el árbol de trabajo del proyecto; acá va lo que importa para probar y reportar.

> **WIP.** Es un port por recompilación + C nativo, no un decompilado completo. Hay bugs esperados, sobre todo
> en efectos, cámara y escenas poco jugadas.

## Qué anda hoy (probado jugando)

Menús, Dueling, Ultimate Battle, Dragon Adventure, peleas por equipos (5 vs 5), memory card, videos y audio.

- **Widescreen 16:9** por defecto (3D con FOV abierto; menús/HUD estirados al ancho). `BT2_ASPECT=4:3` vuelve
  al 4:3.
- **Autoguardado**: contesta sí a "¿guardar?" / "¿sobrescribir?" del juego.
- **Saltar intro**: saltea logos y opening (~2 min), sin tocar título, menú ni attract.
- **Multiidioma** con el disco PAL: textos + texturas de menú en ES/FR/DE/IT; las voces no se tocan.
- **Textos editables** (`bt2_texto.txt` / `textos/bt2_texto.<lang>.txt`).
- **Ventana de ajustes (F1)**: vídeo, efectos, audio, controles y cheats.
- **Renderers**: OpenGL 3.3 (por defecto), Vulkan (SDL3 GPU) y uno por software de referencia.
- **Ritmo**: 60 presentaciones/s en menús y combate. La grabación de vídeo (`BT2_RECORD`) es opt-in porque
  cuesta ~4,5 ms por cuadro.
- **Setup app (F7)**: `setup/build/bt2-setup` instala los datos desde tu ISO (GUI SDL3+ImGui y consola, lector
  ISO9660 propio, SHA-1, progreso, cancelar/retomar y botón Jugar). Ver `setup/ENTREGA.md`.

## Bugs abiertos / a confirmar

| id | qué | estado |
|----|-----|--------|
| B30 | GL: la niebla por profundidad del pase `dclut` usa mal la escala de z (y muestrea el depth adjunto al FBO) | abierto, con fix propuesto |
| B27 | Ultimate del Maestro Roshi | arreglado, falta confirmar jugando |
| B19 | UB 2.ª pelea: bloques de color / cámara lenta por el VU1 del agua | mitigado, falta confirmar |
| B22 | Freeze de ~10 s tras un Ultimate | arreglado, falta confirmar |
| ESC | Escape cierra el juego sin dejar motivo en el log | mejora pendiente |

Cerrados y confirmados el 2026-11-11: derribo trabado contra objeto irrompible (B31), Triangle cargado y R1 en
free roam (B32), pelea de equipo 5v5 (B12), cuerpo del rayo (B14), preview del Map Select (B15), retrato del
diálogo (B29), Piccolo (B28), autoguardado (F3), skip intro (F4), multiidioma (F8), widescreen (F2) y el drop
de FPS por la grabación.

## Pendiente de plataforma

- **F1**: niebla/fade en el borde del mundo (el salto de -300 es del original; falta que no se vea el corte).
- **F5**: entrada **C** del menú (ítem 11) como opción propia del port.
- **F9**: build de Windows (mingw-w64 cruzado; bloqueantes en `mem.c`).
- Reproducibilidad: PS2Recomp `2c5fbb9` + parches del kit, clang 23.x, SDL3/ffmpeg pinneados; los datos del
  juego no se versionan.

## Cómo reportar un bug

Sirve mucho:

1. El log del lanzador de pruebas (`logs/vivo/<fecha>.log`, y `.fight.log` si es en pelea).
2. Un **volcado F9** en el cuadro del problema (lista de dibujos + RAM).
3. Qué personaje/escenario/acción y si pasa también con el renderer por software (`BT3_GS=none`), que separa
   bugs de traducción del juego de bugs del renderer.

## Legal

El repositorio no incluye datos del juego. Código y documentación propios: **CC0 1.0**. *Dragon Ball Z:
Budokai Tenkaichi 2* y sus assets son de sus dueños; proyecto no oficial.
