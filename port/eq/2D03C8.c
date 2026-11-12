#include "common.h"

s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);

void func_002D03C8(s32 arg0) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0;
    s32 temp_s0;

    temp_s0 = *(s32 *) (arg0 + 0x36B0);
    var_v0 = *(s32 *) (temp_s0 + 0xDD0);
    if (var_v0 <= 0) {
        var_a0 = *(s32 *) (temp_s0 + 0xDC4);
        var_a2 = *(s32 *) (temp_s0 + 0xDC8);
        var_a1 = *(s32 *) (temp_s0 + 0xDCC);
        if ((var_a0 <= 0) || (var_a2 <= 0)) {
            var_v0 = *(s32 *) (temp_s0 + 4);
            if (var_v0 <= 0) {
                if (var_a0 <= 0) {
                    var_a0 = *(s32 *) (temp_s0 + 0xDAC);
                }
                if (var_a2 <= 0) {
                    var_a2 = *(s32 *) (temp_s0 + 0xDB0);
                    var_a1 = *(s32 *) (temp_s0 + 0xDB4);
                }
                if ((var_a0 > 0) && (var_a2 > 0)) {
                    var_v0 = func_002E0A98(var_a0, var_a1, var_a2);
                }
            }
        } else {
            var_v0 = func_002E0A98(var_a0, var_a1, var_a2);
        }
    }
    *(s32 *) (temp_s0 + 0xDA8) = var_v0;
}
