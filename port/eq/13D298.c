#include "common.h"

extern s32 rand(void);
extern u8 *EftWater_AllocSplash(void);
extern void func_003126C8(void *dst, void *src);
extern s32 EftWaterSpray_Spawn(u8 **head, u8 **tail, u8 *vec, u8 b0, u8 b1, u8 b2, u8 b3, u8 b4,
                               f32 posScale, f32 yAdd, f32 angleA, f32 angleB, f32 f60, f32 startAlpha,
                               f32 endAlpha, f32 speed, f32 s48, f32 s4C, f32 s50Div, f32 s64Mul, f32 s68,
                               f32 s6C, f32 life, f32 s78Mul, s32 flags);
extern s32 EftWaterDrop_Spawn(u8 *arg0, u8 *arg1, u8 *pos, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                              f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6,
                              f32 farg7, f32 s0, f32 s8, f32 s10, s32 flags);
extern void EftWaterRing_Spawn(u8 *arg0, u8 *arg1, u8 *pos, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                               s32 arg8, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5,
                               f32 farg6);
extern u8 *gEftDust;
extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_00384404, D_00384408, D_0038440C, D_00384410, D_00384414, D_00384418, D_0038441C, D_00384420;
extern f32 D_00384424, D_00384428, D_0038442C, D_00384430, D_00384434, D_00384438, D_0038443C, D_00384440;
extern f32 D_00384444, D_00384448, D_0038444C, D_00384450, D_00384454, D_00384458, D_0038445C, D_00384460;
extern f32 D_00384464;

/* Creates a splash record at pos: sprayA + sprayB water streaks, dropA + dropB billboards and four rings, all
   scaled by `scale`. Streak/billboard directions are spread evenly around a random start angle. */
void EftWater_AddSplash(u8 **head, u8 **tail, u8 *pos, s32 sprayA, s32 sprayB, s32 dropA, s32 dropB, f32 scale) {
    u8 *splash;
    u8 *prev;
    f32 height, rdiv, yaw, step, spread;
    s32 i;

    splash = EftWater_AllocSplash();
    if (splash == 0) {
        return;
    }
    if (*head == 0) {
        *head = splash;
        *(u8 **)(splash + 0x2C) = 0;
        *(u8 **)(splash + 0x30) = 0;
    } else {
        *(u8 **)(splash + 0x30) = 0;
        *(u8 **)(splash + 0x2C) = *tail;
    }
    prev = *tail;
    if (prev != 0) {
        *(u8 **)(prev + 0x30) = splash;
    }
    *tail = splash;
    func_003126C8(splash, pos);
    *(s32 *)(splash + 0x10) = 2;
    height = scale * 7.0f;
    rdiv = D_00384404;
    *(s32 *)(gEftDust + 0x1C) = *(s32 *)(gEftDust + 0x1C) + 1;
    yaw = ((f32)rand() / rdiv) * 360.0f;
    step = 360.0f / (f32)sprayA;
    spread = ((f32)rand() / rdiv) * D_00384408;
    for (i = 0; i < sprayA; i++) {
        f32 sizeVel, life, pitch, gravity;

        sizeVel = ((f32)rand() / rdiv) * D_0038440C + D_00384410;
        gravity = scale * D_00384414;
        life = ((f32)rand() / rdiv) * D_00384418 + 0.5f;
        sizeVel = sizeVel * scale;
        pitch = ((f32)rand() / rdiv) * 12.5f + 62.5f;
        EftWaterSpray_Spawn((u8 **)(splash + 0x1C), (u8 **)(splash + 0x20), D_002C3630, 0x8C, 0x8C, 0x8C, 3, 0,
                            0.0f, height, yaw + step * (f32)i, pitch, 0.0f, D_00384420, D_00384424,
                            scale * 40.0f, 0.0f, sizeVel, -5.0f, gravity, spread + 1.0f, D_0038441C, life, 0.0f,
                            0x102);
    }

    rdiv = D_00384428;
    yaw = ((f32)rand() / rdiv) * 360.0f;
    step = 360.0f / (f32)sprayB;
    for (i = 0; i < sprayB; i++) {
        f32 sizeVel, life, pitch, gravity;

        sizeVel = ((f32)rand() / rdiv) * 4.0f + 6.0f;
        gravity = scale * D_0038442C;
        life = ((f32)rand() / rdiv) * D_00384430 + D_00384434;
        sizeVel = sizeVel * scale;
        pitch = ((f32)rand() / rdiv) * 12.5f + 72.5f;
        EftWaterSpray_Spawn((u8 **)(splash + 0x1C), (u8 **)(splash + 0x20), D_002C3630, 0x8C, 0x8C, 0x8C, 3, 0,
                            2.0f, height, yaw + step * (f32)i, pitch, 0.0f, D_00384444, 0.75f, scale * 40.0f,
                            0.0f, sizeVel, -5.0f, gravity, spread + D_00384438, D_0038443C, life, D_00384440,
                            0x101);
    }

    rdiv = D_00384448;
    yaw = ((f32)rand() / rdiv) * 360.0f;
    step = 360.0f / (f32)dropA;
    for (i = 0; i < dropA; i++) {
        f32 speed, sizeVel, life, pitch, ang;

        speed = ((f32)rand() / rdiv) * 40.0f + 110.0f;
        speed = speed * scale;
        sizeVel = ((f32)rand() / rdiv) * 4.0f + 8.0f;
        sizeVel = sizeVel * scale;
        life = ((f32)rand() / rdiv) * 0.5f + D_0038444C;
        pitch = ((f32)rand() / rdiv) * 10.0f + 72.0f;
        ang = ((f32)rand() / rdiv) * 360.0f;
        EftWaterDrop_Spawn(splash + 0x14, splash + 0x18, D_002C3630, 0x80, 0x80, 0x80, 4, 0, yaw + step * (f32)i,
                           pitch, speed, ang, 0.0f, scale + scale, sizeVel, -5.0f, scale * 11.0f, life, 0.0f,
                           0x106);
    }

    rdiv = D_00384450;
    yaw = ((f32)rand() / rdiv) * 360.0f;
    step = 360.0f / (f32)dropB;
    for (i = 0; i < dropB; i++) {
        f32 sizeVel, life, pitch, ang;

        sizeVel = ((f32)rand() / rdiv) * 4.0f + 8.0f;
        life = ((f32)rand() / rdiv) * D_00384454 + D_00384458;
        sizeVel = sizeVel * scale;
        pitch = ((f32)rand() / rdiv) * 10.0f + 75.0f;
        ang = ((f32)rand() / rdiv) * 360.0f;
        EftWaterDrop_Spawn(splash + 0x14, splash + 0x18, D_002C3630, 0x80, 0x80, 0x80, 1, 0, yaw + step * (f32)i,
                           pitch, scale * 55.0f, ang, 0.0f, scale + scale, sizeVel, -5.0f, scale * 3.5f, life,
                           0.0f, 0xA);
    }

    EftWaterRing_Spawn(splash + 0x24, splash + 0x28, pos, 0x80, 0x80, 0x80, 0, 0, 0xE, 0.0f, scale * 5.0f,
                       scale * 12.0f, -4.0f, 96.0f, D_0038445C, 0.0f);
    EftWaterRing_Spawn(splash + 0x24, splash + 0x28, pos, 0xFF, 0xFF, 0xFF, 2, 0, 0xE, 0.0f, scale * 8.0f,
                       scale * 6.0f, -24.0f, 112.0f, 1.5f, 0.0f);
    EftWaterRing_Spawn(splash + 0x24, splash + 0x28, pos, 0xFF, 0xFF, 0xFF, 2, 0, 0xD, 0.0f, scale * 10.0f,
                       scale * 4.0f, -24.0f, 96.0f, D_00384460, D_00384464);
    EftWaterRing_Spawn(splash + 0x24, splash + 0x28, pos, 0xFF, 0xFF, 0xFF, 2, 0, 0xD, 0.0f, scale * 10.0f,
                       scale * 4.0f, -24.0f, 88.0f, D_00384460, 0.5f);
}
