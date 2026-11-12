#include "m2c_macros.h"

void func_00180580(void **arg0, s32 arg1) {
    s32 temp_v0_2;
    s32 var_a3;
    void **var_a0;
    void *temp_v0;
    void *temp_v1;

    var_a0 = arg0;
    var_a3 = 0x1D;
    do {
        temp_v0 = *var_a0;
        var_a0 += 1;
        if (temp_v0 != NULL) {
            temp_v1 = M2C_FIELD(temp_v0, void **, 0x38);
            temp_v0_2 = M2C_FIELD(temp_v1, s32 *, 0x48);
            if (!(temp_v0_2 & 2)) {
                M2C_FIELD(temp_v1, s32 *, 0x48) = (s32) (temp_v0_2 | 2);
                M2C_FIELD(temp_v1, f32 *, 0x1C) = (f32) (1.0f / (f32) arg1);
            }
        }
        var_a3 -= 1;
    } while (var_a3 >= 0);
}
