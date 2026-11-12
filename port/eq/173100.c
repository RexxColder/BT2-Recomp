#include "common.h"

s32 func_0020B3D0(s32 arg0);
void func_00208DE8(s32 a0, s32 a1, s32 a2);
void BtlCharApi_GetFrameMove(s32 arg0, s32 arg1);
void Vec3_Normalize(void *arg0, void *arg1);
void Vec3_Cross(void *arg0, void *arg1, void *arg2);
void Vec3_RotateAxis(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0);
void func_00129C28(void *arg0, void *arg1);
void func_00129B28(void *arg0, void *arg1, void *arg2);
void func_00129B58(void *arg0, void *arg1, void *arg2);
void func_00129BB8(f32 farg0, void *arg0, void *arg1);
f32 func_00129CD8(void *a, void *b);
f32 Mathf_Acos(f32 farg0);

/* 0x00173100: aim the vector at a0 (output) from the position a1 along the direction a2, for object id
   func_0020B3D0(a3). The offset to the target (func_00208DE8 entry 17 minus a1) is scaled by the speed
   (f12, clamped to 15), the target is advanced by the object's frame move, and the direction is turned
   toward it by Mathf_Acos of their dot product (clamped to f13). Returns the speed; 0 when there is no object
   or no turn. */
f32 func_00173100(s32 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13) {
    u8 *out = (u8 *)a0;
    u8 *pos = (u8 *)a1;
    u8 *dir = (u8 *)a2;
    u8 v17[16];
    u8 v18[16];
    u8 v19[16];
    u8 v20[16];
    u8 v21[16];
    u8 v22[16];
    u8 v23[16];
    s32 obj;
    f32 scale;
    f32 cap;
    f32 speed;
    f32 f21;
    f32 dot;
    f32 ang;

    obj = func_0020B3D0(a3);
    scale = f12;
    cap = f13;

    Vec3_Normalize((void *)dir, (void *)dir);
    if (obj < 0) {
        func_00129C28((void *)out, (void *)dir);
        return 0.0f;
    }

    func_00208DE8(obj, (s32)v17, 17);
    func_00129B58((void *)v22, (void *)v17, (void *)pos);
    speed = __builtin_sqrtf(__builtin_fabsf(func_00129CD8((void *)v22, (void *)v22)));
    f21 = speed / scale;
    scale = f21;
    if (15.0f < f21) {
        scale = 15.0f;
    }

    BtlCharApi_GetFrameMove(obj, (s32)v18);
    func_00129BB8(scale * 0.5f, (void *)v19, (void *)v18);
    func_00129B28((void *)v17, (void *)v17, (void *)v19);
    func_00129B58((void *)v22, (void *)v17, (void *)pos);
    Vec3_Normalize((void *)v22, (void *)v22);
    Vec3_Normalize((void *)v21, (void *)dir);

    dot = func_00129CD8((void *)v22, (void *)v21);
    if (0.0f < dot) {
        if (1.0f < dot) {
            dot = 1.0f;
        }
        ang = Mathf_Acos(dot);
        if (2.0f < f21) {
            ang = ang / (f21 * 0.5f);
        }
        scale = cap;
        if (!(scale < ang)) {
            scale = ang;
        }
        Vec3_Cross((void *)v23, (void *)v21, (void *)v22);
        Vec3_Normalize((void *)v23, (void *)v23);
        Vec3_RotateAxis(v20, (u8 *)v21, (u8 *)v23, scale);
        Vec3_Normalize((void *)v20, (void *)v20);
        func_00129C28((void *)out, (void *)v20);
        return speed;
    }

    func_00129C28((void *)v20, (void *)v21);
    func_00129C28((void *)out, (void *)v20);
    return 0.0f;
}
