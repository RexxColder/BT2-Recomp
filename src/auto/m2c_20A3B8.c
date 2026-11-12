#include "m2c_macros.h"

void *BtlObjVis_GetView_207EA0();                   /* extern */

f32 func_0020A3B8(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    f32 var_f0;
    void *temp_v0;

    temp_v0 = BtlObjVis_GetView_207EA0(r_a0);
    var_f0 = 0.0f;
    if (temp_v0 != NULL) {
        var_f0 = M2C_FIELD(temp_v0, f32 *, 0xBE0);
    }
    return var_f0;
}
