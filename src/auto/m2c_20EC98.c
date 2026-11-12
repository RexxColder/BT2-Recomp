#include "m2c_macros.h"

s32 func_0020A908();                                /* extern */
s32 func_00211288(s32);                             /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void func_0020EC98(s32 arg0) {
    if (func_0020A908(arg0) != 0) {
        func_002113C0(func_00211288(arg0), 7, 0x8000, 1);
    }
}
