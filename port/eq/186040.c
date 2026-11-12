#include "common.h"

void Vec4_Set(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void Mtx_Translate(void *arg0, void *arg1, void *arg2);
void func_00128C58(f32 farg0, void *arg0, void *arg1);
f32 EftMath_WrapAngle(f32 farg0);
void Mtx_RotateZ(f32 farg0, void *arg0, void *arg1);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 y, f32 x);
void Mtx_RotateX(f32 farg0, void *arg0, void *arg1);
void Mtx_RotateY(f32 farg0, void *arg0, void *arg1);
void func_00129C50(void *arg0, void *arg1, void *arg2);

void func_00186040(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0, f32 farg1, f32 farg2) {
    s64 M[8];
    s64 sp40[2];
    s64 sp50[2];
    s64 sp60[2];
    s64 *src;
    f32 f20;
    f32 f21;
    f32 f22;
    u8 *s3;
    u8 *s4;
    u8 *s5;
    u8 *s6;

    s3 = arg0 + 0x40;
    s4 = arg0 + 0x50;
    s5 = arg0 + 0x60;
    s6 = arg0 + 0x70;

    src = (s64 *)arg1;
    M[0] = src[0];
    M[1] = src[1];
    M[2] = src[2];
    M[3] = src[3];
    M[4] = src[4];
    M[5] = src[5];
    M[6] = src[6];
    M[7] = src[7];
    sp40[0] = ((s64 *)arg2)[0];
    sp40[1] = ((s64 *)arg2)[1];

    f20 = *(f32 *)(arg0 + 0x88) * 0.5f;
    f22 = -f20;
    f21 = 1.0f;

    Vec4_Set(sp60, farg1 * f20, farg2 * f20, 0.0f, f21);
    func_00129BD0(sp50, arg0, farg0);
    Vec4_Set(s3, f22, f22, 0.0f, f21);
    Vec4_Set(s4, f22, f20, 0.0f, f21);
    Vec4_Set(s5, f20, f22, 0.0f, f21);
    Vec4_Set(s6, f20, f20, 0.0f, f21);

    Mtx_Translate(M, M, sp60);
    func_00128C58(farg0, M, M);
    Mtx_RotateZ(EftMath_WrapAngle(*(f32 *)(arg0 + 0xA4) + *(f32 *)(arg0 + 0xAC)), M, M);

    f21 = EftMath_WrapAngle(Mathf_Asin(-*(f32 *)(arg0 + 0x14)));
    f20 = atan2f(*(f32 *)(arg0 + 0x10), *(f32 *)(arg0 + 0x18));
    f20 = EftMath_WrapAngle(f20);
    Mtx_RotateX(f21, M, M);
    Mtx_RotateY(f20, M, M);
    Mtx_Translate(M, M, sp50);
    Mtx_Translate(M, M, sp40);

    func_00129C50(s3, M, s3);
    func_00129C50(s4, M, s4);
    func_00129C50(s5, M, s5);
    func_00129C50(s6, M, s6);
}
