# B25 — Niebla / límite de dibujado en el mapa del mundo (plan, 2026-11-06)

Análisis superficial (sin compilar ni ejecutar). Lo marcado "VERIFICAR" no se confirmó.

## Hallazgos
- Renderer del port: NO hay rastro de la niebla del GS. `grep -i fog|FGE` en port/full/gs/*.c y shaders/*
  sólo encuentra el camino de **niebla por profundidad** del juego (GfxDepthFog_Draw: ramp de profundidad a CLUT,
  PSMT8H 0x1B, `gsDepthByteIsFog` en gs_draw.c:74/537, shaders/dclut.frag). No se ven registros FOG (0x0A),
  FOGCOL (0x3D) ni PRIM.FGE (bit 5) en gs_input.c/gs_core.c, ni campo F del vértice en gs.vert/gs.frag
  (VERIFICAR en gs_input.c el decode de XYZF2/XYZF3: probablemente se descarta F).
- Juego: símbolos `GfxDepthFog_Init/Draw/BuildClut` (src/sys/gfxm_b_c284FF8.c, src/auto/perm_285A18.c =
  0x285A18) se llaman desde escenarios de batalla (src/battle/stg_c_281CA0.c, stg_c_282468.c). Para el mapa del
  mundo (overlay historia, tools/sesion_2026-11-06/ov_historia.bin / ov3b.bin) no se ubicó todavía la llamada:
  PENDIENTE buscar en el overlay `jal 0x0028xxxx` hacia GfxDepthFog_* y escrituras GIF con dirección 0x3D/0x0A.
- Referencias: original_t*.png muestran océano + horizonte con degradé celeste; port_t*.png relleno celeste plano
  con rayas verticales (mismo síntoma que B21: búfer leído con otro ancho/página). Es decir, hay DOS cosas:
  (a) el pase de niebla/horizonte que el juego ya manda probablemente se dibuja mal (rayas), y (b) faltaría FGE.

## Opciones
1. **Implementar la niebla del GS (FOG/FOGCOL/FGE)** — correcto y general.
   - gs_input.c: guardar F de XYZF2/3 y registro FOG; FOGCOL en estado; PRIM.FGE (y PRMODE con AC=0).
   - gs_draw.h/gs_draw.c: pasar f por vértice y FOGCOL por dibujo; gs.vert/vu*.vert: atributo f;
     gs.frag: `rgb = mix(fogcol, rgb, f/255.)` tras TFX y antes del alfa-test/blend. Camino software: lo mismo en gs_core.c.
   - Pro: arregla cualquier escena que use FGE. Contra: toca los 4 archivos que el agente principal está editando;
     si el mapa usa GfxDepthFog y no FGE, no cambia nada.
2. **Arreglar lo que el juego ya manda (GfxDepthFog / pase de horizonte)** — probable causa real de las rayas.
   - Volcar los dibujos del cuadro del borde (BT3_GS_VERBOSE) y comparar TBP/TBW/PSM del pase 0x1B y del copiado
     con FBW; mismo camino de investigación que B21 (gs_draw.c, dclut.frag).
   - Pro: fiel al original, resuelve también B21 si es la misma causa. Contra: depende del diagnóstico de B21.
3. **Niebla/far-clip propio del port sólo en el mapa del mundo** (parche visual).
   - Detectar modo: flag del modo historia/escena (overlay cargado = ov_historia + id de escena del mapa; VERIFICAR
     dirección de la variable de modo en ram.bin) expuesto desde port/eq o plat_*.c como `gPortWorldMapFog`.
   - En gs.frag: mezclar con un color celeste según la profundidad (Z normalizado), o descartar más allá de un Z.
   - Pro: rápido, aislado. Contra: no fiel, color/distancia a ojo, riesgo de afectar otros dibujos (HUD, cielo).

Recomendación: primero 2 (diagnóstico con volcado), en paralelo ubicar en el overlay si usa FGE; 1 si lo usa; 3 sólo
como último recurso.

## Pruebas sin ventana
- BT2-test/pruebas/zeni.sh llega al mapa del mundo: correr con GS=1 (software) y por defecto (GPU), guardar PPM del
  cuadro tras empujar al jugador al norte; comparar con referencia/borde/original_t*.png (métrica: ausencia de
  columnas repetidas + histograma de degradé vertical en la mitad superior).
- Con BT3_GS_VERBOSE, contar dibujos con FGE=1 y escrituras a FOGCOL en ese cuadro: si son 0, la opción 1 no aplica.
