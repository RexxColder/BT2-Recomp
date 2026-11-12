#include "m2c_macros.h"

f32 func_001FA318(void *arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x1530) + 0xBD0;
    return M2C_FIELD(temp_v0, f32 *, 0x10) / M2C_FIELD(temp_v0, f32 *, 8);
}
