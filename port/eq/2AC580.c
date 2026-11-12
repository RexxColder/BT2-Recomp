#include "common.h"

extern u8 D_00344F30[] __attribute__((section(".data")));
extern u8 D_003B2654[] __attribute__((section(".data")));

void func_002AC580(void) {
    u8 *b;
    u8 *s0;
    u8 *p;
    s32 t1;
    s32 t2;
    s32 a2;
    s32 t0;
    s32 v1;

    b = D_003B2654;
    memset(b, 0, 0x5C);
    s0 = b - 0x54;
    memset(b + 0x5C, 0, 0x35C);
    t1 = *(s32 *)(s0 + 4);
    a2 = 0;
    t0 = 0;
    if (t1 < 0) {
        *(s32 *)(s0 + 4) = 0;
        *(s32 *)(b + 4) = *(s32 *)(s0 + 0) + 0x2FF;
        return;
    }
    t2 = *(s32 *)(s0 + 0);
    *(s32 *)(b + 0x40) = *(s32 *)(D_00344F30 + 8);
    *(s32 *)(b + 0x3C) = *(s32 *)(D_00344F30 + 0xC);
    if (t2 != 0) {
        p = D_00344F30 + 0xC;
        do {
            v1 = *(s32 *)(p - 8);
            p += 0x10;
            t0 += 1;
            a2 += v1 * 3;
        } while (t0 != t2);
        *(s32 *)(b + 0x3C) = *(s32 *)(p + 0);
        *(s32 *)(b + 0x40) = *(s32 *)(p - 4);
    }
    *(s32 *)(b + 4) = a2 + (t1 * 3) + 0x21;
}
