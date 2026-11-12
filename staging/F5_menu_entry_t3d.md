# F5 — Cómo T3D agrega una entrada al menú y qué sirve en BT2

Fecha: 2026-11-11. **Solo lectura**: no edité, compilé ni ejecuté nada del proyecto. No toqué
`/mnt/datos2/BT2-Decomp`. Material: copia de Tenkaichi3Decomp en `/tmp/opencode/t3d` (commit
`20a8655ad3d3d0481a26ddf0b60c4114dc147683`) y el árbol de `BT2-Recomp`. Lo único escrito es este informe.

Resumen en una línea: **T3D no inventó una entrada: hizo visible un ítem que ya existía en el disco de PS2
("Dragon Net Battle", el ítem 4 del menú principal) y le colgó un pedido global que el renderer ImGui atiende.**
En BT2 ese atajo no existe (los 10 ítems del menú están usados y no hay un 11.º en el movie), pero **el menú de
BT2 sí está en C** (`port/eq/`), no hace falta decompilar nada; igual la vía barata es una pestaña ImGui.

---

## 1. Mecanismo de T3D

### 1.1 Dónde está el menú y cómo se define una entrada

El menú principal de T3D es **C del juego (decompilado matching)** del overlay `DBZP.BIN`, no una tabla del
binario ni un parche al cargar:

- `src/menu/menu_a.c:1-159` — `MainMenu_Init(s32 section)`.
- Estructura: `include/menu/menu_a.h`, `typedef struct MainMenu` (0x188 bytes):
  `items[MAINMENU_ITEM_MAX]` (`:0x118`), `itemCount` (`:0x144`), `top` (`:0x148`), `cursor` (`:0x10C`),
  `flags` (`:0x108`), `voiceLine` (`:0x114`).
  `MAINMENU_ITEM_MAX` = **11**: hay 11 ids de ítem posibles; se dibujan 6 placas (más una séptima mientras
  scrollea) y el cursor se mueve por 4 filas (`MAINMENU_ROWS`).
- La lista **se arma en runtime**, en el mismo `for` del init (`menu_a.c:139-159`):

```c
for (i = 0; i < MAINMENU_ITEM_MAX; i++) {
#ifdef PORT
    if (i == 4 && !Port_NetMenuListed()) { continue; }
#else
    if (i == 4) { continue; }            /* el original salta el 4 */
#endif
    if (i == 10 && (gSaveData->unlockFlags & 0x7F) != 0x7F) { continue; }
    gMainMenu->items[gMainMenu->itemCount++] = i;
}
```

- El ítem NO tiene un struct propio: es un **id entero** en `items[]`. Texto, placa, ícono y voces se indexan
  por ese id al dibujar (ver 1.3). No hay campos "acción"/"visible"/"habilitado" por ítem; la acción es un
  `switch` hardcodeado en el input y la visibilidad son los dos `if` de arriba.

**Evidencia de que no hay tabla en el binario ni parche de carga**: el cambio completo en git son 3 commits y
~25 líneas de C del juego + ~20 del port (`git show 75dc083`, `git show d5c835a`, `git show 84fae11`). No hay
asset nuevo, ni `.yaml`/`.toml`, ni hook de `File_Load`.

### 1.2 La acción: reusa el comando que ya existía (vacío)

El original ya tenía `case 4` en el input, con el cuerpo **vacío** (`case 4: break;`, documentado en
`docs/netplay_notes.md:255`). T3D no inventó un modo ni un comando: le agregó una llamada.

Cadena completa:

| paso | archivo:línea | qué hace |
|---|---|---|
| 1 | `src/menu/menu_a.c:450-456` (`MainMenu_Input`) | `case 4:` → `Port_NetMenuOpen()`; **no** usa `MAINMENU_CHOOSE(next)`, así que no cambia `gProgress->mode` ni arranca el fade |
| 2 | `port/src/headless.c:213-216` | `Port_NetMenuOpen()` sólo hace `gPortNetMenuRequest = 1` |
| 3 | `port/src/gs/ui.cpp:1270-1278` (`frame_build`, hilo del renderer) | si `gPortNetMenuRequest`, lo limpia y llama `net_open()` |
| 4 | `port/src/gs/ui.cpp:484-486` (`net_open`) | `set_open(true); sNet = true; gPortInputCapture = 1`: abre la ventana ImGui y le saca el input al juego (el menú queda dibujado detrás) |

Es un **hook por global + polling en el hilo del renderer**, no un hook de función del juego. El juego sigue en
el modo 4; cuando el jugador cierra la ventana, está otra vez en el mismo menú.

### 1.3 Texto e ícono: del disco, no del port

Todo el arte del ítem 4 ya estaba en el pack del menú de PS2:

- Dibujo: `src/menu/menu_a.c:198-290` (`MainMenu_Draw`). Para cada placa hace
  `uv.y0 = (item % 8) * 0x20` y `Flash_ClipSetTex(flash, &ref, item / 8)` para el texto (hojas de 8 filas) y
  `(item % 4) * 0x40` / `(item / 4) * 0x40` para el ícono, así que el ítem 4 es simplemente una fila más de una
  hoja que ya trae 8.
- `docs/netplay_notes.md:253-263` (investigación del disco): "**Dragon Net Battle**" es la **fila 4 de dos hojas
  de 512x256 (off/on)**, el ícono es una nave, quieta y animada; las guías tienen sus líneas en el pack del menú
  (mensajes 32..35, voces 0x8719..0x871C) y el ítem tiene placa, etiqueta y voz de las cuatro guías.
- El subtítulo de la guía sale igual que los demás: `voiceLine = item*4 + guide + 0x10` (`menu_a.c:431`).

Conclusión: **no se dibujó nada desde el port**. Por eso el ítem se ve exactamente como los otros.

### 1.4 Visibilidad / condiciones

- En el original: **oculto siempre** (`if (i == 4) continue;`), porque no tenía modo detrás (el online era de
  la versión Wii).
- En el port: **visible por defecto**; `BT3_MENU_ITEM4=0` lo vuelve a ocultar (`headless.c:217-221`).
- No hay flag de desbloqueo, idioma ni modo de juego. El único ítem con condición real es el 10 (las 7 esferas:
  `(unlockFlags & 0x7F) != 0x7F`, `menu_a.c:156-158`), y T3D no lo tocó.
- El `getenv` **se lee en la capa del port**, no en el archivo del juego: el commit `84fae11` lo movió porque
  "a pointer from getenv in the game's file crashed the 64-bit build" (en el juego los punteros son de 32 bits,
  el `char*` de `getenv` es de 64 y se trunca). Regla directamente aplicable a BT2.

### 1.5 Qué NO hizo T3D (para no copiar de más)

- No agregó un ítem 11 con arte nuevo: reusó la fila 4.
- No agregó un modo nuevo al dispatcher (`Progress_Main`): el menú se queda en el modo 4.
- No agregó una tabla de acciones ni callbacks: son `switch` en C del juego.
- El único "ítem nuevo" de otro tipo que tiene T3D son ids externos agregados a las **listas de stages y songs**
  (`src/menu/menu_c_e.c:536-607`, `:627-650`), que es otra cosa (contenido, no entrada de menú).

---

## 2. Estado real de BT2

### 2.1 Corrección a `F3F6_desde_tenkaichi3decomp.md` §3.5: el menú de BT2 **sí está en C**

El informe anterior decía "el overlay no está en C, no hay hook limpio". Eso es **falso para el menú
principal**. El menú vive en `0x3B3100..0x3B5xxx`, que es `.text.ovl` del overlay (`readelf -S
port/build/combined.elf`: `.text.ovl` empieza en `0x3b3100`, tamaño `0x6e200`), pero esa parte ya está
traducida a C equivalente en `port/eq/` y **es la que se usa en `bt2full`**:

- `port/build/full/tables.c:22888-22894`:
  `{0x003B3100u, MainMenu_StartBallLoops}`, `{0x003B37A8u, func_003B37A8}`, `{0x003B3F38u, func_003B3F38}`,
  `{0x003B4250u, func_003B4250}` (tabla de overrides del link completo).
- `port/tools/build_full.py:67-76`: un archivo de `port/eq/<ADDR>.c` gana sobre `src/` y sobre el recompilado.
- El dispatcher también es C: `port/eq/3B7FA8.c` (equivale a `Progress_Main`), caso `st == 4` →
  `func_003B4250(1)` en `:140`.

Así que "agregar una entrada" en BT2 **no es trabajo de decomp**: es editar C del port. Lo que sigue siendo
recompilado/asm es el resto del overlay (y el arte está en el disco).

### 2.2 Estructura del menú de BT2: 10 ítems, todos usados

- Inicialización: `port/eq/3B3100.c` (`func_003B3100`, mal nombrada `MainMenu_StartBallLoops`; aloca `D_00421380`,
  tamaño 0x120, carga el pack del menú `gProgress->baseFile + 1` y relocaliza secciones).
- Loop: `port/eq/3B4250.c` (`func_003B4250`): update/draw + `func_003B3F38(sp)` para el input (`:72`).
- Input y selección: `port/eq/3B3F38.c`. El cursor es `G->0xE8` (`G = D_00421380`):
  - `:37-43` arriba: `0xE8--`, si `< 0` → **9**.
  - `:52-58` abajo: `0xE8++`, si `>= **10**` → 0.
  - `:68-110` confirmar: `switch (e8)`, **10 casos** (0..9), y cada uno escribe `P->0x1C` con un modo:
    0→6/7, 1→0xA, 2→0x18, 3→0x1E, 4→0x3D, 5→0x35, 6→5, 7→0x26, 8→0x30, 9→0x2B.
  - `:112-120` cola común: `G->0xF0`, `G->0xE4 |= 1|2`, `G->0xF8 = 0xF`, `func_26EB78(..., D_004217A0)`,
    `func_297FE0(0, 1, ...)`. Esa cola es la que anima el confirm y arranca el fade; `3B4250.c:70-80` cuenta
    `0xF8` y al llegar a -1 hace `func_243A80` y `P->0x28 = G->0xE8`.
- Dibujo: `port/eq/3B37A8.c` (`func_003B37A8`):
  - `:45-50` la placa resaltada: `func_26EC18(s1, sp, G->0xE8)` y
    `func_26EC78(..., *(s32 *)(sp + 0x30 + a3*4), 1, 6)` — **tabla de 10 enteros** `D_004213D8` (se copia con
    `memcpy(sp+0x30, D_004213D8, 0x28)`); volcada del ELF son `{5,4,5,3,7,8,4,6,8,7}`.
  - `:70-79` las 5 placas del anillo: `w = G->0xF0 + s2; a3 = w % 10;` y la hoja/rango
    `v = a3 >> 2`, fila `(a3 % 4) << 6`.
  - `:101` el texto del ítem: `func_249FB8(..., *(u8 **)(G + 8), G->0xEC, 0)` — tabla de strings del pack,
    con `G->0xEC = item + 9` (`3B3E50.c:31`, y `8` al init en `3B3100.c:159`).
- De dónde sale cada pieza:
  - `G + 8` (tabla de texto de los ítems) es **una sección del pack del menú**: `3B3100.c:154`
    `*(G+8) = *(G+4) + (word[0x4C] >> 2) * 4`.
  - `D_004213D8` (10 valores por ítem) es data del overlay (`0x4213D8`), no editable desde C sin pisar la data
    del disco; alrededor se leen los nombres de clips del movie: `mc_menuicon_onanime`, `mc_menutext_onanime`,
    `mc_yaji_down`, `mc_menu_off_up2/up1/center/down1/down2`, `mcGuideEye/Mouth`, `mc_textwindow`, `mc_bg10/30`,
    `fr_menu_down/up/next`.
- Mapa de modos del menú (confirmado con logs): `port/build` y `docs/bugs_open.md:796-800`;
  `BT2-test/logs/vivo` muestra `modo 4 (menu_principal)`, y 30/31/33 son submenús del torneo.

### 2.3 No hay equivalente al "ítem oculto" de T3D

- El original de BT2 **no tiene un ítem sin modo**: los 10 casos del `switch` escriben `P->0x1C` (el 0 con un
  condicional), y el anillo es `% 10` en el input y en el dibujo.
- No hay un 11.º/12.º clip en la tabla `D_004213D8` (son exactamente 10 enteros, `0x28` bytes) ni un 12.º valor
  de texto (`G->0xEC` va de 9 a 18).
- El arte del menú está en un movie del pack: para una placa nueva haría falta un clip que **no está en el
  disco** (a diferencia de T3D, donde la fila 4 ya existía por la versión Wii).
- Posible excepción no verificada: la hoja de placas se indexa con `v = a3>>2` (3 hojas) y `a3%4`
  (4 filas), así que los índices 10 y 11 caerían en la **hoja 2, filas 2 y 3**, que los 10 ítems no usan. No pude
  confirmar si esas filas tienen arte o están en blanco: el pack del menú (AFS `baseFile+1` = entrada `0x545`,
  1.9 MB) está comprimido con el packer del juego (`func_002B24C8`) y no lo descomprimí.

### 2.4 ¿Se puede agregar una entrada sin decompilar? Sí, pero no es barato

No hay que decompilar: `3B3F38.c` / `3B37A8.c` ya son C y están en el build. Pero un 11.º ítem visible toca
**cuatro** piezas, y ninguna es tan simple como el `if` de T3D:

1. **Input** (`3B3F38.c`): wrap 9→10 y `>= 10`→11, `>= 10` del guard (`:69`), `+= 10` del par `0xF0` (`:113-115`),
   y un `case 10` nuevo.
2. **Dibujo** (`3B37A8.c`): `% 10`→`% 11` (`:74`), y la tabla `D_004213D8` (10 enteros) necesita un 11.º valor
   (si no, `a3=10` lee `D_00421400`, que es el nombre del clip `mc_menuicon_onanime`).
3. **Texto** (`G+8`, tabla del pack): agregar una etiqueta. Se puede hacer como la capa de F5
   (`port/full/plat_text.c`: copia en RAM + `Port_TextoAplicarTabla`), pero acá la tabla es una sección del pack
   del menú; habría que copiarla a un buffer del port, agregar el string y apuntar `G+8` ahí. El formato exacto de
   esa sección no está establecido (no lo verifiqué).
4. **Arte**: el clip de la placa/ícono del ítem 10 no existe en el movie. Opciones: reusar la placa de otro ítem
   (se ve repetida) y dibujar el nombre con ImGui encima (como los nombres de stages de T3D, `ui.cpp:1270-1407`),
   o empaquetar una textura nueva en el pack (mucho más trabajo y rompe la regla de no tocar datos del juego si se
   hace en disco; se podría inyectar en RAM).

Y un detalle de comportamiento importante: **no alcanza con copiar el `break` de T3D**. En BT2 la cola común del
confirm (`3B3F38.c:112-120`) arranca el fade; si el ítem no cambia `P->0x1C`, el menú se desvanece y el dispatcher
(`3B7FA8.c:100-105`) vuelve a entrar al modo 4 — un loop visual. Para que el menú quede quieto detrás de la ventana
hay que **salir con `return` antes de la cola** (o con un `goto` después de la animación de la placa), no con
`break`. Y no hay que inventar un modo: el dispatcher sólo tiene casos para 1..64 y un modo sin caso cae en
`if (idx >= 64) continue;` (bucle colgado), así que el modo tiene que seguir siendo 4.

**Riesgo**: medio-alto (input + dibujo + texto + arte). **Esfuerzo**: 1 a 2 días, más si hay que crear arte.
No lo recomiendo para la primera iteración.

---

## 3. Opciones para BT2, de menor a mayor costo

### A. Pestaña propia en la ventana ImGui (recomendada)

BT2 ya tiene la ventana (F1 hardcodeado: `port/full/gs/gs_gpu.c:501-502`, `port/full/gs/gs_gl.c:877`;
`port/full/gs/ui.cpp`, 656 líneas). Pestañas actuales: Video / Effects / Audio / Controls / Cheats
(`ui.cpp:524-531`). Agregar "Port" es una entrada visible, con teclado y mouse, sin tocar el juego.

Contenido natural (cierra pendientes de F3 y F5):

- **Autosave** (F3 ya dejó `Port_Autosave()` / `Port_AutosaveSet()` en `port/full/plat_autosave.c`; el checkbox
  es lo que falta).
- **Textos del memory card**: dejar/sacar "(PS2)" = setting `texto_ps2` (lo lee `plat_text.c:134-143`), y una
  nota de `bt2_texto.txt` / `BT2_TEXTO`.
- Lugar para futuras opciones del port (sin abrir otra vez el tema del menú del juego).

### B. Atajo de mando para abrirla (START+SELECT, como T3D)

T3D lo tiene en `port/src/gs/gs_input.c:108-143` con latch para no abrir/cerrar en el mismo evento. En BT2 el
punto equivalente es `Port_PadRead` (`port/full/gs/gs_input.c:255-315`): ahí se arma `btn` con `B_START` y
`B_SELECT` (`:21-24`). Se puede setear un pedido `volatile int gPortUiRequest` (mismo patrón que
`gPortUnlockAll`, `port/full/plat_gs.c:247`) y atenderlo en el loop de eventos (`gs_gpu.c:499`,
`gs_gl.c:875`) llamando `Ui_Toggle()`. Necesita latch (una vez por pulsación) y conviene exigir 2-3 frames
sostenidos: SELECT+START son botones del juego y un toque accidental no debe abrir la ventana.

### C. Ítem 11 en el menú del juego (lo de 2.4)

Sólo si el requisito es "que esté en el menú del juego". Mismo patrón que T3D (pedido + polling), pero con los
cuatro cambios y el arte. Dejar para una fase 2; no mezclar con A/B.

### D. Modificador sobre un ítem existente (variante barata de C)

En `3B3F38.c`, en el `case` de un ítem inocuo (p. ej. el 9, modo 0x2B), si el port ve una tecla/botón del port
apretado, setear el pedido y `return` antes de la cola; si no, comportamiento normal. No necesita arte ni tabla,
pero es un atajo oculto y confuso para el jugador (y pisa el ítem real si el modificador queda apretado). No lo
recomiendo como feature visible.

---

## 4. Diff propuesto (NO aplicado)

### 4.1 Opción A: pestaña "Port" en la ventana de F1

`port/full/gs/ui.cpp`: nueva función junto a `cheats_tab()` (después de `:441`) y una pestaña más en el tab bar
(`:524-531`).

```diff
--- a/port/full/gs/ui.cpp
+++ b/port/full/gs/ui.cpp
@@ -440,4 +440,41 @@ static void cheats_tab(void) {
     }
 }
 
+/* F5: opciones propias del port que no son del renderer. Autosave (F3) y textos (F5) ya tienen su capa en C;
+   aca solo se prenden y apagan, y se guardan en bt2_settings.txt (Port_SettingSave + Port_SettingsWrite). */
+extern "C" {
+int Port_Autosave(void);
+void Port_AutosaveSet(int on);
+extern int Port_Setting(const char *name, int def);
+extern void Port_SettingSave(const char *name, int value);
+extern void Port_SettingsWrite(void);
+}
+
+static void port_tab(void) {
+    static int autoOn = -1;
+    if (autoOn < 0) { autoOn = Port_Autosave(); }
+    bool a = autoOn != 0;
+    if (ImGui::Checkbox("Autosave (answer the game's save questions with Yes)", &a)) {
+        autoOn = a ? 1 : 0;
+        Port_AutosaveSet(autoOn);
+    }
+    ImGui::SetItemTooltip("The game asks \"Save game data?\" at the end of many screens and waits for an answer.\n"
+                          "With this on the question is answered for you (F3). BT2_AUTOSAVE=0 turns it off for one run.");
+    ImGui::Separator();
+    /* texto_ps2=1 deja "(PS2)" como el juego; ausente/0 lo saca (plat_text.c:134-143). */
+    static int ps2 = -1;
+    if (ps2 < 0) { ps2 = Port_Setting("texto_ps2", 0); }
+    bool keep = ps2 != 0;
+    if (ImGui::Checkbox("Keep \"(PS2)\" in the memory-card texts", &keep)) {
+        ps2 = keep ? 1 : 0;
+        Port_SettingSave("texto_ps2", ps2);
+        Port_SettingsWrite();
+    }
+    ImGui::SetItemTooltip("Memory-card messages from the original say \"The memory card (PS2)...\".\n"
+                          "With this off the port writes them without \"(PS2)\" (F5). Takes effect the next\n"
+                          "time the game loads those messages.");
+    ImGui::Spacing();
+    ImGui::TextWrapped("Texts and their replacements: bt2_texto.txt next to the game (MSG=text, \\n for a line break), "
+                       "or BT2_TEXTO=<path>. Without that file the game's own texts are used.");
+}
+
 static void controls_tab(void) {
     static int player;
     char label[96];
@@ -528,7 +565,8 @@ static void build(void) {
             if (tab("Controls", 3)) { controls_tab(); ImGui::EndTabItem(); }
             if (tab("Cheats", 4)) { cheats_tab(); ImGui::EndTabItem(); }
+            if (tab("Port", 5)) { port_tab(); ImGui::EndTabItem(); }
             ImGui::EndTabBar();
         }
         if (ImGui::GetFrameCount() > 3) {
```

Notas:
- No toqué `build()`: `port_tab()` va antes de `controls_tab()` sólo para que quede cerca en el archivo; el orden
  de las pestañas lo fija la línea del tab bar.
- `Port_SettingSave`/`Port_SettingsWrite` están implementados en `port/full/gs/plat_settings_bt3.c` y ya se usan
  desde `gs_draw.c:1217-1218`; en los enlaces donde no están, `plat_autosave.c` los declara weak (mismo patrón).
- `texto_ps2` se lee al aplicar la tabla (`plat_text.c:140`), o sea que el cambio se ve en el próximo diálogo de
  memory card, sin reiniciar.

### 4.2 Opción B (opcional): START+SELECT abre la ventana

`port/full/gs/gs_input.c`: después de armar `btn` (`:308`), con latch:

```diff
--- a/port/full/gs/gs_input.c
+++ b/port/full/gs/gs_input.c
@@ -305,6 +305,16 @@ int Port_PadRead(int socket, unsigned char *data) {
 #undef HELD
     }
     btn |= script_buttons(socket);
+    /* F5: START+SELECT abre/cierra la ventana del port (lo atiende el hilo del renderer). Se dispara una sola
+       vez, a los 2 frames sostenidos, para que un toque accidental no la abra en medio de una pelea. */
+    {
+        static int sComboFrames;
+        int combo = (btn & (B_START | B_SELECT)) == (B_START | B_SELECT);
+        if (combo) {
+            if (sComboFrames == 2) { gPortUiRequest = 1; }
+            if (sComboFrames < 3) { sComboFrames++; }
+        } else {
+            sComboFrames = 0;
+        }
+    }
     { extern unsigned gPortPadBtn[2]; gPortPadBtn[socket] = btn; }
```

Y el pedido se atiende en los dos back ends (con el global declarado en `ui.h`, junto a los otros dos de
`ui.h:42-43`, y definido en `plat_gs.c:247`):

```diff
--- a/port/full/gs/ui.h
+++ b/port/full/gs/ui.h
@@ -42,3 +42,4 @@
 extern int gPortOverlayOpen;   /* the settings window is open: the keyboard does not reach the game */
 extern int gPortInputCapture;  /* it is waiting for a key or button to bind: nothing reaches the game */
+extern volatile int gPortUiRequest; /* F5: el juego o el pad piden abrir/cerrar la ventana (se atiende en el hilo del renderer) */
```

```diff
--- a/port/full/gs/gs_gpu.c
+++ b/port/full/gs/gs_gpu.c
@@ -498,6 +498,7 @@
     while (SDL_PollEvent(&ev)) {
+        if (gPortUiRequest) { gPortUiRequest = 0; Ui_Toggle(); }
         if (ev.type == SDL_EVENT_QUIT) {
```

```diff
--- a/port/full/gs/gs_gl.c
+++ b/port/full/gs/gs_gl.c
@@ -875,6 +875,7 @@
     while (SDL_PollEvent(&ev)) {
+        if (gPortUiRequest) { gPortUiRequest = 0; Ui_Toggle(); }
         if (ev.type == SDL_EVENT_KEY_DOWN && !ev.key.repeat && ev.key.key == SDLK_F1) { Ui_Toggle(); continue; }
```

Riesgo: bajo. Lo único que hay que cuidar es que SELECT+START no sea un combo que el juego use (no encontré usos;
probarlo en pelea y en menús antes de dejarlo fijo).

### 4.3 Opción C (boceto; NO recomendado para la primera iteración)

(Hunks simplificados: es un boceto de los cambios, no un patch aplicable tal cual.)

```diff
--- a/port/eq/3B3F38.c
+++ b/port/eq/3B3F38.c
@@
-            *(s32 *)(g + 0xE8) = 9;
+            *(s32 *)(g + 0xE8) = 10;              /* F5: 11 items */
@@
-        if (*(s32 *)(g + 0xE8) >= 10) {
+        if (*(s32 *)(g + 0xE8) >= 11) {
@@
-        if ((u32)e8 >= 10) {
+        if ((u32)e8 >= 11) {
@@
         case 9:
             *(s32 *)(p + 0x1C) = 0x2B;
             break;
+#ifdef PORT
+        case 10:
+            /* El ítem del port: abre su ventana y deja el menú como está. Hay que salir ANTES de la cola
+               común (fade + G->0xE4 |= 3), si no el menú se desvanece y el dispatcher re-entra al modo 4. */
+            Port_MenuEntryOpen();      /* gPortUiRequest = 1 (plat_gs.c) */
+            func_26EB78(g + 0x38, D_004217A0);
+            func_297FE0(0, 1, 0x40, 0x40, 1);
+            return;
+#endif
         default:
             break;
@@
-        if (*(s32 *)(g + 0xF0) < 0) {
-            *(s32 *)(g + 0xF0) += 10;
+        if (*(s32 *)(g + 0xF0) < 0) {
+            *(s32 *)(g + 0xF0) += 11;
         }
```

Más, en `3B37A8.c:74`, `a3 = w % 10;` → `% 11`; y los puntos 3 y 4 de §2.4 (tabla de texto y arte). Este diff
solo **no alcanza**: sin el 11.º valor en `D_004213D8` y sin etiqueta/placa, el ítem se dibuja mal. Lo dejo escrito
para que el costo quede claro, no como propuesta. (`Port_MenuEntryOpen()` sería una función nueva de
`port/full/plat_gs.c` que sólo hace `gPortUiRequest = 1`.)

---

## 5. Recomendación

1. **Hacer A** (pestaña "Port"): es una entrada nueva real, visible, con teclado y mouse, riesgo casi nulo,
   1-2 h, y cierra el checkbox de autosave que F3 dejó pendiente y la opción de textos de F5.
2. **Sumar B** si se quiere que también se abra con el mando: ~2-3 h y riesgo bajo (con latch y prueba en pelea).
3. **No hacer C ahora**: el menú de BT2 está en C (no hace falta decomp), pero el ítem 11 no tiene arte ni clip en
   el disco, requiere extender dos tablas y tocar el anillo en input y dibujo, y si se copia el `break` de T3D se
   produce un loop de fade. Si en el futuro es requisito, el camino es: `return` antes de la cola común, `% 11`,
   11.º valor en la copia en RAM de `D_004213D8`, tabla de texto extendida como en `plat_text.c` y el nombre
   dibujado con ImGui sobre una placa repetida.

### Qué descarté y por qué

- **"T3D creó una tabla de ítems nueva o parchea el binario al cargar"**: descartado. La lista se arma en
  `MainMenu_Init` y el cambio en git es de 8+14 líneas de C (`git show 75dc083/d5c835a`).
- **"T3D agregó un comando/modo nuevo"**: descartado. `case 4` ya existía vacío; sólo se agregó
  `Port_NetMenuOpen()` (`menu_a.c:450-456`), sin cambiar `gProgress->mode`.
- **"BT2 no tiene el menú en C" (F3F6 §3.5)**: descartado con `tables.c:22888-22894` y `readelf`: el menú es
  `.text.ovl` pero está traducido a C equivalente en `port/eq` y es lo que corre en `bt2full`.
- **"En BT2 hay un ítem oculto reutilizable"**: descartado. Los 10 casos del `switch` (`3B3F38.c:68-110`) tienen
  modo y el anillo es `% 10` en input y dibujo; `D_004213D8` tiene exactamente 10 valores.
- **"Se puede resolver con una tabla de ítems en RAM"**: descartado. No hay tabla de ítems: hay un `switch` en C,
  una tabla de texto (sección del pack) y una tabla de 10 enteros por ítem.
- **"Cambiar el ítem a un modo nuevo para abrir la pantalla del port"**: descartado. El dispatcher sólo conoce
  1..64 por casos y un modo sin caso cuelga el bucle (`3B7FA8.c:100-105`).

### Sin verificar

- Si la hoja de placas del menú de BT2 tiene arte en las filas 2/3 de la tercera hoja (los índices 10/11 que el
  menú no usa). Requiere descomprimir el pack del menú (AFS `0x545`, `func_002B24C8`).
- El formato y el `count` de la tabla de texto de los ítems (`G+8`, sección `word[0x4C]` del pack). Sin eso no se
  sabe si agregar una etiqueta es "copiar y agregar un string" o algo más.
- Que salir con `return` antes de la cola común deje el menú realmente interactivo detrás de la ventana ImGui
  (es la parte que hay que probar en un build de prueba si se hace C).
- Que SELECT+START no haga nada en el juego (no encontré usos; hay que probarlo en pelea y en menús antes de
  dejarlo fijo).

---

## 6. Referencias

| Tema | Archivo:línea |
|---|---|
| T3D: lista de ítems y salto del 4 | `src/menu/menu_a.c:139-159` |
| T3D: struct `MainMenu` | `include/menu/menu_a.h` (`items[11]`, `itemCount`, `top`, `cursor`) |
| T3D: confirmar el ítem 4 | `src/menu/menu_a.c:450-456` |
| T3D: pedido global en el port | `port/src/headless.c:213-221` |
| T3D: polling en el renderer | `port/src/gs/ui.cpp:1270-1278`, `:484-486` |
| T3D: arte/etiquetas del ítem 4 en el disco | `docs/netplay_notes.md:243-263` |
| T3D: pestañas y opciones del port | `port/src/gs/ui.cpp:1053-1103` |
| T3D: hotkey con latch | `port/src/gs/gs_input.c:108-143` |
| BT2: dispatcher `Progress_Main` | `port/eq/3B7FA8.c:20-160` (modo 4 → `3B4250(1)` en `:140`) |
| BT2: loop del menú | `port/eq/3B4250.c:1-81` |
| BT2: input, 10 ítems → modos | `port/eq/3B3F38.c:37-119` |
| BT2: dibujo (anillo, placas, texto) | `port/eq/3B37A8.c:36-103` |
| BT2: init del menú / tabla de texto | `port/eq/3B3100.c:150-160` |
| BT2: índice de texto = ítem + 9 | `port/eq/3B3E50.c:31-32` |
| BT2: overrides que usa `bt2full` | `port/build/full/tables.c:22888-22894` |
| BT2: ventana ImGui y pestañas | `port/full/gs/ui.cpp:246-250`, `:404-441`, `:524-531` |
| BT2: F1 | `port/full/gs/gs_gpu.c:501-502`; `port/full/gs/gs_gl.c:877` |
| BT2: input de pad | `port/full/gs/gs_input.c:255-315` |
| BT2: pedido desde el juego (patrón) | `port/full/plat_gs.c:247` (`gPortUnlockAll`) |
| BT2: autosave (set) | `port/full/plat_autosave.c:17-37` |
| BT2: textos y setting `texto_ps2` | `port/full/plat_text.c:134-143`, `:302`; `port/eq/29BB88.c:48` |
| BT2: mapa de modos del menú | `docs/bugs_open.md:796-800` |
