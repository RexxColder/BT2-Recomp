#include "common.h"

s32 BtlChar_GetPos(u8 *arg0);
f32 func_001017F0(s32 arg0, s32 arg1);
void func_0020FAD0(s32 arg0, s32 *arg1, s32 *arg2, f32 farg0, f32 farg1);
extern f32 D_00385A0C;

f32 func_00210670(u8 *arg0) {
    s32 out[2];
    u8 *s3;
    u8 *s6;
    s32 s7;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 tr;
    f32 x;
    f32 result;

    s3 = arg0 + 0x4F4;
    s6 = arg0 + 0x364;
    s7 = 0;

    func_0020FAD0(BtlChar_GetPos(arg0), out, &out[1], 200.0f, D_00385A0C);
    x = (((f32)out[0] / 127.0f) - 1.0f) * 200.0f;

    /* cvt.w.s: truncates toward zero */
    tr = (s32)x;
    s2 = tr;
    if (0 < s2) {
        s2 = 0;
    }
    if (s2 < -0x3C0) {
        s2 = -0x3C0;
    }
    result = x;

    do {
        if (*(s3 - 0x190) != 0 || *s3 != 0) {
            s1 = 0;
            s0 = (s7 * 8) + 0x3C1B;
            do {
                s32 cur = s1;
                s1 += 1;
                if (*s6 & (1 << cur)) {
                    result = func_001017F0(s0, s2);
                }
                s0 += 1;
            } while (s1 < 8);
        }
        s7 += 1;
        s3 += 1;
        s6 += 1;
    } while (s7 < 4);

    return result;
}
