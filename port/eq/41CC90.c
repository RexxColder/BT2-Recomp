#include "common.h"

extern u8 *D_0042FD74 __attribute__((section(".data")));

/* 0x0041CC90: for i in 0..2 (B = D_0042FD74): *(B+4i+0x84) = *(B+4i+0x94) = *(B+4i+0xA0) = *(B+4i+0xAC) = 0.
 * t1 = arg0 0 -> 1, 1 -> 5, 2 -> 8, 3 -> 11, else 0; a1 = 4*t1 + 0x80; pk = *(B + 4*arg0 + 0x70) (pointer). Then for j in
 * 0..2: *(B + a1 + 4j) = *(pk + 0x10) (word). */
void func_0041CC90(s32 arg0) {
    u8 *b;
    s32 t1;
    s32 a1;
    u8 *pk;
    s32 i;

    for (i = 0; i < 3; i++) {
        b = D_0042FD74;
        *(s32 *)(b + i * 4 + 0x84) = 0;
        b = D_0042FD74;
        *(s32 *)(b + i * 4 + 0x94) = 0;
        b = D_0042FD74;
        *(s32 *)(b + i * 4 + 0xA0) = 0;
        b = D_0042FD74;
        *(s32 *)(b + i * 4 + 0xAC) = 0;
    }

    switch (arg0) {
    case 0:
        t1 = 1;
        break;
    case 1:
        t1 = 5;
        break;
    case 2:
        t1 = 8;
        break;
    case 3:
        t1 = 11;
        break;
    default:
        t1 = 0;
        break;
    }

    a1 = t1 * 4 + 0x80;
    for (i = 0; i < 3; i++) {
        b = D_0042FD74;
        pk = *(u8 **)(b + arg0 * 4 + 0x70);
        *(s32 *)(b + a1 + i * 4) = *(s32 *)(pk + 0x10);
    }
}
