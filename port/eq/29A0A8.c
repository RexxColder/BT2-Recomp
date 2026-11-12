#include "common.h"

f32 Mathf_Acos(f32 arg0);
f32 sinf(f32 arg0);
void func_003126C8(u8 *arg0, u8 *arg1);
extern f32 D_00387230;

void Quat_Slerp(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0) {
    u8 sp[0x20];
    f32 a0;
    f32 a1;
    f32 a2;
    f32 a3;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;
    f32 dot;
    f32 theta;
    f32 sinT;
    f32 inv;
    f32 c0;
    f32 c1;

    func_003126C8(sp, arg1);
    func_003126C8(sp + 0x10, arg2);
    a0 = *(f32 *)(sp + 0x0);
    a1 = *(f32 *)(sp + 0x4);
    a2 = *(f32 *)(sp + 0x8);
    a3 = *(f32 *)(sp + 0xC);
    b0 = *(f32 *)(sp + 0x10);
    b1 = *(f32 *)(sp + 0x14);
    b2 = *(f32 *)(sp + 0x18);
    b3 = *(f32 *)(sp + 0x1C);

    dot = a0 * b0 + a1 * b1 + a2 * b2 + a3 * b3;
    if (dot < 0.0f) {
        b0 = -b0;
        b1 = -b1;
        b2 = -b2;
        b3 = -b3;
        *(f32 *)(sp + 0x10) = b0;
        *(f32 *)(sp + 0x14) = b1;
        *(f32 *)(sp + 0x18) = b2;
        *(f32 *)(sp + 0x1C) = b3;
        dot = a0 * b0 + a1 * b1 + a2 * b2 + a3 * b3;
    }
    if (dot > 1.0f) {
        dot = 1.0f;
    }

    theta = Mathf_Acos(dot);
    sinT = sinf(theta);
    if (sinT < D_00387230) {
        *(f32 *)(arg0 + 0x0) = a0;
        *(f32 *)(arg0 + 0xC) = a3;
        *(f32 *)(arg0 + 0x4) = a1;
        *(f32 *)(arg0 + 0x8) = a2;
    } else {
        inv = 1.0f / sinT;
        c0 = sinf(theta * (1.0f - farg0)) * inv;
        c1 = sinf(theta * farg0) * inv;
        *(f32 *)(arg0 + 0x0) = a0 * c0 + b0 * c1;
        *(f32 *)(arg0 + 0x4) = a1 * c0 + b1 * c1;
        *(f32 *)(arg0 + 0x8) = a2 * c0 + b2 * c1;
        *(f32 *)(arg0 + 0xC) = a3 * c0 + b3 * c1;
    }
}
