#include "m2c_macros.h"

M2C_UNK func_002F3E90(s8 *);                        /* extern */
extern s8 D_0034AEE0 __attribute__((section(".data")));

void func_002F4090(void) {
    s32 var_s1;
    s8 *var_s0;

    var_s0 = &D_0034AEE0;
    var_s1 = 0xF;
    do {
        if (*var_s0 == 1) {
            func_002F3E90(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0xC8;
    } while (var_s1 >= 0);
}
