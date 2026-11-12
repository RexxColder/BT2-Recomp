#include "common.h"

s32 func_002C3210(s32 arg0, s32 arg1);
s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002CAC18(s32 arg0, s32 arg1);

s32 func_002C5960(s32 arg0, s32 *arg1) {
    *arg1 = 0;
    if (func_002C3210(arg0, (s32)arg1) != 0) {
        return func_002C2FF0(0, 0xFF000182);
    }
    *arg1 = func_002CAC18(arg0, 0xFF000000);
    return 0;
}
