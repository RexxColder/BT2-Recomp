#include "common.h"

extern u8 *gBtlCamView;
extern f32 D_00384BAC;
extern f32 D_00384BB0;
extern f32 D_00384BB4;
extern f32 D_00384BB8;
extern f32 D_00384BBC;
extern f32 D_00384BC0;
extern f32 D_00384BC4;
extern f32 D_00384BC8;
extern u8 D_00341F50[];

extern s32 Vec4_Set(f32 *v, f32 x, f32 y, f32 z, f32 w);
s32 func_00129F60(s32 *a0, f32 *a1, f32 *a2, s32 a3);
extern void Mtx_StoreIdentity(void *arg0);
extern void Mtx_RotateZ(f32 farg0, void *arg0, void *arg1);
void Mtx_MulVec4(f32 *arg0, f32 *arg1, f32 *arg2);
void Vec3_Mul(u8 *arg0, u8 *arg1, u8 *arg2);
s32 EftPrim_IsOffScreen(s32 x, s32 y, s32 z);
s32 func_001870B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                  f32 fA, f32 fB, f32 fC, f32 fD,
                  s32 h0, s32 h1, s32 h2, s32 h3, s32 sortKey, s64 pad5, s64 pad6,
                  s32 shift, s32 mode, u64 extra);

void func_00186B80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   s32 stk0, s32 stk1, f32 stk2, s32 stk3, s32 stk4, s32 stk5, s64 stk6) {
    u8 r = (u8)arg0;
    u8 g = (u8)arg1;
    u8 b = (u8)arg2;
    u8 a = (u8)arg3;
    s32 pos[4];       /* projected position (x, y, z, w as ints) */
    f32 posIn[4];
    s32 corner[16];   /* 4 corners x (x, y, z, w) */
    f32 cf[16];
    f32 mtx[16];
    f32 camScale = *(f32 *)(gBtlCamView + 0x224);
    f32 ang1 = farg7;
    f32 ang2 = stk2;
    f32 t, size;
    s32 step, i, sx, sy, ox, oy;
    u32 hw, hh;
    u32 sizeArg = (u32)stk1;
    s32 flag = (u8)stk5;
    s32 depth;

    Vec4_Set(posIn, farg0, farg1, farg2, 1.0f);
    func_00129F60(pos, (f32 *)(gBtlCamView + 0x100), posIn, 1);
    t = (f32)sizeArg * camScale;
    size = t / (f32)pos[3];
    step = (s32)size;
    if (size >= 2147483648.0f) {
        step = (s32)(size - 2147483648.0f) | (s32)0x80000000;
    }
    hw = (u32)(arg6 * step) >> 12;
    hh = (u32)(arg7 * step) >> 12;
    if (hw < 2 || hh < 2) {
        return;
    }

    if (D_00384BAC < ang1) {
        ang1 = ang1 - D_00384BB0;
    } else if (ang1 < D_00384BB4) {
        ang1 = ang1 + D_00384BB8;
    }
    if (D_00384BBC < ang2) {
        ang2 = ang2 - D_00384BC0;
    } else if (ang2 < D_00384BC4) {
        ang2 = ang2 + D_00384BC8;
    }
    Mtx_StoreIdentity(mtx);
    Mtx_RotateZ(ang1, mtx, mtx);
    Mtx_RotateZ(ang2, mtx, mtx);

    if (arg4 < 0) {
        ox = -(s32)((u32)(-arg4 * step) >> 12);
    } else {
        ox = (s32)((u32)(arg4 * step) >> 12);
    }
    if (arg5 < 0) {
        oy = -(s32)((u32)(-arg5 * step) >> 12);
    } else {
        oy = (s32)((u32)(arg5 * step) >> 12);
    }

    corner[0] = ox - (s32)hw;
    corner[1] = oy - (s32)hh;
    corner[2] = 0;
    corner[3] = 1;
    corner[4] = ox - (s32)hw;
    corner[5] = (s32)hh + oy;
    corner[6] = 0;
    corner[7] = 1;
    corner[8] = (s32)hw + ox;
    corner[9] = oy - (s32)hh;
    corner[10] = 0;
    corner[11] = 1;
    corner[12] = (s32)hw + ox;
    corner[13] = (s32)hh + oy;
    corner[14] = 0;
    corner[15] = 1;

    for (i = 0; i < 4; i++) {
        s32 *c = &corner[i * 4];
        f32 *v = &cf[i * 4];
        v[0] = (f32)c[0];
        v[1] = (f32)c[1];
        v[2] = (f32)c[2];
        v[3] = (f32)c[3];
        Mtx_MulVec4(v, mtx, v);
        Vec3_Mul((u8 *)v, (u8 *)v, D_00341F50);
        c[0] = (s32)v[0];
        c[1] = (s32)v[1];
        c[2] = (s32)v[2];
        c[3] = (s32)v[3];
    }

    if (EftPrim_IsOffScreen(pos[0] + corner[0], pos[1] + corner[1], pos[2]) != 0) {
        return;
    }
    if (EftPrim_IsOffScreen(pos[0] + corner[4], pos[1] + corner[5], pos[2]) != 0) {
        return;
    }
    if (EftPrim_IsOffScreen(pos[0] + corner[8], pos[1] + corner[9], pos[2]) != 0) {
        return;
    }
    if (EftPrim_IsOffScreen(pos[0] + corner[12], pos[1] + corner[13], pos[2]) != 0) {
        return;
    }
    if (flag != 0) {
        pos[2] = 0xFFFFFF;
    }
    depth = pos[2];
    func_001870B8(r, g, b, a,
                  pos[0] + corner[0], pos[1] + corner[1], pos[0] + corner[4], pos[1] + corner[5],
                  farg3, farg4, farg5, farg6,
                  pos[0] + corner[8], pos[1] + corner[9], pos[0] + corner[12], pos[1] + corner[13],
                  depth, depth >> 8, stk0, stk3, stk4, (u64)stk6);
}
