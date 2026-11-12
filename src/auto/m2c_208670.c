#include "m2c_macros.h"

s32 BtlObjVis_GetView_207EA0();                     /* extern */
f32 func_0026A220(s32);                             /* extern */

f32 func_00208670(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    s32 temp_v0;

    temp_v0 = BtlObjVis_GetView_207EA0(r_a0);
    if (temp_v0 != 0) {
        return func_0026A220(temp_v0);
    }
    return 1.0f;
}
