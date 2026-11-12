#include "common.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE4;

/* 0x001E7CD8: when obj flags (+0x38) bit 1 is set and the byte at +0x2C is nonzero, emit three GS packets
   into the display-list buffer at D_00387AD8 and link each into the list at D_00387AE4 (tail at +4). Two
   packets are a 4-quad sprite pair placed at (x, y) of obj +0x10/+0x14 scaled by obj +0x20. Returns the
   last packet, or NULL when nothing is emitted (ctx.h says void; the asm leaves the last packet in v0). */
u8 *func_001E7CD8(u8 *obj) {
    u8 *p1;
    u8 *p2;
    u8 *p3;
    u8 *tail;
    s64 t8;
    s32 xw;
    s32 yw;
    s32 vA;
    s32 vB;
    u16 x0;
    u16 y0;
    f32 sc;

    if ((*(u32 *)(obj + 0x38) & 2) == 0) {
        return NULL;
    }
    if (obj[0x2C] == 0) {
        return NULL;
    }

    t8 = *(s64 *)*(u8 **)obj;
    xw = *(s32 *)(obj + 0x10);
    yw = *(s32 *)(obj + 0x14);
    sc = *(f32 *)(obj + 0x20);
    vA = ((s32)(sc * 64.0f)) >> 1;
    vB = ((s32)(sc * 74.0f)) >> 1;
    x0 = (u16)xw;
    y0 = (u16)yw;

    /* packet 1: header with two tags (not a vertex packet) */
    p1 = D_00387AD8;
    D_00387AD8 = p1 + 0x30;
    *(u64 *)(p1 + 0x20) = 0x310000E0ULL;
    *(u64 *)(p1 + 0x00) = 0xA0000002ULL;
    *(u64 *)(p1 + 0x10) = 0x1000000000008001ULL;
    *(u64 *)(p1 + 0x18) = 14;
    *(u64 *)(p1 + 0x28) = 78;
    tail = *(u8 **)(D_00387AE4 + 4);
    *(u8 **)(tail + 4) = p1;
    *(u8 **)(D_00387AE4 + 4) = p1;

    /* packet 2: sprite with two vertices */
    p2 = D_00387AD8;
    D_00387AD8 = p2 + 0x60;
    *(u64 *)(p2 + 0x20) = 0x156ULL;
    *(u64 *)(p2 + 0x00) = 0xA0000005ULL;
    *(u64 *)(p2 + 0x10) = 0x8400000000008001ULL;
    *(u64 *)(p2 + 0x18) = 0xF4343160ULL;
    *(u64 *)(p2 + 0x28) = (u64)t8;
    *(u8 *)(p2 + 0x33) = 0x80;
    *(f32 *)(p2 + 0x34) = 1.0f;
    *(u16 *)(p2 + 0x3A) = 16;
    *(u8 *)(p2 + 0x30) = 0;
    *(u8 *)(p2 + 0x31) = 0;
    *(u8 *)(p2 + 0x32) = 0;
    *(u16 *)(p2 + 0x38) = 16;
    *(u16 *)(p2 + 0x48) = 2032;
    *(u16 *)(p2 + 0x4A) = 2032;
    *(u16 *)(p2 + 0x40) = (u16)((((s32)x0 - vA) << 4) + 0x7000);
    *(u16 *)(p2 + 0x42) = (u16)((((s32)y0 - vB) << 4) + 0x7200);
    *(u64 *)(p2 + 0x40) |= 0x00FFFFFF00000000ULL;
    *(u8 *)(p2 + 0x47) = 0xFF;
    *(u16 *)(p2 + 0x50) = (u16)((((s32)x0 + vA) << 4) + 0x7000);
    *(u16 *)(p2 + 0x52) = (u16)((((s32)y0 + vB) << 4) + 0x7200);
    *(u64 *)(p2 + 0x50) |= 0x00FFFFFF00000000ULL;
    *(u8 *)(p2 + 0x57) = 0xFF;
    tail = *(u8 **)(D_00387AE4 + 4);
    *(u8 **)(tail + 4) = p2;
    *(u8 **)(D_00387AE4 + 4) = p2;

    /* packet 3: closing header, linked last */
    p3 = D_00387AD8;
    D_00387AD8 = p3 + 0x30;
    *(u64 *)(p3 + 0x00) = 0xA0000002ULL;
    *(u64 *)(p3 + 0x10) = 0x1000000000008001ULL;
    *(u64 *)(p3 + 0x18) = 14;
    *(u64 *)(p3 + 0x20) = 0x1310000E0ULL;
    *(u64 *)(p3 + 0x28) = 78;
    tail = *(u8 **)(D_00387AE4 + 4);
    *(u8 **)(tail + 4) = p3;
    *(u8 **)(D_00387AE4 + 4) = p3;
    return p3;
}
