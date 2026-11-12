/*
 * Host del build 100 % nativo de BT2 (port/tools/link_full.py, docs/PLAN_NATIVO.md etapa 3).
 *
 * Mapa de memoria (todo RWX; el juego guarda punteros de 4 bytes y direcciones PS2 absolutas):
 *   0x00010000..0x02000000  RAM del PS2 (memfd de 32 MB; los primeros 64 KB no se pueden mapear en Linux:
 *                           vm.mmap_min_addr = 65536; un SIGSEGV ahi se informa como "pagina cero del PS2")
 *   0x20000000, 0x30000000  espejos uncached / UCAB del MISMO memfd (32 MB completos, offset 0)
 *   0x70000000              scratchpad 16 KB
 *   0x10000000..0x10010000, 0x12000000..0x12002000  registros de hardware: memoria comun por ahora
 *   0x40000000              codigo nativo (-Ttext-segment, no PIE)
 * Carga: PT_LOAD de gamedata/SLUS_214.41 en su direccion. Despues escribe `jmp rel32` en la direccion PS2 de cada
 * funcion (tabla full_funcs de tables.c) para que los punteros a funcion del juego caigan en la version nativa.
 */
#define _GNU_SOURCE
#include <errno.h>
#include <execinfo.h>
#include <malloc.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <pthread.h>
#include <ucontext.h>
#include <time.h>
#include <unistd.h>

typedef uint32_t u32;
typedef struct { u32 addr; void (*fn)(void); } FullFunc;
extern const FullFunc full_funcs[];
extern const u32 full_nfuncs;

#define RAM_SIZE 0x02000000u
#define OVL_LO 0x3B3100u
#define OVL_HI 0x421300u

static int sMemfd = -1;
static uintptr_t sStackLo, sStackHi;
/* El juego pasa a DMA direcciones "fisicas" (& 0x0FFFFFFF); un buffer en la pila del host (0x4xxxxxxx) pierde el nibble alto.
   Se lo devuelve si cae dentro del rango de la pila (la RAM del PS2 queda debajo de 0x02000000, sin ambiguedad). */
u32 full_dma_addr(u32 a) {
    if (a >= RAM_SIZE && sStackHi && (a & 0x0FFFFFFFu) >= (sStackLo & 0x0FFFFFFFu) && (a & 0x0FFFFFFFu) < (sStackHi & 0x0FFFFFFFu))
        return (a & 0x0FFFFFFFu) | (u32)(sStackLo & 0xF0000000u);
    return a;
}
static unsigned long sStubCalls;

/* Canario de pila (compilacion con -fstack-protector-all via BT2_CANARY): si un desbordamiento pisa el canario,
   __stack_chk_fail avisa y provoca un SIGSEGV para que on_segv muestre el volcado de siempre. */
void __stack_chk_fail(void) {
    fprintf(stderr, "bt2full: CANARIO DE PILA PISADO (stack smashing)\n");
    raise(SIGSEGV);
}

static void *map_at(u32 addr, size_t size, int fd, off_t off, const char *what) {
    int fl = (fd >= 0 ? MAP_SHARED : MAP_PRIVATE | MAP_ANONYMOUS) | MAP_FIXED_NOREPLACE;
    void *p = mmap((void *)(uintptr_t)addr, size, PROT_READ | PROT_WRITE | PROT_EXEC, fl, fd, off);
    if (p != (void *)(uintptr_t)addr) {
        fprintf(stderr, "bt2full: no se pudo mapear %s en 0x%08X: %s\n", what, addr, strerror(errno));
        exit(2);
    }
    return p;
}

/* TEMP (B3): software watchpoint on one byte (bt2_watch_byte). Its page is made read-only; a write faults here,
   the page is opened and the instruction single-stepped (trap flag); on_trap compares the byte, logs the writer's
   address if it changed, and closes the page again. */
static volatile uintptr_t sWatchAddr;
static volatile uint8_t sWatchOld;
static volatile int sWatchHits;
#include <dlfcn.h>
void bt2_fightlog_note(const char *fmt, ...);
void bt2_watch_byte(uintptr_t addr) {
    if (sWatchAddr != 0 || addr == 0) return;
    sWatchAddr = addr;
    sWatchOld = *(volatile uint8_t *)addr;
    mprotect((void *)(addr & ~(uintptr_t)4095), 4096, PROT_READ);
    fprintf(stderr, "watch: byte %p = %u\n", (void *)addr, sWatchOld);
}
/* Herramienta (B25): vigila un float (BT2_WATCH_F32=direccion,umbral) y anota la función que lo escribió cuando salta
   más del umbral (p. ej. la posición del jugador en el salto del borde del mapa del mundo). Misma mecánica que el byte. */
static volatile int sWatchF32;
static volatile float sWatchF32Old, sWatchF32Thr;
void bt2_watch_f32_from_env(void) {
    const char *e = getenv("BT2_WATCH_F32");
    uintptr_t a;
    char *end;
    if (e == NULL || sWatchAddr != 0) return;
    a = (uintptr_t)strtoul(e, &end, 0);
    sWatchF32Thr = *end == ',' ? strtof(end + 1, NULL) : 100.0f;
    sWatchF32 = 1;
    sWatchF32Old = *(volatile float *)a;
    sWatchAddr = a;
    mprotect((void *)(a & ~(uintptr_t)4095), 4096, PROT_READ);
    fprintf(stderr, "watch: float %p = %.2f (umbral %.1f)\n", (void *)a, sWatchF32Old, sWatchF32Thr);
}
static void on_trap(int sig, siginfo_t *si, void *uc_) {
    ucontext_t *uc = uc_;
    uint8_t now = *(volatile uint8_t *)sWatchAddr;
    (void)sig; (void)si;
    uc->uc_mcontext.gregs[REG_EFL] &= ~0x100LL;
    if (sWatchF32) {
        float f = *(volatile float *)sWatchAddr, d = f - sWatchF32Old;
        if (d > sWatchF32Thr || d < -sWatchF32Thr) {
            extern unsigned gPortVBlanks;
            Dl_info di;
            uintptr_t rip = (uintptr_t)uc->uc_mcontext.gregs[REG_RIP];
            int ok = dladdr((void *)rip, &di);
            fprintf(stderr, "watch: float %p %.2f -> %.2f (vblank %u), escrito antes de rip %p (%s +%lx)\n", (void *)sWatchAddr,
                    sWatchF32Old, f, gPortVBlanks, (void *)rip, ok && di.dli_sname ? di.dli_sname : "?",
                    (unsigned long)(ok && di.dli_saddr ? rip - (uintptr_t)di.dli_saddr : 0));
            if (++sWatchHits > 200) { sWatchAddr = 0; return; }
        }
        sWatchF32Old = f;
        mprotect((void *)(sWatchAddr & ~(uintptr_t)4095), 4096, PROT_READ);
        return;
    }
    if (now != sWatchOld) {
        Dl_info di;
        uintptr_t rip = (uintptr_t)uc->uc_mcontext.gregs[REG_RIP];
        int ok = dladdr((void *)rip, &di);
        const char *fn = ok && di.dli_sname ? di.dli_sname : "?";
        uintptr_t off = ok ? rip - (uintptr_t)di.dli_fbase : rip;
        fprintf(stderr, "watch: byte %p %u -> %u, escrito antes de rip %p off %lx (%s)\n", (void *)sWatchAddr, sWatchOld, now, (void *)rip, (unsigned long)off, fn);
        bt2_fightlog_note("B3 WATCH byte %u -> %u rip %p off %lx (%s)", sWatchOld, now, (void *)rip, (unsigned long)off, fn);
        sWatchOld = now;
        if (++sWatchHits > 50) { sWatchAddr = 0; return; } /* page stays open */
    }
    mprotect((void *)(sWatchAddr & ~(uintptr_t)4095), 4096, PROT_READ);
}

static void on_segv(int sig, siginfo_t *si, void *uc_) {
    ucontext_t *uc = uc_;
    uintptr_t a = (uintptr_t)si->si_addr;
    if (sWatchAddr != 0 && (sig == SIGSEGV) && ((a ^ sWatchAddr) & ~(uintptr_t)4095) == 0) {
        static int trapSet;
        if (!trapSet) { struct sigaction st; memset(&st, 0, sizeof st); st.sa_sigaction = on_trap; st.sa_flags = SA_SIGINFO | SA_ONSTACK | SA_NODEFER; sigaction(SIGTRAP, &st, NULL); trapSet = 1; }
        mprotect((void *)(sWatchAddr & ~(uintptr_t)4095), 4096, PROT_READ | PROT_WRITE);
        uc->uc_mcontext.gregs[REG_EFL] |= 0x100LL;
        return;
    }
    void *bt[48];
    int n;
    fprintf(stderr, "\nbt2full: señal %d, direccion 0x%lX, rip 0x%llX%s\n", sig, (unsigned long)a,
            (unsigned long long)uc->uc_mcontext.gregs[REG_RIP],
            a < 0x10000 ? " (pagina cero del PS2: puntero nulo o dato no mapeable)" : "");
    {
        const greg_t *g = uc->uc_mcontext.gregs;
        fprintf(stderr,
            "  rax=%016llX rbx=%016llX rcx=%016llX rdx=%016llX\n"
            "  rsi=%016llX rdi=%016llX rbp=%016llX rsp=%016llX\n"
            "  r8=%016llX r9=%016llX r10=%016llX r11=%016llX\n"
            "  r12=%016llX r13=%016llX r14=%016llX r15=%016llX\n",
            (unsigned long long)g[REG_RAX], (unsigned long long)g[REG_RBX],
            (unsigned long long)g[REG_RCX], (unsigned long long)g[REG_RDX],
            (unsigned long long)g[REG_RSI], (unsigned long long)g[REG_RDI],
            (unsigned long long)g[REG_RBP], (unsigned long long)g[REG_RSP],
            (unsigned long long)g[REG_R8], (unsigned long long)g[REG_R9],
            (unsigned long long)g[REG_R10], (unsigned long long)g[REG_R11],
            (unsigned long long)g[REG_R12], (unsigned long long)g[REG_R13],
            (unsigned long long)g[REG_R14], (unsigned long long)g[REG_R15]);
    }
    {
        extern char __executable_start, etext;
        uintptr_t lo = (uintptr_t)&__executable_start, hi = (uintptr_t)&etext;
        uintptr_t sp = (uintptr_t)uc->uc_mcontext.gregs[REG_RSP];
        uintptr_t end = (sp >= 0x41800000UL && sp < 0x42000000UL) ? 0x42000000UL : 0x7ffffff00000UL;
        uintptr_t *p = (uintptr_t *)sp;
        void *arr[64];
        int m = 0, i;
        for (i = 0; i < 4096 && (uintptr_t)p < end; i++) {
            uintptr_t v = *p++;
            if (v >= lo && v < hi && m < 64) arr[m++] = (void *)v;
        }
        fprintf(stderr, "pila-escaneo (%d candidatos):\n", m);
        backtrace_symbols_fd(arr, m, 2);
    }
    n = backtrace(bt, 48);
    backtrace_symbols_fd(bt, n, 2);
    { extern void bt2_trace_dump(const char *); bt2_trace_dump("crash"); }   /* plat_trace.c: traza de llamadas hasta el crash */
    _exit(139);
}

/* Direccion PS2 de una funcion nativa (el C del juego usa `extern u8 Funcion[]` como direccion de carga, p. ej. el
   overlay: MainMenu_StartBallLoops); 0 si no es ninguna. */
u32 full_native_to_ps2(uintptr_t p) {
    u32 i;
    for (i = 0; i < full_nfuncs; i++) if ((uintptr_t)full_funcs[i].fn == p) return full_funcs[i].addr;
    return 0;
}

/* Parches `jmp rel32` en las direcciones PS2 de funcion dentro de [lo,hi). */
void full_patch_range(u32 lo, u32 hi) {
    u32 i, n = 0;
    for (i = 0; i < full_nfuncs; i++) {
        u32 a = full_funcs[i].addr;
        int64_t rel;
        uint8_t *p;
        if (a < lo || a >= hi || a < 0x10000 || a + 5 > RAM_SIZE) continue;
        rel = (int64_t)(intptr_t)full_funcs[i].fn - (int64_t)(a + 5);
        if (rel > INT32_MAX || rel < INT32_MIN) { fprintf(stderr, "bt2full: salto fuera de rango en 0x%X\n", a); continue; }
        p = (uint8_t *)(uintptr_t)a;
        p[0] = 0xE9;
        *(int32_t *)(p + 1) = (int32_t)rel;
        n++;
    }
    if (getenv("BT2_VERBOSE")) fprintf(stderr, "bt2full: %u saltos escritos en 0x%X..0x%X\n", n, lo, hi);
}

static void load_elf(const char *path) {
    FILE *f = fopen(path, "rb");
    uint8_t h[52], ph[32];
    u32 phoff, i;
    uint16_t phnum;
    if (!f || fread(h, 1, 52, f) != 52 || memcmp(h, "\177ELF", 4)) { fprintf(stderr, "bt2full: no se puede leer %s\n", path); exit(2); }
    memcpy(&phoff, h + 28, 4);
    memcpy(&phnum, h + 44, 2);
    for (i = 0; i < phnum; i++) {
        u32 type, off, va, fsz, msz;
        fseek(f, phoff + i * 32, SEEK_SET);
        if (fread(ph, 1, 32, f) != 32) exit(2);
        memcpy(&type, ph, 4); memcpy(&off, ph + 4, 4); memcpy(&va, ph + 8, 4);
        memcpy(&fsz, ph + 16, 4); memcpy(&msz, ph + 20, 4);
        if (type != 1 || msz == 0 || va < 0x10000 || va + msz > RAM_SIZE) continue;
        memset((void *)(uintptr_t)va, 0, msz);
        fseek(f, off, SEEK_SET);
        if (fread((void *)(uintptr_t)va, 1, fsz, f) != fsz) { fprintf(stderr, "bt2full: ELF truncado\n"); exit(2); }
        if (getenv("BT2_VERBOSE")) fprintf(stderr, "bt2full: PT_LOAD 0x%08X filesz 0x%X memsz 0x%X\n", va, fsz, msz);
    }
    fclose(f);
}

__attribute__((constructor(101))) static void map_memory(void) {
    mallopt(M_MMAP_MAX, 0);   /* malloc del host por brk, justo despues del programa (<4 GB) */
    mallopt(M_ARENA_MAX, 1);
    sMemfd = memfd_create("ps2ram", 0);
    if (sMemfd < 0 || ftruncate(sMemfd, RAM_SIZE) != 0) { perror("bt2full: memfd"); exit(2); }
    map_at(0x00010000u, RAM_SIZE - 0x10000, sMemfd, 0x10000, "la RAM del PS2");
    map_at(0x20000000u, RAM_SIZE, sMemfd, 0, "espejo uncached 0x20000000");
    map_at(0x30000000u, RAM_SIZE, sMemfd, 0, "espejo UCAB 0x30000000");
    map_at(0x70000000u, 0x4000, -1, 0, "el scratchpad");
    map_at(0x10000000u, 0x10000, -1, 0, "registros 0x10000000");
    map_at(0x12000000u, 0x2000, -1, 0, "registros GS 0x12000000");
}

/* Temporizadores del EE (T0..T3 en 0x10000000 + 0x800*n: COUNT +0x00, MODE +0x10; MODE bit 7 = cuenta). El juego espera con
   bucles sobre COUNT (func_0028C790: while (T1_COUNT < 0x190)): un hilo del host los incrementa a bus/256 = 576 kHz. */
static void *timer_thread(void *arg) {
    struct timespec ts = {0, 1000000};   /* 1 ms */
    (void)arg;
    for (;;) {
        int n;
        nanosleep(&ts, NULL);
        for (n = 0; n < 4; n++) {
            volatile uint32_t *cnt = (volatile uint32_t *)(uintptr_t)(0x10000000u + 0x800u * n);
            volatile uint32_t *mode = (volatile uint32_t *)(uintptr_t)(0x10000010u + 0x800u * n);
            if (*mode & 0x80u) *cnt = (*cnt + 576u) & 0xFFFFu;
        }
    }
    return NULL;
}

/* Stub de una funcion DEL JUEGO sin C todavia: devuelve 0 (lista en port/full/TEMP_STUBS_AUTO.txt). */
static unsigned long sGameStubCalls;
long full_stub_game(const char *name, unsigned addr) {
    sGameStubCalls++;
    if (getenv("BT2_STUB_STRICT")) { fprintf(stderr, "STUB(juego) %s 0x%08X\n", name, addr); exit(3); }
    if (getenv("BT2_STUB_LOG")) {
        static char seen[1 << 16];
        unsigned h = (addr * 2654435761u + (unsigned)name[0]) & 0xFFFF;
        if (!seen[h]) { seen[h] = 1; fprintf(stderr, "TEMP-STUB %s 0x%08X (devuelve 0) [llamada %lu]\n", name, addr, sGameStubCalls); }
    }
    return 0;
}

/* Se llama desde stubs.c (generado). Sin BT2_STUB_RET0 corta el programa en el primer stub. */
long full_stub(const char *name, unsigned addr) {
    sStubCalls++;
    if (getenv("BT2_STUB_BT")) {   /* quien llamo a cada stub (primera vez) */
        static char seen2[1 << 16];
        unsigned h = (addr * 2654435761u) & 0xFFFF;
        if (!seen2[h]) { void *bt[4]; int n = backtrace(bt, 4); seen2[h] = 1; fprintf(stderr, "  [%s] llamado desde:\n", name); backtrace_symbols_fd(bt + 1, n - 1, 2); }
    }
    if (getenv("BT2_STUB_RET0")) {
        static char seen[1 << 16];
        unsigned h = (addr * 2654435761u + (unsigned)name[0]) & 0xFFFF;
        if (!seen[h]) { seen[h] = 1; fprintf(stderr, "STUB %s 0x%08X (devuelve 0) [llamada %lu]\n", name, addr, sStubCalls); }
        if (sStubCalls > 2000000) { fprintf(stderr, "bt2full: demasiadas llamadas a stubs (ultima: %s 0x%08X)\n", name, addr); exit(3); }
        { const char *one = getenv("BT2_STUB_ONE"); /* "a,b": estos devuelven 1 (solo para explorar) */
          if (one && strstr(one, name)) return 1; }
        return 0;
    }
    fprintf(stderr, "STUB %s 0x%08X\n", name, addr);
    fflush(stderr);
    exit(3);
}

static ucontext_t sMainCtx, sGameCtx;
static int sResult;

static void game_entry(void) {
    /* _start (0x100008) pone a cero el bss (ya hecho por la carga), llama a dos funciones del CRT del SDK
       (0x338520 SetupThread y 0x32EEE0) y salta a func_00100388 con (argc, argv): es el `main` real. */
    void (*gamemain)(int, char **) = NULL;
    u32 i;
    static char *argv0[2] = {0, 0};
    for (i = 0; i < full_nfuncs; i++) if (full_funcs[i].addr == 0x100388) gamemain = (void (*)(int, char **))full_funcs[i].fn;
    if (!gamemain) { fprintf(stderr, "bt2full: no hay funcion nativa en 0x100388\n"); exit(2); }
    ((int (*)(int, char **))gamemain)(0, argv0);
    sResult = 0;
}

/* SIGUSR2: vuelca los 32 MB de RAM del PS2 a $BT2_DUMP (def. /tmp/bt2_port_ram.bin), mismo formato que eeMemory.bin de PCSX2 */
static void on_dump(int sig) {
    const char *fn = getenv("BT2_DUMP") ? getenv("BT2_DUMP") : "/tmp/bt2_port_ram.bin";
    static char zero[0x10000];
    FILE *f = fopen(fn, "wb");
    (void)sig;
    if (!f) return;
    fwrite(zero, 1, sizeof zero, f);
    fwrite((void *)(uintptr_t)0x10000u, 1, RAM_SIZE - 0x10000, f);
    fclose(f);
    fprintf(stderr, "bt2full: RAM volcada en %s\n", fn);
}

int main(int argc, char **argv) {
    static char altstack[1 << 16];
    stack_t ss = {altstack, 0, sizeof(altstack)};
    struct sigaction sa;
    size_t stksz = 8 << 20;   /* el relleno recompilado anida muchas llamadas C++ */
    void *stk;
    const char *elf = getenv("BT2_ELF") ? getenv("BT2_ELF") : "gamedata/SLUS_214.41";
    (void)argc; (void)argv;
    sigaltstack(&ss, NULL);
    memset(&sa, 0, sizeof sa);
    sa.sa_sigaction = on_segv;
    sa.sa_flags = SA_SIGINFO | SA_ONSTACK | SA_NODEFER;
    sigaction(SIGSEGV, &sa, NULL); sigaction(SIGBUS, &sa, NULL); sigaction(SIGILL, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL); sigaction(SIGABRT, &sa, NULL);
    signal(SIGUSR2, on_dump);
    load_elf(elf);
    full_patch_range(0x100000, OVL_LO);   /* el overlay se parchea al cargarlo (full_patch_range(OVL_LO, OVL_HI)) */
    stk = mmap(NULL, stksz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
    if (stk == MAP_FAILED || (uintptr_t)stk + stksz > 0xFFFFFFFFu) { fprintf(stderr, "bt2full: sin pila bajo 4 GB\n"); return 2; }
    sStackLo = (uintptr_t)stk; sStackHi = (uintptr_t)stk + stksz;
    getcontext(&sGameCtx);
    sGameCtx.uc_stack.ss_sp = stk;
    sGameCtx.uc_stack.ss_size = stksz;
    sGameCtx.uc_link = &sMainCtx;
    makecontext(&sGameCtx, game_entry, 0);
    fprintf(stderr, "bt2full: main del juego (0x100388) en una pila de 8 MB en %p\n", stk);
    { pthread_t th; if (pthread_create(&th, NULL, timer_thread, NULL) == 0) pthread_detach(th); }
    swapcontext(&sMainCtx, &sGameCtx);
    fprintf(stderr, "bt2full: main devolvio\n");
    return sResult;
}
