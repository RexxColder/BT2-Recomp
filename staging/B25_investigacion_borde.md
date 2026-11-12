# B25 — Borde norte del mapa del mundo: investigación del "-300" y opciones de niebla/fade

Fecha: 2026-11-11. Solo lectura: no se compiló, no se ejecutó el juego y no se tocó ningún archivo fuera de
`staging/`. Todo lo que sigue se puede reproducir con los comandos del anexo.

## 0. Resumen para el orquestador (leer esto primero)

1. **La pista del "-300" está mal atribuida.** El `-300` exacto que el agente anterior midió en
   `0x11BA340 + 0x140` **no es la posición del jugador: es una partícula del sistema de clima** (lluvia/nieve) y el
   salto es el *wrap* de esa partícula alrededor de una caja de 300×300×300 unidades.
2. `func_00145A58` **solo tiene 6 llamadas en todo el binario** (original y port, las mismas), y las tres funciones
   llamadoras son del sistema de efectos/clima (`func_00145DF0`, `func_001471C8`, `func_00147508`). No hay ningún
   puntero a función a `func_00145A58`, así que no existe otro camino.
3. Prueba numérica exacta: en el volcado de RAM de PS2 `tools/sesion_2026-11-06/zeni/ram.bin`, el pool de clima
   (`D_00387758`) está en `0x11AC700`; `0x11BA340` cae **exactamente** en el registro 369 de la segunda lista
   (`0x11AC700 + 0x8000 + 369*0x40`) y la dirección vigilada `0x11BA488` es el **z del registro 374**
   (`0x11BA480 + 8`; `0x11AC700 + 0x8000 + 374*0x40`). Los dos registros apuntan (`+0x30`) a `0x00E226C0`, cuyo
   `+0x10` es `(300,300,300)`. El wrap de `func_001471C8` resta/suma ese `full` → **exactamente ±300**.
4. **No pudimos identificar el código real del teleport del borde.** No quedan logs ni el script `borde.sh` /
   `borde4-*.log` (borrados en la limpieza), así que no hay medición del port del mapa para el frame del salto.
   Lo que sí sabemos (inferencia): el mapa 3D corre por el loop de "batalla" y el jugador es un `BtlChar`, cuya
   posición es `chr+0x510` (el `fight.log` ya la imprime). **Ese** es el dato que hay que medir, no `0x11BA488`.
5. El port **no implementa** FOG/FOGCOL/FGE del GS (`gs_core.c:826-858` no decodifica `0x0A`/`0x3D`; el byte F de
   XYZF2/XYZF3 se descarta en `gs_core.c:834/839`; `gs.frag`/`gs.vert` no tienen atributo de niebla). Para tapar el
   salto el enganche más barato y aislado es **el pase de present** (`gs_gl.c:308-323` y su gemelo Vulkan), teñiendo
   la imagen presentada; se dispara desde un hook de puerto (por vblank), sin tocar el código del juego.

Confianza: **alta** en (1)-(3) y (5); **baja/abierta** en el punto (4).

---

## 1. Cadena de código del `-300` (evidencia dura)

### 1.1 Qué hace `func_00145A58`

`port/eq/145A58.c:4-18` (C equivalente) y asm `disc/SLUS_214.41` `0x145A58`:

```
  145a58: d8a10000  lqc2    $vf1,0(a1)
  145a5c: d8c20000  lqc2    $vf2,0(a2)
  145a60: 4bc20868  vadd.xyz $vf1xyz,$vf1xyz,$vf2xyz
  ...
  145a74: 03e00008  jr      ra
  145a78: f8810000  sqc2    $vf1,0(a0)      <- única escritura
```

Es un `vadd.xyz` puro (suma xyz, conserva W). El C es fiel: copia 4 floats de `a1`, suma 3 de `a2`, escribe 4.
**No hay bug de traducción acá.**

### 1.2 Los únicos llamadores

Búsqueda del `jal 0x145A58` (encoding `0x0C051696`) en todo el `.text` del ELF y en el binario del port:

| sitio (ELF) | función original | C del port | línea |
|---|---|---|---|
| `0x1461E8` | `func_00145DF0` (efectos de clima, emisor) | `port/eq/145DF0.c` | 150 |
| `0x147328` | `func_001471C8` (update de lluvia) | `port/eq/1471C8.c` | 73 |
| `0x14733C` | idem | idem | 74 |
| `0x147378` | idem | idem | 87 |
| `0x1474B4` | idem (wrap por registro) | idem | 112 |
| `0x1475FC` | `func_00147508` (wrap de partículas ±500) | `port/eq/147508.c` | 38 |

Verificado además en el **binario del port** (`BT2-test/bin/bt2`, `objdump`): los 6 `call 0x40196000` caen en
`func_00145DF0`, `func_001471C8` (×4) y `func_00147508` (`addr2line`). Y no hay referencias a la dirección
`0x40196000` como dato (solo `.dynsym`, `.eh_frame` y `.debug_info`), es decir **no se llama por puntero**.

Dato extra: los punteros a `func_00146648`, `func_001471C8`, `func_00146D78`, `func_00147620`, `func_00148260`…
viven en una **tabla de funciones de efectos en `0x3401F8`-`0x340234`** (`.data`). Por eso `func_001471C8` (el update
de lluvia) no tiene ningún `jal` directo: se despacha por tipo desde el sistema de efectos. No se ubicó el
despachador en el C (queda como pendiente menor; no cambia la conclusión).

### 1.3 De dónde sale el `-300` exacto

`port/eq/1471C8.c` (asm `0x1471C8`–`0x1474F0`, comparado línea por línea: el C está bien):

- `D_00387758` es el pool de clima, asignado en `port/eq/146D78.c:49-51`
  (`func_0028BAA8(0x2C220)`; `0x8000` + 2304·0x40 = `0x2C000`, más `0x220` de cola).
- Primera lista: **512** registros de 0x40 en `D_00387758` (líneas 51-77) → jitter + viento con `func_00145A58`.
- Segunda lista: **2304** registros desde `D_00387758 + 0x8000` (línea 79), con:
  - `cam = *(u8 **)(rec + 0x30)` — **el "centro" de la caja lo lleva cada registro**
  - `half = cam+0x10 * 0.5f`, `full = cam+0x10 * 1.0f` (líneas 97-99)
  - wrap: `if (half[2] < rel[2]) rel[2] -= full[2]; if (rel[2] < -half[2]) rel[2] += full[2];` (101-110)
  - `func_00145A58(rec, rel, cam)` (línea 112) → `rec = rel + cam`.
- Asm del wrap: `0x147440`-`0x1474B8` (mismas comparaciones y `add.s`/`sub.s` con `sp+0x30`/`sp+0x38`).
  **Coincide con el C: el port reproduce el original.**

Entonces el salto vale **`full` = `cam+0x10`**, y en los datos del juego eso es **300.0** exactos.

### 1.4 La prueba con el volcado de RAM de PS2

`tools/sesion_2026-11-06/zeni/ram.bin` (32.505.856 bytes = PS2 `0x100000`..`0x2000000`; **el offset de archivo es
la dirección PS2 − 0x100000**, verificado contra el `.text` del ELF y contra `DBZP.BIN` cargado en `0x3B3100`):

```
D_00387758 (PS2 0x387758) = 0x011AC700
registro 369 (0x011BA340): (0x11BA340-(0x11AC700+0x8000))/0x40 = 369
registro 374 (0x011BA480): (0x11BA480-(0x11AC700+0x8000))/0x40 = 374   <- el z vigilado es 0x11BA488
registro +0x28 (activo)  = 1        (en los dos)
registro +0x30 (cam)     = 0x00E226C0   (en los dos)
0x00E226C0 + 0x10        = (300.000, 300.000, 300.000, 0.0)
registro 369 pos         = (-1466.72, -28.77, -1308.94, 1.0)
registro 374 pos         = (-1484.85, -30.19, -1326.19, 1.0)   <- z = 0x11BA488
cam pos                  = (-1586.75, 0.0, -1325.14)           ; cam box = 300³
```

Es decir: la dirección que se vigiló (`0x11BA488` = `0x11BA480+8`) es **el Z del registro 374 del pool de clima**, y
el valor que salta ±300 es el wrap de `func_001471C8`. Los registros vecinos (cada 0x40) tienen posiciones
repartidas alrededor del centro de la caja (`x ∈ 1448..1728`, `y ∈ -72..-20`, `z ∈ -1300..-1414`),
exactamente el patrón de partículas de lluvia/nieve.

Números: `0x11AC700 + 0x8000 = 0x11B4700`; `0x11BA340 − 0x11B4700 = 23616 = 369·64`;
`0x11BA480 − 0x11B4700 = 23936 = 374·64`. No es aproximado: caen justo.

### 1.5 Por qué esto invalida la atribución anterior

- El único escritor posible de esa dirección es `func_00145A58`, y sus 3 llamadores hacen **solo** clima/efectos.
- `func_00145DF0` opera sobre emisores (`s3` = emisor), `func_001471C8` sobre el pool `D_00387758`,
  `func_00147508` envuelve un registro en una caja de ±500 (constante `0xc3fa` = −500 en el asm `0x147558`).
- El rango del volcado elegido (z ≈ −1300, x ≈ −1480) coincide con lo que veía el agente (`-1175 → -1475`), lo que
  explica el falso positivo: **la partícula acompaña a la cámara**, así que "se movía con el jugador".
- `dladdr` en `port/full/mem.c:103-113` resuelve por símbolo más cercano; `func_00145A58` mide `0xb6` y el siguiente
  símbolo (`func_00145A80`) está en `0x401960C0`, o sea que el store cayó **dentro** de la función (no es un símbolo
  vecino mal atribuido).

Riesgo residual (lo digo explícito): el volcado `zeni/ram.bin` está en **modo 7** ("duelo?"), no en el mapa. No
tenemos un volcado del mapa 3D. Pero el mecanismo (pool + caja de 300) es global al sistema de clima y el
llamador es el mismo en cualquier escena. **Lo que no está probado es que la sesión del `borde.sh` haya sido el
mapa**; sí está probado que el `-300` solo puede venir de `func_00145A58`.

---

## 2. Sistema de mundo / borde: qué sabemos y qué falta

### 2.1 Lo que se pudo verificar

- **El mapa no es un overlay aparte de los menús**: `func_001002D8` (asm `0x100340-0x100350`, `lui s2,0x3b` +
  `addiu a1,s2,0x3100`) carga el overlay de gameplay en **`0x3B3100`**, que es la misma base que usa el port
  (`port/tools/link_full.py:21`, `OVL_LO=0x3B3100`). El volcado `zeni/ram.bin` confirma `DBZP.BIN` cargado en
  `0x3B3100` (99,5 % de match; los primeros 0x1000 bytes están parcheados).
- **El modo del juego** (`gProgress = *(u32*)0x3876A4`, modo en `+0x1C`): `port/full/plat_fightlog.c:191-205` mapea
  `24..27` a "dragon_adventure?". La máquina de estados del menú de historia es `port/eq/3CB1D0.c:63-90`:
  `0x18`(24) → `func_003CD778`, `0x19`(25) → `func_003CABA8`, `0x1A`(26) → `func_003D09C0` (pelea de historia),
  `0x1B`(27) → `func_003CFAF8`. `0x18` es un loop de menú con globos de texto (`3CD778.c:36-60`), no el 3D.
- **El mapa 3D usa el loop de batalla** (inferencia fuerte, no medida en el mapa): el HUD del mapa (zeni, esferas,
  *map points*) es `func_00259740` (`port/eq/259740.c:2-3`; B24 lo confirmó con datos) y se llama desde
  `func_002ABF30` (`port/eq/2ABF30.c:112`), que es el frame de batalla (`BtlStage_IsReady`,
  `BtlScene_DrawFrame`, cámara), y `func_00259740` no tiene otro llamador en el C. Es decir: el mapa correría como
  una escena de batalla con un `BtlChar`.
- **La posición del jugador en ese mundo es `chr + 0x510`** (`port/full/plat_fightlog.c:12-16` +
  `src/auto/auto_2112c8.c`): `chr(i) = **(u32 **)D_00387930 + i*0x1550`, `pos = chr+0x510` (`x,y,z` en
  `+0..+8`, yaw en `+0xB4`). El `fight.log` ya la imprime en la columna `pos`.
- **El mapa 2D (pantalla de selección, no el 3D)** está en el overlay: `port/eq/419820.c:26` ("map screen layout",
  nombre de mapa, BGM, 7 iconos `mc_mappoint_*`), con loop/fade en `41A5D8.c:52-70` y modo `0x22` en
  `41A5D8.c:91/111`. Es el "mapa del mundo" de menú; **no** es donde vuela el personaje.

### 2.2 Lo que NO pudimos identificar

- **Quién reubica al jugador al cruzar el borde.** No hay un salto `if (z < min) z += size` localizado en el C del
  port para la escena del mapa. Candidatos no verificados: script de escena (GSC), `Stg*`/`BtlStage`, o el propio
  controlador del `BtlChar`. **No lo afirmo**: sin un volcado del mapa no se puede distinguir.
- Cuántas zonas hay y cómo se pasa de una a otra. El mapa parece un planeta chico (las capturas muestran la
  curvatura y etiquetas "Northern Capital"/"Beter"/"West City"), pero no hay evidencia en el código del repo.

### 2.3 Cómo encontrarlo (concreto, para el próximo agente)

1. En el port, entrar al mapa (Dragon Adventure) con `BT2_FIGHTLOG=1` (ya activo con `jugar.sh`) y caminar al norte.
   El `fight.log` imprime `pos x y z` de los dos primeros `chr`. **Si el jugador salta −300, se ve ahí**, y ese es
   el frame exacto. Si no salta, el `-300` era 100 % ruido de clima.
2. Con la dirección real `chr+0x518` (se calcula de `D_00387930` → `*(u32*)` → `+ i*0x1550 + 0x510 + 8`), armar
   `BT2_WATCH_F32=<addr>,150` + `BT2_WATCH_FROM=<vblank-1>` (herramienta en `port/full/mem.c:81-135`,
   armado en `port/full/plat_gs.c:85-95`). El log dice la función que escribió.
3. Cruzar ese resultado con el C (`port/eq`/`src`) y recién ahí decidir si el salto es fiel al original (probable:
   el usuario dice que la PS2 también "lupea") o un error de traducción.
4. Recién entonces poner el log `TEMP B25` de INICIO/FIN en la función real (formato sugerido:
   `B25 BORDE inicio frame=%u modo=%d pos=(%.1f,%.1f,%.1f)`, y el de fin con el delta y la duración).

---

## 3. Niebla / fade: estado del renderer y opciones

### 3.1 Lo que hay hoy (verificado)

- **No hay niebla del GS**:
  - `port/full/gs/gs_core.c:826-858` (`reg_write`) **no tiene** `case 0x0A` (FOG) ni `case 0x3D` (FOGCOL).
  - `gs_core.c:834` (XYZF2) y `:839` (XYZF3) enmascaran a 24 bits → **el byte F se descarta**.
  - `gs_core.c:817-819` (`prim_update`) copia PRIM/PRMODE pero nadie usa el bit FGE (5).
  - Camino de vértices: `gs_core.c:571-573` guarda `x,y,z`, color y STQ; no hay F.
  - GPU: `port/full/gs/shaders/gs.vert:4-8` (atributos `inPos/inColor/inStq`, sin F) y
    `port/full/gs/shaders/gs.frag` (113 líneas, sin `mix` de niebla).
  - Software: `gs_core.c:359` (`pixel`) calcula test/alpha/blend/FBMSK; no hay término de niebla.
- **Lo que sí hay** es la *niebla por profundidad del juego* (`GfxDepthFog_*`: `src/sys/gfxm_b_281758.c:266-279`,
  `src/auto/perm_285A18.c`) que se resuelve como un pase de tabla nativo (`gs_draw.c:74`, `:437-465`, `:503-505`,
  `dclut.frag`). Es el "fog" de los escenarios de pelea; **no se encontró la llamada para el mapa** (el PLAN lo
  dejaba pendiente y sigue pendiente).
- **Fade del juego disponible y funcionando**: `gColorFade` (`estado +0`, RGB `+4/+8/+0xC`, alpha `+0x10`, paso
  `+0x14`) con `func_00243968` / `func_002439E8` / `func_00243A80` (arrancar) y `func_002437E8` (dibujar un quad
  full-screen por `Dma_BeginDirect`), `func_002438E8` (avanzar). Ver `port/eq/243968.c`, `2439E8.c`, `243A80.c`,
  `2437E8.c`, `2438E8.c`. Este fade ya se renderiza bien en el port (es un primitivo GS normal).

### 3.2 Opciones (con punto de enganche)

**Opción 1 — Niebla GS real (FOG/FOGCOL/FGE).** Correcta y general, pero grande y **no sabemos si el mapa la usa**.
Puntos: `gs_core.c:826-858` (guardar `0x0A`/`0x3D` y el F de `0x04`/`0x0C`), `gs_core.c:571-573` + `Vtx`
(`gs_draw.h:32-36`) + `gs.vert/gs.frag` + `dclut/renderer` + `pixel()`. Además toca los 4 archivos que se están
editando por otros bugs. **No la recomiendo como primer paso.**

**Opción 2 — Arreglar el pase de horizonte que el juego ya manda.** Es lo que explica las rayas/banda gris de
`staging/b25_niebla/PLAN.md` y probablemente comparte causa con B21. Requiere un volcado F9 del mapa con
`BT3_GS_VERBOSE` (hoy no existe) y comparar TBP/TBW/PSM del pase de profundidad. **Sin datos, no se puede
avanzar.**

**Opción 3 — Fade/niebla solo en el port (lo que decidió el usuario).** La más barata y aislada: teñir la imagen
**presentada**. No toca el GS ni el código del juego, y sirve aunque el pase del juego esté mal.

- Punto de enganche elegido: **el pase de present**.
  - OpenGL: `port/full/gs/gs_gl.c:305-330` (shader inline del present) y `gs_gl.c:1090-1115` (draw del present,
    justo antes de `SDL_GL_SwapWindow` en `:1149`).
  - Vulkan: `port/full/gs/gs_gpu.c` (mismo pase de present; hay que replicarlo para paridad, igual que se hizo con
    el resto de los efectos).
- Disparador (hook de puerto, sin tocar el juego): un módulo nuevo, p. ej. `port/full/plat_worldfade.c`, llamado
  desde `Port_VBlank` (`port/full/plat_gs.c:84`, al lado del arming del watchpoint B25). Cada vblank:
  1. lee modo (`*(u32*)0x3876A4 + 0x1C`) y solo actúa en 24..27;
  2. lee la posición real del jugador (`chr0+0x510`, mismo cálculo que `plat_fightlog.c:106`);
  3. si `|Δz|` o `|Δxy|` > umbral (p. ej. 100 en un vblank) → arranca el fade (alpha 0→255 en ~4 frames, espera 8,
     255→0 en ~10) con el color de cielo/niebla;
  4. expone `gPortFadeR/G/B/A` que leen los backends de present.
- Variante "más niebla que flash": en el present, aplicar el tinte con peso por altura de pantalla
  (`(1.0 - vUv.y)`) → tapa el horizonte y deja el piso limpio. Es un cambio de 2 líneas en el fragment.

**Diff propuesto (NO aplicado)** — OpenGL present (Vulkan es el mismo cambio):

```diff
--- a/port/full/gs/gs_gl.c
+++ b/port/full/gs/gs_gl.c
@@ -308,3 +308,5 @@ make_present_program
-    static const char *fs = "#version 330 core\nin vec2 vUv;\nout vec4 o;\nuniform sampler2D tex;\nuniform vec2 uvScale;\n"
-        "void main() { o = texture(tex, vUv * uvScale); }\n";
+    /* B25 (solo port): tinte de niebla/fade sobre la imagen presentada. 0 en todos los modos menos el mapa. */
+    static const char *fs = "#version 330 core\nin vec2 vUv;\nout vec4 o;\nuniform sampler2D tex;\nuniform vec2 uvScale;\n"
+        "uniform vec4 fade;\n"
+        "void main() { vec4 c = texture(tex, vUv * uvScale);\n"
+        "             float w = fade.a * (1.0 - vUv.y);\n"      /* horizonte arriba, piso abajo */
+        "             o = vec4(mix(c.rgb, fade.rgb, w), c.a); }\n";
...
     glUniform2f(glGetUniformLocation(p, "uvScale"), 512.0f / (float)GS_W, 448.0f / (float)GS_H);
+    sFadeLoc = glGetUniformLocation(p, "fade");
+    glUniform4f(sFadeLoc, 0.55f, 0.72f, 1.0f, 0.0f);
     return p;
@@ present del frame (gs_gl.c:1090-1115)
             glUseProgram(sPresentProg);
+            glUniform4f(sFadeLoc, gPortFadeR, gPortFadeG, gPortFadeB, gPortFadeA);
             glBindVertexArray(sVaoGs);
```

```diff
--- a/port/full/plat_gs.c
+++ b/port/full/plat_gs.c
@@ void Port_VBlank(void) {
+    { extern void Port_WorldFade_Frame(void); Port_WorldFade_Frame(); }   /* B25: niebla/fade del borde (solo port) */
     static int paced = -1;
```

y el módulo `port/full/plat_worldfade.c` (nuevo, ~60 líneas) con `gPortFadeR/G/B/A` + `Port_WorldFade_Frame()`.
**No lo aplico**: falta (a) confirmar que el mapa tiene `chr0+0x510` válido, (b) medir el salto real, (c) elegir el
color/duración mirando el original.

**Sobre el "límite de dibujado" (far clip)**: no lo propongo como parche del renderer. El GS no tiene far clip; en el
original lo hace el juego (o la niebla). Un `discard` por Z en `gs.frag` afectaría también HUD y partículas y no es
fiel.

---

## 4. Datos del salto (lo que hay y lo que falta)

- **Del port, alrededor del salto**: no hay nada. `BT2-test/logs/vivo/borde4-*.log` no existe, `BT2-test/pruebas/`
  no existe y el script `borde.sh` también se borró. Los `fight.log` que quedan son de duelos/entrenamiento
  (modos 7 y 63); ninguno del mapa (24..27).
- **De PS2**: el volcado `zeni/ram.bin` (modo 7, con clima activo) es lo único con los números. De ahí salen:
  pool `0x11AC700`, registros 369/374 en `0x11BA340`/`0x11BA480`, caja `300³` en `0x00E226C0+0x10`, y el z
  vigilado `-1326.19` (registro 374).
- **El `-1175 → -1475`**: no se puede reconfirmar (log borrado). Es aritméticamente compatible con el wrap
  (`full.z = 300`), y **incompatible con que sea el jugador**, porque el único que escribe ahí es el clima.

---

## 5. Descartes (y por qué)

| Hipótesis | Estado | Motivo |
|---|---|---|
| "`func_00145A58` escribe la posición del jugador" | **Descartada** | 6 llamadas, todas clima/efectos; `0x11BA340` cae justo en el pool de clima y su `+0x30` apunta a la caja de 300³ |
| "Hay un llamador oculto (overlay/indirecto)" | **Descartada** | no hay `jal` a `0x145A58` fuera de los 6, ni punteros a la función en datos |
| "El C de `145A58` o de `1471C8` está mal traducido" | **Descartada** | C vs asm línea por línea: `vadd.xyz` y el wrap con `half/full` coinciden |
| "Falta la niebla FGE del GS" | **Confirmada como carencia**, no como causa del salto | no hay decode de `0x0A`/`0x3D`; pero no hay evidencia de que el mapa use FGE |
| "El horizonte del original es `GfxDepthFog`" | **Abierta** | el pase existe en `src/sys/gfxm_b_*`, pero no se encontró su llamada para el mapa |
| "El fade del juego (`ColorFade`) no sirve para el port" | **Descartada** | `gColorFade` + `2437E8` se dibujan por DMA directo y el port ya los renderiza |
| "`func_00276FD0` (`-300.0f`) es el salto" | **Descartada** | es un valor de cámara/zoom que va a `func_001014E8` (`0x2F52A8`); sus 17 llamadas están en el módulo `0x2770B0`-`0x277A78` (vista/menú), no en el controlador del jugador |

---

## 6. Próximos pasos sugeridos (en orden)

1. **Medir el jugador real** (1 h): mapa con `BT2_FIGHTLOG=1`, caminar al norte, mirar la columna `pos` del
   `fight.log`. Dos resultados posibles: (a) salta ±300 → watchpoint en `chr+0x518` y buscar la función;
   (b) no salta → el `-300` era solo clima y el bug es puramente visual (horizonte/niebla).
2. **F9 del mapa** (`jugar.sh`, F9 antes/después del borde) para tener por fin un volcado del mapa (hoy no existe) y
   poder diagnosticar las rayas/banda gris con `BT3_GS_VERBOSE`.
3. **Recién después** elegir: fade de present (opción 3, rápida y aislada) y/o arreglo del pase de horizonte
   (opción 2, fiel). La niebla GS (opción 1) dejarla para cuando se sepa que el juego la usa.
4. **Log `TEMP B25`**: no se puede escribir todavía; depende del paso 1. Cuando se sepa la función, loguear
   inicio/fin del salto con frame, modo y pos, en el código del juego (no en el port).

---

## Anexo: cómo se verificó (comandos, todos de solo lectura)

```sh
# llamadores en el ELF
python3 - <<'EOF'
import struct
d=open('disc/SLUS_214.41','rb').read(); t=0x145A58
pat=struct.pack('<I',0x0C000000|(t>>2)); i=0
while (j:=d.find(pat,i))>=0: print(hex(0x100000+j-0x1000)); i=j+1
EOF

# llamadores reales en el binario del port
objdump -d --no-show-raw-insn BT2-test/bin/bt2 | grep "call.*40196000"
addr2line -f -e BT2-test/bin/bt2 0x40196937 0x401977fa 0x40197808 0x40197909 0x40197931 0x40197b79

# volcado PS2 (offset de archivo = dirección PS2 - 0x100000)
python3 - <<'EOF'
import struct
ram=open('BT2-Recomp/tools/sesion_2026-11-06/zeni/ram.bin','rb').read()
u=lambda a: struct.unpack('<I',ram[a-0x100000:a-0x100000+4])[0]
pool=u(0x387758); rec=0x11BA340
print(hex(pool), (rec-(pool+0x8000))//0x40)           # 0x11ac700 369
cam=u(rec+0x34-4); print(hex(cam), struct.unpack('<3f',ram[cam+0x10-0x100000:cam+0x10-0x100000+12]))
EOF
```

Notas de credibilidad: el volcado `zeni/ram.bin` NO es del mapa (modo 7), y las capturas de `borde/` son de una
sesión vieja; las conclusiones sobre el mapa 3D (sección 2.1) salen del C/asm y de la tabla del logger, no de una
medición del port. Todo lo que no tiene evidencia está marcado como abierto.
