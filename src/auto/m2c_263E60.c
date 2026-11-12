#include "m2c_macros.h"

void func_00263E60(void *arg0) {
    f32 temp_f1;

    temp_f1 = M2C_FIELD(arg0, f32 *, 0x3C);
    if (temp_f1 > 120.0f) {
        M2C_FIELD(arg0, f32 *, 0x30) = 0.0f;
        return;
    }
    if (temp_f1 > 40.0f) {
        M2C_FIELD(arg0, f32 *, 0x30) = (f32) (1.0f - ((temp_f1 - 40.0f) / 80.0f));
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x30) = 1.0f;
}
