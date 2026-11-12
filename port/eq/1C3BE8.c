#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_00385160;

extern s32 func_00129F60(s32 *dst, u8 *mtx, u8 *pos, s32 a3);
extern void func_001EEEF0(void *dst, void *src);
extern f32 Vec3_Dot(f32 *a, f32 *b);
extern void Vec4_Set(void *dst, f32 x, f32 y, f32 z, f32 w);
extern f32 EftMath_WrapAngle(f32 a);
extern void func_00128EF0(void);
extern void func_00128F08(void);
extern void Vu0Cur_LoadIdentity(void);
extern void Vu0Cur_RotateZ(f32 a);
extern void Vu0Cur_MulVec4(void *dst, void *src);
extern void Vec3_Set(void *dst, f32 x, f32 y, f32 z);
extern s32 func_001C2848(s32 x, s32 y, s32 z);

/* corner vertex: x, y halves and the 24 bit z (64 bit conversion), alpha forced to 0xFF */
#define PUT_CORNER(p, off, v) \
    do { \
        *(u16 *)((p) + (off)) = (u16)(u32)(v)[0]; \
        *(u16 *)((p) + (off) + 2) = (u16)(u32)(v)[1]; \
        *(u64 *)((p) + (off)) = (*(u64 *)((p) + (off)) & 0xFF000000FFFFFFFFULL) | (((u64)(v)[2] & 0xFFFFFF) << 32); \
        (p)[(off) + 7] = 0xFF; \
    } while (0)

#define PUT_COLOR_BYTES(p, off) \
    do { \
        (p)[(off) + 0] = obj[0x18]; \
        (p)[(off) + 1] = obj[0x19]; \
        (p)[(off) + 2] = obj[0x1A]; \
        *(f32 *)((p) + (off) + 4) = 1.0f; \
        (p)[(off) + 3] = obj[0x1B]; \
    } while (0)

/* Queues one screen-space billboard quad (4 corners, rotated by obj+0x14, optionally mirrored). */
void func_001C3BE8(u8 *obj) {
    s32 proj[4];
    f32 corner0[4];
    f32 corner1[4];
    f32 corner2[4];
    f32 corner3[4];
    f32 cam[4];
    u8 dirv[16];
    u8 *view = gBtlCamView;
    f32 scale = *(f32 *)(view + 0x224);
    u32 cnt = (u32)*(f32 *)(obj + 0x10);
    u32 prod;
    u32 n;
    f32 g;
    f32 w;
    f32 nf;
    f32 u0;
    f32 v0;
    f32 u1;
    f32 v1;
    f32 t;
    u8 *p;
    s32 sub;
    s32 layer;
    u8 *node;
    u8 *last;

    if (cnt == 0) {
        return;
    }
    func_00129F60(proj, view + 0x100, obj + 0x20, 1);
    prod = cnt * (u32)((scale * 4096.0f) / (f32)proj[3]);
    n = prod >> 12;
    if (n < 2) {
        return;
    }
    func_001EEEF0(dirv, obj + 0xE0);
    view = gBtlCamView;
    cam[0] = *(f32 *)(view + 0x8);
    cam[1] = *(f32 *)(view + 0x18);
    cam[3] = 1.0f;
    cam[2] = *(f32 *)(view + 0x28);
    nf = (f32)n;
    g = nf;
    w = (g + g) * (1.0f - *(f32 *)(obj + 0xD4));
    if (Vec3_Dot(cam, (f32 *)dirv) < 0.0f) {
        Vec4_Set(corner0, -g - w, -g, 0.0f, 1.0f);
        Vec4_Set(corner1, g - (w + w), -g, 0.0f, 1.0f);
        Vec4_Set(corner2, w - g, g, 0.0f, 1.0f);
        Vec4_Set(corner3, g + w, g, 0.0f, 1.0f);
    } else {
        Vec4_Set(corner0, (w + w) - g, -g, 0.0f, 1.0f);
        Vec4_Set(corner1, g + w, -g, 0.0f, 1.0f);
        Vec4_Set(corner2, -g - w, g, 0.0f, 1.0f);
        Vec4_Set(corner3, g - w, g, 0.0f, 1.0f);
    }

    if (*(f32 *)(obj + 0x14) != 0.0f) {
        func_00128EF0();
        Vu0Cur_LoadIdentity();
        t = EftMath_WrapAngle(*(f32 *)(obj + 0x14));
        *(f32 *)(obj + 0x14) = t;
        Vu0Cur_RotateZ(t);
        Vu0Cur_MulVec4(corner0, corner0);
        Vu0Cur_MulVec4(corner1, corner1);
        Vu0Cur_MulVec4(corner2, corner2);
        Vu0Cur_MulVec4(corner3, corner3);
        func_00128F08();
    }

    if (obj[1] & 2) {
        Vec3_Set(corner0, (f32)proj[0] + corner0[0], ((f32)proj[1] + corner0[1]) - nf, (f32)proj[2]);
        Vec3_Set(corner1, (f32)proj[0] + corner1[0], ((f32)proj[1] + corner1[1]) - nf, (f32)proj[2]);
        Vec3_Set(corner2, (f32)proj[0] + corner2[0], ((f32)proj[1] + corner2[1]) - nf, (f32)proj[2]);
        Vec3_Set(corner3, (f32)proj[0] + corner3[0], ((f32)proj[1] + corner3[1]) - nf, (f32)proj[2]);
    } else {
        Vec3_Set(corner0, (f32)proj[0] + corner0[0], (f32)proj[1] + corner0[1], (f32)proj[2]);
        Vec3_Set(corner1, (f32)proj[0] + corner1[0], (f32)proj[1] + corner1[1], (f32)proj[2]);
        Vec3_Set(corner2, (f32)proj[0] + corner2[0], (f32)proj[1] + corner2[1], (f32)proj[2]);
        Vec3_Set(corner3, (f32)proj[0] + corner3[0], (f32)proj[1] + corner3[1], (f32)proj[2]);
    }

    if (func_001C2848((s32)corner0[0], (s32)corner0[1], (s32)corner0[2]) != 0) {
        return;
    }
    if (func_001C2848((s32)corner1[0], (s32)corner1[1], (s32)corner1[2]) != 0) {
        return;
    }
    if (func_001C2848((s32)corner2[0], (s32)corner2[1], (s32)corner2[2]) != 0) {
        return;
    }
    if (func_001C2848((s32)corner3[0], (s32)corner3[1], (s32)corner3[2]) != 0) {
        return;
    }

    p = D_00387AD8;
    D_00387AD8 = p + 0x90;
    *(u64 *)(p + 0x20) = 0x5C;
    *(u64 *)(p + 0x00) = 0xA0000008ULL;
    *(u64 *)(p + 0x10) = 0xE400000000008001ULL;
    *(u64 *)(p + 0x18) = 0x42142142142160ULL;
    PUT_COLOR_BYTES(p, 0x30);
    PUT_COLOR_BYTES(p, 0x48);
    PUT_COLOR_BYTES(p, 0x60);
    PUT_COLOR_BYTES(p, 0x78);
    PUT_CORNER(p, 0x40, corner0);
    PUT_CORNER(p, 0x58, corner1);
    PUT_CORNER(p, 0x70, corner2);
    PUT_CORNER(p, 0x88, corner3);

    u0 = (f32)*(s8 *)(obj + 0xC) * D_00385160;
    v0 = (f32)*(s8 *)(obj + 0xD) * D_00385160;
    u1 = u0 + (f32)*(s8 *)(obj + 0xE) * D_00385160;
    v1 = v0 + (f32)*(s8 *)(obj + 0xF) * D_00385160;
    if (obj[1] & 0x10) {
        t = u0;
        u0 = u1;
        u1 = t;
    }
    if (obj[1] & 0x20) {
        t = v0;
        v0 = v1;
        v1 = t;
    }
    *(f32 *)(p + 0x54) = v0;
    *(f32 *)(p + 0x68) = u0;
    *(f32 *)(p + 0x80) = u1;
    *(f32 *)(p + 0x84) = v1;
    *(f32 *)(p + 0x38) = u0;
    *(f32 *)(p + 0x3C) = v0;
    *(f32 *)(p + 0x50) = u1;
    *(f32 *)(p + 0x6C) = v1;
    *(u64 *)(p + 0x28) = *(u64 *)(*(u8 **)(obj + 8) + obj[3] * 16);

    sub = proj[2] >> 8;
    layer = obj[2];
    if (sub < 0) {
        node = D_00387AE0 + layer * 8;
    } else if (sub < 0x1000) {
        node = D_00387AE0 + (sub * 2 + layer) * 8;
    } else {
        node = D_00387AE0 + layer * 8 + 0xFFF0;
    }
    last = *(u8 **)(node + 4);
    *(u8 **)(last + 4) = p;
    *(u8 **)(node + 4) = p;
}
