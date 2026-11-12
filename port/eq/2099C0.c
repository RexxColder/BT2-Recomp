#include "common.h"

s32 func_00211288(u32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217488(s32 arg0);
extern s32 D_00387930;

s32 func_002099C0(u32 arg0) {
    s32 temp_v0;
    s32 v;

    if (D_00387930 == 0) {
        return 0;
    }
    if (arg0 >= 2U) {
        return 0;
    }
    temp_v0 = func_00211288(arg0);
    if (func_00211310(temp_v0, 0xE, 0x2000) == 0) {
        return 0;
    }
    if (func_00211310(temp_v0, 9, 0x10000) == 0) {
        return 0;
    }
    v = func_00217488(temp_v0);
    if (v < 0x2E) {
        return 0;
    }
    if (v < 0x34) {
        return 1;
    }
    if (v < 0x50) {
        return 0;
    }
    if (v < 0x56) {
        return 1;
    }
    return 0;
}
