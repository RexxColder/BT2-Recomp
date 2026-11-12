#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern void sceVu0RotTransPers(void *dst, void *m, void *src, s32 n);
extern s32 func_001F2A18(s32 x, s32 y, s32 z);

/* Projects a world point and queues a screen-space sprite (GIF packet, 0x60 bytes) centred on it, sized by
   (w, h) * perspective scale. Skipped when the size is under 2 pixels or func_001F2A18 rejects a corner. */
s32 func_001F14D8(s32 r, s32 g, s32 b, s32 a, s32 w, s32 h, s32 uOfs, s32 vOfs,
                  f32 x, f32 y, f32 z,
                  s32 uSize, s32 vSize, s32 shift, s32 layer, s32 mulA, u8 *tex) {
    s32 scr[4];
    f32 pt[4];
    f32 scale;
    s32 depthScale;
    s32 hw, hh;
    s32 key;
    u8 *pkt;
    u8 *ent;
    u8 *ret;
    s32 v;
    s32 res;
    u64 m = 0xFF000000FFFFFFFFull;

    ret = gBtlCamView;
    scale = *(f32 *)(gBtlCamView + 0x224);
    if (w == 0 || h == 0) {
        return (s32)ret;
    }
    pt[3] = 1.0f;
    pt[0] = x;
    pt[1] = y;
    pt[2] = z;
    sceVu0RotTransPers(scr, gBtlCamView + 0x100, pt, 1);

    scale = scale * 4096.0f / (f32)scr[3];
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
    res = func_001F2A18(scr[0] - hw, scr[1] - hh, scr[2]);
    if (res != 0) {
        return res;
    }
    res = func_001F2A18(scr[0] - hw, scr[1] + hh, scr[2]);
    if (res != 0) {
        return res;
    }
    res = func_001F2A18(scr[0] + hw, scr[1] + hh, scr[2]);
    if (res != 0) {
        return res;
    }
    res = func_001F2A18(scr[0] + hw, scr[1] - hh, scr[2]);
    if (res != 0) {
        return res;
    }

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x60;
    v = *(s32 *)(*(u8 **)(tex + 8) + 0x14) * mulA;

    *(u64 *)(pkt + 0x20) = ((u64)((s64)(s8)shift << 9)) | 0x156;
    *(u64 *)(pkt + 0x00) = 0xA0000005ull;
    *(u64 *)(pkt + 0x28) = *(u64 *)tex + ((u64)(s64)v << 37);
    *(u64 *)(pkt + 0x10) = 0x8400000000008001ull;
    *(u64 *)(pkt + 0x18) = (u64)(s64)(s32)((s32)(s8)shift << 4) + 0xF4343160ull;
    pkt[0x30] = r;
    pkt[0x31] = g;
    pkt[0x32] = b;
    pkt[0x33] = a;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(u16 *)(pkt + 0x38) = uOfs << 4;
    *(u16 *)(pkt + 0x3A) = vOfs << 4;
    *(u16 *)(pkt + 0x48) = (uOfs + uSize) << 4;
    *(u16 *)(pkt + 0x4A) = (vOfs + vSize) << 4;
    *(u16 *)(pkt + 0x40) = scr[0] - hw;
    *(u16 *)(pkt + 0x42) = scr[1] - hh;
    *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & m) | ((u64)(scr[2] & 0xFFFFFF) << 32);
    pkt[0x47] = 0xFF;
    *(u16 *)(pkt + 0x50) = scr[0] + hw;
    *(u16 *)(pkt + 0x52) = scr[1] + hh;
    *(u64 *)(pkt + 0x50) = (*(u64 *)(pkt + 0x50) & m) | ((u64)(scr[2] & 0xFFFFFF) << 32);
    pkt[0x57] = 0xFF;

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
