#include "common.h"

s32 func_002BE878(s32 arg0);
u8 *func_002BF2C0(u8 *arg0);
s32 func_002F4CE0(s32 arg0);
s32 func_002F4D68(s32 arg0);
s32 func_002F4DF0(s32 arg0);

void func_002BE7C0(u8 *arg0) {
    s32 temp_s0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    u8 *temp_v0;

    temp_v0 = func_002BF2C0(arg0);
    if (temp_v0 != NULL && *(s32 *)(temp_v0 + 0) == 0) {
        temp_s0 = **(s32 **)(arg0 + 0x2004);
        if (func_002BE878(temp_s0) != 0) {
            *(s32 *)(temp_v0 + 0x10) = func_002F4D68(temp_s0);
            *(s32 *)(temp_v0 + 0x14) = func_002F4CE0(temp_s0);
            temp_v0_2 = func_002F4DF0(temp_s0);
            *(s32 *)(temp_v0 + 0xC) = temp_v0_2;
            *(s32 *)(temp_v0 + 0) = 1;
            *(s32 *)(temp_v0 + 8) = 1;
            temp_v0_3 = *(s32 *)(temp_v0 + 0x10) * temp_v0_2 * 9;
            *(s32 *)(temp_v0 + 4) = ((temp_v0_3 < 0) ? (temp_v0_3 + 0xF) : temp_v0_3) >> 4;
        }
    }
}
