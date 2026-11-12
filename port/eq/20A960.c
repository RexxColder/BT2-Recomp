#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00217488(s32 arg0);
extern s32 D_00387930;

s32 func_0020A960(u32 arg0) {
    s32 r;

    if (D_00387930 == 0 || !(arg0 < 2U)) {
        return 0;
    }
    r = func_00217488(func_00211288(arg0));
    if (r == 0x7F || r == 0x85) {
        return 1;
    }
    return 0;
}
