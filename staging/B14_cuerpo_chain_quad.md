# B14 — Cuerpo del SBC/KH: EftChain2, EftQuad y EftRibbon (draw → primitivo, C vs asm)

Fecha: 2026-11-11. **Sólo lectura**: no se editó código, no se compiló, no se corrió el juego.
Proyecto: `/home/rexx/Escritorio/BT2-Port/BT2-Recomp`. No se tocó `/mnt/datos2/BT2-Decomp`.

Fuentes:
- asm original: `/tmp/opencode/full.asm` (ELF `disc/SLUS_214.41`), direcciones PS2 citadas abajo.
- binario del port: `port/build/full/bt2full` (idéntico byte a byte a `BT2-test/bin/bt2`, md5 `91328ae6…`).
- volcados originales: `/tmp/opencode/ps2save_sbc/eeMemory.bin`, `/tmp/opencode/ps2save_kh/eeMemory.bin`.
- volcados del port: `BT2-test/logs/vivo/20261111-144103_ram1_f4015.bin`,
  `BT2-test/logs/vivo/20261111-152745_ram1_f3001.bin`, `…150737_ram1_f3431.bin`.

---

## 0. Resumen ejecutivo

| clase | draw (C) | primitivo final | ancho | veredicto | ¿puede ser el cuerpo? |
|---|---|---|---|---|---|
| **EftChain2** `0x3427E8` | `1B31D8` → `1B2930` → `1B1A20` | **triangle strip** `PRIM=0x5C` | dato del efecto (0.16–0.95 u) × escala de hebra (1.0/2.55) | **fiel al asm** | **no**: es la hélice/cables finos; el ancho chico es de diseño |
| **EftQuad** `0x341FB8` | `18CAC8` → `18D4F0` → `18D7C8` → `12C250`/`12C9E8` | **triángulos** `PRIM=0x5B` | 4 esquinas de ~5–7 u por nodo | **fiel** (camino de draw) | **no en el KH**: la tarea está muerta en el dump del KH; en el SBC son billboards chicos |
| **EftRibbon** `0x3429B0`, **kind 0** | `1C6F90` → `1C55B8` | **triángulos** `PRIM=0x5B` (vía `12E158`) | `work+0x74` viene del juego (1.6 SBC / 12.6 KH) | **BUG REAL de orden de argumentos** | **sí, candidata fuerte**: la cinta queda de área 0 |

**Hallazgo principal:** en `port/eq/1C55B8.c:7` la función `func_00129BD0` está declarada como
`(f32 *src, f32 s, f32 *dst)`, pero `0x129BD0` es **`(dst, src, scale)`** (igual que `Vec3_Scale`).
Las tres llamadas (`:93`, `:111`, `:120`) pasan `(edge, ancho, off)`, o sea el compilador emite
`rdi=edge, rsi=off, xmm0=ancho`; el callee escribe el resultado en **`edge`** leyendo **`off`**
(que sigue en 0). Consecuencia: `off` nunca recibe el ancho, los cuatro vértices de cada tramo
colapsan a los dos extremos, **los triángulos tienen área 0 y la cinta no se rasteriza**.

Esto **no es teoría**: en el volcado del port hay paquetes con el `TEX0` de la cinta
(`0x200544a555302b5c`) con **dos vértices idénticos** (misma XYZ), mientras que los paquetes del
chain (`PRIM=0x5C`) sí tienen vértices distintos (§4).

---

## 1. Cadenas de llamadas

### 1.1 EftChain2 (tipo 7 del dispatch, clase `0x3427E8`)

Tabla de clase verificada en los dos volcados (`0x3427E8`):
`1b2fd0 1b2e68 1b2f70 1b31b8 1b31c0 1b31d8` (update, init, term, …, draw).

| # | llamada | archivo:línea | qué hace |
|---|---|---|---|
| 1 | `func_00150700` (creador tipo 7) | `port/eq/150700.c:29-56` | arma `XcChainArg` y llama `EftChain2_Create` (`:48`) |
| 2 | `EftChain2_Create` | `src/battle/xc_1B3378.c:48-50` | `BtlTaskList_AddTail(gEftChain2List, gEftChain2Class, arg)` |
| 3 | init `func_001B2E68` | `port/eq/1B2E68.c:16-42` | copia el arg, fija flags/type/tex |
| 4 | update `EftChain2_Update` (`0x1B2FD0`) | `port/eq/1B2FD0.c:9-82` | temporización, spawns (`1B2990`), stepping (`1B26B8`), textura (`1B2CD0`) |
| 5 | draw `func_001B31D8` | `port/eq/1B31D8.c:11-26` | hidden/`0x10`, push cámara, `func_001B2930`, pop |
| 6 | `func_001B2930` | `src/auto/m2c_1B2930.c:5-19` | por cada hebra con `flags&1`: `func_001B1A20(work, work, strand)` |
| 7 | `func_001B1A20` | `port/eq/1B1A20.c:22-131` | arma **un quad de 4 vértices** por par (nodo, next) y encola |
| 8 | paquete | `1B1A20.c:86-89` | `tag 0xA0000008`, `GIFtag 0xE400000000008001 / 0x0042142142142160`, **`PRIM=0x5C`** |

Verificación C↔asm (todo coincide):

- ancho del primer nodo: asm `0x1b1b7c` `lwc1 f0,4(s7)` × `0x1b1b84` `lwc1 f12,56(list)` → `Vec3_Scale(0x110, normal, …)`
  ↔ C `1B1A20.c:61`. Ancho del segundo: asm `0x1b1ba8` ↔ C `:62`; nodo siguiente asm `0x1b1c24/0x1b1c40` ↔ C `:70-71`.
- primitivo: asm `0x1b1cd0` `li v0,0x5c` (`0x5C & 7 = 4` = **triangle strip**) ↔ C `:86`.
- cabecera/GIFtag: asm `0x1b1ce0-0x1b1d1c` ↔ C `:87-89` (literales idénticos).
- división por W y armado de vértices/UV/color: asm `0x1b1d20-0x1b1ffc` ↔ C `:90-117`; linking asm `0x1b2000-0x1b204c` ↔ C `:119-128`.
- `func_00129BD0` **no se usa** acá; se usa `Vec3_Scale` con la firma correcta (`1B1A20.c:15`, llamadas `:61,62,70,71,91`).

**Datos del dump (esto cierra la duda del ancho):**

- original SBC, task `0x1b5df40`, work `0x1b5e0c0`, `flags@A40=0x9`, 8 hebras activas:
  anchos por nodo `0.16–0.19` en punta y `0.82–0.95` en el medio; `scale@strand+0x38 = 1.0`.
- port, `…144103_ram1_f4015.bin`, task `0x1b5c200`, work `0x1b5c380`: mismos anchos `0.16–0.95`,
  escalas 1.0 / 2.55. Config del efecto (`0xcd2a00`): `+0x28=0.81`, `+0x2C=0.14` → ancho = `0.81+0.14*rand`.

O sea: **el chain se dibuja como cinta de menos de 1 unidad de ancho a propósito**. Las
“polilíneas grises/blancas de 1-3 px” del video son esto, y es el comportamiento del original.
En el buffer del port hay paquetes reales con `PRIM=0x5C` y `TEX0=0x200548c599302ba8`
(base `0x452980`): vértices `(36693,34803)` y `(36584,35016)` → **triángulo no degenerado**.

### 1.2 EftQuad (tipo 6, clase `0x341FB8`)

Tabla `0x341FB8`: `18c4e8 18c3c8 18cba8 18ca90 18cb30 18cac8`.

| # | llamada | archivo:línea | qué hace |
|---|---|---|---|
| 1 | `func_001503E0` (creador) | `port/eq/1503E0.c:21-36` | `EftQuad_Create` + setters |
| 2 | update `func_0018C4E8` | `port/eq/18C4E8.c:20-193` | stepping de nodos (`pt`), vida/alpha, `18D298` |
| 3 | draw `func_0018CAC8` | `src/auto/m2c_18CAC8.c:6-15` | `hidden` y `func_0018D4F0(work, res[0x9C], res[0xAC])` |
| 4 | `func_0018D4F0` | `port/eq/18D4F0.c:8-39` | UVs `0.015625/0.984375`, por nodo `18D7C8(..., useAlt=flag)` |
| 5 | `func_0018D7C8` | `port/eq/18D7C8.c:14-107` | 4 esquinas + UV + color → `12C250` (o `12C9E8`) ×2 |
| 6 | `func_0012C250` → `12E158` | `port/eq/12C250.c:10-83`, `12E158.c:36-75` | clip + **triángulos** `PRIM=(fanFlag<<6)|0x1B` |
| 7 | `func_0012C9E8` | `port/eq/12C9E8.c:21-125` | fan de triángulos, **`PRIM=0x5B`** (`:74`) |

Verificación C↔asm de los saltos que importan:

- `18CAC8` ↔ asm `0x18cafc-0x18cb10`: `a1 = *(res+0x9C)`, `a2 = *(res+0xAC)`, tail a `18D4F0`. C `m2c_18CAC8.c:13` exacto.
- `18D4F0` ↔ asm `0x18d634` (setup `0x18d60c-0x18d630`): `a0=node+0x70`, `a1=mtx`, `a2=v50`, `a3=v60`,
  `t0=node+0x40`, `t1=arg1`, `t2=node[0xF0]`, `t3=0`, pila `+0=flag`, `+8=*(work+0)` ↔ C `18D4F0.c:37`.
- `18D7C8` ↔ asm `0x18d98c` (`12D868`), `0x18dae8` (`12C250`), `0x18db14` (`12C9E8`): mismos registros
  (`a0=sp+0x170`, `a1=sp`, `a2=1`, `a3=0`, `t0/t1=0`, `t2=TEX0`, `t3=key`) ↔ C `:56,82,84`.
- primitivo: `12E158.c:73-75` (`0x5B` / `0x1B`, ambos tipo triángulo) y `12C9E8.c:73-76` (`0x5B`).

**No encontré divergencia de traducción en el draw del quad** (sí hay un `TEMP TEX0` de otra
investigación en `12C9E8.c:111` y `12E158.c:96`, que sólo loguea).

Datos: en el SBC la tarea `0x1b6b800` está viva, `res=0xcd12c0`, nodos en `(0,0,z)` con
`z=1259…831` y escala `+0xB4≈2.09`; las 4 esquinas de un nodo (`node+0x70`) abarcan ~5–7 unidades
(`1145.9,-480.0,49.2` … `1150.5,-481.6,59.3`). En el KH esa tarea está **muerta** (`flags 0xff`,
work en cero). No es un cilindro ni el cuerpo del KH.

### 1.3 EftRibbon (tipo 2, clase `0x3429B0`, **kind 0**)

Tabla `0x3429B0`: `1c6e40 1c6cf8 1c6e20 1c6f70 1c6f78 1c6f90`.

| # | llamada | archivo:línea | qué hace |
|---|---|---|---|
| 1 | `func_0014FB50` (creador tipo 2) | `port/eq/14FB50.c:19-65` | `EftRibbon_Create`, setea tamaño/fade |
| 2 | update `EftRibbon_Update` (`0x1C6E40`) | `src/battle/xc_1C6E20.c:57-77` | `func_001C5320` (stepping) + `func_001C6B28` (textura) |
| 2b | stepping `func_001C5320` | `port/eq/1C5320.c:14-114` | **escribe `work+0x74`** = ancho = `(prm[4] * arg[0x0C]) * ramp` (`:87`) |
| 3 | draw `EftRibbon_Draw` (`0x1C6F90`) | `src/battle/xc_1C6F90.c:48-67` | hidden; kind 0 → `func_001C55B8`; kind 1 → `func_001C6278` |
| 4 | `func_001C55B8` | `port/eq/1C55B8.c:48-162` | por par (nodo,next): normal de cámara, ancho, 2 triángulos (`12C250`) |
| 5 | `func_0012C250` → `12E158` | `12C250.c:10-83`, `12E158.c:36-75` | **triángulos** `PRIM=(fanFlag<<6)|0x1B` |

El draw `1C6F90` coincide con el asm `0x1c6fac-0x1c7018` (`hidden(chr=work+0x14, type=work+0x10)`,
kind en `work+0x54`, `tex=work+0x4C`, `a1=work`, `a2=work+0x10`).
El ancho **no** sale de la cámara: sale del juego (`1C5320.c:87`) y está en `work+0x74`; el valor de
los dumps es no nulo (§2).

---

## 2. Divergencias C vs asm

| # | clase | C (archivo:línea) | asm (dirección) | divergencia | efecto |
|---|---|---|---|---|---|
| **1** | **EftRibbon** | `port/eq/1C55B8.c:7` (declaración), `:93`, `:111`, `:120` (llamadas) | `0x1c5828-0x1c5838`, `0x1c5920-0x1c5930`, `0x1c5994-0x1c59a0`; firma en `0x129bd0` | **orden de argumentos invertido en `func_00129BD0`** | cinta kind 0 con ancho 0 → invisible |
| 2 | EftChain2 | — | — | ninguna | — |
| 3 | EftQuad | — | — | ninguna (camino de draw/prim) | — |

### 2.1 Detalle de la divergencia de la cinta

La función real `0x129BD0` (asm `/tmp/opencode/full.asm:42571`) es:

```
129bd0: lqc2  $vf4,0(a1)      ; src = a1
129bd4: mfc1  t0,$f12         ; escala = f12
129bdc: vmulx.xyz $vf4,$vf4,$vf5x
129be4: sqc2  $vf4,0(a0)      ; dst = a0
```

Es decir `func_00129BD0(dst, src, scale)` (es el `Vec3_Scale` del port: símbolo en
`0x40179860`, `movups (%rsi)` + `movups %xmm0,(%rdi)`).

`1C55B8.c:7` la declara al revés:

```c
void func_00129BD0(f32 *src, f32 s, f32 *dst);
...
func_00129BD0(edge, *(f32 *)(rib + 0x74), off);   /* :93  */
func_00129BD0(edge, *(f32 *)(rib + 0x78), off);   /* :111 */
func_00129BD0(edge, *(f32 *)(rib + 0x78), off);   /* :120 */
```

Con esa declaración, el compilador pasa `rdi=edge, rsi=off, xmm0=ancho`; el callee (que espera
`rdi=dst, rsi=src, xmm0=scale`) calcula **`edge = off * ancho`** y deja **`off` en cero**.

El asm original, en cambio, pasa `a0=sp+0x230` (el buffer `off`), `a1=s1` (`edge`) y `f12=ancho`:

- `0x1c5828`: `move a1,s1`; `0x1c582c`: `addiu v0,sp,560`; `0x1c5830`: `lwc1 f12,116(s6)`;
  `0x1c5834`: `jal 0x129bd0` con `a0=v0` (delay slot `move a0,v0`). → `Vec3_Scale(off, edge, rib[0x74])`.
- `0x1c5920`: `addiu a3,sp,560`; `0x1c5924`: `lwc1 f12,120(s6)`; `0x1c5928`: `move a0,a3`;
  `0x1c592c`: `jal 0x129bd0`. → `Vec3_Scale(off, edge, rib[0x78])`.
- `0x1c5994`: `lw a0,1080(sp)` (= puntero a `off`); `0x1c5998`: `move a1,s1`;
  `0x1c599c`: `jal 0x129bd0`. → idem.

Y `off` se inicializa en cero en `1C55B8.c:70` (asm `0x1c55ec-0x1c569c`: `memset(sp+0x230,0,16)`),
y sólo lo escriben esas tres llamadas. Por eso queda siempre 0.

Después, los vértices se arman con `off`:

```c
Vec3_Sub(stripA + 0, (f32 *)(node + 0x10), off);   /* :95  */
Vec3_Add(stripA + 4, (f32 *)(node + 0x10), off);   /* :96  */
Vec3_Sub(stripA + 8, (f32 *)(next + 0x10), off);   /* :103 */
Vec3_Add(stripA + 12, (f32 *)(next + 0x10), off);  /* :104 */
```

Con `off=0`, `stripA[0]==stripA[4]` y `stripA[8]==stripA[12]` → los dos triángulos de cada tramo
tienen **área 0** (en `12E158`, `p0==p1` o `p1==p2`). El resto de la función (UVs, colores, packet,
linking) coincide con el asm: p. ej. el `TEX0` se lee de `work+8+0x140+node[4]*8` en ambos
(asm `0x1c5a28` `addiu a3,s6,8`, `0x1c5a38` `sw a3,1084(sp)`, `0x1c5b58` `ld t2,320(v0)`;
C `:139`).

### 2.2 Evidencia runtime de la cinta colapsada

En `20261111-144103_ram1_f4015.bin` (la cinta está viva: task `0x1af6400`, work `0x1af6e00`,
`kind=0`, `work+0x74=0.535`, cadena de 6+ nodos desde `0x1aed180`) hay paquetes con el `TEX0` de la
cinta (`0x200544a555302b5c`) y **vértices coincidentes**:

```
base 0x4586e0  PRIM=0x5b  TEX0=200544a555302b5c
   v0 XYZ 33684 32874 16711983   ST 0.00047703 0
   v1 XYZ 33684 32874 16711983   ST 0.00047703 0.0233745   <-- v0 == v1 (área 0)
   v2 XYZ 32327 32645 16711863   ST 0.0141153  0
base 0x458210
   v1 == v2  (32327 32645 16711863)
```

Comparado con los paquetes del **chain2** (base `0x452980`, `PRIM=0x5c`, `TEX0=0x200548c599302ba8`),
cuyos vértices sí difieren (el triángulo tiene área):

```
v0 XYZ 36693 34803 16711924
v1 XYZ 36584 35016 16711923
v2 XYZ 37267 35023 16711920
```

Ese patrón (`v0==v1` en un triángulo y `v1==v2` en el otro) es exactamente el que predice `off=0`
en el strip (triángulos `(A,A,B)` y `(A,B,B)`).

### 2.3 Datos de la cinta (input sano)

| dump | task | work | kind | ancho `work+0x74` | cadena |
|---|---|---|---:|---:|---|
| orig SBC | `0x1af8140` | `0x1af8b40` | 0 | **1.617** | head `0x1aeef10`, 8+ nodos (`next` en `+0x40`) |
| orig KH | `0x1af8140` | `0x1af8b40` | 0 | **12.600** | head `0x1aef460`, 8+ nodos |
| port 144103 | `0x1af6400` | `0x1af6e00` | 0 | 0.535 | head `0x1aed180`, 6+ nodos |
| port 152745 | `0x1af6400` | `0x1af6e00` | 0 | 2.250 | head `0x1aed180`, 6+ nodos |

O sea: la cinta **existe, está viva, tiene nodos y ancho no nulo** en los dos lados; el único
problema es que el draw la colapsa. (Esto corrige el §4 de `B14_cuerpo_kh_vs_sbc.md`: la cinta del
KH **no** tiene 1 nodo; el `next` está en `node+0x40`, no en `+0x60`, y hay 8+ nodos.)

Dato adicional: el color del paquete de cinta es `RGBA=(168,159,124,136)` (amarillo pálido, alpha
136/255 ≈ 53%); coincide con la descripción “cintas amarillas, relleno al ~45%”. La cinta es, con
alta probabilidad, al menos parte de la banda que falta.

---

## 3. Fix propuesto (ordenado por probabilidad)

### 3.1 Fix #1 — corregir el orden de `func_00129BD0` en `port/eq/1C55B8.c` (NO aplicado)

```diff
--- a/port/eq/1C55B8.c
+++ b/port/eq/1C55B8.c
@@
-void func_00129BD0(f32 *src, f32 s, f32 *dst);
+void func_00129BD0(f32 *dst, f32 *src, f32 s);
@@
-            func_00129BD0(edge, *(f32 *)(rib + 0x74), off);
+            func_00129BD0(off, edge, *(f32 *)(rib + 0x74));
@@
-                    func_00129BD0(edge, *(f32 *)(rib + 0x78), off);
+                    func_00129BD0(off, edge, *(f32 *)(rib + 0x78));
@@
-                func_00129BD0(edge, *(f32 *)(rib + 0x78), off);
+                func_00129BD0(off, edge, *(f32 *)(rib + 0x78));
```

Es un cambio de 4 líneas y no toca la lógica: después del fix `off` recibe `edge*ancho` y los
vértices `pos±off` quedan separados por `2*ancho`, como en `0x1c5828`/`0x1c592c`/`0x1c599c`.

**Nota (no hace falta para el arreglo):** `port/eq/192B38.c:8` tiene la misma declaración invertida
y `:90` la llama `func_00129BD0(s0, *(f32*)(e+0xE0), s0)`; ahí `src==dst`, así que el error es
inocuo. Si se corrige el prototipo allí, dejarlo igual (`dst=src=s0`).

**Qué probar:** un SBC y un KH en el port. La cinta kind 0 debería aparecer como banda (KH: ancho
~12.6 u; SBC: ~1.6 u, más fina). Si aparece la banda del KH pero en el SBC sigue faltando el cono
ancho, el SBC tiene además otro constructo (ver §5).

### 3.2 Fix #2 (sólo si tras #1 sigue faltando la banda ancha del SBC)

No hay un segundo fix de traducción identificado en chain/quad/ribbon. El siguiente paso es
instrumentar/abrir el constructo que quede:

1. **EftRay** (tipo 8, clase `0x342818`, draw `1B4240 → 1B45E0`): ya está descripto como anillo de
   chispas, pero es el único draw de “rayo” con `TEX0` propio; verificar `1B45E0` contra asm si el
   cono del SBC no aparece.
2. **Mesh/modelo de la técnica** (hipótesis viva de `B14_investigacion_kamehameha.md`): el KH puede
   tener además un mesh; el fix de la cinta no lo cubre.
3. **EftSprite de 5 capas** (`1E6FB8`): ya validado como humo/polvo (CLUT negra), no es el cuerpo.

---

## 4. Descartes (con motivo)

| hipótesis | resultado |
|---|---|
| El chain2 dibuja **líneas** en vez de triángulos | **no**: `PRIM=0x5C` = triangle strip, en C (`1B1A20.c:86`) y en el paquete real (base `0x452980`). |
| El ancho del chain se multiplica por algo en 0 | **no**: ancho = `seg[+4]`/`seg[+8]` × `strand+0x38`; el dato es 0.16–0.95 y la escala 1.0/2.55, igual en original y port (`1B1A20.c:61-62,70-71`; asm `0x1b1b7c`, `0x1b1ba8`). El chain *es* fino por diseño. |
| El quad está mal orientado / UV en cero | **no** en el camino de draw: UVs `0.015625/0.984375` (`18D4F0.c:26-34`), args y primitivo coinciden con asm (`0x18d634`, `0x18dae8`, `0x18db14`); el quad es chico (~5–7 u) y en el KH está muerto. |
| El ancho del ribbon sale de la cámara y da 0 en el port | **no**: sale del juego (`1C5320.c:87` escribe `work+0x74`); en los dumps es 1.6/12.6 (original) y 0.5/2.25 (port). El 0 aparece **después**, por el argumento invertido de `129BD0`. |
| La cinta del KH tiene 1 solo nodo (informe previo) | **falso**: `next` está en `node+0x40`; el dump del KH tiene 8+ nodos (`0x1aef460 → 0x1aef4b0 → …`). |
| El renderer descarta la cinta | no hace falta: los paquetes salen con área 0 (dos vértices idénticos), el GS no tiene nada que rasterizar. |

---

## 5. Lo que NO verifiqué

- No corrí el juego ni compilé: el fix es propuesto, no probado.
- No comparé **palabra por palabra** el update del quad (`18C4E8`, 193 líneas) ni el stepping de la
  cinta (`1C5320`), sólo su contrato y los campos que usa el draw.
- No verifiqué el **contenido de VRAM/CLUT** de la textura de la cinta (`TEX0 0x200544a555302b5c`);
  si además la paleta estuviera mal, la cinta podría seguir sin verse aun con ancho correcto.
- No identifiqué el draw del **cono ancho del SBC** (el informe previo lo llama “mesh de la técnica”);
  el ancho de la cinta del SBC en el dump es 1.6 u, así que puede ser el cable fino y no el cono.
- No revisé la rama kind 1 (`1C6278`) porque los dumps del KH/SBC tienen `kind=0`; su uso de
  `func_00129BB8` sí tiene la firma correcta.

---

## 6. Evidencia reproducible (comandos)

```bash
# tabla de clase en el dump original (offset = dirección PS2)
python3 - <<'EOF'
import struct
d=open('/tmp/opencode/ps2save_kh/eeMemory.bin','rb').read()
for c in (0x3427E8,0x341FB8,0x3429B0):
    print(hex(c),' '.join('%08x'%v for v in struct.unpack_from('<6I',d,c)))
EOF

# cinta del KH: task 0x1af8140 -> work 0x1af8b40; kind=+0x54, ancho=+0x74, head=+0, next=+0x40
# chain2 del SBC: task 0x1b5df40 -> work 0x1b5e0c0; hebras en +0x40, ancho del nodo en +4/+8

# asm: firma real de 0x129BD0 y llamadas desde 0x1C55B8
sed -n '42571,42579p' /tmp/opencode/full.asm
sed -n '201000,201005p;201062,201067p;201091,201094p' /tmp/opencode/full.asm

# binario del port: llamada compilada (rdi=edge, rsi=off, xmm0=ancho) y Vec3_Scale
objdump -d --start-address=0x40210805 --stop-address=0x40210820 port/build/full/bt2full
objdump -d --start-address=0x40179860 --stop-address=0x401798a5 port/build/full/bt2full
```
