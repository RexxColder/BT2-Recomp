#include "common.h"

/* 0x001B8088(obj): when the flags word at +0x60 has bit 0 set, returns 0. Otherwise, with f1 = the float at +0x3C:
 * if f1 < 1.0f, the float at +0x58 gets f0 = old + f1 (stored), and when f0 >= 1.0f the field is cleared to 0 and
 * the result is 1, else 0. If f1 >= 1.0f the result is f1 rounded to an integer (cvt.w.s: truncates toward zero-even). */
s32 func_001B8088(u8 *arg0) {
    f32 f1;
    f32 f0;
    s32 i;

    if (*(s32 *)(arg0 + 0x60) & 1) {
        return 0;
    }
    f1 = *(f32 *)(arg0 + 0x3C);
    if (f1 < 1.0f) {
        f0 = *(f32 *)(arg0 + 0x58) + f1;
        *(f32 *)(arg0 + 0x58) = f0;
        if (1.0f <= f0) {
            *(s32 *)(arg0 + 0x58) = 0;
            return 1;
        }
        return 0;
    }
    i = (s32)f1;
    return i;
}
