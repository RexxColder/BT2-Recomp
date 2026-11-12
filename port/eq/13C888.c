#include "common.h"

extern s32 rand(void);
extern f32 atan2f(f32 y, f32 x);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern void func_00208798(s32 objId, void *out);
extern s32 func_0013B350(f32 *out);
extern void func_00208BE0(s32 objId, void *out);
extern void func_00208AA0(s32 objId, void *out);
extern f32 func_001407A0(void *v);
extern s32 EftWaterSpray_Spawn(u8 **head, u8 **tail, f32 *vec, u8 b0, u8 b1, u8 b2, u8 b3, u8 b4,
                               f32 posScale, f32 yAdd, f32 angleA, f32 angleB, f32 f60, f32 startAlpha,
                               f32 endAlpha, f32 speed, f32 s48, f32 s4C, f32 s50Div, f32 s64Mul, f32 s68,
                               f32 s6C, f32 life, f32 s78Mul, s32 flags);
extern s32 EftWaterDrop_Spawn(u8 *arg0, u8 *arg1, u8 *pos, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                              f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6,
                              f32 farg7, f32 s0, f32 s8, f32 s10, s32 flags);
extern void EftWaterRing_Spawn(u8 *arg0, u8 *arg1, u8 *pos, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                               s32 arg8, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5,
                               f32 farg6);
extern u8 *D_003876A0;
extern u8 *gEftDust;
extern f32 D_00384378, D_0038437C, D_00384380, D_00384384, D_00384388;
extern f32 D_0038438C, D_00384390, D_00384394, D_00384398, D_0038439C, D_003843A0, D_003843A4;
extern f32 D_003843A8, D_003843AC, D_003843B0, D_003843B4, D_003843B8, D_003843BC, D_003843C0, D_003843C4;
extern f32 D_003843C8, D_003843CC, D_003843D0, D_003843D4, D_003843D8, D_003843DC, D_003843E0, D_003843E4;
extern f32 D_003843E8, D_003843EC, D_003843F0, D_003843F4, D_003843F8, D_003843FC, D_00384400;

/* Wake behind each of the two fighters whose wake record is on (records: objId, frame, on at +0/+4/+8, 0xC apart):
   spray streaks every frame, billboards on even frames, a ring every third frame. Skipped while paused. */
void EftWater_UpdateWakes(void) {
    u8 sp[0x90];
    u8 *wake;
    s32 n;
    f32 k = D_00384378;

    if (*(u64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }
    wake = *(u8 **)gEftDust;
    for (n = 1; n >= 0; n--, wake += 0xC) {
        s32 objId, frame;
        f32 scale, yaw, h;

        if (wake[8] == 0) {
            continue;
        }
        objId = *(s32 *)wake;
        func_00208798(objId, sp + 0x50);
        if (func_0013B350(sp + 0x80)) {
            *(f32 *)(sp + 0x54) = *(f32 *)(sp + 0x80) + -1.0f;
        }
        func_00208BE0(objId, sp + 0x60);
        func_00208AA0(objId, sp + 0x70);
        *(s32 *)(sp + 0x74) = 0;
        scale = __builtin_sqrtf(__builtin_fabsf(func_001407A0(sp + 0x70))) * D_0038437C;
        if (scale < D_00384380) {
            scale = scale * D_00384384;
        }
        yaw = (atan2f(*(f32 *)(sp + 0x60), *(f32 *)(sp + 0x68)) * 180.0f) / D_00384388;
        *(f32 *)(sp + 0x84) = yaw;
        h = BtlCharApi_GetHeight(*(s32 *)wake);
        *(f32 *)(sp + 0x88) = ((h * k) * scale) * 7.0f;

        if ((*(s32 *)(wake + 4) & 1) == 0) {
            s32 i;
            f32 divisor = D_0038438C;
            f32 kk = D_00384390;

            for (i = 0; i < 2; i++) {
                f32 size, sizeVel, life, pitch, speed, gravity, ang, yawc;

                size = ((f32)rand() / divisor) * 3.0f + 1.0f;
                sizeVel = ((f32)rand() / divisor) * 3.0f + 5.0f;
                life = ((f32)rand() / divisor) * D_00384398 + D_0038439C;
                pitch = ((f32)rand() / divisor) * 10.0f + 50.0f;
                speed = ((BtlCharApi_GetHeight(objId) * kk) * scale) * 40.0f;
                sizeVel = sizeVel * ((BtlCharApi_GetHeight(objId) * kk) * scale);
                gravity = ((BtlCharApi_GetHeight(objId) * kk) * scale) * D_00384394;
                ang = ((f32)rand() / divisor) * 360.0f;
                yawc = (*(f32 *)(sp + 0x84) - 60.0f) + (f32)i * 120.0f;
                EftWaterSpray_Spawn((u8 **)(gEftDust + 0x5C), (u8 **)(gEftDust + 0x60), (f32 *)(sp + 0x50),
                                    0x8C, 0x8C, 0x8C, 3, 0, 0.0f, *(f32 *)(sp + 0x88), yawc, pitch, ang,
                                    D_003843A0, D_003843A4, speed, size, sizeVel, -5.0f, gravity, 1.0f, 1.5f,
                                    life, 0.0f, 0x102);
            }
        } else {
            f32 size, sizeVel, life, pitch, speed, gravity, ang, yawc;

            size = ((f32)rand() / D_003843A8) * 3.0f + 1.0f;
            sizeVel = ((f32)rand() / D_003843B0) * 3.0f + 5.0f;
            life = ((f32)rand() / D_003843B4) * D_003843B8 + D_003843BC;
            pitch = ((f32)rand() / D_003843C0) * 10.0f + 50.0f;
            speed = ((BtlCharApi_GetHeight(objId) * k) * scale) * 40.0f;
            sizeVel = sizeVel * ((BtlCharApi_GetHeight(objId) * k) * scale);
            gravity = ((BtlCharApi_GetHeight(objId) * k) * scale) * D_003843AC;
            yawc = (*(f32 *)(sp + 0x84) - 60.0f) + (f32)(rand() % 2) * 120.0f;
            ang = ((f32)rand() / D_003843C4) * 360.0f;
            EftWaterSpray_Spawn((u8 **)(gEftDust + 0x5C), (u8 **)(gEftDust + 0x60), (f32 *)(sp + 0x50), 0x8C,
                                0x8C, 0x8C, 3, 0, 0.0f, *(f32 *)(sp + 0x88), yawc, pitch, ang, D_003843C8, 0.5f,
                                speed, size, sizeVel, -5.0f, gravity, 1.0f, 1.5f, life, 0.0f, 0x102);
        }

        frame = *(s32 *)(wake + 4);
        if ((frame & 1) == 0) {
            f32 size, sizeVel, life, pitch, speed, gravity, ang, yawc;

            sizeVel = ((f32)rand() / D_003843CC) * 3.5f + 6.5f;
            life = ((f32)rand() / D_003843D0) * D_003843D4 + D_003843D8;
            pitch = ((f32)rand() / D_003843DC) * 10.0f + 60.0f;
            speed = ((BtlCharApi_GetHeight(objId) * k) * scale) * 90.0f;
            size = ((BtlCharApi_GetHeight(objId) * k) * scale) * 2.0f;
            sizeVel = sizeVel * ((BtlCharApi_GetHeight(objId) * k) * scale);
            gravity = ((BtlCharApi_GetHeight(objId) * k) * scale) * 9.0f;
            yawc = (*(f32 *)(sp + 0x84) - 30.0f) + (f32)(rand() % 2) * 60.0f;
            ang = ((f32)rand() / D_003843E0) * 360.0f;
            EftWaterDrop_Spawn(gEftDust + 0x54, gEftDust + 0x58, sp + 0x50, 0x80, 0x80, 0x80, 4, 0, yawc, pitch,
                               speed, ang, 0.0f, size, sizeVel, -5.0f, gravity, life, 0.0f, 0x106);

            sizeVel = ((f32)rand() / D_003843E4) * 3.5f + 6.5f;
            life = ((f32)rand() / D_003843E8) * D_003843EC + D_003843F0;
            pitch = ((f32)rand() / D_003843F4) * 10.0f + 70.0f;
            speed = ((BtlCharApi_GetHeight(objId) * k) * scale) * 55.0f;
            size = ((BtlCharApi_GetHeight(objId) * k) * scale) * 2.0f;
            sizeVel = sizeVel * ((BtlCharApi_GetHeight(objId) * k) * scale);
            gravity = ((BtlCharApi_GetHeight(objId) * k) * scale) * 3.5f;
            ang = ((f32)rand() / D_003843F8) * 360.0f;
            EftWaterDrop_Spawn(gEftDust + 0x54, gEftDust + 0x58, sp + 0x50, 0x80, 0x80, 0x80, 1, 0,
                               *(f32 *)(sp + 0x84), pitch, speed, ang, 0.0f, size, sizeVel, -5.0f, gravity, life,
                               0.0f, 0xA);
            frame = *(s32 *)(wake + 4);
        }
        if ((u32)frame % 3 == 0) {
            f32 size = ((BtlCharApi_GetHeight(objId) * k) * scale) * 0.0f;

            EftWaterRing_Spawn(gEftDust + 0x4C, gEftDust + 0x50, sp + 0x50, 0xFF, 0xFF, 0xFF, 2, 0, 0xD, 0.0f,
                               size, ((BtlCharApi_GetHeight(objId) * k) * scale) * 10.0f, -24.0f, 112.0f,
                               D_003843FC, D_00384400);
            frame = *(s32 *)(wake + 4);
        }
        *(s32 *)(wake + 4) = frame + 1;
    }
}
