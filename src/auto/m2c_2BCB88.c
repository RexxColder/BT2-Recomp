#include "m2c_macros.h"

s32 BtlSeq_IsFighting(s32);                         /* extern */
s32 BtlSeq_IsFinish(s32);                           /* extern */

void func_002BCB88(void *arg0) {
    s32 temp_a0;
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x40);
    if ((temp_v0 != 0) && (BtlSeq_IsFinish(temp_v0) != 0)) {
        M2C_FIELD(arg0, s32 *, 4) = 4;
    }
    temp_a0 = M2C_FIELD(arg0, s32 *, 0x48);
    if ((temp_a0 != 0) && (BtlSeq_IsFighting(temp_a0) == 1)) {
        M2C_FIELD(arg0, s32 *, 4) = 4;
    }
}
