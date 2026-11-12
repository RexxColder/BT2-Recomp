> Informe completo de B14 (síntoma, hipótesis, evidencia, descartes, errores y backups): **`B14_investigacion_kamehameha.md`**.
> Este archivo es el detalle del constructo del rayo (clase `0x341F60` y corrección del `EftRay`=lente).

# Constructo del rayo ("Kamehameha", tipo 12) — 2026-11-07

Mismo método que las ventanas de diálogo: desde el efecto visible hasta la tabla y los que la llenan.
Evidencia: log `20261107-003926` (frames 8194-8258) + F9 `ram3_f9447` + dumps `ramkey` de `20261107-010126`.

## Cadena de creación

1. **Movimiento → tabla de efectos.** `func_0014B078` recorre la tabla del movimiento: `*(u8 **)a2` + `0x110*k`
   (16 bloques), dentro `+0x10` y filas de `0x20` bytes; `fila[1]` es el **tipo**. Para cada fila llama a
   `func_001513D0(p0, ctx, ..., vTmp, p4, vOut, type, slot, ...)`.
   - `vTmp` = origen (punto de disparo), `p4` = **target**, `vOut` = vector auxiliar.
2. **Dispatcher.** `func_001513D0` (`port/eq/1513D0.c`) tiene 15 casos. **Caso 12 = rayo** →
   `func_00150C68(ctx, ent, cw[...], cw[...], &slot, cflags, owner, vTmp, p4, vOut, ...)`.
3. **Spawner.** `func_00150C68` (`port/eq/150C68.c`) arma un `ObjBuild`:
   `v1 = origen`, `v2 = origen`, `v3 = target (p4)`, `v4 = vOut`, `ctx = base + 0x1AB8`, `desc3`, `mode`, etc.,
   y crea la task: `func_0018BA90` → `BtlTaskList_AddTail(D_003877B4 + 0x7AF4, D_00341F78, &build)`.
   - `D_00341F78` es la **tabla de clase** del rayo, en RAM `0x341F60` (12 punteros).
4. **Tabla de clase (`0x341F60`)** — volcada de la RAM y del ELF:
   - `+0x00 187E58` no-op · `+0x04 187DF8` aux · `+0x08 187E90` term/reset · `+0x10 187E60` reset (memset 0x79E0)
   - `+0x18 188218` **update** · `+0x1C 187EC0` **init** · `+0x20 1889F0` no-op (`jr ra`)
   - `+0x24 188838` teardown · `+0x28 188978` aux · `+0x2C 188850` **draw**
5. **Init `187EC0`** (con el `ObjBuild` como arg1):
   `+0x30/+0x34` = dueño; `+0x40/+0x48` = v1; `+0x50/+0x58` = v2; `+0x60/+0x68` = v2;
   `+0x70` = `v3 - v2` (dir inicial); `+0x80..+0xBC` radios/timers (random del descriptor);
   `+0x1D8 |= 2` (activo), `+0x1D4`, `+0x1E0/+0x1E4` = lista de nodos.
6. **Update `188218`**:
   - `+0x70 = normalize(+0x60 - +0x50)`; `+0xC4 = |+0x60 - +0x50|` (largo);
   - avanza radios/timers; crea nodos (`1890C8` → `1889F8` / `188D68`);
   - por nodo: `+0x10` = dir del objeto (`188F78` copia `obj+0x70`), `+0x20` = color;
   - `18A2C8` / `18A5A0` arman la matriz y transforman **in place** los 4 corners del nodo (`+0x40..+0x70`);
   - `1899F0` recorre los nodos y emite los quads (`18A9C0`); `188850` es el draw.
7. **Actualización por frame del slot** (mismo `1513D0`, `cflags & 8`): `18BB50` `+0x40 = origen`,
   `18BDE0` `+0x50 = origen`, `18BE48` `+0x60 = target (p4 = shot + 0x80)`.
   - En el log: frame 8194 `fl 1` (sólo crea); 8195+ `fl 28` (0x8|0x20) → actualiza.

## El bug

- En los frames de **largo 0** (8194/8195 y 8229/8230) `Vec3_Normalize` (`port/eq/129AE8.c`, macro VU0 `vrsqrt`)
  hacía `1/sqrt(0) = Inf` y `0*Inf = NaN`. La PS2 devuelve el float máximo y `0*max = 0`.
- Ese NaN iba al `dir` del objeto, de ahí al `+0x10` del **nodo** (`188F78`), a `asin/atan` de `18A2C8` y a la
  matriz; los corners se transforman **in place**, así que quedaban NaN **para siempre** aunque el largo volviera
  a 101/252.
- **Arreglado** en `129AE8` (caso 0 → `0x7F7FFFFF`, NaN→NaN). Backup `129AE8.c.pre_vu_div0`.

## Evidencia de que el mecanismo funciona

- Log `20261107-003926`, objeto `0x1b8fcc0`: `C4` (largo) = 0 → **101.1** (8196-8220) → 90.8 (8228) → 0 (8229-30)
  → 36/72/108/180/252.8 (8231+). O sea el rayo **se extiende** y cambia de largo con el target.
- F9 `ram3_f9447`, mismo objeto ya muerto: `+0x60 - +0x50` = 288.9 y `+0x70` unitario válido.
- Dumps `ramkey` (010126): el target `shot+0x80` **se llena en runtime** (en `ramkey2` = posición de J2
  `403.0 -36.6 -368.3`); en otros frames está en 0 (el aim se calcula sólo en ciertas fases).

## Pendiente

- **Verificar visualmente con un rayo real** (el del log fue con el build viejo, antes del fix; la corrida
  `010126` no tuvo `tipo 12`). Reproducir: personaje de la sesión `003926` (**Piccolo**, izquierda), **Tri+L2**
  (`acc AD`), y **F10** cuando sale el rayo.
- Los 2 primeros frames el target es `(0,0,0)` (el aim llega después): con el fix el rayo nace apuntando al origen
  del mundo y recién al 3.er frame toma el target. Si se ve un parpadeo raro al nacer, es eso.
- `1878A0` / `187B18` (escriben `+0x60`) y `18BBC0` **no están referenciadas** en ELF, overlay ni RAM: código
  muerto (probable herencia de BT3). No son la causa.

## Kamehameha de Goku (2026-11-07, segunda parte)

- El ataque (acc `AF`) **no usa el `tipo 12`**: usa los tipos de la tabla de efectos `0xCC69C0` (bloques
  0,1,2,3,5,8,10,11; los demás count 0). Despachador: **`14A6D0`** (no `14B078`).
- Tamaños medidos (log `B14 T5C/T5S/T10`): `tipo 5` nace con `scale 0` y queda en **1.0–1.5** (la bolita);
  `tipo 10` (flash) usa `w = 12.6/18/2.7` (grande). Sin Inf/NaN.
- **El cuerpo es el `tipo 8`**: `14F320` → `EftRay_Create` (`0x1B3880`, código de BT3 `eft_s.c`). Se crea
  (`fl 1` en el log) y el handle existe (`pass+0x200+slot*8+4`, p.ej. `0x1BAC940`, con partes en
  `0x1BACA40/…`). Su geometría en RAM es válida (posiciones ~181–198, ángulos −2.6).
- **No se dibuja y el renderer no lo descarta**: en la sesión `010907` los contadores `dropped by site` dan
  **0** en todos los sitios. O sea el draw **no se emite**: el `EftRay` corre por el **relleno (PS2Recomp)**,
  no hay C propio.
- El camino `195250` (`18BA90`, misma clase que el rayo de Piccolo) **sólo crea el cuerpo si el personaje NO
  está en técnica**; en técnica `1957F8`→`195538` lo **borra**. El `195738` (manager) no se llama en el port
  (clase `0x342040`, entrada +0x20) — no es el camino de este ataque.
- Siguiente paso acordado: **traducir el `EftRay` a C** (BT3-Decompiled tiene el mismo código, `eft_s.c`) y
  cablearlo en `port/eq/`, para que emita el draw del cuerpo.

## EftRay: estado al portar (2026-11-07, noche)

- `EftRay_Create` (`0x1B3880`, fill) se llama desde `14F320` (tipo 8) y **crea la tarea**:
  `0x1BAC940`, clase `gEftRayClass = 0x342818` (puntero en tarea+0x28), data `0x1BACA40` (+0x38).
- `EftRay_Update` (`0x1B3E68`, miembro +0x00 de la clase) **sí corre**: la geometría de `0x1BACA40`
  cambia entre F10 (posiciones ~181–198, ángulos) y no hay NaN.
- El **draw** son otros miembros de la clase: `+0x30 1B5400`, `+0x34 1B52D8`, `+0x38 1B53C8`, `+0x3C 1B54B8`
  (chequean `BtlScene_IsEffectStopped`, leen `data+0x2C/0x30/0x50` y dibujan). `1B5548` (+0x18) es no-op.
- La tabla de clase `0x342818` es la **única** referencia a esos miembros: el motor los llama por offset.
  En el port **no se llaman** (0 draws y 0 descartes del renderer) → falta el **dispatch del draw** de esta
  clase. El rayo de Piccolo (clase `0x341F60`) sí dibuja porque su draw está en `+0x2C` y ese sí se llama.
- Conclusión: portar `EftRay_Update` no alcanza (ya corre). Siguiente: encontrar el pass que debe llamar a
  `class+0x30..0x3C` para las tareas de rayo (probablemente en el overlay/relleno) y por qué lo saltea.

## Corrección: el `EftRay` es un LENTE, no el cuerpo (2026-11-07)

- `1B5400` (miembro +0x30 de la clase del ray) **no dibuja el rayo**: llama `GfxLens_SetHold/SetPos` →
  es un **lente/flash de pantalla** (y mata la tarea). `1B5630` es un helper que setea un flag del lente.
- El `EftRay` ("ray burst") es el **estallido de luz**, no el cuerpo continuo. Descartado como cuerpo.
- El cuerpo del Kamehameha **sigue sin identificar**: no es el `tipo 5` (tamaño 1–1.5), ni el `tipo 10/11`
  (sprites radiales pegados al personaje), ni el `EftRay` (lente), ni el `18BA90`/`195250` (sólo no-técnica).
- Candidatos a revisar: el efecto **"chain"** (`EftChain2`, clase `0x3427E8`, update `0x1B2FD0`; el C está en
  `src/battle/xc_1B3C98.c` y derivados, con `#ifdef PORT`) y/o un **mesh de la técnica** pegado a la animación
  del personaje (fuera del sistema de slots).
