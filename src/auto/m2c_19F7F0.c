#include "m2c_macros.h"

extern s32 D_003877F8;

void func_0019F7F0(void) {
    s32 *temp_v1;
    s32 var_a0;
    s32 var_a1;

    var_a1 = 0x1C0;
    var_a0 = 0xC;
    do {
        temp_v1 = D_003877F8 + var_a1;
        var_a1 += 4;
        if (*temp_v1 != 0) {
            *temp_v1 = 0;
        }
        var_a0 -= 1;
    } while (var_a0 >= 0);
}
