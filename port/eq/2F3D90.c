#include "common.h"

s32 func_002F3A30(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_003016E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002F3D90(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_002F3A30(2, arg0 + 0x400, arg1 - 0x400, arg3);
    if (temp_v0 != 0) {
        func_003016E0(temp_v0, arg0, 0x400, arg3);
    }
    return temp_v0;
}
