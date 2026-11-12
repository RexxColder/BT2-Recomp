#include "m2c_macros.h"

void *BtlMember_GetActiveGauge();                   /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void func_00203968(s32 arg0, s32 arg1) {
    s32 temp_t1;
    s32 temp_v0_2;
    void *temp_v0;

    temp_v0 = BtlMember_GetActiveGauge(arg0);
    temp_t1 = M2C_FIELD(temp_v0, s32 *, 0x18);
    temp_v0_2 = M2C_FIELD(temp_v0, s32 *, 0x14) + arg1;
    M2C_FIELD(temp_v0, s32 *, 0x14) = temp_v0_2;
    if (temp_t1 < temp_v0_2) {
        M2C_FIELD(temp_v0, s32 *, 0x14) = temp_t1;
        func_002113C0(arg0, 0x10, 0x20000000, 1);
    }
}
