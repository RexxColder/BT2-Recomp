#include "common.h"

s32 func_002CA9A0(void *arg0) {
    s32 temp_v1;
    s32 var_v0;
    s32 temp_a0;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x36B0);
    var_v0 = 0;
    if (temp_v1 != 0) {
        temp_a0 = *(s32 *)((u8 *)arg0 + 0x1FC0);
        var_v0 = (*(s32 *)((u8 *)temp_a0 + 0x88) > 0) ? (temp_v1 + 0xAD0) : 0;
    }
    return var_v0;
}
