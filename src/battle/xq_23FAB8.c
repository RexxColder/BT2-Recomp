#include "m2c_macros.h"

s32 func_001F97F8(void *);                          /* extern */
s32 func_00203C58(void *, M2C_UNK);                 /* extern */

s32 func_0023FAB8(void *arg0) {
    s32 temp_s0;
    s32 temp_s0_2;
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x1530);
    temp_s0_2 = (s32) M2C_FIELD(M2C_FIELD(temp_a1, void **, 0x958), s32 *, 0x88) / 30;
    temp_s0 = temp_s0_2 + func_001F97F8(arg0);
    return (func_00203C58(arg0, 0x40000000) != 0) ? (temp_s0 * 2) : temp_s0;
}
