#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
s32 func_002B8280();                                /* extern */
extern M2C_UNK D_003785F8 __attribute__((section(".data")));

s32 func_002B5AF8(void *arg0) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_003785F8);
        return 0;
    }
    return M2C_FIELD(arg0, s32 *, 0x84);
}
