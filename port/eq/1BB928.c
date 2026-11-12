#include "common.h"

extern void sceVu0RotTransPers(void *dst, void *m, void *src, s32 n);
extern void func_00312730(f32 *dst, s32 *src);
extern void sceVu0UnitMatrix(void *m);
extern void sceVu0RotMatrixZ(void *d, void *s, f32 angle);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void func_00312668(void *dst, void *src, void *k);
extern void func_00312710(s32 *dst, f32 *src);
extern s32 func_001BB8F8(s32 x, s32 y, s32 z);

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u8 D_0036EF20[] __attribute__((section(".data")));

static u32 FloatToU32(f32 x) {
    if (x >= 2147483648.0f) {
        return (u32)(s32)(x - 2147483648.0f) | 0x80000000;
    }
    return (u32)(s32)x;
}

/* Camera-facing sprite: projects the centre, builds the four rotated corners, rejects off screen ones, queues a packet. */
s32 func_001BB928(u8 *obj, u8 *eft, u8 *color_in, u64 tex, f32 w, f32 h) {
    u8 sp[0xf0];   /* tamano de locales del original (antes 0xe8) */
    f32 *color = (f32 *)(sp + 0x00);
    f32 camScale;
    s32 z8;
    s32 zq;
    s32 ot;
    u32 sx;
    u32 sy;
    u32 q;
    s32 x;
    s32 y;
    s32 z;
    s32 ax;
    s32 ay;
    s32 bx;
    s32 by;
    s32 c0x, c0y, c1x, c1y, c2x, c2y, c3x, c3y;
    s32 r;
    u8 *pkt;
    u8 *slot;
    u8 *node;
    s32 i;
    u32 zf;
    f32 ru0, rv0, ru1, rv1;

    *(u64 *)(sp + 0x00) = *(u64 *)(color_in + 0);
    *(u64 *)(sp + 0x08) = *(u64 *)(color_in + 8);
    *(u64 *)(sp + 0x50) = *(u64 *)(D_0036EF20 + 0);
    *(u64 *)(sp + 0x58) = *(u64 *)(D_0036EF20 + 8);
    *(f32 *)(sp + 0x60) = *(f32 *)(eft + 0x80);
    *(f32 *)(sp + 0x64) = *(f32 *)(eft + 0x84);
    *(f32 *)(sp + 0x68) = *(f32 *)(eft + 0x88);
    camScale = *(f32 *)(gBtlCamView + 0x224);
    *(f32 *)(sp + 0x6C) = 1.0f;
    sceVu0RotTransPers(sp + 0x90, gBtlCamView + 0x100, sp + 0x60, 1);

    z8 = *(s32 *)(sp + 0x98) >> 8;
    ot = *(u8 *)(eft + 5);
    sx = FloatToU32(w * 32.0f);
    sy = FloatToU32(h * 32.0f);
    q = FloatToU32(camScale * 4096.0f / (f32)*(s32 *)(sp + 0x9C));
    sx = (sx * q) >> 12;
    sy = (sy * q) >> 12;
    if (sx < 2) return 1;
    if (sy < 2) return 1;

    *(s32 *)(sp + 0xB0) = -(s32)sx;
    *(s32 *)(sp + 0xB4) = sy;
    *(s32 *)(sp + 0xBC) = 1;
    *(s32 *)(sp + 0xA4) = sy;
    *(s32 *)(sp + 0xAC) = 1;
    *(s32 *)(sp + 0xA0) = sx;
    *(s32 *)(sp + 0xA8) = 0;
    *(s32 *)(sp + 0xB8) = 0;
    func_00312730((f32 *)(sp + 0x70), (s32 *)(sp + 0xA0));
    func_00312730((f32 *)(sp + 0x80), (s32 *)(sp + 0xB0));
    sceVu0UnitMatrix(sp + 0x10);
    sceVu0RotMatrixZ(sp + 0x10, sp + 0x10, *(f32 *)(eft + 0x44));
    sceVu0ApplyMatrix(sp + 0x70, sp + 0x10, sp + 0x70);
    sceVu0ApplyMatrix(sp + 0x80, sp + 0x10, sp + 0x80);
    func_00312668(sp + 0x70, sp + 0x70, sp + 0x50);
    func_00312668(sp + 0x80, sp + 0x80, sp + 0x50);
    func_00312710((s32 *)(sp + 0xA0), (f32 *)(sp + 0x70));
    func_00312710((s32 *)(sp + 0xB0), (f32 *)(sp + 0x80));

    x = *(s32 *)(sp + 0x90);
    ax = *(s32 *)(sp + 0xA0);
    y = *(s32 *)(sp + 0x94);
    ay = *(s32 *)(sp + 0xA4);
    z = *(s32 *)(sp + 0x98);
    c0x = x - ax;
    c0y = y - ay;
    r = func_001BB8F8(c0x, c0y, z);
    if (r != 0) return r;
    bx = *(s32 *)(sp + 0xB0);
    by = *(s32 *)(sp + 0xB4);
    c1x = x + bx;
    c1y = y + by;
    r = func_001BB8F8(c1x, c1y, z);
    if (r != 0) return r;
    c2x = x - bx;
    c2y = y - by;
    r = func_001BB8F8(c2x, c2y, z);
    if (r != 0) return r;
    c3x = x + ax;
    c3y = y + ay;
    r = func_001BB8F8(c3x, c3y, z);
    if (r != 0) return r;

    if (*(u32 *)(obj + 0x60) & 0x20) {
        z = 0xFFFFFF;
        *(s32 *)(sp + 0x98) = z;
    }
    pkt = D_00387AD8;
    zq = z >> 8;
    zf = (u32)(zq << 8);
    ru0 = *(f32 *)(eft + 0xD0);
    rv0 = *(f32 *)(eft + 0xD8);
    ru1 = *(f32 *)(eft + 0xD4);
    rv1 = *(f32 *)(eft + 0xDC);
    D_00387AD8 = pkt + 0x80;
    if (pkt == NULL) return zq;

    *(u64 *)(pkt + 0x00) = 0xA0000007ULL;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ULL;
    *(u64 *)(pkt + 0x20) = 0x54;
    *(u64 *)(pkt + 0x18) = 0xF42424242160ULL;
    *(u8 *)(pkt + 0x30) = (u8)FloatToU32(color[0]);
    *(u8 *)(pkt + 0x31) = (u8)FloatToU32(color[1]);
    *(u8 *)(pkt + 0x32) = (u8)FloatToU32(color[2]);
    *(u8 *)(pkt + 0x33) = (u8)FloatToU32(color[3]);
    *(u16 *)(pkt + 0x40) = (u16)c0x;
    *(u16 *)(pkt + 0x42) = (u16)c0y;
    *(u16 *)(pkt + 0x50) = (u16)c1x;
    *(u16 *)(pkt + 0x52) = (u16)c1y;
    *(u16 *)(pkt + 0x60) = (u16)c2x;
    *(u16 *)(pkt + 0x62) = (u16)c2y;
    *(u16 *)(pkt + 0x70) = (u16)c3x;
    *(u16 *)(pkt + 0x72) = (u16)c3y;
    for (i = 0; i < 4; i++) {
        *(u32 *)(pkt + 0x44 + i * 0x10) = (zf & 0xFFFFFF) | 0xFF000000;
    }
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(f32 *)(pkt + 0x48) = ru0;
    *(f32 *)(pkt + 0x5C) = rv0;
    *(f32 *)(pkt + 0x68) = ru1;
    *(f32 *)(pkt + 0x6C) = rv1;
    *(u64 *)(pkt + 0x28) = tex;
    *(f32 *)(pkt + 0x38) = ru0;
    *(f32 *)(pkt + 0x3C) = rv0;
    *(f32 *)(pkt + 0x4C) = rv1;
    *(f32 *)(pkt + 0x58) = ru1;

    if (z8 < 0) {
        slot = D_00387AE0 + ot * 8;
        node = *(u8 **)(slot + 4);
    } else if (z8 < 0x1000) {
        slot = D_00387AE0 + (z8 * 2 + ot) * 8;
        node = *(u8 **)(slot + 4);
    } else {
        slot = D_00387AE0 + ot * 8 + 0xFFF0;
        node = *(u8 **)(slot + 4);
    }
    *(u8 **)(node + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
    return (s32)node;
}
