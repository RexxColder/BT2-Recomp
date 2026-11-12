# F10 — Cómo compilar BT2-Port para Windows

Fecha: 2026-11-11. **Investigación de solo lectura**: no compilé nada, no ejecuté el juego, no toqué
`/mnt/datos2/BT2-Decomp` ni ningún archivo del árbol. Lo único que escribí es este informe.

Material leído: `BT2-Recomp/port/{tools,full}` (build_full.py, link_full.py, mem.c, plat_*.c, gs/*),
`port/build/full/{link.ld,stubs.c,report.json,link.log}`, `scripts/capped.sh`, `docs/{PLAN_NATIVO,PLAN_PUBLICACION,status,LEEME_PRIMERO,RETOMAR}.md`,
el binario `port/build/full/bt2full` y objetos de `port/build/gen/full/obj`, y el clon de T3D en
`/tmp/opencode/t3d` (`port/tools/toolchain.py`, `undefined.py`, `link.py`, `package.py`, `port/src/plat_mem.c`,
`plat_crash.c`, `docs/port/README.md`).

---

## 0. Veredicto en una línea

**Es viable, pero no con el arranque de memoria de hoy.** El port de BT2 (build nativo `bt2full`, el que juega el
usuario según `docs/RETOMAR.md:9`) necesita la RAM del PS2 **en sus direcciones absolutas** (0x100000..0x2000000)
porque el C compilado lleva esas direcciones como constantes en las instrucciones; un `VirtualAlloc` a la buena
suerte en Windows choca casi seguro con el stack/heap inicial del proceso (lo dice el propio T3D:
`/tmp/opencode/t3d/docs/port/README.md:1018-1019`). La ruta barata de compilación es **mingw-w64 cruzado desde
Linux**, la misma de T3D, y la RAM tiene que venir **del propio PE** (una sección de 31 MB dentro de la imagen) o de
un `CreateFileMapping` que consiga las direcciones bajas. Los espejos 0x20000000/0x30000000 **no se pueden aliasear**
si la RAM vive dentro de la imagen: hay que normalizar direcciones en los lectores de cadenas DMA (5 lugares chicos).
No hay que reescribir el modelo de memoria del juego ni el C: se reescribe `mem.c` (arranque) y se elige el layout.
Estimación: **2–4 semanas** de una persona, con la fase 0 (abajo) como primer filtro de viabilidad.

---

## 1. Cómo lo hace Tenkaichi3Decomp (T3D)

### 1.1 No hay CMake, ni MSVC, ni Makefile

`find` sobre el repo no devuelve ningún `CMakeLists.txt`, `Makefile`, `meson.build`, `.bat` ni `.ps1` fuera de
`third_party/`. El build de T3D son **scripts Python + gcc/clang**, igual que BT2. El único "sistema" es un módulo
de configuración de variantes:

| Pieza | Archivo:línea | Qué hace |
|---|---|---|
| Variante | `port/tools/toolchain.py:14-18` | `BT3_CC=win64` → `WIN=1`, `PREFIX="x86_64-w64-mingw32-"` (vacío si ya corre en MSYS2/Cygwin), `CLANG_TARGET=["--target=x86_64-w64-mingw32"]` |
| SDL3 | `port/tools/toolchain.py:23-30` | carpeta con `include/` y `lib/` para Windows: `BT3_SDL3` o `port/build/win/SDL3-*/x86_64-w64-mingw32` |
| Compilación del C del juego | `port/tools/undefined.py:12-26` | `clang --target=x86_64-w64-mingw32` para el código soft-float; **gcc mingw** (`PREFIX+gcc`) para el renderer, ImGui y la ventana de settings; `-mno-ms-bitfields -D__CRT__NO_INLINE` |
| ptr32 en Windows | `port/tools/undefined.py:48-49` | le pasa a `ptr32.py` el target mingw y `-mno-ms-bitfields` (libclang con target Windows) |
| Ensamblado de tablas de datos | `port/tools/undefined.py:105` | `x86_64-w64-mingw32-as` (sin `--64`) |
| Enlace | `port/tools/link.py:12-26` | ver 1.2 |
| Empaquetado | `port/tools/package.py:104-175` | zip con exe, `.dat`, setup.exe, `SDL3.dll`, play.bat, README, licencias; recolecta DLLs de vendor con `objdump -p` |
| Release reproducible | `port/release/{build.sh,inside.sh,Dockerfile}` | contenedor Ubuntu 22.04 que **compila Linux y Windows desde el repo**, sin disco ni datos del juego |

Conclusión: **T3D no usa MSVC ni vcpkg/conan/submódulos**. Dependencias: ImGui y xxhash vendorizados en el repo,
newlib-libm vendorizado, SDL3 como paquete de desarrollo de mingw, y (ver 1.4) ffmpeg **no** se linkea.

### 1.2 Enlace PE: lo que Windows exigió

`port/tools/link.py:15-26`:

```
-lSDL3 -lm -lwinmm -lws2_32 -lwinhttp -static-libgcc
-Wl,-Bstatic -lstdc++ -lwinpthread -Wl,-Bdynamic
-Wl,--image-base,0x20000000 -Wl,--disable-dynamicbase -Wl,--disable-reloc-section
-Wl,--disable-high-entropy-va -Wl,--wrap=main -Wl,--stack,0x1000000 -mwindows
```

- el programa va a **una dirección fija** porque los punteros del juego son de 4 bytes y las tablas de datos llevan
  direcciones absolutas; se prohíbe la reubicación (`--disable-reloc-section`),
- `--wrap=main` para poder mover el `main` del juego a una pila baja (1.3),
- todo el runtime C/C++/pthread linkeado estático (`-static-libgcc`, `-Bstatic -lstdc++ -lwinpthread`),
- `-mwindows` (sin consola),
- la línea de enlace va en un **response file** `@link.rsp` (`link.py:24-26`): en Windows nativo el límite de
  `CreateProcess` es 32767 caracteres (mismo motivo en `undefined.py:190` para `nm`).

Pitfall documentado (`docs/port/README.md:1237-1247`): con `--disable-dynamicbase` pero **con** tabla `.reloc`, una
máquina con "Force randomization for images (Mandatory ASLR)" movía el `.exe` y crasheaba antes de imprimir nada.
Solución: `--disable-reloc-section` + chequeo al arrancar `GetModuleHandle(NULL) != 0x20000000` → mensaje y `exit(4)`.

### 1.3 La memoria en Windows (lo que importa para BT2)

`port/src/plat_mem.c:35-110` y `:180-190`:

- registros de hardware (0x10000000) y scratchpad (0x70000000) **reservados en su dirección PS2** con `VirtualAlloc`
  (son zonas altas, casi siempre libres),
- el **heap del juego** (0x3BE000..0x2000000) se intenta en su dirección PS2 y, si está ocupada, **cae a cualquier
  lado debajo de 2 GB** (`map_heap`, `low_alloc`); el juego no depende de esa dirección,
- `Port_LowAlloc` (lo que el port le da al juego como dirección de 32 bits) sale de una región reservada en
  0x13000000 con fallback debajo de 2 GB (`plat_mem.c:530-545`),
- el `main` del juego corre en una **pila baja**: si la pila del proceso está arriba de 4 GB, `__wrap_main`
  (`plat_mem.c:128-165`) reserva 16 MB con `low_alloc`, **actualiza `TEB.StackBase/StackLimit/DeallocationStack`** y
  salta con un `Port_CallOnStack` en asm (cambia `%rsp`, llama, restaura),
- el reporte de crash es un **`AddVectoredExceptionHandler`** escrito sin libc (`plat_crash.c:6-40,107,131`) que
  escribe código de excepción, dirección y return addresses a `bt3_crash.txt`.

Lo que **no** hace T3D: mapear RAM en la dirección 0. Sus datos viven en el `.exe` (secciones comunes que el linker
coloca dentro de la imagen en 0x20000000) y el heap se puede mover. **Esa es toda la diferencia con BT2.**

### 1.4 Dependencias de T3D en Windows

| Dep | Cómo | Nota |
|---|---|---|
| SDL3 | paquete de desarrollo **mingw** oficial descomprimido en `port/build/win/`, `SDL3.dll` al lado del exe | self-contained; `package.py:107-130` copia dependencias de vendor y sus licencias |
| ImGui | fuente vendorizada (`port/third_party/imgui`) | se compila con mingw g++, sin DLL |
| xxhash | header vendorizado | inline |
| pthread | **winpthreads** de mingw-w64 (`-lwinpthread` estático) | `pthread_once/cond/mutex` funcionan |
| ffmpeg | **no se linkea**: al principio `_popen("ffmpeg ...")` (`docs/port/README.md:1023,1040`), después reemplazado por un **decoder MPEG-2 propio** (`port/src/plat_mpeg2.c`, `docs/port/README.md:1063-1078`) | los `.pss` del juego son MPEG-2 todo-intra; el audio ADX ya era propio |
| OpenGL | no linkea: `SDL_GL_GetProcAddress` | |
| zstd/vcpkg/conan | no existen en el proyecto | |

### 1.5 Empaquetado

`package.py:132-175`: `Tenkaichi3Decomp-windows-x64.zip` = exe + `.dat` de datos + `setup.exe` + `SDL3.dll` +
`play.bat` + README + `licenses/`. 4.6 MB, **sin datos del juego** (el setup extrae del ISO del usuario). El release
se construye en contenedor (`port/release/inside.sh:24-30`: `BT3_CC=win64`, `port/setup/build.sh win`, `package.py`).

---

## 2. Por qué BT2 es distinto: el layout absoluto (y el bloqueante real)

### 2.1 BT2 no puede reubicar nada

| Evidencia | Qué muestra |
|---|---|
| `port/build/full/link.ld`: 6527 líneas, **6229 absolutos** (`X = 0xADDR;`) + **297 alias** (`X = Y;`) | el linker define los símbolos del juego como **valores absolutos** en sus direcciones PS2 (0x33B680..0x430590) |
| `objdump -dr port/build/gen/full/obj/port__eq__100008.o` → `mov $0x0,%eax` con `R_X86_64_32 D_00387E80` | las instrucciones llevan la **dirección de 32 bits como inmediata**; el linker la resuelve al valor absoluto. No hay GOT ni PIC |
| `port/full/mem.c:1-12` | mapa: RAM del PS2 0x00010000..0x02000000 (memfd de 32 MB) + **espejos del MISMO memfd** en 0x20000000 y 0x30000000 + scratchpad + registros + código nativo en 0x40000000 |
| `port/full/mem.c:240-241` | los dos espejos son **alias reales** (`MapShared` del mismo fd) |
| `port/full/mem.c:211-230` (`load_elf`) | los `PT_LOAD` del `SLUS_214.41` se escriben **en su dirección virtual** (0x100000 y 0x33F400) |
| `port/full/mem.c:194-208` (`full_patch_range`) | escribe `jmp rel32` **en la dirección PS2 de cada función** (dentro de la RAM) apuntando al C nativo en 0x40000000 |
| `port/full/plat_mem.c:1-7` | el heap del juego (malloc de newlib) es un first-fit sobre **[0x430590, 0x1EFE000)**, o sea adentro de la RAM emulada |
| `tools/PS2Recomp/ps2xRuntime/src/lib/ps2_memory.cpp:355-366` | **también** el build híbrido (`port/CMakeLists.txt`, `PS2X_IDENTITY_RDRAM`) mapea la RAM del guest en 0x10000 con `mmap` |

O sea: no es solo `mem.c`; **los dos builds de BT2** necesitan RAM en direcciones absolutas bajas. En Windows no hay
`mmap` y no hay garantía de que 0x100000..0x2000000 esté libre.

### 2.2 Lo que hay que mapear (medido)

- RAM: **0x100000..0x2000000** (31 MB). El ELF empieza en 0x100000 (`readelf -l gamedata/SLUS_214.41`: `LOAD
  off 0x1000 vaddr 0x100000 filesz 0x23f390`, `LOAD vaddr 0x33f400 memsz 0x73c38`); lo más bajo que toca el C del
  juego es 0x100000 (los absolutos de datos arrancan en 0x33B680, el heap en 0x430590). 0x0..0x10000 tampoco existe
  en Linux (lo dice `mem.c:5-6`: `vm.mmap_min_addr`), así que Windows puede perder la misma franja.
- Espejos: 0x20000000 y 0x30000000 (32 MB cada uno, alias de la RAM).
- Registros: 0x10000000 (64 KB), 0x12000000 (8 KB), scratchpad 0x70000000 (16 KB).
- Código nativo: 0x40000000..~0x41650000 (`readelf -lW port/build/full/bt2full`: último `LOAD` termina en
  0x4164BBF0).
- Pila del juego: 8 MB debajo de 4 GB (`mem.c:344`, `MAP_32BIT`), con `getcontext/makecontext/swapcontext`.

### 2.3 La realidad de Windows

- Los primeros 64 KB **no se pueden mapear** (como en Linux con `mmap_min_addr`); BT2 ya asume eso.
- El loader mapea la imagen del exe **antes** de crear la pila del hilo inicial, pero la pila se elige al azar en el
  espacio libre; en procesos x64 suele caer en los primeros MB (0x1xxxxx-0xAxxxxx), justo dentro de
  [0x100000, 0x2000000). Evidencia del proyecto hermano: `docs/port/README.md:1018-1019` — "the game heap at its PS2
  address if free, else anywhere below 2 GB (a Windows process has its first stack and heap there)".
- `VirtualAlloc`/`MapViewOfFileEx` **sí** pueden pedir una dirección exacta, y `CreateFileMapping` sobre pagefile +
  `MapViewOfFileEx` **sí** permite aliasear la misma sección en 3 direcciones (equivalente a `memfd`+`mmap` de
  `mem.c:57-58`). La única duda es que las direcciones estén libres.
- **No hay forma de aliasear memoria que ya está dentro de una imagen PE.** Si la RAM se mete en el `.exe` (la única
  manera determinista de reservarla antes de que la pila se ubique), los espejos dejan de existir.

### 2.4 Los espejos se pueden eliminar (con un cambio chico y verificable)

Los espejos se usan porque las **cadenas DMA** del juego llevan en el tag la dirección de los datos con el nibble
alto 2 o 3:

- `src/battle/xi_28B058.c:10`: `p[0] = (s32)((arg1 >> 4) + 0x30000000);` — tag id=3 (REF) apuntando a datos.
- `port/full/gs/gs_core.c:1417-1447` (`Port_GsGifChannel`): `uint32_t ref = tag[1]; ... Gs_Gif((const
  uint8_t *)(uintptr_t)ref, n);` — **desreferencia el valor tal cual**.
- `port/full/gs/gs_core.c:1239-1274` (`race_walk`, herramienta) y `:1535+` (`run_chain`): lo mismo.

Con los espejos mapeados eso funciona; sin ellos, hay que normalizar en esos 3-5 puntos:
`if ((a >> 28) == 2 || (a >> 28) == 3) a &= 0x0FFFFFFF;`. Es el mismo tipo de arreglo que T3D ya hizo con
`VU1_ADDR_MASK` (`docs/port/README.md:1032-1034`) — y el mismo lugar donde T3D se comió la pelea en negro, así que
**se prueba primero en Linux**.

No encontré otro lugar del port que desreferencie 0x2xxxxxxx/0x3xxxxxxx (grep en `port/full`, `port/src`, `src`):
fuera de las cadenas, las apariciones son flags (`BTLB_TRIANGLE`, `DMA_TAG_*`) que no se desreferencian. Eso es
evidencia a favor de la normalización, pero **no es prueba**: hay que correrlo.

---

## 3. Inventario POSIX → Win32 (`archivo:línea`)

Leyenda: **B** = bloqueante (hay que reescribir), **C** = cambio chico, **N/A** = no entra en `bt2full` (es del
build híbrido/herramienta), **OK** = mingw-w64 lo tiene.

### 3.1 Bloqueantes

| Qué | Dónde | Windows |
|---|---|---|
| `mmap` + `memfd_create` de la RAM y espejos | `port/full/mem.c:57-58`, `:237`, `:240-241`; también `tools/PS2Recomp/ps2xRuntime/src/lib/ps2_memory.cpp:355-366` (híbrido) | **B**: `CreateFileMapping(INVALID_HANDLE_VALUE,...)` + `MapViewOfFileEx` ×3 (diseño A) o sección `.ps2ram` en el PE (diseño B). Sin `memfd` |
| `mallopt(M_MMAP_MAX/M_ARENA_MAX)` | `mem.c:235-236` | **B**: no existe; sacar (su fin era que el malloc del host quedara por brk debajo de 4 GB; en Windows el heap ya está bajo y el port no guarda punteros de malloc del host en campos de 32 bits) |
| Pila del juego con `getcontext/makecontext/swapcontext` | `mem.c:299`, `:347-354` | **B**: mingw no tiene ucontext (verificado: no hay `getcontext`/`makecontext`/`swapcontext` en `/usr/x86_64-w64-mingw32/include`). Copiar el esquema de T3D: `VirtualAlloc` bajo + `Port_CallOnStack` en asm + actualizar `TEB.StackBase/StackLimit/DeallocationStack` (`t3d port/src/plat_mem.c:120-165`) |
| `sigaction`/`sigaltstack`/SIGSEGV/SIGBUS/SIGILL/SIGFPE/SIGABRT | `mem.c:330-341` | **B**: `AddVectoredExceptionHandler` (`EXCEPTION_ACCESS_VIOLATION/ILLEGAL_INSTRUCTION/INT_DIVIDE_BY_ZERO/...`), como `t3d port/src/plat_crash.c:6-40,131`. El volcado de registros sale de `CONTEXT`, no de `ucontext_t` |
| `dladdr` (nombre de la función que escribió) | `mem.c:72,109,122` | **B**: `RtlCaptureStackBackTrace` + `GetModuleHandleEx/GetModuleFileName` y el `.map` (T3D, `plat_crash.c:44-60,107`) |
| `backtrace`/`backtrace_symbols_fd` (`execinfo.h`) | `mem.c:16,177-180,283`; `port/full/plat_mem.c:13,59,89`; `plat_trace.c:73,92` | **B**: reemplazar por `RtlCaptureStackBackTrace` (o `#ifdef` y dejar el diagnóstico fuera del release) |
| `mprotect` de los watchpoints (B3/B25) | `mem.c:78,95,116,130,139` | **B** (herramienta): `VirtualProtect(PAGE_READONLY)` + `EXCEPTION_SINGLE_STEP`/trap flag; o compilarlo solo en Linux |
| `signal(SIGUSR2)` para volcar la RAM | `mem.c:314-326,341` | **B** (herramienta): tecla/flag o `#ifdef` |
| `signal(SIGUSR1)` del build instrumentado | `plat_trace.c:167` | **B** (solo `BT2_TRACE_BUILD`): `#ifdef` |
| `__executable_start`/`etext` (símbolos del linker ELF) | `mem.c:165-166` | **B**: no existen en PE; usar `GetModuleHandle(NULL)` + cabeceras PE (o el rango de la sección `.text`) |
| Rango duro 0x41800000..0x42000000 para escanear la pila | `mem.c:168` | **C** pero hay que cambiarlo: depende de dónde quede la pila nueva |

### 3.2 Cambios chicos (shims mecánicos)

| Qué | Dónde | Windows |
|---|---|---|
| `opendir/readdir/closedir` (resolver mayúsculas del AFS) | `plat_file.c:160,183-188`; `plat_mc.c:22,192-200` | `_findfirst/_findnext` o `FindFirstFileA`; en Windows el filesystem ya es case-insensitive, así que alcanza con saltear el branch |
| `strcasecmp/strncasecmp` | `plat_file.c:173,187` | mingw los exporta (`nm libmsvcrt.a`: `strcasecmp`, `strncasecmp` T) → **OK** |
| `stat` | `plat_sdk.c:9,51`; `plat_mc.c:203` | `#define stat _stat` (o `_stat64`) |
| `mkdir` | `plat_mc.c:57-59,129` | ya tiene `#define mkdir(path,mode) _mkdir(path)` en `plat_mc.c:28-30` |
| `mmap(MAP_32BIT)` del buffer de tiras de video (su dirección se entrega al juego como u32) | `plat_movie.c:33,121,267` | `VirtualAlloc` en una dirección baja elegida (p. ej. 0x30000000) |
| `popen/pclose` (grabación mp4, herramienta) | `gs_gl.c:22-23,1210-1213` | `_popen/_pclose` (mingw los tiene); o `#ifdef` |
| rutas `/tmp/...` por defecto | `plat_fightlog.c:88,92`; `mem.c:316`; `plat_trace.c:34` | `%TEMP%` o `#ifdef` |
| `setenv` (ULTRALOG) | `plat_trace.c:151` | `_putenv_s` (herramienta) |
| `clock_gettime`/`nanosleep` | `gs_core.c:1337`; `plat_gs.c:67,89,153`; `plat_movie.c:89,280`; `plat_snd_adx.c:403,464`; `plat_sys.c:71`; `mem.c:254` | **OK** con winpthreads (`nm libwinpthread.a`: `clock_gettime`, `nanosleep` T) |
| `pthread_*`, `pthread_once` | `gs_core.c:25,1224-1403`; `gs_input.c:57,99-102`; `plat_settings_bt3.c:20-93`; `mem.c:353` | **OK** con `-lwinpthread` |
| `getenv`, `fopen`, `snprintf`, `sscanf`, `strtoul` | todo el port | **OK** |

### 3.3 Del build (Python) — no es C pero rompe igual

| Qué | Dónde | Qué hacer |
|---|---|---|
| `systemd-run` en **todos** los pasos pesados | `scripts/capped.sh:12` (lo usan `link_full.py:112,449` y `:198`) | en Windows/MSYS2 no existe: envolver en `try/except`/`if os.name == "nt"` y correr directo |
| `gcc`/`g++` del host | `link_full.py:95,104,188,198,445` | `PREFIX` mingw (como `toolchain.py` de T3D) |
| `clang` sin target | `build_full.py:96`; `gen_native.py:136-138,165` | `--target=x86_64-w64-mingw32`, `-mno-ms-bitfields`, `-D__CRT__NO_INLINE` (T3D `undefined.py:24-26`) |
| `ptr32.py` con `-m64` | `build_full.py:100`; `ptr32.py:18` (libclang) | pasarle el target mingw (`t3d undefined.py:48-49`); libclang existe para Windows |
| `nm -D /usr/lib/libc.so.6` y `/usr/lib64` | `link_full.py:84-95` (`host_syms`) | no existe: lista fija de nombres de libc + `nm` sobre `libmsvcrt.a`/`libucrt.a`/`libmingwex.a`, o el esquema de 2 pasadas de T3D (`link.py:29-40`: link, leer "undefined reference", generar stubs) |
| `gcc -print-libgcc-file-name` + `nm` del libgcc | `link_full.py:89` | mingw lo imprime; `nm` compatible |
| `pkg-config --libs sdl3` | `link_full.py:202` | `-L<SDL3>/lib -lSDL3` (T3D `toolchain.sdl3()`) |
| `link.ld` (script ELF) | `link_full.py:346-350` y `:446` | en PE: **response file con 6229 `--defsym`** + 297 alias (GNU ld PE soporta `--defsym`, verificado en `x86_64-w64-mingw32-ld --help`), y `--image-base`/`--section-start` en vez de `-Ttext-segment` |
| flags `-no-pie`, `-fno-pie`, `-rdynamic`, `-Wl,-z,noexecstack` | `link_full.py:445-448` | no existen en PE: sacar |
| `stubs.c` generado con asm ELF | `link_full.py:391` (`movl $imm,%r11d; jmp bt2_fb_entry`), `:401` (`jmp name@PLT`), `.type sym,@function` | 656 bloques `__asm__`: `.type`/`.size` y `@PLT` son ELF; en COFF hay que usar `.globl` solo y, para libc, `jmp *__imp_name(%rip)` (22 líneas `bt2l_*`) |
| `objcopy --weaken-symbol/--redefine-sym` | `link_full.py:340` | `x86_64-w64-mingw32-objcopy` soporta ambas |
| Línea de enlace con 9745 objetos | `link_full.py:445-448` | **obligatorio** response file (`@`) por el límite de 32767 de `CreateProcess` |
| `port/CMakeLists.txt` (build híbrido) | — | no es el build de publicación (PS2Recomp es GPL, ver `docs/PLAN_PUBLICACION.md:1.1`) y su RAM es Linux-only |

### 3.4 No es problema

- `port/src/storewatch.cpp` (`mmap`, `mprotect`, `sigaction`) **no entra** en `bt2full`: `link_full.py:445` compila
  solo `port/full/*.c` como host. Es del build híbrido.
- `aligned_alloc`/`posix_memalign`: no se usan en el port (el `memalign` del juego lo sirve `plat_mem.c:121`).
- `__builtin_*`: en `port/full` no hay ninguno; en `port/eq`/`src` son `__builtin_memcpy` (422), `memset` (157),
  `fabsf`, `sqrtf` y `__builtin_return_address` (13): clang y mingw-gcc los soportan (el de `return_address` puede
  devolver algo distinto en Windows, pero no es bloqueante).

---

## 4. Las tres rutas

| | (a) mingw-w64 cruzado desde Linux | (b) MSYS2 nativo | (c) MSVC nativo |
|---|---|---|---|
| Herramientas | `x86_64-w64-mingw32-gcc/g++/as/objcopy/nm` (**ya instalados**, GCC 16.2.0 posix) + `clang --target=x86_64-w64-mingw32` (clang 23.1.4) | el mismo toolchain dentro de MSYS2 CLANG64/UCRT64 | `cl.exe`/`link.exe` |
| Python | host Linux (ya está) | Python de MSYS2 | nativo |
| SDL3 | paquete `SDL3-devel-*-mingw.tar.gz` (oficial) | paquete mingw de MSYS2 | paquete MSVC oficial de SDL3 |
| ffmpeg | DLLs LGPL de BtbN o paquetes mingw de MSYS2 | idem | libs MSVC (vcpkg/descarga) |
| Cambios de código | los de la sección 3 | los mismos | **mucho más**: sin `--defsym` (6229 símbolos absolutos), sin `--wrap`, sin asm AT&T (`mem.c`/`stubs.c`), sin `__attribute__`, `__ptr32` existe pero el pipeline es libclang/clang; `-mno-ms-bitfields` no aplica |
| Riesgo | **bajo** en toolchain, alto en memoria (sección 2) | igual, más lento de iterar, mejor para depurar en la máquina real | **muy alto**: reescribir el enlace y el asm; no lo hace ni T3D con años de ventaja |
| Esfuerzo | **el más barato**; es lo que usa T3D para publicar | same code, +0.5 día de setup | semanas extra, no recomendado |

**Recomendación: (a) mingw-w64 cruzado**, igual que T3D (`docs/port/README.md:1010-1015`), y (b) MSYS2 solamente para
depurar en Windows cuando algo falle. (c) MSVC: descartado (ver sección 8).

Alternativas descartadas de entrada: WSL/WSLg (no es un port de Windows: exige WSL instalado y GPU passthrough),
"que el usuario apague Mandatory ASLR" (no publicable), compilar un binario de 32 bits (el port nativo está hecho
para x86-64 con `__ptr32`; un i386 sería otro port, y el espacio de 2 GB de Windows está todavía más ocupado).

---

## 5. Inventario de dependencias de `bt2full` hoy

De `link_full.py:445-448` y `ldd port/build/full/bt2full`:

| Dependencia | Cómo entra | Windows |
|---|---|---|
| **SDL3** | `pkg-config --libs sdl3` (`link_full.py:202`), `#include <SDL3/SDL.h>` en `gs/*.c`, `plat_snd_*` | paquete oficial mingw y MSVC; `SDL3.dll` al lado del exe |
| **ffmpeg**: `libavformat`, `libavcodec`, `libswscale`, `libavutil` | `plat_movie.c:34-37` (demux MPEG-PS/SFD + decode MPEG-2 + swscale) | DLLs LGPL (BtbN/MSYS2) o estático; **o** reusar el decoder MPEG-2 propio de T3D y sacar ffmpeg (`t3d docs/port/README.md:1063-1078`) |
| OpenGL | **no se linkea**: todo por `SDL_GL_GetProcAddress` (`gs_gl.c:192`) | ídem (opengl32 del sistema) |
| `libm`, `libpthread`, `libstdc++`, `libgcc` | `-lm -lpthread -lstdc++` + `-static-libstdc++/gcc` | `-lm` no-op, winpthreads, libstdc++/libgcc estáticos |
| **ImGui** | fuente vendorizada `port/third_party/imgui`, compilada con g++ (`link_full.py:189,198`) | ídem, mingw g++ |
| **xxhash** | header `port/third_party/xxhash` con `XXH_INLINE_ALL` (`gs_texpack.c:23-24`) | ídem |
| **zstd** | **no se usa** (ni en el link ni en el código; lo que aparece es de ffmpeg, transitivo) | — |
| `libxml2`, `bz2`, `dvdnav`, `gnutls`, etc. | transitivas del ffmpeg del sistema (ffmpeg 8 de Arch) | **no** son dependencias del port: con un ffmpeg mingw mínimo desaparecen |
| Python + libclang | `ptr32.py`, `build_full.py`, `link_full.py` | libclang/`clang.cindex` existe para Windows; T3D lo usa así |

Cosas a tener presentes al empaquetar: licencias (SDL3 zlib, ImGui MIT, xxhash BSD-2, ffmpeg LGPL si es shared) y
**no** distribuir `gamedata/SLUS_214.41` ni el AFS (el release lleva exe + DLLs; los datos salen del ISO del usuario).

---

## 6. Plan por pasos (con la decisión de memoria primero)

### Fase 0 — Probar en Linux que los espejos no hacen falta (0.5–1 día)

Objetivo: reducir el riesgo más grande **sin Windows**. BT2 no tiene ningún test headless como el "replay" de T3D,
así que la prueba es jugar (el usuario) con una build en la que `mem.c` **no mapea** 0x20000000/0x30000000 (o mapea
páginas `PROT_NONE`) y con las cadenas normalizadas:

1. agregar el helper `chain_addr()` (sección 7.3) en `gs_core.c` (`Port_GsGifChannel`, `run_chain`, `race_walk`) y,
   si hace falta, en `gs_sony.c`;
2. agregar un `BT2_NO_MIRRORS=1` que saltee `map_at(0x20000000)`/`map_at(0x30000000)` (`mem.c:240-241`) y build;
3. jugar un combate con modelos, HUD y un especial (que es donde se suben texturas por GIF);
4. si crashea, el dump dice quién: ahí se decide si la RAM tiene que venir con alias (diseño A) o no.

Es el mismo camino que hizo T3D con `VU1_ADDR_MASK` (`docs/port/README.md:1032-1034`): el bug se ve enseguida.

### Fase 1 — Spike del layout PE (0.5–1 día, sin tocar BT2)

Un `hello.exe` con mingw que valide lo que no sé de memoria y que puedo probar bajo Wine/VM barato:

- `--image-base 0x10000` (cabeceras), una sección `.ps2ram` de 31 MB **sin datos** en 0x100000 y `.text` en
  0x2100000 (o en 0x40000000, imagen de 1 GB);
- `--disable-dynamicbase --disable-reloc-section`;
- verificar: que GNU ld PE acepte las VMAs (`--section-start`, o un script `-T`), que la tabla de secciones quede
  **ascendente**, que `SizeOfImage` sea coherente, que Windows/Wine cargue y que `VirtualAlloc(0x100000)` falle
  (porque ya está la imagen) y `VirtualAlloc(0x30000000)` funcione para la pila;
- imprimir `GetModuleHandle(NULL)` y `NtCurrentTeb()->StackBase` para ver dónde cayó la pila del proceso.

Si el layout no sale con `--section-start`, la variante B' es: **exe = RAM** (imagen chica de 31 MB en 0x10000) y
**DLL = programa** en 0x40000000 (así el código nativo no se mueve y se evita la imagen de 1 GB). Es más plumbing
pero conserva todas las direcciones de hoy.

### Fase 2 — Plomería de toolchain (1 día)

- `port/tools/toolchain.py` (nuevo, copiando el de T3D): `BT2_CC=win64`, `PREFIX`, `CLANG_TARGET`, `sdl3()`;
- `build_full.py`: target en `clang -E` y en `ptr32.py`, y pasar `-mno-ms-bitfields -D__CRT__NO_INLINE` al compilar;
- `gen_native.py`: `CLANG_FLAGS` con `--target` (no se usa en `bt2full`, pero está en el repo);
- `scripts/capped.sh`: si no hay `systemd-run`, ejecutar directo;
- build del renderer (`link_full.py:185-202`) con `PREFIX+gcc/g++` y `-I/-L` de SDL3 mingw.

### Fase 3 — `mem` de Windows (2–3 días)

- `mem_win.c`/`#ifdef`: sección de RAM (diseño B) o `CreateFileMapping`+3 vistas (diseño A); registros y scratchpad
  con `VirtualAlloc`; `VirtualProtect` de la RAM a RWX solo si hace falta ejecutar desde ahí;
- pila del juego: `VirtualAlloc` bajo + `Port_CallOnStack` + TEB (copiar de T3D) y sacar `ucontext`;
- crash: `AddVectoredExceptionHandler` con `CONTEXT` y volcado a archivo; sin `dladdr`/`backtrace` (o DbgHelp);
- herramientas (watchpoints, dump de RAM, traza) detrás de `#ifndef _WIN32` para el release.

### Fase 4 — Enlace PE (3–5 días, la parte más rompehuesos)

- `link_full.py`: generar `defsym.rsp` (`--defsym=N=0x...` ×6229 y alias) en lugar de `link.ld`;
- `stubs.c`: `.globl` sin `.type`, sin `@PLT` (22 `bt2l_*` con `jmp *__imp_x(%rip)`), resto del asm AT&T válido;
- `host_syms()` con lista/import libs de mingw; el resto de la lógica (alias por dirección, `game_*`, weaken,
  `tables.c`) es portable;
- línea de enlace PE + `@rsp` obligatorio; `--image-base`, `--disable-reloc-section`, `-mwindows`,
  `-static-libgcc -Bstatic -lstdc++ -lwinpthread -Bdynamic -lSDL3` + ffmpeg;
- map file (`-Wl,-Map`) sigue funcionando y sirve para el crash report.

### Fase 5 — Shims de plataforma (1 día)

`plat_file.c`/`plat_mc.c`/`plat_sdk.c` (dirent/stat), `plat_movie.c` (VirtualAlloc bajo), `gs_gl.c` (`_popen`),
rutas `/tmp`, `setenv`, y `plat_file.c:215` (`buf >= 0x40000000u` deja de ser cierto si el código baja a 0x2100000:
usar el rango real del módulo).

### Fase 6 — Dependencias y empaquetado (1–2 días)

SDL3 mingw dev package; decidir ffmpeg (DLLs LGPL vs. decoder propio de T3D vs. `ffmpeg.exe`); zip con exe + DLLs +
README + licencias + `play.bat`; script de extracción del ISO (equivalente al `install.py` de T3D).

### Fase 7 — Pruebas y bugs de ABI (3–8 días)

Wine primero (layout, arranque, menú, pelea), VM Windows después (el usuario). Esperar los bugs que Windows ya le
mostró a T3D: punteros de 4 bytes pasados por stack (`docs/port/README.md:1026-1031` — BT2 tiene el mismo `ptr32.py`,
¿la versión de BT2 ya incluye el arreglo?), `__ptr32` que mingw define a vacío (habrá que `#undef` en los archivos
del port, `docs/port/README.md:1025`), bitfields con `-mno-ms-bitfields`, `getenv` lento (BT2 ya tiene
`Port_GetEnv`, `gs_core.c:1344-1371`, así que este ya está resuelto).

### Estimación

| Fase | Días |
|---|---|
| 0 espejos (Linux) | 0.5–1 |
| 1 spike PE | 0.5–1 |
| 2 toolchain | 1 |
| 3 memoria | 2–3 |
| 4 enlace PE | 3–5 |
| 5 shims | 1 |
| 6 deps/zip | 1–2 |
| 7 pruebas/ABI | 3–8 |
| **Total** | **12–22 días de trabajo** (~2–4.5 semanas) |

Riesgo dominante: la fase 0/1 (memoria). Si la fase 0 falla (los espejos sí hacen falta) hay que ir a diseño A y
rezar por las direcciones bajas, o aceptar mantener Windows "best effort".

---

## 7. Cambios propuestos (bocetos, **no aplicados**)

### 7.1 `mem.c` partido por plataforma

```diff
--- a/port/full/mem.c
+++ b/port/full/mem.c
@@
-#define _GNU_SOURCE
-#include <errno.h>
-#include <execinfo.h>
-#include <malloc.h>
-#include <signal.h>
-#include <sys/mman.h>
-#include <pthread.h>
-#include <ucontext.h>
-#include <time.h>
-#include <unistd.h>
+#ifdef _WIN32
+#include <windows.h>
+#include <stdint.h>
+#include <stdio.h>
+#include <stdlib.h>
+#include <string.h>
+#include "mem_win.inc"      /* map_memory/on_segv/game_entry de Windows */
+#else
+#define _GNU_SOURCE
+#include <errno.h>
+#include <execinfo.h>
+#include <malloc.h>
+#include <signal.h>
+#include <sys/mman.h>
+#include <pthread.h>
+#include <ucontext.h>
+#include <time.h>
+#include <unistd.h>
+#include "mem_posix.inc"    /* lo de hoy, movido tal cual */
+#endif
```

`mem_win.inc`, diseño A (vistas de una sección pagefile; es el equivalente exacto de `mem.c:237-241`):

```c
static HANDLE sMap;
static void *view(uintptr_t at, size_t size, uint64_t off) {
    void *p = MapViewOfFileEx(sMap, FILE_MAP_ALL_ACCESS, (DWORD)(off >> 32), (DWORD)off, size, (void *)at);
    if (p != (void *)at) {
        fprintf(stderr, "bt2full: no se pudo mapear 0x%llX (%lu)\n", (unsigned long long)at, GetLastError());
        ExitProcess(2);
    }
    return p;
}
__attribute__((constructor(101))) static void map_memory(void) {
    sMap = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, RAM_SIZE, L"ps2ram");
    if (sMap == NULL) { fprintf(stderr, "bt2full: CreateFileMapping: %lu\n", GetLastError()); ExitProcess(2); }
    view(0x100000u, RAM_SIZE - 0x100000u, 0x10000u);   /* RAM (mismo offset que hoy: 0x10000) */
    view(0x20000000u, RAM_SIZE, 0);                    /* espejo uncached */
    view(0x30000000u, RAM_SIZE, 0);                    /* espejo UCAB */
    VirtualAlloc((void *)0x70000000u, 0x4000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    VirtualAlloc((void *)0x10000000u, 0x10000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    VirtualAlloc((void *)0x12000000u, 0x2000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}
```

Diseño B (RAM dentro de la imagen del exe): no va en `mem.c` sino en el link (7.2) + `load_elf` igual que hoy;
la RAM es una sección RW del propio módulo, y `VirtualProtect(0x100000, 0x1F00000, PAGE_EXECUTE_READWRITE)` después
de cargar el ELF si alguna vez se ejecuta desde ahí.

### 7.2 `link_full.py` — enlace PE (esquema)

```diff
-    link.ld = ... absolutos y alias ...
-    cmd = ["gcc", "-no-pie", "-m64", ... str(OUT/"link.ld"), "-Wl,-Ttext-segment=0x40000000", "-Wl,-z,noexecstack", ...]
+    if WIN:
+        # 6229 absolutos + 297 alias como --defsym (GNU ld PE los soporta)
+        rsp = OUT / "defsym.rsp"
+        rsp.write_text("\n".join([f"--defsym={n}=0x{a:08X}" for n, a in sorted(absolutes.items())] +
+                                 [f"--defsym={n}={s}" for n, (s, a) in sorted(alias.items())]))
+        cmd = [PREFIX + "gcc", "-w", "-g", "-O1", "-o", str(exe), *hostc, str(OUT/"stubs.c"),
+               str(OUT/"tables.c"), *final, "@" + str(rsp),
+               "-Wl,--image-base,0x10000",              # cabeceras
+               "-Wl,--section-start=.ps2ram=0x100000",  # RAM del PS2 (ver ps2ram.o)
+               "-Wl,--section-start=.text=0x2100000",   # C nativo, arriba de la RAM
+               "-Wl,--disable-dynamicbase", "-Wl,--disable-reloc-section",
+               "-Wl,--disable-high-entropy-va", "-Wl,--stack,0x100000",
+               "-static-libgcc", "-Wl,-Bstatic", "-lstdc++", "-lwinpthread", "-Wl,-Bdynamic",
+               "-L" + str(sdl3() / "lib"), "-lSDL3", "-lavformat", "-lavcodec", "-lswscale", "-lavutil",
+               "-lm", "-mwindows", f"-Wl,-Map={exe}.map"]
+        cmd = [cmd[0], "@" + str(write_link_rsp(cmd[1:]))]   # limite 32767 de CreateProcess
```

con un `ps2ram.o` generado una vez:

```asm
        .section .ps2ram,"aw",@nobits
        .globl __bt2_ps2ram
__bt2_ps2ram:
        .space 0x1F00000          # 0x100000..0x2000000
```

(Detalle: con base de imagen 0x10000 las cabeceras PE ocupan ~0x400 bytes; si se quiere conservar casi toda la
franja 0x10000..0x100000 que Linux mapea, la sección puede empezar en 0x11000 (RVA 0x1000, alineada a 4 KB) y cubrir
0x11000..0x2000000. En la práctica el ELF empieza en 0x100000 y nada del juego toca por debajo, pero es gratis.)

(y la alternativa B': `.exe` con esa sección + `.dll` con el programa en 0x40000000).

### 7.3 Normalización de direcciones en las cadenas DMA (fase 0)

```diff
--- a/port/full/gs/gs_core.c
+++ b/port/full/gs/gs_core.c
@@
+/* Las cadenas DMA del juego llevan la direccion de los datos con el nibble alto en 2 o 3 (uncached/UCAB).
+   Sin los espejos mapeados (Windows: la RAM no se puede aliasear), se normaliza al espejo de RAM. */
+static uint32_t chain_addr(uint32_t a) {
+    return ((a >> 28) == 2u || (a >> 28) == 3u) ? (a & 0x0FFFFFFFu) : a;
+}
@@ void Port_GsGifChannel(uint32_t addr, uint32_t qwc, int chain) {
-        uint32_t n = tag[0] & 0xFFFF, id = (tag[0] >> 28) & 7, ref = tag[1];
+        uint32_t n = tag[0] & 0xFFFF, id = (tag[0] >> 28) & 7, ref = chain_addr(tag[1]);
@@ static void run_chain(uint32_t tadr, int tte) {
-            ... tag[1] / addr = tag[1] ...
+            ... chain_addr(tag[1]) ...
```

(mismos 3 puntos: `Port_GsGifChannel` 1417-1447, `run_chain` 1535+, `race_walk` 1239-1274.)

### 7.4 `plat_file.c:215` — el chequeo de "puntero del host"

```diff
-extern u32 full_native_to_ps2(uintptr_t p);
+extern u32 full_native_to_ps2(uintptr_t p);
+extern char __ImageBase;   /* PE: base del modulo */
 s32 sceRead(s32 fd, u32 buf, s32 size) {
-    if (buf >= 0x40000000u) { u32 a = full_native_to_ps2(buf); if (a) buf = a; }
+    if (buf >= (u32)(uintptr_t)&__ImageBase) { u32 a = full_native_to_ps2(buf); if (a) buf = a; }
```

### 7.5 `build_full.py` / `gen_native.py`

```diff
-    r = subprocess.run(["clang", "-E", "-m64", "-I", ..., str(src), "-o", str(pre)], ...)
+    target = ["--target=x86_64-w64-mingw32"] if WIN else []
+    r = subprocess.run(["clang", "-E", *target, "-m64", "-I", ..., str(src), "-o", str(pre)], ...)
@@
-    r = subprocess.run([sys.executable, ..., "ptr32.py", str(pre), "-m64", "-fms-extensions", ...])
+    r = subprocess.run([sys.executable, ..., "ptr32.py", str(pre), *(target or ["-m64"]), "-fms-extensions",
+                        *(["-mno-ms-bitfields"] if WIN else []), ...])
```

---

## 8. Qué descarté y por qué

| Descartado | Motivo |
|---|---|
| **MSVC** | el enlace depende de 6229 símbolos **absolutos** (equivalente a `--defsym`) y de `--wrap`; `stubs.c` y `mem.c` usan asm AT&T y `__attribute__`; el pipeline es clang/libclang. Rehacerlo para `link.exe` es más caro que todo lo demás junto. Ni T3D (que tiene el port más maduro) lo intentó |
| **Build de 32 bits** | el port nativo es x86-64 con `__ptr32` (`ptr32.py`, `-msse4.1`, `R_X86_64_32`); un i386 sería otro port, y el espacio de usuario de 2 GB en Windows está peor |
| **Espejos por copia/sincronización** | los tags DMA apuntan a la RAM; una copia no es alias. O alias real (diseño A) o normalización |
| **`VirtualAlloc` a 0x100000 como plan principal** | puede funcionar, pero depende de la suerte del layout de cada máquina; T3D ya documenta que las direcciones PS2 las ocupa la pila/heap (`README:1018`) |
| **Pedirle al usuario que desactive Mandatory ASLR / Bottom-up ASLR** | no publicable; T3D ya se comió ese bug (`README:1237-1246`) y lo resolvió con `--disable-reloc-section` |
| **WSL/WSLg / Proton** | no es un port de Windows; requisitos externos y GPU |
| **`memfd_create` con nombre** | Windows no tiene; `CreateFileMapping` pagefile es el equivalente |
| **vcpkg/conan/submódulos** | T3D no los usa; acá tampoco hacen falta (ImGui/xxhash vendorizados, SDL3 y ffmpeg binarios) |

---

## 9. Evidencia que falta (lo que hay que medir, no adivinar)

1. **¿0x100000..0x2000000 está libre en un Windows real con la imagen en 0x10000?** Se responde con el spike (fase 1)
   y con `GetModuleHandle`/`TEB.StackBase` impresos al arrancar. En Wine **no** vale como prueba (layout distinto).
2. **¿Los espejos se usan solo en las cadenas?** Fase 0: jugar en Linux con 0x20000000/0x30000000 sin mapear.
3. **¿GNU ld PE ordena las secciones por VMA** con `--section-start` (o hace falta script `-T`/B')? Spike.
4. **¿Qué hace el `.exe` de 31 MB de bss al cargar** (commit, antivirus, Wine)? Spike.
5. **ffmpeg**: ¿el `.SFD` de BT2 es MPEG-2 todo-intra como los `.PSS` de T3D? Si sí, se puede reusar
   `plat_mpeg2.c` y no linkear ffmpeg (menos DLLs y menos licencias). No lo verifiqué.
6. **ABI**: si la versión de `ptr32.py` de BT2 ya trae el arreglo de "puntero de 4 bytes pasado por stack" de T3D
   (`README:1026-1031`). El archivo dice ser de T3D; no comparé las dos versiones.
7. **SDL3 GPU en la VM**: `gs_gpu.c:69,356` pide solo `SDL_GPU_SHADERFORMAT_SPIRV`, así que en Windows el backend
   "gpu" es **Vulkan** (D3D12 quedaría afuera); si la VM no tiene Vulkan, hay que usar GL (`BT3_GS`/`gs_gl.c`).

## 10. Lo que no está en duda

- El C del juego y su modelo de direcciones **no se tocan**: se reescribe el arranque de memoria y el enlace.
- La ruta de compilación barata es mingw-w64 (ya instalado acá) con `clang --target` para el C del juego, exactamente
  el esquema de T3D.
- `bt2full` es el build que hay que portar (el CMake con PS2Recomp es GPL y Linux-only:
  `tools/PS2Recomp/ps2xRuntime/src/lib/ps2_memory.cpp:355-366`).
