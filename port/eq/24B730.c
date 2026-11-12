#include "common.h"

extern u8 *D_003876A0;

s32 func_0024B730(s32 arg0, s32 arg1) {
    s32 base;
    s32 t2;
    s32 a2;
    s32 addr;
    s32 tmp;
    u8 v;
    u8 w;

    if (arg0 == 0xE || arg0 == 0x2D || arg0 == 0x5E) {
        return 0;
    }
    if (arg1 == 0xE || arg1 == 0x2D || arg1 == 0x5E) {
        return 0;
    }
    base = *(s32 *)(D_003876A0 + 0x74);
    t2 = arg0 * 0x10 + base + 0xC;
    if (arg0 == arg1) {
        return 1;
    }
    a2 = 0;
    addr = t2;
    for (;;) {
        v = *(u8 *)addr;
        tmp = arg1 * 0x10 + base + 0xC + a2;
        if (v != 0xFF && v == arg1) {
            return 1;
        }
        a2 += 1;
        w = *(u8 *)tmp;
        if (w != 0xFF && w == arg0) {
            return 1;
        }
        addr = t2 + a2;
        if (a2 >= 4) {
            return 0;
        }
    }
}
