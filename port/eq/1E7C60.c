#include "common.h"

extern f32 D_003856B4 __attribute__((section(".data")));

void func_001E7C60(u8 *arg0) {
    u8 *p = arg0 + 0x10;
    f32 f0;
    f32 f1;
    f32 f2;

    if ((*(s32 *)(arg0 + 0x38) & 2) == 0) {
        return;
    }
    f0 = *(f32 *)(p + 0x18) + 1.0f;
    *(f32 *)(p + 0x18) = f0;
    if (!(f0 < 9.0f)) {
        f1 = *(f32 *)(p + 0x14);
        f2 = *(f32 *)(p + 0x10) + f1;
        *(s8 *)(p + 0x1C) = 1;
        *(f32 *)(p + 0x10) = f2;
        *(f32 *)(p + 0x14) = f1 * D_003856B4;
        if (f2 > 10.0f) {
            *(f32 *)(p + 0x10) = 10.0f;
        }
    }
}
