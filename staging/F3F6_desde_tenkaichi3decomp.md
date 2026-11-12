# F3F6 — Qué tomar de Tenkaichi3Decomp (T3D) para BT2

Fecha: 2026-11-11. Investigación de solo lectura sobre el código de T3D. No compilé BT2, no ejecuté juegos y no
toqué `/mnt/datos2/BT2-Decomp`. Lo único escrito es este informe.

## 0. Repo clonado

- URL: `https://github.com/RexxColder/Tenkaichi3Decomp` (fork de un proyecto BT3-Decompiled; el fork existe y es
  público).
- Clonado en `/tmp/opencode/t3d`, rama `main`.
- Commit real clonado: **`20a8655ad3d3d0481a26ddf0b60c4114dc147683`** (`Discord Rich Presence, in the settings
  window`, 2026-10-10). El commit `6ae9ef3` que citaban los docs **no existe en este repo**; con `git fetch
  --unshallow` se trajeron 530 commits y tampoco aparece. El informe se basa en el `main` actual.
- El proyecto está completo en C (decompilado matching) + una capa `port/` con renderer propio. No hay backend
  Vulkan "a mano": usa **SDL3 GPU API** (`SDL_GPUDevice`), que por debajo es Vulkan en Linux/Android y D3D12/Metal
  en otras plataformas (`port/src/gs/gs_gpu.c:1-2`). El backend OpenGL 3.3 es `port/src/gs/gs_gl.c`.

---

## 1. Autoguardado (autosave)

### 1.1 Cómo lo hace T3D

La idea central: **no agrega puntos de guardado nuevos ni un formato propio**. El juego ya pregunta "Save game
data?" al final de un capítulo y en algunos otros lugares; el port contesta "sí" por el jugador.

- `port/src/plat_autosave.c` (34 líneas):
  - `Port_Autosave()` (`:18-27`) lee `BT3_AUTOSAVE`; si no está, lee el setting persistente `autosave`
    (`Port_Setting("autosave", 1)`, default **encendido**).
  - `Port_AutosaveSet()` (`:30-34`) cambia el valor en caliente y lo guarda con `Port_SettingSave` +
    `Port_SettingsWrite` (archivo `bt3_settings.txt`, ver `port/src/plat_settings.c:1-12`).
- Enganche en la máquina de estados del juego, `src/sys/mcflow_a.c`:
  - declaración `extern int Port_Autosave(void);` en `:112-115`.
  - estado `0xC` (pregunta normal de guardado), `:271-287`: si `Port_Autosave()` y `choice == 0`, escribe
    `choice = 1` y `timer = 0xC`, exactamente lo que haría un "Yes". El flujo sigue por el mismo camino, con su
    espera de 12 frames y el cartel "Auto Saving" (mensajes 0xA / 0x10 del juego).
  - estado `0xD` ("Save data already exists. Overwrite?"), `:426-436`: la misma sustitución de respuesta.
  - El estado `0xE` se deja **sin** autoguardar a propósito: es el error "cambiaron la memory card" y el estado 3
    vuelve a él si el chequeo falla; contestarlo solo produciría un bucle 3 → 0xE → 3 (comentario en `:358-363`).
  - Ojo: el comentario de `plat_autosave.c:6` dice "three small `#ifdef PORT` branches", pero en el código hay
    **dos** (`0xC` y `0xD`). El tercero no existe en este commit.
- Puntos reales de guardado: los que ya dispara el juego, sobre todo `McFlow_Start(0)` / modo `MCFLOW_MODE_SAVE`
  (`src/sys/mcflow_a.c:2697-2706`) y el modo 4 (`:2723-2729`). El autosave **no** inicia un guardado por tiempo,
  por cambio de pantalla ni por checkpoint; solo evita el diálogo cuando el juego ya decidió guardar.
- Formato: el save del juego, **0x4000 bytes crudos** (`SaveData`), con checksum en los primeros 8 bytes. Se
  escribe con `McCard_WriteSave(0, gSaveData, 0x4000, ...)` (`src/sys/mcflow_a.c:486`) y la capa de memory card
  lo guarda en la carpeta `saves/card1/BASLUS-21678DBZT3/` (`port/src/plat_mc.c:1-20`, `BT3_SAVES` para cambiar
  la raíz, `:66`). Es el **mismo formato que una memory card de PS2**, no un archivo propio del port.
- Cómo evita corromper:
  - Antes de escribir, el flujo del juego recalcula el checksum (`McCard_Checksum(gSaveData, 0x4000, 1)` en
    `McFlow_Start`, `src/sys/mcflow_a.c:2705` y `:2728`; algoritmo en `src/battle/stgm_a_b.c:934-964`).
  - Al cargar, verifica el checksum (`src/sys/mcflow_a.c:796`, `:1107`).
  - No hay escritura atómica: `sceMcWrite` del HLE hace `fwrite` + `fflush` directo sobre el archivo final
    (`port/src/plat_mc.c:188-200`), sin `.tmp` + `rename` ni backup. Si el proceso muere a mitad de escritura, el
    archivo puede quedar truncado; el checksum lo detectaría **salvo** por el bug original del juego: la
    verificación usa `&&` en vez de `||` (`src/battle/stgm_a_b.c:961-962`), así que solo rechaza el save si
    **los dos** bytes del checksum están mal. El mismo bug existe en BT2 (`port/eq/28A6D8.c:38-40`).
  - Conclusión: T3D evita corromper **por usar el flujo y el checksum del juego**, no por una protección nueva de
    escritura. Es un punto a mejorar en BT2, no algo que T3D ya resuelva.

### 1.2 Qué se puede reusar tal cual

- `port/src/plat_autosave.c` es prácticamente copiable: solo hay que renombrar `BT3_` → `BT2_` y el setting.
- El patrón de enganche (contestar `choice` como un "Yes", no saltarse la escritura) es directamente aplicable.
- La idea de dejar el estado de error de card sin autoguardar es importante y hay que conservarla.

### 1.3 Qué hay que adaptar en BT2

- BT2 **sí tiene** la máquina de estados del diálogo de guardado decompilada: `port/eq/3E51F8.c` (636 líneas,
  `func_003E51F8`, "memory-card save/load dialog state machine"). No es la misma máquina que `mcflow_a.c` de T3D,
  pero el enganche es equivalente: buscar el estado que muestra la pregunta de guardado y el de "overwrite", y
  sustituir `ANSWER`/`TIMER` como en T3D.
  - Candidatos por lectura: estado `13` (`MSG = 4`, `:218`) y estados `27` / `28` (`MSG = 24` / `37`, `:484`,
    `:506`). Hay que confirmar contra el texto en pantalla o el recurso cuál es "Save game data?" y cuál
    "Overwrite?"; no lo pude determinar sin ejecutar el juego.
  - El estado 20 (`:368-382`) es el que llama a `McCard_WriteSave(0, D_00387F2C, 0x4000, BUF_END)`. Ese es el
    punto real de escritura, y no hay que tocarlo.
- El save de BT2 usa el mismo HLE adaptado de T3D (`port/full/plat_mc.c`, `$BT2_SAVES`, `saves/card1`), así que
  el formato y la carpeta ya son compatibles.
- BT2 **no tiene** todavía un `Port_Autosave` ni el setting. Hay que agregarlo a `port/full/` (o al archivo de
  settings que use BT2) y a `port/full/gs/ui.cpp` (pestaña Controls, como T3D en `ui.cpp:1086-1097`).
- Cuidado con los punteros: en BT2 el código del juego usa punteros de 32 bits y la RAM de PS2 está mapeada en la
  dirección 0. Cualquier `getenv()` debe hacerse en la capa del port y exponerse como global/int, nunca
  devolverse como puntero de 64 bits al código del juego. T3D ya aplica esta regla, por ejemplo en
  `port/src/headless.c:217-221` (`Port_NetMenuListed`).

### 1.4 Riesgo / esfuerzo

- Riesgo bajo: no cambia el formato, no cambia la escritura, solo evita diálogos.
- Esfuerzo: ~30 líneas de port + encontrar los 2 estados correctos en `3E51F8.c` + un checkbox en la UI.
- Recomendación extra para BT2: agregar escritura atómica (`.tmp` + `rename`) en `sceMcClose` o al terminar
  `McCard_WriteSave`, y un `.bak` del save anterior. Es barato y cubre el agujero que T3D deja.

---

## 2. Saltar intro (skip intro / opening)

### 2.1 Hallazgo: T3D **no** tiene una feature de skip intro como setting

Busqué `skip`, `intro`, `opening`, `logo`, `movie` en todo el repo, en `port/src`, `src`, `docs` y en el historial
completo (530 commits). **No hay** un `Port_SkipIntro`, un setting `skip_intro`, ni una opción en la ventana F1
para saltear logos u opening. Lo que existe es el comportamiento **nativo del juego**, que T3D no modificó:

- Logos de arranque: `src/menu/menu_i_c.c:45-119` (`Logo_Show` / `Logo_ShowAll`). Son 6 imágenes de 120 frames
  cada una; las primeras 5 usan `LOGO_SKIP_ANY` (START o CROSS las corta en cualquier momento) y la última
  `LOGO_SKIP_NONE`. `FirstRun_Main` (`:163-186`) las muestra siempre, después del chequeo de memory card.
- Opening: `src/sys/movie.c:249-300` (`Movie_PlayOpening` / `Movie_Run`). `START` (`MOVIE_SKIP_BUTTON`, definido
  en `include/sys/movie.h:36`) hace fade-out y corta; no hay un salto automático por tiempo ni por setting.
- Intro hablada del título: `src/menu/menu_a_c.c:206-215`, `Title_Input`; START dispara `fl_skip`.
- El único "skip" automático del port es `BT3_NOMOVIE` (`port/src/plat_movie.c:49`): si está definido, el HLE de
  películas termina al instante. No es un setting persistente y no saltea los logos; además la sesión online lo
  pone en 1 (`port/src/gs/net.c:978`, `:989`).

Es decir: **T3D no resolvió "saltar intro"**; dejó el skip manual del juego y, para películas, un env var.

### 2.2 Qué se puede reusar tal cual

- Nada de código. El concepto útil es el punto de enganche: `FirstRun_Main` es el lugar donde se muestran logos +
  card + opening; `Movie_PlayOpening` es el punto exacto para el opening.
- En BT2 ya existe un equivalente para películas: `port/full/plat_movie.c:12-13` documenta
  `BT2_SKIP_MOVIES=1` (las películas terminan al instante). Eso ya cubre el opening y los videos; **lo que falta
  en BT2 son los logos**, que se dibujan desde el overlay recompilado.

### 2.3 Qué hay que adaptar en BT2

- Agregar un setting persistente, por ejemplo `skip_intro` en `bt2_settings.txt`, y un env `BT2_SKIP_INTRO` que
  gane por una corrida.
- Para el opening: usar el mecanismo que ya existe (`BT2_SKIP_MOVIES`) o hacer que `mwPlyGetStat` devuelva 3
  (fin) cuando el setting esté encendido. No hace falta tocar el reproductor.
- Para los logos: el problema es que en BT2 el overlay (`DBZP.BIN`, `Progress_Main` en 0x3B7FA8) corre
  recompilado o por fallback (`port/full/temp_stubs.c:48-57`), no en C como T3D. Opciones, de menor a mayor
  riesgo:
  1. HLE del chequeo de memory card + un "salto" de los frames de logos desde la capa del port. Requiere saber
     cuándo empieza y termina `Logo_ShowAll`; se puede detectar por estado del overlay o por contador de vblanks,
     pero es frágil.
  2. Decompilar/portar a C la función de logos de BT2 (equivalente a `Logo_Show` / `FirstRun_Main`) y ahí poner
     el `if (Port_SkipIntro()) return;`. Es la opción limpia, pero es trabajo de decomp.
  3. Parchear el C recompilado del overlay (si se identifica la función y el punto de llamada). Es la más
     quirúrgica, pero hay que mantener el parche contra el recompilador.
- Criterio recomendado: setting persistente + `BT2_SKIP_INTRO`; si está encendido, saltar **logos + opening**,
  no el chequeo de memory card (el save debe cargarse igual). Si se quiere conservar la primera ejecución, usar
  un flag en el save o en el settings, no el `MPROG_FIRST_RUN` (ese flag es por arranque, no persistente:
  `src/menu/menu_a_b.c:68-70`).

### 2.4 Riesgo / esfuerzo

- Riesgo medio: tocar el arranque puede romper el orden de carga de particiones, la detección de pad o el
  chequeo de card.
- Esfuerzo: bajo para el opening (reusar `BT2_SKIP_MOVIES`), medio/alto para los logos (overlay recompilado).
- Si se implementa, probar con: save existente, sin save, card vacía, y con mando desconectado (el juego espera
  pad en `FirstRun_WaitPad`).

---

## 3. Nueva entrada de menú / pantalla propia del port

T3D tiene **dos mecanismos distintos**, y conviene no confundirlos.

### 3.1 Ventana de settings con Dear ImGui (F1 / START+SELECT)

Es la pantalla propia del port, superpuesta al juego. No es un ítem del menú del juego.

- `port/src/gs/ui.cpp:1-4`: "The settings window of the PC build: Dear ImGui over the finished picture. F1 opens
  and closes it, or START + SELECT of a controller".
- Apertura/cierre:
  - `Ui_Toggle()` en `port/src/gs/ui.cpp:676-680`.
  - `PortInput_Hotkey()` en `port/src/gs/gs_input.c:108-143`: tecla `sOverlayKey` (default `F1`), botón de pad
    configurable, y combo START+SELECT con latch para que no abra y cierre en el mismo evento.
  - La tecla/botón se guardan en settings (`key_overlay` / `pad_overlay`, `gs_input.c:96-97`, `:161-162`).
  - `gPortOverlayOpen` y `gPortInputCapture` (`port/src/gs/gs_input.c:22`) bloquean teclado y pad del juego
    mientras la ventana está abierta (`:409`, `:422`).
- Enganche con el renderer:
  - Vulkan/SDL_GPU: `port/src/gs/gs_gpu.c:497-512` lee eventos, llama `PortInput_Hotkey` → `Ui_Toggle`, y
    `Ui_Event` para la ventana; al final del frame `Ui_Draw(cmd, swap)` (`:950`).
  - OpenGL: `port/src/gs/gs_gl.c:765-766` (eventos), `:1018` y `:1148` (`Ui_DrawGL`).
  - `Ui_Init` se llama desde `gs_gpu.c:472` y `gs_gl.c:730`; `Ui_Draw`/`Ui_DrawGL` en `ui.cpp:1409-1418`.
- Contenido: pestañas Video / Effects / Audio / Controls / Misc (`ui.cpp:1043-1118`). El autosave está en
  Controls (`:1086-1097`). La ventana también dibuja overlays de nombres de stages/songs agregados
  (`ui.cpp:1270-1407`) y la pantalla de online (`net_open`, `ui.cpp:484-674`).
- Persistencia: `Port_Setting` / `Port_SettingSave` / `Port_SettingsWrite` en `port/src/plat_settings.c`
  (`bt3_settings.txt` o `$BT3_SETTINGS`).

### 3.2 Entrada nueva en el menú del juego: "Dragon Net Battle"

T3D no agregó un ítem artificial: usó un ítem **que ya existe oculto en el disco de PS2**, el ítem 4 del menú
principal, y lo hace visible. Es el acceso a la pantalla online del port.

- Lista del menú: `src/menu/menu_a.c:139-159`. El original salta `i == 4`; el port lo lista si
  `Port_NetMenuListed()` devuelve 1 (por defecto sí; `BT3_MENU_ITEM4=0` lo oculta para reproducir grabaciones
  viejas).
- `Port_NetMenuListed()` está en la capa del port, `port/src/headless.c:217-221`, **a propósito**: `getenv`
  devuelve un puntero de 64 bits y el código del juego lo truncaría a 32. Es un detalle clave para BT2.
- Al confirmar el ítem 4: `src/menu/menu_a.c:434-460`, caso `4`, llama `Port_NetMenuOpen()` (implementado en
  `headless.c:213-216`), que solo setea `gPortNetMenuRequest = 1`; el menú del juego sigue donde está.
- El renderer ve el pedido en `ui.cpp:1270-1278` (`frame_build`): si `gPortNetMenuRequest`, lo limpia y llama
  `net_open()`, que abre la ventana ImGui del online. Es un **hook por global + polling en el hilo del renderer**,
  no un hook de función del juego.
- El ítem 4 tiene placa, etiqueta, icono y voces en el disco; no hubo que crear arte. La pantalla en sí es ImGui.

### 3.3 Bonus: ítems agregados a listas existentes (stages y songs)

No es una entrada de menú nueva, pero es el otro enganche que T3D usa para contenido del port:

- `src/menu/menu_c_e.c:536-607`: después de que el juego aplica los unlocks del save, el port **agrega** ids de
  stages externos (`gPortExtraStages`, `gPortExtraStageCount`) a la lista del stage select, copia la lista a un
  buffer propio, rellena la última fila con celdas "empty" y ajusta `stageRows`. No toca el save.
- `src/menu/menu_c_e.c:627-650`: lo mismo para las canciones (`gPortSongCount`, `gPortSongOffsets`), dejando
  "random" al final.
- `src/menu/menu_c_e.c:890-914` y `:996-1008`: publican el rectángulo y el índice del nombre para que `ui.cpp`
  dibuje el nombre con arte del port (`gUiNameX/Y/W/H/Idx/Ready`).
- Los archivos se sirven por alias desde `port/src/plat_stages.c` / `plat_songs.c` y `port/src/plat_file.c:54-57`.
- En BT2 esto es mucho más difícil: el stage select/menú está en el overlay recompilado, no en C. No es el
  camino recomendado para la primera entrada de menú.

### 3.4 Qué se puede reusar tal cual en BT2

- BT2 **ya tiene** una ventana ImGui (`port/full/gs/ui.cpp`, 602 líneas, F1 hardcodeado en
  `port/full/gs/gs_gpu.c:501-502` y `port/full/gs/gs_gl.c:877`). Agregar una pestaña o un checkbox es barato y
  de bajo riesgo.
- El patrón de T3D de "global de pedido + polling en el renderer" es directamente aplicable a BT2 para abrir una
  pantalla propia desde cualquier lado.
- El patrón de settings persistentes (`Port_Setting`/`Port_SettingSave`) ya existe en BT2.

### 3.5 Qué hay que adaptar

- Para una pantalla propia: copiar el estilo y la estructura de `ui.cpp` de T3D no hace falta; alcanza con
  agregar una pestaña a `port/full/gs/ui.cpp`. Si se quiere el hotkey configurable + START+SELECT, portar
  `PortInput_Hotkey` de T3D necesita engancharse en el event loop de BT2 (`gs_gpu.c`/`gs_gl.c`) y en
  `port/full/gs/gs_input.c`; BT2 hoy solo mira F1 a mano.
- Para un ítem en el menú del juego: **no hay hook limpio** en BT2 porque el overlay no está en C. Opciones:
  1. Usar solo ImGui (F1) y dejarlo fuera del menú del juego. Es lo que recomiendo para la primera iteración.
  2. Si se quiere el ítem 4 o uno nuevo, hay que decompilar/portar `MainMenu_Init` / `MainMenu_Input` de BT2, o
     parchear el C recompilado. Es un trabajo de decomp, no de port.
- Respetar la regla de punteros: cualquier `getenv` para decidir si se lista el ítem va en `port/full/`, no en el
  código del juego.

### 3.6 Riesgo / esfuerzo

- Pestaña/checkbox ImGui: riesgo bajo, ~1-2 h.
- Pantalla propia nueva (tipo online): riesgo bajo/medio, ~1 día si se reusa el event loop y el estilo.
- Ítem nuevo en el menú del juego: riesgo alto, esfuerzo de decomp; no lo pondría en la primera etapa.

---

## 4. Vulkan: estado por pase, uniforms y el bug B24

### 4.1 Arquitectura real

T3D no tiene un backend Vulkan propio: `port/src/gs/gs_gpu.c` usa **SDL3 GPU** (`SDL_GPUDevice`,
`SDL_GPUGraphicsPipeline`, `SDL_PushGPUFragmentUniformData`, etc.). El archivo se llama "Vulkan" porque en Linux
SDL3 GPU usa Vulkan. BT2 copió la misma arquitectura: `port/full/gs/gs_gpu.c` también es SDL3 GPU. Por eso el
patrón de estado es casi idéntico.

### 4.2 Qué cachea T3D por pase

En `vk_frame_end` (`port/src/gs/gs_gpu.c:490-915`):

- `lastPipe`, `lastUni`, `lastSampler`, `lastTex`, `haveFu`, `haveScissor`, `lastBlend` (`:493-497`).
- Uniforms de vértice (programas VU): `gsVuUni[d->uniform]` se sube solo si cambió `d->uniform`
  (`:863-866`). En T3D las draws VU son **indexadas** (`sVuIbuf`, `SDL_BindGPUIndexBuffer` en `:849-858` y
  `SDL_DrawGPUIndexedPrimitives` en `:903`); BT2 usa arrays expandidos, sin índice.
- Uniforms de fragmento (`Params`: `mode`, `misc`, `rect`, `orig`): se comparan con `memcmp` contra `lastFu` y
  solo se hace `SDL_PushGPUFragmentUniformData` si cambiaron (`:879-892`).
- Pipeline: solo si cambió el índice (`:867-870`).
- Textura/sampler: solo si cambiaron (`:871-879`).
- Scissor: solo si cambió (`:893-901`).
- Blend constant: solo si cambió (`:880-886`).
- Al empezar un render pass nuevo (`d->target != cur`, `:819-847`), resetea **todo**: `lastPipe = lastUni =
  lastSampler = -1`, `lastTex = NULL`, `haveFu = haveScissor = 0`, `lastBlend = -1`.
- El shader declara `layout(set = 3, binding = 0) uniform Params` (`port/src/gs/shaders/gs.frag:10`) y el pipeline
  se crea con `num_uniform_buffers = 1` para el fragment shader (`gs_gpu.c:371`).

### 4.3 ¿T3D comparte el bug B24 en Vulkan?

**No en el camino actual, por construcción, no por una guarda explícita.**

- B24 en BT2/GL fue: un pase nativo llama `set_params(params, 16)` sobre el mismo UBO y no invalida `lastFu`; el
  siguiente primitivo con los mismos parámetros se saltea el upload y el shader lee los números del pase nativo
  (documentado en `docs/bugs_open.md:1144-1155`; arreglo `haveFu = 0` en `port/full/gs/gs_gl.c:991-994`,
  `:1011`, `:1021`).
- En T3D Vulkan, los pases nativos (`d->native == 3`, `d->native`) **siempre** terminan el render pass, ponen
  `pass = NULL` y `cur = -1` (`gs_gpu.c:747-816`, en particular `cur = -1` en `:757` y `:794`). El siguiente
  primitivo entra por `d->target != cur`, abre un render pass nuevo y resetea `haveFu = 0` (`:845`). Por eso el
  push del pase nativo no puede contaminar al primitivo siguiente: hay un pass nuevo en el medio.
- El backend GL de T3D **sí** necesita la guarda explícita y la tiene: `port/src/gs/gs_gl.c:891`
  (`haveFu = 0` tras el pase de tabla), `:908` (tras pase nativo) y `:918` (tras cambiar de target). Es
  exactamente el mismo arreglo que BT2 ya tiene en `port/full/gs/gs_gl.c:991-994`, `:1011`, `:1021`.
- El riesgo latente en Vulkan existe si en el futuro se agrega un pase nativo que **no** corte el render pass o
  que dibuje primitivos dentro del mismo pass después de un push de `params`: ahí `haveFu` mentiría. La
  documentación de SDL3 dice que `SDL_PushGPUFragmentUniformData` aplica a **los draws siguientes del command
  buffer**, no a un draw puntual; el cache es correcto solo porque cada pass nuevo lo invalida.
- En BT2 Vulkan pasa lo mismo: los pases nativos (`native 3`, `native`, `native 5/4/6`) terminan el pass y ponen
  `cur = -1` (`port/full/gs/gs_gpu.c:743-812`, `:723-740`). El `native 6` (self-copy) es exclusivo de BT2 y
  también corta el pass. Por eso B24 no se reprodujo en Vulkan; el bug era del GL.

### 4.4 Diferencias concretas entre el backend de T3D y `port/full/gs/gs_gpu.c` de BT2

| Tema | T3D (`port/src/gs/gs_gpu.c`) | BT2 (`port/full/gs/gs_gpu.c`) | Qué mirar |
|---|---|---|---|
| Base | SDL3 GPU | SDL3 GPU | Igual. |
| Draws VU | Indexadas: `gsVuIdx`, `sVuIbuf`, `SDL_DrawGPUIndexedPrimitives` (`:46`, `:590-604`, `:849-858`, `:903`) | Arrays expandidos: `sVuVbuf`, `SDL_DrawGPUPrimitives` | Si se porta el cambio de T3D, hay que tocar también `gs_draw.c`/`gs_draw.h` (semántica de `first/count`). No es necesario para las 4 features. |
| Pase nativo 6 (self-sampling) | **No existe** en T3D | **Sí**: `sSelfCopy`, `native == 6` (`:41`, `:683-704`), `GsBackend.selfCopy` (`gs_draw.h:147`) | Es de BT2 (radar/self-target). No pisarlo al cherry-pickear. |
| `GsTarget` | Sin `zcolour`, `drawn`, `fbw` | Con `zcolour`, `drawn`, `fbw` (`gs_draw.h:54-63`) | BT2 los usa para radar/underwater; conservarlos. |
| Lectura de targets | `targetRead`, `targetCopy` en `GsBackend` (`gs_draw.h:151-152`) | No existen; usa `selfCopy` (`gs_draw.h:147`) | T3D los agregó para in-between/cross-fade; no son parte de estas 4 features. |
| Frame idle | `idleFrame` en `GsBackend` (`gs_draw.h:137-139`) | No existe | T3D lo usa para la pantalla de conexión; BT2 tiene su propio net screen. |
| Título / Discord | `GsGpu_TitlePoll()` al inicio del frame (`:497`) | No | No es renderer puro; no hace falta. |
| Hotkey de settings | `PortInput_Hotkey` configurable + START+SELECT (`:506`) | F1 hardcodeado (`:501-502`), F9/F10 dumps (`:511-512`) | Si se porta la ventana configurable, cambiar el event loop. |
| Present | Cálculo simple `w/h` centrado (`:928-945`) | Cálculo con tamaño de ventana en píxeles para Wayland (`gs_gpu.c:918-945` en BT2) | **No regresar** el fix de Wayland de BT2. |
| Caché de uniforms | Mismo `lastFu/haveFu`, reset en pass nuevo | Igual | Correcto en ambos; mantener el reset. |
| Pases nativos | `cur = -1` + fin de pass | Igual | Es la guarda real contra B24 en Vulkan. |
| Pipeline cache | `bt3_pipelines.txt`, 1024 pipelines, claves de 23 bits | Igual (`bt3_pipelines.txt`) | Si se comparte el archivo entre BT2/BT3, las claves podrían colisionar; usar nombre propio. |

### 4.5 Qué revisar primero en BT2

1. Confirmar que **todo** pase nativo de BT2 termina el render pass y pone `cur = -1` (incluido `native 6` y los
   `native >= 100` de movies). Si alguno dibuja dentro del pass actual, agregarle `haveFu = 0` explícito o
   cortar el pass.
2. No copiar el backend de T3D entero: BT2 tiene features propias (`native 6`, `zcolour`, `drawn`, `fbw`,
   present Wayland). Un reemplazo limpio las perdería.
3. Si se quiere el rendimiento de T3D, portar **solo** el cambio de VU indexado como tarea aparte, con su cambio
   de `gs_draw.c` y pruebas de replay; no mezclarlo con autosave/menú.
4. Para el bug B24, la lección es la guarda de GL; en Vulkan alcanza con mantener el corte de pass. Si se agrega
   un efecto nativo nuevo, la regla debe quedar escrita en el código: *después de pushear `Params` para un pase
   especial, invalidar `haveFu` o cortar el pass*.

---

## 5. `Port_WideFactor` de T3D (widescreen)

### 5.1 Dónde está y qué factor aplica

- `port/src/plat_stub.c:396-398`:

```c
float Port_WideFactor(void) {
    return Port_IsWide() && !gPortMenuMode ? (float)Port_AspectMilli() * 3.0f / 4000.0f : 1.0f;
}
```

- `Port_IsWide()` es `Port_AspectMilli() > 1340` (`:389-391`). `Port_AspectMilli()` devuelve el aspecto en
  milésimas (`1333` = 4:3, `1778` = 16:9, `2389` = 21:9, etc.) y se puede cambiar en caliente desde F1
  (`:349-384`, `Port_SetAspectMilli` en `:386-388`).
- Factor resultante: **1.0 en 4:3 y en menús**; **1.3335 en 16:9**; **1.79175 en 21:9**. Es exactamente
  `aspect / 1333.333` (el recíproco de `1333.333/aspect`).
- `gPortMenuMode` se pone en 1 alrededor de la llamada real a `Progress_Main` (`port/src/headless.c:145-147`),
  así que en los menús el factor es 1 y no se ensancha nada.

### 5.2 Dónde se aplica

- Proyección: `src/battle/btl_cam.c:139-143`, `View_SetProjection` multiplica **`aspectY`** por el factor antes
  de la normalización que hace que el factor mayor sea 1. Al 16:9, `aspectY` pasa de 1.1667 a 1.5556 y la
  normalización deja `aspectX = 0.6429` (= 0.8571 × 0.75): mismo FOV horizontal que multiplicar `aspectX` por
  0.75, pero expresado del otro lado.
- Cambio en caliente: `View_UpdateMatrices` (`btl_cam.c:170-193`) recalcula `aspectX/aspectY` y rebuilda la
  proyección si el aspecto cambió durante la partida.
- Culling / frustum: `src/battle/stg_a.c:386-387` (planos laterales) y `:403-404` (`left`/`right`). Sin esto, el
  nuevo FOV se ve pero el culling sigue cortando como 4:3.
- Efectos: `src/battle/eft_a.c:1376` y `:1800`, `eft_b.c:319`, `eft_w.c:772`, `eft_x.c:631`. Usan
  `1.1666667f * Port_WideFactor()` o `0.75f / Port_WideFactor()` para que las proporciones de los efectos
  acompañen.
- 2D: `port/src/gs/gs_draw.c:830-894`. Si `Port_IsWide() && !gPortMenuMode`, cada pieza 2D se angosta por
  `narrow = 1333.333f / Port_AspectMilli()` (`:869`) alrededor de un pivote (izquierda/derecha/centro según
  `gsAnchor`). Los menús no se angostan: se muestran enteros y estirados al ancho.

### 5.3 Contraste con BT2 hoy

- BT2 ya tiene el equivalente en `port/eq/25B688.c:42`:

```c
if (Port_IsWide()) {
    *(f32 *)(v0 + 0x228) *= 1333.333f / (float)Port_AspectMilli();
}
```

  Es decir, multiplica `aspectX` después de la normalización. Para el par estándar (`aspectX=1`,
  `aspectY=view->aspect`) el resultado es **idéntico** al de T3D: 0.75 en 16:9.
- Diferencias actuales:
  1. BT2 **solo** toca la proyección. No toca culling (`StgFrustum` / planos laterales) ni el aspect de los
     efectos, porque esas funciones siguen en el código recompilado/asm. En BT2 el 3D se ve más ancho, pero el
     culling y algunos efectos pueden seguir calculando con 4:3.
  2. BT2 **no** distingue menús: `gPortMenuMode` existe (`port/full/plat_gs.c:221`) pero el comentario dice "el
     juego aun no lo marca" y nadie lo setea. Si se aplica el factor siempre, las cámaras 3D de los menús también
     se ensanchan.
  3. BT2 tiene el narrowing 2D **apagado por defecto** (`BT2_NARROW_2D`, `port/full/gs/gs_draw.c:852-864`):
     el usuario pidió en F2b que todo el 2D se estire al aspecto. Eso es una decisión de producto distinta de
     T3D, que sí angosta el 2D de la pelea. No es un bug, pero hay que decidirlo antes de "portar" el resto.
- Lo que sí conviene tomar de T3D:
  - Aplicar el factor también a los planos de culling y al aspect de los efectos, si se quiere un widescreen
    correcto en los bordes (hoy en BT2 puede aparecer geometría cortada o efectos desalineados).
  - Distinguir menús con un flag equivalente a `gPortMenuMode`, si se puede enganchar alrededor de la llamada a
    `Progress_Main` en BT2 (el `wrap` de T3D no existe igual en BT2; habría que buscar el punto de llamada del
    overlay recompilado).
  - Mantener el rebuild de proyección en caliente: BT2 hoy cambia el aspecto con F1 pero la proyección se arma
    al iniciar la escena (`staging/F2_widescreen.md:227`), así que un cambio en mitad de una pelea no se aplica
    hasta la próxima. T3D lo resuelve en `View_UpdateMatrices`; en BT2 habría que hacerlo en el equivalente
    `port/eq/25...` o en el wrapper de la vista.

### 5.4 Riesgo / esfuerzo

- Bajo para la proyección (ya está).
- Medio para culling/efectos: hay que identificar las funciones equivalentes en `port/eq` o parchear el
  recompilado; validar con capturas en los bordes.
- Bajo para el flag de menús si se encuentra el hook; medio si hay que tocar el overlay.

---

## 6. Lo que NO encontré

- **Skip intro como feature del port**: no existe en T3D. Solo está el skip manual nativo (START/CROSS en logos,
  START en opening/películas y en la intro del título) y `BT3_NOMOVIE` para películas. No hay setting persistente.
- **Autosave con archivo propio o formato propio**: no. Usa el save de memory card del juego y el mismo flujo.
- **Escritura atómica / backup del save**: no. `sceMcWrite` escribe directo sobre el archivo final; el checksum
  del juego es la única validación, y tiene el bug del `&&`.
- **Backend Vulkan escrito a mano**: no. Es SDL3 GPU; no hay `gs_vulkan.c` ni `VkDevice` propio.
- **Entrada de menú creada desde cero**: no. T3D reusa el ítem 4 oculto del menú de PS2 y lo hace visible; la
  pantalla que abre es ImGui, no una pantalla del juego.
- **`Port_WideFactor` en BT2**: no existe con ese nombre; el equivalente es el `1333.333/aspect` de
  `port/eq/25B688.c`.
- **Commit `6ae9ef3`**: no está en el repo clonado (ni en la historia completa). El análisis es sobre `20a8655`.

---

## 7. Orden recomendado de implementación en BT2

1. **Autosave** (mayor valor / menor riesgo): portar `plat_autosave.c` + enganchar los estados 13 y 27/28 de
   `port/eq/3E51F8.c` + checkbox en `port/full/gs/ui.cpp`. Antes de cerrar, agregar escritura atómica
   (`.tmp` + `rename`) y backup del save, porque T3D no lo trae.
2. **Settings/menú propio**: si se quiere una entrada visible, empezar por una pestaña o ventana ImGui en
   `port/full/gs/ui.cpp` (costo bajo). Dejar el ítem en el menú del juego para después: en BT2 el overlay no está
   en C y el costo es de decomp.
3. **Widescreen completo**: mantener la proyección actual y sumar culling/efectos/menús. Validar con capturas en
   4:3, 16:9 y 21:9, y en split-screen.
4. **Skip intro**: primero el opening (reusar `BT2_SKIP_MOVIES`), después los logos (requiere tocar el arranque
   recompilado o decompilar `FirstRun_Main`/`Logo_Show`). No mezclarlo con autosave.
5. **Vulkan**: no hay una feature que portar para estas 4; solo auditoría. Revisar que cada pase nativo corte el
   render pass / invalide `haveFu`, y no reemplazar el backend de BT2 por el de T3D (perdería `native 6`,
   `zcolour`, `drawn`, `fbw` y el present de Wayland). Si se busca rendimiento, el cambio de VU indexado de T3D
   es una tarea aparte, con pruebas de replay.

---

### Referencias rápidas (T3D)

| Tema | Archivo:línea |
|---|---|
| Autosave setting | `port/src/plat_autosave.c:18-34` |
| Autosave en el flujo | `src/sys/mcflow_a.c:271-287`, `:426-436` |
| Escritura del save | `src/sys/mcflow_a.c:486`; `src/battle/stgm_a_b.c:385-...` |
| Checksum | `src/battle/stgm_a_b.c:934-964` |
| Memory card HLE | `port/src/plat_mc.c:1-20`, `:66`, `:188-200` |
| Logos / opening nativos | `src/menu/menu_i_c.c:45-119`, `:163-186`; `src/sys/movie.c:249-300` |
| Ventana ImGui F1 | `port/src/gs/ui.cpp:1-4`, `:676-680`, `:1043-1118`, `:1409-1418` |
| Hotkey F1 / START+SELECT | `port/src/gs/gs_input.c:108-143` |
| Enganche del menú del juego | `src/menu/menu_a.c:139-159`, `:434-460`; `port/src/headless.c:213-221` |
| Pedido de pantalla online | `port/src/gs/ui.cpp:1270-1278` |
| Stages/songs agregados | `src/menu/menu_c_e.c:536-607`, `:627-650`, `:890-914` |
| Vulkan: cache por pase | `port/src/gs/gs_gpu.c:490-915` |
| Vulkan: reset de pass | `port/src/gs/gs_gpu.c:819-847` |
| GL: guarda B24 | `port/src/gs/gs_gl.c:891`, `:908`, `:918` |
| `Port_WideFactor` | `port/src/plat_stub.c:396-398` |
| Wide en proyección | `src/battle/btl_cam.c:139-143`, `:170-193` |
| Wide en culling/efectos | `src/battle/stg_a.c:386-404`; `src/battle/eft_*.c` |
| Wide 2D | `port/src/gs/gs_draw.c:830-894` |

### Referencias rápidas (BT2)

| Tema | Archivo:línea |
|---|---|
| Save dialog flow | `port/eq/3E51F8.c:61-636` (estados 13, 20, 27, 28) |
| Checksum BT2 | `port/eq/28A6D8.c` |
| Memory card HLE | `port/full/plat_mc.c:1-20`, `:166-178` |
| Ventana ImGui | `port/full/gs/ui.cpp`; `port/full/gs/gs_gpu.c:469`, `:501-502`, `:955`; `port/full/gs/gs_gl.c:843`, `:877`, `:1124` |
| Vulkan BT2 | `port/full/gs/gs_gpu.c:490-915` |
| GL B24 | `port/full/gs/gs_gl.c:991-994`, `:1011`, `:1021` |
| Wide BT2 | `port/eq/25B688.c:42`; `port/full/gs/gs_draw.c:852-895`; `port/full/plat_gs.c:221` |
| Películas skip | `port/full/plat_movie.c:12-13` (`BT2_SKIP_MOVIES`) |
