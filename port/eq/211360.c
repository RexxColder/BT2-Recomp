#include "common.h"

/* 0x00211360: p = arg0 + arg1 * 4. A = word at p + 0x2B0; B = (word at p + 0x2F4 & arg2) != 0 ? word at p + 0x378
 * : word at p + 0x440. Returns ((A & ~B) & arg2) != 0. */
s32 func_00211360(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *p = arg0 + arg1 * 4;
    s32 a;
    s32 b;

    a = *(s32 *)(p + 0x2B0);
    if ((*(s32 *)(p + 0x2F4) & arg2) != 0) {
        b = *(s32 *)(p + 0x378);
    } else {
        b = *(s32 *)(p + 0x440);
    }
    return ((a & ~b) & arg2) != 0;
}
