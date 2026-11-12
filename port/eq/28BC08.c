#include "common.h"

/* 0x0028BC08: D_00387EB4 = 0; memset(D_0038A638, 0, 0x60); i = D_00387EB4; p = D_0038A638 + i * 8;
   *(s32 *)p = 0x5010; *(s32 *)(p + 4) = 0x1BAFEF. */
extern u8 D_0038A638[];
extern s32 D_00387EB4;

void func_0028BC08(void) {
    u8 *p;

    D_00387EB4 = 0;
    memset(D_0038A638, 0, 0x60);
    p = D_0038A638 + D_00387EB4 * 8;
    *(s32 *)(p + 0) = 0x5010;
    *(s32 *)(p + 4) = 0x1BAFEF;
}
