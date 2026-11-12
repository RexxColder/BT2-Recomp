#include "common.h"

void func_002D3F38(s32 arg0, s32 arg1, s32 arg2);

s32 func_002D3F08(s32 arg0) {
    s32 temp_a1;
    u8 *temp_v0;

    temp_a1 = arg0 + 0x3678;
    temp_v0 = (u8 *)arg0 + 0x2150;
    *(s32 *)(temp_v0 + 8) = temp_a1;
    func_002D3F38(arg0, temp_a1, *(s32 *)(temp_v0 + 0x10));
    return 0;
}
