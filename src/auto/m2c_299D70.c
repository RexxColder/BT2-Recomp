#include "m2c_macros.h"

f32 Quat_LengthSq(void *arg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;

    temp_f0 = M2C_FIELD(arg0, f32 *, 0);
    temp_f3 = M2C_FIELD(arg0, f32 *, 4);
    temp_f2 = M2C_FIELD(arg0, f32 *, 8);
    temp_f1 = M2C_FIELD(arg0, f32 *, 0xC);
    return (temp_f0 * temp_f0) + (temp_f3 * temp_f3) + (temp_f2 * temp_f2) + (temp_f1 * temp_f1);
}
