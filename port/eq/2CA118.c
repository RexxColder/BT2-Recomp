#include "common.h"

void func_002CA118(u8 *arg0) {
    s32 var_a1;
    s32 var_a2;

    *(s32 *)(arg0 + 0) = 0;
    var_a1 = 0x10;
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 8) = 0;
    *(s32 *)(arg0 + 0xC) = 0;
    var_a2 = 0xF;
    *(s32 *)(arg0 + 0x10) = 0;
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = 0;
    do {
        var_a2 -= 1;
        *(s32 *)(arg0 + 0xC + var_a1) = 0;
        *(s32 *)(arg0 + 0x10 + var_a1) = 0;
        var_a1 += 8;
    } while (var_a2 >= 0);
}
