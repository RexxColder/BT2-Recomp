#include "common.h"

/* 0x001F9978: n = func_001F9618(a0); return (*(u8 **)(D_00387930) + 0x1C)[0x2B1 - n + 0xA] (u8). */
extern u8 D_00387930[];
s32 func_001F9618(s32 arg0);

s32 func_001F9978(s32 a0) {
    u8 *v1;
    s32 n;
    u8 *p;

    n = func_001F9618(a0);
    v1 = *(u8 **)D_00387930;
    p = *(u8 **)(v1 + 0x1C) + (0x2B1 - n);
    return p[0xA];
}
