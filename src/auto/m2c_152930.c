#include "m2c_macros.h"

extern f32 D_00384670;

void func_00152930(void **arg0, void *arg1) {
    M2C_FIELD(arg1, f32 *, 0xE0) = (f32) (M2C_FIELD(arg1, f32 *, 0xE0) + ((f32) M2C_FIELD(*arg0, s16 *, 6) * D_00384670));
}
