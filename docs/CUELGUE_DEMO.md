# Cuelgue del demo: diagnóstico 2026-10-12

Corrige la hipótesis de `docs/ESTADO.md` ("recursión infinita en `func_0028DAA8`, el BVH, desbordando la pila").
**Esa hipótesis es incorrecta.**

## Lo que está desmentido

- `ColMesh_WalkNode` (0x28DAA8) / `ColMesh_CollectNode` (0x28D990) **nunca se ejecutan** en el demo:
  `BT2_COL_TRACE=1` → `walks 0` tras 400 s.
- `ColMesh_CollectBox` (0x28DA48) tiene **0 llamadores** (callgraph.csv).
- El código recompilado de `func_002748B8` y `func_002EE350` es **correcto** (revisado a mano).
- El compilador de PS2Recomp no tiene el bug de `%lo(%gp)` que se sospechó: `lui 0x35` + `lw -0x4380` = `0x34BC80`
  correcto (`func_002EE8A8`); `lui 0x35` + `lw -0x4498` = `0x34BB68` correcto. Son accesos legítimos vía un registro
  distinto de `$gp`, igual que el original.

## Lo que sí reproduce (4 de 4 corridas, determinista)

A los ~390 s el juego hace un **`jalr` a la dirección `0x4`**:

```
[guest-branch:missing-target] kind=IndirectCall op=JALR source=0x2ef1d4 target=0x4 pc=0x4
  ra=0x2ef1dc sp=0x7ffc0 gp=0x38bdf0 a0=0x0 a1=0xc s0=0x1 v0=0x4 v1=0x34bc7c
```

Idéntico byte a byte en las 4 corridas (sched/addr3/store2/store3). Los puntos firmes:

1. El `jalr` está en `func_002EF0D8` (0x2EF1D4), que hace `return D_0034BC80(arg0)` con un chequeo
   `if (D_0034BC80 == NULL) return 0;` (`port/eq/2EF0D8.c:40-45`). `$v1 = 0x34BC7C` confirma que el
   `lui $v0,0x35` se ejecutó, o sea la lectura es de `D_0034BC80` (0x34BC80) y **su valor es 4**, no una función.

2. `sp = 0x7FFC0` (~2 M frames de 0x20 por debajo de la base ~0x01F00000): **sí hay un desbordamiento de pila
   enorme**, pero no en el BVH. La cadena recursiva que muestra el trace del runtime es:

   ```
   0x1006d8 -> 0x2ef200 -> 0x2ee350 -> 0x32eb70 -> 0x32fb28 -> 0x2ee350 -> ... (ciclo)
             ... -> 0x2ee8a8 -> 0x30a800 -> 0x30a9b0 -> 0x2ee8b8 -> 0x307968
   ```

   `func_002EE350` = consulta estado de hilo (`iReferThreadStatus`, syscall 0xCF) y si está WAIT llama
   `iWakeupThread` (0x32FB28). El ciclo `0x2EE350→0x32EB70→0x32FB28→0x2EE350` aparece en el trace pero
   `iWakeupThread` no es un punto de bloqueo, así que no es él solo quien anida la pila.

3. `func_002EF0D8` es invocada por `func_002EF200` (un simple tail-call) y ésta por `func_001006D8`. La
   reentrada viene de arriba; el `trace` del runtime no la muestra completa (se corta en ~60 entradas).

## Pendiente (lo siguiente a atacar)

1. Sacar el **trace completo del crash** (más de 60 entradas) para ver la recursión real desde arriba: falta
   un contador de profundidad en el watchdog cuando `$sp` baja de un umbral, ya implementado
   (`live.tick` detecta `$sp` bajando y vuelca la pila).
2. Identificar quién llama a `func_001006D8` (el caller más arriba) y por qué re-entra.
3. Solo después: los personajes invisibles (puede ser la misma corrupción, pero aún no verificado).

## Instrumentación nueva (port/src/, toda por variable de entorno)

| Archivo | Variable | Para qué |
|---|---|---|
| `coltrace.cpp` | `BT2_COL_TRACE=1\|2` | Recorrido del BVH de colisión, detecta ciclos (salió: nunca corre) |
| `callcount.cpp` | `BT2_CALLTRACE=0xA,0xB,...` | Contadores por función (bucle vs bloqueo) |
| `watchaddr.cpp` | `BT2_WATCH_ADDR=0x...` | Quién cambia una dirección del invitado (sondeo por tick) |
| `storewatch.cpp` | `BT2_STORE_ADDR=0x...` | PC exacto del store (página read-only + SIGSEGV) |
| `main.cpp` watchdog | `BT2_SCHED_TRACE=1` | Contexto vivo + stack dump + contadores del scheduler |
| `ee_scheduler.h/.cpp` | — | `EeScheduler::scheduleDebug()` (parche propio del runtime) |

## Notas de método

- El sondeo por tick (`watchaddr`) **no** da el PC del store (da el del tick). `storewatch` (SIGSEGV) sí, pero
  en las corridas de prueba la protección se perdió antes del store (el runtime re-mapea la RAM en identity) y
  no disparó; queda por resolver por qué.
- `ptrace_scope=1` impide adjuntar gdb a procesos que no son hijos directos: hay que lanzar bajo gdb o usar
  depuración en proceso.