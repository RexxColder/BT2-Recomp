#include "common.h"

extern u8 *gBtlCamView;
extern f32 D_00385708;
extern f32 D_0038570C;
extern f32 D_00385710;
extern f32 D_00385714;
extern u8 D_003435C0[];
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

void sceVu0RotTransPers(void *dst, void *m, void *src, s32 n);
void func_00312730(f32 *dst, s32 *src);
void func_00312710(s32 *dst, f32 *src);
void func_00312668(void *dst, void *src, void *k);
void sceVu0UnitMatrix(void *m);
void sceVu0RotMatrixZ(void *dst, void *src, f32 ang);
void sceVu0ApplyMatrix(void *dst, void *m, void *v);
s32 func_001F2A18(s32 x, s32 y, s32 z);

/* float -> u32 style truncation (cvt.w.s with the 2^31 fix-up) */
static u32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (u32)((s32)(f - 2147483648.0f) | (s32)0x80000000);
    }
    return (u32)(s32)f;
}

/* Projects the world point (px,py,pz), scales the half sizes (w,h) by camera zoom / depth and queues a sprite
   (4 vertices rotated by angle) as a GIF packet of 0x80 bytes, if all four corners pass func_001F2A18.
   Packet vertices: sprite corners (-A), (+B), (-B), (+A) with A = (hw, hh), B = (-hw, hh) rotated. */
void func_001F0958(u8 r, u8 g, u8 b, u8 a, u32 w, u32 h, u32 unused6, u32 num,
                   s8 flag, s32 base, u64 *tex, s32 key,
                   f32 px, f32 py, f32 pz, f32 u0, f32 v0, f32 u1, f32 v1, f32 angle) {
    s32 scr[4];
    s32 A[4];
    s32 B[4];
    f32 pt[4];
    f32 fA[4];
    f32 fB[4];
    u8 rot[0xb0];   /* tamano de locales del original (antes 0x40) */
    f32 camZoom;
    u32 hw;
    u32 hh;
    u32 mulv;
    u8 *pkt;
    u8 *ent;
    u8 *prev;
    u64 m = 0xFF000000FFFFFFFFull;
    u64 zbits;
    u64 hdr;
    s64 sf;

    camZoom = *(f32 *)(gBtlCamView + 0x224);
    pt[0] = px;
    pt[1] = py;
    pt[2] = pz;
    pt[3] = 1.0f;
    sceVu0RotTransPers(scr, gBtlCamView + 0x100, pt, 1);

    mulv = f2u(((f32)num * camZoom) / (f32)scr[3]);
    hw = (w * mulv) >> 12;
    hh = (h * mulv) >> 12;
    if (hw < 2) {
        return;
    }
    if (hh < 2) {
        return;
    }

    if (D_00385708 < angle) {
        angle = angle - D_0038570C;
    } else if (angle < D_00385710) {
        angle = angle + D_00385714;
    }

    A[0] = (s32)hw;
    A[1] = (s32)hh;
    A[2] = 0;
    A[3] = 1;
    B[0] = -(s32)hw;
    B[1] = (s32)hh;
    B[2] = 0;
    B[3] = 1;
    func_00312730(fA, A);
    func_00312730(fB, B);
    sceVu0UnitMatrix(rot);
    sceVu0RotMatrixZ(rot, rot, angle);
    sceVu0ApplyMatrix(fA, rot, fA);
    sceVu0ApplyMatrix(fB, rot, fB);
    func_00312668(fA, fA, D_003435C0);
    func_00312668(fB, fB, D_003435C0);
    func_00312710(A, fA);
    func_00312710(B, fB);

    if (func_001F2A18(scr[0] - A[0], scr[1] - A[1], scr[2]) != 0) {
        return;
    }
    if (func_001F2A18(scr[0] + B[0], scr[1] + B[1], scr[2]) != 0) {
        return;
    }
    if (func_001F2A18(scr[0] - B[0], scr[1] - B[1], scr[2]) != 0) {
        return;
    }
    if (func_001F2A18(scr[0] + A[0], scr[1] + A[1], scr[2]) != 0) {
        return;
    }

    sf = (s64)flag;
    scr[2] = (scr[2] >> 8) << 8;
    zbits = (u64)(scr[2] & 0xFFFFFF) << 32;

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    hdr = (u64)(sf << 9) | 0x40 | 0x14;
    *(u64 *)(pkt + 0x20) = hdr;
    *(u64 *)(pkt + 0x28) = *tex;
    *(u64 *)(pkt + 0x00) = 0xA0000007ull;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
    *(u64 *)(pkt + 0x18) = (u64)((s64)(s32)(sf << 4)) + 0xF42424242160ull;
    pkt[0x30] = r;
    pkt[0x32] = b;
    pkt[0x31] = g;
    pkt[0x33] = a;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(f32 *)(pkt + 0x48) = u0;
    *(f32 *)(pkt + 0x5C) = v0;
    *(f32 *)(pkt + 0x68) = u1;
    *(f32 *)(pkt + 0x6C) = v1;
    *(f32 *)(pkt + 0x38) = u0;
    *(f32 *)(pkt + 0x3C) = v0;
    *(f32 *)(pkt + 0x4C) = v1;
    *(f32 *)(pkt + 0x58) = u1;

    *(u16 *)(pkt + 0x40) = (u16)(scr[0] - A[0]);
    *(u16 *)(pkt + 0x42) = (u16)(scr[1] - A[1]);
    *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & m) | zbits;
    pkt[0x47] = 0xFF;
    *(u16 *)(pkt + 0x50) = (u16)(scr[0] + B[0]);
    *(u16 *)(pkt + 0x52) = (u16)(scr[1] + B[1]);
    *(u64 *)(pkt + 0x50) = (*(u64 *)(pkt + 0x50) & m) | zbits;
    pkt[0x57] = 0xFF;
    *(u16 *)(pkt + 0x60) = (u16)(scr[0] - B[0]);
    *(u16 *)(pkt + 0x62) = (u16)(scr[1] - B[1]);
    *(u64 *)(pkt + 0x60) = (*(u64 *)(pkt + 0x60) & m) | zbits;
    pkt[0x67] = 0xFF;
    *(u16 *)(pkt + 0x70) = (u16)(scr[0] + A[0]);
    *(u16 *)(pkt + 0x72) = (u16)(scr[1] + A[1]);
    *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & m) | zbits;
    pkt[0x77] = 0xFF;

    if (key < 0) {
        ent = D_00387AE0 + base * 8;
    } else if (key < 0x1000) {
        ent = D_00387AE0 + ((key * 2 + base) << 3);
    } else {
        ent = D_00387AE0 + base * 8 + 0xFFF0;
    }
    prev = *(u8 **)(ent + 4);
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(ent + 4) = pkt;
}
