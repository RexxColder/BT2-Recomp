#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_003856D0;
extern f32 D_003856D4;
extern f32 D_003856D8;
extern f32 D_003856DC;

void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129B58(void *arg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1);
void EftMath_MtxFromDir(s32 arg0, s32 arg1, f32 farg0);
void func_00129C50(void *arg0, void *arg1, void *arg2);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
void func_00129FE0(void *a, void *b, void *c, s32 d, s32 e);
s32 func_0012E840(u8 *p);

#define H(p, off) (*(u16 *)((p) + (off)))
#define W(p, off) (*(s32 *)((p) + (off)))

/* Draws a camera-facing quad (variant of 0x001C5D90 with a force-far flag) at world point (farg0, farg1, farg2): the half-size is
   (arg4 * arg6 >> 12) / 16 by (arg5 * arg6 >> 12) / 16, rotated by the angle farg7 (wrapped to the
   D_003856D0.. range). The 4 corners are projected with the camera; if func_0012E840 accepts them all a
   0x80-byte GIF packet (colors arg0..arg3, uv farg3..farg6, tag arg8) is appended to the depth-sorted
   list at D_00387AE0 (bucket from the first corner's depth, layer arg7). */
void func_001EA808(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6,
                   f32 farg7, u8 forceFar, u64 arg8) {
    u8 sp[0xf0];   /* tamano de locales del original (antes 0xe0) */
    f32 angle = farg7;
    f32 halfW;
    f32 halfH;
    s32 i;
    s32 depth;
    u8 *p;
    u8 *entry;

    if (D_003856D0 < angle) {
        angle = angle - D_003856D4;
    } else if (angle < D_003856D8) {
        angle = angle + D_003856DC;
    }
    halfW = (f32)((u32)(arg4 * arg6) >> 12) * 0.0625f;
    halfH = (f32)((u32)(arg5 * arg6) >> 12) * 0.0625f;

    Vec4_Set(sp + 0x80, farg0, farg1, farg2, 1.0f);
    func_00129B58(sp + 0x90, gBtlCamView + 0x1F0, sp + 0x80);
    Vec3_Normalize(sp + 0x90, sp + 0x90);
    EftMath_MtxFromDir((s32)(sp + 0xA0), (s32)(sp + 0x90), angle);
    Vec4_Set(sp + 0x40, -halfW, -halfH, 0.0f, 1.0f);
    Vec4_Set(sp + 0x50, halfW, -halfH, 0.0f, 1.0f);
    Vec4_Set(sp + 0x60, -halfW, halfH, 0.0f, 1.0f);
    Vec4_Set(sp + 0x70, halfW, halfH, 0.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        func_00129C50(sp + 0x40 + 16 * i, sp + 0xA0, sp + 0x40 + 16 * i);
        Vec3_Add(sp + 0x40 + 16 * i, sp + 0x40 + 16 * i, sp + 0x80);
        *(f32 *)(sp + 0x4C + 16 * i) = 1.0f;
    }
    func_00129FE0(sp, gBtlCamView + 0x100, sp + 0x40, 4, 1);

    if (func_0012E840(sp + 0x00) != 0) {
        return;
    }
    if (func_0012E840(sp + 0x10) != 0) {
        return;
    }
    if (func_0012E840(sp + 0x20) != 0) {
        return;
    }
    if (func_0012E840(sp + 0x30) != 0) {
        return;
    }

    p = D_00387AD8;
    D_00387AD8 = p + 0x80;
    *(u64 *)(p + 0x00) = 0xA0000007;
    *(u64 *)(p + 0x20) = 0x54;
    *(u64 *)(p + 0x10) = 0xC400000000008001ULL;
    *(u64 *)(p + 0x18) = 0xF42424242160ULL;
    p[0x30] = arg0;
    p[0x31] = arg1;
    p[0x32] = arg2;
    *(f32 *)(p + 0x34) = 1.0f;
    p[0x33] = arg3;
    *(u64 *)(p + 0x28) = arg8;
    *(f32 *)(p + 0x4C) = farg4;
    *(f32 *)(p + 0x58) = farg3;
    *(f32 *)(p + 0x68) = farg5;
    *(f32 *)(p + 0x6C) = farg6;
    *(f32 *)(p + 0x38) = farg3;
    *(f32 *)(p + 0x3C) = farg4;
    *(f32 *)(p + 0x48) = farg5;
    *(f32 *)(p + 0x5C) = farg6;

    for (i = 0; i < 4; i++) {
        H(p, 0x40 + 0x10 * i) = H(sp, 0x10 * i);
        H(p, 0x42 + 0x10 * i) = H(sp, 4 + 0x10 * i);
        W(p, 0x44 + 0x10 * i) = (W(sp, 8 + 0x10 * i) & 0xFFFFFF) | 0xFF000000;
    }

    if (forceFar != 0) {
        W(sp, 8) = 0xFFFFFF;
    }
    depth = W(sp, 8) >> 8;
    if (depth < 0) {
        entry = D_00387AE0 + arg7 * 8;
    } else if (depth < 0x1000) {
        entry = D_00387AE0 + (depth * 2 + arg7) * 8;
    } else {
        entry = D_00387AE0 + arg7 * 8 + 0xFFF0;
    }
    *(u8 **)(*(u8 **)(entry + 4) + 4) = p;
    *(u8 **)(entry + 4) = p;
}
