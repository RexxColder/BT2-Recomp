#include "common.h"

extern f32 D_00385898;

s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211288(s32 arg0);
s32 func_00240FA0(s32 arg0, s32 arg1);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void sceVu0Normalize(s32 arg0, s32 arg1);
f32 atan2f(f32 farg0, f32 farg1);

/* 0x00200550: direction helper. Builds a vector in arg2 (difference of a reference vector and
 * the pair at arg1+0x20 / arg1+0x30 or +0x10, chosen by the state words at arg1+0x54, +0xC, +0x64
 * and func_00240FA0), normalises it when a component exceeds the epsilon D_00385898, and returns
 * atan2f(x, z) for the x or z case, or 0 when only y is large (after normalising it). */
f32 func_00200550(u8 *arg0, u8 *arg1, f32 *arg2) {
    f32 tmp[4];
    u8 *a2p;
    f32 eps;
    f32 ax;
    f32 az;
    f32 ay;

    if (*(s32 *)(arg1 + 0x54) != 0) {
        func_00208DE8(*(s32 *)(arg0 + 0x1534), (s32)tmp, 3);
        func_00312650((s32)arg2, (s32)tmp, (s32)(arg1 + 0x20));
    } else {
        a2p = arg1 + 0x30;
        if (*(s32 *)(arg1 + 0xC) != 0) {
            u8 *p = *(u8 **)(arg1 + 0x64);

            if (p != NULL) {
                s32 s0 = *(s32 *)(p + 0x4);
                s32 ret = func_00211288(*(s32 *)p);
                s32 v1 = func_00240FA0(ret, s0);

                if (v1 == 0 || v1 == 2) {
                    a2p = arg1 + 0x10;
                }
            }
        }
        func_00312650((s32)arg2, (s32)(arg1 + 0x20), (s32)a2p);
    }

    eps = D_00385898;
    ax = arg2[0] < 0.0f ? -arg2[0] : arg2[0];
    if (eps < ax) {
        sceVu0Normalize((s32)arg2, (s32)arg2);
        return atan2f(arg2[0], arg2[2]);
    }
    az = arg2[2] < 0.0f ? -arg2[2] : arg2[2];
    if (eps < az) {
        sceVu0Normalize((s32)arg2, (s32)arg2);
        return atan2f(arg2[0], arg2[2]);
    }
    ay = arg2[1] < 0.0f ? -arg2[1] : arg2[1];
    if (eps < ay) {
        sceVu0Normalize((s32)arg2, (s32)arg2);
    }
    return 0.0f;
}
