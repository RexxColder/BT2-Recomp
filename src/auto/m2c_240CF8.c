#include "m2c_macros.h"

void *func_0023FFD8();                              /* extern */
extern f32 D_00386CE4;

f32 func_00240CF8(unsigned long r_a0, unsigned long r_a1) { /* asm: a0, a1 arrive and pass through untouched */
    f32 var_f1;
    s8 temp_v0_2;
    void *temp_v0;

    temp_v0 = func_0023FFD8(r_a0, r_a1);
    temp_v0_2 = M2C_FIELD(temp_v0, s8 *, 0x32);
    var_f1 = M2C_FIELD(temp_v0, f32 *, 0x20) * 10.0f * D_00386CE4;
    if (temp_v0_2 > 0) {
        var_f1 /= (f32) temp_v0_2;
    }
    return var_f1;
}
