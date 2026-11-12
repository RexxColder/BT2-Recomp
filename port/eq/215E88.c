#include "common.h"

s32 BtlPad_Test48(s32 arg0, s32 arg1);
f32 func_00207E80(s32 arg0);
f32 func_00207E88(s32 arg0);
void BtlOpp_GetTargetPos(s32 arg0, s32 arg1);
f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
void sceVu0Normalize(s32 dst, s32 src);
void sceVu0InterVector(s32 dst, s32 a, s32 b, f32 t);
s32 func_00312650(s32 arg0, s32 arg1, s32 arg2);
s32 func_003126C8(s32 arg0, s32 arg1);
s32 BtlChar_GetPos(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

#define P(a) ((u8 *)BtlChar_GetPos(a))

void func_00215E88(s32 a0, u32 a1) {
    u8 sp[0x30];
    f32 *v = (f32 *)sp;
    f32 f20, f21, f22, f23, s, c;
    u8 *p, *s0;

    switch (a1) {
    case 0:
    case 1:
        if (BtlPad_Test48(a0, 8) != 0) {
            f23 = func_00207E80(a0);
            f22 = -func_00207E88(a0);
            if (func_00211310(a0, 0, 1) != 0) {
                BtlOpp_GetTargetPos(a0, (s32)(sp + 0x10));
                func_00312650((s32)(sp + 0x20), (s32)(sp + 0x10), BtlChar_GetPos(a0));
                f21 = -atan2f(*(f32 *)(sp + 0x20), *(f32 *)(sp + 0x28));
            } else {
                f21 = -*(f32 *)((u8 *)a0 + 0x150);
            }
            c = cosf(f21);
            s = sinf(f21);
            v[1] = 0.0f;
            v[2] = f23 * s + f22 * c;
            v[0] = f23 * c - f22 * s;
            if (a1 == 1) {
                v[1] = -sinf(*(f32 *)(P(a0) + 0xB0));
            }
        } else {
            func_003126C8((s32)sp, BtlChar_GetPos(a0) + 0x20);
            v[1] = 0.0f;
        }
        break;
    case 2:
        v[0] = sinf(*(f32 *)(P(a0) + 0xB4));
        v[1] = 0.0f;
        v[2] = cosf(*(f32 *)(P(a0) + 0xB4));
        break;
    case 3:
        f20 = cosf(*(f32 *)(P(a0) + 0xB0));
        v[0] = f20 * sinf(*(f32 *)(P(a0) + 0xB4));
        v[1] = -sinf(*(f32 *)(P(a0) + 0xB0));
        f20 = cosf(*(f32 *)(P(a0) + 0xB0));
        v[2] = f20 * cosf(*(f32 *)(P(a0) + 0xB4));
        break;
    case 4:
        v[0] = -sinf(*(f32 *)(P(a0) + 0xB4));
        v[1] = 0.0f;
        v[2] = -cosf(*(f32 *)(P(a0) + 0xB4));
        break;
    case 5:
        f20 = -cosf(*(f32 *)(P(a0) + 0xB0));
        v[0] = f20 * sinf(*(f32 *)(P(a0) + 0xB4));
        v[1] = sinf(*(f32 *)(P(a0) + 0xB0));
        f20 = -cosf(*(f32 *)(P(a0) + 0xB0));
        v[2] = f20 * cosf(*(f32 *)(P(a0) + 0xB4));
        break;
    case 6:
        v[0] = *(f32 *)(P(a0) + 0x20);
        v[1] = 0.0f;
        v[2] = *(f32 *)(P(a0) + 0x28);
        break;
    case 7:
        v[0] = *(f32 *)(P(a0) + 0x20);
        v[1] = *(f32 *)(P(a0) + 0x24);
        v[2] = *(f32 *)(P(a0) + 0x28);
        break;
    default:
        break;
    }
    sceVu0Normalize((s32)sp, (s32)sp);
    func_003126C8(BtlChar_GetPos(a0) + 0x20, (s32)sp);
    f20 = 1.0f;
    p = P(a0);
    s0 = p + 0x30;
    sceVu0InterVector((s32)s0, (s32)sp, BtlChar_GetPos(a0) + 0x30, f20);
    p = P(a0);
    *(f32 *)(p + 0x2C) = f20;
    p = P(a0);
    *(f32 *)(p + 0x3C) = f20;
}
