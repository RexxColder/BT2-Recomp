/*
 * Archivos del juego en el host (etapa 4). BT2 lee todo por el ADXF de CRI: dos particiones AFS (DATA/ZS2US_1.AFS = 0,
 * DATA/ZS2US_2.AFS = 1; formato "AFS\0", cuenta, tabla {offset, tamano} en bytes), archivos por (particion, indice),
 * en sectores de 2048 bytes, de forma asincrona. Aqui se leen directo de gamedata/DATA y la lectura termina al
 * instante. La capa CRI de abajo (adxf_*, cvFs*, RPC al IOP) NO se usa: se sustituye la API publica ADXF_* que llama
 * el juego, como hace plat_file.c de Tenkaichi3Decomp. Los nombres son los del juego de BT2 (func_ + direccion):
 *   0x2EA588 ADXF_LoadPartitionNw   0x2EAFA8 ADXF_GetPtStat   0x2EB9B0 ADXF_OpenAfs   0x2EBB08 ADXF_Close
 *   0x2EC0C8 ADXF_ReadNw            0x2EC6B0 ADXF_GetFsizeSct 0x2EC990 ADXF_GetStat   0x2EF218 ADXM_ExecMain
 * Variables: BT2_DATA = raiz de los datos (por defecto "gamedata"); un archivo suelto gamedata/mods/<particion>/<indice>.bin
 * sustituye al del AFS.
 */
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint32_t u32;
typedef int32_t s32;
#define SECTOR 2048
enum { STAT_STOP = 1, STAT_READING = 2, STAT_READEND = 3, STAT_ERROR = 4 };

typedef struct Part { FILE *fp; u32 count; u32 *tab; char name[64]; } Part;   /* tab: {offset, size} x count */
typedef struct PortFile { Part *part; u32 off, size, posSct; s32 stat; } PortFile;

static Part sPart[4];
#define MAX_FILES 64
#define HANDLE_BASE 0x100
static PortFile sFile[MAX_FILES];
static PortFile *file_of(u32 h) {
    if (h < HANDLE_BASE || h >= HANDLE_BASE + MAX_FILES || sFile[h - HANDLE_BASE].part == NULL) {
        fprintf(stderr, "bt2full: manejador ADXF invalido 0x%X\n", h);
        return NULL;
    }
    return &sFile[h - HANDLE_BASE];
}
static int sFileLog = -1;
extern unsigned gPortVBlanks;
#define FLOG(...) do { if (sFileLog < 0) sFileLog = getenv("BT2_FILELOG") != NULL; if (sFileLog) fprintf(stderr, __VA_ARGS__); } while (0)

static const char *root(void) { const char *r = getenv("BT2_DATA"); return r ? r : "gamedata"; }

static FILE *open_data(const char *fname, char *out, size_t outsz) {
    const char *base = fname, *p;
    char up[96];
    size_t n = 0;
    FILE *f;
    for (p = fname; *p; p++) if (*p == '/' || *p == '\\') base = p + 1;
    for (p = base; *p && *p != ';' && n < sizeof(up) - 1; p++) up[n++] = (char)toupper((unsigned char)*p);
    up[n] = 0;
    snprintf(out, outsz, "%s/DATA/%s", root(), base);
    if ((f = fopen(out, "rb"))) return f;
    snprintf(out, outsz, "%s/DATA/%s", root(), up);
    return fopen(out, "rb");
}

s32 func_002EA588(s32 ptid, u32 fname, u32 dir, u32 ptinfo) {          /* ADXF_LoadPartitionNw */
    Part *p = &sPart[ptid & 3];
    char path[512], h[8];
    (void)dir; (void)ptinfo;
    if (p->fp) { fclose(p->fp); free(p->tab); p->fp = NULL; p->tab = NULL; }
    p->fp = open_data((const char *)(uintptr_t)fname, path, sizeof path);
    if (!p->fp || fread(h, 1, 8, p->fp) != 8 || memcmp(h, "AFS\0", 4)) {
        fprintf(stderr, "bt2full: no se puede abrir la particion AFS %s\n", path);
        if (p->fp) { fclose(p->fp); p->fp = NULL; }
        return 0;
    }
    memcpy(&p->count, h + 4, 4);
    p->tab = malloc((size_t)p->count * 8);
    if (fread(p->tab, 8, p->count, p->fp) != p->count) { fprintf(stderr, "bt2full: tabla AFS truncada: %s\n", path); exit(2); }
    snprintf(p->name, sizeof p->name, "%s", path);
    FLOG("[file] particion %d = %s (%u archivos)\n", ptid, path, p->count);
    return 0;
}
s32 func_002EAFA8(s32 ptid) { return sPart[ptid & 3].fp ? STAT_READEND : STAT_STOP; }   /* ADXF_GetPtStat */

/* ---------------------------------------------------------------- F8 multiidioma (ISO PAL/EU)
   El AFS EU trae 5 copias de los textos y texturas localizados: la historia en 553 packs con stride 0x229
   (EN 0x319, ES 0x542, DE 0x76B, FR 0x994, IT 0xBBD) y el bloque de menu en 23 entradas con stride 0x17
   (EN 0xDE9, ES 0xE00, DE 0xE17, FR 0xE2E, IT 0xE45). Se carga como particion 2 y, con idioma != EN, se
   remapean los ids USA a ese bloque; todo lo demas sigue saliendo de la USA (staging/F8_multidioma_eu.md). */
extern int Port_Idioma(void);
static int sEuTry, sEuOk;   /* sEuTry: ya se intento cargar; sEuOk: la particion 2 tiene el AFS EU */

/* Indice de bloque dentro de ZS2EU_1.AFS. OJO: el orden del port (idioma 2 = FR, 3 = DE) NO es el del AFS
   EU (bloque 2 = DE, bloque 3 = FR), comprobado con los textos de 0x76B (DE) y 0x994 (FR). */
static int eu_lang(int idioma) {
    if (idioma == 2) return 3;
    if (idioma == 3) return 2;
    return idioma;
}

/* Carga perezosa de la particion EU (slot 2). 1 si quedo lista. Sin idioma o sin archivo, 0. */
static int eu_cargar(void) {
    const char *nombre;
    char path[512];
    FILE *f;

    if (sEuTry) return sEuOk;
    sEuTry = 1;
    if (Port_Idioma() == 0) return 0;
    nombre = getenv("BT2_AFS_EU");
    if (nombre == NULL || nombre[0] == 0) nombre = "ZS2EU_1.AFS";
    f = open_data(nombre, path, sizeof path);
    if (f == NULL) {
        fprintf(stderr, "F8 EU: no esta '%s'; el idioma %d sigue leyendo la USA\n", nombre, Port_Idioma());
        return 0;
    }
    fclose(f);
    func_002EA588(2, (u32)(uintptr_t)nombre, 0, 0);
    sEuOk = sPart[2].fp != NULL;
    if (!sEuOk) fprintf(stderr, "F8 EU: no se pudo cargar la particion 2 con '%s'\n", nombre);
    return sEuOk;
}

u32 func_002EB9B0(s32 ptid, s32 flid) {                                  /* ADXF_OpenAfs: 0 = error */
    Part *p;
    PortFile *f;
    /* F8: historia, menus, objetos/Z-items y dialogo de memory card salen del bloque del idioma en la particion EU. */
    if (ptid == 0 && eu_cargar()) {
        int lang = eu_lang(Port_Idioma());
        s32 id = -1;
        if (flid >= 0x319 && flid <= 0x541) id = flid + lang * 0x229;              /* historia (553 packs) */
        else if (flid == 0x550) id = 0xDF5 + lang * 0x17;                          /* dialogo memory card */
        else if (flid >= 0x544 && flid <= 0x55A) id = flid + 0x8A5 + lang * 0x17;  /* bloque de menu (23) */
        else if (flid >= 0x767 && flid <= 0x769) id = 0x1068 + lang * 3 + (flid - 0x767);  /* objetos/Z-items (3) */
        if (id >= 0) {
            static unsigned euLogN = 0;
            if (euLogN < 20) { euLogN++; fprintf(stderr, "F8 EU remap %d:%d -> 2:%d\n", ptid, flid, id); }
            ptid = 2;
            flid = id;
        }
    }
    p = &sPart[ptid & 3];
    if (!p->fp || (u32)flid >= p->count) {
        /* B12: tope al aviso (un cuelgue no debe escribir cientos de MB de log) */
        static unsigned oooN = 0;
        if (oooN++ < 8) fprintf(stderr, "bt2full: ADXF_OpenAfs(%d, %d) fuera de rango\n", ptid, flid);
        return 0;
    }
    /* El manejador es un indice chico (HANDLE_BASE + ranura), no un puntero del host: el juego lo guarda en su
       memoria y algun camino lo pasa por una mascara de direcciones del PS2 (0x4FDB6A5C -> 0x0FDB6A5C: SIGSEGV
       al azar segun donde caia el heap). */
    {
        u32 slot;
        for (slot = 0; slot < MAX_FILES && sFile[slot].part != NULL; slot++) {}
        if (slot == MAX_FILES) { fprintf(stderr, "bt2full: ADXF_OpenAfs: sin ranuras libres (%d)\n", MAX_FILES); return 0; }
        f = &sFile[slot];
        memset(f, 0, sizeof *f);
        f->part = p; f->off = p->tab[flid * 2]; f->size = p->tab[flid * 2 + 1]; f->stat = STAT_STOP;
        FLOG("[file] open (%d,%d) off=0x%X size=0x%X\n", ptid, flid, f->off, f->size);
        return HANDLE_BASE + slot;
    }
}
void func_002EBB08(u32 h) { PortFile *f = file_of(h); if (f) f->part = NULL; }   /* ADXF_Close */
s32 func_002EC6B0(u32 h) { PortFile *f = file_of(h); return f ? (s32)((f->size + SECTOR - 1) / SECTOR) : 0; }   /* GetFsizeSct */
s32 func_002EC990(u32 h) { PortFile *f = file_of(h); return f ? f->stat : STAT_ERROR; }     /* ADXF_GetStat */

/* Lee nsct sectores desde la posicion actual; lo que queda detras del fin del archivo va a cero. */
s32 func_002EC0C8(u32 h, s32 nsct, u32 buf) {                            /* ADXF_ReadNw */
    PortFile *f = file_of(h);
    if (f == NULL) return 0;
    u32 total = (f->size + SECTOR - 1) / SECTOR;
    size_t want, got = 0;
    if (nsct > (s32)(total - f->posSct)) nsct = (s32)(total - f->posSct);
    want = (size_t)nsct * SECTOR;
    if (want) {
        u32 start = f->posSct * SECTOR;
        size_t avail = f->size > start ? f->size - start : 0, n = avail < want ? avail : want;
        fseek(f->part->fp, (long)f->off + (long)start, SEEK_SET);
        got = fread((void *)(uintptr_t)buf, 1, n, f->part->fp);
        memset((uint8_t *)(uintptr_t)buf + got, 0, want - got);
    }
    f->posSct += (u32)nsct;
    f->stat = STAT_READEND;
    return nsct;
}

/* Sonido (plat_snd_adx.c): contenido completo de un archivo de un AFS (ptid, flid) o suelto (fname, en gamedata/DATA).
   Devuelve un bloque malloc (el que llama lo libera) o NULL. */
uint8_t *Port_ReadAudioFile(int ptid, int flid, const char *fname, u32 *outSize) {
    FILE *f;
    uint8_t *buf;
    u32 off = 0, size = 0;
    if (fname) {
        char path[512];
        long n;
        f = open_data(fname, path, sizeof path);
        if (!f) return NULL;
        fseek(f, 0, SEEK_END); n = ftell(f); fseek(f, 0, SEEK_SET);
        buf = malloc((size_t)n + 64);
        if (!buf || fread(buf, 1, (size_t)n, f) != (size_t)n) { free(buf); fclose(f); return NULL; }
        fclose(f);
        *outSize = (u32)n;
        return buf;
    } else {
        Part *p = &sPart[ptid & 3];
        if (!p->fp || (u32)flid >= p->count) return NULL;
        off = p->tab[flid * 2]; size = p->tab[flid * 2 + 1];
        buf = malloc((size_t)size + 64);
        if (!buf) return NULL;
        fseek(p->fp, (long)off, SEEK_SET);
        if (fread(buf, 1, size, p->fp) != size) { free(buf); return NULL; }
        *outSize = size;
        return buf;
    }
}

/* CRI sin hilos: nada que atender. */
void func_002EF218(void) {}                                              /* ADXM_ExecMain */

/* ---------------------------------------------------------------- E/S de archivos del SDK (sceOpen/sceRead...) sobre el disco
   Rutas del estilo "cdrom0:\BIN\DBZP.BIN;1" -> gamedata/BIN/DBZP.BIN (sin distinguir mayusculas). Un sceRead que cae
   en la zona del overlay (0x3B3100..0x421300) reescribe los `jmp` de sus funciones (full_patch_range). */
#include <dirent.h>
#include <strings.h>
#include <sys/stat.h>
extern void full_patch_range(u32 lo, u32 hi);
#define OVL_LO 0x3B3100u
#define OVL_HI 0x421300u
#define MAXFD 32
static FILE *sFd[MAXFD];

static FILE *open_disc(const char *name) {
    char path[600], seg[128];
    const char *p = name;
    size_t n = 0;
    if (!strncasecmp(p, "cdrom0:", 7)) p += 7;
    snprintf(path, sizeof path, "%s", root());
    for (;;) {
        while (*p == '\\' || *p == '/') p++;
        if (!*p) break;
        n = 0;
        while (*p && *p != '\\' && *p != '/' && *p != ';' && n < sizeof seg - 1) seg[n++] = *p++;
        seg[n] = 0;
        while (*p && *p != '\\' && *p != '/') p++;     /* ";1" */
        {   /* busca el nombre sin distinguir mayusculas */
            DIR *d = opendir(path);
            struct dirent *e;
            int found = 0;
            if (d) {
                while ((e = readdir(d))) if (!strcasecmp(e->d_name, seg)) { snprintf(path + strlen(path), sizeof path - strlen(path), "/%s", e->d_name); found = 1; break; }
                closedir(d);
            }
            if (!found) return NULL;
        }
    }
    return fopen(path, "rb");
}
s32 sceOpen(u32 name, s32 flags) {
    int i;
    FILE *f;
    (void)flags;
    f = open_disc((const char *)(uintptr_t)name);
    FLOG("[file] sceOpen(%s) -> %s\n", (const char *)(uintptr_t)name, f ? "ok" : "NO");
    if (!f) return -1;
    for (i = 3; i < MAXFD; i++) if (!sFd[i]) { sFd[i] = f; return i; }
    fclose(f);
    return -1;
}
s32 sceClose(s32 fd) { if (fd >= 3 && fd < MAXFD && sFd[fd]) { fclose(sFd[fd]); sFd[fd] = NULL; } return 0; }
s32 sceLseek(s32 fd, s32 off, s32 whence) {
    if (fd < 3 || fd >= MAXFD || !sFd[fd]) return -1;
    fseek(sFd[fd], off, whence == 0 ? SEEK_SET : whence == 1 ? SEEK_CUR : SEEK_END);
    return (s32)ftell(sFd[fd]);
}
extern u32 full_native_to_ps2(uintptr_t p);
s32 sceRead(s32 fd, u32 buf, s32 size) {
    size_t got;
    /* `MainMenu_StartBallLoops` (y otros `extern u8 Funcion[]`) llega como puntero a la funcion NATIVA. En Linux el
       texto cae en 0x40000000+, pero en el PE de Windows cae en 0x02100000+ (justo arriba de la RAM del PS2) y un
       umbral no lo ve: se leia el overlay SOBRE .text. Se consulta siempre la tabla: una direccion PS2 valida nunca
       coincide con una funcion nativa. */
    { u32 a = full_native_to_ps2(buf); if (a) buf = a; }
    if (fd < 3 || fd >= MAXFD || !sFd[fd]) return -1;
    got = fread((void *)(uintptr_t)buf, 1, (size_t)size, sFd[fd]);
    if (buf < OVL_HI && buf + got > OVL_LO) full_patch_range(buf, buf + (u32)got);
    FLOG("[file] sceRead(%d, 0x%X, %d) = %zu\n", fd, buf, size, got);
    if (buf == OVL_LO && got == (size_t)size) { extern void Port_DemoOverlayLoaded(void); Port_DemoOverlayLoaded(); }   /* plat_demo.c */
    return (s32)got;
}

const char *Port_DataRoot(void) { return root(); }
