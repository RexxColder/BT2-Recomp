#include "common.h"

void func_002B2BE8(s32 arg0, u16 *arg1) {
    s32 temp_t1;
    s32 i;
    s32 a1;
    u16 *var_t0;
    u16 v1;
    u16 v2;

    temp_t1 = arg0 + 0xA;
    var_t0 = arg1;
    i = 0;
    do {
        a1 = i + 0x10;
        v1 = *(u16 *) ((((i < 0) ? (i + 0x1F) : i) >> 5) * 2 + temp_t1 + 0x40);
        v2 = *(u16 *) ((a1 - ((((a1 < 0) ? (i + 0x2F) : a1) >> 5) << 5)) * 2 + temp_t1 + 0x40);
        i += 1;
        *var_t0 ^= v2 ^ v1;
        var_t0 += 1;
    } while (i < 0x400);
}
