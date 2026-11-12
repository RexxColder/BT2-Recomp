#include "m2c_macros.h"

M2C_UNK func_002EBB38(s8 *);                        /* extern */
extern s8 D_00366A58 __attribute__((section(".data")));

void func_002EBC18(void) {
    s32 var_s1;
    s8 *var_s0;

    var_s0 = &D_00366A58;
    var_s1 = 0xF;
    do {
        if (*var_s0 == 1) {
            func_002EBB38(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x48;
    } while (var_s1 >= 0);
}
