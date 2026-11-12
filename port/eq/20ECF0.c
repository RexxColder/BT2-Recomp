#include "common.h"

extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_003859BC;
extern f32 D_003859C0;
extern f32 D_003859C4;
extern f32 D_003859C8;
extern f32 D_003859CC;

s32 func_00211288(s32 arg0);
void BtlOpp_GetDelta(s32 arg0, f32 *arg1);
void sceVu0Normalize(f32 *arg0, f32 *arg1);
u8 *BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 BtlCharApi_GetHeight(s32 arg0);
f32 Mathf_Asin(f32 farg0);
f32 func_001A7D30(s32 arg0, s32 arg1);
void func_001FC3B0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                   s32 a8, s32 a9, s32 a10, s32 a11, s32 a12,
                   f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);

void func_0020ECF0(s32 arg0, s32 arg1) {
    f32 sp30[4];
    f32 f20;
    f32 f21;
    f32 f22;
    s32 s2;
    s32 s3;
    s32 s4;
    u8 *pos;

    s3 = 0x11;
    s4 = 3;
    s2 = func_00211288(arg0);
    f22 = 0.0f;
    BtlOpp_GetDelta(s2, sp30);
    f21 = 0.0f;
    sceVu0Normalize(sp30, sp30);
    f20 = 0.0f;

    switch (arg1) {
    case 0:
        f20 = D_003859BC;
        if (arg0 != 0) {
            f20 = D_003859C0;
        }
        f22 = 0.0f;
        pos = BtlChar_GetPos(s2);
        f21 = BtlUtil_WrapAngle(*(f32 *)(pos + 0xB4) - f20);
        f20 = BtlCharApi_GetHeight(arg0);
        f20 = f20 + func_001A7D30(arg0, arg1);
        break;
    case 1:
        f20 = 0.5f;
        if (arg0 != 0) {
            f20 = -0.5f;
        }
        f22 = 0.0f;
        pos = BtlChar_GetPos(s2);
        f21 = BtlUtil_WrapAngle(*(f32 *)(pos + 0xB4) - f20);
        f20 = BtlCharApi_GetHeight(arg0);
        f20 = f20 + func_001A7D30(arg0, arg1);
        break;
    case 2:
        f20 = D_003859C4;
        s4 = 0x30;
        pos = BtlChar_GetPos(s2);
        s3 = 0x30;
        f21 = BtlUtil_WrapAngle(*(f32 *)(pos + 0xB4) - f20);
        f22 = Mathf_Asin(sp30[1]) - D_003859C8;
        f20 = BtlCharApi_GetHeight(arg0) * D_003859CC;
        f20 = f20 + func_001A7D30(arg0, 2);
        break;
    default:
        break;
    }
    func_001FC3B0(s2, (s32)D_002C3630, (s32)D_002C3630, (s32)D_002C3630,
                  (s32)D_002C3630, (s32)D_002C3630, (s32)D_002C3630, s4,
                  s4, s3, s3, 1, 0x45,
                  f21, 0.0f, f22, 0.0f, f20, 0.0f);
}
