#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
s32 func_002B4EC0(s32);                             /* extern */
s32 func_002B8280();                                /* extern */
extern M2C_UNK D_003783B0 __attribute__((section(".data")));

s32 func_002B4E70(s32 arg0) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_003783B0);
        return 0;
    }
    return func_002B4EC0(arg0);
}
