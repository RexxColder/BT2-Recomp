#include "common.h"

s32 func_002E7BE0(s32 arg0);
s32 func_002E7BF0(s32 arg0, s32 arg1);

s32 func_002F1688(s32 arg0, s32 arg1) {
    if (func_002E7BE0(*(s32 *)((u8 *)arg0 + 4)) > 0) {
        if ((u32)(*(u8 *)((u8 *)arg0 + 1) - 2) >= 2U) {
            return -0x80;
        }
        return func_002E7BF0(*(s32 *)((u8 *)arg0 + 4), arg1);
    }
    return -0x80;
}
