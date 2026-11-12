#include "common.h"

f32 EftMath_WrapAngle(f32 arg0);
void Mtx_StoreIdentity(void *arg0);
void Vec4_Set(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_00129C28(void *arg0, void *arg1);
s32 rand(void);

extern f32 D_00384FD8;
extern f32 D_00384FDC;
extern f32 D_00384FE0;
extern f32 D_00384FE4;

void EftRay_Setup(u8 *arg0, u8 *arg1) {
    f32 f2;
    f32 var_f1;
    f32 f25;
    f32 f23;
    f32 f21;
    f32 f22;
    f32 f0;
    f32 angle;
    f32 f1;
    s32 temp_a0;
    s32 rnd;
    u32 i;
    u8 *p;

    func_00129C28(arg0 + 0x480, arg1);
    *(f32 *)(arg0 + 0x48C) = 1.0f;
    Mtx_StoreIdentity(arg0 + 0x4A0);
    Vec4_Set(arg0 + 0x490, 1.0f, 1.0f, 1.0f, 1.0f);

    f2 = *(f32 *)(arg1 + 0x20);
    *(f32 *)(arg0 + 0x4E4) = f2;
    *(f32 *)(arg0 + 0x4E0) = 1.0f / (*(f32 *)(arg1 + 0x20) * D_00384FD8 * 30.0f);
    *(f32 *)(arg0 + 0x4E8) = 1.0f;
    *(s32 *)(arg0 + 0x4F8) = *(s32 *)(arg1 + 0x1C);
    *(f32 *)(arg0 + 0x4EC) = 1.0f / (f32)*(s32 *)(arg1 + 0x4C);
    *(s32 *)(arg0 + 0x508) = *(s32 *)(arg1 + 0x34);
    *(f32 *)(arg0 + 0x4F0) = *(f32 *)(arg1 + 0x2C);
    *(f32 *)(arg0 + 0x4F4) = *(f32 *)(arg1 + 0x30);
    *(s32 *)(arg0 + 0x4FC) = *(s32 *)(arg1 + 0x38);
    *(s32 *)(arg0 + 0x500) = *(s32 *)(arg1 + 0x40);
    *(s32 *)(arg0 + 0x504) = *(s32 *)(arg1 + 0x44);
    *(s32 *)(arg0 + 0x50C) = *(s32 *)(arg1 + 0x3C);
    *(s32 *)(arg0 + 0x510) = *(s32 *)(arg1 + 0x48);
    if (f2 > 0.0f) {
        *(s32 *)(arg0 + 0x514) |= 1;
    }
    if (*(u8 *)(arg1 + 0x50) != 0) {
        *(s32 *)(arg0 + 0x514) |= 0x10;
    }

    temp_a0 = *(s32 *)(arg1 + 0x38);
    if (temp_a0 >= 0) {
        var_f1 = (f32)temp_a0;
    } else {
        var_f1 = 2.0f * (f32)((temp_a0 & 1) | ((u32)temp_a0 >> 1));
    }
    f25 = 360.0f / var_f1;

    if (temp_a0 != 0) {
        f23 = D_00384FDC;
        f21 = D_00384FE0;
        f22 = D_00384FE4;
        i = 0;
        p = arg0;
        do {
            f0 = (f32)i;
            i += 1;
            rnd = rand();
            angle = EftMath_WrapAngle(((f25 * f0) / 180.0f) * f23 + (((f32)(rnd % 5) / 180.0f) * f23));

            p[0] = *(u8 *)(arg1 + 0x10);
            p[1] = *(u8 *)(arg1 + 0x14);
            p[2] = *(u8 *)(arg1 + 0x18);
            rnd = rand();
            *(f32 *)(p + 4) = angle;
            p[3] = (u8)(*(u8 *)(arg1 + 0x1C) - (rnd % 16));

            rnd = rand();
            *(f32 *)(p + 8) = *(f32 *)(arg1 + 0x24) + (((f32)rnd / f21) * 20.0f);

            rnd = rand();
            f1 = *(f32 *)(arg1 + 0x28) * (((f32)rnd / f21) * 5.0f);
            *(f32 *)(p + 0x10) = f1;
            if (f1 < f22) {
                *(f32 *)(p + 0x10) = f22;
            }
            if (*(s32 *)(arg0 + 0x504) == 1) {
                rnd = rand();
                *(f32 *)(p + 0x10) = *(f32 *)(arg1 + 0x28) + (((f32)rnd / f21) * 4.0f);
            }

            rnd = rand();
            *(f32 *)(p + 0x14) = ((f32)rnd / f21) * *(f32 *)(arg0 + 0x4F4);
            p += 0x18;
        } while (i < (u32)*(s32 *)(arg1 + 0x38));
    }
}
