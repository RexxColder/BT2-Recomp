#include "m2c_macros.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2) {
    return (M2C_FIELD(((arg1 * 4) + arg0), s32 *, 0x2B0) & arg2) != 0;
}
