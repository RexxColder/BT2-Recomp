#include "common.h"

extern s32 gBtlCamView;

void sceVu0UnitMatrix(f32 *arg0);
void sceVu0RotMatrixZ(f32 *arg0, f32 *arg1, f32 arg2);
void sceVu0InversMatrix(void *arg0, s32 arg1);
void sceVu0MulMatrix(f32 *arg0, f32 *arg1, f32 *arg2);
void sceVu0ApplyMatrix(f32 *arg0, f32 *arg1, f32 *arg2);
f32 EftMath_WrapAngle(f32 farg0);
void func_00312638(u8 *a0, f32 *a1, u8 *a2);
s32 func_00129440(s32 *arg0, f32 *arg1);
s32 func_001E6400(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, u64 arg9 /* TEX0 (64-bit; was u8 *: truncated to 32 bits) */, s32 arg10, u8 arg11);

/* int -> float the way the game does it for a 64-bit register: negative values are halved with the low bit kept, converted and doubled */
static f32 cvt64(s64 v) {
    u32 lo = (u32)v;
    f32 f;
    if (v < 0) {
        f = (f32)(s32)((lo & 1) | (lo >> 1));
        return f + f;
    }
    return (f32)(s32)lo;
}

/* 0x001E4760: builds the four corners (+-halfX, +-halfY, 0, 1) of a rectangle (half sizes in
   t0/t1 scaled by t3 / 65536), rotates them by Z angle and the inverse camera view, offsets by
   (fx, fy, fz), projects them with func_00129440 and hands the result to func_001E6400. */
s32 func_001E4760(u8 a0, u8 a1, u8 a2, u8 a3, s64 hx, s64 hy, s64 unused6, s64 scaleBits,
                  s32 st0, s32 stFlag, u8 stByte, s64 *stPtr,
                  f32 fx, f32 fy, f32 fz, f32 c0, f32 c1, f32 c2, f32 c3, f32 angle) {
    u8 sp[0x1F0];
    f32 *rot = (f32 *)(sp + 0xB0);
    f32 *inv = (f32 *)(sp + 0xF0);
    f32 *p0 = (f32 *)(sp + 0x60);
    f32 *p1 = (f32 *)(sp + 0x70);
    f32 *p2 = (f32 *)(sp + 0x80);
    f32 *p3 = (f32 *)(sp + 0x90);
    f32 *off = (f32 *)(sp + 0xA0);
    f32 *colA = (f32 *)(sp + 0x130);
    f32 *colB = (f32 *)(sp + 0x140);
    f32 rotA;
    f32 sc;
    f32 w;
    f32 h;
    u8 *ctx = sp + 0x20;
    s64 sv;

    sceVu0UnitMatrix(rot);
    rotA = EftMath_WrapAngle(angle);
    sceVu0RotMatrixZ(rot, rot, rotA);
    sceVu0InversMatrix(inv, gBtlCamView);
    *(s32 *)(sp + 0x120) = 0;
    *(s32 *)(sp + 0x124) = 0;
    *(s32 *)(sp + 0x128) = 0;
    sc = cvt64(scaleBits) * 0.000244140625f * 0.0625f;
    w = cvt64(hx) * sc;
    h = cvt64(hy) * sc;
    p0[0] = -w;
    p0[1] = -h;
    p0[2] = 0.0f;
    p0[3] = 1.0f;
    p1[0] = -w;
    p1[1] = h;
    p1[2] = 0.0f;
    p1[3] = 1.0f;
    p2[0] = w;
    p2[1] = -h;
    p2[2] = 0.0f;
    p2[3] = 1.0f;
    p3[0] = w;
    p3[1] = h;
    p3[2] = 0.0f;
    p3[3] = 1.0f;
    sceVu0MulMatrix(rot, inv, rot);
    sceVu0ApplyMatrix(p0, rot, p0);
    sceVu0ApplyMatrix(p1, rot, p1);
    sceVu0ApplyMatrix(p2, rot, p2);
    sceVu0ApplyMatrix(p3, rot, p3);
    off[0] = fx;
    off[1] = fy;
    off[2] = fz;
    off[3] = 0.0f;
    func_00312638((u8 *)p0, p0, (u8 *)off);
    func_00312638((u8 *)p1, p1, (u8 *)off);
    func_00312638((u8 *)p2, p2, (u8 *)off);
    func_00312638((u8 *)p3, p3, (u8 *)off);
    p3[3] = 1.0f;
    p0[3] = 1.0f;
    p1[3] = 1.0f;
    p2[3] = 1.0f;
    func_00129440((s32 *)ctx, p0);
    sv = *stPtr;
    colA[0] = c0;
    colA[1] = c1;
    colA[2] = c0;
    colA[3] = c3;
    colB[0] = c2;
    colB[1] = c1;
    colB[2] = c2;
    colB[3] = c3;
    (void)unused6;
    (void)st0;
    return func_001E6400((u8 *)p0, (u8 *)colA, (u8 *)colB, a0, a1, a2, a3, stFlag, 0, (u64)sv,
                         *(s32 *)(sp + 0x28) >> 8, stByte);
}
