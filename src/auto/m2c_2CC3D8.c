#include "m2c_macros.h"

s32 func_002CBE18();                                /* extern */
s32 func_002CC168(s32, M2C_UNK, s32);               /* extern */

s32 func_002CC3D8(void *arg0, M2C_UNK arg1, s32 arg2) {
    if (func_002CBE18(arg0) == 0) {
        return arg2;
    }
    return func_002CC168(M2C_FIELD(arg0, s32 *, 0x1FC0) + 0x1198, arg1, arg2);
}
