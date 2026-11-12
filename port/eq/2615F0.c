#include "common.h"

extern s32 D_003B2654 __attribute__((section(".data")));
s32 func_00261060(s32 a0, s32 a1);
s32 func_00267550(s32 a0, s32 a1, s32 a2);

s32 func_002615F0(s32 arg0, s32 arg1) {
    s32 s0;
    s32 r;

    if ((D_003B2654 & 0x100) != 0) {
        return D_003B2654 & 0x100;
    }
    if ((u32)arg1 >= 0xB) {
        return 0;
    }
    switch (arg1) {
    case 0:
        s0 = 0;
        break;
    case 1:
    case 2:
        s0 = 3;
        break;
    case 3:
        s0 = 4;
        break;
    case 4:
        s0 = 7;
        break;
    case 5:
        s0 = 0xD;
        break;
    case 6:
        s0 = 0xE;
        break;
    case 7:
        s0 = 0xF;
        break;
    case 8:
        s0 = 0x10;
        break;
    case 9:
        s0 = 0x11;
        break;
    default:
        s0 = 0x12;
        break;
    }
    r = func_00261060((s32)((u16)arg0), arg1);
    return func_00267550(r, s0, 0);
}
