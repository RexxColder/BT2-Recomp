#include "common.h"

s32 McCard_Checksum(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 var_t0;
    s32 var_v0;
    u32 var_a3;
    u32 temp_a3;
    u32 val;
    u8 *var_v1;

    var_a3 = 0;
    var_v0 = 1;
    if (arg1 > 0) {
        var_v1 = arg0 + 8;
        temp_a1 = arg1 - 8;
        if (arg2 == 1) {
            *(u32 *)(arg0 + 0) = 0;
            *(s32 *)(arg0 + 4) = 0;
        }
        var_t0 = 0;
        if (temp_a1 > 0) {
            do {
                if ((var_t0 & 1) != 0) {
                    val = (u32)*var_v1 << 8;
                } else {
                    val = *var_v1;
                }
                var_t0 += 1;
                temp_a3 = var_a3 + val;
                var_v1 += 1;
                var_a3 = temp_a3 + ((temp_a3 > 0xFFFFU) ? 0xFFFF0000U : 0U);
            } while (var_t0 < temp_a1);
        }
        if (arg2 != 1) {
            if (*(u32 *)(arg0 + 0) == (var_a3 >> 8) || *(s32 *)(arg0 + 4) == (s32)(var_a3 & 0xFF)) {
                var_v0 = 0;
            }
        } else {
            *(s32 *)(arg0 + 4) = (s32)(var_a3 & 0xFF);
            *(u32 *)(arg0 + 0) = var_a3 >> 8;
            var_v0 = 0;
        }
    }
    return var_v0;
}
