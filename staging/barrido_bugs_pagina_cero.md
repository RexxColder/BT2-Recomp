# Barrido: desreferencias de puntero nulo / fuera de rango (clase "página cero del PS2")

Fecha: 2026-11-07. **Solo lectura**: no se editó, compiló ni ejecutó nada del proyecto. Este archivo es el único
que escribí.

Alcance: `BT2-Recomp/port/eq/*.c` y `BT2-Recomp/port/full/*.c`. Cuando hizo falta para juzgar de dónde sale un
índice o un puntero, leí también `src/` y `src/auto/` (el C que el enlace compila) y el desensamblado `asm/`.

## Contexto y regla que se está barriendo

En el host la RAM de la PS2 se mapea desde `0x00010000`:

```
port/full/mem.c:239
    map_at(0x00010000u, RAM_SIZE - 0x10000, sMemfd, 0x10000, "la RAM del PS2");
```

La página cero (`0x0..0xFFFF`) **no está mapeada**. En la PS2 leer/escribir ahí es legal (vectores, scratchpad,
RAM baja), así que una traducción que desreferencia un puntero nulo o basura funciona en la consola y **revienta en
el host**. El propio manejador de señal ya lo rotula:

```
port/full/mem.c:147
    a < 0x10000 ? " (pagina cero del PS2: puntero nulo o dato no mapeable)" : "");
```

Caso ya arreglado (referencia de la forma buscada): `port/eq/2A3C08.c` leía
`b = D_003B0F40[4 + idx*4]; return b + (*(u32 *)(b + 4) & ~3)` sin chequear nulo ni rango; con `D[1] == 0` moría en
la dirección `0x4`. Se agregó rango `0..7` + nulo y el llamador `port/eq/2A4148.c` oculta el retrato.

## Método

Greps dirigidos sobre `port/eq` + `port/full` (6253 + 17 archivos), y lectura de cada candidato:

- `\*(s32|u32 *)(D_[0-9A-F]+ + <var> * N)` → 48 líneas.
- `(u8|s32|void *)(s32|u32)<var>` → 105 líneas (la mayoría son punteros PS2 legítimos guardados en `s32`).
- tablas de punteros (`*(u8 **)(base + idx*N)`) → se listaron todas y se revisó el chequeo de nulo/rango de cada una.
- `memcpy/memset/memmove` con tamaño variable → 80 líneas; se revisaron las que leen el tamaño de la RAM.
- `->next` → 18 líneas (todas de listas propias del host o con chequeo de nulo).
- funciones "helper de tabla" que devuelven `tabla[idx]` / `tabla[idx] + offset` (ver apéndice A).

Para cada candidato verifiqué contra el asm si el chequeo existe en el original (importa: si el original **tampoco**
chequea, sigue siendo un bug del port, porque es justamente la diferencia PS2↔host). También verifiqué el tamaño
real de cada tabla en `asm/data/...` para poder dar el rango exacto.

## Resumen priorizado

| # | Archivo:línea | Qué | Gravedad | ¿Se dispara hoy? |
|---|---|---|---|---|
| H1 | `port/eq/256C58.c:36-37,47,52` | `rand() % W(p,0x90)` con `0x90` leído de un recurso: si es 0 → **SIGFPE** (la PS2 no trap-ea `div` por cero). Además `arr = (s32 *)(u32)W(p,0x94)` se indexa sin validar | **crash** | El propio código de la línea 46 (`if (W(p,0x90) > 0)`) demuestra que 0 es posible. Hoy no lo vi disparado |
| H2 | `port/eq/1272E8.c:9`, `127128.c:18`, `127320.c:12`, `127388.c:22` | `gEftHitList` se desreferencia sin chequeo (`+0x6000`, `+arg0*0x180`); el hermano `1279F8.c:10` **sí** chequea (también en el asm) | **crash** (dirección `0x6000`, no mapeada) | El puntero arranca en 0 (`.sdata`) y se libera/repone; falta ver el orden exacto |
| H3 | `port/eq/148530.c:7` y 8 funciones más de `D_00387760` | `*(u8 **)(D_00387760 + 4)` con `D_00387760` puesto a `0` en `1481B8.c:16` (free de escena) | **crash** (dirección `0x4`) | Depende del orden teardown vs. update de tareas |
| H4 | `src/auto/m2c_2A78F0.c:10-12` → `src/auto/perm_2A3BB8.c:24` | **Escritor** de la tabla del bug arreglado: `D_003B0F44[idx] = ...` con sólo `idx >= 0`. La tabla tiene **8** slots; `idx = 8` pisa `D_003B0F64` (la base que lee `2A3C68`) | **corrupción** y después crash | Latente (depende del guion) |
| H5 | `src/auto/m2c_2A3C68.c:6` (`2A3CC0.c:13`, `2A3D18.c:20`), llamadas desde `port/eq/2A42C8.c:51` y `2A4420.c:84,90,92,94` | Misma forma exacta que el bug arreglado: `base + (*(u32 *)(base+4)>>2)*4` con `base` = `D_003B0F64`, sin chequeo de nulo | **crash** (dirección `0x4`) | Hoy no (el loader `2A3C30` suele andar), pero no hay chequeo |
| H6 | `port/eq/2A8408.c:16-20,33-35`; `2A84D8.c:16-20,33-35` | Índice de opcode (`Gsc_GetInt`) sólo con `< 0`; `func_002A3DB8` hace `D_003B1FF0 + t*0x28` sobre un buffer de `0x558` (válido `0..33`) y **escribe** | **corrupción / crash** | Latente (guion con slot inválido) |
| H7 | `port/eq/2A3E80.c:4-7` | `D_003B0F7C + arg0*0x68` sin rango; buffer de `0xD04` → válido `0..0x1F`. Llamadores: `2A3EA8.c:28` y `2A7650.c:59,88` con índices de guion | **corrupción** (pisa globals vecinos) | Latente |
| H8 | `port/eq/3F9300.c:41-44` (+ 8 consumidores) | `D_0042139C = func_100ED0(...)` sin el bucle `do{}while(==0)` que usan **todos** los demás loaders; los consumidores hacen `*(u32 *)(D_0042139C + idx*4)` | **crash** (dirección `idx*4 < 0x10000`) | Latente (fallo de carga) |
| H9 | `port/eq/1A1168.c:22-25` | `idx = *(s32 *)arg0` (primer word del registro) indexa `D_0038780C`, que se aloca con `8` bytes = **2** slots (`src/auto/m2c_1A10D0.c:13-15`), sin rango | **corrupción / crash** si `idx > 1` | A confirmar (ver H9: el origen semántico de `idx` no es obvio) |

---

## H1. `func_00256C58`: módulo por cero y puntero de tabla sin validar (crash, clase PS2↔host)

**Archivo:línea**: `BT2-Recomp/port/eq/256C58.c:36-37`, `:46-52`

```
 35:    s0 = 6;
 36:    do {
 37:        a1 = W(p, 0x90);
 38:        t = 1 << (rand() % a1);
 ...
 46:    if (W(p, 0x90) > 0) {
 47:        arr = (s32 *)(u32)W(p, 0x94);
 ...
 52:                W(p, off + 4) = arr[a3];
```

**Qué se va de rango**: `W(p, 0x90)` es la cantidad de entradas de una tabla del recurso; `rand() % a1` revienta con
`SIGFPE` si `a1 == 0`. Después, `arr = W(p, 0x94)` es una dirección PS2 guardada en el struct y se lee `arr[a3]` con
`a3` hasta `0x90-1`, sin comparar contra el tamaño real de la tabla.

**De dónde sale**: `p = D_003879E8` (`256C58.c:16`, con chequeo de nulo) y `0x90/0x94` se cargan en
`port/eq/256360.c:46-51`:

```
 46:    *(s32 *)((u8 *)D_003879E8 + 0x80) = *(s32 *)tmp;      /* cantidad */
 47:    *(s32 *)((u8 *)D_003879E8 + 0x84) = tmp + 4;           /* tabla     */
 ...
 50:    *(s32 *)((u8 *)D_003879E8 + 0x88) = *(s32 *)tmp;
 51:    *(s32 *)((u8 *)D_003879E8 + 0x8C) = tmp + 4;
```

o sea: **cantidad y puntero salen del bloque de recurso**, no de constantes.

**Por qué puede ser 0 / basura**:
- La línea 46 del mismo archivo se protege con `if (W(p, 0x90) > 0)`: el autor del original sabía que 0 es posible.
  Aun así, el `do/while` de la línea 36 lo usa **sin** ese chequeo.
- En el asm el original hace `div $zero, $v0, $a1` (`asm/cod/1565BC.s:552-556`). En MIPS `div` por cero **no genera
  excepción** (deja HI/LO con un valor definido); en x86 el compilador emite `idiv` y el proceso muere con `SIGFPE`.
  Es exactamente la clase "funciona en PS2, crashea en el host".
- Secundario: `1 << (rand() % a1)` con `a1 > 32` es UB en C (MIPS desplaza módulo 32). No lo cuento como el bug
  principal, pero conviene acotarlo.

**Alcanzable desde**: `asm/cod/1A6F04.s:37-44` — `func_002A6F08` (case 0) hace `func_00256C58(Gsc_GetInt())`, es
decir, es el comando de guion que elige un efecto. No es código muerto.

**Arreglo propuesto** (no aplicado; mínimo, sin cambiar la semántica cuando el dato es válido):

```diff
--- a/BT2-Recomp/port/eq/256C58.c
+++ b/BT2-Recomp/port/eq/256C58.c
@@
     W(p, 0x94) = v;
+
+    /* La PS2 hacia `div` por cero sin excepcion; el host tira SIGFPE.
+     * Con 0 entradas no hay nada que elegir (el original ya lo asume en el `if` de abajo). */
+    if (W(p, 0x90) <= 0 || W(p, 0x94) == 0) {
+        return;
+    }
+    if (W(p, 0x90) > 0x20) {
+        W(p, 0x90) = 0x20;   /* `1 << n` con n >= 32 es UB (MIPS desplazaba modulo 32) */
+    }
+
     s1 = 0;
     s0 = 6;
```

## H2. `gEftHitList`: cuatro funciones lo desreferencian sin chequeo (crash en `0x6000`)

**Archivos:líneas**:

```
port/eq/1272E8.c:9      if (arg0 < *(u32 *)(gEftHitList + 0x6000)) {
port/eq/127128.c:18     if (*(s32 *)(gEftHitList + 0x6000) >= 0x40) {
port/eq/127320.c:11-12  temp_s0 = gEftHitList + arg0 * 0x180;
                        if (arg0 < *(u32 *)(gEftHitList + 0x6000)) {
port/eq/127388.c:19-22  temp_a1 = gEftHitList;
                        ...
                        if (*(s32 *)(var_a0 + 0x6000) > 0) {
```

**Qué se va de rango**: si `gEftHitList == 0`, la primera lectura es en `0x6000` (o `arg0*0x180`), muy por debajo
de `0x10000`. En el host: `SIGSEGV`. En la PS2: se lee RAM baja y sigue.

**De dónde sale**: `gEftHitList` es una **variable puntero** (`.sdata` en `0x0038770C`, valor inicial 0):

```
asm/data/cod/287680.sdata.s:202-206
    nonmatching gEftHitList
    dlabel gEftHitList
        /* 28770C 0038770C 00000000 */ .word 0x00000000
```

No aparece **ningún** `sw` a `gp_rel(gEftHitList)` en el asm extraído (los únicos accesos son `lw`), y el valor
inicial es 0. La asignación real viene de un módulo/overlay que no está en el recorte de `asm/`; lo que sí está
probado es que el estado "nulo" existe.

**Evidencia fuerte de que nulo es posible**: dentro del mismo módulo, el hermano **sí** chequea, y ese chequeo está
en el asm original (no lo agregó el port):

```
port/eq/1279F8.c:10
    if (gEftHitList != NULL && arg0 < *(u32 *)(gEftHitList + 0x6000)) {
```
```
asm/cod/027988.s:58-60
    /* 279F8 001279F8 1CB9838F */  lw         $v1, %gp_rel(gEftHitList)($gp)
    /* 279FC 001279FC F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 27A00 00127A00 11006010 */  beqz       $v1, .L00127A48
```

O sea: el desarrollador original sabía que `gEftHitList` puede ser nulo, pero sólo lo cubrió en `1279F8`. Las otras
cuatro quedaron sin red. En PS2 no se notaba; en el host es crash.

**Arreglo propuesto** (idéntico y de dos líneas en cada archivo):

```diff
--- a/BT2-Recomp/port/eq/1272E8.c
+++ b/BT2-Recomp/port/eq/1272E8.c
@@
 s32 func_001272E8(u32 arg0) {
     s32 v0 = 0;
     u8 *p;
 
+    /* La lista puede no existir todavia / estar liberada; en PS2 leer 0x6000 no fallaba. */
+    if (gEftHitList == NULL) {
+        return 0;
+    }
     if (arg0 < *(u32 *)(gEftHitList + 0x6000)) {
```

```diff
--- a/BT2-Recomp/port/eq/127128.c
+++ b/BT2-Recomp/port/eq/127128.c
@@
 void func_00127128(s32 arg0) {
     u8 *p = (u8 *)arg0;
@@
+    if (gEftHitList == NULL) {
+        return;
+    }
     if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
```

(para `127320` y `127388`, `return` temprano con el mismo comentario).

## H3. `D_00387760` (EftShot): free de escena deja el puntero en 0 y 9 funciones lo desreferencian

**Archivo:línea del productor**:

```
port/eq/1481B8.c:14-16
    BtlPool_Free(BtlPool_GetCurrent(), *(s32 *)(D_00387760 + 4));
    BtlPool_Free(BtlPool_GetCurrent(), (s32)D_00387760);
    D_00387760 = 0;
```

**Consumidores sin chequeo** (todos leen `*(u8 **)(D_00387760 + 4)`, que con `D_00387760 == 0` es una lectura de la
**dirección `0x4`**):

```
port/eq/147E70.c:8      u8 *p = *(u8 **)(D_00387760 + 0x4) + arg0 * 0x270 + arg1 * 0x50;
port/eq/148008.c:7      u8 *base = *(u8 **)(D_00387760 + 4);
port/eq/148030.c:7      u8 *base = *(u8 **)(D_00387760 + 4);
port/eq/148268.c:18     s0 = *(u8 **)(D_00387760 + 4) + *arg1 * 0x270;
port/eq/148348.c:17     if (*(s32 *)(D_00387760 + 8) > 0) {
port/eq/148440.c:14     temp_s1 = *(u8 **)(D_00387760 + 4) + arg0 * 0x270;
port/eq/148530.c:7      return *(u8 **)(D_00387760 + 4) + arg0 * 0x270 + arg1 * 0x50;
port/eq/148568.c:17     a3 = *(u8 **)(D_00387760 + 4) + a0 * 624;
port/eq/148888.c:11     temp_s0 = *(u8 **)(D_00387760 + 4) + (arg0 * 0x270);
```

**Por qué puede ser nulo/basura**: `func_001481B8` es la rutina de cierre de escena (libera el bloque y pone
`D_00387760 = 0`). El bloque se crea en `func_00148058` (`148058.c:33`). Ninguna de las nueve funciones de arriba
comprueba `D_00387760`: leen `+4` (o `+8`) sobre el puntero nulo. Si una tarea de efecto sobrevive al cierre (o el
primer frame después de entrar a pelea llega antes del init), en PS2 lee `0x4` y sigue; en el host muere.

Además `148670.c:25-27` ya intenta protegerse:

```
    s0 = func_00148530(*(s32 *)(s1 + 0), *(s32 *)(s1 + 4));
    if (s0 == NULL) {
        return;
    }
```

pero el chequeo **es inútil**: `func_00148530` devuelve `base + arg0*0x270 + arg1*0x50`, que es `NULL` sólo si
`base == NULL` **y** `arg0 == arg1 == 0`. Eso confirma que el autor del port ya vio el problema y lo tapó a medias.
(El asm de `148530` no chequea nada; el crash también existe en la PS2, sólo que ahí no duele.)

**Arreglo propuesto**: un accesor y guardas en cada consumidor.

```diff
--- a/BT2-Recomp/port/eq/148530.c
+++ b/BT2-Recomp/port/eq/148530.c
@@
-/* 0x00148530: address of record arg0 (0x270 bytes each) in the array at D_00387760 + 4, plus arg1 * 0x50. */
+/* 0x00148530: address of record arg0 (0x270 bytes each) in the array at D_00387760 + 4, plus arg1 * 0x50.
+ * Devuelve NULL si el bloque de escena no existe (liberado por func_001481B8); en PS2 se leia 0x4 y seguia. */
 u8 *func_00148530(s32 arg0, s32 arg1) {
+    if (D_00387760 == NULL) {
+        return NULL;
+    }
     return *(u8 **)(D_00387760 + 4) + arg0 * 0x270 + arg1 * 0x50;
 }
```

y en cada uno de los otros ocho, arriba de la primera lectura:

```c
    if (D_00387760 == NULL) {
        return;        /* o `return 0;` segun el tipo (148008/148030/148440/148568/147E70) */
    }
```

Recomiendo **no** tocar `1481B8` ni `148058` (el ciclo de vida es correcto); sólo las lecturas.

## H4. El **escritor** de la tabla del bug arreglado no tiene tope: pisa `D_003B0F64` con `idx = 8`

**Archivos:líneas**:

```
src/auto/m2c_2A78F0.c:9-13
    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt();
        if (temp_v0 >= 0) {                     /* <-- falta el tope */
            func_002A3BB8(temp_v0, Gsc_GetInt());
        }
    }

src/auto/perm_2A3BB8.c:24
    *((&D_003B0F44) + new_var) = func_00100ED0(arg1, 0, D_003876A8 != 0);
```

**Qué se va de rango**: `D_003B0F44` mide **0x20 bytes = 8 punteros**:

```
asm/data/cod/00387F80.bss.s:1442-1445
    nonmatching D_003B0F44, 0x20
    dlabel D_003B0F44
        /* 003B0F44 */ .space 0x20
```

`idx = 8` escribe en `0x003B0F64` = **`D_003B0F64`**, `9` en `D_003B0F68`, `10` en `D_003B0F6C`, `11` en
`D_003B0F70`. Es decir: un slot de texto "de más" sobrescribe la base de recurso que después leen
`func_002A3C68/2A3CC0/2A3D18` (H5). `idx` negativo ya está filtrado; el positivo alto no.

**Por qué puede pasar**: `temp_v0` viene de `Gsc_GetInt()` (operando de guion). El arreglo de `2A3C08` acotó la
**lectura** a `0..7`, pero el guion que pida el slot 8 ahora escribe fuera de la tabla y encima produce un estado
inconsistente: el retrato no se dibuja (lectura rechazada) y la base de fuente queda pisada.

**Arreglo propuesto** (doble red: en el llamador y en la función que escribe):

```diff
--- a/BT2-Recomp/src/auto/m2c_2A78F0.c
+++ b/BT2-Recomp/src/auto/m2c_2A78F0.c
@@
     if (arg0 == 0) {
         temp_v0 = Gsc_GetInt();
-        if (temp_v0 >= 0) {
+        /* D_003B0F44 tiene 8 slots de 4 bytes (asm/data/cod/00387F80.bss.s:1442);
+         * con 8..11 se pisan D_003B0F64/68/6C/70, las bases de fuente. */
+        if (temp_v0 >= 0 && temp_v0 < 8) {
             func_002A3BB8(temp_v0, Gsc_GetInt());
         }
     }
```

```diff
--- a/BT2-Recomp/src/auto/perm_2A3BB8.c
+++ b/BT2-Recomp/src/auto/perm_2A3BB8.c
@@
 void func_002A3BB8(s32 arg0, M2C_UNK arg1)
 {
   int new_var;
+  if (arg0 < 0 || arg0 >= 8) {
+    return;
+  }
   new_var = arg0;
```

> Nota de alcance: estos dos archivos están en `src/auto/` (el enlace los compila; `port/build/full/tables.c:18430`
> mapea `0x002A3BB8`), no en `port/eq`. Los incluyo porque son el complemento directo del bug que se acaba de
> arreglar y sin esto el fix de `2A3C08` queda a medias.

## H5. `func_002A3C68 / 2A3CC0 / 2A3D18`: misma forma exacta que el bug arreglado

**Archivos:líneas**:

```
src/auto/m2c_2A3C68.c:5-7
    void *func_002A3C68(void) {
        return D_003B0F64 + (((u32) M2C_FIELD(D_003B0F64, u32 *, 4) >> 2) * 4);
    }

src/auto/m2c_2A3CC0.c:12-14   (igual con D_003B0F68)
src/auto/m2c_2A3D18.c:19-21   (igual con D_003B0F6C)
```

**Qué se va de rango**: si `D_003B0F64 == 0`, `M2C_FIELD(0, u32*, 4)` lee la **dirección `0x4`** → `SIGSEGV` en el
host. Es literalmente la misma expresión que el bug de `2A3C08` (`b + (*(u32 *)(b+4) & ~3)` con `b = 0`).

**De dónde sale**: `D_003B0F64` es una variable puntero (`.bss`, arranca en 0) que se llena acá:

```
port/eq/2A3C30.c:9
    D_003B0F64 = func_00100ED0(a0, 0, D_003876A8 != 0);
```

sin ningún chequeo y sin limpiarla al salir (`D_003B0F64` nunca se pone en 0 en `port/eq`). Lo mismo `2A3C88`
(`D_003B0F68`) y `2A3CE0` (`D_003B0F6C`). Son init de tarea (se llaman por dirección: no hay `jal` en `asm/`), así
que **nada garantiza** que hayan corrido antes del primer dibujo.

**Llamadores que la usan sin chequear** (todos en `port/eq`):

```
port/eq/2A42C8.c:51      v = func_002A3C68();
                         func_002A4CF0(0x19, 3, v, ...);     /* 2A4CF0 escribe en v+0x18 */
port/eq/2A4420.c:84,90,92,94   slot = func_002A3C68(); func_002A4CF0(27, 6, slot, ...);
```

`func_002A4CF0` escribe en el registro (`port/eq/2A4CF0.c:18` → `SB(0x18, 1)` = `*(u8*)(rec+0x18) = 1`), así que no
alcanza con "sólo lectura": el crash puede ser en escritura, más difícil de diagnosticar.

**Por qué es plausible**: `func_00100ED0` es el mismo cargador que en `3F9300.c:42` se usa **sin** el bucle de
reintento que sí usan otros (ver H8), y los otros 5 llamadores de `func_00100ED0` en `src/` le pasan buffers válidos
como "current" — es un cargador que puede devolver 0. Además H4 puede poner basura en ese slot.

**Arreglo propuesto**:

```diff
--- a/BT2-Recomp/src/auto/m2c_2A3C68.c
+++ b/BT2-Recomp/src/auto/m2c_2A3C68.c
@@
 void *func_002A3C68(void) {
-    return D_003B0F64 + (((u32) M2C_FIELD(D_003B0F64, u32 *, 4) >> 2) * 4);
+    u8 *base = (u8 *)(s32)D_003B0F64;
+    if (base == NULL) {
+        return NULL;     /* recurso no cargado: en PS2 se leia la direccion 4 y seguia */
+    }
+    return base + (((u32) *(u32 *)(base + 4) >> 2) * 4);
 }
```

(ídem `2A3CC0` y `2A3D18`) y en los llamadores:

```diff
--- a/BT2-Recomp/port/eq/2A42C8.c
+++ b/BT2-Recomp/port/eq/2A42C8.c
@@
     v = func_002A3C68();
+    if (v == 0) {
+        return;
+    }
     func_002A4CF0(0x19, 3, v, 0, s1, s0, ...);
```

```diff
--- a/BT2-Recomp/port/eq/2A4420.c
+++ b/BT2-Recomp/port/eq/2A4420.c
@@
     if (mode != 2) {
         slot = func_002A3C68();
+        if (slot == 0) {
+            return;
+        }
         func_002A4CF0(27, 6, slot, mode + 2, ...);
         return;
     }
```

## H6. `func_002A8408 / func_002A84D8`: índice de opcode sólo con `< 0` (escritura fuera del buffer)

**Archivos:líneas**:

```
port/eq/2A8408.c:16-20
        t = Gsc_GetInt();
        if (t < 0) {
            return 1;
        }
        ent = func_002A3DB8(t);
        ...
        *(s8 *)(ent + 0x18) = 1;          /* escritura */

port/eq/2A8408.c:33-35
        t = Gsc_GetInt();
        ent = func_002A3DB8(t);
        return *(s32 *)(ent + 0x20) == 0;  /* lectura */
```

(igual en `port/eq/2A84D8.c:16-20,33-35`)

**Qué se va de rango**: `func_002A3DB8` es `D_003B1FF0 + t * 0x28` (`port/eq/2A3DB8.c:5`). El buffer mide **0x558**
bytes:

```
asm/data/cod/00387F80.bss.s:1497-1500
    nonmatching D_003B1FF0, 0x558
```

⇒ entradas completas válidas: `0 .. 33` (`0x21`). El código legítimo usa hasta `0x20` (ver `2A6CD8.c:51`,
`2A4F50.c:202,213`). Pero `t` viene del operando del opcode (`Gsc_GetInt()`), o sea del guion: `t = 0x22` ya escribe
en el vecino (`D_003B1C80`), y `t` grande (p. ej. `0x100000`) cae fuera de la RAM mapeada → crash.

**Gravedad**: corrupción de globals (y crash con índices grandes). No es exactamente "página cero", pero es la misma
familia "helper de tabla sin rango" del caso arreglado.

**Arreglo propuesto**:

```diff
--- a/BT2-Recomp/port/eq/2A8408.c
+++ b/BT2-Recomp/port/eq/2A8408.c
@@
+/* D_003B1FF0: 0x558 bytes, stride 0x28 -> indices validos 0..33 (asm/data/cod/00387F80.bss.s:1497). */
+#define FONT_SLOT_MAX 0x22
+
     case 0:
         t = Gsc_GetInt();
-        if (t < 0) {
+        if (t < 0 || t >= FONT_SLOT_MAX) {
             return 1;
         }
@@
     case 2:
         t = Gsc_GetInt();
+        if (t < 0 || t >= FONT_SLOT_MAX) {
+            return 1;
+        }
         ent = func_002A3DB8(t);
```

(El `return 1` es el valor que ya usa el camino "sin efecto" en `case 0`; en `case 2` devolver 1 equivale a "no hay
nada pendiente", que es lo seguro.)

## H7. `func_002A3E80`: helper de tabla sin rango (pisa los globals vecinos)

**Archivo:línea**:

```
port/eq/2A3E80.c:4-6
    u8 *func_002A3E80(s32 arg0) {
        return D_003B0F7C + arg0 * 0x68;
    }
```

**Rango real**: `D_003B0F7C` mide **0xD04** bytes (`asm/data/cod/00387F80.bss.s:1472-1475`), stride `0x68` ⇒ índices
válidos `0 .. 0x1F` (31). Cualquier `arg0 >= 0x20` escribe/lee `D_003B1C80` y siguientes.

**Llamadores con índice que viene de la RAM del juego**:

```
port/eq/2A3EA8.c:28    r = func_002A3E80(arg0, arg1, arg2, arg3);   /* arg0 = indice del guion */
                       side = *(s8 *)(r + 3);                       /* lectura inmediata */
port/eq/2A7650.c:59    temp_s0_2 = (u8 *)func_002A3E80(var_s1);      /* var_s1 desde *(s32*)(arg1+0xC) */
port/eq/2A7650.c:88    func_002A4098(var_s1_2);                     /* 2A4098 -> 2A3E80 */
```

En `2A7650.c` el bucle va de `var_s1 = *(s32 *)(arg1 + 0xC)` hasta `*(s32 *)(arg1 + 0)` (ambos leídos del bloque de
guion, `arg1`), sin acotar; y `2A3EA8` recibe `arg0` de `2A3EA8(var_s1, 0)` que también es un id de texto. Nada
verifica `0 <= idx <= 0x1F`.

**Gravedad**: corrupción silenciosa (los registros de texto se pisan entre sí y con `D_003B1C80`), sin crash salvo
índices enormes.

**Arreglo propuesto**:

```diff
--- a/BT2-Recomp/port/eq/2A3E80.c
+++ b/BT2-Recomp/port/eq/2A3E80.c
@@
 u8 *func_002A3E80(s32 arg0) {
+    /* D_003B0F7C: 0xD04 bytes, stride 0x68 -> 0..0x1F (asm/data/cod/00387F80.bss.s:1472).
+     * En PS2 un indice de mas pisaba en silencio D_003B1C80; devolvemos NULL y el llamador omite. */
+    if (arg0 < 0 || arg0 >= 0x20) {
+        return NULL;
+    }
     return D_003B0F7C + arg0 * 0x68;
 }
```

y en los llamadores (`2A3EA8.c:28`, `2A4098.c:9`, `2A7650.c:59`) agregar `if (r == NULL) return;` / `continue;` antes
del primer acceso.

## H8. `D_0042139C`: carga sin reintento + consumidores que la desreferencian

**Archivo:línea**:

```
port/eq/3F9300.c:41-44
    if (D_0042139C == 0) {
        D_0042139C = func_100ED0(*(s32 *)(D_003876A4 + 0x4) + 0x15, 0, 1);
        func_299608();
    }
```

**Comparación con el resto del mismo subsistema** (todos reintentan hasta que el cargador devuelve algo):

```
port/eq/3B3100.c:25-29    do { D_0042138C = (u8 *)func_00100D58(0, 0, 0); } while (D_0042138C == 0);
port/eq/3E3B98.c:29-33    do { D_00421398 = func_100D58(0, 0, 0); } while (D_00421398 == 0);
port/eq/3EC690.c:29-33    do { D_004213A0 = func_100D58(0, 0, 0); } while (D_004213A0 == 0);
port/eq/418410.c:30-34    do { D_00421394 = func_100D58(0, 0, 0); } while (D_00421394 == 0);
port/eq/3F9300.c:177      D_0042139C = 0;      /* y se pone a 0 al salir */
```

Que **seis** loaders del mismo estilo hagan `do{}while(==0)` es la prueba de que el cargador puede devolver 0; éste es
el único que no lo hace.

**Consumidores que la desreferencian sin chequeo**:

```
port/eq/3F0BF8.c:32-33   u8 *t = D_0042139C + arg0 * 4;
                         *(u8 **)G = D_0042139C + ((*(u32 *)t >> 2) << 2);
port/eq/3F4318.c:29      GP(0) = SUB(D_0042139C, arg0 * 4);
port/eq/3F5F00.c:39-40   w = *(u32 *)(D_0042139C + a0 * 4);
port/eq/3F8160.c:44-45   w = *(u32 *)(D_0042139C + a0 * 4);
port/eq/3FA8F0.c:29      *(u8 **)o = D_0042139C + (*(u32 *)(D_0042139C + 4 * arg0) & ~3u);
port/eq/3FBC08.c:51      *(u8 **)G = D_0042139C + ((*(u32 *)(D_0042139C + arg0 * 4) >> 2) << 2);
port/eq/3FE0C0.c:28      T = D_0042139C;
port/eq/3FFD60.c:41-42   w = *(u32 *)(D_0042139C + a0 * 4);
```

Con `D_0042139C == 0` la primera lectura es en `idx * 4`; para los índices de menú reales (decenas/cientos) queda
por debajo de `0x10000` → crash en el host.

**Arreglo propuesto**:

```diff
--- a/BT2-Recomp/port/eq/3F9300.c
+++ b/BT2-Recomp/port/eq/3F9300.c
@@
     if (D_0042139C == 0) {
         D_0042139C = func_100ED0(*(s32 *)(D_003876A4 + 0x4) + 0x15, 0, 1);
+        if (D_0042139C == 0) {
+            return 1;     /* como los otros loaders del subsistema: reintentar el proximo cuadro */
+        }
         func_299608();
     }
```

y en cada consumidor, `if (D_0042139C == NULL) { return ...; }` antes de la primera lectura (en `3FE0C0.c` después de
la asignación de `T`).

## H9. `func_001A1168`: índice tomado del primer word del registro contra una tabla de 2 slots

**Archivo:línea**:

```
port/eq/1A1168.c:22-31
    idx = *(s32 *)arg0;
    var_v0 = 0;
    if (*(s32 *)(D_0038780C + idx * 4) == 0) {
        var_v0 = BtlTaskList_AddTail(D_00387810, (s32)D_00342380, (s32)sp);
        temp_a1 = var_v0;
        if (temp_a1 != 0) {
            var_v0 = 1;
            *(s32 *)(D_0038780C + idx * 4) = temp_a1;
```

**Qué se va de rango**: `D_0038780C` se aloca con **8 bytes** = 2 punteros:

```
src/auto/m2c_1A10D0.c:13-15
    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 8);
    D_0038780C = temp_v0;
    memset(temp_v0, 0, 8);
```

⇒ índices válidos `0..1`. `idx` sale del primer word del registro (`*(s32 *)arg0`), que es el bloque que copia
`port/eq/15A5D8.c:44-64` (`sp+0x10` es copia de `sp+0x50`, y `sp+0x50 = *(s32 *)arg1`). Si ese word es un id y no
0/1, se indexa fuera de un bloque de 8 bytes del heap de batalla (corrupción del pool) o, si es enorme, fuera de la
RAM.

**Caveat honesto**: no pude confirmar que la semántica de ese word sea "índice 0/1" en todos los usos (el asm
traduce igual: `lw $v1, 0x0($sp); sll $v1, 2; addu $a1, $a1, $v1`, `asm/cod/0A1168.s:22-30`). Por eso lo dejo como
H9 "a confirmar": el chequeo es barato y no cambia nada si el dato siempre es 0/1.

**Arreglo propuesto**:

```diff
--- a/BT2-Recomp/port/eq/1A1168.c
+++ b/BT2-Recomp/port/eq/1A1168.c
@@
     idx = *(s32 *)arg0;
+    /* D_0038780C se aloca con 8 bytes = 2 slots (src/auto/m2c_1A10D0.c:13). */
+    if (idx < 0 || idx >= 2) {
+        return 0;
+    }
 
     var_v0 = 0;
```

---

## Apéndice A — TODOS los "helpers de tabla" encontrados y su estado

Estos son los que devuelven `tabla[idx]`, `tabla[idx] + offset`, o una dirección calculada con un índice, y que
encontré con `return D_... + ...`, `return *(T **)(...)` y el barrido de lecturas de tablas:

| Helper | Devuelve | Consumidor | ¿Chequea nulo/rango? |
|---|---|---|---|
| `port/eq/2A3C08.c` | `D_003B0F44[idx] + off` | `2A3328.c:20`, `2A4148.c:49` | **Sí** (arreglado hoy: 0..7 + nulo) |
| `port/eq/2A3DB8.c` | `D_003B1FF0 + idx*0x28` | `2A8408/2A84D8` (idx de guion), `2A4CF0`, `2A6B50` | **No** el rango en `2A8408/2A84D8` → H6 |
| `port/eq/2A3E80.c` | `D_003B0F7C + idx*0x68` | `2A3EA8.c:28`, `2A4098.c:9`, `2A7650.c:59,88` | **No** → H7 |
| `port/eq/2A3E48.c` | `D_003B0F40 + 0x3C + n*104`, `n` propio | `2A7650.c:41` | No (contador interno; sólo si el guion repite sin fin) |
| `port/eq/2A2170.c` | `D_00387EE8 + n*0x4C`, `n` propio incremental | `Font_NewCmd` (`2A21A8.c:23`) | No; nunca devuelve NULL. Bajo riesgo (contador monótono) |
| `port/eq/2F9AC0.c` | slot libre de `D_0039D7F8` (0x28) | `2F9998.c:38` | **Sí** (`if (s0 == NULL)`) |
| `port/eq/25D018.c` | bloque del pool | — | **Sí** (`NULL` si está lleno) |
| `port/eq/125FF0.c` | `D_003876FC` tabla + `idx*0x11F0` | — | **Sí** (nulo + `arg0 < count`) |
| `port/eq/148530.c` | `*(D_00387760+4) + idx*0x270 + j*0x50` | `148670.c:25` | **No** (el `if (s0 == NULL)` del llamador es inútil) → H3 |
| `port/eq/2BC158.c` | `&D_00346BF0 + idx*8` | `src/auto/m2c_2BB9C8.c:11`, `m2c_2BBA38.c:13` | **No**; `D_00346BF0` mide 0x10 = **2** slots (`asm/data/cod/23F400.data.s:9812`). Si el índice viene de RAM > 1, corrompe vecinos. Bajo riesgo (se esperan 0/1) |
| `port/eq/2BCDA0.c` / `2BCE58.c` | resultado de `func_002B61E0()` | — | No chequean, pero el callee no está en `eq`; no pude ver si puede ser 0 → **no reportado** |
| `port/eq/10CD98.c` / `10CDD8.c` | `func_00101A88(arg0) + arg1*88 + off` | — | No chequean; el callee tampoco está en `eq` → **no reportado** |
| `src/auto/m2c_2A3C68.c` (`2A3CC0`, `2A3D18`) | `base + (*(u32*)(base+4)>>2)*4` | `2A42C8.c:51`, `2A4420.c:84,90,92,94` | **No** → H5 |
| `src/auto/perm_2A3BB8.c` (escritor) | escribe `D_003B0F44[idx]` | `m2c_2A78F0.c:12` | **No** → H4 |

## Apéndice B — Lo que descarté y por qué

- **`port/eq/2CA4A0.c:12`**: `slot = func_002CABA0(arg0, arg1)` y en la línea 19 `W32(dst,0)=1` sin chequear nulo.
  `func_002CABA0` **sí** puede devolver `NULL` (`src/battle/xf_2CABA0.c:15,27`, búsqueda en lista). Pero el único
  llamador (`2CA3E0.c:21`) le pasa `temp_s2`, que sale de `func_002CADD8` (`2CADD8.c:7-33`) recorriendo **la misma
  lista** (`arg0+0x1FC0`, `+0x178` entradas, `+0x180` de stride), así que el puntero siempre está en la lista y
  `func_002CABA0` lo encuentra. Además el asm es idéntico. **Descartado** por inalcanzable con el código actual.
- **Chequeos ya presentes**: `125FF0.c:8-16`, `2F9AC0.c:9-13` + `2F9998.c:38-42`, `1272E8.c:11`
  (`p != NULL`), `1279F8.c:10` (`gEftHitList != NULL`), `2A3328.c:19,25,30,35,38`, `2A3430.c:16-43`,
  `2A3C08.c:12-18`, `148670.c:34` (`if (s2 == NULL)`), `127128.c:22` (`temp_a3 != NULL`).
- **`(u8 *)(s32)arg` / `(void *)(s32)valor` (105 líneas)**: en este port los punteros PS2 viven en `s32` y esos casts
  son la traducción correcta (p. ej. `2D7938.c:23-25`, `2C8250.c:17`, `145B70.c:47`). No son bugs por sí mismos; lo
  que importa es si el valor puede ser 0, y eso se revisó caso por caso (H3/H5 salieron de acá).
- **`memcpy/memset` con tamaño variable (80 líneas)**: los que leen el tamaño de la RAM que revisé
  (`19A3F0.c:30,32`, `1F5A98.c:59`, `273630.c:31`, `2A8858.c:13`, `2F8410.c:62`, `2DF838.c:51,55`) se alimentan de
  contadores del bloque que se acaba de alocar con ese mismo tamaño, o de un campo del archivo comprimido; no
  encontré uno que use un tamaño arbitrario de la RAM contra un destino fijo. **No reportados**.
- **`BtlPool_Alloc` sin chequear** (`19A3F0.c:22,29,31`, `145B70.c:31`, `148058.c:32,39`, `13C308.c:16`,
  `131360.c:26`, `1438C8.c:23`): el `memset` iría a `NULL` si el pool se agota. **No lo reporto** porque la
  implementación de `BtlPool_Alloc` no está en `eq`/`full` (es recompilado/asm) y no pude verificar si puede
  devolver 0. Si alguien confirma que sí, es un barrido aparte con muchos sitios.
- **`port/full/*.c`**: revisé los 17 archivos. No hay desreferencias de punteros que vengan de la RAM de la PS2 con
  índice variable; el renderer GS trabaja con buffers propios del host y `plat_mem.c` maneja su propia lista de
  bloques con chequeos. **Sin hallazgos de esta clase.**
- **Listas enlazadas (`->next`, `18` líneas)**: las de `port/full/plat_mem.c` son del host (nodos propios). En `eq`
  los recorridos de partículas (`13D298.c:41`, `13DEB0.c:48`, `13EB68.c:27`, `13F048.c:29`, `13F638.c:41`,
  `140178.c:28`, `17ACA0.c:30-36`) copian `prev/next` de la RAM pero **chequean `next`/`prev` contra 0** antes de
  usarlos, y el patrón es de lista circular interna. **Descartado** (no pude construir un camino a nulo).
- **`2AFFC0.c:54-59`** (`D_003B0B00 + port*0x180` con `port = *(s32*)(arg0+0xC)`): sólo valida `port < 0`, no un tope
  superior; `D_003B0B00` es un puntero (`.bss`) y no sé cuántos slots tiene. Lo dejo anotado sin arreglo propuesto
  para no inventar el tamaño.
- **`2A5FC8.c:49`** (`D_003B26B0 + idx*0x10 + 0x2B0`): el bucle está acotado por `idx < 5` explícito. OK.

## Apéndice C — Lo que NO está verificado

1. **El orden real** teardown/update de H2 y H3. No encontré el `jal`/registro que asigna `gEftHitList` ni el que
   llama a `1481B8`/`148058` (son init de tarea invocados por dirección). La evidencia de que el estado nulo es
   posible es el valor inicial 0 y el chequeo del hermano (`1279F8`, presente en el asm), no una reproducción.
2. **Si `func_00100ED0` devuelve 0** (H5/H8). El argumento es comparativo (los otros loaders del subsistema
   reintentan), no leí la implementación.
3. **La semántica de `idx` en H9** (si es 0/1 por diseño).
4. No corrí el juego ni busqué estos crashes en logs (`BT2-test/logs/vivo`) — la consigna era sólo lectura. Si
   querés priorizar, el orden de la tabla del resumen es mi recomendación; H1 es el único donde el mismo código se
   contradice (línea 46 vs línea 36) y por eso lo pondría primero a probar.
