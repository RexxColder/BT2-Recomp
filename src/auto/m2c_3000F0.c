#include "m2c_macros.h"

M2C_UNK func_00300CD0(s8 *);                        /* extern */
extern s8 D_00357110 __attribute__((section(".data")));

void func_003000F0(void) {
    s32 var_s1;
    s8 *var_s0;

    var_s0 = &D_00357110;
    var_s1 = 0x1F;
    do {
        if (*var_s0 == 1) {
            func_00300CD0(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x238;
    } while (var_s1 >= 0);
}
