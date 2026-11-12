# F5 — Textos de memory card / "(PS2)" del diálogo de guardado/carga

Fecha: 2026-11-11. **Solo lectura**: no se editó, compiló ni ejecutó nada del proyecto. Las pruebas del
mecanismo se hicieron en `/tmp/f5/` sobre una copia de la tabla extraída del AFS (sin tocar el proyecto).

Objetivo: inventariar los textos del diálogo de memory card, entender cómo llegan a pantalla y dejar listo
un mecanismo para reescribirlos desde el port (sacar "(PS2)", acortar mensajes, etc.) **sin tocar los datos
del juego**.

---

## 0. Corrección importante del punto de partida: el dibujante es `func_0029C038`, no `func_0029BD58`

El informe F3 decía que el texto lo dibuja `func_0029BD58` y no lograba explicar el "+1" entre `MSG` y el
índice de la tabla. La pieza que faltaba es el campo `D_00387DA0+0x64`:

| evidencia | qué dice |
|---|---|
| `port/eq/29C1E8.c:111-116` | `if (*(s32 *)(D_00387DA0 + 0x64) == 1) { func_0029BF08(1); func_0029C038(); } else { func_0029BD58(1); }` |
| `port/eq/29C038.c:45` | `s0 = base + ((*(u32 *)(base + (*(s32 *)(p + 0x5C) * 4) + 4) >> 2) << 2);` → **`word[MSG+1]`** |
| asm `29c0a8..29c0b8` | `lw v1,92(v0)` (MSG); `sll v1,2`; `addu v1,v1,a0` (base); `lw v0,4(v1)` → `word[MSG+1]` |
| `port/eq/29BD58.c:45` | `base + word[MSG]` → `word[MSG]` (el que se usa cuando `+0x64 != 1`) |
| `port/eq/3E4CF8.c:26-32` | `fx()` llama `func_0029C7E0(1)` antes de abrir el diálogo |
| `src/auto/m2c_29C7E0.c:5` | `func_0029C7E0(n)` escribe `D_00387DA0+0x64 = n` |

O sea: al entrar al diálogo de save/load desde `func_003E4CF8`, `fx()` deja `+0x64 = 1`, y desde ese
momento `func_0029C1E8` usa **`func_0029BF08` (título) + `func_0029C038` (mensaje)**. `func_0029C038`
indexa `word[MSG+1]`, que es exactamente el "+1" que faltaba. `func_0029BD58` (índice `word[MSG]`) queda para
diálogos sin título (`+0x64 == 0`), no para este.

Consecuencias:

- **`MSG = n` muestra la entrada `n+1` de la tabla** (1-based). Ej.: estado 16 (`MSG=28`) → `word[29]` =
  `"Save game data?"`; estado 27 (`MSG=24`) → `word[25]` = `"The memory card (PS2) has been replaced..."`.
- Los títulos (`"MEMORY CARD slot 1"`, etc.) los dibuja `func_0029BF08` con su propio índice
  `D_00387DA0+0x68` y también `word[idx+1]` (`port/eq/29BF08.c:40-41`).
- El cambio de dibujante **no cambia el layout**: `func_0029C038` usa la caja `mc_dammy_fonts`
  (`D_003777E0`) y otros desplazamientos verticales (1 línea → `+0x28`, 2 → `+0x20`, 3 → `+0x14`,
  4 → `+0x0A`, 5 → `+0x04`; `29C038.c:47-65`).

---

## 1. Inventario de la tabla del recurso `0x550`

### 1.1 Formato exacto

- Archivo: `gamedata/DATA/ZS2US_1.AFS` (partición 0), **entrada `0x550`**.
  - `offset = 0x1C22800`, `size = 0x22AB40` (2.272.064 bytes).
- `0x550` es un **contenedor**: `u32 count = 4`, `u32 header = 0x40`, 4 offsets de fin
  (`0x8AD00`, `0xF1E40`, `0x1B46C0`, `0x22AB40`). Sólo el **sub-bloque 0** tiene esta tabla.
- Sub-bloque 0: header en `+0x40` (`destSize = 0x12B340`, `packedSize = 0x8ACB3`); al descomprimirlo
  (`func_002B24C8`) quedan `0x12B340` bytes. La tabla está en **`P + 0xFCC80`**, bloque de
  **`0x1C80`** bytes (16.º bloque, índice 15, de los 20 de la tabla de bloques del sub-bloque).
- Dentro de la tabla:
  - `u32 count = 49` en `+0`.
  - `u32 word[1..49]`: offsets **relativos a la base de la tabla**, en bytes, alineados a 4
    (`>>2<<2`).
  - Cada string es **UTF-16LE**, empieza con **BOM `FF FE` (U+FEFF)**, usa **`U+000A` (`\n`)** para el
    salto de línea y termina en **`U+0000`**. No hay longitud explícita ni wrap automático: los saltos
    vienen puestos en el texto.
  - Cada string vive en un slot alineado a `0x40` (el siguiente offset). Ejemplos:
    `word[1] = 0x100` ("MEMORY CARD slot 1"), `word[29] = 0x1080` ("Save game data?"),
    `word[49] = 0x1C40` ("Exit loading?"), fin del bloque `0x1C80`.
  - **`MSG = n` → `word[n+1]`** (por el dibujante `29C038`, §0). Los títulos usan `word[t+1]` con `t=0..2`.
- Longitudes:
  - String más largo: **136 unidades UTF-16** (incluido el BOM) → entrada 47.
  - Línea más ancha: **429 px**; línea más larga en caracteres: **45** (entrada 13,
    `"controller, reset, or switch off the console."`). El ancho es proporcional (font0), así que el
    límite útil es **~429 px / ~42-45 caracteres**.
  - Slots útiles (sin NUL): `0x40` bytes = 31 u16 (entradas con slot de 0x40, p. ej. `word[29]`),
    `0x80` = 63 u16, `0xC0` = 95 u16, etc. Nuestros overrides de ejemplo entran todos (§4).

### 1.2 Tabla completa (49 entradas)

Leyenda de flags: **M** = "memory card"; **P** = "(PS2)"; **C** = "card"; **S** = save/load/guardar/cargar;
**F** = format/formatear. "Usado" = estados de `func_003E51F8` que muestran esa entrada (el estado usa
`MSG = k-1`). Las entradas 1-3 son títulos.

| k | MSG | texto | flags | usado |
|---:|---:|---|---|---|
| 1 | 0 | `MEMORY CARD slot 1` | MC | título |
| 2 | 1 | `MEMORY CARD slot 2` | MC | título |
| 3 | 2 | `MEMORY CARD slot 1 \nand MEMORY CARD slot 2` | MC | título |
| 4 | 3 | `Current settings will be lost\nif you begin a new game. OK?` | — | — |
| 5 | 4 | `Current settings will be lost\nif you load this save data. OK?` | S | 13 |
| 6 | 5 | `No memory card (PS2) inserted.` | MPC | 2 |
| 7 | 6 | `No memory card (PS2) inserted.\nAt least 75KB of free space \nis required to save this game data. \nContinue anyway?` | MPCS | — |
| 8 | 7 | `Game data not found \nin memory card (PS2).` | MPC | 3 |
| 9 | 8 | `Loading data. \nDo not remove memory card (PS2), \nreset, or switch off the console.` | MPCS | 9 |
| 10 | 9 | `Load Failed. Please check \nmemory card (PS2) \nand try again.` | MPCS | 11 |
| 11 | 10 | `Load successful.` | S | 10 |
| 12 | 11 | `Do you wish to create a save file \non the memory card (PS2)?` | MPCS | — |
| 13 | 12 | `Formatting memory card (PS2). \nDo not remove memory card (PS2), \ncontroller, reset, or switch off the console.` | MPCF | 24 |
| 14 | 13 | `Memory card (PS2)\nis unformatted.\nFormat memory card (PS2)?` | MPCF | 23 |
| 15 | 14 | `Format successful.` | F | 25 |
| 16 | 15 | `Format failed!\nPlease check memory card (PS2)\nand try again.` | MPCF | 26 |
| 17 | 16 | `Not enough free space.\nA memory card (PS2)\nwith 75KB free is required.` | MPC | 4 |
| 18 | 17 | `Not enough free space on memory \ncard (PS2). At least 75 KB of free \nspace is required to save this game \ndata. Continue anyway?` | PCS | — |
| 19 | 18 | `Creating save file. \nDo not remove memory card (PS2),\ncontroller, reset, or switch off the console.` | MPCS | 19/33 |
| 20 | 19 | `Save file successfully created.` | S | — |
| 21 | 20 | `Save file creation failed.` | S | — |
| 22 | 21 | `Save data already exists.\nWould you like to overwrite the data?` | S | 18/32 |
| 23 | 22 | `Save over previous game?` | S | — |
| 24 | 23 | `Save Failed. memory card (PS2)\nmay contain corrupt data.\nWould you like to overwrite data?` | MPCS | — |
| 25 | 24 | `The memory card (PS2) has been replaced.\nWould you like to overwrite the data?` | MPC | 27 |
| 26 | 25 | `Load Failed. \nMemory card (PS2) error!\nData may be corrupt.` | MPCS | 12 |
| 27 | 26 | `Memory card (PS2) is unformatted.` | MPCF | — |
| 28 | 27 | `Save data?` | S | — |
| 29 | 28 | `Save game data?` | S | 16 |
| 30 | 29 | `Saving data. \nDo not remove memory card (PS2), \ncontroller, reset, or switch off the console.` | MPCS | 20/33 |
| 31 | 30 | `Save successful.` | S | 21 |
| 32 | 31 | `Save failed.\nPlease check memory card \n(PS2) and try again.` | MPCS | 22 |
| 33 | 32 | `Save game now, or your changes\nwill be lost.\nSave again?` | S | — |
| 34 | 33 | `Checking memory card (PS2)...\nDo not remove memory card (PS2), \ncontroller, reset, or switch off the console.` | MPC | — |
| 35 | 34 | `Checking memory card (PS2)...\nDo not remove memory card (PS2),\ncontroller, reset, or switch off the console.` | MPC | 5/7/8/17/31 |
| 36 | 35 | `Save failed!\nPlease check memory card (PS2)\nand try again.` | MPCS | — |
| 37 | 36 | `Start a new game without saving?` | S | — |
| 38 | 37 | `Settings have been\nchanged. Save the\nchanged settings?` | S | 28 |
| 39 | 38 | `Delete Z warrior\nsave data?` | S | — |
| 40 | 39 | `Z warrior save \ndata deleted.` | S | — |
| 41 | 40 | `Delete failed.\nPlease check memory card\n(PS2) and try again.` | MPC | — |
| 42 | 41 | `Deleting Z warrior\nsave data. Please \ndo not remove the \nmemory card (PS2). ` | MPCS | — |
| 43 | 42 | `Now reading entry from the\nmemory card (PS2)\nin MEMORY CARD slot 1!` | MPC | — |
| 44 | 43 | `Now reading entry from the\nmemory card (PS2)\nin MEMORY CARD slot 2!` | MPC | — |
| 45 | 44 | `Dragon Ball Z: Budokai Tenkaichi" \ngame data not found in \nmemory card (PS2).` | MPC | — |
| 46 | 45 | `"Dragon Ball Z Budokai Tenkaichi" \ngame data is corrupted.` | — | — |
| 47 | 46 | `Checking "Dragonball Z: Budokai Tenkaichi" \ngame data. Please do not remove the \nmemory card (PS2), reset, or switch \noff the console. ` | MPC | — |
| 48 | 47 | `Exit saving?` | S | 29 |
| 49 | 48 | `Exit loading?` | S | 30 |

(El bloque usado está en `/tmp/opencode/f3_s0.raw`; la tabla se leyó desde `+0xFCC80`. Los textos son
exactos, incluidos los espacios finales de 42 y 47.)

---

## 2. Constructo de carga (quién lee/descomprime y dónde queda)

### 2.1 Cadena completa

1. `port/eq/1021E8.c:25` → `D_003876A4+4 = 0x544` (base de ids del menú).
2. `port/eq/3E3B98.c:30` → `func_100D58(*(D_003876A4+4) + 0xC, 0, 1)` = **id `0x550`**.
   `func_100D58` (`port/eq/100D58.c:33-40`) reparte ids `< 0x33B2` a la partición 0 (`ZS2US_1.AFS`) y
   `>= 0x33B2` a la 1; el archivo de la partición lo lee `plat_file.c` (ADXF, sin checksum).
3. `port/eq/3E3B98.c:32-33` → `D_00421398 = func_100D58(0,0,0)` en un bucle hasta que devuelve el buffer
   cargado (es asíncrono). `D_00421398` = **entrada `0x550` cruda** (contenedor de 4 sub-bloques).
4. `port/eq/3E6658.c:38` → `func_003E3D38(arg0)` con `arg0 = 1` (el único llamador es `3E3B98.c:46`).
5. `port/eq/3E3D38.c`:
   - `:49` `D_004279CC = func_0028BAA8(0x4544)` (objeto del diálogo, heap).
   - `:53` `G+0 = D_00421398 + (word[arg0<<2] & ~3)` → `+0x40` (sub-bloque 0).
   - `:54` `G+4 = func_002B24C8(G+0, 0, 0)` → **`P` = sub-bloque 0 descomprimido** (0x12B340 bytes).
   - `:101` `G+0x10 = P + (word[P+0x40] & ~3)` → **`P + 0xFCC80` = tabla de mensajes**.
   - `:102` `func_0029BB88(P + (word[P+0x3C] & ~3), G+0x10)`.
6. `port/eq/29BB88.c:14` `D_00387DA0 = func_0028BAA8(0x78)` (objeto pequeño del diálogo, heap);
   `:44` `*(s32 *)(D_00387DA0 + 4) = arg1` → **la tabla queda apuntada por `D_00387DA0+4`**.
7. `port/eq/29C038.c:44-45` lee `base = *(u8 **)(D_00387DA0 + 4)` y resuelve `word[MSG+1]`.

### 2.2 Dirección: no es fija

`P` y `D_00387DA0` se piden con `func_0028BAA8` (heap del juego). La tabla vive **dentro de `P`**, así que su
dirección cambia con cada carga. Confirmado con dumps de RAM del propio port (F9, 32 MB):

| dump | string `MEMORY CARD slot 1` | base de la tabla (`-0x100`) |
|---|---|---|
| `BT2-test/logs/vivo/20261111-131314_ram1_f4957.bin` | `0x9E8AB8` | **`0x9E89B8`** (`word[0]=49`, `word[1]=0x100`) |
| `BT2-test/logs/vivo/20261111-121635_ramkey1_f4116.bin` | `0xB530F8` | **`0xB52FF8`** |

O sea `P = 0x8EBD38` en un caso y `P = 0xA56378` en otro. **No hay que hardcodear ninguna dirección.**

### 2.3 ¿Varias copias?

- **Una copia viva por apertura** de la pantalla de memory card (`3E6658(1)` → `3E3D38(1)`), dentro de `P`.
  Al volver a entrar se vuelve a descomprimir y se reemplaza.
- **Sólo el sub-bloque 0** de `0x550` tiene esta tabla de 49 entradas. Los otros sub-bloques:
  - sub-bloque 1: 35 textos de ayuda de opciones (no es la tabla de mensajes);
  - sub-bloques 2 y 3: otros datos/scripts.
- Otras pantallas de memory card usan **otro sub-bloque o directamente otro recurso**:
  - `port/eq/3E68D0.c` (borrar/copiar) usa `D_00421398` pero offsets `0x54/0x5C` → otro sub-bloque;
  - `port/eq/3E84B0.c` usa `P+0x44` → otra tabla;
  - el flujo del **título** (`3BE778.c`/`3BF748.c`) usa `D_004213A8` cargado desde **id `0x54F`**
    (`3C0700.c:30`: `0x544+0xB`), con sus propios textos ("Please insert the memory card (PS2)...").
- Por lo tanto: la tabla de §1 es **la del diálogo `3E51F8`**, y las otras pantallas tienen copias/tablas
  distintas. Nuestro override se limita a ésta.

---

## 3. Constructo de dibujo

### 3.1 De `MSG` a `Font_PrintAt`

1. La máquina de estados escribe `MSG` (`D_004279CC+0x10C`) en cada estado (`3E51F8.c`, casos 2..33).
2. Al final de cada frame: `port/eq/3E51F8.c:667` `func_0029C800(MSG)` → `D_00387DA0+0x5C = MSG`
   (`src/auto/m2c_29C800.c`); `:668` `func_0029C1E8(1)`.
3. `port/eq/29C1E8.c:111-116` elige el dibujante según `+0x64` (ver §0):
   - `func_0029BF08(1)` → título; usa `D_00387DA0+0x68` y `word[idx+1]` (`29BF08.c:40-41`).
   - `func_0029C038()` → mensaje; `29C038.c:45` resuelve **`word[MSG+1]`**.
4. `29C038.c:46` `func_002A0EA8(s0)` = `Font_CountLinesEx(s0, 0)` (`src/auto/auto_2a0ea8.c:4`) → cuenta
   líneas y ajusta `y` (`:47-65`).
5. `29C038.c:74` `Font_PrintAt(tmp[4], tmp[5], s0)` (`func_002A0F68`), que encola un comando
   `FONT_CMD_STR16` con el puntero UTF-16 (`src/battle/col_c_2A0ED8.c:208-210`, misma convención en el
   object 0x239xxx del printer). El texto se dibuja en el flush de fuentes.

### 3.2 Fuente/glyphs: ¿banca acentos, ñ y paréntesis?

El font del sistema se carga desde el **AFS `0x542`**: `port/eq/1021E8.c:30` llama `func_00102180`, que
hace `D_003876A0+0x70 = func_00100CB8(0x542)` (`src/auto/m2c_102180.c:14`). `Font_InitEx`
(`port/eq/2A0630.c:58-60`) enlaza dos fuentes del contenedor:

- font0 en `+0x40` (magic `"Fnt4"`): **latina**, 170 glyphs.
- font1 en `+0x89C0`: símbolos/Griego/Cirílico/CJK/puntuación fullwidth, 425 glyphs.

Formato del glyph (`Font_SearchGlyph`, `port/eq/2A20D0.c:18-28`): array en `font+0x10`, cantidad en
`font+0x14`, **6 bytes por entrada**: `u16 code`, `u16 metric1`, `u16 metric2`; el avance es
`(metric1 >> 10) & 0x1F` (`Font_AdvanceChar`, `port/eq/2A1DF8.c:41-46`).

Códigos presentes en font0 (leídos del AFS, no de una suposición):

- **ASCII 0x20..0x7E completo** (incluye `(`, `)`, `"`, `:`, `?`, `!`).
- **Latín-1/acentos**: `¡ ¿ À Á Â Ã Ä Æ Ç È É Ê Ë Ì Í Î Ï Ñ Ò Ó Ô Õ Ö Ø Ù Ú Û Ü Þ ß à á â ã ä æ ç è é ê ë
  ì í î ï ñ ò ó ô õ ö ø ù ú û ü ÿ`, más `Ą ą Ę ę Į į Ĳ ĳ Œ œ Ş Ų ų Ÿ`.
- **No** están `…` (U+2026), `—` (U+2014), `’`/`‘` (U+2018/2019). Para texto nuevo usar `...`, `-`, `'`.
- El BOM `U+FEFF` no tiene glyph: el drawer lo saltea con avance 0 (por eso los strings originales
  pueden empezar con él). En texto nuevo no hace falta.

Conclusión: **sí, el font banca acentos, ñ/Ñ y paréntesis**. No hace falta tocar la fuente.

### 3.3 ¿Se puede sustituir sin tocar el juego?

Sí, y hay tres caminos:

| camino | cómo | riesgo |
|---|---|---|
| **(a) pisar la tabla en RAM después de cargada** | en `3E3D38.c`, después de `func_0029BB88(...)`, reescribir los strings dentro de `P` | **bajo**; sólo afecta esta pantalla y esta copia; no toca AFS ni save |
| **(b) interceptar el puntero en el drawer** | en `29C038.c:45`, si `MSG` tiene override, usar nuestro buffer UTF-16 | bajo si se valida que `base` es la tabla de 49 entradas; el drawer `29C038` es **compartido** con otros diálogos (`+0x64==1`), así que sin validar la tabla se puede pisar otro menú |
| **(c) reemplazar el recurso** | editar el AFS (el comentario de `plat_file.c:9` menciona `gamedata/mods/<particion>/<indice>.bin`, pero **no encontré la implementación** en `plat_file.c`; verificar) | alto: hay que rearmar el contenedor comprimido y afecta a todas las pantallas que usen `0x550`; **no lo recomendamos** |

Elegimos **(a)**: es la más barata (una vez por carga), la más acotada (sólo la copia de `3E3D38`) y no
necesita tocar el drawer ni direcciones fijas. La variante (b) queda documentada por si en el futuro se
quiere cubrir también las otras tablas.

---

## 4. Mecanismo propuesto

### 4.1 Diseño

Archivo nuevo `port/full/plat_text.c` (se enlaza solo: `link_full.py` compila `port/full/*.c`), más una
llamada de 2 líneas en `port/eq/3E3D38.c`.

- `Port_TextoAplicarTabla(tabla)` se llama con la tabla ya descomprimida.
- Valida que sea **esta** tabla: `word[0] == 49` y `word[1] == 0x100` ("MEMORY CARD slot 1"). Cualquier otra
  tabla (otro recurso/sub-bloque) se deja intacta.
- Para cada override `MSG → UTF-8`:
  - índice real `k = MSG+1`;
  - slot = `word[k+1] - word[k]` (para `k=49`, `word[49]+0x40`, que es el fin del bloque `0x1C80`);
  - convierte UTF-8 → UTF-16LE (maneja `\n` y acentos; 4 bytes/emoji se descartan);
  - si `texto_ps2=0`/`BT2_TEXTO_PS2=0`, saca `"(PS2)"` y el espacio anterior (sirve también para las
    entradas sin override, recorriendo las 49; esas conservan sus saltos originales y sólo se acortan);
  - los overrides se ajustan a **429 px** (tabla de avances del font0 embebida) y a **5 líneas**;
  - si no entra en el slot (o no se puede envolver), **deja el original** y avisa por `stderr`; nunca
    escribe fuera del slot.
- Codificación: el texto nuevo **no lleva BOM**; termina en `U+0000`; `\n` = `U+000A`.
- Texto más largo que el original: como no movemos offsets ni punteros, el límite real es el **slot**
  (el espacio hasta el siguiente string) y el ancho de línea. Ejemplos:
  - `MSG 28` (k29) tiene slot de 31 u16; `"Save game data?"` = 15+1 → entra.
  - `MSG 21` (k22) tiene slot de 95 u16; nuestro texto de 2 líneas = 40 → entra.
  - Si un texto no entra, se ignora **sólo ese** mensaje (el juego sigue mostrando el original).
- Configuración:
  - `bt2_texto.txt` (o `$BT2_TEXTO`): líneas `MSG=texto`, con `\n` para el salto. Ejemplo:
    ```
    28=Save game data?
    21=Save data already exists.\nOverwrite it?
    ```
  - `texto_ps2=0` en `bt2_settings.txt` (o `BT2_TEXTO_PS2=0`) saca `(PS2)` de todos los mensajes de esta
    tabla. Sin setting, **no cambia nada** (default `texto_ps2=1`).

### 4.2 Diff del enganche (NO aplicado)

```diff
--- a/port/eq/3E3D38.c
+++ b/port/eq/3E3D38.c
@@ -18,6 +18,7 @@
 s32 func_0028A0B8(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0);
 s32 McCard_Checksum(u8 *a0, s32 a1, s32 a2);
 void func_0029C820(s32 a0);
+void Port_TextoAplicarTabla(u8 *tabla);   /* F5: port/full/plat_text.c */
 
 /* byte copy (no libc); optnone so clang does not turn the loops into memcpy/memset on 4-byte game pointers,
  * which the PC build cannot lower */
@@ -100,6 +101,7 @@
     *(u8 **)(G + 0x8) = P + (*(s32 *)(P + 0x38) & ~3);
     *(u8 **)(G + 0x10) = P + (*(s32 *)(P + 0x40) & ~3);
     func_0029BB88(P + (*(s32 *)(P + 0x3C) & ~3), *(u8 **)(G + 0x10));
+    Port_TextoAplicarTabla(*(u8 **)(G + 0x10));   /* F5: reescribe los textos en RAM */
 
     G = D_004279CC;
     *(s32 *)(G + 0x10C) = -1;
```

### 4.3 `port/full/plat_text.c` (archivo nuevo, NO aplicado)

```diff
--- /dev/null
+++ b/port/full/plat_text.c
@@ -0,0 +1,350 @@
+/*
+ * F5: textos del dialogo de memory card.
+ *
+ * El juego muestra los mensajes de guardado/carga desde una tabla UTF-16LE que vive dentro del
+ * recurso 0x550 de ZS2US_1.AFS, descomprimido en RAM por func_003E3D38
+ * (port/eq/3E3D38.c:101). Esta capa reescribe esa copia EN RAM justo despues de cargarla: no toca
+ * el AFS, el ISO ni el save, y no afecta a otras pantallas (cada pantalla que llama a 3E3D38 tiene
+ * su propia copia).
+ *
+ * Formato de la tabla (staging/F5_textos_memorycard.md):
+ *   u32 count = 49; word[1..49] = offsets (relativos a la tabla, alineados a 4) a strings UTF-16LE
+ *   con BOM FF FE, '\n' = U+000A y terminador U+0000.  MSG n usa la entrada n+1.
+ *   Cada string vive en un slot alineado a 0x40: no se puede escribir mas alla del siguiente offset.
+ *
+ * Configuracion (todo opcional; sin nada de esto el juego queda igual):
+ *   bt2_texto.txt (o $BT2_TEXTO)  lineas "MSG=texto", con \n para el salto de linea.
+ *   texto_ps2=0 (bt2_settings.txt) o BT2_TEXTO_PS2=0  saca "(PS2)" de todos los mensajes.
+ */
+#include <stdio.h>
+#include <stdlib.h>
+#include <string.h>
+
+int Port_Setting(const char *name, int def) __attribute__((weak));
+
+#define TEXTO_ENTRADAS 49
+#define TEXTO_MAX      256 /* u16 por string: sobra para el slot mas grande (0x200 bytes) */
+#define TEXTO_ANCHO    429 /* px: la linea mas ancha del juego mide 429 (ver el informe) */
+#define TEXTO_LINEAS   5   /* port/eq/29C038.c:47-65 contempla 1..5 lineas */
+
+typedef struct {
+    int msg; /* campo +0x10C del dialogo; la tabla es word[msg+1] */
+    const char *utf8;
+} TextoDef;
+
+/* Overrides de ejemplo. El MSG es el del estado de port/eq/3E51F8.c, no el indice de la tabla:
+   MSG 21 = estados 18/32 ("already exists"), 24 = estado 27 ("card replaced"),
+   28 = estado 16 ("save game data?"), 37 = estado 28 ("settings changed"). */
+static const TextoDef kDefs[] = {
+    { 21, "Save data already exists.\nOverwrite it?" },
+    { 24, "The memory card has been replaced.\nOverwrite the data?" },
+    { 28, "Save game data?" },
+    { 37, "Settings have been changed.\nSave the changes?" },
+    { 13, "Memory card is unformatted.\nFormat it?" },
+    { 27, "Memory card is unformatted." },
+};
+
+/* Avance (px) de los glifos 0x20..0x7E del font0 del juego (AFS 0x542, font en +0x40). */
+static const unsigned char kAdv[95] = {
+     9, 5, 7,13,11,19,15, 5, 7, 7, 9,13, 7, 7, 5, 9,11,11,11,
+    11,13,11,11,11,11,11, 5, 7,13,13,13, 9,17,15,11,13,13,11,
+    11,13,11, 9, 9,11, 9,13,11,13, 9,13,11,13,13,13,15,17,13,
+    13,13, 7, 9, 7,13,13, 7,11,11,11,11,11, 9,11,11, 5, 7,11,
+     5,17,11,11,11,11, 9,11, 9,11,11,15,11,11, 9,11, 5,11,13,
+};
+
+static int sInit;
+static char *sOverride[TEXTO_ENTRADAS];
+
+static void leer_archivo(void) {
+    const char *ruta;
+    FILE *fp;
+    char linea[512];
+
+    if (sInit != 0) {
+        return;
+    }
+    sInit = 1;
+    ruta = getenv("BT2_TEXTO");
+    if (ruta == NULL || ruta[0] == 0) {
+        ruta = "bt2_texto.txt";
+    }
+    fp = fopen(ruta, "r");
+    if (fp == NULL) {
+        return;
+    }
+    while (fgets(linea, sizeof(linea), fp) != NULL) {
+        char *p = linea;
+        char *q;
+        int msg;
+        size_t n;
+        while (*p == ' ' || *p == '\t') {
+            p++;
+        }
+        if (*p == '#' || *p == '\n' || *p == 0) {
+            continue;
+        }
+        msg = (int)strtol(p, &q, 10);
+        if (q == p || *q != '=') {
+            continue;
+        }
+        q++;
+        while (*q == ' ' || *q == '\t') {
+            q++;
+        }
+        n = strlen(q);
+        while (n > 0 && (q[n - 1] == '\n' || q[n - 1] == '\r')) {
+            q[--n] = 0;
+        }
+        if (msg >= 0 && msg < TEXTO_ENTRADAS) {
+            free(sOverride[msg]);
+            sOverride[msg] = strdup(q);
+        }
+    }
+    fclose(fp);
+}
+
+/* 1 cuando el usuario pidio sacar "(PS2)" (texto_ps2=0 o BT2_TEXTO_PS2=0). */
+static int quitar_ps2(void) {
+    const char *e = getenv("BT2_TEXTO_PS2");
+    if (e != NULL) {
+        return *e == '0';
+    }
+    if (Port_Setting != NULL) {
+        return Port_Setting("texto_ps2", 1) == 0;
+    }
+    return 0;
+}
+
+/* UTF-8 -> UTF-16LE. Acepta \\n como salto. Devuelve la cantidad de u16 (sin el NUL). */
+static int utf8_a_utf16(const char *s, unsigned short *out, int cap) {
+    int n = 0;
+    while (*s != 0) {
+        unsigned char c = (unsigned char)*s++;
+        unsigned cp;
+        if (c == '\\' && *s == 'n') {
+            s++;
+            cp = '\n';
+        } else if (c < 0x80) {
+            cp = c;
+        } else if ((c & 0xE0) == 0xC0) {
+            cp = ((unsigned)(c & 0x1F) << 6) | (unsigned)((unsigned char)*s++ & 0x3F);
+        } else if ((c & 0xF0) == 0xE0) {
+            cp = ((unsigned)(c & 0x0F) << 12) | ((unsigned)((unsigned char)*s++ & 0x3F) << 6);
+            cp |= (unsigned)((unsigned char)*s++ & 0x3F);
+        } else {
+            continue; /* 4 bytes (emoji): el font del juego no los tiene */
+        }
+        if (n + 1 >= cap) {
+            break;
+        }
+        out[n++] = (unsigned short)cp;
+    }
+    out[n] = 0;
+    return n;
+}
+
+/* Saca "(PS2)" y el espacio que lo precede. */
+static int filtrar_ps2(const unsigned short *in, unsigned short *out, int cap) {
+    int i = 0;
+    int n = 0;
+    while (in[i] != 0) {
+        if (in[i] == '(' && in[i + 1] == 'P' && in[i + 2] == 'S' && in[i + 3] == '2' && in[i + 4] == ')') {
+            if (n > 0 && out[n - 1] == ' ') {
+                n--;
+            }
+            i += 5;
+            continue;
+        }
+        if (n + 1 >= cap) {
+            break;
+        }
+        out[n++] = in[i++];
+    }
+    out[n] = 0;
+    return n;
+}
+
+static int ancho_char(unsigned c) {
+    if (c >= 0x20 && c < 0x7F) {
+        return kAdv[c - 0x20];
+    }
+    return 11; /* Latin-1 acentuado: el font0 mide 11 para casi todos */
+}
+
+static int ancho_linea(const unsigned short *s, int n) {
+    int w = 0;
+    int i;
+    for (i = 0; i < n; i++) {
+        w += ancho_char(s[i]);
+    }
+    return w;
+}
+
+/* Corta las lineas que pasen de TEXTO_ANCHO px en el ultimo espacio. -1 si no entra en el buffer
+   o si necesita mas de TEXTO_LINEAS lineas. */
+static int envolver(const unsigned short *in, int len, unsigned short *out, int cap) {
+    int i;
+    int n = 0;
+    int ini = 0;
+    int lineas = 1;
+
+    for (i = 0; i < len; i++) {
+        unsigned c = in[i];
+        if (c == '\n') {
+            if (n + 1 >= cap) {
+                return -1;
+            }
+            out[n++] = (unsigned short)c;
+            ini = n;
+            if (++lineas > TEXTO_LINEAS) {
+                return -1;
+            }
+            continue;
+        }
+        if (n > ini && ancho_linea(out + ini, n - ini) + ancho_char(c) > TEXTO_ANCHO) {
+            int j = n - 1;
+            while (j > ini && out[j] != ' ') {
+                j--;
+            }
+            if (j > ini) {
+                out[j] = '\n';
+                ini = j + 1;
+            } else {
+                if (n + 1 >= cap) {
+                    return -1;
+                }
+                out[n++] = '\n';
+                ini = n;
+            }
+            if (++lineas > TEXTO_LINEAS) {
+                return -1;
+            }
+        }
+        if (n + 1 >= cap) {
+            return -1;
+        }
+        out[n++] = (unsigned short)c;
+    }
+    out[n] = 0;
+    return n;
+}
+
+/* u16 utiles del slot de la entrada k (sin contar el NUL). */
+static int slot_u16(const unsigned int *w, unsigned count, unsigned k, unsigned *off_out) {
+    unsigned off = w[k] & ~3u;
+    unsigned next;
+    if (k < count) {
+        next = w[k + 1] & ~3u;
+    } else {
+        next = off + 0x40; /* ultima entrada del bloque: el siguiente paso de alineacion */
+    }
+    *off_out = off;
+    if (next <= off) {
+        return -1;
+    }
+    return (int)((next - off) / 2) - 1;
+}
+
+static void escribir(unsigned char *base, unsigned off, const unsigned short *s, int n) {
+    unsigned short *dst = (unsigned short *)(base + off);
+    int i;
+    for (i = 0; i <= n; i++) {
+        dst[i] = s[i];
+    }
+}
+
+/* Se llama desde func_003E3D38 (port/eq/3E3D38.c) con la tabla ya descomprimida en RAM. */
+void Port_TextoAplicarTabla(unsigned char *tabla) {
+    unsigned int *w;
+    unsigned count;
+    unsigned k;
+    int i;
+
+    if (tabla == NULL) {
+        return;
+    }
+    leer_archivo();
+    w = (unsigned int *)tabla;
+    count = w[0];
+    /* Solo la tabla del dialogo de memory card (0x550 sub-bloque 0): 49 entradas y el primer
+       string en +0x100 ("MEMORY CARD slot 1"). Cualquier otra tabla se deja intacta. */
+    if (count != TEXTO_ENTRADAS || (w[1] & ~3u) != 0x100) {
+        return;
+    }
+
+    for (i = 0; i < (int)(sizeof(kDefs) / sizeof(kDefs[0])); i++) {
+        unsigned short tmp[TEXTO_MAX];
+        unsigned short tmp2[TEXTO_MAX];
+        const char *src;
+        unsigned msg = (unsigned)kDefs[i].msg;
+        unsigned kk = msg + 1;
+        unsigned off;
+        int slot;
+        int n;
+
+        if (kk < 1 || kk > count) {
+            continue;
+        }
+        slot = slot_u16(w, count, kk, &off);
+        if (slot < 0) {
+            continue;
+        }
+        src = sOverride[msg] != NULL ? sOverride[msg] : kDefs[i].utf8;
+        n = utf8_a_utf16(src, tmp, TEXTO_MAX);
+        if (quitar_ps2() != 0) {
+            n = filtrar_ps2(tmp, tmp2, TEXTO_MAX);
+            memcpy(tmp, tmp2, (size_t)(n + 1) * sizeof(tmp[0]));
+        }
+        n = envolver(tmp, n, tmp2, TEXTO_MAX);
+        if (n < 0) {
+            fprintf(stderr, "F5 texto: MSG %u no se pudo envolver; queda el original\n", msg);
+            continue;
+        }
+        if (n > slot) {
+            fprintf(stderr, "F5 texto: MSG %u no entra en el slot (%d > %d); queda el original\n", msg, n, slot);
+            continue;
+        }
+        escribir(tabla, off, tmp2, n);
+    }
+
+    /* "(PS2)" global en las entradas sin override. */
+    if (quitar_ps2() != 0) {
+        for (k = 1; k <= count; k++) {
+            unsigned short tmp[TEXTO_MAX];
+            unsigned short tmp2[TEXTO_MAX];
+            const unsigned short *orig;
+            unsigned off;
+            int slot;
+            int n;
+            int n2;
+            int con_override = 0;
+
+            for (i = 0; i < (int)(sizeof(kDefs) / sizeof(kDefs[0])); i++) {
+                if ((unsigned)kDefs[i].msg + 1 == k) {
+                    con_override = 1;
+                    break;
+                }
+            }
+            if (con_override) {
+                continue; /* ya se aplico y se filtro arriba */
+            }
+            slot = slot_u16(w, count, k, &off);
+            if (slot < 0) {
+                continue;
+            }
+            orig = (const unsigned short *)(tabla + off);
+            n = 0;
+            while (orig[n] != 0 && n < TEXTO_MAX - 1) {
+                tmp[n] = orig[n];
+                n++;
+            }
+            tmp[n] = 0;
+            n2 = filtrar_ps2(tmp, tmp2, TEXTO_MAX);
+            if (n2 == n || n2 > slot) {
+                continue;
+            }
+            escribir(tabla, off, tmp2, n2);
+        }
+    }
+}
```

### 4.4 Ejemplos de override (efecto)

| MSG | estado | texto original | texto propuesto | slot (u16) | entra |
|---:|---|---|---|---:|---|
| 21 | 18/32 | `Save data already exists.\nWould you like to overwrite the data?` | `Save data already exists.\nOverwrite it?` | 95 | sí (40) |
| 24 | 27 | `The memory card (PS2) has been replaced.\nWould you like to overwrite the data?` | `The memory card has been replaced.\nOverwrite the data?` | 95 | sí (55) |
| 28 | 16 | `Save game data?` | `Save game data?` (queda igual; sirve para probar el mecanismo) | 31 | sí (16) |
| 37 | 28 | `Settings have been\nchanged. Save the\nchanged settings?` | `Settings have been changed.\nSave the changes?` | 63 | sí (46) |
| 13 | 23 | `Memory card (PS2)\nis unformatted.\nFormat memory card (PS2)?` | `Memory card is unformatted.\nFormat it?` | 63 | sí (39) |
| 27 | — | `Memory card (PS2) is unformatted.` | `Memory card is unformatted.` | 31 | sí (28) |

Además, con `texto_ps2=0` / `BT2_TEXTO_PS2=0`, las 49 entradas pierden `"(PS2)"` sin tocar el AFS. Probado
sobre la tabla extraída: todas las entradas siguen entrando en su slot (el filtro sólo acorta).

### 4.5 Cómo probarlo (no ejecutado)

```sh
cd BT2-Recomp
# compilar 3E3D38 (el resto no cambia) y enlazar
BT2_IRFIX=1 scripts/capped.sh 8G python3 port/tools/build_full.py --jobs 2 --only 3E3D38
scripts/capped.sh 8G python3 port/tools/link_full.py
# instalar sólo con el juego cerrado (pgrep -x bt2), guardando el binario anterior en backups/
```

Qué mirar:
1. Menú pausa → Memory Card → Save: la pregunta de sobrescritura debe decir `Overwrite it?` (MSG 21) y
   `Save game data?` (MSG 28). Con un save existente se ve la de MSG 21.
2. `BT2_TEXTO_PS2=0 ./bin/bt2`: los mensajes de "Checking memory card (PS2)..." y "Saving data. Do not
   remove memory card (PS2)..." deben quedar sin `(PS2)`.
3. `bt2_texto.txt` con `28=Save now?` debe verse en el estado 16.
4. `BT2_TEXTO_PS2` sin valor / `texto_ps2=1`: todo igual que antes (default).

---

## 5. Riesgos

1. **Otras pantallas no se tocan** (a propósito): la tabla de 49 entradas es la del diálogo `3E51F8`
   (sub-bloque 0 de `0x550`). El flujo del título (`3BE778`/`3BF748`, recurso `0x54F`) y las pantallas de
   borrar/copiar (`3E68D0`/`3E84B0`, otros sub-bloques) tienen sus propias tablas. Si el usuario quiere
   sacar `(PS2)` **de todas** las pantallas de memory card, hay que repetir el análisis para `0x54F`
   (su tabla está en `P+0x133D80`, formato distinto: `count=4` + offsets) y para los otros sub-bloques.
   No lo incluyo para no romper pantallas que no se probaron.
2. **Layout**: el panel está dimensionado para la línea más ancha del juego (429 px). El mecanismo
   respeta 429 px y 5 líneas; si un texto nuevo tiene **otra cantidad de líneas**, el `y` se corre según
   `29C038.c:47-65` (1..5 líneas). Es el comportamiento previsto del juego, pero no lo vi en pantalla.
   Si el texto nuevo excede el ancho, se envuelve; si aun así no entra en el slot, **se descarta ese
   mensaje** (queda el original), nunca se escribe fuera.
3. **El AFS no tiene checksum** y el port no verifica integridad: `plat_file.c` sólo lee `AFS\0`, cuenta y
   tabla `{offset,size}`. No hay nada que “romper” si se edita el archivo, pero **no lo hacemos**: el
   override es en RAM. El `McCard_Checksum` que llama `3E3D38.c:113` es sobre el **save** (`D_00387F2C`,
   0x4000), no sobre los textos.
4. **La copia es efímera**: `P` se descomprime de nuevo en cada apertura de la pantalla; el override se
   reaplica siempre. No queda texto cambiado en otras pantallas ni en el save.
5. **El drawer `29C038` es compartido** con otros diálogos (`+0x64==1`). Por eso **no** hookeamos el
   drawer: si se hiciera, habría que validar que `base` es esta tabla (49/0x100) para no pisar otro menú
   que use el mismo `MSG` con otro significado.
6. **La fuente no tiene `…`, `—`, `’`**: los textos nuevos deben usar `...`, `-`, `'`. Sí tiene `ñ/Ñ`,
   acentos, `¡¿` y paréntesis.

---

## 6. Lo que no pude confirmar

1. **Nada probado en ejecución**: no compilé, no instalé y no abrí el juego. El diff está verificado con
   `patch --dry-run` sobre una copia en `/tmp/f5/`, y `plat_text.c` compila con `gcc -m64 -fno-pie`
   (`-O1`/`-O2`) y se probó con un harness que carga `f3_s0.raw` y aplica los overrides. Falta verlo en
   pantalla.
2. **El ancho real de la caja de texto**: deduje el límite de 429 px de la línea más ancha del propio
   juego, no del scissor/rect del prim. Si el panel recorta antes, el límite efectivo sería menor.
3. **La dirección de `D_00387DA0+4` con el diálogo abierto**: los dumps de RAM que encontré tenían la
   tabla cargada pero el diálogo cerrado (`D_00387DA0+4` ya no apuntaba a ella). Sí confirmé que la tabla
   existe en RAM en dos direcciones distintas (0x9E89B8 / 0xB52FF8) con el mismo contenido que el AFS.
4. **La cantidad de líneas**: el switch 1..5 de `29C038` sugiere que el panel banca 1..5; no vi qué pasa
   visualmente si un override cambia de 3 a 2 líneas (debería subir/bajar el bloque, no romper).
5. **El flujo del título y borrar/copiar**: no analicé en detalle sus tablas (`0x54F`, otros sub-bloques);
   sólo confirmé que son distintas de la de `3E51F8`.

---

## 7. Evidencia y herramientas

- Tabla descomprimida: `/tmp/opencode/f3_s0.raw` (sub-bloque 0 de `0x550`, 0x12B340).
- Descompresor 1:1 de `func_002B24C8`: `/tmp/opencode/f3_lz.py`.
- AFS leído en modo sólo lectura con un parser de 20 líneas (`AFS\0`, cuenta, tabla `{offset,size}`);
  `0x550` → offset `0x1C22800`, size `0x22AB40`; SHA1 del payload `aecb3db6...` (el mismo de
  `/tmp/opencode/f3_pack550.bin`).
- Dumps de RAM: `BT2-test/logs/vivo/20261111-131314_ram1_f4957.bin` y
  `20261111-121635_ramkey1_f4116.bin`.
- Asm: `/tmp/opencode/full.asm` (`29bd58`, `29c038`, `29c800`, `29c7e0`, `286568`, `2a2018`) y
  `/tmp/opencode/ovl.dis` (`3e3d38`, `3e4cf8`, `3e51f8`, `3e6658`).
- Prueba del mecanismo: `/tmp/f5/plat_text.c` + `/tmp/f5/test.c` (carga `f3_s0.raw`, aplica overrides y
  filtro, imprime la tabla resultante). Compila y corre; no se tocó el proyecto.
