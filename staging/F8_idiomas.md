# F8 — Idiomas (i18n): qué hace Tenkaichi3Decomp y qué soporta BT2

Fecha: 2026-11-11. Solo lectura: no se modificó ni compiló nada del proyecto.
Material: clon de T3D en `/tmp/opencode/t3d` (commit `20a8655`), código del port en
`BT2-Recomp/`, datos USA en `BT2-test/gamedata` (AFS `ZS2US_1/2.AFS`).

## 0. Resumen en cinco líneas

- **T3D no inventó i18n**: usa dos mecanismos del juego original. Las **voces** son el bit 0 del
  save (`gSaveData->flags`, +0x1608 en BT3), que edita la pantalla de opciones del propio juego.
  El **texto** sale de `gProgress->unk0` (0/1) en el handler del comando 701, que pide
  `story + 0x231` (inglés) o `story + 0x263` (japonés). El port de T3D no expone ese segundo
  valor: `Progress_Init` deja `gProgress` en cero y se juega en inglés.
- BT2 USA también tiene **dos juegos de voces** en el disco y **un solo idioma de texto**
  (inglés). La bandera de idioma de BT2 es el **bit 0 de `gSaveData + 0x1008`**, no +0x1608:
  1 = voces inglesas (default del save nuevo), 0 = voces japonesas. Es la opción
  "Japanese voice on/off" del menú de sonido del juego.
- Esa bandera **no cambia el texto**. Los 535 packs de texto de la historia
  (AFS `0x319..0x541`) son UTF-16LE en inglés y el id lo trae fijo el guion GSC; el handler
  `func_002A70F8` no mira +0x1008.
- El port **ya respeta la bandera**: las lecturas están en `port/eq/*.c` y la capa ADX carga el
  id que el juego pide. El selector ya existe en el menú del juego (Opciones → Sonido →
  Japanese voice). Lo más barato es usarlo; si se quiere en F1, es un checkbox que escribe el
  mismo bit.
- **No hay selector de texto que replicar** en el disco USA: no existe el segundo juego de
  textos. Traducir al español sería una capa de traducción (pisar los packs en RAM o
  reemplazarlos), no un selector entre idiomas ya presentes.

---

## 1. Tenkaichi3Decomp: cómo cambia de idioma

### 1.1 Voces: bit 0 del save, editado por el menú del juego

La opción está en la pantalla de sonido del propio juego, que T3D decompiló como C matching:

- `include/menu/menu_x.h:183` — `#define OPT_ITEM_VOICE 15 /* sound page: voice language */`.
- `src/menu/menu_x_c.c:200-203` — lista de estados del menú; el 15 es el idioma de voces.
- `src/menu/menu_x_c.c:587-593` — al entrar al ítem, el valor mostrado es
  `gOption->value = (gSaveData->flags ^ 1) & 1` (el bit invertido).
- `src/menu/menu_x_c.c:1158-1168` — al confirmar:
  - valor 0 → `gSaveData->flags |= SAVE_FLAG_VOICE` (primera opción, la que queda por defecto);
  - valor 1 → `gSaveData->flags &= ~SAVE_FLAG_VOICE`;
  - `gOption->dirty = 1` (al salir, el juego ofrece guardar).
- `src/menu/menu_x_c.c:2115-2121` — el "reset" de sonido vuelve a poner
  `gSaveData->flags |= SAVE_FLAG_VOICE`.
- `include/sys/save.h:36` — `#define SAVE_FLAG_VOICE 1`, con el comentario "set = file base
  0xCC32, clear = 0x8D4E". El default del save nuevo tiene los bits 0-2 en 1
  (`include/sys/save.h:39`, `SAVE_FLAG_DEFAULT 7`), y el release USA arranca en inglés: por eso
  **set = inglés, clear = japonés** en este build (T3D lo anota como "presumably English",
  `docs/systems/save_data.md:35`).

Qué se carga según el bit (todo son archivos del AFS, no texto):

- Voces de personaje en pelea: `src/battle/battle_load.c:408` y `:503-504` piden
  `BTL_FILE_VOICE` (0xBDA + personaje) o `BTL_FILE_VOICE_ALT` (0xC7B + personaje) según
  `gSaveData->flags & SAVE_FLAG_VOICE`; las constantes están en
  `include/battle/battle_work.h:123-124`.
- Líneas de voz de historia: `src/battle/btl_script.c:398-405` — base 0xD48 o 0x47E0, más
  `story * 300 + line` (dos juegos de 300 líneas por historia y por idioma).
- Locutor: `src/battle/hud_e.c:139-146` — base 0x10B34 (inglés) o 0x10B6C (japonés).
- Voces de menú: `src/battle/view_b_c.c:33-49` — `Voice_Play(0, base + line, ...)` o
  `base + line + VOICE_LANG2_OFFSET` (0x55C, `include/battle/view_b.h:182`).
- Otras partes (bobj, lip data) usan el mismo bit:
  `src/battle/btl_script_cmd.c:476-489` (comando 702, lips `story + 0x295` / `+0x2C7`),
  `src/battle/bobj_a.c:1899`, `include/battle/bobj_b.h:256`.

El bit **no** se guarda en el port: se guarda en el save del juego (bloque de 0x4000 que la
capa de memory card copia/pega entero). La pantalla de opciones es del juego, no del port.

### 1.2 Texto: `gProgress->unk0`, sin selector en el menú

El comando 701 ("load text") del guion de pelea:

- `src/battle/btl_script_cmd.c:457-474`:

```c
s32 BtlScriptCmd_LoadText(u32 phase, void *taskWork) {
    ...
    base = -1;
    switch (gProgress->unk0) {
    case 0: base = 0x231; break;
    case 1: base = 0x263; break;
    }
    BtlScript_RequestTextFile(base + BtlScript_GetStory());
    ...
}
```

- `src/battle/btl_script.c:281-283` — `gBtlScript.textFile = File_Request3(id, NULL, 0)`.
- `src/battle/btl_script.c:286-290` — `BtlScript_GetText(n)` indexa `file[n+1]`; el texto es
  16 bits "high byte first" (`docs/systems/menu_support.md:83`).
- El comando 702 elige el archivo de labios con el **bit de voces** (no con `unk0`):
  `src/battle/btl_script_cmd.c:476-489` y `docs/systems/script.md:90-91`.

**Quién escribe `gProgress->unk0`**: no aparece en el C decompilado del clon (solo lecturas en
`btl_script_cmd.c`, `bobj_a.c:2336`, `battle_load.c:596`). El port lo deja en 0 porque
`Progress_Init` hace `memset(gProgress, 0, sizeof(ViewProgress))`
(`src/battle/view_a_e.c:44-53`). Consecuencia: **T3D juega el texto en inglés**; el juego
original probablemente lo fija desde el idioma de la consola/región al arrancar, pero ese
escritor no está en el C del clon. No hay ítem de menú para el texto: el único ítem de idioma
es el de voces (15).

### 1.3 ¿T3D agregó textos propios?

No para i18n. Lo único que el port reescribe son los diálogos de memory card, y lo hace con
`port/tools/patch_texts.py` (textos en inglés que hablan de "save file" en vez de "memory
card"), instalados bajo `mods/` y aceptados por el verificador
(`port/src/plat_verify.c:41-46`). Es el equivalente del F5 de BT2, no un sistema de idiomas.
El port de T3D tampoco tiene un setting de idioma: su ventana de F1 no tiene nada de
`language` (grep en `port/src/gs/ui.cpp`).

### 1.4 ¿En caliente o al cargar?

- Voces de menú/locutor: se lee el bit en cada `Voice_Play` → la **siguiente línea** ya sale
  en el otro idioma.
- Voces de pelea: el banco/línea se pide al cargar el luchador o al disparar la línea; una
  línea ya cargada sigue en el idioma viejo, la siguiente cambia.
- Narración de historia: el id se pide al iniciar la escena (`btl_script_cmd.c` 701/702) → hay
  que **entrar a la escena siguiente** para que cambie.
- Texto: se pide una vez por historia/escena y queda apuntado en `gBtlScript.textFile`; no hay
  relectura en caliente.

---

## 2. BT2: qué hay realmente

### 2.1 La bandera y sus valores

En BT2 USA el bloque de save/work es `D_00387F2C` (puntero en la dirección PS2 `0x00387F2C`,
alojado por `func_00298438`, `src/auto/m2c_298438.c`). **No es el layout de BT3**: el área de
opciones arranca en `+0x1008`, no en `+0x1608`.

- Defaults del save nuevo: `port/eq/2982E8.c:52-60`:

```c
*(s32 *)(arg0 + 0x1008) = *(s32 *)(arg0 + 0x1008) | 1;  /* voces inglesas por defecto */
```

  y enseguida inicializa teclas en `+0x100C` / `+0x102C` y volúmenes en `+0x10A8..0x10B0`.
- Pantalla de sonido del juego: `port/eq/3E92E8.c`:
  - `:30` `#define JP_VOICE GW(0xE8)` (copia de trabajo del valor);
  - `:65-68` el reset pone `JP_VOICE |= 1` y `SW(0x1008) = JP_VOICE` (queda inglés);
  - `:228-235` comentario **"Japanese voice on/off"**: con derecha/izquierda,
    `VALUE != 0` → `SW(0x1008) &= ~1` (japonés), `VALUE == 0` → `SW(0x1008) |= 1`
    (inglés);
  - `:296` al entrar, `VALUE = (JP_VOICE ^ 1) & 1` (el checkbox se muestra invertido).

**Valores: bit 0 = 1 → voces inglesas; bit 0 = 0 → voces japonesas.** El default del save
nuevo (y el reset de sonido) es 1. Los bits 1 y 2 del mismo word son los flags de vibración
por pad (`port/eq/28C810.c:14-15`), no idioma; no confundirlos.

### 2.2 Qué se carga según la bandera

Todos los usos de `+0x1008 & 1` en el juego portado son **audio o arte**, ninguno es texto:

| Archivo | Línea | Qué elige |
|---|---|---|
| `port/eq/101608.c` | 27 | id de archivo ADX: `+0x74F3` (bit 1) vs `+0x3E43` (bit 0) |
| `port/eq/3DDB20.c` | 44 | lo mismo, para la línea de voz de pelea (100 por personaje) |
| `port/eq/1041A0.c` | 48 | ids `43939/44079` (0xABA3/0xAC2F), banco de sonido/voz |
| `port/eq/1043A8.c` | 55-56 | id `0xABA3`/`0xAC2F` |
| `port/eq/104628.c` | 43-46 | id `0xABA3`/`0xAC2F` |
| `port/eq/1048F0.c` | 17-20 | id `0xABA3`/`0xAC2F` |
| `port/eq/104C10.c` | 18-27 | id `0xABA3`/`0xAC2F` |
| `port/eq/10B0C8.c` … `10B398.c` | 17 | id `+0x37D8..` vs `+0x3BF1..` (menú/locutor) |
| `port/eq/2493C0.c` | 14 | id + `arg4` según bit |
| `port/eq/2A4F50.c` | 91 | id de voz `+0x13F6` (narración) |
| `port/eq/2A7400.c` | 62 | id de voz `+0x13F6` (narración) |
| `port/eq/2A7650.c` | 49-50 | id de voz `+0x13F6` (narración) |
| `port/eq/2AB7F0.c` | 11 | `0xABA3`/`0xAC2F` |
| `port/eq/25D190.c` | 115 | base 100 vs 0 en una tabla de sprites |
| `port/eq/25DB98.c` | 17 | base 0x64 vs 0 en otra tabla de sprites |
| `port/eq/3DD160.c` | 215 | bloque de sprites `+0x83` vs `+0x10C` |

Prueba de que los ids alternativos son audio: los archivos `0x3E43`, `0x74F3`, `0x37D8` y
`0x3BF1` del AFS empiezan con `80 00 00 24 … (c)CRI`, el header ADX. `0x74F3 - 0x3E43 = 0x36B0`
(14.000 ids), el tamaño del juego de voces japonés. `0xABA3`/`0xAC2F` no son ADX crudos
(empiezan con `03 00 00 00` y una tabla de offsets), pero se usan en el mismo circuito de
sonido/voz; no los decodifiqué.

### 2.3 El texto de BT2 USA es inglés y no depende de la bandera

- El guion GSC de cada historia pide el archivo de texto con el comando **0xFA4** (4004). El
  handler es `src/auto/m2c_2A70F8.c`:

```c
s32 func_002A70F8(s32 arg0) {
    if (arg0 == 0) {
        func_002A3A98(Gsc_GetInt());   /* id = operando del guion, sin mirar +0x1008 */
    }
    return 1;
}
```

- `port/eq/2A3A98.c:9` — `D_003B0F40 = func_00100ED0(a0, 0, ...)`: pide el AFS por id.
- El comando **0xFA5** (4005) carga hasta 8 archivos de texto para ventanas
  (`src/auto/m2c_2A78F0.c`, `src/auto/perm_2A3BB8.c`); tampoco mira la bandera.
- Parseé los 760 GSC del AFS: 535 historias usan ids de texto **793..1345** (0x319..0x541),
  todos distintos y secuenciales. El rango siguiente, 0x542, es el font (`Fnt4`).
- Los packs 0x319..0x541 tienen el formato `u32 count; u32 offsets[count]` y strings
  **UTF-16LE con BOM `FF FE`**. Ejemplos leídos del AFS:
  - 0x319: "But now, an evil new menace has cast i…"
  - 0x31B: "That's definitely Kakarot. He looks…"
  - 0x31C: "N-No… He won't get away with this…"
- Barrido de los packs de texto (rango 0x319..0x541 y búsqueda de kana/kanji en packs con ese
  formato): **0 archivos con japonés**. No hay un segundo juego de textos en el disco USA.

Conclusión: la bandera de +0x1008 **no cambia el diálogo**. Si el jugador elige voces
japonesas, sigue leyendo subtítulos en inglés (es el comportamiento esperado del release USA:
texto inglés, voces inglesas o japonesas).

### 2.4 El port ya respeta la bandera

- Las lecturas de +0x1008 están en C (`port/eq/*.c`, tabla de arriba).
- La capa ADX del port (`port/full/plat_snd_adx.c`) carga el id que el juego pide; no hay una
  tabla de idioma propia que pise la decisión.
- La pantalla de opciones del juego está portada: `port/eq/3E92E8.c` (sonido) se llama desde
  `port/eq/3EA078.c:66`. O sea, **el selector ya está en el juego**: Opciones → Sonido →
  "Japanese voice".
- El port no tiene ningún setting de idioma en F1 (grep de `language`/`japanese`/`0x1008` en
  `port/full`: sin resultados).

### 2.5 Ojo: `include/sys/save.h` es el layout de BT3, no el de BT2

El header dice que `flags` está en `+0x1608`, `key` en `+0x160C`, `soundMode` en `+0x16A4`,
etc. En BT2 el área de opciones real está en **+0x1008**: `port/eq/2982E8.c:52-60` (defaults),
`port/eq/3E92E8.c` (menú de sonido), claves en +0x100C/+0x102C, volúmenes en +0x10A8..0x10B0.
El header vino del decompilado de BT3 y quedó desfasado. Cualquier código nuevo tiene que usar
`+0x1008` y no `+0x1608`. (Hoy no hay código vivo que use el `flags` de ese header para el
idioma; solo comentarios/typedefs. Pero es una trampa para el próximo cambio.)

---

## 3. La opción más barata para el port

### Opción 0 (cero código): usar el menú del juego

Opciones → Sonido → "Japanese voice". Es el mismo bit, ya funciona en el port, y el juego lo
guarda en el save cuando el jugador sale (o cuando el autoguardado F3 contesta que sí). No hay
nada que portar. Si esto no funcionara en la práctica, sería un bug del port, no una feature
faltante.

### Opción 1 (F1): checkbox que escribe el mismo bit

No hay que pisar ninguna tabla ni archivo del AFS. Alcanza con leer/escribir el bit 0 de
`gSaveData + 0x1008`. El port ya tiene el patrón de acceso a memoria PS2 por dirección
absoluta (`W(0x3876A4)` en `port/full/plat_fightlog.c`, `W(...)` en `port/full/plat_demo.c`).
`D_00387F2C` es un puntero cuya dirección es `0x00387F2C`; el bloque se valida contra el rango
de RAM.

**Diff propuesto (NO aplicado).** Archivo nuevo + checkbox en la pestaña Audio. `link_full.py`
compila todo `port/full/*.c` por glob (`port/tools/link_full.py:92`), así que no hay que tocar
el build.

```diff
--- /dev/null
+++ b/port/full/plat_lang.c
@@ -0,0 +1,44 @@
+/*
+ * F8: idioma de las voces.
+ *
+ * En BT2 (USA) el bit 0 de gSaveData + 0x1008 es la opcion "Japanese voice on/off" del
+ * juego: 1 = voces inglesas (default del save nuevo), 0 = voces japonesas. Es el mismo
+ * bit que edita la pantalla de opciones (port/eq/3E92E8.c). No hay bit de idioma de
+ * texto: el texto de la historia son packs AFS con id fijo (0x319..0x541, ingles).
+ *
+ * gSaveData lo aloja func_00298438 (port/eq/298438.c); su puntero vive en la direccion
+ * PS2 0x00387F2C.
+ */
+#include <stdint.h>
+
+#define SAVE_PTR_ADDR 0x00387F2Cu
+#define SAVE_OPTS_OFF 0x1008u
+#define SAVE_VOICE_EN 0x00000001u
+
+static volatile uint32_t *voice_flag(void) {
+    uint32_t save = *(volatile uint32_t *)(uintptr_t)SAVE_PTR_ADDR;
+    if (save < 0x00010000u || save >= 0x02000000u) {
+        return 0;
+    }
+    return (volatile uint32_t *)(uintptr_t)(save + SAVE_OPTS_OFF);
+}
+
+/* 1 = ingles, 0 = japones, -1 = el save todavia no esta alojado. */
+int Port_VoiceLangEnglish(void) {
+    volatile uint32_t *p = voice_flag();
+
+    return p == 0 ? -1 : (*p & SAVE_VOICE_EN) != 0;
+}
+
+void Port_VoiceLangSetEnglish(int english) {
+    volatile uint32_t *p = voice_flag();
+
+    if (p == 0) {
+        return;
+    }
+    if (english) {
+        *p |= SAVE_VOICE_EN;
+    } else {
+        *p &= ~SAVE_VOICE_EN;
+    }
+}
```

```diff
--- a/port/full/gs/ui.cpp
+++ b/port/full/gs/ui.cpp
@@ -390,7 +390,25 @@ static void video_tab(PortVideo &v) {
 }
 
+extern "C" int Port_VoiceLangEnglish(void);
+extern "C" void Port_VoiceLangSetEnglish(int english);
+
 static void audio_tab(PortVideo &v) {
     ImGui::SliderInt("Music", &v.music, 0, 200, "%d%%", ImGuiSliderFlags_AlwaysClamp);
     ImGui::SliderInt("Sound effects and voices", &v.effects, 0, 200, "%d%%", ImGuiSliderFlags_AlwaysClamp);
     ImGui::SetItemTooltip("Takes effect with the next sound that starts.");
+    ImGui::Spacing();
+    {
+        int english = Port_VoiceLangEnglish();
+        if (english < 0) {
+            ImGui::TextDisabled("Voice language: waiting for the save data.");
+        } else {
+            bool japanese = english == 0;
+            if (ImGui::Checkbox("Japanese voices", &japanese)) {
+                Port_VoiceLangSetEnglish(japanese ? 0 : 1);
+            }
+            ImGui::SetItemTooltip("Same setting as the game's Options > Sound. Menu voices and the announcer "
+                                  "change now; fighter voices change with the next line; story voices with the "
+                                  "next scene. Text stays English.");
+        }
+    }
 }
```

Notas del diff:

- Es una escritura de 32 bits alineada desde el hilo de render. El juego sólo escribe ese word
  en la pantalla de opciones (que además copia el bloque a `G` y lo devuelve al salir:
  `port/eq/3E68D0.c:72`, `3E7738.c:245-246`). Si se quiere evitar del todo la carrera, la
  variante estricta es un `volatile int gPortVoiceLangRequest` en `plat_gs.c` aplicado al
  principio de `Port_VBlank` (`port/full/plat_gs.c:93`), como se quiso hacer con
  `gPortUnlockAll`; el checkbox sólo setea el pedido.
- No persiste por sí solo: el bit vive en el save en RAM. Si el jugador no guarda, se pierde
  al reiniciar; si el juego carga otro save, lo pisa. Para que sea persistente, usar la
  pantalla de opciones del juego (o dejar que el autoguardado F3 escriba el save).
- Si se toca mientras la pantalla de opciones está abierta, el "copiar de vuelta" de esa
  pantalla puede pisar el cambio. Mejor usarlo desde el menú principal o en pausa, no dentro
  de Opciones.

### Texto: no hay opción barata

No existe un segundo juego de textos en el disco USA. Para español habría que:

1. Traducir los 535 packs de historia 0x319..0x541 (y los textos de menús, que están en otros
   packs comprimidos), y
2. pisar la copia en RAM justo después de `func_00100ED0`/`func_002A3A98` (mismo patrón que
   `port/full/plat_text.c` para los 49 mensajes de memory card), o reemplazar los packs en
   `gamedata`/`mods`.

Eso es una feature de traducción, no un selector de idioma. No lo propongo como F8.

---

## 4. Riesgos

1. **Texto en un solo idioma.** El release USA es English-only en texto. Un checkbox
   "Español" no puede apoyarse en el disco: no hay archivos que cargar. Venderlo como
   "selector de idioma" sería engañoso; como mucho, selector de **voces**.
2. **Voces:** el bit cambia bancos ADX completos. Si se cambia en medio de una pelea, una línea
   ya cargada sigue en el idioma anterior; la siguiente sale en el nuevo. No hay crash
   esperado (ambos sets de archivos existen), pero conviene hacerlo en menú/pausa.
3. **Save del usuario.** El bit es parte del save de 0x4000. Si el port lo cambia en RAM y
   después el juego guarda (incluido el autoguardado F3, que contesta "sí"), el cambio queda
   persistido en la memory card. No es pérdida de datos, pero es una opción del usuario que se
   modifica sin pasar por el menú. Si se agrega un setting propio del port
   (`bt2_settings.txt`) que fuerce el idioma, va a pelear con el save: el save gana al cargar.
4. **Offset equivocado.** `include/sys/save.h` documenta +0x1608 (BT3). En BT2 es +0x1008.
   Copiar el código de T3D tal cual escribiría otra parte del save (posible corrupción de
   opciones). El diff de arriba usa +0x1008.
5. **Pantalla de opciones abierta.** El menú de sonido copia el bloque de opciones a su propio
   `G` y lo devuelve al confirmar (`3E68D0.c:72`, `3E7738.c:245-246`). Un cambio desde F1
   mientras esa pantalla está abierta puede perderse.
6. **Voces japonesas no verificadas de oído.** Inferí el mapeo del texto de la opción
   ("Japanese voice on/off") y del default inglés; no decodifiqué el audio de 0x3E43 vs 0x74F3.
   Si el usuario prueba y suenan al revés, el mapeo del checkbox se invierte (una línea).

---

## 5. Evidencia y descartes

### Verificado leyendo código/asm/datos

- El handler de texto de BT2 no mira +0x1008: `src/auto/m2c_2A70F8.c` (comando 0xFA4) y
  `src/auto/m2c_2A78F0.c` (0xFA5); `port/eq/2A3A98.c:9`.
- El mapeo de ids de texto de las 535 historias: parser propio sobre los 760 GSC del AFS;
  comandos 0xFA4/0xFA5 con operandos resueltos por la tabla `GSDT`.
- Los packs 0x319..0x541 son texto UTF-16LE inglés (BOM `FF FE`, strings "But now…",
  "That's definitely Kakarot…", etc.).
- Los archivos 0x3E43/0x74F3/0x37D8/0x3BF1 son ADX (`(c)CRI`); el bit 0 elige entre ellos.
- El default de BT2 pone `+0x1008 |= 1` (`port/eq/2982E8.c:54`) y la opción del menú lo
  invierte para "Japanese voice" (`port/eq/3E92E8.c:228-252`).
- T3D: comando 701 elige 0x231/0x263 por `gProgress->unk0` (`src/battle/btl_script_cmd.c:457-474`);
  el ítem 15 del menú edita el bit de voces (`src/menu/menu_x_c.c:1158-1168`, `:2115-2121`).
- T3D no tiene un setting de idioma en el port: `grep -i lang port/src` no encuentra nada.

### Descartado y por qué

- **"+0x1008 es un flag de texto en BT2"**: todos los usos son ids ADX, tablas de sprites o el
  menú de sonido; el handler de texto usa un operando fijo del guion. Descartado.
- **"BT2 USA tiene los textos japoneses en el AFS"**: no aparecen en los packs de historia ni en
  el formato de texto; el rango 0x319..0x541 es inglés y el siguiente id es el font. Descartado
  para la historia (los menús comprimidos no los descomprimí, pero el release USA no tiene
  selector de texto).
- **"T3D agregó textos propios para i18n"**: sólo `patch_texts.py` reescribe los diálogos de
  memory card en inglés; no hay tabla de traducción ni selector. Descartado.
- **"El port ignora la bandera"**: las lecturas y la pantalla de opciones están en C portado;
  la capa ADX carga el id pedido. Descartado.
- **"Hay que tocar el AFS o el save en disco"**: el cambio es un bit en RAM del save; se
  persiste recién cuando el juego guarda. Descartado.
- **"Se puede cambiar el texto en caliente"**: el texto se pide por escena y queda apuntado en
  `gBtlScript.textFile`; no hay relectura. Descartado.

### No verificado

- El idioma real del audio de los ADX alternativos (no los decodifiqué; el mapeo sale de la
  opción y del default).
- Que la pantalla Opciones → Sonido sea alcanzable y funcione en el build actual (está en C,
  pero no la probé jugando).
- El comportamiento exacto de un cambio de bit en medio de una pelea (inferido de que BT2 pide
  las voces por línea/archivo, no por banco cargado).
- Los menús comprimidos de `DBZP.BIN`/packs: no los descomprimí; podría haber arte o rótulos
  alternativos, pero no un juego completo de textos.

---

## 6. Referencias rápidas

| Qué | Dónde |
|---|---|
| T3D: opción de voces (ítem 15) | `src/menu/menu_x_c.c:200-203`, `:587-593`, `:1158-1168`, `:2115-2121` |
| T3D: flag de voces | `include/sys/save.h:36-39` |
| T3D: texto por `gProgress->unk0` | `src/battle/btl_script_cmd.c:457-474` |
| T3D: voz de historia por idioma | `src/battle/btl_script.c:398-405` |
| T3D: Progress_Init deja unk0=0 | `src/battle/view_a_e.c:44-53` |
| T3D: docs | `docs/systems/script.md:90-91`, `docs/systems/save_data.md:35`, `docs/systems/menu_overlay.md:790` |
| BT2: defaults del save | `port/eq/2982E8.c:52-60` |
| BT2: menú "Japanese voice" | `port/eq/3E92E8.c:30`, `:65-68`, `:228-252`, `:296` |
| BT2: carga de texto por id fijo | `src/auto/m2c_2A70F8.c`, `port/eq/2A3A98.c:9` |
| BT2: lecturas del bit | `port/eq/101608.c:27`, `3DDB20.c:44`, `2A4F50.c:91`, `2A7400.c:62`, `2A7650.c:49-50`, `10B0C8.c:17`… |
| BT2: puerta de la UI F1 | `port/full/gs/ui.cpp:524-531` (tabs), `:392-396` (Audio) |
| BT2: patrón de pedido desde F1 | `port/full/plat_gs.c:247` (`gPortUnlockAll`), `port/full/gs/ui.cpp:398-430` |
| Build del port | `port/tools/link_full.py:92` (glob de `port/full/*.c`) |
