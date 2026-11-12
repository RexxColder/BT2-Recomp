#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u8 D_003435E0[];
extern f32 D_00385728;
extern f32 D_0038572C;
extern f32 D_00385730;
extern f32 D_00385734;

extern void sceVu0RotTransPers(void *dst, void *m, void *src, s32 n);
extern void sceVu0UnitMatrix(f32 *m);
extern void sceVu0RotMatrixZ(f32 *dst, f32 *m, f32 ang);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void func_00312730(f32 *dst, s32 *src);
extern void func_00312668(void *dst, void *src, void *k);
extern void func_00312710(s32 *dst, f32 *src);
extern s32 func_001F2A18(s32 x, s32 y, s32 z);

/* Rotated screen-space sprite (GIF packet, 0x80 bytes) centred on a projected world point; half extent
   (w, h) * size / depth, rotated by ang. Skipped when an extent is under 2 pixels or a corner is rejected. */
s32 func_001F1868(s32 r, s32 g, s32 b, s32 a, u32 w, u32 h, s32 unused, u32 size,
                  f32 x, f32 y, f32 z, f32 u0, f32 v0, f32 u1, f32 v1, f32 ang,
                  s32 shift, s32 layer, s32 mulA, u8 *tex) {
    s32 scr[4];
    f32 pt[4];
    s32 ext[4];
    s32 ext2[4];
    f32 fv[4];
    f32 fv2[4];
    f32 mtx[16];
    f32 scale;
    s32 depthScale;
    s32 hw, hh;
    s32 key;
    s32 res;
    u8 *pkt;
    u8 *ent;
    u8 *ret;
    s32 v;
    u64 m = 0xFF000000FFFFFFFFull;

    scale = *(f32 *)(gBtlCamView + 0x224);
    pt[0] = x;
    pt[1] = y;
    pt[2] = z;
    pt[3] = 1.0f;
    sceVu0RotTransPers(scr, gBtlCamView + 0x100, pt, 1);

    scale = (f32)size * scale / (f32)scr[3];
    if (scale >= 2147483648.0f) {
        depthScale = (s32)(scale - 2147483648.0f) | (s32)0x80000000;
    } else {
        depthScale = (s32)scale;
    }
    hw = (u32)(w * depthScale) >> 12;
    hh = (u32)(h * depthScale) >> 12;
    if ((u32)hw < 2) {
        return 1;
    }
    if ((u32)hh < 2) {
        return 1;
    }
    if (D_00385728 < ang) {
        ang = ang - D_0038572C;
    } else if (ang < D_00385730) {
        ang = ang + D_00385734;
    }
    ext[0] = hw;
    ext[1] = hh;
    ext[2] = 0;
    ext[3] = 1;
    ext2[0] = -hw;
    ext2[1] = hh;
    ext2[2] = 0;
    ext2[3] = 1;
    func_00312730(fv, ext);
    func_00312730(fv2, ext2);
    sceVu0UnitMatrix(mtx);
    sceVu0RotMatrixZ(mtx, mtx, ang);
    sceVu0ApplyMatrix(fv, mtx, fv);
    sceVu0ApplyMatrix(fv2, mtx, fv2);
    func_00312668(fv, fv, D_003435E0);
    func_00312668(fv2, fv2, D_003435E0);
    func_00312710(ext, fv);
    func_00312710(ext2, fv2);

    res = func_001F2A18(scr[0] - ext[0], scr[1] - ext[1], scr[2]);
    if (res != 0) {
        return res;
    }
    res = func_001F2A18(scr[0] + ext2[0], scr[1] + ext2[1], scr[2]);
    if (res != 0) {
        return res;
    }
    res = func_001F2A18(scr[0] - ext2[0], scr[1] - ext2[1], scr[2]);
    if (res != 0) {
        return res;
    }
    res = func_001F2A18(scr[0] + ext[0], scr[1] + ext[1], scr[2]);
    if (res != 0) {
        return res;
    }

    pkt = D_00387AD8;
    scr[2] = (scr[2] >> 8) << 8;
    D_00387AD8 = pkt + 0x80;
    v = *(s32 *)(*(u8 **)(tex + 8) + 0x14) * mulA;

    *(u64 *)(pkt + 0x20) = ((u64)((s64)(s8)shift << 9)) | 0x54;
    *(u64 *)(pkt + 0x00) = 0xA0000007ull;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
    *(u64 *)(pkt + 0x18) = (u64)(s64)(s32)((s32)(s8)shift << 4) + 0xF42424242160ull;
    *(u64 *)(pkt + 0x28) = *(u64 *)tex + ((u64)(s64)v << 37);
    pkt[0x30] = r;
    pkt[0x31] = g;
    pkt[0x32] = b;
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

    *(u16 *)(pkt + 0x40) = scr[0] - ext[0];
    *(u16 *)(pkt + 0x42) = scr[1] - ext[1];
    *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & m) | ((u64)(scr[2] & 0xFFFFFF) << 32);
    pkt[0x47] = 0xFF;
    *(u16 *)(pkt + 0x50) = scr[0] + ext2[0];
    *(u16 *)(pkt + 0x52) = scr[1] + ext2[1];
    *(u64 *)(pkt + 0x50) = (*(u64 *)(pkt + 0x50) & m) | ((u64)(scr[2] & 0xFFFFFF) << 32);
    pkt[0x57] = 0xFF;
    *(u16 *)(pkt + 0x60) = scr[0] - ext2[0];
    *(u16 *)(pkt + 0x62) = scr[1] - ext2[1];
    *(u64 *)(pkt + 0x60) = (*(u64 *)(pkt + 0x60) & m) | ((u64)(scr[2] & 0xFFFFFF) << 32);
    pkt[0x67] = 0xFF;
    *(u16 *)(pkt + 0x70) = scr[0] + ext[0];
    *(u16 *)(pkt + 0x72) = scr[1] + ext[1];
    *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & m) | ((u64)(scr[2] & 0xFFFFFF) << 32);
    pkt[0x77] = 0xFF;

    key = scr[2] >> 8;
    if (key < 0) {
        ent = D_00387AE0 + (layer << 3);
    } else if (key < 0x1000) {
        ent = D_00387AE0 + ((2 * key + layer) << 3);
    } else {
        ent = D_00387AE0 + (layer << 3) + 0xFFF0;
    }
    ret = *(u8 **)(ent + 4);
    *(u8 **)(ret + 4) = pkt;
    *(u8 **)(ent + 4) = pkt;
    return (s32)ret;
}
