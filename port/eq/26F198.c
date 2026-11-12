#include "common.h"

s32 memset(s32 arg0, s32 arg1, s32 arg2);

u8 *func_0026F198(u8 *arg0) {
    u8 *var_s0;
    u32 temp_v1;
    u32 var_a1;

    var_a1 = 0;
    temp_v1 = *(u32 *)(arg0 + 4);
    var_s0 = *(u8 **)arg0;
    if (temp_v1 != 0) {
loop_2:
        var_a1 += 1;
        if (*(s32 *)var_s0 == 0) {
            memset((s32)var_s0, 0, 0x38);
            return var_s0;
        }
        var_s0 += 0x38;
        if (var_a1 >= temp_v1) {
            goto block_6;
        }
        goto loop_2;
    }
block_6:
    return NULL;
}
