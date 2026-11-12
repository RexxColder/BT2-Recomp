#include "common.h"

s32 func_002DCE50(s32 arg0);
s32 func_002DCFE8(s32 arg0, s32 arg1, s32 arg2);

s32 func_002DE6B8(u8 *arg0, s32 *arg1) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v0_3;

    if (*(s32 *)(arg0 + 0x35C) == 0) {
        temp_v0 = func_002DCFE8(arg1[0], arg1[1], 0x40);
        temp_v1 = temp_v0 + 4;
        if (temp_v0 != 0) {
            temp_v0_2 = func_002DCFE8(temp_v1, arg1[1] - (temp_v1 - arg1[0]), -1);
            if (temp_v0_2 != 0) {
                temp_v0_3 = func_002DCE50(temp_v0_2);
                if (temp_v0_3 & 0x10) {
                    *(s32 *)(arg0 + 0x35C) = 2;
                } else if (temp_v0_3 != 0) {
                    *(s32 *)(arg0 + 0x35C) = 1;
                }
            }
        }
    }
    return *(s32 *)(arg0 + 0x35C);
}
