#include "common.h"

extern u8 gGfx[] __attribute__((section(".data")));

void *EftBurst_PutModelEnv(void *arg0) {
    u8 *a;
    s64 t6;
    s64 v1;
    s64 last;

    a = (u8 *)arg0;
    t6 = 0x1000000000008006LL;
    v1 = (*(s32 *)(gGfx + 0x234) & 1) ? (s64)0xFF00000000080000ULL : (s64)0xFF00000000080070ULL;
    last = (*(s32 *)(gGfx + 0x234) & 1) ? 0x80000 : 0x80070;

    *(s64 *)(a + 0x08) = 0xE;
    *(s64 *)(a + 0x00) = t6;
    *(s64 *)(a + 0x10) = 0x60;
    *(s64 *)(a + 0x18) = 0x14;
    *(s64 *)(a + 0x28) = 0x47;
    *(s64 *)(a + 0x20) = 0x5000D;
    *(s64 *)(a + 0x38) = 0x4E;
    *(s64 *)(a + 0x30) = 0x310000E0;
    *(s64 *)(a + 0x40) = 0x44;
    *(s64 *)(a + 0x48) = 0x42;
    *(s64 *)(a + 0x50) = 1;
    *(s64 *)(a + 0x58) = 0x46;
    *(s64 *)(a + 0x68) = 0x4C;
    *(s64 *)(a + 0x60) = v1;
    *(s64 *)(a + 0x78) = 0xE;
    *(s64 *)(a + 0x70) = t6;
    *(s64 *)(a + 0x88) = 0x15;
    *(s64 *)(a + 0x80) = 0x60;
    *(s64 *)(a + 0x98) = 0x48;
    *(s64 *)(a + 0x90) = 0x5000D;
    *(s64 *)(a + 0xA8) = 0x4F;
    *(s64 *)(a + 0xA0) = 0x310000E0;
    *(s64 *)(a + 0xB0) = 0x44;
    *(s64 *)(a + 0xB8) = 0x43;
    *(s64 *)(a + 0xC0) = 1;
    *(s64 *)(a + 0xC8) = 0x46;
    *(s64 *)(a + 0xD8) = 0x4D;
    *(s64 *)(a + 0xD0) = last;
    return (void *)(a + 0xE0);
}
