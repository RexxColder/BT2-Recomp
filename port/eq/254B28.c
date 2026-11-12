#include "common.h"

void func_0026E908(void *arg0);
void func_0028BB60(void *arg0);
extern u8 *D_003879D0;

void func_00254B28(void) {
    s32 var_s0;
    s32 var_s1;
    u8 *temp_a0;
    u8 *temp_a0_2;

    var_s0 = 1;
    var_s1 = 0;
    temp_a0 = D_003879D0;
loop_1:
    var_s0 -= 1;
    temp_a0_2 = temp_a0 + var_s1;
    var_s1 += 0x28;
    func_0026E908(temp_a0_2 + 0x28);
    if (var_s0 >= 0) {
        goto loop_1;
    }
    func_0028BB60(*(u8 **)(D_003879D0 + 8));
    func_0028BB60(*(u8 **)(D_003879D0 + 0xC));
    func_0028BB60(*(u8 **)(D_003879D0 + 0x10));
    func_0028BB60(*(u8 **)(D_003879D0 + 0x14));
    func_0028BB60(*(u8 **)(D_003879D0 + 0x18));
    func_0028BB60(*(u8 **)(D_003879D0 + 4));
    func_0028BB60(*(u8 **)(D_003879D0 + 0));
    func_0028BB60(D_003879D0);
}
