#include "m2c_macros.h"

f32 func_00240E80(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x98C)), f32 *, 0x68) * 10.0f;
}
