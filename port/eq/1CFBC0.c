#include "common.h"

extern u8 *D_00387E9C;
extern f32 D_003852E8;
extern f32 D_003852EC;
extern f32 D_003852F0;

s32 rand(void);
void Vec4_Set(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
/* 8 int regs (t3 is not set by the caller: passed as 0), 8 float regs, then 5 stack slots */
s32 func_001D6FF0(void *a0, void *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2,
                  f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  f32 st0, f32 st1, f32 st2, f32 st3, f32 st4);

s32 func_001CFBC0(void *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    s64 sp30[2];
    f32 v40[4];
    f32 f0;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f24;
    f32 f25;
    f32 f26;
    f32 f27;
    f32 f28;
    f32 f29;
    f32 f30;
    f32 f31;
    s32 i;
    s32 r;

    sp30[0] = *(s64 *)arg0;
    sp30[1] = *(s64 *)((u8 *)arg0 + 8);
    if (D_00387E9C[0x1491] == 0) {
        return 0;
    }

    f31 = 360.0f / (f32)arg1;
    f30 = ((f32)rand() / D_003852E8) * 360.0f;
    if (arg1 <= 0) {
        return 1;
    }
    f28 = 0.0f;
    f29 = D_003852E8;
    f25 = 1.0f;
    i = 0;
    do {
        r = rand();
        f0 = (f32)r / f29;
        f21 = arg3 * arg2;
        f22 = arg4 * arg2;
        f27 = arg2 * D_003852EC;
        f20 = f0 + 4.0f;
        rand();
        f0 = (f32)i;
        i += 1;
        f20 = f20 * arg2;
        f0 = f31 * f0;
        f20 = f20 * arg5;
        r = rand();
        f26 = f30 + f0;
        f0 = (f32)r / f29;
        f0 = f0 * 6.0f;
        f24 = f0 + 24.0f;
        r = rand();
        if (r & 1) {
            Vec4_Set(v40, f28, f28, f25, f25);
        } else {
            Vec4_Set(v40, f25, f28, f28, f25);
        }
        r = rand();
        if (r & 1) {
            f0 = 1.5f;
        } else {
            f0 = -1.5f;
        }
        func_001D6FF0(sp30, v40, 0x80, 0x80, 0x80, 0xB, 0,
                      f20, -7.5f, f21, f22, D_003852F0, f26, f24, -7.0f,
                      0.0f, f0, f27, 0.0f, f25);
    } while (i < arg1);
    return 1;
}
