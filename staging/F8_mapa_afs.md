# F8 — Mapa completo de ids AFS USA ↔ EU (BT2)

Fecha: 2026-11-11. Análisis **offline**: no se compiló, no se ejecutó el port y no se tocó el juego. Script reproducible: `/tmp/opencode/mapa_afs.py`. Este archivo y el JSON se generan con ese script.

## 0. Resumen en cinco bullets

- **La EU1 tiene 3 bloques localizados**, no 2: historia (553 packs, stride `0x229`), menú (23 entradas, stride `0x17`) y **objetos/Z-items/habilidades** (3 entradas, stride `3`, USA `0x767..0x769` → EU `0x1068..0x1076`). Este último es el que faltaba para los textos de objetos en pelea/pausa.

- **Los textos de pelea/pausa/HUD están en la partición 1 (AFS2)**, no en la AFS1: USA2 `0x18`/`0x19` son dos tablas de texto (condiciones de misión + rótulos de pausa: `1P PAUSE`, `Continue Battle`, `Look at Z Items`, `EXIT?`). La EU2 las reemplaza por **10 archivos**, 5 idiomas × 2, en `0x94A..0x953` (orden DE, EN, IT, FR, ES).

- **Todo lo demás de la AFS2 es 1:1**: USA2 `0x1A..0x7DF4` → EU2 `+0x93A`; USA2 `0x0..0x17` → EU2 `+0x932`. La EU2 solo agrega 893 ADX (audio PAL) + 10 archivos de texto al principio.

- **La AFS1 USA tiene una cola de audio que no está en la EU1**: `0x2A80..0x33B1` (2.354 entradas, 166.544.660 B, ADX). No es texto; el port sigue usando el audio USA. La EU1 compensa ese espacio con los bloques localizados (menú, sobre todo): su archivo total es apenas 65.536 B menor que el USA.

- **Riesgo**: el mapa está verificado por contenido/geometría, no en pantalla. El orden de idioma del port (`0=EN,1=ES,2=FR,3=DE,4=IT`) **no** es el del AFS (EN,ES,DE,FR,IT) ni el de la AFS2 (DE,EN,IT,FR,ES): usar los códigos de idioma del JSON, no los índices.


## 1. Método

1. Se leen las tablas AFS y se hashea **el contenido completo** de cada entrada (SHA-1 + tamaño). El hash incluye el tamaño, así que una entrada comprimida también se empareja por bytes.

2. Se buscan anclas de contenido idéntico y único en ambas particiones; con una LIS se obtiene la secuencia ordenada. Los tramos con `id_eu - id_usa` constante son el „esqueleto“ del AFS.

3. Entre dos tramos consecutivos queda un hueco. Cada hueco se explica como uno o más **bloques de 5 copias**: `5n` entradas EU contra `n` entradas USA. Se prueban de atrás hacia adelante (menú/items/textos de pelea) y de adelante hacia atrás (historia, cuya copia EN queda antes del hueco).

4. Un bloque se acepta si las 5 copias comparten estructura (primer u32 = count/magic, o tamaños dentro de 4×) y, cuando hay contenido sin traducir, la copia 0 se alinea parcialmente 1:1 con la USA. Eso descarta las regiones 1:1 (GSC, ADX) que también tienen tipos uniformes.

5. El idioma de cada copia se verificó con textos de muestra (primer string de historia, `LOAD_*.DBT` del menú, `Health +1`/`Salud +1`/… de items, `Clear Conditions`/`Condiciones`/… de la AFS2).


## 2. Bloques detectados

### 2.1 Partición 0 — `ZS2US_1.AFS` ↔ `ZS2EU_1.AFS`

| Bloque | USA base | count | EU base | stride | Copias (EN, ES, DE, FR, IT) | Bytes EU | Idénticas a USA |
|---|---:|---:|---:|---:|---|---:|---:|
| Historia | `0x319` | 553 | `0x319` | `0x229` | `0x319` / `0x542` / `0x76b` / `0x994` / `0xbbd` | 1.752.928 | EN 517, ES 16, DE 16, FR 16, IT 16 (de 553) |
| Menú | `0x544` | 23 | `0xde9` | `0x17` | `0xde9` / `0xe00` / `0xe17` / `0xe2e` / `0xe45` | 204.153.600 | EN 3, ES 2, DE 2, FR 2, IT 2 (de 23) |
| Objetos/Z-items | `0x767` | 3 | `0x1068` | `0x3` | `0x1068` / `0x106b` / `0x106e` / `0x1071` / `0x1074` | 2.450.176 | EN 0, ES 0, DE 0, FR 0, IT 0 (de 3) |

Fórmula general: `eu_id = eu_base + lang_index*stride + (usa_id - usa_base)`, con `lang_index` = posición del idioma en la lista `langs` del JSON (para la AFS1: EN=0, ES=1, DE=2, FR=3, IT=4).

**Historia** — 553 packs UTF-16 por idioma; la copia EN es la versión UK (36 packs difieren de la USA).

| Idioma | Base EU | Primer texto / muestra |
|---|---:|---|
| EN | `0x319` | Five peaceful years have \npassed since the epic \nbattle against Piccolo... But n |
| ES | `0x542` | Han pasado cinco \npacíficos años desde la \nbatalla contra Piccolo... Pero ahora, |
| DE | `0x76b` | Fünf friedliche Jahre \nsind seit der epischen\nSchlacht mit Piccolo\nvergangen ... |
| FR | `0x994` | Cinq années de paix se\nsont écoulées depuis le\ncombat épique contre\nPiccolo... M |
| IT | `0xbbd` | Sono trascorsi cinque\nanni di pace dall'epica\nbattaglia contro\nPiccolo... Ma ora |

**Menú** — 23 recursos de menú (FOD/texturas + tablas); la última entrada es LOAD_*.DBT. Memory card = posición 0xC.

| Idioma | Base EU | Primer texto / muestra |
|---|---:|---|
| EN | `0xde9` | mem card + LOAD_UK.DBT |
| ES | `0xe00` | mem card + LOAD_SP.DBT |
| DE | `0xe17` | mem card + LOAD_DU.DBT |
| FR | `0xe2e` | mem card + LOAD_FR.DBT |
| IT | `0xe45` | mem card + LOAD_IT.DBT |

**Objetos/Z-items** — 3 contenedores comprimidos: nombres y descripciones de objetos/Z-items. No estaba remapeado.

| Idioma | Base EU | Primer texto / muestra |
|---|---:|---|
| EN | `0x1068` | Health +1 Health +2 Health +3 Health +4 Health +5 Health +6 Health +7 Health +8  |
| ES | `0x106b` | Salud +1 Salud +2 Salud +3 Salud +4 Salud +5 Salud +6 Salud +7 Salud +8 Salud +9 |
| DE | `0x106e` | Gesundheit +1 Gesundheit +2 Gesundheit +3 Gesundheit +4 Gesundheit +5 Gesundheit |
| FR | `0x1071` | Santé +1 Santé +2 Santé +3 Santé +4 Santé +5 Santé +6 Santé +7 Santé +8 Santé +9 |
| IT | `0x1074` | Salute +1 Salute +2 Salute +3 Salute +4 Salute +5 Salute +6 Salute +7 Salute +8  |

**Font/sistema (mapeo especial, no es un bloque de 5 copias)**

| USA | EU | Bytes USA / EU | Qué es |
|---|---:|---:|---|
| `0x542` | `0xDE6` | 105.792 / 110.144 | font `Fnt4`; en USA está en `+0x40` y en EU en `+0x80`: **no es drop-in** |
| `0x543` | `0xDE7` | 92.864 / 92.864 | byte-idéntico |
| — | `0xDE8` | — / 235.056 | blob EU sin equivalente USA |

Puntos finos de la partición 0:

- **Historia**: la copia EN de la EU (`0x319`) es la versión UK: 517/553 packs son byte-idénticos a la USA, 36 cambian (10 de tamaño). Si el port usa la USA para inglés, no hace falta el bloque EN; para ES/DE/FR/IT sí. La fórmula con `lang=0` apunta a la copia EN de la EU, no a la USA.

- **Menú**: 21 de las 23 entradas cambian entre idiomas; solo `0x544` (5.824 B) y `0x54B` (67.008 B) son iguales en los 5 bloques. El diálogo de memory card es la posición `0xC` (`USA 0x550` → `0xDF5/0xE0C/0xE23/0xE3A/0xE51`). La última entrada de cada bloque es `LOAD_UK/SP/DU/FR/IT.DBT`.

- **Objetos/Z-items**: bloque nuevo respecto del informe anterior. Son 3 contenedores comprimidos por idioma; el tercero (`USA 0x769`) descomprime a una tabla `count=11, header=0x40` con `Health +1…`, `Salud +1…`, `Gesundheit +1…`, `Santé +1…`, `Salute +1…`. Los otros dos tienen `count=18, header=0x80` y textos de descripción. **Hoy el port no remapea `0x767..0x769`**, por eso quedan en inglés los nombres/descripciones de objetos en pelea y pausa.

- **Font/sistema**: no es un bloque de 5 copias. USA `0x542` (105.792 B, `Fnt4` en `+0x40`) ≠ EU `0xDE6` (110.144 B, `Fnt4` en `+0x80`); **no es drop-in**, conviene seguir usando el font USA. USA `0x543` == EU `0xDE7` (92.864 B, byte-idéntico). EU `0xDE8` (235.056 B) no tiene equivalente USA.


### 2.2 Partición 1 — `ZS2US_2.AFS` ↔ `ZS2EU_2.AFS`

| Bloque | USA base | count | EU base | stride | Copias (DE, EN, IT, FR, ES) | Bytes EU |
|---|---:|---:|---:|---:|---|---:|
| Pelea/pausa/HUD | `0x18` | 2 | `0x94a` | `0x2` | `0x94a` / `0x94c` / `0x94e` / `0x950` / `0x952` | 4.015.744 |

Este es **el bloque que faltaba para pelea/pausa/HUD**. Contiene, entre otros:

```
Clear Conditions / Win the Battle! / Survive as long as you can!
1P PAUSE / 2P PAUSE / EXIT? / Yes / No
Continue Battle / Continue Game / Fight Again / Look at Skill List / Look at Status
Look at basic control list / Look at Z Items / Return to Character Select / Return to Main Menu
```

Los 10 archivos de la EU2 están en orden **DE (0x94A/0x94B), EN (0x94C/0x94D), IT (0x94E/0x94F), FR (0x950/0x951), ES (0x952/0x953)**. Cada par es (tabla principal, tabla auxiliar); ambos tienen `count=120, header=0x200` y las mismas 114 cadenas. La fórmula con `lang_index` del JSON funciona igual: `eu2_id = 0x94A + lang_index*2 + (usa2_id - 0x18)`.

El resto de la AFS2 es 1:1: `USA2 0x1A..0x7DF4` → `EU2 +0x93A`; `USA2 0x0..0x17` → `EU2 +0x932`. La EU2 tiene además `0x0..0x931` (2.354 entradas, 166.544.660 B): 893 ADX únicos (audio PAL) + 1.461 duplicados de contenido USA (stubs de 202 B en su mayoría). No hay texto ahí.


## 3. Qué queda sin equivalencia

### 3.1 USA que no aparece en la EU

| Partición | Rango USA | Entradas | Bytes | Qué es |
|---|---:|---:|---:|---|
| 0 | `0x0021`..`0x0318` | 733 | 1.321.952 | guiones GSC (la EU tiene su propia versión en el mismo id) (4 tramos) |
| 0 | `0x0545`..`0x0559` | 20 | 40.778.448 | entradas de un bloque localizado (traducidas en la EU) (2 tramos) |
| 0 | `0x2a80`..`0x33b1` | 2354 | 166.544.660 | audio ADX: cola ausente en EU1; 892 entradas con contenido único (166.173.484 B) |
| 1 | `0x0018`..`0x0019` | 2 | 802.944 | tablas de pelea/pausa (reemplazadas por 10 archivos EU2 0x94A..0x953) |

- La cola `0x2A80..0x33B1` de la AFS1 es **audio ADX**: 2.354 entradas / 166.544.660 B. La EU1 no la tiene (su tabla termina en `0x338C`). De esas entradas, 892 tienen contenido único (166.173.484 B); el resto son stubs de 202 B que sí existen en la EU1 en otro lugar. **No es texto**; el port debe seguir leyendo el audio de la USA.

- `0x21..0x318` de la AFS1 son **guiones GSC** (`GSCF`): no desaparecen, pero la EU tiene versiones propias en los mismos ids (no son localización de texto). El port usa los GSC USA y remapea los ids de texto; no hay que tocar nada.

- `0x545..0x559` de la AFS1 son las entradas del menú que cambian por idioma; están cubiertas por el bloque de menú (no son „faltantes“, son traducciones).

- AFS2 `0x18`/`0x19`: reemplazadas por los 10 archivos de `0x94A..0x953`. No hay una copia 1:1.


### 3.2 EU que no aparece en la USA

| Partición | Rango EU | Entradas | Bytes | Qué es |
|---|---:|---:|---:|---|
| 0 | `0x0021`..`0x0318` | 733 | 1.321.952 | guiones GSC propios de la EU (no es texto localizado) (4 tramos) |
| 0 | `0x0542`..`0x0de5` | 2148 | 1.388.400 | bloque historia (copia localizada) (9 tramos) |
| 0 | `0x0dea`..`0x0e5b` | 104 | 203.763.680 | bloque menú (copia localizada) (10 tramos) |
| 0 | `0x1068`..`0x1076` | 15 | 2.450.176 | bloque objetos (copia localizada) |
| 1 | `0x094a`..`0x0953` | 10 | 4.015.744 | bloque pelea/pausa (copia localizada) |
| 1 | `0x0000`..`0x0931` | 2354 | 166.544.660 | ADX extra de la EU2 (audio PAL) + duplicados: 893 únicos / 166.249.538 B |

- **Font/sistema**: `0xDE6` no es drop-in (`Fnt4` en `+0x80`), `0xDE7` == USA `0x543` y `0xDE8` es solo EU. Por eso no aparece como fila de „sin equivalencia“: no es un bloque de 5 copias (ver 2.1).

- AFS1: las 4 copias extra de historia (`0x542..0xDE5`, 2.212 entradas; 2.148 con contenido único), el font/sistema (`0xDE6..0xDE8`, ver tabla especial en 2.1), las 5 copias de menú (`0xDE9..0xE5B`, 115 entradas; 104 únicas) y las 5 de objetos (`0x1068..0x1076`, 15). Todo eso lo cubre el mapa.

- AFS1 `0x21..0x318`: GSC propios de la EU (no son texto localizado; el port no los necesita).

- AFS2 `0x0..0x931`: 893 ADX extra (audio PAL, 166.249.538 B) + 1.461 duplicados de contenido USA; no es texto. AFS2 `0x94A..0x953`: los 10 archivos de pelea/pausa (4.015.744 B).

**Cardinalidades** (para chequear el mapa):

- AFS1: EU1 tiene **2.317 entradas netas extra** = 2.212 (4 copias de historia) + 1 (font) + 92 (4 copias extra de menú: 5×23 vs 23) + 12 (4 copias extra de items: 5×3 vs 3). La USA tiene **2.354 entradas de cola ADX** sin par; 13.234 − 2.354 + 2.317 = **13.197**, el count de la EU1.

- AFS2: EU2 tiene **2.362 entradas netas extra** = 2.354 (ADX PAL + duplicados) + 10 (textos de pelea/pausa) − 2 (USA2 `0x18`/`0x19` reemplazadas). 32.245 + 2.362 = **34.607**, el count de la EU2.

- Los `LOAD_*.DBT` **no son entradas aparte**: son la última entrada (posición `0x16`) de cada bloque de menú (`0xDFF/0xE16/0xE2D/0xE44/0xE5B`); en el ISO EU también están sueltos en `DATA/LOAD_UK|SP|DU|FR|IT.DBT`.


## 4. Qué cubre el mapa y qué falta para el port

Cubre **todos** los recursos localizados de la AFS1 y de la AFS2:

| Texto | Dónde | Estado en el port |
|---|---|---|
| Historia | AFS1 `0x319 + lang*0x229 + k` | ya remapeado |
| Menú + memory card | AFS1 `0xDE9 + lang*0x17 + k` | ya remapeado (memory card aparte) |
| Objetos/Z-items/habilidades | AFS1 `0x1068 + lang*3 + k` | **falta** |
| Pelea/pausa/HUD/condiciones | AFS2 `0x94A + lang_idx*2 + k` | **falta** |

Para cubrir objetos en el port alcanza con agregar el rango `0x767..0x769` al remapeo de `func_002EB9B0` (`ptid==0`): `id = 0x1068 + lang*3 + (flid - 0x767)`.

Para pelea/pausa/HUD hay dos caminos:

1. **Recomendado**: extraer los 10 archivos de `ZS2EU_2.AFS` (`0x94A..0x953`, 4,0 MB) a un overlay `gamedata/EU2/<id>.bin` y remapear `ptid==1` en `func_002EB9B0`. No copiar la EU2 entera (1,78 GB, reordenada).

2. Copiar `ZS2EU_2.AFS` como partición 3 y remapear solo esos 10 ids; es más simple de implementar pero suma 1,78 GB y deja el resto de la EU2 sin usar.


No hace falta remapear el font (`0x542`): el de la EU tiene otro layout (`Fnt4` en `+0x80`) y no es drop-in. Tampoco los GSC ni el audio: el port sigue con la USA.


## 5. Verificado, inferido y pendiente

### Verificado con datos

- Tablas y hashes completos de las 4 particiones (13.234/13.197 y 32.245/34.607 entradas).

- Los 3 bloques de la AFS1: base, count, stride y las 5 bases por idioma; textos de muestra en cada copia; `LOAD_*.DBT` del menú por SHA-1; items `Health +1`/`Salud +1`/…

- El bloque de la AFS2: `count=120, header=0x200`, 114 cadenas, `1P PAUSE`/`Continue Battle`/`Clear Conditions` y sus traducciones; orden DE, EN, IT, FR, ES.

- La cola ADX de la AFS1 (`0x2A80..0x33B1`) no está en la EU1; la EU2 tiene 893 ADX extra + 10 textos.

- El mapeo 1:1 de la AFS2: `0x1A..0x7DF4` → `+0x93A` (32.219/32.219 exactas), `0x0..0x17` → `+0x932` (24/24 exactas).


### Inferido (consistente, no probado en ejecución)

- Que los contenedores EU de items y de pelea/pausa son compatibles con los loaders USA (mismo `count/header`; el juego los descomprime con `func_002B24C8`). No se renderizó nada.

- Que el texto de pausa que muestra el port sale de AFS2 `0x18`/`0x19`; el contenido lo confirma, pero no se trazó el caller exacto en el ejecutable USA.


### Pendiente

- Probar en el port con la partición EU: items (`0x767..0x769`) y los 10 archivos de AFS2.

- Implementar el overlay `gamedata/EU2/<id>.bin` o la partición 3; hoy `plat_file.c` solo carga `ZS2EU_1.AFS`.

- Confirmar el caller de AFS2 `0x18`/`0x19` en el ejecutable USA (para saber si el `ptid` que llega es 1).


## 6. Referencia rápida

| Qué | Dónde |
|---|---|
| Historia EU | AFS1 `0x319 + lang*0x229`, 553 |
| Menú EU | AFS1 `0xDE9 + lang*0x17`, 23 |
| Memory card | posición `0xC` del menú: `0xDF5/0xE0C/0xE23/0xE3A/0xE51` |
| Objetos EU | AFS1 `0x1068 + lang*3`, 3 |
| Pelea/pausa EU | AFS2 `0x94A + lang_idx*2`, 2 (orden DE,EN,IT,FR,ES) |
| Font USA a conservar | AFS1 `0x542` (`Fnt4` en `+0x40`) |
| Font EU (no drop-in) | AFS1 `0xDE6` (`Fnt4` en `+0x80`) |
| Cola ADX USA sin EU | AFS1 `0x2A80..0x33B1` |
| ADX EU extra | AFS2 `0x0..0x931` |

## 7. Estado en el port (2026-11-11)

- **AFS1 historia / menú / memory card**: remapeados y confirmados en pantalla (menús, historia y diálogo en ES).
  `eu_lang()` en `port/full/plat_file.c` ya corrige el orden FR/DE del bloque; la fórmula del mapa coincide.
- **Objetos/Z-items**: remapeados en `func_002EB9B0` (`0x767..0x769` → `0x1068 + lang*3 + delta`), build
  `7415fd89…`. **No ejercitado en runtime**: el demo CPU vs CPU no abre `0:0x767..0x769`; falta entrar al menú
  de Z-items/objetos y confirmar los textos en pantalla. Offline se verificó que EU ES `0x106B..0x106D` existen
  y tienen tamaño/estructura equivalentes a las USA.
- **AFS2 (pausa/HUD)**: **pendiente, no aplicado**. El demo abre `(1,25)` = USA2 `0x19` dos veces, así que esa
  tabla sí se usa en pelea; para traducirla hace falta un overlay con las 10 entradas EU2 `0x94A..0x953`
  (~4 MB) y remapear `ptid==1` con el orden **DE,EN,IT,FR,ES**. No se aplicó porque no hay forma de pausar el
  demo (START sale del attract y vuelve al título) y no quería cambiar el build confirmado sin verlo en pantalla.
- **Font `0xDE6`**: no es drop-in (USA `0x542` está en `+0x40`, EU en `+0x80`); seguir usando el USA.
- **Cola ADX USA `0x2A80..0x33B1`**: no está en EU1; el audio sigue saliendo de la USA (no es texto).
- **Título/overlay**: "Press START button" sigue en inglés y no aparece como string en el `DBZP.BIN` USA/EU
  (búsqueda de strings planos); parece una textura/tabla USA fuera de este mapa. No cubierto.
