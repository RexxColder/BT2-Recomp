#include "common.h"

s64 EftVram_AddImage(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* whole TEX0 (was s32) */
u64 EftVram_AddClut(s32 arg0);

void func_001A43C8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *s0;
    u8 *s1;
    s32 s2;
    s32 idx;
    s32 clut;
    s64 v;

    if ((*(s32 *)(*(u8 **)(arg1 + 0x34) + 0x104) & (1 << *(s32 *)(arg1 + 0x30))) == 0) {
        s2 = 0;
        if (*(s32 *)(arg0 + 0x100) > 0) {
            s0 = arg0 + 0x148;
            s1 = arg0;
            do {
                *(s64 *)s0 = (s64)EftVram_AddImage((s32)(s1 + 0x108), 1, 0, arg3, arg4, arg5);
                clut = EftVram_AddClut((s32)(s1 + 0x118));
                v = *(s64 *)s0 | ((s64)clut << 37);
                s1 += 0x20;
                *(s64 *)s0 = v;
                idx = *(s32 *)(arg1 + 0x30) + s2;
                s2 += 1;
                *(s64 *)(*(u8 **)(arg1 + 0x34) + idx * 0x10) = v;
                s0 += 8;
            } while (s2 < *(s32 *)(arg0 + 0x100));
        }
        *(s32 *)(*(u8 **)(arg1 + 0x34) + 0x104) =
            *(s32 *)(*(u8 **)(arg1 + 0x34) + 0x104) | (1 << *(s32 *)(arg1 + 0x30));
        return;
    }

    s2 = 0;
    if (*(s32 *)(arg0 + 0x100) > 0) {
        do {
            idx = *(s32 *)(arg1 + 0x30) + s2;
            *(s64 *)(arg0 + 0x148 + s2 * 8) = *(s64 *)(*(u8 **)(arg1 + 0x34) + idx * 0x10);
            s2 += 1;
        } while (s2 < *(s32 *)(arg0 + 0x100));
    }
}
