# F2 — Widescreen 16:9: cómo está hoy y plan mínimo

Fecha: 2026-11-11. Investigación de **solo lectura**: no compilé, no ejecuté el juego, no edité código del
proyecto y no toqué `/mnt/datos2/BT2-Decomp`. Lo único escrito es este informe en `staging/`.

## 0. Resumen para el orquestador

1. **Hoy el aspecto solo cambia el rectángulo del present.** `Port_AspectMilli()` decide la forma de la
   ventana y el rectángulo al que se escala el framebuffer de 512x448; el juego nunca se entera. Resultado:
   con 16:9 el cuadro entero se **estira 4/3 en horizontal**. Los objetos 3D quedan 33 % más anchos.
2. **La proyección del juego es fija 4:3.** Las cuatro rutinas que inicializan vistas (`func_0025BB38`,
   `func_0025A060`, `func_0025A310`, `func_0025C618`) pasan siempre los mismos dos números:
   `1.0f` (aspectX) y `1.1666666f` (aspectY), y `View_SetProjection` (`func_0025B688`) los normaliza a
   `0.8571429 / 1.0`. No hay ninguna lectura de setting, registro ni variable de entorno en el C del juego.
3. **El renderer ya tiene la otra mitad hecha.** El narrowing 2D de `gs_draw.c:851-894` escala *x* por
   `1333.333 / aspect` (0,75 en 16:9) alrededor de pivotes. Ese 0,75 es exactamente el factor que le falta a
   la proyección 3D: si el 3D abre el FOV horizontal por 0,75, el contenido 4:3 viejo queda en el 75 %
   central y el narrowing 2D vuelve a alinear HUD y efectos en pantalla.
4. **Recomendación:** opción **C** (abrir FOV horizontal) tocando **una sola función**,
   `port/eq/25B688.c` (`View_SetProjection`), reutilizando el mismo factor `1333.333/Port_AspectMilli()`.
   Es el equivalente en BT2 del `Port_WideFactor` de BT3 que mencionan los comentarios del port y que en BT2
   no existe. No hay que tocar scissor, XYOFFSET, framebuffer ni resolución.
5. **Lo que queda roto hasta una segunda fase (opcional):** menús y películas 4:3 se siguen estirando
   (comportamiento heredado de BT3: el comentario de `gs_draw.c` dice que los menús se muestran enteros,
   estirados); split-screen hay que probarlo; y hay que verificar culling, sombras y efectos en los bordes.

---

## 1. Cómo decide hoy el port el aspecto (archivo:línea + fórmula)

| Pieza | Dónde | Qué hace |
|---|---|---|
| Setting | `port/full/plat_gs.c:227-239` (`Port_AspectMilli`) | Lee `aspect_milli` del `bt2_settings.txt` (default **1333**) y lo pisa con `BT2_ASPECT=W:H`, `BT2_WIDE=1/0` (1 → **1778**) o `BT2_WINDOW=WxH`. Clamp 1333..4000. |
| “¿es ancho?” | `port/full/plat_gs.c:242` (`Port_IsWide`) | `Port_AspectMilli() > 1340`. |
| Ventana | `port/full/gs/gs_draw.c:1138-1188` y `1194-1201` | Crea/redimensiona la ventana con forma `h * aspect` (896 líneas de alto). |
| Present GL | `port/full/gs/gs_gl.c:1089-1099` | `want = aspect/1000`; `w = min(sw, sh*want)`, `h = sw/want`; `dx/dy` centran; `glViewport(dx,dy,w,h)` y dibuja el triángulo de presentación. **El framebuffer entero 512x448 se estira a ese rectángulo.** |
| Present Vulkan | `port/full/gs/gs_gpu.c:916-945` | Misma fórmula; `SDL_GPUBlitInfo` con `source 512x448` y destino `w x h` centrado. Mismo estiramiento. |
| Log | `gs_gl.c:1094-1098` / `gs_gpu.c:937-940` | `gl:/vk: present window WxH pixels ... aspect N -> picture WxH at (x,y)` con `BT3_GS_VERBOSE=1` (o `BT2_GS_VERBOSE`, ver §5). |
| Narrowing 2D | `port/full/gs/gs_draw.c:851-894` | Si `Port_IsWide()`, para cada prim 2D texturada/plana al framebuffer principal: `x' = pivot + (x-pivot) * (1333.333/aspect)`. Pivotes: 0/512/256 según `gsAnchor` (`gs_draw.c:876-880`, marcadores `GsGpu_Native` en `1093-1101`). |
| UI | `port/full/gs/ui.cpp:313-336` | Combo “Aspect ratio”: 4:3 (1333), 16:10 (1600), 16:9 (1778), 21:9 (2389), 32:9 (3556). Tooltip: *“Wider than 4:3 shows more of the fight to the sides. Menus are stretched.”* |
| Aplicar/salvar | `port/full/gs/gs_draw.c:1236-1262` | `Port_SetAspectMilli`, `GsDraw_WindowShape`, `Port_SettingSave("aspect_milli", ...)`. |

**Fórmula del present:** `want = aspect/1000`; si `sw > sh*want` el ancho manda (`w = sh*want`), si no el alto
(`h = sw/want`); el resto queda negro (letterbox/pillarbox). No hay crop: el `source` es siempre 512x448
completo (`gs_gpu.c:909-911`, `gs_gl.c:1105-1110`).

**Prueba de que el juego no ve el aspecto:** en `port/eq` no aparece `Port_AspectMilli` ni `Port_IsWide`;
las llamadas a `func_0025B688` pasan constantes (`port/eq/25BB38.c:31,42,48`, `25A060.c:20`, `25C618.c:20`);
y `func_0025AFE0` sólo lee los campos del `View` (`0x228`/`0x22C`), que nadie más escribe para “ancho”.
El propio port lo dice en `port/full/plat_gs.c:224-225`:
> “Solo el renderer la usa por ahora: el C del juego aun no ensancha la proyeccion (Port_WideFactor de BT3),
> asi que ancho = barras / estirado.”

**Contradicción a tener presente:** `gs_draw.c:852` dice “The 3D scene is projected for a 16:9 picture by the
game itself” y el tooltip de la UI promete “shows more of the fight to the sides”. Eso **no es cierto en BT2
hoy**: es texto heredado de BT3. El comentario autoritativo es el de `plat_gs.c:225`.

---

## 2. Estado del GS que define el encuadre

El área de dibujo no es un “viewport” configurable: la fija el juego al armar el `sceGsDBuff` y los `View`:

| Registro / pieza | Evidencia | Valor |
|---|---|---|
| `FRAME_1` / `ZBUF_1` | `port/full/gs/gs_sony.c:38-39` (`fill`) | `fbp` 0 / 0x70, `FBW=(w+63)/64`, PSM 0; zbuf 24/32 bits. |
| `XYOFFSET` | `gs_sony.c:40` | `((2048 - w/2)<<4, (2048 - h/2)<<4)`; con `w=512,h=448` → 0x7000/0x7200. Es el “centro” del espacio GS de 4096. |
| `SCISSOR` | `gs_sony.c:41`; además `port/eq/25BB38.c:33-35` (batalla) y `25A060.c:21-24` (demo) | `x 0..511`, `y 0..447` (`0x1FF`/`0x1BF`). |
| Tamaño del DBuff | `port/eq/24B800.c:17-18`, `port/eq/271078.c:17` | `sceGsSetDefDBuff(..., psm 0, w=0x200 (512), h=0x1C0 (448), ...)`. |
| `PRIM` / `TEST` / `ALPHA` | `port/full/gs/gs_core.c:820-848` | Se interpretan; no definen el encuadre. |
| `XYRANGE` | **no existe como registro GS** (0x1A/0x1B son PRMODECONT/PRMODE; `gs_core.c:843-844`). | — |

Conclusión: el juego fija **512x448** y no lo cambia con el aspecto. Si se “ensancha el área” sin tocar la
proyección, el 3D sigue proyectado para 4:3: sólo se verían bandas laterales vacías o geometría recortada;
no aparece más mundo. Por eso la opción de tocar scissor/XYOFFSET se descarta (§6).

---

## 3. Proyección del juego (lo que hay que tocar)

### 3.1 Cadena real (C nativo en el port, no recompilado)

En el binario actual (`BT2-test/bin/bt2`, `nm`/`objdump`):

- `func_0025B688` = **View_SetProjection**, nativo en `0x40296fc0`. `port/eq/25B688.c:5-36` es fiel al asm
  `asm/cod/15B684.s:16-67` (mismos stores y mismas comparaciones `c.lt.s`/`div.s`).
- `func_0025AFE0` = **View_BuildProjection**, nativo en `0x40296840` (`port/eq/25AFE0.c`).
- `func_0025BB38` = **View_InitLayout / layouts de batalla**, nativo en `0x40297360`
  (`port/eq/25BB38.c`). Arma la vista full-screen y las dos medias de split-screen.
- `func_0012E900` = matriz de efectos por frame (`port/eq/12E900.c`), llamada desde
  `src/battle/xa_1263D0.c:36` (`BtlScene_DrawFrame`), **lee el aspecto del `View`** en `12E900.c:53-54`.

### 3.2 Los números

`func_0025B688` guarda (offsets reales de BT2, verificados en el asm/C):

| Offset | Campo | 4:3 full-screen |
|---|---|---|
| `+0x210..0x21C` | `screenSize` | `(2047, 2047, 0.1, 16777215)` |
| `+0x224` | screenDist | `433` |
| `+0x228` | **aspectX** | `1.0 / 1.1666666 = 0.8571429` |
| `+0x22C` | **aspectY** | `1.0` |
| `+0x230/+0x234` | centerX/centerY | `2048/2048` (medias: 1920/2176 y 2048) |
| `+0x238..0x248` | zMin/zMax/near/far/unk | `1, 10877000, 0.3, 65536, 1` |

La normalización está en `port/eq/25B688.c:23-34`: el mayor de los dos aspect se lleva a 1 y el otro queda
como cociente. Por eso todos los callers pasan `1.0f, 1.1666666f`:

- `port/eq/25BB38.c:31` (full), `:42` (izquierda, centerX 1920), `:48` (derecha, centerX 2176).
- `port/eq/25A060.c:20` (vista de la demo/título).
- `port/eq/25A310.c:22` (init de la demo).
- `port/eq/25C618.c:20` (otra vista full-screen).

La constante `1.1666666f` está en `.lit4` (`asm/data/cod/284D68.lit4.s:12441-12443`, `D_00386DC8`) y vale
`448*4/512/3`. No depende de nada en runtime. El cociente final `0.8571429` es exactamente
`(512/448)/(4/3)`: la compensación de píxel no cuadrado para una pantalla 4:3. **El juego está proyectando
4:3, no 16:9.**

### 3.3 Qué factor hay que aplicar para 16:9

Para que un objeto del mundo se vea cuadrado cuando el cuadro 512x448 se estira al aspecto `A = W/H`:

```
Sx / Sy = (512/448) / A = 1.142857 / A
```

- 4:3 (`A=1.3333`): `0.8571429` → lo que ya hace el juego.
- 16:9 (`A=1.7778`): `0.642857` → hay que multiplicar el aspectX por `0.75`.
- 21:9: `0.478` → factor `0.558`; 32:9: `0.321` → factor `0.375`.

Ese factor es **el mismo** que ya usa el narrowing 2D (`gs_draw.c:890`: `1333.333/aspect`). O sea: la
proyección 3D tiene que achicar su escala horizontal por `1333.333/Port_AspectMilli()`.

### 3.4 Por qué no alcanza con tocar sólo `View_BuildProjection`

`func_0025AFE0` construye tres matrices (`+0x40`, `+0x80`, `+0xC0`) y `12E900` arma aparte la matriz de
efectos leyendo **el mismo** `+0x228/+0x22C` (`12E900.c:53-54`). Si el factor se aplica sólo al constructor
de matrices, los efectos quedan con el aspecto viejo y se desalinean. Por eso el cambio va en
**`View_SetProjection`**, que es donde queda guardado el aspecto para todos los consumidores.

### 3.5 El clip de VU1 no debería cortar el FOV nuevo (a verificar)

La matriz de clip (`+0x80`) se arma en `25AFE0.c:68` con `screenSize.x` y **no** con el aspecto:
`[0][0] = 433/2047 = 0.2116`. La de pantalla (`+0xC0`, `25AFE0.c:84`) usa `aspectX`: a 4:3 da
`2047*0.857 = 1755`. El clip es ~4x más ancho que el área visible a 4:3; a 16:9/21:9/32:9 el área visible
sigue entrando (a 32:9 el semi-ancho visible proyectado a z=near es ~0.94 contra ~1.42 del clip). **Es una
inferencia a partir de las fórmulas; hay que confirmarla con una prueba a 32:9** (ver §8).

---

## 4. HUD y pantallas 2D

- La UI se dibuja con prims **GIF** en coordenadas GS (0..511, 0..447), no con un sistema de layout por
  resolución. Las ventanas de texto (`mc_textwindow`, `func_2A38C0`, `Font_PrintAt`) leen `x/y` de registros
  fijos y no hay tabla por resolución (ver `staging/informe_ventanas_texto.md`, resumen: no existe una
  llamada común de posicionamiento ni una tabla de posiciones; los `x/y` salen de `+0x50/+0x54/+0x58...`).
- El `clip` de la fuente también es fijo 0..511/0..447 (`port/eq/2A0630.c:25,32`).
- El renderer compensa el estiramiento con `gs_draw.c:851-894`:
  - Piezas con `gsAnchor` 1/2 (panel izquierdo/derecho) se anclan a x=0/512 → quedan **en los bordes** de la
    pantalla 16:9.
  - Piezas con `gsAnchor` 3/4 (centro/caption) y **todo lo demás** (pausa, mensajes, texto) usan pivote 256 →
    quedan en el **75 % central**, que es el área 4:3 segura. Eso incluye a los efectos dibujados como
    prims 2D (sprites de impactos, auras, etc.), que es justamente lo que los vuelve a alinear con el mundo
    cuando la proyección se ensancha.
  - Se dejan sin tocar: fills/fades sin textura de altura completa y sprites de >=480 px de ancho (bandas de
    READY/FIGHT, flashes, líneas de velocidad): están pensados para ir de borde a borde.
  - Limitación conocida y documentada en `gs_draw.c:884-886`: un marcador que el juego clava sobre un
    luchador se corre un poco hacia el centro; no está resuelto.
- **Menús:** las páginas de ancho completo (>=480) no se narrowan; se muestran estiradas 4/3
  (`gs_draw.c:872-875` y el comentario `854`: “not in the menus: their pages are shown whole, stretched”).
  Es comportamiento heredado de BT3, no un bug introducido por BT2.
- Después del cambio de proyección, el narrowing 2D **no hay que tocarlo**: el 0,75 es el complemento exacto
  del FOV abierto. Sin el cambio de proyección, en cambio, el narrowing sólo corrige la forma pero no la
  posición relativa al 3D (por eso hoy un marker puede quedar corrido).

---

## 5. Opciones que ya existen (no hay que inventarlas)

| Qué | Dónde | Notas |
|---|---|---|
| `aspect_milli` persistente | `port/full/gs/plat_settings_bt3.c` (archivo `bt2_settings.txt`, `BT2_SETTINGS`) | En `BT2-test/bt2_settings.txt` hoy sólo hay `fullscreen=0`; el default es 1333. |
| `BT2_ASPECT=16:9` | `plat_gs.c:233` | `sscanf("%d:%d")`; es la forma más directa de probar sin tocar la UI. |
| `BT2_WIDE=1` | `plat_gs.c:234` | Fija 1778 (16:9 aproximado). `BT2_WIDE=0` fuerza 4:3. |
| `BT2_WINDOW=WxH` | `plat_gs.c:235` | Si el window es más ancho que 4:3, toma ese aspecto. |
| Combo en F1 | `ui.cpp:313-336` | Ya permite 16:10/16:9/21:9/32:9 y guarda. |
| Renderer software | `gs_core.c:1069` | **No soporta wide**: `SDL_SetRenderLogicalPresentation(..., 512,448, LETTERBOX)` y `SDL_RenderTexture(tex,NULL,NULL)`. La ventana por software siempre muestra 4:3. Probar con `BT3_GS=gpu` (`jugar.sh`). |
| Capturas | `BT3_SHOT` (framebuffer 512x448), `BT3_GL_WINSHOT=n` (ventana real, `gs_gl.c:1125-1148`) | Para validar el estiramiento final hay que mirar **window shots**, no los PPM de 512x448. |
| Log de estado | `BT2_STATELOG`/`BT2_FIGHTLOG` (`plat_fightlog.c:188-235`) | Ya calcula `gBt2InBattle` (lista de personajes válida) para el log; sirve como hook si se quiere detectar menú. |

No hay ningún otro parámetro de resolución/recorte en `port/full`. El renderer soporta cualquier forma de
ventana (letterboxea), pero **el juego no**.

---

## 6. Estrategias posibles

### A. Letterbox 4:3 dentro de 16:9 (pillarbox)

- **Qué es:** mantener la proyección 4:3 y presentar el cuadro 512x448 en un rectángulo 4:3 centrado, con
  barras negras a los lados.
- **Cómo:** ya está implementado: poné `aspect_milli=1333` con una ventana/fullscreen 16:9; el present de
  `gs_gl.c:1089-1099` / `gs_gpu.c:916-945` lo hace solo. Para usarlo selectivamente (menús/FMV) haría falta
  un override por frame.
- **Qué se rompe:** nada. Se ve como la PS2, con barras.
- **Esfuerzo:** 0 si es el modo global; ~15 líneas si se quiere sólo para menús/películas.

### B. Estirar el área visible (lo que hace hoy) / crop vertical

- **B1, estiramiento (actual):** `aspect=1778`. El framebuffer completo se estira 4/3. Los objetos 3D quedan
  33 % más anchos; el narrowing 2D corrige la forma del 2D pero no el 3D. **No es widescreen correcto.**
  Esfuerzo: 0, pero no sirve.
- **B2, crop vertical:** para sacar 16:9 del buffer 512x448 habría que recortar a 512x288 (16:9), perdiendo
  160 de 448 líneas (36 %): se van el HUD superior/inferior y partes de los luchadores. No es viable sin
  rehacer el layout vertical. Esfuerzo bajo en el present, pero rompe todo. **Descartada.**

### C. Abrir el FOV horizontal (recomendada)

- **Qué es:** mantener 512x448, el scissor, el XYOFFSET y el FOV vertical; achicar la escala horizontal de la
  proyección por `1333.333/aspect`. El mundo 4:3 viejo pasa al 75 % central y aparece mundo nuevo a los
  lados; el present estira 4/3 y las proporciones vuelven a ser correctas.
- **Qué se toca:** `View_SetProjection` (`port/eq/25B688.c`), que es el único punto por donde pasan todas las
  vistas (batalla, split-screen, demo, cámaras de menú) y el aspecto que después leen los efectos
  (`12E900.c:53-54`).
- **Qué se rompe / hay que probar:**
  - Menús y películas 4:3: siguen estirados (fase 2 opcional).
  - Split-screen: el factor uniforme 0,75 es el correcto para el cuadro completo; para cada mitad puede no
    serlo (las medias tienen otro aspecto físico). Hay que probar 2P.
  - Efectos dibujados por VU (no pasan por el narrowing GIF): deberían quedar bien porque son 3D y usan la
    misma proyección; los que se dibujan como sprites GIF pasan por el narrowing 0,75 y también. Verificar
    impactos/auras.
  - Sombras: `ObjShadow_CalcScreenDist` (`port/eq/268BC8.c`) y el VU6 usan una distancia de pantalla propia;
    `func_0025B2D0` (`port/eq/25B2D0.c:41-51`) usa `screenSize.x` y `433` con un factor 1/512 fijo. No leen
    el aspecto. Probar sombras y efectos cerca de los bordes.
  - Culling: `EftPrim_IsOffScreen` (símbolo en el binario `0x4013c8c0`) prueba `z>0` y x/y dentro del rango
    GS 12.4 (constantes `0xFFFF0010/0xFFFF0011`), no 512x448: no debería cortar el FOV nuevo. Las pruebas de
    visibilidad que usan el scissor (`port/eq/27E9F0.c:37-44`, con `1792/1824`) siguen dentro de 0..511.
  - Borde del mundo / LOD: al abrir el FOV se ve más de los costados; puede aparecer el “borde” de B25 o
    geometría de baja calidad. Probar en un escenario abierto.
  - Cambio de aspecto en caliente: la proyección se arma al iniciar la escena (`func_00102640` llama a
    `func_0025BE48` = BtlCam_Init y `func_0025A310` = DemoCam_Init; ver `port/eq/102640.c:90-91`). Si se
    cambia el aspecto con F1 **durante** una pelea, no se aplica hasta la próxima pelea/escena (o hasta
    agregar un rebuild explícito). Avisar en el tooltip o agregar el hook.
- **Esfuerzo:** ~6 líneas en un archivo + pruebas visuales. La fase 2 (menús/FMV en 4:3) suma ~15-30 líneas.

---

## 7. Plan mínimo recomendado (diff, **sin aplicar**)

### 7.1 Cambio único: `port/eq/25B688.c`

Se aplica después de la normalización existente (líneas 25-34) y antes de `func_0025AFE0` (línea 35). No toca
la constante de `.lit4` (es read-only y la comparten los cuatro callers; cambiarla afectaría también al
default 4:3).

```diff
--- a/port/eq/25B688.c
+++ b/port/eq/25B688.c
@@ -1,5 +1,11 @@
 #include "common.h"
 
+/* F2 (widescreen): el renderer estira el cuadro 512x448 al aspecto pedido; para que el 3D no se
+   estire, la proyeccion abre el FOV horizontal por el mismo factor que el narrowing 2D
+   (1333.333/aspect). Es el equivalente en BT2 del Port_WideFactor de BT3. */
+extern int Port_IsWide(void);
+extern int Port_AspectMilli(void);
+
 void func_0025AFE0(void *a0, void *a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19, f32 f20, f32 f21);
 
 void func_0025B688(void *arg0, void *arg1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19, f32 f20, f32 f21) {
@@ -31,6 +37,9 @@
         *(f32 *)(v0 + 0x22C) = 1.0f;
         *(f32 *)(v0 + 0x228) = f0v / f1v;
     }
+    if (Port_IsWide()) {
+        *(f32 *)(v0 + 0x228) *= 1333.333f / (float)Port_AspectMilli();
+    }
     func_0025AFE0(arg0, arg1, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21);
 }
```

Notas:
- `+0x228` es siempre el factor **horizontal** (el `f13` que guarda la línea 23; la normalización sólo lo
  reescala). Multiplicarlo no rompe la normalización: `25AFE0` usa `+0x228` y `+0x22C` por separado.
- A 4:3 el factor es 1.0 → no cambia nada.
- A 16:9 el factor es 0.75 → el aspectX pasa de 0.857 a 0.643; el vertical queda 1.0.
- **No** hace falta tocar `gs_draw.c`: el narrowing ya usa el mismo 1333.333/aspect.
- El binario actual lleva esta función como C nativo (`nm`: `func_0025B688` en `0x40296fc0`; `objdump`
  coincide con el C), así que el cambio impacta directo en el juego.

### 7.2 Fase 2 opcional (sólo si se quiere que menús/FMV no se estiren)

Idea, a validar antes de codificar: en el present, si el frame **no tuvo dibujos 3D** (por ejemplo
`gsVuVertCount == 0` al llegar al present; se resetea después, en `gs_gl.c:1227-1230` / `gs_gpu.c:1128-1131`),
usar `want = 4.0f/3.0f` y no aplicar el narrowing 2D. Eso pillar-boxea logos, películas y menús puramente 2D,
y deja 16:9 para todo frame con 3D (pelea, character select con modelo, preview de escenario). Es
independiente del cambio de proyección y se puede dejar para después. **No hay que hacerlo en el primer
intento.**

### 7.3 Qué NO tocar

- `sceGsSetDefDBuff` / `gs_sony.c` / el scissor / el framebuffer 512x448: el FOV se abre dentro del mismo
  espacio; cambiar el tamaño del buffer obligaría a rehacer targets, HUD y present.
- La constante `D_00386DC8` (1.1666666) en `.lit4`: es read-only y compartida.
- El narrowing 2D: ya está en el factor correcto.

---

## 8. Qué medir/loguear primero (sondas concretas)

1. **Present actual:** `BT3_GS_VERBOSE=1` (o `BT2_GS_VERBOSE=1`) y `BT2_ASPECT=16:9`; confirmar
   `... aspect 1778 -> picture WxH at (x,y)` con `W/H ≈ 1.778` y sin crop (`gs_gl.c:1097`, `gs_gpu.c:940`).
2. **Estado del GS:** `BT3_GS_DUMP=<frame de pelea>` (se arma en `gs_core.c:1394`). Imprime por prim
   `xyoff`, `scis`, `frame`, `zbuf`, `test` y las coordenadas (`gs_core.c:605-617`). Esperado en pelea:
   `xyoff 0,0`, `scis 0..511,0..447`, `frame` 0/0x70. Comparar la extensión en x de los prims 3D con 4:3 vs
   16:9: después del cambio, el mundo viejo debe ocupar el 75 % central.
3. **Proyección:** log TEMP en `port/eq/25B688.c` después de línea 34:
   `arg0`, `+0x224`, `+0x228`, `+0x22C`, `+0x230`, `+0x234`, `Port_AspectMilli()`. Esperado 4:3:
   `433, 0.8571, 1.0, 2048, 2048`; 16:9: `433, 0.6429, 1.0, ...`.
4. **Matrices construidas:** log TEMP en `port/eq/25AFE0.c` al final:
   `[0][0]/[1][1]` en `+0x40/+0x54` (pantalla), `+0x80/+0x94` (clip), `+0xC0/+0xD4` (otra). Esperado 4:3:
   `371/433`, `0.2116/0.2116`, `1755/2047`; 16:9 después del parche: `278/433`, **clip igual**, `1316/2047`.
   Si el clip cambia, revisar la suposición de §3.5.
5. **Efectos:** log TEMP en `port/eq/12E900.c` después de `B[0]/B[5]` (`12E900.c:53-54`): debe seguir el
   mismo cociente que `+0x228/+0x22C` del `View`.
6. **¿El frame es 3D?** log TEMP en `gs_gl.c`/`gs_gpu.c` antes del present:
   `gGsFrame`, `gsVuVertCount`, `Port_AspectMilli()`. En pelea debe ser >0; en el menú principal y en las
   películas, 0. Es la validación de la heurística de la fase 2.
7. **Aspecto final:** `BT3_GL_WINSHOT=60` (GL) para capturar **la ventana** (no el framebuffer de 512x448);
   comparar el mismo cuadro con `BT2_ASPECT=4:3` y `16:9`. Medir el ancho/alto de un luchador o de un objeto
   conocido; después del parche la relación debe ser la misma (hoy crece 33 %).
8. **Culling/sombras/efectos:** jugar un combate en un escenario abierto y mirar los costados (pop-in,
   sombras, auras, impactos). Si algo desaparece en los bordes, comparar con el volcado `BT3_GS_DUMP` para ver
   si el prim llegó al GS o si lo culló el juego antes.

---

## 9. Riesgos y qué se rompe (resumen)

| Área | Con la opción C | Cómo verificarlo |
|---|---|---|
| 3D en pelea | **Se arregla**: objetos con proporción correcta y más mundo a los lados. | Window shots 4:3 vs 16:9. |
| HUD anclado a bordes | Paneles quedan en los bordes reales; los marcadores no anclados quedan en el 75 % central. | Pelea con daño/markers. |
| Texto/ventanas 2A* | En el 75 % central; el `clip` de fuente sigue 0..511, no se recorta. | Menú/pausa/mensajes. |
| Menús full-screen | Se estiran 4/3 (igual que BT3). Fase 2 opcional. | Menú principal, character select. |
| FMV/logos | 512x448 estirados a 16:9. Fase 2 opcional. | Intro/opening/ending. |
| Split-screen | Factor uniforme 0,75; puede no ser el correcto para cada mitad. | Duelo 2P. |
| Efectos VU vs GIF | Los VU usan la proyección nueva; los GIF pasan por el narrowing 0,75. Deberían coincidir. | Kamehameha/auras/impactos (B14). |
| Sombras | `268BC8`/`25B2D0` usan 433 y 1/512 fijos; posible desfase. | Sombras cerca de los bordes. |
| Culling | `EftPrim_IsOffScreen` usa rango GS 12.4 (no 512x448); el clip VU parece 4x más holgado. | Objetos que entran/salen por los costados. |
| Borde del mundo / LOD | Se ve más costado; puede aparecer B25/seams. | Escenario abierto (Wasteland). |
| Cambio en caliente | La proyección se arma al iniciar escena; F1 en pelea no se aplica hasta la próxima. | Cambiar aspecto en pelea y volver a entrar. |
| Renderer software | No soporta wide (letterbox fijo 4:3). | Usar `BT3_GS=gpu`. |

---

## 10. Lo que NO pude determinar (pendiente de correr el juego)

- Si el modo 16:9 actual fue probado alguna vez: **no encontré ningún log con `aspect` distinto de 1333**
  en `BT2-test/logs` (todos los `present window` son 4:3). La conclusión de “estiramiento” es de código, no
  visual.
- La implementación exacta del `Port_WideFactor` de BT3: no hay copia local de Tenkaichi3Decomp; sólo
  aparece el nombre en comentarios (`gs_draw.c:854`, `plat_gs.c:225`). Nuestro factor se deriva de las
  fórmulas del propio `View_SetProjection`.
- Si el clip de VU1 (`+0x80`, sin aspecto) es realmente un guard-band o el frustum visible. Las cuentas
  sugieren guard-band, pero hay que probar 32:9 y mirar si desaparece geometría en los bordes.
- Si *todo* el 3D pasa por los caminos VU (`gsVuVertCount > 0`) o si hay 3D por GIF que rompería la
  heurística de “frame 3D” de la fase 2. Se resuelve con el log del punto 6 de §8.
- El comportamiento correcto de split-screen (2P) con aspecto ancho.
- Si las sombras (`ObjShadow_*`) y `func_0025B2D0` quedan bien con el FOV abierto; no leen el aspecto y usan
  constantes de 512/433.
- Si los menús que mezclan 3D y páginas 2D de ancho completo (character select, map select) se ven aceptables
  con la página estirada y el modelo 3D correcto.
- El impacto exacto en el “borde del mundo” (B25) y en el LOD de los escenarios abiertos.

---

## Anexo — direcciones y referencias rápidas

- Binario actual `BT2-test/bin/bt2` (x86-64, con símbolos):
  - `func_0025B688` @ `0x40296fc0` (View_SetProjection, C nativo; `objdump` coincide con `port/eq/25B688.c`).
  - `func_0025AFE0` @ `0x40296840` (View_BuildProjection).
  - `func_0025BB38` @ `0x40297360` (View_InitLayout / layouts de batalla).
  - `EftPrim_IsOffScreen` @ `0x4013c8c0` (chequeo fijo de rango GS 12.4).
- Asm de referencia:
  - `asm/cod/15B684.s:16-67` — `func_0025B688` (stores `+0x228/+0x22C`, normalización, `div.s`).
  - `asm/data/cod/284D68.lit4.s:12441-12443` — `D_00386DC8 = 1.166666627`.
  - `asm/data/cod/23F400.data.s:3715-3719` — vector de aspecto `(1, 7/6, 1, 1)` que usan los efectos 2D.
- C del port:
  - `port/eq/25B688.c` (View_SetProjection), `25AFE0.c` (matrices), `25BB38.c` (layouts),
    `25A060.c`/`25A310.c`/`25C618.c` (vistas demo/full), `12E900.c` (matriz de efectos por frame),
    `25B2D0.c` (frame de objeto con 512/433), `268BC8.c` (sombra).
  - `port/full/gs/gs_draw.c:851-894` (narrowing 2D), `gs_gl.c:1089-1099` / `gs_gpu.c:916-945` (present),
    `plat_gs.c:227-242` (aspect), `ui.cpp:313-336` (combo).
- Documentos del proyecto usados: `staging/informe_ventanas_texto.md` (ventanas 2A/Font, sin tabla por
  resolución), `staging/B25_investigacion_borde.md` (borde del mundo, FOG no implementado).
