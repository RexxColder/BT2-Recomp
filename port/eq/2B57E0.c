#include "common.h"

s32 Rand_Range(s32 arg0, s32 arg1);
extern u8 D_00378500[] __attribute__((section(".data")));

s32 func_002B57E0(u32 arg0) {
    s32 temp_a1;
    s32 var_v0;
    s32 var_v1;

    temp_a1 = arg0 < 3U;
    var_v1 = 2;
    if (arg0 != 2) {
        if (temp_a1 == 0) {
            var_v1 = 3;
            if (arg0 != 3) {
                var_v0 = 4;
                var_v1 = 4;
                goto block_8;
            }
        } else {
            var_v0 = 1;
            var_v1 = 1;
block_8:
            if (arg0 != var_v0) {
                Rand_Range((s32)D_00378500, temp_a1);
                var_v1 = 1;
            }
        }
    }
    return var_v1;
}
