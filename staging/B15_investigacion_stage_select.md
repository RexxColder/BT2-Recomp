# B15 — Selección de mapa: falta la vista previa grande del escenario

Investigación de solo lectura (2026-11-11). No se modificó nada del proyecto ni se lanzó el juego.
Estado: **no hay evidencia suficiente para un arreglo**. Abajo está lo que sí se pudo fundamentar, lo que no,
y el dato que falta para cerrarlo.

---

## 1. Síntoma y reproducción

Del reporte del usuario (`BUGS_ABIERTOS.md:20`, `BT2-Recomp/docs/bugs_open.md:437-441`):

- En la pantalla de selección de escenario (Dueling / Free Battle: elegir luchadores y después el mapa), la
  referencia de PS2 muestra a la **izquierda una imagen grande del escenario elegido** (detrás del panel) y a la
  **derecha una columna de miniaturas**.
- En el port sale la columna de miniaturas, pero la vista previa grande **no aparece o queda como una franja
  borrosa**.
- Las capturas originales del reporte (`BT2-test/referencia/mapsel_ref1.png`, `mapsel_ref2.png`,
  `mapsel_port.png`) **no están en este árbol**: `BT2-test/referencia/` no existe. Tampoco hay video ni F9 de
  esa pantalla (ver §4).

Pasos para reproducir (los del menú del juego): Menú principal → Dueling/Free Battle → elegir personaje(s) →
pantalla de escenario. Es la misma pantalla donde en su momento se vio "FPS disparados / control acelerado"
(`bugs_open.md:442`).

---

## 2. Cadena de código de la vista previa (en el original)

La única descripción precisa que hay en este repo está en las cabeceras del decomp matching, que describen el
objeto **CharSel** (selección de personaje / escenario / música de los modos versus). No hay implementación
`.c` en el port (ver §3), así que la cadena se puede dar a nivel de estructura y de funciones declaradas, no
de líneas de implementación.

### 2.1 El objeto y el estado del escenario

`include/menu/menu_d.h:7-9`:

```
 * Menu overlay DBZP.BIN, 0x342190..0x348D78: ONE object, the character / stage / music select screen of the
 * versus modes ("CharSel"; names are guesses), src/menu/menu_c_e.c.
```

`include/menu/menu_d.h:100-111` — `CharSelStage`:

```
/* 0x00 */ s32 col;        /* cursor column in the stage grid (6 columns) */
/* 0x04 */ s32 row;
/* 0x08 */ s32 chip[2][6]; /* stage ids on the six chips of the reel */
/* 0x3C */ s32 stage;      /* stage id under the cursor: picture file 0x39D + stage */
/* 0x40 */ s32 state;      /* step of the stage / music choice (CharSel_Input) */
/* 0x44 */ s32 mask;       /* non-zero while the stage chips are hidden */
/* 0x4C */ s32 bgm;        /* index in the music list */
```

### 2.2 De dónde sale la imagen grande

`include/menu/menu_d.h:142-165` — campos del objeto `CharSel`:

```
/* 0x0018 */ void *stageFile;           /* 0x3B800 bytes: compressed stage picture */
/* 0x001C */ MTexRes *stageRes[2];      /* 0x43000 bytes each: unpacked, two buffers for the cross fade */
/* 0x0030 */ u32 *stagePack;            /* section 46: 38 texture lists */
/* 0x0110 */ MTexRes *bg[2];            /* stage picture drawn behind: new, old */
/* 0x0304 */ s32 stageState;            /* CHARSEL_LOAD_: the stage picture loader */
/* 0x030C */ s32 stageBuf;              /* which of stageRes the next picture goes to */
/* 0x37F0 */ s32 bgAlpha[2];            /* of bg[0] / bg[1], 0..0x80 */
```

`include/menu/menu_d.h:206`:

```
#define CHARSEL_STAGE_FILE 0x39D  /* + stage id */
```

Es decir: la vista previa grande es un **MTexRes** (imagen ya descomprimida) guardado en `bg[0]/bg[1]`, con
dos buffers para hacer el cross-fade al cambiar de escenario (`bgAlpha[2]`), que se dibuja **detrás** del
panel. Los thumbnails de la columna derecha no son imágenes sueltas: salen de `stagePack`, la **sección 46**
del pack del menú, con **38 listas de texturas**. El id de la imagen del escenario es `0x39D + stage`.

### 2.3 Quién la crea, la llena y la dibuja

Las funciones están declaradas en `include/menu/menu_d.h:222-231`:

```
void CharSel_SetStageChips(void);
void CharSel_UpdateFaceLoad(void);
void CharSel_RequestFace(s32 side);
void CharSel_UpdateStageLoad(void);   <-- llena stageRes[]/bg[] (máquina de estados)
void CharSel_RequestStage(void);      <-- pide el archivo 0x39D + stage
void CharSel_Draw(void);              <-- dibuja, entre otras cosas, bg[0]/bg[1]
void CharSel_Update(void);
void CharSel_Input(s32 *running);
s32 CharSel_Run(s32 section);         <-- frame loop (0x348710..0x348D78, menu_e.h:10-14)
```

Estados del loader (`menu_d.h:196-203`): `CHARSEL_LOAD_REQUEST=1`, `READ=2`, `UNPACK=3`, `IDLE=4`,
`ABORT=5`, `RESTART=6`. `stageState` y `faceState` comparten la cola de pedidos de archivo y se turnan
(comentario en `menu_d.h:195-196`).

**Lo que no se puede dar**: la línea exacta de `CharSel_Draw` que arma el quad de `bg[]`, porque el archivo
`src/menu/menu_c_e.c` **no existe en este repo**. El port sólo conserva las cabeceras.

---

## 3. Estado en el port (evidencia negativa, exhaustiva)

Busqué el objeto CharSel y su loader en todo el árbol del port. **No está traducido**:

| Búsqueda | Resultado |
|---|---|
| `find . -name "menu_c_e.c"` / `src/menu/` | no existe en `BT2-Port` (sólo `include/menu/*.h`) |
| `port/eq/34*.c` | **no hay ningún archivo** que empiece con `34` (6.253 `.c`, rango 100000..4211D8) |
| `port/funcmap.csv` | **0** funciones en `0x0034xxxx` (`grep -c "0x0034"` = 0) |
| `port/build/recomp/register_functions.cpp` | **0** entradas `0x34xxxx` (no hay función recompilada en ese rango) |
| `grep -rn "gCharSel"` (`.c`) | 0 resultados (sólo aparece en `include/menu/menu_d.h` / `menu_e.h`) |
| `grep -rn "0x39D|0x3B800|0x43000|stagePack"` en `port/eq` | sólo `port/eq/3FC8B8.c:203 return 0x430000` (otra cosa, un tamaño 0x430000) |
| strings del bloque CharSel del DBZP (`0x4278c0`: `fr_menu_chrsel`, `mc_item_off_%d`, `mc_musicprogram_%d`) | **ningún** `.c` de `port/eq` las usa |

Además, el renderer tiene una referencia **muerta** a ese archivo:

`port/full/gs/gs_draw.c:29-38`:

```
/* Stage-name overlay: defined here (C) so both the renderer (gs_gpu.c) and the game's menu (menu_c_e.c) can
   reach them without C++ name mangling. */
volatile int gUiNameIdx = -1;
...
```

`gUiNameIdx`/`gUiPresent*` **no se escriben desde ningún `.c` del árbol** (sólo se leen en `gs_gl.c:1116-1118`).
Es decir: en algún momento se esperaba integrar `menu_c_e.c` para el cartel del escenario y esa integración
**no está**.

### 3.1 Dónde caen las direcciones del header

`readelf -S disc/SLUS_214.41` muestra que `0x342190` cae en **`.data`** (vaddr `0x0033F400`, tamaño `0x2CD44`),
no en `.text`. Los bytes ahí son una tabla de punteros, no código. El overlay que el port **sí** carga
(`DBZP.BIN`, base **0x3B3100**; comprobado en el asm original `0x100340: lui s2,0x3b` + `0x100348:
addiu a1,s2,12544` = `0x3B3100`, y en `port/eq/3B3100.c`) no contiene esas direcciones. Por lo tanto el
CharSel del decomp, si el juego lo ejecuta, vive en un **módulo/overlay cargado a una dirección fija
(0x33F400) que el port no traduce ni figura en su tabla de funciones**.

Consecuencia: **el port no puede estar ejecutando el `CharSel` que describen las cabeceras**. La pantalla que
el usuario ve debe ser otra implementación del menú (DBZP 0x3F.. / 0x3C.. / 0x3D..). Busqué en todas ellas una
carga/dibujo de imagen grande de escenario y **no encontré ninguna**:

- `func_003F9300` (modo 0xA; `port/eq/3F9300.c:42`) es el grupo de menú que tiene el char select de dos
  jugadores `func_003F16E0` (`port/eq/3F16E0.c`). Ese draw sólo pone textos, colores, cursores y el **nombre**
  del escenario (`"mc_couse_name"`, `3F16E0.c:96-105`); no carga ni dibuja una imagen grande.
- `func_003F0800` (`port/eq/3F0800.c:38`) es el loader de **retratos**: pide `valor + 0x56B` (confirmado en
  BT2: los AFS 0x56B.. tienen tamaños 0x14600/0x16C20, compatibles con un retrato comprimido). No hay ningún
  loader análogo para `0x39D + stage` ni buffers de 0x43000.
- `func_00400AC0` (torres/nubes de Ultimate Battle), `func_003F6778`/`func_003C6260` (selección de curso),
  `func_003CB1D0`/`func_003D09C0` (battle setup) tampoco tienen imagen grande de escenario.

No pude determinar con certeza **cuál** de esas pantallas es la que el usuario fotografió, porque no hay
captura/F9/video de ese momento (§4). Pero, sea cual sea, en el árbol actual **no existe el código que crea el
quad de la vista previa**.

---

## 4. Logs y volcados disponibles: no sirven para B15

Revisé `BT2-test/logs/vivo/` (243 archivos). Todas las sesiones con menús tienen este patrón:

```
modo 4 (menu_principal) -> modo 6 -> modo 7 -> modo 8 -> modo 7 -> BATALLA modo 7
```

**Ese 6/7/8 no es Dueling: es Dragon Adventure.** Lo verifiqué con los videos de las sesiones
`20261106-200837`, `20261106-202444` y `20261106-223353`: el modo 7 muestra la lista de sagas ("Saiyan Saga",
"Kakarot") y el modo 7 final entra a una pelea con cinemática de historia. No hay ninguna sesión grabada que
llegue a la selección de escenario de Dueling/Free Battle.

Volcados F9/F10 revisados y descartados (todos posteriores a la pelea o de otro modo):

- `20261106-200837_ram1..5_f3168..f9452` (la batalla de historia)
- `20261106-202444_ram1..8_f2914..f4124`
- `20261106-203244_ram1..3_f3880..f4595`
- `20261106-210306_ram1..3`, `20261106-220305_ram1..4`, `20261106-232531_ram1..2`
- `20261107-003926_ram1..5` (entrenamiento), `20261107-010126_ramkey1..5` (torneo),
  `20261107-013859_ramkey1..3` (entrenamiento), `20261111-111320_ramkey1_f6110` (pelea)

No hay ningún `RAMDUMP`/`ram*` tomado entre la elección de personajes y el inicio de la pelea de un Dueling.

Tampoco hay `dropped by site` de esa pantalla: el contador se imprime sólo con `BT3_GS_VERBOSE`
(`port/full/gs/gs_gl.c:885-887`, `gs_gpu.c:518-520`) y los `.log` de menús no lo tienen activo.

---

## 5. Causa más probable (con lo que hay)

**El port no tiene traducido el objeto que crea y dibuja la vista previa** (el `CharSel`/`TeamSel` del menú
versus: `CharSel_RequestStage` + `CharSel_UpdateStageLoad` + el draw de `bg[0]/bg[1]`). No es un problema de
FPU ni de punteros: no hay código que tocar. La evidencia fuerte es la ausencia total de:

- `src/menu/` y `menu_c_e.c` en el árbol,
- funciones en `0x34xxxx` en `port/eq`, en `funcmap.csv` **y** en la tabla de PS2Recomp,
- `gCharSel`, `0x39D`, `0x3B800`, `0x43000`, `stagePack` y los strings del bloque CharSel en cualquier `.c` del
  port.

Eso explica el síntoma "sale el marco/thumbnails pero no la imagen grande": la parte de UI que sí existe
(probablemente dibujada por el otro camino de menú, o por capas de script del pack) se ve, y la parte que
dependía del loader del escenario no se ejecuta/nunca se creó.

**Segunda posibilidad, no descartable**: que la pantalla que corre el port sea una implementación distinta
(0x3F..) que directamente **no incluye** el preview en su `Draw`. En ese caso el arreglo sería agregar el
loader/draw que falta, no corregir uno existente.

**Lo que NO sostiene la evidencia**:

- *"El renderer descarta el pase"*: los 6 sitios de descarte de `gs_draw.c:530-612` son para vistas de 16
  bits (site 0), CLUT de profundidad (1), formatos PS2/zbp (2), work buffers viejos (3), switches de efectos
  del usuario (4) y buffer sampleado mientras es target (5). Un quad texturado normal subido a VRAM no cae en
  ninguno. Sin contadores `dropped by site` de esa pantalla, culpar al GS es adivinar.
- *"Textura que no se carga/decodifica"*: posible sólo si el quad existe; no hay volcado para verlo.
- *"Quad de tamaño 0"*: posible sólo si el `Draw` existe; no hay código.
- *"Dato PS2 usado como host"*: no hay dirección de preview que seguir.

---

## 6. Qué dato falta (y cómo obtenerlo)

El dato que cierra B15 es **un F9 + video en la pantalla de selección de escenario de Dueling/Free Battle**.
Con `BT2-test/jugar.sh` el F9 ya vuelca 32 MB de RAM (`BT2_F9_RAM` está seteado en `jugar.sh:14`) y el video
se graba en `.mp4`.

Pasos concretos:

1. Reproducir: Menú → Dueling/Free Battle → elegir personajes → **quedarse en la pantalla de escenario** (con
   la vista previa faltante a la vista) y apretar **F9** ahí, sin entrar a la pelea.
2. Repetir con `BT3_GS_VERBOSE=1` para ver `dropped by site` de ese cuadro.
3. Con el F9, buscar en RAM el objeto del menú:
   - `gCharSel` del decomp está en `0x3B38D4`; en el port el equivalente puede ser otro puntero. Buscar un
     bloque con `stageState` (1..6) y dos punteros `bg[0]/bg[1]`, o los dos buffers de 0x43000.
   - Si `stageState`/`bg[]` no existen o están en 0, el código que crea la preview no corrió (confirma §5).
   - Si existen pero `bgAlpha=0` o el tamaño del quad es 0, es un bug del `Draw`/loader traducido.
4. Si se puede, build con traza (`BT2_TRACE_BUILD=1`, `port/build/full_trace/`) y ver qué direcciones guest se
   ejecutan al entrar a esa pantalla. Eso dice si es `3F16E0` u otro objeto, y si hay llamadas a `0x34xxxx`
   (que en el port no tienen traducción: sería un hallazgo grande).
5. Comparar el draw contra el asm original de esa función (una vez identificada) y recién ahí proponer el
   arreglo.

---

## 7. Cambio propuesto

**No propongo un diff de arreglo**: no hay una función identificada en el port que cree/dibuje la vista previa,
y cualquier cambio sería inventar. Tampoco propongo un parche de "contención" (por ejemplo, forzar un fondo)
porque taparía el síntoma sin causa.

Cuando llegue el F9 del punto 6, el arreglo probable es uno de estos dos, y se decide con ese dato:

- **Si el objeto del menú existe pero no tiene `bg[]`**: portar el loader que falta (`CharSel_RequestStage` /
  `CharSel_UpdateStageLoad`) y el draw de `bg[]` desde el decomp matching, adaptando direcciones al port; o
- **si el objeto no existe**: agregar el `CharSel`/`TeamSel` completo al port (es el trabajo grande), o al
  menos el camino de la imagen grande.

---

## 8. Descartado explícitamente

- **F9 de menús existentes**: no hay ninguno de la pantalla de escenario de Dueling; los `modo 6/7/8` son
  Dragon Adventure (verificado con video). No sirven.
- **Renderer (GS)**: sin `dropped by site` de esa pantalla y con sitios de descarte que no aplican a un quad
  texturado normal, no hay evidencia. No se descarta al 100 %, pero no es la hipótesis principal.
- **Pack de texturas (`gs_texpack`)**: es opcional y sólo reemplaza texturas; no puede hacer desaparecer un
  dibujo.
- **FPU/NaN, punteros de 32 bits, argumentos perdidos**: no hay código de la preview que auditar; no aplica
  todavía.
- **`0x39D` como constante literal**: no aparece en ningún `.c` del port ni en el asm de DBZP/SLUS que
  desensamblé; el id puede venir de una tabla, así que no se puede usar como pista de búsqueda.
