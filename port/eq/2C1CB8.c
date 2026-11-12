#include "common.h"

s32 func_002C1D50(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C1CB8(s32 arg0, s32 arg1, s32 arg2) {
    if (func_002C1D50(arg0, arg1, arg2) != 0) {
        return 1;
    }
    if (func_002C1D50(arg0 + 2, arg1 - 2, arg2) != 0) {
        return 1;
    }
    if (func_002C1D50(arg0 + 1, arg1 - 1, arg2) != 0) {
        return 1;
    }
    return func_002C1D50(arg0 + 3, arg1 - 3, arg2) != 0;
}
