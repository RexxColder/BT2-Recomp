#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u8 D_0036F080[];

extern void sceVu0RotTransPers(void *dst, void *m, void *src, s32 n);
extern void sceVu0UnitMatrix(f32 *m);
extern void sceVu0RotMatrixZ(f32 *dst, f32 *m, f32 ang);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void func_00312730(f32 *dst, s32 *src);
extern void func_00312668(void *dst, void *src, void *k);
extern void func_00312710(s32 *dst, f32 *src);
extern s32 func_001CBA68(s32 x, s32 y, s32 z);

/* float -> u32 style truncation (cvt.w.s with the 2^31 fix-up) */
static s32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (s32)(f - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)f;
}

/* Queues a rotated, tinted screen-space sprite (one GIF packet of 0x80 bytes) for the effect object `obj`
   (data at obj+0x38: world pos +0x10, rotation +0x6C, uv +0x90..0x9C, flags +0x40, layer byte via +0x34),
   half extent (w, h) * perspective scale, colour floats from `colour`, texture word `tex`. */
s32 func_001CBA98(u8 *obj, f32 *colourIn, u64 tex, f32 w, f32 h) {
    f32 colour[4];
    u8 *fx;
    u8 *layerp;
    f32 pt[4];
    f32 k[4];
    s32 scr[4];
    s32 ext[4];
    s32 ext2[4];
    f32 fv[4];
    f32 fv2[4];
    f32 mtx[16];
    f32 scale;
    s32 key;
    s32 ds, hw, hh;
    s32 c[8];
    s32 res;
    s32 z;
    s32 slot;
    u8 *pkt;
    u8 *ent;
    u8 *ret;
    u64 m = 0xFF000000FFFFFFFFull;
    f32 u0, v0, u1, v1;
    f32 val;

    __builtin_memcpy(colour, colourIn, 0x10);
    __builtin_memcpy(k, D_0036F080, 0x10);
    fx = *(u8 **)(obj + 0x38);
    layerp = *(u8 **)(fx + 0x34);
    pt[0] = *(f32 *)(fx + 0x10);
    pt[1] = *(f32 *)(fx + 0x14);
    pt[2] = *(f32 *)(fx + 0x18);
    pt[3] = 1.0f;
    scale = *(f32 *)(gBtlCamView + 0x224);
    sceVu0RotTransPers(scr, gBtlCamView + 0x100, pt, 1);
    key = scr[2] >> 8;

    val = scale * 4096.0f / (f32)scr[3];
    ds = f2u(val);
    hw = (u32)(f2u(w) * ds) >> 12;
    hh = (u32)(f2u(h) * ds) >> 12;
    if ((u32)hw < 2) {
        return 1;
    }
    if ((u32)hh < 2) {
        return 1;
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
    sceVu0RotMatrixZ(mtx, mtx, *(f32 *)(fx + 0x6C));
    sceVu0ApplyMatrix(fv, mtx, fv);
    sceVu0ApplyMatrix(fv2, mtx, fv2);
    func_00312668(fv, fv, k);
    func_00312668(fv2, fv2, k);
    func_00312710(ext, fv);
    func_00312710(ext2, fv2);

    c[0] = scr[0] - ext[0];
    c[1] = scr[1] - ext[1];
    res = func_001CBA68(c[0], c[1], scr[2]);
    if (res != 0) {
        return res;
    }
    c[2] = scr[0] + ext2[0];
    c[3] = scr[1] + ext2[1];
    res = func_001CBA68(c[2], c[3], scr[2]);
    if (res != 0) {
        return res;
    }
    c[4] = scr[0] - ext2[0];
    c[5] = scr[1] - ext2[1];
    res = func_001CBA68(c[4], c[5], scr[2]);
    if (res != 0) {
        return res;
    }
    c[6] = scr[0] + ext[0];
    c[7] = scr[1] + ext[1];
    res = func_001CBA68(c[6], c[7], scr[2]);
    if (res != 0) {
        return res;
    }

    if ((*(u32 *)(fx + 0x40) & 0x10) != 0) {
        scr[2] = 0xFFFFFF;
    }
    z = (scr[2] >> 8) << 8;
    u0 = *(f32 *)(fx + 0x90);
    v0 = *(f32 *)(fx + 0x98);
    u1 = *(f32 *)(fx + 0x94);
    v1 = *(f32 *)(fx + 0x9C);
    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    if (pkt == 0) {
        return scr[2] >> 8;
    }
    *(u64 *)(pkt + 0x00) = 0xA0000007ull;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
    *(u64 *)(pkt + 0x20) = 0x54;
    *(u64 *)(pkt + 0x18) = 0xF42424242160ull;
    pkt[0x30] = f2u(colour[0]);
    pkt[0x31] = f2u(colour[1]);
    pkt[0x32] = f2u(colour[2]);
    pkt[0x33] = f2u(colour[3]);
    *(u16 *)(pkt + 0x40) = c[0];
    *(u16 *)(pkt + 0x42) = c[1];
    *(u16 *)(pkt + 0x50) = c[2];
    *(u16 *)(pkt + 0x52) = c[3];
    *(u16 *)(pkt + 0x60) = c[4];
    *(u16 *)(pkt + 0x62) = c[5];
    *(u16 *)(pkt + 0x70) = c[6];
    *(u16 *)(pkt + 0x72) = c[7];
    *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & m) | ((u64)(z & 0xFFFFFF) << 32);
    *(u64 *)(pkt + 0x50) = (*(u64 *)(pkt + 0x50) & m) | ((u64)(z & 0xFFFFFF) << 32);
    *(u64 *)(pkt + 0x60) = (*(u64 *)(pkt + 0x60) & m) | ((u64)(z & 0xFFFFFF) << 32);
    *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & m) | ((u64)(z & 0xFFFFFF) << 32);
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(f32 *)(pkt + 0x48) = u0;
    *(f32 *)(pkt + 0x5C) = v0;
    *(f32 *)(pkt + 0x68) = u1;
    *(f32 *)(pkt + 0x6C) = v1;
    pkt[0x77] = 0xFF;
    *(u64 *)(pkt + 0x28) = tex;
    *(f32 *)(pkt + 0x38) = u0;
    *(f32 *)(pkt + 0x3C) = v0;
    *(f32 *)(pkt + 0x4C) = v1;
    *(f32 *)(pkt + 0x58) = u1;
    pkt[0x47] = 0xFF;
    pkt[0x57] = 0xFF;
    pkt[0x67] = 0xFF;

    slot = *layerp;
    if (key < 0) {
        ent = D_00387AE0 + (slot << 3);
    } else if (key < 0x1000) {
        ent = D_00387AE0 + ((key * 2 + slot) << 3);
    } else {
        ent = D_00387AE0 + (slot << 3) + 0xFFF0;
    }
    ret = *(u8 **)(ent + 4);
    *(u8 **)(ret + 4) = pkt;
    *(u8 **)(ent + 4) = pkt;
    return (s32)ret;
}
