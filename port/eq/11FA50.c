#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_003876FC;

void func_0011FA50(void) {
    u8 *b = *(u8 **)D_003876A0;
    u8 *e = b + ((u32)*(s32 *)(b + 0x14) & ~3U);
    s32 ee = (s32)e;
    s32 i = 0;

    *(s32 *)(e + 4) = ee + *(s32 *)(e + 4);
    *(s32 *)(e + 8) = ee + *(s32 *)(e + 8);
    if (*(s32 *)e > 0) {
        do {
            u8 *w = (u8 *)(s32)*(s32 *)(e + 8) + i * 4;

            i += 1;
            *(s32 *)w = ee + *(s32 *)w;
        } while (i < *(s32 *)e);
    }
    *(s32 *)(D_003876FC + 0xC) = ee;
}
