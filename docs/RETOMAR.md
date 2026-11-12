# Retomar la sesión — estado al 2026-11-06 (noche, sistema nuevo Arch)

## Sistema (Arch Linux, desde 2026-11-06)
- Build NATIVO en el host, sin contenedores (clang 23, SDL3, ffmpeg 8). Disco de datos en /mnt/datos; enlace permanente
  /run/media/system/Datos -> /mnt/datos (/etc/tmpfiles.d/bt2-datos.conf) para las rutas viejas. Detalle en
  docs/SETUP_NUEVO_SISTEMA.md. Memoria de Claude en ~/.claude/projects/-mnt-datos-Proyectos-BT2-Clean-BT2-Recomp/memory/.

## Binarios (BT2-test/bin) y accesos del escritorio (~/Escritorio, copias en BT2-test/escritorio/)
- `bt2full_c23`: el que juega el usuario. Accesos: "jugar, modo debug" (jugar_debug.sh), "renderer por SOFTWARE,
  ventana" (jugar_software.sh: BT3_GS=1 BT3_SW_WINDOW=1, mismo binario), "debug TOTAL" (jugar_total.sh, bt2full_total)
  y "abrir logs y videos" (logs/vivo). Tras un arreglo: backup BT2-backups/bt2full_c23.pre_*, copiar cvc -> c23 si
  `pgrep -x bt2full_c23` está vacío, y DEJAR QUE EL USUARIO PRUEBE (no repetir pruebas largas propias).
  Últimos backups: pre_arch, pre_swwindow, pre_b24fix, pre_f9ram.
- `bt2full_total`: build instrumentado (BT2_TRACE_BUILD=1, port/build/full_trace). Detector de argumentos perdidos, no
  para jugar. `scripts/trace_sym.py TRACE.bin EXE first|text|diff`.
- Modo debug: logs en BT2-test/logs/vivo/<fecha>.{log,fight.log,mp4}; F9 = volcado del cuadro (port/build/shots/gpu_N.ppm
  + dibujos en el .log) y AHORA TAMBIÉN la RAM del juego (logs/vivo/<fecha>_ramN_fM.bin, BT2_F9_RAM).
- Escape cierra el juego en GPU (sin log); la ventana por software no cierra con Escape y loguea el cierre.

## Cómo compilar / probar
- Normal: `BT2_IRFIX=1 scripts/capped.sh 12G python3 port/tools/build_full.py --jobs 4 && scripts/capped.sh 8G python3
  port/tools/link_full.py` (solo cambios en port/full: alcanza con link_full.py). TOTAL: + BT2_TRACE_BUILD=1.
- Sin ventana: pruebas/menu.sh, pruebas/tec.sh, y pruebas/zeni.sh (llega al mapa del mundo de Dragon Adventure en ~3
  min; GS=1 software; BT2_B24/PROBE para sondas). SDL_VIDEODRIVER=offscreen, graba mp4 con libx264.
- Sonda por dibujo del backend GL: BT3_PROBE_FROM=<cuadro> (gs_gl.c probeOn) — qué dibujo cambia qué píxeles.
- Asm: main exe con objdump (tools/binutils); overlays desde la RAM (ahora con F9 + BT2_F9_RAM; ptrace_scope=1 impide
  leer /proc/<pid>/mem desde afuera).

## Estado de bugs (tabla completa en docs/bugs_open.md)
- CERRADOS hoy por el usuario: B20, B21, B23, B24 (zeni: gs_gl.c reutilizaba los parámetros del shader tras un pase
  nativo), y "de momento" B13, BL, CH, TR.
- ABIERTOS:
  - B26 diálogos del modo historia: el TEXTO sale más abajo (globo bien). Renglones cada 25 px; 3 renglones desde y 346,
    4 desde y 343 (el bloque no se centra). Código del juego: buscar la función que arma los renglones (fuente tbp 2a08).
  - B27 Maestro Roshi / B28 Piccolo: fallas en sus Ultimates (el usuario anota los síntomas).
  - B25 (A IMPLEMENTAR, decisión del usuario): niebla con FADE solo en el port de PC para disimular el salto del borde
    del mapa del mundo + en el código del juego un log que marque INICIO y FIN del salto (para quien lo porte a otra
    consola). Falta ubicar la función del salto: el usuario hará F9 antes y después de cruzar el borde (RAM en cada F9)
    para encontrar la variable de posición. Plan del agente: staging/b25_niebla/PLAN.md (el port no implementa
    FOG/FOGCOL/FGE del GS; el horizonte del original se ve como el síntoma de B21).
  - B14 Kamehameha (WIP): también es bola flotante con el renderer por SOFTWARE -> es CÓDIGO DEL JUEGO (creación /
    actualización del cuerpo del rayo). Logs BEAM/BEAMPOS siguen en c23.
  - B15 selección de mapa sin vista previa grande.
  - Arreglados sin probar: B6, B12, B16, B17, B18, B19, B22.

## PUNTO EXACTO DE CORTE (2026-11-06 noche, sin contexto): todos los remanentes en WIP
- c23 (actualizado 2026-11-06 noche, backup bt2full_c23.pre_b14nan) = B24 + F9-RAM + B14: 128C58 escala la diagonal
  (fiel al asm) y 18A2C8 acota el argumento de asin a [-1,1] (contención). El usuario lo está probando.
- 145A58.c ya restaurado (sin TEMP B25; la versión con log en BT2-backups/145A58.c.b25_con_log). La prueba borde4 (FIN=40)
  no llegó al borde: repetir con FIN=120 usando 145A58.c.b25_con_log y BT2_B25=1.
- Publicación del DECOMP: plan en repos/PLAN_DECOMP.md (decisiones pendientes: contenido v0.1, "compilable" = clang vs
  matching, repo privado). gh logueado como RexxColder; no subir sin OK.
- (anterior) c23 = arreglo B24 + herramienta F9-RAM (BT2_F9_RAM). bt2full_cvc (NO en c23) tiene además logs TEMP:
  port/eq/18A2C8.c ("BEAM 18A2C8 dir", backup .pre_nanlog) y port/eq/145A58.c (TEMP B25, backup .pre_caller) +
  watchpoint de float (mem.c BT2_WATCH_F32, plat_gs.c; backups .pre_watchf32). Primer paso al volver: quitar el TEMP
  B25 de 145A58.c (restaurar el backup) antes de pasar cvc a c23.
- B25 borde: posición del jugador = objeto 0x11BA340, vec en +0x140 (x,y,z,w). Al cruzar el borde norte Z salta
  EXACTO -300 (-1175 -> -1475) cada vez; lo escribe func_00145A58 (suma de vectores, VU0), llamada por una función aún
  NO identificada (la prueba "borde4" con el log por dirección escrita quedó corriendo: ver
  BT2-test/logs/vivo/borde4-*.log, líneas "B25:"). Prueba sin ventana: BT2-test/pruebas/borde.sh (WATCH=0x11ba488,150
  WFROM=9000 o BT2_B25=1; FIN=segundos manteniendo arriba). Con el llamador: log de INICIO/FIN del salto en el código
  del juego + niebla con FADE solo en el port.
- B14 Kamehameha: ver bugs_open.md "Cierre de sesión" (NaN de asinf del host; 128C58 escala mal la diagonal). Falta
  UN Kamehameha con bt2full_cvc para ver dir.y.
- B28 Piccolo: F9 del Ultimate en la sesión 20261106-152736 (cuadros 15383-15562 según el usuario; parecían de Goku:
  confirmar con el usuario). B27 Roshi y B26 diálogos: ver bugs_open.md.

## Publicación: DOS repos (como BT3: BT3-Decompiled = decomp CC0, Tenkaichi3Decomp = port MIT)
- Plan: docs/PLAN_PUBLICACION.md. Preparación de los agentes en staging/:
  - staging/repos/{decomp,port}: .gitignore, MANIFEST, README, LICENSE, sync_decomp.py, install.py (borrador), LEEME.md
    con 13 decisiones pendientes.
  - staging/relleno_a_c/: 37 funciones del relleno de PS2Recomp traducidas a C (31 verificadas, 6 dudosas). Integrar de
    a una: copiar a port/eq/, build --only, link.
  - staging/limpieza/: 36 parches (sondas TEMP, TEX0TRUNC, B3, B10, CHKREG, chispas) + frontera de region() en
    link_full.py. Pasan --dry-run. Aplicar de a uno con backup y prueba.
- Repos locales armados (sin commits): ver /mnt/datos/Proyectos/BT2-Clean/repos/LEEME.md.
- Bloqueos para un build limpio: link_full.py usa PS2Recomp (GPL) para el relleno de 633 funciones (el port no puede ser
  MIT hasta sacarlo); build_port/bt3_names.csv; gen_native.py llama clang fijo; game.toml con ruta absoluta; toolchain
  MIPS (tools/) sin script de descarga.

## Clases de bug (detalle en bugs_open.md)
1 compares de punteros de función; 2 TEX0 64-bit truncado; 3 buffers de pila chicos; 4 tareas liberadas; 5 memcpy corto;
6 argumentos perdidos; 7 bucles con base recargada; 8 void que devuelve valor; 9 bucle bgez con una vuelta menos;
10 tamaños = resta de etiquetas; 11 delay slot / branch-likely ignorado; 12 literal de 64 bits con un dígito de más o de
menos. Nueva de renderer (B24): estado de shader cacheado entre pases nativos y dibujos comunes.

## Referencias
BT2-test/referencia/pcsx2/ (Kamehameha, técnicas, historia), referencia/borde/, referencia/agua_f9/, videos_usuario/.

## Reglas del usuario
Español rioplatense; "borrar" = mover a BT2-backups; commit solo si lo pide; nunca tocar ~/Proyectos/BT2-Recomp; un
arreglo por vez con backup y build; copiar cvc -> c23 y que el usuario pruebe; máx. 4 agentes; los agentes trabajan en
staging/ sin tocar el árbol vivo; pruebas sin ventana solo para diagnosticar; nada debe robar el foco del escritorio.
Nada commiteado.

## 2026-11-06 (cierre): FOCO = llevar BT2-Decompiled al nivel de BT3-Decompiled (todo lo demás detenido)
- Publicado PRIVADO: https://github.com/RexxColder/BT2-Decompiled (v0.1, commit 1590240, desde repos/bt2-decomp;
  modelo BT3: src/ incl. auto, sin src/eq (C equivalente del port, guardado en BT2-backups/repo_decomp_eq/)).
- Estado matching: 9,97% del código del juego en C (scripts/progress.py), 8139 funciones en asm. BT3: 95%.
- 4 agentes en copias propias /mnt/datos/Proyectos/BT2-Clean/matching/{sys,battle,hud,menu} (áreas 100000-1A0000,
  1A0000-250000, 250000-2D0000, DBZP.BIN + verificación byte-idéntica del build). Entregas en matching/*/ENTREGA.md:
  integrarlas de a una en BT2-Recomp/src, verificar ninja byte-idéntico y recién ahí commit/push al repo privado.
- Port (B14 Kamehameha, B25 borde, B26, B27, B28, FPS a 60 Hz de vblank) en pausa.
