#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);

s32 func_002C71F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg1 == 0) {
        return 0;
    }
    if (arg1 == -2 || arg1 == -3) {
        if (arg2 > 0) {
            return 0;
        }
        return func_002C2FF0(arg0, arg1);
    }
    return func_002C2FF0(arg0, arg3);
}
