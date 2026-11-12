# Barrido: puntero de función PS2 vs PC en tablas de clase (`BtlTask`)

Fecha: 2026-11-11. Alcance: todo el port nativo `BT2-Recomp` (solo lectura; no se compiló ni se aplicó ningún cambio).
Build que juega el usuario: `BT2-test/bin/bt2` == `BT2-Recomp/port/build/full/bt2full` (mismo SHA1
`0466ef6d…`, 2026-11-11 12:11). El híbrido `port/build/native/bt2` (Oct 13) se menciona aparte porque comparte
las mismas fuentes pero resuelve los símbolos distinto.

## 0. Resumen

- Hay **25 sitios rotos** en 25 archivos, además del ya arreglado `port/eq/191728.c`.
- **11 sitios** no desreferencian la tabla: comparan `*(u8 **)(task+0x28)` (el puntero a la tabla) contra la
  dirección de la función. Eso **no reproduce el asm** (el original hace dos cargas) y está roto **en los dos
  builds**.
- **10 sitios** sí desreferencian (`cls[0]`) pero comparan contra `func_XXXX` (dirección PC en `bt2full`). En
  `bt2full` siempre dan falso; en el híbrido 4 de ellos funcionan de casualidad porque
  `port/build/gen/native_syms.ld:492-499` fija esos símbolos a la dirección PS2.
- **4 sitios** más están en `src/auto/*` (los usa solo `bt2full`): misma variante `cls[0] == &func_XXXX`.
- **No existe** ningún sitio vivo con la variante `task->cls == func_XXXX` (comparar el puntero de la tabla); los
  únicos `task->cls ==` son contra `NULL`.
- Todos los sitios correctos del port usan el patrón bueno: `cls[0]` contra la **constante PS2** (o contra
  `EftXxx_Update` solo bajo `#ifdef __mips__`).
- No se aplicó nada. Los diffs de §6 son propuestas.

## 1. La regla del despacho (evidencia)

### 1.1 Layout

`include/battle/eft_ae.h:50-68`: el `BtlTask` tiene `cls` en `+0x28`; `include/battle/eft_ae.h:27-34`: la clase es
una tabla de callbacks (`update` en `+0x00`, `init` en `+0x04`, `term` en `+0x08`, `postUpdate` en `+0x0C`,
`reset` en `+0x10`, `draw` en `+0x14`). Lo mismo en `eft_aa.h:47`, `eft_b.h:44`, `eft_c.h:56`, `eft_e.h:98`, etc.:
**todas** las tareas del motor guardan la tabla en `+0x28`.

### 1.2 Despacho

`src/battle/eft_ae_1F2D30.c:397-431` (`BtlTaskList_Update`):

```c
if (task->cls->update != NULL) {
    gBtlTaskCur = task;
    task->cls->update(task);
```

Es decir: carga `task->cls` (un puntero que está en RAM) y después carga el primer word de esa tabla y lo llama.
El puerto **no reescribe la tabla**: el word es una dirección PS2.

### 1.3 La tabla de clase es data original y conserva direcciones PS2

- `port/full/mem.c:1-15` (comentario del build): *"los punteros a función del juego caen en la versión nativa"* y
  la RAM del PS2 se mapea en su dirección. `load_elf` (`port/full/mem.c`, ~210-240) copia los `PT_LOAD` tal cual.
- `port/full/mem.c:194-207` (`full_patch_range`): escribe un `jmp rel32` **en la dirección PS2 de cada función**
  (no toca las tablas de `.data`). `port/full/mem.c:343` lo aplica en `0x100000..OVL_LO`.
- `port/build/full/tables.c:14008`: `{0x00191238u, func_00191238},` (PS2 → host) es la tabla que usa ese parcheo.
- `port/tools/gen_native.py:1-30`: compila C con punteros de 4 bytes y símbolos absolutos, pero **no reescribe la
  data del juego**.
- Evidencia directa en la imagen (`disc/SLUS_214.41`, `.data` VMA `0x33F400`, offset de archivo `0x240400`):

```
VA 0x342018: 191238 190f08 191210 191468 191510 191568 194d08 194c30 ...
```

  El primer word de la tabla de clase es `0x00191238` (dirección PS2 del update), no un puntero del host.
  Barrido de todas las tablas usadas en comparaciones (primer word == update):

| update PS2 | tabla `.data` |
|---|---|
| `0x191238` | `0x342018` |
| `0x195E70` | `0x342090` |
| `0x19C868` | `0x3422A0` |
| `0x1A45B0` | `0x342418` |
| `0x1B5400` | `0x342848` |
| `0x1DDA10` | `0x3431D8` |
| `0x1E9428` | `0x343568` |
| `0x1EB270` | `0x343598` |
| `0x194948` | `0x342048` |
| `0x19FAC8` | `0x342320` |
| `0x19FFA8` | `0x342350` |
| `0x1CC770` | `0x342D98` |
| `0x1CB078` | `0x342C68` |
| `0x183228` | `0x341F00` |
| `0x1A68A8` | `0x342688` |
| `0x1BC188` | `0x3428F0` |
| `0x1C05F8` | `0x342920` |
| `0x1C6E40` | `0x3429B0` |
| `0x1B2FD0` | `0x3427E8` |
| `0x1B3E68` | `0x342818` |
| `0x143C38` | `0x3401A0` |
| `0x131760` | `0x340058` |
| `0x13A8B8` | `0x340140` |
| `0x1A7FA0` | `0x3426C8` |

### 1.4 Por qué la comparación con `func_XXXX` falla en `bt2full`

`func_00191238` es la función nativa y vive en `0x401db9a0` (`nm -n port/build/full/bt2full`). Desarmado del
propio port:

```
func_00191890 @ 0x401dbde0:
    ... mov $0x401db9a0,%edx     ; dirección PC de func_00191238
        cmp %edx,(%rcx)          ; contra task->cls (¡una sola carga!)
```

La tabla (0x342018) tiene `0x191238`, así que la igualdad nunca se cumple. Lo mismo para `&func_00195E70`,
`&func_0019C868`, `&func_001A45B0`, `&func_001DDA10`, `&func_001E9428`, `&func_001EB270`, `&func_001B5400`
(ver §2/§3: los `mov $0x40xxxxxx` del desarmado).

El arreglo de `191728.c` es el patrón correcto: `cmpl $0x191238,(%rcx)` (disasm de `bt2full`, 2026-11-11).

### 1.5 El build híbrido (matiz importante)

`port/build/gen/native_syms.ld:492-499` fija unos pocos símbolos a la dirección PS2:

```
func_00191238 = 0x00191238;
func_0019C868 = 0x0019C868;
func_001A45B0 = 0x001A45B0;
func_001B5400 = 0x001B5400;
func_001DDA10 = 0x001DDA10;
func_001E9428 = 0x001E9428;
func_001EB270 = 0x001EB270;
```

Por eso en `port/build/native/bt2` los 4 sitios que declaran el símbolo como objeto
(`extern M2C_UNK func_X __attribute__((section(".data")))`) **sí** comparan contra `0x191238`/`0x1E9428`/etc.
(`nat_func_00191768`: `mov $0x191238,%esi`). Pero:

- Los que declaran un **prototipo** (`void func_X(void);`) son reescritos por `gen_native` a
  `bt2g_func_X` y comparan contra la dirección del puente: `195A58` contra `0x43d6ff60`, `19D808` contra
  `0x43d70110`, `1EB930`/`1EBBC8` contra `0x43d71790` (desarmado de `bt2`).
- Los que tienen la carga faltante están rotos igual.

Conclusión: **la constante PS2 es lo único correcto en los dos builds**; depender de `native_syms.ld` es frágil.
Igual, el build que se prueba es `bt2full` (ver §0), así que el criterio principal es ése.

### 1.6 Un segundo error, en 11 de los sitios: falta una desreferencia

En `191890.c` (y 10 más) la C dice:

```c
if (arg0 != NULL && *(u8 **)(arg0 + 0x28) == func_00191238) {
```

Eso compara **el puntero a la tabla** (`task->cls`) contra la dirección del update. El asm original hace **dos
cargas**:

```
full.asm:148295  func_00191890:
  1918a0: lw  v1,40(a2)        ; v1 = task->cls
  1918a4: lui a0,0x19
  1918a8: addiu a0,a0,0x1238   ; a0 = 0x191238
  1918ac: lw  a1,0(v1)         ; a1 = cls[0]  <-- carga que falta en la C
  1918b0: bne a1,a0,...
```

Prueba de que la C actual no reproduce el original: el asm MIPS que generó `scripts/fdiff.py` desde esa misma C
(`build/fdiff/port_eq_191890_default/191890.s:28-31`) hace **una sola** carga (`lw $3,40($4)` y compara `$3`).
O sea: el "fdiff OK" que figura en `docs/agents/b9/done_031.txt` para estos archivos no es confiable; el binario
MIPS de esa C nunca coincidió con el original. Los archivos que sí tienen la doble carga (`191768`, `195A58`,
`19D808`, `1DDCF0`, `1EAEE0`, `1EBC30`, `1EB930`, `1EBBC8`) muestran `lw …,40(...)` + `lw …,0(...)` en su `.s` de
fdiff.

## 2. Tabla — los 16 sitios pedidos

Variantes:
- **V1**: `cls[0]` (dos cargas) contra `&func_XXXX` → rota en `bt2full`; en híbrido correcta solo si el símbolo
  está fijado por `native_syms.ld` (marcado `OK*`).
- **V2**: `cls` (una carga) contra `func_XXXX` → rota en ambos builds; además no equivale al asm.
- **V3**: `cls[0]` contra constante PS2 → correcta (no hay ninguna en esta tabla; es el patrón del arreglo).

| # | archivo:línea | var | update PS2 / tabla | evidencia asm (`/tmp/opencode/full.asm`) | híbrido | diff propuesto (resumen) | riesgo |
|---|---|---|---|---|---|---|---|
| 1 | `port/eq/191768.c:10` | V1 | `0x191238` / `0x342018` | `148221-148238`: `lw v1,40(a2)` … `lw a1,0(v1)` … `bne a1,0x191238` | OK* | `BLAST_IS_UPDATE(cls[0])` con `#ifdef` | bajo |
| 2 | `port/eq/191890.c:11` | V2 | `0x191238` / `0x342018` | `148295-148314`: `lw v1,40(a2)`; `lw a1,0(v1)`; `bne` | ROTA | agregar `*(void **)` + macro | medio |
| 3 | `port/eq/1918F8.c:11` | V2 | `0x191238` / `0x342018` | `148321-148340`: idem | ROTA | idem | medio |
| 4 | `port/eq/191960.c:11` | V2 | `0x191238` / `0x342018` | `148347-148366`: idem | ROTA | idem | medio |
| 5 | `port/eq/195A58.c:12` | V1 | `0x195E70` / `0x342090` | `152444-152460`: `lw v1,40(a2)`; `lw a1,0(v1)`; `bne a1,0x195E70` | ROTA (puente `0x43d6ff60`) | macro `BLAST_IS_UPDATE` | bajo |
| 6 | `port/eq/19D808.c:12` | V1 | `0x19C868` / `0x3422A0` | `160422-160440`: dos cargas; `bne a1,0x19C868` | ROTA (puente `0x43d70110`) | macro | bajo |
| 7 | `port/eq/1A4AC8.c:10` | V2 | `0x1A45B0` / `0x342418` | `167682-167702`: `lw v1,40(t2)`; `lw t1,0(v1)`; `bne` | ROTA | agregar `*(void **)` + macro | medio |
| 8 | `port/eq/1DDCF0.c:12` | V1 | `0x1DDA10` / `0x3431D8` | `225535-225549`: dos cargas; `bne a1,0x1DDA10` | OK* | macro | bajo |
| 9 | `port/eq/1DDD30.c:9` | V2 | `0x1DDA10` / `0x3431D8` | `225551-225570`: dos cargas; `bne` | ROTA | agregar `*(void **)` + macro | medio |
| 10 | `port/eq/1DDDF8.c:10` | V2 | `0x1DDA10` / `0x3431D8` | `225601-225620`: dos cargas; `bne` | ROTA | idem | medio |
| 11 | `port/eq/1EAE10.c:13` | V2 | `0x1E9428` / `0x343568` | `238837-238856`: `lw v0,40(a2)`; `lw a0,0(v0)`; `bne` | ROTA | idem | medio |
| 12 | `port/eq/1EAE78.c:13` | V2 | `0x1E9428` / `0x343568` | `238863-238882`: idem | ROTA | idem | medio |
| 13 | `port/eq/1EAEE0.c:8` | V1 | `0x1E9428` / `0x343568` | `238889-238905`: dos cargas; `bne a0,0x1E9428` | OK* | macro | bajo |
| 14 | `port/eq/1EAF68.c:11` | V2 | `0x1E9428` / `0x343568` | `238923-238942`: dos cargas; `bne` | ROTA | agregar `*(void **)` + macro (`!=` → `!`) | medio |
| 15 | `port/eq/1EAFD0.c:13` | V2 | `0x1E9428` / `0x343568` | `238949-238968`: dos cargas; `bne` | ROTA | idem `1EAE10` | medio |
| 16 | `port/eq/1EBC30.c:9` | V1 | `0x1EB270` / `0x343598` | `239740-239756`: dos cargas; `bne a1,0x1EB270` | OK* | macro | bajo |

`OK*` = en el híbrido da bien porque `native_syms.ld` fija el símbolo; en `bt2full` está roto igual.

## 3. Tabla — sitios extra (mismo error, no estaban en la lista)

| # | archivo:línea | var | update PS2 / tabla | evidencia asm | híbrido | diff | riesgo |
|---|---|---|---|---|---|---|---|
| 17 | `port/eq/1B55C8.c:9` | V2 | `0x1B5400` / `0x342848` | `184628-184648`: `lw v0,40(a2)`; `lw a0,0(v0)`; `bne a0,0x1B5400` | ROTA | agregar `*(void **)` + macro | medio |
| 18 | `port/eq/1EB8D0.c:13` | V1 | `0x1EB270` / `0x343598` | `239524-239546`: dos cargas; `bne a0,0x1EB270` | no está en el híbrido | macro | bajo |
| 19 | `port/eq/1EB930.c:13` | V1 | `0x1EB270` / `0x343598` | `239548-239582`: dos cargas; `bne a0,0x1EB270` | ROTA (puente `0x43d71790`) | macro | bajo |
| 20 | `port/eq/1EB9C0.c:13` | V1 | `0x1EB270` / `0x343598` | `239584-239606`: dos cargas; `bne a0,0x1EB270` | no está en el híbrido | macro | bajo |
| 21 | `port/eq/1EBBC8.c:12` | V1 | `0x1EB270` / `0x343598` | `239714-239738`: dos cargas; `bne a0,0x1EB270` | ROTA (puente `0x43d71790`) | macro | bajo |
| 22 | `src/auto/m2c_1EB830.c:9` | V1 | `0x1EB270` / `0x343598` | `239484-239502`: dos cargas; `bne a0,0x1EB270` | no (solo full) | macro | bajo (auto) |
| 23 | `src/auto/m2c_1EB880.c:9` | V1 | `0x1EB270` / `0x343598` | `239504-239522`: dos cargas; `bne` | no (solo full) | macro | bajo (auto) |
| 24 | `src/auto/perm_1EBA68.c:21` | V1 | `0x1EB270` / `0x343598` | `239626-239644`: dos cargas; `bne a0,0x1EB270` | no (solo full) | macro | bajo (auto) |
| 25 | `src/auto/m2c_1EBB48.c:11` | V1 | `0x1EB270` / `0x343598` | `239682-239712`: dos cargas; `bne a0,0x1EB270` | no (solo full) | macro | bajo (auto) |

Comprobación en el binario que se juega (`bt2full`), todos con `mov $0x40xxxxxx` contra `cls[0]`:

```
func_001EB830 / _1EB880 / _1EBA68 / _1EBB48 / _1EB8D0 / _1EB930 / _1EB9C0 / _1EBBC8:
        cmp $0x40235620, ...        ; 0x40235620 = func_001EB270 host
```

## 4. Sitios correctos (y por qué)

Todos los que ya usan **constante PS2** sobre `cls[0]` están bien en los dos builds. Son, por familia:

- `src/battle/xc_1BC010.c:50-56`, `xc_1BC230.c:54-57`, `xc_1BC440.c:50-53`, `xc_1BC840.c:50-53`,
  `xc_1BC970.c:50-53` (`IS_PTCL` → `0x001BC188`), con `#ifdef __mips__` para el decomp.
- `src/battle/xc_1C0488.c`, `xc_1C06A0.c`, `xc_1C08B8.c`, `xc_1C0B30.c` (`IS_PTCL4` → `0x001C05F8`).
- `src/battle/xc_1C6E20.c`, `xc_1C6F90.c`, `xc_1C7150.c`, `xc_1C74F8.c` (`IS_RIBBON` → `0x001C6E40`).
- `src/battle/xc_1B3378.c`, `xc_1B3630.c`, `xc_1B37D0.c`, `xc_1B3C98.c` (`IS_CHAIN2` → `0x001B2FD0`,
  `IS_RAY` → `0x001B3E68`).
- `src/battle/xc_1CAF98.c`, `xc_1CB140.c`, `xc_1CB350.c` (`IS_MOD1CB` → `0x001CB078`).
- `src/battle/xa_1437D0.c:364/374/385` (`0x00143C38`), `src/battle/eft_b_1312C8.c:436/450` y
  `src/battle/eft_b_c13A518.c:437` (`0x00131760`), `src/battle/eft_e_13A460.c:228` y
  `src/battle/xa_13A558.c:239` (`0x0013A8B8`).
- `port/eq/1A7C60.c:26` (`0x001A7FA0`), `port/eq/13A4B0.c:8` (`0x0013A8B8`), `port/eq/1A6688.c:7` y
  `1A6720.c:7` (`0x001A68A8`), `port/eq/1B3778.c:10` (`0x001B2FD0`), `port/eq/1BC918.c:10` (`0x001BC188`),
  `port/eq/1C74A0.c:10` (`0x001C6E40`), `port/eq/1CCC68.c:10` (`0x001CC770`).
- `port/eq/194E70.c:9`, `194F60.c:9`, `195098.c:9`, `1950E0.c:9`, `195128.c:10` (`0x00194948`);
  `port/eq/19D758.c:8`, `19D7B0.c:11` (`0x0019C868`); `port/eq/19F8F8.c:7`, `19F940.c:7` (`0x0019FAC8`);
  `port/eq/1A0C28.c:18` (`0x0019FFA8`); `port/eq/182C00.c:9` (`0x00183228`).
- `port/eq/1EBA20.c:11`, `1EBB00.c:11` (`0x001EB270`), y los equivalentes constantes de `src/auto`
  (`m2c_182AB8.c:8`, `m2c_182BB0.c:8`, `m2c_1A0B90.c:12`, `m2c_1B5630.c:9`).
- `port/eq/1917B0.c:12`, `191838.c:11`, `191A18.c:9` (`0x00191238`) — mismos updates que los sitios rotos,
  pero bien hechos.

Por qué son correctos: (a) desreferencian `cls` una vez (`cls[0]`), que es lo que hace el asm; (b) comparan
contra la constante de la dirección PS2, y la tabla en RAM (data original cargada por `load_elf`) guarda
exactamente esa dirección; el `#ifdef __mips__` solo cambia la forma de escribir la misma constante y mantiene
el matching. Verifiqué contra `.data` las 24 constantes de arriba (tabla de §1.3): todas son el primer word de
una tabla de clase.

## 5. No fundamentados / fuera de alcance

- `src/battle/xb_1AC968.c:12` y `src/battle/xh_1EB8D0.c:11`, `src/battle/xh_1EB9C0.c:11` tienen el mismo bug,
  pero **no están en el build**: el yaml usa `src/auto/m2c_1AC968.c` (constante correcta `0x001AC650u`) para
  `0x1AC968`, y `asm` (`cod/0EB8D0`) para `0x1EB8D0`; `port/eq/1EB8D0.c` es la implementación viva. Son
  borradores/duplicados; si alguien los promueve, hay que arreglarlos.
- Hay muchos **stors** de punteros a función del host en campos del juego (`port/eq/10B0C8.c:19`,
  `10B158.c:19`, `132F18.c:98-99`, `277B80.c:56-98`, etc.). No son comparaciones de tabla de clase y no los
  audité; en `bt2full` un puntero `0x40xxxxxx` es código nativo llamable, así que no los puedo declarar rotos
  sin probarlos. Quedan como riesgo relacionado, no como hallazgo.
- No pude verificar el uso efectivo en partida de cada helper (solo que tienen llamadores en C: p. ej.
  `func_00191890` lo llaman `port/eq/16DD90.c:67/143` y `16F2E8.c:52`; `func_00195A58` lo llaman
  `src/auto/m2c_195840.c` y hermanos). No deduzco el síntoma de cada uno.
- El híbrido `port/build/native/bt2` es del 13/10 y no lo probé; el binario que se juega es `bt2full`, así que
  el análisis principal es ése.

## 6. Diffs propuestos (NO aplicados)

Patrón (el mismo de `port/eq/191728.c:13-17`):

```c
#ifdef __mips__
#define XXX_IS_UPDATE(p) ((void *)(p) == (void *)func_XXXX)
#else
#define XXX_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x00XXXXXXu)
#endif
```

### 6.1 `port/eq/191768.c`

```diff
@@
 extern M2C_UNK func_00191238 __attribute__((section(".data")));
 
+#ifdef __mips__
+#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)&func_00191238)
+#else
+#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x00191238u)
+#endif
+
 s32 func_00191768(void *arg0) {
@@
-    if (arg0 != NULL && *(void **)*(u8 **)((u8 *)arg0 + 0x28) == (void *)&func_00191238) {
+    if (arg0 != NULL && BLAST_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
```

### 6.2 `port/eq/191890.c`, `1918F8.c`, `191960.c` (idéntico en los tres)

```diff
@@
 extern u8 func_00191238[] __attribute__((section(".data")));
+
+#ifdef __mips__
+#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)func_00191238)
+#else
+#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x00191238u)
+#endif
@@
-    if (arg0 != NULL && *(u8 **)(arg0 + 0x28) == func_00191238) {
+    if (arg0 != NULL && BLAST_IS_UPDATE(*(void **)*(u8 **)(arg0 + 0x28))) {
```

### 6.3 `port/eq/195A58.c`

```diff
@@
 void func_00195E70(void);
 
+#ifdef __mips__
+#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)func_00195E70)
+#else
+#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x00195E70u)
+#endif
+
 s32 func_00195A58(u8 *arg0) {
@@
-    if (*(void **)v1 != (void *)func_00195E70) {
+    if (!BLAST_IS_UPDATE(*(void **)v1)) {
```

### 6.4 `port/eq/19D808.c`

```diff
@@
 void func_0019C868(void);
 
+#ifdef __mips__
+#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)func_0019C868)
+#else
+#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x0019C868u)
+#endif
+
 s32 func_0019D808(u8 *arg0) {
@@
-    if (*(void **)v1 != (void *)func_0019C868) {
+    if (!BLAST_IS_UPDATE(*(void **)v1)) {
```

### 6.5 `port/eq/1A4AC8.c`

```diff
@@
 extern s32 func_001A45B0[] __attribute__((section(".data")));
 
+#ifdef __mips__
+#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)func_001A45B0)
+#else
+#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001A45B0u)
+#endif
+
 s32 func_001A4AC8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
@@
-        if (*(s32 **)((u8 *)arg0 + 0x28) == func_001A45B0) {
+        if (BLAST_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
```

### 6.6 `port/eq/1B55C8.c`

```diff
@@
 extern u8 func_001B5400[] __attribute__((section(".data")));
 
+#ifdef __mips__
+#define SHOT_IS_UPDATE(p) ((void *)(p) == (void *)func_001B5400)
+#else
+#define SHOT_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001B5400u)
+#endif
+
 void func_001B55C8(u8 *arg0, s32 arg1) {
@@
-        if (*(u8 **)(arg0 + 0x28) == func_001B5400 && !(arg0[0] & 1)) {
+        if (SHOT_IS_UPDATE(*(void **)*(u8 **)(arg0 + 0x28)) && !(arg0[0] & 1)) {
```

### 6.7 `port/eq/1DDCF0.c`

```diff
@@
 extern M2C_UNK func_001DDA10 __attribute__((section(".data")));
 
+#ifdef __mips__
+#define GEYSER_IS_UPDATE(p) ((void *)(p) == (void *)&func_001DDA10)
+#else
+#define GEYSER_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001DDA10u)
+#endif
+
 s32 func_001DDCF0(void *arg0) {
@@
-        if (*(void **)obj == (void *)&func_001DDA10) {
+        if (GEYSER_IS_UPDATE(*(void **)obj)) {
```

### 6.8 `port/eq/1DDD30.c` y `1DDDF8.c` (idéntico)

```diff
@@
 extern s32 func_001DDA10[] __attribute__((section(".data")));
 
+#ifdef __mips__
+#define GEYSER_IS_UPDATE(p) ((void *)(p) == (void *)func_001DDA10)
+#else
+#define GEYSER_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001DDA10u)
+#endif
+
@@
-    if (arg0 != NULL && *(s32 **)((u8 *)arg0 + 0x28) == func_001DDA10) {
+    if (arg0 != NULL && GEYSER_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
```
(`1DDDF8.c` tiene la comparación anidada; mismas dos líneas.)

### 6.9 `port/eq/1EAE10.c`, `1EAE78.c`, `1EAFD0.c` (idéntico)

```diff
@@
 extern u8 func_001E9428[] __attribute__((section(".data")));
 
+#ifdef __mips__
+#define STEAM_IS_UPDATE(p) ((void *)(p) == (void *)func_001E9428)
+#else
+#define STEAM_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001E9428u)
+#endif
+
@@
-    if (arg0 != NULL && *(u8 **)(arg0 + 0x28) == func_001E9428) {
+    if (arg0 != NULL && STEAM_IS_UPDATE(*(void **)*(u8 **)(arg0 + 0x28))) {
```

### 6.10 `port/eq/1EAF68.c`

```diff
@@
 extern u8 func_001E9428[] __attribute__((section(".data")));
 
+#ifdef __mips__
+#define STEAM_IS_UPDATE(p) ((void *)(p) == (void *)func_001E9428)
+#else
+#define STEAM_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001E9428u)
+#endif
+
 void func_001EAF68(u8 *arg0, u8 *arg1, s32 arg2) {
@@
-    if (*(u8 **)(arg0 + 0x28) != func_001E9428) {
+    if (!STEAM_IS_UPDATE(*(void **)*(u8 **)(arg0 + 0x28))) {
```

### 6.11 `port/eq/1EAEE0.c`

```diff
@@
 extern M2C_UNK func_001E9428 __attribute__((section(".data")));
 
+#ifdef __mips__
+#define STEAM_IS_UPDATE(p) ((void *)(p) == (void *)&func_001E9428)
+#else
+#define STEAM_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001E9428u)
+#endif
+
 void func_001EAEE0(void *arg0, f32 farg0) {
@@
-    if (arg0 != NULL && *(void **)*(u8 **)((u8 *)arg0 + 0x28) == (void *)&func_001E9428) {
+    if (arg0 != NULL && STEAM_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
```

### 6.12 `port/eq/1EBC30.c`

```diff
@@
 extern M2C_UNK func_001EB270 __attribute__((section(".data")));
 
+#ifdef __mips__
+#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)&func_001EB270)
+#else
+#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
+#endif
+
 s32 func_001EBC30(void *arg0) {
@@
-    if (arg0 != NULL && *(void **)*(u8 **)((u8 *)arg0 + 0x28) == (void *)&func_001EB270) {
+    if (arg0 != NULL && LOOP_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
```

### 6.13 `port/eq/1EB8D0.c` y `1EB9C0.c` (idéntico)

```diff
@@
 extern s32 func_00129C28(u8 *p, s32 a1);
 
+#ifdef __mips__
+#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)func_001EB270)
+#else
+#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
+#endif
+
@@
-    if (**(u8 ***)(obj + 0x28) != (u8 *)func_001EB270) {
+    if (!LOOP_IS_UPDATE(*(void **)*(u8 **)(obj + 0x28))) {
```

### 6.14 `port/eq/1EB930.c`

```diff
@@
 extern void func_001EB270(void);
 
+#ifdef __mips__
+#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)func_001EB270)
+#else
+#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
+#endif
+
 void func_001EB930(u8 *arg0, s32 arg1) {
@@
-    if (*(s32 *)(*(u8 **)(arg0 + 0x28)) != (s32)func_001EB270) {
+    if (!LOOP_IS_UPDATE(*(void **)*(u8 **)(arg0 + 0x28))) {
```

### 6.15 `port/eq/1EBBC8.c`

```diff
@@
 void func_001EB270(void);
 
+#ifdef __mips__
+#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)func_001EB270)
+#else
+#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
+#endif
+
 void func_001EBBC8(s32 arg0, s32 arg1) {
@@
-    if (*(s32 *)(*(u8 **)((u8 *)arg0 + 0x28)) != (s32)func_001EB270) {
+    if (!LOOP_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
```

### 6.16 `src/auto/m2c_1EB830.c`, `m2c_1EB880.c`, `m2c_1EBB48.c`

```diff
@@
 extern M2C_UNK func_001EB270 __attribute__((section(".data")));
 
+#ifdef __mips__
+#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)&func_001EB270)
+#else
+#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
+#endif
+
@@
-    if ((arg0 != NULL) && (*M2C_FIELD(arg0, s32 **, 0x28) == &func_001EB270)) {
+    if ((arg0 != NULL) && LOOP_IS_UPDATE(*M2C_FIELD(arg0, s32 **, 0x28))) {
```
(En `m2c_1EBB48.c` la línea está anidada, mismo reemplazo.)

### 6.17 `src/auto/perm_1EBA68.c`

```diff
@@
 extern M2C_UNK func_001EB270 __attribute__((section(".data")));
+
+#ifdef __mips__
+#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)&func_001EB270)
+#else
+#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
+#endif
+
 void func_001EBA68(void *arg0, s32 arg1, s32 arg2)
@@
-  if ((arg0 != 0) && ((*(*((s32 **) (((u8 *) arg0) + 0x28)))) == (&func_001EB270)))
+  if ((arg0 != 0) && LOOP_IS_UPDATE((*(*((s32 **) (((u8 *) arg0) + 0x28))))))
```

## 7. Cómo lo verifiqué (reproducible, todo de solo lectura)

```sh
# 1) el update de la tabla y la tabla misma (VA -> offset de .data)
cd BT2-Recomp
python3 - <<'EOF'
import struct,re
f=open('disc/SLUS_214.41','rb').read();base,off=0x33F400,0x240400
print(struct.unpack('<8I',f[off+(0x342018-base):off+(0x342018-base)+32]))
EOF
# -> (0x191238, 0x190f08, ...)

# 2) asm original de un sitio
python3 /tmp/opencode/xr.py   # extractor por rango que usé sobre /tmp/opencode/full.asm
# o: tools/binutils/mips-ps2-decompals-objdump -d --start-address=0x191890 --stop-address=0x1918f8 disc/SLUS_214.41

# 3) qué compara el binario que se juega
nm -n port/build/full/bt2full | grep ' func_00191890$'
objdump -d --start-address=0x401dbde0 --stop-address=0x401dbe30 port/build/full/bt2full
# -> mov $0x401db9a0 (func_00191238 PC), cmp contra cls[0]
```

## 8. Recomendación de aplicación

Un arreglo por vez (regla del proyecto), en este orden: primero los 4 de V1 que en el híbrido ya andan
(`191768`, `1DDCF0`, `1EAEE0`, `1EBC30`; en `bt2full` están rotos por el símbolo), después los V1 con doble
carga que en el híbrido usan un puente (`195A58`, `19D808`, `1EB930`, `1EBBC8`), después los V1 que solo
existen en `bt2full` (`1EB8D0`, `1EB9C0`) y los 4 `src/auto`, y por último los 11 de carga faltante (son los de
riesgo medio porque cambian el resultado de helpers que hoy siempre dan falso). Los archivos `src/auto` son
generados por m2c: si se regeneran, el `#ifdef` se pierde; conviene anotarlo en `docs/`.
