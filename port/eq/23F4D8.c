#include "common.h"

s32  func_0023F4D8(s32 arg0, s32 arg1, s32 arg2) {
    u32 v1 = *(u32 *)(arg0 + 0x1530);
    u32 a0 = *(u32 *)(v1 + 0x958);
    u32 addr = (u32)arg2 + (u32)arg1 * 6 + a0;

    return (u8)(*(u8 *)(addr + 0x16));
}
