# B12 — Índice de sonido basura en la carga de una pelea de equipo (5v5)

Fecha: 2026-11-11. **Solo lectura**: no compilé, no ejecuté el juego y no toqué nada fuera de `staging/`
(los únicos archivos que leí del proyecto y de `BT2-test/logs` se listan en el anexo). El diff del final **no está
aplicado**.

## 0. Resumen para el orquestador (leer primero)

1. **El índice no viene de `101FD0` ni de `1031E0`.** Viene de `func_00104990` (estado 0), que abre tres archivos con
   `func_00100ED0`: primero `(1,33)`, después `(1,34)` y después los dos "motion/sound set" de cada lado. La prueba
   es doble: el orden exacto en el log y el backtrace del crash de la segunda sesión, que tiene `func_00104990` en la
   pila. En una pelea normal (volcados de RAM + log) esa misma secuencia abre `(1,33)`, `(1,34)`, **`(1,30853)`** y
   **`(1,30849)`**; en la sesión rota abre `(1,33)`, `(1,34)`, **`(1,752167)`**, **`(1,752168)`**.
2. Los dos números basura son el par `v17[3]`/`v17[4]` que arma `func_00104C10`:
   `sp[3] = 0xAC2F + (g->0x2AC)/9` y `sp[4] = 0xAC2F + (g->0x47C)/9` (la rama `flag==1`, que es la de los volcados).
   Con `arg0 = 752167 + 0x33B2 = 0xBADD9` → `q = 721.322`; el otro es `q+1`.
   *(Ojo: el valor correcto es `0xBADD9`, no `0xBADF9` como decía el resumen previo.)*
3. `g->0x2AC` (`func_00102900:23`) **no es un campo suelto**: es `lista0+0x1CC`, la copia que hace `func_00101BF0`
   (líneas 38-40) de `record[0]+0`, el `d` del primer miembro del equipo. Ese `d` lo escribe **sólo**
   `func_00101AF8` (asm: `sw s6,0(s0)` en `0x101B70`, con `a1 = d`). Los llamadores de `101AF8` que llenan
   esos registros son cuatro: `func_00255EA0` (roster de `D_003879D0`, `port/eq/255EA0.c:152,170`),
   `func_003FD990` (roster de `D_003876A4`), `func_003D09C0` y `func_003EB9D0`.
4. El `d` válido en una pelea 1v1 es **`0x48` (lado 0) y `0x24` (lado 1)** (volcado `20261111-150737_ram1`: `+0x2AC=0x48`,
   `+0x47C=0x24`, `record0 = {0x48, 0, 2, ...}`, `lista+0x1C0=0`, `contador=1`). En la pelea rota, el par observado
   exige `d0 ≈ 6.491.898` y `d1 ≈ 6.491.907`, es decir **~5.157 veces** el máximo válido (`d ≤ 1259`).
5. **Clasificación:** es un problema de **dato** (iii/i), no de offset/stride (ii). Toda la cadena de traducción de
   `101FD0`, `104C10`, `101AF8`, `101BF0`, `255EA0`, `2AD588` y `253C88` la comparé línea a línea contra el asm y
   **coincide** (incluidos los `sw` en delay slot de `0x254A14/20/2C/3C`, que son una trampa fácil). El valor basura
   entra antes: viene de la tabla de roster `D_003B26B0+0x58+0x78*i` que llena `func_002A7ED8` con `Gsc_GetInt()`
   (el motor de scripts GSC, reescrito a mano en el port).
6. Números concretos del valor crudo del roster que se deduce del par: **`raw0 = 0x63BBB5+r0`** y
   **`raw1 = 0x63BBBE+r1`** (r∈[0,8]), o sea un valor `9` (o casi) mayor entre lados — la firma de *dos registros
   consecutivos de 9 bytes*, no de dos ids de archivo. El rango válido de ese crudo es **`0xACBB..0xB1A6`**
   (ver §2).
7. **Falta un dato para cerrar el último eslabón:** un volcado de RAM (`BT2_F9_RAM`) o una sonda en el momento del
   setup de la pelea con `D_003B26B0+0x58` / `D_003879D0+0x1A0` y los `d`. El diff de §5 es una sonda (segura) +
   un tope defensivo para que no vuelva a colgarse; **el arreglo de fondo no se puede escribir sin ese dato**.

---

## 1. La cadena real, con evidencia

### 1.1 Quién pide el índice (log + backtrace)

Sesión `20261111-162449.log` (la que colgó):

```
283839: [file] open (1,33) off=0x5B9000 size=0x83180      <- func_00104990 estado 0: 0x33D3 fijo
283840: [file] open (1,34) off=0x63C800 size=0x13A40      <- req[2] = g->0xD4 + 0x33D4 (acá 0xD4 = 0)
283841: bt2full: ADXF_OpenAfs(1, 752167) fuera de rango   <- req[3] (v17[3])
```

Sesión `20261111-163116.log` (la que crasheó después, con el par completo):

```
125637: ADXF_OpenAfs(1, 752167) fuera de rango     <- req[3]
125638: ADXF_OpenAfs(1, 752168) fuera de rango     <- req[4]
125819: señal 11, direccion 0x61AD6E6C, rip 0x40151878
125849: pila-escaneo: bin/bt2(func_00104990+0x149) / func_00104990+0x0 / func_002A8678 / func_002998D8
        / func_00102900+0x5f / func_00103000+0x93
```

La pila confirma el camino: `func_00103000 → func_00102900 → func_002998D8` (dispatcher de tareas)
`→ func_00104990`. `func_00102900` (`port/eq/102900.c:23`) es el que arma el pedido:

```c
func_00104C10(*(s32 *)(p + 0xD4), *(s32 *)(p + 0x2AC), *(s32 *)(p + 0x47C));
```

y `func_00104C10` (`port/eq/104C10.c:16-26`) hace `q1 = arg1/9; q2 = arg2/9; sp[3]=choice(q1); sp[4]=choice(q2)`
y registra la tarea `func_00104990` (`0x104990`). El asm es idéntico (`0x104C18..0x104CB8`, `div` **con signo**,
`movz` según `D_00387F2C+0x1008 & 1`, delay slots bien).

`func_00104990` estado 0 (`port/eq/104990.c:20-25`; asm `0x1049D0..0x104A33`) abre, en este orden:
`0x33D3` fijo, `req[2]`, `req[3]`, `req[4]`. El log muestra 33, 34 y después el basura ⇒ **`req[3]` y `req[4]`**.

### 1.2 Prueba cruzada: la misma secuencia en una pelea sana

`20261111-150737.log` (pelea 1v1 normal, mismo build con `BT2_FILELOG`):

```
98299: [file] open (1,33)  off=0x5B9000
98300: [file] open (1,34)  off=0x63C800
98301: [file] open (1,30853) off=0x33E3F800 size=0x40BC0   <- req[3] = 0xAC2F + 8
98302: [file] open (1,30849) off=0x33D1F800 size=0x476C0   <- req[4] = 0xAC2F + 4
```

`30853 - (0xAC2F - 0x33B2) = 30853 - 30845 = 8` y `30849 - 30845 = 4`. O sea, en la pelea sana
`g->0x2AC/9 = 8` y `g->0x47C/9 = 4`, exactamente los valores del volcado de RAM:

```
20261111-150737_ram1_f3431.bin  (D_003876A0 = 0x76B500)
  +0x2AC = 0x48   +0x47C = 0x24   +0xE8 = 0x48   +0x2B8 = 0x24
  lista0+0x1C0 = 0 (contador de equipo = 1)
  record0 (0x76B5E8) = 48 00 00 00 | 00 00 00 00 | 02 00 00 00 | ... (d=0x48, a3val=2, después punteros de buffer)
```

En la sesión rota, en cambio: `752167 - 30845 = 721.322` y `752168 - 30845 = 721.323`. **Mismo camino, mismo
`+0x2AC`, valor distinto.**

### 1.3 De dónde sale `g->0x2AC` (la parte que faltaba)

`g->0x2AC` es el campo `+0x1CC` de la lista por lado que devuelve `func_00101A88(side)`:
`lista = g + 0xE0 + 464*side` (asm `0x101A88`). Entonces:

* `0xE0 + 0x1CC = 0x2AC` (lado 0) y `0x2B0 + 0x1CC = 0x47C` (lado 1).
* `func_00102900` llama **primero** `func_00101BF0` (`0x102918`) y **después** `func_00104C10` (`0x10293C`).
* `func_00101BF0` (`port/eq/101BF0.c:38-40`, asm `0x101C5C..0x101C88`) copia
  `*(s32 *)(lista + (lista[0x1C0])*0x58 + 8)` a `lista+0x1C8` **y** `lista+0x1CC`.

⇒ En el momento del pedido, `g->0x2AC` **siempre** es el `d` del registro `lista[0x1C0]` (= índice 0), sin importar
qué hayan escrito antes `func_001041A0`/`1043A8`/`104628` (esas escriben `+0x2AC` directo, pero `101BF0` lo pisa).
Ese `d` es el `arg1` de `func_00101AF8`, que lo guarda en `record+0` (`port/eq/101AF8.c:17`; asm `0x101B70`
`sw s6,0(s0)`, con `s6 = a1`).

### 1.4 Quién llena ese registro (roster del equipo)

`func_00255EA0` (`port/eq/255EA0.c:117-172`; asm `0x256008..0x2562DC`) es el arranque de pelea
(**lo llama el handler de comando GSC `func_002AC450`, `src/auto/m2c_2AC450.c:7-12`, que hace
`*(s64*)(g+0x4D8) = 0`, `func_00298158(0)`, `func_00255EA0()`, `func_00298158(1)`** — o sea, toda esta cadena
la dispara el mismo script de setup de pelea que llena el roster con la opción `0x63`):
`func_00101A10()` (memset de `g+0xB8`, 0x420 bytes → incluye `0x2AC`/`0x47C`) y
`func_00101AB0(side, count, side, 0)`, y por cada miembro:

```c
p3 = D_003879D0 + s3;                        /* entry del roster */
v1x = FLD(p3, 0);                            /* índice */
s0 = v1x * 9 + FLD(p3, 0xC);                 /* d = offset de registro de 9 bytes */
a0v = func_00101A88(s5, sp94) + spA0 + 8;    /* lista+8+i*0x58 = record[i]+0 */
func_00101AF8(a0v, s0, 0, a3val, ...);       /* guarda d en record+0 */
```

Los `p3[0]`/`p3[0xC]` salen de `D_003879D0+0x1A0`/`+0x204` (lados), que a su vez los copia
`func_00253C88` (`port/eq/253C88.c:32-33`) de la tabla estática `D_003B26B0+0x58+0x78*i`:

```c
*(s32 *)a1p                     = *(s32 *)(*(u8 **)(D_003879D0 + 0x2A8) + var_a3 + 0xC); /* idx */
*(s32 *)(D_003879D0 + var_a2+0xC) = *(s32 *)(*(u8 **)(D_003879D0 + 0x2A8) + var_a3 + 0x10); /* rem */
```

`func_002AD588` (`port/eq/2AD588.c:12-21`; asm `0x2AD588`) precalcula `idx = (raw-0xACBB)/9` y
`rem = (raw-0xACBB)%9` a partir del crudo `raw = *(s32 *)(D_003B26B0+0x58+0x78*i)`.
`D_003879D0+0x2A8 = &tabla` lo hace `func_002542F0` (`port/eq/2542F0.c:153-160`, con los delay slots
`0x254A14/0x254A20`; el C coincide) y llama a `2AD588` y a `253C88` ahí mismo (líneas 155 y 180).

⇒ El crudo del roster es el origen de todo. El único escritor de `D_003B26B0+0x58+0x78*i+0` que encontré es
**`func_002A7ED8`** (`port/eq/2A7ED8.c:39`, asm `0x2A7F80..0x2A7F88`: `*(s32*)(s3+0) = Gsc_GetInt();`,
`s3 += 0x78`), es decir el **motor de scripts GSC**. (No hice una búsqueda exhaustiva de escritores indirectos
con puntero calculado en runtime; si apareciera otro, la sonda de §5 lo va a delatar.)

### 1.5 Aritmética exacta del valor basura

Con el par observado y la rama `flag==1` (`0xAC2F`; `D_00387F2C+0x1008 & 1 == 1` en los dos volcados):

```
arg0 = 752167 + 0x33B2 = 0xBADD9
q0 = arg0 - 0xAC2F = 721.322
d0 = 9*q0 + r0  = 6.491.898 + r0   (r0 ∈ [0,8], el resto que 104C10 descarta)
d1 = 9*q1 + r1  = 6.491.907 + r1
raw = d + 0xACBB  (identidad: 2AD588 invierte d = raw - 0xACBB)
  raw0 = 0x63BBB5 + r0
  raw1 = 0x63BBBE + r1
```

Si los restos son válidos (`r∈[0,8]`), `idx0 = 721.322` y `idx1 = 721.323`: dos índices consecutivos. Los crudos
quedan a 9 bytes exactos uno del otro (`0x63BBB5` / `0x63BBBE`) ⇒ **más que "un id inválido", parecen dos punteros
a registros consecutivos de 9 bytes** (la tabla de "motion" del juego). Con la variante `flag==0` (`0xABA3`) los
números son `q=721.462`, `d=6.493.158`, `raw=0x63C0A1`; elijo la de `flag==1` porque es la de los volcados, pero
la conclusión no cambia.

---

## 2. Rangos válidos (respuesta al punto b)

* `gamedata/DATA/ZS2US_1.AFS` tiene **13.234 = 0x33B2** archivos (exactamente el umbral de `func_00100ED0`);
  `ZS2US_2.AFS` tiene **32.245** archivos. Partición 0: ids 0..13.233; partición 1: 0..32.244.
* Las familias de constantes de este camino caen todas al final de la partición 1:

| expresión | id AFS (`arg0`) | índice en partición 1 (`arg0-0x33B2`) | ventana válida |
|---|---|---|---|
| `0xACBB + d` (`104CC0`, `1048F0`, `1043A8`, `104628`) | 44.219+d | 30.985+d | d ∈ [0, 1.259] |
| `0xACC1/0xACC2 + 9q` | 44.225/44.226+9q | 30.991/30.992+9q | q ≤ 1.398 |
| `0xABA3/0xAC2F + d/9` (`v17[3]/v17[4]`) | 43.939/44.079+q | 30.705/30.845+q | q ≤ 1.540/1.400 |
| `0x3CC2 + 2q (+1)` (`101FD0`) | 15.554+2q | 2.320+2q | q ≤ 14.961 |

* Por lo tanto el **crudo del roster válido** es `raw ∈ [0xACBB, 0xB1A6]` (d≤1259). Los observados rondan
  `0x63BBB5` (**~6,19 MiB fuera**, y en la zona de heap/punteros `0x63xxxx`, no en la zona de ids).
* El índice "752167" **no existe** en ninguna partición: no es un id válido que se calculó mal por un factor
  (p. ej. ×9 tampoco: `752167/9` no es entero), es un valor de otra naturaleza (dirección/offset de heap).

---

## 3. Descartes (y por qué)

| Hipótesis | Estado | Evidencia |
|---|---|---|
| `101FD0` calcula mal stride/offset/división | **Descartada** | asm `0x101FD0..0x1020E8` vs `port/eq/101FD0.c`: `lw -72(s0)` = `list+8+i*0x58`, `divu` por 9, `sll 1`, `movz` con `s4^1`, `+15554`; todo igual. Además, en el build actual el par basura sale de `104990` (orden del log y backtrace), no de `101FD0` (que recién corre en la tarea siguiente, `104CC0`; en la carga de la pelea esa tarea **no llega a correr**: después de las 283.841 no hay ninguna apertura de su familia, ni `(1,2169)` — las dos que aparecen en el log son de la sesión de menú, líneas 111900/111909, mucho antes). |
| `1031E0` recibe el índice de `v17[5]` | **Descartada para este caso** | `1031E0` corre en la tarea de `1041A0/1043A8/104628`; el orden del log (33, 34, basura) y la pila apuntan a `104990`. `1031E0` no aparece en la pila. |
| Traducción de `104C10` (offset/stride/div) | **Descartada** | `port/eq/104C10.c:16-26` vs asm `0x104C18..0x104CB8` (incluye `div` con signo y `movz`); idéntico. |
| Traducción de `101AF8` (dónde guarda `d`) | **Descartada** | asm `0x101B54..0x101BE8`: `sw s6,0(s0)` con `s6=a1`; C línea 17 lo mismo. Los demás campos (`+0x40=s3`, `+8=a3`) coinciden con el volcado (`record0+8=2`). |
| Traducción de `101BF0` / `255EA0` / `2AD588` / `253C88` | **Descartada** | comparadas con asm; `255EA0` lee `p3[0]`/`p3[0xC]` y `d = v1x*9 + p3[0xC]` = asm `0x2561AC..0x2561DC`; los stores de `2542F0` con delay slot (`0x2A4=2AD4E0`, `0x2A8=2AD588`, `0x19C=2AD540`, `0x268=*(2AD630+0x10)`, `0x26C=2AD5E8`) están bien en `port/eq/2542F0.c:150-160`. |
| El HLE devuelve un handle y el CRI lo desreferencia | **Cierto pero posterior** | Es la causa del SIGSEGV en `2EC198` (`0x100`), no del índice: el índice ya viene mal de `104990`. La mitigación de `plat_file.c:77-95` (handle a archivo vacío) sólo convierte el cuelgue en un parseo de banco inexistente → `SndHd_GetVagMax` (crash `0x61AD6E6C`). |
| `func_00208228` (caso `u == 0x37` faltante) | **Bug real, no es B12** | `port/eq/208228.c` no tiene el caso `0x37`: el asm (`0xFE` del dispatch, `0x2082E0`) manda `0x37` a `func_00208158(arg0,0)` con `dv=1`; el binario actual (`0x4024ee00`, jump table en `0x40b35c60`) lo manda al default y **devuelve 0**. Produciría `d=0` (→ abriría `(1,30845)`), no `6,49M`. **No explica B12**, pero conviene arreglarlo aparte. |
| `func_001048F0` / `104790` (cambio de "motion" en pelea) | **Descartada** | También produce ids `0xACBB + q`; si hubiera corrido, el log mostraría `(1,31057...)` antes del par basura, y no lo hace. |

---

## 4. Clasificación (respuesta al punto c)

* **(ii) traducción con offset/stride equivocado: NO.** Verificada toda la cadena contra el asm.
* **(i) campo de tabla sin inicializar: posible en parte.** `2AD588` **no escribe** `+0xC/+0x10` cuando el crudo es 0
  (asm `0x2AD504`: `beqz v0 → 0x2AD528`). Si el slot quedó en 0 en el init, `idx`/`rem` conservan lo que hubiera en
  la tabla estática `D_003B26B0+0x58+0x78*i+0xC/+0x10` (BSS = 0 la primera vez, basura si algo la pisó).
* **(iii) dato de archivo/script mal cargado: es el candidato principal.** El crudo lo escribe `func_002A7ED8` con
  `Gsc_GetInt()` (motor GSC, reescrito a mano en `src/sys/gsc_*.c`). El valor observado (~`0x63BBB5`, zona de heap)
  no es un id de archivo ni un resto (0..8): es un valor de otra naturaleza que entró por la lectura del script.
  Ojo: entre el script y `D_003B26B0` hay operaciones de **relocalización de recursos**
  (`Res_RelocateOffsets` en `2542F0.c:100-140`) sobre los datos del archivo del roster; si esa relocalización se
  aplica mal, los `int` del `GSDT` pueden quedar convertidos en direcciones. Ese es el punto a medir.

Mi lectura: **el índice válido existe (debería ser `0xACBB+9*idx`) y el valor que llega es un puntero/offset de
heap**; el cálculo de `d` a partir de ese valor es correcto. La corrupción está aguas arriba, en el roster del
equipo (script/save/relocación), no en el cálculo del índice de AFS.

---

## 5. Cambio propuesto (no aplicado)

### 5.1 Sonda mínima (segura, no cambia comportamiento)

Tres puntos, todos con la macro `bt2_fightlog_note` que ya usan los parches B12:

```diff
--- a/BT2-Recomp/port/eq/104990.c
+++ b/BT2-Recomp/port/eq/104990.c
@@
     switch (req[0]) {
     case 0:
+        {   /* TEMP B12: que ids de sonido se van a pedir (req[3]/req[4] son v17[3]/v17[4]) */
+            extern void bt2_fightlog_note(const char *fmt, ...);
+            bt2_fightlog_note("B12 S 104990 f %08x %08x %08x", (unsigned)req[2],
+                              (unsigned)req[3], (unsigned)req[4]);
+        }
         *(s32 *)(st + 0x10) = func_00100ED0(0x33D3, 0, 1);
```

```diff
--- a/BT2-Recomp/port/eq/2AD588.c
+++ b/BT2-Recomp/port/eq/2AD588.c
@@
     for (i = 4; i >= 0; i--) {
         v0 = *(s32 *)(p + 0x0);
         v1 = (s32)((u32)v0 + 0xFFFF5345U);
+        {   /* TEMP B12: crudo -> idx/rem de cada miembro del roster */
+            extern void bt2_fightlog_note(const char *fmt, ...);
+            bt2_fightlog_note("B12 R %s i %d raw %08x", "2AD588", i, (unsigned)v0);
+        }
         if (v0 != 0) {
             *(s32 *)(p + 0xC) = v1 / 9;
             *(s32 *)(p + 0x10) = v1 % 9;
         }
```

```diff
--- a/BT2-Recomp/port/eq/255EA0.c
+++ b/BT2-Recomp/port/eq/255EA0.c
@@
                     p3 = D_003879D0 + s3;
                     v1x = FLD(p3, 0);
                     s0 = v1x * 9 + FLD(p3, 0xC);
+                    {   /* TEMP B12: miembro, indice, resto y d final de cada lado */
+                        extern void bt2_fightlog_note(const char *fmt, ...);
+                        bt2_fightlog_note("B12 M %s s%d i%d v %d r %d d %08x", "255EA0",
+                                          s5, sp94, v1x, FLD(p3, 0xC), (unsigned)s0);
+                    }
                     sp94 += 1;
```

Con eso, una sola reproducción (`Free 5v5`) dice:
* si `B12 R raw` ya sale `0x63xxxx` → el motor GSC/relocación (`2A7ED8`) es el culpable;
* si `B12 R raw` sale `0xACBB+9*x` y `B12 M d` sale `0x630xxx` → el culpable es la copia/resto (`2AD588`/`253C88`);
* si `B12 S` muestra los `0x2AC/0x47C` crudos, cierra la cadena sin ambigüedad.

### 5.2 Tope defensivo (workaround, no arreglo de fondo)

Para que un valor fuera de rango no vuelva a generar el `do-while` infinito ni el crash posterior:

```diff
--- a/BT2-Recomp/port/eq/104C10.c
+++ b/BT2-Recomp/port/eq/104C10.c
@@
     q1 = arg1 / 9;
     q2 = arg2 / 9;
+    /* B12: d fuera de la ventana valida de la particion 1 (0xACBB..0xB1A6 -> q 0..1259)
+       pide un AFS inexistente; func_00100ED0 gira para siempre. Se satura a 0 y se avisa. */
+    if ((u32)q1 > 1259u || (u32)q2 > 1259u) {
+        extern void bt2_fightlog_note(const char *fmt, ...);
+        bt2_fightlog_note("B12 CLAMP %08x %08x", (unsigned)arg1, (unsigned)arg2);
+        if ((u32)q1 > 1259u) { q1 = 0; }
+        if ((u32)q2 > 1259u) { q2 = 0; }
+    }
     flag = *(s32 *)(D_00387F2C + 0x1008) & 1;
```

Efecto: la pelea arranca con el set de sonido del "miembro 0" en vez de colgarse; el bug de origen sigue
existiendo (se va a ver la voz/música equivocada). Es a propósito: no quiero enmascarar el origen con un valor
"inventado" hasta tener la sonda.

---

## 6. Qué falta confirmar / qué no miré

**Falta (para el arreglo de fondo):**

1. Un `BT2_F9_RAM` de la sesión que falla (las dos sesiones rotas no tienen volcado) o la sonda de 5.1. En ese
   volcado alcanza con leer `D_003879D0+0x2A8`→`+0x58..` (crudos), `D_003879D0+0x1A0/0x204` (idx/rem) y
   `D_003876A0+0xE8` (d), igual que hice con los volcados sanos.
2. El script GSC concreto (archivo, acción y opción `0x63`) y sus `GSDT`: **no** lo localicé ni decodifiqué. Es el
   candidato a contener el valor basura; el `Gsc_GetInt` del port lee el valor con
   `GscTask_PeekOperand` (`src/sys/gsc_2A02E0.c:222-236`) **sin chequear el tamaño del chunk `GSDT`**, así que un
   cursor de operandos corrido lee memoria de más sin fallar.
3. Si en el 5v5 el equipo se arma con `func_00255EA0` o con `func_003FD990`/`func_003D09C0` (los tres llaman a
   `101AF8`); la sonda `B12 M` lo distingue por el `s5/i` y el valor de `d`.
4. El contenido del save/memory card del torneo (`BT2-test/saves/card1/...`): **no** encontré ids de motion en el
   archivo de 16 KiB (busqué `0xACBB+9i` y valores `0xAC00..0xB000` y no hay), así que el roster de equipo no
   parece venir literal del save.

**No miré / no puedo afirmar:**

* No ejecuté el juego ni compilé, así que no tengo registros en vivo ni pude usar watchpoints.
* No revisé los llamadores de `func_002A86E8` para descartar que la tarea `104990` se re-registre con un `sp`
  reusado (el `sp` es de pila de `func_00104C10`; `func_002A86E8` lo copia, pero no verifiqué su traducción
  completa).
* No revisé la traducción completa de `func_002998D8`/`func_002A8678` (dispatcher de tareas), sólo que aparecen en
  la pila.
* No revisé el modo "Free 5v5" vs "torneo" (el log dice modo 33, `torneo_mundial`): no sé si el bug es exclusivo
  del torneo o también pasa en Free 5v5; el usuario lo vio en Free según `BUGS_ABIERTOS.md`, pero el log de la
  sesión rota es del torneo.
* No verifiqué si otras versiones del binario (la que produjo `20261111-162449.log` no tiene el tope de 8 líneas de
  `plat_file.c`) cambian algo del camino; el par de índices es idéntico en las dos sesiones y en el build actual
  (`bin/bt2` 16:33) el `208228` no tiene el caso `0x37`.

---

## Anexo: cómo reproducir la evidencia (solo lectura)

```sh
cd BT2-Port/BT2-test/logs/vivo
grep -n "open (1,33)\|open (1,34)\|752167\|752168" 20261111-162449.log | head
grep -n "752167\|señal 11\|func_00104990"             20261111-163116.log | head
grep -n "open (1,33)\|open (1,30853)\|open (1,30849)" 20261111-150737.log | head

python3 - <<'EOF'
import struct
d=open('20261111-150737_ram1_f3431.bin','rb').read()
g=struct.unpack_from('<I',d,0x3876A0)[0]
for o in (0x2A8,0x2AC,0x47C,0xE0,0xE8,0x2B0,0x2B8,0xE0+0x1C0):
    print(hex(g+o), hex(struct.unpack_from('<I',d,g+o)[0]))
EOF

# tamaño de las particiones AFS (0x33B2 = 13234)
od -A d -t u4 -j 4 -N 4 BT2-Port/BT2-Recomp/gamedata/DATA/ZS2US_1.AFS   # 13234
od -A d -t u4 -j 4 -N 4 BT2-Port/BT2-Recomp/gamedata/DATA/ZS2US_2.AFS   # 32245

# asm de la cadena (ELF original)
D=BT2-Port/BT2-Recomp/tools/binutils/mips-ps2-decompals-objdump
$D -d --start-address=0x101AF8 --stop-address=0x101BF0 BT2-Port/BT2-Recomp/disc/SLUS_214.41
$D -d --start-address=0x104990 --stop-address=0x104A34 BT2-Port/BT2-Recomp/disc/SLUS_214.41
$D -d --start-address=0x256000 --stop-address=0x2562DC BT2-Port/BT2-Recomp/disc/SLUS_214.41
```

Archivos del proyecto leídos: `port/eq/{100ED0,101AF8,101BF0,101FD0,104990,104C10,104CC0,102900,102640,1031E0,
1041A0,1043A8,104570,104628,105278,253C88,253BE8,2542F0,255EA0,208228,208008,208060,2080E0,208158,2081A8,2085C8,
2AD4E0,2AD540,2AD588,2AD5E8,2AD630,207EC0,207F88,208470,2E08F8,2E0830}.c`,
`src/sys/gsc_{29FEB0,2A0038,2A02E0}.c`, `include/sys/gsc.h`, `port/full/plat_file.c`,
`port/build/full/bt2full.map` y el ELF `disc/SLUS_214.41` (asm en `/tmp/opencode/full.asm`).

---

# F9 2026-11-11: valores reales y causa (sesión `20261111-170735`)

Solo lectura otra vez: no edité el proyecto, no compilé y no lancé el juego. Todo el análisis nuevo sale de
`BT2-test/logs/vivo/20261111-170735_{ram1_f3842,ram2_f3952,ram3_f4126}.bin`, del log de esa sesión,
del asm de `disc/SLUS_214.41` y del **asm del overlay `disc/DBZP.BIN`** (que se puede desensamblar con
`objdump -D -b binary -m mips:isa32r2 --adjust-vma=0x3B3100`, porque `config/overlay/DBZP.yaml` dice que se carga
crudo en `0x3B3100`) y del propio binario compilado `port/build/full/bt2full` (x86-64).

**Resultado en una línea:** el `d` basura **no viene de un script GSC ni del roster**, ni de un offset/stride mal
traducido: viene de que `func_004115C0` (el setup de pelea de equipo, overlay `0x4115C0`) tiene el **bucle que llena
`tmp[]` sin incrementar el índice** (`port/eq/4115C0.c:113-119`). El bucle es infinito “en el fuente”, GCC lo borra
(UB) y la lectura posterior `tmp[idx]` queda indefinida: en el binario compilado el compilador deja en `esi` (arg1 de
`func_00101AF8`) el puntero `D_00387F2C + 4*lado`, que es `0x630F00` / `0x630F04`. Eso es lo que se ve en los volcados.

(Con esto, las sondas de §5.1 —`2AD588`/`255EA0`— siguen siendo inocuas pero ya no hacen falta para el diagnóstico;
la sonda útil es la de F9.4.)

## F9.0. Corrección de la aritmética de §1.1/§1.5 (importante)

Los volcados rotos tienen `*(D_00387F2C + 0x1008) = 0` (en `0x631F08`), así que `104C10` usa la rama **`flag == 0`
(`0xABA3`)**, no `0xAC2F`. Con esa rama:

```
id_open = (0xABA3 - 0x33B2) + d/9 = 30705 + q
752027  = 30705 + 721322            ⇒ q = 721322
⇒ d ∈ [9*721322, 9*721322+8] = [0x630EFA, 0x630F02]   (0x630F00 está justo adentro)
```

O sea, **el `d` que se pidió es exactamente el `record[0]+0` que muestran los volcados** (`0x630F00`), sin residuo
“desconocido”. Y encaja también con las dos sesiones rotas viejas: `752167 = 30845 + 721322` es la rama
`flag == 1` (`0xAC2F`) con **el mismo `q = 721322`**, o sea el mismo `d = 0x630F00`. Es decir:

| sesión | rama (`0x631F08 & 1`) | id pedido | q = d/9 | d |
|---|---|---|---|---|
| `150737` (sana 1v1) | 1 | 30853 | 8 | 0x48 |
| `162449`/`163116` (rotas) | 1 | 752167 | 721322 | **0x630F00** |
| `170735` (rota, nueva) | 0 | 752027 | 721322 | **0x630F00** |

El bit de idioma del bloque de save cambia la constante, no el `d`. La cuenta anterior (con `0xAC2F` para la nueva
sesión) daba `0x630F0E` y era la que sobraba 14: el valor real es `0x630F00`.

## F9.1. Qué dicen los volcados (frames 3842 / 3952 / 4126, idénticos)

```
g = D_003876A0 = 0x76B500
lista0 = g+0xE0 = 0x76B5E0 : [0]=5        (+0x1C0=0, +0x1C8=+0x1CC=0)
  record_i = 0x76B5E8 + 0x58*i  (i=0..4)
     +00 = 00 0F 63 00   (0x00630F00)   <- todos los 5 iguales
     +04 = 0             +08 = 2         +0C = 0         +10 = 1
     +14..+30 = 1 (ocho) +38 = 0
     +40 = 0x9C40 / 0x4E20      (limit)
     +44 = +48 = 0xC350 / 0x7530 / 0x9C40 (base)
     +50 = +54 = 0              (buffers de archivo todavía no cargados)
lista1 = g+0x2B0 = 0x76B7B0 : [0]=5, record_i = 0x76B7B8 + 0x58*i
     +00 = 0x00630F04  <- todos los 5 iguales
     resto con el mismo patrón que el lado 0
D_00387F2C = 0x630F00   *(0x631F08) = 0        D_003879D0 = 0   (0 en los tres volcados)
```

Los campos “caros” (`+0x40/+0x44/+0x48`) son **válidos y distintos por miembro**: coinciden con las entradas de la
tabla de personajes `p74 = *(g+0x74) = 0x8C48C0` (16 bytes por personaje: `[0]=base`, `[4]=limit`) con ids chicos
(0..5). Por ejemplo `0xC350/0x9C40` es `p74[0..2]`, `0x7530/0x4E20` es `p74[4]`, `0x9C40/0x9C40` es `p74[5]`.
En cambio `+0x00` quedó en el puntero al bloque de save. Es la firma de que **el `d` se escribió con otro valor que
el resto del registro** (o mejor: que la expresión del `d` no usó los mismos índices).

Para comparar, en las 84 volcadas viejas `d0`/`d1` son siempre chicos (`0`, `0x48=9*8`, `0x49=9*8+1`, `0xf3=9*27`,
`0x319=9*88+1`, todos `= 9*id+rem` y `< 1259`) y `cnt` es 1; solo esta sesión tiene `cnt=5` y `d = D_00387F2C`.

## F9.2. Qué es `0x630F00` (respuesta al punto 2)

No es una tabla de registros de 9 bytes, ni un roster, ni un bloque del sonido. Es el **payload de la asignación
global de 16 KiB que hace el arranque**:

```
ELF 0x298438:  jal 0x28baa8        ; func_0028BAA8(0x4000) = 16384
ELF 0x298440:  li  a0,0x4000
ELF 0x298450:  sw  v0,-16068(gp)   ; D_00387F2C = v0
```

En el volcado se ve el header del bloque en `0x630EC0` = `80 40 00 00 | 00 0F 63 00 | 80 0A 63 00 | 00 4F 63 00`
(tamaño `0x4080`, payload `0x630F00`, vecinos `0x630A80` / `0x634F00`), y el payload arranca con
`9c 00 00 00 | f5|f6 00 00 00 | 00 00 00 00 | 02 00 00 00` (en la sana el segundo campo es `0xf6`, en la rota `0xf5`).
`D_00387F2C` es el **bloque de save/“work” global** que usan muchísimos subsistemas: bandera de idioma en `+0x1008`,
tablas de inventario `+0x1F30` y dinero `+0x283C` (`246860.c`), tablas de movimiento `+0x1408`
(`2484D8.c`, `255EA0.c`, `4115C0.c`), flags de SON en `+0x24C2` (`101BF0.c`), etc. Es decir: el `d` guardado en los
10 registros es **literalmente la dirección del save global** (y +4 para el lado 1).

## F9.3. Quién escribe `record+0` en la pelea de equipo (respuesta al punto 1 y 3)

Repasé los 4 llamadores del informe anterior y además **barrí los binarios**: en el ELF principal hay **1** solo
`jal 0x101af8` (`0x25629C`, dentro de `255EA0`), y en `DBZP.BIN` hay **10**: `0x3B9CC0`, `0x3D16CC`, `0x3EC4BC`,
`0x3FDDB0` y `0x3FDF4C` (los dos de `3FD990`), `0x402BC8` y `0x402D64` (los dos de `4027B0`), `0x40A404`
(`409BB8`), `0x411D90` (`4115C0`), `0x4180CC` (`4178F8`).
Los que importan para este modo:

| función | miembros por lado | ¿es este caso? |
|---|---|---|
| `func_00255EA0` (`0x255EA0`, .text del ELF) | `D_003879D0+0x268` (5 en 5v5) | **no**: el registro lo escribió otro (sus args no coinciden) |
| `func_003FD990` (`0x3FD990`) | `D_003876A4+0x68` | no: setup de historia/misiones; no escribe los arrays `D_003876A4+0x390/0x430` que sí vemos, y sus `d` son `9*idx+rem` de su roster |
| `func_003D09C0` (`0x3D09C0`) | 1 por lado (`func_00101A88(side)+8`) | no: es 1v1/duelo |
| `func_003EB9D0` (`0x3EB9D0`) | 2 por lado | no: escribe solo 2 registros/lado |
| `func_00409BB8` (`0x409BB8`) | 1 por lado | no |
| `func_004178F8` (`0x4178F8`) | 2 por lado | no |
| **`func_004115C0` (`0x4115C0`)** | **5 por lado** (`idx = i*5+k`) | **SÍ** |

Prueba de que es `4115C0` y no otro (todo del volcado):

1. Escribe en `D_003876A4+0x390/0x3B8/0x408/0x430` (`4115C0.c:88-100`). En el volcado roto,
   `D_003876A4+0x390` = `[0,1,2,3,5]` (cinco miembros; en la sana 1v1 era `[5]`), `+0x408 = [0,0,0,0,0]`, `+0x430 = 0`.
2. Su `func_00101AF8` (asm `0x411D90`) pasa `arg3 = *(D_00387F2C+0x810)` y `arg5 = *(D_00387F2C+4*i+0x814)^1`
   para **todos** los miembros. En el volcado, `*(0x630F00+0x810) = 2` y `*(0x630F00+0x814) = *(0x630F00+0x818) = 0`
   ⇒ `+8 = 2` y `+0x10 = 1` en los 10 registros. En los otros setups esos argumentos salen de sus propios rosters
   (`W(q,0xC)`, `W(s0,4)`, ...), no de `D_00387F2C`.
3. El camino de menú: `func_00418410` (`0x418410`) `case 3` (estado `D_003876A4+0x1C == 0x21` = 33, que coincide
   con el `modo 33 (torneo_mundial)` del log) llama `func_004115C0(1)`; `case 2` llama `4178F8` (2 por lado) y
   `case 1` `409BB8` (1 por lado). Por estructura (5 por lado) este es también el camino que esperaría para el
   Free Battle 5v5 del B12 original, aunque eso no lo verifiqué en un log de Free Battle.

### Lo que pasa en `a1` (el valor que se guarda en `record+0`)

Esto es lo central. En el **asm original** (`DBZP.BIN`, `0x4115C0`), el primer bucle llena `tmp[]` bien:

```
4118a8: lw v1,0(t7)          ; estado
4118b4: lw v0,12(v1)         ; count = state[0x2DC + 4*lado]
4118b8: blez v0,0x411914
...
4118d0: lw a2,0(t2)          ; a2 = state
4118d4: addu a3,t3,t0        ; &tmp[t5]
4118d8: addiu s4,s4,1        ; <-- CONTADOR DE MIEMBROS: incrementa
4118e8: lw a0,736(v0)        ; charid = state[0x2E4 + 4*t5]
4118f0: lw a1,816(v1)        ; rem    = state[0x334 + 4*t5]
4118f4: sll v0,a0,3
4118f8: addu v0,v0,a0        ; 9*charid
4118fc: addu v0,v0,a1
411900: sw v0,0(a3)          ; tmp[t5] = 9*charid + rem
411904: lw v1,12(a2)
411908: slt v1,s4,v1         ; s4 < count ?
41190c: bnez v1,0x4118d0
411910: addiu t0,t0,4        ; <-- INDICE: +4
411918: addiu t5,t5,5        ; lado siguiente: idx += 5
...
411d80: lw a1,0(s0)          ; arg1 = tmp[idx]   (s0 = sp+0x50 + 4*idx)
411d90: jal 0x101af8
```

El **port** (`port/eq/4115C0.c:113-119`) escribió el mismo bucle **sin `k++`**:

```c
            if (W(0x2DC + i * 4) > 0) {
                k = 0;
                do {
                    idx = i * 5 + k;
                    tmp[idx] = W(0x2E4 + idx * 4) * 9 + W(0x334 + idx * 4);
                } while (k < W(0x2DC + i * 4));      // <-- k nunca cambia
            }
```

Consecuencias, verificadas en el binario compilado (`port/build/full/bt2full`, símbolo `func_004115C0`):

* El bucle es **infinito** si `count > 0`; C11 6.8.5p6 permite *asumir que termina* cuando no tiene efectos
  externos (solo escribe un array local), así que GCC **lo elimina**. En el binario no hay **ninguna** lectura de
  `state+0x2E4` fuera del bucle de escritura (`0x40367A24` y `0x40367CAE`) y **no existe ninguna multiplicación por 9**
  en toda la función (los 9 `lea ...,%r?,8` son `8*x` para el `7*x` de la tabla de movimiento). El preheader
  `0x40367A04` salta **directo** al cuerpo del segundo bucle (`0x40367B16`).
* `tmp[idx]` queda indefinida; el compilador deja en `esi` (arg1) el valor que ya tenía para otra subexpresión:

```
40367A85: mov  D_00387F2C,%esi      ; esi = 0x630F00
40367A8B: mov  0x810(,%rsi,1),%ecx  ; arg3 = *(0x630F00+0x810) = 2
40367A95: mov  0x40(%rsp),%r14      ; r14 = 4*lado
40367A9A: add  %r14d,%esi           ; esi = 0x630F00 + 4*lado   <-- ESTE es el arg1
40367AA5: mov  0x814(,%rsi,1),%r9d  ; arg5 = (*(...)) ^ 1
40367AE5: call func_00101AF8        ; rdi = base+8,  esi = puntero
```

  y `func_00101AF8` lo escribe tal cual en `record+0` (`0x40153716: mov %ecx,(%rax)` con `ecx = esi` de entrada).
  De ahí `0x630F00` (lado 0) y `0x630F04` (lado 1), iguales para los 5 miembros de cada lado.

**Respuesta al punto 3:** `d` **debe** ser `9*idx + rem` con `idx`/`rem` **offsets** que llenan
`func_00253C88` desde la tabla del roster (o, en este setup, `state[0x2E4+4idx]` / `state[0x334+4idx]`).
Ninguno de los dos debe ser un puntero. En la 5v5 no hay ningún puntero “legítimo” en esa cadena: el puntero entra
por la **traducción del bucle** (UB). La tabla estática `D_003B26B0+0x58+0x78*i` está **toda en cero** en los tres
volcados, así que tampoco es el origen de un crudo basura por GSC.

## F9.4. Fix mínimo (no aplicado)

```diff
--- a/BT2-Recomp/port/eq/4115C0.c
+++ b/BT2-Recomp/port/eq/4115C0.c
@@ -113,9 +113,10 @@
                 k = 0;
                 do {
                     idx = i * 5 + k;
                     tmp[idx] = W(0x2E4 + idx * 4) * 9 + W(0x334 + idx * 4);
+                    k++;
                 } while (k < W(0x2DC + i * 4));
             }
         }
```

Eso es todo: restituye la semántica del asm (`0x4118D8 addiu s4,s4,1` / `0x411910 addiu t0,t0,4`).
`tmp[]` es local y solo se usa para el `d` de `func_00101AF8`, así que el único cambio de comportamiento es el `d`
(que pasa de `0x630F00+4*lado` a `9*charid+rem`, dentro del rango válido `d ≤ 1259` de §2). No toca `255EA0` ni la
cadena 253C88/2AD588/104C10.

### Sonda de confirmación (segura, TEMP B12)

Antes de la llamada, en el segundo bucle, para ver los tres números con una sola reproducción:

```diff
--- a/BT2-Recomp/port/eq/4115C0.c
+++ b/BT2-Recomp/port/eq/4115C0.c
@@
                     } else {
                         s3 = 0;
                         s1 = 0;
                         for (j = 7; j >= 0; j--) o80[j] = 1;
                         s2 = *(s32 *)(p74 + (W(0x2E4 + idx * 4) << 4));
                     }
+                    {   /* TEMP B12: id/rem del estado y d que se guarda en record+0 */
+                        extern void bt2_fightlog_note(const char *fmt, ...);
+                        bt2_fightlog_note("B12 D 4115C0 s%d k%d id%d rem%d d%08x", i, k,
+                                          W(0x2E4 + idx * 4), W(0x334 + idx * 4), (unsigned)tmp[idx]);
+                    }
                     func_00101AF8(base + 8 + k * 0x58, tmp[idx], 0, ...
```

Qué dice cada resultado:

* **Con el fix**: 10 líneas `B12 D 4115C0 s0|s1 k0..4 id0..N rem0..8 d000000..` con `d = 9*id+rem`, chico, y
  distinto por miembro. Después, `func_00104C10`/`func_00104990` deben pedir ids chicos de la familia
  `30705 + d/9` (o `30845 + d/9` si el bit de idioma está en 1), no `752027`.
* **Sin el fix**: `d630f00`/`d630f04` constante por lado (lo que ya sabemos).
* Para confirmar el binario sin jugar: `objdump -d --start-address=0x40367a80 --stop-address=0x40367af0` sobre
  `bt2full` y verificar que **arg1 ya no sea** `esi = D_387F2C + 4*lado` sino una carga de la pila (`tmp[idx]`).

### Red de seguridad (opcional, no arregla nada por sí sola)

El tope defensivo de §5.2 en `port/eq/104C10.c` sigue siendo útil para que un `d` fuera de `[0,1259]` no vuelva a
colgar la máquina en `func_00100ED0`; marcarlo como workaround y no dejarlo si se aplica el fix de verdad.

## F9.5. Qué falta / qué no verifiqué

* **No compilé ni probé** (solo lectura). El fix está sin aplicar; falta que el `porter` lo aplique, regenere
  `build/gen/full/src/port__eq__4115C0.c` y verifique la descompilación de arriba.
* No pude ver el **estado `G = D_0042BB78` del momento del setup** en los volcados (a la hora del F9 el puntero
  `0xC177C0` ya apunta a otra cosa: basura con strings `vs_pmap_selct_04`), así que los `charid`/`rem` exactos de
  los 10 miembros no se pueden reconstruir de los volcados; sí se deducen del `+0x40/+0x44` (ids 0..5) y se verán
  con la sonda.
* `D_003879D0 = 0` en los tres volcados: el único store a ese global está en `0x254320` (`func_002542F0`, lo
  primero que hace `func_00255EA0`), y el overlay no lo referencia (las `addiu reg,reg,31184` de `DBZP.BIN` son a
  `0x4279D0`, no a `0x3879D0`). Es decir, **en esta pelea `255EA0`/`2542F0` no corrieron**: la hipótesis del informe
  anterior sobre el roster no aplica a este caso (su traducción verificada de §1 sigue valiendo si alguna vez se usa).
* No revisé los otros flags/estados de `func_00418410` (cases 0..5) para saber si algún otro setup de equipo
  (2v2/3v3) reusa `4115C0`; los 2 por lado van por `4178F8`, que **sí** tiene `k++` (`4115C0` no).
* Un barrido rápido (`do{}while(x < ...)` sin incremento) marcó otros ficheros (`123380`, `17B158`, `1BB3D0`,
  `1BF690`, `1C1D68`, `2565E0`, `26D6A0`, `2E1630`, `3E23E8`, `3E6E10`, `3FAD88`, `src/main_1002D8`). Los que miré
  son falsos positivos (incrementan vía `next = i+1; i = next;` o vía macro); **no** los audité todos, pero
  conviene tener el patrón presente porque el compilador no avisa (borra el bucle y sigue).
