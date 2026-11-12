#include "m2c_macros.h"

M2C_UNK func_002E1CE8(M2C_UNK *);                   /* extern */
extern M2C_UNK D_00347BB8 __attribute__((section(".data")));

s32 func_002E1C98(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        func_002E1CE8(&D_00347BB8);
    } else {
        func_002E1CE8(arg0 + 4);
    }
    return arg1;
}
