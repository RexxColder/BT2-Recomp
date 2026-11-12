# B15 — Map Select: por qué el preview queda estático (la rama live nunca ve `G->0xC4 == 2`)

Investigación de solo lectura. No se compiló ni se ejecutó nada. Todo lo que sigue sale del recompilado
(`port/build/recomp/*.cpp`), del overlay (`disc/DBZP.BIN`, base 0x3B3100), del binario enlazado
(`port/build/full/bt2full`, map + `nm` + `objdump`) y de los dos volcados de RAM.

---

## TL;DR — causa probable

`G->0xC4` no llega a 2 porque en el port **`func_002B8328` (mwPlyGetStat) no es la CRI**: lo pisa el HLE de
`port/full/plat_movie.c:165`, que devuelve **3** cuando no hay una película abierta por el reproductor HLE
(`!M.open`). Y nunca hay película abierta para el preview porque:

1. `func_002B4038` (mwPlyCreateSofdec) también es HLE (`plat_movie.c:132`) y devuelve un **buffer estático del host
   en ceros** (`sPly`), no un handle mwPly real (used=0, stat=0, sfd=0).
2. El juego **sí** intenta arrancar el preview: `func_00419040` → `func_003B4780` → `func_003B4FF8` →
   `func_002BB038` (mwPlyStartAfsLp) con `(handle, ptid=0, flid=0x55B + índice de escenario)`.
   Pero `func_002BB038` es la CRI real (no está HLE) y aborta en la primera línea porque
   `func_002B8280(sPly) != 1` (handle en cero).
3. Sin arranque, `M.open == 0` → GetStat HLE = **3** todos los frames → `G->0xC4 = 3` → en 0x419DC4 se elige
   `func_00418E78` (imagen pre-renderizada) y nunca `func_00418CC8` (cuadro de película a la textura 0x3041).

En resumen: **no falta el renderer ni una carga del juego; falta que el HLE de películas entienda el camino
"mwPlyStartAfs" (películas del AFS), que es el que usa el preview de escenario.**

### Corrección importante sobre la comparación de RAM

El dato del PS2 "descriptor +0x2D8/2DC/2E8 con datos (0x80Fxxxxx)" **es una lectura fuera del objeto**.
`D_00421384` se aloca con 0x1F0 bytes (asm 0x3B43F4: `li a0,496`; memset 0x1F0) y la escena es `D+0x20`.
`scene+0x2D8 = D+0x2F8`, o sea **0x108 bytes más allá del bloque**. Es basura del heap vecino. Los campos que
mira `func_002B8328` son del **handle** `*(scene+0xC0)`, no de la escena. En el handle real del PS2:
`+0x2D8=0`, `+0x2DC=1`, `+0x2E8=1`. (Ver tabla abajo.)

---

## 1. La cadena, con asm

### Selección de rama (overlay DBZP, addr = offset de archivo + 0x3B3100)

```
00419dc0: li   v1,2
00419dc4: lw   v0,196(a0)      ; v0 = G->0xC4
00419dc8: bne  v0,v1,0x419df0  ; != 2  -> estatica
00419dd0: lw   v0,208(a0)      ; G->0xD0
00419dd4: andi v0,v0,0x4
00419dd8: bnez v0,0x419df0     ; bit 4 -> estatica
00419de0: jal  0x418cc8        ; LIVE  (offset 0x66ce0)
00419de8: b    0x419dfc
00419df0: jal  0x418e78        ; ESTATICA (offset 0x66cf0)
```

### Quién pone `G->0xC4` (419E80)

```
00419f08: jal 0x3b46a0                     ; scene update (3B4B90: si GetStat==3 -> mwSfdStop)
00419f14: jal 0x3b5128                     ; a0 = *(G+0xC0)
00419f20: sw  v0,196(v1)                   ; G->0xC4 = v0
00419f28: lw  v0,196(s0)
00419f2c: bnezl v0, ...                    ; si ==0 -> 3B4FF8(...) por cola
```

### Arranque del preview (lo que el port SÍ ejecuta)

```
00419040: ...                              ; func_00419040
00419074: lw   v1,252(v0)                  ; v1 = G->FC[G->D4]  (indice de escenario)
0041907c: addiu v1,v1,1371                 ; + 0x55B  <-- indice de archivo en el AFS
00419090: jal  0x3b4780                    ; crea/reconfigura la escena con el cprm de la pila
0041909c: sw   v0,192(v1)                  ; G->0xC0 = escena
004190a4: jal  0x3b4ff8                    ; ARRANCA la pelicula ya
```

`func_003B4B58` (helper de `3B4780`) hace `GetStat(*(D_00421384+0x20+0xC0))` y devuelve la escena.
`func_003B4780(ptr_cprm)` copia 0x18 bytes a `scene+0x1AC` y llama `func_002B7290(handle,1,scene+0x1AC)`
(mwPlyPause) — o sea, le pasa el índice de archivo a la capa CRI.

`func_003B4FF8(scene)` (asm 0x3B4FF8):

```
3b5040: lw   a2,428(s0)   ; a2 = scene->0x1AC (flid = 0x55B + escenario)
3b5044: lw   a0,192(s0)   ; a0 = scene->0xC0 (handle)
3b5048: jal  0x2bb038     ; mwPlyStartAfsLp(handle, ptid, flid)  (scene->0x1B8 != 0)
3b504c: lw   a1,196(s0)   ; a1 = scene->0xC4 (ptid = 0)
...
3b505c: lw   a0,192(s0)   ; camino alternativo:
3b5060: jal  0x2b73c0     ; mwPlyStartAfs(handle, 0, flid)  (scene->0x1B8 == 0)
3b5064: lw   a1,196(s0)
```

### Nombres reales (strings de la CRI en RAM + comentarios del recompilado)

| addr | nombre | evidencia |
|---|---|---|
| 0x2B6208 | mwPlyInitSfdFx | "E1122611 mwPlyInitSfdFx: iprm is NULL." |
| 0x2B30E0 | mwPlyCalcWorkCprmSfd | "E1122613 mwPlyCalcWorkCprmSfd: cprm is NULL." |
| 0x2B4038 | mwPlyCreateSofdec | "E4061801 ... Number of MWPLY handles..." |
| 0x2B4E18 | mwPlySetFrmSync | "E1122629: mwPlySetFrmSync..." |
| 0x2B7290 | mwPlyPause | "E1122604 mwPlyPause; handle is invalid." |
| 0x2B73C0 | mwPlyStartAfs | "E1122638: mwPlyStartAfs..." |
| 0x2BB038 | mwPlyStartAfsLp | "E1122632: mwPlyStartAfsLp..." |
| 0x2B4FD0 | mwPlyGetCurFrm | "E1122614: mwPlyGetCurFrm..." |
| 0x2B58F0 | mwPlyRelCurFrm | "E1122615: mwPlyRelCurFrm..." |
| 0x2B8328 | mwPlyGetStat | `src/cri/xf_2B82B0.c`, `plat_movie.c:165` |
| 0x2B8280 | `ply->used` (getter) | `src/cri/xf_2B8280.c` |
| 0x2B8398 | GetStat interno (usa `sfd`) | `src/cri/xf_2B82B0.c:92` |
| 0x2B7210 | mwSfdStop | "E1122602 mwSfdStop: handle is invalid." (0x2B7228) |
| 0x2B6E50 | mwPlyStart por nombre (FMV) | `plat_movie.c:134` |
| 0x2D0468 | estado del decoder SFD | `tail func_2C3210`; devuelve `*(sfd+0x48)` |

`func_002B8280(ply)` = `return ply ? ply->used : 0;` (`src/cri/xf_2B8280.c`).
`func_002D0468(sfd)` llama `func_002C3210(sfd)` y devuelve `*(sfd+0x48)`; 4 o 6 significan "decodificando" y
GetStat los mapea a **2** (`src/cri/xf_2B82B0.c:92-101`).

### Quién llena los campos del handle

- `+0x00` (used) y `+0x04` (stat): los pone `func_002B4038` al crear (`used=1`, `stat=0`). El arranque
  (`mwPlyStartAfs/Lp` y sus internos 0x2BAF70/0x2BAD68/0x2BACC8/0x2B3190/0x2B7088) deja `stat=2`
  (el volcado del PS2 lo muestra en 2 y `func_2D0468(sfd)=4`, que GetStat reporta como 2).
- `+0x2D8/+0x2DC/+0x2E8`: `func_002B4038` los deja en 0. `func_002BB038` (StartAfsLp) escribe:
  `+0x2E4=2`, `+0x2EC=arg1(ptid)`, `+0x2F0=arg2(flid)`, `+0x2DC=used`, y `+0x2E8=used` si `+0x2E0==0`
  (`port/eq/2BB038.c`). No los llena nadie más en este camino.

---

## 2. Evidencia de los volcados

### La base del "descriptor" es la misma en los dos

| | PS2 (`/tmp/opencode/ps2save/eeMemory.bin`) | Port (`.../20261111-121635_ram1_f3752.bin`) |
|---|---|---|
| `*(0x42BB80)` G | 0x00C181C0 | 0x00CBCFC0 |
| `*(0x421384)` D | 0x00F4AD00 | 0x00FEF180 |
| `G->0xC0` | 0x00F4AD20 = **D+0x20** | 0x00FEF1A0 = **D+0x20** |
| `G->0xC4` | 2 | **3** |
| `G->0xD0` | 0 | 0 |

Misma instancia: no es "otra copia".

### El handle (esto es lo que importa)

`handle = *(scene+0xC0)`.

| offset | PS2 (handle 0x003453B4) | Port (handle 0x40DE4350) |
|---|---|---|
| +0x000 used | 1 | — (fuera de RAM PS2, host) |
| +0x004 stat | 2 | — |
| +0x03C sfd | 0x01A33500 | — |
| sfd+0x048 | 4 → GetStat=2 | — |
| +0x2D8 | 0 | — |
| +0x2DC | 1 | — |
| +0x2E4 | 2 | — |
| +0x2E8 | 1 | — |
| +0x2EC | 0 (ptid) | — |
| +0x2F0 | **0x55B (flid)** | — |

`+0x2E4=2 / +0x2EC=0 / +0x2F0=0x55B / +0x2DC=1 / +0x2E8=1` es exactamente lo que deja
`func_002BB038` (mwPlyStartAfsLp). **Prueba de que en el PS2 el preview se arrancó con
`StartAfsLp(handle, 0, 0x55B)`.**

En el port, el "handle" es un puntero **del host** (0x40DE4350 ≥ 32 MiB; en el build actual `sPly` está en
0x40DE4370, el dump es de un build previo). No es una dirección PS2: la devuelve el HLE
`func_002B4038 { return (u32)(uintptr_t)sPly; }` y el buffer está en ceros. Cuando una función CRI real lo lee
con `READ32`, el runtime enmascara con `PS2_RAM_MASK` (0x1FFFFFFF) y termina leyendo `0x00DE4350` (bytes de
textura) — por eso no crashea, pero nunca ve `used == 1`.

### La escena del port: creada y configurada, pero sin cuadro de película

Los campos estáticos de la escena coinciden (constructor `3B4A70`: `+0x90..+0xA4`, `+0xB0..`, `+0x160..+0x19C`,
`+0x1A4..+0x1C0`); los que son punteros difieren, como es esperable entre dos corridas.
Además el port tiene `+0x1AC=0x55B`, `+0x1B8=1`, `+0x1BC=0x3000`, `+0x1C0=2` (los dejó `3B4780`) y
`+0xC8=1`, `+0xCC=2` (los dejó `3B4FF8`). O sea, **el camino de arranque se ejecutó**.

`scene+0x00..+0x8F` está en cero en el port porque eso lo llena `func_003B4C20`/`mwPlyGetCurFrm`
(rama live), que nunca corre. En el PS2: `+0x0C=512`, `+0x10=256`, `+0x0=ptr al cuadro`, etc.

### Qué es el flid 0x55B (verificado contra el AFS, solo lectura)

`ZS2US_1.AFS` (partición 0), entrada 0x55B:
- offset 0x2BC1800, tamaño **6.746.112** bytes.
- Empieza con `00 00 01 BA` (MPEG-PS).
- `ffprobe`: **mpeg2video 512x256, 29.97 fps, 8.34 s**.
- Las FMV (ZS2USOP/ZS2USED/LOGO_O) son **512x448**. El HLE actual usa 512x448 fijo (`MW/MH`).

---

## 3. Diagnóstico

1. **No es "otra instancia"**: `D_00421384`, `D+0x20` y los campos estáticos de la escena coinciden.
2. **No es "sin crear"**: la escena existe, está configurada con el cprm y hasta con el flid 0x55B.
3. **El handle mwPly no existe**: es el buffer estático `sPly` del HLE, en ceros. Por eso `func_002BB038`
   (CRI real) aborta con "handle inválido" y no abre el AFS.
4. **GetStat HLE devuelve 3** (`!M.open`), no 0/1/2. Por eso `419E80` escribe 3 en `G->0xC4` todos los frames
   y `419DC4` elige la imagen estática.
5. **No depende del renderer GS ni del alfa**: el estado 3 se decide antes de dibujar. La rama estática
   (418E78) anda porque ya la arreglamos; la live (418CC8) no se ejecuta nunca.
6. Las strings de error de la CRI no aparecen en el log porque el sink `func_002BC630` no escribe a stderr
   (el log solo tiene 10 `[printf]` de arranque). La ausencia de "E1122632" **no** significa que no se llame.

---

## 4. Qué descarté

- **`scene+0x2D8/+0x2DC/+0x2E8` con datos en el PS2**: lectura fuera de la alocación de 0x1F0. No son la causa
  (el handle real tiene 0/1/1 y aun así el PS2 llega a 2).
- **El recompilado de `func_002B8328`**: no se usa. En el binario gana el HLE de `plat_movie.c`
  (`nm`/`objdump` 0x4010e5d8 = `sPresent`/`M.open`/`nanosleep`, no la lógica CRI).
- **Renderer/GS**: no toca esta decisión.
- **`G->0xD0 & 4`**: está en 0; no bloquea la rama live.
- **El contador `0xC8/0xCC`**: el port tiene 1/2 (los escribió 3B4FF8), pero eso no cambia la selección
  (solo mira `0xC4 == 2`).

---

## 5. Arreglo propuesto (mínimo, un solo archivo)

**Archivo: `port/full/plat_movie.c`** (es donde ya viven los HLE de mwPly). Tres piezas:

1. HLE de `func_002B73C0` (StartAfs) y `func_002BB038` (StartAfsLp): leer la entrada `(ptid, flid)` del AFS con
   `Port_ReadAudioFile()` (ya existe en `port/full/plat_file.c:119`) y abrirla con libavformat desde memoria.
2. Dimensiones por película: 512x448 para FMV, **512x256** para el preview (medido con ffprobe).
3. GetStat: devolver **0** mientras el handle HLE no fue arrancado (es lo que espera la CRI), 3 solo si el
   arranque falló o la película terminó.

```diff
--- a/port/full/plat_movie.c
+++ b/port/full/plat_movie.c
@@ -40,6 +40,11 @@
 #define MW 512
 #define MH 448
+typedef struct MemIO { const uint8_t *p; size_t n, pos; } MemIO;
 static struct {
     AVFormatContext *fmt; AVCodecContext *cod; struct SwsContext *sws; AVPacket *pkt; AVFrame *frm;
     int vstream, open, eof, drained, started, frames, shown;
@@ -48,7 +53,14 @@
     uint8_t *strips;     /* cuadro en tiras, direccion de 32 bits (el juego la usa como puntero PS2) */
     int pending;         /* hay un cuadro decodificado esperando su hora */
+    AVIOContext *pb;     /* AVIO sobre memoria (peliculas del AFS) */
+    MemIO *io;
+    int w, h;            /* 512x448 FMV; 512x256 preview de escenario */
+    int loop;            /* mwPlyStartAfsLp */
 } M;
+static int sPlyStarted;  /* ya se intento arrancar: GetStat deja de devolver 0 */
+static uint8_t *sAfsData;
+extern uint8_t *Port_ReadAudioFile(int ptid, int flid, const char *fname, u32 *outSize);

+/* AVIO de solo lectura sobre un bloque en RAM. */
+static int mem_read(void *op, uint8_t *buf, int n) {
+    MemIO *m = op; size_t left = m->n - m->pos;
+    if (left < (size_t)n) n = (int)left;
+    memcpy(buf, m->p + m->pos, n); m->pos += n; return n;
+}
+static int64_t mem_seek(void *op, int64_t off, int whence) {
+    MemIO *m = op;
+    if (whence == AVSEEK_SIZE) return (int64_t)m->n;
+    if (whence == SEEK_CUR) off += (int64_t)m->pos;
+    else if (whence == SEEK_END) off += (int64_t)m->n;
+    if (off < 0 || (size_t)off > m->n) return -1;
+    m->pos = (size_t)off; return off;
+}
+
+/* Igual que open_movie() pero desde memoria; w/h son las dimensiones que espera el juego. */
+static int open_movie_mem(uint8_t *data, u32 size, int w, int h, int loop) {
+    close_movie();
+    M.io = calloc(1, sizeof *M.io); M.io->p = data; M.io->n = size;
+    M.pb = avio_alloc_context(av_malloc(4096), 4096, 0, M.io, mem_read, NULL, mem_seek);
+    M.fmt = avformat_alloc_context(); M.fmt->pb = M.pb;
+    if (!M.pb || avformat_open_input(&M.fmt, "afs", NULL, NULL) < 0) return 0;
+    return finish_open(w, h, loop);   /* ver nota: el cuerpo actual de open_movie() desde
+                                         avformat_find_stream_info() hasta el final */
+}
+
+static void start_afs(int ptid, int flid) {
+    u32 size = 0;
+    close_movie(); free(sAfsData); sAfsData = NULL;
+    sPlyStarted = 1;
+    sAfsData = Port_ReadAudioFile(ptid, flid, NULL, &size);
+    if (!sAfsData || !open_movie_mem(sAfsData, size, MW, 256, 1))
+        fprintf(stderr, "[movie] no se puede abrir AFS (%d,%d)\n", ptid, flid);
+}
+void func_002B73C0(u32 p, s32 ptid, s32 flid) { (void)p; start_afs(ptid, flid); }   /* mwPlyStartAfs */
+void func_002BB038(u32 p, s32 ptid, s32 flid) { (void)p; start_afs(ptid, flid); }   /* mwPlyStartAfsLp */

@@ -128,6 +160,9 @@
 void func_002B6E50(u32 p, s32 file) {   /* mwPlyStart(ply, name) */
     (void)p;
+    sPlyStarted = 1;
     close_movie();
     if (getenv("BT2_SKIP_MOVIES") || !file || !open_movie((const char *)(uintptr_t)(u32)file)) { M.open = 1; close_movie(); }
 }

@@ -160,7 +195,7 @@
     if (M.frames == 0) return;
-    out[0] = (u32)(uintptr_t)M.strips; out[3] = MW; out[4] = MH;
+    out[0] = (u32)(uintptr_t)M.strips; out[3] = (u32)M.w; out[4] = (u32)M.h;
@@ -181,6 +216,7 @@
-    if (!M.open || (M.drained && M.shown > 0)) return 3;
+    if (!M.open) return sPlyStarted ? 3 : 0;   /* nunca arrancado -> 0 (la CRI real); fallo/fin -> 3 */
+    if (M.drained && M.shown > 0) return 3;
     return M.started ? 2 : 1;
 }
@@ -184,5 +220,8 @@
 void func_002B45D8(u32 p) { (void)p; close_movie(); }
+/* close_movie(): agregar  free(sAfsData); sAfsData = NULL;
+   if (M.pb) { av_freep(&M.pb->buffer); avio_context_free(&M.pb); M.pb = NULL; }
+   free(M.io); M.io = NULL;  */
```

Notas del diff (para cuando se aplique, no ahora):

- `next_frame()` tiene que usar `M.w`/`M.h` en `sws_getCachedContext(...)` y en `((size_t)s * M.h + y) * 64`
  (el mmap de `M.strips` ya alcanza: 512*448*4).
- `finish_open(w,h,loop)` es el cuerpo actual de `open_movie()` desde `avformat_find_stream_info()` hasta el
  final (elegir stream, decoder, `M.fps`, `M.w=w; M.h=h; M.loop=loop`). Para loop: al `AVERROR_EOF`,
  `mem_seek(M.io,0,SEEK_SET); avcodec_flush_buffers(M.cod); M.eof=M.drained=0; continue;`.
- `func_002BB038` ya existe en `port/eq/2BB038.c` (CRI real). Hay que neutralizarlo para que gane el HLE
  (sacarlo del build o dejarlo weak), igual que ya pasa con `2B4038`/`2B8328`.
- El GetStat de arriba es deliberadamente conservador: devuelve 0 una sola vez (antes del primer arranque) y
  3 si el arranque falló, para no re-abrir el AFS de 6.7 MB en cada frame.

### Experimento barato para confirmar antes del fix grande

Si querés validar el diagnóstico con 5 líneas y sin decoder:

1. En `plat_movie.c`, `func_002B8328`: agregar un `fprintf(stderr, "[ply] open=%d started=%d p=%08X\n", M.open, M.started, p);`
   (TEMP) y correr Map Select. Debería mostrar `open=0`, `p=0x40DE43xx` en todos los frames y nunca `open=1`.
2. En `func_002BB038` de `port/eq/2BB038.c`: agregar un TEMP al entrar
   (`fprintf(stderr, "[ply] StartAfsLp h=%08X ptid=%d flid=%d used=%d\n", arg0, arg1, arg2, func_002B8280(arg0));`).
   Debería verse **una vez** al entrar al Map Select, con `flid=0x55B` y `used=0`.
3. Opcional: `sPly[0] = 1;` en `func_002B4038` (used=1) y ver hasta dónde llega `2BB038`
   (probablemente hasta la parte AFS/SFD). Eso confirma que el único faltante es el arranque HLE.

---

## 6. Pendiente / no verificado

- No lo probé jugando: el resultado visual del fix (encuadre del video en la textura 0x3041) hay que verlo.
- El preview debe quedar en 512x256 (medido). El HLE actual usa 512x448 (FMV); si se usa ese tamaño, el
  video sale estirado ~1.75x en vertical.
- El loop (`StartAfsLp`) hay que implementarlo rebobinando el AVIO; la película dura 8.34 s.
- No verifiqué si la partición 0 del AFS está cargada (`sPart[0].fp`) en el momento del Map Select;
  `Port_ReadAudioFile` devuelve NULL si no. El log no lo dice porque `BT2_FILELOG` no estaba activo.
- No identifiqué qué interno exacto de la CRI escribe `stat=2`; el volcado del PS2 lo muestra y GetStat lo
  mapea vía `func_2D0468(sfd)=4`, pero el nombre de esa asignación no está confirmado.
- `scene+0x00..0x8F` del PS2 lo llena `mwPlyGetCurFrm`; los campos `+0x04=0x3D`, `+0x08=2`, `+0x14=0x20`,
  `+0x18=0x10`, `+0x1C=2` son parte del struct de frame que devuelve la CRI. No los reproduje uno por uno.
