# B14 — Constructo del cuerpo del Special Beam Cannon (SBC): cadena C vs asm

Fecha: 2026-11-11. **Sólo lectura**: no se editó código, no se compiló, no se corrió el juego.
Proyecto: `/home/rexx/Escritorio/BT2-Port/BT2-Recomp`. No se tocó `/mnt/datos2/BT2-Decomp`.

Fuentes usadas:
- `port/eq/{1E4760,1E2020,1E65C8,1E1258,1DFCA0,1DFD28,1E6400,1E5D00,1E0C80,1DF840,129720,129A50,1296A0,129C28,129440}.c`
- `src/auto/m2c_1E6FB8.c`, `port/eq/1E6B30.c`
- asm original: `/tmp/opencode/full.asm` (ELF `disc/SLUS_214.41`), direcciones PS2 citadas abajo
- binario del port: `port/build/full/bt2full` (x86-64), `port/build/gen/full/src/port__eq__1E5D00.nat.c`
- logs: `BT2-test/logs/vivo/20261111-143020.fight.log`, `20261111-144103.fight.log`
- volcados: `/tmp/opencode/ps2save_sbc/eeMemory.bin` (original) y
  `BT2-test/logs/vivo/20261107-010126_ramkey1_f3341.bin`, `20261111-144103_ram1_f4015.bin` (port)

---

## 0. Resumen ejecutivo

**No encontré ninguna divergencia de traducción PS2→PC en la cadena pedida.**
Cada una de las funciones (`1E4760`, `1E2020`, `1E65C8`, `1E1258`, `1DFD28`, `1DFCA0`, `1E6400`, `1E5D00`,
`1E0C80`, `1DF840`) coincide con el asm original: firma semántica, orden de argumentos (incluidos los de pila),
shifts, literales de 64 bits, conversiones float→int, índices de tablas, alpha y campos del paquete.

Los puntos que *parecían* divergencias y no lo son están en §4 (ABI de `s64`, punteros de 4 bytes, `cvt64/ftou`).
El único hallazgo real es **de etiqueta de log** (el TEMP `B14SPR` imprime `A[0x4C]` como “ci”, pero ese campo es
el índice de **slot TEX0**, no el índice de color) — no cambia el dibujo.

Con la cadena descartada, el siguiente constructo a abrir es **qué pasa entre `1E5D00` y el GS**: si el prim se
arma/encola para el cuerpo y, si se arma, si el alpha sale del **CLUT** (los TEX0 del cuerpo son PSMT8 con
`TCC=1`, o sea el alpha **no** es el color de vértice). Instrumentación propuesta en §7.

---

## 1. Cadena del constructo (llamada → función → qué hace → estado en el port)

| # | Llamada / entrada | Función (archivo) | Qué hace | Estado en el port |
|---|---|---|---|---|
| 1 | `1E6FB8` draw de `EftSprite` (`src/auto/m2c_1E6FB8.c`) | carga vf16..19 con `128F90`, llama `1E6B30` | ya validado: `B14DRAW ... hid 0` todos los frames | **OK / no es el filtro** |
| 2 | `1E6B30(work)` (`port/eq/1E6B30.c`) | switch `work[2]`/`work[6]` | casos 0/1/6 → `1DFD28(anim, 0/1)` | coincide con asm |
| 3 | `1DFD28(anim, flag)` (`port/eq/1DFD28.c`) | `1DFCA0(anim, *(s32*)(anim+0x21C0), flag&0xFF)` | pasa el **pack** (`+0x21C0`) como `arg1` | coincide (0x1DFD2C–0x1DFD40) |
| 4 | `1DFCA0(obj, pack, flag)` (`port/eq/1DFCA0.c`) | recorre `*(u8*)(obj+0x21CC)` capas de 0x1B0; salta si `+0x21DA==0` o `+0x21CC==0`; `f12 = *(f32*)(obj+0x21D0)` | `1E1258(entry, pack, flag&0xFF, alpha)` | coincide (0x1DFCA4–0x1DFD24) |
| 5 | `1E1258(layer, pack, flag, fc)` (`port/eq/1E1258.c`) | `+0x16B != 0` → si `+0x16C == 0` `1E2020(layer+0x10, layer+0x60, pack, *(s32*)(layer+0x194), flag&0xFF, fc)`; si no `1E2F60(...)` | tail-call | coincide (0x1E1258–0x1E12B8) |
| 6 | `1E2020(A,B,pack,colorIdx,flag,fc)` (`port/eq/1E2020.c`) | copia A (0x50)/B (0x130); `1E65C8` (TEX0→TW/TH); k0/k1; `312680` (tamaño); color/UV por `B[0x10E]` y `B[0x110]`; ángulo y slot | arma args y llama `1E4760` | coincide (0x1E2020–0x1E2590) |
| 7 | `1E65C8(out,pack,idx)` (`port/eq/1E65C8.c`) | `bits=*(u64*)(pack+(idx&0xFF)*16)`; `out[0]=tab[(bits>>26)&0xF]` (TW); `out[1]=tab[(bits>>30)&0xF]` (TH); `out[2]=0; out[3]=1` | saca TW/TH del TEX0 | coincide exacto (0x1E65C8–0x1E6638) |
| 8 | `312680(out,vec,s)` (recompilado, asm 0x312680) | `out = vec * s` (vmulx) | escala el tamaño por `fc` | asm: `vmulx` con `f12`; el C pasa `s` en f12 |
| 9 | `1E4760(...)` (`port/eq/1E4760.c`) | 4 esquinas `(±hx,±hy,0,1)*esc`, rot Z, `inv(gBtlCamView)*rot`, `+ (fx,fy,fz)`, `129440` para el z, arma `colA/colB` y llama `1E6400` | **núcleo del prim** | coincide (ver §3.1) |
| 10 | `1E6400(p0,colA,colB,c0..c3,stFlag,0,TEX0,depth>>8,white)` (`port/eq/1E6400.c`) | `memset(0x1B0)`; 4 `Vec4_Set` (UVs); `129C28` (complementos); 2× `1296A0` (3 vértices) y 2× `1E5D00` | arma el buffer de vértices y encola 2 paquetes | coincide (0x1E6400–0x1E65C4) |
| 11 | `1E5D00(buf,TEX0,mode,off,white)` (`port/eq/1E5D00.c`) | clip (5 planos) → proyección → 1 paquete 0x80 por triángulo (+ pre/post 0x30 si modo 2/3), con PRIM 0x5B, TEX0, 3 vértices (color, UV, XYZ) | **el prim final** | coincide (0x1E5D00–0x1E63FC) |
| 12 | init de capas: `1DF840` (`port/eq/1DF840.c`) y `1E0C80` (`port/eq/1E0C80.c`) | `+0x21C4` len, `+0x21CC` layers, `+0x21D0` alpha=1.0, `+0x21C0` pack=0; por capa copia 0x1B0 y escala/rota | lo que fija `+0x16B/+0x16C/+0x21D0` | coincide (0x1DF840–0x1DF920, 0x1E0C80–0x1E0E98) |

> `1E2F60` (la otra rama de `1E1258`, `+0x16C != 0`) no está cubierta por el log `B14SPR`; ver §6.

---

## 2. Verificación concreta de las incógnitas que planteó el pedido

1. **`1E4760`: tipo de prim y campos.**
   No arma el prim él mismo: arma las **4 esquinas del quad** (`p0..p3`, floats) y dos bloques de UV
   (`colA = {c0,c1,c0,c3}`, `colB = {c2,c1,c2,c3}`), y se los pasa a `1E6400`, que recién ahí arma los vértices
   y llama a `1E5D00` (el que escribe el paquete). El paquete final es: tag `0xA0000007`, `GIFtag`
   `0xC400000000008001`, lista de registros `0xF42142142160`, `PRIM=0x5B` (triángulo gouraud + texturado +
   alpha blend), `TEX0` = el `u64` del slot, y 3 vértices `{RGBA, Q, S, T, XYZ}` en `q+0x30..0x77`
   (`1E5D00.c:132-153`).
   - **Firma/orden de args**: `1E4760.c:30-32` ↔ asm: `a0..a3` (bytes, `andi 0xff` en 0x1E4764/0x1E47A4-0x1E47B4),
     `t0=hx`, `t1=hy`, `t2=unused6`, `t3=scaleBits` (0x1E4788/0x1E4790/0x1E4798; t2 no se usa), pila
     `+0x00=st0`, `+0x08=stFlag`, `+0x10=stByte`, `+0x18=stPtr` (call site 0x1E237C/0x1E239C/0x1E2398/0x1E23BC
     y lecturas 0x1E4B5C/0x1E4B6C/0x1E4B4C/0x1E4BA8). Todo coincide con el C.
   - **Escala**: `sc = cvt64(scaleBits)*0.000244140625f*0.0625f` (`1E4760.c:57`) ↔ asm 0x1E4860-0x1E4878:
     `lui 0x3980` (2^-12), `lui 0x3d80` (2^-4), `mul.s`. Exacto.
   - **Esquinas**: `(∓w,∓h,0,1)` (`:60-75`) ↔ asm 0x1E48B0-0x1E4A80, incluido el `neg.s` en los 4 casos y
     los stores de `1.0` en `[3]`. Exacto.
   - **Conversión int→float de 64 bits** (`cvt64`, `:17-25`): el asm usa, para negativos,
     `srl lo,1 | andi lo,1 → cvt.s.w → add.s f,f` (0x1E4848-0x1E485C y repetido). El C lo replica bit a bit.
   - **Proyección**: `func_00129440(ctx, p0)` con `ctx = sp+0x20` (`:93`) ↔ asm 0x1E4B2C-0x1E4B48
     (`a0=sp+32`, `a1=p0`, `a2=1`). El tercer arg `a2=1` **no lo usa** el asm de `0x129440`
     (0x129440-0x1294A8 solo toca `a0`/`a1`), así que el prototipo de 2 args en `129440.c:13` es inocuo.
   - **TEX0**: `sv = *stPtr` (`:94`) ↔ asm 0x1E4B5C `ld t4,0(v0)`. **Lee 8 bytes** (64 bits). Ver §5: el
     compilado del port también lo pasa entero (objdump 0x4022FEBE-0x4022FEC6 y `push rax` en 0x4022FF67).
   - **Orden de los 4 colores a `1E6400`**: asm 0x1E4B80-0x1E4B9C:
     `colA={f15,f16,f15,f18}`, `colB={f17,f16,f17,f18}`; C `colA={c0,c1,c0,c3}`, `colB={c2,c1,c2,c3}`
     (`:95-102`). Exacto.
   - **Args de pila a `1E6400`**: asm 0x1E4BA0-0x1E4BAC: `sp+0=0`, `sp+8=sv(64)`, `sp+0x10=ctx[8]>>8`,
     `sp+0x18=stByte`; registro `t3=stFlag`. C `:105-106` pasa `stFlag, 0, sv, ctx>>8, stByte` → misma
     correspondencia (arg7..arg11). Exacto.
   - **Shift `>> 8`**: asm 0x1E4B68 `sra v1,8`; C `:106` `>> 8` sobre `*(s32*)(sp+0x28)`. Exacto.

2. **`1E2020`: `ftou`, switch de color, `k0/k1`, `A[0x4C]`, orden a `1E4760`.**
   - `ftou` (`:17-22`): el asm usa `trunc.w.s` + `lui 0x4f00` (2^31) + `sub.s` + `or 0x80000000`
     (0x1E2224-0x1E2360), **no** `cvt.w.s`. El C replica ese patrón (comparar `>= 2^31`, restar, `| 0x80000000`).
   - Switch (`:46-72`): `B[0x10E]` = `lbu 382(sp)` (0x1E2140), selector `*(s32*)(B+0x110)` = `lw 384(sp)`
     (0x1E2148); tablas `0x343258, 0x343298, 0x3433A8, 0x343318` y `colorIdx*4` (0x1E2198-0x1E21D0).
     El C usa exactamente esas 4 tablas y ese índice. Y el orden de `c[0..3]` coincide
     (`:50-62` ↔ 0x1E21D8-0x1E2200). **Ojo**: las tablas son floats 0..1; en `1E4760` son las **UV**, no el
     color RGBA (el RGBA es `A+0x30..0x3C`).
   - `k0/k1` (`:42-43`): asm 0x1E2104-0x1E2134: `k1 = 1/vec1a0[1]`, `k0 = (vec1a0[0]-1)/vec1a0[0]`; el
     log da `va 128 → k1=0.0078, k0=0.9922` y `va 32 → k1=0.0312, k0=0.9688`. Coherente.
   - `A[0x4C]`: **es el índice de slot TEX0** (`base + idx*16`, 0x1E23A4-0x1E23B4 y `1E65C8` 0x1E65C8+), y
     **no** el índice de color (ese es `colorIdx`, el 4º arg, que viene de `layer+0x194`). El log actual lo
     rotula “ci” y confunde. El uso en ambos lados del C coincide con el asm; no hay bug.
   - Orden de args a `1E4760` (`:92-97`): `a0..a3 = ftou(A+0x30..0x3C)&0xFF`, `t0/t1 = ftou(vec1c0[0/1])`,
     `t2=0`, `t3 = A[0x40]<<12`, pila `0/16/8/24 = 0, flag&0xFF, A[0x48], slot`, `f12..f14 = A+0x10/14/18`,
     `f15..18 = c[0..3]`, `f19 = ang`. Asm 0x1E22F0-0x1E23BC: idéntico (incluido `sll t3,0xc` y `move t2,zero`).
   - Ángulo/slot (`:74-80`): `B[0x10A]==0` → `D_0038566C` y `slot=base+A[0x4C]*16`; si no `D_00385670` y
     `slot=base+(B[0x108]+B[0x109])*16`. Asm 0x1E2218-0x1E2330 y 0x1E2508-0x1E2568. Exacto.

3. **`1E65C8` y `312680`.**
   - `1E65C8`: asm 0x1E65C8-0x1E6638 hace `idx&0xFF`, `×16`, `ld` del `u64`, `>>26 &0xF`, `dsll32/dsra32`
     (sign-extend de 4 bits, siempre 0..15), `×4`, tabla `0x3434A8`; luego `>>30 &0xF` para `out[1]`;
     `out[2]=0`, `out[3]=1`. C `:6-14` exacto. Tabla en el dump: `{0,2,4,8,16,32,64,128,256,512,1024,0,...}`.
   - `312680`: asm 0x312680 `vmulx.xyzw vf6 = vf4 * vf5x` (escalar en f12). El C de `1E2020` pasa `fc` como
     tercer arg (f12). Coincide.
   - **División por cero**: `k1 = 1/vec1a0[1]` es un riesgo latente **solo si el TEX0 tiene TH=0**
     (`tab[0] = 0.0`; índices ≥ 11 de la tabla son basura/0). En el cuerpo los slots usan TW=TH 5/6/7
     (ver §5), así que no se dispara. Queda anotado: en PC `1/0 = +Inf` y en la PS2 el `div.s` no da Inf
     (FPU sin Inf/NaN); si alguna capa usara un TEX0 con TH=0 habría que espejar el resultado. **No es el caso
     del SBC según el pack y el log.**

4. **`1E1258` y `1DFCA0`.**
   - `1E1258`: asm 0x1E1258-0x1E12B8: `a2&0xFF` en `t0` (0x1E1264), `lbu layer+0x16B` (0x1E1268),
     `lbu +0x16C` (0x1E1274), `lw +0x194` (0x1E1280); tail-calls a `1E2020` con
     `a0=layer+0x10, a1=layer+0x60, a2=arg1, a3=+0x194, t0=flag&0xFF, f12=fc` (0x1E1288-0x1E1294) o a
     `1E2F60` con `a0=+0x10, a1=+0x60, a2=arg1, a3=flag&0xFF, f12=fc` (0x1E1298-0x1E12A8). C `:8-14` exacto.
   - `1DFCA0`: asm 0x1DFCA0-0x1DFD24: `a2&0xFF` (0x1DFCB0), chequeos `+0x21DA`/`+0x21CC`
     (0x1DFCC4/0x1DFCD0), `f12 = lwc1 +0x21D0` (0x1DFCE0), loop con `s1 += 0x1B0` y `i < +0x21CC`
     (0x1DFCDC-0x1DFD04). C `:9-24` exacto.
   - `1DFD28`: asm 0x1DFD28-0x1DFD40: `a2 = a1&0xFF`, `a1 = lw *(a0+0x21C0)`, tail `1DFCA0`.
     C `:6` exacto. El `B14DRAW ... pack 01bcef00` del log **es** ese `*(u32*)(anim+0x21C0)`: la cadena usa el
     pack correcto.

5. **Init de capas (`1E0C80`, `1DF840`).**
   - `1DF840`: asm 0x1DF840-0x1DF920: `memset(arg0,0,0x21E0)` (0x1DF894-0x1DF898), `+0x21C4 = *(f32*)(arg1+0x1A4)`
     (0x1DF89C-0x1DF8AC), `+0x21CC = *(u8*)(arg1+0x1A0)` (0x1DF8B0-0x1DF8B8), `+0x21D0 = 1.0` (0x1DF8A0-0x1DF8C4),
     `+0x21D9 = *(u8*)(arg1+0x19C)`, `+0x21DA = 1`, `+0x21C0 = 0`, loop de `1E0C80` con stride 0x1B0.
     C `:16-30` exacto. (`+0x16B/+0x16C` **no** los escribe la init: vienen copiados del template de 0x1B0 que
     recibe de `arg1`, o sea de los datos del efecto, no de una traducción.)
   - `1E0C80`: asm 0x1E0C80-0x1E0E98: copia 0x1B0, `fs = farg0 ?: 1`, `*(s32*)arg0 < 4` → `+0x164=0,+0x1A8=0`,
     `+0x150..0x15C = arg2[0..3]`, 4× `312680` sobre `+0x120/+0x130/+0x140/+0x110`, `+0x88 += farg1`,
     `1E0EA0`, y el loop `arg3→+0xB0/+0xC0`, `arg4→+0xD0`, `arg5→+0xE0`, `+0x194=0,+0x198=0`,
     `1E1E28(+0x10,+0x60)`. C exacto (con el orden `a0=dest, a1=src, a2..a3, t0,t1` de 0x1DF8E0-0x1DF900).

---

## 3. Comparación C-vs-asm por función (detalle)

### 3.1 `func_001E4760` (0x1E4760–0x1E4C00) vs `port/eq/1E4760.c`

| Ítem | asm | C | ¿Divergencia? |
|---|---|---|---|
| firma/registros | a0..a3 bytes; t0=hx,t1=hy,t2=unused,t3=scale; pila +0/+8/+0x10/+0x18 = st0/stFlag/stByte/stPtr | `(u8 a0..a3, s64 hx,hy,unused6,scaleBits, s32 st0, s32 stFlag, u8 stByte, s64 *stPtr, 8 floats)` | No (ver §4.1) |
| `sc` | ×2^-12 ×2^-4 | `*0.000244140625f*0.0625f` | No |
| esquinas | `neg.s` + stores | `-w/-h` etc. | No |
| rotación | `sceVu0UnitMatrix(rot)`, `WrapAngle(angle)`, `RotMatrixZ(rot,rot,a)`, `InversMatrix(inv,gBtlCamView)`, `MulMatrix(rot,inv,rot)` | mismas 5 llamadas, mismo orden | No (0x1E47F8-0x1E4824 vs `:50-53`) |
| `mul`+`apply` | 0x312448 / 0x312418 | `sceVu0MulMatrix`/`sceVu0ApplyMatrix` | No |
| offset | `func_00312638(p_i,p_i,off)` con `off={fx,fy,fz,0}` | idem | No |
| `1.0` en `[3]` | 0x1E4B38-0x1E4B48 (último en delay slot) | `:89-92` antes del call | No (orden irrelevante) |
| proyección z | `129440(sp+0x20,p0,1)` | `func_00129440((s32*)sp+0x20, p0)` | No (a2 no se usa) |
| TEX0 | `ld t4,0(slot)` | `sv=*stPtr` | No |
| UV | `colA/colB` | idem | No |
| call | `1E6400(p0,colA,colB,a0..a3,stFlag,0,sv,ctx[2]>>8,stByte)` | idem | No |

### 3.2 `func_001E2020` (0x1E2020–0x1E2590)
Todo verificado en §2.2. Diferencia cosmética: el switch de color en C es `switch` y en asm un árbol
`beq/slti`; el resultado es el mismo (incluido el `default` que deja `c[]` como estaba).

### 3.3 `func_001E6400` (0x1E6400–0x1E65C4)
- `memset(buf,0,0x1B0)` ↔ `li a2,432` (0x1E641C).
- 4 `Vec4_Set` (0x129AC0) ↔ asm 0x1E646C-0x1E64D0.
- colores `s3=arg3&0xFF, s5=arg4&0xFF, s6=arg5&0xFF, s7=arg6&0xFF, s4=arg7, s2=arg11` ↔ 0x1E6430-0x1E6454
  (incluido `lbu 680(sp)` = arg11).
- `129C28(s1,s0)`, `129C28(buf+0x210,s0)`, `129C28(buf+0x220,s0)` ↔ 0x1E6500-0x1E6524.
- `1296A0(buf,arg0,buf+0x1B0,s0,3)` ↔ 0x1E6528-0x1E6540; `1E5D00(buf,arg9,s4,arg10,s2)` ↔ 0x1E6544-0x1E6558,
  donde **arg9 = `ld a1,664(sp)`** (TEX0 de 64 bits) y **arg10 = `lw a3,672(sp)`**. Exacto.
- segunda mitad con `arg0+0x10`, `buf+0x1C0`, `s1` ↔ 0x1E655C-0x1E658C. Exacto.

### 3.4 `func_001E5D00` (0x1E5D00–0x1E63FC)
- clip: `tbl=12B9B0()`, 5× `n=129720(obj,obj,tbl,n)`, `tbl+=0x10` ↔ 0x1E5D48-0x1E5D78; `n==0 → return 0` ↔
  0x1E5D7C.
- `129A50(sp, sp+0x90, obj, n)` ↔ 0x1E5D80-0x1E5D90.
- `j=2..n-1`, `vB/vC = sp+0x10*(j-1/j)`, `uB/uC`, `cB/cC = obj+0x20+0x30*(j-1/j)` ↔ 0x1E5D98-0x1E5DF4 y
  0x1E63B4-0x1E63CC (t2/t4/t0 incrementados por 0x10/0x10/0x30).
- clamp `z > 0xFFFFFF → 0xFFFFFF` y `white → z=0xFFFFFF` ↔ 0x1E5DF8-0x1E5E44.
- `small_pkt(0x42/0x49)` para modo 2/3 y post `0x48` ↔ 0x1E5E60-0x1E5F00 / 0x1E6334-0x1E6374.
- `link_pkt` ↔ 0x1E5F08-0x1E5F3C y 0x1E62E0-0x1E6328 (idx/off y `+0xFFF0`).
- cabecera `0xA0000007`, `0xC400000000008001`, `0xF42142142160`, `PRIM 0x5B` ↔ 0x1E5F44-0x1E5F88
  (`li 0x5b` en 0x1E5F58; el `Q`/`ST`/`XYZ` en 0x1E5F8C-0x1E62D4).
- `tag` en `q+0x28` ↔ 0x1E62D0-0x1E62DC (`ld v0,288(sp)` = arg1; `sd v0,40(a3)`).

**Nota sobre `link_pkt` y punteros**: en el C fuente se lee `*(u8**)(slot+4)` (parecería 8 bytes en PC). El build
aplica `ptr32.py`: en `port/build/gen/full/src/port__eq__1E5D00.nat.c:63-65` queda
`u8 * __ptr32 __uptr * __ptr32 __uptr`, es decir puntero de 4 bytes como en PS2. **No es bug.**

---

## 4. Diferencias que *parecen* divergencias y no lo son

### 4.1 `1E4760` declara `s64` donde el original usa ranuras de 32 bits
El asm original pasa `hx,hy,unused6,scaleBits` en `t0,t1,t2,t3` (32 bits) y `st0/stFlag/stByte/stPtr` en pila con
ranuras de **8 bytes** (call site escribe en `sp+0,+8,+0x10,+0x18`; callee lee `504/512/520`). El C del port
declara `s64` para los 4 primeros y `s32/s32/u8/ptr` para los de pila. Como **el único que llama es C**
(`1E2020.c`) y **el que define es C** (`1E4760.c`), la convención es internamente consistente: no hay caller
recompilado con ABI PS2. Verificado en el binario: el TEX0 se pasa con `push rax` (8 bytes) y el callee lo lee
como `u64` (`0x4022FEBE-0x4022FEC6`, `0x4022FF67`), sin truncar.
No es el bug del SBC. (Si algún día se llama desde asm/recompilado, sí habría que ajustar la firma.)

### 4.2 `cvt64` y `ftou` son UB en C
`(s32)lo`, `(s32)x`, y `x<<12` con posibles valores fuera de rango son UB, pero el compilador emite exactamente
lo del asm (`cvttss2si`/`shl`) y los valores reales están en rango (colores 0..255, `A[0x40]` chico, TW/TH 5..7).
No hay evidencia de que se dispare para el cuerpo.

### 4.3 `vtx_pos` usa stores de 32 bits donde el asm hace un read-modify-write de 64 bits
El asm (`0x1E6214-0x1E6240`) conserva el **byte 6** del valor previo y lo OR-ea con el byte alto de `z`
(máscara `0x00ff000000ffffffff`); el C (`1E5D00.c:39-44`) limpia los bytes 4..6 y escribe `z`. Solo difieren si
el byte 6 previo no era 0 (pool reutilizado). No afecta la visibilidad. Diferencia inofensiva/de estilo.

### 4.4 Log `B14SPR`: “ci” no es el índice de color
`1E2020.c:86-90` imprime `A[0x4C]` como `ci`. Ese campo es el **índice del slot TEX0** (`base+idx*16` y
`1E65C8`). El índice de color es `colorIdx` (4º arg = `layer+0x194`). Los `c=...` del log corresponden a
`colorIdx` 2/3, no a `ci=1`. Es un problema de etiqueta, no de lógica.

---

## 5. Evidencia en datos (para sostener que la entrada y el TEX0 están bien)

- **El pack del log es el correcto**: `B14DRAW ... pack 01bcef00` = `*(u32*)(anim+0x21C0)`, y `1DFD28` pasa
  exactamente ese valor a `1DFCA0`→`1E1258`→`1E2020` (`base`). `1E2020` lo usa en `1E65C8` y en
  `slot = base + A[0x4C]*16`.
- **TEX0 de 64 bits e íntegro en RAM**: en `20261107-010126_ramkey1_f3341.bin`, pack `0x01bcef00`:
  - idx0 `2005472555302b88` → `PSM=0x13 (PSMT8)`, `TW=TH=5` (32), `TCC=1`, `CBP=0x2a39`, `CPSM=0`, `CSM=0`, `CLD=0`
  - idx1 `200547a5dd30ab8c` → `PSMT8`, `TW=TH=7` (128), `TCC=1`, `CBP=0x2a3d`
  - idx2 `2005482599302bcc` → `PSMT8`, `TW=TH=6` (64), `TCC=1`, `CBP=0x2a41`
  - idx3 `2000000155300000` → `PSMT8`, `TW=TH=5`, `TCC=0`
  Esos TW/TH **coinciden** con los `va 128.000` (slot 1) y `va 32.000` (slot 0) del `B14SPR`: la lectura
  `slot→TEX0→TW/TH→k0/k1` es coherente. (El volcado es de otra corrida; los tamaños son propiedad estática del
  efecto, por eso se comparan.)
- **El binario del port pasa el TEX0 entero** (`0x4022FEBE-0x4022FEC6`: `mov rax,[stPtr]; mov rax,[rax]` y
  `push rax` antes del call a `1E6400`): el fix de `arg9 u64` documentado en `docs/bugs_open.md` está aplicado.
- **El constructor de paquetes de esa familia produce paquetes en el port**: en
  `20261111-144103_ram1_f4015.bin` hay ≥11 bloques con `PRIM=0x5B` en `X` y un `TEX0 PSMT8/TW=TH=7` en `X+8`
  (p.ej. `0x450450 → 0x20054a45dd30abc0`; base del paquete `0x450430`), con la misma forma que escribe
  `1E5D00`/`12DA70` (`q+0x10=0xC400000000008001`, `q+0x18=0xF42142142160`, `q+0x20=0x5B`, `q+0x28=TEX0`).
  No puedo atribuirlos al cuerpo del SBC en ese frame (el ataque ya había terminado), pero confirman que el
  formato no se pierde en el camino.
- **El clip no debería descartar el cuerpo**: tomando la tabla de planos `0x3886C0` del volcado del port
  (5 planos con normales unitarias y `d`), la posición del log `(612.99,-25.04,288.81)` da
  `dot(p,n)+d ≈ +17,+15,+13,+26,+32` para los 5 planos → **dentro**. (Caveat: la tabla de planos es de otro
  frame/cámara; sirve como control de que los planos están sanos y no en cero.)

---

## 6. Descartes (con el motivo)

| Hipótesis | Resultado |
|---|---|
| `1E4760` arma un prim degenerado / alfa 0 | **no**: arma esquinas y UV y delega; los campos y el TEX0 llegan enteros (§2.1, §5). |
| argumento corrido / literal de 64 bits mal en `1E4760` | **no**: los 20 args coinciden con el call site y con el compilado del port (§2.1, §4.1). |
| `1E2020` `ftou` mal (cvt.w vs trunc.w) | **no**: el asm usa `trunc.w.s`+rebase y el C lo replica (§2.2). |
| `A[0x4C]` tomado como color | **no**: se usa como slot TEX0 en ambos lados; el color es `colorIdx` (§2.2, §4.4). |
| `1/vec1a0[1]` con 0 → Inf en PC | **latente**, no disparado: los slots del cuerpo tienen TH=5/6/7 (§2.3, §5). |
| `1DFD28`/`1DFCA0` pasan mal el pack | **no**: el log y el asm coinciden (`pack 01bcef00` = `*(anim+0x21C0)`). |
| `link_pkt` usa punteros de 8 bytes | **no**: el build aplica ptr32 (§3.4). |
| La init de capas no escribe `+0x16B/+0x16C`/alpha | **no es un bug**: vienen del template de 0x1B0; `+0x21D0=1.0` lo escribe `1DF840` y el log da `fc≈1` (§2.5). |
| El clip (5 planos) descarta el quad | **poco probable**: planos sanos y posición dentro (§5); a confirmar con log en `1E5D00` (§7). |
| El renderer descarta el draw | **no por los filtros conocidos**: TBP 0x2b8c/0x2bc0 no es depth/16-bit/PSMT8H; no cae en `gsSkipWhy[0..4]` (`gs_draw.c:496-560`). Queda el alpha del CLUT (§7). |

---

## 7. Siguiente constructo a abrir + instrumentación propuesta (NO aplicada)

La cadena está descartada. Lo que falta es **demostrar si el prim del cuerpo se arma/encola y cómo llega al GS**.
Orden de probabilidad:

### 7.1 ¿`1E5D00` arma el paquete del cuerpo? (lo más barato y decisivo)
Hoy el log se corta en `1E2020` (antes de `1E4760`/`1E6400`/`1E5D00`). Un log TEMP en `1E5D00` cierra el
diagnóstico: cuántos triángulos sobreviven al clip (`n`), con qué `off`/`mode`, qué TEX0 y qué XYZ proyectados.

```diff
--- a/port/eq/1E5D00.c
+++ b/port/eq/1E5D00.c
@@
     func_00129A50(sp, sp + 0x90, obj, n);
 
     for (j = 2; j < n; j++) {
@@
         vtx_pos(q, 0x40, vA);
@@
         *(u64 *)(q + 0x28) = tag;
+        {   /* TEMP B14SBC: ¿se arma el prim del cuerpo? (sólo lee) */
+            extern void bt2_fightlog_note(const char *fmt, ...);
+            static unsigned n_;
+            if (tag == 0x200547a5dd30ab8cull || (n_++ & 63) == 0)
+                bt2_fightlog_note("B14SBC pkt base %p j %d n %d mode %d off %d tex %016llx "
+                                  "xyz0 %d %d %d xyz1 %d %d %d xyz2 %d %d %d",
+                                  q, j, n, savedMode, off, (unsigned long long)tag,
+                                  *(u16 *)(vA + 0), *(u16 *)(vA + 4), *(u32 *)(vA + 8),
+                                  *(u16 *)(vB + 0), *(u16 *)(vB + 4), *(u32 *)(vB + 8),
+                                  *(u16 *)(vC + 0), *(u16 *)(vC + 4), *(u32 *)(vC + 8));
+        }
         link_pkt(q, mode, off);
```
(El `tag == ...` fijo sirve para la corrida del SBC; en el build final se quita. Si se prefiere no hardcodear,
filtrar por `tag` cuyo `PSM==0x13` y `TW==TH==7`.)

**Qué mirar**: si durante el SBC aparecen `B14SBC pkt` con `off` razonable (z/256) y XYZ dentro de 0..4095*16,
el prim **se arma**; entonces el problema es el consumo (7.2). Si `n` queda en 2 (o `1E5D00` no se llama),
el problema es el clip/proyección y hay que abrir `129720`/`129A50`/`1299A0` contra el asm.

### 7.2 Si el prim se arma: alpha del CLUT (TCC=1)
Los tres TEX0 del cuerpo son `PSMT8, TCC=1, CPSM=0, CLD=0`. Con `TCC=1` el alpha **no** sale del color de
vértice (`A+0x30..0x3C`, p.ej. 99) sino de **la paleta** (`CBP=0x2a39/0x2a3d/0x2a41`). Si la paleta no está
cargada en VRAM en esa dirección, `Gs_ClutRead`/`Gs_Expand` devuelven alpha 0 y el sprite es invisible.
No hace falta tocar código: el renderer ya tiene el log de texturas detrás de `BT3_TEXLOG=<frame>`
(`gs_draw.c:240-248`). Correr la pelea con `BT3_TEXLOG=2540` (el frame del ataque en la sesión 144103) y buscar:

```
texlog: frame ... tbp 2b8c ... psm 13 128x128 cbp 2a3d cpsm 0 ... | N of 16384 texels not black | clut ...
texlog: frame ... tbp 2bc0 ...
```

Si `clut` sale todo 0 (o `0 of ... texels not black`), el cuerpo se dibuja transparente y la causa está en la
**subida de la paleta** (`EftVram_AddTex`/`AddImage` → VRAM), no en el constructo.

### 7.3 Si no hay paquete: `129720`/`129A50`
Son C traducidos (no matching) y son el único punto entre la entrada válida y el paquete que puede devolver
`n==0` en silencio. `129720` usa `u8 fr[0x280]` y el asm tiene frame `-720 (0x2D0)` con locales 0..0x27F:
**el tamaño coincide**; el comentario “antes 0x270” es correcto ahora. Comparar el retorno (`arg3` vs `cnt`) y
`129A50` (proyección con `vf16..19`, `v2.w` de `vf2`) contra el asm 0x129720/0x129A50, con log de `n` después de
cada uno de los 5 planos.

---

## 8. Lo que NO verifiqué

- No corrí el juego ni saqué volcados nuevos: no puedo afirmar si el paquete del cuerpo se arma **en los frames
  del ataque** (el F10 disponible es de un frame posterior).
- No comparé `129720`/`129A50`/`1299A0` palabra por palabra (solo su contrato y el tamaño de frame); si el
  diagnóstico cae ahí, hay que hacerlo.
- No comparé la rama `1E2F60` (`+0x16C != 0`), que no está cubierta por el log.
- No verifiqué el contenido de VRAM ni la subida de la paleta (no hay volcado de VRAM en este repo).
- No revisé `1E6FB8`/`1E6B30` contra el asm en esta pasada (estaban ya validados por el log y por el informe
  `staging/B14_cuerpo_kh_vs_sbc.md`).

---

## 9. Respuesta corta

- **Divergencia más probable en la cadena**: ninguna. La cadena `1E4760→1E2020→1E65C8/312680→1E1258/1DFCA0/
  1DFD28→1E6400→1E5D00` (y la init `1E0C80/1DF840`) coincide con el asm. El punto que queda es **después**:
  ¿se arma/encola el prim? y, si se arma, **alpha del CLUT** (`TCC=1`, PSMT8).
- **Archivo:línea del hallazgo real**: `port/eq/1E2020.c:86-90` (etiqueta “ci” = slot TEX0, no color; corregir
  el texto del log). No hay fix funcional que proponer sin el log de §7.1.
- **Fix propuesto**: instrumentación TEMP de `1E5D00` (§7.1) + corrida con `BT3_TEXLOG=2540` (§7.2). El único
  “fix” de código seguro y trivial es renombrar `ci` por `slot` en el log.
- **Sin mirar**: `129720`/`129A50` en detalle, `1E2F60`, y la subida/estado de la paleta en VRAM.
- **Qué probar**: una pasada del SBC con el build instrumentado de §7.1; en el `.fight.log`, si aparece
  `B14SBC pkt` con XYZ válidos → ir a §7.2 (CLUT); si no aparece → ir a §7.3 (clip/proyección).
