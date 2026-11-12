#include "m2c_macros.h"

void func_002E81C0(u16 *arg0, u16 *arg1, s32 arg2) {
    s32 var_a2;
    u16 *var_a0;
    u16 *var_a1;
    u16 temp_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    if (var_a2 > 0) {
        do {
            temp_v0 = *var_a1;
            var_a1 += 1;
            var_a2 -= 1;
            *var_a0 = temp_v0;
            var_a0 += 1;
        } while (var_a2 > 0);
    }
}
