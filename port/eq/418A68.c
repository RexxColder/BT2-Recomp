#include "common.h"

extern u8 gGfx[] __attribute__((section(".data")));
extern u8 *D_0042BB80 __attribute__((section(".data")));

u8 *func_004186B8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, f32 farg0);

/* 0x00418A68: same packet builder as 0x00418808 with a different tail mask and quadword source (see below).
 * 0x00418808: GS/DMA packet builder. pk is the packet cursor; flag (5th arg) selects the first block (sets two extra
 * tag quadwords and calls func_004186B8, whose return value becomes the cursor). The last quadword takes its low
 * 64 bits from D_0042BB80 -> 0xCC -> 0x10 -> (0xD4 index, 0xFC word) * 64 + 0x70, OR-ed with a constant. */
u8 *func_00418A68(u8 *pk, u8 *obj, s32 a2, s32 a3, s32 flag, f32 f) {
    u8 *t3 = pk;
    u8 *b;
    u8 *c;
    u8 *e;
    s32 i;
    s32 w;
    u64 lo;
    u64 mask;

    if (flag != 0) {
        *(u64 *)(t3 + 0x8) = 0xE;
        *(u64 *)(t3 + 0x0) = 0x1000000000008006ULL;
        t3 += 0x10;
        *(u64 *)(t3 + 0x8) = 0x4C;
        if (*(s32 *)(gGfx + 0x234) & 1) {
            *(u64 *)(t3 + 0x0) = 0xFFFFFF00080000ULL;
        } else {
            *(u64 *)(t3 + 0x0) = 0xFFFFFF00080070ULL;
        }
        t3 += 0x10;
        *(u64 *)(t3 + 0x8) = 0x47;
        *(u64 *)(t3 + 0x0) = 0x50000;
        t3 += 0x10;
        *(u64 *)(t3 + 0x0) = 0x44;
        *(u64 *)(t3 + 0x8) = 0x42;
        t3 += 0x10;
        *(u64 *)(t3 + 0x0) = 0;
        *(u64 *)(t3 + 0x8) = 0x3F;
        t3 += 0x10;
        *(u64 *)(t3 + 0x8) = 0x14;
        *(u64 *)(t3 + 0x0) = 0x60;
        t3 += 0x10;
        b = D_0042BB80;
        c = *(u8 **)(b + 0xCC);
        e = *(u8 **)(c + 0x10);
        *(u64 *)(t3 + 0x8) = 6;
        *(u64 *)(t3 + 0x0) = *(u64 *)(e + 0x30) | 0x0006080400003000ULL;
        t3 = func_004186B8(t3 + 0x10, obj + 0x38, a2, a3, f);
    }

    *(u64 *)(t3 + 0x8) = 0xE;
    *(u64 *)(t3 + 0x0) = 0x1000000000008004ULL;
    t3 += 0x10;
    *(u64 *)(t3 + 0x8) = 0x4C;
    if (*(s32 *)(gGfx + 0x234) & 1) {
        *(u64 *)(t3 + 0x0) = 0x80000;
    } else {
        *(u64 *)(t3 + 0x0) = 0x80070;
    }
    t3 += 0x10;
    *(u64 *)(t3 + 0x8) = 0x42;
    *(u64 *)(t3 + 0x0) = (flag != 0) ? 0x54 : 0x44;
    t3 += 0x10;
    *(u64 *)(t3 + 0x0) = 0;
    *(u64 *)(t3 + 0x8) = 0x3F;
    t3 += 0x10;

    if (flag != 0) {
        mask = (((u64)0xE << 16 | 0x2400) << 16) | 0x3041;
    } else {
        mask = (((u64)0x6 << 16 | 0x2400) << 16) | 0x3041;
    }
    b = D_0042BB80;
    c = *(u8 **)(b + 0xC0);
    w = *(s32 *)(c + 0xC);
    lo = (u64)(((s64)((w < 0 ? w + 0x3F : w) >> 6)) << 14) | mask;
    *(u64 *)(t3 + 0x0) = lo;
    *(u64 *)(t3 + 0x8) = 6;
    return func_004186B8(t3 + 0x10, obj, a2, a3, f);
}
