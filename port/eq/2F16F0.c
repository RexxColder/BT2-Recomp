#include "common.h"

s32 func_002E7BE0(s32 arg0);
s32 func_002E7C00(s32 arg0);

s32 func_002F16F0(void *arg0) {
    if (func_002E7BE0(*(s32 *)((u8 *)arg0 + 0x4)) <= 0) {
        return 0;
    }
    if ((u32)(*(u8 *)((u8 *)arg0 + 0x1) - 2) >= 2U) {
        return 0;
    }
    return func_002E7C00(*(s32 *)((u8 *)arg0 + 0x4));
}
