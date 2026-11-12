#include "common.h"

f32 func_001DA640(void *arg0);
void func_00129B28(void *arg0, void *arg1, void *arg2);
extern u8 *D_00387E9C;

void func_001D57B0(u8 *arg0) {
    f32 *var_s1;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 temp_f3;
    u8 temp_v1;

    temp_v1 = *(u8 *)(arg0 + 0x57);
    if (temp_v1 == 0) {
        temp_f0 = *(f32 *)(arg0 + 0x48) - 1.0f;
        *(f32 *)(arg0 + 0x48) = temp_f0;
        if (temp_f0 <= 0.0f) {
            *(f32 *)(arg0 + 0x48) = 0.0f;
            *(u8 *)(arg0 + 0x5C) = 1;
            *(u8 *)(arg0 + 0x57) = 1;
            goto block_5;
        }
    } else if (temp_v1 == 1) {
        goto block_5;
    }
    goto check_end;

block_5:
    var_s1 = (f32 *)(arg0 + 0x10);
    func_00129B28(arg0, arg0, var_s1);
    temp_f1 = *var_s1;
    *var_s1 = temp_f1 + (temp_f1 * *(f32 *)(arg0 + 0x24));
    temp_f3 = *(f32 *)(arg0 + 0x14);
    temp_f2 = *(f32 *)(arg0 + 0x18);
    temp_f0_2 = *(f32 *)(arg0 + 0x24);
    temp_f1_2 = *(f32 *)(arg0 + 0x28) + *(f32 *)(arg0 + 0x2C);
    *(f32 *)(arg0 + 0x28) = temp_f1_2;
    *(f32 *)(arg0 + 0x18) = temp_f2 + (temp_f2 * temp_f0_2);
    *(f32 *)(arg0 + 0x14) = temp_f3 + (temp_f3 * temp_f0_2);
    if (temp_f1_2 < 0.0f) {
        *(f32 *)(arg0 + 0x28) = 0.0f;
    }
    *(f32 *)(arg0 + 0x30) = *(f32 *)(arg0 + 0x30) + *(f32 *)(arg0 + 0x34);
    *(f32 *)(arg0 + 0x38) = *(f32 *)(arg0 + 0x38) - *(f32 *)(arg0 + 0x3C);
    *(f32 *)(arg0 + 0x14) = *(f32 *)(arg0 + 0x14) + *(f32 *)(arg0 + 0x40);
    *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x44) - -1.0f;
    *(s32 *)(arg0 + 0x50) = *(s32 *)(arg0 + 0x50) + 1;
    if ((func_001DA640(var_s1) > 1.0f) && !(*(s32 *)(arg0 + 0x50) & 1)) {
        *(s8 *)(arg0 + 0x5A) = 1;
    }

check_end:
    if ((*(u8 *)(arg0 + 0x5C) != 0) && (*(f32 *)(arg0 + 0x38) <= 0.0f)) {
        *(f32 *)(arg0 + 0x38) = 0.0f;
        *(u8 *)(arg0 + 0x5C) = 0;
        *(s8 *)(arg0 + 0x5B) = 0;
        *(s32 *)(D_00387E9C + 0x1430) = *(s32 *)(D_00387E9C + 0x1430) - 1;
    }
}
