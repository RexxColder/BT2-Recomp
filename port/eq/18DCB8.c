#include "common.h"

s64 EftVram_AddImage(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* returns the whole TEX0 (was s32: TH/TCC/TFX lost) */
s64 EftVram_AddClut(s32 arg0);

void func_0018DCB8(u8 *arg0, u8 *arg1) {
    s32 s0;
    s64 s1; /* TEX0 from EftVram_AddImage (64-bit) */
    s32 s3;
    s32 s6;
    s32 a2;
    s32 count;
    s64 clut;
    s64 *dst;
    u8 *s5;
    u8 *src;

    if (arg1 == NULL) {
        return;
    }
    count = *(u8 *)(arg0 + 0x4C);
    if (count == 0) {
        return;
    }
    s6 = 0;
    s5 = arg0 + 0x44;
    do {
        a2 = *s5;
        if ((*(u16 *)(arg0 + 0x56) & 0x400) == 0) {
            s3 = 1 << a2;
            s0 = (s32)(arg1 + (a2 * 0x10));
            if ((*(s32 *)(arg1 + 0x84) & s3) == 0) {
                s1 = EftVram_AddImage(s0, 1, 0, 0);
                clut = EftVram_AddClut(s0);
                *(s64 *)s0 = (s64)s1 | (clut << 37);
                *(s32 *)(arg1 + 0x84) = *(s32 *)(arg1 + 0x84) | s3;
            }
        } else {
            s0 = a2 + *(u8 *)(arg0 + 0x4E);
            s3 = 1 << s0;
            if ((*(s32 *)(arg1 + 0x84) & s3) == 0) {
                *(s64 *)(arg0 + (a2 * 0x10) + 0x58) = *(s64 *)(arg1 + (a2 * 0x10));
                *(s64 *)(arg0 + (a2 * 0x10) + 0x60) = *(s64 *)(arg1 + (a2 * 0x10) + 8);
                s1 = EftVram_AddImage((s32)(arg0 + (a2 * 0x10) + 0x58), 1, 0,
                                      (s32)(arg0 + (a2 * 0x10) + 0x58));
                src = arg1 + (s0 * 0x10);
                dst = (s64 *)(arg0 + (s0 * 0x10) + 0xD8);
                *dst = *(s64 *)src;
                *(s64 *)((u8 *)dst + 8) = *(s64 *)(src + 8);
                clut = EftVram_AddClut((s32)dst);
                *(s64 *)src = (s64)s1 | (clut << 37);
                *(s32 *)(arg1 + 0x84) = *(s32 *)(arg1 + 0x84) | s3;
            }
        }
        s6 += 1;
        s5 += 1;
    } while (s6 < count);
}
