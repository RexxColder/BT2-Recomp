#include "common.h"

s32 func_00202DA0(s32 arg0, s32 arg1);
s32 func_00202FC8(s32 arg0, s32 arg1);

void func_00203040(s32 arg0, s32 arg1) {
    u8 *base;
    s32 s1;
    s32 a1;
    s32 temp_a1;
    s32 temp_v1;
    u8 *a0;

    base = (u8 *)arg0;
    s1 = func_00202FC8(arg0, arg1);
    if (s1 < 0) {
        return;
    }
    *(s32 *)func_00202DA0(arg0, s1) = -1;
    a1 = s1;
    *(s8 *)(func_00202DA0(arg0, s1) + 8) = 0;
    if (s1 < 4) {
        a0 = base + s1 * 4 + 0x1410;
        do {
            a1 += 1;
            *(s32 *)a0 = *(s32 *)(a0 + 4);
            a0 += 4;
        } while (a1 < 4);
    }
    temp_a1 = *(s32 *)(base + 0x1180);
    *(s32 *)(base + 0x1420) = -1;
    *(s32 *)(base + 0x1184) = *(s32 *)(base + 0x1184) - 1;
    if (s1 < temp_a1) {
        *(s32 *)(base + 0x1180) = temp_a1 - 1;
    }
    temp_v1 = *(s32 *)(base + 0x118C);
    if (s1 < temp_v1) {
        *(s32 *)(base + 0x118C) = temp_v1 - 1;
    }
}
