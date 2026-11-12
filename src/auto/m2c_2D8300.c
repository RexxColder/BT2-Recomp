#include "m2c_macros.h"

s32 strncmp(s32, M2C_UNK *, M2C_UNK);               /* extern */
extern M2C_UNK D_0037AE40 __attribute__((section(".data")));

s32 func_002D8300(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg1 < 0)) {
        return 0;
    }
    return strncmp(arg0 + 0x13, &D_0037AE40, 1) == 0;
}
