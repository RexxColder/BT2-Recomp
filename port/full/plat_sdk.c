/*
 * SDK de Sony que faltaba para no depender de BT2_STUB_RET0 (etapa 5). Se va ampliando a medida que el juego llega a
 * cada funcion (BT2_STUB_BT=1 dice quien la llamo). Punteros del juego = u32 (memoria bajo 4 GB).
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef uint32_t u32;
typedef int32_t s32;
typedef int16_t s16;
typedef uint8_t u8;

/* sceCdLayerSearchFile(sceCdlFILE *fp, const char *name, int layer): fp = {u32 lsn, u32 size, char name[16], u8 date[8]}.
   Los datos del juego estan en gamedata/ (ver plat_file.c); se informa un lsn falso y el tamano del archivo real. */
extern const char *Port_DataRoot(void);
/* Registro de archivos del CD: cada archivo encontrado recibe un lsn base ((indice+1) << 20, o sea 2 GB de sectores);
   sceCdRead(lsn) lee del archivo que corresponde. */
static char sCdPath[64][600];
static int sCdN;
static u32 cd_register(const char *path) {
    int i;
    for (i = 0; i < sCdN; i++) if (!strcmp(sCdPath[i], path)) return (u32)(i + 1) << 20;
    if (sCdN >= 64) return 0;
    snprintf(sCdPath[sCdN], sizeof sCdPath[0], "%s", path);
    return (u32)(++sCdN) << 20;
}
s32 sceCdRead(u32 lsn, u32 sectors, u32 buf, u32 mode) {
    unsigned idx = (lsn >> 20), sec = lsn & 0xFFFFF;
    FILE *fp;
    size_t want = (size_t)sectors * 2048, got = 0;
    (void)mode;
    if (idx == 0 || idx > (unsigned)sCdN || !buf) { fprintf(stderr, "sceCdRead: lsn 0x%X desconocido\n", lsn); return 0; }
    fp = fopen(sCdPath[idx - 1], "rb");
    if (fp) { fseek(fp, (long)sec * 2048, SEEK_SET); got = fread((void *)(uintptr_t)buf, 1, want, fp); fclose(fp); }
    if (got < want) memset((uint8_t *)(uintptr_t)buf + got, 0, want - got);
    return 1;
}
s32 sceCdSeek(u32 lsn) { (void)lsn; return 1; }
s32 sceCdLayerSearchFile(u32 fp, u32 name, u32 layer) {
    const char *n = (const char *)(uintptr_t)name, *base = n, *p;
    uint32_t *f = (uint32_t *)(uintptr_t)fp;
    char path[600], nm[20];
    struct stat st;
    (void)layer;
    if (!n || !f) return 0;
    for (p = n; *p; p++) if (*p == '/' || *p == '\\') base = p + 1;
    snprintf(path, sizeof path, "%s/%.*s", Port_DataRoot(), (int)strcspn(base, ";"), base);
    if (stat(path, &st) != 0) { snprintf(path, sizeof path, "%s/DATA/%.*s", Port_DataRoot(), (int)strcspn(base, ";"), base); if (stat(path, &st) != 0) return 0; }
    f[0] = cd_register(path); f[1] = (u32)st.st_size;
    memset(nm, 0, sizeof nm); snprintf(nm, 16, "%.*s", (int)strcspn(base, ";"), base);
    memcpy(f + 2, nm, 16); memset(f + 6, 0, 8);
    return 1;
}

/* ---- cache del EE: sin cache que sincronizar en el host (SyncDCache / InvalidDCache y sus variantes con DIntr) */
void _sceSDC(u32 a, u32 b) { (void)a; (void)b; }
void _sceIDC(u32 a, u32 b) { (void)a; (void)b; }
void func_0032F430(void) {}
void func_0032F558(u32 a, u32 b) { (void)a; (void)b; }
void func_0032F698(u32 a, u32 b) { (void)a; (void)b; }
void func_0032F810(u32 a) { (void)a; }

/* vibracion: sin actuadores */
s32 sceVibGetProfile(u32 port, u32 slot, u32 prof) { (void)port; (void)slot; (void)prof; return 0; }

/* ---- newlib reentrante del SDK (el primer argumento es struct _reent *, se ignora) */
#include <ctype.h>
#include <errno.h>
#include <locale.h>
s32 _mbtowc_r(u32 r, u32 pwc, u32 s, u32 n, u32 st) {          /* configuracion "C": un byte = un caracter */
    (void)r; (void)st;
    if (!s) return 0;
    if (n == 0) return -1;
    if (pwc) *(u32 *)(uintptr_t)pwc = *(const unsigned char *)(uintptr_t)s;
    return *(const char *)(uintptr_t)s ? 1 : 0;
}
s32 _strtol_r(u32 r, u32 s, u32 end, s32 base) {
    char *e; long v = strtol((const char *)(uintptr_t)s, &e, base); (void)r;
    if (end) *(u32 *)(uintptr_t)end = (u32)(uintptr_t)e;
    return (s32)v;
}
u32 _strtoul_r(u32 r, u32 s, u32 end, s32 base) {
    char *e; unsigned long v = strtoul((const char *)(uintptr_t)s, &e, base); (void)r;
    if (end) *(u32 *)(uintptr_t)end = (u32)(uintptr_t)e;
    return (u32)v;
}
double _strtod_r(u32 r, u32 s, u32 end) {
    char *e; double v = strtod((const char *)(uintptr_t)s, &e); (void)r;
    if (end) *(u32 *)(uintptr_t)end = (u32)(uintptr_t)e;
    return v;
}
u32 _setlocale_r(u32 r, s32 cat, u32 loc) { static char c[] = "C"; (void)r; (void)cat; (void)loc; return (u32)(uintptr_t)c; }
u32 _signal_r(u32 r, s32 sig, u32 h) { (void)r; (void)sig; (void)h; return 0; }
s32 _raise_r(u32 r, s32 sig) { (void)r; (void)sig; return 0; }
void _init_signal_r(u32 r) { (void)r; }
void __sigtramp_r(u32 r, s32 sig) { (void)r; (void)sig; }
void __register_frame_info(u32 a, u32 b) { (void)a; (void)b; }
void __register_frame_info_table(u32 a, u32 b) { (void)a; (void)b; }
u32 __deregister_frame_info(u32 a) { (void)a; return 0; }
/* __ieee754_*f: libm del host (mismos resultados salvo ulp) */
#include <math.h>
float __ieee754_acosf(float x) { return acosf(x); }
float __ieee754_asinf(float x) { return asinf(x); }
float __ieee754_atan2f(float y, float x) { return atan2f(y, x); }
float __ieee754_logf(float x) { return logf(x); }
float __ieee754_powf(float x, float y) { return powf(x, y); }
float __ieee754_sqrtf(float x) { return sqrtf(x); }

/* ---- libmpeg: sin decodificador todavia (etapa 6: plat_mpeg2.c de BT3). Todo "correcto"; no se entrega ninguna imagen. */
s32 sceMpegInit(void) { return 1; }
s32 sceMpegCreate(u32 a, u32 b, s32 c) { (void)a; (void)b; (void)c; return 1; }
s32 sceMpegReset(u32 a) { (void)a; return 1; }
u32 sceMpegAddCallback(u32 a, s32 b, u32 c, u32 d) { (void)a; (void)b; (void)c; (void)d; return 0; }
s32 sceMpegSetBuffType(u32 a, s32 b) { (void)a; (void)b; return 0; }
s32 sceMpegGetPicture(u32 a, u32 b, u32 c) { (void)a; (void)b; (void)c; return -1; }
s32 sceMpegGetPictureRAW8(u32 a, u32 b, u32 c) { (void)a; (void)b; (void)c; return -1; }

/* ---- libdma: sceDmaChan = el bloque de registros del canal (CHCR +0, MADR +0x10, QWC +0x20, TADR +0x30). Las transferencias se
   entregan a gs_core.c: VIF1 (canal 1) en cadena = lista del cuadro; GIF (canal 2) normal o en cadena. */
extern void Port_GsVif1Chain(u32 tadr, int tte);
extern void Port_GsGifChannel(u32 addr, u32 qwc, int chain);
extern u32 full_dma_addr(u32 a);
static const u32 kDmaBase[10] = {0x10008000, 0x10009000, 0x1000A000, 0x1000B000, 0x1000B400, 0x1000C000, 0x1000C400, 0x1000C800, 0x1000D000, 0x1000D400};
u32 sceDmaGetChan(u32 ch) { return kDmaBase[ch % 10]; }
static u32 dma_phys(u32 a) { return full_dma_addr(a & 0xF0000000u ? a : a); }
s32 sceDmaSend(u32 d, u32 tag) {
    u32 a = dma_phys(tag);
    if (d == 0x10009000u) Port_GsVif1Chain(a, 0);
    else if (d == 0x1000A000u) Port_GsGifChannel(a, 0, 1);
    return 0;
}
s32 sceDmaSendN(u32 d, u32 addr, u32 qwc) {
    u32 a = dma_phys(addr);
    if (d == 0x1000A000u) Port_GsGifChannel(a, qwc, 0);
    else if (d == 0x10009000u && getenv("BT2_DMALOG")) fprintf(stderr, "sceDmaSendN(VIF1) normal ignorado\n");
    return 0;
}
s32 sceDmaSendI(u32 d, u32 addr, u32 qwc) { return sceDmaSendN(d, addr, qwc); }
s32 sceDmaRecv(u32 d, u32 tag) { (void)d; (void)tag; return 0; }
s32 sceDmaRecvN(u32 d, u32 addr, u32 qwc) { (void)d; (void)addr; (void)qwc; return 0; }
s32 sceDmaRecvI(u32 d, u32 addr, u32 qwc) { (void)d; (void)addr; (void)qwc; return 0; }

/* ---- reproductor de peliculas CRI Sofdec (mwPly*): sin IOP ni decodificador SFD no se puede crear. TEMPORAL: la pelicula
   "termina" al instante (estado 4 = fin) para que logos y menus sigan. Las funciones reales (src/cri, port/eq) quedan ignoradas
   porque la capa plat_* manda. Un reproductor real (MPEG-2 intra de plat_mpeg2.c de BT3 + ADX) es la etapa 6. Variable
   BT2_MOVIES=1 reservada para activarlo.
     2B6208 mwPlyInit(cfg)   2B30E0 mwPlyCalcWorkCnt   2B4038 mwPlyCreate -> handle   2B88C0 SetFile?   2B6E50 Start
     2B7BD8 mwPlyExecServer  2B4FD0 GetFrame(ply, out)   2B58F0 FrameDone   2B8328 GetStat   2B45D8 Destroy   2B65C0 Finish */
/* mwPly* ahora en plat_movie.c (libavcodec). */

/* ---- vsprintf del SDK: lo llama el C recompilado (sprintf de newlib) con un va_list de la EE: puntero a ranuras de 8 bytes
   (enteros en la parte baja, doubles enteros). Cada conversion se delega a snprintf del host. */
s32 func_00329198(u32 buf_, u32 fmt_, u32 ap_) {
    char *out = (char *)(uintptr_t)buf_, *o = out;
    const char *f = (const char *)(uintptr_t)fmt_;
    const uint8_t *ap = (const uint8_t *)(uintptr_t)ap_;
    while (*f) {
        char spec[40], tmp[512];
        int n = 0, lng = 0, k;
        if (*f != '%') { *o++ = *f++; continue; }
        spec[n++] = *f++;
        while (*f && strchr("-+ #0", *f) && n < 30) spec[n++] = *f++;
        if (*f == '*') { s32 w = *(const s32 *)ap; ap += 8; n += snprintf(spec + n, 8, "%d", w); f++; }
        else while (*f >= '0' && *f <= '9' && n < 30) spec[n++] = *f++;
        if (*f == '.') {
            spec[n++] = *f++;
            if (*f == '*') { s32 w = *(const s32 *)ap; ap += 8; n += snprintf(spec + n, 8, "%d", w); f++; }
            else while (*f >= '0' && *f <= '9' && n < 34) spec[n++] = *f++;
        }
        while (*f == 'l' || *f == 'h' || *f == 'z' || *f == 'j' || *f == 't') { if (*f == 'l') lng++; f++; }
        if (!*f) break;
        k = *f++;
        if (k == '%') { *o++ = '%'; continue; }
        if (k == 'd' || k == 'i') { long long v = lng >= 2 ? *(const long long *)ap : (long long)*(const s32 *)ap; ap += 8; spec[n] = 0; strcat(spec, "lld"); o += sprintf(o, spec, v); }
        else if (k == 'u' || k == 'x' || k == 'X' || k == 'o') { unsigned long long v = lng >= 2 ? *(const unsigned long long *)ap : (unsigned long long)*(const u32 *)ap; ap += 8; spec[n++] = 'l'; spec[n++] = 'l'; spec[n++] = (char)k; spec[n] = 0; o += sprintf(o, spec, v); }
        else if (k == 'c') { *o++ = (char)*(const s32 *)ap; ap += 8; }
        else if (k == 's') { const char *s = (const char *)(uintptr_t)*(const u32 *)ap; ap += 8; spec[n++] = 's'; spec[n] = 0; o += sprintf(o, spec, s ? s : "(null)"); }
        else if (k == 'p') { void *p = (void *)(uintptr_t)*(const u32 *)ap; ap += 8; o += sprintf(o, "%p", p); }
        else if (strchr("fFeEgGaA", k)) { double d = *(const double *)ap; ap += 8; spec[n++] = (char)k; spec[n] = 0; o += sprintf(o, spec, d); }
        else { *o++ = '%'; *o++ = (char)k; }
    }
    *o = 0;
    return (s32)(o - out);
}
