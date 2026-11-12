#include "m2c_macros.h"

s32 func_00211288(M2C_UNK);                         /* extern */
s32 func_00211310(s32, M2C_UNK, M2C_UNK);           /* extern */
extern s32 D_00387930;

s32 func_0020B158(void) {
    if ((D_00387930 != 0) && ((func_00211310(func_00211288(0), 0, 0x400) != 0) || (func_00211310(func_00211288(1), 0, 0x400) != 0))) {
        return 1;
    }
    return 0;
}
