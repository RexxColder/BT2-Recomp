#include "common.h"

s32 func_002D07B0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002D8AD8(void *arg0);
void func_002D05E8(void *arg0, s32 arg1, s32 arg2);

void func_002CD408(u8 *arg0) {
    u8 *temp_a1;
    u32 temp_a1_2;
    u32 temp_a1_3;
    s32 var_s0;

    temp_a1 = arg0 + 0xA0C;
    temp_a1_2 = (*(s32 *)(temp_a1 + 0x18) == 1);
    temp_a1_3 = (((*(s32 *)(temp_a1 + 0x14)) ^ 1) == 0) ? (temp_a1_2 | 2) : temp_a1_2;
    var_s0 = 2;
    if (temp_a1_3 != 2) {
        if (temp_a1_3 >= 3U) {
            var_s0 = 3;
            if (temp_a1_3 == 3) {
                var_s0 = func_002D07B0(arg0, 0x19, 2, 1);
                if ((var_s0 == 0) && ((func_002D8AD8(arg0) != 0) ||
                                      (((s32 (*)(void *, s32))func_002D07B0)(arg0, 0x48) == 0))) {
                    var_s0 = 3;
                }
            }
        } else {
            var_s0 = 1;
            if (temp_a1_3 != 1) {
                var_s0 = 3;
            }
        }
    }
    func_002D05E8(arg0, 0x19, var_s0);
}
