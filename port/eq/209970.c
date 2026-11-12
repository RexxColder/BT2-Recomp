#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

s32 func_00209970(u32 arg0) {
    s32 ret;

    if (D_00387930 == 0) {
        return 0;
    }
    if (arg0 >= 2) {
        return 0;
    }
    ret = func_00211310(func_00211288(arg0), 0xE, 0x2000);
    return ret != 0;
}
