#include "m2c_macros.h"

M2C_UNK func_002E8558(s16 *);                       /* extern */
extern s16 D_00347BF8 __attribute__((section(".data")));

void func_002E86A8(void) {
    s16 *var_s0;
    s32 var_s1;

    var_s0 = &D_00347BF8;
    var_s1 = 0xF;
    do {
        if (*var_s0 == 1) {
            func_002E8558(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 130;
    } while (var_s1 >= 0);
}
