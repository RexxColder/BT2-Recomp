#include "m2c_macros.h"

M2C_UNK func_002F0F90(s8 *);                        /* extern */
extern s8 D_003534B0 __attribute__((section(".data")));

void func_002F12C8(void) {
    s8 *var_s0;

    var_s0 = &D_003534B0;
    do {
        if (*var_s0 == 1) {
            func_002F0F90(var_s0);
        }
        var_s0 += 0xAC;
    } while ((s32) var_s0 < (s32) (&D_003534B0 + 0xAC0));
}
