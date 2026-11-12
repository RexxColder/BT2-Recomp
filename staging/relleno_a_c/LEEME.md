# Relleno (PS2Recomp) -> C: las 37 funciones ejecutadas en pelea

Origen de la lista: `docs/audit/fallback_used_fight.txt` + `docs/PLAN_PUBLICACION.md` §1.3. Asm leído de
`asm/cod/*.s` (spimdisasm). Un `.c` por función, con las convenciones de `port/eq/` (`#include "common.h"`,
prototipos locales, `extern ... __attribute__((section(".data")))`, comentario `/* 0x00XXXXXX ... */`).

Comprobación hecha: cada archivo pasa por la misma cadena que `port/tools/build_full.py` (clang -E con
`native_compat.h` -> `ptr32.py` como texto del juego -> `gen_native.compile_c`), con salida en `/tmp/relleno_obj`:
**37/37 compilan**. No se pudo usar `scripts/fdiff.py`: compara bytes con ee-gcc y estos archivos son C
equivalente, no C que reproduzca los bytes. Tampoco se corrió `fn_diff.py`, que necesita PCSX2. La verificación es
a mano contra el asm: delay slots, branch-likely, signo de las comparaciones, tamaños y retornos.

Contexto: `port/full/TEMP_STUBS.txt` dice que 0x2F3xxx-0x30Axxx es **CRI/ADX y cliente IOP de sonido** (los nombres
Hud_Term / BtlPause_Term / BtlEvent_SetWaitOff son homónimos falsos de la tabla de BT3), no código de pelea.
0x325830-0x32B168 es newlib (sprintf y stdio) y 0x336E50 es un cliente RPC del SDK.

## Cómo integrar (de a una)
1. Copiar `staging/relleno_a_c/<ADDR>.c` a `port/eq/<ADDR>.c`. `build_full.py` levanta solo cualquier
   `port/eq/<ADDR6>.c` cuya dirección no defina un archivo de `src/` enlazado. Los nombres con símbolo
   (Hud_Term, std, __sinit…) se mapean por `config/symbols/*.txt`. No hace falta tocar `config/`.
2. `port/tools/build_full.py --only <ADDR>` y después `link_full.py`: la función sale sola de
   `port/full/FALLBACK_AUTO.txt` (se regenera). Las 18 que figuran en `port/full/TEMP_STUBS.txt` (300898 300DD0
   302278 303B48 303C78 304690 305440 306E08 306E68 3073E0 307590 307700 307798 3077D8 3077F0 307AF8 30A450
   30A9B0) tienen stub DÉBIL en temp_stubs.c, que el C nuevo desplaza solo. Conviene borrar la línea de la lista a mano.
3. Si una rompe: `BT2_NATIVE_SKIP` / sacar el archivo (ver docs/PORT_LOG.md).
4. Los borradores `src/battle/xl_307700.c`, `xl_3077D8.c` y `xl_3077F0.c` definen las mismas funciones, pero no
   están en el yaml (no se enlazan). `xl_307700.c` además tiene aritmética de punteros sobre `M2C_UNK` (dudosa); no usarlo.

Orden sugerido: primero las simples (bloque A), luego la cadena IOP (B) y al final libc (C).

## Tabla

| dirección | nombre | estado | qué revisar |
|---|---|---|---|
| 300898 | func_00300898 | verificada | buffer de pila de 16 B para 3007A0/3007B8 (igual que 2FFA38.c) |
| 300DD0 | func_00300DD0 | verificada | devuelve &D_0035B820; se usa como callback en 2F3408.c |
| 301A98 | func_00301A98 | dudosa | llamada por vtabla `obj->vt[+0x20](obj, 0, e+0x10)`; firma de func_00305510 (3 args: 1, D_0035D580+i*0x100, 0x100: args puestos antes del branch, revisado); los cuelgues `for(;;)` son del original |
| 302278 | func_00302278 | dudosa | callbacks 0x301EF0/0x301F50 pasados como direcciones PS2 literales (no tienen C: dependen del jmp de full_patch_range y del relleno) |
| 3025A0 | func_003025A0 | verificada | buffers send/recv/val de 16 B (sp+0, +0x10, +0x20) |
| 303B48 | Hud_Term | verificada | – |
| 303C78 | BtlPause_Term | verificada | – |
| 304690 | func_00304690 | verificada | – |
| 305440 | func_00305440 | verificada | – |
| 305568 | func_00305568 | verificada | guarda el callback como 0x003053A8 (dirección PS2, igual que el original; clase "puntero de función comparado") |
| 305878 | func_00305878 | verificada | – |
| 305C50 | func_00305C50 | verificada | copia de 8 bytes ldl/ldr hecha con dos s32 (desc alineado a 4) |
| 306560 | func_00306560 | verificada | RPC 0x22 |
| 306850 | func_00306850 | verificada | – |
| 306AA8 | func_00306AA8 | dudosa | callbacks 0x3068E0/0x306980 como direcciones PS2 literales (sin C nativo); printf con a1 basura en el original (aquí 0) |
| 306CB8 | func_00306CB8 | verificada | devuelve puntero a la entrada (u8 *) |
| 306E08 | BtlEvent_SetWaitOff | verificada | devuelve el $v0 del asm (auto_306f28.c hace `return ...`) |
| 306E68 | func_00306E68 | verificada | devuelve el retorno del callback o 0 (auto_307000.c) |
| 3070D0 | func_003070D0 | verificada | con msg NULL llama al callback sin comprobarlo (como el original) |
| 3073E0 | func_003073E0 | verificada | grupos de 0x48 = 6 huecos x 12 |
| 307590 | func_00307590 | verificada | 5 argumentos (el 5.º en $t0) |
| 307600 | func_00307600 | verificada | orden de los chequeos: arg1 >= 6 antes que arg0 >= 8 |
| 307700 | func_00307700 | verificada | – |
| 307798 | func_00307798 | verificada | – |
| 3077D8 | func_003077D8 | verificada | – |
| 3077F0 | func_003077F0 | verificada | – |
| 307808 | func_00307808 | verificada | relee fn de cada hueco después de la llamada anterior (igual que el asm) |
| 307AF8 | func_00307AF8 | verificada | – |
| 30A450 | func_0030A450 | verificada | D_003A0390 se escribe siempre, antes del contador |
| 30A9B0 | func_0030A9B0 | verificada | – |
| 325830 | func_00325830 (sprintf) | dudosa | NO es una traducción literal: usa vsprintf del host (como 2BC568.c), porque el C nativo no puede armar la va_list de la EE. Algunos llamadores (2518F0.c, 244708.c) la declaran SIN `...`: en x86-64 anda con enteros y punteros, pero no con floats. Diferencias de formato newlib/glibc (%f, %p) |
| 326980 | __sprint | verificada | sin uso desde sprintf una vez integrada 325830 |
| 326A80 | func_00326A80 (vfprintf) | dudosa | `ap` es una va_list de la EE (u32) que se pasa a `_vfprintf_r` de la EE: revisar a qué resuelve `_vfprintf_r` en el enlace |
| 32A940 | std | verificada | guarda __sread 0x32CC90, __swrite 0x32CCF8, __sseek 0x32CD78 y __sclose 0x32CDE0 como direcciones PS2 (tomadas de los bytes lui/addiu) |
| 32AB50 | __sinit | verificada | _cleanup_r = 0x32AB10, como dirección PS2 |
| 32B168 | __sfvwrite | dudosa | `fflush` se llama como **func_0032A828** (la EE), porque el nombre `fflush` es el del host (regex STDIO de link_full.py): confirmar que el enlace resuelve func_0032A828; _write se llama por puntero de 32 bits |
| 336E50 | func_00336E50 | verificada | 9.º argumento de sceSifCallRpc = 0 (en la pila del original) |

**Resumen:** 37 traducidas: 31 verificadas y 6 dudosas (301A98, 302278, 306AA8, 325830, 326A80, 32B168).

## Riesgos generales
- Las direcciones PS2 que se guardan como punteros a función (0x3053A8, 0x3068E0, 0x306980, 0x301EF0, 0x301F50,
  __sread…) dependen del `jmp` que `full_patch_range` (port/full/mem.c) escribe en cada dirección PS2. Si al
  quitar el relleno alguna de esas funciones queda sin C, el jmp va a un stub. 3068E0, 306980, 301EF0 y 301F50
  no están en la lista de ejecutadas, pero son callbacks de RPC: con el relleno apagado podrían empezar a hacer falta.
- El cliente de sonido (RPC, sceSifAllocIopHeap) ya corre hoy contra stubs plat_*. El C nativo hace las mismas
  llamadas, así que el comportamiento no debería cambiar, pero solo se va a ver probándolo en juego (sonido).
- Los `printf` (func_002EFAB8) de error del original reciben argumentos basura en a1/a2. Aquí van 0.
