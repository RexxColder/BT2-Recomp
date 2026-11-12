#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
/* Log de pelea (2026-10-28): estado de los dos luchadores cuadro a cuadro, para diagnosticar golpes/hit-stun.
 *
 * Variables:
 *   BT2_FIGHTLOG=1          activa (tambien BT2_ULTRALOG=1)
 *   BT2_FIGHTLOG_OUT=ruta   archivo de salida (def. /tmp/bt2_fight.log; "-" = stderr)
 *   BT2_FIGHTLOG_ALL=1      una linea por luchador en CADA cuadro (def.: solo cuando cambia accion/animacion)
 *   BT2_FIGHTLOG_STUCK=N    cuadros con la animacion quieta y el luchador moviendose para avisar "TRABADO" (def. 90)
 *
 * Mapa del luchador en BT2 (sacado del asm):
 *   chr(i)       = **(u32 **)D_00387930 + i * 0x1550                (func_00211288)
 *   pos          = chr + 0x510: +0x00 x,y,z  +0x20 dir  +0xB0 pitch  +0xB4 yaw   (BtlChar_GetPos = func_002112C8)
 *   accion       = chr + 0xC00..0xC10: +0xC08 pedida (BtlAct_Request 2174D8), +0xC0C en cola (2174B8), resto crudo
 *   animacion    = *(u32 *)(chr + 0x1530) + 0xBD0: +0x08 largo  +0x10 frame  +0x14 frame previo  +0x18 paso
 *                  +0x1C blend  +0x20 paso del blend                 (BtlAnim_Advance = func_001F9FB0)
 * Cuando el luchador lleva STUCK cuadros con frame == frame previo pero su posicion cambia, se escribe TRABADO con
 * un volcado hexadecimal del bloque de accion y de animacion, y (en el build de trazas) se vuelca la traza de llamadas
 * (bt2_trace_dump), que dice que funciones corrieron en esos cuadros. */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned gPortVBlanks;
void bt2_trace_dump(const char *why);

#define RAM_LO 0x00010000u
#define RAM_HI 0x02000000u
#define CHR_LIST 0x00387930u
#define CHR_SIZE 0x1550u

typedef struct {
    uint32_t act[5];        /* C00 C04 C08 C0C C10 */
    float frame, len, step, blend;
    float x, y, z, yaw;
    uint32_t f9, frz, frzNext, frzDelay;   /* flags grupo 9 (+0x2D4: 0x10000/0x20000 = pide hit-stop), congelamiento +0x984/988/98C */
    unsigned pad;                         /* botones de ese jugador (gs_input.c) */
    uint32_t b48, b4C, b50;
    uint32_t fl[17], hit[3];              /* flags grupos 0..16 (chr+0x2B0) y B48/B74/AB0 */               /* botones del personaje: chr+0x48/+0x4C/+0x50 (BtlPad_Test48/4C/50) */
    unsigned stuck;
    int valid, reported;
} FState;

static int sOn = -1, sAll, sStuckN = 90;
static FILE *sOut;
static FState sPrev[2];
unsigned gPortPadBtn[2];   /* lo llena Port_PadRead (gs_input.c) */

/* botones como texto: Arr Der Aba Izq X O Cua Tri L1 R1 L2 R2 St Sel */
static const char *padstr(unsigned b) {
    static char s[80];
    static const struct { unsigned bit; const char *n; } k[] = {
        {0x10, "Arr"}, {0x20, "Der"}, {0x40, "Aba"}, {0x80, "Izq"}, {0x4000, "X"}, {0x2000, "O"}, {0x8000, "Cua"},
        {0x1000, "Tri"}, {0x400, "L1"}, {0x800, "R1"}, {0x100, "L2"}, {0x200, "R2"}, {0x8, "St"}, {0x1, "Sel"}};
    unsigned j;
    s[0] = 0;
    for (j = 0; j < sizeof k / sizeof *k; j++) if (b & k[j].bit) { strcat(s, k[j].n); strcat(s, "+"); }
    if (s[0]) s[strlen(s) - 1] = 0; else strcpy(s, "-");
    return s;
}

static int ok(uint32_t a, uint32_t n) { return a >= RAM_LO && a + n <= RAM_HI && a + n > a; }
static uint32_t rd32(uint32_t a) { return *(volatile uint32_t *)(uintptr_t)a; }
static float rdf(uint32_t a) { return *(volatile float *)(uintptr_t)a; }

/* 1 mientras el juego tiene montada la lista de los dos luchadores (la misma comprobacion con la que el log por
   estado distingue BATALLA de MENU). No depende de que ningun log este encendido. Lo usa plat_gs.c para elegir
   el periodo de vsync de pelea o de menu (BT2_FPS_FIGHT / BT2_FPS_MENU). */
int Port_EnPelea(void) {
    uint32_t base;
    if (!ok(CHR_LIST, 4)) return 0;
    base = rd32(CHR_LIST);
    if (!ok(base, 4)) return 0;
    return ok(rd32(base), CHR_SIZE * 2);
}

static void hexdump(const char *what, uint32_t a, uint32_t n) {
    uint32_t i;
    fprintf(sOut, "      %s @%08X:", what, a);
    for (i = 0; i < n; i += 4) {
        if (i % 32 == 0) fprintf(sOut, "\n        +%03X:", i);
        fprintf(sOut, " %08X", rd32(a + i));
    }
    fprintf(sOut, "\n");
}

static void init(void) {
    const char *v = getenv("BT2_FIGHTLOG"), *u = getenv("BT2_ULTRALOG");
    sOn = (v && *v && *v != '0') || (u && *u && *u != '0');
    if (!sOn) return;
    sAll = getenv("BT2_FIGHTLOG_ALL") != NULL;
    if ((v = getenv("BT2_FIGHTLOG_STUCK")) && atoi(v) > 0) sStuckN = atoi(v);
    v = getenv("BT2_FIGHTLOG_OUT");
    if (v && !strcmp(v, "-")) sOut = stderr;
    else {
        sOut = fopen(v && *v ? v : "/tmp/bt2_fight.log", "w");
        if (!sOut) sOut = stderr;
    }
    setvbuf(sOut, NULL, _IOLBF, 0);
    fprintf(stderr, "bt2: FIGHTLOG activo -> %s (todo=%d, trabado=%d cuadros)\n", v && *v ? v : "/tmp/bt2_fight.log", sAll, sStuckN);
    fprintf(sOut, "# vblank J | acc C00 C04 C08(pedida) C0C(cola) C10 | anim frame/largo paso blend | pos x y z yaw | vel | f9 (flags grupo 9) frz (congelado/pendiente/retraso) | pad (botones) chr +48/+4C/+50 (botones como los ve el personaje) | evento\n");
}

void bt2_fightlog_frame(void) {
    uint32_t base, i;
    if (sOn < 0) init();
    if (!sOn) return;
    if (!ok(CHR_LIST, 4)) return;
    base = rd32(CHR_LIST);                       /* func_00211288: lw v1, D_00387930 ; lw v0, 0(v1) ; v0 + i*0x1550 */
    if (!ok(base, 4)) { sPrev[0].valid = sPrev[1].valid = 0; return; }
    base = rd32(base);
    if (!ok(base, CHR_SIZE * 2)) { sPrev[0].valid = sPrev[1].valid = 0; return; }   /* fuera de pelea */
    for (i = 0; i < 2; i++) {
        uint32_t chr = base + i * CHR_SIZE, pos = chr + 0x510, st = rd32(chr + 0x1530), an;
        FState s, *p = &sPrev[i];
        float vel = 0.0f;
        const char *ev = NULL;
        int k;
        memset(&s, 0, sizeof s);
        if (!ok(st, 0xBD0 + 0x40)) continue;
        an = st + 0xBD0;
        for (k = 0; k < 5; k++) s.act[k] = rd32(chr + 0xC00 + 4 * k);
        s.len = rdf(an + 0x08); s.frame = rdf(an + 0x10); s.step = rdf(an + 0x18); s.blend = rdf(an + 0x1C);
        s.x = rdf(pos + 0x00); s.y = rdf(pos + 0x04); s.z = rdf(pos + 0x08); s.yaw = rdf(pos + 0xB4);
        s.f9 = rd32(chr + 0x2B0 + 9 * 4);
        s.frz = rd32(chr + 0x984); s.frzNext = rd32(chr + 0x988); s.frzDelay = rd32(chr + 0x98C);
        s.pad = gPortPadBtn[i];
        for (k = 0; k < 17; k++) s.fl[k] = rd32(chr + 0x2B0 + 4 * k);
        s.hit[0] = rd32(chr + 0xB48); s.hit[1] = rd32(chr + 0xB74); s.hit[2] = rd32(chr + 0xAB0);
        s.b48 = rd32(chr + 0x48); s.b4C = rd32(chr + 0x4C); s.b50 = rd32(chr + 0x50);
        s.valid = 1;
        if (p->valid) {
            float dx = s.x - p->x, dy = s.y - p->y, dz = s.z - p->z;
            vel = sqrtf(dx * dx + dy * dy + dz * dz);
            if (memcmp(s.act, p->act, sizeof s.act)) ev = "ACCION";
            else if (s.frame < p->frame) ev = "ANIM-REINICIO";
            else if (s.len != p->len) ev = "ANIM-CAMBIO";
            else if ((s.f9 ^ p->f9) & 0x30000) ev = "HITSTOP-FLAG";
            else if ((s.frz > 0) != (p->frz > 0)) ev = s.frz ? "CONGELADO" : "DESCONGELADO";
            else if (s.pad != p->pad) ev = "BOTONES";
            else if (s.b4C != p->b4C || s.b48 != p->b48) ev = "BOTONES-PJ";
            /* animacion quieta (frame igual, sin blend) pero el luchador se mueve: el sintoma del hit-stun roto */
            if (s.frame == p->frame && vel > 0.01f) s.stuck = p->stuck + 1;
            else s.stuck = 0;
            s.reported = s.stuck ? p->reported : 0;
        } else {
            ev = "ENTRA-PELEA";
        }
        if (ev || sAll)
            fprintf(sOut, "%7u J%u | acc %X %X %X %X %X | anim %.2f/%.2f paso %.3f blend %.2f | pos %.1f %.1f %.1f yaw %.3f | vel %.2f | f9 %08X frz %d/%d/%d | pad %s chr %08X/%08X/%08X | %s\n",
                    gPortVBlanks, i + 1, s.act[0], s.act[1], s.act[2], s.act[3], s.act[4], s.frame, s.len, s.step, s.blend,
                    s.x, s.y, s.z, s.yaw, vel, s.f9, (int)s.frz, (int)s.frzNext, (int)s.frzDelay, padstr(s.pad), s.b48, s.b4C, s.b50, ev ? ev : "");
        if (p->valid) {   /* todo cambio de flags o de estado de golpe, grupo por grupo */
            for (k = 0; k < 17; k++)
                if (s.fl[k] != p->fl[k])
                    fprintf(sOut, "%7u J%u | FLAGS g%X %08X -> %08X (+%08X -%08X)\n", gPortVBlanks, i + 1, k, p->fl[k], s.fl[k],
                            s.fl[k] & ~p->fl[k], p->fl[k] & ~s.fl[k]);
            if (memcmp(s.hit, p->hit, sizeof s.hit))
                fprintf(sOut, "%7u J%u | GOLPE B48 %d->%d B74 %d->%d AB0 %d->%d\n", gPortVBlanks, i + 1, (int)p->hit[0], (int)s.hit[0],
                        (int)p->hit[1], (int)s.hit[1], (int)p->hit[2], (int)s.hit[2]);
        }
        if (s.stuck >= (unsigned)sStuckN && !s.reported) {
            char why[64];
            s.reported = 1;
            fprintf(sOut, "%7u J%u | *** TRABADO: %u cuadros con la animacion en %.2f/%.2f (paso %.3f) y moviendose a %.2f/cuadro ***\n",
                    gPortVBlanks, i + 1, s.stuck, s.frame, s.len, s.step, vel);
            hexdump("luchador+0xC00 (accion)", chr + 0xC00, 0x40);
            hexdump("anim (+0xBD0)", an, 0x40);
            hexdump("pos (+0x510)", pos, 0xC0);
            fprintf(stderr, "bt2: FIGHTLOG J%u TRABADO en vblank %u (ver log de pelea)\n", i + 1, gPortVBlanks);
            snprintf(why, sizeof why, "J%u trabado vblank %u", i + 1, gPortVBlanks);
            bt2_trace_dump(why);   /* no hace nada si no es el build de trazas o BT2_TRACE no esta activo */
        }
        *p = s;
    }
}

/* Nota libre desde el codigo del juego (p. ej. la eleccion de ataque en 23BDA8). */
volatile int gGsDumpOnHit; /* 1: an impact was logged and BT3_GS_DUMP=hit asks for that frame's dump (gs_core.c) */

void bt2_fightlog_note(const char *fmt, ...) {
    va_list ap;
    if (gGsDumpOnHit == 0 && strncmp(fmt, "IMPACTO", 7) == 0 && getenv("BT3_GS_DUMP") != NULL && strcmp(getenv("BT3_GS_DUMP"), "hit") == 0) {
        gGsDumpOnHit = 1;
    }
    if (sOn < 0) init();
    if (!sOn) return;
    fprintf(sOut, "%7u    | ", gPortVBlanks);
    va_start(ap, fmt);
    vfprintf(sOut, fmt, ap);
    va_end(ap);
    fputc('\n', sOut);
}

/* ---- Log por estado (BT2_STATELOG=1, o siempre que BT2_FIGHTLOG esté activo) ---------------------------------
 * Cada vblank lee el modo actual del juego (gProgress = *(u32*)0x3876A4, modo en +0x1C, flags en +0x18) y la fase
 * (BATALLA si la lista de personajes es válida, si no MENU) y anota cada cambio con el nombre de la escena. Va a
 * stderr (log principal) y, si el log de pelea está activo, también a ese archivo. Mapa en docs/bugs_open.md. */
static const char *mode_name(uint32_t m) {
    if (m == 1) return "titulo";
    if (m == 2) return "memory_card";
    if (m == 4) return "menu_principal";
    if (m == 5) return "opciones?";
    if (m >= 6 && m <= 8) return "duelo?";
    if (m >= 10 && m <= 16) return "ultimate_battle?";
    if (m >= 24 && m <= 27) return "dragon_adventure?";
    if (m >= 30 && m <= 35) return "torneo_mundial";
    if (m >= 38 && m <= 41) return "evolution_z?";
    if (m >= 43 && m <= 47) return "data_center?";
    if (m >= 48 && m <= 51) return "submenu_48?";
    if (m >= 53 && m <= 58) return "submenu_53?";
    if (m >= 61 && m <= 64) return "entrenamiento";
    return "desconocido";
}

int gBt2InBattle; /* 1 mientras la fase es BATALLA (otros logs pueden consultarlo) */

void bt2_statelog_frame(void) {
    static int on = -1;
    static uint32_t pmode = 0xFFFFFFFFu, pflags = 0xFFFFFFFFu;
    static int pbattle = -1;
    uint32_t p, mode = 0, flags = 0, base;
    int battle = 0;
    if (on < 0) {
        const char *s = getenv("BT2_STATELOG"), *f = getenv("BT2_FIGHTLOG");
        on = (s && *s && *s != '0') || (f && *f && *f != '0');
    }
    if (!on) return;
    if (ok(0x3876A4u, 4)) {
        p = rd32(0x3876A4u);
        if (ok(p, 0x20)) { mode = rd32(p + 0x1C); flags = rd32(p + 0x18); }
    }
    base = rd32(CHR_LIST);
    if (ok(CHR_LIST, 4) && ok(base, 4) && ok(rd32(base), CHR_SIZE * 2)) battle = 1;
    gBt2InBattle = battle;
    if (mode != pmode || battle != pbattle || ((flags ^ pflags) & 0x200)) {
        fprintf(stderr, "ESTADO vblank %u fase %s modo %u (%s) flags %X\n", gPortVBlanks, battle ? "BATALLA" : "MENU",
                mode, mode_name(mode), flags);
        if (sOn > 0) fprintf(sOut, "%7u    | ESTADO fase %s modo %u (%s) flags %X\n", gPortVBlanks, battle ? "BATALLA" : "MENU",
                             mode, mode_name(mode), flags);
        pmode = mode; pbattle = battle; pflags = flags;
    }
}
