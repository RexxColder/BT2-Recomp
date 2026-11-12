# F9 — Instalador desde ISO: cómo lo hace Tenkaichi3Decomp y plan para BT2

**Alcance:** sólo lectura. No se modificó ni compiló nada del proyecto. El único archivo escrito es este informe en
`staging/`.
**Fuentes:** clon de Tenkaichi3Decomp en `/tmp/opencode/t3d`, commit `20a8655` (2026-10-10, licencia MIT), y
`/home/rexx/Escritorio/BT2-Port/BT2-Recomp` + `BT2-test` del lado BT2.

---

## 0. Resumen ejecutivo

- **T3D no usa un wizard “mágico”**: en una release el usuario abre `Tenkaichi3Decomp-setup` (ventana ImGui + SDL3),
  elige su `.iso`, y el instalador nativo (`port/setup/native.cpp`) lee el ISO9660 con un lector propio de ~70 líneas,
  verifica SHA-1 de `SLUS_216.78` y `BIN/DBZP.BIN`, y descomprime los datos a `gamedata/`. En un checkout de fuentes
  el mismo trabajo lo hace `install.py` (Python stdlib + `7z` externo), mostrando el mismo protocolo de eventos `@...`.
- **No hay dependencia de libarchive ni de CDVD**: el lector ISO9660 es propio (sector 16 = PVD, `CD001`, recorre
  directorios, `extent × 2048`). En la ruta de release tampoco se usa `7z`; sólo lo usa `install.py` en la ruta de
  fuentes.
- **T3D detecta “ya instalado” con un archivo marcador vacío**: `gamedata/.installed` (`native.cpp:260, 326-329,
  748-751`). Si existe, el setup abre directo la página “Ready to play” (`setup.cpp:716-724`). Para reinstalar:
  `BT3_SETUP_ISO=<iso> ./GAME-setup` (`setup.cpp:728-733`), borrar el marcador, o `install.py --force`.
- **BT2 hoy no tiene wizard ni marcador.** El binario asume `gamedata/SLUS_214.41` (o `BT2_ELF`) y si no está hace
  `exit(2)` (`port/full/mem.c:211-216, 333`); los AFS se abren de `BT2_DATA/DATA/...` o `gamedata/DATA/...`
  (`port/full/plat_file.c:41-54`). El “install” actual es manual: `7z x -ogamedata "<iso>"` (README:24).
- **Para BT2 alcanza con copiar la estructura del disco tal cual** (`SLUS_214.41`, `BIN/DBZP.BIN`, `DATA/*.AFS`,
  `DATA/*.SFD`, `DATA/ZS2US.DIR`, `DATA/*.ALG`, `IRX/*`), ~**2,98 GB**. No hace falta partir los AFS como T3D:
  `plat_file.c` los lee directo por `fseek/fread`. El wizard mínimo se puede hacer sin dependencias nuevas: lector
  ISO9660 propio en C (o en Python stdlib) + SHA-1 + `statvfs` para espacio libre. El único riesgo real es la
  corrección del lector ISO9660 y el manejo de offsets de 64 bits.

---

## 1. Qué hace Tenkaichi3Decomp (mecanismo real, con archivo:línea)

### 1.1 Dos caminos de instalación, un mismo protocolo

T3D tiene dos instaladores porque hay dos situaciones:

1. **Checkout de fuentes:** `install.py` en la raíz del repo. Hace todo: requisitos, ISO, datos, textos, split del
   ejecutable, build y self-test (`install.py:388-430`). Necesita `7z`, compiladores, etc.
2. **Carpeta de release:** `Tenkaichi3Decomp-setup` (binario aparte) + `Tenkaichi3Decomp` + `Tenkaichi3Decomp.dat`.
   El setup **no compila nada**: `port/setup/native.cpp` lee el ISO, extrae los datos y corre el self-test
   (`native.cpp:1-11`, `port/tools/package.py:19-28`). La ventana (`port/setup/setup.cpp`) sólo orquesta y muestra
   el progreso.

Ambos caminos hablan el mismo protocolo de líneas `@step`, `@note`, `@ok`, `@skip`, `@fail`, `@missing`, `@stopped`,
`@done` (`install.py:29-36`, `native.h:2`, `setup.cpp:201-232`). Eso permite que la misma ventana muestre al script de
Python o al instalador nativo.

También hay modo consola/sin ventana: `Tenkaichi3Decomp-setup --install <iso>` imprime los eventos y sale 0 si hubo
`@done` (`setup.cpp:616-638`).

### 1.2 La UI: ImGui + SDL3, no consola

- La ventana es SDL3 + Dear ImGui, con el mismo look que el menú F1 del juego (`setup.cpp:1-6`, `style()` en
  `setup.cpp:94-118`).
- Página inicial `page_pick()` (`setup.cpp:354-380`): título, texto “This sets the game up on your computer from your
  own PlayStation 2 disc.”, campo de texto con hint *“drop the file on this window, or browse”*, botón **Browse...**
  con `SDL_ShowOpenFileDialog` y filtros `{"PS2 disc image", "iso;bin;img"}` (`setup.cpp:355, 365-369`).
- **Drag & drop** de un archivo sobre la ventana: `SDL_EVENT_DROP_FILE` (`setup.cpp:740-741`).
- Página de progreso `page_run()` (`setup.cpp:438-455`): lista de pasos con íconos (pendiente / girando / ok /
  fallado), detalle (`@note`), barra de progreso y botón Cancel que mata el proceso / pone el flag atómico.
- Página final `page_done()` (`setup.cpp:457-492`): “Ready to play”, botón **Play** que lanza el juego con
  `BT3_GS=gpu`.
- Página de error `page_failed()` (`setup.cpp:495-540`): muestra el texto de `@stopped`, una tabla de dependencias
  faltantes (`@missing name|purpose|package`) y botones **Open the log**, **Close**, **Back**.
- El detalle fino queda en `install.log` (`install.py:38-43`, `native.cpp:681-687`).

### 1.3 El lector ISO9660 propio (la pieza clave)

En release, `native.cpp` implementa un lector mínimo de ISO9660 sobre `SDL_IOStream`:

- `struct Iso` y `struct IsoFile { path, offset, size }` (`native.cpp:102-108`).
- `Iso::open()` (`native.cpp:152-166`):
  - abre el archivo con `SDL_IOFromFile(path, "rb")`;
  - lee el **sector 16** (2048 bytes) y exige `pvd[0] == 1` y `memcmp(pvd+1, "CD001", 5) == 0`;
  - si no, error explícito: *“This file is not a disc image (.iso). Compressed images (.chd, .cso, .gz) have to be
    converted to .iso first.”* (`native.cpp:161`);
  - toma el *root directory record* en `pvd + 156`: LBA en `+2`, tamaño en `+10` (`native.cpp:163-165`).
- `Iso::walk()` (`native.cpp:113-150`) recorre los *directory records*:
  - `len = d[pos]`; si `len == 0`, salta al siguiente sector (los records no cruzan sector);
  - `extent` en `+2`, `size` en `+10`, `flags` en `+25`, `nameLen` en `+32`, nombre en `+33`;
  - ignora `\0` y `\1` (directorio actual / padre);
  - corta en `;` (versión ISO) y saca el punto final (`;1`, `.`);
  - si `flags & 2` es directorio, recursión con `depth < 8`; si no, agrega `{offset = ext*2048, size}`;
  - si el mismo path aparece de nuevo (archivo en varios *extents*), suma el tamaño al anterior
    (`native.cpp:141-143`).
- `Iso::find()` compara sin distinguir mayúsculas (`native.cpp:167-174`).
- `copy_out()` copia en bloques de 1 MiB y avisa si no puede escribir / disco lleno (`native.cpp:203-220`).

No hay `libarchive`, no hay `7z`, no hay `CDVD`, no hay montaje del ISO. Es lectura directa de un archivo plano.

### 1.4 Qué extrae y dónde lo deja

**Release (`native.cpp`):**

- `step_disc` verifica que estén `SLUS_216.78` y `BIN/DBZP.BIN`; si falta cualquiera:
  *“This is not a disc image of the USA release of Budokai Tenkaichi 3 (no SLUS_216.78 on it). Other regions and the
  Wii version have different programs and are not supported.”* (`native.cpp:223-231`).
- `step_data` (`native.cpp:259-333`) toma **todos** los archivos cuyo path (en mayúsculas) sea:
  - `SLUS_216.78` exacto,
  - cualquier cosa bajo `BIN/`,
  - cualquier cosa bajo `DATA/` (`native.cpp:269-275`).
- Los que **no** son `.AFS` se copian a `gamedata/disc/<PATH_EN_MAYÚSCULAS>` (`native.cpp:292-298`).
- Los `DATA/*.AFS` **no se copian**: se abren, se lee `"AFS\0"` + `u32 count`, la tabla `{offset,size} × count`, y
  cada entrada se escribe como `gamedata/<stem-en-minúsculas>/00000.bin`, `00001.bin`, etc.
  (`native.cpp:300-324`). Es el mismo layout de `port/tools/extract_disc.py`.
- Al final crea el marcador vacío `gamedata/.installed` (`native.cpp:326-329`) y reporta
  `@ok <n> files in gamedata/`.

**Checkout (`install.py` + `extract_disc.py`):**

- `step_disc` (`install.py:215-241`): `7z l` para confirmar que el ISO tiene `SLUS_216.78`, `7z x -o disc` para
  extraer `SLUS_216.78` y `BIN`, `flat_image()` para armar la imagen plana desde las secciones `SHF_ALLOC` del ELF
  (`install.py:200-213`), y SHA-1 contra `ROM_SHA1` / `DBZP_SHA1` (`install.py:26-27, 218-221`).
- `step_gamedata` (`install.py:244-259`) llama a `port/tools/extract_disc.py`:
  - `7z x -o gamedata/disc <iso> DATA BIN SLUS_216.78` (`extract_disc.py:31`);
  - parte cada `gamedata/disc/DATA/*.AFS` en `gamedata/<stem>/00000.bin` y **borra el AFS** (`extract_disc.py:12-24,
    33-36`);
  - deja los archivos sueltos del disco en `gamedata/disc/`.
- Luego `step_texts` reescribe los diálogos de memory card en `gamedata/mods/` (`install.py:262-283`), `step_split`
  parte el ejecutable con `splat` a `asm/` (`install.py:292-320`), `step_build` compila (`install.py:322-349`) y
  `step_test` corre el combate demo (`install.py:351-371`).

Layout final de release:

```
<release>/
  Tenkaichi3Decomp
  Tenkaichi3Decomp.dat
  Tenkaichi3Decomp-setup
  gamedata/
    .installed
    disc/
      SLUS_216.78
      BIN/DBZP.BIN
      DATA/<archivos sueltos, sin .AFS>
    pzs3us0/00000.bin ...
    pzs3us1/00000.bin ...
    pzs3us2/00000.bin ...
    mods/pzs3us1/...        (textos reescritos)
    .selftest/              (saves del self-test)
  saves/
```

En el checkout, además, `asm/`, `.venv`, `port/build/`, `play.sh`, `install.log`.

### 1.5 Verificación: hashes, tamaños y mensajes

- **SHA-1 de los dos programas**, no del ISO entero:
  - `ROM_SHA1 = caee6c...` para la imagen plana de `SLUS_216.78` desde `0x100000` a `0x2FF180`;
  - `DBZP_SHA1 = 4f9109...` para `BIN/DBZP.BIN`;
  - si no coinciden: *“The game's programs on this disc do not have the expected checksums. The port is built from
    the unmodified USA release (SLUS-21678); a patched or damaged image will not work.”* (`native.cpp:245-256`,
    `install.py:236-239`).
- **Estructura AFS**: verifica `"AFS\0"`, `count`, que `count*8+8 <= tamaño` y que cada `{offset,size}` caiga dentro
  del archivo; si no: *“An archive on the disc (...) is damaged.”* (`native.cpp:307-318`).
- **Errores de escritura**: *“Could not write ... Is the disk full or the folder read-only?”*
  (`native.cpp:206-219`).
- **Tamaño de disco**: la UI avisa “Needs about 4 GB of free space” (`setup.cpp:375`); `install.py` habla de 3,5 GB
  (`install.py:255`).
- **En runtime**, la release stripped verifica un hash FNV-1a de las tablas de datos extraídas del ELF/DBZP contra el
  valor guardado en `GAME.dat` (`port/src/plat_mem.c:266-383`). Si el usuario cambió los archivos, el juego sale con
  *“the game's programs in your game data are not the unmodified USA release (SLUS-21678)”*
  (`plat_mem.c:379-382`).

### 1.6 Cómo detecta que faltan los datos en arranques posteriores

- **Setup:** `Native_Installed(root)` devuelve verdadero si existe `gamedata/.installed`
  (`native.cpp:748-751`). En `main()` del setup, si está instalado y no se pidió otra ISO, salta directo a
  `PAGE_DONE`, marca todos los pasos como `SKIPPED` / “already done” y pone el botón **Play**
  (`setup.cpp:716-724`).
- **Juego:** el constructor `Port_MapMemory()` llama a `Port_LoadGameData()`
  (`port/src/plat_mem.c:470-500`). Si falta `gamedata/disc/SLUS_216.78`:
  *“bt3: the game's program was not found: ... The game's data comes from your own disc image; run the setup
  (Tenkaichi3Decomp-setup) to unpack it.”* y `exit(2)` (`plat_mem.c:266-270, 337-342`). Si falta
  `gamedata/disc/BIN/DBZP.BIN`: *“the game's menu program was not found”* (`plat_mem.c:356-364`).
- **Re-ejecutar la instalación:**
  - en release: `BT3_SETUP_ISO=<iso> ./Tenkaichi3Decomp-setup` (`setup.cpp:728-733`);
  - o borrar `gamedata/.installed` y abrir el setup de nuevo;
  - en checkout: `python3 install.py --iso <iso> --force`;
  - cada paso se saltea si su resultado ya existe (`install.py:215-219, 246-249, 264-267, 292-296, 322-326`).

---

## 2. Estado de BT2: qué necesita hoy para arrancar

### 2.1 Lista exacta de archivos (sacada del ISO real del usuario)

Verifiqué el ISO con un lector ISO9660 de sólo lectura (mismo algoritmo que T3D) y con `sha1sum`. El ISO del usuario:

- archivo: `DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).iso`
- tamaño: `2.998.829.056` bytes
- sha1: `0b11f7a2a4c178b555c45a58ce8ee725e57a1423` (coincide con `docs/PORT_LOG.md:15`)
- PVD: `type=1`, `"CD001"`, volume id `SLUS_21441`, root LBA `261`, root size `368`.

Contenido completo del root (no hay más carpetas):

| Archivo en el ISO | Tamaño (bytes) | ¿Quién lo abre en el port? | Dónde |
|---|---:|---|---|
| `SLUS_214.41` | 2.675.936 | `load_elf()` | `port/full/mem.c:211-232`; default en `mem.c:333` (`BT2_ELF` lo pisa) |
| `SYSTEM.CNF` | 57 | nadie en runtime | sólo diagnóstico (`BOOT2 = cdrom0:\SLUS_214.41;1`) |
| `BIN/DBZP.BIN` | 513.167 | `sceOpen()` ← `Overlay_Load()` | `src/main_1002D8.c:63-79`; `port/full/plat_file.c:169-205` |
| `DATA/ZS2US_1.AFS` | 1.100.716.032 | `ADXF_LoadPartitionNw` (partición 0) | `port/full/plat_file.c:57-74` |
| `DATA/ZS2US_2.AFS` | 1.610.694.656 | `ADXF_LoadPartitionNw` (partición 1) | `port/full/plat_file.c:57-74` |
| `DATA/ZS2US.DIR` | 64 | `sceCdSearchFile` → `stat()` | `src/sys/file_2EE8B8.c:12`; `port/full/plat_sdk.c:42-56` |
| `DATA/ZS2US_1.ALG` | 26 | no lo abre el port | — |
| `DATA/ZS2US_2.ALG` | 26 | no lo abre el port | — |
| `DATA/LOGO_O.SFD` | 2.869.248 | `open_movie()` | `port/full/plat_movie.c:134-148` |
| `DATA/ZS2USOP.SFD` | 97.454.080 | `open_movie()` | idem |
| `DATA/ZS2USED.SFD` | 161.533.952 | `open_movie()` | idem |
| `IRX/*` (17 `.IRX` + `IOPRP300.IMG`) | 726.850 | `sceSifLoadModule` / `sceSifRebootIop` (hoy stubs) | `port/full/plat_sys.c:61-63` |

Total si se copia todo: **2.977.184.094 bytes ≈ 2,98 GB** (sin contar saves ni logs).

Los nombres que el juego pide están en el ELF (`strings port/build/combined.elf`):
`cdrom0:\BIN\DBZP.BIN;1`, `cdrom0:\IRX\*.IRX;1`, `cdrom0:\IRX\IOPRP300.IMG;1`, `logo_o.sfd`, `zs2us_1.afs`,
`zs2us_2.afs`, `zs2us.dir`, `zs2used.sfd`, `zs2usop.sfd`. En el binario nativo el que existe es
`sceCdLayerSearchFile`; el alias de `sceCdSearchFile` está documentado en `docs/PORT_LOG.md:70-74`, y éste hace
`stat` del archivo antes de registrarlo (`plat_sdk.c:42-56`).

### 2.2 Rutas y variables

- **ELF:** `BT2_ELF` o `gamedata/SLUS_214.41` (`port/full/mem.c:333`). Es la ruta por defecto, relativa al
  directorio de trabajo.
- **Datos del juego (AFS, SFD, overlay, IRX):** `BT2_DATA` o `gamedata` (`port/full/plat_file.c:41`);
  `plat_file.c` busca `gamedata/DATA/<nombre>` y, si no, `gamedata/DATA/<NOMBRE_EN_MAYÚSCULAS>`
  (`plat_file.c:43-54`). El overlay se resuelve con `open_disc()` desde `BT2_DATA/BIN/DBZP.BIN`, sin distinguir
  mayúsculas (`plat_file.c:169-194`). Las películas usan su propia copia de la variable:
  `BT2_DATA/DATA/<name>.SFD` (`plat_movie.c:134-148`).
- **Saves:** `BT2_SAVES` o `saves/` (`port/full/plat_mc.c:5, 19, 51`).
- **Settings:** `bt2_settings.txt` en el directorio actual (`port/full/plat_intro.c:3`, `plat_text.c:17`, etc.).
- **El ISO no se usa en runtime.** `main()` ignora `argc/argv` (`mem.c:334`) y `play.sh` le pasa
  `gamedata/SLUS_214.41 gamedata.iso` sólo por compatibilidad con el runtime viejo. El puerto nativo lee la carpeta,
  no el ISO.

### 2.3 Qué pasa hoy si faltan datos

**Causa probable (no es un bug de traducción, es una funcionalidad que nunca se agregó):** el port nativo se armó
sobre un `gamedata/` ya extraído a mano con `7z` (README:24). Nadie escribió el paso de instalación, así que el
binario asume las rutas y falla con `exit(2)` o se cuelga. No hay marcador, ni chequeo, ni UI.

No hay detección amigable ni wizard:

- Si falta el ELF: `load_elf()` imprime `bt2full: no se puede leer gamedata/SLUS_214.41` y hace `exit(2)`
  (`mem.c:211-216`).
- Si falta un AFS: `func_002EA588` imprime `bt2full: no se puede abrir la particion AFS ...` y sigue; el juego
  probablemente se cuelga o falla más adelante (`plat_file.c:63-66`).
- Si falta el overlay: `Overlay_Load()` reintenta `sceOpen` para siempre (`src/main_1002D8.c:68-70`): **cuelgue
  silencioso** si `BIN/DBZP.BIN` no está.
- Si falta un SFD: `[movie] no se puede abrir ...` y sigue (`plat_movie.c:147`), salvo `BT2_SKIP_MOVIES=1`.
- Si falta `ZS2US.DIR`: `sceCdSearchFile` devuelve 0; no hay mensaje claro en el port.

### 2.4 Qué NO hace falta (y por qué)

- **No hace falta partir los AFS.** BT2 los lee directo con `fseek/fread` (`plat_file.c:104-122`). Partirlos como T3D
  duplicaría ~2,7 GB o exigiría borrar los AFS, y el port no los busca por índice suelto.
- **No hace falta el ISO en runtime.** Basta la carpeta extraída; `gamedata.iso` es un residuo del runtime PS2Recomp.
- **`.ALG`** no se abre en el port; se puede copiar por fidelidad (52 bytes) o ignorar.
- **`IRX/*`** hoy no se abren porque `sceSifLoadModule` y `sceSifRebootIop` son stubs (`plat_sys.c:61-63`). Conviene
  copiarlos igual (726 KB) para no re-descubrir el problema si mañana se implementa el IOP real.
- **No hace falta BIOS ni PCSX2.** El port no es un emulador.

### 2.5 Bibliotecas que ya están en el proyecto

- **SDL3** (ventana, audio, diálogos de archivo): linkeado por `port/tools/link_full.py:202`.
- **FFmpeg** (`libavformat`, `libavcodec`, `libswscale`, `libavutil`): videos SFD (`link_full.py:448`).
- **Dear ImGui** completo, con backends `imgui_impl_sdl3`, `imgui_impl_sdlgpu3`, `imgui_impl_opengl3`:
  `port/third_party/imgui/`. Se puede reusar para el wizard.
- **xxhash** en `port/third_party/xxhash` (para estado), no para el instalador.
- **Python 3 + stdlib**: ya se usa para `configure.py`, `build_full.py`, etc.
- **No hay** `libarchive` ni `zlib` enlazados de forma directa por el port (`link_full.py:448`). `7z` está en el
  sistema, pero es una dependencia externa evitable.
- **Ojo:** existe un lector ISO9660 en `third_party/PS2Recomp/ps2xIOP/include/ps2x/iop/iso9660.h`, pero PS2Recomp es
  **GPL-3**; no conviene copiarlo a un port MIT. Mejor adaptar el de T3D (MIT) o escribir uno nuevo.

---

## 3. Plan para el wizard de BT2

### 3.1 Arquitectura recomendada (dos fases)

**Fase 1 (ya, para el repo de desarrollo): `install.py` en la raíz de BT2-Recomp.**

- Python stdlib únicamente: `struct`, `hashlib`, `shutil`, `pathlib`, `os`, `sys`.
- Lector ISO9660 propio (el mismo algoritmo de T3D, ~40 líneas en Python).
- Sin `7z`, sin `libarchive`, sin compilar nada.
- Reemplaza el paso manual `7z x -ogamedata "<iso>"` del README:24.
- Sirve para verificar la instalación (`--check`) y para el self-test (`--test`).
- Es la opción más barata y la que menos riesgo agrega al runtime.

**Fase 2 (cuando haya release): `port/setup/` en C++/ImGui, copiando el modelo de T3D.**

- `port/setup/native.cpp` adaptado de T3D (MIT, con aviso de copyright): lector ISO9660, SHA-1, copia, marcador.
- `port/setup/setup.cpp`: ventana ImGui + SDL3 con `Browse...`, drag & drop, lista de pasos y barra de progreso.
- `port/setup/build.sh`: compila con `g++` + SDL3 + el ImGui que ya está en `port/third_party/imgui`.
- Es un binario aparte (`bt2setup`), igual que `Tenkaichi3Decomp-setup`, así no se toca el binario del juego ni su
  mapa de memoria fijo.

No recomiendo meter el wizard dentro de `bt2full` en `main()`: el binario mapea RAM en constructores y carga el ELF
antes de cualquier UI; un proceso aparte es más simple y más seguro.

### 3.2 Flujo mínimo del wizard

1. **Pedir la imagen**
   - `--iso <archivo>` o campo de texto / Browse / drag & drop.
   - Si no se pasó, buscar `*.iso` en el directorio actual y en el padre (como `install.py:176-198`), pero **ignorar
     el symlink `gamedata.iso`** para no confundirlo con la fuente.
   - Formatos: sólo ISO9660 plano (`.iso`). Si el PVD no es `CD001`, mensaje claro: *“No es una imagen .iso. Los
     .chd/.cso/.gz hay que convertirlos a .iso primero.”*
2. **Abrir y validar el ISO**
   - leer sector 16, verificar `pvd[0]==1`, `"CD001"`;
   - volume id `SLUS_21441` (o al menos presencia de `SLUS_214.41`);
   - buscar `SLUS_214.41`, `BIN/DBZP.BIN`, `DATA/ZS2US_1.AFS`, `DATA/ZS2US_2.AFS`, `DATA/ZS2US.DIR`;
   - si falta `SLUS_214.41`: *“No es la versión USA (SLUS-214.41). Otras regiones (PAL SLES_..., Japón SLPS_...) no
     están soportadas.”*
3. **Verificar autenticidad**
   - SHA-1 del `SLUS_214.41` crudo: `cf01d5b2023843eecf7cf8ccda8bcd102dd61db7`
     (coincide con `docs/REPRODUCIBILIDAD.md:50-51`);
   - SHA-1 de `BIN/DBZP.BIN`: `0463612b526e6e90a48636bb419720e212515ed1`;
   - opcional: SHA-1 del ISO entero `0b11f7a2...` (tarda ~30-60 s en 3 GB; no es necesario si los dos programas
     coinciden);
   - si no coinciden: *“La imagen no es la versión USA sin modificar (SLUS-214.41). Una imagen parcheada o dañada no
     funciona.”*
4. **Chequear espacio libre**
   - `shutil.disk_usage(destino).free` ≥ 3,2 GB (el contenido son ~2,98 GB; dejar margen para `.part` y logs).
   - Si no alcanza: mensaje con los GB libres y los necesarios.
5. **Extraer a `gamedata/`**
   - destino por defecto: `gamedata/` al lado del `install.py` / del binario; `--data <dir>` para elegirlo.
   - copiar preservando la estructura del ISO:
     `SLUS_214.41`, `SYSTEM.CNF`, `BIN/DBZP.BIN`, `DATA/*.AFS`, `DATA/*.SFD`, `DATA/ZS2US.DIR`, `DATA/*.ALG`,
     `IRX/*`.
   - escribir cada archivo a `<nombre>.part` y hacer `os.replace()` al terminar, para no dejar archivos a medias.
   - buffer de 1 MiB; mostrar progreso por archivo y por porcentaje (los AFS son 1,1 y 1,6 GB).
   - después de copiar cada AFS, verificar los primeros 8 bytes: `"AFS\0"` y un `count` razonable.
6. **Marcar y guardar**
   - escribir `gamedata/.installed` **último**, con texto:
     ```
     bt2-install 1
     iso=/ruta/al.iso
     iso_sha1=...
     elf_sha1=...
     dbzp_sha1=...
     fecha=...
     ```
   - el juego sólo necesita que exista; los datos son para diagnóstico y para `--check`.
7. **Self-test opcional**
   - correr el combate demo sin ventana:
     `BT2_DEMO=1 BT3_GS=none BT2_SKIP_MOVIES=1 BT2_SAVES=<tmp> ./port/build/full/bt2full`
     y esperar `bt2: battle finished` (`port/full/plat_demo.c:1-31`; `BT3_GS=none` está soportado en
     `port/full/gs/gs_core.c:1373-1383`).
   - si no aparece, mostrar las últimas líneas y el log; el paso se puede saltear con `--skip-test`.
8. **Al terminar**
   - imprimir cómo jugar: `cd BT2-test && ./jugar.sh` (o `bin/bt2`).
   - no borrar el ISO ni copiarlo al repo.

### 3.3 Lector ISO9660 sin dependencias nuevas

La pieza central es chica. En C (adaptado de T3D, MIT) alcanza con esto:

```c
/* offsets dentro del directory record ISO9660 */
#define DR_LEN     0
#define DR_EXTENT  2   /* u32 LE: LBA del archivo */
#define DR_SIZE   10   /* u32 LE: tamaño en bytes */
#define DR_FLAGS  25
#define DR_NAMELEN 32
#define DR_NAME   33

typedef struct { char path[160]; uint64_t off, size; } IsoFile;
typedef struct { FILE *f; IsoFile v[256]; int n; } Iso;

static void iso_read(Iso *iso, uint64_t off, void *buf, size_t n) {
    if (fseeko(iso->f, (off_t)off, SEEK_SET) != 0 || fread(buf, 1, n, iso->f) != n)
        die("no se pudo leer la imagen del disco (¿está incompleta?)");
}

/* recorre un directorio; los records no cruzan sector */
static void iso_walk(Iso *iso, uint32_t lba, uint32_t size, const char *dir, int depth) {
    uint8_t *d = malloc(size);
    iso_read(iso, (uint64_t)lba * 2048, d, size);
    for (size_t pos = 0; pos + 34 <= size; ) {
        uint8_t len = d[pos];
        if (len == 0) { pos = (pos / 2048 + 1) * 2048; continue; }
        if (pos + len > size) break;
        uint32_t ext, bytes;
        memcpy(&ext,   d + pos + DR_EXTENT, 4);
        memcpy(&bytes, d + pos + DR_SIZE,   4);
        uint8_t flags = d[pos + DR_FLAGS], nl = d[pos + DR_NAMELEN];
        char name[128];
        memcpy(name, d + pos + DR_NAME, nl); name[nl] = 0;
        pos += len;
        if (nl == 1 && (name[0] == 0 || name[0] == 1)) continue; /* "." y ".." */
        char *semi = strchr(name, ';'); if (semi) *semi = 0;
        size_t L = strlen(name); if (L && name[L-1] == '.') name[L-1] = 0;
        char full[160];
        snprintf(full, sizeof full, "%s%s", dir, name);
        if (flags & 2) { if (depth < 8) iso_walk(iso, ext, bytes, strcat(full, "/"), depth + 1); }
        else if (iso->n < 256) iso->v[iso->n++] = (IsoFile){ .off = (uint64_t)ext * 2048, .size = bytes };
    }
    free(d);
}

static void iso_open(Iso *iso, const char *path) {
    uint8_t pvd[2048];
    iso->f = fopen(path, "rb");
    if (!iso->f) die("no se pudo abrir la imagen");
    iso_read(iso, 16 * 2048, pvd, sizeof pvd);
    if (pvd[0] != 1 || memcmp(pvd + 1, "CD001", 5) != 0)
        die("no es una imagen .iso (los .chd/.cso/.gz hay que convertir primero)");
    uint32_t lba, size;
    memcpy(&lba,  pvd + 156 + 2,  4);
    memcpy(&size, pvd + 156 + 10, 4);
    iso_walk(iso, lba, size, "", 0);
}
```

Detalles que no hay que olvidar:

- **Offsets de 64 bits**: usar `fseeko`/`off_t` con `_FILE_OFFSET_BITS=64`, o `uint64_t` + `pread`. Los AFS de BT2
  pasan de 1 GB; un `long` de 32 bits trunca.
- **Records que no cruzan sector**: si `len == 0`, saltar al próximo múltiplo de 2048 (`native.cpp:116-118`).
- **Nombres**: cortar `;1` y el punto final; comparar sin distinguir mayúsculas (`open_disc` ya lo hace).
- **Multi-extent**: si el mismo path aparece varias veces, sumar tamaños (T3D lo hace en `native.cpp:141-143`); en
  BT2 no aparece, pero es barato.
- **Profundidad**: BT2 sólo tiene 2 niveles (`BIN/`, `DATA/`, `IRX/`); el límite 8 de T3D sobra.
- **Joliet/Rock Ridge**: no hacen falta; los discos de PS2 usan ISO9660 plano con nombres en mayúscula.
- **UDF-only**: si el PVD no está, rechazar con mensaje claro; no intentar adivinar.

En Python es aún más corto (`struct.unpack_from("<I", ...)`, `open(..., "rb")`), y no hay que pelear con `off_t`.

### 3.4 Estructura de destino para BT2

```
BT2-test/ (o la carpeta donde corre el juego)
  bin/bt2
  gamedata/
    .installed
    SLUS_214.41
    SYSTEM.CNF
    BIN/DBZP.BIN
    DATA/ZS2US_1.AFS
    DATA/ZS2US_2.AFS
    DATA/ZS2US.DIR
    DATA/ZS2US_1.ALG
    DATA/ZS2US_2.ALG
    DATA/LOGO_O.SFD
    DATA/ZS2USOP.SFD
    DATA/ZS2USED.SFD
    IRX/*.IRX + IOPRP300.IMG
  saves/
```

Es exactamente la estructura que hoy tiene `BT2-test/gamedata`, así que el wizard no cambia nada del runtime: sólo
automatiza el `7z x` y agrega el marcador.

### 3.5 Cómo detectar “ya instalado” y cómo reinstalar

- **Detección:** `gamedata/.installed` existe y, si se quiere ser estricto, los 5 archivos críticos están y el
  SHA-1 del ELF/DBZP coincide.
- **Arranque posterior:** `install.py --check` (o `bt2setup`) muestra “ya instalado” y ofrece jugar; el juego ni se
  entera del marcador, sigue usando `gamedata/`.
- **Reinstalar:**
  - `python3 install.py --iso <iso> --force`;
  - o borrar `gamedata/.installed` y volver a correr;
  - o `BT2_SETUP_ISO=<iso> ./bt2setup` (si se copia el modelo de T3D).
- **Ruta guardada:** no hace falta un config nuevo. El juego ya usa `gamedata/` relativo al CWD y `BT2_DATA` para
  override. Si se quiere soportar “datos en otra carpeta”, el lugar limpio es centralizar `Port_DataRoot()` y hacer
  que `plat_movie.c` también lo use; pero eso es un cambio aparte, no parte del wizard mínimo.

### 3.6 Integración con el runtime (mensajes, no lógica)

Hoy el runtime falla feo. El cambio mínimo y seguro es un *preflight* antes de `load_elf`, que no toca la lógica del
juego:

```diff
--- a/port/full/mem.c
+++ b/port/full/mem.c
@@ -330,6 +330,22 @@ int main(int argc, char **argv) {
     void *stk;
     const char *elf = getenv("BT2_ELF") ? getenv("BT2_ELF") : "gamedata/SLUS_214.41";
     (void)argc; (void)argv;
+    {
+        const char *root = getenv("BT2_DATA") ? getenv("BT2_DATA") : "gamedata";
+        static const char *need[] = {
+            "SLUS_214.41", "BIN/DBZP.BIN", "DATA/ZS2US_1.AFS", "DATA/ZS2US_2.AFS", "DATA/ZS2US.DIR",
+        };
+        char path[512];
+        for (unsigned i = 0; i < sizeof need / sizeof need[0]; i++) {
+            snprintf(path, sizeof path, "%s/%s", root, need[i]);
+            if (access(path, R_OK) != 0) {
+                fprintf(stderr,
+                    "bt2: faltan los datos del juego: %s\n"
+                    "     Extraelos de tu propia ISO con: ./install.py --iso <disco.iso>\n"
+                    "     (o apuntá BT2_DATA a la carpeta que tiene SLUS_214.41, DATA/ y BIN/).\n", path);
+                return 2;
+            }
+        }
+    }
     sigaltstack(&ss, NULL);
```

Eso convierte el `exit(2)` seco de `load_elf` en un mensaje accionable y cubre el cuelgue de `Overlay_Load` si falta
`DBZP.BIN`. No reemplaza al wizard; lo complementa.

### 3.7 Esqueleto de `install.py` (propuesto, NO aplicado)

```python
#!/usr/bin/env python3
"""Extrae los datos de BT2 desde tu propia ISO USA (SLUS-214.41) a gamedata/.
Uso: ./install.py --iso <disco.iso> [--data gamedata] [--check] [--force] [--skip-test]"""
import argparse, hashlib, os, pathlib, shutil, struct, sys

ROOT = pathlib.Path(__file__).resolve().parent
ISO_SHA1  = "0b11f7a2a4c178b555c45a58ce8ee725e57a1423"
ELF_SHA1  = "cf01d5b2023843eecf7cf8ccda8bcd102dd61db7"
DBZP_SHA1 = "0463612b526e6e90a48636bb419720e212515ed1"
NEED = ["SLUS_214.41", "BIN/DBZP.BIN", "DATA/ZS2US_1.AFS", "DATA/ZS2US_2.AFS",
        "DATA/ZS2US.DIR", "DATA/LOGO_O.SFD", "DATA/ZS2USOP.SFD", "DATA/ZS2USED.SFD",
        "DATA/ZS2US_1.ALG", "DATA/ZS2US_2.ALG", "SYSTEM.CNF"]
DIRS = ["IRX"]

def read_dir(f, lba, size):
    """Devuelve [(path, lba, size, es_dir)] de un directorio ISO9660."""
    f.seek(lba * 2048); d = f.read(size); out = []; pos = 0
    while pos + 34 <= len(d):
        n = d[pos]
        if n == 0:
            pos = (pos // 2048 + 1) * 2048; continue
        if pos + n > len(d): break
        ext, = struct.unpack_from("<I", d, pos + 2)
        sz,  = struct.unpack_from("<I", d, pos + 10)
        flags, nl = d[pos + 25], d[pos + 32]
        name = d[pos + 33:pos + 33 + nl].decode("latin1")
        pos += n
        if nl == 1 and name in ("\0", "\1"): continue
        name = name.split(";")[0].rstrip(".")
        if flags & 2: out.append((name + "/", ext, sz, True))
        else:         out.append((name, ext, sz, False))
    return out

def list_iso(iso):
    with open(iso, "rb") as f:
        f.seek(16 * 2048); pvd = f.read(2048)
        if pvd[0] != 1 or pvd[1:6] != b"CD001":
            sys.exit("No es una imagen .iso (convertí .chd/.cso/.gz primero).")
        lba, size = struct.unpack_from("<I", pvd, 158)[0], struct.unpack_from("<I", pvd, 166)[0]
        files = {}
        def walk(prefix, lba, size, depth=0):
            for name, ext, sz, isdir in read_dir(f, lba, size):
                if isdir:
                    if depth < 4: walk(prefix + name, ext, sz, depth + 1)
                else:
                    files[prefix + name] = (ext, sz)
        walk("", lba, size)
    return files

def sha1_file(path):
    h = hashlib.sha1()
    with open(path, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""): h.update(b)
    return h.hexdigest()

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--iso"); ap.add_argument("--data", default=str(ROOT / "gamedata"))
    ap.add_argument("--check", action="store_true"); ap.add_argument("--force", action="store_true")
    ap.add_argument("--skip-test", action="store_true"); a = ap.parse_args()
    dest = pathlib.Path(a.data)
    if a.check:
        missing = [n for n in NEED if not (dest / n).is_file()]
        print("faltan:", *missing, sep="\n  ") if missing else print("instalado:", dest)
        return 0 if not missing else 1
    iso = pathlib.Path(a.iso) if a.iso else next(iter(ROOT.glob("*.iso")), None)
    if not iso or not iso.is_file(): sys.exit("Pasá --iso <disco.iso>.")
    files = list_iso(iso)
    for n in NEED:
        if n not in files: sys.exit(f"No es la versión USA (falta {n}). Otra región no está soportada.")
    # verificación de los dos programas
    for name, want in (("SLUS_214.41", ELF_SHA1), ("BIN/DBZP.BIN", DBZP_SHA1)):
        lba, sz = files[name]
        with open(iso, "rb") as f: f.seek(lba * 2048); h = hashlib.sha1()
        # (leer por bloques; acá abreviado)
        # if h.hexdigest() != want: sys.exit(...)
    free = shutil.disk_usage(dest.parent).free
    if free < 3_200_000_000: sys.exit(f"Faltan {3_200_000_000 - free:,} bytes libres.")
    for name, (lba, sz) in files.items():
        if name == "SLUS_214.41" or name.startswith(("BIN/", "DATA/", "IRX/")) or name == "SYSTEM.CNF":
            out = dest / name; out.parent.mkdir(parents=True, exist_ok=True)
            tmp = out.with_suffix(out.suffix + ".part")
            with open(iso, "rb") as fi, open(tmp, "wb") as fo:
                fi.seek(lba * 2048); left = sz
                while left:
                    b = fi.read(min(1 << 20, left));
                    if not b: sys.exit("ISO incompleta."); fo.write(b); left -= len(b)
            os.replace(tmp, out)
    (dest / ".installed").write_text(f"bt2-install 1\niso={iso}\n")
    print("listo:", dest)
    return 0

if __name__ == "__main__":
    sys.exit(main())
```

(El esqueleto está abreviado: falta la lectura por bloques del hash y el progreso; la estructura y las constantes
son las correctas.)

### 3.8 Adaptación concreta de `native.cpp` de T3D (fase 2)

Si se copia el instalador nativo de T3D, los cambios son mecánicos:

| T3D | BT2 |
|---|---|
| `kRomSha1 = "caee6c..."` | `"cf01d5b2023843eecf7cf8ccda8bcd102dd61db7"` |
| `kDbzpSha1 = "4f9109..."` | `"0463612b526e6e90a48636bb419720e212515ed1"` |
| `kRomBase/kRomEnd = 0x100000/0x2FF180` | no hace falta: hashear el `SLUS_214.41` crudo |
| `step_disc` busca `SLUS_216.78` + `BIN/DBZP.BIN` | `SLUS_214.41` + `BIN/DBZP.BIN` |
| `step_data` parte `DATA/*.AFS` | copiar `DATA/*.AFS` tal cual (BT2 los lee directo) |
| toma `SLUS_216.78`, `BIN/`, `DATA/` | toma `SLUS_214.41`, `SYSTEM.CNF`, `BIN/`, `DATA/`, `IRX/` |
| `step_texts` reescribe diálogos de memory card | opcional; BT2 ya reescribe textos en RAM (`plat_text.c`) |
| `step_test` corre `BT3_DEMO=1` | `BT2_DEMO=1 BT3_GS=none BT2_SKIP_MOVIES=1`, esperar `battle finished` |
| `gamedata/.installed` | igual |
| `GAME-setup --install <iso>` | `bt2setup --install <iso>` |

La licencia de T3D es MIT (`LICENSE`), así que se puede reutilizar con el aviso de copyright correspondiente.

### 3.9 Orden de trabajo sugerido (un cambio por vez)

1. Agregar `install.py` (fase 1) y probarlo contra el ISO real del usuario en un directorio temporal; comparar
   tamaños/SHA-1 con `BT2-test/gamedata`.
2. Agregar el preflight de `mem.c` (diff de 3.6) y probar que con `gamedata/` vacío el mensaje sale claro y no
   cuelga.
3. Actualizar `README.md` (reemplazar el `7z x` manual por `./install.py --iso ...`) y `docs/PORT_LOG.md` con el
   resultado.
4. Recién después, si se quiere release: copiar `port/setup/` de T3D, adaptar constantes/lista de archivos, compilar
   y probar el self-test.
5. Opcional: `--check` en `play.sh`/`jugar.sh` para avisar antes de arrancar.

---

## 4. Riesgos legales y operativos

- **No distribuir datos del juego.** Este repo ya lo dice (`README.md:3-5`) y `.gitignore` cubre `*.iso`, `/gamedata/`,
  `/disc/`. El wizard debe extraer **sólo del disco del usuario** y no descargar nada. Tampoco hay que commitear
  `gamedata/`, `*.AFS`, `*.SFD`, `SLUS_214.41`, `DBZP.BIN` ni capturas con assets.
- **No publicar el ISO ni los archivos extraídos** en releases, issues, CI, docs ni tests. Si se agregan tests
  automáticos, que usen un fixture sintético (por ejemplo, un ISO de prueba con archivos dummy) y no datos reales.
- **Región:** sólo USA `SLUS-214.41`. PAL (`SLES_...`) y Japón (`SLPS_...`) tienen otro ELF, otro overlay y otros
  índices de AFS; el wizard debe **rechazar** esas imágenes con un mensaje claro, no intentar extraerlas. Si algún día
  se soporta PAL, será un trabajo aparte con sus propios hashes.
- **Imagen parcheada/traducida:** los SHA-1 fallan y el wizard debe negarse; es intencional. Permite detectar ISOs
  dañadas, modificadas o de otra revisión.
- **Sin BIOS:** no se pide BIOS ni se emula la consola; el usuario sólo aporta la imagen del juego.
- **Espacio y permisos:** chequear ~3,2 GB libres y avisar si la carpeta es de sólo lectura. No escribir dentro del
  ISO ni en `/mnt/datos2/BT2-Decomp`.
- **Rutas con symlinks:** `gamedata.iso` es un symlink a `/run/media/...`; si el disco no está montado, el wizard no
  debe tomarlo como fuente ni borrarlo. Mejor pedir `--iso` explícito o ignorar symlinks al autodetectar.
- **Windows (futuro):** nombres con `\`, mayúsculas y `fseeko` de 64 bits; el lector de T3D ya usa SDL_IO y funciona
  en Windows, pero BT2 todavía no tiene release Windows.
- **Licencias:** T3D es MIT, se puede adaptar. PS2Recomp es GPL-3: **no** copiar su `iso9660.h` a un port MIT.
  `ffmpeg`/SDL3 ya están enlazados y no cambian por el wizard.

---

## 5. Evidencia (comandos de sólo lectura usados)

```text
# 1) Estructura extraída actual de BT2
$ ls -la BT2-test/gamedata
  BIN/  DATA/  IRX/  IOPModules/ (copia de IRX)  SLUS_214.41  SYSTEM.CNF  mc0/ mc1/
$ ls DIRS: DATA = LOGO_O.SFD, ZS2US_1.AFS, ZS2US_1.ALG, ZS2US_2.AFS, ZS2US_2.ALG,
                ZS2US.DIR, ZS2USED.SFD, ZS2USOP.SFD; BIN = DBZP.BIN; IRX = 18 archivos, 726.850 B.

# 2) Hash del ISO y de los programas
$ sha1sum 'DragonBall Z - Budokai Tenkaichi 2 (USA) (En,Ja).iso'
0b11f7a2a4c178b555c45a58ce8ee725e57a1423
$ sha1sum disc/SLUS_214.41 disc/DBZP.BIN
cf01d5b2023843eecf7cf8ccda8bcd102dd61db7  disc/SLUS_214.41
0463612b526e6e90a48636bb419720e212515ed1  disc/DBZP.BIN

# 3) PVD y listado del ISO (lector ISO9660 propio, sin montar)
PVD 1 b'CD001' vol SLUS_21441
root 261 368
F SYSTEM.CNF 57
D BIN/ ; F BIN/DBZP.BIN 513167
D IRX/ ; 17 .IRX + IOPRP300.IMG = 726850
D DATA/ ; LOGO_O.SFD 2869248, ZS2US.DIR 64, ZS2USED.SFD 161533952,
           ZS2USOP.SFD 97454080, ZS2US_1.AFS 1100716032, ZS2US_1.ALG 26,
           ZS2US_2.AFS 1610694656, ZS2US_2.ALG 26
F SLUS_214.41 2675936

# 4) Referencias de código
T3D: install.py:26-27,176-241,244-259,388-430; port/tools/extract_disc.py:12-36;
     port/setup/native.cpp:102-174,203-333,694-707,748-751;
     port/setup/setup.cpp:79-91,126-173,354-380,457-540,616-638,716-733,740-741.
BT2: port/full/mem.c:211-232,333; port/full/plat_file.c:41-74,169-205,224;
     port/full/plat_movie.c:134-148; port/full/plat_sdk.c:42-56;
     src/main_1002D8.c:63-79; include/main.h:9; src/sys/file_2EE8B8.c:12;
     docs/PORT_LOG.md:15,78; docs/REPRODUCIBILIDAD.md:50-51; README.md:24.
```

---

## 6. Qué descarté y por qué

- **`7z` como dependencia del instalador:** T3D sólo lo usa en el camino de fuentes; la release usa su lector propio.
  BT2 puede evitar depender de `7z` con ~40 líneas de ISO9660.
- **`libarchive`/`zlib`:** no hacen falta para ISO9660 plano; agregan dependencia y problemas de licencia/empaquetado.
- **Copiar/partir los AFS como T3D:** BT2 lee los AFS directo (`plat_file.c:104-122`). Partirlos duplicaría datos o
  exigiría borrar los originales; no aporta nada al port actual.
- **Guardar una ruta absoluta en un config nuevo:** T3D no lo hace; usa `gamedata/` relativo y `BT3_DATA`. En BT2 ya
  existe `BT2_DATA`; agregar un config es más superficie de error. El marcador `.installed` alcanza.
- **Hashear el ISO entero como único chequeo:** es lento (3 GB) y no detecta mejor que los SHA-1 del ELF/DBZP. Se
  puede ofrecer como opción, no como paso obligatorio.
- **Reusar `third_party/PS2Recomp/.../iso9660.h`:** funciona, pero es GPL-3 y el plan del port es MIT; además el
  release quiere sacar PS2Recomp. No conviene.
- **Meter el wizard dentro de `bt2full`:** el binario mapea RAM y carga el ELF en constructores/`main`; un proceso
  aparte es más limpio y no arriesga el mapa fijo de memoria.

---

## 7. Lo que no verifiqué

- No corrí el instalador de T3D ni el juego; el análisis es de código y del ISO del usuario.
- No probé el esqueleto de `install.py` ni el diff de `mem.c` (no se aplicaron).
- No sé si el `bt2full` actual arranca el combate demo con `BT2_DEMO=1` en este árbol exacto; el código existe
  (`plat_demo.c`) y el modo `BT3_GS=none` está soportado (`gs_core.c:1373-1383`), pero no lo ejecuté.
- No verifiqué el comportamiento con un ISO PAL/JPN real (no hay imagen); el rechazo propuesto se basa en el nombre
  `SLUS_214.41` y en los hashes.
- No revisé si hay otros archivos que el juego pida dinámicamente más adelante (por ejemplo, IDs de AFS que
  correspondan a módulos IOP); la lista de arriba sale del árbol actual del port y de `strings` del ELF.

---

## 3. Fase 1 implementada (2026-11-11)

`setup/install.py` (sólo biblioteca estándar, sin `7z` ni montar el ISO):

- Lector ISO9660 propio (PVD sector 16, `CD001`, records de directorio, **multi-extent**, sin Rock Ridge).
- Exige `SLUS_214.41`, verifica su **SHA-1** (`cf01d5b2…`) y copia sólo el ELF, `SYSTEM.CNF` y las carpetas
  `BIN/`, `DATA/`, `IRX/` (~2,98 GB). Saltea archivos ya presentes con el mismo tamaño (retomable).
- `--check` (valida y mide espacio), `--list` (contenido del disco), `--eu-iso` (copia `DATA/ZS2EU_1.AFS` del
  disco PAL para F8), `--force`. Al final escribe `gamedata/.installed` (JSON con hash, fecha y bytes).
- Mensajes claros: archivo que no es ISO, región equivocada (detecta `SLES_541.64` y avisa), archivos faltantes,
  disco lleno, hash distinto.

Probado con la ISO PAL real: `--list` da 33 archivos / 2,9 GB; extrajo `DATA/ZS2EU_1.AFS` (1,1 GB) con SHA-1
idéntico al de `gamedata/`; `--check` rechaza la región con el mensaje esperado; un archivo random se rechaza como
"no es ISO9660". Además se probó con una **ISO USA sintética** (con el `SLUS_214.41` real): copia completa, verificó
el SHA-1, escribió `.installed`, la segunda corrida salteó todo (retomable) y un ELF con un byte cambiado se rechazó
con código 3 sin dejar marcador.

**Sin verificar:** la ISO USA real (no está en esta máquina) y el arranque del port con un `gamedata/` recién
instalado. Falta el preflight en el binario: hoy si faltan datos hace `exit(2)` o `Overlay_Load()` cuelga; el
marcador `.installed` todavía no lo lee el juego.

---

## 4. Fase 2 implementada: app nativa `bt2-setup` (2026-11-12)

La app de setup completa está en `setup/` y **no depende de Python ni de `7z`** para instalar: el lector ISO9660,
el SHA-1, la copia y el marcador son C/C++ propios. `setup/install.py` queda como alternativa y comparte el mismo
layout de datos y de marcador.

### 4.1 Archivos

```
setup/
  CMakeLists.txt              build reproducible (SDL3 por pkg-config, ImGui del repo)
  build.sh                    -> setup/build/bt2-setup
  src/iso.c, iso.h            lector ISO9660 (PVD sector 16, CD001, records, multi-extent, offsets 64 bits)
  src/sha1.c, sha1.h          SHA-1 propio
  src/install.c, install.h    preflight, copia con progreso/cancelación, chequeo, marcador JSON
  src/gui.cpp, gui.h          ventana SDL3 + ImGui OpenGL3 (drag & drop, diálogos, Play)
  src/launch.cpp, launch.h    lanzar el juego en segundo plano con BT2_DATA/BT2_ELF
  src/paths.cpp, paths.h      raíz del repo y rutas absolutas
  src/main.cpp                CLI (--install/--check/--list/--play) y arranque de la GUI
  tests/make_test_iso.py      ISO sintética para probar hash/región/GUI sin datos reales
  ENTREGA.md                  arquitectura, build y pruebas
```
No toca `port/build/`, `port/full/`, `src/`, `include/`, `gamedata/` ni el binario del juego. El binario sale en
`setup/build/bt2-setup`.

### 4.2 Decisiones

- **Todo nativo en C/C++**: se descartó invocar `install.py` y parsear eventos. El lector de ~250 líneas se probó
  contra las ISOs USA y PAL reales y contra una ISO sintética.
- **Dos ISO abiertas a la vez**: la USA para el juego y la PAL sólo para `DATA/ZS2EU_1.AFS` (`--eu-iso`).
- **Validación antes de copiar**: región por nombre de programa (`SLUS_214.41`, `SLES_541.64`, `SLPS_*`), archivos
  requeridos, SHA-1 de `SLUS_214.41` y `BIN/DBZP.BIN`, y espacio libre con 64 MB de margen.
- **Escritura atómica por archivo**: `<archivo>.part` → `rename()`; el ELF se hashea mientras se copia y sólo se
  renombra si coincide. Al cancelar se borra el `.part` y quedan los archivos completos (retomable).
- **Marcador JSON** `gamedata/.installed` al final, con `elf_sha1`, `eu_afs`, `files`, `bytes`, `iso` y fecha.
- **GUI OpenGL3** (3.3 core, fallback 3.0) para no depender de Vulkan; el look sigue al F1 (`port/full/gs/ui.cpp`).
- **Play** lanza `port/build/full/bt2full` desde la raíz del repo, en segundo plano, con `BT2_DATA`/`BT2_ELF`
  apuntando al destino; si no existe, busca `../BT2-test/bin/bt2` y acepta `BT2_GAME`.
- **Consola y GUI usan el mismo motor** (`bt2_install`), con eventos `Bt2Event` y callback; la GUI los encola con
  mutex y el hilo de copia no bloquea la ventana.

### 4.3 Pruebas (2026-11-12)

Build desde cero: `./setup/build.sh --clean` (sin warnings, binario de 1,24 MB).

| Prueba | Comando | Resultado |
|---|---|---|
| ISO USA real, consola | `bt2-setup --install "…(USA).iso" --dest /mnt/datos/tmp/setup_app_test` | **29 archivos, 2.977.184.094 bytes**, 26,9 s (67 s en frío), marcador OK |
| SHA-1 del ELF/DBZP | `sha1sum` sobre el destino | `cf01d5b2…` / `0463612b…` |
| Comparación con `install.py` | `diff` de `find -printf '%s %p'` contra `/mnt/datos/tmp/bt2install` y contra una instalación Python de la ISO sintética | listados idénticos |
| Región PAL como `--iso` | ISO PAL real | exit 1, “Esta ISO es la edición PAL (SLES_541.64)…” |
| Archivo que no es ISO | `/etc/hostname` | exit 1, “no es una imagen de disco ISO9660” |
| `--eu-iso` con PAL | USA + PAL a `/mnt/datos/tmp/setup_app_test` | copia `DATA/ZS2EU_1.AFS` (1.100.650.496 B, SHA-1 `deb5010a…`), 6,5 s |
| Retomar | segunda corrida sobre el destino completo | 0 copiados, 29 ya estaban, 0,0 s |
| `--force` | USA+EU `--force` / USA `--force` | 30 copiados (73,2 s) / 29 copiados (26,9 s) |
| SHA-1 distinto | ISO sintética con `--bad-elf` | exit 3, sin marcador ni `.part` |
| `--check` con ELF alterado | copia del destino + 1 byte | exit 3 |
| Falta un archivo | `--check` sin `DATA/ZS2USOP.SFD` | exit 1, lista el faltante |
| Disco lleno | tmpfs de 10 MB en `unshare -rm` | exit 1, “No hay espacio suficiente…” |
| Falla de escritura | `ulimit -f 2048` | exit 1, sin `.part` ni marcador |
| GUI smoke | `xvfb-run -a env BT2_SETUP_AUTOCLOSE_MS=3000 bt2-setup` | exit 0, ventana y captura PPM |
| GUI instalación | ISO sintética, `BT2_SETUP_AUTOSTART=1` | página “Listo para jugar”, 12 archivos |
| GUI cancelar | ISO USA, `BT2_SETUP_AUTOCANCEL_MS=500` | sin marcador, sin `.part`, aviso de retomable |
| GUI Play | destino instalado, `BT2_GAME=/bin/true` y un script que escribe 2 s después, `BT2_SETUP_AUTOPLAY=1` | lanza el proceso, cierra y el proceso sigue vivo |
| Pruebas automáticas | `BT2_TEST_PAL_ISO=… ./setup/tests/smoke.sh` | 17 ok, 0 fallos |

### 4.4 Limitaciones

- **Linux x86-64** únicamente (SDL3 + OpenGL3; no se probó Windows/macOS).
- Sólo ISO9660 plano: `.chd`, `.cso` y `.gz` hay que convertirlos a `.iso` (mensaje explícito).
- Sólo edición **USA** (`SLUS_214.41`); PAL/JPN se rechazan. La ISO PAL sirve únicamente para `--eu-iso`.
- No se hashea la ISO entera (3 GB): se validan los dos programas que importan, como en T3D/`install.py`.
- La GUI necesita un servidor gráfico y OpenGL 3.3/3.0; sin eso queda el modo consola.
- Si el juego no está compilado, la instalación funciona pero **Play** queda deshabilitado con el motivo.
- El preflight amigable dentro de `bt2full` sigue pendiente: hoy si faltan datos hace `exit(2)` y el overlay puede
  colgarse. La app cubre la instalación, no cambia el runtime.
