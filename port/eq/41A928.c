#include "m2c_macros.h"

s32 func_0041A928(void) {
    u8 *p = *(u8 **)0x00387F2C;
    s32 x = *(s32 *)(p + 0x10A8);

    if (x == 0) {
        return -0x3C0;
    }
    if (x == 9) {
        return -96;
    }
    /* (x - 9) * 24 - 96 is an exact integer in f32, so the cvt.w.s rounding has nothing to round here */
    return (s32)((f32)(x - 9) * 24.0f + -96.0f);
}
