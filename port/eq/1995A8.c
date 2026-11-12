#include "common.h"

/* 0x001995A8: draws the glow sprites of one kind (kind = s2 byte +7) from the effect glow list gEftGlow+0x10
 * (next at +0xB0). Each glow is a quad: its 4 corners are built from a lookup table of corner vectors (choice by
 * bytes +4 / +9 / +0xA and flag 0x20), transformed by the glow matrix, converted to screen ints and rejected when
 * outside the 0xFFF0 window; the survivor becomes one 0x90-byte GIF packet linked into the draw list slot given by
 * the average depth. Colour is glow +0x50.. times 255, alpha also times obj+0x3C and the float argument. */
extern u8 *gEftGlowCfg;
extern u8 *gEftGlow;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

void func_001993D0(u8 *mtx, u8 *a, u8 *b);
void func_00129C50(u8 *dst, u8 *mtx, u8 *src);
void func_00129440(u8 *dst, u8 *src, s32 n);
void func_00129BB8(u8 *dst, u8 *src, f32 s);
s32 func_00126630(void);

/* float -> u32 style truncation used for the colour bytes (cvt.w.s with the 2^31 fix-up) */
static s32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (s32)(f - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)f;
}

static void put_pos(u8 *q, s32 off, u8 *v) {
    *(u16 *)(q + off) = *(u16 *)v;
    *(u16 *)(q + off + 2) = *(u16 *)(v + 4);
    *(u32 *)(q + off + 4) = (*(u32 *)(q + off + 4) & 0xFF000000u) | (*(u32 *)(v + 8) & 0xFFFFFFu);
    q[off + 7] = 0xFF;
}

void func_001995A8(u8 *obj, s32 kind, f32 alphaScale) {
    u8 sp[0x130];   /* tamano de locales del original (antes 0x120) */
    u8 *cfg = gEftGlowCfg;
    u8 *glow = gEftGlow;
    u8 *tab40[2];
    u8 *tab50[4];
    u8 *tab60[2];
    u8 *e;
    u8 *next;
    u8 *q;
    u8 *slot;
    u8 *tail;
    u8 *scr = sp + 0xD0;
    u8 *vec = sp + 0x70;
    f32 *in = (f32 *)(sp + 0xC0);
    f32 s0, s1, s2;
    f32 a;
    s32 bad;
    s32 k;
    s32 off;
    s32 ci[3];
    s32 depth;
    s32 nk;
    f32 inv;
    f32 *srcp;

    tab40[0] = cfg + 0x290;
    tab40[1] = cfg + 0x2D0;
    tab50[0] = cfg + 0x310;
    tab50[1] = cfg + 0x390;
    tab50[2] = cfg + 0x350;
    tab50[3] = cfg + 0x3D0;
    tab60[0] = cfg + 0x410;
    tab60[1] = cfg + 0x450;

    e = *(u8 **)(glow + 0x10);
    while (e != 0) {
        next = *(u8 **)(e + 0xB0);
        if (e[7] != kind) {
            e = next;
            continue;
        }
        bad = (*(u32 *)e & 2) != 0;
        if (bad) {
            e = next;
            continue;
        }

        func_001993D0(sp, e + 0xA0, e + 0x40);
        s0 = *(f32 *)(e + 0x18) * *(f32 *)(e + 0x20);
        s1 = (*(f32 *)(e + 0x18) * *(f32 *)(e + 0x1C)) * *(f32 *)(e + 0x24);
        k = 0;
        do {
            off = k * 16;
            srcp = (f32 *)(tab40[e[4]] + off);
            in[0] = srcp[0] * s1;
            in[1] = ((f32 *)(tab40[e[4]] + off))[1] * *(f32 *)(e + 0x18);
            a = ((f32 *)(tab40[e[4]] + off))[2] * s0;
            in[3] = 1.0f;
            in[2] = a;
            if (k >= 2) {
                in[2] = a * *(f32 *)(e + 0x28);
            }
            func_00129C50(sp + 0xB0, sp, (u8 *)in);
            func_00129440(scr + off, sp + 0xB0, 1);
            k++;
            if (*(u32 *)(scr + off) > 0xFFF0) {
                bad = 1;
                break;
            }
            if (*(u32 *)(scr + off + 4) > 0xFFF0) {
                bad = 1;
                break;
            }
            if (*(s32 *)(scr + off + 8) < 0) {
                bad = 1;
                break;
            }
            inv = 1.0f / (f32)*(s32 *)(scr + off + 12);
            if (*(u32 *)e & 0x20) {
                func_00129BB8(vec + off, tab60[e[9]] + off, inv);
            } else {
                func_00129BB8(vec + off, tab50[e[10] * 2 + e[9]] + off, inv);
            }
        } while (k < 4);
        if (bad) {
            e = next;
            continue;
        }

        ci[0] = (s32)(*(f32 *)(e + 0x50) * 255.0f);
        ci[1] = (s32)(*(f32 *)(e + 0x54) * 255.0f);
        ci[2] = (s32)(*(f32 *)(e + 0x58) * 255.0f);
        q = D_00387AD8;
        a = *(f32 *)(obj + 0x3C);
        D_00387AD8 = q + 0x90;
        a = ((*(f32 *)(e + 0x5C) * 255.0f) * a) * alphaScale;
        if (q == 0) {
            return;
        }
        *(u64 *)(q + 0x20) = 0x5C;
        *(u64 *)(q + 0x00) = 0xA0000008ull;
        *(u64 *)(q + 0x10) = 0xE400000000008001ull;
        *(u64 *)(q + 0x18) = 0x42142142142160ull;
        for (nk = 0; nk < 4; nk++) {
            static const u8 colOff[4] = {0x30, 0x48, 0x60, 0x78};
            static const u8 uvOff[4] = {0x38, 0x50, 0x68, 0x80};
            u8 *c = q + colOff[nk];
            f32 *v = (f32 *)(vec + nk * 16);

            c[0] = (u8)ci[0];
            c[1] = (u8)ci[1];
            c[2] = (u8)ci[2];
            c[3] = (u8)f2u(a);
            *(f32 *)(q + uvOff[nk] - 4) = v[2];
            *(f32 *)(q + uvOff[nk]) = v[0];
            *(f32 *)(q + uvOff[nk] + 4) = v[1];
        }
        put_pos(q, 0x40, scr + 0x00);
        put_pos(q, 0x58, scr + 0x10);
        put_pos(q, 0x70, scr + 0x20);
        put_pos(q, 0x88, scr + 0x30);
        if (*(u32 *)e & 0x20) {
            *(u64 *)(q + 0x28) = *(u64 *)(glow + 0x4E8);
        } else if (*(u32 *)obj & 0x20) {
            *(u64 *)(q + 0x28) = *(u64 *)(obj + 0x2A8 + e[6] * 8);
        } else {
            *(u64 *)(q + 0x28) = *(u64 *)(obj + 0x2A0);
        }
        depth = (*(s32 *)(scr + 0x08) + *(s32 *)(scr + 0x38) + (*(s32 *)(scr + 0x28) + *(s32 *)(scr + 0x18))) >> 10;
        if (func_00126630() != 0) {
            if (depth < 0) {
                slot = D_00387AE0 + 8;
            } else if (depth < 0x1000) {
                slot = D_00387AE0 + depth * 16 + 8;
            } else {
                slot = D_00387AE0 + 0xFFF8;
            }
        } else {
            if (depth < 0) {
                slot = D_00387AE0 + e[0xC] * 8;
            } else if (depth < 0x1000) {
                slot = D_00387AE0 + (depth * 2 + e[0xC]) * 8;
            } else {
                slot = D_00387AE0 + e[0xC] * 8 + 0xFFF0;
            }
        }
        tail = *(u8 **)(slot + 4);
        *(u8 **)(tail + 4) = q;
        *(u8 **)(slot + 4) = q;
        e = next;
    }
}
