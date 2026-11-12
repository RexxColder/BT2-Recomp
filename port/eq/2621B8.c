#include "common.h"

extern u8 D_00388D48[] __attribute__((section(".data")));

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);

void func_002621B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    u8 *base = D_00388D48;
    u16 idx = (u16)a1;
    u8 *s0;
    u8 *s1;
    s32 v1;
    s32 r;

    s0 = *(u8 **)(base + 4) + idx * 48;
    s1 = *(u8 **)(base + 8);
    *(s32 *)(s1 + 8) = a2;
    v1 = a0 & 0xFF;
    *(s32 *)(s0 + 0x10) = a3;
    *(s32 *)(s0 + 0x14) = t0;
    if (*(s32 *)(s1 + 8) >= 0) {
        r = func_00100ED0(*(s32 *)(s1 + 8), *(s32 *)(s1 + 0), v1 != 0);
        v1 = 0;
        *(s32 *)(s1 + 0) = r;
    }
    a0 = *(s32 *)(s0 + 0x10);
    if (a0 >= 0) {
        r = func_00100ED0(a0, *(s32 *)(s0 + 0x28), v1 != 0);
        v1 = 0;
        *(s32 *)(s0 + 0x28) = r;
    }
    a0 = *(s32 *)(s0 + 0x14);
    if (a0 >= 0) {
        r = func_00100ED0(a0, *(s32 *)(s0 + 0x2C), v1 != 0);
        *(s32 *)(s0 + 0x2C) = r;
    }
    *(s32 *)(base + 0x10) = idx;
}
