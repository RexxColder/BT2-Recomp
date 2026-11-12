# Limpieza de sondas TEMP y frontera de region() — parches SIN aplicar

Generados por copia en /tmp/limpieza/work + `diff -u` contra el original (rutas `a/` `b/` relativas a la raíz).
Todos pasan `patch -p1 --dry-run` sobre el árbol actual. No se compiló nada.
Fuera de alcance (no tocados): `port/full/gs/gs_draw.c`, `gs_core.c`, `gs_input.c` (marcadores "TEMP B24" del agente principal).

Nota: `bt2_fightlog_note` ya sólo escribe con `BT2_FIGHTLOG`/`BT2_ULTRALOG`, pero los argumentos se evalúan siempre
(algunos recorren listas o llaman funciones del juego cada frame), por eso conviene quitar los de bugs cerrados.

## Parches (acción: QUITAR)

| Archivo(s) | Marcador | Bug | Riesgo |
|---|---|---|---|
| port/eq/12C468 12C9E8 12DA70 12E158 137F58 138C90 139390 139AA8 13A070 13AD28 141628 142180 1448C8 178440 181040 1E5570 1E5D00 1EDD98 1EE8B0 (.c) | TEX0TRUNC + prototipo `/* TEMP TEX0 */` | B5 cerrado | Muy bajo: sólo se borra un `if (...) log` de una línea; el store del TEX0 queda igual |
| port/eq/1F3830.c | TEMP TEX0 (TEX0ADDTEX) | B5 | Bajo: el bloque se reemplaza por `return` de la MISMA expresión |
| port/eq/224130, 235F38, 22C9B8, 21C5F8 (.c) | `B3 BIT2` / `B3 MARCA-2C` | B3 cerrado | Muy bajo (línea de log suelta; el `|= 2` / `=1` quedan) |
| port/eq/23BDA8.c | TEMP B3 (TECNICA-ESTADO, watch 2C, TECNICA-PASOS) | B3 | Bajo: se dejan de llamar func_0023D4E0/208738/2411E0/241718 sólo-lectura del log. Revisar: el bloque llamaba funciones del juego; si alguna tuviera efecto lateral cambia el comportamiento (son consultas). Puede quedar `gg` sin usar (warning). Se conserva ELIGE-ATAQUE (no marcado TEMP) |
| port/eq/148670, 191600, 1513D0 (.c) | `B10 log temporal` | B10 cerrado | Muy bajo. En 1513D0 se conserva BEAMPOS |
| port/eq/1F49E8.c | B10 TAREA-ID | B10 | Bajo: el envoltorio queda `return func_001F49E8_real(...)` |
| port/eq/1A5EF0, 1A55E0, 1BA518, 1BAD80 (.c) | TEMP chispas / PTCL-QUAD / PTCL-COLOR / CHISPA-INIT | B5 | Muy bajo |
| src/battle/xc_1BC230.c | TEMP chispas (contadores nCall/nHid/nView/nOk + PTCL3-DRAW) | B5 | Bajo: se quitan contadores estáticos; los `return` siguen igual |
| port/eq/1899F0.c | CHKREG (RB/RB13: asm x86 que lee rbx/r13 y escribe a stderr SIN variable de entorno) | B14 (diagnóstico) | Bajo; además quita asm no portable. Se conservan los logs BEAM de ese archivo |
| port/tools/link_full.py | frontera de region() | — | Nulo en el binario (ver abajo) |

## Clasificados aparte (SIN parche)

| Archivo | Marcador | Decisión | Motivo |
|---|---|---|---|
| port/full/temp_stubs.c | `#define TEMP __attribute__((weak))` | CONSERVAR (código funcional) | Son stubs débiles de funciones del juego sin C (lista en TEMP_STUBS.txt); desaparecen solos cuando exista el C. Quitarlos rompe el enlace |
| port/full/mem.c:229-237 | `TEMP-STUB` (full_stub_game) | CONSERVAR | Es el stub que devuelve 0 para funciones del juego sin C; el mensaje sale una vez por función. Funcional |
| port/full/mem.c:66-110 | TEMP (B3) watchpoint `bt2_watch_byte` + on_trap/on_segv | CONSERVAR como herramienta (opt-in) | Sólo se arma si alguien llama bt2_watch_byte; tras el parche de 23BDA8 no lo llama nadie. Sugerido: quitar la palabra TEMP y mover a plat_trace.c. Ojo: on_segv es el manejador general de SIGSEGV, no borrar a ciegas |
| port/eq/188218, 188850, 1899F0, 18A2C8, 18A9C0, 18AE98, 188D68, 18BBC0 (.c) | BEAM | CONSERVAR por ahora | B14 sigue PARCIAL (falta el cuerpo largo del rayo). Ya van por FIGHTLOG. Quitar al cerrar B14 (algunos recorren la lista de nodos cada frame aunque el log esté apagado) |
| port/eq/1513D0.c:224, 187EC0.c:43 | BEAMPOS | CONSERVAR (B14) | Ídem |
| port/eq/100D58.c:33 | TEMP / B12 | CONSERVAR, renombrar comentario | B12 "no reapareció, sin verificar". Sólo imprime con índice basura (>=0x10000), una vez por valor: es un aviso de error barato |
| port/full/gs/gs_gl.c:850,1042 | TEMP (impact square hunt) | DEJAR detrás de env (ya lo está: BT3_PROBE_HIT / BT3_GS_DUMP=hit) | B5 cerrado → candidato a quitar, pero gs_gl.c tiene cambios sin commitear del agente principal (git status M) y depende de gGsDumpOnHit de plat_fightlog.c; hacerlo después de su commit |
| port/full/gs/gs_vu1.c:793 | B19 | CONSERVAR | Ya detrás de BT2_VULOG |
| src/sys/mem_read_1957D8.c, port/eq/14B078/1535A0/165488/165F60/29EE10/10EBF0/3FD610 | "B14/B17/B18/B19" en comentarios | CONSERVAR | Son comentarios que explican arreglos, no sondas |
| src/battle/xa_*.c | `ATTEMPT` | Fuera de alcance | Falso positivo del grep (`#if 0` de intentos de matching) |
| port/eq/2F08D8.c, 23E520.c | `B18`, `B10` | Falso positivo | Etiqueta de goto / nombre de tabla |
| uplog, VULOG, PADLOG, STATELOG, FIGHTLOG | — | CONSERVAR | Diagnóstico del modo debug |

## Orden sugerido (de a uno, con backup y prueba)

Para cada parche: `cp archivo archivo.bak` (o `git stash`/commit previo), `patch -p1 < staging/limpieza/parches/X.patch`,
compilar, probar, y si falla `patch -R -p1 < ...` o restaurar el .bak.

1. `00_region_port_tools_link_full.py.patch` — sólo cambia etiquetas del informe; correr link_full.py y comparar que el
   código generado (stubs, relleno) es idéntico byte a byte (`diff` del .c generado antes/después).
2. Los 19 TEX0TRUNC + `port_eq_1F3830.c.patch` — prueba: una pelea con golpes/chispas (texturas de efectos OK).
3. B5 chispas: 1A5EF0, 1A55E0, 1BA518, 1BAD80, `src_battle_xc_1BC230.c` — prueba: golpes y chispas visibles.
4. B10: 148670, 191600, 1513D0, 1F49E8 — prueba: Gekiretsu Madan de Gohan niño (varios disparos) y un rayo.
5. B3: 224130, 235F38, 22C9B8, 21C5F8, 23BDA8 — prueba: dos o tres especiales seguidos (B3/B9).
6. `port_eq_1899F0.c.patch` (CHKREG) — prueba: un Ultimate de rayo (B14).
Después de cada grupo, con `BT2_FIGHTLOG=1` revisar que el log sigue saliendo (ELIGE-ATAQUE, BEAM, IMPACTO).

## Frontera de region() en link_full.py

Hoy `region()` etiqueta todo 0x300000–0x33B5F8 como "SDK", pero el mismo archivo ya usa `GAME_END = 0x30C7B8`
como corte juego/SDK para decidir el stub (`full_stub_game` devuelve 0 vs `full_stub` que corta) y el relleno.
Evidencia de que 0x300000–0x30C7B8 es juego (+CRI):
- `scratch/m2c_sweep/00303B48.s`: `glabel Hud_Term` (contador D_003605A8, pone D_003605A0=0): lógica del HUD.
- `config/symbols/bt3_data.txt` / `bt3_funcs.txt`: Hud_Term 0x303B48, PauseMenu_Term 0x303BB0, BtlSeq_Term 0x303BC8,
  BtlGame_Term 0x303C48, BtlPause_Term 0x303C78, BtlEvent_SetWaitOff 0x306E08, BtlFacade_BeginWait 0x306EF8,
  StgModel_InitStage 0x307C68, StgFx_Reset 0x307C98.
- src/ ya tiene ~150 archivos decompilados del juego en ese rango (p. ej. `src/battle/btl_tech_b_303C48.c`,
  `btl_facade_306EF8.c`, `xl_301040.c` … `xl_30C218.c`).
- Al principio del rango hay middleware CRI (ADXF_*, LSC_ExecServer según build_port/bt3_names.csv): CRI va con el juego
  según el comentario de GAME_END ("C del juego + CRI").
- El primer símbolo del SDK/libm por encima es `atanf` = 0x30CF58 (`config/symbols/sdk.txt`).

Qué cambia: el parche sube `GAME_END` a nivel de módulo y `region()` devuelve "juego+CRI 300000-30C7B8" y
"SDK 30C7B8-33B5F8". `region()` sólo se usa en el informe (`stubs_ref_por_region`, `absolutos_por_region`,
`alias_por_region`, `relleno_por_region` y la lista FALLBACK_AUTO.txt). El enlace, los stubs y el relleno NO cambian
(ya usaban GAME_END); cambian los conteos del informe, que ahora dejan de inflar el "SDK" con funciones del juego.
