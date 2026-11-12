#include "common.h"

s32 func_002F1988(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002F1A60(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002F1B78(s32 arg0, s32 arg1) {
    if (arg1 < 0x100) {
        return func_002F1988(0, 0, 0, arg0);
    }
    return func_002F1A60(0, 0, 0, arg0);
}
