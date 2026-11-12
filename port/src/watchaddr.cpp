// BT2 port: catch who writes a guest address, by backing that address up and comparing it every cycle.
//
// Usage: BT2_WATCH_ADDR=0x34BC80            (decimal or hex, one address)
//
// A hardware watchpoint in gdb cannot be attached here (ptrace_scope=1 blocks it) and the guest writes through
// thousands of recompiled functions, so this is done in software: the 8 bytes at the address are saved, the
// watchdog hook (once per rendered frame) compares them, and when they differ it prints the new value and the live
// context. Guest RAM is at its own host addresses (identity mode), so the address is the host pointer; the low
// 64 KB lives in the kernel shadow (ps2_identity.h).
//
// BT2_WATCH_STOP=1 aborts on the first write (one core with everything), default 0 keeps running and prints.

#include "ps2_runtime.h"
#include "ps2_identity.h"
#include "runtime/ee_scheduler.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace
{
const char *const kRegNames[32] = {
    "zero", "at", "v0", "v1", "a0", "a1", "a2",  "a3",  "t0", "t1", "t2",  "t3",  "t4",  "t5", "t6", "t7",
    "s0",   "s1", "s2", "s3", "s4", "s5", "s6",  "s7",  "t8", "t9", "k0",  "k1",  "gp",  "sp", "s8", "ra"};

uint8_t *g_addr = nullptr;
uint32_t g_guest = 0;
uint32_t g_saved[2] = {0, 0};
bool g_stop = false;
uint64_t g_writes = 0;

uint32_t guestWord(uint32_t addr)
{
    addr &= 0x1FFFFFFCu;
    if (addr < kPs2LowShadowSize)
    {
        uint32_t v;
        std::memcpy(&v, g_ps2LowShadow + addr, sizeof(v));
        return v;
    }
    if (addr >= PS2_RAM_SIZE)
        return 0u;
    uint32_t v;
    std::memcpy(&v, reinterpret_cast<const void *>(static_cast<uintptr_t>(addr)), sizeof(v));
    return v;
}

void setGuestWord(uint32_t addr, uint32_t value)
{
    addr &= 0x1FFFFFFCu;
    if (addr < kPs2LowShadowSize)
    {
        std::memcpy(g_ps2LowShadow + addr, &value, sizeof(value));
        return;
    }
    if (addr >= PS2_RAM_SIZE)
        return;
    std::memcpy(reinterpret_cast<void *>(static_cast<uintptr_t>(addr)), &value, sizeof(value));
}
} // namespace

int installGuestWatch(PS2Runtime &)
{
    const char *spec = std::getenv("BT2_WATCH_ADDR");
    // Not `spec[0] == '0'`: every address here starts with that digit.
    if (spec == nullptr || spec[0] == '\0' || std::strcmp(spec, "0") == 0)
        return 0;
    const char *s = std::getenv("BT2_WATCH_STOP");
    g_stop = (s != nullptr && s[0] == '1');
    g_guest = static_cast<uint32_t>(std::strtoul(spec, nullptr, 0)) & 0x1FFFFFFCu;
    g_addr = reinterpret_cast<uint8_t *>(static_cast<uintptr_t>(g_guest));
    if (g_guest < kPs2LowShadowSize)
        g_addr = g_ps2LowShadow + g_guest;
    g_saved[0] = guestWord(g_guest);
    g_saved[1] = guestWord(g_guest + 4);
    std::fprintf(stderr, "[watch-addr] %08x = %08x %08x%s\n", g_guest, g_saved[0], g_saved[1],
                 g_stop ? " (stop on first write)" : "");
    return 1;
}

void guestWatchTick(PS2Runtime &rt)
{
    if (g_addr == nullptr)
        return;
    const uint32_t w0 = guestWord(g_guest), w1 = guestWord(g_guest + 4);
    if (w0 == g_saved[0] && w1 == g_saved[1])
        return;
    ++g_writes;
    R5900Context *live = rt.eeScheduler().currentContext();
    std::fprintf(stderr, "[watch-addr] write #%llu to %08x: %08x %08x -> %08x %08x\n",
                 static_cast<unsigned long long>(g_writes), g_guest, g_saved[0], g_saved[1], w0, w1);
    if (live != nullptr)
    {
        // The PC in a watch tick is wherever the thread happens to be, which for a delay slot is one instruction
        // after the store (the recompsiled code runs the delay slot inside the branch handler). Print the whole
        // general register file: the store's operands are still in them.
        std::fprintf(stderr, "[watch-addr]   pc %08x ra %08x sp %08x branch_pc %08x in_delay_slot %d\n", live->pc,
                     getRegU32(live, 31), getRegU32(live, 29), live->branch_pc, live->in_delay_slot ? 1 : 0);
        std::fprintf(stderr, "[watch-addr]   ");
        for (int i = 2; i < 32; ++i)
        {
            if (i % 8 == 2)
                std::fprintf(stderr, "\n[watch-addr]   ");
            std::fprintf(stderr, " %s=%08x", kRegNames[i], getRegU32(live, i));
        }
        std::fprintf(stderr, "\n");
        // The guest stack around sp: for a recursion the saved return addresses are the code-range words.
        const uint32_t sp = getRegU32(live, 29);
        std::fprintf(stderr, "[watch-addr]   stack sp=%08x:", sp);
        for (uint32_t off = 0; off < 0x80u; off += 0x10u)
        {
            std::fprintf(stderr, " %08x", guestWord(sp + off));
        }
        std::fprintf(stderr, "\n");
    }
    g_saved[0] = w0;
    g_saved[1] = w1;
    std::fflush(stderr);
    if (g_stop)
        std::abort();
}