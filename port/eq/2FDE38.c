#include "common.h"

s32 func_002FDDD8(s32 arg0, s32 arg1);
s32 func_002FDDE8(s32 arg0, s32 arg1);
s32 func_002FDE08(s32 arg0, s32 arg1);
s32 func_002FDE10(s32 arg0, s32 arg1);
s32 func_002FDE28(s32 arg0, s32 arg1);
s32 func_002FDE30(s32 arg0, s32 arg1);

s32 func_002FDE38(s32 arg0, s32 arg1) {
    s32 r;

    r = 0;
    if (arg0 == 0) {
        return 0;
    }
    switch (arg1) {
    case 0xC8:
        r = func_002FDDD8(arg0, arg1);
        break;
    case 0xC9:
        r = func_002FDDE8(arg0, arg1);
        break;
    case 0xCA:
    case 0xCC:
        r = func_002FDE08(arg0, arg1);
        break;
    case 0xCB:
    case 0xCD:
        r = func_002FDE10(arg0, arg1);
        break;
    case 0x12B:
        r = 1;
        break;
    case 0x12D:
        r = func_002FDE28(arg0, arg1);
        break;
    case 0x12E:
        r = func_002FDE30(arg0, arg1);
        break;
    default:
        r = 0;
        break;
    }
    return r;
}
