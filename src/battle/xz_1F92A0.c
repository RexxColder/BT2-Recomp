#include "common.h"

/* Battle obj: decrements 4x4 countdown timers at +0x14/+0xAF0 and clears the matching flags at +0xAFA, then
   calls BtlObjXf_Update and func_001F9138 on a state change (0x1F92A0). */

s32 BtlObjXf_Update(s32 arg0);
void func_001F9138(s32 arg0);
s32 func_001FA3A0(s32 arg0);
s32 func_001FA3A8(s32 arg0);

void BtlObj_TickTimers(s32 arg0) {
    s32 *var_v1;
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s8 *var_a0;
    s32 temp_v0;
    s32 base;

    base = arg0 + 0x14;
    var_a2 = 0;
    var_a3 = 0;
    do {
        var_a1 = 1;
        temp_v0 = (var_a3 + var_a2) * 4;
        var_a0 = (s8 *)(temp_v0 + arg0 + 0xAFA);
        var_v1 = (s32 *)(temp_v0 + base + 0xAF0);
        do {
            temp_v0_2 = *var_v1 - 1;
            *var_v1 = temp_v0_2;
            if (temp_v0_2 <= 0) {
                *var_v1 = 0;
                *var_a0 = 0;
            }
            var_a1 -= 1;
            var_a0 += 1;
            var_v1 += 1;
        } while (var_a1 >= 0);
        var_a2 += 1;
        var_a3 += 4;
    } while (var_a2 < 4);
    temp_s1 = func_001FA3A8(BtlObjXf_Update(arg0));
    temp_a0 = func_001FA3A8(func_001FA3A0(arg0)) & 0x50;
    if ((temp_a0 == 0x40) && ((temp_s1 & 0x50) != temp_a0)) {
        func_001F9138(arg0);
    }
}
