#include "common.h"

s32 func_0020A658(u32 arg0);
s32 func_00211288(u32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

s32 func_0020C038(u32 arg0) {
    s32 temp_v0;

    if (D_00387930 == 0) {
        return -1;
    }
    if (arg0 >= 2U) {
        return -1;
    }
    if (func_0020A658(arg0) != 0) {
        return -1;
    }
    temp_v0 = func_00211288(arg0);
    if (func_00211310(temp_v0, 0xF, 0x400) != 0) {
        return 0;
    }
    if (func_00211310(temp_v0, 0xF, 0x800) != 0) {
        return 1;
    }
    if (func_00211310(temp_v0, 0xF, 0x1000) != 0) {
        return 2;
    }
    if (func_00211310(temp_v0, 0xF, 0x2000) != 0) {
        return 3;
    }
    if (func_00211310(temp_v0, 0xF, 0x4000) != 0) {
        return 4;
    }
    return -1;
}
