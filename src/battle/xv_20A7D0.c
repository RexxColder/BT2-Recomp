#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00217488(s32 arg0);
extern s32 D_00387930;

/* 1 when D_00387930 is set, arg0 < 2 and r = func_00217488(func_00211288(arg0)) is in [0xB8, 0xC1); 0 otherwise */
s32 func_0020A7D0(u32 arg0) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        s32 r = func_00217488(func_00211288(arg0));
        if (r < 0xC1) {
            if (r >= 0xB8) {
                return 1;
            }
        }
    }
    return 0;
}
