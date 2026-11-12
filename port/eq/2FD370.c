#include "common.h"

extern s8 D_00356080[] __attribute__((section(".data")));

s32 func_002FD370(void) {
    s8 *var_a0;
    s32 var_a1;

    var_a1 = 0;
    var_a0 = D_00356080;
    do {
        if ((var_a0[0] == 1) && (var_a0[2] == 2)) {
            return 1;
        }
        var_a1 += 1;
        var_a0 += 0x48;
    } while (var_a1 < 0x28);
    return 0;
}
