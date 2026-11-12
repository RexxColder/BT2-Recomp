#include "m2c_macros.h"

void *BtlMember_GetActiveGauge(s32);                /* extern */
s32 func_00211288(s16);                             /* extern */
s32 *func_0023FF80();                               /* extern */

s32 func_00240040(void *arg0) {
    s32 var_s0;

    var_s0 = *func_0023FF80(arg0);
    if (M2C_FIELD(BtlMember_GetActiveGauge(func_00211288(M2C_FIELD(M2C_FIELD(arg0, void **, 0x68), s16 *, 0x10))), u8 *, 0x2C) != 0) {
        var_s0 &= ~3;
    }
    return var_s0;
}
