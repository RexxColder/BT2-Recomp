#include "common.h"

extern u8 D_00388728[] __attribute__((section(".data")));

void func_001489A8(void) {
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;
    u8 *var_v0;

    var_a0 = 0;
    var_a1 = 0;
    do {
        var_v1 = 5;
        var_v0 = D_00388728 + ((var_a1 + var_a0) * 8) + 0x14;
        do {
            var_v1 -= 1;
            *(s32 *)var_v0 = 0;
            var_v0 -= 4;
        } while (var_v1 >= 0);
        var_a0 += 1;
        var_a1 += 2;
    } while (var_a0 < 7);
}
