#include "common.h"

s32 BtlChar_GetPos(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_003126C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0020EAA8(s32 arg0, s32 arg1, s32 arg2) {
    u8 *temp_a1;
    u8 *temp_a3;

    temp_a3 = (u8 *)arg0 + (arg2 * 0x10);
    temp_a1 = temp_a3 + 0x830;
    if (*(s32 *)((u8 *)arg0 + 0x8B0) & (1 << arg2)) {
        func_003126C8(arg1, (s32)temp_a1, arg2, (s32)temp_a3);
        return;
    }
    {
        s32 pos = BtlChar_GetPos(arg0, (s32)temp_a1, arg2, (s32)temp_a3);
        func_003126C8(arg1, pos + 0x10, arg2, (s32)temp_a3);
    }
}
