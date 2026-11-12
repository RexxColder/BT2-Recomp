# B31 — personaje trabado contra un objeto irrompible (Cuadrado cargado al máximo)

Fecha: 2026-11-11. Solo lectura: no se aplicó ningún cambio ni se compiló.
Fuentes: `port/eq/*.c` (código que corre en el port), `include/battle/*.h` (mapa del decomp matching),
`/tmp/opencode/full.asm` (ELF `disc/SLUS_214.41`), `config/symbols`, y los `*.fight.log` de
`BT2-test/logs/vivo/`.

> **CAUSA RAÍZ CONFIRMADA (21:00):** el `run` de la acción `0xA9` (`port/eq/222A78.c`,
> bloque `common_0xDB`) **descarta el retorno de `BtlObjXf_Update`** y usa el resultado de
> `func_00211310(0,4)` (=1), así que pide `func_001FA0A0(chr, 2, 0)` en vez de `xf+1` (`0xD8/0xDA`).
> El asm `0x222af0-0x222b04` usa `addiu a1,v0,1` sobre el retorno de `BtlObjXf_Update`. El pedido
> erróneo `2` (animación de reacción, 13 frames) pisa el clip del derribo y deja la acción trabada.
> Fix de una línea en `222A78.c` (§22); el workaround hay que revertirlo. Es un bug de traducción
> C-vs-asm, no del input ni de la colisión.
>
> **Actualización 20:00 (F9 `20261111-194141_ram1_f12863.bin`, acción `0xA9`):** volcado del freeze
> provocado por la CPU. El personaje queda en `acc 0xA9`, `anim 0/13`, `+0x8E0=2`: el clip del derribo
> (`0xD7/0xD9`) existe y se jugó (29 frames), pero a las 12579 lo pisó el pedido erróneo `2` (13 frames).
> Ver §17-20. El análisis de la acción `0x99` de §5 y el de `0xAF` de §11-16 quedan como hipótesis de
> otras corridas; el `0xA9` es el caso confirmado.
>
> **Actualización 19:00 (corrida `20261111-190045`):** el freeze de esa corrida es `acc 0xAF` durante 648
> cuadros. `0xAF` es la acción de **ki blast cargado**, no una reacción del defensor; el rayo (`BEAM`)
> aparece en la posición del afectado y queda `stop 1` con la animación clavada en `6/16`. Ver §11-16.

## Resumen ejecutivo

- El golpe de Cuadrado cargado al máximo **no es una técnica**: es el remate de rush (acción `0x4B`/`0x4C`,
  sin dirección) con el registro de ataque de carga llena (`chr+0xD78 >= 0.99`). En el log `20261111-184449`
  se ve al atacante en `acc 4B` y al golpeado pasar a `acc 99` (derribo).
- La acción `0x99` es el estado de **derribado/caído** (`BattleSide_SetChara 0xD2/0xD3`, timer `chr+0x8C0`,
  animación de 19 frames). Su salida depende de `func_00212820` (vida / flag 0/0x4000), del flag 1/0x40000 y de
  `(BtlPad_Test48(chr, 8) || func_00212878())`. `func_00212878()` es `modo == 4` (`D_003876A0+0xD4`).
- La parte de “choque con el escenario” existe y está bien traducida: `func_0011D3A0` escribe el contacto en
  `obj+0xE50` (bit 0x20 = pared, bit 0x40 = rompió objeto), `func_002659B8` lo copia a `obj+0xE54` y limpia
  `0xE50`, y el handler de la acción `0x31` (`func_00239B48`) usa `0xE54 & 0x20 && !(0xE54 & 0x40)` para
  rebotar/recuperarse. **No encontré una divergencia C-vs-asm en esa cadena** (los C de `11D3A0`, `11D670`,
  `20D450`, `239B48` y `2659B8` coinciden con el asm en el flujo y en los offsets).
- La acción `0x99` **no lee** el contacto del escenario. Si el personaje queda en `0x99` (lo que sugiere el
  log), el obstáculo es incidental: el bug está en la salida del derribo, no en la colisión.
- Sin una corrida con el estado exacto no hay fix honesto. La sonda de abajo (log por cuadro de `obj+0xE50/0xE54`,
  acción, timer de derribo, vida y modo) distingue en **una sola corrida** entre “no llega el bit de pared”
  (acción `0x31`) y “no sale del derribo” (acción `0x99`).

---

## 1. Máquina de estados del luchador al recibir un golpe fuerte

Mapa de datos usado por el port (verificado con `plat_fightlog.c` y el asm):

| qué | dirección | quién lo usa |
|---|---|---|
| roster de luchadores | `**(u32**)0x387930 + i*0x1550` | `plat_fightlog.c`, `func_00211288` |
| acción actual / pedida / cola | `chr+0xC00` / `+0xC08` / `+0xC0C` | `func_00217488`, `func_002174D8`, `func_002174B8` |
| bloque de reacción del golpe | `chr+0xFB0` (`HitReact`) | `200EF8.c`, `202088.c` y los handlers |
| cuerpo/colisión del objeto | `obj = *(u32*)(chr+0x1530)` | `BtlChar_GetObj`, `11D670.c` |
| movimiento del objeto | `obj+0x9A0/0x9A4/0x9A8` | `11D3A0.c:92-100`, `20E6B8.c` |
| contacto del escenario del cuadro | `obj+0xE50` | `11D3A0.c`, `11D670.c:33` |
| contacto “comprometido” (lo leen los handlers) | `obj+0xE54` | `20D450.c:86-92`, `239B48.c:139` |
| polígono tocado | `obj+0xED0` | `11D3A0.c:86-89`, `20D450.c:87` |
| timer de derribo / mash | `chr+0x8C0` / `chr+0x8C4` | `221468.c:18-21`, `221520.c:70-96` |
| bits de “quedarse abajo” | `chr+0x8DC` | `221520.c:77`, `221520.c` (leave) |
| animación pedida | `chr+0x8E0` (y `BattleSide_SetChara`) | `1F9AC8.c`, `221468.c:13-15` |
| modo de juego | `*(u8*)D_003876A0+0xD4` | `func_00212878` (`src/auto/m2c_212878.c`) |
| flags globales de pausa/tiempo | `D_003876A0+0x4D8` | `2659B8.c:18,34`, `20D450.c:82` |

Cadena de un golpe fuerte (la parte que importa para B31):

1. **Decisión del ataque.** `port/eq/23BDA8.c` elige técnicas/remates; el Cuadrado cargado al máximo entra por
   la rama de “rush con carga” (acción `0x47..0x4C`; sin dirección, `0x4B` si `chr+0xD60 < 5`, `0x4C` si no,
   ver `include/battle/btl_act_i.h:117-120`). La carga se mide en `chr+0xD78` (0..1; llena `>= 0.99`,
   `include/battle/btl_tech_a.h:22-24`) y elige el registro de ataque `0x1D..0x21` / `0x4A`/`0x4D` según la
   tabla (`btl_tech_a.h:33-43`). El `ELIGE-ATAQUE` de `23BDA8.c` sólo registra la elección; no crea el estado
   del golpeado.
2. **Impacto.** El registro de ataque (en `obj+0x920`, id `BtlAtk_GetId`) trae `react` (+0x1B) y los ángulos de
   lanzamiento (+0x15/+0x16). `BtlHit_ApplyHit` llena `chr+0xFB0` (`HitReact`) y el código de reacción pide la
   acción siguiente. En el log `20261111-184449`, el golpeado J2 pasa de `acc 3A` a `acc 99` justo en el cuadro
   6251, el mismo cuadro en que J1 golpea con `acc 4B`.
3. **Vuelo/derribo.** La pose tiene `dir` en `chr+0x80` y `speed` en `chr+0x98` (más el impulso `+0x70`;
   `include/battle/btl_char_move.h:20-52`). En el log, J2 se mueve a `vel 9.26/cuadro` durante ~25 cuadros y
   la animación de 19 frames se repite (`ANIM-REINICIO` en 6270).
4. **Colisión con el escenario.** Cada cuadro, `BtlChar_UpdateStage8` llama a `func_0011D670` (cuerpo) y
   `func_0011CA40` (suelo). `func_0011D670` limpia `obj+0xE50 & ~0x60` (`11D670.c:33`) y `func_0011D3A0`
   empuja la esfera fuera de los triángulos sólidos (`11D3A0.c:40-85`).
5. **Contacto.** Si hubo empuje, `func_0011D3A0` setea `obj+0xE50 |= 0x20` y copia el polígono a `obj+0xED0`
   (`11D3A0.c:85-89`). Si además “rompió” un objeto, setea `0x40` y los bits de daño `0x80/0x100/0x200`
   (`11D3A0.c:57-70`). Al final del dibujo, `func_002659B8` copia `obj+0xE50 -> obj+0xE54` y limpia `0xE50`
   (`2659B8.c:20-21`); los handlers leen `0xE54` (el valor del cuadro anterior).
6. **Salida.** `BtlColl_UpdateGround` (`20D450.c:86-96`) convierte `0xE54 & 0x20 && !(0xED0 & 0xC0)` o
   `0xE54 & 0x40` en el flag `0/0x8000` (sólo si `func_00212878() != 0`, `20D450.c:82`). El handler de la
   acción `0x31` (`239B48.c:137-162`) usa directamente `0xE54 & 0x20 && !(0xE54 & 0x40)` para pedir la
   animación `0x39` (rebote/recuperación), bajar la velocidad y vibrar. **La acción `0x99` no consulta nada de
   esto**: su salida es el timer `chr+0x8C0` y el gate de `221520.c:72-78`.

## 2. Dónde se detecta “chocó con un objeto del escenario” y qué debería hacer

Punto exacto: `port/eq/11D3A0.c:47-89`.

- `func_0011CB18(..., func_0011D298)` devuelve qué triángulo/objeto tocó. El callback `func_0011D298`
  (`StgCol_PushCb`) empuja la esfera, copia el polígono a `ctx+0x50` y pone `ctx[0]=1` (hit).
- Si tocó un objeto destructible, `func_00274680` devuelve el tipo del objeto (`274680.c`); el gate
  `func_0020AA78(id)` / `func_0020AB00(id)` decide si el luchador puede romperlo (`11D3A0.c:52-56`).
- Si puede: `func_00274338` marca el objeto como roto y se setea `0xE50 |= 0x40` (`11D3A0.c:57-59`).
- Si no puede (objeto irrompible): no se setea `0x40`; al final, si hubo empuje, se setea `0xE50 |= 0x20`
  (`11D3A0.c:80-85`). Éste es el caso que debería disparar el rebote/recuperación.
- El bit viaja por `0xE50 -> 0xE54` (`2659B8.c:20-21`) y lo consumen:
  - `20D450.c:87-92` para el flag `0/0x8000` (si `modo == 4`), y
  - `239B48.c:139-142` (acción `0x31`) para el rebote.

Qué debería hacer: con `0x20` y sin `0x40`, la acción de vuelo/derribo debe **cambiar de estado** (rebote,
caída o recuperación) y no quedarse esperando. En el código actual eso sólo lo hace la acción `0x31`; las
acciones de reacción `0x8E..0x94` y el derribo `0x99` no leen el contacto.

## 3. Comparación C vs asm

Lo que verifiqué (y **coincide**):

- `11D670.c:33` ↔ asm `0x11d670`: `lw v0,0(s1); and v0,a2; and v0,a3; sw v0,0(s1)` con `s1 = obj+0xE50`
  (máscaras `~0x20` y `~0x40`).
- `11D3A0.c:80-89` ↔ asm `0x11d558-0x11d5a0`: `lbu v0,0(s4)` (hit), `ori 0x20`, `sd` del polígono a
  `+0x80/+0x88/+0x90/+0x98` (o sea `obj+0xED0..`), y la corrección del movimiento en `obj+0x9A0`.
- `11D3A0.c:47-70` ↔ asm `0x11d480-0x11d548`: `func_0011CB18`, `StgCol_FirstBit`, `func_00274680`,
  `func_0020AA78`/`func_0020AB00`, `func_00274338`, `ori 0x40`, bits `0x80/0x100/0x200`. El C **no** usa el
  valor de retorno de `func_00274338`, igual que el asm (`jal 0x274338` seguido de `ori 0x40`).
- `20D450.c:82-96` ↔ asm `0x20d700-0x20d794`: `lw 0xE54`, `andi 0x20`, `lw 0xED0`, `andi 0xC0`, `lui/li
  0x8000`, `jal 0x2113c0`. La condición de `modo == 4` (`func_00212878`) también está en el asm.
- `239B48.c:137-162` ↔ asm `0x239ea0-0x23a128`: `TestFlag(0,4)`, `lw 0xE54`, `andi 0x20`, `andi 0x40`,
  `movz`, `li 0x39`, `jal 0x1f9d78`. Coincide.
- `2659B8.c:18-21,34-37` ↔ asm `0x2659e8-0x265a28`: `ld 0x4D8`, `andi 0x100`, `lw 0xE50`, `sw zero,0xE50`,
  `sw v0,0xE54`. Coincide.
- `221520.c:52-110` (acción `0x99`) ↔ asm `0x221520-0x221a38`: timer `s2 = chr+0x8C0`, mash `s0 =
  chr+0x8C4`, `func_00212820`, `TestFlag(1,0x40000)`, `BtlPad_Test48(8)`, `func_00212878`, get-up
  `func_001F9D78(F9/FA)`, si no `0x8DC |= 1`. Coincide.
- `func_00212878` (`src/auto/m2c_212878.c`) ↔ asm `0x212878`: `lw v0,0xD4; xori 4; sltiu` (modo == 4).
  Coincide.

**No encontré una instrucción traducida mal en esta cadena.** Los offsets mágicos que parecían raros
(`0xE50` vs `0xE54`) son dos palabras distintas a propósito: `0xE50` es el contacto del cuadro y `0xE54` el
del cuadro anterior que consumen los handlers; `2659B8` hace el pasaje.

Conclusión de la comparación: si B31 fuera “no se entera de la pared”, el bug no está en la traducción de
`11D3A0/20D450/239B48/2659B8`, sino en **si esos caminos se ejecutan** (modo, pausa global, orden de cuadro)
o en que el estado que queda no es la acción `0x31`.

## 4. Dato nuevo: “sólo con Cuadrado cargado al máximo”

Evidencia del log `BT2-test/logs/vivo/20261111-184449.fight.log` (Dueling, J1 vs J2):

- 6250: J1 `acc 49` (rush), J2 `acc 3A`, `GOLPE B48 1->16`.
- 6251: J1 `acc 4B` (`pad Cua`), J2 pasa a `acc 99`, `anim 2/19`, `vel 9.26`, `pos 396.1 7.9 438.8`;
  flags de J2: `g0 00400005 -> 00402087`, `g1 00000401 -> 02001800`, `g9 00000240 -> 04000200`.
- 6252–6276: J2 sigue en `acc 99`, la animación de 19 frames se repite (`ANIM-REINICIO` en 6270), el `vel` se
  mantiene en 9.26.
- 6276: J2 llega a `pos 258.4 3.5 624.9`.
- 6277 en adelante: J2 `vel 0.00`, `pos` y `anim` congelados en `12/19`, `acc 99`, `f9 00000200`; el log sigue
  hasta 6335 y termina (sesión cerrada). J1 sigue en `acc 6` (idle).
- En el cuadro 6251 J2 tenía `f9` con `0x04000000` (se limpia al cuadro siguiente), y no hay `frz` (0/0/0).

Interpretación: el ataque que dispara el bug es el **remate de rush cargado sin dirección** (`0x4B/0x4C`), y
el estado que queda es la acción `0x99` (derribo). El objeto/roca puede ser el lugar donde termina el vuelo,
pero la acción `0x99` no consulta la colisión: su única salida es el timer de `221520.c:70-78`.

Ojo: la acción `0x99` también es el estado de KO. Si la vida de J2 estaba en 0, quedarse abajo es correcto y
este log **no** sería B31. El log no imprime vida. Hay que confirmarlo con la sonda.

## 5. Hipótesis (ordenadas)

1. **(Principal) El derribo `0x99` no sale.** `221520.c:70-78`: el timer `chr+0x8C0` baja, pero el get-up
   exige `func_00212820(chr)` (vida no vacía y sin flag 0/0x4000), `!(flag 1/0x40000)` y
   `(BtlPad_Test48(chr,8) || func_00212878())`. `func_00212878()` es `D_003876A0+0xD4 == 4`. Si en el port ese
   modo no vale 4 (o la vida quedó en 0, o el flag 1/0x40000 quedó prendido), el personaje hace `0x8DC |= 1`
   y se queda abajo hasta que otro golpe le cambia la acción. Explica “CPU o jugador”, “hasta que recibe otro
   golpe” y “sólo con el Cuadrado cargado” (es el golpe que derriba).
2. **El bit de pared no llega a la acción `0x31`.** Si el estado es `0x31` (get-hit/fall) y `obj+0xE54` nunca
   tiene `0x20` (o tiene `0x40` de un “rompió” falso), el rebote de `239B48.c:139-142` no ocurre. El candidato
   mecánico es el orden de cuadro: `2659B8` copia `0xE50 -> 0xE54` dentro del **draw** (`265EB8.c:177,182`);
   si el port corre la lógica y el dibujo a distinto ritmo, o el flag global `0x4D8 & 0x100` está prendido,
   la copia se saltea y el contacto de un cuadro se pierde. También podría ser un `0x40` falso por el gate
   `func_0020AA78/AB00` sobre un objeto irrompible.
3. **El objeto tiene polígonos `NO_SOLID` (0x08000000).** En ese caso no hay empuje ni bit; la posición se
   frena por otra vía (límite de zona/altura) y el estado queda esperando. La sonda lo distingue mirando
   `obj+0xE50/0xE54/0xED0`.

## 6. Sonda exacta para una corrida

Objetivo: que el log diga, en el cuadro del bug, **qué acción quedó**, **qué contacto hay** y **por qué no
sale**. Todo es TEMP B31; no se aplicó.

### 6.1 Diff propuesto en `port/full/plat_fightlog.c` (no aplicado)

Agregar cerca de los helpers (`rd32`, `rdf`, `ok`) y dentro de `bt2_fightlog_frame`, después de calcular
`chr`, `obj` y `st`:

```diff
@@
 static int sOn = -1, sAll, sStuckN = 90;
 static FILE *sOut;
 static FState sPrev[2];
 unsigned gPortPadBtn[2];
+
+/* TEMP B31: contacto con el escenario y estado de derribo. */
+static int sB31 = -1;
+extern unsigned char *BtlMember_GetActiveGauge(unsigned chr);
+
+static void b31_dump(uint32_t chr, uint32_t i, const char *tag) {
+    uint32_t obj = rd32(chr + 0x1530);
+    unsigned char *g = BtlMember_GetActiveGauge(chr);
+    uint32_t mode = 0, fl4d8 = 0, base = rd32(0x3876A0);
+    if (ok(base, 0x4E0)) { mode = rd32(base + 0xD4); fl4d8 = rd32(base + 0x4D8); }
+    if (!ok(obj, 0x1000)) return;
+    fprintf(sOut, "%7u J%u | B31 %s obj %08X e50 %08X e54 %08X ed0 %08X | mv %.3f %.3f %.3f"
+                   " | 8C0 %d 8C4 %d 8DC %08X 8E0 %d | act %X req %X q %X"
+                   " | react %d/%d/%d stun %d mash %d | hp %d/%d | modo %d 4D8 %08X\n",
+            gPortVBlanks, i + 1, tag, obj, rd32(obj + 0xE50), rd32(obj + 0xE54), rd32(obj + 0xED0),
+            rdf(obj + 0x9A0), rdf(obj + 0x9A4), rdf(obj + 0x9A8),
+            (int)rd32(chr + 0x8C0), (int)rd32(chr + 0x8C4), rd32(chr + 0x8DC), (int)rd32(chr + 0x8E0),
+            rd32(chr + 0xC00), rd32(chr + 0xC08), rd32(chr + 0xC0C),
+            (int)rd32(chr + 0xFB0), (int)rd32(chr + 0xFB4), (int)rd32(chr + 0xFB8),
+            (int)rd32(chr + 0xFE0), (int)rd32(chr + 0x1000),
+            g ? *(int *)(g + 0x00) : -1, g ? *(int *)(g + 0x04) : -1, (int)mode, fl4d8);
+}
@@
     if (sOn < 0) init();
     if (!sOn) return;
+    if (sB31 < 0) sB31 = getenv("BT2_B31LOG") != NULL;
@@
         s.valid = 1;
+        if (sB31) b31_dump(chr, i, "f");
         if (p->valid) {
@@
             if (s.frame == p->frame && vel > 0.01f) s.stuck = p->stuck + 1;
             else s.stuck = 0;
+            /* TEMP B31: quieto del todo (acción y posición), que es el síntoma reportado. */
+            if (s.frame == p->frame && vel < 0.01f && s.act[0] != 6) {
+                s.stuck0 = p->stuck0 + 1;
+                if (s.stuck0 == 30) b31_dump(chr, i, "*** QUIETO 30");
+            } else {
+                s.stuck0 = 0;
+            }
             s.reported = s.stuck ? p->reported : 0;
*** (agregar `unsigned stuck0;` a FState y copiarlo en `*p = s;`) ***
```

La línea `B31 f` sale **cada cuadro** con `BT2_B31LOG=1`; con 2 luchadores son ~120 líneas/s, suficiente
para 10 s. La línea `*** QUIETO 30` sale sola a los 30 cuadros de acción+posición congeladas.

### 6.2 Diff propuesto en `port/eq/2659B8.c` (no aplicado) — ¿la copia ve el 0x20?

```diff
@@
 void func_002659B8(void) {
+    void bt2_fightlog_note(const char *, ...);
@@
             if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) == 0) {
                 func_00260620((s32)elem);
+                if (*(u32 *)(elem + 0xE50) & 0x60)
+                    bt2_fightlog_note("B31 COPY %08X e50 %08X (e54 %08X)", (s32)elem,
+                                      *(u32 *)(elem + 0xE50), *(u32 *)(elem + 0xE54));
                 *(s32 *)(elem + 0xE54) = *(s32 *)(elem + 0xE50);
                 *(s32 *)(elem + 0xE50) = 0;
             }
```

Con esto, una corrida dice si el `0x20` llega a `func_002659B8` y qué objeto es. Si no aparece ninguna línea
`B31 COPY` con `0x20` durante el bug, el problema está antes (colisión/no empuje o pausa global).

### 6.3 Diff propuesto en `port/eq/11D3A0.c` (no aplicado) — qué objeto y qué bit

```diff
@@
                 if (v0 != 0) {
                     func_00274338(s0, arg5);
+                    { void bt2_fightlog_note(const char *, ...);
+                      bt2_fightlog_note("B31 BREAK obj %08X id %d tipo %08X", (s32)arg0, s0, s2); }
                     *(u32 *)s1 |= 0x40;
                 }
@@
     *(u32 *)s1 |= 0x20;
+    { void bt2_fightlog_note(const char *, ...);
+      bt2_fightlog_note("B31 WALL obj %08X id %d e50 %08X ed0 %08X", (s32)arg0,
+                        *(s32 *)arg0, *(u32 *)s1, *(u32 *)(s1 + 0x80)); }
```

Así se ve si el golpeado “rompe” (0x40) o sólo “toca pared” (0x20) en el objeto irrompible.

### 6.4 Reproducción

1. Dueling, mapa con rocas/edificios irrompibles (Dying Namek / mapa con estructuras), J1 vs J2 (o 1P vs CPU).
2. Mantener Cuadrado hasta carga máxima, sin dirección, y soltar cuando el rival esté contra la roca.
3. Al quedar trabado, anotar el `vblank` de la última línea y apretar **F9** (volcado de cuadro; si el lanzador
   no tiene `BT2_F9_RAM`, apretar **F10** para el volcado de RAM de 32 MB, que es el que hace falta). El
   `fight.log` anota `RAMDUMP f<frame> <archivo>`.
4. Cerrar el juego después del volcado (no hace falta esperar).

Variables de entorno: `BT2_FIGHTLOG=1 BT2_FIGHTLOG_ALL=1 BT2_B31LOG=1` y `BT2_F9_RAM=<carpeta>` (o
`BT2_RAMDUMP_DIR` para F10).

## 7. Qué leer del volcado F9/F10

En el `.bin` (32 MB, RAM de la PS2 desde 0x100000; la zona 0..0x100000 va en cero):

- `0x387930`: puntero al roster; en el archivo, `u32 roster = rd32(0x387930)`, `u32 chars = rd32(roster)`,
  `chr = chars + i*0x1550` (i = 0/1).
- `u32 obj = rd32(chr+0x1530)`.
- `obj+0xE50` (contacto del cuadro), `obj+0xE54` (contacto que ven los handlers), `obj+0xED0` (flags del
  polígono; `&0xC0` distingue ring-out).
- `obj+0x9A0/0x9A4/0x9A8` (delta de movimiento; en el empuje se corrige a 0).
- `chr+0xC00/C08/C0C` (acción actual/pedida/cola), `chr+0xFB0..0xFC8` (reacción del golpe),
  `chr+0x8C0` (timer de derribo), `chr+0x8C4` (mash), `chr+0x8DC` (quedarse abajo), `chr+0x8E0` (animación
  pedida), `chr+0x1530` (objeto).
- Vida: `BtlMember_GetActiveGauge(chr)` +0x00/+0x04, o el bloque de miembros `chr+0x9A4 + k*0xA4`.
- `D_003876A0` (puntero en 0x3876A0): `+0xD4` (modo; `func_00212878` = 4) y `+0x4D8` (flags globales;
  `0x100` = pausa/tiempo detenido que **saltea** la copia de `2659B8`).

Del `fight.log` del mismo `vblank`: `acc`, `anim`, `pos`, `vel`, `f9`, `frz`, y las líneas `B31 *` de la sonda.
Del log principal: la línea `RAMDUMP` y cualquier `TRABADO`/`QUIETO`.

## 8. Fix propuesto (condicional; NO aplicar todavía)

No hay un fix mínimo justificado por la comparación C-vs-asm: la cadena de colisión y la de derribo coinciden
con el original. El fix depende de lo que diga la sonda:

- **Si la sonda muestra `acc 99`, vida > 0, `modo != 4` y `8DC |= 1`:** el problema es el gate de get-up.
  El cambio mínimo *de diagnóstico* sería aceptar el modo de batalla real (4/7/8) en `func_00212878` o no
  exigirlo para el get-up en `221520.c:73-78`. **No lo propongo como fix final** hasta comparar el valor del
  modo contra PCSX2: si el original también tiene `modo != 4` en Dueling, el bug es otro.
- **Si la sonda muestra `acc 31` y `e54` sin `0x20`:** el problema es que el contacto no llega. El fix
  mínimo probable es asegurar que `2659B8` corra **después** de la colisión de cada cuadro de lógica (o
  duplicar el pasaje `0xE50 -> 0xE54` al final de `BtlChar_UpdateStage8`), y no depender del draw. Es un
  cambio de orden de cuadro, no de instrucción; hay que medirlo con la sonda.
- **Si la sonda muestra `acc 31`, `e54 & 0x20` y `e54 & 0x40`:** hay un “rompió” falso en un objeto
  irrompible. El fix sería no setear `0x40` cuando el objeto no es rompible (gate `func_0020AA78/AB00` /
  `func_00274680`), pero el asm también ignora el retorno de `func_00274338`; primero hay que ver qué tipo
  devuelve el objeto y qué flags tiene el golpeado.
- **Si la sonda muestra vida 0:** es KO, no es B31; el log `20261111-184449` no sirve como reproducción.

## 9. Descartado y por qué

- **No es el renderer.** El síntoma es de lógica (acción/posición congeladas); el GS no decide acciones.
- **No es el `push out` en sí.** `11D3A0.c` y `11D670.c` coinciden con el asm; el personaje se frena porque el
  empuje funciona.
- **No es (sólo) el límite del área.** El bug se reporta contra rocas/edificios; el código de límite
  (`func_00216990`, `func_0020E6B8`) es otro camino. La sonda `obj+0xE50/0xE54/0xED0` lo distingue.
- **No es la reacción `0x8E`.** La acción `0x8E` no lee `0xE54`; si el estado fuera `0x8E`, el obstáculo no
  sería la causa.
- **El log `20261111-184449` no prueba B31 por sí solo.** Muestra `acc 99` (derribo/KO) y el congelamiento,
  pero no imprime vida ni modo; puede ser un KO normal.

## 10. Referencias rápidas

- Acción `0x99` (derribo): tabla de acciones en `.data` `0x3438E0 + 0x99*16` =
  `[0x221468, 0x221520, 0x221A40, 0x221EE8]`; entrar `port/eq/221468.c:11-25`; correr `port/eq/221520.c:52-110`.
- Acción `0x31` (get-hit/fall con pared): tabla `0x343C10` = `[0x223750, 0x239B48, 0x23A248, 0x23A250]`;
  pared en `port/eq/239B48.c:137-162`; asm `0x239ea0-0x23a128`.
- Colisión: `port/eq/11D670.c:33` (limpieza), `port/eq/11D3A0.c:40-100` (empuje, `0x20/0x40`, `0xED0`).
- Pasaje de contacto: `port/eq/2659B8.c:18-21,34-37`; llamado desde `port/eq/265EB8.c:177,182` (draw).
- Consumo: `port/eq/20D450.c:82-96` (flag `0/0x8000`, `modo==4`) y `port/eq/239B48.c:139`.
- Modo: `src/auto/m2c_212878.c` (`D_003876A0+0xD4 == 4`), asm `0x212878`; setter `port/eq/1040E0.c`,
  `port/eq/104150.c`.
- Cuadrado cargado: `port/eq/23BDA8.c` (decisión), `include/battle/btl_act_i.h:117-120`,
  `include/battle/btl_tech_a.h:22-24,33-43`.

---

# Actualización 2026-11-11 19:00 — corrida `20261111-190045`: la acción trabada es `0xAF`

Este log cambia el diagnóstico de la sección 5. La sección 5 (acción `0x99`) queda como historia: `0x99`
es el derribo/KO, y el log `20261111-184449` no prueba B31. La corrida nueva sí tiene el freeze largo y
muestra otra acción.

## 11. Evidencia del log nuevo

Archivo: `BT2-test/logs/vivo/20261111-190045.fight.log` (3.2 MB, ~6980 vblanks).

- 6307: J2 entra en `acc AF`, `anim 2.00/13.00`, `pos 99.6 -1.9 -49.3`, `vel 0.00`, `f9 00040280`,
  `pad O` (`chr +48 00001100`). El ataque que lo precede es J1 en `acc 4B` (remate de rush cargado) en
  6256-6257, con J2 pasando por `0x8E`, `0x8`, `0x3A`, `0x6`, `0x18`.
- 6325: aparece `BEAM 188218 obj 0x1b83380 stop 0 ...` con origen `101.5 -10.3 -46.4`, o sea **en la
  posición de J2**, no en la de J1 (`129.7 -1.5 5.9`). El `BEAM` es el rayo/ki blast cargado de J2.
- 6328-6330: `CARGA8 chr 017E6000 ...` (J1) y el beam de J2 sigue vivo; J2 `anim 0/30`, `2/16`, ...
- 6331: `BEAM 188218 obj 0x1b83380 stop 1` (el efecto dice que su dueño está parado) y J2 queda
  `anim 6.00/16.00` **congelado**.
- 6332-6979: J2 `acc AF AF FFFFFFFF FFFFFFFF 0`, `anim 6.00/16.00`, `pos 99.6 -1.9 -49.4`, `vel 0.00`,
  `f9 00040280`, `frz 0/0/0`, sin cambios. Son 648 cuadros (~11 s) hasta el final del log.
- J1 sigue en `acc 6` y con animación normal: no es un freeze global.

La acción `0xAF` **no es una animación de reacción del defensor**. En la tabla de acciones de BT2
(`.data` `0x3438E0 + 0xAF*16`) la entrada es `[0x231D48, 0x231F40, 0x232638, 0x232770]`, y el `enter`
`port/eq/231D48.c:32-36` hace:

```c
v3 = func_00217488(arg0);
if (v3 == 0xAF) {
    BattleSide_SetChara(arg0, 0x11C);      /* animación 0x11C = estado 284 */
    func_00206958(arg0, (s64)0x8000 << 38);
    func_002113C0(arg0, 0xF, 0x1000, 1);
    func_00211418(arg0, 0x80000);
}
```

Es la acción de **ki blast cargado** (`btl_act_i.h:128-130`: input “blast held 6 frames” -> `0xAF`),
no la reacción `0xAE/0xAF` del comentario de `btl_tech_a_23F770.c:251`. Ese comentario se refiere al
**campo +0x22 del registro de ataque** (`BtlAtk_GetReactionG`), que devuelve una *animación del defensor*
`0xAE/0xAF`; es otro espacio de nombres. Que el valor `0xAF` termine en `chr+0xC0C` (cola de acción) es
sospechoso y hay que confirmarlo con la sonda (ver §13), pero la acción actual es, sin duda, la de ki
blast cargado.

## 12. Handler y condición de salida

Cadena del `0xAF`:

1. `enter` `port/eq/231D48.c:20-63`: setea animación `0x11C` (estado 284), flags y `obj+0xA30 = 0`.
2. `run` `port/eq/231F40.c:51-214`: máquina de estados de la carga.
   - 284/318/352: arranca la carga (`func_001FA0A0(state+1)`).
   - 285/319/353: mientras `BtlPad_Test48(obj,1)` esté apretado avanza `obj+0xA30`; al soltar pide
     `func_001F9D78(state+1)`.
   - 286/320/354: fase de disparo. `moving = func_00241170(obj, chr) != 0;` (`231F40.c:112-116`).
   - 290/324/358: `func_001F9FB0(obj,0)` (avanza animación).
   - 386: fin/recuperación.
   - Cola común (`231F40.c:155-177`): si `moving == 0`, usa la rama “quieto” (`func_00215068(5,...)`,
     `func_00215E88(6,...)`) y **no avanza** la animación.
3. `decide` `port/eq/232638.c:12-41`: sale sólo si
   - `func_00211310(arg0,4,0x04000000)` (bit de “blast disparado/terminado”), o
   - `func_00211310(arg0,2,1)` (bit de animación terminada), y entonces devuelve `func_0023C710`.
   Si no, devuelve `-1` y sigue.
4. `func_00241170` (`port/eq/241170.c`):
   ```c
   s32 func_00241170(u8 *arg0, s32 arg1) {
       u8 *p = func_00208768(*(s32 *)(arg0 + 0x1534), arg1);
       if (p == 0) return 0;
       return *(s16 *)(p + 0x4A) == 0;
   }
   ```
   Devuelve 0 cuando el estado del ataque/blast (`p+0x4A`) no está “libre”.

En el log, el bit de animación terminada (`chr+0x2B8 & 0x1`, grupo 2 bit 0) **nunca** se prende:
g2 vale `0x10 -> 0x2 -> 0x0` en 6328-6330 y queda 0. La animación está clavada en `6/16`, así que el
evento `0x400` que consulta `231F40.c:112` (`BtlObjAnim_QueryEvent(obj, 0x400, 0, 0)`) tampoco llega.
El beam dice `stop 1` desde 6331: `BtlScene_IsEffectStopped(..., 1)` = `BtlScene_IsCharStopped(dueño)`
(`126748.c:11-13`), y `BtlScene_IsCharStopped` devuelve 1 si `func_0020A658(objId)` o el flag global
`D_003876A0+0x4D8 & 0x100` (`1264F0.c:7-12`).

Hipótesis mecánica (la más ajustada al log): el ki blast cargado de J2 **choca con el objeto irrompible**;
el beam queda `stop 1` (su dueño/estado se marca parado), `func_00241170` devuelve 0, `moving` queda 0,
la animación de disparo se congela en 6/16 y el evento `0x400` / bit `2/1` no llega nunca. El `decide`
no sale nunca. Otro golpe lo libera porque cambia la acción por fuera de este estado.

## 13. C vs asm

- `231D48.c` (enter) ↔ asm `0x231d48`: el `li a1,0x11C`, los `ori` y `func_00211418(0x80000)` coinciden.
- `231F40.c` (run) ↔ asm `0x231f40-0x232634`: el switch por `BtlObjXf_Update` usa la tabla de saltos
  `0x36 0970`; los casos 284/285/286/287/290/318..358/386 y las condiciones `BtlPad_Test48(1)`,
  `func_00241170`, `BtlObjAnim_QueryEvent(0x400)`, `func_00230D30`, `func_002310B8` coinciden con el C.
  En particular, la rama de `286/320/354` es la misma: `moving = func_00241170 != 0`.
- `232638.c` (decide) ↔ asm `0x232638-0x232760`: el test `func_00211310(4,0x04000000)`, el
  `BtlAnim_SetBlend`, el retorno `0xCE/0xCD/0xCF` y el `func_00211310(2,1)` / `func_0023C710` coinciden.
- `241170.c` ↔ asm `0x241170`: `*(s16*)(p+0x4A) == 0` coincide.
- **No hay divergencia C-vs-asm en el handler de la acción 0xAF.** La diferencia está en el estado de
  runtime (beam `stop 1`, `func_00241170` en 0) o en los accesores que no son C:
  `BtlAtk_GetReactionG` y `func_002411E0` no tienen implementación C en `port/eq`/`src` (el decomp matching
  los declara “not decompiled”); corren por el recompilado. Si el valor `0xAF` del registro llega a la cola
  de acción, el problema puede estar ahí, no en `231F40`.

## 14. Sonda siguiente (una corrida)

Además de lo de §6, agregar en `port/full/plat_fightlog.c` (TEMP B31, no aplicado):

```diff
+extern s32 BtlObjXf_Update(unsigned chr);
+extern s32 func_00211310(unsigned chr, s32 grp, s32 bit);
+extern s32 func_00241170(unsigned chr, s32 slot);
+extern s32 func_002411E0(unsigned chr, s32 slot);
+extern s32 func_00212320(unsigned chr);
+extern s32 BtlObjAnim_QueryEvent(unsigned obj, unsigned mask, s32 layer, s32 what);
+extern s32 BtlPad_Test48(unsigned chr, s32 n);
+extern s32 func_0020A658(unsigned id);
@@
         s.valid = 1;
         if (sB31) b31_dump(chr, i, "f");
+        if (sB31) {
+            uint32_t obj = rd32(chr + 0x1530);
+            s32 slot = func_00212320(chr);
+            fprintf(sOut, "%7u J%u | B31AF xf %d 2/1 %d 4/4000000 %d"
+                           " 41170 %d 411E0 %08X ev400 %d pad1 %d a10 %d a30 %.3f stop %d g4D8 %08X\n",
+                    gPortVBlanks, i + 1, (int)BtlObjXf_Update(chr),
+                    (int)func_00211310(chr, 2, 1), (int)func_00211310(chr, 4, 0x04000000),
+                    (int)func_00241170(chr, slot), (unsigned)func_002411E0(chr, slot),
+                    (int)BtlObjAnim_QueryEvent(obj, 0x400, 0, 0), (int)BtlPad_Test48(chr, 1),
+                    (int)rd32(chr + 0xA10), rdf(obj + 0xA30),
+                    (int)func_0020A658(rd32(chr + 0xC)), (unsigned)rd32(rd32(0x3876A0) + 0x4D8));
+        }
```

`func_002411E0` devuelve el estado del ataque/blast; el `decide` mira `& 0x200000`. Si en el freeze
`41170 == 0`, `ev400 == 0`, `2/1 == 0` y `xf == 286` (o 320/354), queda confirmado el deadlock.

También conviene un TEMP en `port/eq/231F40.c` en la rama 286/320/354:

```diff
     case 286: case 320: case 354:
+        { void bt2_fightlog_note(const char *, ...);
+          bt2_fightlog_note("B31AF run286 obj %08X xf %d mov %d ev400 %d", (s32)obj,
+              (s32)obj, (s32)func_00241170(obj, chr), (s32)BtlObjAnim_QueryEvent(*(u8 **)(obj + 0x1530), 0x400, 0, 0)); }
```

## 15. Fix mínimo candidato (condicional, NO aplicar)

Si la sonda confirma el deadlock, el cambio más chico y local es en `port/eq/232638.c`: dar salida al
estado cuando el blast está parado y no hay input, sin tocar la rama normal de carga.

```diff
 s32 func_00232638(u8 *arg0) {
+    static s32 stuck[2];
+    s32 id = (s32)(arg0 - *(u8 **)0x387930) / 0x1550; /* 0/1; o usar arg0->0xC */
@@
 block_11:
     if (func_00211310(arg0, 2, 1) == 0) {
+        /* B31: el disparo se quedó sin evento (beam detenido por un objeto): no colgar la acción. */
+        if (*(s32 *)(arg0 + 0x8CC) > 45 && !BtlPad_Test48(arg0, 1) &&
+            func_00241170(arg0, func_00212320(arg0)) == 0) {
+            if (++stuck[id] > 30) {
+                stuck[id] = 0;
+                BtlAnim_SetBlend(D_003868D8, arg0);
+                return func_0023C710(arg0, 1);
+            }
+        } else {
+            stuck[id] = 0;
+        }
         return -1;
     }
```

Es deliberadamente conservador (45 cuadros de animación, sin botón, blast parado, 30 cuadros de
confirmación) y **no está aplicado**. No lo propongo como definitivo hasta ver la sonda; el fix “correcto”
puede ser marcar el beam como terminado cuando choca con un objeto irrompible (`188218`/`188D68`/`1899F0`,
zona B14) y que `func_00241170`/`BtlObjAnim_QueryEvent(0x400)` se destraben solos.

## 16. Qué capturar con F9/F10 en este freeze

1. Apretar **F9** en el cuadro del freeze (o **F10** si el lanzador no tiene `BT2_F9_RAM`; el `fight.log`
   anota `RAMDUMP f<frame> <archivo>`). El log nuevo es del 19:00; si se repite, anotar el vblank de la
   primera línea `acc AF` con `anim 6/16`.
2. Del `.bin` de 32 MB (misma disposición que PCSX2 `eeMemory.bin`):
   - `u32 roster = rd32(0x387930)`, `u32 chars = rd32(roster)`, `chr = chars + 1*0x1550` (J2).
   - `u32 obj = rd32(chr+0x1530)`.
   - `obj+0xA30` (progreso de carga), `chr+0xA10`, `chr+0x8C0/0x8C4/0x8CC/0x8DC/0x8E0`,
     `chr+0xC00/C08/C0C`, `chr+0xFB0..0xFC8`.
   - `chr+0x1534` (miembro/personaje) y `func_00208768(*(chr+0x1534), func_00212320(chr))`; leer
     `+0x4A` (es lo que mira `func_00241170`).
   - El beam del log (`0x1b83380` en esta corrida; la dirección cambia por heap): `+0xD0` (scene),
     `+0x1DC` (stop kind), `+0x1D8`, `+0xC8`, `+0xC4`, `+0xB4`, `+0x1E0` (head), `+0x84`.
   - `D_003876A0` (puntero en `0x3876A0`): `+0xD4` (modo) y `+0x4D8` (flags; `0x100` = tiempo detenido).
3. Del `fight.log`: las líneas `BEAM`, `CARGA8`, `B31AF`, `B31 COPY/WALL` y el `acc/anim/pos/vel` de J2.

---

# Actualización 20:00 — F9 `20261111-194141_ram1_f12863.bin`: la acción trabada es `0xA9`

Esta corrida la causó la **CPU** y el volcado es del freeze. La acción actual del trabado es
`chr 0x17E7550 = [0xA9,0xA9,FFFFFFFF,FFFFFFFF,0]`; el otro (`0x17E6000`) está en 6 (idle). El
`20261111-194141.fight.log` de la misma sesión permite ver la transición:

- 12564: J2 pasa de `acc 99` a `acc A9`, `anim 2.00/29.00`, `pos -327.4 -32.1 -5.4`, `vel 0.36`,
  `f9 00000080`.
- 12565-12578: `acc A9`, la animación de 29 frames avanza 4, 6, ... 28.
- **12579: `acc A9`, `anim 0.00/13.00`, `vel 0.00`, `f9 00000000`.** La animación de 29 frames se
  reemplaza por un clip de **13 frames en frame 0** y queda clavada hasta el final (16354).
- El F9 es del frame 12863, ya en el estado clavado: `anim 0/13`, `+0x8E0 = 2`, `+0x8E4 = -1`.

La acción `0xA9` es el estado de derribo/caído (`enter` `0x2229F0` setea `BattleSide_SetChara(0xD7/0xD9)`;
`run` `0x222A78`; `decide` `0x222C08`). El clip de 29 frames es el del derribo; el clip de 13 frames que
queda es una **reacción de golpe** (id 2), no el clip del derribo.

## 17. El objeto de animación, campo por campo

`chr+0x152C` y `chr+0x1530` son **el mismo puntero** en el volcado: `0x1718A00`. El objeto es el modelo
(`BtlObj`), no otro. La cabecera del objeto:

| offset | volcado | qué es |
|---|---|---|
| +0x00 | 1 | tipo/estado del objeto (cabecera del `BtlObj`) |
| +0x04 | 4 | id/variante del modelo |
| +0x08 | 0 | — |
| +0x0C, +0x10 | 1, 1 | flags de carga/visibilidad |
| +0x14 | 0 | — |
| +0x18 | 0x008CB9B0 | puntero a datos del modelo (jerarquía/malla), **no** al clip |
| +0x1C | 0x009BA940 | puntero a datos del modelo (esqueleto/transformadas), **no** al clip |
| +0x20 | 0x009FB240 | puntero a datos del modelo (texturas/CLUT), **no** al clip |

Los campos del **clip actual** están en `+0xBD0` (bloque que usan `func_001F9FB0`/`func_001FA110`):

| offset | volcado | qué es |
|---|---|---|
| +0xBD0 | 0 | flags/estado del clip (0) |
| +0xBD4 (s16) | **2** | **id del clip principal** (el que devuelve la animación) |
| +0xBD6 (s16) | 0x1C | id del clip secundario (sub-capa) |
| +0xBD8 | 13.0f | **largo del clip principal** (13 frames) |
| +0xBDC | 12.0f | largo del clip secundario (12) |
| +0xBE0 | 0.0f | **frame actual** (el “frame” real) |
| +0xBE4 | 0.0f | frame previo |
| +0xBE8 | 2.0f | paso por cuadro (`step`) |
| +0xBEC | 0.0f | blend restante |
| +0xBF0 | 0.2222f | paso del blend |
| +0xBF8 | 0x171BF80 | buffer de trabajo del clip principal (`obj+0x3580`) |
| +0xBFC | 0x1726780 | buffer de trabajo del clip secundario (`obj+0xDD80`) |

El “clip terminado” que espera el `decide` es el **bit 0 del grupo 2** (`chr+0x2B8 & 1`). Lo prende
`func_001F9FB0` cuando `frame >= length` (`1F9FB0.c:21-30`). En el volcado `chr+0x2B8 = 0` (bit 0 en 0).
La función `BtlObjXf_Update` **no lee +0xBD4**: lee `*(s32 *)(chr+0x8E0)` (asm nativo
`0x4011b1f0: mov 0x8e0(%rdi),%eax; ret`). En el volcado `chr+0x8E0 = 2`, y por eso el `run` de `0xA9`
cae en el `default` del switch (espera `0xD7/0xD8/0xD9/0xDA`).

## 18. Por qué `func_00211310(obj,2,1)` nunca da != 0

No es que el clip no se pida ni que el objeto sea otro:

- El clip del derribo **existe**: `obj+0x60 + 0xD7*4 = 0x00D9ECC0` y `+0xD9*4 = 0x00D9F9C0`, ambos
  punteros válidos. `func_0025EF60` los encuentra y `func_0025F990` copia el clip al buffer `+0x3580`.
- El `enter` de `0xA9` pide `0xD7/0xD9`; en el log se ve el clip de 29 frames del derribo desde 12564.
- A las 12579 alguien pide el **clip 2** (13 frames) y lo aplica: `chr+0x8E0 = 2`, `chr+0x8E4 = -1`
  (firma de `BattleSide_SetChara(chr,2)`/`func_001F9C10(chr,2)`), y el objeto queda con clip id `2`,
  largo `13`, frame `0`.
- El `run` de `0xA9` sólo llama a `func_001F9FB0` (el que avanza y prende `2/1`) en los estados
  `0xD7/0xD8/0xD9/0xDA`. Como `BtlObjXf_Update` devuelve `2`, no avanza el frame; el frame queda en 0 y
  `frame >= 13` nunca ocurre. El clip de 13 frames **no arranca** porque no es el clip que el estado
  `0xA9` sabe manejar.

El valor `2` es sospechoso: es el id de reacción `BTL_REACT_NO_FLINCH` (`btl_char_hit.h`), no una
animación de derribo. La cadena que lo aplica es la de petición diferida de animación:
`func_001F9D78(chr, 2)` / `func_001F9DB8(chr, 2)` dejan `chr+0x8E4 = 2` y el bit `2/0x10/0x20`; el
dispatcher `214A08.c:103-109` hace `BattleSide_SetChara(chr,2)` o `func_001F9C10(chr,2)`, que escribe
`chr+0x8E0 = 2` y `+0x8E4 = -1`. El volcado coincide exactamente con esa firma. El pedido de animación 2
llegó **después** del `enter` del `0xA9` (o en el mismo cuadro, después de la cola) y pisó el clip del
derribo.

## 19. Fix mínimo o sonda siguiente

### Sonda (la que decide)

1. TEMP en `port/eq/1F9D78.c` y `port/eq/1F9DB8.c`: si `arg1 == 2`, imprimir
   `chr`, `arg1`, la acción actual `*(s32*)(arg0+0xC00)` y `__builtin_return_address(0)`. Ese return
   address se busca en `port/build/full/bt2full.map` y dice **quién pide la animación 2**.
2. TEMP en `port/eq/1F9AC8.c` y `port/eq/1F9C10.c`: imprimir cada `arg1` y el return address; así se ve
   si el `enter` de `0xA9` pidió `0xD7` y quién pidió `2` después.
3. Watchpoint: en el primer cuadro de `0xA9`, `bt2_watch_byte(chr+0x8E0)` (o `obj+0xBD4`); el fallo de
   escritura anota la dirección nativa del escritor, que se resuelve con el mapa. Es la forma más directa
   de cazar al que escribe `2`.

### Fix candidato (NO aplicado)

- **Correcto:** en el que pide la animación 2 (lo dirá la sonda), no aplicar una animación cuando la
  reacción es `2` (`BTL_REACT_NO_FLINCH`: “el golpe duele pero el defensor conserva su acción”). Es un
  bug de traducción de la reacción: el id de reacción se usa como id de animación. La corrección va en el
  llamador de `func_001F9D78`/`func_001F9C10`, no en el objeto de animación.
- **Workaround mínimo y local** en `port/eq/222A78.c` (run de `0xA9`): si el estado actual no es
  `0xD7..0xDA`, volver a pedir el clip del derribo y salir; así el clip 2 no deja la acción sin avance:

```diff
 void func_00222A78(s32 arg0) {
+    extern s32 func_00218838(s32, s32);
+    extern void BattleSide_SetChara(s32, s32);
     s32 v0;
@@
     v1 = BtlObjXf_Update(arg0);
+    if (v1 != 0xD7 && v1 != 0xD8 && v1 != 0xD9 && v1 != 0xDA) {
+        /* B31: la reacción (anim 2) pisó el clip del derribo; reaplicarlo. */
+        BattleSide_SetChara(arg0, func_00218838(arg0, 0) ? 0xD9 : 0xD7);
+        return;
+    }
     if (v1 == 0xD8) {
```

Es un parche de seguridad: puede repetir el clip de derribo una vez, pero evita el freeze. El fix
definitivo es el del llamador que pide 2.

## 20. Qué capturar con F9 en la próxima

El F9 actual es del frame 12863, 648 cuadros después del cambio; sirve para el estado, no para el
escritor. Para la próxima:

- Apretar F9 en el **primer cuadro de `acc A9`** (12564 en este log) y en el **cuadro 12579** (cuando
  `anim` pasa a `0/13`), no al final.
- Leer en el `.bin`:
  - `chr = roster(0x387930) + 1*0x1550`; `obj = *(u32*)(chr+0x1530)`.
  - `obj+0xBD0..0xBF0` (id `+0xBD4`, largo `+0xBD8`, frame `+0xBE0`, step `+0xBE8`,
    buffers `+0xBF8/+0xBFC`).
  - `chr+0x8E0` (id que devuelve `BtlObjXf_Update`), `chr+0x8E4` (pedido pendiente), `chr+0x8EC`
    (sub-animación), `chr+0x8CC` (frame de acción), `chr+0xC00/C04/C08/C0C`.
  - `chr+0x2B8` (grupo 2; bit 0 = clip terminado).
  - `chr+0xFB0..0xFC8` (reacción del golpe; `+0xB48` = id de reacción).
  - La tabla de punteros `obj+0x60+id*4` para `0xD7`, `0xD9` y `2` (para probar que los clips existen).
- Del `fight.log`: las líneas de `J2` alrededor de 12564-12579 (`acc`, `anim`, `f9`, `GOLPE B48`).

---

# Actualización 21:00 — causa raíz confirmada: el `run` de `0xA9` descarta el retorno de `BtlObjXf_Update`

Las sondas de la sesión `20261111-201545` cierran el caso:

```
B31ANIM2 fn BattleSide_SetChara chr 017E7550 acc A9 ret 0x40265b9f anim 215   (enter 0xA9, 0xD7)
B31ANIM2 fn func_001F9D78       chr 017E7550 acc A9 ret 0x40243a50             (lo pide func_001FA0A0+0x20)
B31ANIM2 fn BattleSide_SetChara chr 017E7550 acc A9 ret 0x4025967c anim 2    (214A08 aplica +0x8E4=2)
```

El que pide `func_001FA0A0(chr, 2, 0)` **no es el código de golpe ni el motor**: es el propio `run` de la
acción `0xA9`, `port/eq/222A78.c`, en su bloque `common_0xDB`. El C actual hace:

```c
common_0xDB:
    v0 = func_00211310(arg0, 0, 4);          /* 1 si está en el piso */
    if (v0 == 0) {
        func_001F9FB0(arg0, 0);
    } else {
        BtlObjXf_Update(arg0);               /* <-- descarta el retorno */
        v0 = func_001FA0A0(arg0, v0 + 1, 0); /* v0 sigue siendo 1 => pide 2 */
        ...
```

El asm `0x222adc-0x222b04` hace lo contrario:

```asm
222ae0  jal 0x211310          ; TestFlag(arg0,0,4)
222ae8  beqzl v0, 0x222b30    ; 0 -> func_001F9FB0
222af0  jal 0x1fa390          ; BtlObjXf_Update -> v0 = xf
222af8  move a0,s0
222afc  move a2,zero
222b00  jal 0x1fa0a0
222b04  addiu a1,v0,1         ; a1 = xf + 1
```

O sea: el original pide **`xf + 1`**. Para el derribo `xf = 0xD7` pide `0xD8`; para `0xD9` pide `0xDA`
(los clips de “levantarse”). El C, al descartar el retorno de `BtlObjXf_Update`, deja `v0 = 1` (el
resultado del `TestFlag`) y pide `2`. `2` es una animación de reacción (`BTL_REACT_NO_FLINCH`), de 13
frames, que el `run` de `0xA9` no sabe avanzar. **Ésa es la causa raíz de B31, y es un bug de
traducción C-vs-asm, no del input ni de la colisión.**

El workaround que se aplicó (reaplicar `0xD7/0xD9` cuando el estado no es `0xD7..0xDA`) tapa el síntoma
pero provoca el loop observado: el estado se vuelve `2` por el pedido erróneo, el workaround reaplica
`0xD7/0xD9`, y el clip de derribo de 29 frames vuelve a empezar. Hay que **revertir el workaround** y
aplicar esta línea.

## 22. Fix de raíz (mínimo)

Archivo: `port/eq/222A78.c`, bloque `common_0xDB` (líneas 45-56). Revertir el workaround y dejar:

```diff
     } else {
-        BtlObjXf_Update(arg0);
+        v0 = BtlObjXf_Update(arg0);
         v0 = func_001FA0A0(arg0, v0 + 1, 0);
         if (v0 != 0) {
             func_00212DD8(arg0, 0);
             func_002100C0(arg0, 2);
         }
     }
```

o, equivalente y más corto:

```c
v0 = func_001FA0A0(arg0, BtlObjXf_Update(arg0) + 1, 0);
```

Efecto: al terminar el clip de 29 frames, el `run` pide `0xD8`/`0xDA` en vez de `2`; el motor aplica el
clip de levantarse; el `decide` de `0xA9` (`func_00211310(obj,2,1)`) recibe el clip terminado y sale por
`func_0023C710`. No hace falta tocar `BattleSide_SetChara`, `func_001F9D78` ni la tabla de reacciones.

## 23. ¿Por qué el original no loopearía?

Porque en el original `BTL_REACT_NO_FLINCH` (2) significa “el golpe duele pero el defensor conserva su
acción”: no se pide una animación nueva. El `run` de `0xA9`, cuando el personaje está en el piso, no debe
pedir la animación `2`; debe pedir el siguiente clip del propio derribo (`xf + 1`, o sea `0xD8/0xDA`). El
C actual convierte el `TestFlag(0,4)` (=1) en “2” y pide una reacción, que es exactamente lo que el
comentario de `btl_char_hit.h` prohíbe para “no flinch”. La colisión con el objeto irrompible sólo elige
el momento/estado (`0xD7/0xD9` + piso); no es la causa.

## 24. Video

`Videocaptura de pantalla_20261111_201632.webm` (31 s, 60 fps). Los primeros ~2 s muestran a Gohan
recibiendo el golpe, cayendo y quedando en el piso; a los ~2 s el usuario abre **1P PAUSE** y sale al
selector de personaje/mapa. El video no muestra el loop con claridad porque se pausa antes de que se
repita; las capturas 1-2 s son consistentes con “derribado en el piso” y no agregan información sobre el
reinicio. El dato exacto del reinicio está en el `fight.log`: el clip de 29 frames llega a 29 y en el
cuadro siguiente pasa a `0/13` (clip 2), que es el pedido erróneo de `func_001FA0A0(chr,2)`.

## 25. Sonda opcional (sólo si se quiere ver el return address exacto)

Si se quiere confirmar el llamador de `func_001FA0A0`, agregar en `port/eq/1FA0A0.c`:

```diff
 s32 func_001FA0A0(s32 a0, s32 a1, s32 a2) {
+    void bt2_fightlog_note(const char *, ...);
+    if (a1 == 2) bt2_fightlog_note("B31 CALL 1FA0A0 chr %08X a1 2 ret %p", a0, __builtin_return_address(0));
     s32 r;
```

El return address va a caer dentro de `func_00222A78` (nat. `0x40265b10 + 0x88 = 0x40265b98`), que es el
`jal 0x1fa0a0` del bloque `common_0xDB`. No es necesaria para el fix: el asm ya lo prueba.
