# F3 — Autoguardado: estados de la máquina de diálogo de memory card (BT2)

Fecha: 2026-11-11. **Solo lectura**: no se editó ni compiló nada del proyecto.

Máquina analizada: `port/eq/3E51F8.c` (`func_003E51F8`, overlay `0x3E51F8..0x3E6658`).
Asm usado: `/tmp/opencode/ovl.dis` (overlay combinado; el `full.asm` **no** la contiene: el `.text` del
`SLUS_214.41` termina en `0x33B67C` y esta función vive en un overlay). Copia del rango:
`/tmp/opencode/f3_3E51F8.dis`.

Referencia BT3: `/tmp/opencode/t3d/src/sys/mcflow_a.c` estados `0xC` (msg `0xD`) y `0xD` (msg `0xE`), que
hacen `choice = 1; timer = 0xC`; estado `0xE` (msg `0xF`, "tarjeta cambiada") **no** se autoguarda para no
hacer bucle. `port/src/plat_autosave.c` de BT3 (env `BT3_AUTOSAVE`, setting `autosave`, default ON).

---

## 1. Conclusión corta

| Pregunta | Estado | MSG (campo `0x10C`) | Texto real (tabla) |
|---|---|---|---|
| **¿Guardar?** (datos de juego) | **16** (`case 16`) | 28 | `"Save game data?"` |
| **¿Guardar?** (ajustes cambiados) | **28** (`case 28`) | 37 | `"Settings have been changed. Save the changed settings?"` |
| **¿Sobrescribir?** (ya existe) | **18** y **32** | 21 | `"Save data already exists. Would you like to overwrite the data?"` |
| **NO autoguardar** (error tarjeta cambiada) | **27** | 24 | `"The memory card (PS2) has been replaced. Would you like to overwrite the data?"` |
| **NO autoguardar** (formatear) | **23** | 13 | `"Memory card (PS2) is unformatted. Format memory card (PS2)?"` |
| **NO autoguardar** (es carga, no guardado) | **13** | 4 | `"Current settings will be lost if you load this save data. OK?"` |

Los valores a forzar son **exactamente los de BT3**: `ANSWER = 1; TIMER = 12` (= `0xC`), sólo si
`ANSWER == 0`. Con eso el flujo sigue el mismo camino que un "Sí" manual: la espera de 12 cuadros, el
`func_00288348()` (reset del paso de la tarjeta, `gMcCardStep = 0`), el cartel `"Checking memory card..."`,
el `"Saving data..."` del estado 20 y el `"Save successful."` del 21.

**Candidatos que había en el informe previo (`staging/F3F6_desde_tenkaichi3decomp.md:425`): estado 13 y
27/28. Quedan descartados 13 y 27** (ver §2 y §5).

---

## 2. Cómo se identificó cada texto (evidencia)

Los textos **no** están en el ELF ni en el AFS en ASCII: van en UTF-16LE dentro del recurso del menú,
comprimido. Camino completo:

1. `port/eq/1021E8.c:25` → `*(s32 *)(D_003876A4 + 4) = 0x544` (base de ids de los recursos de menú).
2. `port/eq/3E3B98.c:30` → `func_100D58(*(D_003876A4+4) + 0xC, 0, 1)` = **id 0x550**.
   (`func_100D58` reparte ids < `0x33B2` al archivo 0; `0x33B2` = 13234 = cantidad de entradas de
   `ZS2US_1.AFS`, así que id `0x550` = entrada `0x550` de `gamedata/DATA/ZS2US_1.AFS`.)
3. La entrada `0x550` es un contenedor: `u32 count=4`, `u32 header=0x40`, 4 offsets de fin (`0x8AD00`,
   `0xF1E40`, `0x1B46C0`, `0x22AB40`); cada sub-archivo empieza con `u32 destSize`, `u32 packedSize` y un
   stream comprimido (el descompresor es `func_002B24C8`, `port/eq/2B24C8.c`).
4. Descomprimí el sub-archivo 0 (`dest 0x12B340`, `packed 0x8ACB3`) con una traducción 1:1 de
   `func_002B24C8` (`/tmp/opencode/f3_lz.py`; salida exacta de `0x12B340` bytes → sin corrimiento).
5. Ese bloque tiene su propia tabla de bloques: `u32 count=0x14`, `u32 header=0x80`, 20 offsets.
   `port/eq/3E3D38.c:99-102`:
   - `*(u8**)(G+0x10) = P + (*(s32*)(P+0x40) & ~3)` → `P + 0xFCC80` = **tabla de mensajes**, que se pasa a
     `func_0029BB88(..., arg1)` y queda en `D_00387DA0+4` (`port/eq/29BB88.c:45`).
   - Esa tabla es `u32 count = 49` + 49 offsets (`u32`) a strings **UTF-16LE** (arrancan con `FF FE`).
6. Cruce estado↔texto: **el texto del `MSG=n` es la entrada `n+1` de la tabla** (la entrada 1 es
   `"MEMORY CARD slot 1"`, la 2 `"...slot 2"`, la 3 `"...slot 1 and ...slot 2"`, que son los 3 títulos del
   diálogo). El ajuste es exacto en los 25 estados y además con otras máquinas que usan la misma numeración
   (p.ej. `port/eq/3BF748.c:242` `CODE = 29` mientras escribe → `"Saving data..."` = entrada 30).
   *No pude determinar el porqué del +1*: el dibujante de mensajes (`0x29BD58`) indexa `base[msg]` sin sumar,
   mientras el de títulos (`port/eq/29BF08.c:40-41`, asm `29bdf0..29bdf8` con `lw v0,4(v1)`) indexa
   `base[idx+1]`. Lo más probable es que la primera palabra (el contador `49`) sea cabecera de la tabla.
   Para el arreglo no importa: la identificación de los estados sale del **flujo** (§3), no del texto.

**Dato decisivo del flujo (no del texto):** `func_003E4CF8` (`port/eq/3E4CF8.c:63-68`) abre un menú de 2
ítems y escribe `STATE = 0x10 (16)` en el ítem 0 y `STATE = 0xD (13)` en el ítem 1. Es decir **16 = "Save"**
y **13 = "Load"**; 13 desemboca en `5 → 9 ReadFile → 10 "Load successful."` y 16 en `17 → 31 → 18/32 → 20
WriteSave`. Estado 29 = `"Exit saving?"` (Sí → salir, No → 16/28) y 30 = `"Exit loading?"` (Sí → salir,
No → 13), lo que cierra el círculo.

---

## 3. Tabla de estados (2..33)

Leyenda: "MSG" = valor del campo `0x10C`; "texto" = entrada `MSG+1` de la tabla (§2).
"Entrada/Salida" = qué la lleva ahí / a dónde va.
Los estados con `func_0029C640(0)` son preguntas de 2 opciones: opción 0 = `ANSWER = 1` (>0), opción 1 =
`ANSWER = -2` (<0). `ANSWER = -1` (cancelar) no ocurre: todos pasan `arg0 = 0`.

| Estado | MSG | Texto (tabla) | Entrada | Opciones | Al confirmar (Sí) | Al No (-2) |
|---|---|---|---|---|---|---|
| 2 | 5 | No memory card (PS2) inserted. | cualquier error de tarjeta | sólo OK (`PAD_OK_OR_BACK`) | → 29 (`0xD0&8`) si no → 30/29 según `0xDC` | — |
| 3 | 7 | Game data not found in memory card (PS2). | 7 | sólo OK | → 30 (y limpia `SYS_FLAGS & 0x400`) | — |
| 4 | 16 | Not enough free space. A memory card (PS2) with 75KB free is required. | 17/31 | sólo OK | → 29, `ANSWER=0` | — |
| 5 | 34 | Checking memory card (PS2)... | 13 | — | timer 120 → `func_00289C98` (¿están los 3 archivos?) → 9; si no: 2/7 | — |
| 7 | 34 | Checking memory card (PS2)... | 5 | — | `func_0028A578` (getdir) → 12 si `MC_STATUS==1`, si no 3; error → 2 | — |
| 8 | 34 | Checking memory card (PS2)... | 17 | — | getdir → 19; error → 2 | — |
| 9 | 8 | Loading data. Do not remove... | 5 | — | `McCard_ReadFile(0,BUF,0x4000)` → 12 (si `MC_FLAGS&1` o checksum malo) / copia + 10 / error 11 | — |
| 10 | 10 | Load successful. | 9 | sólo OK o timer | → 14 | — |
| 11 | 9 | Load Failed. Please check memory card (PS2) and try again. | 9/11 | sólo OK | → 30 | — |
| 12 | 25 | Load Failed. Memory card (PS2) error! Data may be corrupt. | 9 | sólo OK | → 30 | — |
| **13** | **4** | **Current settings will be lost if you load this save data. OK?** | **menú "Load" (3E4CF8)** | **2** | **`TIMER=12` → 5 (carga) + `func_00288348`** | **→ 30** |
| 14 | — | — | 10/21/29/30/15 | — | transición: `C7C0(0), C550(1), C640(0)` → 15 | — |
| 15 | — | — | 14 | — | cierra ventana: `0x11C=1`, `STATE=0`, SE `fr_saveload_out`, `func_003E4B10()` | — |
| **16** | **28** | **Save game data?** | **menú "Save" (3E4CF8), 29 (Sí a "Exit saving?" y `0xD0&4`)** | **2** | **`TIMER=12` → 17 (guardado)** | **→ 29** |
| 17 | 34 | Checking memory card (PS2)... | 16, 27, 28 | — | timer 120: `func_00289C98` (3 archivos) → 31; si no: 2 / 23 / 8 / 4 / **27** | — |
| **18** | **21** | **Save data already exists. Would you like to overwrite the data?** | **31 (no hace falta espacio nuevo)** | **2** | **→ 20 (WriteSave)** | **→ 29** |
| 19 | 18 | Creating save file. Do not remove... | 8/25 | — | `McCard_CreateSave` → 20; error → 22 | — |
| 20 | 29 | Saving data. Do not remove... | 18/19/32/33 | — | **`McCard_WriteSave(0, D_00387F2C, 0x4000, BUF_END)`** → 21 | — |
| 21 | 30 | Save successful. | 20 | sólo OK o timer | → 14 | — |
| 22 | 31 | Save failed. Please check memory card (PS2) and try again. | 19/20/33 | sólo OK | → 29 | — |
| **23** | 13 | Memory card (PS2) is unformatted. **Format** memory card (PS2)? | 17/31 | 2 | → 24 (**formatea**) | → 29 |
| 24 | 12 | Formatting memory card (PS2)... | 23 | — | `McCard_Format` → 25 / 26 | — |
| 25 | 14 | Format successful. | 24 | — | timer → 19 (crear) | — |
| 26 | 15 | Format failed! ... | 24/25 | sólo OK | → 29 | — |
| **27** | **24** | **The memory card (PS2) has been replaced. Would you like to overwrite the data?** | **rama de polling de 17 con `MC_STATUS != 0`** | **2** | **`McCard_Probe` → 17 (reintenta)** | **→ 29** |
| **28** | **37** | **Settings have been changed. Save the changed settings?** | **29 (Sí a "Exit saving?" y `!(0xD0&4)`)** | **2** | **`TIMER=12` → 17 + `func_00288348`** | **→ 29** |
| 29 | 47 | Exit saving? | 2/3/4/11/12/18/22/23/26/27/28/32 | 2 | → 14 (salir) | **→ 16 o 28** (`0xD0&4`) |
| 30 | 48 | Exit loading? | 2/3/4/11/12 | 2 | → 14 (salir) | **→ 13** |
| 31 | 34 | Checking memory card (PS2)... | 17 | — | timer → 4 / 18 / 32 / 23 / 2 | — |
| **32** | **21** | **Save data already exists. Would you like to overwrite the data?** | **31 (`MC_NEEDED > 0` y hay espacio)** | **2** | **→ 33 (CreateSave) → 20 (WriteSave)** | **→ 29** |
| 33 | 29 | Saving data. Do not remove... | 31 | — | `McCard_CreateSave` → 20; error → 22 | — |

Notas:
- `MSG` en los estados 18 y 32 es el mismo (21): BT2 muestra **la misma pregunta de sobrescritura** tanto si
  el archivo ya está y no crece (18: sólo write) como si hay que crearlo/agrandarlo (32: create + write).
- El estado 2 tiene un único botón y dos placas; no es pregunta (usa `PAD_OK_OR_BACK`, no `func_0029C640`).
- El estado 4 también es sólo "OK" (`PAD_OK_OR_BACK`): el texto de 75KB es informativo, no pregunta.
- `func_00288348` (`port/eq/288348.c`) es sólo `gMcCardStep = 0` (reset del paso de la tarjeta).

---

## 4. Verificación contra el asm (fidelidad del C y campos forzados)

Campos (`D_004279CC`, confirmados en asm): `MSG = +0x10C (268)`, `STATE = +0x110 (272)`,
`ANSWER = +0x114 (276)`, `TIMER = +0x118 (280)`.

| Caso | Asm | Qué hace |
|---|---|---|
| 16 (`MSG=28`) | `0x3E52E8..0x3E5348` | `MSG=28` en `0x3E5300`; `ANSWER>0` → `TIMER--` → al llegar a −1: `STATE=17` (`0x3E5334`), `TIMER=120` (`0x3E5338/40`), `ANSWER=0` |
| 18 (`MSG=21`) | `0x3E5700..0x3E5770` | `MSG=21` en `0x3E5710`; `McCard_Probe` = `jal 0x288538` en `0x3E5718`; fatal → `2`; Sí → `STATE=20` (`0x3E5768`) |
| 27 (`MSG=24`) | `0x3E5518..0x3E559C` | `MSG=24` en `0x3E5528`; Sí → `STATE=17`, `TIMER=120`, `ANSWER=0`, `McCard_Probe` (`0x3E5570`); No → `STATE=29` (`0x3E5598`) |
| 28 (`MSG=37`) | `0x3E5260..0x3E52E4` | `MSG=37` en `0x3E5278`; Sí → `STATE=17`, `TIMER=120` (`0x3E52AC/B8`); No → `29` (`0x3E52E0`) |
| 32 (`MSG=21`) | `0x3E6478..0x3E64E8` | `MSG=21` en `0x3E6488`; fatal → `2`; Sí → `STATE=33` (`0x3E64DC`) |
| 13 (`MSG=4`) | `0x3E58A8..0x3E5920` | `MSG=4` en `0x3E58C0`; Sí → `STATE=5`, `TIMER=120` (`0x3E58EC/F0`) |
| lectura de la respuesta | `0x3E6528..0x3E6544` | `ANSWER = func_0029C640(0)`, `TIMER = 12` — **este es el valor a imitar** |
| `func_0029C640` | `port/eq/29C640.c` | devuelve **1** (cursor 0 + confirmar), **-2** (cursor 1 + confirmar), **-1** (cancelar sólo si `arg0 != 0`; todos pasan 0). Confirmar además pone `D_00387DA0+0x54 |= 1` y suena el SE de OK |
| cursor | `port/eq/29C820.c` (`0x29C820`) | `D_00387DA0+0x58` y `+0x60`; el menú deja el cursor en **1** al entrar (`func_0029C820(1)`), así que el resaltado visual queda en la opción "No" aunque forcemos "Sí" (igual que en BT3) |

El C de `port/eq/3E51F8.c` es **fiel** al asm en todos estos estados (mismos valores, mismos destinos, mismo
orden `PROBE → fatal → ANSWER`). No hay bug de traducción que explotar acá.

---

## 5. Enganche propuesto (mínimo, 4 puntos)

Archivo `port/eq/3E51F8.c`. Forzar **antes** de los `if (ANSWER ...)` de cada caso, con guarda
`ANSWER == 0` (igual que BT3: `if (Port_Autosave() && choice == 0)`).

```diff
--- a/port/eq/3E51F8.c
+++ b/port/eq/3E51F8.c
@@ -11,6 +11,10 @@
 extern s32 D_003B0C34;
 extern u8 gMcCardPort[];
 
+#ifdef PORT
+extern int Port_Autosave(void);   /* port/full/plat_autosave.c */
+#endif
+
 s32 func_0029C1E8();
 void func_0029C7C0(s32 arg0);
 void func_0029C550(s32 arg0);
@@ -259,12 +263,18 @@
     case 16:
         func_0029C7C0(1);
         func_0029C550(0);
         DLG(0x11C) = 0;
         MSG = 28;
+#ifdef PORT
+        /* Autoguardado: "Save game data?" se contesta "Sí" por el jugador (mismos valores que un
+           pulsado manual: ANSWER=1 y la espera de 12 cuadros de func_0029C640). */
+        if (Port_Autosave() && ANSWER == 0) { ANSWER = 1; TIMER = 12; }
+#endif
         if (ANSWER > 0) {
             TIMER -= 1;
@@ -330,6 +340,11 @@
     case 18:
         func_0029C7C0(1);
         MSG = 21;
         McCard_Probe(0);
+#ifdef PORT
+        /* "Save data already exists. Would you like to overwrite the data?" → Sí. */
+        if (Port_Autosave() && ANSWER == 0) { ANSWER = 1; TIMER = 12; }
+#endif
         if (McCard_IsFatalError(MC_STATUS)) {
@@ -502,6 +517,12 @@
     case 28:
         func_0029C7C0(1);
         func_0029C550(0);
         DLG(0x11C) = 0;
         MSG = 37;
+#ifdef PORT
+        /* "Settings have been changed. Save the changed settings?" → Sí.
+           (Si NO se quiere autoguardar los ajustes, sacar este bloque: es el único de los cuatro
+           que no es progreso de juego.) */
+        if (Port_Autosave() && ANSWER == 0) { ANSWER = 1; TIMER = 12; }
+#endif
         if (ANSWER > 0) {
             TIMER -= 1;
@@ -591,6 +612,11 @@
     case 32:
         func_0029C7C0(1);
         MSG = 21;
         McCard_Probe(0);
+#ifdef PORT
+        /* La misma pregunta de sobrescritura, cuando hay que crear/agrandar los archivos. */
+        if (Port_Autosave() && ANSWER == 0) { ANSWER = 1; TIMER = 12; }
+#endif
         if (McCard_IsFatalError(MC_STATUS)) {
```

**No tocar**: 20 (WriteSave, `:368-382`), 19/33 (CreateSave), 23 (Formatear), 13 (cargar), 27 (error de
tarjeta cambiada), 29/30 (los "Exit saving/loading?" los dispara el jugador, no el juego).

Alternativa más corta (3 líneas, mismo efecto): poner el forzado una sola vez después de `MSG = -1;`
(`:68`) antes del `switch`:
```c
#ifdef PORT
    if (Port_Autosave() && ANSWER == 0 &&
        (STATE == 16 || STATE == 18 || STATE == 28 || STATE == 32)) { ANSWER = 1; TIMER = 12; }
#endif
```
Ninguno de esos cuatro casos resetea `ANSWER`, así que es equivalente; pero es más frágil a futuro que
dejarlo dentro de cada caso (como BT3).

### Capa del port (archivo nuevo, no aplicado)

`port/full/plat_autosave.c` (`link_full.py` ya compila `port/full/*.c`, no hay que registrarlo):

```c
/* Autoguardado: contesta "Sí" a las preguntas de guardado/sobrescritura de la memory card
   (port/eq/3E51F8.c estados 16/18/28/32). Prendido por defecto; BT2_AUTOSAVE=0 lo apaga, y si
   está el setting `autosave` en bt2_settings.txt manda ese. */
#include <stdlib.h>

/* plat_settings_bt3.c sólo se enlaza con el renderer GS; weak para no romper con BT2_NO_GS=1. */
extern int Port_Setting(const char *name, int def) __attribute__((weak));

static int sOn = -1;

int Port_Autosave(void) {
    const char *env;
    if (sOn >= 0) return sOn;
    env = getenv("BT2_AUTOSAVE");
    if (env != NULL) sOn = atoi(env) != 0;
    else if (Port_Setting != NULL) sOn = Port_Setting("autosave", 1) != 0;
    else sOn = 1;
    return sOn;
}
```
(Opcional, paridad con BT3: `Port_AutosaveSet(int)` + `Port_SettingSave`/`Port_SettingsWrite` y un toggle en
el overlay F1 de `port/full/gs/gs_draw.c:1261-1270`.)

Build sugerido (no ejecutado): `BT2_IRFIX=1 scripts/capped.sh 8G python3 port/tools/build_full.py --jobs 2
--only 3E51F8`, después `scripts/capped.sh 8G python3 port/tools/link_full.py`.
Prueba del usuario: menú pausa → Memory Card → Save (debe guardar solo, mostrando "Checking...", "Saving
data...", "Save successful."), y con un save ya existente (debe pasar la pregunta de sobrescritura).

---

## 6. Estado de error a NO autoguardar

**Estado 27** (`port/eq/3E51F8.c:482-501`, `MSG = 24` → `"The memory card (PS2) has been replaced. Would you
like to overwrite the data?"`). Es el equivalente exacto del estado `0xE` de BT3 (mismo texto, misma
estructura: Sí → reintentar con `McCard_Probe` y volver al chequeo; No → cancelar), y por las mismas razones:
si el chequeo de tarjeta vuelve a fallar, el flujo `17 → 27 → 17` se repetiría y un autoguardado en bucle
escribiría sobre una tarjeta que el juego considera cambiada.

Cómo se llega: es la **rama de polling** de 17 (`:303-328`), cuando `McCard_GetInfo` responde `MC_STATUS != 0`
y la bandera `SYS_FLAGS & 4` no está puesta → `McCard_Probe` → `STATE = 27`. No es una pregunta sobre el
archivo de save, es sobre el estado de la tarjeta.

También dejar sin autoguardar **23** (formatear, borra todo) y **13** (es la carga: contestar "Sí" haría que
el juego cargue el save en vez de guardar).

---

## 7. ¿BT2 ya tiene autosave / flag equivalente?

**No.** `grep -rn "autosave\|auto_save\|autoSave" port/ src/` no devuelve nada en el port de BT2 (sólo el
texto del informe F3F6). Lo que sí existe y se puede reutilizar:

- `port/full/gs/plat_settings_bt3.c` — **ya es el sistema de settings de BT2** (a pesar del nombre):
  `Port_Setting`, `Port_SettingSave`, `Port_SettingsWrite`; archivo `bt2_settings.txt` (o `$BT2_SETTINGS` /
  `$BT3_SETTINGS`), formato `nombre=valor`. Lo usan `plat_gs.c:226` (aspect) y el overlay F1
  (`gs_draw.c:1217-1270`, `gs_input.c:110-113`).
  Ojo: `link_full.py:443` sólo agrega `plat_settings_bt3.c` si se construye el renderer GS (default; con
  `BT2_NO_GS=1` no está) → por eso el `extern` weak en el archivo nuevo.
- `bt2_settings.txt` actual del usuario (`BT2-test/bt2_settings.txt`) sólo tiene `fullscreen=0`. No hay
  ninguna clave de autoguardado.

## 8. Formato del save: mismo `0x4000`, misma `plat_mc.c`

- `port/full/plat_mc.c` implementa libmc sobre archivos (`saves/card1/<ruta del juego>`, `$BT2_SAVES`).
  Es una adaptación del `plat_mc.c` de Tenkaichi3Decomp (el comentario de cabecera todavía dice
  `BASLUS-21678DBZT3`, residuo de BT3).
- El archivo real del usuario: `BT2-test/saves/card1/BASLUS-21441DBZT2/BASLUS-21441DBZT2` = **16384 bytes
  (0x4000)**, más `icon.sys` + `dbzsn.ico`. Coincide exactamente con lo que escribe el estado 20
  (`McCard_WriteSave(0, D_00387F2C, 0x4000, BUF_END)`), así que **no hay formato propio del port que
  respetar**: el autoguardado usa el save de memory card del juego.
- `McCard_WriteSave` es `port/eq/288F60.c:13`; el `0x4000` sale de `D_00387F2C` (bloque de progreso) y el
  buffer de trabajo `D_004279CC+0x4120`.

---

## 9. Dudas / lo que NO pude confirmar

1. **El +1 de la tabla de mensajes** (§2): el cruce estado↔texto es exacto en 25 estados (y en otras
   máquinas), pero no encontré en el asm el punto donde el índice se desplaza (el dibujante de mensajes
   indexa `base[msg]` y el de títulos `base[idx+1]`). No afecta el arreglo: los estados se identifican por
   flujo.
2. **Qué máquina usa el modo historia al terminar un capítulo**: no lo pude determinar sin ejecutar. Esta
   máquina (`3E51F8`) es la pantalla de save/load del menú (se abre desde `3E4CF8`/`3E6658`/`3E3B98`, estados
   de menú 47..50). Hay **otras** máquinas que también escriben `D_00387F2C, 0x4000`:
   `2587A8.c:237`, `3B9EF0.c:311`, `3BF748.c:244` (pregunta `CODE = 28` en `:144`, tabla propia en
   `D_00421C94`), `3C5710.c:205`, `3CEF10`. Si el autoguardado no aparece donde el usuario lo espera, el
   candidato siguiente es `3BF748` (su `CODE=28` es la misma pregunta "Save data?", misma numeración).
3. **Si se quiere autoguardar el estado 28** (ajustes): es el único de los cuatro que no es progreso de
   juego. Lo dejé en el diff pero marcado para poder quitarlo.
4. **Cosmético**: al forzar `ANSWER = 1` el resaltado del diálogo queda en la opción "No" (el cursor lo dejó
   en 1 `func_0029C820(1)`), y no suena el SE de confirmación de `func_0029C640`. BT3 tiene el mismo
   comportamiento. Si molesta, agregar `func_0029C820(0)` junto al forzado (no lo propongo para no tocar el
   cursor que usa el resto del menú).
5. **Nada probado en ejecución** (solo lectura). No verifiqué que el estado 16 sea alcanzable en el build
   actual ni que el menú de memory card funcione con el renderer por software.

---

## Apéndice: tabla de mensajes del recurso 0x550 de `ZS2US_1.AFS`

Entrada `n` = texto que muestra `MSG = n-1` (§2). 49 entradas, UTF-16LE.

| n | texto |
|---|---|
| 1 | MEMORY CARD slot 1 |
| 2 | MEMORY CARD slot 2 |
| 3 | MEMORY CARD slot 1 and MEMORY CARD slot 2 |
| 4 | Current settings will be lost if you begin a new game. OK? |
| 5 | Current settings will be lost if you load this save data. OK? |
| 6 | No memory card (PS2) inserted. |
| 7 | No memory card (PS2) inserted. At least 75KB of free space is required to save this game data. Continue anyway? |
| 8 | Game data not found in memory card (PS2). |
| 9 | Loading data. Do not remove memory card (PS2), reset, or switch off the console. |
| 10 | Load Failed. Please check memory card (PS2) and try again. |
| 11 | Load successful. |
| 12 | Do you wish to create a save file on the memory card (PS2)? |
| 13 | Formatting memory card (PS2). Do not remove memory card (PS2), controller, reset, or switch off the console. |
| 14 | Memory card (PS2) is unformatted. Format memory card (PS2)? |
| 15 | Format successful. |
| 16 | Format failed! Please check memory card (PS2) and try again. |
| 17 | Not enough free space. A memory card (PS2) with 75KB free is required. |
| 18 | Not enough free space on memory card (PS2). At least 75 KB of free space is required to save this game data. Continue anyway? |
| 19 | Creating save file. Do not remove memory card (PS2), controller, reset, or switch off the console. |
| 20 | Save file successfully created. |
| 21 | Save file creation failed. |
| 22 | Save data already exists. Would you like to overwrite the data? |
| 23 | Save over previous game? |
| 24 | Save Failed. memory card (PS2) may contain corrupt data. Would you like to overwrite data? |
| 25 | The memory card (PS2) has been replaced. Would you like to overwrite the data? |
| 26 | Load Failed. Memory card (PS2) error! Data may be corrupt. |
| 27 | Memory card (PS2) is unformatted. |
| 28 | Save data? |
| 29 | Save game data? |
| 30 | Saving data. Do not remove memory card (PS2), controller, reset, or switch off the console. |
| 31 | Save successful. |
| 32 | Save failed. Please check memory card (PS2) and try again. |
| 33 | Save game now, or your changes will be lost. Save again? |
| 34 | Checking memory card (PS2)... (variante 1) |
| 35 | Checking memory card (PS2)... (variante 2) |
| 36 | Save failed! Please check memory card (PS2) and try again. |
| 37 | Start a new game without saving? |
| 38 | Settings have been changed. Save the changed settings? |
| 39 | Delete Z warrior save data? |
| 40 | Z warrior save data deleted. |
| 41 | Delete failed. Please check memory card (PS2) and try again. |
| 42 | Deleting Z warrior save data. Please do not remove the memory card (PS2). |
| 43 | Now reading entry from the memory card (PS2) in MEMORY CARD slot 1! |
| 44 | Now reading entry from the memory card (PS2) in MEMORY CARD slot 2! |
| 45 | Dragon Ball Z: Budokai Tenkaichi" game data not found in memory card (PS2). |
| 46 | "Dragon Ball Z Budokai Tenkaichi" game data is corrupted. |
| 47 | Checking "Dragonball Z: Budokai Tenkaichi" game data. Please do not remove the memory card (PS2), reset, or switch off the console. |
| 48 | Exit saving? |
| 49 | Exit loading? |

(Herramientas usadas, todas de solo lectura, en `/tmp/opencode/`: `f3_pack550.bin` (entrada AFS),
`f3_lz.py` (descompresor), `f3_sub0.bin` (bloque descomprimido), `f3_3E51F8.dis` (asm del overlay).)
