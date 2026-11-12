#include "m2c_macros.h"

s32 func_002B0DA0(void *arg0, s32 arg1) {
    return (M2C_FIELD(arg0, s32 *, 0x84) & arg1) != 0;
}
