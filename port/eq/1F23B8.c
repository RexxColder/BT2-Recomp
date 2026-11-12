#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_00385748, D_0038574C, D_00385750, D_00385754;

extern void func_00312650(u8 *dst, u8 *m, u8 *v);
extern void sceVu0Normalize(u8 *dst, u8 *src);
extern void func_001F2A48(u8 *dst, u8 *src, f32 ang);
extern void sceVu0ApplyMatrix(u8 *dst, u8 *m, u8 *v);
extern void sceVu0RotTransPers(u8 *dst, u8 *m, u8 *src, s32 n);
extern void func_00312680(u8 *dst, u8 *src, f32 s);

/* Queues one camera-facing textured quad (4 projected corners, one 0x90-byte GIF packet). Colour is (r,g,b,a)
   (a0..a3), centre (px,py,pz) (f12..f14), half extents from the u32 sizes a4,a5,a7 and f15..f16 scaled by
   a7 / 2^16, uv corners (u0,v0)=(f18,f19), (u1,v1)=(s0,s1). The packet goes into ordering-table slot
   (depth >> 8) of layer `layer`; `tex` points at the 8-byte texture word. */
void func_001F23B8(u8 r, u8 g, u8 b, u8 a, u32 w, u32 h, u32 unused, u32 size,
                   f32 px, f32 py, f32 pz, f32 ex, f32 ey, f32 dist, f32 u0, f32 v0,
                   f32 u1, f32 v1, f32 zoff, s32 sl, s32 layer, u8 whiteOut, u64 *tex) {
    u8 sp[0x150];   /* tamano de locales del original (antes 0x140) */
    f32 f20;
    f32 sc;
    f32 A, B, C, D;
    s32 i;
    u8 *pkt;
    u8 *slot;
    u8 *slot2;
    s32 key;
    s32 sl8 = (s8)sl;

    *(f32 *)(sp + 0xD0) = px;
    *(f32 *)(sp + 0xD4) = py;
    *(f32 *)(sp + 0xD8) = pz;
    *(f32 *)(sp + 0xA4) = v0;
    *(f32 *)(sp + 0xB0) = u0;
    *(f32 *)(sp + 0xC0) = u1;
    *(f32 *)(sp + 0xC4) = v1;
    *(f32 *)(sp + 0xDC) = 1.0f;
    *(f32 *)(sp + 0xC8) = 1.0f;
    *(f32 *)(sp + 0x90) = u0;
    *(f32 *)(sp + 0x94) = v0;
    *(f32 *)(sp + 0x98) = 1.0f;
    *(s32 *)(sp + 0x9C) = 0;
    *(f32 *)(sp + 0xA0) = u1;
    *(f32 *)(sp + 0xA8) = 1.0f;
    *(s32 *)(sp + 0xAC) = 0;
    *(f32 *)(sp + 0xB4) = v1;
    *(f32 *)(sp + 0xB8) = 1.0f;
    *(s32 *)(sp + 0xBC) = 0;
    *(s32 *)(sp + 0xCC) = 0;

    f20 = zoff + D_00385748;
    if (D_00385748 < f20) {
        f20 = f20 - D_0038574C;
    } else if (f20 < D_00385750) {
        f20 = f20 + D_00385754;
    }

    func_00312650(sp + 0xE0, gBtlCamView + 0x1F0, sp + 0xD0);
    sceVu0Normalize(sp + 0xE0, sp + 0xE0);
    func_001F2A48(sp + 0xF0, sp + 0xE0, f20);
    *(f32 *)(sp + 0x120) = px - *(f32 *)(sp + 0xE0) * dist;
    *(f32 *)(sp + 0x124) = py - *(f32 *)(sp + 0xE4) * dist;
    *(f32 *)(sp + 0x128) = pz - *(f32 *)(sp + 0xE8) * dist;
    *(f32 *)(sp + 0x12C) = *(f32 *)(sp + 0xDC);

    sc = (f32)size * 0.000244140625f * 0.0625f;
    A = (f32)w * sc;
    B = (f32)h * sc;
    C = ey * sc;
    D = ex * sc;
    f20 = 1.0f;

    *(s32 *)(sp + 0x58) = 0;
    *(f32 *)(sp + 0x5C) = 1.0f;
    *(s32 *)(sp + 0x68) = 0;
    *(f32 *)(sp + 0x6C) = 1.0f;
    *(s32 *)(sp + 0x78) = 0;
    *(f32 *)(sp + 0x7C) = 1.0f;
    *(s32 *)(sp + 0x88) = 0;
    *(f32 *)(sp + 0x8C) = 1.0f;
    *(f32 *)(sp + 0x80) = A + D;
    *(f32 *)(sp + 0x84) = B + C;
    *(f32 *)(sp + 0x70) = D - A;
    *(f32 *)(sp + 0x74) = B + C;
    *(f32 *)(sp + 0x64) = C - B;
    *(f32 *)(sp + 0x60) = A + D;
    *(f32 *)(sp + 0x50) = D - A;
    *(f32 *)(sp + 0x54) = C - B;
    sceVu0ApplyMatrix(sp + 0x50, sp + 0xF0, sp + 0x50);
    sceVu0ApplyMatrix(sp + 0x60, sp + 0xF0, sp + 0x60);
    sceVu0ApplyMatrix(sp + 0x70, sp + 0xF0, sp + 0x70);
    sceVu0ApplyMatrix(sp + 0x80, sp + 0xF0, sp + 0x80);

    for (i = 0; i < 4; i++) {
        sceVu0RotTransPers(sp + 16 * i, gBtlCamView + 0x100, sp + 0x50 + 16 * i, 1);
        *(f32 *)(sp + 0x130 + 4 * i) = f20 / (f32)*(s32 *)(sp + 0xC + 16 * i);
        if (*(u32 *)(sp + 16 * i) > 0xFFF0) {
            return;
        }
        if (*(u32 *)(sp + 4 + 16 * i) > 0xFFF0) {
            return;
        }
        if (*(s32 *)(sp + 8 + 16 * i) < 0) {
            return;
        }
        if (whiteOut != 0) {
            *(s32 *)(sp + 8 + 16 * i) = 0xFFFFFF;
        }
        func_00312680(sp + 0x90 + 16 * i, sp + 0x90 + 16 * i, *(f32 *)(sp + 0x130 + 4 * i));
    }
    sceVu0RotTransPers(sp + 0x40, gBtlCamView + 0x100, sp + 0xD0, 1);

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x90;
    *(s64 *)(pkt + 0x20) = ((s64)sl8 << 9) | 0x5C;
    *(u64 *)(pkt + 0x00) = 0xA0000008ull;
    *(u64 *)(pkt + 0x10) = 0xE400000000008001ull;
    *(s64 *)(pkt + 0x18) = (s64)sl8 * 16 + 0x42142142142160ll;
    for (i = 0; i < 4; i++) {
        u8 *p = pkt + 0x30 + 0x18 * i;
        p[0] = r;
        p[1] = g;
        p[2] = b;
        p[3] = a;
        *(f32 *)(p + 4) = *(f32 *)(sp + 0x98 + 16 * i);
        *(f32 *)(p + 8) = *(f32 *)(sp + 0x90 + 16 * i);
        *(f32 *)(p + 12) = *(f32 *)(sp + 0x94 + 16 * i);
        *(u16 *)(p + 0x10) = *(u16 *)(sp + 16 * i);
        *(u16 *)(p + 0x12) = *(u16 *)(sp + 4 + 16 * i);
        *(u64 *)(p + 0x10) = (*(u64 *)(p + 0x10) & 0xFF000000FFFFFFFFull) |
                             ((u64)(*(u32 *)(sp + 8 + 16 * i) & 0xFFFFFF) << 32);
        p[0x17] = 0xFF;
    }
    *(u64 *)(pkt + 0x28) = *tex;

    key = *(s32 *)(sp + 0x48) >> 8;
    if (key < 0) {
        slot = D_00387AE0 + layer * 8;
        slot2 = *(u8 **)(slot + 4);
    } else if (key < 0x1000) {
        slot = D_00387AE0 + (key * 2 + layer) * 8;
        slot2 = *(u8 **)(slot + 4);
    } else {
        slot = D_00387AE0 + layer * 8 + 0xFFF0;
        slot2 = *(u8 **)(slot + 4);
    }
    *(u8 **)(slot2 + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
}
