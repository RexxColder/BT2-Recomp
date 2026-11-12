#include "common.h"

s32 func_002E9F60(s32 arg0, s32 arg1, s32 arg2, u32 arg3) {
    s32 temp_v1;

    temp_v1 = arg2 + arg3;
    if (arg0 == 0) {
        return (((u32)(arg1 + temp_v1 + 0x21) / arg3) * arg3) - arg2;
    }
    return (((u32)(arg1 + temp_v1 + 0x39) / arg3) * arg3) - arg2;
}
