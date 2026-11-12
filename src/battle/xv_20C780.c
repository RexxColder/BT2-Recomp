#include "common.h"

s32 func_001F94A0(s32 arg0, s32 arg1);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

/* when D_00387930 is set and arg0 < 2: func_001F94A0(func_00211288(arg0), 0) (tail call), else 0 */
s32 func_0020C780(u32 arg0) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        return func_001F94A0(func_00211288(arg0), 1);
    }
    return 0;
}
