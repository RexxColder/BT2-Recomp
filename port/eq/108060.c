#include "common.h"

u8 *func_00108060(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);

u8 *func_00108060(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    s32 temp_a3;
    s32 var_s2;
    u8 *temp_a2;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *var_s0;
    u8 *var_t0;
    u8 *base;

    var_t0 = 0;
    var_s0 = arg0;
    var_s2 = 0;
loop_3:
    temp_a3 = *(s32 *)(arg1 + 4);
loop_4:
    if (var_s2 < temp_a3) {
        base = *(u8 **)arg1;
        temp_a2 = base + (var_s2 << 5);
        temp_v1 = temp_a2;
        var_s2 += 1;
        if ((*(s32 *)(temp_v1 + 0x14) == 1) && (*(u8 *)(temp_v1 + 0x1D) != 0)) {
            var_t0 = temp_v1;
            if (var_s0 != 0) {
                var_t0 = *(u8 **)var_s0 + (*(s32 *)(var_s0 + 0x18) << 5);
            }
        } else {
            temp_v0 = *(u8 **)(temp_a2 + 8);
            if (temp_v0 != 0) {
                if (var_s0 == 0) {
                    var_s0 = arg1;
                }
                var_t0 = func_00108060(var_s0, temp_v0, temp_a2, temp_a3);
                if (var_t0 == 0) {
                    goto loop_3;
                }
            } else {
                goto loop_4;
            }
        }
    }
    return var_t0;
}
