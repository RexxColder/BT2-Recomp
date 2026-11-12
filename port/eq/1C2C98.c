#include "common.h"

extern u8 *gBtlCamView;
extern f32 D_0038514C;
extern f32 D_00385150;
extern f32 D_00385154;
extern f32 D_00385158;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

s32 func_00129F60(s32 *a0, f32 *a1, f32 *a2, s32 a3);
s32 func_001C2848(s32 a, s32 b, s32 c);

/* float -> u32 style truncation (cvt.w.s with the 2^31 fix-up) */
static u32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (u32)((s32)(f - 2147483648.0f) | (s32)0x80000000);
    }
    return (u32)(s32)f;
}

/* Queues one sprite-like GIF packet (0x60 bytes) for a 2D quad of half-size radius (screen space),
   if all four corners pass the visibility test func_001C2848. */
void func_001C2C98(u8 *q) {
    s32 scr[4];
    f32 camScale;
    f32 ratio;
    u32 s4;
    u32 prod;
    s32 x;
    s32 y;
    s32 z;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    f32 base;
    u32 w0 = *(u32 *)(q + 0xD4);
    u32 w1 = *(u32 *)(q + 0xD8);
    u32 c0;
    u32 c1;
    u32 c2;
    u32 c3;
    u32 tmp;
    u8 *pkt;
    u8 *ent;
    u8 *prev;
    s32 key;
    u64 m = 0xFF000000FFFFFFFFull;
    f32 fa;
    f32 fb;

    s4 = f2u(*(f32 *)(q + 0x10));
    camScale = *(f32 *)(gBtlCamView + 0x224);
    if (s4 == 0) {
        return;
    }
    func_00129F60(scr, (f32 *)(gBtlCamView + 0x100), (f32 *)(q + 0x20), 1);
    ratio = (camScale * 4096.0f) / (f32)scr[3];
    prod = (u32)s4 * f2u(ratio);
    s4 = prod >> 12;
    if (s4 < 2) {
        return;
    }
    x = scr[0];
    y = scr[1];
    z = scr[2];
    x0 = x - (s32)s4;
    y0 = y - (s32)s4;
    if (func_001C2848(x0, y0, z) != 0) {
        return;
    }
    y1 = y + (s32)s4;
    if (func_001C2848(x0, y1, z) != 0) {
        return;
    }
    x1 = x + (s32)s4;
    if (func_001C2848(x1, y1, z) != 0) {
        return;
    }
    if (func_001C2848(x1, y0, z) != 0) {
        return;
    }

    base = (f32)(s8)q[0xC] * D_0038514C;
    c0 = f2u(base * (f32)w0);
    base = (f32)(s8)q[0xD] * D_00385150;
    c1 = f2u(base * (f32)w1);
    fa = (f32)(s8)q[0xC] * D_00385154;
    fb = (f32)(s8)q[0xE] * D_00385154;
    c2 = f2u((fa + fb) * (f32)w0);
    fa = (f32)(s8)q[0xD] * D_00385158;
    fb = (f32)(s8)q[0xF] * D_00385158;
    c3 = f2u((fa + fb) * (f32)w1);

    if ((q[1] & 0x10) != 0) {
        tmp = c0;
        c0 = c2;
        c2 = tmp;
    }
    if ((q[1] & 0x20) != 0) {
        tmp = c1;
        c1 = c3;
        c3 = tmp;
    }

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x60;
    *(u64 *)(pkt + 0x20) = 0x156;
    *(u64 *)(pkt + 0x28) = *(u64 *)(*(u8 **)(q + 8) + q[3] * 16);
    *(u64 *)(pkt + 0x00) = 0xA0000005ull;
    *(u64 *)(pkt + 0x10) = 0x8400000000008001ull;
    *(u64 *)(pkt + 0x18) = 0xF4343160ull;
    pkt[0x30] = q[0x18];
    pkt[0x31] = q[0x19];
    pkt[0x32] = q[0x1A];
    *(f32 *)(pkt + 0x34) = 1.0f;
    pkt[0x33] = q[0x1B];
    *(u16 *)(pkt + 0x38) = (u16)(c0 << 4);
    *(u16 *)(pkt + 0x3A) = (u16)(c1 << 4);
    *(u16 *)(pkt + 0x48) = (u16)(c2 << 4);
    *(u16 *)(pkt + 0x4A) = (u16)(c3 << 4);
    *(u16 *)(pkt + 0x40) = (u16)(scr[0] - (s32)s4);
    *(u16 *)(pkt + 0x42) = (u16)(scr[1] - (s32)s4);
    *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & m) | ((u64)(scr[2] & 0xFFFFFF) << 32);
    pkt[0x47] = 0xFF;
    *(u16 *)(pkt + 0x50) = (u16)(scr[0] + (s32)s4);
    *(u16 *)(pkt + 0x52) = (u16)(scr[1] + (s32)s4);
    *(u64 *)(pkt + 0x50) = (*(u64 *)(pkt + 0x50) & m) | ((u64)(scr[2] & 0xFFFFFF) << 32);
    pkt[0x57] = 0xFF;

    key = scr[2] >> 8;
    if (key < 0) {
        ent = D_00387AE0 + q[2] * 8;
    } else if (key < 0x1000) {
        ent = D_00387AE0 + ((key * 2 + q[2]) << 3);
    } else {
        ent = D_00387AE0 + q[2] * 8 + 0xFFF0;
    }
    prev = *(u8 **)(ent + 4);
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(ent + 4) = pkt;
}
