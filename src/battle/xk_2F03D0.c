#include "m2c_macros.h"

void func_002F03D0(s32 arg0, s32 arg1, s32 arg2) {
    arg0 = (u8 *) arg0 + arg1 * 4;
    M2C_FIELD(arg0, s32 *, 0xC) = arg2;
}
