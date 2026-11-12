# Piezas que faltan por escribir (no son decompilacion)

Actualizado 2026-10-21. La decompilacion a C equivalente esta completa; esto es lo que queda para un port jugable.

## 1. Videos (intro/logos/opening/ending) - IMAGEN HECHA, falta el audio
- Hecho: `port/full/plat_movie.c` (HLE de los mwPly* con libavformat/libavcodec; link_full.py enlaza -lavformat -lavcodec -lswscale -lavutil).
  Abre el .SFD (BT2_DATA/DATA), decodifica (hay cuadros P/B: por eso libavcodec y no plat_mpeg2.c de BT3), entrega cada cuadro como RGBA en
  tiras de 16 px (contrato de func_0024B980) a ritmo real (reloj de pared, 29.97/30 fps). GetStat: 1 preparando, 2 reproduciendo, 3 fin.
  Saltar con Start/Cross lo hace el propio func_0024BA78. Verificado: LOGO_O (Okratron) y ZS2USOP (opening completo) -> copyright -> titulo.
  Nota: el renderer solo presenta al terminar una cadena VIF1, y el bucle de la pelicula solo usa el canal GIF; plat_movie.c presenta con
  una cadena vacia (Port_GsVif1Chain) en cada pasada. BT2_SKIP_MOVIES=1 las omite, BT2_MOVIELOG=1 traza. ZS2USED (ending) usa el mismo camino (no probado).
- FALTA AUDIO (ADX, stream 0xC0 del SFD, 48 kHz estereo): gancho en plat_movie.c, funciones debiles que snd_adx.c debe definir (fuertes):
    `void Movie_AudioBegin(int sample_rate, int channels)`  al abrir la pelicula
    `void Movie_AudioPacket(const uint8_t *adx, int len, int64_t pts)`  cada paquete de audio del demuxer (pts en 1/90000 s). OJO: son los
        bytes del PES tal cual los entrega ffmpeg (tramas ADX sin cabecera de archivo; ffmpeg sintetiza la cabecera en extradata).
    `void Movie_AudioEnd(void)`  al cerrar (Destroy)
  El audio se pide por delante del video (se demuxa hasta el siguiente cuadro): ponerlo en cola y arrancarlo al primer paquete.

## 2. Sonido
- ADX/SE: `port/full/gs/snd_adx.c`, `snd_se.c` existen; SIF/SPU/IOP estan en stubs (los .IRX no se cargan). Hace falta decidir HLE: reproducir
  musica (ADX de AFS) y efectos (SE) directamente en el host sin emular el IOP.

## 3. Crash de la demo (attract fight)
- Ver HANDOFF.md punto 3. Hoy se corrigio un prototipo erroneo que caia mucho antes (func_0028C4B8 llamada sin argumento en 41A988.c).
  Repetir con `BT2-test/run5.sh` y comparar con `strace`.

## 4. Control del jugador / gameplay
- Entrada: teclado y mando funcionan en menus (gs_input.c). Falta probar la pelea con mando real una vez la demo/combate no crashee.

## 5. Stubs y overrides temporales
- `func_002B24C8` (descompresor) reimplementada en plat_sdk.c: el llamador `func_003BBEF8` pasaba rdx basura; revisar codegen/ptr32 y borrar el override.
- 22 `src/` con asm inline (15 auto_*, xe_293BE0, eft_t_c_1B58D0, xd_2111E8, xd_242948, randf_128580, vu0_a_c_c_128F30): no compilan para PC; hoy
  usan el fallback. Reescribirlos como eq.
- Guard temporal en `port/eq/1F3830.c` (EftVram_AddTex sin imagen).
- 9 funciones del SDK (SIF/alarm/TLB) fallan al compilar el relleno C++ (`port/build/recomp`, desde 11 oct): cubiertas por stubs.
- Textura/renderer: centrado Vulkan sin confirmar; SIGSEGV intermitente en func_002EC6B0 al arrancar bajo xvfb.

## 6. Independencia del repo antiguo
- El overlay y algunos scripts aun leen `~/Proyectos/BT2-Recomp` (en la copia: `legacy-Proyectos-BT2-Recomp`). Integrar el overlay en el master.
- Rutas absolutas de `rexx` en scripts: ver SETUP_NUEVO_SISTEMA.md.

## 7. Dudas de decompilacion aun abiertas
- 931 discrepancias de aridad entre declaraciones (barrido del agente de prototipos) sin revisar una a una; `func_00100FC8` declarada con 1 arg
  en ~20 ficheros pero definida con 4. Retornos s64 declarados s32 en llamadores (func_002E0A98, func_002C7830, func_002BEF38...). Detalle: 
  `docs/agents/b12/verif_protos.txt`, `verif_logica.txt`.


## Actualizacion 2026-10-21 (noche) - ver LEEME_PRIMERO.md seccion 4
- Videos: HECHO (imagen y audio). Audio: HECHO (musica ADX, SE del SPU2, audio de peliculas via Movie_AudioPacket). Sin ajustar por oido: BT2_SE_GAIN (25 %), reverb SPU2.
- Pendiente: radar del HUD, posiciones/glitches de combate, fps del selector de escenario, camara (arreglo sin probar), los 22 src/ con asm, integrar overlay.
