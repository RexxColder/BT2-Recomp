#include "m2c_macros.h"

void func_002D3018(s32 arg0, s32 arg1, s32 arg2) {
    arg0 = (u8 *) arg0 + arg1 * 0x44;
    M2C_FIELD(arg0, s32 *, 0x1F30) = arg2;
}
