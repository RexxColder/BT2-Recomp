# B15 — preview del Map Select (pelicula del AFS) por HLE, con bucle

Fecha: 2026-11-11. Un solo arreglo. Archivos tocados: port/full/plat_movie.c, port/eq/2BB038.c.
Backups: backups/plat_movie.c.pre_b15afs, backups/2BB038.c.pre_b15afs, backups/bt2.pre_b15afs (binario anterior).

## Que se hizo

- `func_002BB038` (mwPlyStartAfsLp) ya no intenta hablar con el CRI: llama a `Port_MovieStartAfs(ptid, flid)`.
- `plat_movie.c`: nuevo camino "pelicula desde el AFS": `start_afs` lee el bloque completo del AFS con
  `Port_ReadAudioFile` (plat_file.c), guarda el puntero en `M.afsData` y la abre en el acto con un AVIOContext en memoria
  (`mem_read`/`mem_seek`) + `movie_init(..., 512, 256, loop=1, live=1)` (en la 1ª versión era diferida a GetFrame: deadlock,
  ver "CORRECCIÓN" al final).
- Dimensiones dinamicas: `M.w/M.h` (default 512x448; AFS 512x256) usadas en sws, en la copia a tiras y en out[3]/out[4].
- Bucle: al EOF de `av_read_frame`, si `M.loop && M.pb`: `M.io->pos = 0; avio_seek(M.pb, 0, SEEK_SET); avformat_flush(); avcodec_flush_buffers();` y sigue (no marca eof). `avformat_flush` existe en libavformat 63.1.102, se uso esa.
- GetStat: `if (M.open && M.live) return 2;` antes de la logica vieja (el juego pregunta el estado ANTES de pedir cuadro en la rama live; sin esto no entraba nunca).
- AVIO propio: `M.fmt->flags |= AVFMT_FLAG_CUSTOM_IO` para que `avformat_close_input` no libere el pb; `close_io()` hace `av_freep(&M.pb->buffer); avio_context_free(&M.pb); free(M.io);`.
- `M.afsData` NO se libera en `close_movie` (se reusa al rebobinar/reabrir); solo `start_afs` lo libera al reemplazarlo. Fuga aceptada: un bloque por preview.

## Diff real — port/eq/2BB038.c
```diff
--- backups/2BB038.c.pre_b15afs	2026-11-11 14:04:08.451283914 -0300
+++ port/eq/2BB038.c	2026-11-11 14:05:09.500736969 -0300
@@ -8,25 +8,11 @@
 void func_002FFF90(s32 arg0);
 extern u8 D_00379CB8[] __attribute__((section(".data")));
 
-void func_002BB038(s32 arg0, s32 arg1, s32 arg2) {
-    u8 *s0;
-    s32 temp_v0;
+void Port_MovieStartAfs(s32 ptid, s32 flid);
 
-    s0 = (u8 *)arg0;
-    temp_v0 = func_002B8280(arg0, arg1, arg2);
-    if (temp_v0 != 1) {
-        Rand_Range((s32)D_00379CB8);
-        return;
-    }
-    func_002FFF90(*(s32 *)(s0 + 0x48));
-    func_002BAF70(arg0, arg1, arg2);
-    func_002BAD68(arg0, 1);
-    func_002BACC8(arg0);
-    *(s32 *)(s0 + 0x2E4) = 2;
-    *(s32 *)(s0 + 0x2EC) = arg1;
-    *(s32 *)(s0 + 0x2F0) = arg2;
-    *(s32 *)(s0 + 0x2DC) = temp_v0;
-    if (*(s32 *)(s0 + 0x2E0) == 0) {
-        *(s32 *)(s0 + 0x2E8) = temp_v0;
-    }
+void func_002BB038(s32 arg0, s32 arg1, s32 arg2) {
+    /* CRI fuera de juego: el preview del escenario es una pelicula del AFS (ptid, flid); la reproduce el HLE de
+       port/full/plat_movie.c (Port_MovieStartAfs). El handle real no existe en el port. */
+    (void)arg0;
+    Port_MovieStartAfs(arg1, arg2);
 }
```

## Diff real — port/full/plat_movie.c
```diff
--- backups/plat_movie.c.pre_b15afs	2026-11-11 14:04:08.450283907 -0300
+++ port/full/plat_movie.c	2026-11-11 14:05:00.067662916 -0300
@@ -13,6 +13,12 @@
  * juego (func_0024BA78 comprueba D_003B0B00+0x134 & 8), aqui no se duplica.
  * Variables: BT2_SKIP_MOVIES=1 (terminan al instante), BT2_MOVIELOG=1.
  *
+ * B15 (preview del Map Select): ademas de los SFD sueltos, el juego reproduce videos que viven DENTRO de un AFS
+ *   (ZS2US_1.AFS, ptid/flid). func_002BB038 (mwPlyStartAfsLp) llama a Port_MovieStartAfs(ptid, flid); aqui se lee el
+ *   bloque del AFS a memoria (plat_file.c: Port_ReadAudioFile), se demuxa/decodifica desde memoria con un AVIOContext
+ *   propio y se rebobina al llegar al final (loop). Esos videos responden GetStat = 2 en cuanto estan abiertos: el juego
+ *   consulta el estado ANTES de pedir cuadro en esa rama.
+ *
  * AUDIO: el demuxer entrega los paquetes de los streams que no son video (el ADX, stream 0xC0 del SFD) a
  *   void Movie_AudioPacket(const uint8_t *adx, int len, int64_t pts)   (pts en unidades de 1/90000 s desde el inicio)
  * Es una funcion DEBIL vacia: quien implemente el sonido (port/full/gs/snd_adx.c) la define de forma fuerte. Tambien hay
@@ -39,6 +45,27 @@
 
 #define MW 512
 #define MH 448
+
+/* Lector AVIO en memoria: el bloque del AFS ya esta entero en RAM (ver Port_MovieStartAfs). */
+typedef struct { const uint8_t *p; size_t n, pos; } MemIO;
+static int mem_read(void *op, uint8_t *buf, int n) {
+    MemIO *m = op;
+    size_t left = m->n - m->pos;
+    if (left < (size_t)n) n = (int)left;
+    memcpy(buf, m->p + m->pos, n);
+    m->pos += n;
+    return n;
+}
+static int64_t mem_seek(void *op, int64_t off, int whence) {
+    MemIO *m = op;
+    if (whence == AVSEEK_SIZE) return (int64_t)m->n;
+    if (whence == SEEK_CUR) off += (int64_t)m->pos;
+    else if (whence == SEEK_END) off += (int64_t)m->n;
+    if (off < 0 || (size_t)off > m->n) return -1;
+    m->pos = (size_t)off;
+    return off;
+}
+
 static struct {
     AVFormatContext *fmt; AVCodecContext *cod; struct SwsContext *sws; AVPacket *pkt; AVFrame *frm;
     int vstream, open, eof, drained, started, frames, shown;
@@ -46,11 +73,27 @@
     double fps; int64_t first_pts;
     uint8_t *strips;     /* cuadro en tiras, direccion de 32 bits (el juego la usa como puntero PS2) */
     int pending;         /* hay un cuadro decodificado esperando su hora */
+    int w, h;            /* ancho/alto actuales del cuadro (default 512x448; los videos del AFS son 512x256) */
+    int loop;            /* 1 = pelicula del AFS: rebobina al terminar */
+    int live;            /* 1 = pelicula del AFS: GetStat responde 2 en cuanto esta abierta */
+    AVIOContext *pb;     /* AVIO propio cuando la pelicula viene de memoria (AFS) */
+    MemIO *io;
+    uint8_t *afsData;    /* bloque del AFS en RAM; lo libera start_afs al reemplazarlo */
+    u32 afsSize;
+    int afsPtid, afsFlid;
+    int pending_open;    /* hay un bloque del AFS esperando abrirse en el proximo GetFrame */
 } M;
 
 static int64_t now_ns(void) { struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); return (int64_t)ts.tv_sec * 1000000000ll + ts.tv_nsec; }
 static int logon(void) { static int l = -1; if (l < 0) l = getenv("BT2_MOVIELOG") != NULL; return l; }
 
+/* libera el AVIO propio (solo cuando la pelicula vino de memoria) */
+static void close_io(void) {
+    av_freep(&M.pb->buffer);
+    avio_context_free(&M.pb);
+    free(M.io); M.io = NULL;
+}
+
 static void close_movie(void) {
     if (!M.open) return;
     if (logon()) fprintf(stderr, "[movie] fin: %d cuadros decodificados, %d mostrados\n", M.frames, M.shown);
@@ -58,21 +101,14 @@
     sws_freeContext(M.sws); av_frame_free(&M.frm); av_packet_free(&M.pkt);
     avcodec_free_context(&M.cod); avformat_close_input(&M.fmt);
     M.sws = NULL; M.open = 0;
+    if (M.pb) close_io();          /* M.afsData NO se libera: lo reusa/libera start_afs */
+    M.live = M.loop = 0;
 }
 
-static int open_movie(const char *name) {
-    char base[96], path[512]; const char *root = getenv("BT2_DATA"), *p, *b = name;
-    size_t n = 0; int i;
-    for (p = name; *p; p++) if (*p == '/' || *p == '\\') b = p + 1;
-    for (p = b; *p && *p != ';' && n < sizeof(base) - 1; p++) base[n++] = *p;
-    base[n] = 0;
-    for (i = 0; i < 2; i++) {
-        if (i) for (n = 0; base[n]; n++) base[n] = (char)toupper((unsigned char)base[n]);
-        snprintf(path, sizeof path, "%s/DATA/%s", root ? root : "gamedata", base);
-        if (avformat_open_input(&M.fmt, path, NULL, NULL) == 0) break;
-        M.fmt = NULL;
-    }
-    if (!M.fmt || avformat_find_stream_info(M.fmt, NULL) < 0) { fprintf(stderr, "[movie] no se puede abrir %s\n", name); return 0; }
+/* Decoder, strips, fps, flags y audio sobre M.fmt ya abierto. w/h = tamano al que se escala el cuadro. */
+static int movie_init(const char *label, int w, int h, int loop, int live) {
+    int i;
+    M.w = w; M.h = h; M.loop = loop; M.live = live;
     M.vstream = av_find_best_stream(M.fmt, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
     if (M.vstream < 0) return 0;
     const AVCodecParameters *par = M.fmt->streams[M.vstream]->codecpar;
@@ -89,23 +125,60 @@
         const AVCodecParameters *a = M.fmt->streams[i]->codecpar;
         if (a->codec_type == AVMEDIA_TYPE_AUDIO) { Movie_AudioBegin(a->sample_rate, a->ch_layout.nb_channels); break; }
     }
-    if (logon()) fprintf(stderr, "[movie] %s %dx%d %.2f fps\n", path, par->width, par->height, M.fps);
+    if (logon()) fprintf(stderr, "[movie] %s %dx%d (escalado a %dx%d, loop %d) %.2f fps\n", label, par->width, par->height, w, h, loop, M.fps);
     return 1;
 }
 
+static int open_movie(const char *name) {
+    char base[96], path[512]; const char *root = getenv("BT2_DATA"), *p, *b = name;
+    size_t n = 0; int i;
+    M.w = MW; M.h = MH; M.loop = 0; M.live = 0;
+    for (p = name; *p; p++) if (*p == '/' || *p == '\\') b = p + 1;
+    for (p = b; *p && *p != ';' && n < sizeof(base) - 1; p++) base[n++] = *p;
+    base[n] = 0;
+    for (i = 0; i < 2; i++) {
+        if (i) for (n = 0; base[n]; n++) base[n] = (char)toupper((unsigned char)base[n]);
+        snprintf(path, sizeof path, "%s/DATA/%s", root ? root : "gamedata", base);
+        if (avformat_open_input(&M.fmt, path, NULL, NULL) == 0) break;
+        M.fmt = NULL;
+    }
+    if (!M.fmt || avformat_find_stream_info(M.fmt, NULL) < 0) { fprintf(stderr, "[movie] no se puede abrir %s\n", name); return 0; }
+    return movie_init(path, MW, MH, 0, 0);
+}
+
+/* Abre la pelicula que ya esta en M.afsData (bloque del AFS) desde memoria, en bucle. 0 si no se pudo. */
+static int open_afs_movie(void) {
+    if (!M.afsData || !M.afsSize) return 0;
+    M.io = calloc(1, sizeof *M.io);
+    if (!M.io) return 0;
+    M.io->p = M.afsData; M.io->n = M.afsSize;
+    M.pb = avio_alloc_context(av_malloc(4096), 4096, 0, M.io, mem_read, NULL, mem_seek);
+    M.fmt = avformat_alloc_context();
+    if (!M.pb || !M.fmt) { fprintf(stderr, "[movie] AFS: sin memoria para el AVIO\n"); return 0; }
+    M.fmt->pb = M.pb;
+    /* el AVIO es nuestro: que avformat_close_input no lo libere */
+    M.fmt->flags |= AVFMT_FLAG_CUSTOM_IO;
+    if (avformat_open_input(&M.fmt, "afs", NULL, NULL) < 0 || avformat_find_stream_info(M.fmt, NULL) < 0) {
+        fprintf(stderr, "[movie] AFS: no se pudo abrir el stream\n");
+        return 0;
+    }
+    M.fmt->flags |= AVFMT_FLAG_CUSTOM_IO;
+    return movie_init("afs", 512, 256, 1, 1);   /* ancho/alto medidos del mpeg2video del ZS2US_1.AFS */
+}
+
 /* decodifica el siguiente cuadro a M.strips; 0 al final */
 static int next_frame(void) {
     for (;;) {
         int got = avcodec_receive_frame(M.cod, M.frm);
         if (got == 0) {
             if (M.first_pts == AV_NOPTS_VALUE) M.first_pts = M.frm->pts != AV_NOPTS_VALUE ? M.frm->pts : 0;
-            M.sws = sws_getCachedContext(M.sws, M.frm->width, M.frm->height, M.frm->format, MW, MH, AV_PIX_FMT_RGBA, SWS_BILINEAR, NULL, NULL, NULL);
+            M.sws = sws_getCachedContext(M.sws, M.frm->width, M.frm->height, M.frm->format, M.w, M.h, AV_PIX_FMT_RGBA, SWS_BILINEAR, NULL, NULL, NULL);
             static uint8_t rgba[MW * MH * 4];
-            uint8_t *dst[1] = {rgba}; int ds[1] = {MW * 4};
+            uint8_t *dst[1] = {rgba}; int ds[1] = {M.w * 4};
             sws_scale(M.sws, (const uint8_t *const *)M.frm->data, M.frm->linesize, 0, M.frm->height, dst, ds);
-            for (int s = 0; s < MW / 16; s++)
-                for (int y = 0; y < MH; y++) {
-                    uint8_t *d = M.strips + ((size_t)s * MH + y) * 64; const uint8_t *q = rgba + (size_t)y * MW * 4 + s * 64;
+            for (int s = 0; s < M.w / 16; s++)
+                for (int y = 0; y < M.h; y++) {
+                    uint8_t *d = M.strips + ((size_t)s * M.h + y) * 64; const uint8_t *q = rgba + (size_t)y * M.w * 4 + s * 64;
                     memcpy(d, q, 64);
                     for (int x = 3; x < 64; x += 4) d[x] = 0x80;
                 }
@@ -114,7 +187,17 @@
         }
         if (got == AVERROR_EOF) return 0;
         if (M.eof) { avcodec_send_packet(M.cod, NULL); continue; }
-        if (av_read_frame(M.fmt, M.pkt) < 0) { M.eof = 1; avcodec_send_packet(M.cod, NULL); continue; }
+        if (av_read_frame(M.fmt, M.pkt) < 0) {
+            if (M.loop && M.pb) {   /* pelicula del AFS: rebobina sin cerrar */
+                M.io->pos = 0;
+                avio_seek(M.pb, 0, SEEK_SET);
+                avformat_flush(M.fmt);
+                avcodec_flush_buffers(M.cod);
+                M.eof = 0; M.drained = 0; M.first_pts = AV_NOPTS_VALUE;
+                continue;
+            }
+            M.eof = 1; avcodec_send_packet(M.cod, NULL); continue;
+        }
         if (M.pkt->stream_index == M.vstream) avcodec_send_packet(M.cod, M.pkt);
         else {
             AVRational tb = M.fmt->streams[M.pkt->stream_index]->time_base;
@@ -137,6 +220,21 @@
     if (getenv("BT2_SKIP_MOVIES") || !file || !open_movie((const char *)(uintptr_t)(u32)file)) { M.open = 1; close_movie(); }
 }
 void func_002B7BD8(void) {}
+
+/* B15: preview del Map Select = pelicula dentro del AFS (mwPlyStartAfsLp). Se lee el bloque a RAM y se abre recien en el
+   proximo GetFrame, para no decodificar antes de que el juego pida cuadro. */
+extern uint8_t *Port_ReadAudioFile(int ptid, int flid, const char *fname, u32 *outSize); /* port/full/plat_file.c */
+static void start_afs(s32 ptid, s32 flid) {
+    close_movie();
+    free(M.afsData); M.afsData = NULL; M.afsSize = 0; M.afsPtid = ptid; M.afsFlid = flid;
+    M.afsData = Port_ReadAudioFile(ptid, flid, NULL, &M.afsSize);
+    if (M.afsData) fprintf(stderr, "[movie] AFS ptid %d flid 0x%X -> %u bytes\n", ptid, flid, M.afsSize);
+    else fprintf(stderr, "[movie] AFS ptid %d flid 0x%X: no se pudo leer\n", ptid, flid);
+    if (!M.afsData) return;
+    M.pending_open = 1;
+}
+void Port_MovieStartAfs(s32 ptid, s32 flid) { start_afs(ptid, flid); }
+
 /* El juego dibuja el cuadro y el fundido por el canal GIF (sceDmaSend(chan 2)): el renderer presenta un cuadro solo al
    terminar una cadena VIF1 (Port_GsVif1Chain). Se presenta aqui con una cadena vacia (un tag END) al final de cada pasada
    del bucle del juego en la que pidio cuadro (GetFrame), que es cuando dibuja. */
@@ -147,6 +245,10 @@
 void func_002B4FD0(u32 p, u32 out_) {   /* mwPlyGetFrame(ply, out) */
     u32 *out = (u32 *)(uintptr_t)out_; (void)p;
     memset(out, 0, 0x20);
+    if (M.pending_open) {
+        M.pending_open = 0;
+        if (!open_afs_movie()) { if (M.pb) close_io(); avformat_close_input(&M.fmt); }
+    }
     if (!M.open) return;
     sPresent = 1;
     /* avanza la decodificacion hasta el cuadro que toca por el reloj; el ultimo cuadro se entrega siempre (el juego lo sube
@@ -158,7 +260,7 @@
             if (!next_frame()) M.drained = 1;
     }
     if (M.frames == 0) return;
-    out[0] = (u32)(uintptr_t)M.strips; out[3] = MW; out[4] = MH;
+    out[0] = (u32)(uintptr_t)M.strips; out[3] = (u32)M.w; out[4] = (u32)M.h;
     if (M.shown++ % 100 == 0 && logon()) fprintf(stderr, "[movie] pasada %d, cuadro %d t=%.1fs\n", M.shown, M.frames, (now_ns() - M.t0) / 1e9);
 }
 void func_002B58F0(u32 p) { (void)p; }
@@ -178,6 +280,7 @@
         sPresent = 0;
         Port_GsVif1Chain((u32)(uintptr_t)sEndTag, 0);
     }
+    if (M.open && M.live) return 2;   /* pelicula del AFS: ya esta decodificando (el juego pregunta antes de pedir cuadro) */
     if (!M.open || (M.drained && M.shown > 0)) return 3;
     return M.started ? 2 : 1;
 }
```

## Link (últimas 5 líneas de scripts/capped.sh 8G python3 port/tools/link_full.py)
```
 "sin_relleno_thunk_de_runtime_PS2Recomp": 96,
 "sin_C_ni_relleno": 0,
 "sdk_con_stub_que_corta": 178
}
enlace OK -> port/build/full/bt2full; 0 lineas de error
```

Cadena presente en el binario:
```
[movie] AFS ptid %d flid 0x%X -> %u bytes
[movie] AFS ptid %d flid 0x%X: no se pudo leer
```

## Binario instalado

```
md5 port/build/full/bt2full : 098cf8831b72ab1ddad11fb326da88b4
md5 BT2-test/bin/bt2       : 098cf8831b72ab1ddad11fb326da88b4
backup bt2.pre_b15afs      : 6cbc51c02274288b4c4a76bb4241f918
```

(pgrep -x bt2 estaba vacío al instalar; se instaló.)

## Verificado / NO verificado

VERIFICADO:
- Compila y enlaza: build_full --only 2BB038 -> {"OK": 1}; link_full -> "enlace OK", 0 errores (rc=0).
- `objdump -dr port__eq__2BB038.o`: func_002BB038 es `jmp Port_MovieStartAfs` con arg1/arg2 en los registros correctos.
- `nm bt2full`: Port_MovieStartAfs y Port_ReadAudioFile definidos.
- Cadenas "[movie] AFS ptid ..." presentes en el binario.
- libavformat 63.1.102 tiene avformat_flush (usado) y avio_alloc_context/AVFMT_FLAG_CUSTOM_IO.

NO VERIFICADO (lo prueba el usuario jugando):
- Que el bloque (ptid, flid) del ZS2US_1.AFS se lea bien con Port_ReadAudioFile (que la particion del AFS este abierta cuando
  el Map Select pide el preview) y que el mpeg2video demuxee desde memoria sin avformat_open_input fallando. Si falla, stderr
  dice "[movie] AFS ptid %d flid 0x%X: no se pudo leer" o "no se pudo abrir el stream" -> correr con BT2_MOVIELOG=1.
- Que la rama live (418CC8) se elija: deberia, porque GetStat devuelve 2 con M.live=1 y G->0xC4 = 2.
- Que no cuelgue: es la duda principal (GetStat=2 permanente). Si el preview queda en negro o se cuelga, el arreglo se revierte
  con backups/bt2.pre_b15afs.
- Bucle real (rebobinar con avio_seek/avformat_flush + decoder flush) y que no haya glitch/negro de 1-2 cuadros en la costura.
- Ritmo: 29.97 fps del AFS dentro del pacer de 60 Hz del GetStat.

## Riesgos de encuadre (512x256 vs textura 0x3041)
- El camino de subida SI es dinamico en alto: func_003B4C20 pasa out[3]/out[4] a func_003B5350(ptr, w=512, h=256), que arma
  w/16 = 32 tiras con chunk = h*64 = 0x4000 bytes (TRXREG alto = 256). Nuestro layout de tiras coincide (tira s en s*h*64).
- Pero la textura destino 0x3041 y el blit de func_00418A68 se dimensionan en el codigo del juego (frame+0xC0/+0xC4 y
  0x3000/0x3040): si esa textura esta asignada 512x448 y el blit usa alto 448, se verian las 256 lineas del video y debajo
  basura de VRAM (o el video se estira/recorta). No se puede saber sin ver la pantalla; si pasa, el arreglo es de encuadre
  (escalar a 512x448 en vez de 512x256), no de decodificacion.
- Color/alpha: rgb24->RGBA con A=0x80 forcado (igual que las FMV) y sin conversion de gama; puede verse mas oscuro/claro que el original.

---

## CORRECCIÓN (2ª pasada, 2026-11-11): deadlock por apertura diferida

Problema: `start_afs` sólo marcaba `M.pending_open = 1` y la apertura real quedaba en `func_002B4FD0` (GetFrame). Pero la rama
live sólo pide cuadro; para entrar en ella el juego necesita que GetStat devuelva 2 (419820: `N->0xC4 == 2 && !(N->0xD0 & 4)`),
y con M.open==0 GetStat devolvía 3. Nadie abría nunca: deadlock.

Arreglo: `start_afs` abre en el acto (`open_afs_movie()`), sin decodificar (el primer `next_frame()` sigue siendo en el primer
GetFrame). Se borró el bloque de `func_002B4FD0` y el campo `pending_open` del struct (verificado: `grep pending_open` = 0).

Orden final del camino: 2BB038 → Port_MovieStartAfs → start_afs (lee el AFS + abre, M.live=1) → func_002B8328 (GetStat) = 2
→ 419820 elige func_00418CC8 → func_003B4C20 → func_002B4FD0 (GetFrame, primer next_frame) → subida de tiras → present.

Backup previo a esta corrección: `backups/plat_movie.c.pre_b15afs2` (md5 42291d7a67a7ddeaea39be6ddf185860)
y `backups/bt2.pre_b15afs2` (binario anterior, md5 098cf8831b72ab1ddad11fb326da88b4).

### Diff de la corrección (pre_b15afs2 -> actual)
```diff
--- backups/plat_movie.c.pre_b15afs2	2026-11-11 14:08:53.175854669 -0300
+++ port/full/plat_movie.c	2026-11-11 14:09:31.003270403 -0300
@@ -81,7 +81,6 @@
     uint8_t *afsData;    /* bloque del AFS en RAM; lo libera start_afs al reemplazarlo */
     u32 afsSize;
     int afsPtid, afsFlid;
-    int pending_open;    /* hay un bloque del AFS esperando abrirse en el proximo GetFrame */
 } M;
 
 static int64_t now_ns(void) { struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); return (int64_t)ts.tv_sec * 1000000000ll + ts.tv_nsec; }
@@ -221,8 +220,9 @@
 }
 void func_002B7BD8(void) {}
 
-/* B15: preview del Map Select = pelicula dentro del AFS (mwPlyStartAfsLp). Se lee el bloque a RAM y se abre recien en el
-   proximo GetFrame, para no decodificar antes de que el juego pida cuadro. */
+/* B15: preview del Map Select = pelicula dentro del AFS (mwPlyStartAfsLp). Se lee el bloque a RAM y se abre YA: el juego
+   elige la rama live (418CC8, la unica que pide cuadro) mirando GetStat, asi que la pelicula tiene que estar abierta antes.
+   Abrir no decodifica: el primer next_frame() ocurre en el primer func_002B4FD0. */
 extern uint8_t *Port_ReadAudioFile(int ptid, int flid, const char *fname, u32 *outSize); /* port/full/plat_file.c */
 static void start_afs(s32 ptid, s32 flid) {
     close_movie();
@@ -231,7 +231,11 @@
     if (M.afsData) fprintf(stderr, "[movie] AFS ptid %d flid 0x%X -> %u bytes\n", ptid, flid, M.afsSize);
     else fprintf(stderr, "[movie] AFS ptid %d flid 0x%X: no se pudo leer\n", ptid, flid);
     if (!M.afsData) return;
-    M.pending_open = 1;
+    if (!open_afs_movie()) {
+        avformat_close_input(&M.fmt);
+        if (M.pb) close_io();
+        return;
+    }
 }
 void Port_MovieStartAfs(s32 ptid, s32 flid) { start_afs(ptid, flid); }
 
@@ -245,10 +249,6 @@
 void func_002B4FD0(u32 p, u32 out_) {   /* mwPlyGetFrame(ply, out) */
     u32 *out = (u32 *)(uintptr_t)out_; (void)p;
     memset(out, 0, 0x20);
-    if (M.pending_open) {
-        M.pending_open = 0;
-        if (!open_afs_movie()) { if (M.pb) close_io(); avformat_close_input(&M.fmt); }
-    }
     if (!M.open) return;
     sPresent = 1;
     /* avanza la decodificacion hasta el cuadro que toca por el reloj; el ultimo cuadro se entrega siempre (el juego lo sube
```

### Link tras la corrección
```
 "sin_relleno_thunk_de_runtime_PS2Recomp": 96,
 "sin_C_ni_relleno": 0,
 "sdk_con_stub_que_corta": 178
}
enlace OK -> port/build/full/bt2full; 0 lineas de error
```

Binario instalado tras la corrección: md5 28bbffe777a3c86d4da9e9155334d336 (BT2-test/bin/bt2 == port/build/full/bt2full).
Cadenas AFS presentes: 2 (lectura OK / no se pudo leer). Sin errores de compilación ni warnings que corten el link.

---

## CORRECCIÓN 2 (3ª pasada, 2026-11-11): cuelgue por mem_read devolviendo 0 en EOF

Síntoma: el binario anterior (28bbffe…) colgaba el juego en el stage select (pantalla negra, proceso al 100 % de CPU).

Causa, reproducida fuera del juego (/tmp/opencode/test_afs3.c con el bloque real 0x55B del AFS): `mem_read` devolvía 0 al
llegar al final del bloque. libavformat interpreta 0 como "sin datos, reintentá" y `avformat_find_stream_info` entra en bucle
infinito de lecturas (1.047 M de llamadas en 10 s, todas con left 0). Con `return AVERROR_EOF` cuando `pos >= n`: abre, decodifica
y rebobina bien (249 cuadros por vuelta, 4 rebobinados en la prueba). No era el AVIO ni el GetStat: era el lector.

Cambios (backup previo: backups/plat_movie.c.pre_b15eof, md5 6ff1d3521ce1ef914c74ae3eba98bec2):
1. `mem_read`: `if (m->pos >= m->n) return AVERROR_EOF;`
2. `func_002B4FD0`: el while de decodificación lleva tope `int guard = 0; ... && guard++ < 64` para que un salto de reloj no
   decodifique sin fin en una sola pasada.

### Diff (pre_b15eof -> actual)
```diff
--- backups/plat_movie.c.pre_b15eof	2026-11-11 14:18:11.597032285 -0300
+++ port/full/plat_movie.c	2026-11-11 14:18:26.394524591 -0300
@@ -50,7 +50,10 @@
 typedef struct { const uint8_t *p; size_t n, pos; } MemIO;
 static int mem_read(void *op, uint8_t *buf, int n) {
     MemIO *m = op;
-    size_t left = m->n - m->pos;
+    size_t left;
+    /* EOF explicito: devolver 0 hace que libavformat reintente para siempre (avformat_find_stream_info en bucle) */
+    if (m->pos >= m->n) return AVERROR_EOF;
+    left = m->n - m->pos;
     if (left < (size_t)n) n = (int)left;
     memcpy(buf, m->p + m->pos, n);
     m->pos += n;
@@ -254,9 +257,10 @@
     /* avanza la decodificacion hasta el cuadro que toca por el reloj; el ultimo cuadro se entrega siempre (el juego lo sube
        a VRAM en cada pasada y presenta), asi no hay cuadros en negro entre dos de la pelicula */
     if (!M.drained) {
+        int guard = 0;   /* tope: si el reloj salta, no decodificar sin fin en una sola pasada */
         if (!M.started && M.frames == 0) { if (!next_frame()) M.drained = 1; }
         if (!M.started) { M.started = 1; M.t0 = now_ns(); }
-        while (!M.drained && now_ns() - M.t0 >= (int64_t)(1e9 * M.frames / M.fps))
+        while (!M.drained && guard++ < 64 && now_ns() - M.t0 >= (int64_t)(1e9 * M.frames / M.fps))
             if (!next_frame()) M.drained = 1;
     }
     if (M.frames == 0) return;
```

### Link
```
 "sin_relleno_thunk_de_runtime_PS2Recomp": 96,
 "sin_C_ni_relleno": 0,
 "sdk_con_stub_que_corta": 178
}
enlace OK -> port/build/full/bt2full; 0 lineas de error
```

Binario instalado: md5 326e2671a2dce80eb2cecd3da02d15c5 (BT2-test/bin/bt2 == port/build/full/bt2full); backup del anterior 28bbffe777a3c86d4da9e9155334d336 en backups/bt2.pre_b15eof.

Sigue SIN VERIFICAR: que el juego real no vuelva a colgar (el cuelgue se reprodujo sólo en el programa de prueba y la prueba del tope del while no cubre la lógica del juego) y el encuadre 512x256 vs textura 0x3041.
