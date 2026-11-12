# F7 — Ataque de ki cargado (mantener Triangle) y R1 en free roam

**Solo lectura.** No se aplicó ningún cambio. Fecha: 2026-11-11.
Referencias: ELF `disc/SLUS_214.41` (desensamblado en `/tmp/opencode/full.asm`), árbol `port/eq`, `src/auto`, `src/battle`.

## 0. Resumen ejecutivo

- El camino del Triangle mantenido es: pad crudo → `func_00207630` (palabras `+0x48/+0x4C/+0x50` y contadores) →
  `BtlPad_TestStep(3)` (Triangle sostenido exactamente 6 frames) → `func_0023C798(chr, 0x44F)` (bit `0x8`) → acción
  `0x88` (carga) → al soltar, `func_00226510` pasa a `0x89` (disparo).
- **CAUSA ENCONTRADA (con la corrida CARGA8):** `port/eq/2267D8.c` tiene la condición **invertida** respecto del
  asm `0x2267D8`. Es el `decide` de la acción 0x88: el original devuelve -1 (se queda en 0x88) cuando
  `func_001FA288(chr,0x89) == 0`; el port hace lo contrario, llama a `func_0023C710` (que devuelve 6) en ese caso.
  Por eso la acción 0x88 dura **un frame**: entra, incrementa `a10`, y al frame siguiente el decide la manda a 6.
  El resto del camino (`207630`, `207D40`, `23C798`, `208738`, `241718`, `BtlMember_HasKi`, `1F9FB0`) coincide con
  el asm; la sonda confirmó `step3=1`, `pass=1`, `f758=1`, `a10=0<5`.
- El dato nuevo `tiene = 13.499.520 (0xCE0000)` **no es ki**: es un puntero a la entrada de técnica del slot 3.
  `costo = 60000` sí es ki (3 barras de 20000; el ki va de 0 a 100000) y `alcanza = 0` sólo dice
  `gauge+0xC < 60000`. La sonda no imprime `gauge+0xC`, así que todavía no se puede concluir que sea un bug.
- Además, esa sonda (`TECNICA-*`) mide la tabla de **técnicas especiales** (`+0x980`, `func_00241718`), no la tabla de
  **acciones** que usa el blast cargado (`+0x978`, `func_00240438`). Para el ataque cargado hay que sondear otra cosa.
- ~~La condición que más encaja es `func_00218758` (tope de proyectiles)~~: **descartada por la corrida CARGA8**,
  que dio `f758=1`, `pass=1`. El bloqueo no estaba en 23C798 sino en el decide de la acción 0x88 (sección 2bis).
- **Segunda causa (corrida 20261111-192507):** `port/eq/1FA288.c` devuelve 1 cuando el estado ya es 0x89 pero el
  flag 2/0x1 (clip terminado) está en 0; el asm devuelve 0 en ese caso. Por eso, al arrancar el clip 0x89 (13 frames), el `decide` de 0x88 cree que ya terminó,
  pasa a la acción 6 y el enter de 6 pisa la animación con el idle (2/71). El evento del clip 0x89 nunca corre.
  Fix: `return 1` → `return 0` (sección 4ter).
- Encontré un bug real pero **latente**: `src/auto/m2c_2411E0.c` perdió el segundo argumento de `func_002411E0`
  (el asm reenvía `a1` a `func_002411A0`). Hoy funciona de casualidad porque los llamadores dejan el slot en `rsi` y
  el wrapper no toca `rsi`. No explica el síntoma; se propone el fix igual (sección 5).

## 1. Cadena del “Triangle mantenido”

Todo el código de batalla usa la tabla de pad de 0x180 bytes por jugador en `D_003B0B00` (crudo: `held` en
`+0x134`, flanco en `+0x144`), **no** el layout de `include/sys/pad.h` (ese header parece heredado de BT3:
`held +0x148`, `gameHeld +0x188`, entrada 0x1C0). Ver `port/eq/107860.c:63`, `port/eq/3C48F8.c:28`, y la entrada
cruda leída por el port en `port/full/gs/gs_input.c`.

| Paso | Dónde | Qué hace |
|---|---|---|
| 1 | `port/eq/207630.c:22-118` | `func_00207630`: arma `chr+0x48` (held), `chr+0x4C` (pressed), `chr+0x50` (released) desde `chr+0x20` y el `prev` (`chr+0x44`). |
| 2 | `port/eq/207630.c:119-138` | actualiza los tres contadores por bit (`+0xDC` held, `+0xFC` not-held, `+0x11C` since-press). Sólo corre si `!(D_003876A0+0x4D8 & 0x3800)`. |
| 3 | `port/eq/207340.c:28-35` | tabla de máscaras: `mask[1] = func_00207298(chr, 3)`; con el keyConfig por defecto `{2,1,0,3,...}` y `D_0036F940 = {CIRCLE,CROSS,SQUARE,TRIANGLE,...}` eso da **TRIANGLE**. |
| 4 | `src/battle/xd_207BF0.c:31-38` | `BtlPad_Test48/4C/50` = `word & mask[key]` sobre `+0x48/+0x4C/+0x50`. |
| 5 | `port/eq/207D40.c:27-45` | `BtlPad_TestStep(2)` = Triangle **soltado** con `count11C < 7` (tap); `TestStep(3)` = `Test48(key1)` y `count11C(key1) == 6` (mantenido 6 frames) y L2 no held. |
| 6 | `port/eq/228118.c:48` | la acción **6** (idle de pie) decide con `func_0023C798(obj, 0x44F)`. `0x44F` incluye el bit `0x8`. |
| 7 | `port/eq/23C798.c:78-92` | bloque `arg1 & 8`: `TestStep(3)` + `func_00218758` + `chr+0xA10 < func_0023F8F8` + `HasKi(chr, func_00240438(chr,3))` → devuelve **0x88**. |
| 8 | `port/eq/226488.c` / `226510.c:44-56` | acción `0x88`: guarda el progreso de carga en `chr+0xA1C`; si `Test48(key1) == 0` (Triangle soltado) pasa a `0x89` (disparo). |
| 9 | acción `0x17` (vuelo) | `port/eq/22DB30.c:25` también llama `func_0023C798(obj, 0x133)`, otro mask con el bit `0x8` (para el estado de vuelo). |

En criollo: el tap sale por `TestStep(2)` → `0x87`; el mantenido sale por `TestStep(3)` → `0x88`. Los dos usan el
mismo contador `count11C` y la misma palabra `+0x4C`.

## 2. Comparación con el asm (piezas “normal vs cargado”)

| Archivo:línea | Asm | Veredicto |
|---|---|---|
| `port/eq/207630.c:116-118` | `0x207AEC-0x207B08`: `nor`/`and` → `+0x48 = a1v`, `+0x50 = prev & ~a1v`, `+0x4C = a1v & ~prev` | fiel |
| `port/eq/207630.c:119-138` | `0x207B30-0x207BC8`: reset/incremento por bit, tope 100, `s8` | fiel |
| `port/eq/207D40.c:27-45` | `0x207DD0-0x207E40`: kind 2/3, `Test50/Test48(key1)`, `count11C < 7` / `== 6`, `Test48(key7)` | fiel (incluido el `== 6`, no `>=`) |
| `port/eq/23C798.c:78-92` | `0x23CAB0-0x23CB6C`: `arg1&8`, `TestStep(3)`, `11310(1,1)`, `Test48(0xC)`, `3F420&0x8000`, `A10 < 3F8F8`, `218758`, `240438(3)`, `HasKi` | fiel |
| `port/eq/226510.c:44-56` | `0x226560-0x2265B0`: `Test48(s1,1) == 0` → `func_001F9D78(0x89)` | fiel |
| `port/eq/208738.c:6-10` | `0x208738`: `GetView(a0) + (a1<<2) + 0x940`, `lw` | fiel (devuelve el puntero del array) |
| `port/eq/241718.c:8-18` | `0x241718`: `idx=2411A0()`, `*(*(chr+0x1530)+0x980) + idx*4 + 0x54`, mitad si flag `0x1000000000` | fiel |
| `src/battle/btl_char_member_203858.c:179-184` | `0x203858`: `gauge->ki < amount ? 0 : 1` (compilado: `cmp; setge`) | fiel |
| `port/eq/2267D8.c:9-14` | `0x2267D8`: `beqz v0, 0x226818` (resultado 0 → `return -1`) | **INVERTIDO** (sección 2bis) |
| `src/auto/m2c_2411E0.c:5-7` | `0x2411E0` reenvía **a1** a `2411A0` | **divergencia** (latente, sección 5) |

No encontré un `>` vs `>=`, ni un bit equivocado, ni un contador que no incremente, en las piezas que deciden
“normal vs cargado”. El único candidato a “contador que no incrementa” es el flag de congelamiento
`D_003876A0+0x4D8 & 0x3800` (`port/eq/207630.c:119`), que hay que medir en vivo.

## 2bis. Causa: `func_002267D8` (decide de la acción 0x88) está invertido

Esta es la pieza que faltaba y la que explica exactamente el 88→6 de un frame y el `a10` que queda en 1.

Asm `0x2267D8` (`/tmp/opencode/full.asm:299538` y siguientes):

```
2267e8: jal 0x1fa288            ; func_001FA288(chr, 0x89)
2267f4: beqz v0, 0x226818       ; si devuelve 0  -> 0x226818
...
2267fc: jal 0x1f9df8            ; BtlAnim_SetBlend
226810: j 0x23c710              ; return func_0023C710(chr)  (normalmente 6)
...
226818: li v0,-1                ; return -1  (se queda en la acción)
```

C actual (`port/eq/2267D8.c:9-14`):

```c
if (func_001FA288(arg0, 0x89) == 0) {   // <-- invertido
    BtlAnim_SetBlend(arg0, D_0038627C);
    return func_0023C710(arg0);
}
return -1;
```

El binario compilado lo confirma (`0x402689f0`): `test eax,eax; je 0x40268a08` y en 0x40268a08 hace el blend +
`jmp func_0023C710`; en el camino `!= 0` devuelve `-1`. O sea el port **sale** de 0x88 justo cuando el original
**se queda**.

Semántica: `func_001FA288(chr,0x89)` devuelve 0 mientras `BtlObjXf_Update(chr)` (`chr+0x8E0`) no sea 0x89. El
original usa eso para **mantener** la acción 0x88 durante la carga; cuando la animación llega a 0x89, recién ahí
hace el blend y pasa a `func_0023C710` (6). El port hacía lo contrario: como al entrar a 0x88 el estado de
animación todavía es 0x87/0x88, mataba la acción al frame siguiente. Eso coincide con el log: 2446 `acc 88`,
2447 `acc 6` y `a10` queda en 1 (el enter de 226488 lo incrementó y el leave 226830 es vacío).

No es el pad, ni el ki, ni `func_001F9FB0`, ni `func_00208738`: la sonda CARGA8 ya mostró `step3=1`, `held1=0x1000`,
`since1=6`, `f758=1`, `a10=0<5`, `pass=1`. La falla estaba **después**, en el decide de la acción.

Sobre `a10`: es el contador de “carga activa”. Lo incrementa el **enter** de 0x88 (`port/eq/226488.c:15`, asm
`0x2264AC-0x2264C0`: `lw v0,2576(s0); addiu v0,v0,1; sw v0,2576(s0)`), y el **leave** (`226830`) es un `jr ra`
vacío, no lo decrementa. Que quede en 1 es la **consecuencia** de que la acción entró una vez y se abortó; no es
la causa. Su incremento es fiel al asm.

### Fix mínimo propuesto (no aplicado)

```diff
--- a/port/eq/2267D8.c
+++ b/port/eq/2267D8.c
@@
-    if (func_001FA288(arg0, 0x89) == 0) {
+    if (func_001FA288(arg0, 0x89) != 0) {
         BtlAnim_SetBlend(arg0, D_0038627C);
         return func_0023C710(arg0);
     }
     return -1;
```

Un solo carácter (`== 0` → `!= 0`) o, equivalentemente, intercambiar las dos ramas. El backup obvio es
`2267D8.c.pre_f7`. Con esto la acción 0x88 debería durar toda la carga y recién pasar a 6 cuando la animación
llegue a 0x89; es el arreglo que hay que probar jugando (mantener Triangle y ver si sale el blast cargado).

## 3. El dato nuevo: `tiene`, `costo`, `alcanza`

Salida del usuario:

```
TECNICA-PASOS gauge 0x17e71c8 chr 017E6000 tiene 13499520 suelo 1 gauge2C 0 flags 00021000 costo 60000 alcanza 0
```

- **`tiene = 13.499.520 = 0xCE0000` es un puntero, no un contador de ki.**
  `func_00208738` (`0x208738`) devuelve `*(u32*)(GetView(id) + slot*4 + 0x940)`. Ese array `+0x940` lo llena
  `func_0025D190` (`port/eq/25D190.c:85-92`) con `setIf(a0 + 0x940 + i*4, ...)`, y `setIf` guarda
  `g + (offset & ~3)` (`port/eq/25D190.c:22-26`), o sea **punteros a la entrada de técnica**. `0xCE0000` cae dentro
  de la RAM de PS2 (32 MB) y es un puntero plausible. Que sea distinto de 0 sólo significa “el slot 3 existe”.
  El asm `0x208738` hace exactamente eso; no hay que “arreglarlo”.
- **`costo = 60000` sí está en unidades de ki.** Ki va de 0 a 100000, 20000 por barra
  (`src/battle/btl_char_member_203858.c:13`). 60000 = 3 barras. Sale de la tabla `+0x980`, índice
  `func_002411A0(3)=1`, campo `+0x54+4` (`port/eq/241718.c:8-18`); el asm `0x241718` lo confirma.
- **`alcanza = BtlMember_HasKi(chr, 60000)` compara con `gauge+0xC` (ki actual), no con `gauge+0x2C`.**
  `gauge+0x2C` es el contador de “técnica bloqueada” que ya se arregló en B3. `alcanza=0` significa, ni más ni menos,
  `ki_actual < 60000`. La sonda imprime `gauge+0x2C` pero **no** `gauge+0xC`, así que con estos datos no se puede
  distinguir “ki bajo de verdad” de “el gauge apunta mal”.

**Ojo con la tabla:** `func_00241718` (tabla `+0x980`) es la de técnicas especiales; el blast cargado usa
`func_00240438(chr,3)` (tabla `+0x978`, `0x240438`, campo `+0xC` de la entrada de acción). Son tablas y costos
distintos. El `costo 60000` del log **no** es necesariamente el que bloquea el Triangle mantenido.

## 4. Sonda CARGA8 (corrida 20261111-190045) y verificación

La sonda se aplicó en `port/eq/23C798.c` (bloque `arg1 & 8`) y dio, con Triangle mantenido:

```
step3=1  held1=0x1000  press1=0  since1=6  a10=0  max=5  f758=1  cost=3500  ki=100000  pass=1  flag4D8=1
```

Descartes que deja la corrida:

- El pad llega y el contador `since1` llega exacto a 6 → `207630`/`207D40` están bien.
- `f758=1`: **no** es el tope de proyectiles.
- `a10=0 < max=5`: **no** es el tope de cargas activas.
- `cost=3500` y `ki=100000`: **no** es el ki (y el costo del blast cargado es 3500, no los 60000 de la tabla
  de técnicas especiales; confirma que la sonda `TECNICA-*` miraba otra tabla).
- `pass=1`: el bloque `arg1 & 8` de `func_0023C798` devuelve 0x88. El problema está **después**, en el ciclo de
  vida de la acción (sección 2bis).

Verificación después del fix de `2267D8`: repetir la misma corrida y comprobar que el log de pelea muestra la
acción `0x88` durante toda la carga (varios frames, no uno) y que al soltar Triangle pasa a `0x89` y sale el
disparo. Si la acción se mantiene pero el disparo no sale, la sonda siguiente es en `226898` (run de 0x89), no en
`23C798`.

## 4bis. Salida de 0x88 y acción 0x89 (corrida 20261111-191743)

Con el fix de `2267D8` la acción 0x88 se mantiene y la carga avanza, pero **`acc 89` no aparece nunca**. La
pregunta correcta no es “quién pide 0x89” sino “quién debería pedirla”: en el camino del Triangle mantenido
**nadie pide la acción 0x89**.

Evidencia estática:

- `port/eq/226510.c:54-56` (run de 0x88, rama `v == 0x88`) hace
  `if (BtlPad_Test48(s1,1) == 0) func_001F9D78(s1, 0x89);`. `func_001F9D78` escribe **`chr+0x8E4`** (estado de
  animación *pedido*) y pone el flag de grupo 2 bit `0x10`; **no** escribe la acción `chr+0xC00`. El asm
  `0x226610-0x226630` es idéntico.
- La acción `0x89` sólo se devuelve en `port/eq/229678.c:43`, `port/eq/229CE0.c:67` (especiales cargados con
  dirección/L2) y en la tabla de técnicas `23FE04`; **ninguno** es el Triangle mantenido básico. `func_0023C798`
  sólo devuelve `0x87` (tap) y `0x88` (mantenido).
- Por diseño, al soltar, el run pide **animación 0x89**, el `decide` 2267D8 (ya corregido) devuelve `-1` mientras
  `BtlObjXf_Update(chr)` (`+0x8E0`) no sea 0x89, el motor aplica el pedido con `BattleSide_SetChara(chr, +0x8E4)`
  y, cuando el estado ya es 0x89, el decide llama a `func_0023C710` (6). Es decir: la **acción** vuelve a 6 y la
  **animación** 0x89 es la que debe disparar el efecto/proyectil. `acc 89` no es esperable; lo que falta es que
  corra el clip/evento 0x89.

El punto crítico que hay que medir es **en qué estado de animación (`v`) está el run al soltar**. La rama que
tiene el chequeo de soltada es **sólo `v == 0x88`**; la rama `v == 0x87` (0x226568) no lo tiene. Si la carga se
queda en 0x87 (porque `func_001FA0A0(s1,0x88,0)` / `func_001F9FB0(s1,0)` nunca devuelve 1), al soltar no se pide
0x89 y no hay disparo.

Las cuatro funciones de la acción 0x89 (tabla `D_003438E0`, entrada 0x89 = `0x226838/0x226898/0x2269D0/0x226A20`):

- enter `226838`: `BattleSide_SetChara(0x86)`, resetea `func_00203888`, pone a cero la velocidad (`+0xC0/+0xC4`) y
  `func_00211418(0x8000)`. No crea ningún proyectil.
- run `226898`: `func_001F9FB0(chr,0)`, arma la pose/aim con `func_00208DE8`/`func_00209268`. Tampoco crea
  proyectil: sólo calcula el vector de tiro.
- decide `2269D0`: si `func_00211310(chr,2,1)` está prendido, blend y devuelve 10; si no, -1. Es una pose de
  “recoil/aim”, no el disparo.
- leave `226A20`: vacío (`jr ra`).

O sea: aunque se entrara a la acción 0x89, el proyectil **no** se crea ahí. El disparo del blast es un **evento
de animación** (el clip 0x89 que se pide con `func_001F9D78`), no el run de la acción. Por eso “acc 89” no es el
indicador correcto: el indicador es si el clip 0x89 llega a ejecutar su evento.

Hay una segunda puerta que puede pisar todo esto: el motor `func_00214A08` (`port/eq/214A08.c:50-70`) llama
**primero** a `func_0021FB00(arg0)`; si devuelve algo distinto de -1, transiciona a esa acción **sin llamar al
decide** y después corre el run de la acción nueva. Si en el frame de soltada la “pedida” (`C04`/`C08` del log)
es 6, el run de 0x88 ni se ejecuta y el `func_001F9D78(0x89)` no se llama. El log de pelea ya tiene las columnas
`C00 C04 C08(pedida)`: en el frame de soltada hay que ver si la pedida es 6 o 88.

### Sonda exacta (una corrida)

En `port/eq/226510.c`, al entrar a la función y en las ramas 0x88/0x89:

```diff
--- a/port/eq/226510.c
+++ b/port/eq/226510.c
@@
 void func_00226510(u8 *arg0) {
@@
     v = BtlObjXf_Update(s1);
+    {
+        u8 *t = *(u8 **)(s1 + 0x1530) + 0xBD0;
+        bt2_fightlog_note("CARGA88RUN chr %08X v %X held1 %d since1 %d a10 %d timer %.0f/%.0f step %.0f",
+                          (s32)s1, v, BtlPad_Test48(s1, 1), BtlPad_GetCount11C(s1, 1),
+                          *(s32 *)(s1 + 0xA10), *(f32 *)(t + 0x10), *(f32 *)(t + 0x08),
+                          *(f32 *)(t + 0x18));
+    }
     if (v == 0x88) {
@@
-        if (BtlPad_Test48(s1, 1) == 0) {
+        if (BtlPad_Test48(s1, 1) == 0) {
+            bt2_fightlog_note("CARGA88RELEASE chr %08X pide anim 0x89 (a10 %d)", (s32)s1, *(s32 *)(s1 + 0xA10));
             func_001F9D78(s1, 0x89);
         }
@@
     } else if (v == 0x89) {
+        bt2_fightlog_note("CARGA88V89 chr %08X corre la rama 0x89", (s32)s1);
         func_001F9FB0(s1, 0);
```

Y en `port/eq/2267D8.c`, antes del `if`:

```diff
+    bt2_fightlog_note("CARGA88DEC chr %08X xf %X fa %d", (s32)arg0,
+                      BtlObjXf_Update((s32)arg0), func_001FA288((s32)arg0, 0x89));
```

Qué decide:

- `v` siempre 0x87 y nunca 0x88: el timer `func_001F9FB0(s1,0)` no llega a max; mirar `timer actual/max/step`.
  Si `step` es 0 o `max` es 0, el problema es la carga del clip/timer (`func_0025FA60`/`func_001F9D10`), no el
  input.
- `v == 0x88` y `CARGA88RELEASE` sale con `held1=0`: el pedido de 0x89 se hace; entonces el problema es que el
  clip/evento 0x89 no dispara el proyectil (mirar `CARGA88V89` y el sistema de eventos de animación).
- `CARGA88RELEASE` no sale nunca aunque `held1=0`: el run no estaba en 0x88 al soltar (ver el punto anterior).

## 4ter. CAUSA del corte del clip 0x89: `func_001FA288` devuelve 1 con el flag 2/0x1 en 0

La corrida `20261111-192507` muestra que el pedido de 0x89 llega bien, el motor aplica la animación (g2 0x10 →
0x02) y el clip 0x89 arranca (2/13), pero al frame siguiente la acción 6 lo pisa con el idle (2/71). El
responsable es el `decide` de 0x88 (`2267D8`), que ahora está bien: llama a `func_001FA288(chr,0x89)` y, si
devuelve distinto de 0, transiciona a `func_0023C710` (6). El problema es que **`func_001FA288` devuelve 1
aunque el flag 2/0x1 esté en 0**, o sea aunque el clip 0x89 todavía no haya terminado.

Asm `0x1FA288`:

```
1fa29c: jal 0x1fa390          ; Xf = BtlObjXf_Update(chr)
1fa2ac: bne v0,s1, 0x1fa2c4   ; Xf != 0x89 -> return 0
1fa2b0: li a2,1
1fa2b4: jal 0x211310          ; func_00211310(chr,2,1)  (flag "clip terminado")
1fa2bc: bnez v0, 0x1fa2c8     ; flag != 0 -> return 1
1fa2c0: li v0,1               ; delay slot
1fa2c4: move v0,zero          ; flag == 0 -> return 0
1fa2c8: jr ra
```

El `bnez` no es *branch-likely*: el delay `li v0,1` corre siempre. Si el flag es 0, cae en `0x1FA2C4` y devuelve
**0**. El C actual (`port/eq/1FA288.c:10-13`) hace lo contrario:

```c
var_v0 = func_00211310(arg0, 2, 1);
if (var_v0 != 0) {
    return var_v0;
}
return 1;        // <-- debería ser 0
```

Con flag 0 devuelve 1 → el `decide` 2267D8 cree que el clip 0x89 ya terminó, transiciona a 6 y el enter de 6
(`227E30` → `BattleSide_SetChara(start)`) pisa la animación 0x89 con el idle de 71 frames. El evento del clip
0x89 (el que crea el proyectil) nunca llega a correr. Coincide exacto con el log: en 9173 el flag g2 es `0x02`
(bit 0x1 en 0) y en 9174 ya está la acción 6 con anim `2/71`.

### Fix mínimo propuesto (no aplicado)

```diff
--- a/port/eq/1FA288.c
+++ b/port/eq/1FA288.c
@@
     var_v0 = func_00211310(arg0, 2, 1);
     if (var_v0 != 0) {
         return var_v0;
     }
-    return 1;
+    return 0;
```

O, más corto y equivalente al asm: `return func_00211310(arg0, 2, 1);` después del chequeo de `BtlObjXf_Update`.
Backup `1FA288.c.pre_f7`. Es la segunda pieza de la cadena, después de `2267D8`; con las dos, la acción 0x88 debe
quedarse hasta que el clip 0x89 termine (flag 2/0x1) y recién ahí volver a 6.

## 5. Fix mínimo real encontrado (latente): `func_002411E0`

`src/auto/m2c_2411E0.c` declara y llama a `func_002411A0` con **un** argumento:

```c
s32 func_002411A0();
s32 func_002411E0(void *arg0) {
    return M2C_FIELD(((func_002411A0(arg0) * 4) + ...
```

El asm `0x2411E0` no toca `a1` antes del `jal 0x2411A0`: le reenvía el **slot** que recibió. O sea la firma correcta
es `func_002411E0(chr, slot)` y la llamada interna es `func_002411A0(chr, slot)`. Hoy “funciona” porque los 101
llamadores pasan 2 argumentos, el slot queda en `rsi` y el wrapper compilado (`0x40129380`) no escribe `rsi` antes
del `call`. Es comportamiento indefinido y se rompe si cambia el compilador/optimización.

```diff
--- a/src/auto/m2c_2411E0.c
+++ b/src/auto/m2c_2411E0.c
@@
-s32 func_002411A0();
+s32 func_002411A0(s32 arg0, s32 arg1);
 
-s32 func_002411E0(void *arg0) {
-    return M2C_FIELD(((func_002411A0(arg0) * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x980)), s32 *, 0xD0);
+s32 func_002411E0(void *arg0, s32 arg1) {
+    return M2C_FIELD(((func_002411A0((s32)arg0, arg1) * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x980)), s32 *, 0xD0);
 }
```

No lo aplico acá. No es la causa del ataque cargado (esa ruta no llama a `2411E0`), pero es fiel al asm y conviene
tenerlo.

## 6. R1 en el free roam

Lo que sí está verificado:

- El bit R1 crudo llega: `Port_PadRead` usa `B_R1 = 0x0800` (`port/full/gs/gs_input.c:32`) y el juego lee el crudo en
  `D_003B0B00 + pad*0x180 + 0x134` (`port/eq/107860.c:63`, `port/eq/3C48F8.c:28`). El `PADDBG` del usuario confirma
  que el botón se mantiene.
- **No encontré el consumidor de R1 del mapa.** Busqué `0x800` junto a las palabras de pad (`+0x134`/`+0x144`,
  `D_003B0B00`, `D_003B0C34`, `D_003B0C44`) en `port/eq` y en `src`: los únicos usos claros de `0x800` con pad son
  menús (p. ej. `port/eq/3C48F8.c:122`, `port/eq/3F25C0.c:173`, que además usan `0x400/0x800` como izquierda/derecha
  de un cursor, no como ascender). El módulo del jugador del mapa no quedó identificado con evidencia suficiente.
- Descartado: que el problema sea el pad (ya probado por el usuario) y que sea el `-300` de clima/B25 (es
  `func_00145A58`, suma de vectores, y no lee pad).

Siguiente paso concreto para R1 (una corrida): el objeto del jugador del mapa es `0x11BA340`, posición en `+0x140`
(`docs/RETOMAR.md`, B25). Con `BT2_WATCH_F32` sobre `0x11BA340 + 0x144` (Y) y R1 mantenido, el watchpoint dice **qué
función escribe la Y**. Si no escribe nadie, la sonda es leer en el mapa las dos palabras
`*(u32*)(D_003B0B00+0x134)` y `+0x144` y comparar con lo que espera el consumidor (R1 = `0x800`). No propongo un
parche de R1 sin eso: sería inventar.

## 7. Lo que NO está verificado

- **Los fixes de `2267D8` y `1FA288` no están aplicados juntos** (este informe es de solo lectura). El de
  `2267D8` ya se probó y la carga se mantiene; falta aplicar el de `1FA288`, compilar y probar que el clip 0x89
  llega a su evento y sale el proyectil.
- No se repitió la corrida después del fix de `1FA288`, así que no está comprobado que el evento del clip 0x89
  dispare el blast. La condición es fiel al asm, pero el efecto en el juego lo confirma la prueba.
- El consumidor de R1 en el mapa no está identificado (sección 6).
- `func_001F9FB0` y el temporizador `chr+0x1530->+0xBD0` no se sondearon; con el fix de 2267D8 no deberían ser
  necesarios, pero si la acción se mantiene y el disparo sigue sin salir, hay que mirar el run de 0x89 (`226898`).
