# F8 — Textos de la historia (packs 0x319..0x541): cadena, punto de enganche y formato

Fecha: 2026-11-11. **Solo lectura**: no edité, compilé ni ejecuté nada del proyecto. No toqué
`/mnt/datos2/BT2-Decomp`. Lo único escrito es este informe (y scripts de análisis en `/tmp/opencode/`,
que no forman parte del proyecto). El diff del final **no está aplicado**.

Objetivo: diseñar la capa de traducción de los diálogos/narración de la historia, análoga a
`port/full/plat_text.c` (F5), pero para los 553 packs de texto del AFS `0x319..0x541`.

---

## 0. Resumen en cinco líneas

- El comando GSC **`0xFA4`** (`src/auto/m2c_2A70F8.c:6-10`) llama `func_002A3A98(id)` con el id
  absoluto del pack; `func_002A3A98` (`port/eq/2A3A98.c:9`) **encola** la lectura con
  `func_00100ED0(id,0,flag)` y guarda el buffer en `gBtlScript.textFile` (`0x003B0F40`,
  `port/build/full/link.ld:6122`).
- La lectura **no es inmediata**: `func_00100ED0` sólo abre el AFS, obtiene el tamaño en sectores,
  asigna `sectores << 11`, cierra y deja en cola `{tamaño, buffer, id}` en `D_00387F80`
  (`port/eq/100ED0.c:28-43`). El *scene loader* llama `func_00100FC8`, que hace el `ReadNw`
  (`port/eq/100FC8.c:53-95`, llamado desde `port/eq/2AB1A0.c:72,77`, `2AB488.c:71,76`,
  `2AB6F8.c:26,33`).
- El string se lee al dibujar: `BtlScript_GetText(n)` (`src/battle/btl_script_2A3AD0.c:101-105`)
  devuelve `textFile + (word[n+1] / 4) * 4`; lo llaman **sólo** `func_002A38C0`
  (`port/eq/2A38C0.c:64,66`, globo de diálogo/narración) y `func_002A7650`
  (`port/eq/2A7650.c:69`, cálculo de layout). En el ELF principal hay exactamente 3 `jal` a
  `0x2A3AD0` (0x2A39A8, 0x2A39C8, 0x2A777C) y ninguno en `DBZP.BIN`.
- **Punto de enganche elegido: (b)**, interceptar esas 3 llamadas en `port/eq/2A38C0.c` y
  `port/eq/2A7650.c`, devolviendo un buffer UTF-16LE estático si hay traducción para
  `(pack, n)`. No se toca el AFS, ni el buffer del juego, ni `src/` (matching).
- El formato para el traductor es `pack:linea=texto` (p. ej. `0x319:4=¿Quién sos? ¡Decímelo!`),
  con `\n` para el salto; se carga por pack en `func_002A3A98`. Los menús, tutoriales, nombres,
  frases de victoria y títulos de misión están en **otras tablas** (0x54C, 0x54F, 0x550 sub1-3,
  0x553 sub2, 0x545/0x546) y **no** quedan cubiertos por este hook.

---

## 1. Cómo se lee un texto de historia (cadena completa)

### 1.1 Del guion al buffer

| paso | archivo:línea | qué hace |
|---|---|---|
| 1 | `src/auto/m2c_2A70F8.c:6-10` | comando GSC `0xFA4`: si `arg0 == 0`, `func_002A3A98(Gsc_GetInt())`. El operando del guion es el **id absoluto del pack** (0x319..0x541). No mira la bandera de idioma de voces. |
| 2 | `port/eq/2A3A98.c:8-13` | `D_003B0F40 = func_00100ED0(a0, 0, D_003876A8 != 0);` — `D_003B0F40` es `gBtlScript.textFile` (ver 1.2). |
| 3 | `port/eq/100ED0.c:28-43` | abre la partición AFS (`func_002EB9B0`), pide el tamaño en **sectores** (`func_002EC6B0`), asigna `sectores << 11` (`func_0028BAA8`), cierra (`func_002EBB08`) y **encola** `{sectores, buffer, id}` en `D_00387F80[D_00387698..+2]`; devuelve el buffer. **No lee el archivo.** |
| 4 | `port/eq/100FC8.c:53-69` | *state 0*: toma el triplete de la cola y abre el archivo. |
| 5 | `port/eq/100FC8.c:89-95` | `func_002EC0C8(handle, sectores, buffer)` = `ReadNw` sobre el buffer encolado. |
| 6 | `port/eq/100FC8.c:71-81` | *state 2*: cuando `func_002EC990(handle) == 3`, cierra y avanza. |
| 7 | `port/eq/2AB1A0.c:72,77` (y `2AB488.c:71,76`, `2AB6F8.c:26,33`) | el *scene loader* arranca y bombea la cola: `func_00100FC8(1)` / `func_00100FC8(0)`. En el ELF, los `jal 0x100FC8` están en 0x2AB2DC, 0x2AB5C0, 0x2AB770, etc. |
| 8 | `src/battle/btl_script_2A3AD0.c:101-105` | al dibujar: `return (u8 *)gBtlScript.textFile + (file[n+1] / 4) * 4;` (n 0-based). |
| 9 | `port/eq/2A38C0.c:63-66` | `func_002A38C0` (globo de diálogo/narración) llama `Font_GetHeight(BtlScript_GetText(rec[1]))` y `Font_PrintAt(..., BtlScript_GetText(rec[1]))`. `rec[1]` es el índice de línea (byte con signo) del registro de 0x68 bytes. |
| 10 | `port/eq/2A7650.c:69` | el comando que arma el layout llama `BtlScript_GetText(var_a0, ...)` para contar líneas (`func_002A0EA8`). |

**Consecuencia importante para el enganche:** en el paso 2 el contenido del pack todavía **no está
leído**; recién llega en los pasos 4-6. Por eso “pisar la tabla al cargarla” (como en el popup de
memory card) **no es directamente posible** en `func_002A3A98`: estaríamos escribiendo sobre un
buffer que después el `ReadNw` sobrescribe (o sobre memoria sin inicializar).

### 1.2 `gBtlScript.textFile` y el layout

- `port/build/full/link.ld:6122`: `gBtlScript = 0x003B0F3C`.
- `include/battle/btl_script.h:96-99` (layout de BT3, coincide en los dos primeros campos):
  `+0x000 story`, `+0x004 textFile`, `+0x008 file8`.
- `D_003B0F40` = `gBtlScript + 4` = **`textFile`**.
- En BT2 `file8` es un **array de hasta 8 punteros** (`port/eq/2A3BB8.c` / `src/auto/perm_2A3BB8.c`
  escribe `D_003B0F44 + i*4`), no un solo puntero como en BT3. No es texto: `func_002A3C08` y
  `func_002A4148` lo usan para los buffers de retrato; el comando `0xFA5` los carga
  (`src/auto/m2c_2A78F0.c` → `func_002A3BB8`). Nuestro hook **no** los toca.

### 1.3 Formato exacto del pack

Los 553 archivos del rango `0x319..0x541` son **datos crudos** (no LZ) con este formato:

```
+0x00  u32 count
+0x04  u32 off[count]        // offsets relativos a la base del pack, alineados a 4
+...   strings UTF-16LE      // empiezan con BOM FF FE, '\n' = U+000A, terminan en U+0000
```

- `BtlScript_GetText(n)` usa `word[n+1]` → `off[n]`, con `n = 0 .. count-1`.
- `count` **no** incluye un sentinel: hay exactamente `count` offsets. Las últimas entradas pueden
  apuntar a un string vacío (por ejemplo, en 0x319 `count=10`, `off[8]=off[9]=0x360=size`, y las
  líneas 8 y 9 están vacías).
- Ejemplo real (AFS `0x319`, size `0x360`): `count=10`, `off = 0x30,0xD0,0x180,0x190,0x1D0,
  0x200,0x270,0x2C0,0x360,0x360`; línea 0 = `"Five peaceful years have \npassed since the epic
  battle against Piccolo..."`, línea 4 = `"Who are you? Tell me!"`.

### 1.4 Evidencia en RAM (dump del port)

`BT2-test/logs/vivo/20261106-200837_ram1_f3168.bin` (32 MB, modo historia):

- En la dirección PS2 `0x003B0F40` (campo `textFile`) hay `0x00109E7C0`.
- En `0x00109E7C0`: `count=10`, `off = 0x30,0xD0,0x180,0x190,0x1D0,0x200,0x270,0x2C0,0x360,0x360`.
- Línea 0 del pack: `"Five peaceful years have \npassed since the epic battle against Piccolo..."`.
- El registro 0 del globo (`0x003B0F7C`, 0x68 bytes por registro) tiene `+0xC = 1` (activo) y
  `+0x1 = 0` (índice de línea 0). Coincide con lo que dibuja `func_002A38C0`.

O sea: el pack está en RAM, entero, en el buffer que devolvió `func_00100ED0`; el puntero del
string es **relativo al pack** y se resuelve en cada llamada a `BtlScript_GetText`.

### 1.5 Cuánto texto hay

Barrido de las 553 entradas (sólo lectura del AFS, `/tmp/opencode/story_layout.py`):

| métrica | valor |
|---|---:|
| packs en `0x319..0x541` | 553 |
| strings no vacíos | 2.587 |
| caracteres UTF-16 (sin BOM/NUL) | ~147.500 |
| largo máximo de un string | 156 unidades |
| líneas por string | 1..5 (máx. 5) |
| ancho máximo de línea | **359 px** (font0, misma tabla de avances que F5) |
| slot original: holgura mediana | **4 u16** |
| strings que no entrarían en su slot con una traducción +20 % | **2.047 / 2.587 (79 %)** |

La holgura mediana de 4 u16 es la clave: los offsets están empaquetados al byte, no hay slots de
0x40 como en la tabla del memory card. Una traducción al español (típicamente +15..25 %) **no entra
en el slot original** en la mayoría de las líneas.

---

## 2. Dónde engancharía un override

### 2.1 Opciones evaluadas

| opción | cómo | veredicto |
|---|---|---|
| **(a) pisar el pack al cargarlo** (análogo a `plat_text.c`) | en `func_002A3A98`, después de `func_00100ED0`, reescribir el buffer | **descartada**: (1) en ese momento el contenido **no está leído** (la lectura se encola y la hace `func_00100FC8`), así que el `ReadNw` posterior pisaría el override; (2) el 79 % de los strings no entra en su slot con +20 % de traducción, habría que reempaquetar y reescribir los offsets; (3) habría que esperar la finalización de la lectura (hookear el *pump* compartido o sondear), con más riesgo. |
| **(b) interceptar el puntero en el lector** | en las 3 llamadas a `BtlScript_GetText`, devolver nuestro buffer UTF-16 si hay traducción | **elegida**: no depende del timing de la lectura, no toca el AFS ni el buffer del juego, no tiene límite de slot (sólo el ancho/líneas del globo), y cubre el 100 % de los lectores (3 `jal` en el ELF, 0 en el overlay). |
| **(c) reemplazar los archivos del pack** | editar el AFS / usar `gamedata/mods/...` | **descartada**: toca datos del juego, hay que rearmar 553 archivos y afecta a cualquier pantalla que use el mismo id; no lo necesitamos. |

### 2.2 Por qué (a) no es “barata” acá

La diferencia con el popup de memory card (F5) es el **timing**:

- F5: `func_003E3D38` descomprime el sub-bloque **sincrónicamente** (`func_002B24C8`) y llama
  `func_0029BB88`; cuando `plat_text.c` escribe, la tabla ya está en RAM.
- Historia: `func_00100ED0` **sólo encola**. El `ReadNw` lo hace `func_00100FC8` en otro momento
  (el *scene loader*). `func_00100ED0` no tiene callback de finalización por archivo; el *pump* es
  genérico y compartido con todas las cargas.

Aun si se hookeara el *pump* para aplicar el override después del `ReadNw`, habría que reempaquetar
los strings y reescribir `off[]` dentro de la asignación por sectores (`sectores << 11`,
`port/eq/100ED0.c:35`; `func_002EC6B0` = `GetFsizeSct`, `port/full/plat_file.c:101`). Mis cuentas
dicen que un +20 % **entra** en la asignación por sectores en los 553 packs (el tamaño máximo es
0x820 y casi todos tienen holgura de sector), pero es bastante más código y más frágil que (b).

### 2.3 Cobertura de (b)

`BtlScript_GetText` tiene exactamente **3 llamadas** en el binario USA:

| dirección del `jal` | función que llama | archivo del port |
|---|---|---|
| `0x002A39A8` | `func_002A38C0` (globo de diálogo/narración) | `port/eq/2A38C0.c:64` |
| `0x002A39C8` | `func_002A38C0` (misma función, segunda llamada) | `port/eq/2A38C0.c:66` |
| `0x002A777C` | `func_002A7650` (layout del texto) | `port/eq/2A7650.c:69` |

No hay `jal 0x2A3AD0` en `DBZP.BIN`. Por lo tanto, hookear esas 3 llamadas cubre todo lo que
dibuja/mede los packs de historia en esta build. (La llamada al `0x2A3AD0` desde una tabla de
funciones no existe: no es un comando GSC, es una función interna.)

### 2.4 Punto exacto y registro del pack

- **Pack pedido:** `port/eq/2A3A98.c:9` — agregar `Port_HistoriaPack(a0)` **antes** de
  `func_00100ED0`. Guarda el id (0x319..0x541) y carga en memoria los overrides de ese pack. No
  depende de que la lectura haya terminado.
- **Línea mostrada:** `port/eq/2A38C0.c:64,66` y `port/eq/2A7650.c:69` — reemplazar
  `BtlScript_GetText(n)` por `Port_HistoriaLinea(n, BtlScript_GetText(n))`.
- **Limpieza (opcional):** `port/eq/2A3430.c:44` (unload de los archivos de texto) —
  `Port_HistoriaPack(-1)` después de `func_002A3170()`.

---

## 3. Formato del archivo de traducción

### 3.1 Esquema

Archivo de texto **UTF-8** (BOM opcional), una línea por texto:

```
# comentario
# pack:linea = texto        (pack en hex o decimal; linea 0-based, la misma n de BtlScript_GetText)
0x319:0=Cinco años de paz han pasado\ndesde la épica batalla\ncontra Piccolo...
0x319:4=¿Quién sos? ¡Decímelo!
0x31b:4=Goku y sus amigos\ndisfrutaban de un reencuentro...
```

- Clave: `pack:linea`; `strtol(..., 0)` acepta `0x319` y `793`.
- Valor: todo lo que sigue al primer `=` (puede contener `:` y `=`). `\n` = salto de línea.
  Se ignoran espacios/tabs inmediatamente después de `=`; se conservan los espacios finales.
- Línea vacía o valor vacío = “sin override” (queda el original).
- `#` sólo es comentario al principio de la línea.
- Sin límite de slot: el texto puede ser más largo que el original. Sí hay límites de **ancho**
  (359 px) y **líneas** (5), que el cargador valida/ajusta.

### 3.2 Dónde se lee y cuándo

- Ruta: `$BT2_TEXTO_HISTORIA` si está; si no, `textos/bt2_historia.<lang>.txt` según el setting
  `idioma` / `$BT2_IDIOMA` (mismo criterio que `plat_text.c:102-118`: 0=EN, 1=ES, 2=FR, 3=DE,
  4=IT); fallback a `textos/bt2_historia.txt`.
- Se lee **una vez** (cache en un buffer estático) y se filtran las líneas del pack actual en
  `Port_HistoriaPack`. Al cambiar de pack se vuelve a filtrar; no hace falta reiniciar el juego.
- Si el archivo no existe, no hay overrides y el juego queda igual.

### 3.3 Herramientas para el traductor (propuestas, no implementadas)

1. `port/tools/dump_historia.py` (sólo lectura del AFS del usuario): recorre `0x319..0x541` y
   escribe una **plantilla local** con el original como comentario y la clave vacía:

   ```
   # 0x319:0  "Five peaceful years have \npassed since..."
   0x319:0=
   ```

   Ese archivo contiene texto original del juego: va a `gamedata/` o a una carpeta ignorada por
   git, **no se versiona**. El archivo final de traducción (`textos/bt2_historia.es.txt`) contiene
   sólo las claves y el texto traducido.
2. `port/tools/check_historia.py`: valida claves existentes, ancho ≤ 359 px, ≤ 5 líneas, sin
   caracteres sin glyph (`—` U+2014, emoji), y reporta faltantes/sobrantes. Se puede reutilizar la
   tabla de avances y el conversor de `check_textos.py` (F5) cambiando el rango de packs y la
   capacidad (sin slot fijo).

### 3.4 Límites del font/globo (corrección a F5)

- El font0 (AFS `0x542`, `+0x40`) tiene ASCII, latín-1, `¿ ¡ ñ Ñ` y vocales acentuadas. El font1
  (`+0x89C0`) tiene `’ ‘ “ ” …` y `　` (U+3000). `Font_FindGlyph` (`port/eq/2A2018.c`) recorre
  hasta 8 fuentes, así que **`’` y `…` sí se dibujan** (a diferencia de lo que decía F5, que sólo
  miró el font0). **No** hay `—` (U+2014) ni emoji.
- Recomendación: usar `'`, `...`, `-` (ASCII) para que el ancho sea predecible; los acentos y `¿¡`
  son seguros.
- Límites medidos en los 2.587 strings originales: **359 px** de ancho máximo y **5 líneas**
  máximo. El cargador envuelve a 360 px y rechaza > 5 líneas (queda el original y se avisa). El
  alto del globo lo maneja el juego (`Font_GetHeight` / `func_002A0EA8`), así que un texto de 2
  líneas se centra distinto que uno de 4 (comportamiento normal).

---

## 4. Alcance: ¿todos los textos pasan por este lector?

**No.** El lector `BtlScript_GetText` sólo sirve los packs de historia `0x319..0x541` (diálogo y
narración de las escenas). Los demás textos del juego están en otras tablas, con el mismo formato
`u32 count; u32 off[]; UTF-16LE` pero en otros recursos:

| recurso | qué contiene | ¿lo cubre este hook? | evidencia |
|---|---|---|---|
| `0x319..0x541` | 553 packs de diálogo/narración de la historia (2.587 strings) | **sí** | cadena de §1 |
| `0x54C` | menú/UI: 50 líneas de diálogo, 41 nombres de movimientos, 95 ayudas/tutoriales, 580 etiquetas de bonus/items, 333 frases | **no** | `port/eq/3EC690.c:30-33` carga `0x544+8`; `port/eq/3EABC0.c:26-30` descomprime; `port/eq/3EA470.c:35` dibuja `tbl = D_00428F48+8` |
| `0x54F` | prompts de “Receive link bonus?” y copia de la tabla de 49 del memory card | **no** (el popup de F5 es `0x550`) | F5 §2.3; barrido: tabla de 4 en `+0x133D80` |
| `0x550` sub-bloque 0 | 49 mensajes del diálogo de memory card | **sí, pero por `plat_text.c` (F5)**, no por este hook | `port/full/plat_text.c`, `port/eq/29BB88.c:48` |
| `0x550` sub-bloques 1..3 | 35 textos de ayuda de opciones (el mismo set repetido en los 3) | **no** | barrido: `e550_s1/s2/s3.raw`, tabla de 35 en `+0xAAA00/+0x15F740/+0x112DC0` |
| `0x553` sub-bloque 2 | 416 títulos de misión/capítulo (`"Mysterious Alien Warrior"`, `"Kakarot"`, ...) | **no** | barrido: `e553_s2.raw`, tabla de 416 en `+0x11DEC0` |
| `0x545` | 19 avisos de salud/seguridad + copia de la tabla de 49 | **no** | barrido del AFS (`e545_s0/s1.raw`); no rastreé el llamador en código |
| `0x546` | 135 nombres/formas + copia de la tabla de 49 + 16 textos de tutorial | **no** | barrido del AFS (`e546_s0/s2.raw`); no rastreé el llamador en código |
| `0x542` | fuente (dos `Fnt4`), no texto | n/a | F5 §3.2 |

Notas:

- La tabla de 49 del memory card aparece **duplicada** en 0x545, 0x546 y 0x54F (mismo contenido,
  `count=49`, `word[1]=0x100`). `plat_text.c` valida `count==49 && word[1]==0x100`, así que también
  aceptaría esas copias; hoy sólo se llama desde `3E3D38` (0x550), que es la que F5 probó.
- Los **nombres de personaje** (placas/menús) y las **voces** no están en el pack de historia: las
  voces son ADX (F8) y los nombres están en la tabla de 135 de 0x546/0x54C; los títulos de misión,
  en la de 416 de 0x553.
- Por lo tanto, una traducción completa del juego necesita, además de este hook, capas para
  `0x54C`, `0x54F`, `0x550` sub1-3, `0x553` sub2 y (si se confirma el llamador) `0x545/0x546`.

---

## 5. Esfuerzo, riesgo y sonda de confirmación

### 5.1 Esfuerzo

| parte | tamaño | nota |
|---|---|---|
| hook C (`port/full/plat_text_historia.c`) | ~200-250 líneas | copia el conversor UTF-8→UTF-16, la tabla de avances y el `envolver` de `plat_text.c`, adaptados a “sin slot” |
| enganches en game C | 3 archivos, ~10 líneas | `2A3A98.c`, `2A38C0.c`, `2A7650.c` (+ opcional `2A3430.c`) |
| herramienta de dump/check | ~100 líneas Python | plantilla local + validación |
| traducción | 2.587 strings / ~147.500 caracteres | es el grueso; a 10-20 k caracteres/día, 1-2 semanas de traducción + QA |

### 5.2 Riesgo

- **Bajo** en el runtime: se devuelve un puntero a un buffer estático; no se escribe en RAM del
  juego, no se toca el AFS, no se cambia el save.
- **Medio** en layout: si un texto supera 359 px o 5 líneas, se rechaza (queda el original). El
  check tool lo detecta antes de jugar.
- **Bajo/medio** en punteros: el buffer debe ser estático (no `malloc`, que puede devolver > 4 GB)
  y estar alineado a 4. El binario se enlaza `-no-pie` con `-Ttext-segment=0x40000000`, así que
  una dirección estática (~0x40C8xxxx) entra en 32 bits. La firma propuesta usa `u32` para el
  puntero, como `plat_text.c` usa `uint32_t` para la tabla.
- **Bajo** por el pack: el id se registra antes de la lectura; si no hay archivo de traducción,
  `sTiene[]` queda todo en 0 y se devuelve el original.

### 5.3 Sonda (una corrida, con el juego cerrado para instalar)

> El que aplique el cambio debe seguir el ciclo de `BT2-Port/AGENTS.md`: backup de cada `.c` a tocar
> en `BT2-Recomp/backups/<archivo>.pre_historia`, compilar con `capped.sh`, e instalar sólo con
> `pgrep -x bt2` vacío.

1. Compilar sólo lo tocado y enlazar:

   ```sh
   cd BT2-Recomp
   BT2_IRFIX=1 scripts/capped.sh 8G python3 port/tools/build_full.py --jobs 2 --only 2A3A98
   BT2_IRFIX=1 scripts/capped.sh 8G python3 port/tools/build_full.py --jobs 2 --only 2A38C0
   BT2_IRFIX=1 scripts/capped.sh 8G python3 port/tools/build_full.py --jobs 2 --only 2A7650
   scripts/capped.sh 8G python3 port/tools/link_full.py
   ```
2. Instalar `BT2-Recomp/port/build/full/bt2full` en `BT2-test/bin/bt2`, guardando el anterior en
   `BT2-Recomp/backups/bt2.pre_historia` (sólo con `pgrep -x bt2` vacío).
3. Archivo de prueba `BT2-test/textos/bt2_historia.es.txt` (el juego corre con cwd `BT2-test`, por
   eso la ruta relativa `textos/...`):

   ```
   0x319:0=Cinco años de paz han pasado\ndesde la épica batalla\ncontra Piccolo...
   0x319:4=¿Quién sos? ¡Decímelo!
   0x31b:4=Texto de prueba de cinco líneas\npara ver que el globo\ncrece y se centra\nsin recortar\nninguna línea.
   0x541:0=Hace mucho tiempo...
   ```

4. Correr con log (el `jugar.sh` de BT2-test hereda las variables de entorno; el stderr va a
   `logs/vivo/<fecha>.log`):

   ```sh
   cd BT2-test
   BT2_TEXTO_HISTORIA=textos/bt2_historia.es.txt BT2_HISTLOG=1 ./jugar.sh
   ```

   El log (stderr o `bt2_fightlog_note`) debe imprimir una vez por `(pack,linea)`:
   `F8 historia: pack 0x319 linea 0`, etc.

5. Qué mirar:
   - Modo Historia → primera escena (Raditz): la línea 0 y la 4 deben salir en español.
   - Una escena de otro pack (p. ej. 0x31B) para confirmar que el id cambia y que se aplican sus
     overrides.
   - La línea de 5 líneas: el globo debe centrarse/crecer sin recortar.
   - Un menú/tutorial: debe seguir en inglés (confirma que el hook no se metió en 0x54C).
   - El log: que no aparezcan packs fuera de 0x319..0x541 ni líneas fuera de rango.

Si el log muestra `(pack,linea)` distintos de los esperados, el problema es el mapeo del dump, no
el hook; se corrige la herramienta antes de traducir.

---

## 6. Cambio propuesto (diff boceto, **NO aplicado**)

### 6.1 `port/eq/2A3A98.c` — registrar el pack pedido

```diff
--- a/port/eq/2A3A98.c
+++ b/port/eq/2A3A98.c
@@ -2,10 +2,12 @@
 
 s32 func_00100ED0(s32 a0, s32 a1, s32 a2);
+void Port_HistoriaPack(s32 pack);                 /* F8: port/full/plat_text_historia.c */
 extern u8 D_003876A8;
 extern s32 D_003B0F40;
 
 /* 0x002A3A98 (approx): D_003B0F40 = func_00100ED0(a0, 0, D_003876A8 != 0); clear D_003876A8. */
 void func_002A3A98(s32 a0) {
+    Port_HistoriaPack(a0);                        /* F8: recuerda el pack (0x319..0x541) */
     D_003B0F40 = func_00100ED0(a0, 0, D_003876A8 != 0);
     if (D_003876A8 != 0) {
         D_003876A8 = 0;
```

### 6.2 `port/eq/2A38C0.c` — sustituir el puntero al dibujar

```diff
--- a/port/eq/2A38C0.c
+++ b/port/eq/2A38C0.c
@@ -8,6 +8,7 @@
 void BattleSetup_FinishEx(s32 arg0);
 s32 BtlScript_GetText(s32 arg0);
+s32 Port_HistoriaLinea(s32 linea, s32 original); /* F8: port/full/plat_text_historia.c */
 u32 Font_GetHeight(s32 arg0);
 void Font_PrintAt(s32 arg0, s32 arg1, s32 arg2);
@@ -24,6 +25,7 @@
     s32 temp_v0;
     u32 temp_v0_2;
+    s32 texto;
@@ -62,7 +64,9 @@
-                temp_v0_2 = Font_GetHeight(BtlScript_GetText(*(s8 *)(var_s1 + 1)));
+                texto = Port_HistoriaLinea(*(s8 *)(var_s1 + 1),
+                                           BtlScript_GetText(*(s8 *)(var_s1 + 1)));
+                temp_v0_2 = Font_GetHeight(texto);
                 var_s0 -= (s32)((temp_v0_2 >> 0x1F) + temp_v0_2) >> 1;
-                Font_PrintAt(var_s2, var_s0, BtlScript_GetText(*(s8 *)(var_s1 + 1)));
+                Font_PrintAt(var_s2, var_s0, texto);
```

### 6.3 `port/eq/2A7650.c` — el layout también usa la traducción

```diff
--- a/port/eq/2A7650.c
+++ b/port/eq/2A7650.c
@@ -1,6 +1,7 @@
 #include "common.h"
 
 s32 BtlScript_GetText(s32 a0, s32 a1);
+s32 Port_HistoriaLinea(s32 linea, s32 original); /* F8: port/full/plat_text_historia.c */
 s32 Font_GetGlyphHeight(void);
@@ -66,7 +67,7 @@
-                temp_r = BtlScript_GetText(var_a0, temp_a1);
+                temp_r = Port_HistoriaLinea(var_a0, BtlScript_GetText(var_a0, temp_a1));
                 var_s1 += 1;
```

### 6.4 `port/eq/2A3430.c` — limpiar al descargar (opcional)

```diff
--- a/port/eq/2A3430.c
+++ b/port/eq/2A3430.c
@@ -1,6 +1,7 @@
 #include "common.h"
 
 void func_00256590(void);
+void Port_HistoriaPack(s32 pack);                 /* F8 */
 void func_0028BB60(s32 arg0);
@@ -42,4 +43,5 @@
-    func_002A3170();
+    func_002A3170();
+    Port_HistoriaPack(-1);
 }
```

### 6.5 Archivo nuevo `port/full/plat_text_historia.c` (boceto)

> `link_full.py` compila todo `port/full/*.c` por glob; no hay que tocar el build.
> El código de UTF-8→UTF-16, `kAdv` y `envolver` se copia de `plat_text.c` (misma fuente 0x542).

```c
/*
 * F8: textos de la historia (packs 0x319..0x541).
 *
 * El juego pide el pack con el comando GSC 0xFA4: func_002A3A98(id) encola la lectura en
 * func_00100ED0 y guarda el buffer en gBtlScript.textFile (0x003B0F40). El scene loader
 * (func_00100FC8) hace el ReadNw. Al dibujar, func_002A38C0/2A7650 llaman BtlScript_GetText(n)
 * -> textFile + (word[n+1]/4)*4. Este archivo NO toca el AFS ni el buffer: recuerda el id y, en
 * cada llamada, devuelve un buffer UTF-16LE propio si hay traduccion para (pack, n).
 *
 * Config: $BT2_TEXTO_HISTORIA o textos/bt2_historia.<lang>.txt (idioma = setting "idioma" /
 * $BT2_IDIOMA, igual que plat_text.c). Sin archivo no hay overrides.
 * Formato: "pack:linea=texto", pack hex o decimal, linea 0-based, \n para el salto.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Port_Setting(const char *name, int def) __attribute__((weak));

#define HIST_PACK_MIN 0x319
#define HIST_PACK_MAX 0x541
#define HIST_LINEAS   64      /* el pack mas grande tiene ~23 lineas */
#define HIST_U16      512     /* 5 lineas x ~100 caracteres */
#define HIST_ANCHO    360     /* px: la linea mas ancha del original mide 359 */
#define HIST_MAXLIN   5
#define HIST_ARCHIVO  (2u << 20)

static char sArchivo[HIST_ARCHIVO];
static unsigned sArchivoLen;
static int sCargado;
static int32_t sPack = -1;
static unsigned short sLinea[HIST_LINEAS][HIST_U16] __attribute__((aligned(4)));
static unsigned char sTiene[HIST_LINEAS];
static unsigned long long sAvisado;

/* Mismas rutas que plat_text.c:102-118 (el idioma sale de "idioma" / $BT2_IDIOMA). */
static const char *kRuta[5] = {
    "textos/bt2_historia.txt",
    "textos/bt2_historia.es.txt",
    "textos/bt2_historia.fr.txt",
    "textos/bt2_historia.de.txt",
    "textos/bt2_historia.it.txt",
};

/* Avance (px) de 0x20..0x7E del font0 del juego (AFS 0x542, +0x40); igual que plat_text.c. */
static const unsigned char kAdv[95] = {
     9, 5, 7,13,11,19,15, 5, 7, 7, 9,13, 7, 7, 5, 9,11,11,11,
    11,13,11,11,11,11,11, 5, 7,13,13,13, 9,17,15,11,13,13,11,
    11,13,11, 9, 9,11, 9,13,11,13, 9,13,11,13,13,13,15,17,13,
    13,13, 7, 9, 7,13,13, 7,11,11,11,11,11, 9,11,11, 5, 7,11,
     5,17,11,11,11,11, 9,11, 9,11,11,15,11,11, 9,11, 5,11,13,
};

/* Mismo parser que plat_text.c:90-101 (0..4, en/es/fr/de/it). */
static int idioma_de_texto(const char *s);

static void cargar_archivo(void) {
    char ruta[256];
    const char *e;
    FILE *fp;
    if (sCargado) return;
    sCargado = 1;
    e = getenv("BT2_TEXTO_HISTORIA");
    if (e != NULL && e[0] != 0) {
        snprintf(ruta, sizeof ruta, "%s", e);
    } else {
        int lang = 0;
        const char *env = getenv("BT2_IDIOMA");
        if (env != NULL && env[0] != 0) lang = idioma_de_texto(env);
        else if (Port_Setting != NULL) lang = Port_Setting("idioma", 0);
        if (lang < 0 || lang > 4) lang = 0;
        /* kRuta[0..4] = textos/bt2_historia.txt, .es, .fr, .de, .it */
        snprintf(ruta, sizeof ruta, "%s", kRuta[lang]);
    }
    fp = fopen(ruta, "rb");
    if (fp == NULL) return;                 /* sin archivo: todo original */
    sArchivoLen = (unsigned)fread(sArchivo, 1, sizeof sArchivo - 1, fp);
    sArchivo[sArchivoLen] = 0;
    fclose(fp);
}

static int utf8_a_utf16(const char *s, unsigned short *out, int cap);   /* de plat_text.c */
static int ancho_char(unsigned c) { return (c >= 0x20 && c < 0x7f) ? kAdv[c - 0x20] : 11; }
/* copiar de plat_text.c cambiando TEXTO_ANCHO -> HIST_ANCHO y TEXTO_LINEAS -> HIST_MAXLIN */
static int envolver(const unsigned short *in, int len, unsigned short *out, int cap);

/* Se llama desde func_002A3A98 ANTES de func_00100ED0: la lectura todavia no empezo. */
void Port_HistoriaPack(int32_t pack) {
    char *line;
    if (pack == sPack) return;
    sPack = pack;
    sAvisado = 0;
    memset(sTiene, 0, sizeof sTiene);
    if (pack < HIST_PACK_MIN || pack > HIST_PACK_MAX) return;
    cargar_archivo();
    if (sArchivoLen == 0) return;
    line = sArchivo;
    if (sArchivoLen >= 3 && (unsigned char)line[0] == 0xEF &&
        (unsigned char)line[1] == 0xBB && (unsigned char)line[2] == 0xBF) {
        line += 3;                         /* BOM UTF-8 del archivo */
    }
    for (; line != NULL && *line != 0; ) {
        char buf[2048];
        char *nl = strchr(line, '\n');
        char *p = buf, *q, *r;
        size_t len = (nl != NULL) ? (size_t)(nl - line) : strlen(line);
        long pk, idx;
        if (len >= sizeof buf) len = sizeof buf - 1;   /* linea gigante: truncar */
        memcpy(buf, line, len);
        buf[len] = 0;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '#' || *p == 0) goto next;
        pk = strtol(p, &q, 0);
        if (q == p || *q != ':') goto next;
        idx = strtol(q + 1, &r, 0);
        if (r == q + 1 || *r != '=') goto next;
        r++;
        while (*r == ' ' || *r == '\t') r++;
        { size_t z = strlen(r); while (z > 0 && r[z - 1] == '\r') r[--z] = 0; }
        if (pk == (long)pack && idx >= 0 && idx < HIST_LINEAS && *r != 0) {
            unsigned short tmp[HIST_U16];
            int n = utf8_a_utf16(r, sLinea[idx], HIST_U16);
            n = envolver(sLinea[idx], n, tmp, HIST_U16);
            if (n < 0) {
                if (!(sAvisado & (1ull << idx))) {
                    sAvisado |= 1ull << idx;
                    fprintf(stderr, "F8 historia: %04lx:%ld no entra en 360px/5 lineas; queda el original\n",
                            (unsigned long)pk, idx);
                }
            } else {
                memcpy(sLinea[idx], tmp, (size_t)(n + 1) * sizeof(tmp[0]));
                sTiene[idx] = 1;
            }
        }
next:
        line = (nl != NULL) ? nl + 1 : NULL;
    }
}

/* Se llama en lugar de BtlScript_GetText: devuelve la traduccion o el puntero original. */
uint32_t Port_HistoriaLinea(int32_t linea, uint32_t original) {  /* el game C lo declara s32 */
    if (linea < 0 || linea >= HIST_LINEAS || !sTiene[linea]) return original;
    return (uint32_t)(uintptr_t)sLinea[linea];
}
```

Notas de implementación:

- `sLinea` es estático, alineado a 4 y vive en el BSS del host (~0x40C8xxxx, < 4 GB): el juego lo
  puede usar como puntero de 32 bits. **No** usar `malloc` para el buffer que se devuelve.
- Si se quiere blindar contra un cambio de pack con texto viejo todavía en la cola de fuentes,
  usar dos generaciones de `sLinea` (128 KB) y alternar en `Port_HistoriaPack`; no es necesario
  para la primera prueba.
- El `sArchivo` de 2 MB alcanza para ~2.587 líneas; si el archivo es más grande, se trunca (mejor
  avisar por stderr).
- El texto nuevo **no lleva BOM**; el drawer no lo necesita. Sí debe terminar en `U+0000`.

---

## 7. Lo que no pude confirmar / queda para la corrida

1. **Nada ejecutado**: no compilé, no instalé, no abrí el juego. El diff está razonado sobre el C y
   el asm; falta verlo en pantalla.
2. **El ancho real del globo**: 359 px es el máximo de las líneas originales, no el scissor del
   prim. Si el globo recorta antes, el límite efectivo sería menor; el check tool y la corrida lo
   ajustan.
3. **La cantidad de packs realmente pedidos**: F8 contó 535 GSC con ids de texto; el rango tiene
   553 entradas. El log de la sonda dice exactamente qué `(pack,linea)` pide el juego.
4. **La fuente en el drawer de historia**: `Font_FindGlyph` busca en 8 fuentes; `’`/`…` están en
   font1. No vi el render de un `’` en el globo, pero el mecanismo es el mismo que usa el juego
   para los 17 `’` que ya traen los packs originales.
5. **El `0x54C` y los demás recursos**: los conteos salen de descomprimir el AFS; no rastreé todos
   los llamadores (sí el de `0x54C` por `3EC690`). Para una traducción completa hay que hacer el
   mismo trabajo de enganche por tabla.
6. **`0x545`/`0x546`/`0x553`**: el barrido encuentra tablas UTF-16 con el formato de offsets, pero
   no confirmé en código qué pantalla las usa. No las incluyo en el alcance de este hook.

---

## 8. Evidencia y artefactos (sólo lectura)

- Cadena del comando: `src/auto/m2c_2A70F8.c:6-10`, `port/eq/2A3A98.c:8-13`,
  `port/eq/100ED0.c:28-43`, `port/eq/100FC8.c:53-95`, `port/eq/2AB1A0.c:72,77`,
  `port/eq/2AB488.c:71,76`, `port/eq/2AB6F8.c:26,33`.
- Lector: `src/battle/btl_script_2A3AD0.c:101-105`; llamadores `port/eq/2A38C0.c:64,66` y
  `port/eq/2A7650.c:69`. Búsqueda de `jal 0x2A3AD0` en `disc/SLUS_214.41.rom`: 3 hits
  (0x2A39A8, 0x2A39C8, 0x2A777C); 0 en `disc/DBZP.BIN`.
- `gBtlScript = 0x003B0F3C` en `port/build/full/link.ld:6122`; `textFile` en `+4`
  (`include/battle/btl_script.h:96-99`); único `sw` a `0x3B0F40` en `asm/cod/1A3A94.s:28`
  (`func_002A3A98`).
- Pack 0x319 en RAM: `BT2-test/logs/vivo/20261106-200837_ram1_f3168.bin`; `textFile=0x109E7C0`,
  `count=10`, offsets y línea 0 ya citados. Registro 0 del globo en `0x3B0F7C` con `+1 = 0`.
- Barrido de packs y métricas: `/tmp/opencode/story_layout.py` (no escribe en el proyecto; lee
  `gamedata/DATA/ZS2US_1.AFS`). Tablas de otros recursos: `/tmp/opencode/find_tables.py` y los
  `e54c_s0.raw`, `e550_s1.raw`, `e553_s2.raw`, etc. (extraídos con `f3_lz.py`).
- Fuente: `0x542` cruda; `Fnt4` en `+0x40` (170 glyphs) y `+0x89C0` (425 glyphs); `0x2019`,
  `0x2026`, `0x3000` presentes en font1; `0x2014` ausente.
