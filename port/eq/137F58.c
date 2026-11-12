#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern u8 *gEftSurf;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_003842E4;

extern s32 func_00129720(u8 *a0, u8 *poly, u8 *plane, s32 n);
extern void func_00129A50(u8 *scr, f32 *uv, u8 *poly, s32 n);

/* float -> u32 style truncation used for the colour bytes (cvt.w.s with the 2^31 fix-up) */
static s32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (s32)(f - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)f;
}

/* Clips a polygon (vertices 0x30 bytes apart: colour floats at +0x20) against the 5 planes of gEftSurf and queues
   it as a triangle fan of textured GIF packets (0x80 bytes each). `invert` flips the depth sort key, `layer`
   (<0 -> 0) picks the ordering-table slot pair, `keyBias` is subtracted from the depth key. Returns nothing useful. */
void func_00137F58(u8 *poly, s32 layer, s32 unused, u32 invert, u64 tex, s32 keyBias) {
    u8 scr[0x140];   /* tamano de locales del original (antes 0x90) */
    f32 uv[36];
    u8 *plane;
    s32 n;
    s32 i;
    s32 k;
    u64 m = 0xFF000000FFFFFFFFull;

    invert &= 0xFF;
    plane = *(u8 **)(gEftSurf + 0x10);
    n = 3;
    for (k = 4; k >= 0; k--) {
        n = func_00129720(poly, poly, plane, n);
        plane += 0x10;
    }
    if (n == 0) {
        return;
    }
    func_00129A50(scr, uv, poly, n);
    for (i = 2; i < n; i++) {
        u8 *v0c = poly + 0x20;
        u8 *v1c = poly + i * 0x30 - 0x10;
        u8 *v2c = poly + i * 0x30 + 0x20;
        u8 *p0 = scr;
        u8 *p1 = scr + i * 16 - 16;
        u8 *p2 = scr + i * 16;
        f32 *uv0 = uv;
        f32 *uv1 = uv + i * 4 - 4;
        f32 *uv2 = uv + i * 4;
        s32 z0 = *(s32 *)(scr + 8);
        s32 key = z0 >> 8;
        s32 slot;
        s32 flag = 1;
        u8 *pkt;
        u8 *ent;
        u8 *prev;

        if (invert != 0) {
            key = 0x1000 - key;
        }
        if (*(s32 *)(scr + 8) > 0xFFFFFF) {
            *(s32 *)(scr + 8) = 0xFFFFFF;
        }
        if (*(s32 *)(p1 + 8) > 0xFFFFFF) {
            *(s32 *)(p1 + 8) = 0xFFFFFF;
        }
        if (*(s32 *)(p2 + 8) > 0xFFFFFF) {
            *(s32 *)(p2 + 8) = 0xFFFFFF;
        }
        key -= keyBias;
        slot = layer;
        if (*(f32 *)(poly + 0x2C) < D_003842E4 && *(f32 *)(poly + i * 0x30 - 4) < D_003842E4 &&
            *(f32 *)(v2c + 0xC) < D_003842E4) {
            continue;
        }
        if (layer < 0) {
            slot = 0;
            flag = 0;
        }
        pkt = D_00387AD8;
        D_00387AD8 = pkt + 0x80;
        *(u64 *)(pkt + 0x20) = ((u64)flag << 6) | 0x1B;
        *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
        *(u64 *)(pkt + 0x00) = 0xA0000007ull;
        *(u64 *)(pkt + 0x18) = 0xF42142142160ull;
        pkt[0x30] = f2u(*(f32 *)(v0c + 0x0));
        pkt[0x31] = f2u(*(f32 *)(v0c + 0x4));
        pkt[0x32] = f2u(*(f32 *)(v0c + 0x8));
        pkt[0x33] = f2u(*(f32 *)(v0c + 0xC));
        *(f32 *)(pkt + 0x34) = uv0[2];
        pkt[0x48] = f2u(*(f32 *)(v1c + 0x0));
        pkt[0x49] = f2u(*(f32 *)(v1c + 0x4));
        pkt[0x4A] = f2u(*(f32 *)(v1c + 0x8));
        pkt[0x4B] = f2u(*(f32 *)(v1c + 0xC));
        *(f32 *)(pkt + 0x4C) = uv1[2];
        pkt[0x60] = f2u(*(f32 *)(v2c + 0x0));
        pkt[0x61] = f2u(*(f32 *)(v2c + 0x4));
        pkt[0x62] = f2u(*(f32 *)(v2c + 0x8));
        pkt[0x63] = f2u(*(f32 *)(v2c + 0xC));
        *(f32 *)(pkt + 0x64) = uv2[2];
        *(u64 *)(pkt + 0x28) = tex;
        if ((u32)(*(u64 *)(pkt + 0x28) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 137F58 %llx", (unsigned long long)*(u64 *)(pkt + 0x28)); /* TEMP TEX0 */
        *(f32 *)(pkt + 0x38) = uv0[0];
        *(f32 *)(pkt + 0x3C) = uv0[1];
        *(f32 *)(pkt + 0x50) = uv1[0];
        *(f32 *)(pkt + 0x54) = uv1[1];
        *(f32 *)(pkt + 0x68) = uv2[0];
        *(f32 *)(pkt + 0x6C) = uv2[1];
        *(u16 *)(pkt + 0x40) = *(u16 *)p0;
        *(u16 *)(pkt + 0x42) = *(u16 *)(p0 + 4);
        *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & m) | ((u64)(*(s32 *)(p0 + 8) & 0xFFFFFF) << 32);
        pkt[0x47] = 0xFF;
        *(u16 *)(pkt + 0x58) = *(u16 *)p1;
        *(u16 *)(pkt + 0x5A) = *(u16 *)(p1 + 4);
        *(u64 *)(pkt + 0x58) = (*(u64 *)(pkt + 0x58) & m) | ((u64)(*(s32 *)(p1 + 8) & 0xFFFFFF) << 32);
        pkt[0x5F] = 0xFF;
        *(u16 *)(pkt + 0x70) = *(u16 *)p2;
        *(u16 *)(pkt + 0x72) = *(u16 *)(p2 + 4);
        *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & m) | ((u64)(*(s32 *)(p2 + 8) & 0xFFFFFF) << 32);
        pkt[0x77] = 0xFF;

        if (key < 0) {
            ent = D_00387AE0 + (slot << 3);
        } else if (key < 0x1000) {
            ent = D_00387AE0 + ((key * 2 + slot) << 3);
        } else {
            ent = D_00387AE0 + (slot << 3) + 0xFFF0;
        }
        prev = *(u8 **)(ent + 4);
        *(u8 **)(prev + 4) = pkt;
        *(u8 **)(ent + 4) = pkt;
    }
}
