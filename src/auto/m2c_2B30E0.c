#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
s32 func_002B2FD0();                                /* extern */
s32 func_002B3088(s32);                             /* extern */
extern M2C_UNK D_00377DE8 __attribute__((section(".data")));

s32 func_002B30E0(s32 arg0) {
    s32 temp_s0;

    if (arg0 == 0) {
        Rand_Range(&D_00377DE8);
        return 0;
    }
    temp_s0 = func_002B2FD0();
    return temp_s0 + func_002B3088(arg0);
}
