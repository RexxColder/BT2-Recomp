#include "common.h"

s32 func_00241C50(u8 *arg0, u32 arg1) {
    u8 *temp_v0;
    s32 idx;
    idx = (arg1 != 0U) ? 1 : 0;
    temp_v0 = *(u8 **)(arg0 + 0x1530);
    return *(s32 *)(*(u8 **)(temp_v0 + 0x984) + idx * 4);
}
