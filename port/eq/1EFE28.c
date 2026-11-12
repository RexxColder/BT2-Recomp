#include "common.h"

void sceVu0RotTransPersN(f32 *dst, f32 *m, f32 *src, s32 n, s32 flag);
s32 func_001F2A18(s32 arg0, s32 arg1, s32 arg2);
extern s32 gBtlCamView;
extern s32 D_00387AD8;
extern s32 D_00387AE0;

/* Projects two points through the camera matrix, then appends an 80-byte GS packet
 * (tag, two 64-bit register sets, two vertex words) to the packet list at D_00387AD8 and links it
 * into the table at D_00387AE0 indexed by (2 * depth + a17). */
void func_001EFE28(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8,
                   f32 a9, f32 a10, f32 a11, f32 a12, f32 a13, f32 a14,
                   s64 a15, s32 a16, s32 a17) {
    f32 v31[8];
    s32 v32[8];
    s32 pk;
    s32 t1;
    s32 b16;
    s32 entry;
    s32 old;
    s32 s0 = a17;

    v31[0] = a9;
    v31[1] = a10;
    v31[2] = a11;
    v31[3] = 1.0f;
    v31[4] = a12;
    v31[5] = a13;
    v31[6] = a14;
    v31[7] = 1.0f;

    sceVu0RotTransPersN((f32 *)v32, (f32 *)(gBtlCamView + 0x100), v31, 2, 1);

    if (func_001F2A18(v32[0], v32[1], v32[2]) != 0) {
        return;
    }
    if (func_001F2A18(v32[4], v32[5], v32[6]) != 0) {
        return;
    }
    t1 = (v32[2] + v32[6]) >> 9;
    if ((u32)t1 >= 0x1000u) {
        return;
    }

    pk = D_00387AD8;
    D_00387AD8 = pk + 0x50;
    if (pk == 0) {
        return;
    }

    b16 = (s32)(s8)a16;

    *(s64 *)(pk + 0x00) = 0x00000000A0000004LL;
    *(s64 *)(pk + 0x10) = 0x6400000000008001LL;
    *(s64 *)(pk + 0x18) = 0x00F41410LL;
    *(s64 *)(pk + 0x20) = ((s64)b16 * 512) | 0x49LL;
    *(u8 *)(pk + 0x28) = (u8)a1;
    *(u8 *)(pk + 0x29) = (u8)a2;
    *(u8 *)(pk + 0x2A) = (u8)a3;
    *(u8 *)(pk + 0x2B) = (u8)a4;
    *(f32 *)(pk + 0x2C) = 1.0f;

    *(u16 *)(pk + 0x30) = (u16)v32[0];
    *(u16 *)(pk + 0x32) = (u16)v32[1];
    *(s64 *)(pk + 0x30) = (*(s64 *)(pk + 0x30) & 0xFF000000FFFFFFFFLL)
                          | ((s64)(v32[2] & 0xFFFFFF) << 32);
    *(u8 *)(pk + 0x37) = 0xFF;

    *(u8 *)(pk + 0x38) = (u8)a5;
    *(u8 *)(pk + 0x39) = (u8)a6;
    *(u8 *)(pk + 0x3A) = (u8)a7;
    *(u8 *)(pk + 0x3B) = (u8)a8;
    *(f32 *)(pk + 0x3C) = 1.0f;

    *(u16 *)(pk + 0x40) = (u16)v32[4];
    *(u16 *)(pk + 0x42) = (u16)v32[5];
    *(s64 *)(pk + 0x40) = (*(s64 *)(pk + 0x40) & 0xFF000000FFFFFFFFLL)
                          | ((s64)(v32[6] & 0xFFFFFF) << 32);
    *(u8 *)(pk + 0x47) = 0xFF;

    entry = D_00387AE0 + ((2 * t1 + s0) << 3);
    old = *(s32 *)(entry + 4);
    *(s32 *)(old + 4) = pk;
    *(s32 *)(entry + 4) = pk;
}
