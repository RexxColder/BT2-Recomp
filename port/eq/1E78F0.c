#include "common.h"

extern u8 *D_003876A0;
extern f32 D_003856B0;

void func_00208DE8(void *arg0, void *arg1, s32 arg2);
void Vec4_Set(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void BtlTask_SetDead(void *arg0);
void func_001E8450(void *arg0);
void func_001329A0(s32 arg0);
void func_002822C8(s32 arg0, s32 arg1, f32 farg0);
void func_0020CA90(void *arg0);
void func_0020C9B0(void *arg0, s32 arg1);
void func_001E7BA0(void *arg0);
void func_001E8518(void *arg0);
void func_001E7C60(void *arg0);

void func_001E78F0(u8 *arg0) {
    u8 sp[0x40] __attribute__((aligned(8)));
    u8 *s0;
    u8 *s2;
    s32 v1;
    s32 v1b;
    f32 f0;
    f32 f12v;
    f32 fa;
    f32 fb;
    f32 fc;
    f32 f21;
    f32 f20;
    f32 f14;
    f32 f22;
    f32 f23;
    f32 f24;
    s32 r;
    s32 cond;

    if ((*(u64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return;
    }
    s0 = *(u8 **)(arg0 + 0x38);
    s2 = s0 + 0x68;
    func_00208DE8(*(void **)s2, sp + 0x20, 3);

    v1 = arg0[1];
    if (v1 == 0) {
        arg0[1] = 1;
    } else if (v1 == 1) {
        if ((*(s32 *)(s0 + 0x30) & 3) == 0) {
            f22 = 4.0f;
            f23 = 8.0f;
            f24 = D_003856B0;

            r = rand();
            f0 = (f32)r / f24;
            f0 = f0 * f23;
            f21 = *(f32 *)(sp + 0x20);
            f21 = f21 + f0;

            r = rand();
            f0 = (f32)r / f24;
            f0 = f0 * f23;
            f20 = *(f32 *)(sp + 0x24);
            f21 = f21 - f22;
            f20 = f20 + f0;
            f20 = f20 - f22;

            r = rand();
            f0 = (f32)r / f24;
            f0 = f0 * f23;
            f20 = f20 - 6.0f;
            f14 = *(f32 *)(sp + 0x28);
            f14 = f14 + f0;
            f14 = f14 - f22;
            Vec4_Set(sp + 0x10, f21, f20, f14, 1.0f);
        }
        cond = (*(s32 *)(s0 + 0x30) < 0x19);
        if (!cond) {
            v1b = *(s32 *)(s0 + 0x38);
            if ((v1b & 1) == 0) {
                f22 = 4.0f;
                fa = *(f32 *)(sp + 0x20);
                fb = *(f32 *)(sp + 0x24) - f22;
                fc = *(f32 *)(sp + 0x28);
                Vec4_Set(sp, fa, fb, fc, 1.0f);
                v1b = *(s32 *)(s0 + 0x38) | 1;
                *(s32 *)(s0 + 0x38) = v1b;
            }
        } else {
            v1b = *(s32 *)(s0 + 0x38);
        }
        if ((v1b & 0x10) != 0) {
            func_001E8450(arg0);
            func_001329A0(0);
            func_002822C8(1, 0, 0.0f);
            func_0020CA90(*(void **)s2);
            func_0020C9B0(*(void **)s2, 1);
            func_001E7BA0(s0);
            arg0[1] = arg0[1] + 1;
        }
    } else if (v1 == 2) {
        f0 = *(f32 *)(s0 + 0x34) + 1.0f;
        if (10.0f < f0) {
            *(f32 *)(s0 + 0x34) = f0;
            *(s32 *)(s0 + 0x38) = *(s32 *)(s0 + 0x38) | 4;
            arg0[1] = arg0[1] + 1;
        }
    } else if (v1 == 3) {
        BtlTask_SetDead(arg0);
    }

    func_001E8518(arg0);
    func_001E7C60(s0);
    *(s32 *)(s0 + 0x30) = *(s32 *)(s0 + 0x30) + 1;
}
