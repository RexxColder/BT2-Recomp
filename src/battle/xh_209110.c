#include "m2c_macros.h"

s32 BtlObjVis_GetView_207EA0();                     /* extern */
void *func_00269A08(s32, M2C_UNK);                  /* extern */

// Returns 0.0 if no view, else 1.0 or field 0x5C of the object found by func_00269A08(view, arg).
f32 func_00209110(s32 unused0, M2C_UNK arg1) {
    f32 var_f0;
    s32 temp_v0;
    void *temp_v0_2;

    temp_v0 = BtlObjVis_GetView_207EA0(unused0);
    var_f0 = 0.0f;
    if (temp_v0 != 0) {
        temp_v0_2 = func_00269A08(temp_v0, arg1);
        var_f0 = 1.0f;
        if (temp_v0_2 != NULL) {
            var_f0 = M2C_FIELD(temp_v0_2, f32 *, 0x5C);
        }
    }
    return var_f0;
}
