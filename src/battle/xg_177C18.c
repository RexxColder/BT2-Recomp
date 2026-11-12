/* Spd line: steps a streak with two helper calls; returns 1 once the countdown at +0x3C reaches zero. */
#include "m2c_macros.h"

M2C_UNK func_00129B28();      /* extern */
M2C_UNK func_00129BB8(f32, void *, s32);            /* extern */

/* Spd line: steps a streak; returns 1 once the countdown at +0x3C reaches zero. */
s32 EftSpdLine_StepStreak(void *arg0) {
    s32 sp[4];
    void *temp_a0;

    if (M2C_FIELD(arg0, s32 *, 0x44) & 1) {
        func_00129BB8(M2C_FIELD(arg0, f32 *, 0x34), sp, arg0 + 0x20);
        func_00129B28(arg0, arg0, sp);
        temp_a0 = arg0 + 0x10;
        func_00129B28(temp_a0, temp_a0, sp);
        M2C_FIELD(arg0, f32 *, 0x3C) = (f32) (M2C_FIELD(arg0, f32 *, 0x3C) - M2C_FIELD(arg0, f32 *, 0x40));
    }
    if (M2C_FIELD(arg0, f32 *, 0x3C) <= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0x3C) = 0.0f;
        return 1;
    }
    return 0;
}
