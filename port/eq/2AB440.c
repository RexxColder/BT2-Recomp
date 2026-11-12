#include "common.h"

s32 func_002A86E8(s32 *a0, u8 *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern u8 func_002AB1A0[] __attribute__((section(".data")));

s32 func_002AB440(s32 arg0, s32 pad1, s32 pad2, s32 arg3) {
    s32 sp[8];

    sp[0] = 0;
    sp[1] = 0x33D3;
    sp[2] = -1;
    sp[3] = -1;
    sp[4] = -1;
    sp[5] = arg0;
    return func_002A86E8(sp, func_002AB1A0, 0, arg3, -1, arg0);
}
