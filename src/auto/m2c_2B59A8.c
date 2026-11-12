#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
s32 func_002B7CB8(s32);                             /* extern */
s32 func_002B8280();                                /* extern */
s32 func_002CB050(s32);                             /* extern */
extern M2C_UNK D_00378588 __attribute__((section(".data")));

s32 func_002B59A8(s32 arg0) {
    s32 temp_v0;

    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_00378588);
        return 0;
    }
    temp_v0 = func_002B7CB8(arg0);
    if (temp_v0 != 0) {
        return func_002CB050(temp_v0);
    }
    return temp_v0;
}
