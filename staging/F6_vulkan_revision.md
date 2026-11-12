# F6 — Revisión del backend Vulkan (SDL3 GPU) de BT2-Port

Fecha: 2026-11-11. **Solo lectura**: no compilé, no ejecuté el juego, no toqué `/mnt/datos2/BT2-Decomp` ni ningún
archivo del port. Lo único escrito es este informe.

Archivos leídos:

- `BT2-Recomp/port/full/gs/gs_gpu.c` (1156 líneas, backend "Vulkan" = SDL3 GPU) — el del port.
- `BT2-Recomp/port/full/gs/gs_gl.c` (1255 líneas) — el de OpenGL, del **mismo** port (el que tuvo B24).
- `BT2-Recomp/port/full/gs/gs_draw.c`, `gs_draw.h`, `gs_internal.h`, `shaders/*`, `ui.cpp`, `gs_texpack.c`.
- T3D: `/tmp/opencode/t3d/port/src/gs/gs_gpu.c` (1271 líneas, commit `20a8655`, el mismo que usó
  `staging/F3F6_desde_tenkaichi3decomp.md`).

## Veredicto en una línea

**No hay un B24 en el backend Vulkan de BT2**: todo pase nativo corta el render pass y pone `cur = -1`, así que el
estado cacheado se resetea por construcción (`gs_gpu.c:838-842`). Lo que sí encontré es **una diferencia real y
continua entre GL y Vulkan en los pases de efecto que leen profundidad** (el dclut), **dos huecos de paridad de
herramientas** (grabación mp4 y sonda por dibujo existen solo en GL; el dump F9 no saca foto en Vulkan), **una
diferencia de un solo cuadro** (alfa del clear del target) y **una diferencia posible de clipping** (GL clampea z,
Vulkan no). Nada de eso es "parámetros de shader heredados".

---

## 1. Tabla de estado cacheado (pieza → ¿se resetea? → GL vs GPU → riesgo/síntoma)

Leyenda: "pase" = render pass nuevo; "corte" = el pase nativo termina el pass y hace `cur = -1`, lo que obliga a
abrir pase nuevo en el próximo dibujo común.

| Pieza de estado | Vulkan (`gs_gpu.c`) | GL (`gs_gl.c`) | Riesgo / síntoma |
|---|---|---|---|
| Pipeline (`lastPipe`) | Se resetea al abrir pase: **838-839**. Los 6 tipos de pase nativo terminan el pass y `cur=-1`: 667, 690, 710, 730, 753, 790. | `sCurPipe=-1` al inicio de cuadro (935) y al cambiar de target (1022); `set_native` lo invalida (667). `set_pipe` compara y reaplica (645-664). | **Ninguno análogo a B24.** El pipeline incluye blend, máscara, depth test/write/compare y topología en la clave (228-309), así que no puede quedar "el del pase anterior". |
| Uniform de fragmento (`Fu`: mode/misc/rect/orig) | `haveFu=0` al abrir pase: **841**. | `haveFu=0` al cambiar de target (**1021**) y **después de los dos pases que escriben `params`**: tabla (**994**) y efecto nativo (**1011**) — éste es el fix de B24. | En Vulkan el push de 16 bytes de un pase nativo (774, 807) no puede contaminar al siguiente primitivo porque hay pase nuevo en el medio. **Riesgo latente** solo si mañana se agrega un pase que dibuje sin cortar el pass: en ese caso hay que mantener la regla "o se corta el pass, o se invalida `haveFu`". |
| Uniform de vértice / VU (`lastUni`) | Se resetea en 839. Se sube si cambia el índice (853-855). | No cachea: sube siempre por dibujo VU (1029). | Seguro: el índice de `gsVuUni[]` es único por dibujo grabado (`gs_draw.c:980`, `:1020`, `:1075`) y la lista se resetea por cuadro (`gs_gpu.c:1130`). Descartado como bug. |
| Textura + sampler 0 (`lastTex`, `lastSampler`) | Se resetean en **839-840**. | `sCurTex0..2`/`sCurSamp0..1` a 0 al inicio de cuadro (937-938); `set_textures` compara y ata (698-719). | Sin fuga: al bindear 2 samplers (861-870) siempre incluye `sDateCopy` en el 1. |
| Scissor (`haveScissor`, `lastScissor`) | Se resetea en 841; los pases nativos 3/efecto lo fijan explícito (775, 809) y cortan el pass. | Reset al inicio (939), al cambiar target (1023) y tras los blits (956, 980); `set_scissor` compara (690-696). | Sin fuga. Ojo: **ningún backend clampea** el scissor al tamaño del target (`gs_draw.c:676-679`); ver §5.4. |
| Constante de blend (`lastBlend`) | Se resetea en **842**; `SetGPUBlendConstants` si cambia (881-885). | `lastBlendc=-1` al inicio (940); `glBlendColor` si cambia (995, 1041). | Sin fuga: el valor cacheado siempre describe lo que hay en el estado. |
| Vertex buffer (`bound`) | Se resetea al abrir pase (838) y se ata si cambia VU/GS (844-849). | No cachea (VAO por dibujo, 1028). | Sin fuga. |
| Target y pass (`cur`, `pass`) | `cur=-1` en todos los pases nativos; `pass=NULL` al terminarlos. | Ídem (958, 981, y `bind_target`). | Es la guarda real contra B24 en Vulkan. |
| Depth test/write/compare | No es estado suelto: va en la clave del pipeline (270-273) y en la creación del pass (`dt`, 829-836). Los pases nativos no llevan attachment de depth (282-291, y 763/798). | `set_pipe` aplica `glEnable(GL_DEPTH_TEST)`, `glDepthMask`, `glDepthFunc` (656-663); `set_native`/dclut lo apagan (656-658, 666-688). | Sin fuga de z entre pases. Ver §4 sobre la **limpieza** del depth. |
| Target de color/aux/depth y su `load_op` | Decide en el pass nuevo: 824-831, con `gsTargets[].cleared`. | `bind_target(target, !cleared)` (1018) + `gsTargets[].cleared=1` (1019). | Paridad 1:1. El clear sintético ocurre **una vez por vida del slot**, no por cuadro (ver §4). |

Conclusión del punto 1: **cada pieza que se cachea en Vulkan se resetea al empezar un pase o un blit, o no puede
quedar vieja porque el valor cacheado describe el estado real**. Los casos análogos a B24 (un push que no invalida
`haveFu`) **no existen** en el camino actual.

---

## 2. Bugs concretos encontrados

### 2.1 (REAL, continua, efectos) GL y Vulkan no leen la misma profundidad en el pase dclut

- Evidencia 1: el shader que usan **los dos** backends asume que la profundidad leída está en `[0,1]` con
  `0 = z 0` y `1 = z máximo` del GS:
  `shaders/dclut.frag:25-26` → `float z = texture(depthTex, vUv).r * u.p.y; idx = z >= 65448.0 ? 0 : clamp(255 - int(z / 256.0), 0, 255);`
  y `gs_draw.c:459` le pasa `p.y` = 65535 / 16777215 / 4294967295 según ZBITS, y `put()` (`gs_draw.c:683-690`)
  guarda `z = v->z / zmax`.
- Evidencia 2: **Vulkan** escribe ese valor tal cual (Vulkan mapea el clip z a `[0,1]`; el `gs.vert:10` NO toca z:
  `vec4(..., inPos.z, 1.0)`), o sea el depth texture contiene `z/zmax`. Correcto respecto del shader.
- Evidencia 3: **GL no**. El traductor de shaders antepone
  `gl_Position.z = clamp(gl_Position.z, 0.0, 1.0)` (`gs_gl.c:245`) y **no hay `glClipControl` ni `glDepthRangef`
  en todo el archivo** (grep vacío; contexto 3.3 core en `gs_gl.c:744-748`). Con el rango de profundidad por
  defecto de GL, lo que queda en el depth buffer es `z_win = (z_ndc + 1) / 2`, es decir `(z/zmax + 1)/2` en
  `[0.5, 1]`.
- Síntoma concreto: para 16 bits, Vulkan calcula `idx = 255 - z/256` y GL calcula
  `idx = 255 - ((z + 32768)/512) ≈ 127 - z/512`. Es decir, **en GL la tabla de 256 entradas se recorre con la
  mitad de pendiente y desplazada 128**, y el corte de "cerca" se corre apenas: se cumple para `z >= 65361` en GL
  contra `z >= 65448` en Vulkan. La niebla/tinte por profundidad (GfxDepthFog_Draw → `depth_clut` → `dclut.frag`,
  `src==0`) sale distinta entre backends.
- Agravante GL: el pase de tabla en GL muestrea `sTgDep[d->target]` **mientras ese mismo depth texture sigue
  adjunto al FBO actual como `GL_DEPTH_ATTACHMENT`** (`bind_target` en `gs_gl.c:721-735`; el pase nativo no bindea
  otro FBO: 984-989) → feedback loop, resultado indefinido por spec. En Vulkan ese pase **no tiene depth
  attachment** (`gs_gpu.c:282-291` crea el pipeline fx sin depth; el pass de 763 no pasa depth), así que Vulkan es
  el lado bien definido.
- **No es un bug a arreglar en Vulkan**: si se confirma con A/B (§6), el arreglo va en GL (`gs_gl.c:245`), y el
  diff está en §7.A. No lo apliqué.

### 2.2 (REAL, herramientas) en Vulkan no hay grabación de video: `BT2_RECORD` solo existe en GL

- `BT2_RECORD` / `BT2_RECORD_EVERY` (ffmpeg por pipe, el cuadro mostrado) están implementados **solo** en
  `gs_gl.c:1194-1218`. En `gs_gpu.c` no hay `popen` ni ffmpeg.
- `BT2-test/jugar.sh` **siempre** exporta `BT2_RECORD=...mp4` (línea del `exec env`), así que
  `./jugar.sh vulkan` corre sin video y el `.mp4` del log queda vacío/inexistente. Para A/B "GL vs Vulkan" con
  video, hoy solo sirve GL.
- Impacto: alto para diagnosticar efectos en movimiento (los `.mp4` de `logs/vivo` que usan los informes); nulo para el jugador.

### 2.3 (REAL, herramientas) `BT3_GS_DUMP` / F9 no saca foto en Vulkan

- GL: la descarga del cuadro se dispara también por el dump de F9:
  `gs_gl.c:1161` incluye `(gGsDumpFrame >= 0 && gGsFrame - gGsDumpFrame <= 1u)`.
- Vulkan: la condición de `BT3_SHOT` **no** incluye `gGsDumpFrame` (`gs_gpu.c:1073`), así que con F9 (o
  `BT3_GS_DUMP=<frame>`) se obtiene el listado de primitivas pero **ninguna imagen**. Para A/B hay que usar
  `BT3_SHOT_FROM/TO` (ver §6).
- Además `BT3_GL_WINSHOT` (`gs_gl.c:1125-1148`) no tiene equivalente Vulkan; el sustituto es
  `BT3_UI_SHOT=<frame>:<archivo.ppm>` (`gs_gpu.c:956-1031`), que saca **un** cuadro con la ventana de ImGui.

### 2.4 (REAL, herramientas) la sonda por dibujo (`BT3_PROBE_*`) es solo GL

- `probeOn()` y el `glReadPixels` antes/después de cada dibujo chico viven en `gs_gl.c:852-858` y `1043-1071`.
  `gs_core.c:1394-1397` acepta `BT3_GS_PROBE`, pero en Vulkan nadie lee ese pedido.
- Consecuencia para F6: la técnica que encontró B24 ("qué dibujo cambia qué píxeles") **no está disponible en
  Vulkan**. Alternativas en Vulkan: `BT3_GPU_CUT=<frame>:<n>` (`gs_gpu.c:522-532`), `BT3_GPU_TAIL=<frame>`
  (`533-548`), `BT3_SHOT_FROM/TO` (`1072-1075`) y `BT3_SHOT_AUX`.

### 2.5 (MENOR, un cuadro) el clear del target en Vulkan deja alfa 0; en GL alfa 1.0

- GL: `float col[4] = {0,0,0,1.0}` y `glClearBufferfv` en los dos attachments (`gs_gl.c:727-732`).
- Vulkan: `SDL_zero(ct)` y `cts[1] = ct`, `cts[0] = ct` (`gs_gpu.c:821-835`) → `clear_color = {0,0,0,0}`.
- Coincide en RGB y en el canal alfa del auxiliar (R8 = 0 en los dos). Difiere en el **alfa del target de color**.
- Impacto acotado: el clear sintético ocurre una sola vez por vida del slot (`cleared` se pone en 1 al crear el
  pass y **no se resetea por cuadro**; sólo se resetea al crear el slot, `gs_draw.c:413`), y las zonas afectadas
  son píxeles que ningún dibujo tocó (RGB negro). Puede notarse solo si un efecto (a) muestrea ese target
  (`mode.x==2`) o (b) mezcla por `DST_ALPHA` (ALPHA 0x54, "el desenfoque de las cosas lejanas",
  `gs_draw.c:584-585`) justo en el borde de un buffer de trabajo recién creado. Por eso lo dejo como *diferencia a
  verificar*, no como bug confirmado.

### 2.6 (MENOR / posible) GL clampea el clip z y Vulkan deja que el clipper descarte

- `gs_gl.c:245` hace `clamp(gl_Position.z, 0.0, 1.0)`. Los shaders de programa VU no clampean:
  `vu4.vert:25` y `vu6.vert:28` escriben `s.z / u.misc.z` con `w = s.w`; el de programa 0 sí clampea
  (`vu0.vert:38`), lo que sugiere que el caso existe.
- En Vulkan un vértice con `0 > z > w` o `z > w` **se recorta** (parte del triángulo desaparece); en GL se
  "aplasta" al plano cercano/lejano. Diferencia esperable: triángulos del escenario/sombra que cruzan el far plane.
- No lo puedo confirmar sin datos (no corrí nada). Chequeo barato: en un build de prueba, agregar el mismo
  `clamp` al `.z` de los shaders SPIR-V y ver si el cuadro vulkan cambia (si no cambia, descartado).

### 2.7 (NIT) chequeos de NULL que T3D tiene y BT2 no

- `gs_gpu.c` de T3D valida `sDev == NULL` (1146, 1186, 1214) y `cmd == NULL` (1228).
- BT2 no chequea `SDL_AcquireGPUCommandBuffer` en `vk_frame_end` (`gs_gpu.c:550`) ni `sDclutFs` después de crearlo
  (`467`; si falla, el pipeline fx queda NULL y `SDL_BindGPUGraphicsPipeline` recibe NULL). No es visual; es
  robustez. El caso "no hay Vulkan" sí termina bien: `vk_init` devuelve 0 y `GsGpu_Init` deja `sBackend = NULL`
  → el renderer por software toma el control (`gs_core.c:1456`).

---

## 3. Comparación con T3D: qué guardas tiene T3D que a BT2 le falten

**En la máquina de estado por pase: ninguna.** El bucle de replay es prácticamente el mismo archivo:

| Pieza | T3D (`port/src/gs/gs_gpu.c`) | BT2 (`port/full/gs/gs_gpu.c`) |
|---|---|---|
| Reset al abrir pase | 819-847, resets en 843-846 | 815-843, resets en 838-842 (idéntico) |
| Corte de pass en blit de película | 691 (`cur=-1`) | 667 (`cur=-1`) |
| Corte en copia de alfa (native 5/4) | 714 / 734 | 710 / 730 |
| Corte en pase de tabla | 757 | 753 |
| Corte en efecto nativo (outline/key) | 794 | 790 |
| Copia de target a sí mismo | **no existe** | native 6, 683-702 (propio de BT2) |
| Draws VU | indexados (`sVuIbuf`, 848-858, 902-903) | arrays expandidos, `DrawGPUPrimitives` (892) |
| Present | simple en px del swapchain (918-945) | fix Wayland (916-945) — **no regresar** |
| Chequeos NULL | `sDev`/`cmd` (1146, 1186, 1214, 1228) | ausentes (550, 467) |
| `native == 6` (radar) | no | sí (`sSelfCopy`, 41, 683-702) |
| `targetRead`/`targetCopy` (+ blit fuera del frame) | 1141-1202 | no (BT2 usa native 6) |
| `vk_idle_frame` (pantalla de conexión) | 1204-1250 | no (BT2 tiene `net_screen.c`) |

Lo único "de guarda" que T3D tiene de más es el chequeo de NULL del command buffer/device (§2.7). Las demás
diferencias son features (T3D tiene de más) o features propias de BT2 que hay que conservar (native 6, `zcolour`,
`drawn`, `fbw`, present Wayland).

`native 6` en BT2 **sí corta el pass** (686-690 `pass=NULL`, 690 `cur=-1`), así que tampoco introduce un B24. El
`zcolour` se limpia al final del cuadro en los dos backends (gpu 1132, gl 1231).

---

## 4. Targets, `fbp` y "native pass": ¿se limpia/escribe depth? ¿se arrastra el z?

- **Los pases nativos (3, 4, 5, 6, ≥100, efecto) NO llevan depth attachment**: el pipeline fx se crea con
  `has_depth_stencil_target = false` y `enable_depth_test/write = false` (`gs_gpu.c:282-291`), y los passes de
  763/798 no pasan `SDL_GPUDepthStencilTargetInfo`. El outline/key tienen su propio pipeline de 1 target sin depth
  (429-461). O sea: **no hay estado de z que se arrastre desde un pase nativo**.
- El attachment de depth solo existe en los passes comunes y su `load_op` es `LOAD` si el target ya fue "limpiado"
  (`gs_gpu.c:830`), igual que GL (`bind_target(target, !cleared)`, 1018). El clear de depth (a 0.0, como GL:
  `gs_gl.c:727-732`) ocurre **una vez por vida del slot**, no por cuadro: `cleared` no se resetea por cuadro
  (solo al crear el slot, `gs_draw.c:413`). En la práctica el que limpia cada cuadro es el juego, con sus propios
  dibujos de clear (que sí escriben depth). **Es idéntico en los dos backends**, así que no es un bug de Vulkan;
  sí es un riesgo compartido: si un cuadro nuevo no cubre una zona que el anterior sí cubrió, esa zona conserva
  el z viejo y un dibujo con z-test puede quedar rechazado. No tengo evidencia de que pase.
- `native 6` (self-copy): exige `cleared` (691), copia **todo** el target (`GS_W*SCALE`, `GS_H*SCALE`) y corta el
  pass; el registro solo inserta la copia si algo se dibujó en ese target desde la última (gs_draw.c:593-604). En
  split-screen la copia es del target entero, igual en GL (`glBlitFramebuffer` 0..GS_W/GS_H).
- Blit de película (`native >= 100`, 661-682): `load_op = DONT_CARE` (descarta el contenido anterior, que es lo
  buscado), no toca el aux ni el depth, y marca `cleared=1` (679). GL hace lo mismo con `glDrawBuffers(1, one)`
  (953) para no pisar el aux. Paridad.
- `fbp`: los dos backends indexan la tabla compartida y usan `sTgCol/sTgAux/sTgDep[i]`; no hay nada específico de
  Vulkan. El "radar" (`zcolour`, fbp == zbp) usa un target propio y su depth separado en ambos; la diferencia con
  la PS2 (donde el color vive en la memoria del z-buffer) es de diseño, no de backend.

---

## 5. Áreas puntuales del pedido

### 5.1 PSMT4/PSMT8 con CLUT (los efectos)

El decode es **CPU y compartido**: `gs_draw.c:227-235` (`bits==8` reordena bits 3/4 y lee `Gs_ClutRead(cbp,cpsm,c&15,c>>4)`;
`bits==4` idem con 16 entradas) y sube RGBA8 por `texCreate/texUpload`. **No hay nada específico de Vulkan**
salvo el upload (`gs_gpu.c:153-167` vs `gs_gl.c` `tex_upload`: RGBA8 empaquetado, mismos bytes) y el sampler
(índice de `gs_draw`, misma tabla `sSamplers[16]` en ambos). La tabla del dclut es una textura 256x1 RGBA
(`gs_draw.c:325-330`) y el shader la lee con `texelFetch` (`dclut.frag:32`) — igual en los dos.

Lo que **sí** es un riesgo conocido y **no** es de Vulkan (ya anotado en `docs/bugs_open.md:321`): el CLUT se lee
como 16x16 (CSM1) y `CSA` se ignora; las texturas de los efectos (tbp 2b00/2b10, PSMT4/8 con alfa 0x00..0x16 del
informe de las chispas) dependen de eso. Comparar GL vs Vulkan **no** lo va a revelar: hay que comparar contra el
renderer por software (`jugar_software.sh`) o contra el original.

Para packs DDS/BC: el upload de Vulkan pasa `bytes` al transfer buffer y deja que SDL calcule el pitch; usa
`SDL_GPUTextureSupportsFormat` antes de crear (137-139) y gs_draw cae a `gsWhite` si `texCreate` devuelve 0
(`gs_draw.c:250-259`). Mismo comportamiento observable que GL.

### 5.2 Alpha/blend del GS (0x80 = opaco)

`blend_from_key` (`gs_gpu.c:203-223`) es una traducción línea por línea de `apply_blend` (`gs_gl.c:605-624`):
mismos `k[]`, mismo `C` (SRC_ALPHA / DST_ALPHA / CONSTANT_COLOR), mismo `SUBTRACT`/`REVERSE_SUBTRACT`, alfa con
`ONE/ZERO` (el frame buffer guarda el alfa tal cual), y el auxiliar sin blend y con máscara solo de alfa
(`gs_gpu.c:275-277` ≡ `glColorMaski(1, A,0,0,0)`, `gs_gl.c:629`). `GS_CC_*` (`gs_draw.h:124-127`: 1,2,4,8) coincide
con `SDL_GPU_COLORCOMPONENT_*` (1,2,4,8). La escala 1.0 = 0x80 está en el shader (`gs.frag:73-79`,
`a = vColor.a * 255/128`), compartido. **No encontré diferencias funcionales de blend.**
Lo único distinto es el alfa del clear (§2.5).

### 5.3 Present (letterbox/pillarbox, `gUiPresent*`)

- GL: viewport en píxeles del drawable con `(sw,sh)` de `SDL_GetWindowSizeInPixels` (1080-1099), y
  `gUiPresent*` = ese rectángulo (1112-1115).
- Vulkan: blit del rect 512×448 del target al swapchain; el rect se calcula en **píxeles de ventana** y se mapea
  proporcionalmente al swapchain (916-945), y `gUiPresent*` = el rect resultante (951-954). Es el fix de Wayland
  documentado en `docs/PORT_LOG.md:681-685`; **no regresar**.
- `Ui_Draw` (Vulkan) y `Ui_DrawGL` mapean los nombres de escenario/canción por `gUiPresent*` (`ui.cpp:622-646`), y
  el disco de autoguardado por `gUiPresent*` (`ui.cpp:564-586`). Ahí hay un detalle **compartido** (no Vulkan):
  `autosave_disk()` usa `sc = gUiPresentW/512` para **x e y** (`ui.cpp:571-576`) aunque el buffer 512×448 se
  muestra con píxeles no cuadrados (`sy = gUiPresentH/448`); el disco queda corrido en vertical en cualquier
  aspecto (en 4:3, ~17 %; en 16:9, más). En Vulkan y en GL por igual.
- `gUiPresent*` se llenan **solo** si se adquirió swapchain y hay target (`gs_gpu.c:906`): en un cuadro sin
  adquisición (ventana minimizada) ImGui usa el rect viejo; en GL `Ui_DrawGL` se llama siempre (1124). Diferencia
  menor de un cuadro.
- HiDPI: `gUiPresent*` está en **píxeles** (swapchain) y se usa como coordenadas de ImGui, que trabaja en unidades
  de `DisplaySize` (lógicas) × `FramebufferScale`; con escala 2.0 los overlays quedarían al doble de distancia y
  tamaño. Compartido GL/Vulkan; no lo pude verificar (no corrí). Anotado como sospecha, no como bug.

### 5.4 Scissor y target

`gs_draw.c:676-679` calcula `w/h` como `(x1+1)*SCALE - x0` sin clamps. Si el juego alguna vez manda `x1 < x0`
(scissor vacío), GL trata el ancho negativo como error y conserva el scissor anterior; Vulkan recibiría un `Uint32`
enorme y podría pintar de más. No encontré evidencia de que el juego lo haga y no lo puedo verificar sin datos;
lo dejo como sospecha menor (compartida en el origen, distinta en el síntoma).

---

## 6. Plan de prueba A/B GL vs Vulkan

### 6.1 Preparación

- Correr **con display real** (KDE Wayland o X11). Bajo xvfb Vulkan no presenta (sin DRI3),
  `docs/PORT_LOG.md:686`; las capturas por `BT3_SHOT` sí funcionan porque leen el target, no la ventana.
- Usar `BT2-test/jugar.sh gl` y `./jugar.sh vulkan` (el script ya setea `BT3_GS=gpu` + `BT3_GPU_API`), o a mano
  `env BT3_GS=gpu BT3_GPU_API=vulkan bin/bt2`.
- **No compartir** el archivo de pipelines entre las dos corridas: `BT3_PIPELINES=/tmp/pipes_gl.txt` vs
  `/tmp/pipes_vk.txt` (mismo formato de clave, pero así el contador `%d pipelines` es comparable y no se mezclan
  corridas).
- Guion determinista de entrada: `BT3_PAD="frame:boton,..."` (cada pulsación dura 4 cuadros, `gs_input.c:180-198`);
  mismo guion para las dos corridas. Para 2P: `BT3_PAD2`.
- Para forzar el mismo estado sin jugar: un save/estado cargado igual en las dos corridas y el mismo guion.

### 6.2 Capturas

En las **dos** ramas (mismo cuadro, mismo `BT3_SCALE`, ideal `BT3_SCALE=2`):

```
BT3_GS_VERBOSE=1
BT3_SHOT=1 BT3_SHOT_FROM=<F> BT3_SHOT_TO=<F>      # port/build/shots/gpu_0000F.ppm (512*SCALE x 448*SCALE)
BT3_SHOT_AUX=1                                     # el mismo cuadro con el canal de alfa (ids)
```

- `BT3_SHOT` está implementado en los dos backends (GL 1155-1189, Vulkan 1054-1124) y es la vía recomendada.
- `BT3_GL_WINSHOT` no tiene Vulkan; para la ventana completa usar `BT3_UI_SHOT=<F>:<salida.ppm>` (solo Vulkan,
  un cuadro).
- `BT2_RECORD` **solo GL** (§2.2); para video en Vulkan hoy no hay.

### 6.3 Escenas y qué mirar (en orden de valor para F6)

1. **Pelea con niebla/tinte por profundidad** (estadio con neblina; el pase dclut `src==0`). Mirar el gradiente de
   la niebla/velo: si GL y Vulkan difieren en intensidad y "altura" del corte, es §2.1. Cuadros: los del comienzo
   de la pelea y uno con la cámara lejos.
2. **Kamehameha / aura** (cadena de glare/glow: buffer de trabajo → reducción → blur → suma con ALPHA 0x68/0x54).
   Mirar el borde del halo contra el fondo y su forma cerca de los bordes de pantalla (ahí el `DST_ALPHA` y el alfa
   del clear del buffer de trabajo, §2.5, pueden cambiar). Usar `BT3_GLOW=100` para exagerar.
3. **Radar visible** (native 6 + `zcolour`): el disco y las flechas deben ser idénticos; si en Vulkan el disco
   sale negro o con la imagen vieja, mirar `native 6` (683-702) y el orden de las copias.
4. **Pantalla partida 2P** (scissor): las dos mitades no deben mezclarse; comparar `BT3_GPU_TAIL` de un cuadro y
   las dos capturas. Ahí también se ve el bug del scissor de §5.4 si existe.
5. **Menú principal / selección** (2D + CLUT + blend): textos, barras, iconos. Si difieren, **no** es Vulkan
   (decode compartido, §5.1) sino el estado de blend/scissor; comparar contra `jugar_software.sh`.
6. **Película / fade** (`native>=100`): la imagen del video y el fade encima. Ver que en Vulkan no quede el
   contenido anterior (DONT_CARE) ni el aux pisado.
7. **Present**: ventana 4:3 y 16:9 (widescreen), redimensionar y fullscreen. Comparar las líneas
   `vk: present ...` y `gl: present ...` de `BT3_GS_VERBOSE` (mismo `window/pixels/swapchain/aspect -> picture
   WxH at (x,y)`); el rectángulo debe ser el mismo salvo 1 px por redondeo. Repetir en Wayland y X11.
8. **HiDPI** (si hay monitor 2x): mirar el F1 y los nombres de escenario/canción (§5.3).

### 6.4 Lectura de los logs

- `gpu: frame N: D draws, V vertices, T targets, X textures, P pipelines, S dropped, E native effects`
  (`gs_gpu.c:517-521`, `gs_gl.c:884-888`): **D/V/T/X/S/E deben coincidir** entre backends cuadro a cuadro; si no,
  el problema está en la grabación (`gs_draw.c`), no en el backend. `S`/`E` y la segunda línea `dropped by site`
  (los dos backends la imprimen: `gs_gpu.c:520`, `gs_gl.c:887`) sirven para ver si un pase nativo se está salteando.
- `time: of ending the frame: ...` (solo Vulkan, 1045-1048) para descartar que una diferencia sea de sincronía.
- Ante un píxel distinto: `BT3_GPU_CUT=<frame>:<n>` (mismo cuadro en las dos ramas, recortando la lista de dibujos)
  para bisecar el dibujo culpable; `BT3_GPU_TAIL=<frame>` para ver los últimos 14 dibujos y sus claves.
- Recordar que la sonda por dibujo (`BT3_PROBE_*`) **no existe en Vulkan** (§2.4).

---

## 7. Cambios propuestos (NO aplicados)

### 7.A — GL: que el depth buffer de GL guarde el mismo valor que Vulkan (arregla §2.1)

Solo si el A/B del §6.3.1 confirma la diferencia. El lado "correcto" respecto del shader es Vulkan.

```diff
--- a/BT2-Recomp/port/full/gs/gs_gl.c
+++ b/BT2-Recomp/port/full/gs/gs_gl.c
@@ -242,7 +242,10 @@ static char *translate(const char *src, int is_vertex) {
-        PUSH("\nvoid main() { gs_main(); gl_Position.y = -gl_Position.y; gl_Position.z = clamp(gl_Position.z, 0.0, 1.0); }\n");
+        /* GL mapea el clip z (-1..1) al rango de profundidad 0..1: para que el depth buffer guarde z/zmax (lo que
+           asume dclut.frag, y lo que guarda Vulkan) hay que pasar de [0,1] a [-1,1]. El clamp se mantiene para
+           no cambiar el clipping de los triángulos que ya se veían bien. */
+        PUSH("\nvoid main() { gs_main(); gl_Position.y = -gl_Position.y; gl_Position.z = clamp(gl_Position.z, 0.0, 1.0) * 2.0 - 1.0; }\n");
```

Riesgo: el orden del z-test no cambia (la transformación es monótona y el clear sigue en 0.0); mejora la
precisión (hoy sólo usa la mitad del rango del float). Verificar: misma pelea, `BT3_SHOT` frame a frame, y que no
aparezcan objetos recortados por el near plane. **No lo apliqué.**

### 7.B — Vulkan: alfa del clear del target igual a GL (arregla §2.5, un cuadro por slot)

```diff
--- a/BT2-Recomp/port/full/gs/gs_gpu.c
+++ b/BT2-Recomp/port/full/gs/gs_gpu.c
@@ -833,6 +833,7 @@ static void vk_frame_end(void) {
             gsTargets[d->target].cleared = 1;
             cts[0] = ct;
+            cts[0].clear_color.a = 1.0f; /* como el clear de GL (gs_gl.c: col[4] = {0,0,0,1}) */
             pass = SDL_BeginGPURenderPass(cmd, cts, 2, &dt);
```

(Escribirlo **después** de `cts[0] = ct` para no tocar el clear del auxiliar, que es R8 y usa sólo `.r`.)
Ningún efecto sobre la presentación normal; sólo el primer cuadro tras crear/reciclar un target.

### 7.C — Vulkan: que F9/`BT3_GS_DUMP` saque foto (paridad con GL, §2.3)

```diff
--- a/BT2-Recomp/port/full/gs/gs_gpu.c
+++ b/BT2-Recomp/port/full/gs/gs_gpu.c
@@ -1070,7 +1070,9 @@ static void vk_frame_end(void) {
         /* BT3_SHOT_FROM / BT3_SHOT_TO limit the frames */
-        if (every > 0 && gGsFrame % (unsigned)every == 0 && best >= 0 && gsTargets[best].cleared &&
+        if (((every > 0 && gGsFrame % (unsigned)every == 0) ||
+             (gGsDumpFrame >= 0 && gGsFrame - (unsigned)gGsDumpFrame <= 1u)) &&
+            best >= 0 && gsTargets[best].cleared &&
             (getenv("BT3_SHOT_FROM") == NULL || (int)gGsFrame >= atoi(getenv("BT3_SHOT_FROM"))) &&
```

(`gGsDumpFrame` ya está declarado `extern int` en `gs_core.c:58`; en `gs_gl.c:1160` se declara local. Falta la
misma declaración acá.)

### 7.D — Vulkan: `BT2_RECORD` (mp4) — no es un diff de una línea

Hace falta descargar el target mostrado por cuadro (como `BT3_SHOT`) a un pipe de ffmpeg. Se puede copiar casi
tal cual el bloque de `gs_gl.c:1194-1218` usando `SDL_DownloadFromGPUTexture` + fence (patrón ya presente en
`gs_gpu.c:1076-1122`). **No lo propongo aplicar ahora**: es una feature de herramientas, no un arreglo visual.

---

## 8. Lo que descarté (y por qué)

| Hipótesis | Evidencia de descarte |
|---|---|
| B24 (parámetros de shader heredados entre pases) en Vulkan | Todo pase nativo termina el pass y pone `cur=-1` (667, 690, 710, 730, 753, 790) → pase nuevo → `haveFu=0`/`lastFu` inválido (841). El push de 16 bytes del pase de tabla (774) y del efecto (807) no puede llegar al siguiente dibujo común. |
| Uniform VU cacheado por índice pero con contenido distinto | `d.uniform = gsVuUniCount++` por dibujo grabado, único dentro del cuadro (`gs_draw.c:980/1020/1075`), y el contador se resetea por cuadro (`gs_gpu.c:1130`). Además GL no cachea (sube siempre). |
| Scissor/textura/pipeline heredados de un pase nativo | Se resetean en 838-842 y los pases nativos cortan el pass; GL hace lo equivalente (1021-1023 y `haveFu=0` en 994/1011). |
| El blend de Vulkan difiere del de GL | `blend_from_key` (203-223) ≡ `apply_blend` (605-624), mismo mapeo de factores/ecuaciones y mismo alfa `ONE/ZERO`; `GS_CC_*` = bits de SDL. |
| El pase de tabla (`native 3`) puede dejar z raro | No tiene depth attachment (`pipeline_create` fx, 282-291; pass de 763 sin depth) y el pipeline fx apaga depth test/write. |
| El present de Vulkan muestra al revés o mal el letterbox | Vulkan: rect fuente (0,0)-(512,448) con fila 0 = arriba (SDL/Vulkan) y blit SIN flip → correcto; GL: FBO con la escena guardada al revés (`gs_gl.c:245` invierte `y`) y present que invierte `v` (`gs_gl.c` `make_present_program`: `vUv.y = (1-p.y)/2`), también correcto. |
| Falta de reset en el cambio de resolución (`scale_changed`) deja basura | `scale_apply` vacía la tabla: `gsTargetCount = 0` (`gs_draw.c:1133`) → todos los slots se recrean con `cleared=0` (`gs_draw.c:413`), que fuerza clear en el primer pase. |
| Texturas PSMT4/8 con CLUT se decodifican distinto por backend | El decode es CPU y único (`gs_draw.c:227-235`); solo cambia el upload, con los mismos bytes. |
| Una textura pendiente puede liberarse antes de subirse | El barrido de `MAX_TEX` conserva lo usado en el cuadro (`gs_draw.c:177-205`); y `texSlotsLeft()` corta antes de crear (`gs_draw.c:177`). |
| El depth queda cargado de un pase nativo | Esos passes no bindean depth; el `load_op` del pass común es LOAD/CLEAR según `cleared` (830) igual que GL (1018). |

---

## 9. Resumen de severidades

| # | Qué | Backend | Severidad | Confirmado con datos |
|---|---|---|---|---|
| 2.1 | GL y Vulkan leen profundidades en escalas distintas (dclut/fog) | GL (Vulkan es el correcto) | **Alta** para efectos de profundidad | Sí, por spec + código; falta A/B visual |
| 2.2 | `BT2_RECORD` (mp4) solo en GL | Vulkan | Media (herramientas) | Sí (grep) |
| 2.3 | F9/`BT3_GS_DUMP` sin foto en Vulkan | Vulkan | Media (herramientas) | Sí (código) |
| 2.4 | Sonda por dibujo solo en GL | Vulkan | Media (herramientas) | Sí (código) |
| 2.5 | Alfa 0 vs 1 en el clear del target | Vulkan | Baja (1 cuadro/slot) | Sí (código) |
| 2.6 | GL clampea z; Vulkan recorta | Ambos | Baja/posible | No (hipótesis) |
| 2.7 | Chequeos de NULL ausentes | Vulkan | NIT | Sí (código) |
| 5.3 | Disco de autosave con `sc` de ancho para x e y | Ambos | Baja (F3) | Sí (código) |

## 10. Sin verificar

- Nada de esto se probó corriendo el juego (era solo lectura). El punto 2.1 es el único con impacto visual
  esperable y necesita el A/B del §6.3.1 para confirmarse en pantalla.
- El punto 2.5 depende de que algún efecto lea el alfa de un buffer recién creado; no lo pude medir.
- El punto 2.6 depende de que los programas VU4/VU6 produzcan `z/w` fuera de `[0,1]`; sin log de vértices no lo sé.
- El punto 5.3 (HiDPI) no lo pude verificar sin un display con escala ≠ 1.
