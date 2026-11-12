#include "common.h"

extern void sceVu0RotTransPers(void *dst, void *m, void *src, s32 n);
extern void Vec3_Add(void *dst, void *a, void *b);
extern void func_00129C38(void *dst, void *src);
extern void func_00312730(f32 *dst, s32 *src);
extern void sceVu0UnitMatrix(void *m);
extern void sceVu0RotMatrixZ(void *d, void *s, f32 angle);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void func_00312668(void *dst, void *src, void *k);
extern void func_00312710(s32 *dst, f32 *src);
extern s32 func_001A2890(s32 x, s32 y, s32 z);

extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u8 D_0036EA20[] __attribute__((section(".data")));

static u32 FloatToU32(f32 x) {
    if (x >= 2147483648.0f) {
        return (u32)(s32)(x - 2147483648.0f) | 0x80000000;
    }
    return (u32)(s32)x;
}

/* Draws every sprite of a particle list (next at +0x120) as a flat screen-space quad, one 0x80 byte packet each. */
void func_001A28C0(u8 *ctrl, u8 *origin) {
    u8 sp[0xB8 + 4];
    u8 *base = origin + 0x10;
    f32 camScale;
    s32 zc;
    u8 *node;
    u8 *pkt;
    u8 *slot;
    u8 *link;
    s32 ok;
    u32 sx;
    u32 sy;
    u32 q;
    s32 x, y, z;
    s32 ax, ay, bx, by;
    s32 c0x, c0y, c1x, c1y, c2x, c2y, c3x, c3y;
    u32 zf;
    u32 a;
    u64 *w;
    s32 i;
    f32 sz;

    *(u64 *)(sp + 0x40) = *(u64 *)(D_0036EA20 + 0);
    *(u64 *)(sp + 0x48) = *(u64 *)(D_0036EA20 + 8);
    camScale = *(f32 *)(gBtlCamView + 0x224);
    sceVu0RotTransPers(sp + 0x80, gBtlCamView + 0x100, base, 1);
    node = *(u8 **)ctrl;
    zc = *(s32 *)(sp + 0x88) >> 8;
    if (node == NULL) return;

    do {
        Vec3_Add(node + 0x50, base, node + 0x40);
        *(f32 *)(node + 0x5C) = 1.0f;
        func_00129C38(sp + 0x50, node + 0x50);
        ok = 1;
        *(f32 *)(sp + 0x5C) = 1.0f;
        sceVu0RotTransPers(sp + 0x80, gBtlCamView + 0x100, sp + 0x50, 1);

        sz = *(f32 *)(node + 0x1C);
        sx = FloatToU32(sz * 32.0f);
        sy = FloatToU32(sz * 32.0f);
        q = FloatToU32(4096.0f * camScale / (f32)*(s32 *)(sp + 0x8C));
        sx = (sx * q) >> 12;
        sy = (sy * q) >> 12;
        if (sx < 2 || sy < 2) ok = 0;

        if (ok) {
            *(s32 *)(sp + 0xA0) = -(s32)sx;
            *(s32 *)(sp + 0xA4) = sy;
            *(s32 *)(sp + 0x94) = sy;
            *(s32 *)(sp + 0x9C) = 1;
            *(s32 *)(sp + 0xAC) = 1;
            *(s32 *)(sp + 0x90) = sx;
            *(s32 *)(sp + 0x98) = 0;
            *(s32 *)(sp + 0xA8) = 0;
            func_00312730((f32 *)(sp + 0x60), (s32 *)(sp + 0x90));
            func_00312730((f32 *)(sp + 0x70), (s32 *)(sp + 0xA0));
            sceVu0UnitMatrix(sp);
            sceVu0RotMatrixZ(sp, sp, 0.0f);
            sceVu0ApplyMatrix(sp + 0x60, sp, sp + 0x60);
            sceVu0ApplyMatrix(sp + 0x70, sp, sp + 0x70);
            func_00312668(sp + 0x60, sp + 0x60, sp + 0x40);
            func_00312668(sp + 0x70, sp + 0x70, sp + 0x40);
            func_00312710((s32 *)(sp + 0x90), (f32 *)(sp + 0x60));
            func_00312710((s32 *)(sp + 0xA0), (f32 *)(sp + 0x70));

            x = *(s32 *)(sp + 0x80);
            y = *(s32 *)(sp + 0x84);
            z = *(s32 *)(sp + 0x88);
            ax = *(s32 *)(sp + 0x90);
            ay = *(s32 *)(sp + 0x94);
            if (func_001A2890(x - ax, y - ay, z) != 0) {
                ok = 0;
            } else {
                bx = *(s32 *)(sp + 0xA0);
                by = *(s32 *)(sp + 0xA4);
                if (func_001A2890(x + bx, y + by, z) != 0) {
                    ok = 0;
                } else if (func_001A2890(x - bx, y - by, z) != 0) {
                    ok = 0;
                } else if (func_001A2890(x + ax, y + ay, z) != 0) {
                    ok = 0;
                }
            }
        }

        if (ok) {
            pkt = D_00387AD8;
            c3x = x + ax;
            c3y = y + ay;
            c1x = x + bx;
            c1y = y + by;
            c2x = x - bx;
            c2y = y - by;
            c0x = x - ax;
            c0y = y - ay;
            zf = (u32)((z >> 8) << 8);
            D_00387AD8 = pkt + 0x80;
            if (pkt == NULL) return;

            *(u64 *)(pkt + 0x20) = 0x54;
            *(u64 *)(pkt + 0x00) = 0xA0000007ULL;
            *(u64 *)(pkt + 0x10) = 0xC400000000008001ULL;
            *(u64 *)(pkt + 0x18) = 0xF42424242160ULL;
            *(u8 *)(pkt + 0x30) = (u8)FloatToU32(*(f32 *)(node + 0x80));
            *(u8 *)(pkt + 0x31) = (u8)FloatToU32(*(f32 *)(node + 0x84));
            *(u8 *)(pkt + 0x32) = (u8)FloatToU32(*(f32 *)(node + 0x88));
            a = FloatToU32(*(f32 *)(node + 0x8C));
            *(u16 *)(pkt + 0x40) = (u16)c0x;
            *(u16 *)(pkt + 0x42) = (u16)c0y;
            *(u16 *)(pkt + 0x50) = (u16)c1x;
            *(u16 *)(pkt + 0x52) = (u16)c1y;
            *(u16 *)(pkt + 0x60) = (u16)c2x;
            *(u16 *)(pkt + 0x62) = (u16)c2y;
            *(u16 *)(pkt + 0x70) = (u16)c3x;
            *(u16 *)(pkt + 0x72) = (u16)c3y;
            for (i = 0; i < 4; i++) {
                w = (u64 *)(pkt + 0x40 + i * 0x10);
                *w = (*w & 0xFF000000FFFFFFFFULL) | ((u64)(zf & 0xFFFFFF) << 32);
            }
            *(u8 *)(pkt + 0x33) = (u8)a;
            *(f32 *)(pkt + 0x58) = 1.0f;
            *(f32 *)(pkt + 0x6C) = 1.0f;
            *(f32 *)(pkt + 0x34) = 1.0f;
            *(s32 *)(pkt + 0x38) = 0;
            *(s32 *)(pkt + 0x3C) = 0;
            *(s32 *)(pkt + 0x48) = 0;
            *(f32 *)(pkt + 0x4C) = 1.0f;
            *(s32 *)(pkt + 0x5C) = 0;
            *(f32 *)(pkt + 0x68) = 1.0f;
            *(u8 *)(pkt + 0x47) = 0xFF;
            *(u8 *)(pkt + 0x57) = 0xFF;
            *(u8 *)(pkt + 0x67) = 0xFF;
            *(u8 *)(pkt + 0x77) = 0xFF;
            *(u64 *)(pkt + 0x28) = *(u64 *)(ctrl + 0x148);

            if (zc < 0) {
                slot = D_00387AE0 + node[6] * 8;
            } else if (zc < 0x1000) {
                slot = D_00387AE0 + (zc * 2 + node[6]) * 8;
            } else {
                slot = D_00387AE0 + node[6] * 8 + 0xFFF0;
            }
            link = *(u8 **)(slot + 4);
            *(u8 **)(link + 4) = pkt;
            *(u8 **)(slot + 4) = pkt;
        }
        node = *(u8 **)(node + 0x120);
    } while (node != NULL);
}
