#include "common.h"

extern s32 rand(void);
f32 BtlCharApi_GetHeight(s32 arg0);
f32 func_00208DC0(s32 arg0);
void func_00208798(s32 arg0, f32 *out);
s32 func_0013B350(f32 *out);
s32 func_0013FDF8(u8 **head, u8 **tail, u8 *pos, u32 b0, u32 b1, u32 b2, u32 b3, u32 b4,
                  f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  f32 st0, f32 st1, f32 st2, f32 st3, f32 st4, f32 st5, f32 st6, f32 st7, f32 st8, f32 st9);
s32 EftWaterDrop_Spawn(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                       f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                       f32 farg8, f32 farg9, f32 farg10, s32 arg8);
void EftWaterRing_Spawn(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                        s32 arg8, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6);

extern u8 *gEftDust;
extern u8 *D_003876A0;
extern f32 D_00384328, D_0038432C, D_00384330, D_00384334, D_00384338, D_0038433C, D_00384340;
extern f32 D_00384344, D_00384348, D_0038434C, D_00384350, D_00384354, D_00384358;
extern f32 D_0038435C, D_00384360, D_00384364, D_00384368, D_0038436C;

s32 func_0013B6A0(s32 objId, s32 count, f32 delay) {
    f32 pos[4];
    f32 level;
    f32 surfY;
    f32 height;
    f32 step;
    f32 yaw;
    f32 radius, speed, gravity, size, sizeVel, life, pitch, yawVel, dist;
    f32 unit;
    f32 rdiv;
    s32 i;

    level = 0.0f;
    if (gEftDust == NULL) {
        return 0;
    }
    if (*(u64 *)(D_003876A0 + 0x4D8) & 2) {
        return 0;
    }
    func_0013B350(&level);
    if (func_00208DC0(objId) < level) {
        return 0;
    }
    func_00208798(objId, pos);
    if (func_0013B350(&surfY)) {
        pos[1] = surfY + -1.0f;
    }
    unit = D_00384328;
    height = BtlCharApi_GetHeight(objId) * unit * 7.0f;
    rdiv = D_0038432C;
    step = 360.0f / (f32)count;
    yaw = ((f32)rand() / rdiv) * 360.0f;

    for (i = 0; i < count; i++) {
        f32 ang;
        size = ((f32)rand() / rdiv) * 1.5f + 1.0f;
        gravity = D_00384330;
        sizeVel = ((f32)rand() / rdiv) * D_00384334 + D_00384338;
        life = ((f32)rand() / rdiv) * 0.25f + D_0038433C;
        pitch = ((f32)rand() / rdiv) * 10.0f + 50.0f;
        yawVel = ((f32)rand() / rdiv) * 5.0f + 14.0f;
        radius = 10.0f;
        speed = 25.0f;
        radius = BtlCharApi_GetHeight(objId) * unit * radius;
        speed = BtlCharApi_GetHeight(objId) * unit * speed;
        sizeVel = sizeVel * (BtlCharApi_GetHeight(objId) * unit);
        gravity = BtlCharApi_GetHeight(objId) * unit * gravity;
        ang = ((f32)rand() / rdiv) * 360.0f;
        func_0013FDF8((u8 **)(gEftDust + 0x64), (u8 **)(gEftDust + 0x68), (u8 *)pos, 0x8C, 0x8C, 0x8C, 3, 0,
                      radius, height, yaw + step * (f32)i, yawVel, -7.0f, pitch, ang, D_00384340,
                      0.75f, speed, size, sizeVel, -5.0f, gravity, 1.0f, 1.5f, life, delay);
    }

    dist = D_00384344;
    size = BtlCharApi_GetHeight(objId) * dist * 0.0f;
    EftWaterRing_Spawn(gEftDust + 0x4C, gEftDust + 0x50, (s32)pos, 0xFF, 0xFF, 0xFF, 2, 0, 0xD,
                       0.0f, size, BtlCharApi_GetHeight(objId) * dist * 8.0f, -24.0f, 112.0f, D_00384348, delay);

    rdiv = D_0038434C;
    step = 180.0f;
    yaw = ((f32)rand() / rdiv) * 360.0f;
    for (i = 0; i < 2; i++) {
        f32 ang;
        speed = ((f32)rand() / rdiv) * 10.0f + 35.0f;
        gravity = D_00384350;
        size = ((f32)rand() / rdiv) * 2.0f + 1.0f;
        sizeVel = ((f32)rand() / rdiv) * 2.5f + 4.5f;
        life = ((f32)rand() / rdiv) * D_00384354 + D_00384358;
        pitch = ((f32)rand() / rdiv) * 10.0f + 30.0f;
        BtlCharApi_GetHeight(objId);
        speed = speed * (BtlCharApi_GetHeight(objId) * dist);
        sizeVel = sizeVel * (BtlCharApi_GetHeight(objId) * dist);
        gravity = BtlCharApi_GetHeight(objId) * dist * gravity;
        ang = ((f32)rand() / rdiv) * 360.0f;
        EftWaterDrop_Spawn(gEftDust + 0x54, gEftDust + 0x58, (u8 *)pos, 0x80, 0x80, 0x80, 1, 0,
                           yaw + step * (f32)i, pitch, speed, ang, 0.0f, size, sizeVel, -5.0f,
                           gravity, life, delay, 9);
    }

    rdiv = D_0038435C;
    step = 180.0f;
    unit = D_00384360;
    yaw = ((f32)rand() / rdiv) * 360.0f;
    for (i = 0; i < 2; i++) {
        f32 ang;
        gravity = D_00384364;
        speed = ((f32)rand() / rdiv) * 10.0f + 30.0f;
        size = ((f32)rand() / rdiv) * 2.0f + 2.0f;
        sizeVel = ((f32)rand() / rdiv) * 3.0f + 5.0f;
        life = ((f32)rand() / rdiv) * D_00384368 + D_0038436C;
        pitch = ((f32)rand() / rdiv) * 10.0f + 40.0f;
        BtlCharApi_GetHeight(objId);
        speed = speed * (BtlCharApi_GetHeight(objId) * unit);
        sizeVel = sizeVel * (BtlCharApi_GetHeight(objId) * unit);
        gravity = BtlCharApi_GetHeight(objId) * unit * gravity;
        ang = ((f32)rand() / rdiv) * 360.0f;
        EftWaterDrop_Spawn(gEftDust + 0x54, gEftDust + 0x58, (u8 *)pos, 0x8C, 0x8C, 0x8C, 4, 0,
                           yaw + step * (f32)i, pitch, speed, ang, 0.0f, size, sizeVel, -5.0f,
                           gravity, life, delay, 0x105);
    }
    return 1;
}
