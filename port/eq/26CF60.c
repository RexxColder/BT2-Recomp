#include "common.h"

/* 0x0026CF60(dst, src, cur): flags = src[*cur]; *cur += 1. Two groups of three items: group g writes at dst + 0xC*g,
 * item k at +4*k. Bit t1 of flags (t1 counts every item from 0) selects the item: a set bit copies the 4 bytes at
 * src + *cur to the item and advances *cur by 4. */
void func_0026CF60(u8 *arg0, u8 *arg1, s32 *arg2) {
    s32 flags = arg1[*arg2];
    s32 t1 = 0;
    s32 g;
    s32 k;
    u8 *a3;

    *arg2 = *arg2 + 1;
    for (g = 0; g < 2; g++) {
        a3 = arg0 + g * 0xC;
        for (k = 0; k < 3; k++) {
            if ((flags >> t1) & 1) {
                s32 cur = *arg2;
                a3[0] = arg1[cur + 0];
                a3[1] = arg1[cur + 1];
                a3[2] = arg1[cur + 2];
                a3[3] = arg1[cur + 3];
                *arg2 = cur + 4;
            }
            t1 += 1;
            a3 += 4;
        }
    }
}
