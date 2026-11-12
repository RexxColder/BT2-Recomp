#include "m2c_macros.h"

void func_002D1C08(s32 arg0, s32 arg1, s32 arg2) {
    arg0 = (u8 *) arg0 + arg2 * 4;
    M2C_FIELD(arg0, s32 *, 0xD30) = arg1;
}
