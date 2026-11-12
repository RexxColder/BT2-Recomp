#include "m2c_macros.h"

s32 func_00202DA0(s32 arg0, s32 arg1) {
    return arg0 + (M2C_FIELD(((arg1 * 4) + arg0), s32 *, 0x1410) << 7) + 0x1190;
}
