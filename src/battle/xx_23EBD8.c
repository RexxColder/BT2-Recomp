#include "m2c_macros.h"

void *Battle_GetSetup(void *arg0);
s32 func_001F9898(void *arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_00218128(void *arg0, s32 arg1);
u32 func_0023E520(void *arg0);
s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

// Scales a value by the setup's ratio and divides it by an event count (func_0023EBD8).
s32 func_0023EBD8(void *arg0) {
    f32 temp_f20;
    s32 temp_ret;
    f32 temp_f1;
    f32 c100;

    temp_f20 = (f32) M2C_FIELD(Battle_GetSetup(arg0), s32 *, 8);
    temp_f1 = (f32) func_001F9898(arg0);
    c100 = M2C_BITWISE(f32, 0x42C80000);
    temp_f20 = (temp_f20 * temp_f1) / c100;
    if (func_00211310(arg0, 0, 0x800) != 0) {
        if (func_00218128(arg0, 4) != 0) {
            if (func_0023E520(arg0) < 0xAU) {
                f32 c3 = M2C_BITWISE(f32, 0x40400000);
                f32 c10 = M2C_BITWISE(f32, 0x41200000);
                temp_f20 = temp_f20 - ((temp_f20 * c3) / c10);
            }
        }
    }
    temp_ret = BtlObjAnim_QueryEvent(M2C_FIELD(arg0, s32 *, 0x1530), 1, 0, 2);
    if (temp_ret > 0) {
        temp_f20 = temp_f20 / (f32) temp_ret;
    }
    return (s32) temp_f20;
}
