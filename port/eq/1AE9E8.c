#include "common.h"

s32 func_001B03A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_00387858;

void func_001AE9E8(s32 arg0) {
    s32 var_a3;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_a1;

    var_a3 = 0;
    do {
        temp_v0 = var_a3 * 4;
        var_a3 += 1;
        temp_a1 = temp_v0 + 0xD0;
        if (*(s32 *)(D_00387858 + 0xC + temp_a1) <= 0) {
            *(s32 *)(D_00387858 + 0xC + temp_v0 + 0xC0) = 0;
            *(s32 *)(D_00387858 + temp_a1 + 4) = 0;
        }
    } while (var_a3 < 2);
    *(s32 *)(D_00387858 + 0x590 + 0x104) = 0;
    temp_a0 = *(s32 *)(*(s32 *)(arg0 + 0x24) + 4);
    if (temp_a0 != 0) {
        func_001B03A8(temp_a0, 1, 0, var_a3);
    }
}
