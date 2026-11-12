#include "m2c_macros.h"

void *BtlKiBlast_Get();                             /* extern */
extern f32 D_00386CDC;

f32 func_00240C48(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    f32 var_f1;
    s8 temp_v0_2;
    void *temp_v0;

    temp_v0 = BtlKiBlast_Get(r_a0);
    temp_v0_2 = M2C_FIELD(temp_v0, s8 *, 0x32);
    var_f1 = M2C_FIELD(temp_v0, f32 *, 0x20) * 10.0f * D_00386CDC;
    if (temp_v0_2 > 0) {
        var_f1 /= (f32) temp_v0_2;
    }
    return var_f1;
}
