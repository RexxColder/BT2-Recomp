#include "m2c_macros.h"

s32 func_002C2FF0(M2C_UNK, M2C_UNK);                /* extern */
s32 func_002C3210();                                /* extern */
M2C_UNK func_002CFD28(s32, s32 *);                  /* extern */

s32 func_002CFCB8(void *arg0, s32 *arg1) {
    *arg1 = 0;
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000155);
    }
    func_002CFD28(M2C_FIELD(arg0, s32 *, 0x36B0), arg1);
    return 0;
}
