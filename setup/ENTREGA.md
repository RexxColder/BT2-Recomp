# Entrega F7 — app de setup nativa (`bt2-setup`)

**Fecha:** 2026-11-12
**Estado:** completa para Linux x86-64, con GUI SDL3 + ImGui y modo consola equivalente.
**Alcance:** todo lo nuevo está en `setup/`; no se tocó `port/full/`, `src/`, `include/`, `BT2-test/bin/`,
`gamedata/` ni el binario instalado del juego.

---

## 1. Qué hace

`setup/build/bt2-setup` instala los datos de **tu propia ISO** de Dragon Ball Z: Budokai Tenkaichi 2 (edición USA,
`SLUS_214.41`) en una carpeta (por defecto `gamedata/` al lado del port), sin montar la imagen, sin `7z`, sin
Python y sin root.

- **Ventana:** elegir ISO con diálogo o arrastrarla, ISO PAL opcional para el multiidioma, carpeta destino,
  espacio libre, validación en vivo, progreso por archivo, cancelar, retomar y botón **Jugar**.
- **Consola:** `--install`, `--check`, `--list`, `--play`; códigos de salida 0 (ok), 1 (error), 3 (el programa del
  disco no es el de la edición USA sin modificar).
- **Datos:** copia `SLUS_214.41`, `SYSTEM.CNF`, `BIN/`, `DATA/` e `IRX/` (~2,98 GB) y escribe `gamedata/.installed`
  (JSON) al final. Saltea archivos ya presentes con el mismo tamaño; cada archivo se escribe a `.part` y se
  renombra al terminar.
- **Verificación:** SHA-1 de `SLUS_214.41` (`cf01d5b2…`) y de `BIN/DBZP.BIN` (`0463612b…`), región por nombre de
  programa, archivos requeridos, espacio libre con 64 MB de margen y errores de escritura.

---

## 2. Arquitectura

```
setup/
  CMakeLists.txt          build reproducible (C11 + C++17, SDL3 por pkg-config, ImGui del repo)
  build.sh                ./build.sh [--clean] -> setup/build/bt2-setup
  src/
    iso.c / iso.h         lector ISO9660 propio
    sha1.c / sha1.h       SHA-1 propio
    install.c / install.h motor: preflight, copia, chequeo, marcador
    gui.cpp / gui.h       ventana SDL3 + ImGui (OpenGL 3.3, fallback 3.0)
    launch.cpp / launch.h lanzar el juego en segundo plano
    paths.cpp / paths.h   raíz del repo y rutas absolutas
    main.cpp              CLI + arranque de la GUI
  tests/
    make_test_iso.py      ISO9660 sintética para pruebas (no se commitea ningún dato del juego)
    smoke.sh              pruebas rápidas de consola (17 checks)
  ENTREGA.md              este documento
```

### 2.1 Lector ISO9660 (`iso.c`)

- Lee el **PVD en el sector 16**, exige `pvd[0] == 1` y `"CD001"`.
- Toma el *root directory record* de `pvd+156` y recorre los *directory records*: longitud, extent LE de 32 bits,
  tamaño, flags, longitud y nombre. Los records no cruzan sector (si `len == 0`, salta al próximo múltiplo de
  2048). Ignora `.` y `..`, corta `;1` y el punto final, y compara rutas sin distinguir mayúsculas.
- Soporta **multi-extent** (flag `0x80`): si el mismo nombre aparece en records consecutivos, acumula extents.
- **Offsets de 64 bits** (`uint64_t` + `fseeko`), porque los AFS de BT2 pasan de 1 GB.
- Profundidad máxima 8; límites de 1024 archivos, 8 extents y 512 caracteres de ruta con errores claros.
- Si el archivo no es ISO9660: mensaje que aclara que `.chd`, `.cso` y `.gz` hay que convertirlos a `.iso`.

### 2.2 Motor (`install.c`)

- `bt2_preflight()`: abre la ISO, detecta región (`SLUS_214.41` = USA; `SLES_*` = PAL; `SLPS_*`/`SLPM_*` = Japón;
  otro `SLUS_*` = otra revisión), exige los 9 archivos requeridos, calcula SHA-1 de ELF/DBZP desde la ISO, suma
  tamaños (USA + AFS PAL opcional), descuenta lo ya instalado y comprueba `statvfs`.
- `bt2_install()`: repite las validaciones, copia el ELF primero, después el resto y el AFS PAL, y escribe el
  marcador. Usa bloques de 1 MiB, informa `BT2_EV_FILE`/`BT2_EV_PROGRESS` y consulta una función de cancelación
  entre bloques. El SHA-1 del ELF/DBZP se calcula **mientras se copia**; el `.part` sólo se renombra si coincide.
- `bt2_check_dest()`: comprueba marcador, archivos requeridos y tamaños; opcionalmente vuelve a hashear ELF/DBZP y
  cuenta archivos/bytes del destino.
- `bt2_human_bytes()`: tamaños decimales (2,98 GB = 2.977.184.094 bytes), como el README.

### 2.3 GUI (`gui.cpp`)

- Ventana SDL3 + Dear ImGui del repo (`port/third_party/imgui`), OpenGL 3.3 core con fallback a 3.0. Estilo oscuro
  con acento naranja, inspirado en el menú F1 (`port/full/gs/ui.cpp`).
- Páginas: **elegir**, **instalando**, **listo para jugar**, **error**. La copia corre en un `std::thread`; los
  eventos se pasan por una cola con mutex, así la ventana nunca se bloquea.
- Diálogos con `SDL_ShowOpenFileDialog` (filtro `iso;bin;img`) y `SDL_ShowOpenFolderDialog`; drag & drop con
  `SDL_EVENT_DROP_FILE`.
- La validación se ejecuta en el hilo de UI con un debounce de 350 ms (abrir la ISO y hashear 3,2 MB es rápido).
- **Jugar**: busca `BT2_GAME`, `port/build/full/bt2full`, `../BT2-test/bin/bt2` o `BT2-test/bin/bt2`; lanza el
  proceso con `SDL_PROCESS_CREATE_BACKGROUND_BOOLEAN`, cwd = raíz del repo y `BT2_DATA`/`BT2_ELF` = destino. El
  setup se puede cerrar sin esperar al juego.

### 2.4 Modo consola (`main.cpp`)

```
bt2-setup                                      ventana
bt2-setup <iso>                                ventana con la ISO puesta
bt2-setup --install <iso> [--dest DIR] [--eu-iso ISO] [--force]
bt2-setup --check [--iso ISO] [--dest DIR]
bt2-setup --list <iso>
bt2-setup --play [--dest DIR]
bt2-setup --help | --version
```

- `--install` valida primero (preflight) y después copia; imprime un paso por línea y un porcentaje cada 10 %.
- `--check` valida la ISO si se pasa `--iso` y siempre revisa el destino (marcador, archivos, SHA-1).
- `--play` exige una instalación completa y lanza el juego igual que el botón.
- Ctrl+C corta la copia de forma ordenada (`SIGINT`/`SIGTERM`); el archivo en curso queda como `.part` y se
  descarta al reintentar.
- Códigos: **0** ok, **1** error/cancelado, **3** hash del programa distinto. `--check` devuelve 3 si el ELF/DBZP
  instalado no coincide.

### 2.5 Variables de entorno

De uso normal:

| Variable | Para qué |
|---|---|
| `BT2_SETUP_ROOT` | raíz del repo si el binario se movió de `setup/build/` |
| `BT2_SETUP_DEST` | destino inicial de la GUI |
| `BT2_SETUP_ISO` | ISO inicial (y con `BT2_SETUP_AUTOSTART=1`, instala al abrir) |
| `BT2_SETUP_EU_ISO` | ISO PAL inicial (activa el multiidioma) |
| `BT2_GAME` | binario del juego para **Jugar** (default: `port/build/full/bt2full`) |

Sólo para pruebas automáticas: `BT2_SETUP_AUTOSTART=1`, `BT2_SETUP_AUTOCANCEL_MS=N`,
`BT2_SETUP_AUTOCLOSE_MS=N`, `BT2_SETUP_AUTOPLAY=1`, `BT2_SETUP_SHOT=prefijo` (escribe `prefijo_N.ppm` en cada
cambio de página y en el frame 30).

---

## 3. Build

Requisitos: Linux x86-64, `cmake`, `ninja` o `make`, `g++`/`gcc` con C++17, SDL3 (`pkg-config --modversion sdl3`
= 3.4.18 probado) y el Dear ImGui vendorizado en `port/third_party/imgui`.

```sh
cd /ruta/al/repo
./setup/build.sh              # build incremental -> setup/build/bt2-setup
./setup/build.sh --clean      # desde cero (borra setup/build/)
```

`setup/build.sh` usa `cmake -S setup -B setup/build -DCMAKE_BUILD_TYPE=Release` y compila con `-j2` por defecto
(`JOBS=4 ./setup/build.sh` para más jobs). No hay rutas absolutas ni se toca el build del juego. El binario final
es `setup/build/bt2-setup` (~1,2 MB).

Build verificado desde cero el 2026-11-12: 0 warnings, 0 errores.

---

## 4. Pruebas

Todas las pruebas se hicieron con las ISOs reales del usuario y con una ISO sintética. **No se subió ningún dato
del juego al repo.**

### 4.1 Instalación real USA

```sh
./setup/build/bt2-setup --install \
  "/mnt/datos/tmp/bt2usa/DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).iso" \
  --dest /mnt/datos/tmp/setup_app_test
```

Resultado:

- **29 archivos**, **2.977.184.094 bytes**, 26,9 s (67 s en frío, con la ISO fuera de caché).
- `SLUS_214.41`: `cf01d5b2023843eecf7cf8ccda8bcd102dd61db7`.
- `BIN/DBZP.BIN`: `0463612b526e6e90a48636bb419720e212515ed1`.
- `.installed`:
  ```json
  {
    "version": 1,
    "elf_sha1": "cf01d5b2023843eecf7cf8ccda8bcd102dd61db7",
    "eu_afs": false,
    "files": 29,
    "bytes": 2977184094,
    "iso": "/mnt/datos/tmp/bt2usa/DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).iso",
    "installed_at": "2026-11-12T00:42:09"
  }
  ```
- `--check` posterior: `ok: 29 archivos, 2.98 GB`, `ELF: SHA-1 correcto`, `DBZP: SHA-1 correcto`, exit 0.

### 4.2 Comparación con `setup/install.py`

- `diff` de `find . -type f ! -name .installed -printf '%s %p\n' | sort` entre el destino nativo y
  `/mnt/datos/tmp/bt2install` (instalación hecha con `install.py` con la misma ISO): **listados idénticos**.
- Misma comparación nativa vs. Python sobre la ISO sintética: **listados idénticos** y mismo SHA-1 del ELF.
- `--force` sobre el destino real: 29 copiados, 0 ya estaban, mismo marcador (con `installed_at` nuevo).

### 4.3 Rechazos y casos límite

| Caso | Comando | Resultado |
|---|---|---|
| Región PAL como ISO principal | `--install "…(Europe…).iso"` | exit 1: “Esta ISO es la edición PAL (SLES_541.64)…” |
| Archivo que no es ISO | `--install /etc/hostname` | exit 1: “no es una imagen de disco ISO9660…” |
| SHA-1 alterado | ISO sintética con `--bad-elf` | exit 3, sin marcador ni `.part` |
| Instalación alterada | `--check` con 1 byte cambiado en el ELF | exit 3 |
| Archivo faltante | `--check` sin `DATA/ZS2USOP.SFD` | exit 1, lista el faltante |
| Disco lleno | tmpfs de 10 MB (`unshare -rm`) | exit 1: “No hay espacio suficiente…” |
| Falla de escritura | `ulimit -f 2048` | exit 1, sin `.part` ni marcador |
| Retomar | segunda corrida completa | 0 copiados, 29 ya estaban, 0,0 s |
| `--force` | USA+EU | 30 copiados, 73,2 s |
| Cancelar consola | SIGINT a los 2 s | exit 1, sin marcador ni `.part`, archivos completos conservados |

### 4.4 `--eu-iso` (multiidioma)

```sh
./setup/build/bt2-setup --install "…(USA).iso" \
  --eu-iso "…(Europe, Australia)….iso" --dest /mnt/datos/tmp/setup_app_test
```

Copia `DATA/ZS2EU_1.AFS`: **1.100.650.496 bytes**, SHA-1 `deb5010ae65ac4b065f8f1e87c9df0525138b050` (idéntico al
de `BT2-test/gamedata/DATA/ZS2EU_1.AFS`), en 6,5 s. El marcador queda con `"eu_afs": true` y `files: 30`.

### 4.5 GUI

- **Smoke:** `xvfb-run -a env BT2_SETUP_AUTOCLOSE_MS=3000 ./setup/build/bt2-setup` → exit 0, ventana abierta y
  cerrada sin robar el escritorio; captura PPM generada.
- **Instalación:** ISO sintética con `BT2_SETUP_AUTOSTART=1`, destino temporal → página “Listo para jugar”, 12
  archivos, marcador correcto.
- **Cancelar:** ISO USA real con `BT2_SETUP_AUTOCANCEL_MS=500` → sin marcador, sin `.part`, aviso “Instalación
  cancelada…” y archivos ya copiados conservados.
- **Play:** destino instalado + `BT2_GAME=/bin/true` + `BT2_SETUP_AUTOPLAY=1` → lanza el proceso y cierra el
  setup. Además, con un script de prueba que escribe un archivo 2 s después, el proceso **siguió vivo** tras
  cerrarse el setup (no se probó el juego real para no abrir una ventana en el escritorio del usuario).
- Capturas revisadas: pantalla inicial, validación verde con “Edición USA · 29 archivos · 2.98 GB · libre …”,
  progreso, “Listo para jugar” y error de región PAL.

### 4.6 Pruebas automáticas rápidas

```sh
BT2_TEST_PAL_ISO="/ruta/PAL.iso" ./setup/tests/smoke.sh
```

Resultado con el build final: **17 ok, 0 fallos** (listado, instalación sintética, `--check`, hash alterado,
archivo que no es ISO, retomar, `--force`, región PAL, comparación con `install.py` y archivo faltante).

### 4.7 ISO sintética

`setup/tests/make_test_iso.py` arma una ISO9660 mínima con los 12 archivos que espera el instalador, usando el
ELF/DBZP reales de una copia local (no se commitea). Sirve para probar el hash, el marcador, la GUI y la
comparación con `install.py` en segundos:

```sh
python3 setup/tests/make_test_iso.py /tmp/test.iso \
  /ruta/gamedata/SLUS_214.41 /ruta/gamedata/BIN/DBZP.BIN [--bad-elf]
```

---

## 5. Limitaciones y pendientes

- **Sólo Linux x86-64.** No se probó Windows/macOS; la GUI usa OpenGL 3.3 (o 3.0) y SDL3.
- **Sólo ISO9660 plano.** `.chd`, `.cso` y `.gz` se rechazan con el mensaje que pide convertirlos a `.iso`.
- **Sólo edición USA** (`SLUS_214.41`). La ISO PAL se usa únicamente para `--eu-iso` (`DATA/ZS2EU_1.AFS`).
- No se hashea la ISO entera (3 GB): se verifican los dos programas que importan, como en `install.py`.
- El lector soporta archivos **multi-extent** (flag `0x80`), pero las ISOs de BT2 no los usan; esa rama no se
  ejercitó con una imagen real.
- La GUI necesita servidor gráfico y OpenGL 3.3/3.0; si no, el binario avisa y queda el modo consola.
- **Play** necesita el port compilado (`port/build/full/bt2full`) o `BT2_GAME`; si no está, el botón queda
  deshabilitado con el motivo.
- El **preflight amigable dentro de `bt2full`** sigue pendiente (hoy `exit(2)` si falta el ELF y `Overlay_Load()`
  puede colgarse sin `DBZP.BIN`). Esta entrega no modifica el runtime.
- No hay integración en `.desktop` ni instalador del propio setup; se ejecuta desde el repo o se copia el binario
  con su carpeta.

---

## 6. Licencia y origen

El código nuevo es propio. La idea y el protocolo de eventos se inspiraron en Tenkaichi3Decomp (MIT), pero no se
copió su `native.cpp`/`setup.cpp`: el lector, el SHA-1, el motor y la GUI se escribieron para BT2. El repo no
incluye datos del juego; cada usuario aporta su ISO.
