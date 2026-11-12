#include "common.h"

u8 *func_00106A00(u8 *arg0, s32 arg1, s32 arg2);

u8 *func_00106A00(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s0;
    s32 var_s3;
    u8 *base;
    u8 *temp_a0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *var_a2;

    var_a2 = 0;
    var_s3 = 0;
    if (*(s32 *)(arg0 + 4) > 0) {
        base = *(u8 **)arg0;
        var_s0 = 0;
        if (arg1 == *(s32 *)(base + 4)) {
            var_a2 = base;
        } else {
            for (;;) {
                temp_v1 = base + var_s0;
                var_s0 += 0x20;
                temp_v0 = *(u8 **)(temp_v1 + 8);
                if (temp_v0 != 0) {
                    var_a2 = func_00106A00(temp_v0, arg1, 0);
                    if (var_a2 != 0) {
                        break;
                    }
                }
                var_s3 += 1;
                if (var_s3 >= *(s32 *)(arg0 + 4)) {
                    break;
                }
                temp_a0 = base + var_s0;
                if (arg1 == *(s32 *)(temp_a0 + 4)) {
                    var_a2 = temp_a0;
                    break;
                }
            }
        }
    }
    return var_a2;
}
