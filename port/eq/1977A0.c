#include "common.h"

s32 func_001977A0(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a3;
    s32 var_a3_2;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x0);
    temp_a3 = temp_v0 & 0x2;
    if ((arg1 & 0xFF) != 0) {
        var_a3_2 = temp_a3 | 0x20;
    } else {
        var_a3_2 = ((arg2 & 0xFF) != 0) ? (temp_a3 | 0x40) : temp_a3;
    }
    temp_v1 = *(s32 *)((u8 *)arg0 + 0xC);
    if (temp_v1 != 3) {
        var_a3 = ((temp_v1 ^ 4) == 0) ? (var_a3_2 | 0x100) : var_a3_2;
    } else {
        var_a3 = var_a3_2 | 0x80;
    }
    return ((temp_v0 & 0x20) == 0) ? var_a3 : (var_a3 | 0x10);
}
