# B14 — Kamehameha: "bola flotante, falta el cuerpo del rayo"

Informe de investigación completo (2026-11-07). Todo lo de abajo salió de logs, volcados F9/F10, el video de las
partidas y el asm/descompilado. Los valores son los medidos; las hipótesis descartadas quedan con el motivo.

---

## 1. Síntoma

- Reportado por el usuario: el **Kamehameha** (y rayos de Ultimates) sale como **una bola flotante**; **falta el
  cuerpo del rayo**.
- Video de la sesión `20261107-003926` (GPU, Piccolo vs Roshi): a los 136.6–137.6 s (frames 8194–8258) **no se
  dibuja nada** del rayo; el visor no ve geometría. En la Light Grenade (150.6 s) aparece el cartel y después un
  **bloom redondo pegado al torso** y una **esfera suelta** que casi no se mueve (4.1 s → ~10 px).
- Video de `20261107-010907` (Goku, torneo): a los 84.9 s y 89.0 s (los dos F10) hay un **estallido blanco/azul
  grande** centrado en las manos y una **esfera chica clavada** a la izquierda del personaje. Sin cuerpo.
- **Confirmado por software**: el usuario probó con el renderer GS por software y el problema es el mismo
  (importante: ver §7, la prueba no descarta del todo el renderer porque `gs_draw.c` es compartido, pero los
  contadores de descarte dan 0).

## 2. Sesiones usadas

| sesión | modo | qué aportó |
|---|---|---|
| `20261106-234124` | pelea | crash de sonido (otro bug, §8) |
| `20261107-000314` | pelea | crash página cero en `2A3C08` (otro bug, §8) |
| `20261107-002717` | pelea | crash del wrap en `lookup` (otro bug, §8) |
| `20261107-003926` | duelo Piccolo/Roshi | **el único log con el rayo `tipo 12`**: BEAM 8194–8258; video 136–159 s |
| `20261107-005131` | entrenamiento | sin `tipo 12` (no sirve para el cuerpo) |
| `20261107-010126` | torneo | F10 ×5 + F9 ×2; sin `tipo 12` |
| `20261107-010907` | torneo (Goku) | **F10 durante el Kamehameha**: `ramkey1_f5091`, `ramkey2_f5335` |
| `20261107-011812` | entrenamiento | el ataque pasó por `1513D0` (7461 líneas B10) pero **no** por `14B078` |
| `20261107-012445` | entrenamiento | logs de tamaño del sprite (`B14 T5C/T5S/T10`) |
| `20261107-012814` | entrenamiento | logs del manager del rayo (`B14 BEAMMGR/CREATE/STOP`): 0 líneas |

## 3. Herramienta nueva (necesaria para este bug): F10 = volcado de RAM

- **F9** = volcado del cuadro + RAM (si `BT2_F9_RAM`); **F10** = **RAM sola** (32 MB) al instante.
- Implementado en `port/full/gs/gs_core.c` (`gRamDumpKey`, bloque en `screenshot()`), y la tecla en los 3 backends
  (`gs_core.c`, `gs_gl.c`, `gs_gpu.c`).
- Archivo: `<BT2_RAMDUMP_DIR | BT2_F9_RAM | logs/vivo>_ramkey<N>_f<frame>.bin`; además deja
  `RAMDUMP f<frame> <archivo>` en el `fight.log` (para alinear con `B10`/`BEAM`).
- Sin tecla: `kill -USR2 $(pgrep -x bt2)` → `/tmp/bt2_port_ram.bin` (handler que ya existía en `mem.c`).
- Backups: `gs_core.c.pre_ramkey`, `gs_gl.c.pre_ramkey`, `gs_gpu.c.pre_ramkey`, `bt2.pre_ramkey`.

## 4. Qué se probó, en orden (con evidencia)

### 4.1. El rayo de Piccolo (`tipo 12`) y el NaN de `Vec3_Normalize` — **ARREGLADO**

- En `20261107-003926`, el rayo `tipo 12` spawnea en el frame 8194 (pad `Tri+L2`, `acc AD`, objeto `0x1b8fcc0`).
- Log: `BEAM 188218 ... C4 0.0` → al frame siguiente `BEAM 18A2C8 dir -nan -nan -nan asin nan atan -nan ...
  M0 nan ... M3 nan ... post nan`; nodo `0x1b87f90` con NaN; `c0/c1` NaN.
- Causa: `port/eq/129AE8.c` (macro VU0 `vrsqrt`) hacía `q = 1.0f / sqrtf(len2)`; con largo 0 → `Inf` en el host
  y `0*Inf = NaN`. La PS2 devuelve el float máximo y `0*max = 0`. Los corners del nodo se transforman **in place**
  (`18A2C8`), así que el NaN quedaba pegado para siempre aunque el largo volviera a 101/252.
- **Arreglo**: caso 0 → `gVu0.q = 0x7F7FFFFF`; NaN→NaN. Backup `129AE8.c.pre_vu_div0`; binario
  `bt2.pre_vu_div0`. Verificado en el binario (`ucomiss` + `movl $0x7f7fffff`).
- Evidencia de que el mecanismo funciona: `C4` del objeto 0x1b8fcc0 = **0 → 101.1 (8196-8220) → 90.8 (8228) →
  0 (8229-30) → 36/72/108/180/252.8 (8231+)**; en el F9 `ram3_f9447` el objeto (ya muerto) tiene
  `+0x60 - +0x50 = 288.9` y `dir` unitario válido. Impacto: sólo los frames de largo 0 tenían NaN.
- **Estado**: instalado; el usuario lo probó pero **el ataque que probó no era este `tipo 12`** (Goku usa otro
  camino), así que este fix sigue **sin verificación visual**.

### 4.2. "El log no tiene `tipo 12`" — **ERROR MÍO**

- Insistí dos veces con que la prueba no incluía el ataque. **Falso**: el Kamehameha de Goku **no usa el spawner
  `tipo 12`**; usa la tabla de efectos (tipos 0/1/2/3/5/8/10/11). El usuario tenía razón.

### 4.3. La tabla de efectos (`0xCC69C0`) y el despachador (`14A6D0`)

- La tabla runtime está en RAM `0xCC69C0` (16 bloques de `0x110`; count en +0; filas de `0x20` desde +0x10).
  Contadas en el dump: **0:1, 1:2, 2:1, 3:1, 5:4, 8:1, 10:6, 11:2**; el resto 0. **Todas las filas con count>0 se
  despachan** (no falta ninguna).
- Despachador real: **`func_0014A6D0`** (`port/eq/14A6D0.c`), identificado por los punteros del log:
  `p0=*(s1+0xB0)=0x1bc9be0`, `ctx=arg2=0x1bce880`, `p2=s1+0xB4=0x1bd9834`, `p3=s1+0x860=0x1bd9fe0`,
  `p4=s1+0x80=0x1bd9800`, `dir=s1+0x30=0x1bd97b0` → `s1=0x1bd9780` (el "shot").
- `s16@+0x18` de cada fila (escala de los spawners): 0 en casi todas; **1/1 = 512** y **8/0 = 150**.
- Instrumenté primero `14B078` (log `B14 ROWS` → **0 líneas**; función equivocada) y después `195738/195250/195538`.

### 4.4. Tamaños medidos de los sprites

- `tipo 5` (4 sprites; el "wave" chico): creación `scale 0` (row18=0), `f2=1.2`, `f3=0.9`; por frame
  `ratio=f2/f1 = 1.0–1.5`, `q = row[0x10]/row[0xC] = 0`, `cur = arg8*ratio = 1.0–1.5`, `arg8=1.0`. **Sin Inf/NaN**;
  el tamaño queda 1–1.5 (la bolita).
- `tipo 10` (6 sprites; el flash): `entF 0`, `w = 12.6/1.8/18/2.7`, `scale 1.8`, `row18 0`; el tamaño por frame
  usa `w` (grande). Pegado al personaje (posición del sprite = la del personaje).

### 4.5. El manager `195738` y el `18BA90`/`195250` — **no es este ataque**

- `195738` (clase `0x342040`, entrada +0x20) **no se llama nunca** (0 líneas `B14 BEAMMGR`).
- `195250` (crea el cuerpo `18BA90`/clase `0x341F60`) se llama **sólo si el personaje NO está en técnica**
  (`BtlCharApi_IsInTechnique == 0`); si está en técnica, `1957F8`→`195538` lo **borra**. En el Kamehameha (técnica)
  no se crea. El "puente" `1957D8` (fix previo) cubre sólo el otro camino.

### 4.6. `EftRay` (`tipo 8`) — **es un lente, no el cuerpo**

- Se crea (`fl 1` en el log): tarea `0x1BAC940`, clase `0x342818`, data `0x1BACA40`; geometría válida y animando
  (posiciones ~181–198, ángulos −2.6, difiere entre F10).
- `EftRay_Update` (`0x1B3E68`, miembro +0x00) **corre** y no dibuja (sólo estado/geometría; rand/ángulos).
- Los "draw" de su clase: `+0x30 1B5400`, `+0x34 1B52D8`, `+0x38 1B53C8`, `+0x3C 1B54B8`; **`1B5400` llama
  `GfxLens_SetHold/SetPos`** → es un **flash/lente** y además mata la tarea. `1B5548` (+0x18) es no-op.

### 4.7. `EftChain2` (la cadena) — **es un burst, no un rayo continuo**

- Tarea `0x1B5C200`, clase `0x3427E8`, work `0x1B5C380`; 16 tramos de `0xA0` desde `+0x40`; flag activo en `+8`.
- En los dos F10: 11 tramos inicializados (`+4 = 7` nodos, puestos por `func_001B0CD0`) y **ninguno activo**
  (`+8 = 0`); timer `+0xA5C` alterna **1 → 0** → emisor de bursts de vida corta (los tramos expiran entre F10).
- `func_001B2930` dibuja sólo los tramos con `flag & 1`; `func_001B2090` crea un tramo (pide nodos con
  `func_001B0CD0`, pone `+8 |= 1`, y devuelve 0 si `+4 < 3`).
- Conclusión: es el **estallido de tramos** (probablemente el "bloom" grande), no el cuerpo continuo.

### 4.8. Otras comprobaciones

- **Render descartes**: en las sesiones del ataque (`010907`) `dropped by site` = **0 0 0 0 0 0**; no hay
  primitivas descartadas. (Los descartes viven en `gs_draw.c`, compartido por software y GPU; por eso en general
  la prueba por software no descarta el renderer, pero acá los contadores son 0.)
- **"Efecto parado"**: `gBtlStage = 0xF36D00` (no nulo) y `D_003876A0+0x4D8 = 1` (sin `0x100` ni `0x2000`) →
  `BtlStage_IsReady()=1`, `IsTimeStopped()=0`: los efectos **no** están congelados por esa vía.
- **Inventario de tareas vivas** (F10 del ataque): 7 × `EftPtcl3` (0x3428F0), 4 × Sprite (0x3434F0), 1 × chain
  (0x3427E8), 1 × ray (0x342818), 0 × beam (0x341F60).
- **`shot` (`0x1BD9780`)** en los dumps: `+0x30` = dirección unitaria; `+0x80` = **target** (en `ramkey2` es la
  posición de J2: `403.0 -36.6 -368.3`; en otros frames 0); `+0xB0 = 0x1bc9be0` (dueño). O sea el target se llena
  en runtime; no es un valor fijo de bug.

## 5. Qué se descartó (resumen)

| hipótesis | resultado |
|---|---|
| NaN del `Vec3_Normalize` mata el rayo | **cierto** para el `tipo 12` (arreglado); **no aplica** al cuerpo de Goku |
| falta una fila en la tabla de efectos | falso: todas las filas con count>0 se despachan |
| el `tipo 5` es el cuerpo | es una bolita de 1–1.5 (dato), no el cuerpo |
| el `tipo 10/11` es el cuerpo | es el flash radial pegado al personaje |
| el `EftRay` (tipo 8) es el cuerpo | es un lente (`GfxLens`) |
| el `EftChain2` es el cuerpo | es un burst de tramos de vida corta |
| `18BA90`/`195250` crea el cuerpo | sólo si NO está en técnica; en técnica lo borra |
| el manager `195738` no corre y por eso no hay rayo | irrelevante: no es el camino de este ataque |
| el renderer descarta el cuerpo | no: 0 descartes en el ataque |
| los efectos están "parados" | no: `IsTimeStopped=0` |

## 6. Estado actual y siguiente paso

- B14 **sigue abierto**. Lo que se arregló (el NaN del `tipo 12`) es real y quedó instalado, pero el **cuerpo
  continuo** del Kamehameha de Goku **no es ninguna tarea del sistema de efectos** que hayamos podido crear/ver.
- La hipótesis viva: el cuerpo es un **modelo/mesh de la técnica** (la "ola" del Kamehameha) dibujado por el
  renderer de modelos/personajes, no por los slots de efectos.
- Siguiente paso concreto: buscar ese mesh en el sistema de modelos de la técnica (los `mc_*`/personajes) y ver
  si la instancia se crea y se dibuja; si no, comparar el *draw list* de un frame con la ola (hay que agregar un
  volcado de la lista de dibujos, el F9 sólo da RAM + estadísticas).
- Herramientas ya listas: F10 (RAM), F9 (RAM+stats), logs `B14 ROWS/T5C/T5S/T10/BEAMMGR/CREATE/STOP` (TEMP, hay
  que quitarlos cuando B14 cierre), dumps `ramkey1/2` de `010907`.

## 7. Errores y correcciones (para no repetirlos)

- Insistí con el `tipo 12` y dije que la prueba no incluía el ataque: **era el ataque, otro sistema**.
- Instrumenté `14B078` cuando el despachador real es `14A6D0` (se detectó por los punteros del log).
- Propuse el `EftRay` como cuerpo: es un lente.
- Dije que la prueba por software descartaba el renderer: los descartes están en `gs_draw.c` (compartido), así que
  en general no lo descarta; en esta sesión igual dan 0.

## 8. Otros bugs tocados en la misma sesión (no B14)

- **Crash de sonido** (`20261106-234124`): `chunk/lookup` sin el tamaño del bloque del IOP; acotado con
  `iop_remain()`; `on_segv` con tope de pila. Backups `plat_snd_se.c.pre_crash`, `mem.c.pre_stackscan`.
- **Crash del retrato** (`20261107-000314`): `2A3C08` leía `0x4` con slot 0; rango+nulo y `2A4148` oculta el
  retrato. Backups `2A4148.c.pre_slotguard`, `2A3C08` (nuevo).
- **Crash del wrap** (`20261107-002717`): `so=0xFFFFFFFF` → `sesq+4GB`; fix `so <= srem-0x14`; `Port_IopAlloc`
  rechaza tamaños inválidos. Backup `plat_snd_se.c.pre_wrap`.
- **Guards de tabla de texto/efectos**: `2A3C68/2A3CC0/2A3D18/2A3D70`, escritor `2A78F0` (0..7), `gEftHitList`,
  `D_00387760`.
- **F10 RAM dump** (herramienta) con marca `RAMDUMP` en el fight.log.

## 9. Archivos y backups

- Docs: este informe; `staging/constructo_rayo.md` (constructo del rayo/corrección del lente);
  `staging/barrido_bugs_io_snd.md`, `staging/barrido_bugs_pagina_cero.md`.
- Código tocado para B14 (logs TEMP, **quitar al cerrar**): `port/eq/14B078.c` (log de filas, no se usa),
  `port/eq/1513D0.c` (T5/T10), `port/eq/1501C0.c` (T5C/T5S), `port/eq/195738.c` (BEAMMGR), `port/eq/195250.c`
  (CREATE), `port/eq/195538.c` (STOP), `port/full/gs/gs_core.c` (F10).
- Arreglo real de B14: `port/eq/129AE8.c` (NaN del VU0).
- Backups: `129AE8.c.pre_vu_div0`, `bt2.pre_vu_div0`; `14B078.c.pre_b14rows`, `1501C0.c.pre_b14log`,
  `1513D0.c.pre_b14log`, `195738.c.pre_b14mgr`, `195250.c.pre_b14create`, `195538.c.pre_b14stop`,
  `bt2.pre_b14rows`, `bt2.pre_b14scale`, `bt2.pre_b14mgr`, `bt2.pre_ramkey`.
- Binario instalado al escribir esto: md5 `5c6770f20efe6dfb2cc118a79af68398` (= `port/build/full/bt2full`).

## 10. Cómo reproducir y qué capturar

1. Pelear con **Piccolo** (izquierda) y **Tri+L2** (`acc AD`) para el rayo `tipo 12` del log `003926`:
   F10 durante el rayo.
2. Con **Goku** en el torneo (o el personaje del ataque de las 01:09) hacer el Kamehameha: F10 en el momento del
   estallido/bola (los `ramkey` de `010907` son de esto).
3. Si se quiere el *draw list*, hoy F9 no lo vuelca: hay que agregar un volcado de la lista (pendiente).

---

## Anexo: Hellzone Grenade (ulti de Piccolo sin capa, `acc B4`) — 2026-11-07 noche

- Ataque: `acc B4`, `pad Tri+L2`, `chr 01021102` (Piccolo fusionado con Kami, sin capa). En el log `013859`
  empieza en el frame **2920** y dura **59** cuadros (~1 s); el cartel es **"Hellzone Grenade"**.
- Crea un **shot** (clase `0x341A98`) vía `B10 SHOT-PIDE obj 0 slot 4 tipo 144 clase 0x341a98` (frame 2919).
  La task `0x1BDD040` (data `0x1BDD100`) sigue **viva 11 s después**; sus campos: dir al rival
  `(-0.94,0.02,-0.34)`, posiciones `(+0x40) 515,-15,116` y `(+0x50) 503,-15,119` (pegadas a Piccolo), contadores
  `+0x04 = 0x2D`, `+0x08 = 0x1F`, `+0x14 = 30.56`.
- `task[1] = 0x04` (**estado 4**); el update (`port/eq/1669B8.c`) en `case 4` espera
  `EftShot_TestBits(obj, 8)` para pasar a 5/kill. Si ese bit no llega, la bola queda para siempre.
- `EftShot_TestBits(obj, mask) = (EftTechEvt_GetEvents(obj) & mask) != 0`; los eventos están en
  `gEftTechEvt (0x387770) -> +4 + objId*0x10`. Log `B14 EVT` (instrumentado en `src/battle/eft_g_147D18.c`):
  durante/después del ataque los eventos toman **`0x2`, `0x4`, `0x10`, `0x14`** (¡el sistema de eventos funciona!)
  pero **nunca `0x8`** (ni `0x20`/`0x40`): el shot queda esperando el de fin. La palabra es 0 el resto del tiempo.
- Siguiente: ver quién debe poner el bit `8` (evento de animación del impacto/fin del movimiento o la detección
  de choque del proyectil) y por qué no aparece; el proyectil además no viaja (posiciones en Piccolo, no en el
  rival, aunque la dirección sí apunta al rival).
- Herramienta: log TEMP `B14 EVT` en `src/battle/eft_g_147D18.c` (backup `eft_g_147D18.c.pre_evtlog`).

### Anexo 2: máquina de estados del shot (logs `B14 SHOT` / `B14 EVTCH`, sesión `20261111-110846`)

- Ataque `acc B4` en el frame 3693 (59 cuadros). Shot creado en 3692 (`B10 SHOT-PIDE`, clase `0x341A98`).
- Log `B14 SHOT` (en cada cambio de estado, desde `port/eq/1669B8.c`):
  - f3692 `st 0  flags 00000000 done 0 adv 0 r 0 b2 0 b4 0 b8 0 b80 0`
  - f3731 `st 1  flags 00000080 done 0 adv 0 r 1 b2 1 b4 0 b8 0 b80 0`  ← ve el bit 2
  - f3732 `st 2  flags 00000080 done 0 adv 1 r 1 b2 0 b4 0 b8 0 b80 0`
  - f3776 `st 3  flags 00000483 done 0 adv 0 r 1 b2 0 b4 1 b8 0 b80 0`  ← ve el bit 4; el mismo frame hay
    `B10 BLAST-CREA` (impacto).
- La máquina (0→1→2→3) llega al impacto con `flags = 0x483` (incluye `0x400` = impacto), pero **no mata**:
  `if (done == 0 && r == 0) { if (flags & 2) SetDead; }` y `r = func_00152200(other, ev) != 0` da **1**.
- El estado 4 (el que espera el bit `8` para pasar a 5) **no se alcanza**: el `task[1]++` se hace después del
  switch y la tarea no vuelve a actualizarse (el `flags & 1` del frame 3776 la deja terminada). Ninguna función
  escribe `task[1] = 4` (grep en `port/eq` y `src/battle`: sólo 0/1/2/3/5).
- Eventos (`B14 EVTCH`, cada cambio): llegan `0x2`, `0x4`, `0x10`, `0x14`, `0x20`, `0x24`, `0x40` y **`0x8`**
  (frames 3090 y 3820); el bit **`0x80` (fin) nunca aparece**.
- Siguiente: `func_00152200(other, ev)` (por qué `r=1`) y la condición `done == 0` (`func_00166580`), que son
  las dos que permiten el kill; y por qué no se ejecuta el update del estado 3→4 en el frame siguiente.
- Logs TEMP: `B14 EVTCH` (`src/battle/eft_g_147D18.c`, backup `eft_g_147D18.c.pre_evtlog`),
  `B14 SHOT` (`port/eq/1669B8.c`).

### Anexo 3: lo que se ve en el video del F10 (sesión `20261111-111320`, Hellzone Grenade)

- **100.0 s** (durante): Piccolo en pose de carga a la derecha, con un **glow amarillo-blanco difuso pegado a las manos**
  (bbox x[558–681], y[384–559]); Goku idle al fondo a la izquierda; cuadro entero oscurecido (luminancia media ~47).
- **101.8 s** (F10, 2 s después): Piccolo en pose de "terminado", el glow **sigue en su mano izquierda** (más grande y
  difuso, bbox x[516–715], y[354–611]); HUD normal; aparece el radar.
- **103.0 s**: la bola es ahora una **esfera compacta con núcleo duro** (bbox x[251–327], y[375–456]) **junto a Goku**
  (viajó ~330 px en pantalla); Goku **sigue en idle y sin daño** (barras idénticas en las tres capturas); la bola
  **no se apaga**.
- Extra raro: **franja oscura con borde recto** sobre el pasto (y≈730 en 101.8, y≈500 en 103.0) — parece que el
  oscurecimiento de la ultimate no terminó de irse.
- Conclusión visual: el proyectil **sí viaja**, pero **no impacta** (ni daño ni reacción del rival) y **no se apaga**;
  concuerda con el shot que llega a estado 4 y no ejecuta el fin (Anexo 2).

### Anexo 4: comparación del rayo port vs original (video del usuario, 2026-11-11)

Informe completo: `staging/B14_rayo_port_vs_orig.md`. Port `124353` (6.85 s) vs PCSX2 `124617` (9.57 s), 15 fps.

- **El cuerpo del rayo no aparece en ningún cuadro del port.** En el original es un cono/aguja amarillo con núcleo
  blanco que sale de las manos (~760,372) hacia la izquierda hasta x≈450→430 (~330 px) y se **afina** con el tiempo
  (26 px de alto a los 2.07 s → 15 → 7 → 1-3 px a los 3.53 s). Dura **2.13→3.53 s**. En el port, entre la bola
  (x≈795) y x≈650 no hay nada (0 píxeles con umbral de luminancia).
- **El "layer adicional" es la hélice/resorte** (alambre amarillo, 3-4 vueltas de ~25 px) que en el original envuelve
  la **punta** del rayo. En el port **sí se dibuja y en la punta correcta** (≈330 px a la izquierda de la bola), pero
  **desconectada**: crece a ~200x180 px, se achica, queda quieta y **sobrevive al ataque** derivando hasta 4.13 s
  (en el original muere con el rayo en 3.73).
- **El port no tiene fase de disparo**: después del flash vuelve a la apariencia de carga (bola + anillos + hélice
  suelta) durante 1 s, con el personaje ya en pose de disparo.
- **Falta la cuña blanca del disparo** (original 1.87-2.07 s); el port sólo tiene una banda horizontal en 1 cuadro.
- Ritmo: el ataque empieza/termina casi igual (rótulo 0.93 vs 0.87 s; fin 3.73 vs 3.73 s), pero el port **estira la
  carga 0.65 s** (flash 2.53 en vez de 1.87).
