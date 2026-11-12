#include "common.h"

s32 func_002D14F8(u8 *arg0, s32 arg1, s32 arg2); /* tail-calls 0x2D1510 with a0-a2 */
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);

s32 func_002D13D0(u8 *arg0, s32 *arg1, s32 *arg2) {
    s32 temp_a1;
    s32 var_v0;
    u8 *temp_s1;
    u8 *temp_s3;

    temp_s1 = arg0 + 0xE48;
    temp_s3 = arg0 + 0xD30;
    var_v0 = func_002D14F8(arg0, (s32)arg1, (s32)arg2);
    temp_a1 = *arg2;
    if (temp_a1 != 1) {
        if (temp_a1 != *(s32 *)(temp_s3 + 0x148)) {
            if (*(s32 *)(temp_s1) != 0) {
                *arg1 += func_002E0A98(*(s32 *)(temp_s1 + 0x24), temp_a1, *(s32 *)(temp_s1 + 0x28));
            }
        } else {
            *arg1 += *(s32 *)(temp_s3 + 0x144);
        }
    }
    return var_v0;
}
