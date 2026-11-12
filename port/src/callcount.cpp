// BT2 port: call counters for chosen guest functions, to tell a busy loop from a real block.
//
// Usage: BT2_CALLTRACE=0x28B090,0x28B318,0x28DAA8   (up to 16 addresses, comma separated, hex with or without 0x)
//
// Each address in the runtime's function table is replaced by a wrapper that counts the call and then runs the
// recompiled function, so the count is the number of times the guest called it. The watchdog prints the totals
// every tick, and the log's timestamps give the rate: a rate in the millions per second is a spin loop, a count
// that stops growing while the game should be moving is a block. Functions the native C replaces later
// (installNativeFunctions runs after this) keep their native version, so turn BT2_NATIVE=0 when counting them.

#include "ps2_runtime.h"
#include <ps2_recompiled_functions.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace
{
constexpr int kMaxCounters = 16;

uint64_t g_counts[kMaxCounters];
uint32_t g_addrs[kMaxCounters];
const char *g_names[kMaxCounters];
int g_installed = 0;

template <int N> void countingFunction(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
{
    ++g_counts[N];
    switch (N)
    {
    case 0: func_0028B090_0x28b090(rdram, ctx, runtime); return;
    case 1: func_0028B318_0x28b318(rdram, ctx, runtime); return;
    case 2: func_0028B110_0x28b110(rdram, ctx, runtime); return;
    case 3: func_0028DAA8_0x28daa8(rdram, ctx, runtime); return;
    case 4: func_0028D990_0x28d990(rdram, ctx, runtime); return;
    case 5: func_0028DB40_0x28db40(rdram, ctx, runtime); return;
    case 6: func_002EDF48_0x2edf48(rdram, ctx, runtime); return;
    case 7: func_002EE050_0x2ee050(rdram, ctx, runtime); return;
    case 8: func_002EE350_0x2ee350(rdram, ctx, runtime); return;
    case 9: func_00102E80_0x102e80(rdram, ctx, runtime); return;
    default: return;
    }
}

// Wrapping means calling the recompiled function directly, so only addresses whose translation is a generated
// function can be counted. Anything else (an SDK stub, a function with no translation) is reported and skipped.
bool installOne(PS2Runtime &runtime, int slot, uint32_t addr, const char *name)
{
    PS2Runtime::RecompiledFunction fn = nullptr;
    switch (slot)
    {
    case 0: fn = countingFunction<0>; break;
    case 1: fn = countingFunction<1>; break;
    case 2: fn = countingFunction<2>; break;
    case 3: fn = countingFunction<3>; break;
    case 4: fn = countingFunction<4>; break;
    case 5: fn = countingFunction<5>; break;
    case 6: fn = countingFunction<6>; break;
    case 7: fn = countingFunction<7>; break;
    case 8: fn = countingFunction<8>; break;
    case 9: fn = countingFunction<9>; break;
    default: return false;
    }
    if (!runtime.replaceFunction(addr, fn))
    {
        std::fprintf(stderr, "[calls] %s (%s): outside the function table, skipped\n", name, addr);
        return false;
    }
    g_addrs[slot] = addr;
    g_names[slot] = name;
    ++g_installed;
    return true;
}

// The wrapper above calls one specific translation, so the slot -> address mapping has to be written down here.
// Only the functions this port has needed so far; add one (and its case in countingFunction) when needed.
struct Slot
{
    uint32_t addr;
    const char *name;
};

const Slot kSlots[] = {
    {0x0028B090u, "func_0028B090"},
    {0x0028B318u, "func_0028B318"},
    {0x0028B110u, "func_0028B110"},
    {0x0028DAA8u, "func_0028DAA8"},
    {0x0028D990u, "func_0028D990"},
    {0x0028DB40u, "func_0028DB40"},
    {0x002EDF48u, "thread4_entry"},
    {0x002EE050u, "thread5_entry"},
    {0x002EE350u, "thread_end_handler"},
    {0x00102E80u, "func_00102E80"},
};
} // namespace

void installCallCounters(PS2Runtime &runtime)
{
    const char *spec = std::getenv("BT2_CALLTRACE");
    // Not `spec[0] == '0'`: every address here starts with that digit.
    if (spec == nullptr || spec[0] == '\0' || std::strcmp(spec, "0") == 0)
        return;
    const int known = static_cast<int>(sizeof(kSlots) / sizeof(kSlots[0]));
    int slot = 0;
    for (const char *p = spec; *p != '\0' && slot < kMaxCounters;)
    {
        while (*p == ',' || *p == ' ')
            ++p;
        char *end = nullptr;
        const unsigned long v = std::strtoul(p, &end, 0);
        if (end == p)
            break;
        p = end;
        const uint32_t addr = static_cast<uint32_t>(v);
        const char *name = addr ? nullptr : "?";
        int found = -1;
        for (int i = 0; i < known; ++i)
            if (kSlots[i].addr == addr)
            {
                found = i;
                name = kSlots[i].name;
                break;
            }
        if (found < 0)
        {
            std::fprintf(stderr, "[calls] %08x: no counter wired for it (add it to kSlots)\n", addr);
            continue;
        }
        installOne(runtime, found, addr, name);
    }
    std::fprintf(stderr, "[calls] counting %d function(s)\n", g_installed);
}

void callCountReport()
{
    if (g_installed == 0)
        return;
    std::fprintf(stderr, "  [calls]");
    for (int i = 0; i < kMaxCounters; ++i)
        if (g_names[i] != nullptr)
            std::fprintf(stderr, " %s=%llu", g_names[i], static_cast<unsigned long long>(g_counts[i]));
    std::fprintf(stderr, "\n");
}