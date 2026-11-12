#include "common.h"

s32 func_002CF580(u8 *arg0, u32 arg1, u32 arg2, s32 arg3) {
    s32 temp_t0;
    s32 temp_t3;
    s32 count;
    s32 var_t2;
    s32 var_t1;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_a0;
    u32 temp_t4;
    u32 temp_v1;
    u8 *temp_v0_2;

    count = *(s32 *)(arg0 + 8);
    temp_t4 = arg2 + arg3;
    temp_t3 = *(s32 *)(arg0 + 4);
    var_t2 = 0;
    var_t1 = *(s32 *)(arg0 + 0x10);
    if (count <= 0) {
        return -1;
    }
    var_v0 = var_t1 * 0x10;
    for (;;) {
        temp_v0_2 = *(u8 **)arg0 + var_v0;
        temp_v1 = *(u32 *)(temp_v0_2 + 8);
        temp_t0 = arg1 < temp_v1;
        temp_a0 = temp_v1 + *(u32 *)(temp_v0_2 + 0xC);
        if (temp_t4 >= temp_a0) {
            var_v0_2 = var_t1 + 1;
            if (temp_t0 == 0) {
                if (arg1 < temp_a0) {
                    return var_t2;
                }
            }
            /* block_11 / block_12 */
        } else if ((temp_t0 != 0) || (arg1 >= temp_t4)) {
            var_v0_2 = var_t1 + 1;
            if (arg1 >= arg2) {
                if (arg1 < (temp_a0 - arg3)) {
                    return var_t2;
                }
            }
        } else {
            return var_t2;
        }
        var_t2 += 1;
        if (var_v0_2 >= temp_t3) {
            var_v0_2 = (var_t1 - temp_t3) + 1;
        }
        var_t1 = var_v0_2;
        if (var_t2 >= count) {
            return -1;
        }
        var_v0 = var_t1 * 0x10;
    }
}
