#include "common.h"

extern u8 *EftWaterSpray_Alloc(void);
extern void func_003126C8(void *arg0, void *arg1);
extern f32 EftMath_WrapAngle(f32 farg0);
extern f32 func_0012A3F8(f32 farg0);
extern f32 Mathf_Cos(f32 farg0);
extern void sceVu0Normalize(void *arg0, void *arg1);
extern void func_00312680(void *arg0, void *arg1, f32 farg0);
extern void func_00312638(void *arg0, void *arg1, void *arg2);
extern u8 *gEftDust;
extern f32 D_003844D0;
extern f32 D_003844D4;
extern f32 D_003844D8;
extern f32 D_003844DC;

/* Spawns one water-spray particle at the tail of a doubly linked list (head/tail passed by
   pointer): origin from vec, velocity from two angles (degrees) and a speed, fade and size
   rates from the timing floats. Returns the new live count (0 when the pool is empty). */
s32 EftWaterSpray_Spawn(u8 **head, u8 **tail, f32 *vec, u8 b0, u8 b1, u8 b2, u8 b3, u8 b4,
                        f32 posScale, f32 yAdd, f32 angleA, f32 angleB, f32 f60, f32 startAlpha, f32 endAlpha,
                        f32 speed,
                        f32 s48, f32 s4C, f32 s50Div, f32 s64Mul, f32 s68, f32 s6C, f32 life, f32 s78Mul,
                        s32 flags) {
    u8 *rec = EftWaterSpray_Alloc();
    f32 tmp[4];
    f32 a;
    f32 b;
    f32 wrapped;
    f32 *dir;

    if (rec == 0) {
        return 0;
    }
    if (*head == 0) {
        *head = rec;
        *(u8 **)(rec + 0x88) = 0;
        *(u8 **)(rec + 0x8C) = 0;
    } else {
        *(u8 **)(rec + 0x8C) = 0;
        *(u8 **)(rec + 0x88) = *tail;
    }
    if (*tail != 0) {
        *(u8 **)(*tail + 0x8C) = rec;
    }
    *tail = rec;
    *(s32 *)(rec + 0) = 0;
    *(s32 *)(rec + 4) = 0;
    *(s32 *)(rec + 8) = 0;
    *(f32 *)(rec + 0xC) = 1.0f;
    func_003126C8(rec + 0x10, vec);
    *(f32 *)(rec + 0x14) = *(f32 *)(rec + 0x14) + yAdd;
    *(f32 *)(rec + 0x48) = s48;
    *(f32 *)(rec + 0x4C) = s4C;
    *(f32 *)(rec + 0x40) = startAlpha;
    *(f32 *)(rec + 0x44) = (endAlpha - startAlpha) / (life * 30.0f);
    if (s50Div == 0.0f) {
        *(f32 *)(rec + 0x50) = 0.0f;
    } else {
        *(f32 *)(rec + 0x50) = 1.0f / s50Div;
    }
    a = angleA / 180.0f;
    *(f32 *)(rec + 0x68) = s68;
    *(f32 *)(rec + 0x64) = s64Mul * D_003844D0;
    *(f32 *)(rec + 0x74) = D_003844D4;
    b = angleB / 180.0f;
    *(f32 *)(rec + 0x78) = s78Mul * 30.0f;
    *(f32 *)(rec + 0x6C) = s6C;
    *(f32 *)(rec + 0x60) = f60;
    rec[0x7C] = b0;
    rec[0x7D] = b1;
    rec[0x7E] = b2;
    rec[0x7F] = b3;
    rec[0x80] = b4;
    *(s32 *)(rec + 0x70) = 0;
    *(s32 *)(rec + 0x84) = flags;

    wrapped = EftMath_WrapAngle(a * D_003844D8);
    dir = (f32 *)(rec + 0x30);
    dir[0] = func_0012A3F8(wrapped);
    dir[1] = 0.0f;
    dir[2] = Mathf_Cos(wrapped);
    dir[3] = 1.0f;
    wrapped = b * D_003844D8;
    sceVu0Normalize(dir, dir);
    *(f32 *)(rec + 0x20) = dir[0] * speed * Mathf_Cos(wrapped);
    *(f32 *)(rec + 0x24) = -speed * func_0012A3F8(wrapped);
    *(f32 *)(rec + 0x28) = dir[2] * speed * Mathf_Cos(wrapped);
    func_00312680(tmp, dir, posScale);
    func_00312638(rec + 0x10, rec + 0x10, tmp);
    *(f32 *)(rec + 0x1C) = 1.0f;
    if (flags & 0x100) {
        *(s32 *)(rec + 0x54) = 0;
        *(f32 *)(rec + 0x5C) = 96.0f;
        *(f32 *)(rec + 0x58) = 96.0f / (life * D_003844DC * 30.0f);
    }
    *(s32 *)(gEftDust + 0x34) = *(s32 *)(gEftDust + 0x34) + 1;
    return *(s32 *)(gEftDust + 0x34);
}
