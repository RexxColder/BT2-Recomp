#include "common.h"

s32 func_0020C2E0(s32 arg0);
s32 func_0020C688(s32 arg0);
s32 func_0020C6D0(s32 arg0);
extern f32 D_00383E6C;
extern f32 D_00383E70;
extern f32 D_00383E74;
extern f32 D_00383E78;
extern f32 D_00383E7C;
extern u8 *D_003876A0;

void func_00110108(u8 *arg0, s32 arg1) {
    s32 *s0;
    s32 a;
    s32 v;
    f32 f0;
    f32 f2;

    s0 = (s32 *)(D_003876A0 + (arg1 * 0x1D0) + 0xE0);
    a = func_0020C688(arg1);
    if (*s0 == 1) {
        *(s32 *)(arg0 + 0x72C) = 0;
        *(s32 *)(arg0 + 0x730) = -0x80;
        return;
    }
    *(s32 *)(arg0 + 0x728) = a;
    *(s32 *)(arg0 + 0x72C) = (a >= 2) ? 1 : 0;
    if (func_0020C6D0(arg1) != 0) {
        *(s32 *)(arg0 + 0x72C) = 0;
    }
    v = *(s32 *)(arg0 + 0x730);
    if (*(s32 *)(arg0 + 0x72C) != 0) {
        v = v + 0x20;
        *(s32 *)(arg0 + 0x730) = v;
        if (v > 0) {
            if (func_0020C2E0(arg1) != 0) {
                *(f32 *)(arg0 + 0x738) = D_00383E6C;
                *(s32 *)(arg0 + 0x73C) = func_0020C2E0(arg1);
            }
            f0 = *(f32 *)(arg0 + 0x740) + D_00383E70;
            *(f32 *)(arg0 + 0x740) = f0;
            if (D_00383E74 < f0) {
                *(f32 *)(arg0 + 0x740) = f0 - D_00383E74;
            }
            f2 = *(f32 *)(arg0 + 0x738);
            if (f2 == 0.0f) {
                *(s32 *)(arg0 + 0x730) = 0;
                return;
            }
            f0 = f2 + D_00383E78;
            *(f32 *)(arg0 + 0x738) = f0;
            if (D_00383E7C <= f0) {
                *(f32 *)(arg0 + 0x738) = 0.0f;
            }
            *(s32 *)(arg0 + 0x730) = 0;
        }
    } else {
        *(f32 *)(arg0 + 0x738) = 0.0f;
        v = v - 0x20;
        *(s32 *)(arg0 + 0x73C) = 0;
        *(s32 *)(arg0 + 0x730) = v;
        if (v < -0x80) {
            *(s32 *)(arg0 + 0x730) = -0x80;
        }
    }
}
