#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u8 D_003435D0[];
extern f32 D_00385718;
extern f32 D_0038571C;
extern f32 D_00385720;
extern f32 D_00385724;

extern void sceVu0RotTransPers(void *dst, void *m, void *src, s32 n);
extern void sceVu0UnitMatrix(f32 *m);
extern void sceVu0RotMatrixZ(f32 *dst, f32 *m, f32 ang);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void func_00312730(f32 *dst, s32 *src);
extern void func_00312668(void *dst, void *src, void *k);
extern void func_00312710(s32 *dst, f32 *src);
extern s32 func_001F2A18(s32 x, s32 y, s32 z);

/* Rotated screen-space sprite (GIF packet, 0x80 bytes) at a projected world point, like 1F1868 but with an extra
   screen offset (offX, offY) scaled by the same depth factor, and per-corner uv (u0,v0)-(u1,v1). Returns 1 when
   an extent is under 2 pixels, the non-zero result of a rejected corner, else the previous list tail. */
s32 func_001F0EE8(s32 r, s32 g, s32 b, s32 a, s32 offX, s32 offY, s32 w, s32 h,
                  f32 x, f32 y, f32 z, f32 u0, f32 v0, f32 u1, f32 v1, f32 ang,
                  s32 unused, u32 size, s32 shift, s32 layer, u8 *tex) {
    s32 scr[4];
    f32 pt[4];
    s32 ext[16];
    f32 fv[16];
    f32 mtx[16];
    f32 scale;
    f32 sz;
    s32 depthScale;
    s32 hw, hh, ox, oy;
    s32 res;
    s32 k;
    s32 key;
    u8 *pkt;
    u8 *ent;
    u8 *ret;
    u64 m = 0xFF000000FFFFFFFFull;

    r &= 0xFF;
    g &= 0xFF;
    b &= 0xFF;
    a &= 0xFF;
    scale = *(f32 *)(gBtlCamView + 0x224);
    pt[0] = x;
    pt[1] = y;
    pt[2] = z;
    pt[3] = 1.0f;
    sceVu0RotTransPers(scr, gBtlCamView + 0x100, pt, 1);

    if ((s32)size < 0) {
        sz = (f32)((size & 1) | (size >> 1));
        sz = (sz + sz) * scale;
    } else {
        sz = (f32)(s32)size * scale;
    }
    sz = sz / (f32)scr[3];
    if (sz >= 2147483648.0f) {
        depthScale = (s32)(sz - 2147483648.0f) | (s32)0x80000000;
    } else {
        depthScale = (s32)sz;
    }
    hw = (u32)(w * depthScale) >> 12;
    hh = (u32)(h * depthScale) >> 12;
    if ((u32)hw < 2) {
        return 1;
    }
    if ((u32)hh < 2) {
        return 1;
    }

    if (D_00385718 < ang) {
        ang = ang - D_0038571C;
    } else if (ang < D_00385720) {
        ang = ang + D_00385724;
    }
    sceVu0UnitMatrix(mtx);
    sceVu0RotMatrixZ(mtx, mtx, ang);

    if (offX < 0) {
        ox = -(s32)((u32)(-offX * depthScale) >> 12);
    } else {
        ox = (u32)(offX * depthScale) >> 12;
    }
    if (offY < 0) {
        oy = -(s32)((u32)(-offY * depthScale) >> 12);
    } else {
        oy = (u32)(offY * depthScale) >> 12;
    }
    ext[0] = ox - hw;
    ext[1] = oy - hh;
    ext[2] = 0;
    ext[3] = 1;
    ext[4] = ox - hw;
    ext[5] = oy + hh;
    ext[6] = 0;
    ext[7] = 1;
    ext[8] = ox + hw;
    ext[9] = oy - hh;
    ext[10] = 0;
    ext[11] = 1;
    ext[12] = ox + hw;
    ext[13] = oy + hh;
    ext[14] = 0;
    ext[15] = 1;
    for (k = 0; k < 4; k++) {
        func_00312730(&fv[k * 4], &ext[k * 4]);
        sceVu0ApplyMatrix(&fv[k * 4], mtx, &fv[k * 4]);
        func_00312668(&fv[k * 4], &fv[k * 4], D_003435D0);
        func_00312710(&ext[k * 4], &fv[k * 4]);
    }

    for (k = 0; k < 4; k++) {
        res = func_001F2A18(scr[0] + ext[k * 4], scr[1] + ext[k * 4 + 1], scr[2]);
        if (res != 0) {
            return res;
        }
    }

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    scr[2] = (scr[2] >> 8) << 8;

    *(u64 *)(pkt + 0x20) = ((u64)((s64)(s8)shift << 9)) | 0x54;
    *(u64 *)(pkt + 0x28) = *(u64 *)tex;
    *(u64 *)(pkt + 0x00) = 0xA0000007ull;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
    *(u64 *)(pkt + 0x18) = (u64)(s64)(s32)((s32)(s8)shift << 4) + 0xF42424242160ull;
    pkt[0x30] = r;
    pkt[0x31] = g;
    pkt[0x33] = a;
    pkt[0x32] = b;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(f32 *)(pkt + 0x48) = u0;
    *(f32 *)(pkt + 0x5C) = v0;
    *(f32 *)(pkt + 0x68) = u1;
    *(f32 *)(pkt + 0x6C) = v1;
    *(f32 *)(pkt + 0x38) = u0;
    *(f32 *)(pkt + 0x3C) = v0;
    *(f32 *)(pkt + 0x4C) = v1;
    *(f32 *)(pkt + 0x58) = u1;

    for (k = 0; k < 4; k++) {
        u8 *q = pkt + 0x40 + k * 0x10;
        *(u16 *)(q + 0x0) = scr[0] + ext[k * 4];
        *(u16 *)(q + 0x2) = scr[1] + ext[k * 4 + 1];
        *(u64 *)q = (*(u64 *)q & m) | ((u64)(scr[2] & 0xFFFFFF) << 32);
        q[7] = 0xFF;
    }

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
