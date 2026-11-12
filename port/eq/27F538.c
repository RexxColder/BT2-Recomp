#include "common.h"

void func_0027F2C8(s32 arg0, s32 *arg1);
void func_0027F368(s32 *arg0, u8 *arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_00387A40;

void func_0027F538(void *arg0) {
    s32 sp[64];
    u8 *temp_a0;
    u8 *var_a1;
    u8 *temp_a1_3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s0_2;
    s32 var_s1_2;

    var_s0 = 0;
    memset(sp, 0, 0x100);
    temp_a0 = D_00387A40;
    if (*(s32 *)(temp_a0 + 4) > 0) {
        var_s1 = 0;
        do {
            var_a1 = *(u8 **)D_00387A40 + var_s1;
            var_s1 += 0x18580;
            var_s0 += 1;
            func_0027F368(sp, var_a1);
        } while (var_s0 < *(s32 *)(D_00387A40 + 4));
    }
    var_s0_2 = 0;
    if (*(s32 *)(D_00387A40 + 0xC) > 0) {
        var_s1_2 = 0;
        var_a1 = *(u8 **)(D_00387A40 + 8);
loop_5:
        temp_a1_3 = var_a1 + var_s1_2;
        var_s1_2 += 0x1520;
        if (*(s32 *)(temp_a1_3 + 0xAF0) & 2) {
            func_0027F368(sp, temp_a1_3);
        }
        var_s0_2 += 1;
        if (var_s0_2 < *(s32 *)(D_00387A40 + 0xC)) {
            var_a1 = *(u8 **)(D_00387A40 + 8);
            goto loop_5;
        }
    }
    func_0027F2C8(*(s32 *)(*(u8 **)((u8 *)arg0 + 0x9C0) + 0x490), sp);
}
