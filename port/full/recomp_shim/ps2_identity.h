#pragma once
#include <cstdint>
// BT2 port (hybrid native/recompiled build): the PS2's main RAM can be mapped at its own addresses, so that host
// address == guest address and native C that shares the memory reads a guest pointer as a host pointer. The RAM's
// base pointer (rdram) is then 0; these helpers stand in for the runtime's `rdram == nullptr` sanity checks.
// Enabled by PS2X_IDENTITY_RDRAM=1 (ps2_memory.cpp); off, nothing changes.
extern bool g_ps2IdentityRdram;
inline bool ps2RdramMissing(const void *p) { return p == nullptr && !g_ps2IdentityRdram; }
// The host can not map its first 64 KB, so guest 0x0-0xFFFF (EE kernel area; also what a guest null pointer
// reads) lives in this shadow in identity mode (ps2_memory.cpp). Ps2FastPtr (ps2_runtime_macros.h) sends the
// recompiled code's accesses there; the shadow holds what PS2Runtime writes into the kernel area otherwise.
constexpr uint32_t kPs2LowShadowSize = 0x10000u;
extern uint8_t g_ps2LowShadow[kPs2LowShadowSize];
