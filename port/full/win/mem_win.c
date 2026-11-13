/*
 * Arranque Windows del build nativo (prueba F10, diseño B): la RAM del PS2 vive en la seccion .ps2ram del PE
 * (0x00100000..0x02000000), los registros/scratchpad se reservan con VirtualAlloc en su direccion PS2, y el main del
 * juego corre en la pila normal del proceso (el PE ocupa la zona baja, asi que Windows/Wine la pone arriba pero <4 GB).
 * Sin ucontext/sigaction/mmap/backtrace. Version de prueba, no release.
 */
#include <windows.h>
#include <winnt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint32_t u32;
typedef struct { u32 addr; void (*fn)(void); } FullFunc;
extern const FullFunc full_funcs[];
extern const u32 full_nfuncs;
extern unsigned char __bt2_ps2ram[];

#define RAM_SIZE 0x02000000u
#define OVL_LO 0x3B3100u
#define OVL_HI 0x421300u

static uintptr_t sStackLo, sStackHi;

/* Las cadenas DMA del juego llevan la direccion con el nibble alto en 2/3 (uncached/UCAB). Sin espejos, se normaliza. */
u32 full_dma_addr(u32 a) {
    if ((a >> 28) == 2u || (a >> 28) == 3u) a &= 0x0FFFFFFFu;
    if (a >= RAM_SIZE && sStackHi && (a & 0x0FFFFFFFu) >= (sStackLo & 0x0FFFFFFFu) && (a & 0x0FFFFFFFu) < (sStackHi & 0x0FFFFFFFu))
        return (a & 0x0FFFFFFFu) | (u32)(sStackLo & 0xF0000000u);
    return a;
}

void __stack_chk_fail(void) {
    fprintf(stderr, "bt2full: CANARIO DE PILA PISADO\n");
    ExitProcess(139);
}
void bt2_watch_byte(uintptr_t addr) { (void)addr; }
void bt2_watch_f32_from_env(void) { }

u32 full_native_to_ps2(uintptr_t p) {
    u32 i;
    for (i = 0; i < full_nfuncs; i++) if ((uintptr_t)full_funcs[i].fn == p) return full_funcs[i].addr;
    return 0;
}

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

static unsigned long sStubCalls;
long full_stub_game(const char *name, unsigned addr) {
    if (getenv("BT2_STUB_STRICT")) { fprintf(stderr, "STUB(juego) %s 0x%08X\n", name, addr); exit(3); }
    if (getenv("BT2_STUB_LOG")) {
        static char seen[1 << 16];
        unsigned h = (addr * 2654435761u + (unsigned)name[0]) & 0xFFFF;
        if (!seen[h]) { seen[h] = 1; fprintf(stderr, "TEMP-STUB %s 0x%08X (devuelve 0) [llamada %lu]\n", name, addr, sStubCalls); }
    }
    return 0;
}
long full_stub(const char *name, unsigned addr) {
    sStubCalls++;
    if (getenv("BT2_STUB_RET0")) {
        static char seen[1 << 16];
        unsigned h = (addr * 2654435761u + (unsigned)name[0]) & 0xFFFF;
        if (!seen[h]) { seen[h] = 1; fprintf(stderr, "STUB %s 0x%08X (devuelve 0) [llamada %lu]\n", name, addr, sStubCalls); }
        { const char *one = getenv("BT2_STUB_ONE");
          if (one && strstr(one, name)) return 1; }
        return 0;
    }
    fprintf(stderr, "STUB %s 0x%08X\n", name, addr);
    fflush(stderr);
    exit(3);
}

static DWORD WINAPI timer_thread(LPVOID arg) {
    (void)arg;
    for (;;) {
        int n;
        Sleep(1);
        for (n = 0; n < 4; n++) {
            volatile uint32_t *cnt = (volatile uint32_t *)(uintptr_t)(0x10000000u + 0x800u * n);
            volatile uint32_t *mode = (volatile uint32_t *)(uintptr_t)(0x10000010u + 0x800u * n);
            if (*mode & 0x80u) *cnt = (*cnt + 576u) & 0xFFFFu;
        }
    }
    return 0;
}

static void game_entry(void) {
    void (*gamemain)(int, char **) = NULL;
    u32 i;
    static char *argv0[2] = {0, 0};
    for (i = 0; i < full_nfuncs; i++) if (full_funcs[i].addr == 0x100388) gamemain = (void (*)(int, char **))full_funcs[i].fn;
    if (!gamemain) { fprintf(stderr, "bt2full: no hay funcion nativa en 0x100388\n"); exit(2); }
    ((int (*)(int, char **))gamemain)(0, argv0);
}

static LONG WINAPI crash_handler(EXCEPTION_POINTERS *ep) {
    CONTEXT *c = ep->ContextRecord;
    fprintf(stderr, "\nbt2full: excepcion 0x%08lX en %p rip=%p rsp=%p rax=%p rbx=%p rcx=%p rdx=%p\n",
            (unsigned long)ep->ExceptionRecord->ExceptionCode, ep->ExceptionRecord->ExceptionAddress,
            (void *)c->Rip, (void *)c->Rsp, (void *)c->Rax, (void *)c->Rbx, (void *)c->Rcx, (void *)c->Rdx);
    fflush(stderr);
    ExitProcess(139);
    return EXCEPTION_EXECUTE_HANDLER;
}

extern void bt2_init_stderr(void);

int main(int argc, char **argv) {
    const char *elf = getenv("BT2_ELF") ? getenv("BT2_ELF") : "gamedata/SLUS_214.41";
    DWORD old;
    NT_TIB *teb = (NT_TIB *)NtCurrentTeb();
    (void)argc; (void)argv;
    bt2_init_stderr();
    AddVectoredExceptionHandler(1, crash_handler);
    sStackLo = (uintptr_t)teb->StackLimit;
    sStackHi = (uintptr_t)teb->StackBase;
    printf("bt2full-win: base=%p ps2ram=%p pila=%p..%p\n", (void *)GetModuleHandle(NULL), (void *)__bt2_ps2ram,
           (void *)sStackLo, (void *)sStackHi);
    if (sStackHi > 0xFFFFFFFFu) { fprintf(stderr, "bt2full-win: pila arriba de 4 GB, no sirve para ptr32\n"); return 2; }
    if (__bt2_ps2ram != (unsigned char *)0x100000u) { fprintf(stderr, "bt2full-win: .ps2ram no esta en 0x100000\n"); return 2; }
    VirtualProtect((void *)0x100000u, 0x1F00000u, PAGE_EXECUTE_READWRITE, &old);
    if (!VirtualAlloc((void *)0x10000000u, 0x10000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE) ||
        !VirtualAlloc((void *)0x12000000u, 0x2000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE) ||
        !VirtualAlloc((void *)0x70000000u, 0x4000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)) {
        fprintf(stderr, "bt2full-win: no se pudieron reservar los registros/scratchpad (err %lu)\n", GetLastError());
        return 2;
    }
    load_elf(elf);
    full_patch_range(0x100000, OVL_LO);
    CreateThread(NULL, 0, timer_thread, NULL, 0, NULL);
    fprintf(stderr, "bt2full-win: main del juego (0x100388) en pila %p\n", (void *)sStackLo);
    game_entry();
    fprintf(stderr, "bt2full-win: main devolvio\n");
    return 0;
}
