#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

/* float -> u32 style truncation used for the colour bytes (cvt.w.s with the 2^31 fix-up) */
static s32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (s32)(f - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)f;
}

/* Inserts the 0x30-byte packet `pk` into the ordering table slot (key, layer). */
static u8 *ot_insert(u8 *pk, s32 key, s32 layer) {
    u8 *ent;
    u8 *prev;

    if (key < 0) {
        ent = D_00387AE0 + (layer << 3);
    } else if (key < 0x1000) {
        ent = D_00387AE0 + ((key * 2 + layer) << 3);
    } else {
        ent = D_00387AE0 + (layer << 3) + 0xFFF0;
    }
    prev = *(u8 **)(ent + 4);
    *(u8 **)(prev + 4) = pk;
    *(u8 **)(ent + 4) = pk;
    return prev;
}

/* Queues one Gouraud-textured triangle: a small 0x30-byte header packet (type 0xA0000002) followed by the 0x80-byte
   vertex packet, both inserted in ordering-table slot layer / average-z key. p0..p2 = {s16 x, s16 y@4, s32 z@8},
   uv0..uv2 = {u, v, q}, c0..c2 = float RGBA. The key is (z0+z1+z2)/3 >> 8. */
s32 func_001448C8(u8 *p0, u8 *p1, u8 *p2, u8 *uv0, u8 *uv1, u8 *uv2, u8 *c0, u8 *c1, u8 *c2,
                  s32 layer, u64 tex) {
    u8 *pkt;
    u8 *hdr;
    s32 key;
    u8 *prev;
    u64 m = 0xFF000000FFFFFFFFull;

    pkt = D_00387AD8;
    hdr = pkt + 0x80;
    if (pkt == 0) {
        D_00387AD8 = hdr;
        return *(s32 *)(c2 + 8);
    }
    key = (*(s32 *)(p0 + 8) + *(s32 *)(p1 + 8) + *(s32 *)(p2 + 8)) / 3;
    D_00387AD8 = pkt + 0xB0;
    *(u64 *)(hdr + 0x00) = 0xA0000002ull;
    *(u64 *)(pkt + 0x90) = 0x1000000000008001ull;
    *(u64 *)(hdr + 0x18) = 0xE;
    *(u64 *)(hdr + 0x28) = 8;
    if ((u32)(*(u64 *)(hdr + 0x28) >> 32) == 0 && (u32)*(u64 *)(hdr + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 1448C8 %llx", (unsigned long long)*(u64 *)(hdr + 0x28)); /* TEMP TEX0 */
    *(u64 *)(hdr + 0x20) = 0;
    key >>= 8;
    ot_insert(hdr, key, layer);

    *(u64 *)(pkt + 0x20) = 0x5B;
    *(u64 *)(pkt + 0x00) = 0xA0000007ull;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
    *(u64 *)(pkt + 0x18) = 0xF42142142160ull;
    pkt[0x30] = f2u(*(f32 *)(c0 + 0));
    pkt[0x31] = f2u(*(f32 *)(c0 + 4));
    pkt[0x32] = f2u(*(f32 *)(c0 + 8));
    pkt[0x33] = f2u(*(f32 *)(c0 + 12));
    *(f32 *)(pkt + 0x34) = *(f32 *)(uv0 + 8);
    pkt[0x48] = f2u(*(f32 *)(c1 + 0));
    pkt[0x49] = f2u(*(f32 *)(c1 + 4));
    pkt[0x4A] = f2u(*(f32 *)(c1 + 8));
    pkt[0x4B] = f2u(*(f32 *)(c1 + 12));
    *(f32 *)(pkt + 0x4C) = *(f32 *)(uv1 + 8);
    pkt[0x60] = f2u(*(f32 *)(c2 + 0));
    pkt[0x61] = f2u(*(f32 *)(c2 + 4));
    pkt[0x62] = f2u(*(f32 *)(c2 + 8));
    pkt[0x63] = f2u(*(f32 *)(c2 + 12));
    *(f32 *)(pkt + 0x64) = *(f32 *)(uv2 + 8);
    *(f32 *)(pkt + 0x38) = *(f32 *)(uv0 + 0);
    *(f32 *)(pkt + 0x3C) = *(f32 *)(uv0 + 4);
    *(f32 *)(pkt + 0x50) = *(f32 *)(uv1 + 0);
    *(f32 *)(pkt + 0x54) = *(f32 *)(uv1 + 4);
    *(f32 *)(pkt + 0x68) = *(f32 *)(uv2 + 0);
    *(f32 *)(pkt + 0x6C) = *(f32 *)(uv2 + 4);
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
    *(u64 *)(pkt + 0x28) = tex;
    if ((u32)(*(u64 *)(pkt + 0x28) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 1448C8 %llx", (unsigned long long)*(u64 *)(pkt + 0x28)); /* TEMP TEX0 */
    pkt[0x77] = 0xFF;
    prev = ot_insert(pkt, key, layer);
    return (s32)prev;
}
