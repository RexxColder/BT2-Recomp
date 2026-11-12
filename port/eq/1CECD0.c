#include "common.h"

f32 func_00129CD8(f32 *arg0, f32 *arg1);
void Vec4_Set(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_001DA670(f32 *arg0, f32 *arg1, f32 *arg2);
void func_001DA788(f32 *arg0, f32 *arg1);
extern s32 rand(void);
f32 EftMath_WrapAngle(f32 farg0);
f32 func_0012A3F8(f32 farg0);
f32 Mathf_Cos(f32 farg0);
void Mtx_MulVec4(f32 *out, f32 *mtx, f32 *in);
void Vec4_Scale(f32 *dst, f32 *src, f32 s);
void Vec4_Add(f32 *dst, f32 *a, f32 *b);
void Vec3_Normalize(f32 *arg0, f32 *arg1);
void func_001D4678(s32 arg0, u8 *a1, u8 *a2, u8 *a3, u8 *a4, s32 a5, s32 a6, s32 a7,
                   f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                   f32 st0, f32 st1, f32 st2, f32 st3);
void func_001D5548(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   f32 arg8, f32 arg9, f32 arg10);
extern u8 *D_00387E9C;

#define RANDF() ((f32)rand() / 2147483520.0f)

s32 func_001CECD0(u8 *obj, f32 *dir) {
    f32 down[4];
    f32 quat[4];
    f32 mtx[16];
    f32 pt[4];
    f32 off[4];
    f32 sum[4];
    f32 colA[4];
    f32 colB[4];
    f32 d, base, ang, a, b, c, e, g;
    s32 i, r;

    d = func_00129CD8(down, dir);
    if (*(u8 *)(D_00387E9C + 0x1491) == 0) {
        return 0;
    }
    Vec4_Set(down, 0.0f, -1.0f, 0.0f, 1.0f);
    if (d != 1.0f && d != -1.0f) {
        func_001DA670(quat, down, dir);
        func_001DA788(mtx, quat);
    }
    base = RANDF() * 6.2831855f;
    for (i = 0; i < 16; i++) {
        ang = EftMath_WrapAngle(base + 0.3926991f * (f32)i);
        pt[0] = func_0012A3F8(ang);
        pt[1] = 0.0f;
        pt[2] = Mathf_Cos(ang);
        pt[3] = 1.0f;
        if (d != 1.0f && d != -1.0f) {
            Mtx_MulVec4(pt, mtx, pt);
        }
        Vec4_Scale(off, pt, 3.0f);
        Vec4_Add(sum, (f32 *)obj, off);
        a = RANDF() * 2.0f + 3.5f;
        b = RANDF() * 3.0f + 6.0f;
        c = RANDF() * 0.5f + 0.8f;
        e = RANDF() + 2.0f;
        Vec4_Set(colA, 128.0f, 128.0f, 128.0f, 0.0f);
        r = rand();
        Vec4_Set(colB, 128.0f, 128.0f, 128.0f, (f32)(128 - r % 32));
        g = RANDF() * 360.0f;
        func_001D4678(0, obj, (u8 *)pt, (u8 *)colA, (u8 *)colB, 0, 0xB, 0,
                      a, -5.0f, b, c, b * 4.0f, g, (rand() & 1) ? 1.5f : -1.5f, -0.02f,
                      0.0f, e, 0.0f, 1.0f);
    }
    base = RANDF() * 6.2831855f;
    for (i = 0; i < 3; ) {
        f32 sp, rv;
        a = RANDF() * 2.0f + 2.5f;
        b = RANDF() * 4.0f + 8.0f;
        c = RANDF() * 0.5f + 1.0f;
        ang = EftMath_WrapAngle(base + 2.0943952f * (f32)i);
        i++;
        pt[0] = func_0012A3F8(ang);
        pt[1] = 0.0f;
        pt[2] = Mathf_Cos(ang);
        pt[3] = 1.0f;
        pt[1] = pt[1] - (RANDF() * 0.6f + 0.4f);
        Vec3_Normalize(pt, pt);
        if (d != 1.0f) {
            if (d == -1.0f) {
                pt[1] = -pt[1];
            } else {
                Mtx_MulVec4(pt, mtx, pt);
            }
        }
        e = RANDF() * 360.0f;
        sp = (rand() & 1) ? 2.0f : -2.0f;
        r = rand();
        func_001D5548(obj, (u8 *)pt, 0x80, 0x80, 0x80, 0xB, 0, 0,
                      a, -24.0f, b, 2.0f, e, sp, (f32)(128 - r % 32), 0.03f,
                      c, 0.0f, 1.0f);
    }
    {
        f32 a2, b2, c2, e2, s2;
        a2 = RANDF() * 2.0f + 4.0f;
        b2 = RANDF() * 4.0f + 12.0f;
        c2 = RANDF() + 1.5f;
        e2 = RANDF() * 360.0f;
        s2 = (rand() & 1) ? 2.0f : -2.0f;
        r = rand();
        func_001D5548(obj, (u8 *)dir, 0x80, 0x80, 0x80, 0xB, 0, 0,
                      a2, -16.0f, b2, 2.0f, e2, s2, (f32)(128 - r % 32), 0.0f,
                      c2, 0.0f, 1.0f);
    }
    return 1;
}
