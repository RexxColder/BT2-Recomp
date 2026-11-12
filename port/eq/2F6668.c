#include "common.h"

s32 func_002EFFF0(s32 arg0);
void func_002F5CE8(void);
void func_002F4960(void *arg0, s32 *arg1, s32 *arg2);
extern s32 D_0034AED8;
extern s32 D_00354EC8;
extern s32 D_00354F14;

s32 func_002F6668(void *arg0) {
    s32 out[2];
    s32 temp_s1;
    s32 temp_s2;
    s32 var_v0;
    f32 temp_f1;
    f32 v;
    f32 cx;
    s32 ct;
    s32 r;
    s32 hi;

    var_v0 = 0;
    if (*(s8 *)((u8 *)arg0 + 0x72) != 0) {
        temp_s2 = func_002EFFF0(*(s32 *)((u8 *)arg0 + 0xC));
        func_002F5CE8();
        temp_s1 = D_00354EC8;
        D_00354EC8 = 0;
        func_002F4960(arg0, out, &out[1]);
        temp_f1 = (f32)D_00354F14;
        D_00354EC8 = temp_s1;
        var_v0 = temp_s2;
        v = ((f32)out[0] / (f32)out[1]) * temp_f1;
        hi = 0;
        if (v >= 2147483648.0f) {
            v = v - 2147483648.0f;
            hi = 1;
        }
        /* cvt.w.s: truncates toward zero */
        cx = v;
        ct = (s32)cx;
        r = ct;
        if (hi != 0) {
            r = (s32)((u32)r | 0x80000000u);
        }
        *(s32 *)((u8 *)arg0 + 0x9C) = r;
        *(s32 *)((u8 *)arg0 + 0xA0) = D_0034AED8;
    }
    return var_v0;
}
