#include "m2c_macros.h"

void _sceSifLoadModuleBuffer(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

// Passes its three arguments through to _sceSifLoadModuleBuffer with a 4-word scratch array.
void func_003379C0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    _sceSifLoadModuleBuffer(arg0, arg1, arg2, sp);
}
