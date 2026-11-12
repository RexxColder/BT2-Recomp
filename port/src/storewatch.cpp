// BT2 port: catch the exact guest instruction that writes a watched address.
//
// Usage: BT2_STORE_ADDR=0x34BC80   (identity mode only: PS2X_IDENTITY_RDRAM=1)
//
// port/src/watchaddr.cpp polls once per rendered frame, so the pc it prints is wherever the thread happened to
// be, not where the store happened. Here the guest page holding the address is made read-only, so the store
// itself faults: the SIGSEGV handler prints the live context (the pc of the storing instruction, the register
// file, the guest stack) and aborts, leaving a core with everything.
//
// Only identity mode works: guest RAM is mapped at its own addresses, so protecting the page protects the guest
// bytes. Without identity mode there is no host address to protect and this does nothing.
//
// The handler must not lock anything, so it uses the context pointer cached by the watchdog (g_live) rather than
// EeScheduler::currentThread(), which walks an unordered_map. The executor runs between watchdog ticks, so the
// pointer can be one tick stale: the pc printed is then the address the thread had when it was last published,
// which is still the store's, because a store to this address happens exactly once and nothing else runs in
// between.

#include "ps2_runtime.h"
#include "ps2_identity.h"
#include "runtime/ee_scheduler.h"

#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>

namespace
{
constexpr size_t kPage = 4096u;
uint32_t g_guest = 0;
bool g_watched = false;
R5900Context *volatile g_live = nullptr;

const char *const kRegNames[32] = {
    "zero", "at", "v0", "v1", "a0", "a1", "a2",  "a3",  "t0", "t1", "t2",  "t3",  "t4",  "t5", "t6", "t7",
    "s0",   "s1", "s2", "s3", "s4", "s5", "s6",  "s7",  "t8", "t9", "k0",  "k1",  "gp",  "sp", "s8", "ra"};

// async-signal-safe output only.
void say(const char *s, size_t n)
{
    const ssize_t ignored = ::write(2, s, n);
    (void)ignored;
}

void sayStr(const char *s) { say(s, std::strlen(s)); }

void sayHex32(uint32_t v)
{
    char b[11];
    b[0] = '0';
    b[1] = 'x';
    for (int i = 0; i < 8; ++i)
        b[2 + i] = "0123456789abcdef"[(v >> ((7 - i) * 4)) & 0xF];
    b[10] = ' ';
    say(b, sizeof b);
}

uint32_t guestWord(uint32_t addr)
{
    addr &= 0x1FFFFFFCu;
    if (addr < kPs2LowShadowSize || addr >= PS2_RAM_SIZE)
        return 0u;
    uint32_t v;
    std::memcpy(&v, reinterpret_cast<const void *>(static_cast<uintptr_t>(addr)), sizeof(v));
    return v;
}

void handler(int, siginfo_t *info, void *)
{
    const uintptr_t faulted = reinterpret_cast<uintptr_t>(info->si_addr);
    // The protection is per page, so writes anywhere in it land here. Only the watched address matters: for the
    // others, let the store through (the watchdog re-protects on its next tick) and keep running.
    if (faulted != static_cast<uintptr_t>(g_guest))
    {
        mprotect(reinterpret_cast<void *>(faulted & ~(kPage - 1u)), kPage, PROT_READ | PROT_WRITE);
        return;
    }
    char head[160];
    const int n = std::snprintf(head, sizeof head, "[store] write at %p, watched %08x\n", info->si_addr, g_guest);
    say(head, static_cast<size_t>(n));
    R5900Context *c = g_live;
    if (c != nullptr)
    {
        sayStr("[store] pc ");
        sayHex32(c->pc);
        sayStr(" ra ");
        sayHex32(getRegU32(c, 31));
        sayStr(" sp ");
        sayHex32(getRegU32(c, 29));
        sayStr(" branch_pc ");
        sayHex32(c->branch_pc);
        sayStr(c->in_delay_slot ? " (delay slot)\n" : "\n");
        sayStr("[store] regs:");
        for (int i = 2; i < 32; ++i)
        {
            sayStr(" ");
            sayStr(kRegNames[i]);
            sayHex32(getRegU32(c, i));
            if (i % 6 == 1)
                sayStr("\n");
        }
        sayStr("\n[store] guest stack:\n");
        const uint32_t sp = getRegU32(c, 29);
        for (uint32_t off = 0; off < 0x100u; off += 0x10u)
        {
            sayStr("  ");
            sayHex32(sp + off);
            sayStr(":");
            for (int i = 0; i < 4; ++i)
                sayHex32(guestWord(sp + off + 4u * i));
            sayStr("\n");
        }
    }
    sayStr("[store] aborting\n");
    ::abort();
}
} // namespace

int installStoreWatch(PS2Runtime &)
{
    const char *spec = std::getenv("BT2_STORE_ADDR");
    // Not `spec[0] == '0'`: every address here starts with that digit.
    if (spec == nullptr || spec[0] == '\0' || std::strcmp(spec, "0") == 0)
        return 0;
    if (!g_ps2IdentityRdram)
    {
        std::fprintf(stderr, "[store] needs PS2X_IDENTITY_RDRAM=1 (no host address to protect otherwise)\n");
        return 0;
    }
    g_guest = static_cast<uint32_t>(std::strtoul(spec, nullptr, 0)) & 0x1FFFFFFCu;
    const uintptr_t page = static_cast<uintptr_t>(g_guest) & ~(kPage - 1u);
    if (mprotect(reinterpret_cast<void *>(page), kPage, PROT_READ) != 0)
    {
        std::fprintf(stderr, "[store] mprotect failed on %08x\n", static_cast<unsigned>(page));
        return 0;
    }
    struct sigaction sa
    {
    };
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO | SA_NODEFER;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, nullptr);
    g_watched = true;
    std::fprintf(stderr, "[store] %08x watched (page %08x read-only); the first write aborts with the exact pc\n",
                 g_guest, static_cast<unsigned>(page));
    return 1;
}

void storeWatchSetLiveContext(R5900Context *ctx)
{
    g_live = ctx;
    // Re-protect every tick, not only after a bypassed fault: the runtime may re-map the guest RAM (identity
    // mode mmaps it once, but anything that recreates the mapping drops the protection silently).
    if (g_watched)
        mprotect(reinterpret_cast<void *>(static_cast<uintptr_t>(g_guest) & ~(kPage - 1u)), kPage, PROT_READ);
}