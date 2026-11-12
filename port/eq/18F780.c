#include "common.h"

f32 EftMath_WrapAngle(f32 farg0);
void Mtx_RotateX(f32 farg0, void *arg0, void *arg1);
void Mtx_RotateY(f32 farg0, void *arg0, void *arg1);
void Mtx_RotateZ(f32 farg0, void *arg0, void *arg1);
void Mtx_Translate(void *arg0, void *arg1, void *arg2);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 y, f32 x);
void Vec4_Set(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_00129C50(void *arg0, void *arg1, void *arg2);

void func_0018F780(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, f32 farg0) {
    u8 sp[0x70] __attribute__((aligned(8)));
    u8 *s2;
    u8 *s4;
    s32 k;
    f32 v;
    f32 a;
    f32 f21;
    f32 f20;

    for (k = 0; k < 8; k++) {
        ((s64 *)sp)[k] = ((s64 *)arg1)[k];
    }
    ((s64 *)(sp + 0x40))[0] = ((s64 *)arg2)[0];
    ((s64 *)(sp + 0x40))[1] = ((s64 *)arg2)[1];
    ((s64 *)(sp + 0x50))[0] = ((s64 *)arg3)[0];
    ((s64 *)(sp + 0x50))[1] = ((s64 *)arg3)[1];

    s2 = arg0 + 0x80;
    s4 = s2;

    Mtx_RotateZ(EftMath_WrapAngle(*(f32 *)(arg0 + 0x58)), sp, sp);
    Mtx_RotateX(EftMath_WrapAngle(*(f32 *)(arg0 + 0x50)), sp, sp);
    Mtx_RotateY(EftMath_WrapAngle(*(f32 *)(arg0 + 0x54)), sp, sp);
    Mtx_RotateX(EftMath_WrapAngle(*(f32 *)(arg0 + 0x60)), sp, sp);
    Mtx_RotateY(EftMath_WrapAngle(*(f32 *)(arg0 + 0x64)), sp, sp);
    Mtx_RotateZ(EftMath_WrapAngle(*(f32 *)(arg0 + 0x68)), sp, sp);

    func_00129BD0(sp + 0x60, arg0, farg0);
    Mtx_Translate(sp, sp, sp + 0x60);

    a = Mathf_Asin(-*(f32 *)(sp + 0x54));
    f21 = EftMath_WrapAngle(a);
    f20 = atan2f(*(f32 *)(sp + 0x50), *(f32 *)(sp + 0x58));
    f20 = EftMath_WrapAngle(f20);
    Mtx_RotateX(f21, sp, sp);
    Mtx_RotateY(f20, sp, sp);
    Mtx_Translate(sp, sp, sp + 0x40);

    v = *(f32 *)(arg0 + 0xDC);
    Vec4_Set(s2, -v, -v, 0.0f, 1.0f);
    Vec4_Set(arg0 + 0xA0, -v, v, 0.0f, 1.0f);
    Vec4_Set(arg0 + 0x90, v, -v, 0.0f, 1.0f);
    Vec4_Set(arg0 + 0xB0, v, v, 0.0f, 1.0f);

    for (k = 0; k < 4; k++) {
        func_00129C50(s4, sp, s4);
        s4 += 0x10;
    }
}
