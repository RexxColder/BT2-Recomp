#include "m2c_macros.h"

s32 strncmp(s32, M2C_UNK *, M2C_UNK);               /* extern */
extern M2C_UNK D_0037AE28 __attribute__((section(".data")));

s32 func_002D82C0(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg1 < 0)) {
        return 0;
    }
    return strncmp(arg0 + 0x12, &D_0037AE28, 1) == 0;
}
