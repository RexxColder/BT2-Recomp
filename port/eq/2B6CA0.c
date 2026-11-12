#include "common.h"

void Rand_Range(void *arg0, s32 arg1);
s32 func_002CCA28(s32 arg0);
extern u8 D_00378AD8[] __attribute__((section(".data")));

s32 func_002B6CA0(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x3C);
    if (temp_v1 != 0) {
        temp_v0 = func_002CCA28(temp_v1);
        var_v1 = 0;
        if (temp_v0 != 0) {
            var_v1 = 1;
            if (temp_v0 != 1) {
                Rand_Range(D_00378AD8, temp_v0);
                var_v1 = 0;
            }
        }
        var_v0 = var_v1;
    }
    return var_v0;
}
