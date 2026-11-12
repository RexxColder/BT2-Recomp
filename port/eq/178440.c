#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

/* float -> u8 with the game's >= 2^31 sign-bit fixup */
static u8 f2b(f32 v) {
    u32 r = (u32)(s32)v;
    if (v >= 2147483648.0f) {
        r = (u32)(s32)(v - 2147483648.0f) | 0x80000000;
    }
    return (u8)r;
}

/* one 3-component vertex: u16 x, u16 y (+4), 24-bit z (+8), alpha 0xFF in the top byte */
static void put_vtx(u8 *dst, u8 *src) {
    *(u16 *)(dst + 0) = *(u16 *)(src + 0);
    *(u16 *)(dst + 2) = *(u16 *)(src + 4);
    *(u32 *)(dst + 4) = (*(u32 *)(src + 8) & 0xFFFFFF) | 0xFF000000;
}

/* 0x00178440: appends a 0x80-byte primitive packet (triangle with 3 vertices, 3 colors, 3 uv pairs)
   from the buffer at D_00387AD8, and links it into the depth-sorted bucket list at D_00387AE0
   (bucket = avg z >> 8, clamped, 2 lists per bucket selected by `list`). */
s32 func_00178440(u8 *a0, u8 *a1, u8 *a2, f32 *a3, f32 *a4, f32 *a5, f32 *c0, f32 *c1, f32 *c2,
                  s64 *tag, u8 list) {
    u8 *pkt = D_00387AD8;
    u8 *slot;
    u8 *bucket;
    s32 depth;
    s32 head;

    D_00387AD8 = pkt + 0x80;
    *(s64 *)(pkt + 0x20) = 0x5B;
    *(s64 *)(pkt + 0x00) = 0xA0000007;
    *(s64 *)(pkt + 0x10) = (s64)0xC400000000008001ULL;
    *(s64 *)(pkt + 0x18) = 0xF42142142160LL;
    pkt[0x30] = f2b(c0[0]);
    pkt[0x31] = f2b(c0[1]);
    pkt[0x32] = f2b(c0[2]);
    pkt[0x33] = f2b(c0[3]);
    *(f32 *)(pkt + 0x34) = a3[2];
    pkt[0x48] = f2b(c1[0]);
    pkt[0x49] = f2b(c1[1]);
    pkt[0x4A] = f2b(c1[2]);
    pkt[0x4B] = f2b(c1[3]);
    *(f32 *)(pkt + 0x4C) = a4[2];
    pkt[0x60] = f2b(c2[0]);
    pkt[0x61] = f2b(c2[1]);
    pkt[0x62] = f2b(c2[2]);
    pkt[0x63] = f2b(c2[3]);
    *(f32 *)(pkt + 0x64) = a5[2];
    put_vtx(pkt + 0x40, a0);
    put_vtx(pkt + 0x58, a1);
    put_vtx(pkt + 0x70, a2);
    *(f32 *)(pkt + 0x38) = a3[0];
    *(f32 *)(pkt + 0x3C) = a3[1];
    *(f32 *)(pkt + 0x50) = a4[0];
    *(f32 *)(pkt + 0x54) = a4[1];
    *(f32 *)(pkt + 0x68) = a5[0];
    *(f32 *)(pkt + 0x6C) = a5[1];
    *(s64 *)(pkt + 0x28) = *tag;
    if ((u32)(*(u64 *)(pkt + 0x28) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 178440 %llx", (unsigned long long)*(u64 *)(pkt + 0x28)); /* TEMP TEX0 */
    depth = (*(s32 *)(a0 + 8) + *(s32 *)(a1 + 8) + *(s32 *)(a2 + 8)) / 3;
    depth >>= 8;
    if (depth < 0) {
        slot = D_00387AE0 + list * 8;
    } else if (depth < 0x1000) {
        slot = D_00387AE0 + (depth * 2 + list) * 8;
    } else {
        slot = D_00387AE0 + list * 8 + 0xFFF0;
    }
    head = *(s32 *)(slot + 4);
    *(u8 **)(head + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
    return head;
}
