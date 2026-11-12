/*
 * Kernel del EE, SIF/IOP, CD y tiempo, para el build nativo de un solo hilo (docs/PLAN_NATIVO.md etapa 4).
 * No hay segundo procesador, ni modulos que cargar, ni unidad: todo informa exito. Los hilos del juego (CRI, SDK)
 * no existen: CreateThread da un id, StartThread/WakeupThread no hacen nada, SleepThread/WaitSema retornan.
 * Los archivos los sirve plat_file.c.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef uint32_t u32;
typedef int32_t s32;

unsigned gPortVBlanks;                 /* vblanks desde el inicio: el reloj del build headless */
static int sLog = -1;
#define LOG(...) do { if (sLog < 0) sLog = getenv("BT2_SYSLOG") != NULL; if (sLog) fprintf(stderr, __VA_ARGS__); } while (0)

/* ---------------------------------------------------------------- syscalls del kernel (por numero) */
#define MAXSEMA 256
static s32 sSemaCount[MAXSEMA], sSemaMax[MAXSEMA];
static int sSemas = 1, sThreads = 2;

long Port_Syscall(int num, long a, long b, long c, long d) {
    (void)b; (void)c; (void)d;
    switch (num) {
    case 16: case 18: return 1;                          /* AddIntcHandler / AddDmacHandler: id de handler */
    case 32: return sThreads++;                          /* CreateThread */
    case 47: return 1;                                   /* GetThreadId */
    case 60: return (a != 0 && (u32)b != 0xFFFFFFFFu) ? (long)((u32)b + (u32)c) : 0x01FFF000; /* SetupThread */
    case 62: return 0x01EFE000;                          /* EndOfHeap */
    case 64: {                                           /* CreateSema(ThreadParam sema): initCount en +8 */
        int id = sSemas++ % MAXSEMA;
        u32 p = (u32)a;
        sSemaCount[id] = p ? ((s32 *)(uintptr_t)p)[2] : 0;
        sSemaMax[id] = p ? ((s32 *)(uintptr_t)p)[1] : 1;
        return id ? id : (sSemas++ % MAXSEMA);
    }
    case 66: case 67: if ((u32)a < MAXSEMA) sSemaCount[a]++; return a;
    case 68:                                             /* WaitSema: sin hilos no se puede bloquear */
        if ((u32)a < MAXSEMA && sSemaCount[a] > 0) sSemaCount[a]--;
        else LOG("WaitSema(%ld) sin cuenta (seria un bloqueo)\n", a);
        return 0;
    case 69: case 70:                                    /* PollSema: id si habia cuenta, -419 si no */
        if ((u32)a < MAXSEMA && sSemaCount[a] > 0) { sSemaCount[a]--; return a; }
        return -419;
    case 100: return 0;                                  /* FlushCache */
    default: LOG("syscall %d(0x%lX, 0x%lX, 0x%lX)\n", num, a, b, c); return 0;
    }
}

/* ---------------------------------------------------------------- SIF / IOP / CD */
void func_00321E50(void) {}                            /* __main (constructores C++ globales: ninguno) */
void sceSifInitRpc(u32 mode) { (void)mode; }
void sceCdInit(u32 mode) { (void)mode; }
void sceCdMmode(u32 media) { (void)media; }
s32 sceSifRebootIop(u32 img) { (void)img; return 1; }
s32 sceSifSyncIop(void) { return 1; }
void sceFsReset(void) {}
s32 func_00337C28(u32 name, s32 argLen, s32 args) { (void)name; (void)argLen; (void)args; return 1; } /* sceSifLoadModule */
void sceSifInitIopHeap(u32 x) { (void)x; }
s32 sceChk01(u32 p) { if (p) *(s32 *)(uintptr_t)p = 0; return 0; }
s32 sceCdSync(s32 mode) { (void)mode; return 0; }       /* nada pendiente */
s32 sceCdStatus(void) { return 0; }
s32 sceCdGetError(void) { return 0; }

/* ---------------------------------------------------------------- tiempo */
int64_t GetTimerSystemTime(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (int64_t)ts.tv_sec * 147456000 + (int64_t)ts.tv_nsec * 147456 / 1000000;   /* ticks del EE (147.456 MHz bus) */
}

/* ---------------------------------------------------------------- RPC / memoria del IOP */
/* "Memoria del IOP": direcciones de 24 bits que el juego solo pasa de vuelta. Se reparte de un pozo falso. */
extern u32 Port_IopAlloc(u32 size); extern void Port_IopFree(u32 p);   /* plat_snd_se.c: memoria del IOP real (buffer del host) */
u32 sceSifAllocIopHeap(u32 size) { return Port_IopAlloc(size); }
s32 sceSifFreeIopHeap(u32 p) { Port_IopFree(p); return 0; }
s32 sceSifQueryTotalFreeMemSize(void) { return 0x100000; }
s32 sceSifQueryMaxFreeMemSize(void) { return 0x100000; }
/* El bind se responde en el acto: sceSifClientData.serve (+0x24) pasa a no nulo. */
static struct { u32 client; s32 id; } sRpcBind[16];
s32 sceSifBindRpc(u32 client, s32 id, s32 mode) { (void)mode;
    { int i; for (i = 0; i < 15 && sRpcBind[i].client && sRpcBind[i].client != client; i++); sRpcBind[i].client = client; sRpcBind[i].id = id; } LOG("sceSifBindRpc(client=%x id=%x)\n", client, id); *(u32 *)(uintptr_t)(client + 0x24) = client; return 0; }
s32 sceSifCallRpc(u32 client, s32 fno, s32 mode, u32 send, s32 ssize, u32 recv, s32 rsize, u32 endfn, u32 endarg) {
    (void)mode; (void)endfn; (void)endarg;
    LOG("sceSifCallRpc(fno=%d)\n", fno);
    /* SOUNDS.IRX (servidor 0x2000004): efectos de sonido, plat_snd_se.c */
    { extern void Port_SndRpc(s32 fno, u32 send, s32 ssize, u32 recv, s32 rsize); int i;
      for (i = 0; i < 16 && sRpcBind[i].client; i++)
        if (sRpcBind[i].client == client && sRpcBind[i].id == 0x2000004) { Port_SndRpc(fno, send, ssize, recv, rsize); return 0; } }
    /* Servidor DTX del IOP (CRI, id 0x90000200): DTX_Create & co. esperan un resultado distinto de cero (handle). */
    { int i; for (i = 0; i < 16 && sRpcBind[i].client; i++)
        if (sRpcBind[i].client == client && sRpcBind[i].id == (s32)0x90000200 && recv && rsize >= 4) { memset((void *)(uintptr_t)recv, 0, (size_t)rsize); *(s32 *)(uintptr_t)recv = 1; } }
    return 0;
}
s32 sceSifCheckStatRpc(u32 client) { (void)client; return 0; }   /* nunca ocupado */
s32 sceSifDmaStat(u32 id) { (void)id; return -1; }              /* transferencia terminada */
u32 sceSifSetDma(u32 data, s32 count) { extern void Port_SifSetDma(u32 d, s32 n); Port_SifSetDma(data, count); return 1; }

/* ---------------------------------------------------------------- consola de depuracion del SDK */
/* func_00331710 (sceTty/printf del SDK, 0x331710): los mensajes de error del juego. Solo se muestra el formato. */
long func_00331710(u32 fmt) { if (fmt && getenv("BT2_SYSLOG")) fprintf(stderr, "[printf] %s\n", (const char *)(uintptr_t)fmt); return 0; }
/* hilos: sin hilos, StartThread / InitThread / iWakeupThread no hacen nada (el id sirve de resultado) */
s32 StartThread(s32 id, u32 arg) { (void)arg; return id; }
void InitThread(void) {}
s32 iWakeupThread(s32 id) { return id; }
