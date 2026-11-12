#include "common.h"

s32 func_00126560(void);
s32 func_001F42D8(s32 arg0);
s32 func_0020B3D0(s32 arg0);
s32 func_0020A440(s32 arg0);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
void func_00129BB8(s32 arg0, s32 arg1, f32 farg0);
void func_00129C28(s32 arg0, s32 arg1);
f32 func_00129CD8(s32 arg0, s32 arg1);
void BtlCharApi_GetFrameMove(s32 arg0, s32 arg1);
void Vec4_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec3_Cross(s32 arg0, s32 arg1, s32 arg2);
void Vec3_RotateAxis(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
f32 Mathf_Acos(f32 farg0);

/* Aim helper: writes into out (arg0) a unit direction from the point arg1 towards the target arg2,
 * rotated by an angle derived from the distance over the speed farg0; farg1 caps the rotation. */
void func_0012D5D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1) {
    u8 sp[0xD0];
    s32 s5 = arg0;
    s32 s4 = arg1;
    s32 s3 = arg2;
    s32 s0 = arg3;
    s32 s1;
    f32 f20 = farg0;
    f32 f21;
    f32 f22 = 0.5f;
    f32 f23 = farg1;
    f32 f1;
    f32 dot;

    if (func_00126560() != 0) {
        s1 = func_001F42D8(s0);
    } else {
        s1 = func_0020B3D0(s0);
    }
    Vec3_Normalize(s3, s3);

    if (func_0020A440(s0) == 0) {
        func_00129C28(s5, s3);
        return;
    }

    func_00208DE8(s1, (s32)(sp + 0), 17);
    func_00129B58((s32)(sp + 0x50), (s32)(sp + 0), s4);
    dot = func_00129CD8((s32)(sp + 0x50), (s32)(sp + 0x50));
    f21 = __builtin_sqrtf(dot) / f20;
    f20 = f21;
    if (15.0f < f21) {
        f20 = 15.0f;
    }

    BtlCharApi_GetFrameMove(s1, (s32)(sp + 0x10));
    func_00129BB8((s32)(sp + 0x20), (s32)(sp + 0x10), f20 * f22);
    Vec4_Add((u8 *)(sp + 0), (u8 *)(sp + 0), (u8 *)(sp + 0x20));
    func_00129B58((s32)(sp + 0x50), (s32)(sp + 0), s4);
    Vec3_Normalize((s32)(sp + 0x50), (s32)(sp + 0x50));
    Vec3_Normalize((s32)(sp + 0x40), s3);
    dot = func_00129CD8((s32)(sp + 0x50), (s32)(sp + 0x40));

    if (0.0f < dot) {
        if (1.0f < dot) {
            dot = 1.0f;
        }
        f1 = Mathf_Acos(dot);
        f20 = f23;
        if (2.0f < f21) {
            f1 = f1 / (f21 * f22);
        }
        if (!(f20 < f1)) {
            f20 = f1;
        }
        Vec3_Cross((s32)(sp + 0x60), (s32)(sp + 0x40), (s32)(sp + 0x50));
        Vec3_Normalize((s32)(sp + 0x60), (s32)(sp + 0x60));
        Vec3_RotateAxis((s32)(sp + 0x30), (s32)(sp + 0x40), (s32)(sp + 0x60), f20);
        Vec3_Normalize((s32)(sp + 0x30), (s32)(sp + 0x30));
    } else {
        func_00129C28((s32)(sp + 0x30), (s32)(sp + 0x40));
    }
    func_00129C28(s5, (s32)(sp + 0x30));
}
