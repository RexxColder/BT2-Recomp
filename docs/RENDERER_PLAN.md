# Etapa 5: renderer de BT2 = el de Tenkaichi3Decomp (preparación, 2026-10-13)

## Decisión: Vulkan por defecto (SDL3 GPU API), OpenGL 3.3 core de respaldo — como BT3
- Tenkaichi3Decomp ya trae las dos ramas sobre la MISMA lista de dibujo (`port/src/gs/gs_draw.c` graba el frame;
  `gs_gpu.c` = Vulkan vía SDL3 GPU, SPIR-V; `gs_gl.c` = GL 3.3 core, shaders traducidos del mismo GLSL en tiempo de
  ejecución). Se elige con `BT3_GPU_API=vulkan|gl|auto` (→ `BT2_GPU_API`). Ambas deben dar la misma imagen.
- Razones: Vulkan es la rama principal y más probada de BT3 (Linux, Windows; D3D12/Metal por SDL en otros); GL queda
  para máquinas sin Vulkan, VMs y depuración (RenderDoc anda en las dos). No escribir un renderer propio.
- Equipo del usuario: AMD RX 580 (RADV), Vulkan 1.4.354, OpenGL 4.6 (Mesa 26.2.4), `glslangValidator` instalado,
  SDL3 3.4.18 (64 bits: BT2 es x86-64, no hace falta lib32-sdl3 como en el BT3 de 32 bits).
- La build de prueba actual (híbrido PS2Recomp, raylib/GL) dibuja por software: ese camino se abandona.

## Hecho clave: el microcódigo VU1 de BT2 es idéntico al de BT3
`.vutext` de SLUS_214.41 (0x33B680, 0x3CD0 bytes) == `.vutext` de SLUS_216.78 (0x2BF6B0): 1946 de 1946 palabras de
64 bits iguales. Por lo tanto:
- el intérprete `gs_vu1.c` y la lista de instrucciones que soporta valen tal cual;
- los shaders que reemplazan programas VU1 (`shaders/vu0.vert`, `vu4.vert`, `vu6.vert`, `fx.vert`, `outline.frag`,
  `gs.vert/.frag`, `dclut.frag`, `alphakey.frag`) valen tal cual, porque reemplazan el mismo microcódigo;
- lo que puede diferir es lo que el C del juego le manda (formatos de paquetes/uniformes): el mismo motor sugiere
  que coincide; se verifica con capturas (`BT3_SHOT`) contra el render por software de referencia (`gs_core.c`).

## Qué hay que portar (de `~/Proyectos/Tenkaichi3Decomp/port/src/gs/`, ~8,5 k líneas)
| Archivo | Rol | Cambios esperables para BT2 |
|---|---|---|
| `gs_core.c` | GS de referencia por software + intérprete de cadenas DMA/VIF1/GIF | ninguno de lógica; entrada desde `port/full/plat_gs.c` (Port_DmaChcr ya existe en BT2) |
| `gs_vu1.c` | intérprete VU1 (microcódigo original) | ninguno (microcódigo idéntico) |
| `gs_draw.c/.h` | graba el frame, elige backend, efectos, escalas | `BT3_*` → `BT2_*`; ajustes (`Port_Setting`) |
| `gs_gpu.c` | Vulkan (SDL3 GPU) | ninguno salvo nombres; shaders a `shaders.h` con glslangValidator (`port/tools/undefined.py` de BT3 muestra cómo) |
| `gs_gl.c` | OpenGL 3.3 | ninguno salvo nombres |
| `gs_sony.c` | HLE de las funciones `sceGs*` del SDK (display, swap) | direcciones/nombres BT2 desde `build_port/bt3_names.csv` + firmas de `ps2-tool/sce_flat.txt` |
| `gs_input.c`, `ui.cpp` (Dear ImGui), `gs_texpack.c` | mando, ventana de ajustes F1, texturas PCSX2 | opcionales al principio; ImGui ya está en `Tenkaichi3Decomp/port/third_party` |
| `snd_adx.c`, `snd_se.c` | sonido (etapa 6) | después |

## Cableado (cuando bt2full llegue al título con el relleno)
1. Copiar `gs/` a `port/full/gs/` (MIT, del fork del usuario) + `shaders/`; generar `shaders.h` en `link_full.py`.
2. `plat_gs.c` de BT2: hoy descarta los DMA → entregarlos a `gs_core.c` (canal 1 VIF1 y 2 GIF), como `plat_gs.c` de BT3.
3. VSync: `sceGsSyncV` / handler de vblank → `GsGpu_FrameEnd` (presentar) + `gPortVBlanks`.
4. Modos: `BT2_GS=none` (headless, pruebas), `BT2_GS=1` (software de referencia, capturas), `BT2_GS=gpu` (ventana).
5. Verificación por capturas: logos y título en software vs Vulkan vs GL; luego el escenario del demo (personajes:
   VU1) — el bug "personajes invisibles" del híbrido debería desaparecer si era del runtime.
6. Velocidad: ghpc y BT3 midieron que el costo está en VU1 interpretado; los shaders vu0/vu4/vu6 ya sacan del
   intérprete los programas de modelos en BT3; medir qué programas usa BT2 (`gs_vu1.c` cuenta llamadas por dirección).

## Adelantado (2026-10-13, sin cablear todavía)
- `port/full/gs/`: copia del `port/src/gs/` de Tenkaichi3Decomp (MIT) + `shaders/`; `port/third_party/{xxhash,imgui}`.
- `port/tools/gen_shaders.py`: SPIR-V (glslangValidator) + GLSL embebidos → `port/build/full/gen/shaders.h` (18 arreglos).
- **Los 10 .c del renderer compilan para x86-64 sin cambios** (gcc, `port/build/full/gs_obj/`): gs_core, gs_vu1,
  gs_draw, gs_gpu (Vulkan), gs_gl (GL), gs_sony, gs_input, gs_texpack, snd_adx, snd_se. Falta `ui.cpp` (ImGui).
- Lo que el renderer necesita de la capa del port (hay que darlo en BT2): `Port_Setting/SettingSave/SettingsWrite`,
  `Port_AspectMilli/SetAspectMilli/IsWide` (→ `plat_settings.c` de BT3, copiado como `gs/plat_settings_bt3.c`),
  `Port_FilePath`, `Port_GsGifChannel`, `Port_AudioDevice/AudioRefresh`, `gPortVBlanks` (BT2 ya lo tiene),
  `gPortSleptNs`, `gPortMenuMode`, `gPortDataStripped`, `gPortMusicPercent/SePercent`, `Ui_*` (ui.cpp),
  y libm (`sin/cos/pow`). `Port_GetEnv` = getenv con prefijo: mapear `BT3_*` → `BT2_*`.
