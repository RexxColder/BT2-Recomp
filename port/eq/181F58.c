#include "common.h"

s32 func_0020B3D0();
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void Vec4_Sub(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec4_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec4_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec3_Cross(void *arg0, void *arg1, void *arg2);
void Vec3_RotateAxis(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0);
f32 Vec3_Dot(f32 *arg0, f32 *arg1);
f32 Mathf_Acos(f32 farg0);
void BtlCharApi_GetFrameMove(s32 arg0, s32 arg1);
s32 func_00129C28(s32 arg0, s32 arg1);

/* 0x00181F58: steers the aim vector at self+0x30 toward a target id's position
 * (self+0x10), limited by self+0x44 (speed) and self+0x4C (max angle). flag 0 always
 * rotates; flag 1 rotates only when the dot product is positive; other flags never do. */
void func_00181F58(u8 *self, s32 arg1, u8 *arg2, u8 flag)
{
    f32 pos[4];
    f32 frame[4];
    f32 dir[4];
    f32 axis[4];
    f32 scaled[4];
    s32 id;
    f32 angle;
    f32 dotv;
    f32 cv;

    id = func_0020B3D0(arg1);
    if (id < 0) {
        return;
    }

    func_00208DE8(id, (u8 *)pos, 17);
    if (arg2 != NULL) {
        Vec3_Add((s32)pos, (s32)pos, (s32)arg2);
    }

    Vec4_Sub((u8 *)dir, (u8 *)pos, self + 0x10);
    angle = __builtin_sqrtf(Vec3_Dot(dir, dir)) / *(f32 *)(self + 0x44);
    if (angle > 15.0f) {
        angle = 15.0f;
    }

    BtlCharApi_GetFrameMove(id, (s32)frame);
    Vec4_Scale((u8 *)frame, (u8 *)frame, angle * 0.5f);
    Vec4_Add((u8 *)pos, (u8 *)pos, (u8 *)frame);
    Vec4_Sub((u8 *)dir, (u8 *)pos, self + 0x10);
    Vec3_Normalize((s32)dir, (s32)dir);
    Vec3_Normalize((s32)(self + 0x30), (s32)(self + 0x30));
    dotv = Vec3_Dot(dir, (f32 *)(self + 0x30));

    if (flag == 0 || (flag == 1 && dotv > 0.0f)) {
        cv = dotv;
        if (cv < 0.0f) {
            cv = 0.0f;
        } else if (1.0f < cv) {
            cv = 1.0f;
        }
        angle = Mathf_Acos(cv);
        if (*(f32 *)(self + 0x4C) < angle) {
            angle = *(f32 *)(self + 0x4C);
        }

        Vec3_Cross(axis, self + 0x30, dir);
        Vec3_Normalize((s32)axis, (s32)axis);
        Vec3_RotateAxis(self + 0x30, self + 0x30, (u8 *)axis, angle);
        Vec3_Normalize((s32)(self + 0x30), (s32)(self + 0x30));
    }

    func_00129C28((s32)(self + 0x20), (s32)(self + 0x10));
    Vec4_Scale((u8 *)scaled, self + 0x30, *(f32 *)(self + 0x44));
    Vec4_Add(self + 0x10, self + 0x10, (u8 *)scaled);
}
