#include "common.h"

s32 func_002BF2C0(void *arg0) {
    s32 temp_v1;
    s32 var_v0;
    s32 temp_a0;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x36B0);
    var_v0 = 0;
    if (temp_v1 != 0) {
        temp_a0 = *(s32 *)((u8 *)arg0 + 0x2004);
        var_v0 = (*(s32 *)((u8 *)temp_a0 + 0x40) > 0) ? (temp_v1 + 0xD0C) : 0;
    }
    return var_v0;
}
