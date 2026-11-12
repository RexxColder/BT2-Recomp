#include "common.h"

u16 *func_002A20D0(s32 *arg0, s32 arg1) {
    s32 temp_a2;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;
    s32 var_v1;
    u16 *temp_a3;
    u16 temp_v1_2;
    u32 temp_a1;
    u8 *temp_v1;
    u8 *base;

    temp_v1 = (u8 *)*arg0;
    var_t2 = 0;
    temp_a1 = arg1 & 0xFFFF;
    var_t0 = *(s32 *)(temp_v1 + 0x14) - 1;
    var_t1 = var_t0 < 0;
    if (var_t1 != 0) {
        return 0;
    }
    base = (u8 *)*(s32 *)(temp_v1 + 0x10);
    var_v1 = var_t0 - var_t2;
    while (1) {
        temp_a2 = var_t2 + (var_v1 / 2);
        temp_a3 = (u16 *)(base + temp_a2 * 6);
        temp_v1_2 = *temp_a3;
        if (temp_v1_2 < temp_a1) {
            var_t2 = temp_a2 + 1;
        } else if (temp_a1 < temp_v1_2) {
            var_t0 = temp_a2 - 1;
        } else {
            return temp_a3;
        }
        var_t1 = var_t0 < var_t2;
        if (var_t1 != 0) {
            return 0;
        }
        var_v1 = var_t0 - var_t2;
    }
}
