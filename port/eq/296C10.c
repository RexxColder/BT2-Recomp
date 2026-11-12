#include "common.h"

void Rigid_Integrate(s32 arg0, f32 farg0);
void Mat3_SetSkew(s32 arg0, s32 arg1);
void Mat3_Mul(s32 arg0, s32 arg1, s32 arg2);
void Mat3_Add(s32 arg0, s32 arg1, s32 arg2);
void Mat3_Orthonormalize(s32 arg0);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);

void Rigid_Step(s32 arg0, f32 farg0) {
    f32 a[4];
    f32 w[4];
    f32 m20[16];
    f32 m60[16];
    f32 mA0[16];
    s32 s3;
    f32 dt;

    dt = farg0;
    s3 = arg0 + 0x50;
    Rigid_Integrate(arg0, farg0);
    w[0] = dt * *(f32 *)(arg0 + 0xA0);
    w[1] = dt * *(f32 *)(arg0 + 0xA4);
    w[2] = dt * *(f32 *)(arg0 + 0xA8);
    a[0] = *(f32 *)(arg0 + 0x40) + (dt * *(f32 *)(arg0 + 0x90));
    a[1] = *(f32 *)(arg0 + 0x44) + (dt * *(f32 *)(arg0 + 0x94));
    a[2] = *(f32 *)(arg0 + 0x48) + (dt * *(f32 *)(arg0 + 0x98));
    Mat3_SetSkew((s32)m60, (s32)w);
    Mat3_Mul((s32)mA0, s3, (s32)m60);
    Mat3_Add((s32)m20, s3, (s32)mA0);
    Mat3_Orthonormalize((s32)m20);
    func_003126C8(arg0 + 0x40, (s32)a);
    sceVu0CopyMatrix(s3, (s32)m20);
}
