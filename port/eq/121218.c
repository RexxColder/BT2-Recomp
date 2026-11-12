#include "common.h"

/* 0x00121218: d = 10 - arg0->8 * 2, clamped up to 2; if (arg0->0x18 % d) == 1 then arg0->0x14 |= arg1.
 * (The divide-by-zero trap of the original is not needed: d >= 2.) */
void func_00121218(u8 *arg0, s32 arg1) {
    u8 *t1 = arg0 + 0x10;
    s32 d = 10 - *(s32 *)(arg0 + 0x8) * 2;

    if (d < 2) {
        d = 2;
    }
    if (*(s32 *)(t1 + 0x8) % d == 1) {
        *(s32 *)(t1 + 0x4) = *(s32 *)(t1 + 0x4) | arg1;
    }
}
