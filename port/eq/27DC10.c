#include "common.h"

void func_0027DC10(u8 *arg0) {
    s32 temp_v1;
    s32 var_a1;
    u8 temp_a0;
    u8 temp_v0_2;
    u8 *temp_v0;
    u8 *temp_v1_2;

    var_a1 = 0;
    arg0[0] = 0;
    arg0[1] = 0;
    arg0[2] = 0;
    arg0[3] = 0;
    do {
        temp_v1 = ((var_a1 & 0xE7) | ((var_a1 & 8) * 2) | ((s32)(var_a1 & 0x10) >> 1)) * 4;
        if (temp_v1 != 0) {
            if (var_a1 == 0xFF) {
                temp_v0 = arg0 + temp_v1;
                temp_v0[3] = 0;
                temp_v0[0] = 0;
                temp_v0[1] = 0;
                temp_v0[2] = 0;
            } else {
                temp_v0_2 = (var_a1 * 8) & 0xFF;
                temp_v1_2 = arg0 + temp_v1;
                temp_a0 = (temp_v0_2 != 0) ? temp_v0_2 : 0x80;
                temp_v1_2[3] = 0x80;
                temp_v1_2[1] = temp_a0;
                temp_v1_2[0] = temp_a0;
                temp_v1_2[2] = 0;
            }
        }
        var_a1 += 1;
    } while (var_a1 < 0x100);
}
