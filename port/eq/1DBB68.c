#include "common.h"

s32 func_001DBB68(s32 arg0, s32 arg1, s32 arg2) {
    f32 temp_f1;
    s32 *temp_a0;
    s32 *temp_a1;
    s32 temp_a3_2;
    s32 temp_t3;
    s32 temp_v1;
    s32 var_a2;
    s32 var_t0;
    s32 var_t1;
    s32 *temp_v0;
    s32 *var_a1;
    s32 *var_v1;
    s32 temp_a3;
    s32 temp_v0_2;

    var_a2 = arg2;
    temp_t3 = var_a2 * 4;
    temp_v0 = (s32 *)(temp_t3 + arg0);
    var_t1 = arg1 - 1;
    temp_v1 = var_t1 * 4;
    var_t0 = temp_v1;
    var_v1 = (s32 *)(temp_v1 + arg0);
    temp_f1 = *(f32 *)((u8 *)*temp_v0 + 0x88);
    var_a1 = temp_v0;
loop_1:
    var_v1 += 1;
    var_t0 += 4;
    var_t1 += 1;
    if (*(f32 *)((u8 *)*var_v1 + 0x88) < temp_f1) {
        goto loop_1;
    }
    var_a2 -= 1;
loop_3:
    var_a1 -= 1;
    if (var_t1 < var_a2) {
        temp_v0_2 = *var_a1;
        if (temp_f1 < *(f32 *)((u8 *)temp_v0_2 + 0x88)) {
            var_a2 -= 1;
        } else {
            temp_a3 = *var_v1;
            *var_v1 = temp_v0_2;
            *var_a1 = temp_a3;
            goto loop_1;
        }
        goto loop_3;
    }
    temp_a1 = (s32 *)(temp_t3 + arg0);
    temp_a0 = (s32 *)(var_t0 + arg0);
    temp_a3_2 = *temp_a0;
    *temp_a0 = *temp_a1;
    *temp_a1 = temp_a3_2;
    return var_t1;
}
