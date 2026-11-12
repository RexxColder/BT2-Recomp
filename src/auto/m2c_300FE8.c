#include "m2c_macros.h"

extern s8 D_0035B888 __attribute__((section(".data")));

s8 *func_00300FE8(void) {
    s32 var_a1;
    s8 *temp_v0;
    s8 *var_a3;

    var_a3 = NULL;
    var_a1 = 0;
    if (D_0035B888 == 0) {
        var_a3 = &D_0035B888;
    } else {
loop_2:
        var_a1 += 1;
        if (var_a1 < 0x28) {
            temp_v0 = (var_a1 * 0x38) + &D_0035B888;
            if (*temp_v0 == 0) {
                var_a3 = temp_v0;
            } else {
                goto loop_2;
            }
        }
    }
    return var_a3;
}
