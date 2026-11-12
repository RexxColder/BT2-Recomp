#include "m2c_macros.h"

f32 BtlCharApi_GetHeight(s32);                      /* extern */
void *func_00211288(M2C_UNK);                       /* extern */

f32 BtlOpp_GetHalfHeightDiff(void *arg0) {
    f32 temp_f20;
    void *var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    temp_f20 = BtlCharApi_GetHeight(M2C_FIELD(arg0, s32 *, 0x1534));
    return (temp_f20 * 0.5f) - (BtlCharApi_GetHeight(M2C_FIELD(var_v0, s32 *, 0x1534)) * 0.5f);
}
