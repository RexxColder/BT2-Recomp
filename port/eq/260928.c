#include "common.h"

void Quat_Mul(s32 arg0, s32 arg1, s32 arg2);
void Quat_Slerp(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
void Quat_ToMtx(s32 arg0, s32 arg1);
void Quat_FromEuler(s32 arg0, s32 arg1);
s32 func_00267518(s32 arg0);
s32 func_003126C8(s32 arg0, s32 arg1);

/* 0x00260928: builds a matrix from a quaternion chosen by the mode word at arg2+0xD4: 0x2E
 * slerps with the factor at arg3+0x30 (toward arg3+0x10), 0x2F with the factor at arg3+0x34
 * (toward arg3+0x20), 2 multiplies arg3 by the quaternion at arg2+0x90, 0x31 picks a euler
 * conversion (func_00267518 test on arg0) or the plain copy, and every other mode copies the
 * quaternion at arg2+0x90. The result goes through Quat_ToMtx into arg1. */
void func_00260928(s32 arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    s32 sp[4];
    u32 v1 = *(u32 *)(arg2 + 0xD4);

    if (v1 == 0x2E) {
        Quat_Slerp((s32)sp, (s32)(arg2 + 0x90), (s32)(arg3 + 0x10), *(f32 *)(arg3 + 0x30));
    } else if (v1 < 0x2F) {
        if (v1 == 2) {
            Quat_Mul((s32)sp, (s32)arg3, (s32)(arg2 + 0x90));
        } else {
            func_003126C8((s32)sp, (s32)(arg2 + 0x90));
        }
    } else if (v1 == 0x2F) {
        Quat_Slerp((s32)sp, (s32)(arg2 + 0x90), (s32)(arg3 + 0x20), *(f32 *)(arg3 + 0x34));
    } else if (v1 == 0x31) {
        if (func_00267518(arg0) != 0) {
            Quat_FromEuler((s32)sp, arg0 + 0xE40);
        } else {
            func_003126C8((s32)sp, (s32)(arg2 + 0x90));
        }
    } else {
        func_003126C8((s32)sp, (s32)(arg2 + 0x90));
    }
    Quat_ToMtx(arg1, (s32)sp);
}
