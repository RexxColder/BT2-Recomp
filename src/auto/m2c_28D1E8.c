#include "m2c_macros.h"

s32 ColBox_ContainsPoint(void *arg0, void *arg1) {
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    s32 var_v0;

    temp_f1 = M2C_FIELD(arg1, f32 *, 0);
    var_v0 = 0;
    if (!(M2C_FIELD(arg0, f32 *, 0xC) < temp_f1) && !(temp_f1 < M2C_FIELD(arg0, f32 *, 0))) {
        temp_f1_2 = M2C_FIELD(arg1, f32 *, 4);
        if (!(M2C_FIELD(arg0, f32 *, 0x10) < temp_f1_2) && !(temp_f1_2 < M2C_FIELD(arg0, f32 *, 4))) {
            temp_f1_3 = M2C_FIELD(arg1, f32 *, 8);
            if (!(M2C_FIELD(arg0, f32 *, 0x14) < temp_f1_3) && !(temp_f1_3 < M2C_FIELD(arg0, f32 *, 8))) {
                var_v0 = 1;
            }
        }
    }
    return var_v0;
}
