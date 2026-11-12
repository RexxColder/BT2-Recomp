#include "m2c_macros.h"

extern f32 D_00386CF8;

f32 func_00240E20(void *arg0) {
    return (M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), void **, 0x98C), f32 *, 0x54) / 180.0f) * D_00386CF8;
}
