#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);

s32 func_002C11E8(s32 arg0) {
    if (func_002D07B0(arg0, 0x31) != 0) {
        return 1;
    }
    return func_002D07B0(arg0, 0x39) != 0;
}
