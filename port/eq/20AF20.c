#include "common.h"

s32 *func_00202E60(s32 arg0, s32 arg1);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

s32 func_0020AF20(u32 arg0, s32 arg1) {
    s32 *p;

    if (D_00387930 == 0 || !(arg0 < 2U)) {
        return 0;
    }
    p = func_00202E60(func_00211288(arg0), arg1);
    if (*p > 0) {
        return 0;
    }
    return 1;
}
