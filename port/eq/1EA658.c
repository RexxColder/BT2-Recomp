#include "common.h"

void Vec3_Sub(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
void Vec3_Cross(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_RotateAxis(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0);
f32 func_00129CD8(u8 *arg0, u8 *arg1);
s32 func_00129C28(u8 *arg0, u8 *arg1);
f32 Mathf_Acos(f32 farg0);
f32 sqrtf(f32 arg0);
f32 fabsf(f32 arg0);

void func_001EA658(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, f32 farg0, f32 farg1) {
    u8 sp[0x50];
    u8 *tmp1;
    u8 *tmp2;
    u8 *tmp3;
    u8 *tmp4;
    f32 dot;
    f32 len;
    f32 angle;
    f32 f20;

    tmp1 = sp + 0x30;
    tmp2 = sp + 0x20;
    tmp3 = sp + 0x10;
    tmp4 = sp + 0x40;

    memcpy(sp, arg3, 16);
    Vec3_Sub(tmp1, sp, arg1);
    dot = func_00129CD8(tmp1, tmp1);
    len = sqrtf(fabsf(dot));
    f20 = len / farg0;
    Vec3_Normalize(tmp1, tmp1);
    Vec3_Normalize(tmp2, arg2);

    dot = func_00129CD8(tmp1, tmp2);
    if (dot < 0.0f) {
        func_00129C28(tmp3, tmp2);
    } else {
        if (1.0f < dot) {
            dot = 1.0f;
        }
        angle = Mathf_Acos(dot);
        if (2.0f < f20) {
            angle = angle / (f20 * 0.5f);
        }
        f20 = farg1;
        if (!(f20 < angle)) {
            f20 = angle;
        }
        Vec3_Cross(tmp4, tmp2, tmp1);
        Vec3_Normalize(tmp4, tmp4);
        Vec3_RotateAxis(tmp3, tmp2, tmp4, f20);
        Vec3_Normalize(tmp3, tmp3);
    }
    func_00129C28(arg0, tmp3);
}
