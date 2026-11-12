# F8 — Cómo guarda el multiidioma la versión PAL/EU (En/Fr/De/Es/It)

Fecha: 2026-11-11. **Solo lectura sobre el proyecto**: no se compiló, no se ejecutó el port y no se tocó
`/mnt/datos2/BT2-Decomp`. Todo el análisis se hizo en `/tmp/opencode/eu/` sobre una copia del ISO; el zip del
usuario se abrió en modo lectura.

Objetivo: entender el multiidioma de la ISO EU para que el setup del port pueda extraer de ahí los textos y las
texturas de menú, manteniendo la ISO USA como base (el modelo que usa Tenkaichi3Decomp: USA obligatoria + EU para
los idiomas).

---

## 0. Resumen en cinco bullets

- **La EU trae 5 copias completas de los textos**, no un selector dentro de un mismo archivo:
  - **Historia**: 5 bloques de **553 entradas** (packs `0x319..0x541` de la USA) con stride **`0x229`**:
    EN `0x319`, ES `0x542`, DE `0x76B`, FR `0x994`, IT `0xBBD`. Son textos UTF-16LE sin comprimir.
  - **Menús**: 5 bloques de **23 entradas** con stride **`0x17`**, base EU **`0xDE9`**:
    EN `0xDE9`, ES `0xE00`, DE `0xE17`, FR `0xE2E`, IT `0xE45`. Ahí viven los textos de menú y los recursos
    gráficos (FOD/texturas) de cada idioma.
- **Los guiones GSC son byte-idénticos entre USA y EU** (mismos bytes, distinto id de AFS). Por lo tanto el offset
  de idioma **se aplica en el ejecutable**, no en los guiones: el port puede reproducirlo remapeando ids en la
  capa ADXF (`func_002EB9B0`), sin tocar los GSC ni los datos de la USA.
- **El diálogo de memory card** sigue siendo el recurso `0x550` de la USA; en la EU es `bloque_de_menú + 0xC`:
  EN `0xDF5`, ES `0xE0C`, DE `0xE23`, FR `0xE3A`, IT `0xE51`. Tiene el mismo contenedor de 4 sub-bloques y la
  misma tabla de **49 mensajes UTF-16LE**, pero el offset de la tabla dentro del sub-bloque descomprimido cambia
  por idioma (`0xFCC80`, `0xFCB00`, `0xFC140`, `0xFCD00`, `0xFCBC0`).
- **Las texturas de menú están en el AFS, no en `BIN/DBZP.BIN`**. `DBZP.BIN` es el overlay MIPS del menú
  (511.855 B en EU, 513.167 B en USA: código, no texturas). El bloque de 23 entradas por idioma pesa ~38,9 MB y
  21 de sus 23 entradas cambian entre idiomas; ahí están los FOD y sus texturas.
- **Recomendación**: copiar `DATA/ZS2EU_1.AFS` entero (1,1 GB) como partición extra y remapear ids es lo más
  simple y seguro; si se quiere un pack chico, alcanza con los 5 bloques de historia + 5 bloques de menú
  (~196,5 MB) o sólo los 4 idiomas distintos del inglés (~157,3 MB). **No** copiar `ZS2EU_2.AFS` entero: está
  reordenado respecto de la USA; sólo sus 10 archivos de condiciones de misión (3,8 MB) son texto localizado.

---

## 1. Contenido del zip y del ISO

### 1.1 Zip

`/home/rexx/Descargas/Dragon Ball Z - Budokai Tenkaichi 2 (Europe Australia) (EnFrDeEsIt).zip`

- Tamaño: **1.856.342.708 B** (1,73 GiB).
- Contiene **un solo archivo**:
  - `Dragon Ball Z - Budokai Tenkaichi 2 (Europe, Australia) (En,Fr,De,Es,It).iso`
  - Tamaño real: **3.148.382.208 B** (2,93 GiB).
- El zip no está cifrado; se extrajo con `unzip` (en esta máquina no hay `7z` en el PATH).

### 1.2 Contenido del ISO (nombres y tamaños)

| Archivo | Tamaño EU | Nota |
|---|---:|---|
| `SYSTEM.CNF` | 58 | `BOOT2 = cdrom0:\SLES_541.64;1`, `VMODE = PAL` |
| `SLES_541.64` | 2.681.824 | ejecutable PAL; USA es `SLUS_214.41` (2.675.936) |
| `BIN/DBZP.BIN` | 511.855 | overlay del menú (código MIPS); USA 513.167 |
| `DATA/ZS2EU_1.AFS` | 1.100.650.496 | partición 0; USA `ZS2US_1.AFS` 1.100.716.032 |
| `DATA/ZS2EU_2.AFS` | 1.784.217.600 | partición 1; USA `ZS2US_2.AFS` 1.610.694.656 |
| `DATA/ZS2EU.DIR` | 117 | lista `zs2eu_1.afs`, `zs2eu_2.afs`, `zs2euop.sfd`, `zs2eued.sfd`, `load_*.dbt` |
| `DATA/ZS2EU_1.ALG` | 26 | `zs2eu_1.afs 0 1100015616` |
| `DATA/ZS2EU_2.ALG` | 26 | `zs2eu_2.afs 0 1782554624` |
| `DATA/ZS2EUOP.SFD` | 96.421.888 | opening PAL |
| `DATA/ZS2EUED.SFD` | 141.383.680 | ending PAL |
| `DATA/LOAD_UK.DBT` | 25.760 | inglés |
| `DATA/LOAD_SP.DBT` | 25.760 | español |
| `DATA/LOAD_DU.DBT` | 25.760 | alemán (`Deutsch`) |
| `DATA/LOAD_FR.DBT` | 25.760 | francés |
| `DATA/LOAD_IT.DBT` | 25.760 | italiano |
| `LOGO_O.SFD` | — | **no existe en la EU** (la USA lo tiene, 2.869.248) |

Los `IRX/` son los mismos 18 módulos que la USA, con los mismos tamaños:

```
CDVDSTM.IRX 33521   CRI_ADXI.IRX 77677   DBCMAN.IRX 15653   DS2O_D.IRX 11797
DS2U_D.IRX 11725    IOPRP300.IMG 275345  LIBSD.IRX 28661    MCMAN.IRX 96181
MCSERV.IRX 7385     MODHSYN.IRX 63037    MODMIDI.IRX 21941  MODSEIN.IRX 9393
MODSESQ2.IRX 19069  MODSESQ.IRX 13717    SDRDRV.IRX 9161    SIO2D.IRX 11289
SIO2MAN.IRX 6641    SOUNDS.IRX 14657
```

### 1.3 Tabla comparativa EU vs USA

| Archivo | USA | EU | Delta |
|---|---:|---:|---:|
| ejecutable | `SLUS_214.41` 2.675.936 | `SLES_541.64` 2.681.824 | **+5.888** |
| overlay menú | `BIN/DBZP.BIN` 513.167 | `BIN/DBZP.BIN` 511.855 | **−1.312** |
| AFS partición 0 | `ZS2US_1.AFS` 1.100.716.032 | `ZS2EU_1.AFS` 1.100.650.496 | **−65.536** |
| AFS partición 1 | `ZS2US_2.AFS` 1.610.694.656 | `ZS2EU_2.AFS` 1.784.217.600 | **+173.522.944** |
| `.DIR` | 64 | 117 | +53 |
| opening | `ZS2USOP.SFD` 97.454.080 | `ZS2EUOP.SFD` 96.421.888 | −1.032.192 |
| ending | `ZS2USED.SFD` 161.533.952 | `ZS2EUED.SFD` 141.383.680 | −20.150.272 |
| logo | `LOGO_O.SFD` 2.869.248 | — | — |
| `LOAD_*.DBT` | — | 5 × 25.760 = 128.800 | +128.800 |

Cabeceras AFS (formato `AFS\0`, `u32 count`, `count` pares `{offset, size}`):

| AFS | count | primer offset | último fin | tamaño archivo |
|---|---:|---:|---:|---:|
| `ZS2US_1.AFS` | 13.234 | `0x1A000` | `0x4191DAB2` | 1.100.716.032 |
| `ZS2EU_1.AFS` | 13.197 | `0x1A000` | `0x4190E2E6` | 1.100.650.496 |
| `ZS2US_2.AFS` | 32.245 | `0x3F000` | `0x5FE99900` | 1.610.694.656 |
| `ZS2EU_2.AFS` | 34.607 | `0x44000` | `0x6A3F9900` | 1.784.217.600 |

---

## 2. El mecanismo: 5 bloques completos, con stride fijo

### 2.1 Historia: 5 bloques de 553 packs (stride `0x229`)

En la USA, los textos de historia son los packs `0x319..0x541` (553 entradas; 535 las usan los 760 GSC, el resto
son packs extra). En la EU **no se agregaron sub-bloques por idioma dentro del mismo pack**: se copió el bloque
completo 5 veces, uno detrás del otro.

| Idioma | Base EU | Rango | Total | Primera cadena | Última cadena |
|---|---:|---|---:|---|---|
| EN | `0x319` | `0x319..0x541` | 352.624 B | `Five peaceful years have...` | `Long ago...` |
| ES | `0x542` | `0x542..0x76A` | 350.624 B | `Han pasado cinco pacíficos años...` | `Hace mucho tiempo,` |
| DE | `0x76B` | `0x76B..0x993` | 359.696 B | `Fünf friedliche Jahre...` | `Vor langer Zeit ...` |
| FR | `0x994` | `0x994..0xBBC` | 340.784 B | `Cinq années de paix...` | `Il y a bien longtemps...` |
| IT | `0xBBD` | `0xBBD..0xDE5` | 349.200 B | `Sono trascorsi cinque anni...` | `Molto tempo fa...` |

Fórmula observada (con `lang`: EN=0, ES=1, DE=2, FR=3, IT=4):

```
id_eu = id_us + lang * 0x229
```

Verificaciones:

- **Las 553 entradas de cada bloque existen y no están vacías** (`sizes > 0`), incluso los huecos que la USA
  deja entre pack y pack. El mapeo es 1:1 por offset dentro del bloque.
- El formato es el mismo de la USA: `u32 count`, `u32 offsets[count]`, strings **UTF-16LE con BOM `FF FE`**,
  `\n` = `U+000A`, terminador `U+0000`. No están comprimidos.
- **Los GSC son byte-idénticos USA/EU**, sólo cambia el id de AFS donde viven (p. ej. el GSC de la USA `0xD22`
  es exactamente el mismo archivo que el de la EU `0x162F`; también `0xD33`/`0x1640`, `0xDA6`/`0x16B3`,
  `0xFB3`/`0x18C0`). Si los guiones son los mismos y piden ids fijos `0x319+k`, el offset de idioma **tiene que**
  aplicarse en código. Es exactamente lo que hace la EU.

El bloque EN de la EU **no es idéntico al de la USA**: 517 de 553 packs son byte-idénticos, 36 cambian (10 de
ellos también de tamaño). Son retoques de la versión UK, no sólo acentos; por ejemplo:

- USA `0x373`: `...Kami and Mr. Popo used the Dragon Balls...`
- EU `0x373`: `...King Kai used the Dragon Balls...`
- USA `0x363`: termina una frase con `...`; EU usa `…` (puntuación distinta).

Consecuencia práctica: si el port usa la USA para el inglés, el texto EN es el de USA; si copia el bloque EN de
la EU, obtiene el guion UK. Para ES/DE/FR/IT no hay ambigüedad: son bloques nuevos.

### 2.2 Menús: 5 bloques de 23 entradas (stride `0x17`)

La USA tiene un único bloque de recursos de menú en `0x544..0x55A` (23 entradas; base de menú `0x544`, que el
juego guarda en `D_003876A4+4`). La EU lo copió 5 veces, con base:

| Idioma | Base EU | Rango | Total | Última entrada = `LOAD_*.DBT` |
|---|---:|---|---:|---|
| EN | `0xDE9` | `0xDE9..0xDFF` | 40.768.624 B | `LOAD_UK.DBT` (25.760 B) |
| ES | `0xE00` | `0xE00..0xE16` | 40.864.832 B | `LOAD_SP.DBT` |
| DE | `0xE17` | `0xE17..0xE2D` | 40.817.104 B | `LOAD_DU.DBT` |
| FR | `0xE2E` | `0xE2E..0xE44` | 40.808.272 B | `LOAD_FR.DBT` |
| IT | `0xE45` | `0xE45..0xE5B` | 40.894.768 B | `LOAD_IT.DBT` |

Fórmula observada (partiendo del id USA):

```
id_eu = id_us + 0x8A5 + lang * 0x17
```

(porque `0xDE9 - 0x544 = 0x8A5`). O directamente `id_eu = 0xDE9 + lang*0x17 + (id_us - 0x544)`.

Verificaciones:

- La entrada `0xDE9` (primer recurso del bloque EN) es **byte-idéntica** a la `0x544` de la USA.
- La entrada `0xDF0` (posición 7 del bloque) es **byte-idéntica** a la `0x54B` de la USA.
- La **última entrada de cada bloque es byte-idéntica al `LOAD_XX.DBT` del ISO** (comprobado con SHA-1):
  `0xDFF` = `LOAD_UK.DBT`, `0xE16` = `LOAD_SP.DBT`, `0xE2D` = `LOAD_DU.DBT`, `0xE44` = `LOAD_FR.DBT`,
  `0xE5B` = `LOAD_IT.DBT`. Eso confirma que el bloque es el "pack de menú + pantalla de carga" de cada idioma.
- De las 23 entradas, **21 cambian entre idiomas**; sólo `0x544` (5.824 B) y `0x54B` (67.008 B) son iguales en
  los 5 bloques. Las demás (1,7–7,7 MB cada una) son específicas de cada idioma.

El orden de idiomas de la EU es **EN, ES, DE, FR, IT** (coincide con `LOAD_UK`, `LOAD_SP`, `LOAD_DU`, `LOAD_FR`,
`LOAD_IT`). Es el orden que hay que usar para `lang = 0..4` si se implementa la fórmula.

### 2.3 El diálogo de memory card: `0x550` de la USA → `base+0xC` de cada bloque EU

La entrada `0x550` de la USA (diálogo de guardado/carga) está en la posición 12 del bloque de menú
(`0x550 - 0x544 = 0xC`). En la EU:

| Idioma | Entry EU | Tamaño contenedor | Tabla en el sub-bloque descomprimido |
|---|---:|---:|---:|
| EN | `0xDF5` | 2.273.088 | `P + 0xFCC80` |
| ES | `0xE0C` | 2.270.144 | `P + 0xFCB00` |
| DE | `0xE23` | 2.269.120 | `P + 0xFC140` |
| FR | `0xE3A` | 2.252.672 | `P + 0xFCD00` |
| IT | `0xE51` | 2.256.704 | `P + 0xFCBC0` |

El contenedor tiene **el mismo formato que la USA**: `u32 count = 4`, `u32 header = 0x40`, 4 offsets de fin, y el
sub-bloque 0 (comprimido con `func_002B24C8`) se descomprime a ~1,2 MB. La tabla de mensajes está dentro del
sub-bloque 0, apuntada por el campo `P+0x40` (el mismo que usa `func_003E3D38` en el port). En los 5 idiomas:

- `count = 49`
- `word[1] = 0x100` (primer string)
- strings UTF-16LE con BOM `FF FE`, `\n` = `U+000A`, terminador `U+0000`
- `MSG = n` sigue usando `word[n+1]` (misma convención que la USA)

**Muestras exactas de la tabla (49 entradas) por idioma:**

| | EN `0xDF5` | ES `0xE0C` | DE `0xE23` | FR `0xE3A` | IT `0xE51` |
|---|---|---|---|---|---|
| `word[1]` | `MEMORY CARD slot 1` | `Ranura para MEMORY CARD 1` | `MEMORY CARD-Steckplatz 1` | `Fente pour MEMORY CARD N°1` | `Ingresso MEMORY CARD 1` |
| `word[6]` | `No memory card (PS2) inserted.` | `No hay memory card (PS2) insertada.` | `Keine Memory Card (PS2) eingelegt.` | `Pas de memory card (PS2) insérée.` | `Nessuna memory card (PS2) inserita.` |
| `word[29]` | `Save game data?` | `¿Guardar datos?` | `Spieldaten speichern?` | `Sauvegarder les\ndonnées de jeu ?` | `Salvare i dati\ndi gioco?` |
| `word[30]` | `Saving data. ...` | `Guardando datos. ...` | `Speichert Daten. ...` | `Sauvegarde en cours. ...` | `Salvataggio dei dati in corso...` |

Las tablas completas (49 líneas por idioma) se volcaron a `/tmp/opencode/eu/tablas/mc_{EN,ES,DE,FR,IT}.txt`;
se regeneran con el script de §5.3.

**Sub-bloques del contenedor EN vs USA** (todos los 4 cambian, no sólo el texto):

| Sub-bloque | EU EN `0xDF5` (dest / packed) | USA `0x550` (dest / packed) |
|---:|---:|---:|
| 0 | `0x12B400` / `0x8AF36` | `0x12B340` / `0x8ACB3` |
| 1 | `0xB4C00` / `0x66CDB` | `0xB4C00` / `0x670FD` |
| 2 | `0x18CBC0` / `0xC2E0C` | `0x18CBC0` / `0xC2868` |
| 3 | `0x11D380` / `0x76475` | `0x11D380` / `0x7645C` |

Offsets de fin del contenedor EN: `0x8AF80`, `0xF1C80`, `0x1B4AC0`, `0x22AF40`. Los del USA: `0x8AD00`,
`0xF1E40`, `0x1B46C0`, `0x22AB40`. La cabecera es igual (`count=4`, `header=0x40`), pero **el contenido de los 4
sub-bloques es distinto**; reemplazar sólo el sub-bloque de texto no reproduce el menú EU.

En el contenedor EN, los 4 sub-bloques contienen textos de ayuda UTF-16; los primeros 6 strings de cada uno son
el mismo prefijo:

```
You can set the various game settings. Choose wisely!
You can save and load game data. Save often!
You can change the controller's button settings...
During the game you can change the camera settings.
Change the volume, or change the sound settings to mono or stereo.
The changed settings will be saved and you can return to the main menu.
```

Después de ese prefijo el contenido diverge; no son texturas puras. En ES/DE/FR/IT los 4 sub-bloques también
cambian respecto del EN (hashes distintos) y la tabla de mensajes de sub0 está traducida; no verifiqué string por
string los sub-bloques 1–3 de cada idioma.

### 2.4 Font y mensajes de sistema: `0xDE6`

- La EU tiene el font/sistema en `0xDE6` (110.144 B), no en `0x542` como la USA (105.792 B).
- El contenedor EU tiene `count = 0x19` (25 sub-bloques) y el `Fnt4` en `+0x80`; el USA tiene `count = 0x0D`
  y el `Fnt4` en `+0x40`. **No es drop-in para el loader de font USA**: `Font_Init`/`func_00102180` esperan el
  layout USA. Si se cambia el menú a EU, conviene **seguir usando el font USA `0x542`** (ya tiene acentos,
  ñ/Ñ, umlauts y `¿¡`, ver F5).
- `0xDE6` contiene los mensajes de sistema ("No analog controller (DUALSHOCK®2)...") en EN (2 variantes),
  ES (2), DE, FR e IT. Es útil sólo si el port quiere localizar esos carteles de hardware; no hace falta para
  los textos del juego.
- `0xDE7` es byte-idéntico a la `0x543` de la USA; `0xDE9` es byte-idéntico a la `0x544`. `0xDE8` (235.056 B)
  es un blob extra de la EU sin equivalente USA en esa posición; no lo usa el flujo de menú que analizamos.

### 2.5 `ZS2EU_2.AFS`: 893 ADX extra + 10 archivos de texto de misión

Comparando por contenido (SHA-1 de cada entrada, no por índice):

- `ZS2US_2.AFS`: 32.245 entradas, 1.610.694.656 B.
- `ZS2EU_2.AFS`: 34.607 entradas, 1.784.217.600 B (**+2.362 entradas, +173,5 MB / 165,5 MiB**).
- **33.704 entradas EU (1.497 MiB, ≈1,5 GiB) son byte-idénticas a alguna entrada USA**; están
  reordenadas/duplicadas.
- **903 entradas EU no existen en la USA** (162,4 MiB):
  - **893 ADX** (magic `80 00 00 24`, `(c)CRI`): 162,38 MiB. Son audio PAL extra (no los decodifiqué; no son
    texto).
  - **10 archivos de texto** (magic `78 00 00 00`, count 120): 3,83 MiB. Son las **condiciones de misión**
    ("Clear Conditions" / "Bedingungen" / "Objectifs" / "Obiettivi" / "Condiciones") en 5 idiomas, en
    `0x94A..0x953`.

Mapeo de esos 10 (USA `0x18`/`0x19` → EU2):

| Idioma | Entry EU2 (fichero 1 / 2) | Tamaños | Muestra |
|---|---|---|---|
| EN | `0x94C` / `0x94D` | 656.320 / 146.752 | `Clear Conditions`, `Win the Battle!` |
| ES | `0x952` / `0x953` | 656.384 / 146.816 | `Condiciones`, `¡Gana la batalla!` |
| DE | `0x94A` / `0x94B` | 656.384 / 146.816 | `Bedingungen`, `Gewinne!` |
| FR | `0x950` / `0x951` | 656.320 / 146.752 | `Objectifs`, `Gagner !` |
| IT | `0x94E` / `0x94F` | 656.384 / 146.816 | `Obiettivi`, `Vinci!` |

El orden de estos 10 **no** sigue el orden de los bloques de AFS1 (es DE, EN, IT, FR, ES); hay que mapearlos
explícitamente, no con una fórmula de `lang*0x17`.

**No copiar `ZS2EU_2.AFS` entero**: está reordenado respecto de la USA y el port pide ids USA; reemplazar la
partición 1 rompería modelos/audio. Sólo tiene sentido extraer los 10 archivos de texto y remapear `0x18`/`0x19`
en el caller correspondiente (no identifiqué ese caller en este trabajo; ver §7).

---

## 3. Texturas de menú: AFS, no `BIN/DBZP.BIN`

Evidencia:

- `BIN/DBZP.BIN` de la EU mide **511.855 B** (USA 513.167 B): es el **overlay MIPS del menú**, código. Su primera
  instrucción es `addiu sp,sp,-0x40` (`c0 ff bd 27`), y sus strings son nombres de recursos/animaciones
  (`mc_menutext_onanime`, `mc_memory_name_%d`, `fr_memory_select`, etc.). No es un archivo de texturas.
- El bloque de menú de la EU pesa **~38,9 MB por idioma** (194,7 MB los 5). La entrada `0x551` (posición 13,
  746.576 B) descomprime a un archivo de **47 recursos** cuyo primer sub-recurso empieza con el magic **`FOD\x10`**;
  el port ya sabe que los FOD son "movie/animation + textures" (`src/sys/gfxm_c_26FBF8.c`: *"Sets a movie up on
  a FOD file and its textures"*). Las entradas `0x552`, `0x554`, `0x555` son del mismo tipo.
- El código de menú del port carga justamente `base+0xD`, `base+0xE`, `base+0x10`, `base+0x11`
  (`port/eq/243E38.c:101`, `255C98.c:28`, `256F10.c:51`, etc.), es decir `0x551`, `0x552`, `0x554`, `0x555` de
  la USA. En la EU esos mismos offsets caen en `0xDF6`, `0xDF7`, `0xDF9`, `0xDFA` del bloque del idioma.
- **21 de las 23 entradas del bloque cambian entre idiomas**. Los rótulos/animaciones de menú no están sólo en
  la tabla UTF-16: también hay FOD/texturas con texto horneado. Por eso, para tener el menú localizado completo,
  hay que copiar **el bloque entero de 23 entradas**, no sólo el sub-bloque de texto del `0x550`.

Si el objetivo fuera **sólo** el diálogo de memory card, alcanzaría con el contenedor `0x550` de cada idioma
(~2,25 MB cada uno). Pero para "textos y texturas de menú" hace falta el bloque completo.

---

## 4. Qué tendría que copiar el setup

### 4.1 Opción recomendada (simple y consistente con F9): el AFS EU1 entero

Copiar de la ISO EU:

```
DATA/ZS2EU_1.AFS       1.100.650.496 B
```

y dejarlo como una **partición extra de solo lectura** (p. ej. partición 2 del port, o un `Part` aparte en
`plat_file.c`). No se toca ni se renombra `ZS2US_1.AFS`; la USA sigue siendo la base.

Ventajas:

- No hay que repackear nada: el formato AFS se lee tal cual y el port ya tiene el loader (`func_002EA588`,
  `func_002EB9B0`, `func_002EC0C8`).
- Se conservan los 5 idiomas completos, con texturas, FOD, tablas y pantallas de carga exactamente como en la EU.
- El costo es 1,1 GB extra (el `gamedata` USA actual es ~3 GB).

Cómo se usa en runtime:

- `lang` = 0 EN, 1 ES, 2 DE, 3 FR, 4 IT.
- Para un pedido USA `id` en `0x319..0x541` (historia), leer de EU con `id + lang*0x229`.
- Para un pedido USA `id` en `0x544..0x55A` (menú), leer de EU con `id + 0x8A5 + lang*0x17`.
- Todo lo demás sigue saliendo de la USA sin cambios.

### 4.2 Opción compacta: sólo los bloques localizados (~196,5 MB los 5 idiomas)

Si el setup quiere minimizar disco, extraer **entradas completas** (no sub-bloques) del `ZS2EU_1.AFS`:

| Qué | Entradas | Tamaño |
|---|---|---:|
| Historia EN | `0x319..0x541` (553) | 352.624 B |
| Historia ES | `0x542..0x76A` (553) | 350.624 B |
| Historia DE | `0x76B..0x993` (553) | 359.696 B |
| Historia FR | `0x994..0xBBC` (553) | 340.784 B |
| Historia IT | `0xBBD..0xDE5` (553) | 349.200 B |
| Menú EN | `0xDE9..0xDFF` (23) | 40.768.624 B |
| Menú ES | `0xE00..0xE16` (23) | 40.864.832 B |
| Menú DE | `0xE17..0xE2D` (23) | 40.817.104 B |
| Menú FR | `0xE2E..0xE44` (23) | 40.808.272 B |
| Menú IT | `0xE45..0xE5B` (23) | 40.894.768 B |
| Font/sistema (opcional) | `0xDE6` | 110.144 B |
| **Total 5 idiomas** | | **~196,4 MB sin font / ~196,5 MB con font** |
| **Total 4 idiomas (sin EN)** | | **~157,2 MB sin font / ~157,3 MB con font** |
| Condiciones de misión (EU2, opcional) | `0x94A..0x953` (10) | 4.015.744 B |
| **Total 4 idiomas + misión** | | **~161,1 MB** |

Se puede guardar de dos formas:

1. **AFS recortado** con el mismo id space que la EU: `count = 13.197`, tabla de 13.197 pares; las entradas
   copiadas con su offset/tamaño, las demás con `size = 0` (offset cualquiera, p. ej. 0). Alinear cada entrada a
   sector de 2048 B. El port lo abre como partición extra y remapea igual que en 4.1. Tamaño final ~197 MB.
2. **Archivos por id** (`gamedata/EU/<id>.bin`), y que `plat_file.c` busque ahí antes de la USA. Más simple de
   debuggear, pero son ~2.300 archivos (553×4 + 23×5 + 10). El comentario de `plat_file.c` ya menciona
   `gamedata/mods/<particion>/<indice>.bin`, pero **la implementación no existe** (F5 ya lo había notado); habría
   que agregarla.

En ambos casos, el setup **no necesita descomprimir** nada: copia el payload crudo y el juego lo descomprime con
`func_002B24C8` como hasta ahora.

### 4.3 Qué NO copiar

- **`ZS2EU_2.AFS` entero**: reordenado; rompería los ids USA. Sólo los 10 archivos de §2.5 si se quieren las
  condiciones de misión.
- **`SLES_541.64` / `BIN/DBZP.BIN` de la EU**: son el ejecutable/overlay PAL; el port usa el código USA
  decompilado. No hacen falta para los textos ni para las texturas.
- **`ZS2EUOP.SFD` / `ZS2EUED.SFD`**: videos PAL; sólo si se quiere reemplazar el opening/ending.
- **`IRX/`**: idénticos a la USA.

### 4.4 Enganche en el port (boceto, NO aplicado)

En `port/full/plat_file.c`, agregar un `Part sEU` para `gamedata/DATA/ZS2EU_1.AFS` y un setting de idioma.
En `func_002EB9B0(ptid, flid)`:

```c
/* lang: 0=EN, 1=ES, 2=DE, 3=FR, 4=IT  (orden de la EU) */
static int eu_id(int id, int lang) {
    if (lang == 0) return -1;                       /* EN: seguir usando la USA */
    if (id >= 0x319 && id <= 0x541) return id + lang * 0x229;
    if (id >= 0x544 && id <= 0x55A) return id + 0x8A5 + lang * 0x17;
    return -1;
}
/* en func_002EB9B0: si ptid==0 y eu_id() >= 0, usar sEU con el id mapeado */
```

Notas:

- No hace falta cambiar `port/eq/1021E8.c:25` (`D_003876A4+4 = 0x544`): el remapeo en ADXF cubre el bloque de
  menú. La alternativa es poner ahí `0xDE9 + lang*0x17`, pero entonces hay que remapear sólo la historia y
  acordarse de que el font sigue en `0x542`.
- **Font**: dejar `func_00102180` con `0x542` (USA). No cargar `0xDE6` con el loader USA: el `Fnt4` está en
  `+0x80` en vez de `+0x40`.
- **F5**: el override de textos de memory card (`port/full/plat_text.c`) **recibe el puntero a la tabla ya
  resuelto** (`*(u8 **)(G + 0x10)`, que el juego calcula como `P + (word[P+0x40] & ~3)`), no un `P` fijo. Por eso
  funciona igual con las 5 tablas EU: las cinco cumplen `count==49 && word[1]==0x100` y los offsets internos son
  relativos a la propia tabla. No hay que cambiar el hook por el offset variable (`0xFCB00`, `0xFC140`,
  `0xFCD00`, `0xFCBC0`); sólo tener en cuenta que el `(PS2)` se filtra sobre la tabla EU si se activa
  `texto_ps2=0`.
- **Inglés**: si se copia el bloque EN de la EU, usar `lang=0` con las bases EU (`0x319`, `0xDE9`); si no, dejar
  `lang=0` sin remapeo y seguir con la USA. No mezclar: el EN de la EU es UK y tiene 36 packs distintos.

---

## 5. Comandos reproducibles

> En esta máquina no hay `7z`; se usó `unzip` y `bsdtar`. En el setup se puede usar `7z` equivalente:
> `7z l`, `7z x -o...`, etc.

### 5.1 Listar y extraer el zip / ISO

```sh
mkdir -p /tmp/opencode/eu && cd /tmp/opencode/eu

# listar el zip (Python, sin 7z)
python3 - <<'PY'
import zipfile
z = zipfile.ZipFile("/home/rexx/Descargas/Dragon Ball Z - Budokai Tenkaichi 2 (Europe Australia) (EnFrDeEsIt).zip")
for i in z.infolist(): print(i.file_size, i.filename)
PY

# extraer el ISO (unzip soporta el tamaño)
unzip -o "/home/rexx/Descargas/Dragon Ball Z - Budokai Tenkaichi 2 (Europe Australia) (EnFrDeEsIt).zip"

# listar el ISO
bsdtar -tvf "Dragon Ball Z - Budokai Tenkaichi 2 (Europe, Australia) (En,Fr,De,Es,It).iso"

# extraer los archivos que interesan
mkdir -p extract
bsdtar -xf "Dragon Ball Z - Budokai Tenkaichi 2 (Europe, Australia) (En,Fr,De,Es,It).iso" -C extract \
  SYSTEM.CNF SLES_541.64 BIN DATA/LOAD_DU.DBT DATA/LOAD_FR.DBT DATA/LOAD_IT.DBT DATA/LOAD_SP.DBT \
  DATA/LOAD_UK.DBT DATA/ZS2EU.DIR DATA/ZS2EU_1.ALG DATA/ZS2EU_2.ALG \
  DATA/ZS2EU_1.AFS DATA/ZS2EU_2.AFS
```

### 5.2 Leer la tabla AFS

```python
import struct

def afs_tab(path):
    f = open(path, "rb")
    assert f.read(4) == b"AFS\0"
    n = struct.unpack("<I", f.read(4))[0]
    tab = [struct.unpack("<II", f.read(8)) for _ in range(n)]
    return f, tab

f, tab = afs_tab("/tmp/opencode/eu/extract/DATA/ZS2EU_1.AFS")
o, s = tab[0xDF5]                      # contenedor del diálogo EN
f.seek(o); raw = f.read(s)
open("/tmp/opencode/eu/pack550_en.bin", "wb").write(raw)
print(hex(o), hex(s), len(tab))
```

### 5.3 Descomprimir el sub-bloque 0 y leer la tabla de 49 mensajes

El descompresor es el mismo `func_002B24C8` que ya usa el port; el script de F5 quedó en
`/tmp/opencode/f3_lz.py`. Para el setup no hace falta: alcanza con copiar el contenedor crudo.

```python
import struct, sys
sys.path.insert(0, "/tmp/opencode")
import f3_lz

# raw = contenedor 0xDF5 (count=4, header=0x40)
cnt = struct.unpack("<I", raw[:4])[0]
end0 = struct.unpack("<I", raw[8:12])[0]          # fin del sub-bloque 0
P = f3_lz.decomp(raw[0x40:end0])[2]               # sub-bloque 0 descomprimido (0x12B400)

toff = struct.unpack("<I", P[0x40:0x44])[0] & ~3  # en EN: 0xFCC80
base = P[toff:]
n = struct.unpack("<I", base[:4])[0]              # 49
offs = [struct.unpack("<I", base[4+4*k:8+4*k])[0] for k in range(n)]
for k in range(1, n+1):
    p = toff + (offs[k-1] & ~3)
    q = p
    while P[q:q+2] != b"\x00\x00": q += 2
    print(k, P[p:q].decode("utf-16le", "replace"))
```

### 5.4 Verificar los `LOAD_*.DBT`

```python
import hashlib
for lang, entry in [("UK", 0xDFF), ("SP", 0xE16), ("DU", 0xE2D), ("FR", 0xE44), ("IT", 0xE5B)]:
    o, s = tab[entry]
    f.seek(o); a = hashlib.sha1(f.read(s)).hexdigest()
    b = hashlib.sha1(open(f"extract/DATA/LOAD_{lang}.DBT", "rb").read()).hexdigest()
    print(lang, a == b, a)
```

---

## 6. Verificado, inferido y pendiente

### Verificado con datos

- Tamaños y nombres del zip/ISO; tabla comparativa EU vs USA.
- Cabeceras AFS: counts 13.197/34.607, primeros offsets y últimos fines.
- Los 5 bloques de historia: bases, 553 entradas no vacías cada uno, formato `u32 count + offsets + UTF-16LE`,
  primeras/últimas cadenas de cada idioma.
- Los 5 bloques de menú: bases, 23 entradas, `0xDE9` == `0x544` USA y `0xDF0` == `0x54B` USA; la última entrada
  de cada bloque == `LOAD_XX.DBT` (SHA-1).
- Las 5 tablas del diálogo de memory card: `count=49`, `word[1]=0x100`, offsets de tabla por idioma y muestras
  de texto en los 5 idiomas.
- Los 4 sub-bloques del `0x550` EU vs USA y sus tamaños descomprimidos/comprimidos.
- Los GSC son byte-idénticos USA/EU (4 pares comprobados).
- EU2: 33.704 entradas byte-idénticas a USA, 893 ADX nuevos + 10 textos de misión (3,83 MB).

### Inferido (consistente, pero no visto en ejecución)

- La fórmula `id_eu = id_us + lang*0x229` para historia y `+0x8A5 + lang*0x17` para menú. La geometría de los
  bloques y los GSC idénticos la hacen la única explicación razonable, pero **no disassemblé la instrucción
  exacta del SLES** que aplica el offset.
- Que los contenedores de menú EU (FOD/texturas) son compatibles con el código de menú USA. La cabecera
  `count=4/header=0x40` y la entrada `0xDE9` idéntica a `0x544` lo sugieren fuerte, pero no se probó en el port.
- Que las texturas de menú están dentro de los FOD del bloque (`FOD\x10`) y no en otro lado. El port ya trata los
  FOD como "movie + textures" y el bloque pesa 38,9 MB por idioma; no rendericé las texturas.

### Pendiente / no hecho

- No se compiló ni ejecutó el port con datos EU: no hay prueba en pantalla.
- No se identificó el caller exacto de `ZS2EU_2.AFS` `0x18/0x19` en el port para las condiciones de misión.
- No se decodificaron los 893 ADX extra de EU2 (no son texto).
- No se encontró en el SLES la instrucción que multiplica por `0x229`/`0x17` (sí se desensambló `.text`, pero
  el patrón no apareció limpio; el próximo paso es buscar la función que arma el id de texto, probablemente cerca
  del handler `0xFA4`/`func_002A70F8`).
- F5 (`plat_text.c`) no se probó en ejecución con tablas EU; por código debería funcionar sin cambios (recibe el
  puntero a la tabla, §4.4), pero falta la prueba en pantalla.

---

## 7. Referencias rápidas

| Qué | Dónde |
|---|---|
| Bloques de historia EU | `ZS2EU_1.AFS` `0x319 + lang*0x229`, 553 entradas |
| Bloques de menú EU | `ZS2EU_1.AFS` `0xDE9 + lang*0x17`, 23 entradas |
| Diálogo memory card EU | `base_menu + 0xC`: `0xDF5/0xE0C/0xE23/0xE3A/0xE51` |
| Tabla de 49 mensajes | sub-bloque 0, `P + (word[P+0x40] & ~3)` |
| Font USA que hay que conservar | `ZS2US_1.AFS` `0x542` (`Fnt4` en `+0x40`) |
| Font/sistema EU (no drop-in) | `ZS2EU_1.AFS` `0xDE6` (`Fnt4` en `+0x80`) |
| Overlay de menú (código) | `BIN/DBZP.BIN` 511.855 B EU / 513.167 B USA |
| Condiciones de misión EU2 | `0x94A..0x953` (DE,EN,IT,FR,ES), 10 archivos |
| Carga AFS del port | `port/full/plat_file.c` `func_002EA588` / `func_002EB9B0` / `func_002EC0C8` |
| Fuente de texto del juego | `port/eq/2A3A98.c` → `func_00100ED0` → `func_00100D58` |
| Base de menú USA | `port/eq/1021E8.c:25` (`0x544`) |
| F5 textos memory card | `port/full/plat_text.c`, `staging/F5_textos_memorycard.md` |
