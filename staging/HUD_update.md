# HUD de pelea: valores continuos escalonados (vida/ki/power level) — 2026-11-12

Investigación de solo lectura. Build en uso: `3392817f` (DATE cap 200, copia `native 5` por scissor,
`gsDateLiveAux = 0`, `BT2_FPS_MENU=65` / `BT2_FPS_FIGHT=45`, `Port_EnPelea()`).
Nada de esto se aplicó: no se editó código ni se compiló.

## Síntoma (refinado por el usuario)

La barra de ki, el contador de power level y la vida **sí** son dinámicos, pero se actualizan **solo en
eventos discretos**: al bajar una barra entera de vida, al subir un nivel de power level o al completar una
barra de ki. Los valores continuos quedaron escalonados. El usuario propone restaurar el cap DATE a 600
(`BT2_DATE_CAP=600`) y relanzó con `BT2_FPS_MENU=65 BT2_FPS_FIGHT=45`.

## 1. Separar estado de dibujo — el ESTADO ES CONTINUO (evidencia dura)

Volcados de RAM del F9 (`BT2_F9_RAM`) de una pelea, 4 dumps 2 cuadros aparte
(`BT2-test/logs/vivo/20261112-001002_ram{1..4}_f393{0,2,4,6}.bin`, 32 MB = toda la RAM de PS2;
la sesión entra en BATALLA en el vblank 1295 y sigue así hasta el 4437).

Leído en los dumps: `chr(i) = **(u32 **)0x387930 + i*0x1550`, gauge del miembro activo en `chr + 0x11C8`
(`health`, `healthMax`, `ki`, `kiMax = 100000`, `maxPower`, unidades de
`include/battle/btl_char_member.h:41-50`: **10000 = una barra**):

```
f3930  chr0 hp=31070/50000 ki=52413  kmax=100000 | chr1 hp=20850/30000 ki=23260
f3932  chr0 hp=31070/50000 ki=52413  kmax=100000 | chr1 hp=20850/30000 ki=23496
f3934  chr0 hp=31070/50000 ki=52413  kmax=100000 | chr1 hp=20850/30000 ki=23732
f3936  chr0 hp=31070/50000 ki=52413  kmax=100000 | chr1 hp=20850/30000 ki=23968
```

`chr1.ki` sube **exactamente 118 por cuadro** (236 cada 2 cuadros) durante los 4 volcados. O sea: el ki se
actualiza de forma continua en el estado del juego (45 Hz), no por barra. Lo mismo vale para la posición /
animación que registra el `.fight.log` (`anim frame` avanza `paso 2.000` en cada vblank).

Y el **work del HUD** también guarda la fracción exacta, no un conteo de barras. Bloque del gauge encontrado
en el mismo dump (`0x017EAE8C`, sesión del 2026-11-12 00:10):

```
017eae8c  float 0.6214   = 31070 / 50000   (health/hpMax del chr0, exacto)
017eae90  float 0.52413  = 52413 / 100000  (ki/kiMax del chr0, exacto)
017eae74  100000                          (kiMax)
```

`0.6214` y `0.52413` no son múltiplos de barra: el HUD recibe el valor continuo. **El bug no está en el
estado del juego ni en el valor que se le pasa al HUD; está en el camino de dibujo (o en si el HUD reescribe
su máscara de alfa cada cuadro).**

Falta (no lo pude probar sin correr): que la *fracción dibujada* (rect del sprite) avance 1 px por frame.
El work tiene la fracción; el rect se arma en `HudSprite_SetRect` con las esquinas del nodo.

## 2. Mapa del camino del HUD

Juego (BT2):
- `Hud_Draw` toma el árbol de nodos (`gHud`, 7 partes: gauges, timer, team panel, notices, combo, prompt,
  caption; `include/battle/hud_a.h:79-99`) y dibuja los sprites con VU0 como tiras de 4 vértices.
- Parte gauge (vida/ki/power): `include/battle/hud_b.h` (rango 0x21CA60-0x222400), **sin C propio**: la sirve
  el recompilado (`port/build/recomp/func_0021*.cpp`), es traducción instrucción-a-instrucción, fiel.
- Setters: `HudGauge_SetHp/SetKi/SetMaxPower` (`include/battle/hud_b.h:50-55`). Unidades 10000/barra.
- C del HUD que sí existe: `src/battle/xa_114328.c` y `port/eq/10B*.c` (librería de sprites: `HudGfx_SetEnv`,
  `HudSprite_DrawAlphaClear/Set`, `HudGfx_ClearAlpha`, máscaras GS), `src/battle/xa_10BF38.c` (team panel),
  `src/battle/hud_d_b_10B938.c` (anuncios), `port/eq/10C060/10C170/10C298/10C4E0/10C770/10C868/10CA68/10CBE0.c`
  (paquetes GS del HUD).
- **El HUD usa DATE**: `HudTeam_GsBeginMask` escribe `TEST_1 = 0x34000` (DATE=1, DATM=0) y
  `FRAME_2` con `FBMSK 0x00FFFFFF` + FBA (solo alfa) antes de cada sprite enmascarado; el barrido de valor se
  hace con `HudSprite_DrawAlphaClear` (alfa 0) / `DrawAlphaSet` (alfa 0xFF) y `HudGfx_ClearAlpha` limpia el
  alfa de todo el cuadro en 16 tiras. La barra se dibuja con DATE contra ese alfa.
- Doble buffer: todo el HUD elige el buffer por paridad de cuadro (`Gfx.frame & 1`, `D_003B0A84` =
  `gGfx.frame`; `include/sys/gfx.h:99-102`); `BtlGame_Draw` dibuja el HUD después del 3D.

Renderer:
- Cada primitiva con TEST.DATE llama `date_snapshot()` (`port/full/gs/gs_draw.c:734`), que inserta una
  copia `native 5` con el scissor de esa primitiva, hasta `sDateCap` por target por cuadro
  (`gs_draw.c:740`, `756`, `775-790`). Pasado el cap hace **una** copia full-frame y el resto la reusa
  (`gs_draw.c:782-789`) — ahí el alfa que lee el HUD queda congelado en ese punto del cuadro.
- GL: `glCopyImageSubData` para la copia parcial (`gs_gl.c:1045-1060`), contador `blit5` en `GLTIME`
  (`gs_gl.c:1363`).
- Texturas: `texture_get()` identifica el contenido con **hash de las páginas** (`Gs_PageHash`,
  `gs_draw.c:151-156`) + hash de paleta; cada upload sube `gGsPageGen` de todas las páginas que puede tocar
  (`gs_core.c:807-813`). El HUD re-sube a `0x3000..0x30C0` **todos los cuadros** (uplog: 39.313 líneas a
  `0x3000` en una sesión de 5.200 cuadros; ~14/cuadro, desde el cuadro 26 hasta el final de la pelea).
- Ritmo: `Port_VBlank` duerme un período por vblank (`port/full/plat_gs.c:88-105`); pelea 45 / menú 65.
- `Port_EnPelea()` (`port/full/plat_fightlog.c:64`) elige el período; el `.fight.log` demuestra 1 vblank por
  cuadro de juego en pelea.

## 3. Evidencia sobre la hipótesis DATE

Números reales de `GLTIME` (`blit5` = copias DATE del cuadro):

| sesión | build | cuadros de pelea muestreados | `blit5` |
|---|---|---|---|
| `20261112-015417` | cap 200 | 1620..2400 | 201 en 20 muestras (cap tocado: 200+1) |
| `20261112-013211` | sin cap (o >1214) | 1560..6780 | 151..**1214** (mediana 312) |
| `20261112-020202` | **cap 600** | 2100..5280 (54 muestras) | 163..**504** (ninguna ≥ 600) |

Conclusiones:
- Una pelea real hace **150-1200+** primitivas DATE por cuadro, no 200. El cap 200 **se toca siempre**; el
  600 **no se tocó en las 54 muestras** de la sesión nueva (`20261112-020202`, pelea con 22 `IMPACTO`,
  BATALLA desde el vblank 1910). Por lo tanto, si el HUD sigue escalonado con 600, el cap no es la causa en
  esos cuadros.
- Ojo 1: `GLTIME` se imprime cada 60 cuadros; una pelea pesada llegó a 1214 copias. **600 puede seguir
  cortando en cuadros no muestreados**: el experimento no es concluyente al 100 % sin contar por cuadro.
- Ojo 2 (**trampa de la prueba anterior**): `BT2_DATE_CAP=0` **no desactiva el cap**, cae al default 200
  (`gs_draw.c:740`: `e && atoi(e) > 0 ? atoi(e) : 200`). Si se probó "cap 0" creyendo que lo apagaba, en
  realidad se probó 200 otra vez.
- Costo medido de **no** poner cap: `blit 1215/0.7 ms` en el cuadro más pesado (f=5640), y 505 copias a
  `0.0 ms` en la sesión 600. Con `glCopyImageSubData` el cap ya no se justifica por costo.

## 4. Hipótesis revisadas y descartes

(a) **HUD atado a 60 Hz / a 45 se congela o salta** — DESCARTADA como causa del escalonado: el `.fight.log`
    muestra 1 cuadro de juego por vblank (anim avanza en cada vblank) y el ritmo es exacto; no hay saltos de
    vblank en pelea. (El FPS de pelea lo cubre el otro agente.)

(b) **Textura/página del HUD cacheada y no invalidada** — DESCARTADA con evidencia: las páginas del HUD se
    re-suben todos los cuadros (uplog 0x3000/0x3080/0x3041/0x3050…) y el caché se indexa por **hash de
    contenido** de las páginas + paleta (`gs_draw.c:151-156`), no por dirección. Además las hojas del HUD son
    arte estático idéntico todos los cuadros: si el valor continuo viviera en la textura, el hash cambiaría.
    Tampoco hay copias GS→GS (`trxdir=2`): en todos los logs el 100 % de los uploads son `dir 0`.
    Lo único no verificado: que el juego no escriba el valor en VRAM por un camino que no bumpee `gGsPageGen`
    (p. ej. sprite a `FRAME.FBW == 1`); no hay ninguna evidencia de eso en los logs.

(c) **El DATE dejó el alfa/color viejo** — SIGUE VIVA, pero **no como "un cuadro de atraso"**. Si el juego
    reescribe la máscara de alfa del gauge **solo cuando el valor cambia de barra** (para ahorrar ancho de
    banda), con el cap tocado la copia se toma *antes* de esas escrituras y el HUD lee el alfa que quedó del
    **último evento** → escalonado por barra, exactamente el síntoma. Si en cambio el juego reescribe el alfa
    todos los cuadros, el atraso sería de 1 cuadro y se vería continuo. La corrida con 600 discrimina esto:
    en la sesión `20261112-020202` las 54 muestras no tocaron el cap (máx. 504).

(d) **Una función C del HUD no actualiza el estado** — DESCARTADA para el valor: el work del HUD tiene la
    fracción exacta (`0.6214`, `0.52413`) y el estado del juego es continuo (ki +118/cuadro). La parte gauge
    es recompilado fiel, y no hay C propio de `HudGauge_*`. Queda abierta la posibilidad de que el *rect* del
    sprite se arme mal (esa parte es recompilado, no C: sin evidencia de error).

(e) **Widescreen/2D** — DESCARTADA: afecta geometría global, no el escalonado por unidad de barra.

## 5. Experimento mínimo para decidir (sin aplicarlo)

Corrida A (decide DATE, la que ya está lanzada pero con un valor útil):
```
BT2_DATE_CAP=2000 BT2_FPS_MENU=65 BT2_FPS_FIGHT=45 BT2_GLTIME=1
```
`2000 > 1214` (máximo histórico) ⇒ ninguna copia se trunca en ningún cuadro. Con `BT2_DATE_CAP=0` **no**
sirve (0 = 200). Si con 2000 el HUD queda continuo → es DATE/cap; si sigue escalonado → es otra cosa.

Corrida B (cuenta por cuadro, 6 líneas TEMP, sin tocar el renderer):
en `date_snapshot()` loguear una vez por cuadro `sDateSnaps[target]` máximo y `sDateFull[target]`
(`fprintf(stderr, "DATE f=%u target=%d snaps=%u full=%d\n", ...)` en el reset de `gs_draw.c:751`), para
saber si el cap se toca en cuadros no muestreados y en qué target (el HUD va a `0x00/0x70`).

Corrida C (decide si el valor continuo llega al *draw*): F9-RAM durante la pelea (`BT2_F9_RAM`) y, con los
dumps, leer `0x017EAE8C/0x017EAE90` (fracción de vida/ki del HUD; la dirección del heap es estable en este
camino) y compararla con el rect del sprite. Si la fracción avanza y el rect no, el problema está en el
armado del rect / máscara, no en el valor.

Corrida D (si hace falta el emisor): `BT2_WATCH_F32=0x17eae8c,0.00001` (herramienta `port/full/mem.c:85`)
loguea cada escritura a la fracción de vida con la función (dladdr) y el vblank. Si el juego la escribe todos
los cuadros, el alfa/máscara debería refrescarse igual; si solo aparece en eventos, refuerza (c).

## 6. Fix propuesto (NO aplicado)

Si la corrida con 2000/600 arregla: el problema es el cap, y el arreglo no es "600" sino **no truncar cuando
la copia es barata** (0.7 ms para 1215 copias con `glCopyImageSubData`), y arreglar la semántica de
`BT2_DATE_CAP` para que 0 signifique "sin tope" (hoy 0 = 200 y arruinó la prueba anterior).

```diff
--- a/port/full/gs/gs_draw.c
+++ b/port/full/gs/gs_draw.c
@@ -735,10 +735,15 @@ static void date_snapshot(const GsDraw *d) {
     GsDraw c;
 
     if (sDateCap < 0) {
         const char *e = getenv("BT2_DATE_CAP");
-        sDateCap = e && atoi(e) > 0 ? atoi(e) : 200;
+        /* 0 or a negative value = no cap ("0" used to fall back to 200, which made the experiment
+           BT2_DATE_CAP=0 silently the same as 200). The default stays a sanity bound: 1215 copies of a
+           scissor cost 0.7 ms with glCopyImageSubData (measured, GLINE f=5640). */
+        sDateCap = e != NULL ? atoi(e) : 200;
+        if (sDateCap < 0) { sDateCap = 0; }
     }
-    if ((int)sDateSnaps[d->target] >= sDateCap && sDateFull[d->target]) {
+    if (sDateCap > 0 && (int)sDateSnaps[d->target] >= sDateCap && sDateFull[d->target]) {
         return; /* the full copy the back end made this frame is what this draw reads */
     }
@@ -772,7 +777,7 @@ static void date_snapshot(const GsDraw *d) {
     c.native = 5; /* the back ends copy c.scissor[0..3] from the target's alpha */
     c.wmask = d->wmask;
     c.target = d->target;
-    if ((int)sDateSnaps[d->target] < sDateCap) {
+    if (sDateCap == 0 || (int)sDateSnaps[d->target] < sDateCap) {
         sDateSnaps[d->target]++;
         c.scissor[0] = x0;
         c.scissor[1] = y0;
```

Notas:
- Con `BT2_DATE_CAP` ausente queda 200 (mismo comportamiento actual) o subirlo a 2048 si se prefiere no
  depender del env; con 0 = sin tope, la corrida A se puede repetir con `BT2_DATE_CAP=0` y la semántica
  coincide con lo que uno espera.
- Si la corrida con 2000 **no** arregla: el arreglo no es DATE. Pasar a la corrida B/C/D y buscar el rect /
  la máscara; mi sospecha siguiente es que el juego reescribe el alfa del gauge solo en eventos (habría que
  verlo en el volcado F9 del HUD: `TEST` con DATE=1 y `FRAME_2` con `FBMSK 0xFFFFFF`), o que el rect del
  sprite sale del valor discreto y no de la fracción.

## Evidencia usada (rutas)

- `port/full/gs/gs_draw.c:734-790` (`date_snapshot`, cap, copia full-frame reusada).
- `port/full/gs/gs_draw.c:151-156` (hash de contenido de textura), `port/full/gs/gs_core.c:807-813`
  (`gGsPageGen` por upload), `gs_core.c:700-720` (uplog).
- `port/full/gs/gs_gl.c:796-798` (`gsDateLiveAux = 0`), `:1032-1060` (copia parcial `native 5`),
  `:1363` (`GLTIME ... blit5`).
- `port/full/plat_gs.c:73-105` (ritmo por fase), `port/full/plat_fightlog.c:64` (`Port_EnPelea`).
- `include/battle/btl_char_member.h:41-50` (unidades), `include/battle/hud_a.h:79-99`, `hud_b.h:44-61`.
- `include/sys/gfx.h:92-102` (paridad de buffer / frame).
- Logs: `20261112-015417.log` (cap 200, blit5=201), `20261112-020202.log` (cap 600, blit5≤504, 22 IMPACTO),
  `20261112-013211.log` (blit5 hasta 1214, costo 0.7 ms).
- Dumps: `20261112-001002_ram{1..4}_f393*.bin` (estado: ki +118/cuadro; work del HUD en `0x017EAE8C/E90`).
