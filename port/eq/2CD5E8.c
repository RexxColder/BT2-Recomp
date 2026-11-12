#include "common.h"

s32 func_002CDC28(s32 arg0, s32 arg1, s32 arg2);

s32 func_002CD5E8(s32 arg0) {
    u8 *temp_a2;
    u8 *temp_a1;
    s32 temp_a1_2;
    s32 var_v0;

    temp_a2 = (u8 *)arg0 + 0xA0C;
    var_v0 = 1;
    temp_a1 = (u8 *)arg0 + 0xD30;
    if (*(s32 *)(temp_a2 + 0x38) != 0 && *(s32 *)(temp_a2 + 0x14) != 0 && *(s32 *)(temp_a1 + 0x2B0) == 0) {
        temp_a1_2 = *(s32 *)(temp_a2 + 0xB4);
        if (*(s32 *)(temp_a1 + 0x2CC) < temp_a1_2) {
            var_v0 = func_002CDC28(arg0, temp_a1_2, (s32)temp_a2) != 0;
        }
    }
    return var_v0;
}
