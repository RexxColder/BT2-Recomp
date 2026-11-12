#include "common.h"

s32 BtlMenu_IsControls(u8 *arg0);
s32 BtlMenu_IsSkillList(u8 *arg0); /* GUESS arity: a0 = arg0 passes through */
s32 func_00106958(u8 *arg0);

void func_001075F0(u8 *arg0) {
    s32 temp_a1;
    s32 temp_s1;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_v0;
    s32 var_v0_2;
    u8 *base;

    temp_s1 = *(s32 *)(arg0 + 0x18);
    if ((BtlMenu_IsSkillList(arg0) == 0) && (BtlMenu_IsControls(arg0) == 0) && (func_00106958(arg0) == 0)) {
        temp_a1 = *(s32 *)(arg0 + 4);
        base = *(u8 **)arg0;
loop_4:
        var_a0 = *(s32 *)(arg0 + 0x18);
        var_v0 = var_a0 < temp_a1;
        if (var_a0 < 0) {
            var_a0 = temp_a1 - 1;
            *(s32 *)(arg0 + 0x18) = var_a0;
            var_v0 = var_a0 < temp_a1;
        }
        var_v0_2 = var_a0 << 5;
        if (var_v0 == 0) {
            *(s32 *)(arg0 + 0x18) = 0;
            var_a0 = 0;
            var_v0_2 = 0 << 5;
        }
        temp_v0_2 = var_a0 + 1;
        if (*(u8 *)(base + var_v0_2 + 0x19) != 0) {
            *(s32 *)(arg0 + 0x18) = temp_v0_2;
            if (temp_v0_2 != temp_s1) {
                goto loop_4;
            }
        }
    }
}
