#include "common.h"

void func_0026EA88(s32 arg0);
void func_0026EB08(s32 arg0);
extern u8 *D_00387A10;

void func_00259DE0(void) {
    s32 var_s0;
    s32 var_s1;
    u8 *temp_a0_2;

    var_s0 = 0;
    var_s1 = 2;
    *(s32 *)(D_00387A10 + 0xAC) = 0;
    do {
        var_s1 -= 1;
        func_0026EA88((s32)(D_00387A10 + var_s0 + 4));
        temp_a0_2 = D_00387A10 + var_s0;
        var_s0 += 0x28;
        func_0026EB08((s32)(temp_a0_2 + 4));
    } while (var_s1 >= 0);
}
