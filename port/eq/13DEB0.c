#include "common.h"

s32 EftWaterTrail_Alloc(void);
void func_003126C8(void *arg0, void *arg1);
s32 func_0013B350(f32 *out);
void func_00312650(void *arg0, void *arg1, void *arg2);
void sceVu0Normalize(void *arg0, void *arg1);
f32 func_001407A0(void *arg0);
extern f32 atan2f(f32 y, f32 x);
extern f32 sqrtf(f32 x);
extern s32 rand(void);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 EftWaterSpray_Spawn(u8 **head, u8 **tail, f32 *vec, u8 b0, u8 b1, u8 b2, u8 b3, u8 b4,
                        f32 posScale, f32 yAdd, f32 angleA, f32 angleB, f32 f60, f32 startAlpha, f32 endAlpha,
                        f32 speed,
                        f32 s48, f32 s4C, f32 s50Div, f32 s64Mul, f32 s68, f32 s6C, f32 life, f32 s78Mul,
                        s32 flags);
s32 EftWaterDrop_Spawn(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                       f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                       f32 farg8, f32 farg9, f32 farg10, s32 arg8);
void EftWaterRing_Spawn(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                        s32 arg8, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6);
extern u8 *gEftDust;

#define RANDF() ((f32)rand() / 2147483520.0f)
#define SCALE(obj, sc) (BtlCharApi_GetHeight(obj) * 0.05f * (sc))

void EftWaterTrail_Spawn(u8 **head, u8 **tail, s32 objId, u8 *hit) {
    u8 *trail;
    f32 pos[4];
    f32 dir[4];
    f32 delta[4];
    f32 y[4];
    f32 yaw, scale, height, len;
    f32 size, sizeVel, life, pitch, speed, gravity, dropYaw;
    s32 i;

    trail = (u8 *)EftWaterTrail_Alloc();
    if (trail == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = trail;
        *(u8 **)(trail + 0x1C) = NULL;
        *(u8 **)(trail + 0x20) = NULL;
    } else {
        *(u8 **)(trail + 0x20) = NULL;
        *(u8 **)(trail + 0x1C) = *tail;
    }
    if (*tail != NULL) {
        *(u8 **)(*tail + 0x20) = trail;
    }
    *tail = trail;
    *(s32 *)trail = 2;
    *(s32 *)(gEftDust + 0x20) = *(s32 *)(gEftDust + 0x20) + 1;
    func_003126C8(pos, hit + 0x20);
    if (func_0013B350(y)) {
        pos[1] = y[0] + -1.0f;
    }
    func_00312650(delta, hit + 0x20, hit + 0x30);
    sceVu0Normalize(dir, delta);
    delta[1] = 0.0f;
    len = func_001407A0(delta);
    scale = sqrtf(len) * 0.26f;
    if (scale < 0.9f) {
        scale *= 0.65f;
    }
    yaw = atan2f(dir[0], dir[2]) * 180.0f / 3.1415925f;
    height = BtlCharApi_GetHeight(objId) * 0.05f * scale * 7.0f;
    for (i = 0; i < 2; i++) {
        size = RANDF() * 3.0f + 1.0f;
        sizeVel = RANDF() * 3.0f + 5.0f;
        life = RANDF() * 0.2f + 0.3f;
        pitch = RANDF() * 10.0f + 50.0f;
        speed = 40.0f * SCALE(objId, scale);
        sizeVel = sizeVel * SCALE(objId, scale);
        gravity = 6.4f * SCALE(objId, scale);
        EftWaterSpray_Spawn((u8 **)(trail + 0xC), (u8 **)(trail + 0x10), pos, 0x8C, 0x8C, 0x8C, 3, 0,
                            0.0f, height, yaw - 60.0f + (f32)i * 120.0f, pitch, RANDF() * 360.0f, 0.8f, 0.6f,
                            speed, size, sizeVel, -5.0f, gravity, 1.0f, 1.5f, life, 0.0f, 0x102);
    }
    sizeVel = RANDF() * 3.5f + 6.5f;
    life = RANDF() * 0.2f + 0.4f;
    pitch = RANDF() * 10.0f + 60.0f;
    speed = 90.0f * SCALE(objId, scale);
    size = 2.0f * SCALE(objId, scale);
    sizeVel = sizeVel * SCALE(objId, scale);
    gravity = SCALE(objId, scale) * 9.0f;
    dropYaw = yaw - 30.0f + (f32)(rand() % 2) * 60.0f;
    EftWaterDrop_Spawn(trail + 4, trail + 8, (u8 *)pos, 0x80, 0x80, 0x80, 4, 0,
                       dropYaw, pitch, speed, RANDF() * 360.0f, 0.0f, size, sizeVel, -5.0f,
                       gravity, life, 0.0f, 0x106);
    sizeVel = RANDF() * 3.5f + 6.5f;
    life = RANDF() * 0.3f + 0.6f;
    pitch = RANDF() * 10.0f + 70.0f;
    speed = 55.0f * SCALE(objId, scale);
    size = 2.0f * SCALE(objId, scale);
    sizeVel = sizeVel * SCALE(objId, scale);
    gravity = SCALE(objId, scale) * 3.5f;
    EftWaterDrop_Spawn(trail + 4, trail + 8, (u8 *)pos, 0x80, 0x80, 0x80, 1, 0,
                       yaw, pitch, speed, RANDF() * 360.0f, 0.0f, size, sizeVel, -5.0f,
                       gravity, life, 0.0f, 0xA);
    size = SCALE(objId, scale) * 0.0f;
    sizeVel = SCALE(objId, scale) * 10.0f;
    EftWaterRing_Spawn(trail + 0x14, trail + 0x18, (s32)pos, 0xFF, 0xFF, 0xFF, 2, 0, 0xD,
                       0.0f, size, sizeVel, -24.0f, 112.0f, 0.6f, 0.1f);
}
