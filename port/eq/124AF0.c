#include "common.h"

extern f32 D_0038412C;
extern f32 D_00384130;
extern f32 D_00384134;
extern f32 D_00384138;
extern f32 D_0038413C;
extern f32 D_00384140;
extern f32 D_00384144;
extern f32 D_00384148;
extern f32 D_0038414C;

void *func_00126040(s32 arg0);
void BtlOpp_GetTargetPos(s32 arg0, s32 arg1);
void func_00210868(s32 arg0, s32 arg1);
void *BtlChar_GetPos(s32 arg0);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
f32 BtlOpp_GetHalfHeightDiff(s32 arg0);
f32 func_0029DFD0(s32 arg0);
void func_00312680(f32 farg0, s32 arg0, s32 arg1);
f32 sinf(f32 farg0);
f32 cosf(f32 farg0);
f32 func_002086B0(s32 arg0);
f32 func_00210D10(s32 arg0);
f32 atan2f(f32 farg0, f32 farg1);
f32 Mathf_Asin(f32 farg0);
void func_002109C8(s32 arg0, s32 arg1);
f32 sceVu0InnerProduct(s32 arg0, s32 arg1);
s32 func_00210DD8(s32 arg0);
f32 func_00208DC0(s32 arg0);

void func_00124AF0(u8 *arg0) {
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *p;
    f32 h;
    f32 t;
    f32 t2;
    f32 a;
    f32 b;

    s1 = arg0 + 0x10B0;
    s2 = arg0 + 0x10A0;
    s4 = arg0 + 0x10D0;
    s3 = (u8 *)func_00126040((s32)arg0);
    BtlOpp_GetTargetPos((s32)s3, (s32)s1);
    func_00210868((s32)s3, (s32)(arg0 + 0x10C0));
    p = (u8 *)BtlChar_GetPos((s32)s3);
    func_00312650((s32)s4, (s32)s1, (s32)p);
    h = BtlOpp_GetHalfHeightDiff((s32)s3);
    *(f32 *)(s2 + 0x34) = *(f32 *)(s2 + 0x34) + h;
    t = func_0029DFD0((s32)s4);
    *(f32 *)(s2 + 0x50) = t;
    if (D_0038412C < t) {
        func_00312680(1.0f / t, (s32)s4, (s32)s4);
    } else {
        p = (u8 *)BtlChar_GetPos((s32)s3);
        a = sinf(*(f32 *)(p + 0xB4));
        *(s32 *)(s2 + 0x34) = 0;
        *(f32 *)(s2 + 0x30) = a;
        p = (u8 *)BtlChar_GetPos((s32)s3);
        b = cosf(*(f32 *)(p + 0xB4));
        *(s32 *)(s2 + 0x3C) = 0;
        *(f32 *)(s2 + 0x38) = b;
    }

    t = func_002086B0(*(s32 *)(s3 + 0x1534));
    *(f32 *)(s2 + 0x50) = *(f32 *)(s2 + 0x50) - t;
    t = func_00210D10((s32)s3);
    t2 = *(f32 *)(s2 + 0x50) - t;
    *(f32 *)(s2 + 0x50) = t2;
    if (t2 < 0.0f) {
        *(f32 *)(s2 + 0x50) = 0.0f;
    }

    t = atan2f(*(f32 *)(s2 + 0x30), *(f32 *)(s2 + 0x38)) - *(f32 *)(s3 + 0x150);
    *(f32 *)(s2 + 0x58) = t;
    if (t < D_00384130) {
        *(f32 *)(s2 + 0x58) = t + D_00384134;
    }
    t = *(f32 *)(s2 + 0x58);
    if (D_00384138 < t) {
        *(f32 *)(s2 + 0x58) = t - D_0038413C;
    }

    t = atan2f(*(f32 *)(s2 + 0x30), *(f32 *)(s2 + 0x38));
    p = (u8 *)BtlChar_GetPos((s32)s3);
    t2 = t - *(f32 *)(p + 0xB4);
    *(f32 *)(s2 + 0x54) = t2;
    if (t2 < D_00384130) {
        *(f32 *)(s2 + 0x54) = t2 + D_00384140;
    }
    t = *(f32 *)(s2 + 0x54);
    if (D_00384138 < t) {
        *(f32 *)(s2 + 0x54) = t - D_00384144;
    }

    *(f32 *)(s2 + 0x5C) = -Mathf_Asin(*(f32 *)(s2 + 0x34));
    func_002109C8((s32)s3, (s32)(s2 + 0x40));
    *(f32 *)(s2 + 0x60) = func_0029DFD0((s32)(s2 + 0x40));
    p = (u8 *)BtlChar_GetPos((s32)s3);
    t = sceVu0InnerProduct((s32)(s2 + 0x30), (s32)(p + 0x50));
    t2 = t - sceVu0InnerProduct((s32)(s2 + 0x30), (s32)(s2 + 0x40));
    if (D_00384148 < t2) {
        *(f32 *)(s2 + 0x64) = *(f32 *)(s2 + 0x50) / t2;
    } else {
        *(f32 *)(s2 + 0x64) = D_0038414C;
    }

    p = (u8 *)func_00210DD8((s32)s3);
    t = func_00208DC0((s32)p);
    *(f32 *)(s2 + 0x68) = t - *(f32 *)(s2 + 0x14);
}
