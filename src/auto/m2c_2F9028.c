#include "m2c_macros.h"

M2C_UNK func_002F8F30(s32 *);                       /* extern */
extern s32 D_00354F38 __attribute__((section(".data")));

void func_002F9028(void) {
    s32 *var_s0;
    s32 var_s1;

    var_s0 = &D_00354F38;
    var_s1 = 0xF;
    do {
        if (*var_s0 == 1) {
            func_002F8F30(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 15;
    } while (var_s1 >= 0);
}
