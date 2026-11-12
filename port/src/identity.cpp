// Hybrid port, step 1: guest RAM at its own host addresses (PS2X_IDENTITY_RDRAM=1, third_party PS2Recomp patch
// 0011, include/ps2_identity.h). The host does not let a process map its first 64 KB, so guest addresses below
// 0x10000 (the EE kernel's area) have no memory. The game reads that area in one place: the SDK's
// kFindAddress(start, end, value) (0x338388), which scans words for the syscall table. Here it runs on a 64 KB
// shadow of the kernel area holding the probe words PS2Runtime::initializeEeKernelState writes in the normal
// mode (0x2F0: 0x8001, 0x2F8: 0x1F80), and on the guest RAM above it. The shadow, g_ps2LowShadow (ps2_identity.h),
// is also where the recompiled code's own accesses below 0x10000 go (a guest null pointer reads 0 there).

#include "ps2_identity.h"
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace
{
constexpr uint32_t kFindAddressPc = 0x00338388u;
constexpr uint32_t kLowEnd = kPs2LowShadowSize;

uint32_t guestWord(uint32_t addr)
{
    addr &= 0x1FFFFFFCu;
    if (addr < kLowEnd)
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

// kFindAddress as the original computes it: `p` from start, return p when *p == value and p < end, else 0.
void findAddress(uint8_t *, R5900Context *ctx, PS2Runtime *)
{
    uint32_t p = getRegU32(ctx, 4);
    const uint32_t end = getRegU32(ctx, 5), value = getRegU32(ctx, 6);
    uint32_t result = 0u;
    for (;;)
    {
        const bool inside = p < end;
        if (guestWord(p) == value)
        {
            result = inside ? p : 0u;
            break;
        }
        if (!inside)
            break;
        p += 4u;
    }
    SET_GPR_U32(ctx, 2, result);
    ctx->pc = getRegU32(ctx, 31);
}
} // namespace

void installIdentityHle(PS2Runtime &runtime)
{
    if (!g_ps2IdentityRdram)
        return;
    const uint32_t hi = 0x80011F80u >> 16, lo = 0x80011F80u & 0xFFFFu;
    std::memcpy(g_ps2LowShadow + 0x2F0, &hi, 4);
    std::memcpy(g_ps2LowShadow + 0x2F8, &lo, 4);
    runtime.replaceFunction(kFindAddressPc, findAddress);
    std::fprintf(stderr, "[identity] guest RAM at its own addresses; kFindAddress on the kernel shadow\n");
}
