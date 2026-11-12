#include "m2c_macros.h"

extern u8 D_0036E9B0[] __attribute__((section(".data")));
extern u8 *D_00387AD8;
extern u8 *D_00387AE4;
void func_00129DB8(void *a0, void *a1, void *a2, f32 f12);

/* GS packet for one coloured vertex: the vector returned by func_00129DB8 is turned into four colour bytes
 * (floats at or above 2^31 wrap with the sign bit set), the position halfwords are fixed, the packet is
 * appended to the list headed at D_00387AE4 + 8. */
void GsPkt_EmitColorVert(u8 *arg0) {
    u8 tmp[0x20];
    u8 *q;
    u8 *pkt;
    u8 *ent;
    u8 *prev;
    f32 x;
    f32 y;
    f32 z;
    f32 a;
    u32 lim;

    *(u64 *)(tmp + 0x18) = *(u64 *)(D_0036E9B0 + 8);
    *(u64 *)(tmp + 0x10) = *(u64 *)D_0036E9B0;
    q = *(u8 **)(arg0 + 0x38);
    func_00129DB8(tmp, tmp + 0x10, q, *(f32 *)(q + 0x20));

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x40;
    *(u64 *)(pkt + 0x20) = 0x46;
    *(u64 *)(pkt + 0x00) = 0xA0000003ULL;
    *(u64 *)(pkt + 0x10) = 0x4400000000008001ULL;
    *(u64 *)(pkt + 0x18) = 0x4410;

    x = *(f32 *)(tmp + 0x0);
    y = *(f32 *)(tmp + 0x4);
    z = *(f32 *)(tmp + 0x8);
    a = *(f32 *)(tmp + 0xC);
    lim = 0x80000000u;

    if (2147483648.0f <= x) {
        pkt[0x28] = (u8)(((u32)(s32)(x - 2147483648.0f)) | lim);
    } else {
        pkt[0x28] = (u8)(s32)x;
    }
    if (2147483648.0f <= y) {
        pkt[0x29] = (u8)(((u32)(s32)(y - 2147483648.0f)) | lim);
    } else {
        pkt[0x29] = (u8)(s32)y;
    }
    if (2147483648.0f <= z) {
        pkt[0x2A] = (u8)(((u32)(s32)(z - 2147483648.0f)) | lim);
    } else {
        pkt[0x2A] = (u8)(s32)z;
    }
    if (2147483648.0f <= a) {
        pkt[0x2B] = (u8)(((u32)(s32)(a - 2147483648.0f)) | lim);
    } else {
        pkt[0x2B] = (u8)(s32)a;
    }

    *(u16 *)(pkt + 0x30) = 0x7000;
    *(u16 *)(pkt + 0x32) = 0x7200;
    *(u16 *)(pkt + 0x38) = 0x9000;
    *(u16 *)(pkt + 0x3A) = 0x8E00;
    *(u64 *)(pkt + 0x30) = *(u64 *)(pkt + 0x30) | 0x00FFFFFF00000000ULL;
    *(u64 *)(pkt + 0x38) = *(u64 *)(pkt + 0x38) | 0x00FFFFFF00000000ULL;
    *(f32 *)(pkt + 0x2C) = 1.0f;
    pkt[0x3F] = 0xFF;
    pkt[0x37] = 0xFF;

    ent = D_00387AE4 + 8;
    prev = *(u8 **)(ent + 4);
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(ent + 4) = pkt;
}
