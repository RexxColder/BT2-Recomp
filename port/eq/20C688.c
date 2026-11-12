#include "common.h"

s32 func_00203118(s32 arg0);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

s32 func_0020C688(u32 arg0) {
    if (D_00387930 != 0 && arg0 < 2U) {
        return func_00203118(func_00211288((s32)arg0));
    }
    return 0;
}
