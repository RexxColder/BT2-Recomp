#include "common.h"

s32 func_002D1070(s32 arg0);
s32 func_002D10A8(s32 arg0, s32 arg1);

void func_002D1000(s32 arg0) {
    u8 *temp_s1;

    temp_s1 = (u8 *)arg0 + 0xD30;
    if (func_002D1070(arg0) != 0) {
        *(s32 *)(temp_s1 + 0x2A8) = *(s32 *)(temp_s1 + 0x2A8) + *(s32 *)(temp_s1 + 0x2AC);
    }
    if (func_002D10A8(arg0, (s32)temp_s1) != 0) {
        *(s32 *)(temp_s1 + 0x2CC) = *(s32 *)(temp_s1 + 0x2CC) + *(s32 *)(temp_s1 + 0x2AC);
    }
}
