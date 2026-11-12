#include "common.h"

void func_0027E968(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 var_a2;
    s32 temp_p;

    var_a2 = 0;
    do {
        temp_a0 = ((var_a2 & 0xE7) | ((var_a2 & 8) * 2) | ((var_a2 & 0x10) >> 1)) * 4;
        temp_p = arg1 + temp_a0;
        if (var_a2 == 0xFF) {
            *(u8 *)(temp_p + 3) = (u8)-0x80;
            *(u8 *)(temp_p + 0) = (u8)-1;
            *(u8 *)(temp_p + 1) = (u8)-1;
            *(u8 *)(temp_p + 2) = (u8)-1;
        } else {
            *(u8 *)(temp_p + 0) = (u8)-1;
            *(u8 *)(temp_p + 1) = (u8)-1;
            *(u8 *)(temp_p + 2) = (u8)-1;
            *(u8 *)(temp_p + 3) = *(u8 *)(arg0 + 0x524);
        }
        var_a2 += 1;
    } while (var_a2 < 0x100);
}
