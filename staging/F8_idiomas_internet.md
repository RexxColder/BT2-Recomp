# F8 — Qué idiomas tiene BT2 y cómo encarar la traducción de los popups

Fecha: 2026-11-11.
Alcance: investigación de **solo lectura** sobre los datos del usuario y el código del port. No se compiló, no se instaló
nada y no se tocó el AFS, el ISO ni el save. Lo único que se agregó son los archivos de propuesta en
`BT2-Recomp/staging/F8_textos/` y este informe.

Material leído: `BT2-test/gamedata/DATA/ZS2US_1.AFS`, `ZS2US_2.AFS`, `BT2-test/bt2_texto.txt`,
`BT2-Recomp/port/full/plat_text.c`, `port/eq/29BB88.c`, `port/eq/3E3D38.c`, `staging/F5_textos_memorycard.md`,
`staging/F8_idiomas.md`.

---

## 0. Resumen en cinco líneas

- **NTSC-U (SLUS-21441):** texto **solo inglés**; voces **inglés + japonés** elegibles en Opciones → Sonido.
- **PAL (SLES-54164):** texto **Multi-5: EN/FR/DE/ES/IT**; voces **inglés + japonés**. El disco PAL no dobla las voces
  a cada idioma: cambia el texto, no las voces.
- **NTSC-J (SLPS-25690):** texto y voces **solo japonés** (no hay opción de voces inglesas). **Corea (SLKA-25397):**
  texto coreano, voces japonesas, basado en la versión USA.
- **En los datos USA no hay tablas por idioma.** La entrada `0x550` tiene **4 sub-bloques**, pero no son traducciones:
  solo el sub-bloque 0 trae la tabla de **49 mensajes**; los cuatro traen la **misma tabla de 35 ayudas** en inglés.
  La misma tabla de 49 está duplicada, idéntica, en `0x545`, `0x546`, `0x54F` y `0x550`.
- **La bandera `D_00387F2C + 0x1008` es de voces, no de texto** (bit 0: 1 = inglés, 0 = japonés). Para texto el port
  necesita su propio selector y sus propios archivos: dejé **ES/FR/DE/IT** propuestos y validados contra los slots.

---

## 1. Idiomas de DBZ Budokai Tenkaichi 2 en PS2, por región

### 1.1 Tabla

| Región | Serial | Texto | Voces | Notas | Fuentes |
|---|---|---|---|---|---|
| **NTSC-U (USA)** | SLUS-21441 (y SLUS-21441GH) | **Inglés** | **Inglés + japonés** | El tag de Redump es `En,Ja`; el `Ja` es audio, no texto. OGDB USA dice "Textsprache: Englisch" y "Sprachausgabe: Englisch" (el default). | [1], [2], [3], [4] |
| **PAL (Europa/Australia)** | SLES-54164 (también `-ANZ` y `/P`) | **EN, FR, DE, ES, IT** | **Inglés + japonés** | Redump lo titula `(Europe, Australia) (En,Fr,De,Es,It)` y en los comentarios del disco dice **"Voices: English, Japanese"**. OGDB Alemania lista texto DE/EN/FR/IT/ES. | [5], [6], [7], [8] |
| **NTSC-J (Japón)** | SLPS-25690 | **Japonés** | **Japonés** | Las versiones japonesas no tienen la opción de voces inglesas. | [3], [9], [10] |
| **Corea** | SLKA-25397 | **Coreano** | **Japonés** | Localización coreana basada en la versión USA; NamuWiki dice que la serie está traducida al coreano y que las voces son las japonesas. | [11], [12] |
| **Wii PAL** (contexto, no PS2) | RDBPAF | **EN, FR, DE, ES, IT** | EN + JA | GametDB lista los 5 idiomas de texto; Kanzenshuu dice que la opción de voces también está en Wii. | [3], [13] |

### 1.2 Texto vs. voces: la confusión típica

- **Las voces no se doblan a los 5 idiomas.** En BT2 las voces son dos bancos: inglés (FUNimation) y japonés. Eso vale
  para USA y PAL. El disco japonés trae solo el banco japonés; el coreano usa el japonés.
- **El texto sí cambia por región.** USA es English-only. PAL es Multi-5. Japón es japonés. Corea es coreano.
- El tag `En,Ja` de Redump para USA **no significa "texto japonés"**: significa que el disco tiene texto inglés y audio
  japonés. La prueba local está en `staging/F8_idiomas.md` §2.2-2.3: los 535 packs de historia `0x319..0x541` son
  UTF-16LE en inglés, y los únicos assets japoneses son bancos ADX de voz.
- **No encontré documentación de un selector de texto dentro del juego PAL.** Lo más probable es que el disco PAL elija
  el texto por el idioma de la consola o por un ítem de opciones, pero **no lo pude verificar** porque no tengo la ISO
  PAL. Lo que sí está confirmado por Redump es que el disco contiene los 5 idiomas de texto.

### 1.3 Qué implica para el port

El port corre sobre la ISO **USA** (`BT2-test/gamedata` = `ZS2US_*`). Esa ISO **no trae los textos francés/alemán/
español/italiano**. Aunque el disco PAL los tenga, no están en los datos que usa el port. Por eso:

- No se puede "elegir el idioma del disco" en la versión USA: no hay tablas que elegir.
- El selector de texto del port tiene que ser **una capa de traducción propia** (archivos `bt2_texto.<lang>.txt`),
  no un índice de sub-bloque ni una bandera del save.
- Si algún día se consigue la ISO PAL, hay que repetir el análisis de `0x550`/`0x545`/`0x546`/`0x54F` sobre ella para
  ver si trae 5 tablas de 49 entradas (una por idioma) o 5 recursos distintos. **Eso no está verificado.**

---

## 2. Análisis de los datos del usuario (solo lectura)

### 2.1 La entrada `0x550` y sus 4 sub-bloques

`ZS2US_1.AFS` es un AFS normal: `AFS\0`, `u32 count = 0x33B2`, y una tabla de `count` pares `{offset, size}`.
`ZS2US.DIR` es solo una lista de nombres de archivo (`zs2us_1.afs`, `zs2us_2.afs`, ...); **no** tiene offsets.
Los offsets que usa `port/full/plat_file.c` salen de la tabla del AFS. La entrada **`0x550`** está en:

- `offset = 0x1C22800`
- `size = 0x22AB40` (2.272.064 bytes)

La entrada es un **contenedor**:

- `u32 count = 4` en `+0x00`
- `u32 header = 0x40` en `+0x04`
- 4 offsets de fin en `+0x08`: `0x8AD00`, `0xF1E40`, `0x1B46C0`, `0x22AB40`

Cada sub-bloque tiene su header `{u32 destSize, u32 packedSize, ...}` y se descomprime con el mismo algoritmo que
`func_002B24C8` (LZ propio de CRI). Los tamaños son:

| Sub-bloque | Rango dentro de la entrada | Bytes comprimidos | `destSize` | `packedSize` | Qué tiene |
|---:|---|---:|---:|---:|---|
| **0** | `0x40 .. 0x8AD00` | `0x8ACC0` | `0x12B340` | `0x8ACB3` | **tabla de 49 mensajes** en `P+0xFCC80` + tabla de 35 ayudas en `P+0xF2A80` |
| **1** | `0x8AD00 .. 0xF1E40` | `0x67140` | `0xB4C00` | `0x670FD` | solo tabla de 35 ayudas en `P+0xAAA00` |
| **2** | `0xF1E40 .. 0x1B46C0` | `0xC2880` | `0x18CBC0` | `0xC2868` | solo tabla de 35 ayudas en `P+0x15F740` |
| **3** | `0x1B46C0 .. 0x22AB40` | `0x76480` | `0x11D380` | `0x7645C` | solo tabla de 35 ayudas en `P+0x112DC0` |

`P` = sub-bloque ya descomprimido. La tabla de 49 arranca con `u32 count = 49` y `word[1] = 0x100`; la de 35 con
`count = 35` y `word[1] = 0xC0`.

### 2.2 Primeras cadenas de cada sub-bloque

**Sub-bloque 0 — tabla de 49 (la del diálogo de memory card):**

```
word[1]  "MEMORY CARD slot 1"
word[2]  "MEMORY CARD slot 2"
word[3]  "MEMORY CARD slot 1 \nand MEMORY CARD slot 2"
word[4]  "Current settings will be lost\nif you begin a new game. OK?"
...
word[29] "Save game data?"
...
word[49] "Exit loading?"
```

**Sub-bloques 0, 1, 2 y 3 — tabla de 35 (idéntica en los cuatro):**

```
texto[1] "You can set the various game\nsettings. Choose wisely!"
texto[2] "You can save and load\ngame data. Save often!"
texto[3] "You can change the \ncontroller's button settings\nto make it easier for you to \nuse."
...
texto[35] "Return to default. \nOK?"
```

La tabla de 35 es **byte-idéntica** en los cuatro sub-bloques: `0x1400` bytes, SHA1 `a3a971c495c9eb69...`.
No es una traducción: es la misma ayuda de opciones que cada pantalla lleva embebida.

### 2.3 ¿Hay tablas por idioma?

**No, en el disco USA no.** Evidencia:

1. El sub-bloque 0 tiene **una sola** tabla de 49; los otros tres **no tienen** tabla de 49. Si fueran idiomas, cada
   sub-bloque tendría su tabla de 49 con el mismo `count`.
2. La tabla de 35 que sí está en los cuatro es **la misma en inglés**, no una versión traducida por sub-bloque.
3. Barrido de **los sub-bloques relevantes ya descomprimidos** (`0x550` sub 0-3, `0x545` sub 1, `0x546` sub 0,
   `0x54F` sub 0) buscando UTF-16LE de palabras clave en otros idiomas: `TARJETA`, `CARTE`, `KARTE`, `SPEICHER`,
   `SCHEDA`, `MEMORIA`, `メモリー` → **0 ocurrencias**. En todos ellos solo aparece `MEMORY` (en inglés).
   Un barrido de los AFS crudos (sin descomprimir) también encuentra `MEMORY` en `0x545`/`0x546`, pero eso solo prueba
   las partes sin comprimir: la prueba fuerte es el barrido de los sub-bloques descomprimidos.
4. Los 535 packs de historia (`0x319..0x541`) son inglés (ver `staging/F8_idiomas.md` §2.3).

**Conclusión:** los 4 sub-bloques de `0x550` son **pantallas distintas**, no idiomas. El sub-bloque 0 es el diálogo de
memory card; los otros son otras pantallas de opciones/menú que comparten la tabla de ayudas. No hay un índice de
idioma que el port pueda usar.

### 2.4 La misma tabla de 49 está en cuatro recursos

Esto es importante para la traducción: la tabla de 49 **no es exclusiva de `0x550`**. Es la misma copia byte a byte
(SHA1 `a87734616a81d9f366e95f167fbff855ccfe996a...`, `0x1C80` bytes) en:

| `flid` | Offset en el AFS | Size | Sub-bloque | Offset de la tabla en `P` | Quién lo carga |
|---:|---:|---:|---:|---:|---|
| `0x545` | `0x4C1800` | `0x1D4D80` | 1 | `0x1F1840` | menú principal (`port/eq/3B3100.c:28`) |
| `0x546` | `0x696800` | `0x34BBC0` | 0 | `0x18D440` | battle setup (`port/eq/418410.c:31`, decompress `41A988.c:54`) |
| `0x54F` | `0x1A36800` | `0x1EB880` | 0 | `0x1433C0` | flujo del título (`port/eq/3C0700.c:30`, `3BE778.c:36`) |
| `0x550` | `0x1C22800` | `0x22AB40` | 0 | `0xFCC80` | diálogo de memory card (`port/eq/3E3B98.c:30`, `3E3D38.c:54`) |

Las cuatro copias tienen los mismos 49 strings, en el mismo orden. Si el port traduce una, conviene traducir las
cuatro para que los carteles del título/menú no queden en inglés. **Hoy el port solo engancha el diálogo que pasa por
`func_0029BB88` (`port/eq/29BB88.c:48`), que es el de `0x550`.** No verifiqué si las otras tres copias llegan a esa
función con su tabla de 49; si no, hay que engancharlas aparte (ver §4.4).

### 2.5 La bandera `D_00387F2C + 0x1008` no es de texto

`staging/F8_idiomas.md` ya lo documentó y lo confirmé en el código:

- `+0x1008` bit 0: **1 = voces inglesas** (default del save nuevo), **0 = voces japonesas**.
- Todos los usos son IDs de archivos **ADX** (audio) o tablas de sprites; ninguno elige texto.
- La opción existe en el menú del juego: Opciones → Sonido → "Japanese voice" (`port/eq/3E92E8.c:228-252`).
- El port ya la respeta; no hay que portar nada para las voces.

Entonces: **no sirve para elegir el idioma del texto**. El texto del disco USA es inglés y no depende del save.

---

## 3. Propuesta de traducción de los 49 mensajes

### 3.1 Restricciones reales del port

- Cada string vive en un slot alineado a `0x40`; la capacidad es `(next_offset - offset) / 2 - 1` unidades UTF-16.
  Hay slots de 31, 63, 95, 127 y 159 u16. Los más ajustados son **MSG 0/1/5/10/14/20/22/27/28/30/38/39/47/48**
  (31 u16).
- Ancho máximo por línea: **429 px** (tabla de avances del font0). El port envuelve solo si hace falta, pero conviene
  dejar los saltos puestos.
- Máximo **5 líneas**.
- Sin `…` (U+2026) ni comillas tipográficas: el font0 no las tiene. Usar `...`, `-`, `'` y comillas ASCII.
- El font0 **sí** tiene `¿ ¡ ñ Ñ` y vocales acentuadas; también `Ä Ö Ü ß` y `à è é ì ò ù` (F5 §3.2).
- El parser del port lee `MSG=texto` y interpreta `\n` como salto. Las líneas que empiezan con `#` son comentarios.

### 3.2 Archivos entregados

Están en `BT2-Recomp/staging/F8_textos/` (propuesta, **no instalados**):

| Archivo | Idioma | SHA1 |
|---|---|---|
| `bt2_texto.es.txt` | Español | `25eeea071c86b76d6040ab12e625721d68aa2e5d` |
| `bt2_texto.fr.txt` | Francés | `90dbdfc0220e85fefabaf8cf264b55fea58b3d79` |
| `bt2_texto.de.txt` | Alemán | `202c4ec882d52cea734ecb6666e52f7f9d566983` |
| `bt2_texto.it.txt` | Italiano | `cff88f0a888fe1baceef9be90b51a27bbfdee1ae` |

Todos tienen 49 líneas `MSG=...`, el mismo orden que `BT2-test/bt2_texto.txt`, y pasan el verificador de slots/ancho
(§3.5).

### 3.3 Español: tabla completa

Terminología: **"archivo de guardado"** para reflejar que el port emula la memory card como un archivo/folder. Si
preferís "partida guardada", es un reemplazo directo y suele entrar mejor en los slots de 31; avisá y lo cambio.

| MSG | Slot u16 | Largo | Ancho máx. | Inglés actual | Español propuesto |
|---:|---:|---:|---:|---|---|
| 0 | 31 | 19 | 199 | `Save file` | `Archivo de guardado` |
| 1 | 31 | 19 | 199 | `Save file` | `Archivo de guardado` |
| 2 | 63 | 25 | 166 | `Save file` | `Ranuras 1 y 2 de\nguardado` |
| 3 | 63 | 43 | 233 | `Start a new game?` | `Se perderán los ajustes\nactuales. ¿Empezar?` |
| 4 | 63 | 42 | 233 | `Load this save file?` | `Se perderán los ajustes\nactuales. ¿Cargar?` |
| 5 | 31 | 27 | 273 | `No save file found.` | `No hay archivo de guardado.` |
| 6 | 127 | 38 | 222 | `Not enough space.\nContinue anyway?` | `No hay espacio.\n¿Continuar igualmente?` |
| 7 | 63 | 38 | 249 | `Save file not found.` | `No se encontró el archivo\nde guardado.` |
| 8 | 95 | 16 | 166 | `Loading save file` | `Cargando archivo` |
| 9 | 63 | 16 | 150 | `Load failed.` | `Error al cargar.` |
| 10 | 31 | 14 | 146 | `Load successful` | `Carga correcta` |
| 11 | 63 | 27 | 277 | `Create save file?` | `¿Crear archivo de guardado?` |
| 12 | 127 | 15 | 155 | `Creating save file` | `Creando archivo` |
| 13 | 63 | 25 | 147 | `Save file not found.\nCreate it?` | `No hay archivo.\n¿Crearlo?` |
| 14 | 31 | 14 | 146 | `Save file created` | `Archivo creado` |
| 15 | 63 | 14 | 134 | `Create failed` | `Error al crear` |
| 16 | 95 | 35 | 191 | `Not enough space.\n75 KB required.` | `No hay espacio.\nSe necesitan 75 KB.` |
| 17 | 159 | 38 | 222 | `Not enough space.\nContinue anyway?` | `No hay espacio.\n¿Continuar igualmente?` |
| 18 | 127 | 15 | 155 | `Creating save file` | `Creando archivo` |
| 19 | 63 | 14 | 146 | `Save file created` | `Archivo creado` |
| 20 | 31 | 14 | 134 | `Create failed` | `Error al crear` |
| 21 | 95 | 38 | 199 | `Save file exists.\nOverwrite it?` | `Ya existe el archivo.\n¿Sobrescribirlo?` |
| 22 | 31 | 25 | 239 | `Overwrite save file?` | `¿Sobrescribir el archivo?` |
| 23 | 95 | 38 | 188 | `Save failed.\nOverwrite anyway?` | `Error al guardar.\n¿Sobrescribir igual?` |
| 24 | 95 | 35 | 174 | `Save file changed.\nOverwrite it?` | `El archivo cambió.\n¿Sobrescribirlo?` |
| 25 | 63 | 47 | 298 | `Load failed.\nSave may be corrupt.` | `Error al cargar.\nEl archivo puede estar dañado.` |
| 26 | 63 | 27 | 273 | `No save file.` | `No hay archivo de guardado.` |
| 27 | 31 | 9 | 95 | `Save?` | `¿Guardar?` |
| 28 | 31 | 15 | 157 | `Save game data?` | `¿Guardar datos?` |
| 29 | 95 | 17 | 177 | `Saving save file` | `Guardando archivo` |
| 30 | 31 | 17 | 179 | `Save successful` | `Guardado correcto` |
| 31 | 63 | 17 | 161 | `Save failed.` | `Error al guardar.` |
| 32 | 63 | 15 | 157 | `Save now?` | `¿Guardar ahora?` |
| 33 | 127 | 19 | 205 | `Checking save file` | `Comprobando archivo` |
| 34 | 127 | 19 | 205 | `Checking save file` | `Comprobando archivo` |
| 35 | 63 | 17 | 161 | `Save failed.` | `Error al guardar.` |
| 36 | 63 | 21 | 217 | `Start without saving?` | `¿Empezar sin guardar?` |
| 37 | 63 | 21 | 211 | `Save settings?` | `¿Guardar los ajustes?` |
| 38 | 31 | 30 | 169 | `Delete save file?` | `¿Borrar los datos\nde guardado?` |
| 39 | 31 | 26 | 181 | `Save file deleted` | `Datos de guardado\nborrados` |
| 40 | 63 | 16 | 148 | `Delete failed.` | `Error al borrar.` |
| 41 | 95 | 16 | 162 | `Deleting save file` | `Borrando archivo` |
| 42 | 95 | 18 | 168 | `Reading save file...` | `Leyendo archivo...` |
| 43 | 95 | 18 | 168 | `Reading save file...` | `Leyendo archivo...` |
| 44 | 95 | 38 | 249 | `Save file not found.` | `No se encontró el archivo\nde guardado.` |
| 45 | 63 | 35 | 220 | `Save file is corrupted.` | `El archivo de guardado\nestá dañado.` |
| 46 | 159 | 19 | 205 | `Checking save file` | `Comprobando archivo` |
| 47 | 31 | 19 | 181 | `Exit without saving?` | `¿Salir sin guardar?` |
| 48 | 31 | 7 | 63 | `Exit?` | `¿Salir?` |

**Ojo con los slots ajustados:** MSG 5 usa 27 de 31 u16 y MSG 38 usa 30 de 31. Si se cambia la redacción, esos dos
son los primeros que se salen. El port, si no entra, deja el texto original y avisa una vez por MSG.

### 3.4 Francés, alemán e italiano

Los tres archivos están completos (49 mensajes). Muestras:

| MSG | Francés | Alemán | Italiano |
|---:|---|---|---|
| 5 | `Aucune sauvegarde.` | `Kein Spielstand da.` | `Nessun salvataggio.` |
| 9 | `Échec du chargement.` | `Laden fehlgeschlagen.` | `Caricamento fallito.` |
| 21 | `La sauvegarde existe.\nL'écraser?` | `Spielstand existiert.\nÜberschreiben?` | `Salvataggio esistente.\nSovrascriverlo?` |
| 25 | `Échec du chargement.\nLa sauvegarde peut être corrompue.` | `Laden fehlgeschlagen.\nSpielstand evtl. defekt.` | `Caricamento fallito.\nIl file può essere corrotto.` |
| 38 | `Effacer la sauvegarde?` | `Spielstand löschen?` | `Eliminare il salvataggio?` |
| 47 | `Quitter sans sauver?` | `Ohne Speichern beenden?` | `Uscire senza salvare?` |

Terminología: FR `sauvegarde`, DE `Spielstand`, IT `salvataggio`. Son las formas cortas y naturales; las largas
(`fichier de sauvegarde`, `Speicherdatei`, `file di salvataggio`) no entran en varios slots de 31.

### 3.5 Verificación hecha

Escribí un checker que:

1. Lee la tabla real de `0x550`/`P+0xFCC80` (49 offsets) y calcula la capacidad de cada slot.
2. Parsea cada `bt2_texto.<lang>.txt` y convierte `\n` en salto.
3. Verifica `len(texto) <= slot`, `líneas <= 5` y `ancho(línea) <= 429` con la misma tabla `kAdv` del font0.

Resultado: **los 4 archivos pasan los 49 mensajes**. En español el ancho máximo es MSG 25 con 298 px; en las otras
tres el máximo global es 352 px (FR MSG 25). Todo queda por debajo de 429. No se probó el render real en el juego;
eso queda para cuando se instale uno.

### 3.6 Lo que esta traducción NO cubre

- **Solo los 49 mensajes de memory card** (y, si se enganchan, las otras tres copias de la misma tabla).
- **No** traduce los 535 packs de historia, los menús, los nombres de ataques, los tutoriales ni los textos de
  personajes. Eso es otro trabajo (ver `staging/F8_idiomas.md` §3).
- **No** cambia las voces: siguen siendo EN/JP y se eligen con la opción del juego.

---

## 4. Plan de integración en el port (sin implementar)

### 4.1 Archivos y setting

Propuesta de layout, relativo al CWD del juego (`BT2-test/`, que es donde corre `bin/bt2`):

```
BT2-test/
  textos/
    bt2_texto.en.txt      (copiar el bt2_texto.txt actual)
    bt2_texto.es.txt
    bt2_texto.fr.txt
    bt2_texto.de.txt
    bt2_texto.it.txt
  bt2_texto.txt           (fallback viejo = inglés, no rompe instalaciones actuales)
```

Setting nuevo en `bt2_settings.txt`:

```
idioma=0   # 0=EN, 1=ES, 2=FR, 3=DE, 4=IT
```

El parser de `port/full/gs/plat_settings_bt3.c:34` acepta nombres `[a-z0-9_]` y valores enteros, así que `idioma`
es válido sin tocar el parser. El setup app escribe esa línea antes de lanzar el juego. `Port_Setting("idioma", 0)`
la lee.

### 4.2 Cambios en `port/full/plat_text.c` (archivo:línea)

| Línea actual | Qué hay | Qué habría que hacer |
|---:|---|---|
| 33 | `int Port_Setting(...) __attribute__((weak));` | Ya está; se usa para `idioma`. |
| 77 | `static int sInit;` | Se mantiene: el archivo se lee una vez por proceso. Cambiar de idioma requiere reiniciar el juego. |
| 81-130 | `leer_archivo()` | Agregar la selección por `idioma` y el fallback. |
| 90-93 | `ruta = getenv("BT2_TEXTO"); if (... ) ruta = "bt2_texto.txt";` | Reemplazar por: `$BT2_TEXTO` si está; si no, `textos/bt2_texto.<lang>.txt`; si no existe, `bt2_texto.txt`. |
| 94 | `fp = fopen(ruta, "r");` | Si `fp == NULL` y el idioma no es EN, reintentar con `textos/bt2_texto.en.txt` y después con `bt2_texto.txt`; avisar por stderr una vez. |
| 110-125 | parser `MSG=texto` | No se toca. |
| 122 | `if (msg >= 0 && msg < TEXTO_ENTRADAS)` | No se toca. |
| 302 | `Port_TextoAplicarTabla(uint32_t tabla)` | No se toca: ya aplica overrides a cualquier tabla de 49 que le pasen. |
| 320-324 | guard `count == 49 && (w[1] & ~3) == 0x100` | No se toca: es el fingerprint de la tabla. |
| 365-378 | filtro `(PS2)`, wrap y escritura | No se toca. |

Esquema del cambio en `leer_archivo()` (NO aplicado):

```c
static const char *kTextoIdioma[5] = {
    "textos/bt2_texto.en.txt",
    "textos/bt2_texto.es.txt",
    "textos/bt2_texto.fr.txt",
    "textos/bt2_texto.de.txt",
    "textos/bt2_texto.it.txt",
};
char rutaBuf[256];
int lang = 0;

/* ... dentro de leer_archivo(), después de sInit = 1; ... */
ruta = getenv("BT2_TEXTO");
if (ruta == NULL || ruta[0] == 0) {
    lang = Port_Setting != NULL ? Port_Setting("idioma", 0) : 0;
    if (lang < 0 || lang > 4) {
        lang = 0;
    }
    snprintf(rutaBuf, sizeof rutaBuf, "%s", kTextoIdioma[lang]);
    ruta = rutaBuf;
}
fp = fopen(ruta, "r");
if (fp == NULL && lang != 0) {
    ruta = "textos/bt2_texto.en.txt";
    fp = fopen(ruta, "r");
}
if (fp == NULL) {
    ruta = "bt2_texto.txt";
    fp = fopen(ruta, "r");
}
```

Detalles:

- `snprintf` ya está disponible (`<stdio.h>` está incluido en `plat_text.c`).
- `Port_Setting` es weak: si no está linkeado, `lang` queda 0.
- `sInit` cachea: el setup app tiene que escribir `idioma` **antes** de lanzar el juego. Si se cambia en caliente,
  no se relee hasta reiniciar.
- `$BT2_TEXTO` sigue ganando sobre todo, para pruebas de un solo archivo.
- Si el archivo del idioma no existe, el fallback deja el inglés y no rompe nada.

### 4.3 Selección en el setup app

Contrato mínimo:

1. Combo "Idioma del texto": English / Español / Français / Deutsch / Italiano.
2. Al aceptar, escribir `idioma=N` en `bt2_settings.txt` (mismo archivo que ya usa el port para `scale`, `music`, etc.).
3. Copiar/instalar los `textos/bt2_texto.<lang>.txt` si no están.
4. Opcional: mostrar "se aplica al reiniciar el juego" (por el `sInit`).

Si el setup app no quiere tocar `bt2_settings.txt`, la alternativa es lanzar el juego con
`BT2_TEXTO=textos/bt2_texto.es.txt`; el port ya lo respeta. Pero para que persista, el setting es mejor.

### 4.4 Cobertura de las otras tres copias de la tabla

La tabla de 49 es idéntica en `0x545`, `0x546`, `0x54F` y `0x550` (§2.4). El hook actual está en
`port/eq/29BB88.c:48`: cualquier diálogo que llame a `func_0029BB88(..., tabla)` con una tabla de 49 entra. Hoy está
confirmado para el diálogo de memory card (`0x550`). **No verifiqué** si los carteles del título/menú principal
(`0x545`), battle setup (`0x546`) y flujo del título (`0x54F`) pasan su tabla de 49 a `func_0029BB88`; si no lo hacen,
hay que engancharlos en sus loaders:

- `port/eq/3B3100.c:34` (0x545, después de `func_002B24C8`).
- `port/eq/41A988.c:54` (0x546, después de `func_002B24C8`).
- `port/eq/3BE778.c:36` (0x54F, después de `func_002B24C8`).
- `port/eq/3E3D38.c:54` (0x550, ya cubierto vía `29BB88`).

La forma robusta es un `Port_TextoAplicarRecurso(void *P)` que escanee `P` buscando el fingerprint
(`count == 49`, `w[1] & ~3 == 0x100`, string `MEMORY CARD slot 1` en `P+0x100`) y llame a
`Port_TextoAplicarTabla(P + off)`. Así no dependés de offsets fijos ni del sub-bloque. Si se opta por offsets fijos,
ya están medidos en la tabla de §2.4, pero **pueden cambiar en la versión PAL**.

### 4.5 Qué NO cubre este plan

- No traduce los textos de historia/menús (535 packs + menús comprimidos).
- No cambia las voces.
- No reemplaza el AFS: todo sigue siendo override en RAM, como el F5 actual.
- No incluye un selector dentro del juego (F1/ImGui); el pedido habla del setup app. Si se quiere también en F1, es
  un combo que escriba `idioma` y pida reinicio (o releer el archivo).

---

## 5. Verificado / no verificado

### Verificado leyendo datos y código

- La entrada `0x550` tiene 4 sub-bloques y sus tamaños/offsets (§2.1).
- Solo el sub-bloque 0 tiene la tabla de 49; los cuatro tienen la misma tabla de 35 en inglés (§2.2-2.3).
- La tabla de 49 es byte-idéntica en `0x545`/`0x546`/`0x54F`/`0x550` (§2.4).
- Barrido de los sub-bloques relevantes descomprimidos (`0x550` 0-3, `0x545` 1, `0x546` 0, `0x54F` 0): no hay
  `TARJETA`/`CARTE`/`KARTE`/`SPEICHER`/`SCHEDA`/`MEMORIA`/`メモリー` en UTF-16LE; solo `MEMORY` en inglés.
- `+0x1008` es la bandera de voces (1=EN, 0=JP), no de texto (F8_idiomas.md + código).
- Los 4 archivos de traducción pasan slots (31..159 u16), 5 líneas y 429 px.
- El font0 tiene los caracteres acentuados que usan las traducciones (F5 §3.2).

### No verificado

- **La ISO PAL no está disponible**: no sé si el disco PAL trae 5 tablas de 49, 5 recursos o textos en otro formato.
  Si aparece, hay que repetir §2 sobre `ZS2US`→`SLES` y ajustar el plan.
- **El render real** de las traducciones en el juego (no se instalaron).
- **La cobertura de las otras tres copias** (`0x545`/`0x546`/`0x54F`) por `func_0029BB88`; hay que probarlo o
  engancharlas como en §4.4.
- **El idioma de texto del PAL**: no encontré si se elige por consola o por menú. No afecta al port USA, pero es la
  pregunta que quedaría abierta si se quiere usar el disco PAL.

---

## 6. URLs y fuentes

1. Redump USA (SLUS-21441, `(USA) (En,Ja)`): https://redump.info/disc/4045
2. OGDB USA (texto inglés, voz inglés): https://ogdb.eu/index.php?gameid=43450&section=game
3. Kanzenshuu — menú de voces EN/JP en BT2, y las versiones japonesas sin voces inglesas:
   https://www.kanzenshuu.com/2026/08/21/budokai-tenkaichi-games-voice-menu/
4. PSXDatacenter (SLUS-21441 `[E][J]`): https://psxdatacenter.com/psx2/ulist2.html
5. Redump PAL (SLES-54164, `(Europe, Australia) (En,Fr,De,Es,It)`, comentario "Voices: English, Japanese"):
   https://redump.info/disc/4285
6. Titlescreen PAL (languages En,Fr,De,Es,It): https://titlescreen.org/release/r5pmbnyv/dragon-ball-z-budokai-tenkaichi-2
7. OGDB Alemania (texto DE/EN/FR/IT/ES, voz inglés): https://ogdb.eu/index.php?gameid=13677&section=game
8. CDRomance Europa (languages English, French, German, Italian, Japanese, Spanish; SLES-54164):
   https://cdromance.org/ps2-iso/dragon-ball-z-budokai-tenkaichi-2-europe/
9. PCSX2 Wiki (seriales por región: SLUS-21441, SLES-54164, SLPS-25690, SLKA-25397):
   https://wiki.pcsx2.net/Dragon_Ball_Z:_Budokai_Tenkaichi_2
10. GameFAQs — Release Data (fechas/seriales JP, KO, EU, US, AU):
    https://gamefaqs.gamespot.com/ps2/932683-dragon-ball-z-budokai-tenkaichi-2/data
11. NamuWiki — versión coreana traducida y voces japonesas:
    https://en.namu.wiki/w/%EB%93%9C%EB%9E%98%EA%B3%A4%EB%B3%BC%20Z%20%EC%8A%A4%ED%8C%8C%ED%82%B9!%20%EB%84%A4%EC%98%A4
12. Redump Corea (SLKA-25397): https://redump.info/disc/105962
13. GametDB Wii PAL (EN, FR, DE, ES, IT): https://www.gametdb.com/Wii/RDBPAF
14. Archive.org PS2 BoB Collection (nombres `(Europe, Australia) (En,Ja,Fr,De,Es,It)`):
    https://archive.org/details/ps2_bob_collection

---

## 7. Archivos de esta entrega

- `BT2-Recomp/staging/F8_idiomas_internet.md` — este informe.
- `BT2-Recomp/staging/F8_textos/bt2_texto.es.txt` — propuesta español (49 mensajes).
- `BT2-Recomp/staging/F8_textos/bt2_texto.fr.txt` — propuesta francés.
- `BT2-Recomp/staging/F8_textos/bt2_texto.de.txt` — propuesta alemán.
- `BT2-Recomp/staging/F8_textos/bt2_texto.it.txt` — propuesta italiano.

No se modificó ningún archivo vivo del port ni de `BT2-test/`: los `.txt` son propuestas en staging. Para probar uno:

```bash
cp BT2-test/bt2_texto.txt BT2-Recomp/backups/bt2_texto.txt.pre_f8
cp BT2-Recomp/staging/F8_textos/bt2_texto.es.txt BT2-test/bt2_texto.txt
# jugar y mirar el diálogo de memory card; después restaurar el backup
```
