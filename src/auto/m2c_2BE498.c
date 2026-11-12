#include "m2c_macros.h"

s32 func_002F4590(s32);                             /* extern */

s32 func_002BE498(void *arg0) {
    return func_002F4590(*M2C_FIELD(arg0, s32 **, 0x2004)) == 3;
}
