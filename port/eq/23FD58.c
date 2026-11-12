#include "common.h"

s32  func_0023FD58(u8 *arg0, u32 arg1) {
    u8 *temp_a2;
    u8 *temp_v1;
    u32 idx;
    idx = (arg1 < 3U) ? arg1 : 0U;
    temp_a2 = *(u8 **)(arg0 + 0x1530);
    temp_v1 = *(u8 **)(temp_a2 + 0x958);
    return (u8)(*(u8 *)(temp_v1 + idx + 0xC2));
}
