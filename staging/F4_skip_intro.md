# F4 — Saltar intro (logos + opening) en BT2

Fecha: 2026-11-11. **Solo lectura**: no edité, no compilé y no lancé el juego. No accedí a
`/mnt/datos2/BT2-Decomp`. Lo único escrito es este informe.

Referencia usada: `Tenkaichi3Decomp` clonado en `/tmp/opencode/t3d` (el mismo commit que el informe
`F3F6_desde_tenkaichi3decomp.md`), el asm del port en `port/build/combined.elf` y los logs viejos de
`BT2-test/logs/vivo/`.

---

## 0. Conclusión corta

1. **Todo el arranque que se ve está en C nativo del port**, no en el overlay recompilado:
   `port/eq/3BC310.c` (secuencia completa), `port/eq/3BC000.c` (cada logo quieto), `port/eq/24BA78.c`
   (reproductor de películas) y `src/auto/m2c_24BE80.c` (opening). `port/build/recomp/` tiene copias de
   esas funciones, pero **no se usan**: `port/build/gen/full/report.csv` las marca `OK,cached` y
   `port/full/FALLBACK_AUTO.txt` no las lista.
2. **La intro de arranque es:** espera de pad + chequeo de memory card (no es video) → 5 logos quietos →
   `LOGO_O.SFD` → opening `ZS2USOP.SFD` → título. Los logos quietos suman ~10 s, `LOGO_O` 5,04 s y el
   opening **107,87 s**: ~2 min 3 s en total.
3. **Hoy se puede saltear a mano, pero no con un setting:** START/CROSS corta los logos 5, 4, 2 y 3
   (con un fade de 15 cuadros, no instantáneo); el logo 1 (el último) **no** tiene skip. START corta
   `LOGO_O` y el opening. `BT2_SKIP_MOVIES=1` cubre **sólo los SFD** (`LOGO_O`, opening, ending), no los
   logos quietos, y no hay atajo propio del port.
4. **Enganche mínimo propuesto:** un flag `Port_SkipIntro()` (env `BT2_SKIP_INTRO`, setting persistente
   `skip_intro` en `bt2_settings.txt`) y **dos hooks**: uno en `3BC310` después de `3BBD98` (saltea los
   logos + `LOGO_O` + opening del arranque) y otro en el estado 2 de `3B7FA8` (el opening que se repite
   al quedar idle en el título). **Default propuesto: encendido (1)**; se apaga con
   `BT2_SKIP_INTRO=0` o `skip_intro=0`.
5. **No tocar** `3BC5A8` (espera de pad) ni `3BBD98` (chequeo de memory card): este último **puede dejar**
   flags `D_003876A4+0x18` bits `0x400/0x800` que el título y el demo consultan después
   (`port/eq/3BB480.c:146-147`, `port/eq/3B9710.c:76`, `port/eq/3B84B8.c:140`). Saltearlas por la fuerza
   puede cambiar el flujo de "New Game"/memory card.

---

## 1. Secuencia de arranque: archivo, función y duración

### 1.1 Dónde vive cada cosa

`main` (`port/eq/100388.c:35`, `func_00100388`) hace la init de SDK/pad/memory card y entra al bucle
`Overlay_Load(0)` → `Progress_Main` (`port/eq/100388.c:123-127`). `func_001021E8`
(`port/eq/1021E8.c:40-41`) deja el modo en **1 (título)** y prende el flag `0x40`; `Progress_Main`
(`port/eq/3B7FA8.c:51-55`) ve ese flag una sola vez y llama a `func_003BC310()`, que es **toda la intro**.
Después sigue el estado 1 = título (`port/eq/3B7FA8.c:108-130`, `func_003BAFE8`).

Evidencia en el asm (`/tmp/opencode/bt2_dis.txt`, salida de
`tools/binutils/mips-ps2-decompals-objdump -d port/build/combined.elf`):

- `0x3BC310`: `jal 0x24be18`, `jal 0x3bc5a8`, `jal 0x24be18`, `jal 0x3bbd98`, carga la sección `+7`
  del archivo (`jal 0x100d58`), `jal 0x100950`, y después `jal 0x3bc000` con `a0 = 5, 4, 2, 3, 1`
  (`a1 = 0x3C`, 60 cuadros), `jal 0x24ba78` con `a0 = 0x421C88`, `jal 0x100990`, y `j 0x24be80`.
- `0x24BE80`: `lui a0,0x37; addiu a0,a0,0x4a38` = **0x374A38** = `"zs2usop.sfd"` (string en `.rodata`,
  offset de archivo `0x275a38`).
- `0x24BEA8`: `0x374A48` = `"zs2used.sfd"` (ending, **no** es parte del arranque).
- `D_00421C88` (en `.data.ovl`, vaddr `0x421C88`) = `"logo_o.sfd"` (offset de archivo `0x28dc88`).

### 1.2 Tabla de etapas

| # | Etapa | Dónde (C nativo) | Qué hace | Duración | ¿Se puede saltear? |
|---|-------|------------------|----------|----------|--------------------|
| 0 | Init / espera de pad | `port/eq/3BC5A8.c:22-46` | Carga la sección `+0x13` y espera a que el pad esté en estado 1; dibuja mientras espera | hasta que el pad responde | **No** (no es video; asegura el pad) |
| 1 | Chequeo de memory card | `port/eq/3BBD98.c:32-69` + `3BB480.c` | Corre la máquina de memory card del arranque (estado `0xC`); puede dejar flags `0x400/0x800` | variable; el estado usa timers de `0x78` (120 cuadros) | **No** (la usan el título y el demo) |
| 2 | Logo 5 | `3BC310.c:35` → `3BC000.c` | Logo quieto del pack `D_00421388` | 60 cuadros de espera + fades de 30+30 ≈ 122 cuadros ≈ **2,0 s** | Sí, START/CROSS (fade a 15) |
| 3 | Logo 4 | `3BC310.c:37` → `3BC000.c` | Idem | ≈ **2,0 s** | Sí, START/CROSS |
| 4 | `LOGO_O.SFD` | `3BC310.c:39` → `24BA78.c` | Video (Okratron) | 151 cuadros a 29,97 = **5,04 s** | Sí, START |
| 5 | Logo 2 | `3BC310.c:41` → `3BC000.c` | Logo quieto | ≈ **2,0 s** | Sí, START/CROSS |
| 6 | Logo 3 | `3BC310.c:42` → `3BC000.c` | Logo quieto | ≈ **2,0 s** | Sí, START/CROSS |
| 7 | Logo 1 | `3BC310.c:43` → `3BC000.c` | Último logo quieto (a2=0) | ≈ **2,0 s** | **No** por el juego; sólo con el setting/hook |
| 8 | Opening `ZS2USOP.SFD` | `3BC310.c:47` → `24BE80.c` → `24BA78.c` | Video de apertura | 3236 cuadros a 30 = **107,87 s** | Sí, START |
| 9 | Título | `3B7FA8.c:108-130` → `3BAFE8.c` | Carátula/“PRESS START”, después menú | — | No es intro; no se toca |
| 10 | Attract (idle) | `3B9710.c:107-190` | A los `0x708` cuadros (~30 s) monta una pelea CPU vs CPU; a los 2 demos vuelve a poner el opening en cola | ~30 s de espera; pelea real | No es video; CROSS corta el estado de título (ver §3) |
| 11 | Opening repetido por idle | `3B9710.c:117-120` → `3B7FA8.c:126-129` → `24BE80.c` | Después de 2 demos, `*s2p=2` ⇒ estado 2 ⇒ opening otra vez | **107,87 s** | Sí, START (y con el hook B, automático) |

Notas de la tabla:

- La duración de los logos quietos sale de `3BC000`: `a1 = 0x3C` se guarda en `O->0x10`; el contador
  `O->0x14` espera hasta `O->0x10 + 2` y recién ahí dispara el fade-out de `0x1E`
  (`port/eq/3BC000.c:91-99`); además hay fade-in de `0x1E` (`:56-68`). Es ~2 s por logo a 60 Hz.
- La duración de los SFD sale de `ffprobe` (solo lectura) sobre `gamedata/DATA`:
  `LOGO_O.SFD` 151 cuadros / 5,039 s; `ZS2USOP.SFD` 3236 cuadros / 107,867 s; `ZS2USED.SFD`
  5400 cuadros / 180 s (ending, no se toca).
- **Mapping exacto de las secciones 2/3 a “Bandai” y “Spike” no lo pude confirmar** sin extraer el pack
  `D_00421388` (sección `0x54B` de `ZS2US_1.AFS`: `D_003876A4+4 = 0x544` en `1021E8.c:24`, `+7` en
  `3BC310.c:28`). El orden observado en `docs/PORT_LOG.md:142-143` es Atari, Funimation, Okratron,
  Bandai Namco, Spike, Sofdec/ADX; con el video en el medio, lo seguro es: 5 y 4 antes, 2/3 después,
  1 último.

### 1.3 Dónde **no** está la intro

- `port/build/recomp/func_003BC310_0x3bc310.cpp` y `func_0024BE80_0x24be80.cpp` existen, pero son el
  **relleno** de PS2Recomp. No se usan porque hay C del juego (`report.csv`: `port/eq/3BC310.c,OK,cached`,
  `src/auto/m2c_24BE80.c,OK,cached`; `port/full/FALLBACK_AUTO.txt` no los contiene). Tocar el C++
  recompilado no cambiaría nada en este build.
- No hay `src/menu/menu_i_c.c` en BT2: el `menu_i.h` que está en `include/menu/` es nomenclatura tomada
  de BT3/T3D, pero la implementación de BT2 está en `port/eq/3BC310.c` + `3BC000.c`.

---

## 2. Equivalencia con Tenkaichi3Decomp

| T3D | BT2 |
|-----|-----|
| `FirstRun_Main` (`src/menu/menu_i_c.c:163-186`) | `func_003BC310` (`port/eq/3BC310.c:22`) |
| `Logo_ShowAll` / `Logo_Show` (`menu_i_c.c:45-119`) | `func_003BC000` (`port/eq/3BC000.c:33`) |
| `LOGO_SKIP_ANY` / `LOGO_SKIP_NONE` | argumento `a2` de `3BC000` (1 = START/CROSS, 0 = sin skip) + bits `0x4008` |
| `Movie_PlayOpening` (`src/sys/movie.c:249-300`) | `func_0024BE80` (`src/auto/m2c_24BE80.c:7`, abre `zs2usop.sfd`) |
| `MOVIE_SKIP_BUTTON` (START) | `D_003B0B00+0x134 & 8` en `func_0024BA78` (`port/eq/24BA78.c:151-157`) |
| `Title_Input` + `fl_skip` (`menu_a_c.c:206-215`) | El título de BT2 no tiene intro hablada; `func_003B9710` maneja el attract/entrada (`port/eq/3B9710.c:48-105`) |

T3D **no** tiene un setting de skip: sólo el skip nativo. El único automático es `BT3_NOMOVIE`, que, igual
que `BT2_SKIP_MOVIES`, no cubre los logos quietos.

---

## 3. Cómo se saltea hoy, etapa por etapa

### 3.1 Logos quietos (`3BC000`)

`port/eq/3BC000.c:101-107`:

```c
if (a2 != 0 && (*(s32 *)(D_003B0B00 + 0x134) & 0x4008) != 0) {
    if (t0 != 0) {
        func_243AF8(0, 0, 0, 0xF);
    } else {
        func_243AF8(0xFF, 0xFF, 0xFF, 0xF);
    }
}
```

- `D_003B0B00+0x134` es el **pressed** del pad (`func_0028BDA0` lo llena con `tv & ~old`;
  `port/eq/28BDA0.c:58`). `0x4008` = **START (`0x8`) | CROSS (`0x4000`)**.
- No corta el logo de inmediato: dispara un **fade-out de 15 cuadros** (`0xF`) en vez del de 30 (`0x1E`).
  En la práctica el logo termina ~15 cuadros después de apretar.
- `a2` vale 1 para los logos 5, 4, 2 y 3, y **0 para el logo 1** (`3BC310.c:41-43`): el último logo no
  responde a START/CROSS. Es el equivalente al `LOGO_SKIP_NONE` de T3D.
- No hay ninguna variable de entorno del port que afecte a `3BC000`, ni un skip por timer: el contador
  `O->0x10 = 60` es la duración normal, no un temporizador de salto.

### 3.2 Películas `24BA78` (`LOGO_O`, opening, ending)

`port/eq/24BA78.c:150-173`:

```c
ret = func_002B8328(s3);
v1 = *(s32 *)(D_003B0B00 + 0x134);
if ((u32)(ret - 3) < 2) { s4 = 2; }   /* fin o error del reproductor */
if ((v1 & 8) != 0) { s4 = 2; }        /* START */
...
vnew = s2 + 8;
...
if (s4 == 2) { s2 = vnew; }
```

`s2` arranca en `0x80` (`:61`) y el bucle corta cuando `s2 >= 0x91` (`:158`): con START son **3 pasadas**
(0x80 → 0x88 → 0x90 → 0x98) y sale. Es el skip nativo del juego, no del port. Ojo: en las películas el
único botón es **START** (bit `0x8`); **CROSS no las corta**.

### 3.3 `BT2_SKIP_MOVIES` (lo único automático que hay hoy)

`port/full/plat_movie.c:14` y `:219-223`:

```c
void func_002B6E50(u32 p, s32 file) {   /* mwPlyStart(ply, name) */
    (void)p;
    close_movie();
    if (getenv("BT2_SKIP_MOVIES") || !file || !open_movie(...)) { M.open = 1; close_movie(); }
}
```

Con la película “cerrada”, `mwPlyGetStat` devuelve **3** de inmediato (`plat_movie.c:288`) y `24BA78`
hace el ramp de 3 pasadas. **Cubre exactamente:** `LOGO_O.SFD`, `ZS2USOP.SFD` (opening), `ZS2USED.SFD`
(ending) y cualquier otro `mwPlyStart` por nombre. **No cubre:**
- los logos quietos de `3BC000` (no pasan por `mwPly*`),
- el preview del Map Select (AFS), que va por `Port_MovieStartAfs`/`start_afs` y **no** consulta
  `BT2_SKIP_MOVIES` (`plat_movie.c:226-249`),
- la espera de pad ni el chequeo de memory card.

### 3.4 Título / intro al quedar idle

`func_003B9710` es el handler del título (`port/eq/3B9710.c:48`):

- Antes del attract: START (`0x8`) muestra el cartel y prende `0xCC |= 4` (`:86-94`); sin input el
  contador se resetea (`:95-97`) y el demo no arranca.
- Con `0xCC & 8`: UP/DOWN cambian el demo (`0x10`/`0x40`), **CROSS (`0x4000`) corta** y pone `*s2p=0`
  (`:64-70`); después `3BAFE8` devuelve 0 y `Progress_Main` va al **menú principal** (`3B7FA8.c:121-122`).
  **START no sale del attract.**
- A los `0x708` cuadros (~30 s) monta la pelea CPU vs CPU (`3B9710.c:107-190`). No es un video: es una
  batalla real.
- Después de **2** demos (`D_3876A4+0x24 >= 2`, `3B9710.c:117-120`) devuelve `*s2p=2`; `Progress_Main`
  pasa al **estado 2** y **reproduce el opening otra vez** (`3B7FA8.c:126-129` → `:133-137` →
  `m2c_24BE80.c`). Ese es el “opening al quedar idle”. Se saltea con START (por `24BA78`), pero no hay
  nada automático.

### 3.5 ¿El port tiene un botón propio para saltear películas?

No. El único atajo es el del juego: **Enter = START** en el teclado (`port/full/gs/gs_input.c:8`,
`:47` `{"start", "START", B_START, SDL_SCANCODE_RETURN, ...}`), que llega al `pressed` del pad y por eso
funciona en `LOGO_O` y en el opening. **En los logos quietos funciona sólo en 4 de 5** y como fade de
15 cuadros; el logo 1 no responde.

---

## 4. Enganche propuesto para “skip intro”

### 4.1 Idea

- Un flag global `Port_SkipIntro()` (mismo patrón que `Port_Autosave` de F3):
  `BT2_SKIP_INTRO` gana por corrida; si no está, lee el setting persistente `skip_intro` de
  `bt2_settings.txt` (default **1 = encendido**).
- Hook A: en `func_003BC310`, **después** de `func_003BBD98()` (o sea, ya hechos el pad y el chequeo de
  memory card) y antes de cargar el pack de logos. Si el flag está prendido, limpia el cuadro con
  `func_24BE18()` y vuelve. Se saltean los 5 logos, `LOGO_O` y el opening del arranque, pero se conservan
  la init de pad, la memory card y el `BtlWork_InitOnce()` que hace `Progress_Main` después.
- Hook B (recomendado para cubrir el idle): en `Progress_Main`, estado 2 (`case 1`), evitar `24BE80` si el
  flag está prendido y pasar directo al estado 1 (título). Cubre el opening que se repite después de 2
  demos sin tocar el attract.

### 4.2 Diff propuesto (NO aplicado)

**Archivo nuevo `port/full/plat_intro.c`:**

```c
/* F4 (saltar intro): los logos y el opening del arranque se pueden saltear sin tocar el flujo del juego.
   Mismo patron que plat_autosave.c (F3): BT2_SKIP_INTRO gana por corrida; si no, setting persistente
   "skip_intro" de bt2_settings.txt. Default: encendido (1); con BT2_SKIP_INTRO=0 o skip_intro=0 se ve
   la intro original. Las funciones de settings viven en port/full/gs/plat_settings_bt3.c y pueden no
   entrar en todos los enlaces: quedan weak. */
#include <stdlib.h>

int Port_Setting(const char *name, int def) __attribute__((weak));
void Port_SettingSave(const char *name, int value) __attribute__((weak));
void Port_SettingsWrite(void) __attribute__((weak));

static int sSkip = -1;

int Port_SkipIntro(void) {
    if (sSkip < 0) {
        const char *e = getenv("BT2_SKIP_INTRO");
        if (e != NULL) {
            sSkip = (*e != '0' && *e != 0);
        } else if (Port_Setting != NULL) {
            sSkip = Port_Setting("skip_intro", 1);   /* 0 = ver la intro siempre */
        } else {
            sSkip = 1;
        }
    }
    return sSkip;
}

void Port_SkipIntroSet(int on) {
    sSkip = on != 0;
    if (Port_SettingSave != NULL) {
        Port_SettingSave("skip_intro", sSkip);
        if (Port_SettingsWrite != NULL) {
            Port_SettingsWrite();
        }
    }
}
```

**Hook A — `port/eq/3BC310.c`:**

```diff
--- a/port/eq/3BC310.c
+++ b/port/eq/3BC310.c
@@ -14,6 +14,7 @@
 void func_100990(s32 arg0);
 void func_28BB60(void *arg0);
 s32 func_24BE80(void);
+int Port_SkipIntro(void);   /* F4: port/full/plat_intro.c */
 
 /* 0x003BC310: the init sequence: ... */
 s32 func_003BC310(void) {
@@ -24,6 +25,12 @@
     func_24BE18();
     func_003BBD98();
+    /* F4: pad y memory card ya inicializados; saltear logos + LOGO_O + opening. */
+    if (Port_SkipIntro()) {
+        func_24BE18();
+        return 0;
+    }
     if (D_00421388 == 0) {
         func_100D58(*(u8 **)(D_003876A4 + 4) + 7, 0, 1);
         do {
```

**Hook B — `port/eq/3B7FA8.c` (opening repetido por idle):**

```diff
--- a/port/eq/3B7FA8.c
+++ b/port/eq/3B7FA8.c
@@ -36,6 +36,7 @@
 void func_297A60(s32 a0, s32 a1);
 void func_297EC8(void);
 void func_298158(s32 a0);
+int Port_SkipIntro(void);   /* F4 */
 
 s32 func_003B7FA8(void) {
@@ -133,7 +134,9 @@
             case 1:
                 func_24BE18();
-                func_24BE80();
+                if (!Port_SkipIntro()) {
+                    func_24BE80();   /* F4: el opening que se repite al quedar idle */
+                }
                 *(s32 *)(D_3876A4 + 0x1C) = 1;
                 break;
```

**Opcional (F5, ventana de settings):** agregar un checkbox en la pestaña **Cheats** de
`port/full/gs/ui.cpp` (función `cheats_tab`, `:399`). No hace falta tocar `PortVideo` ni
`GsGpu_SetSettings`:

```diff
--- a/port/full/gs/ui.cpp
+++ b/port/full/gs/ui.cpp
@@ -13,6 +13,10 @@
 #include "imgui_impl_opengl3.h"
 #include "ui.h"
 
+/* F4 (port/full/plat_intro.c) */
+extern "C" int Port_SkipIntro(void);
+extern "C" void Port_SkipIntroSet(int on);
+
 static bool sReady, sOpen;
@@ -397,6 +401,16 @@
 }
 
 static void cheats_tab(void) {
-    extern "C" int Port_SkipIntro(void);
-    extern "C" void Port_SkipIntroSet(int on);
     ImGui::TextWrapped("Unlock everything: ...");
@@ -425,6 +439,15 @@
         ImGui::EndPopup();
     }
+    ImGui::Spacing();
+    {
+        static int skip = -1;
+        if (skip < 0) skip = Port_SkipIntro();
+        bool on = skip != 0;
+        if (ImGui::Checkbox("Skip intro (logos and opening), next start", &on)) {
+            skip = on ? 1 : 0;
+            Port_SkipIntroSet(skip);
+        }
+    }
 }
```

### 4.3 Por qué default **encendido**

- La intro completa son ~2 min (10 s de logos + 5 s de `LOGO_O` + 108 s de opening); el port está en
  etapa de prueba y se arranca muchas veces.
- El pedido es explícito y el setting es persistente: se prende una vez y queda.
- La escotilla para verla es de una línea: `BT2_SKIP_INTRO=0` (por corrida) o `skip_intro=0` en
  `bt2_settings.txt`. Si se prefiere el criterio conservador (respetar la intro en una instalación
  nueva), cambiar el `1` de `Port_Setting("skip_intro", 1)` por `0` y el fallback `sSkip = 0`; no hay
  que tocar los hooks.

### 4.4 Interacción con lo que ya existe

- `BT2_SKIP_MOVIES=1` sigue funcionando y no choca: si `skip_intro=1`, ni siquiera se llega a
  `mwPlyStart` en la intro; si `skip_intro=0`, `BT2_SKIP_MOVIES=1` sigue salteando sólo los SFD y deja
  los logos quietos.
- El flag no se guarda en el save del juego: es un setting del port (`bt2_settings.txt`), no toca el
  save de la memory card.
- No encontré un “primera vez” persistente: el juego no parece tener un flag de primera ejecución para
  la intro; el único control es este setting.

---

## 5. Riesgos: qué es seguro y qué no

### 5.1 Seguro de saltear (sólo imagen/video)

- **Los 5 logos quietos** (`3BC310.c:35-43`): el pack `D_00421388` se carga justo antes y **sólo lo usan
  `3BBEF8`/`3BC310`** (grep: no hay otro lector). No crea tareas ni recursos para el resto del juego.
- **`LOGO_O.SFD`** (`3BC310.c:39`): mismo camino que ya usa `BT2_SKIP_MOVIES`; no deja estado.
- **Opening del arranque** (`3BC310.c:47`) y **opening repetido por idle** (`3B7FA8.c:133-137`): el
  reproductor se cierra solo (`func_002B45D8` → `close_movie`) y el estado pasa al título; no hay
  recursos del juego que dependan de esas películas.
- **Música de la intro**: `func_100950(1)` arranca el stream y `func_100990(1)` espera a que termine
  (`port/eq/100950.c:9-12`, `port/eq/100990.c:9-13`). Al saltear no se arranca, así que no hay nada que
  esperar ni liberar.

### 5.2 **No** tocar / no saltear a la fuerza

- **`3BC5A8` (espera de pad)**: el bucle no sale hasta que `D_003B0B00+0x104 == 1` y
  `func_28C4B8(0) == 0` (`3BC5A8.c:25-41`). Es la garantía de que el pad esté listo; si se saltea, los
  menús pueden arrancar sin estado de pad.
- **`3BBD98` (chequeo de memory card)**: corre la máquina `3BB480` y **puede dejar** flags `0x400` y `0x800`
  en `D_003876A4+0x18` (`3BB480.c:146-147`). Esos bits se consultan después:
  `3B9710.c:76` (`& 0x808` para elegir mensaje) y `3B84B8.c:140` (para `D0/D4` del título). Además,
  `D_00421C00` es el estado de la ventana de memory card que usa el propio `3BBD98` y libera al final
  (`3BB438`). Si se saltea el chequeo, el flujo de “New Game”/crear save puede cambiar.
- **`BtlWork_InitOnce()`** (`3B7FA8.c:53`): se llama después de `3BC310`; no hay que saltearlo.
- **Título (`3BAFE8`) y menú principal (`3B4250`)**: no son intro; no tocarlos.
- **Attract (`3B9710`)**: es una batalla real (monta luchadores, reglas, `func_101A60`), no un video.
  Forzar su salto por tiempo/estado puede romper la creación de la batalla. La feature no lo necesita:
  sólo se saltea el opening que se repite después de 2 demos.

### 5.3 Riesgo del hook propuesto

- **Bajo**: el early return de `3BC310` ocurre después de toda la init (pad + card + `D_00421388` sin
  asignar). `Progress_Main` limpia el flag `0x40` y llama a `BtlWork_InitOnce()` igual. Después el
  estado 1 (título) carga su propio pack (`D_0042138C` en `3B7FA8.c:108-113`, `func_101438(0x3E1F)` en
  `:116`) y dibuja.
- **Medio si se olvida Hook A y sólo se usa Hook B**: el arranque seguiría mostrando logos y `LOGO_O`;
  no es un riesgo de crash, sólo feature incompleta.
- **Medio si se mueve el early return antes de `3BBD98`**: se pierden los flags de memory card (ver
  5.2). Por eso el diff lo pone después.
- **Medio si se toca `3BC000` en vez de `3BC310`**: cada llamada igual carga/descomprime su sección y
  hace `func_24BE18`; funcionaría, pero es más lento y deja el pack cargado. El early return es más
  limpio.

---

## 6. Qué descarté y por qué

- **Enganchar sólo `plat_movie.c` / `mwPlyStart`**: no cubre los logos quietos (`3BC000` no usa
  `mwPly*`). `BT2_SKIP_MOVIES` ya hace eso y el problema reportado sigue.
- **Contar vblanks/tiempo desde el port**: frágil y dependiente de la velocidad del renderer; el juego ya
  tiene puntos de entrada claros (`3BC310`, estado 2).
- **Parchear el C++ de `port/build/recomp/`**: no se usa (hay C nativo `OK`; `FALLBACK_AUTO.txt` no los
  lista). Sería un parche que no cambia el binario.
- **Saltear todo `3BC310` desde la primera línea**: se pierde la espera de pad y el chequeo de memory
  card; flags `0x400/0x800` y el flujo de card quedan a medias.
- **Saltear el cartel de copyright/legal**: no está en `3BC310`. En la referencia de B15
  (`staging/B15_referencia_video.md`, 10-13 s) se ve un cartel de copyright antes del título; por el
  código, lo más probable es que sea la **primera fase de `3BAFE8`** (espera de fade de hasta `0x79`
  cuadros, `3BAFE8.c:50-71`), que además carga el pack del título (`3B84B8`). No lo toqué ni lo propuse:
  no está verificado y no es lo pedido.
- **Usar `D_3876A4+0x18` bit `0x40` como “primera vez”**: ese flag es por arranque, no persistente
  (`1021E8.c:41`, `3B7FA8.c:51-54`); no sirve para un setting. Tampoco encontré en el arranque un flag
  persistente de “primera ejecución” para la intro: el único control que hay es este setting del port.

---

## 7. Lo que NO pude verificar (no inventar)

- El mapping exacto de las secciones 2 y 3 del pack de logos a “Bandai Namco” y “Spike”. El orden global
  (5/4 antes del video, 2/3/1 después) sí sale del código; los nombres salen de `PORT_LOG.md:142-143`.
- Si el cartel de copyright de la referencia es la primera fase de `3BAFE8` o parte del SFD. No extraje
  los cuadros para confirmarlo.
- Si el estado 2 (`3B7FA8.c:133`) se alcanza en el juego normal sólo por el idle de 2 demos; lo deduje de
  `3B9710.c:117-120` y `3B7FA8.c:126-129`, pero no lo vi en un log con el contador.
- El tiempo real de `3BC5A8`/`3BBD98` en el port (depende del pad y de la memory card; no lo medí).
- No ejecuté el juego ni compilé: los diffs son propuestas, no código probado.

## 8. Cómo lo probaría el usuario (sin que yo lance nada)

1. Aplicar el archivo nuevo + Hook A (mínimo). Arrancar con `BT2_SKIP_INTRO=1` y ver que se pasa de la
   init de pad/card al título sin logos ni opening.
2. Verificar que el título sigue funcionando: START → menú principal (`modo 4`), “New Game” → diálogo de
   memory card, y que el save se carga/crea igual.
3. Probar `BT2_SKIP_INTRO=0` y confirmar que la intro original sigue completa (logos + `LOGO_O` +
   opening) y que START/CROSS la corta como antes.
4. Aplicar Hook B y dejar el título idle: a los ~30 s debe montar el attract; después de 2 demos **no**
   debe repetirse el opening, debe volver al título.
5. En el log, el arranque debería mostrar el título sin las líneas `[movie]` de `LOGO_O`/`ZS2USOP` y sin
   el pack de logos; con `BT2_SKIP_INTRO=0` deberían volver.
