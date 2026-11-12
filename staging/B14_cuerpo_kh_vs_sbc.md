# B14 — Cuerpo del Kamehameha vs Special Beam Cannon (KH vs SBC)

Fecha: 2026-11-11. **Sólo lectura**: no se editó código, no se compiló, no se corrió el juego.
Fuentes: `port/eq/*.c`, `src/auto/*`, `port/build/recomp/*.cpp`, `port/build/full/tables.c`,
`/tmp/opencode/full.asm` (asm del ELF), log `BT2-test/logs/vivo/20261111-134107.fight.log`,
volcados PCSX2 `/tmp/opencode/ps2save_kh/eeMemory.bin` y `ps2save_sbc/eeMemory.bin`, y volcados del port
`20261107-010126_ramkey*.bin`, `20261107-010907_ramkey*.bin`, `20261107-011812_ramkey1_f4596.bin`.

---

## 0. Resumen (y dos correcciones al contexto que me pasaron)

1. **El tipo 7 NO es un EftSprite.** `func_00150700` → `EftChain2_Create` → clase **0x3427E8**
   (`port/eq/150700.c`, `src/battle/xc_1B3378.c:39-43`). El sprite largo del SBC (layers 5, len 120) lo crea
   **el tipo 5, slot 0** (EftSprite, clase `0x3434F0`): `port/eq/1501C0.c:31` → `1E70B0` → `1E66A0`
   (`BtlTaskList_AddTail(D_003878EC, D_003434F0)`), y en el volcado original aparece la tarea con
   `len 120 / layers 5` (ver §3). El despacho del tipo 5 slot 0 en el SBC es el frame 11645
   (`20261111-134107.fight.log:19447` y siguientes).
2. **En el KH no existe ningún sprite largo.** En el volcado original del KH las 4 tareas sprite (todas muertas,
   en la freelist) tienen packs `0x1bd0f40` (len 30/layers 2), `0x1bd1158` (len 30/layers 4),
   `0x1bd0f40` (len 15/layers 1) y `0x1bd0f40` (len 1/layers 4). El pack largo del SBC (`0x1bd1370`) **no
   aparece en el dump del KH**. En el port pasa lo mismo (packs `0x1bcef00/0x1bcf118`, largos máximos 45).
   El slot 0 del KH (**sí** existe: `SPRSTP t 0x1a55580` en el frame 10632 y `SPRKILL` en 10634) usa una
   animación corta, no la de 120.

**Conclusión corta:** el cuerpo del SBC es el sprite del tipo 5 slot 0; **no encontré ninguna de las 8 tareas
de efecto de la tabla del KH** (0,1,2,3,5,8,10,11) **cuya geometría pueda ser el cuerpo**. El único efecto
exclusivo del KH es el tipo 0, pero su
geometría es un *burst* de 8 pétalos de ~25 unidades, no el cono largo. La evidencia sigue apuntando a la
hipótesis anterior: **el cuerpo del KH es un mesh/modelo de la técnica**, fuera del sistema de slots.
No pude identificar la función que lo dibuja; no hay base para un arreglo todavía (§6).

---

## 1. Cadena de cada tipo del KH (quién crea qué clase)

Despachador `func_001513D0` (`port/eq/1513D0.c`): el caso `type` está en las líneas 182–238.
Cada spawner recibe `p2`/`pass` y guarda el handle en un slot; la creación real es `BtlTaskList_AddTail`.

| tipo | spawner | crea (llamada) | clase (tabla) | update / draw |
|---|---|---|---|---|
| 0 | `func_0014F7D8` (`14F7D8.c:12-32`) | `func_00181760` → `BtlTaskList_AddTail(D_0038779C, D_00341E70, blk)` (`src/auto/m2c_181760.c:7-12`) | **0x341E70** | 0x181990 / 0x181A18 (draw vacío; el trabajo lo hacen los hijos) |
| 0 (hijos) | `func_001818D0` (init) → `func_00181A20` → `func_00180440` | `BtlTaskList_AddTail(*(D_00387798+0xC), D_00341E40, frame)` (`port/eq/180440.c:12`) | **0x341E40** ×8 | 0x180890 / **0x1809F0** |
| 1 | `func_0014F8E0` (`14F8E0.c:26+`) | `func_001CC978` → `AddTail(D_003878C4, D_00342D98)` (`src/battle/xu_1CC978.c`) | **0x342D98** (EftMod1CC) | 0x1CC770 / 0x1CC808 |
| 2 | `func_0014FB50` (`14FB50.c:40`) | `EftRibbon_Create` → `AddTail(D_003878A0, D_003429B0)` | **0x3429B0** (EftRibbon) | 0x1C6E40 / 0x1C6F90 |
| 3 | `func_0014FD40` (`14FD40.c:40`) | `EftChain_Create` → `AddTail(D_00387820, D_00342418)` (`src/battle/xu_1A4818.c`) | **0x342418** (EftChain) | 0x1A45B0 / 0x1A4658 |
| 5 | `func_001501C0` (`1501C0.c:31`) | `func_001E70B0` → `func_001E66A0` → `AddTail(D_003878EC, D_003434F0)` (`port/eq/1E66A0.c:11`) | **0x3434F0** (EftSprite) | **0x1E6EF8 / 0x1E6FB8** |
| 8 | `func_0014F320` (`14F320.c:64/97`) | `EftRay_Create` / `_CreateByValue` | **0x342818** (EftRay) | 0x1B3E68 / **0x1B4240 → 0x1B45E0** |
| 10 | `func_00150990` (`150990.c:52`) | `EftPtcl3_Create` | **0x3428F0** | 0x1BC188 / 0x1BC230 |
| 11 | `func_00150990` (ctx+0x1958) | idem | **0x3428F0** | idem |
| 7 (SBC) | `func_00150700` (`150700.c`) | `EftChain2_Create` | **0x3427E8** | 0x1B2FD0 |
| 6 (SBC) | `func_001503E0` (`1503E0.c:32`) | `EftQuad_Create` | **0x341FB8** | 0x18C4E8 / 0x18CAC8 |
| 12 (no KH/SBC) | `func_00150C68` | `func_0018BA90` → `AddTail(D_003877B4+0x7AF4, D_00341F78)` (`18BA90.c`) | **0x341F78** (rayo) | 0x188218 / 0x188850 |

Tablas de clase verificadas en los dos volcados (base de 6 punteros; el primer word es update y el sexto draw):

```
0x341E40: 180890 180770 180878 00000000 1809D8 1809F0
0x341E70: 181990 1818D0 181960 00000000 181978 181A18   (181A18 = stub: 8 bytes, jr ra)
0x342D98: 1CC770 1CC590 1CC760 1CC7E8 1CC7F0 1CC808
0x3429B0: 1C6E40 1C6CF8 1C6E20 1C6F70 1C6F78 1C6F90
0x342418: 1A45B0 1A4508 1A4590 1A4650 1A4658 1A4670
0x3434F0: 1E6EF8 1E6E38 1E6ED8 00000000 1E6FA0 1E6FB8
0x342818: 1B3E68 1B3DB8 1B3E48 00000000 1B4228 1B4240
0x3428F0: 1BC188 1BC0D0 1BC168 1BC210 1BC218 1BC230
0x3427E8: 1B2FD0 1B2E68 1B2F70 1B31B8 1B31C0 1B31D8
0x341FB8: 18C4E8 18C3C8 18CBA8 18CA90 18CB30 18CAC8
0x341F78: 188218 187EC0 1889F0 188838 188978 188850
```

> Ojo con la base: el rayo de Piccolo es `0x341F78` (no `0x341F60`); `0x341F60` son 0x18 bytes previos
> (datos de otra tabla). Lo mismo con `0x341E70` vs `0x341E40`.

---

## 2. EftSprite: qué son `layers` (+0x21CC) y `len` (+0x21C4)

- El update `func_001E6EF8` (`src/auto/m2c_1E6EF8.c:20-25`) sólo **lee** para el log:
  `anim = work+0x40`, `time = *(f32*)(anim+0x21C8)`, `len = *(f32*)(anim+0x21C4)`,
  `layers = *(u8*)(anim+0x21CC)`. `anim` = `work+0x50` (lo fija la init `1E6E38`).
- **Quién los escribe:** la init de la animación `func_001DF840` (recomp, `func_001DF840_0x1df840.cpp`):
  - línea 130: `swc1 f0, 0x21C4(s0)` ← `*(f32*)(res+0x1A4)` = **`len` (duración en frames)**;
  - línea 136: `sw zero, 0x21C8(s0)` = `time`;
  - línea 139: `sb v0, 0x21CC(s0)` ← `*(u8*)(res+0x1A0)` = **`layers` (cantidad de capas)**;
  - líneas 196-222: **bucle `s3` de 0 a `layers-1`**, y por cada capa llama `func_001E0C80(anim, ...)`
    (parsea/arma la capa). O sea, `layers` es un **conteo de capas**, no un factor de repetición.
- **Quién los usa para dibujar:** `EftSprite` draw = `1E6FB8` → `1E6B30` (switch por `work+8`/`work+6`);
  las formas 0/1/6 llaman `func_001DFD28(anim, ...)` = **tail-call a `func_001DFCA0(anim, anim+0x21C0, ...)`**
  (`func_001DFD28_0x1dfd28.cpp:32-38`). Es decir, **el draw dibuja UNA capa** (la apuntada por
  `anim+0x21C0`); el que recorre las `layers` es el update/anim (`1DF940`/`1DFA50`), que llama al draw una
  vez por capa. **`len` no estira el quad**: es el largo de la animación en frames; `time` avanza 1/frame.
- Por eso el sprite del SBC con `layers=5, len=120` son **5 quads** (5 capas de un pack V000) durante
  **120 frames** (2 s a 60 Hz), no "un quad repetido a lo largo de 120".

Verificación del layout con el dump original: `anim+0x21C0` = puntero al pack V000 (ej. `0x1bd1370`),
`+0x21C4` = len, `+0x21C8` = time, `+0x21CC` = layers. Todo consistente entre el original y el port.

---

## 3. Comparación KH vs SBC en los volcados (original y port)

### 3.1 Inventario de clases en los dumps originales (KH vs SBC)

Búsqueda de `cls` (task+0x28) contra las tablas conocidas, en `0x100000..0x1FF0000`:

| clase | KH | SBC | qué es |
|---|---:|---:|---|
| `0x341E70` | **1** | **0** | manager del tipo 0 (8 hijos) |
| `0x341E40` | **8** | **0** | cada capa del tipo 0 (draw 1809F0) |
| `0x342D98` | 2 | 2 | EftMod1CC (tipo 1) |
| `0x3429B0` | 1 | 1 | EftRibbon (tipo 2) |
| `0x3427E8` | 1 | 3 | EftChain2 (tipo 7, SBC) |
| `0x342818` | 1 | 1 | EftRay (tipo 8) |
| `0x3428F0` | 7 | 7 | EftPtcl3 (tipos 10/11) |
| `0x3434F0` | 4 | 3 | EftSprite (tipo 5) |
| `0x341FB8` | 1 | 2 | EftQuad (tipo 6, SBC) |
| `0x341F78` | **0** | **0** | rayo tipo 12 / 195250 (no se crea en ninguno) |

El **único par de clases que existe en el KH y no en el SBC es el tipo 0** (`0x341E70` + 8×`0x341E40`).
Eso es lo que hay que mirar si el cuerpo del KH es un efecto.

### 3.2 Tipo 0 en detalle (el candidato KH-only)

- Manager `0x341E70` (original, task `0x19c9680`): work `0x19c9900`; en `work+0x00..0x1F` hay **8 punteros**
  a tareas `0x19ca100/140/180/1c0/200/240/280/2c0` (clase `0x341E40`). Posición del manager en `+0xA0`:
  `1057.7385, -349.1014, 239.9182`. `+0xB0 = 1.8` (escala que el update copia a cada hijo en `+0x28`).
- Cada hijo tiene un registro de 0x30 bytes del pack en `0x00CC9C00` (`+0x2D0 = 8`), idéntico en el dump
  del port (`0x00CC9040`):

```
rec0: ang -1.42  vel 0.02  largo 13.60  ? 0.10  ancho 6.95  ...  color AA C1 FF 3F  (170,193,255,63)
rec1: ang 71.06  vel 0.02  largo 13.35  ...        ancho 5.65
rec2: ang 143.56 vel 0.02  largo 14.85  ...        ancho 5.60
rec3: ang -148.67 ...      largo 15.65             ancho 4.90
rec4: ang -73.76 ...       largo 18.90             ancho 6.00
rec5: ang -99.86 ...       largo 17.60             ancho 2.00
rec6: ang 29.36  ...       largo 18.55             ancho 3.00
rec7: ang 130.91 ...       largo 17.10             ancho 2.00
```

- El draw `0x1809F0` (`port/eq/1809F0.c:8-12`) hace: si `IsHidden(work+0x58, work+0x4C)==0` y
  `flags&1`, llama `0x180A40`. `0x180A40` arma 4 puntos desde `D_0036E870` (plantilla
  `(-1,-1),(1,-1),(-1,0.01),(1,0.01)`), los rota por `work+0x10`, los traslada por
  `(work+0x2C*work+0x24, work+0x38*work+0x20, -10*work+0x20)` escalado por `work+0x28` (1.8)
  (`port/eq/180A40.c:78-84`), y los manda por `180D98` → `181040` (GIF).
- **Tamaño real:** el quad es unitario; la traslación máxima es `13.6 * 1.8 ≈ 24.5` unidades y el ancho
  `6.95` (con `*0.5`). Son 8 pétalos de ~25 unidades alrededor de las manos: un **flash/burst**, no el cono
  de ~300 unidades del video. Por eso **no lo considero el cuerpo**.
- **Dónde viven las 8 capas:** `180440` las agrega a `*(D_00387798 + 0xC)` (la lista del sistema de efectos
  de clima/escenario), no a `manager->child`; en los dumps, la lista (`0x19ca0c0` orig / `0x19c8380` port)
  tiene `parent = 0x19beb00 / 0x19bcdc0`, es decir cuelga de otra tarea del árbol. El draw del manager
  (`0x181A18`) es `jr ra` (stub): **el dibujo lo hacen los 8 hijos**. Esto importa para el diagnóstico: si el
  pase de draw no llega a esa lista, los hijos no se dibujan aunque su update corra y estén `updated=1`.

### 3.3 El sprite largo del SBC (tipo 5 slot 0)

Volcado original (tareas sprite, work+0x40 = anim):

| task | pack (`anim+0x21C0`) | time | len | layers |
|---|---|---:|---:|---:|
| `0x1a572c0` (KH) | `0x1bd0f40` | 31 | 30 | 2 |
| `0x1a57300` (KH) | `0x1bd1158` | 31 | 30 | 4 |
| `0x1a57340` (KH) | `0x1bd0f40` | 16 | 15 | 1 |
| `0x1a57380` (KH) | `0x1bd0f40` | 2 | 1 | 4 |
| `0x1a572c0` (SBC) | `0x1bd1158` | 27 | 30 | 4 |
| `0x1a57340` (SBC) | `0x1bd1588` | 27 | 30 | 2 |
| `0x1a57300` (SBC, muerta) | `0x1bd1370` | 21 | **20** | **1** |

El `len 120 / layers 5` del SBC (log del port, frame 11647) es la **primera fase** de la tarea del pack
`0x1bd1370`: a los 2 frames de vida la anim está en `len 120, layers 5`; a los 17-21 frames ya está en
`len 20, layers 1` (el cuerpo se retrae). Es el mismo mecanismo que en el port: la tarea existe, está viva y
actualiza time/len/layers. **En el KH no hay ningún pack `0x1bd1370`** (ni en el original ni en el port).

### 3.4 Estado en el port: las tareas del KH se crean y se actualizan bien

Dump del port `20261107-010126_ramkey1_f3341.bin` (dentro del span del tipo 0, `3174..5888`):

```
mgr 0x19c7940 bits fe work 0x19c7bc0
  ch0..ch7 = 0x19c83c0/400/440/480/4c0/500/540/580   bits fe   flags 00000001 (activo)
  largo 13.60/13.35/14.85/15.65/18.90/17.60/18.55/17.10   ancho 6.95/5.65/5.60/4.90/6.00/2.00/3.00/2.00
  pack 0x00CC9040 = idéntico byte a byte al original 0x00CC9C00
```

O sea: **"no se crea" está descartado** para el tipo 0. También están creados el EftMod1CC (2), el ribbon
(1), el EftRay (1), los EftPtcl3 (7) y los sprites (2-4), con los mismos valores que el original.

---

## 4. Descartes (con el motivo)

| hipótesis | resultado |
|---|---|
| el cuerpo del KH es un EftSprite (layers 5 / len 120) | **falso**: en el KH no existe ningún pack con len 120/layers 5; los packs son de 30/15 frames y 1-4 capas (§3.3). El sprite del SBC sí es así. |
| el tipo 7 es el que crea el sprite del SBC | **falso**: tipo 7 = `EftChain2` (0x3427E8); el sprite del SBC es **tipo 5 slot 0**. |
| el cuerpo del KH es el tipo 0 (8 capas) | **no**: la geometría da ~25 unidades (8 pétalos), no un cono de ~300. Está creado y activo, pero es el flash. |
| el cuerpo es el EftRay (tipo 8) | **no**: en el dump tiene `count = 0x14` (20 rayos), cada quad de largo ~1 y radio ~190; es un anillo de chispas, no un cuerpo continuo. Además el draw real es `1B4240 → 1B45E0` (no `1B5400`, que es el lens/manager). |
| el cuerpo es EftMod1CC (tipo 1) | **no**: `res[1]=0` → forma 0 = `1CBA98`, **un solo sprite screen-space** con w=h=281.6 (KH) / 355.5 (SBC), rotado por `work+0x6C`. Es un glare cuadrado, no un cono 320×26. Existe en los dos ataques. |
| el cuerpo es el ribbon (tipo 2) | **no**: en los dos dumps el ribbon tiene **1 solo nodo** (head = node0, `next=1`), o sea un tramo degenerado. |
| el cuerpo es la cadena (tipo 3) | **no**: `EftChain2/EftChain` son bursts de tramos de vida corta (informe previo §4.7); en el SBC hay 3 y en el KH 1. |
| el cuerpo es el rayo `tipo 12` (clase 0x341F78) | **no se crea**: 0 tareas de `0x341F78` en los dos dumps; el KH no tiene filas de tipo 12 en la tabla. El camino `195250` sólo crea si `!IsInTechnique` (informe previo). |
| el cuerpo está en el renderer (descartado) | no hay descartes (`dropped by site` = 0) en las sesiones del ataque (informe previo). |
| el port no crea las tareas del KH | **falso**: dump `010126 ramkey1` con el tipo 0 activo y los 8 hijos con los mismos parámetros que el original. |

---

## 5. Conclusión

**(a) Qué dibuja el cuerpo del KH en el original:** con la evidencia disponible, **ninguno de los tipos de la
tabla de efectos del KH**. El SBC sí tiene un cuerpo de efecto identificable (tipo 5 slot 0, 5 capas, pack
`0x1bd1370`), pero el KH no tiene ningún pack/efecto con esa geometría. El único efecto KH-only (tipo 0) es
un burst de 8 pétalos de ~25 unidades. Por eliminación (y coincidiendo con el informe previo §6), el cuerpo
del KH tiene que ser un **mesh/modelo de la técnica** (dibujado por el renderer de modelos/personajes), no una
tarea de `BtlTask` del sistema de efectos. **No pude identificar la función de draw de ese mesh** con
lectura sola; haría falta un volcado de la lista de dibujos (F9 no la vuelca hoy) o buscar el mesh en los
datos del modelo de la técnica.

**(b) Por qué no se ve en el port:** no es "no se crea" (el tipo 0 y los demás están creados y activos, §3.4).
Tampoco pude probar que sea "se dibuja con parámetros en cero": el estado del tipo 0 en el port es idéntico al
del original. La parte que falta (el cono) **no es una tarea de efecto**, así que el problema está en el
camino del mesh/modelo o en la lista de dibujos. No tengo evidencia para afirmar cuál de los dos.

**Nota sobre el SBC (para no mezclar dos bugs):** el video del usuario
(`staging/B14_rayo_port_vs_orig.md` §2) dice que en el port **tampoco** se ve el cuerpo del SBC, aunque la
tarea sprite larga (pack `0x1bd1370`, 5 capas) **sí se crea y se actualiza**. Eso apunta a un problema de
**draw/textura del EftSprite** (o de las capas) en el port, distinto del KH (que no tiene ese sprite). No lo
pude confirmar con los volcados: en el buffer de paquetes del port busqué el tag `0xA0000007` + el TEX0
`0x2005400599302b00` y no apareció, pero el buffer es compartido con otros efectos y el momento del F10 no es
necesariamente el del último draw; **no es concluyente**. Si el usuario confirma que el SBC tampoco se ve,
la misma instrumentación de §6.1/§6.2 se puede replicar en `1E6FB8`/`1E6B30` para ver cuántas capas se
dibujan y con qué TEX0.

**(c) Arreglo:** no propongo un arreglo "a ciegas". Propongo **dos instrumentaciones TEMP** para cerrar el
diagnóstico (diff abajo, no aplicado):
1. `B14 T0DRAW` en `1809F0.c` y `B14 T0SEG` en `180A40.c`: confirma si el tipo 0 se dibuja y con qué tamaño.
   Si durante el KH no aparece `T0DRAW` estando los hijos con `flags&1`, el problema es el pase de draw;
   si aparece con puntos válidos y el cuerpo sigue faltando, el tipo 0 no es el cuerpo (confirma el mesh).
2. Un volcado de la **lista de dibujos** (o de los modelos de la técnica) durante el KH, para comparar el
   original con el port. Es la herramienta que falta; el F9 actual sólo da RAM + estadísticas.

Si el usuario quiere un experimento de una sola corrida: la instrumentación 1 es la más barata y decide entre
"draw del efecto" y "mesh".

---

## 6. Diff propuesto (diagnóstico, NO aplicado)

### 6.1 `port/eq/1809F0.c` — ¿se llama el draw del tipo 0?

```diff
--- a/port/eq/1809F0.c
+++ b/port/eq/1809F0.c
@@
 #include "common.h"
 
+void bt2_fightlog_note(const char *fmt, ...); /* TEMP B14 */
+
 s32 func_001267E8(s32 arg0, s32 arg1);
 void func_00180A40(s32 arg0);
 
 void func_001809F0(u8 *arg0) {
     u8 *p = (u8 *)*(s32 *)(arg0 + 0x38);
     s32 r = func_001267E8(*(s32 *)(p + 0x58), *(u8 *)(p + 0x4C));
 
+    { static unsigned n_; if ((n_++ & 15) == 0) /* TEMP B14 */
+        bt2_fightlog_note("B14 T0DRAW t %p flags %08x chr %d hid %d pos %.1f %.1f %.1f",
+                          arg0, *(u32 *)(p + 0x48), *(s32 *)(p + 0x58), r,
+                          *(f32 *)(p + 0x00), *(f32 *)(p + 0x04), *(f32 *)(p + 0x08)); }
     if (r == 0 && (*(s32 *)(p + 0x48) & 1) != 0) {
         func_00180A40((s32)p);
     }
 }
```

### 6.2 `port/eq/180A40.c` — tamaño y puntos del quad (una vez cada 256 llamadas)

Agregar arriba la declaración `void bt2_fightlog_note(const char *fmt, ...); /* TEMP B14 */` e insertar
**antes** del `func_00180D98(...)` de la línea 120 (después del bucle de 4 puntos):

```diff
@@
     y0 = y0 & 0xFF;
 
+    { static unsigned n_; if ((n_++ & 255) == 0) /* TEMP B14 */
+        bt2_fightlog_note("B14 T0SEG flags %08x len %.2f wid %.2f prog %.2f "
+                          "p0 %.1f %.1f %.1f p1 %.1f %.1f %.1f",
+                          S32AT(arg0, 0x48), F32AT(arg0, 0x38), F32AT(arg0, 0x2C),
+                          F32AT(arg0, 0x20),
+                          F32AT(sp, 0xF0), F32AT(sp, 0xF4), F32AT(sp, 0xF8),
+                          F32AT(sp, 0x100), F32AT(sp, 0x104), F32AT(sp, 0x108)); }
     /* 9th..13th arguments go to the stack at sp+0, +8, +0x10, +0x18, +0x20 (GUESS arity 13) */
     func_00180D98(4.0f, sp + 0xF0, sp + 0x170, a2u, a3u, t0u, t1, a2u, a3u, t0u, y0, (s32)(sp + 0x70),
                   S32AT(arg0, 0x50), S32AT(arg0, 0x60));
```

> Ambos son **TEMP B14**: se quitan cuando el bug se cierre. No cambian la lógica (sólo leen).

### 6.3 Qué mirar en el `fight.log`

- Durante los frames del KH (10619-10726 en la sesión 134107): si aparecen `B14 T0DRAW` con `flags & 1` y
  `B14 T0SEG` con `len ~13-19`, `wid ~2-7`, el tipo 0 **se está dibujando**. Entonces el cuerpo que falta
  **no es el tipo 0** y hay que ir al mesh (punto 2 de §5).
- Si **no** aparece `T0DRAW` durante el KH pero los hijos están activos (se ve en el dump de RAM con F10), el
  problema es el pase de dibujo de la lista de efectos: ahí sí hay un bug de port que se puede atacar
  (comparar el orden/`updated` de `BtlTaskList_Draw`, `src/battle/eft_ae_1F2D30.c:493-514`).

---

## 7. Evidencia reproducible (comandos usados)

```bash
# clases y tareas en los dumps (offset = dirección PS2)
python3 - <<'EOF'
import struct
d=open('/tmp/opencode/ps2save_kh/eeMemory.bin','rb').read()
for c in (0x341E40,0x341E70,0x3434F0,0x342818,0x3429B0):
    print(hex(c),' '.join('%08x'%v for v in struct.unpack_from('<6I',d,c)))
EOF

# sprite largo del SBC (work+0x40 -> anim; +0x21C4 len, +0x21C8 time, +0x21CC layers)
# task 0x1a57300 en ps2save_sbc: len 20, layers 1, pack 0x1bd1370

# pack de 8 capas del tipo 0: 0xCC9C00 (orig) / 0xCC9040 (port), +0x2D0 = 8, records de 0x30
```

Archivos de referencia:
- `port/eq/1513D0.c:182-238` (despacho), `14F7D8.c`, `1501C0.c:31`, `150700.c`.
- `port/eq/1E66A0.c:11`, `port/eq/1E70B0.c:25`, `src/auto/m2c_1E6EF8.c:20-25`.
- `port/build/recomp/func_001DF840_0x1df840.cpp:130-222` (len/layers y bucle de capas).
- `port/build/recomp/func_001DFD28_0x1dfd28.cpp:32-38` (draw de una capa).
- `src/auto/m2c_1E6FB8.c` (draw del sprite), `src/auto/m2c_1E6B30.c` (formas).
- `port/eq/1809F0.c`, `180A40.c`, `180D98.c`, `181040.c`, `180440.c`, `181A20.c`.

---

## 8. Lo que NO está verificado

- No vi el video de la sesión 134107; la forma/tamaño del cuerpo del KH sale del informe previo
  (`staging/B14_rayo_port_vs_orig.md`) y del análisis de geometría, no de una captura nueva.
- No pude probar que `1809F0`/`180A40` se llamen o no en el KH (por eso el diff de instrumentación).
- No busqué el mesh de la técnica en los datos del modelo; sólo descarté el sistema de efectos.
- La ausencia de tareas de la clase del rayo (`0x341F78`) en un dump no es prueba absoluta de que no existieran
  (el pool puede reutilizar/limpiar), pero en el caso de los sprites sí se conservan los packs, y el
  `0x1bd1370` del SBC no está en el KH.
