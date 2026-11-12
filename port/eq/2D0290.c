#include "common.h"

s32 func_002C1180(void *arg0);
s32 func_002D0380(void *arg0);
void func_002D03C8(void *arg0);

void func_002D0290(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s1;
    s32 var_s3;
    u8 *temp_s0;
    u8 *temp_s4;

    temp_s4 = (u8 *)arg0 + 0xDC4;
    temp_s0 = *(u8 **)((u8 *)arg0 + 0x36B0);
    if (func_002C1180(arg0) == 0) {
        var_s3 = 0;
        if (*(s32 *)(temp_s0 + 0xDAC) <= 0) {
            var_s1 = 0;
            if (*(s32 *)((u8 *)arg0 + 0x36B8) != -3) {
                var_s1 = *(s32 *)(temp_s0 + 0xDD4);
            }
            if (var_s1 >= 0) {
                temp_v0 = func_002D0380(arg0);
                if (temp_v0 != -1) {
                    var_s3 = 1;
                    *(s32 *)(temp_s0 + 0xDAC) = var_s1 + temp_v0;
                }
            }
        }
        if (*(s32 *)(temp_s0 + 0xDB0) <= 0) {
            temp_v0_2 = *(s32 *)(temp_s4 + 0x24);
            if (temp_v0_2 > 0) {
                *(s32 *)(temp_s0 + 0xDB0) = temp_v0_2;
                var_s3 = 1;
                *(s32 *)(temp_s0 + 0xDB4) = *(s32 *)(temp_s4 + 0x28);
            }
        }
        if (var_s3 != 0) {
            func_002D03C8(arg0);
        }
    }
}
