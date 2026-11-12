#include "common.h"

s32 func_0020A440(s32 arg0);
s32 func_0020B3D0(s32 arg0);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
void func_00312650(void *arg0, void *arg1, void *arg2);
f32 sceVu0InnerProduct(void *arg0, void *arg1);
void BtlCharApi_GetFrameMove(s32 arg0, s32 arg1);
void func_00312680(void *arg0, void *arg1, f32 farg0);
void func_00312638(void *arg0, void *arg1, void *arg2);
void func_00312490(void *arg0, void *arg1, void *arg2);
void sceVu0Normalize(void *arg0, void *arg1);
f32 Mathf_Acos(f32 farg0);
void Vec3_RotateAxis(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0);
s32 func_003126C8(s32 arg0, s32 arg1);
extern f32 D_00384F5C;

/* 0x001B07D0: turn the unit block a1 toward its target. Needs an object id from func_0020A440/func_0020B3D0
   (from block +0x44); the direction (block +0x30) is built from func_00208DE8, func_00312650 and
   BtlCharApi_GetFrameMove, then the angle from Mathf_Acos (clamped to block +0x4C) is applied with
   Vec3_RotateAxis. The angle rate is stored at block +0x148 (sign from block +0x5A). Returns the last
   func_003126C8 result, or the object-id code when there is no object. */
s32 func_001B07D0(s32 a1) {
    u8 *blk = (u8 *)a1;
    u8 *cz = blk + 0x80;
    u8 v16[16];
    u8 v17[16];
    u8 v18[16];
    u8 v19[16];
    u8 v20[16];
    u8 v21[16];
    u8 *s2 = blk + 0x30;
    s32 result;
    s32 objId;
    f32 ip1;
    f32 len;
    f32 speed;
    f32 f20;
    f32 f21;
    f32 ip2;
    f32 v13;
    f32 v14;
    f32 v15;

    result = func_0020A440(*(s32 *)(blk + 0x44));
    if (result != 0) {
        result = func_0020B3D0(*(s32 *)(blk + 0x44));
        objId = result;
    } else {
        objId = -1;
    }
    if (objId < 0) {
        return result;
    }

    func_00208DE8(objId, (s32)v19, 3);
    func_00312650((void *)v16, (void *)v19, (void *)blk);
    ip1 = sceVu0InnerProduct((void *)v16, (void *)v16);
    len = __builtin_sqrtf(__builtin_fabsf(ip1));
    speed = *(f32 *)(blk + 0x48);
    f20 = len / speed;
    if (15.0f < f20) {
        f20 = 15.0f;
    }

    BtlCharApi_GetFrameMove(objId, (s32)v21);
    func_00312680((void *)v17, (void *)v21, f20 * 0.5f);
    func_00312638((void *)v19, (void *)v19, (void *)v17);
    func_00312650((void *)v16, (void *)v19, (void *)blk);
    sceVu0Normalize((void *)v16, (void *)v16);
    sceVu0Normalize((void *)s2, (void *)s2);
    ip2 = sceVu0InnerProduct((void *)v16, (void *)s2);

    if (0.0f < ip2) {
        f32 t = ip2;
        if (1.0f < t) {
            t = 1.0f;
        }
        f20 = Mathf_Acos(t);
        f21 = *(f32 *)(blk + 0x4C);
        if (!(f21 < f20)) {
            f21 = f20;
        }
        func_00312490((void *)v18, (void *)s2, (void *)v16);
        sceVu0Normalize((void *)v18, (void *)v18);
        Vec3_RotateAxis(v20, s2, v18, f21);
        sceVu0Normalize((void *)v20, (void *)v20);
        if (D_00384F5C < f20) {
            f20 = D_00384F5C;
        }
        v13 = *(f32 *)(cz + 0xCC);
        v14 = f20 + f20;
        if (v13 == 0.0f) {
            *(f32 *)(cz + 0xCC) = v14;
            v13 = v14;
        }
        v15 = v13 - v14;
        if (blk[0x5A] == 0) {
            v15 = -v15;
        }
        *(f32 *)(cz + 0xC8) = v15;
    } else {
        func_003126C8((s32)v20, (s32)s2);
    }
    return func_003126C8((s32)s2, (s32)v20);
}
