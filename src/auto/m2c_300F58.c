#include "m2c_macros.h"

M2C_UNK func_00300F50(s8 *);                        /* extern */
extern s8 D_0035B888 __attribute__((section(".data")));

void func_00300F58(void) {
    s32 var_s1;
    s8 *var_s0;

    var_s0 = &D_0035B888;
    var_s1 = 0x27;
    do {
        if (*var_s0 != 0) {
            func_00300F50(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x38;
    } while (var_s1 >= 0);
}
