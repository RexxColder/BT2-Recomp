#include "common.h"

/* 0x001A4B80: draws a textured, tinted screen rectangle (x, y, w, h) whose four corners are offset by corner[]
 * (pairs of s32 at offsets 0, 0x10, 0x20, 0x30 for x and 0x4, 0x14, 0x24, 0x34 for y), as a chain of GIF packets
 * appended to the list D_00387AE4: a setup packet, a 4-vertex sprite (clamped to 512x448), a state packet,
 * two 0x60-byte texture strips, a frame packet (0x90 bytes) and a final 0x60-byte quad. Does nothing when
 * D_00387824 (the texture source) or its +8 member is null. */
extern u8 *D_00387AD8;
extern u8 *D_00387AE4;
extern u8 *D_00387824;
extern u8 gGfx[] __attribute__((section(".data")));

static void link_pkt(u8 *pkt) {
    u8 *tail = *(u8 **)(D_00387AE4 + 4);

    *(u8 **)(tail + 4) = pkt;
    *(u8 **)(D_00387AE4 + 4) = pkt;
}

static s32 clamp_x(s32 v) {
    if (v < 0) {
        v = 0;
    }
    if (!(v < 0x201)) {
        v = 0x200;
    }
    return v;
}

static s32 clamp_y(s32 v) {
    if (v < 0) {
        v = 0;
    }
    if (!(v < 0x1C1)) {
        v = 0x1C0;
    }
    return v;
}

void func_001A4B80(s32 x, s32 y, s32 w, s32 h, s32 *c) {
    u8 *q;
    s32 X0, X1, X2, X3, Y0, Y1, Y2, Y3;
    s32 i;
    s32 sx;
    s32 sx2;
    s32 u;
    u64 mask = 0x00FFFFFF00000000ull;

    if (D_00387824 == 0) {
        return;
    }
    if (*(s32 *)(D_00387824 + 8) == 0) {
        return;
    }

    X0 = x + c[0];
    X1 = x + w + c[4];
    X2 = x + c[8];
    X3 = x + w + c[12];
    Y0 = y + c[1];
    Y1 = y + c[5];
    Y2 = y + h + c[9];
    Y3 = y + h + c[13];

    /* setup packet */
    q = D_00387AD8;
    D_00387AD8 = q + 0x80;
    *(u64 *)(q + 0x20) = 0x10150;
    *(u64 *)(q + 0x30) = 0x1310000E0ull;
    *(u64 *)(q + 0x40) = 0x30000;
    *(u64 *)(q + 0x10) = 0x1000000000008006ull;
    *(u64 *)(q + 0x50) = 0x3F0000003F0000ull;
    *(u64 *)(q + 0x58) = 0x40;
    *(u64 *)(q + 0x38) = 0x4E;
    *(u64 *)(q + 0x48) = 0x47;
    *(u64 *)(q + 0x68) = 0x14;
    *(u64 *)(q + 0x00) = 0xA0000007ull;
    *(u64 *)(q + 0x28) = 0x4C;
    *(u64 *)(q + 0x18) = 0xE;
    *(u64 *)(q + 0x60) = 0;
    *(u64 *)(q + 0x70) = 0;
    *(u64 *)(q + 0x78) = 0x3F;
    link_pkt(q);

    X0 = clamp_x(X0);
    X1 = clamp_x(X1);
    X2 = clamp_x(X2);
    X3 = clamp_x(X3);
    Y0 = clamp_y(Y0);
    Y1 = clamp_y(Y1);
    Y2 = clamp_y(Y2);
    Y3 = clamp_y(Y3);

    /* the 4-vertex block */
    q = D_00387AD8;
    D_00387AD8 = q + 0x80;
    *(u64 *)(q + 0x20) = 0x114;
    *(u64 *)(q + 0x00) = 0xA0000007ull;
    *(u64 *)(q + 0x10) = 0xC400000000008001ull;
    *(u64 *)(q + 0x18) = 0xF43434343160ull;
    *(u16 *)(q + 0x52) = 0x7200;
    *(u16 *)(q + 0x60) = 0x7000;
    *(u16 *)(q + 0x72) = 0x7600;
    *(u16 *)(q + 0x40) = 0x7000;
    *(u16 *)(q + 0x42) = 0x7200;
    *(u16 *)(q + 0x50) = 0x7400;
    *(u16 *)(q + 0x62) = 0x7600;
    *(u16 *)(q + 0x70) = 0x7400;
    *(u64 *)(q + 0x70) |= mask;
    *(u64 *)(q + 0x40) |= mask;
    *(u64 *)(q + 0x50) |= mask;
    *(u64 *)(q + 0x60) |= mask;
    *(u64 *)(q + 0x28) = (*(s32 *)(gGfx + 0x234) & 1) ? 0xE64020000ull : 0xE64020E00ull;
    q[0x33] = 0x80;
    q[0x30] = 0x80;
    q[0x31] = 0x80;
    q[0x32] = 0x80;
    *(f32 *)(q + 0x34) = 1.0f;
    *(u16 *)(q + 0x38) = (u16)(X0 << 4);
    *(u16 *)(q + 0x48) = (u16)(X1 << 4);
    *(u16 *)(q + 0x58) = (u16)(X2 << 4);
    *(u16 *)(q + 0x5A) = (u16)(Y2 << 4);
    *(u16 *)(q + 0x68) = (u16)(X3 << 4);
    *(u16 *)(q + 0x3A) = (u16)(Y0 << 4);
    *(u16 *)(q + 0x4A) = (u16)(Y1 << 4);
    *(u16 *)(q + 0x6A) = (u16)(Y3 << 4);
    q[0x47] = 0xFF;
    q[0x57] = 0xFF;
    q[0x67] = 0xFF;
    q[0x77] = 0xFF;
    link_pkt(q);

    /* state packet */
    q = D_00387AD8;
    D_00387AD8 = q + 0x40;
    *(u64 *)(q + 0x00) = 0xA0000003ull;
    *(u64 *)(q + 0x10) = 0x1000000000008002ull;
    *(u64 *)(q + 0x18) = 0xE;
    *(u64 *)(q + 0x20) = 0xFFFFFF00010150ull;
    *(u64 *)(q + 0x28) = 0x4C;
    *(u64 *)(q + 0x38) = 0x3F;
    *(u64 *)(q + 0x30) = 0;
    link_pkt(q);

    /* two texture strips */
    sx = 0x7000;
    sx2 = 0x7200;
    u = 0x800;
    for (i = 0; i < 2; i++) {
        q = D_00387AD8;
        D_00387AD8 = q + 0x60;
        *(u64 *)(q + 0x20) = 0x116;
        *(u64 *)(q + 0x00) = 0xA0000005ull;
        *(u64 *)(q + 0x10) = 0x8400000000008001ull;
        *(u64 *)(q + 0x18) = 0xF4343160ull;
        *(u64 *)(q + 0x28) = **(u64 **)(D_00387824 + 8);
        *(u16 *)(q + 0x40) = (u16)sx;
        sx += 0x200;
        *(u16 *)(q + 0x50) = (u16)sx2;
        sx2 += 0x200;
        *(u16 *)(q + 0x42) = 0x7200;
        *(u16 *)(q + 0x52) = 0x7600;
        *(u64 *)(q + 0x40) |= mask;
        *(u64 *)(q + 0x50) |= mask;
        *(u16 *)(q + 0x48) = (u16)u;
        u += 0x800;
        *(u16 *)(q + 0x38) = (u16)(i << 11);
        q[0x30] = 0x80;
        q[0x31] = 0x80;
        q[0x32] = 0x80;
        q[0x33] = 0x80;
        *(f32 *)(q + 0x34) = 1.0f;
        *(u16 *)(q + 0x3A) = 0;
        *(u16 *)(q + 0x4A) = 0x1000;
        q[0x47] = 0xFF;
        q[0x57] = 0xFF;
        link_pkt(q);
    }

    /* frame packet */
    q = D_00387AD8;
    D_00387AD8 = q + 0x90;
    *(u64 *)(q + 0x00) = 0xA0000008ull;
    *(u64 *)(q + 0x10) = 0x1000000000008007ull;
    *(u64 *)(q + 0x18) = 0xE;
    *(u64 *)(q + 0x20) = (*(s32 *)(gGfx + 0x234) & 1) ? 0x80000ull : 0x80070ull;
    *(u64 *)(q + 0x30) = 0x1310000E0ull;
    *(u64 *)(q + 0x40) = 0x50000;
    *(u64 *)(q + 0x50) = 0x44;
    *(u64 *)(q + 0x60) = 0x1BF000001FF0000ull;
    *(u64 *)(q + 0x70) = 0x60;
    *(u64 *)(q + 0x28) = 0x4C;
    *(u64 *)(q + 0x38) = 0x4E;
    *(u64 *)(q + 0x48) = 0x47;
    *(u64 *)(q + 0x58) = 0x42;
    *(u64 *)(q + 0x68) = 0x40;
    *(u64 *)(q + 0x78) = 0x14;
    *(u64 *)(q + 0x80) = 1;
    *(u64 *)(q + 0x88) = 0x3F;
    link_pkt(q);

    /* final quad */
    q = D_00387AD8;
    D_00387AD8 = q + 0x60;
    *(u64 *)(q + 0x20) = 0x156;
    *(u64 *)(q + 0x00) = 0xA0000005ull;
    *(u64 *)(q + 0x10) = 0x8400000000008001ull;
    *(u64 *)(q + 0x18) = 0xF4343160ull;
    *(u16 *)(q + 0x40) = (u16)((x << 4) + 0x7000);
    *(u16 *)(q + 0x42) = (u16)((y << 4) + 0x7200);
    *(u16 *)(q + 0x50) = (u16)(((x + w) << 4) + 0x7000);
    *(u16 *)(q + 0x52) = (u16)(((y + h) << 4) + 0x7200);
    *(u64 *)(q + 0x28) = 0x5DC006A00ull;
    *(u64 *)(q + 0x40) |= mask;
    *(u64 *)(q + 0x50) |= mask;
    q[0x30] = 0x80;
    q[0x31] = 0x80;
    q[0x32] = 0x80;
    q[0x33] = 0x80;
    *(f32 *)(q + 0x34) = 1.0f;
    *(u16 *)(q + 0x4A) = 0x400;
    q[0x57] = 0xFF;
    *(u16 *)(q + 0x38) = 0;
    *(u16 *)(q + 0x3A) = 0;
    *(u16 *)(q + 0x48) = 0x400;
    q[0x47] = 0xFF;
    link_pkt(q);
}
