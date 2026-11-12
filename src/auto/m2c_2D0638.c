#include "m2c_macros.h"

s32 func_002D0688();                                /* extern */

void func_002D0638(s32 arg0, s32 arg1, s32 arg2) {
    if (func_002D0688(arg0, arg1, arg2) != 0) {
        M2C_FIELD(((arg1 * 4) + arg0), s32 *, 0xB9C) = arg2;
    }
}
