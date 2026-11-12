# F8 — el menú vuelve en inglés al recargarse: el `ptid` sale de `gGfxLens.tex`, no de la tabla de particiones

Fecha: 2026-11-11. **Solo lectura**: no se compiló, no se ejecutó el port, no se tocó
`/mnt/datos2/BT2-Decomp` ni ningún archivo del proyecto (salvo este informe). Todo el análisis se hizo sobre
el binario ya instalado (`BT2-test/bin/bt2`, md5 `7028da6b85e7a3e1708b5c334d774418`, idéntico a
`BT2-Recomp/port/build/full/bt2full`), el log de la corrida `BT2-test/logs/vivo/20261111-194141.log` y su volcado
de RAM `20261111-194141_ram1_f12863.bin`.

---

## 0. Resumen

- **No se pierde el idioma ni se cierra la partición EU.** Lo que se rompe es el **primer argumento (`ptid`)** de
  los cargadores de archivos del menú: después de inicializar el 3D de un escenario/duelo, `func_00100D58` (y otras
  3 funciones) leen el `ptid` de la dirección equivocada, `0x388F20`.
- `0x388F20` **no es** una tabla de particiones: es `gGfxLens + 0x180` = el campo `GfxTexFile *tex` de
  `GfxLensWork` (`include/sys/gfxm_b.h:70`). Cuando arranca el 3D de escenario (`func_002AB878` → `func_00280CD8`
  → `func_00283880`, GfxLens_Init), ahí queda un puntero a textura: en esta corrida **`0x83A600`**.
- Entonces el menú pide, por ejemplo, `ptid=8627712 (0x83A600), flid=0x545`. El remapeo F8 de `func_002EB9B0` sólo
  actúa si `ptid == 0` (`plat_file.c:120`); como no lo es, no remapea. Además `sPart[ptid & 3]` (`plat_file.c:133`)
  da `sPart[0]` porque `0x83A600 & 3 == 0`, así que **lee silenciosamente la partición USA**: menú en inglés.
- El ASM original lee **`D_00387F20`** (`gp - 0x3ED0`, con `_gp = 0x38BDF0` → `0x387F20`), la tabla que el juego
  inicializa a `[0, 1]`. El C del port usa un símbolo inventado, `D_00388F20 = 0x388F20`, que cae justo en
  `gGfxLens.tex`.
- **Arreglo**: cambiar `D_00388F20` por `D_00387F20` en 4 archivos (`100D58.c`, `1009E0.c`, `1011A0.c`,
  `1018E8.c`). Diff al final, sin aplicar.

---

## 1. Causa probable (cadena completa)

### 1.1 El `ptid` que llega al HLE

El binario instalado hace, en `func_00100D58`:

```
40153df7:   8b 3c 85 20 8f 38 00    mov    0x388f20(,%rax,4),%edi
40153dfe:   e8 de 7b fb ff          call   func_002EB9B0
```

(`objdump -d --disassemble=func_00100D58 BT2-Recomp/port/build/full/bt2full`)

Es decir, lee la **tabla de particiones desde la dirección absoluta `0x388F20`** y se la pasa como `ptid` a
`ADXF_OpenAfs` (`func_002EB9B0`).

### 1.2 Qué hay realmente en `0x388F20`

- `0x388F20` cae dentro del objeto `D_00388DC4` (0x388DC4, tamaño 0x16C), pero el objeto real que lo contiene es
  **`gGfxLens` (0x388DA0) + 0x180**:
  - `include/sys/gfxm_b.h:68-72`:
    ```c
    typedef struct GfxLensWork {
        /* 0x000 */ GfxLens slot[8];
        /* 0x180 */ GfxTexFile *tex; /* texture file of the lens shape ... */
        /* 0x184 */ s32 unk184[3];
    } GfxLensWork; /* 0x190 */
    ```
  - `readelf -s` del ELF original: `gGfxLens = 0x00388DA0`. `0x388DA0 + 0x180 = 0x388F20`. ✔
- Lo escribe `func_00283880` (GfxLens_Init), `port/eq/283880.c:15`:
  ```c
  *(u8 **)(gGfxLens + 0x180) = temp_v1_2;   /* puntero a GfxTexFile */
  ```
- `func_00283880` lo llama `func_00280CD8` (`src/auto/m2c_280CD8.c:39`), que es la inicialización de gráficos;
  `func_00280CD8` se llama desde `func_002AB878` (inicialización del 3D de escenario/batalla,
  `port/eq/2AB878.c:54`) y desde `func_001050A8` (3D de menú, `port/eq/3DCAE0.c:109`).
- En la corrida del usuario el disparador fue `func_002AB878`: el log muestra
  `[file] open (0,1895) off=0xAC86000 size=0x337D0` en el vblank 5326 (0x767 es justo uno de los recursos que
  carga `func_002AB878`), y **dos líneas de vblank después** aparecen los primeros `open` con `ptid=0x83A600`.

En el volcado de RAM de esa corrida:

```
20261111-194141_ram1_f12863.bin
0x388F20: 00 a6 83 00   -> 0x83A600
```

y `0x83A600` es un `GfxTexFile` plausible: en `+0x10` tiene `0x83A620`, que es el campo `entries` del header
(`GfxTexFile { u8 unk00[0x10]; GfxTexEntry *entries; }`, `include/sys/gfxm_b.h:24-29`).

### 1.3 Por qué eso salta el remapeo F8

`port/full/plat_file.c`:

```c
120:    if (ptid == 0 && eu_cargar()) {
121:        int lang = eu_lang(Port_Idioma());
...
129:            ptid = 2;
130:            flid = id;
133:    p = &sPart[ptid & 3];
```

- Con `ptid = 0x83A600` la condición `ptid == 0` es falsa → **no remapea**.
- `0x83A600 & 3 == 0` → `sPart[0]` = **ZS2US_1.AFS**. El `flid` no se toca, así que abre el **recurso USA** del
  mismo id. El juego no falla: simplemente muestra el menú USA.

### 1.4 El ASM original (la prueba de que el símbolo del C está mal)

`_gp = 0x0038BDF0` (símbolo del ELF). `gp - 0x3ED0 = 0x387F20` = `D_00387F20`, la tabla que el juego deja en
`[0, 1]` (`port/eq/100708.c:57`, `port/eq/100950.c:9`; el volcado de RAM muestra `0x387F20 = 0, 1`).

El ASM de las 4 funciones lee siempre `-0x3ED0($gp)`:

| Función | Línea del ASM | Instrucción |
|---|---|---|
| `func_00100D58` | `asm/cod/000708.s:525` (0xDD4) | `lw a0, -0x3ED0(a0)` |
| `func_001009E0` | `asm/cod/000708.s:246` (0xA20) | `lw a0, -0x3ED0(a0)` |
| `func_001011A0` | `asm/cod/000ED0.s:249` (0x11D4) | `lw a0, -0x3ED0(a0)` |
| `func_001018E8` | `asm/cod/0018E8.s:57` (0x197C) | `lw a1, -0x3ED0(a1)` |

El C, en cambio, usa `D_00388F20` (`0x388F20`) en:

- `port/eq/100D58.c:13` y `:33`
- `port/eq/1009E0.c:5` y `:16`
- `port/eq/1011A0.c:6` y `:15`
- `port/eq/1018E8.c:7` y `:19` (curiosamente con el comentario *"gp-relative table at gp - 0x3ED0"* en la línea
  18, pero con el símbolo equivocado en la 19)

`D_00388F20` no existe en el ELF original; lo define el linker del port (`port/build/full/link.ld:5235:
D_00388F20 = 0x00388F20`). El símbolo correcto ya está definido en `link.ld:5214: D_00387F20 = 0x00387F20`.

---

## 2. Evidencia en el log (corrida `20261111-194141`)

### 2.1 Al arrancar, con `D_00388F20 == 0`, el menú sale de la EU

```
98:  [file] particion 2 = gamedata/DATA/ZS2EU_1.AFS (13197 archivos)
99:  F8 EU remap 0:1370 -> 2:3606        # 0x55A -> 0xE16 (LOAD_SP.DBT)
100: [file] open (2,3606) off=0x572B800 size=0x64A0
102: F8 EU remap 0:1348 -> 2:3584        # 0x544 -> 0xE00 (bloque ES)
103: [file] open (2,3584) off=0x3034800 size=0x16C0
```

Y al recargar el menú principal, todavía sano:

```
110538: F8 EU remap 0:1349 -> 2:3585    # 0x545 -> 0xE01
110539: [file] open (2,3585) off=0x3036000 size=0x1D4AC0
216167: F8 EU remap 0:1349 -> 2:3585
216168: [file] open (2,3585) off=0x3036000 size=0x1D4AC0
```

`0x3036000/0x1D4AC0` es la entrada **EU 0xE01** (menú ES). La USA `0x545` es `0x4C1800/0x1D4D80` (tabla del
`ZS2US_1.AFS`). Se ve que son recursos distintos.

### 2.2 El 3D del duelo inicializa GfxLens y a partir de ahí el `ptid` es basura

```
255597: ESTADO vblank 5240 fase MENU modo 8 (duelo?) flags D08
256342: [file] open (0,1895) off=0xAC86000 size=0x337D0      # 0x767, recurso de func_002AB878 (3D de escenario)
256351: ESTADO vblank 5328 fase MENU modo 7 (duelo?) flags D0A
...
271852: [file] open (8627712,1365) off=0x2326000 size=0x116700   # ptid = 0x83A600, flid 0x555
278413: [file] open (8627712,1362) off=0x1F03800 size=0xDAF00    # 0x552
333702: [file] open (8627712,1364) off=0x2217800 size=0x10E7B0   # 0x554
409600: [file] open (8627712,1363) off=0x1FDE800 size=0x238B40   # 0x553
427571: [file] open (8627712,1349) off=0x4C1800 size=0x1D4D80    # 0x545, ¡USA!
518706: [file] open (8627712,1356) off=0x115A000 size=0x3F12C0   # 0x54C
```

`8627712 = 0x83A600`. Ninguna de esas líneas tiene su `F8 EU remap` correspondiente. La de la línea 427571
(`0x545`) es exactamente el recurso del menú principal, y su offset/tamaño (`0x4C1800/0x1D4D80`) son los de la
**USA**, no los de la EU (`0x3036000/0x1D4AC0`). Es el "vuelve en inglés" del reporte.

### 2.3 Volcado de RAM

```
0x387F20: 00 00 00 00 01 00 00 00   -> D_00387F20 = [0, 1]  (tabla correcta)
0x388F20: 00 a6 83 00 ...           -> 0x83A600              (gGfxLens.tex)
```

`0x83A600` aparece **una sola vez** en los 32 MB, en `0x388F20`.

### 2.4 Lo que NO se ve en el log

- No hay ningún `ADXF_LoadPartitionNw(2)` posterior ni `particion 2` recargada: `sPart[2]` sigue viva toda la
  corrida.
- Después de la "corrupción" siguen apareciendo remapeos por el camino `ptid == 0`, p. ej.
  `264273: F8 EU remap 0:793 -> 2:1346` (historia). O sea, `Port_Idioma()` sigue devolviendo 1.

---

## 3. Hipótesis evaluadas y descartadas

| Hipótesis | Veredicto | Evidencia |
|---|---|---|
| **(a)** Al volver se reusa un buffer/handle del arranque con datos USA | **Descartada** | Cada vuelta vuelve a abrir el recurso: `open (2,3585)` en 110539/216168 y `open (0,1349)` en 427571. No es un buffer viejo: es una lectura nueva, pero de la partición equivocada. |
| **(b)** Al volver pide los menús con otro `ptid` y el remapeo sólo cubre `ptid == 0` | **Confirmada, con el matiz de que el `ptid` no es 1 sino basura** | `ptid = 8627712 = 0x83A600` (líneas 271852/427571). Sale de `0x388F20`, no de `D_00387F20`. `0x83A600 & 3 == 0` → cae en la USA. |
| **(c)** El port cierra/reutiliza la partición 2 o las ranuras de `sFile` | **Descartada** | No hay recarga de la partición 2 en todo el log; `sPart[2]` sigue abierta y los remapeos por `ptid == 0` siguen funcionando después del fallo (`264273`). Si estuviera cerrada, `ADXF_OpenAfs` devolvería 0 (error), no datos USA. |
| **(d)** Los ids de menú al volver están fuera del rango remapeado | **Descartada** | Los ids que fallan son `0x545, 0x54C, 0x552, 0x553, 0x554, 0x555`, todos dentro de `0x544..0x55A`. |
| **(e)** `Port_Idioma()` se relee y vuelve a 0 | **Descartada** | `BT2_IDIOMA=1`/`textos/bt2_texto.es.txt` (línea 127 del log), `sIdioma` cacheado (`plat_text.c:104-131`), y los remapeos de historia/menú con `ptid == 0` siguen ocurriendo después del fallo (p. ej. línea 264273). No hay `Port_Setting` que lo pise. |

---

## 4. Sonda exacta (una corrida)

Hay dos niveles; con el primero no hace falta recompilar nada.

### 4.1 Sonda sin recompilar (recomendada para confirmar)

```bash
cd /home/rexx/Escritorio/BT2-Port/BT2-test
BT2_IDIOMA=1 BT2_FILELOG=1 ./jugar.sh          # o como lo lances habitualmente
```

El `FLOG` de `plat_file.c` ya imprime **todos** los `ADXF_OpenAfs`:

```
[file] open (ptid,flid) off=... size=...
```

**Qué hacer en el juego**: boot → menú principal (tiene que verse ES) → entrar a **Duelo** (o cualquier modo que
cargue un escenario/3D; el selector de personajes ya lo dispara) → volver al menú principal (se ve EN) → cerrar.

**Qué mirar**:

1. Al principio: `F8 EU remap 0:1349 -> 2:3585` y `open (2,3585) off=0x3036000 size=0x1D4AC0`.
2. Después de entrar al duelo: `open (8627712,1349) off=0x4C1800 size=0x1D4D80` **sin** `F8 EU remap`.
3. Que `8627712 = 0x83A600` y que `0x4C1800` es el offset de la `0x545` de la USA.

Si aparece eso, la causa de este informe queda confirmada en una sola corrida.

### 4.2 Sonda instrumentada (para dejar el `ptid` y el escritor en el log)

Si se quiere atar todo con nombres y llamadores, agregar temporalmente (marcado `TEMP F8`):

**a) En `port/eq/100D58.c`, rama `D_00387688 == 0` (después de calcular `t`):**

```c
extern s32 D_00387F20[];   /* ya está en el archivo si se aplica el fix */
fprintf(stderr, "TEMP F8 100D58 id=%d t=%d p87=[%d,%d] p88=[%d,%d] ret=%p\n",
        arg0, t, D_00387F20[0], D_00387F20[1], D_00388F20[0], D_00388F20[1],
        __builtin_return_address(0));
```

(Repetir el mismo log, si se quiere, en `1009E0`, `1011A0` y `1018E8`; los cuatro tienen el mismo typo.)

**b) En `port/full/plat_file.c`, `func_002EB9B0`, sin tope para el rango de menú:**

```c
if (flid >= 0x540 && flid <= 0x560) {
    fprintf(stderr, "TEMP F8 open ptid=%d flid=%d idioma=%d -> %d:%d part=%s off=0x%X size=0x%X ret=%p\n",
            ptid_original, flid_original, Port_Idioma(),
            (int)ptid, (int)flid,
            (ptid >= 0 && ptid < 4 && sPart[ptid & 3].fp) ? sPart[ptid & 3].name : "?",
            (ptid >= 0 && ptid < 4 && sPart[ptid & 3].fp && (u32)flid < sPart[ptid & 3].count)
                ? sPart[ptid & 3].tab[flid * 2] : 0,
            (ptid >= 0 && ptid < 4 && sPart[ptid & 3].fp && (u32)flid < sPart[ptid & 3].count)
                ? sPart[ptid & 3].tab[flid * 2 + 1] : 0,
            __builtin_return_address(0));
}
```

(Guardar `ptid_original`/`flid_original` antes del remapeo; el `ret` es una dirección del host: si hace falta
simbolizarla, `addr2line -f -e BT2-test/bin/bt2 <ret>`; el `call` a `func_002EB9B0` es directo desde el C traducido,
así que `ret` cae dentro de `func_00100D58` o `func_00100CB8`, que es lo que interesa distinguir.)

**c) Opcional: quién escribe `0x388F20`.** Ya sabemos por lectura que es `func_00283880` (GfxLens_Init), pero para
confirmarlo en vivo alcanza con vigilar el **byte 0x388F21** (el byte 0 no cambia: `00 a6 83 00`):

- con gdb: `watch *(int*)0x388F20` después de que el port mapee la RAM (break en `main` y seguir hasta después de
  `map_at`), o
- con la herramienta del port: llamar una vez `bt2_watch_byte(0x388F21);` al arrancar (`port/full/mem.c:74`), que
  loguea `rip` y nombre de función del que escribe.

**Qué hacer en el juego**: lo mismo que 4.1 (boot → menú ES → duelo → volver → menú EN).

**Criterio de decisión**:

- Antes del duelo: `p87=[0,1]`, `p88=[0,0]`, y `open` con `ptid=0` + remapeo.
- Después del duelo: `p88=[0x83A600,0]`, `p87=[0,1]`, `open` con `ptid=0x83A600` y sin remapeo.
- Si en cambio `p87` también cambiara o `p88` quedara en 0, habría que revisar otra cosa (no es lo que muestra el
  volcado de RAM de esta corrida).

---

## 5. Fix mínimo (NO aplicado)

El arreglo es **un solo cambio conceptual**: usar el símbolo que dice el ASM (`D_00387F20`, `0x387F20`) en lugar
del inventado `D_00388F20` (`0x388F20`). El mínimo para F8 es `100D58.c` (es el cargador asíncrono de los menús);
los otros tres son el mismo typo, verificado contra el ASM, y conviene corregirlos en el mismo paso para no dejar
la misma bomba en `func_001009E0`, `func_001011A0` y `func_001018E8` (esta última pasa el `ptid` a
`func_002F7040`, o sea también a la carga por id).

```diff
--- a/port/eq/100D58.c
+++ b/port/eq/100D58.c
@@
-extern s32 D_00388F20[];
+extern s32 D_00387F20[];
@@
-        D_0038768C = func_002EB9B0(D_00388F20[t ? 0 : 1], val, arg2, arg0);
+        D_0038768C = func_002EB9B0(D_00387F20[t ? 0 : 1], val, arg2, arg0);
```

```diff
--- a/port/eq/1009E0.c
+++ b/port/eq/1009E0.c
@@
-extern s32 D_00388F20[];
+extern s32 D_00387F20[];
@@
-        if (func_002EAFA8(D_00388F20[arg0]) == 3) {
+        if (func_002EAFA8(D_00387F20[arg0]) == 3) {
```

```diff
--- a/port/eq/1011A0.c
+++ b/port/eq/1011A0.c
@@
-extern s32 D_00388F20[] __attribute__((section(".data")));
+extern s32 D_00387F20[];
@@
-        r = func_002EB9B0(D_00388F20[s1 / 4], s2);
+        r = func_002EB9B0(D_00387F20[s1 / 4], s2);
```

```diff
--- a/port/eq/1018E8.c
+++ b/port/eq/1018E8.c
@@
-extern s32 D_00388F20[];
+extern s32 D_00387F20[];
@@
-    func_002F7040(D_00387F04, *(s32 *)((u8 *)D_00388F20 + ((temp_v0 != 0) ? 0 : 4)), (temp_v0 != 0) ? arg0 : (arg0 - 0x33B2));
+    func_002F7040(D_00387F04, *(s32 *)((u8 *)D_00387F20 + ((temp_v0 != 0) ? 0 : 4)), (temp_v0 != 0) ? arg0 : (arg0 - 0x33B2));
```

Notas:

- `D_00387F20` ya está definido en `port/build/full/link.ld:5214`, así que no hace falta tocar el linker.
- En `1011A0.c` se saca el `__attribute__((section(".data")))` porque `D_00387F20` es `.cod_bss` (BSS del juego);
  igual el símbolo es absoluto y el atributo sólo confunde. Si se prefiere el cambio mínimo absoluto, se puede
  dejar el atributo: no cambia la dirección.
- **No** cambiar `D_00387F20[0/1]` por otra cosa: el juego los deja en `0` y `1` (`100708.c:57`,
  `100950.c:9`, y el volcado de RAM lo confirma).
- **No** parchear `func_002EB9B0` con `if ((ptid & 3) == 0)` como "contención": taparía el síntoma del menú, pero
  dejaría a los cargadores pidiendo la partición equivocada para los ids `>= 0x33B2` (que deberían ir a la
  partición 1). La causa es el símbolo, no el HLE.

Comando de build cuando se aplique (según `AGENTS.md`): al tocar `port/eq` hay que recompilar los objetos
afectados y después linkear:

```bash
cd BT2-Recomp
BT2_IRFIX=1 scripts/capped.sh 8G python3 port/tools/build_full.py --jobs 2 --only 00100D58
# idem 001009E0, 001011A0, 001018E8 (o un build completo)
scripts/capped.sh 8G python3 port/tools/link_full.py
```

---

## 6. Qué queda sin verificar

- **No se compiló ni se ejecutó** el fix: la conclusión es estática (ASM original + C del port + binario ya
  instalado + log + volcado de RAM).
- **No se identificó con un watchpoint en vivo** el instante exacto en que `func_00283880` escribe `0x83A600` en
  esta corrida; la cadena `func_002AB878 → func_00280CD8 → func_00283880` es la que explica el recurso `0x767`
  abierto en el vblank 5326 y el primer `ptid` basura en el 5328, pero no se vio el write.
- **No se verificó** si el mismo símbolo equivocado está causando otros bugs latentes cuando los ids son
  `>= 0x33B2` y deberían ir a la partición 1 (p. ej. carga de modelos/escenarios después del 3D de batalla). El
  fix los corrige, pero no se midió el alcance.
- **No se verificó** que `0x83A600` sea un `GfxTexFile*` leyendo el recurso; se infiere del header
  (`+0x10 = 0x83A620`, que encaja con `GfxTexFile.entries`).
- El nombre `D_00388F20` no existe en el ELF original: lo inventó el decompilado/port. Conviene, aparte de este
  fix, revisar si hay otros símbolos `D_00388xxx` inventados que caigan dentro de `gGfxLens` o de otros objetos
  (no lo hice en este trabajo).
