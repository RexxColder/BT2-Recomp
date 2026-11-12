#include "common.h"

void func_002B3C68(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0;
    temp_v0 = arg0 + 0x160;
    *(u8 **)(arg0 + 0x178) = temp_v0;
    *(s32 *)(arg0 + 0x160) = arg1;
    *(s32 *)(temp_v0 + 4) = arg2;
    *(s32 *)(temp_v0 + 8) = arg3;
}
