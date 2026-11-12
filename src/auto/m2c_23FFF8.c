#include "m2c_macros.h"

s32 *BtlKiBlast_Get();                              /* extern */
void *BtlMember_GetActiveGauge(s32);                /* extern */

s32 func_0023FFF8(s32 arg0) {
    s32 var_s0;

    var_s0 = *BtlKiBlast_Get(arg0);
    if (M2C_FIELD(BtlMember_GetActiveGauge(arg0), u8 *, 0x2C) != 0) {
        var_s0 &= ~3;
    }
    return var_s0;
}
