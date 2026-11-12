#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211328(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

s32 func_0020BE80(u32 arg0) {
    s32 temp_v0;

    if (D_00387930 == 0) {
        return 0;
    }
    if (!(arg0 < 2U)) {
        return 0;
    }
    temp_v0 = func_00211288(arg0);
    if (func_00211310(temp_v0, 0, 1) == 0) {
        return 0;
    }
    if (func_00211328(temp_v0, 0, 1) != 0) {
        return 0;
    }
    return 1;
}
