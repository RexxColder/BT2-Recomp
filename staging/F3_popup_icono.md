# F3 — Apagar el cartel de guardado y poner un ícono chico

Fecha: 2026-11-11. **Solo lectura**: no se editó, compiló ni ejecutó nada del proyecto.
Máquina: `port/eq/3E51F8.c` (`func_003E51F8`, overlay `0x3E51F8..0x3E6658`). Asm: `/tmp/opencode/ovl.dis`
(rango en `/tmp/opencode/f3_3E51F8.dis`). Herramientas nuevas: las tablas de mensajes ya descomprimidas en
`/tmp/opencode/f3_s0.raw..f3_s3.raw` (4 sub-bloques de la entrada `0x550` de `ZS2US_1.AFS`) y
`port/build/combined.elf` sección `.data.ovl` (los nombres de los prims del menú).

---

## 0. Resumen

- El cartel **no tiene un flag de "visible"**: lo dibuja, entero, `func_0029C1E8(1)` (más `func_0029C800(MSG)`
  para el texto) al final de `func_003E51F8`, **cada frame mientras `STATE != 0`**.
- Se apaga con la llamada que el propio juego usa para cerrarlo: **`func_0029C550(1)`** (estado 14). No hace
  falta inventar nada: flag `0x54 |= 8`, script del cartel a `"fr_out"` y fundido del fondo a alpha 0.
- `func_0029C7C0(1)` (campo `0x70`) **no** es visibilidad: es el permiso de leer el pad en `func_0029C640`
  (`29C640.c:23`). `DLG(0x11C)` tampoco: es un pestillo de flujo que lee `3E4CF8.c:39`.
- No existe ningún texto "Auto saving" en los recursos de menú (49 entradas revisadas). Lo más cercano es
  **MSG 29 = "Saving data. Do not remove memory card (PS2), controller, reset, or switch off the console."**
- Sí existe un ícono del propio juego: **`mc_icon_saveload`, 64×64**, dibujado en la pantalla de memory card
  (`3E4218.c:98-116`). Pero cada prim se busca por *nombre único* dentro del objeto (`270270.c`), así que no se
  puede duplicar: para el port conviene un adorno propio (ImGui), y el arte del juego queda como opción "2.0".

---

## (a) Mecanismo que hace visible / oculta el cartel

### a.1 Quién dibuja, cada frame

`func_003E6658` (bucle del menú) llama `func_003E4218()` **siempre** y después, sólo si `STATE != 0`,
`func_003E51F8()` (`port/eq/3E6658.c:48-52`). `func_003E51F8` arranca con el early-return de `STATE == 0`
(`3E51F8.c:67-69`) y termina siempre con:

```c
    func_0029C800(MSG);          /* 3E51F8.c:640 */
    return func_0029C1E8(1);     /* 3E51F8.c:641 */
```

asm (idéntico, cola de la función):

```
3e6608: lw   v0,31180(s4)      ; D_004279CC
3e660c: jal  0x29c800          ; func_0029C800(MSG = lw a0,268(v0))
3e6614: li   a0,1
3e6630: j    0x29c1e8          ; func_0029C1E8(1)   (tail call)
```

- `func_0029C800(n)` = `D_00387DA0+0x5C = n` (`src/auto/m2c_29C800.c`). `0x5C` es **sólo** el índice de texto:
  su único lector es `func_0029BD58` (`29BD58.c:29-33`, y sale si `0x5C < 0`).
- `func_0029C1E8(1)` es **todo el dibujo** (`port/eq/29C1E8.c`):
  - `:35` `func_0026E9E8(dlg+8)` → tick del script del menú 2D: es lo que **emite** los prims `mc_*`
    (`func_0026E9E8` → `func_0026DF68` → `func_0026DC60`, `src/auto/m2c_26E9E8.c`).
  - `:36-40` si flag `0x54 & 8` y el script dice "terminado" (`func_0026EB70(dlg+8) & 0x200`) → `0x54 |= 2`.
    **Este es el único lugar donde se pone el bit 2** (lo usa el estado 15, ver a.4).
  - `:43-54` anima `placa+0x34`: flag 4 → `+= 4` hasta `0x60`; flag 8 → `-= 4` hasta 0.
  - `:55` `func_002788A0(0, 0, placa)` → `func_002784E0` emite el paquete GS del panel.
  - `:58-110` ubica las dos filas de respuesta y el cursor (`mc_text_off_y`, `mc_text_off_n`,
    `mc_general_plate_*`, `mc_text_on`; nombres en `disc/SLUS_214.41` `.rodata` `0x3777A0..0x377890`) y les
    aplica el flag de estilo según `0x70`.
  - `:115` `func_0029BD58(1)` imprime el texto de `MSG` (alpha sacado del prim, `270F40.c:9-21`).

Los nombres/estructura del cartel (de `.rodata`, con el ELF a mano):

| símbolo | dirección | contenido |
|---|---|---|
| `D_003777A0` | `0x3777A0` | `"mc_dammy_fonts"` (caja de texto) |
| `D_00377818` / `D_00377828` | `0x377818` / `0x377828` | `"mc_text_off_n"` / `"mc_text_off_y"` (respuestas) |
| `D_00377838` | `0x377838` | `"mc_general_plate_text_on"` (cursor) |
| `D_00377858` / `D_00377870` | `0x377858` / `0x377870` | `"mc_general_plate_no_off"` / `"..._yes_off"` |
| `D_00377890` | `0x377890` | `"mc_text_on"` |
| `D_00387DA8` (símbolo en `0x387DA8`) | string en `0x387DAC` | **`"fr_out"`** (label del script que usan los `C550(1)`) |

### a.2 Qué hace el fondo del panel (el "0x70" no es visibilidad)

La placa es la lista de registros de `0x38` bytes en `*(D_00387DA0+0x50)`; en `func_002784E0.c:26-27`:

```c
packed = *(s0+0x28) | (*(s0+0x34) << 24) | (*(s0+0x30) << 16) | (*(s0+0x2C) << 8);
```

o sea **`+0x34` = alpha del primer strip** (byte alto de RGBAQ). Y `func_0029BB88.c:43` lo arranca en `0`
(invisible) al crear el diálogo. `func_0029C550(0)` lo vuelve a 0 y pone flag 4 (fundido de entrada
`29C550.c:24-31`); `func_0029C550(1)` pone flag 8, saca el 4, salta el script a `"fr_out"` y suena el SE 5
(`29C550.c:13-22`). Con flag 8, `29C1E8.c:49-53` baja el alpha 4 por frame → en 24 frames el panel es
transparente; el script `fr_out` hace lo mismo con los prims de texto/respuestas/cursor (su alpha se lee de
cada prim: `270F40.c:9-21`).

### a.3 Qué pieza "abre" el cartel en los casos 16/18/28/32

| pieza | ¿abre/dibuja? | evidencia |
|---|---|---|
| `func_0029C7C0(1)` → `0x70 = 1` | **No**. Habilita leer el pad en `func_0029C640` (`29C640.c:23`) y cambia un bit de estilo (bit 1 de `+0x44`, `270A10.c:16-21`) de las dos placas de respuesta. | `src/auto/m2c_29C7C0.c` (solo escribe), `29C640.c:23` |
| `func_0029C550(0)` | **Sí, es el que lo abre**: alpha `placa+0x34 = 0` → flag 4 → fundido hacia `0x60`, rebobina el script (`func_0026EA88`) y pone el cursor. En 16/28 ya venía abierto por `fx()` de `3E4CF8.c:32-38`, así que el call es idempotente (guardado por `if (!(flag & 4))`, `29C550.c:24`). | `29C550.c:24-31`, asm `3e52f4`/`3e62c0` |
| `DLG(0x11C) = 0` | **No**. Pestillo de flujo que lee el menú padre (`3E4CF8.c:39`); además `3E4218.c:165` lo pone en 1 cada frame. | `3E4CF8.c:37-41`, `3E4218.c:165` |
| `MSG = n` | **Sí, pero sólo el texto** (índice → `0x5C` → `func_0029BD58`). Con `MSG = -1` (lo que hace `3E51F8.c:70` al entrar) no hay texto, pero el panel y las respuestas siguen. | `29C800`, `29BD58.c:29-33` |

Los prims del cartel (panel, "yes/no", cursor) no se dibujan en otro lado: se emiten dentro de `func_0029C1E8`
(el `func_0026E9E8` de `:35` + el `func_002788A0` de `:55`). Nada más, en ningún otro lugar, vuelve a dibujar
este diálogo (grep de `func_0029C1E8`/`func_0029C800`/`func_0029BD58`: sólo las máquinas de diálogo y este
drawer; `D_00387DA0` sólo lo tocan `29BB88`/`29C*`).

### a.4 Cómo se apaga (lo que ya hace el juego)

Estado 14 (`3E51F8.c:238-243`) hace exactamente:

```c
func_0029C7C0(0);   func_0029C550(1);   func_0029C640(0);   STATE = 15;
```

y el asm lo confirma (`3e62c0: jal 0x29c550` con `a0=1`). Después el estado 15 espera
`func_0029C830()` = `(0x54 >> 1) & 1` (bit 2, `src/auto/m2c_29C830.c`), que —como se vio en a.1— **sólo se pone
dentro de `func_0029C1E8`**, cuando el script de salida terminó. Cuando eso pasa: `0x11C = 1`, `STATE = 0`,
SE `"fr_saveload_out"`, `func_003E4B10()` → al frame siguiente `func_003E51F8` sale por el early-return y el
cartel deja de existir (si además `0xD0 & 2`, en vez de volver a la pantalla de la memory card cierra todo con
`func_00243A80`).

**Conclusión de (a):** el "off" nativo es `func_0029C550(1)` (cierra: flag 8 + `fr_out` + SE) y, como último
paso, `STATE = 0`. Un `MSG = -1` oculta sólo el texto.

---

## (b) Opciones para que el cartel no aparezca (con riesgo)

### Opción 1 (recomendada): en 16/28, cerrar en vez de abrir

En `case 16` y `case 28` cambiar `func_0029C550(0)` por `func_0029C550(1)` cuando `Port_Autosave()`.
El cartel se funde (24 frames, con el fundido normal del juego) mientras corre el `TIMER` de "Checking memory
card...", y no vuelve a abrirse: 17, 18, 19, 20, 21, 31, 33 no llaman `C550(0)` (grep del asm: `C550` aparece
sólo en los estados 13, 14, 16 y 28). El estado 14 reintenta cerrar (`C550(1)` sale por el guard del flag 8) y
el 15 encuentra el bit 2 ya puesto → cierra en 1 frame.

- Riesgo **bajo**: no toca tiempos ni el flujo; sólo estética. Efectos secundarios: suena el SE de "cerrar
  ventana" al empezar a guardar en vez de al final (SE 5, `29C550.c:21`).
- **Ojo con los estados de error**: 2, 4, 22, 26, 27, 29, 30 tampoco abren el cartel (nacen con la ventana
  abierta), así que si el autoguardado falla la pregunta quedaría invisible. Por eso el diff incluye un
  watchdog al final del `switch` que reabre (`C550(0)`) en cuanto el `STATE` sale de {16..21, 31..33}.
  Sin ese watchdog, la Opción 1 **no** es segura.
- Riesgo **medio** en lo visual: si el `fr_out` deja algún prim a medio animar, no lo puedo ver sin correr el
  juego (ver (f)).

### Opción 2: saltear el tail de dibujo (`func_0029C800` + `func_0029C1E8`) en 16..21

Funciona para "no ver nada" en esos estados (el panel y los prims sólo se emiten en ese tail) pero **rompe el
cierre**: el bit 2 del estado 15 sólo se pone dentro de `func_0029C1E8`, así que al llegar a 14/15 el cartel
volvería a dibujarse durante los ~24 frames del fundido de salida (parpadeo) y habría que replicar a mano
`func_0026E9E8(dlg+8)` + la comprobación de `0x200`. Además queda la duda de si el balance de DMA por frame
tolerar saltear el drawer (no verificado). **No la recomiendo** frente a la 1.

### Opción 3 (barata y sin efecto): dejar el cartel pero vaciarle el texto

`func_0029C800(-1)` mientras `Port_Autosave()`. Cero riesgo (MSG es puramente visual), pero queda una caja con
dos botones "yes/no" mudos: no cumple el objetivo, sólo sirve como plan B si la 1 sale mal.

### Opción 4 (no recomendada): guardar directo desde el port, sin la máquina de diálogo

Llamar `func_00289C98`/`func_0028A790`/`McCard_CreateSave`/`McCard_WriteSave` desde el port y saltear 16..21.
Evita todo el cartel, pero hay que reproducir los chequeos de tarjeta y el mantenimiento de estado del juego
(`SYS_FLAGS |= 0x400`, `&= ~1` en 21/10) y la salida al menú. **Riesgo alto**: toca el guardado real.

### Extra (no en el mismo arreglo): los tiempos

Con autoguardado el jugador se queda ~7,5 s sin nada en pantalla (ver la tabla de abajo): 121 frames en 17
("Checking..."), 121 en 20 ("Saving data...") y hasta 181 en 21. Si molesta, se pueden recortar los `TIMER`
(120 → 20, 180 → 60) en los caminos de autoguardado. Es otro cambio, con su propia prueba.

---

## (c) Ícono: qué hay y cuál es la opción más barata

### c.1 ¿Hay texto "Auto saving"?

**No.** La tabla de mensajes completa (recurso `0x550` de `ZS2US_1.AFS`, 49 entradas, UTF-16LE) no tiene nada
tipo "Auto saving"/"Saving…". Revisé además los 4 sub-bloques del recurso (`/tmp/opencode/f3_s0.raw..s3.raw`,
207+91+96+109 strings): sólo hay textos de ayuda de opciones y los del memory card. Lo más cercano:

| MSG | texto | se usa en |
|---|---|---|
| **29** (entrada 30) | "Saving data. Do not remove memory card (PS2), controller, reset, or switch off the console." | estado 20 |
| 18 (entrada 19) | "Creating save file. Do not remove memory card (PS2)..." | 19/33 |
| 34 (entrada 35) | "Checking memory card (PS2)..." | 5/7/8/17/31 |

### c.2 ¿Hay un ícono usable?

**Sí, en el juego**: la pantalla de memory card dibuja 4 íconos de **64×64** (`3E4218.c:98-116`, celdas
`i<<6`, `0x40` de ancho/alto). Sus nombres están en `.data.ovl` de `port/build/combined.elf`:

| dirección | nombre |
|---|---|
| `0x428280` | **`mc_icon_saveload`** |
| `0x42837F` | `mc_icon_controller` |
| `0x42847E` | `mc_icon_screen` |
| `0x42857D` | `mc_icon_sound` |

`mc_icon_saveload` es exactamente el "disquito" de guardar/cargar. **Pero no se puede duplicar en juego**:
`func_0026EBC0` → `func_00270270` busca los prims por `strcmp` contra el nombre y devuelve `{primero, cantidad}`
(`270270.c:10-40`); el objeto del diálogo y el de la pantalla tienen *una* instancia cada uno. Volver a ubicar
`mc_icon_saveload` **mueve** el original (el de la lista de la pantalla de memory card), no crea otro. Además el
objeto del diálogo (`D_00387DA0+8`) no tiene íconos en su pool, sólo `mc_dammy_fonts`, `mc_text_*`,
`mc_general_plate_*`.

Para usarlo *como arte* en el port habría que sacarle la textura (GS: `Gs_VramRead`/`Gs_PageHash` en
`gs_core.c`, o el directorio de texture pack con nombres PCSX2, `gs_texpack.h`). Eso ya requiere correr el
juego para localizar la textura → **fuera del alcance de esta investigación**.

### c.3 La opción más barata en el port: un adorno ImGui sin ventana

Ya existe el patrón exacto: el overlay de nombres de escenario/canción (`ui.cpp:560-596`) dibuja con
`ImGui::GetForegroundDrawList()` **sin abrir ninguna ventana**, mapeando píxeles del juego (512×448) al
rectángulo de la imagen con `gUiPresentX/Y/W/H` (`ui.h:55-64`, alimentado en `gs_gpu.c:951-954` y
`gs_gl.c:1112-1115`).

- **No** hay ningún toast/HUD dibujado siempre: `Ui_Draw` corre cada frame (`gs_gpu.c:955`) pero sale en
  `:565` si `!sOpen && !overlay`; `Ui_DrawGL` corre cada frame (`gs_gl.c:1124`) y sale en `:549` si `!sOpen`.
  El único overlay "a demanda" es el de nombres, y en BT2 nadie setea `gUiNameIdx` (está muerto, listo para
  reusar el camino).
- **Enganche más barato**: un disco de 2 círculos (`AddCircleFilled`), sin textura ni fuente, en la esquina
  inferior derecha de la imagen, con un `volatile int gUiAutosave` que prenda/apague el estado de la máquina de
  diálogo. Costo: ~25 líneas en `ui.cpp` (2 lugares), +1 `extern` en `ui.h`, el global definido en
  `plat_autosave.c` (se enlaza siempre; no en `gs_draw.c`, para no romper `BT2_NO_GS=1`) y ~10 líneas en
  `3E51F8.c` (prender/apagar). Ni `link_full.py` ni el build necesitan nada nuevo: `port/full/*.c` y
  `port/full/gs/ui.cpp` ya se compilan.
- **Limitación**: el renderer por software (`BT3_SW_WINDOW`, `gs_core.c:1051`) usa `SDL_Renderer` sin ImGui →
  ahí no aparece. Aceptable (es modo de diagnóstico).

Si se quiere el ícono "de verdad" (arte del juego, 64×64), el camino es: F9 sobre la pantalla de memory card →
encontrar la textura del prim `mc_icon_saveload` en VRAM → exportarla como strip RGBA (`gamedata/...`, mismo
formato de `names.rgba`: 12 bytes de header `w,h,count` + imágenes apiladas, `ui.cpp:26-50`) y usar
`AddImage` en vez del círculo. Queda como paso 2.

---

## (d) Secuencia exacta 16 → vuelta al juego (para dimensionar el "sin cartel")

Contando 1 paso de estado por frame a 60 Hz (el `switch` corre 1 vez por frame desde `3E6658`):

| estado | qué hace | espera | texto |
|---|---|---|---|
| 16 | autosave: `ANSWER=1`, `TIMER=12` → al llegar a −1: `STATE=17`, `TIMER=120`, `ANSWER=0`, `func_00288348` | 13 frames | "Save game data?" |
| 17 | `TIMER=120`; al llegar a −1: `func_00289C98(0, BUF_END)` (¿están los archivos?) → `STATE=31` | 121 | "Checking..." |
| 31 | inmediato: `func_0028A790` (espacio libre) → `18` (no hace falta crear) o `32` (create + write) | 1 | — |
| 18 | autosave: `ANSWER=1`, `TIMER=12` → `STATE=20`, `TIMER=120` | 13 | "Save data already exists... overwrite?" |
| 32 | autosave: `ANSWER=1`, `TIMER=12` → `STATE=33`, `TIMER=120` | 13 | idem |
| 33 | `TIMER=120` → `McCard_CreateSave` → `STATE=20` | 121 | "Saving data..." |
| 20 | `TIMER=120` → **`McCard_WriteSave(0, D_00387F2C, 0x4000, BUF_END)`** → `STATE=21`, `TIMER=180` | 121 | "Saving data..." |
| 21 | `SYS_FLAGS |= 0x400; &= ~1`; OK del pad **o** `TIMER=180` → `STATE=14` | ≤181 | "Save successful." |
| 14 | `C7C0(0)`, `C550(1)` (cierra), `C640(0)` → `STATE=15` | 1 | — |
| 15 | espera el bit 2 del cierre → `0x11C=1`, `STATE=0`, SE, `func_003E4B10()` (o `func_00243A80` si `0xD0 & 2`) | 1 (si ya venía cerrado) | — |

Total: **~452 frames (7,5 s)** por el camino 18, **~573 frames (9,6 s)** por el 32/33. El forzado de
`TIMER=12` pisa el `TIMER=120` que deja el estado 31 al entrar a 18/32 — por eso la pregunta dura 13 frames y
no 121.

Y sí: **la máquina avanza igual sin el cartel**. Los casos 16..21/31/33 sólo leen `ANSWER`, `TIMER`, `MSG`(sólo
lo escriben) y las funciones de memory card. Lo único que depende del dibujo es el estado 15 (espera el bit 2,
que se pone en `func_0029C1E8`), y eso se cumple porque hay que seguir llamando al drawer (la Opción 1 lo hace).

---

## (e) Diff propuesto (NO aplicado)

### e.1 `port/eq/3E51F8.c` — cerrar el cartel en vez de abrirlo

```diff
--- a/port/eq/3E51F8.c
+++ b/port/eq/3E51F8.c
@@ -11,8 +11,12 @@
 extern s32 D_003B0C34;
 extern u8 gMcCardPort[];
 extern int Port_Autosave(void);
+void Port_AutosaveIcon(int on);   /* port/full/plat_autosave.c: prende el icono del port */
 extern void bt2_fightlog_note(const char *fmt, ...);
 
+/* F3: 1 mientras el autoguardado tiene el cartel cerrado (apaga tambien el texto). */
+static int sAutoHidden;
+
 s32 func_0029C1E8();
 void func_0029C7C0(s32 arg0);
 void func_0029C550(s32 arg0);
@@ -63,8 +67,11 @@
 s32 func_003E51F8(void) {
     s32 saved;
     s32 v;
+    s32 busy;
 
     if (DLG(0x110) == 0) {
+        sAutoHidden = 0;
+        Port_AutosaveIcon(0);
         return -1;
     }
     MSG = -1;
@@ -240,6 +247,8 @@
         func_0029C550(1);
         func_0029C640(0);
         STATE = 15;
+        sAutoHidden = 0;
+        Port_AutosaveIcon(0);
         break;
     case 15:
         func_0029C640(0);
@@ -260,7 +269,11 @@
         break;
     case 16:
         func_0029C7C0(1);
-        func_0029C550(0);
+        /* F3: con autoguardado no se abre el cartel: se CIERRA con la misma llamada que usa el estado 14
+           (flag 0x54 |= 8, script a "fr_out", fundido del panel a alpha 0 en 24 frames). El flujo sigue
+           igual: 17 -> 31 -> 18/32 -> 20 -> 21 -> 14 -> 15 -> 0. */
+        if (Port_Autosave()) { sAutoHidden = 1; Port_AutosaveIcon(1); func_0029C550(1); }
+        else { func_0029C550(0); }
         DLG(0x11C) = 0;
         MSG = 28;
         if (Port_Autosave() && ANSWER == 0) { ANSWER = 1; TIMER = 12; bt2_fightlog_note("F3 AUTOSAVE estado %d msg %d", STATE, MSG); }
@@ -505,7 +518,8 @@
         break;
     case 28:
         func_0029C7C0(1);
-        func_0029C550(0);
+        if (Port_Autosave()) { sAutoHidden = 1; Port_AutosaveIcon(1); func_0029C550(1); }
+        else { func_0029C550(0); }
         DLG(0x11C) = 0;
         MSG = 37;
         if (Port_Autosave() && ANSWER == 0) { ANSWER = 1; TIMER = 12; bt2_fightlog_note("F3 AUTOSAVE estado %d msg %d", STATE, MSG); }
@@ -637,6 +651,19 @@
     default:
         break;
     }
-    func_0029C800(MSG);
+    /* F3: si el autoguardado cerro el cartel y el flujo se fue a un estado que espera al jugador (tarjeta
+       ausente, error de escritura, "Exit saving?"...), volver a abrirlo: si no, la pregunta queda invisible. */
+    if (sAutoHidden) {
+        busy = STATE == 16 || STATE == 17 || STATE == 18 || STATE == 19 || STATE == 20 ||
+               STATE == 21 || STATE == 31 || STATE == 32 || STATE == 33;
+        if (!busy && STATE != 14 && STATE != 15) {
+            func_0029C550(0);      /* reabrir: alpha a 0, flag 4, rebobina el script */
+            sAutoHidden = 0;
+            Port_AutosaveIcon(0);
+        }
+    }
+    /* F3: si el cartel esta cerrado, que tampoco quede el texto colgado de un frame (MSG = -1 lo saltea
+       entero en func_0029BD58). Es cinturon y tiradores: normalmente el alpha del prim ya es 0. */
+    func_0029C800(sAutoHidden ? -1 : MSG);
     return func_0029C1E8(1);
 }
```

Notas:
- No hace falta tocar 18/32 (no abren el cartel) ni el forzado de `ANSWER` que ya está.
- **El watchdog del final es parte del arreglo, no un adorno**: sin él, si el autoguardado cae en un estado de
  error (2 "No memory card", 4 "Not enough space", 22 "Save failed", 27 "card replaced", 29/30) o en 23
  (formatear), el jugador se queda mirando una pantalla sin pregunta y con el pad gobernando a ciegas.
  Los estados 14/15 quedan afuera a propósito (son el cierre normal).
- Si preferís no agregar el texto apagado, sacá `func_0029C800`: el fundido del script ya deja el texto en
  alpha 0. Lo dejé porque no lo puedo verificar sin jugar.
- En el estado 16 el `C550(1)` no llega a hacer nada raro si el cartel ya venía cerrado: `29C550.c:15-17`
  sale enseguida con flag 8.

### e.2 `port/full/plat_autosave.c` — global + setter (aditivo)

```diff
--- a/port/full/plat_autosave.c
+++ b/port/full/plat_autosave.c
@@ -10,6 +10,14 @@
 
 static int sAuto = -1;
 
+/* F3: 1 mientras el autoguardado esta guardando (lo dibuja ui.cpp como un discosito en la esquina).
+   Vive aca y no en gs_draw.c para que el enlace funcione tambien con BT2_NO_GS=1. */
+volatile int gUiAutosave;
+
+void Port_AutosaveIcon(int on) {
+    gUiAutosave = (on != 0);
+}
+
 int Port_Autosave(void) {
     if (sAuto < 0) {
         const char *e = getenv("BT2_AUTOSAVE");
```

### e.3 `port/full/gs/ui.h` — declaración

```diff
--- a/port/full/gs/ui.h
+++ b/port/full/gs/ui.h
@@ -54,6 +54,8 @@
    stylized glyphs), over the picture, in the game's own coordinates. gs_gpu.c fills the present rectangle (the
    letterboxed 512x448 picture in window pixels); the game's menu fills the name's rectangle (game pixels) and
    which strip image to show, each frame it draws a stage name. ui.cpp combines them. */
+extern volatile int gUiAutosave; /* F3: el juego esta autoguardando; ui.cpp dibuja un disco chico en la esquina */
+
 extern volatile int gUiPresentX, gUiPresentY, gUiPresentW, gUiPresentH; /* window pixels */
 extern volatile int gUiNameX, gUiNameY, gUiNameW, gUiNameH;            /* game pixels */
 extern volatile int gUiNameIdx;   /* strip image to show; < 0 = none */
```

### e.4 `port/full/gs/ui.cpp` — el ícono (sin ventana)

```diff
--- a/port/full/gs/ui.cpp
+++ b/port/full/gs/ui.cpp
@@ -545,14 +545,37 @@
     SDL_EndGPURenderPass(pass);
 }
 
+/* F3: el disco del autoguardado: dos circulos en la esquina inferior derecha de la imagen, en pixeles del juego
+   (512x448) escalados como el overlay de nombres. Sin ventana, sin textura, sin tocar el juego. */
+static void autosave_disk(void) {
+    ImDrawList *dl;
+    float sc, x, y, r;
+
+    if (gUiPresentW <= 0 || gUiPresentH <= 0) {
+        return;
+    }
+    dl = ImGui::GetForegroundDrawList();
+    sc = (float)gUiPresentW / 512.0f;
+    x = (float)gUiPresentX + 486.0f * sc;
+    y = (float)gUiPresentY + 420.0f * sc;
+    r = 13.0f * sc;
+    dl->AddCircleFilled(ImVec2(x, y), r, IM_COL32(235, 235, 235, 200));
+    dl->AddCircleFilled(ImVec2(x, y), r * 0.22f, IM_COL32(40, 40, 45, 230));
+    dl->AddCircle(ImVec2(x, y), r, IM_COL32(20, 20, 25, 220), 0, 2.0f * sc);
+}
+
 void Ui_DrawGL(void) {
-    if (!sReady || !sGL || !sOpen) {
+    if (!sReady || !sGL || (!sOpen && !gUiAutosave)) {
         return;
     }
     ImGui_ImplOpenGL3_NewFrame();
     ImGui_ImplSDL3_NewFrame();
     ImGui::NewFrame();
-    build();
+    if (sOpen) {
+        build();
+    } else {
+        autosave_disk();
+    }
     ImGui::Render();
     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 }
@@ -561,8 +584,9 @@
     int nameOn = gUiNameReady != 0 && gUiNameIdx >= 0 && gUiNameIdx < (int)sNameCount;
     int songOn = gUiSongReady != 0 && gUiSongIdx >= 0 && gUiSongIdx < (int)sSongCount;
     int overlay = nameOn || songOn;
+    int icon = gUiAutosave != 0;
 
-    if (!sReady || (!sOpen && !overlay)) {
+    if (!sReady || (!sOpen && !overlay && !icon)) {
         return;
     }
     ImGui_ImplSDLGPU3_NewFrame();
@@ -594,6 +618,9 @@
                          ImVec2(1.0f, (float)(gUiSongIdx + 1) / (float)sSongCount));
         }
     }
+    if (icon) {
+        autosave_disk();
+    }
     if (sOpen) {
         build();
     }
```

(El helper `autosave_disk()` va antes de `void Ui_DrawGL(void)`; ya está incluido en el diff de
arriba. Usa sólo `ImGui::GetForegroundDrawList()`: ni ventana, ni fuente, ni textura.)

Los cuatro diffs se verificaron con `patch -p1 --dry-run` sobre copias en `/tmp/f3m/` (los cuatro aplican
limpios); el proyecto no se tocó. Igual conviene revisarlos a ojo: el build no se corrió.

Build y prueba (no ejecutado):

```
cd BT2-Recomp && BT2_IRFIX=1 scripts/capped.sh 8G python3 port/tools/build_full.py --jobs 2 --only 3E51F8
scripts/capped.sh 8G python3 port/tools/link_full.py
# instalar sólo con el juego cerrado (pgrep -x bt2), guardando el binario anterior en backups/
```

Qué mirar el usuario: menú pausa → Memory Card → Save (o el punto de autoguardado de siempre): al apretar
"Save" el cartel debe fundirse en ~0,4 s y no volver; durante ~7,5 s se ve el disquito abajo a la derecha y al
final se vuelve al menú (y el save se escribe igual que ahora). Probar también con `BT2_AUTOSAVE=0`: el cartel
tiene que comportarse como siempre.

---

## (f) Lo que NO pude confirmar sin correr el juego

1. **Que con `C550(1)` no quede ningún resto visible** (un prim del script `fr_out` a medio animar, o el panel
   con varios strips donde `placa+0x34` sólo gobierna el primero). Deduje el layout de `2784E0.c:26-27` y del
   uso en `29BB88.c:43`/`29C1E8.c:43-54`, pero no lo vi en pantalla.
2. **Que reabrir la pantalla de memory card después del autoguardado quede bien**: `fx()` (`3E4CF8.c:32-38`)
   vuelve a llamar `C550(0)`, que rebobina el script (`func_0026EA88`) y reasigna el flag a 4. Debería
   alcanzar, pero no lo probé.
3. **El aspecto real de `mc_icon_saveload`** (nunca lo vi; sólo sé nombre, dueño y tamaño de celda 64×64).
4. **El camino ImGui del port sin la ventana de ajustes**: `Ui_Draw`/`Ui_DrawGL` ya tienen la rama `overlay`,
   pero en BT2 nadie la usó (`gUiNameIdx` nunca se setea) → es código nuevo en la práctica, sin probar.
5. **Si el enlace de DMA por frame tolera saltear `func_0029C1E8`** (sólo importa para la Opción 2, que no
   recomiendo).
6. **Los tiempos exactos**: asumí 1 paso de estado por frame y 60 Hz; el ritmo real del menú (vblank) no lo
   medí. Y no verifiqué si el renderer por software (`BT3_SW_WINDOW`) llega a dibujar algo del ícono (no usa
   ImGui).
7. **El SE de cierre** al comienzo del autoguardado (`29C550.c:21`, SE 5): es comportamiento del juego, pero
   puede sonar raro; no lo escuché.
