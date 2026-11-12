#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00211360(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

s32 func_0020BD60(u32 arg0) {
    if (D_00387930 == 0) {
        return 0;
    }
    if (arg0 >= 2) {
        return 0;
    }
    return func_00211360(func_00211288(arg0), 0x10, 0x04000000) != 0;
}
