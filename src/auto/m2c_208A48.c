#include "m2c_macros.h"

void *BtlChar_GetPos(s32);                          /* extern */
void *BtlObjVis_GetView_207EA0(u32, u32);           /* extern */
s32 func_00211288(u32);                             /* extern */
extern s32 D_00387930;

f32 func_00208A48(u32 arg0) {
    f32 var_f0;
    void *temp_v0;

    if ((D_00387930 != 0) && (arg0 < 2U)) {
        return M2C_FIELD(BtlChar_GetPos(func_00211288(arg0)), f32 *, 0xB4);
    }
    temp_v0 = BtlObjVis_GetView_207EA0(arg0, arg0);
    var_f0 = 0.0f;
    if (temp_v0 != NULL) {
        var_f0 = M2C_FIELD(temp_v0, f32 *, 0x9B4);
    }
    return var_f0;
}
