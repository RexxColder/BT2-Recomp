#include "common.h"

s32 func_002D3078(s32 arg0, s32 arg1);

s32 func_002D0688(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 6 && arg2 == 1) {
        if (func_002D3078(arg0, 3) == 0) {
            return 0;
        }
    }
    if (arg1 != 5) {
        return 1;
    }
    if (arg2 != 1) {
        return 1;
    }
    if (func_002D3078(arg0, 2) != 0) {
        return 1;
    }
    return 0;
}
