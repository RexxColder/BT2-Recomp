# Montar el proyecto en un sistema nuevo

Origen: respaldo COMPLETO en `/mnt/datos/Proyectos/BT2-Port-FULL/` (ver `LEEME_PRIMERO.md` para el arbol) y copia limpia de trabajo en `/mnt/datos/Proyectos/BT2-Clean/`.
Las rutas de abajo que dicen `BT2-Port/...` equivalen a `BT2-Port-FULL/home-Escritorio/...` y `BT2-Port-FULL/home-Proyectos/...`.

## Dependencias
- Linux x86-64, ffmpeg (libavformat/libavcodec/libswscale/libavutil: los videos SFD, port/full/plat_movie.c), clang (con soporte `-m64`, `-fms-extensions`), python3 (sin paquetes extra para build_full/link_full; el `.venv` no se copio),
  ninja, SDL3, Vulkan SDK/headers y glslang (shaders `.spv` ya estan en `port/build/full/gen`), `xvfb` para pruebas sin pantalla,
  `systemd-run --user` para `scripts/capped.sh`, `rsync`.
- ISO original `DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).iso` (esta en `legacy-Proyectos-BT2-Recomp/`) y los datos extraidos
  en `BT2-test/gamedata`.

## Rutas esperadas
Los scripts usan rutas absolutas del usuario `rexx`. Opciones:
```
mkdir -p ~/Escritorio ~/Proyectos
ln -s /mnt/datos/Proyectos/BT2-Port/BT2-Recomp        ~/Escritorio/BT2-Recomp
ln -s /mnt/datos/Proyectos/BT2-Port/BT2-test          ~/Escritorio/BT2-test
ln -s /mnt/datos/Proyectos/BT2-Port/BT2-overlay-work  ~/Escritorio/BT2-overlay-work
ln -s /mnt/datos/Proyectos/BT2-Port/legacy-Proyectos-BT2-Recomp ~/Proyectos/BT2-Recomp
ln -s /mnt/datos/Proyectos/BT2-Port/ref/BT3-Decompiled  ~/Proyectos/BT3-Decompiled
ln -s /mnt/datos/Proyectos/BT2-Port/ref/Tenkaichi3Decomp ~/Proyectos/Tenkaichi3Decomp
```
(si el usuario del sistema nuevo no es `rexx`, usar `grep -rl /home/rexx scripts port/tools | head` para ver que rutas ajustar).

## Reconstruir
```
cd BT2-Recomp
BT2_IRFIX=1 scripts/capped.sh 12G python3 port/tools/build_full.py --jobs 3      # ~10 min (BT2_IRFIX=1 obligatorio: ver LEEME_PRIMERO.md sec. 8); regenera port/build/gen/full y los objetos
python3 port/tools/link_full.py                                       # -> port/build/full/bt2full
# una sola funcion eq:  python3 port/tools/build_full.py --jobs 2 --only <ADDR6> ; python3 port/tools/link_full.py
python3 scripts/fdiff.py port/eq/<ADDR6>.c                            # comprobar que un eq compila
```
Ejecutar: `BT2-test/bt2-launch.sh` (ver `BT2-test/README`/`release/LEEME.txt`). Variables: `BT3_GS=1` software, `BT3_GS=gpu BT3_GPU_API=gl|vulkan`,
`BT3_GS_VERBOSE=1`, `BT2_SKIP_MOVIES=1`, `BT3_PAD=` guion de botones. Teclas: K=X, L=O, J=cuadrado, I=triangulo, Enter=START, flechas.

## No copiado (regenerable o prescindible)
`build/`, `build_port/`, `.venv`, `scratch/ptest` (2.9G), `scratch/shots`, `scratch/gstrace.log`, objetos `.o`/`obj2`/`fallback`/`hostobj`/`gs_obj`,
`BT2-test/logs`, ISOs de otros juegos, DownhillJam/Outbreak/sonic-heroes/ps2-decomp-kit (otros proyectos).

## Build en Bazzite (2026-10-28)
El host es inmutable: el build corre en el distrobox Fedora 44 `bt2-build` (clang 22, SDL3, ffmpeg-free 8, python3-clang).
Creado con `distrobox create -n bt2-build -i registry.fedoraproject.org/fedora:44` y
`sudo dnf install clang llvm python3-clang gcc gcc-c++ SDL3-devel ffmpeg-free-devel pkgconf-pkg-config gdb`.
Fedora pone los headers de ffmpeg en `/usr/include/ffmpeg`: exportar `CPATH=/usr/include/ffmpeg` antes de `link_full.py`.
```
distrobox enter bt2-build
cd BT2-Recomp && export CPATH=/usr/include/ffmpeg BT2_IRFIX=1
scripts/capped.sh 12G python3 port/tools/build_full.py --jobs 4 && scripts/capped.sh 8G python3 port/tools/link_full.py
# build de trazas (modo debug): lo mismo con BT2_TRACE_BUILD=1 -> port/build/full_trace/bt2full (= BT2-test/bin/bt2full_debug)
```
Los binarios enlazados ahi corren en el host (ffmpeg 62 / SDL3 de Bazzite). Los anteriores (ffmpeg 63) NO.

## Agregado 2026-11-06 (antes de formatear)
- Contenedor `bt2-old` (distrobox, Fedora rawhide): además de lo anterior, `sudo dnf install xorg-x11-server-Xvfb`
  (pantalla virtual `Xvfb :99` para correr cosas sin ventana). El contenedor vive en el disco del sistema: hay que
  recrearlo.
- Accesos del escritorio: copias en `BT2-test/escritorio/BT2-debug.desktop` (-> BT2-test/jugar_debug.sh, binario
  bin/bt2full_c23) y `BT2-total.desktop` (-> jugar_total.sh, bin/bt2full_total). Copiarlos a ~/Escritorio y ajustar
  rutas si cambia el punto de montaje.
- Memoria de Claude Code: copia en `docs/claude_memory/` (original en ~/.claude/projects/<proyecto>/memory/). En el
  sistema nuevo, copiar esos .md de vuelta a la carpeta de memoria del proyecto.
- PCSX2: flatpak net.pcsx2.PCSX2 2.8.2 (crasheaba en modo automatizado); ISO de BT2 en
  /run/media/system/Datos/Rexx/Descargas/Roms/PS2/BT2/. Referencias del original ya extraídas en BT2-test/referencia/.
- Herramientas y análisis de la sesión 2026-11-06: `tools/sesion_2026-11-06/` (pcs.py = muestreo de pila con ptrace;
  volcados F9 bajo/sobre el agua; overlay de menús ov3b.bin 0x3B0000; cuadros de referencia). Los detectores de
  argumentos (kr.py, short.py, verify.py, kr_apply.py) se perdieron con la limpieza del scratchpad; su lógica está
  descrita en bugs_open.md (clase 6) para rehacerlos.

## Arch Linux (2026-11-06, tras formatear)
- Build NATIVO en el host (sin distrobox): clang 23, SDL3, ffmpeg 8 (headers en /usr/include, no hace falta CPATH),
  vulkan-headers, glslang, gdb ya estaban; se instaló `xorg-server-xvfb` y `rsync`.
- Disco de datos montado en /mnt/datos. Enlace permanente para las rutas viejas:
  `/etc/tmpfiles.d/bt2-datos.conf` = `L+ /run/media/system/Datos - - - - /mnt/datos`.
- jugar_debug.sh / jugar_total.sh corren directo (sin distrobox ni bin-viejo: Arch trae libx264). Originales en
  BT2-backups/scripts_bazzite/. Pruebas (pruebas/*.sh) sin bin-viejo.
- Accesos en ~/Escritorio: BT2-debug, BT2-total y BT2-logs (abre logs/vivo). Copias en BT2-test/escritorio/.
- Memoria de Claude restaurada en ~/.claude/projects/-mnt-datos-Proyectos-BT2-Clean-BT2-Recomp/memory/.
