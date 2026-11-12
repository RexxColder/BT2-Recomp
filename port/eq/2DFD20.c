#include "common.h"

s32 func_002DFBC8(s32 arg0);
s32 func_002DFDF0(s32 arg0, s32 arg1, s32 arg2);

s32 func_002DFD20(s32 arg0, s32 arg1, s32 arg2) {
    u8 *base;
    u8 *a1p;
    s32 a2v;
    s32 s1;
    s32 temp;

    base = (u8 *)arg0;
    a1p = base + 0x250;
    a2v = *(s32 *)(base + 0x194);
    if (*(s32 *)(base + 0x384) != 0) {
        *(s32 *)(base + 0x384) = 0;
        *(s32 *)(base + 0x388) = *(s32 *)(base + 0x388) + 1;
        *(s32 *)(a1p + 0xC) = *(s32 *)(a1p + 0xC) + 1;
        if (a2v == 0) {
            return -2;
        }
        *(s32 *)(a1p + 0x10) = *(s32 *)(a1p + 0x10) + 1;
    }
    s1 = (a2v != 0) ? -3 : -2;
    for (;;) {
        temp = func_002DFBC8(arg2);
        if (temp != 0) {
            if (temp & arg1) {
                s1 = 0;
                break;
            }
            if (func_002DFDF0(arg2, 1, 4) == 4) {
                continue;
            }
        }
        break;
    }
    return s1;
}
