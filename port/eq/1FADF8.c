#include "common.h"

f32 BtlCharApi_GetHeight(s32 a0);
s32 BtlChar_GetPos(void *a0);
void func_003126C8(void *a0, s32 a1);
f32 func_00273048(void);
void func_001FA3D0(void *a0, void *a1, s32 a2);
f32 func_001FA4F0(void *a0, s32 a1);
f32 func_001FA730(void *a0);
f32 sinf(f32 a);
f32 cosf(f32 a);
extern f32 D_003857E4;

void func_001FADF8(void *arg0, void *arg1, void *arg2, void *arg3) {
    f32 spf[12];
    u8 *s1;
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_t3;
    f32 temp_h2;
    f32 temp_sin;
    f32 temp_cos;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    f32 f8;

    s1 = (u8 *)arg0 + 0x150;
    temp_f20 = BtlCharApi_GetHeight(*(s32 *)((u8 *)arg0 + 0x1534));
    func_003126C8(spf, BtlChar_GetPos(arg0));
    temp_f21 = func_00273048();
    temp_h2 = BtlCharApi_GetHeight(*(s32 *)((u8 *)arg0 + 0x1534));
    temp_f21 = temp_f21 + (temp_h2 * 0.5f);
    temp_f20 = temp_f20 * D_003857E4;
    if (temp_f21 < spf[1]) {
        spf[1] = temp_f21;
    }
    temp_f20 = -temp_f20;
    spf[9] = temp_f20;
    spf[11] = 1.0f;
    spf[8] = 0.0f;
    spf[10] = 0.0f;
    temp_f21 = 1.0f;

    func_001FA3D0(arg0, &spf[4], *(s32 *)(s1 + 0xB4));
    temp_f23 = func_001FA4F0(arg0, *(s32 *)(s1 + 0xB4));
    temp_f22 = *(f32 *)(s1 + 0x0);
    temp_t3 = *(f32 *)(s1 + 0x10) + temp_f21;

    temp_sin = sinf(temp_f22);
    f6 = spf[10];
    f3 = spf[6] - f6;
    f5 = spf[9];
    f1 = spf[5] - f5;
    f4 = spf[0];
    f2 = spf[1];
    f0 = temp_sin * f3;
    f1 = f1 * temp_t3;
    f0 = f0 * temp_t3;
    f2 = f2 + f1;
    f4 = f4 + f0;
    f2 = f2 + f5;
    f4 = f4 + f6;
    *(f32 *)((u8 *)arg1 + 0x4) = f2;
    *(f32 *)((u8 *)arg1 + 0x0) = f4;

    temp_cos = cosf(temp_f22);
    *(f32 *)((u8 *)arg1 + 0xC) = temp_f21;
    f6 = spf[10];
    f2 = spf[6] - f6;
    f5 = spf[8] + spf[0];
    f1 = spf[2];
    f8 = f6 + f1;
    f3 = spf[9] + spf[1];
    f0 = temp_cos * f2;
    f0 = f0 * temp_t3;
    f1 = f1 + f0;
    f1 = f1 + f6;
    *(f32 *)((u8 *)arg1 + 0x8) = f1;

    *(f32 *)((u8 *)arg3 + 0xC) = 1.0f;
    *(f32 *)((u8 *)arg3 + 0x0) = f5;
    *(f32 *)((u8 *)arg3 + 0x4) = f3;
    *(f32 *)((u8 *)arg3 + 0x8) = f8;

    *(f32 *)((u8 *)arg2 + 0x0) = temp_f23;
    *(f32 *)((u8 *)arg2 + 0x4) = temp_f22;
    *(s32 *)((u8 *)arg2 + 0xC) = 0;
    *(s32 *)((u8 *)arg2 + 0x8) = 0;

    f0 = func_001FA730(arg0);
    *(f32 *)((u8 *)arg1 + 0x4) = *(f32 *)((u8 *)arg1 + 0x4) + f0;
}
