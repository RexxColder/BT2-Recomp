#include "m2c_macros.h"

M2C_UNK func_00308338(s8 *);                        /* extern */
extern s8 D_00366530 __attribute__((section(".data")));

void func_00308360(void) {
    s32 var_s1;
    s8 *var_s0;

    var_s0 = &D_00366530;
    var_s1 = 0xF;
    do {
        if (*var_s0 == 1) {
            func_00308338(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x30;
    } while (var_s1 >= 0);
}
