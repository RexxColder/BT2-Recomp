#include "common.h"

extern f32 D_00385548;
extern f32 D_0038554C;
extern f32 D_00385550;
extern f32 D_00385554;
extern f32 D_00385558;
extern f32 D_0038555C;
extern f32 D_00385560;
extern f32 D_00385564;
extern f32 D_00385568;
extern f32 D_0038556C;
extern f32 D_00385570;
extern f32 D_00385574;
extern f32 D_00385578;
extern f32 D_0038557C;
extern f32 D_00385580;
extern f32 D_00385584;
extern f32 D_00385588;
extern f32 D_0038558C;
extern f32 D_00385590;
extern f32 D_00385594;
extern f32 D_00385598;

extern s32 rand(void);
extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec3_Cross(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern void Vec4_Scale(f32 s, u8 *dst, u8 *src);
extern void Vec3_Lerp(f32 t, u8 *dst, u8 *a, u8 *b);
extern void Vec4_Add(u8 *dst, u8 *a, u8 *b);
extern void func_00129C28(u8 *dst, u8 *src);
extern s32 func_001D4E70(s32 a0, u8 *a1, u8 *a2, u8 *a3, s32 t0, s32 t1, s32 t2, s32 t3,
                         f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                         f32 st0, f32 st8, f32 st10, s32 st18, s32 st20, f32 st28);
extern s32 func_001D4678(s32 a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, s32 t1, s32 t2, s32 t3,
                         f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                         f32 st0, f32 st8, f32 st10, f32 st18);

/* Spawns a burst of impact effects (two sparks, two flashes) at the position of a0 along the direction a1.
   angA/angB are angles in degrees, scale the effect size, extra is passed through to every effect. */
s32 func_001D9040(u8 *a0, u8 *a1, f32 angA, f32 angB, f32 scale, f32 extra) {
    u8 pos[0x10];
    u8 dir[0x10];
    u8 up[0x10];
    u8 side[0x10];
    u8 vA[0x10];
    u8 vB[0x10];
    u8 sum[0x10];
    u8 tmpV[0x10];
    u8 lerpV[0x10];
    u8 col0[0x10];
    u8 col1[0x10];
    f32 fa = 0.0f;
    f32 fb;
    f32 f12v;
    f32 div;
    f32 sc;
    f32 w0;
    f32 w1;
    f32 w2;
    f32 w3;
    f32 w4;
    f32 w5;
    f32 w6;
    f32 k;
    f32 half;
    f32 big;
    f32 grey;
    f32 spin;
    f32 t;

    __builtin_memcpy(pos, a0, 16);
    __builtin_memcpy(dir, a1, 16);
    Vec4_Set(up, 0.0f, -1.0f, 0.0f, 1.0f);
    Vec3_Cross(side, dir, up);
    Vec3_Normalize(side, side);
    if (angA != 0.0f) {
        fa = angA / 90.0f;
    }
    fb = (angB == 0.0f) ? 0.0f : angB / 90.0f;
    Vec4_Scale(fa < 0.0f ? -1.0f : 1.0f, vA, side);
    Vec4_Scale(fb < 0.0f ? -1.0f : 1.0f, vB, dir);
    f12v = fa;
    if (f12v < 0.0f) {
        f12v = -f12v;
    }
    Vec3_Lerp(f12v, vA, vA, up);
    f12v = fb;
    if (f12v < 0.0f) {
        f12v = -f12v;
    }
    Vec3_Lerp(f12v, vB, vB, up);
    Vec4_Add(sum, vA, vB);
    div = D_00385548;
    k = D_0038554C;
    Vec3_Normalize(sum, sum);

    /* effect 1 */
    sc = scale * D_00385554;
    w6 = sc * D_0038555C;
    w0 = ((f32)rand() / div + D_00385550) * sc;
    w1 = ((f32)rand() / div + 1.0f) * sc;
    w2 = ((f32)rand() / div + 2.5f) * sc;
    w3 = ((f32)rand() / div * 3.0f + 9.0f) * sc;
    w4 = (f32)rand() / div * k + D_00385560;
    func_00129C28(tmpV, pos);
    *(f32 *)(tmpV + 4) = *(f32 *)(tmpV + 4) - sc;
    *(f32 *)(tmpV + 0) = *(f32 *)(tmpV + 0) + *(f32 *)(dir + 0) * 4.0f * scale * D_00385554;
    *(f32 *)(tmpV + 8) = *(f32 *)(tmpV + 8) + *(f32 *)(dir + 8) * 4.0f * scale * D_00385554;
    half = D_00385558;
    Vec3_Lerp(half, lerpV, dir, sum);
    Vec3_Normalize(lerpV, lerpV);
    t = (f32)(0x60 - rand() % 16);
    func_001D4E70(0, tmpV, lerpV, sum, 0x80, 0x80, 0x80, 0,
                  w0, -2.5f, w1, w2, w3, 0.0f, t, w6,
                  k, w4, 0.0f, 9, 0, extra);
    w6 = sc * D_00385564;

    /* effect 2 */
    w0 = ((f32)rand() / div * half + 1.5f) * sc;
    w1 = ((f32)rand() / div + 1.0f) * sc;
    w2 = ((f32)rand() / div * half + 1.5f) * sc;
    w3 = (((f32)rand() / div) * 2.0f + 6.5f) * sc;
    w4 = (f32)rand() / div * k + D_00385568;
    func_00129C28(tmpV, pos);
    *(f32 *)(tmpV + 4) = *(f32 *)(tmpV + 4) - sc;
    *(f32 *)(tmpV + 0) = *(f32 *)(tmpV + 0) + *(f32 *)(dir + 0) * 2.0f * scale * D_00385554;
    *(f32 *)(tmpV + 8) = *(f32 *)(tmpV + 8) + *(f32 *)(dir + 8) * 2.0f * scale * D_00385554;
    Vec3_Lerp(0.5f, lerpV, dir, sum);
    Vec3_Normalize(lerpV, lerpV);
    t = (f32)(0x60 - rand() % 16);
    func_001D4E70(0, tmpV, lerpV, sum, 0x80, 0x80, 0x80, 0,
                  w0, -3.5f, w1, w2, w3, 0.0f, t, w6,
                  k, w4, 0.0f, 9, 0, extra);

    /* effect 3 */
    w6 = sc * D_0038556C;
    w0 = (f32)rand() / div * 1.5f + 2.0f;
    w0 = w0 * sc;
    w1 = ((f32)rand() / div + 1.0f) * sc;
    w2 = ((f32)rand() / div + D_00385570) * sc;
    w3 = ((f32)rand() / div * 5.0f + 9.0f) * sc;
    w4 = (f32)rand() / div * D_00385574 + D_00385578;
    func_00129C28(tmpV, pos);
    grey = 128.0f;
    *(f32 *)(tmpV + 4) = *(f32 *)(tmpV + 4) - scale * 3.0f * D_00385554;
    *(f32 *)(tmpV + 0) = *(f32 *)(tmpV + 0) + *(f32 *)(dir + 0) * 3.0f * scale * D_00385554;
    *(f32 *)(tmpV + 8) = *(f32 *)(tmpV + 8) + *(f32 *)(dir + 8) * 3.0f * scale * D_00385554;
    Vec4_Set(col0, grey, grey, grey, 0.0f);
    Vec4_Set(col1, grey, grey, grey, (f32)(0x60 - rand() % 16));
    spin = (f32)rand() / div * 360.0f;
    func_001D4678(0, tmpV, dir, col0, col1, 0, 0xB, 0,
                  w0, -6.0f, w1, w2, w3, spin, (rand() & 1) ? 1.5f : -1.5f, w6,
                  D_0038557C, w4, 0.0f, extra);

    /* effect 4 */
    div = D_00385580;
    big = D_00385584;
    w6 = D_00385588;
    w0 = (f32)rand() / div + 1.5f;
    w1 = (f32)rand() / div * 0.5f + 0.5f;
    w2 = (f32)rand() / div * D_0038558C + D_00385590;
    w3 = (f32)rand() / div * 3.5f + 6.5f;
    t = (f32)rand() / div;
    sc = scale * big;
    w6 = sc * w6;
    w0 = w0 * sc;
    w1 = w1 * sc;
    w2 = w2 * sc;
    w3 = w3 * sc;
    w4 = t * 0.5f + D_00385594;
    func_00129C28(tmpV, pos);
    grey = 128.0f;
    *(f32 *)(tmpV + 4) = *(f32 *)(tmpV + 4) - scale * 3.0f * big;
    *(f32 *)(tmpV + 0) = *(f32 *)(tmpV + 0) + *(f32 *)(dir + 0) * 1.5f * scale * big;
    *(f32 *)(tmpV + 8) = *(f32 *)(tmpV + 8) + *(f32 *)(dir + 8) * 1.5f * scale * big;
    Vec4_Set(col0, grey, grey, grey, 0.0f);
    Vec4_Set(col1, grey, grey, grey, (f32)(0x60 - rand() % 16));
    spin = (f32)rand() / div * 360.0f;
    return func_001D4678(0, tmpV, dir, col0, col1, 0, 0xB, 0,
                         w0, -5.0f, w1, w2, w3, spin, (rand() & 1) ? 1.5f : -1.5f, w6,
                         D_00385598, w4, 0.0f, extra);
}
