/*
 * Relleno TEMPORAL (docs/agents/FALLBACK_SPEC.md): deja correr en bt2full las funciones del juego que aun no tienen C,
 * ejecutando el C++ que genero PS2Recomp (port/build/recomp/*_0x<dir>.cpp) sobre un R5900Context y un PS2Runtime
 * minimos propios (recomp_shim/ps2_runtime.h), sin el runtime real. Se apaga con `link_full.py --no-fallback`.
 *
 * Reglas:
 *  - El C nativo SIEMPRE gana: la tabla de relleno (bt2_fb_funcs, generada) solo contiene funciones sin C. Un salto/llamada
 *    del codigo recompilado a una direccion que no esta en esa tabla va al C nativo (tabla full_funcs de tables.c) por un
 *    adaptador de ABI: a0-a3,t0-t3 -> registros enteros de x86-64, f12-f19 -> xmm0-7; v0 <- rax, f0 <- xmm0.
 *  - El C nativo que llama a una funcion sin C entra por un adaptador generado en stubs.c (`movl $dir,%r11d; jmp
 *    bt2_fb_entry`) que vuelca los registros de argumento de x86-64 en el contexto y corre la funcion recompilada.
 *  - Un unico contexto (g_ctx) con pila del EE propia en la RAM del PS2: el codigo recompilado y el nativo que se llaman
 *    entre si comparten sp. rdram == nullptr (memoria en identidad: direccion PS2 == direccion del host).
 *  - Los saltos de cola (`j`) del recompilado vuelven al bucle de despacho (run_loop) con ctx->pc = destino, como en el
 *    runtime real; eeCheckpointDue() es falso salvo cada tanto, que avanza un vsync (bucles de espera del recompilado).
 * BT2_FALLBACK_LOG=1 imprime la primera vez que corre cada funcion de relleno y, al salir, cuantas corrieron.
 */
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
typedef struct { uint32_t addr; void (*fn)(void); } FullFunc;
extern const FullFunc full_funcs[];
extern const uint32_t full_nfuncs;
long Port_Syscall(int num, long a, long b, long c, long d);
void Port_VBlank(void);
void bt2_call_native(void *fn, const uint64_t *ints, const float *fl, uint64_t *raxOut, float *xmm0Out);
void bt2_fb_call(uint32_t addr, const uint64_t *regs, uint64_t *out);
void bt2_forward(R5900Context *ctx, uint32_t addr);
void bt2_fallback_init(void);
}

struct FbFunc { uint32_t addr, end; PS2Runtime::RecompiledFunction fn; const char *name; };
extern const FbFunc bt2_fb_funcs[];   // generada por link_full.py, ordenada por addr
extern const uint32_t bt2_fb_n;

bool g_ps2IdentityRdram = true;
uint8_t g_ps2LowShadow[kPs2LowShadowSize];

namespace {
constexpr uint32_t kSentinel = 0x00000008u;   // direccion sin funcion: el bucle termina cuando pc llega ahi
constexpr uint32_t kGp = 0x0038BDF0u;         // _start: lui a0,0x39; addiu a0,a0,-0x4210; daddu gp,a0,zero
constexpr uint32_t kSp = 0x01FFEF00u;         // pila del EE: [EndOfHeap 0x1EFE000 .. 0x1FFF000)

R5900Context g_ctx;
PS2Runtime g_rt;
bool g_log, g_trace;
std::vector<unsigned char> g_seen;
unsigned g_executed;
unsigned long g_checkpoints;

const FbFunc *find_fb(uint32_t pc) {
    uint32_t lo = 0, hi = bt2_fb_n;
    while (lo < hi) {   // ultimo con addr <= pc
        uint32_t m = (lo + hi) / 2;
        if (bt2_fb_funcs[m].addr <= pc) lo = m + 1; else hi = m;
    }
    if (!lo) return nullptr;
    const FbFunc *f = &bt2_fb_funcs[lo - 1];
    return pc < f->end ? f : nullptr;
}

const FullFunc *find_native(uint32_t pc) {
    uint32_t lo = 0, hi = full_nfuncs;
    while (lo < hi) {
        uint32_t m = (lo + hi) / 2;
        if (full_funcs[m].addr < pc) lo = m + 1; else hi = m;
    }
    return (lo < full_nfuncs && full_funcs[lo].addr == pc) ? &full_funcs[lo] : nullptr;
}

[[noreturn]] void fatal(R5900Context *ctx, uint32_t pc, const char *why) {
    std::fprintf(stderr, "bt2full[relleno]: FATAL %s en 0x%08X (ra=0x%08X sp=0x%08X)\n", why, pc, getRegU32(ctx, 31), getRegU32(ctx, 29));
    std::fflush(stderr);
    std::exit(4);
}

void call_native(R5900Context *ctx, const FullFunc *n) {
    // ints[0..7] = a0-a3,t0-t3 (64 bits completos: un eq con parametro s64 recibe el registro entero);
    // ints[8..15] = las 8 primeras ranuras de pila del EE (sp+0, +8, ...): los argumentos 9.. de la llamada MIPS.
    uint64_t ints[16], rax = 0;
    float fl[8], f0 = 0;
    for (int i = 0; i < 8; i++) {
        ints[i] = static_cast<uint64_t>(_mm_extract_epi64(ctx->r[4 + i], 0));
        fl[i] = ctx->f[12 + i];
    }
    const uint64_t *gsp = reinterpret_cast<const uint64_t *>(static_cast<uintptr_t>(getRegU32(ctx, 29)));
    // Las ranuras de pila se escriben a menudo con sw (la mitad alta es basura vieja): solo los 32 bits bajos, sin signo.
    for (int i = 0; i < 8; i++) ints[8 + i] = static_cast<uint32_t>(gsp[i]);
    const uint32_t ra = getRegU32(ctx, 31);
    bt2_call_native((void *)n->fn, ints, fl, &rax, &f0);
    SET_GPR_S32(ctx, 2, (int32_t)(uint32_t)rax);
    ctx->f[0] = f0;
    SET_GPR_U32(ctx, 31, ra);
    ctx->pc = ra;
}

void invoke(R5900Context *ctx, uint32_t pc) {
    if (const FbFunc *f = find_fb(pc)) {
        if (g_log) {
            unsigned i = (unsigned)(f - bt2_fb_funcs);
            if (!g_seen[i]) { g_seen[i] = 1; g_executed++; std::fprintf(stderr, "FALLBACK %s 0x%08X [%u]\n", f->name, f->addr, g_executed); }
        }
        ctx->pc = pc;
        f->fn(nullptr, ctx, &g_rt);
        return;
    }
    if (const FullFunc *n = find_native(pc)) {
        call_native(ctx, n);
        if (g_trace) std::fprintf(stderr, "  [recomp->nativo] 0x%08X(a0=%x a1=%x a2=%x) -> v0=0x%x\n", pc, getRegU32(ctx, 4), getRegU32(ctx, 5), getRegU32(ctx, 6), getRegU32(ctx, 2));
        return;
    }
    if (pc >= 0x40000000u && pc < 0x44000000u) {   // puntero a funcion NATIVA guardado por el C (p. ej. un callback): se llama directo
        FullFunc tmp = {pc, reinterpret_cast<void (*)(void)>(static_cast<uintptr_t>(pc))};
        call_native(ctx, &tmp);
        return;
    }
    if (pc == 0) fatal(ctx, pc, "salto a 0 (puntero a funcion nulo)");
    fatal(ctx, pc, "no hay funcion (ni de relleno ni nativa)");
}

// Corre desde `pc` hasta que el control vuelva a `stop` (los saltos de cola dejan ctx->pc = destino y se despachan aqui).
void run_loop(R5900Context *ctx, uint32_t pc, uint32_t stop) {
    bt2_fallback_init();   // perezoso: g_ctx (constructor de C++) ya existe
    ctx->pc = pc;
    while (ctx->pc != stop) invoke(ctx, ctx->pc);
}
}  // namespace

extern "C" void bt2_fallback_init(void) {
    static bool done;
    if (done) return;
    done = true;
    g_log = std::getenv("BT2_FALLBACK_LOG") != nullptr;
    g_trace = g_log && std::getenv("BT2_FALLBACK_LOG")[0] == '2';   // =2: tambien cada llamada recompilado -> nativo
    g_seen.assign(bt2_fb_n, 0);
    SET_GPR_U32(&g_ctx, 29, kSp);
    SET_GPR_U32(&g_ctx, 28, kGp);
    if (g_log) std::atexit([] { std::fprintf(stderr, "bt2full[relleno]: %u de %u funciones de relleno ejecutadas\n", g_executed, bt2_fb_n); });
}

// Nativo -> recompilado. regs: 8 enteros (a0-a3,t0-t3) y 8 floats (f12-f19) tal como los dejo bt2_fb_entry.
extern "C" void bt2_fb_call(uint32_t addr, const uint64_t *regs, uint64_t *out) {
    R5900Context *ctx = &g_ctx;
    const float *fl = reinterpret_cast<const float *>(regs + 8);
    const uint32_t ra = getRegU32(ctx, 31);
    for (int i = 0; i < 8; i++) { SET_GPR_U32(ctx, 4 + i, (uint32_t)regs[i]); ctx->f[12 + i] = fl[i]; }
    SET_GPR_U32(ctx, 31, kSentinel);
    run_loop(ctx, addr, kSentinel);
    SET_GPR_U32(ctx, 31, ra);
    out[0] = getRegU32(ctx, 2);
    std::memcpy(reinterpret_cast<float *>(out + 1), &ctx->f[0], 4);
}

// Llamada directa de C++ a otra funcion recompilada que no esta en el relleno (tiene C): sale por el despachador.
extern "C" void bt2_forward(R5900Context *ctx, uint32_t addr) {
    run_loop(ctx, addr, getRegU32(ctx, 31));
}

asm(R"(
    .text
    .globl bt2_call_native
    .type bt2_call_native, @function
bt2_call_native:
    push %rbp
    mov %rsp, %rbp
    push %rbx
    push %r12
    mov %rcx, %r12
    mov %r8, %rbx
    mov %rdi, %r10
    mov %rsi, %r11
    movss 0(%rdx), %xmm0
    movss 4(%rdx), %xmm1
    movss 8(%rdx), %xmm2
    movss 12(%rdx), %xmm3
    movss 16(%rdx), %xmm4
    movss 20(%rdx), %xmm5
    movss 24(%rdx), %xmm6
    movss 28(%rdx), %xmm7
    push 120(%r11)
    push 112(%r11)
    push 104(%r11)
    push 96(%r11)
    push 88(%r11)
    push 80(%r11)
    push 72(%r11)
    push 64(%r11)
    push 56(%r11)
    push 48(%r11)
    mov 0(%r11), %rdi
    mov 8(%r11), %rsi
    mov 16(%r11), %rdx
    mov 24(%r11), %rcx
    mov 32(%r11), %r8
    mov 40(%r11), %r9
    mov $8, %eax
    call *%r10
    add $80, %rsp
    mov %rax, (%r12)
    movss %xmm0, (%rbx)
    pop %r12
    pop %rbx
    pop %rbp
    ret
    .size bt2_call_native, .-bt2_call_native

    .globl bt2_fb_entry
    .type bt2_fb_entry, @function
bt2_fb_entry:
    push %rbp
    mov %rsp, %rbp
    sub $128, %rsp
    mov %rdi, 0(%rsp)
    mov %rsi, 8(%rsp)
    mov %rdx, 16(%rsp)
    mov %rcx, 24(%rsp)
    mov %r8, 32(%rsp)
    mov %r9, 40(%rsp)
    mov 16(%rbp), %rax
    mov %rax, 48(%rsp)
    mov 24(%rbp), %rax
    mov %rax, 56(%rsp)
    movss %xmm0, 64(%rsp)
    movss %xmm1, 68(%rsp)
    movss %xmm2, 72(%rsp)
    movss %xmm3, 76(%rsp)
    movss %xmm4, 80(%rsp)
    movss %xmm5, 84(%rsp)
    movss %xmm6, 88(%rsp)
    movss %xmm7, 92(%rsp)
    mov %r11d, %edi
    mov %rsp, %rsi
    lea 96(%rsp), %rdx
    call bt2_fb_call
    mov 96(%rsp), %rax
    movss 104(%rsp), %xmm0
    leave
    ret
    .size bt2_fb_entry, .-bt2_fb_entry
)");

// ---------------------------------------------------------------------------------------------------------------
// PS2Runtime minimo
bool PS2Runtime::dispatchGuestBranch(uint8_t *, R5900Context *ctx, uint32_t targetPc, uint32_t sourcePc, uint32_t fallthroughPc,
                                     GuestBranchKind kind, const char *) {
    (void)sourcePc;
    ctx->pc = targetPc;
    if (kind == GuestBranchKind::DirectCall || kind == GuestBranchKind::IndirectCall) {
        run_loop(ctx, targetPc, fallthroughPc);
        return true;
    }
    return false;   // salto/retorno: la funcion generada retorna y el bucle de despacho sigue en ctx->pc
}

bool PS2Runtime::eeCheckpointDue(uint32_t) noexcept {
    // Bucles de espera del codigo recompilado (esperan un flag que levanta la interrupcion de vsync): cada tanto un vsync.
    if ((++g_checkpoints & 0x1FFFFFu) == 0) {
        if (g_log) if (g_checkpoints < (8u << 21) || (g_checkpoints & 0xFFFFFFu) == 0) std::fprintf(stderr, "bt2full[relleno]: bucle de espera en pc=0x%08X ra=0x%08X, vsync forzado (checkpoint %lu)\n", g_ctx.pc, getRegU32(&g_ctx, 31), g_checkpoints);
        Port_VBlank();
    }
    return false;
}

void PS2Runtime::SignalException(R5900Context *ctx, PS2Exception e) {
    static int n;
    if (n++ < 5) std::fprintf(stderr, "bt2full[relleno]: excepcion %d en pc=0x%08X (ignorada)\n", (int)e, ctx->pc);
}
void PS2Runtime::handleBreak(uint8_t *, R5900Context *ctx) {
    static int n;
    if (n++ < 5) std::fprintf(stderr, "bt2full[relleno]: break en pc=0x%08X (ignorado)\n", ctx->pc);
}
void PS2Runtime::clearLLBit(R5900Context *ctx) { ctx->llbit = 0; }
void PS2Runtime::handleSyscall(uint8_t *r, R5900Context *ctx) { handleSyscall(r, ctx, 0); }
void PS2Runtime::handleSyscall(uint8_t *, R5900Context *ctx, uint32_t id) {
    const int num = (int)((id ? id : getRegU32(ctx, 3)) & 0xFF);
    long r = Port_Syscall(num, (long)getRegU32(ctx, 4), (long)getRegU32(ctx, 5), (long)getRegU32(ctx, 6), (long)getRegU32(ctx, 7));
    SET_GPR_S32(ctx, 2, (int32_t)r);
}

// Memoria en identidad: registros (0x1xxxxxxx) y scratchpad (0x7xxxxxxx) son memoria comun del host.
template <class T> static inline T rd(uint32_t a) { T v; std::memcpy(&v, reinterpret_cast<void *>(static_cast<uintptr_t>(a)), sizeof v); return v; }
template <class T> static inline void wr(uint32_t a, T v) { std::memcpy(reinterpret_cast<void *>(static_cast<uintptr_t>(a)), &v, sizeof v); }
uint8_t PS2Runtime::Load8(uint8_t *, R5900Context *, uint32_t a) { return rd<uint8_t>(a); }
uint16_t PS2Runtime::Load16(uint8_t *, R5900Context *, uint32_t a) { return rd<uint16_t>(a); }
uint32_t PS2Runtime::Load32(uint8_t *, R5900Context *, uint32_t a) { return rd<uint32_t>(a); }
uint64_t PS2Runtime::Load64(uint8_t *, R5900Context *, uint32_t a) { return rd<uint64_t>(a); }
__m128i PS2Runtime::Load128(uint8_t *, R5900Context *, uint32_t a) { return rd<__m128i>(a); }
void PS2Runtime::Store8(uint8_t *, R5900Context *, uint32_t a, uint8_t v) { wr(a, v); }
void PS2Runtime::Store16(uint8_t *, R5900Context *, uint32_t a, uint16_t v) { wr(a, v); }
void PS2Runtime::Store32(uint8_t *, R5900Context *, uint32_t a, uint32_t v) {
    // CHCR de un canal DMA (0x10008000..0x1000EFFF, +0x00): la transferencia "termina" al instante (como Port_DmaChcr).
    if (a >= 0x10008000u && a < 0x1000F000u && (a & 0xFFu) == 0) v &= ~0x100u;
    wr(a, v);
}
void PS2Runtime::Store64(uint8_t *, R5900Context *, uint32_t a, uint64_t v) { wr(a, v); }
void PS2Runtime::Store128(uint8_t *, R5900Context *, uint32_t a, __m128i v) { wr(a, v); }
