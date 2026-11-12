#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387F2C;

s32  func_0024B6C8(u32 arg0) {
    s32 v;
    s32 t;
    u8 *base;

    if (arg0 >= 0x83U) {
        return (u8)(2);
    }
    v = 2;
    if (*(s16 *)(D_00387F2C + 0x254E) != 0) {
        v = 3;
    }
    if (*(s16 *)(D_00387F2C + 0x255E) != 0) {
        v += 1;
    }
    if (*(s16 *)(D_00387F2C + 0x2572) != 0) {
        v += 1;
    }
    base = *(u8 **)(D_003876A0 + 0x74);
    t = base[arg0 * 0x10 + 9];
    if (*(s16 *)(D_00387F2C + 0x2586) != 0) {
        v += 1;
    }
    return (u8)((t < v) ? (u8)t : (u8)v);
}
