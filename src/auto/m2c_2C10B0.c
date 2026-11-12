#include "m2c_macros.h"

extern s32 D_00393E74 __attribute__((section(".data")));

s32 func_002C10B0(void **arg0) {
    return M2C_FIELD(*arg0, s32 (**)(), 0x10)() == D_00393E74;
}
