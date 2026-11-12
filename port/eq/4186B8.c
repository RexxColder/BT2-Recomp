#include "common.h"

s32 func_277E68(s32 arg0, s32 arg1);

/* 0x004186B8: GIF/GS packet builder into arg0 (returns arg0 + 0x40). Qwords: 0x6400000000008001 / 0x535310 (tag),
 * 0x156 (register list); then a word built from src+0x28 | (int)(f12 * (float)src+0x34) << 24 | src+0x30 << 16 |
 * src+0x2C << 8 (the same a1 value is also the first argument of func_277E68(src+0x8 + arg3, a1)); then
 * (src+0x18 << 4) << 16 | (src+0x14 << 4) with r1 = func_277E68 result: (r1 << 4 + 0x7200) << 16 | ((src+4 + arg2) << 4
 * + 0x7000), then (src+0x20 << 4) << 16 | (src+0x1C << 4), then (r2 << 4 + 0x7200) << 16 | ((src+0xC + arg2) << 4 + 0x7000)
 * with r2 = func_277E68(src+0x10 + arg3) (its arg1 is left over in the asm: GUESS 0). */
u8 *func_004186B8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, f32 farg0) {
    u8 *p = arg0;
    s64 a1v;
    s32 t;
    s32 r1;
    s32 r2;
    f32 fv;

    *(u64 *)(p + 0x00) = 0x6400000000008001ULL;
    *(u64 *)(p + 0x08) = 0x535310ULL;
    p += 0x10;
    *(u64 *)(p + 0x00) = 0x156ULL;

    fv = (f32)*(s32 *)(arg1 + 0x34) * farg0;
    t = (s32)fv;
    a1v = ((s64)*(s32 *)(arg1 + 0x30) << 16) | ((s64)*(s32 *)(arg1 + 0x2C) << 8);
    *(u64 *)(p + 0x08) = (s64)*(s32 *)(arg1 + 0x28) | ((s64)t << 24) | a1v;
    p += 0x10;

    *(u64 *)(p + 0x00) = ((s64)(s32)((u32)*(s32 *)(arg1 + 0x18) << 4) << 16) | (s64)(s32)((u32)*(s32 *)(arg1 + 0x14) << 4);

    r1 = func_277E68(*(s32 *)(arg1 + 0x8) + arg3, (s32)a1v);
    *(u64 *)(p + 0x08) = ((s64)(s32)(((u32)*(s32 *)(arg1 + 0x4) + (u32)arg2) << 4) + 0x7000)
                         | ((s64)(s32)(((u32)r1 << 4) + 0x7200) << 16);
    p += 0x10;

    *(u64 *)(p + 0x00) = ((s64)(s32)((u32)*(s32 *)(arg1 + 0x20) << 4) << 16) | (s64)(s32)((u32)*(s32 *)(arg1 + 0x1C) << 4);

    r2 = func_277E68(*(s32 *)(arg1 + 0x10) + arg3, 0); /* GUESS arg1 */
    *(u64 *)(p + 0x08) = ((s64)(s32)(((u32)*(s32 *)(arg1 + 0xC) + (u32)arg2) << 4) + 0x7000)
                         | ((s64)(s32)(((u32)r2 << 4) + 0x7200) << 16);
    p += 0x10;

    return p;
}
