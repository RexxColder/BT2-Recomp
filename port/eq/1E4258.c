#include "common.h"

extern u8 *gBtlCamView;
void sceVu0UnitMatrix(void *m);
f32 EftMath_WrapAngle(f32 farg0);
void sceVu0RotMatrixZ(void *dst, void *src, f32 ang);
void sceVu0InversMatrix(void *dst, void *src);
void sceVu0MulMatrix(void *dst, void *a, void *b);
void sceVu0ApplyMatrix(void *dst, void *m, void *v);
void func_00312FB0(void *dst, void *src, f32 scale);
void func_00312638(void *dst, void *src, void *off);
s32 func_00129440(s32 *arg0, f32 *arg1);
s32 func_001E6400(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, u64 arg9 /* TEX0 (64-bit; was u8 *: truncated to 32 bits) */, s32 arg10, u8 arg11);

s32 func_001E4258(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 x, s32 y, u32 w, u32 h,
                  s32 arg8, u32 scaleRaw, s32 arg10, s32 arg11, u8 arg12, s32 skipOut,
                  s32 *outA, u8 **outB,
                  f32 offX, f32 offY, f32 offZ, f32 fL, f32 fT, f32 fR, f32 fB, f32 angle) {
    f32 mat[16];
    f32 inv[16];
    f32 pts[16];
    f32 off[4];
    f32 va[4];
    f32 vb[4];
    s32 out[4];
    f32 scale;
    f32 fx;
    f32 fy;
    f32 negW;
    f32 negH;
    s32 i;

    sceVu0UnitMatrix(mat);
    sceVu0RotMatrixZ(mat, mat, EftMath_WrapAngle(angle));
    sceVu0InversMatrix(inv, gBtlCamView);
    inv[12] = 0.0f;
    inv[13] = 0.0f;
    inv[14] = 0.0f;

    scale = (f32)scaleRaw * 0x1p-12f * 0x1p-4f;
    fx = (f32)x;
    fy = (f32)y;
    negW = -(f32)w;
    negH = -(f32)h;

    pts[0] = fx + negW;
    pts[1] = fy + negH;
    pts[2] = 0.0f;
    pts[3] = 1.0f;
    pts[4] = fx + negW;
    pts[5] = (f32)(u32)(y + (s32)h);
    pts[6] = 0.0f;
    pts[7] = 1.0f;
    pts[8] = (f32)(u32)(x + (s32)w);
    pts[9] = fy + negH;
    pts[10] = 0.0f;
    pts[11] = 1.0f;
    pts[12] = (f32)(u32)(x + (s32)w);
    pts[13] = (f32)(u32)(y + (s32)h);
    pts[14] = 0.0f;
    pts[15] = 1.0f;

    for (i = 0; i < 4; i++) {
        func_00312FB0(pts + i * 4, pts + i * 4, scale);
    }
    sceVu0MulMatrix(mat, inv, mat);
    for (i = 0; i < 4; i++) {
        sceVu0ApplyMatrix(pts + i * 4, mat, pts + i * 4);
    }
    off[0] = offX;
    off[1] = offY;
    off[2] = offZ;
    off[3] = 0.0f;
    for (i = 0; i < 4; i++) {
        func_00312638(pts + i * 4, pts + i * 4, off);
    }
    pts[3] = 1.0f;
    pts[7] = 1.0f;
    pts[11] = 1.0f;
    pts[15] = 1.0f;

    func_00129440(out, pts);

    va[0] = fL;
    va[1] = fT;
    va[2] = fL;
    va[3] = fB;
    vb[0] = fR;
    vb[1] = fT;
    vb[2] = fR;
    vb[3] = fB;

    if (skipOut == 0) {
        *outA = out[2] >> 8;
    }
    return func_001E6400((u8 *)pts, (u8 *)va, (u8 *)vb, arg0, arg1, arg2, arg3, arg11, 0,
                         *(u64 *)outB, *outA, arg12);
}
