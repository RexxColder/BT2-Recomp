#include "m2c_macros.h"

M2C_UNK BtlChar_GetSnapPos(s32, M2C_UNK, M2C_UNK);  /* extern */
s32 func_00211288(M2C_UNK);                         /* extern */

void BtlOpp_GetTargetPos(void *arg0, M2C_UNK arg1) {
    s32 var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    BtlChar_GetSnapPos(var_v0, arg1, 7);
}
