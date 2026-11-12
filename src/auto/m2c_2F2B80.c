#include "m2c_macros.h"

s32 func_002F2B80(void *arg0, s32 *arg1, s32 *arg2) {
    *arg1 = M2C_FIELD(arg0, s32 *, 0x1C);
    *arg2 = M2C_FIELD(arg0, s32 *, 0x18);
    return 1;
}
