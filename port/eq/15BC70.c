#include "common.h"

extern f32 D_0036E2A0[4];
extern f32 D_0036E2B0[4];
extern f32 D_0036E2C0[4];
extern f32 D_003846EC;
extern f32 D_003846F0;
extern f32 D_003846F4;
extern f32 D_003846F8;
extern f32 D_003846FC;
extern f32 D_00384700;
extern f32 D_00384704;
extern f32 D_00384708;

f32 sinf(f32 x);
f32 cosf(f32 x);
s32 rand(void);
void Vec3_Sub(f32 *dst, f32 *a, f32 *b);
s32 Vec3_Normalize(f32 *dst, f32 *src);
void Vec3_Lerp(f32 *dst, f32 *a, f32 *b, f32 t);
f32 EftMath_WrapAngle(f32 angle);
void func_001D4678(s32 arg0, u8 *a1, u8 *a2, u8 *a3, u8 *a4, s32 a5, s32 a6, s32 a7,
                   f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                   f32 st0, f32 st1, f32 st2, f32 st3);

/* Spawns 30 sparks on a ring of radius `radius` around `pos`, each given a randomised size, spin and lifetime. */
void func_0015BC70(s32 unused, f32 *pos, f32 scale, f32 radius, f32 lerpT, f32 sizeMul, f32 alphaScale) {
    f32 spark[4];
    f32 dir[4];
    f32 axis[4];
    f32 colA[4];
    f32 colB[4];
    f32 angle = 0.0f;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;
    f32 g;
    s32 i;

    colB[0] = D_0036E2C0[0];
    colB[1] = D_0036E2C0[1];
    colB[2] = D_0036E2C0[2];
    colB[3] = D_0036E2C0[3];
    colB[3] = colB[3] * alphaScale;
    axis[0] = D_0036E2A0[0];
    axis[1] = D_0036E2A0[1];
    axis[2] = D_0036E2A0[2];
    axis[3] = D_0036E2A0[3];
    colA[0] = D_0036E2B0[0];
    colA[1] = D_0036E2B0[1];
    colA[2] = D_0036E2B0[2];
    colA[3] = D_0036E2B0[3];
    for (i = 0; i < 30; i++) {
        spark[0] = pos[0] + sinf(angle) * radius;
        spark[1] = pos[1];
        spark[2] = pos[2] + cosf(angle) * radius;
        spark[3] = 1.0f;
        spark[0] += ((f32)rand() / D_003846EC) * 10.0f - 5.0f;
        spark[1] += ((f32)rand() / D_003846EC) * 10.0f - 5.0f;
        spark[2] += ((f32)rand() / D_003846EC) * 10.0f - 5.0f;
        Vec3_Sub(dir, spark, pos);
        Vec3_Normalize(dir, dir);
        Vec3_Normalize(dir, dir);
        Vec3_Lerp(dir, dir, axis, lerpT);
        angle = EftMath_WrapAngle(0.0f + D_003846F0 * (f32)i);
        a = ((f32)rand() / D_003846EC) * 0.5f + 1.0f;
        a *= sizeMul;
        b = ((f32)rand() / D_003846EC) * 1.5f + 2.0f;
        b *= scale;
        c = ((f32)rand() / D_003846EC) * D_003846F4 + 0.5f;
        c *= scale;
        d = ((f32)rand() / D_003846EC) * D_003846F8 + 0.5f;
        e = ((f32)rand() / D_003846EC) * 360.0f;
        g = (rand() & 1) ? D_003846FC : D_00384700;
        func_001D4678(0, (u8 *)spark, (u8 *)dir, (u8 *)colA, (u8 *)colB, 0, 0xB, 0,
                      a, 0.0f, b, c, b * D_00384704, e, g, D_00384708,
                      0.0f, d, 0.0f, 1.0f);
    }
}
