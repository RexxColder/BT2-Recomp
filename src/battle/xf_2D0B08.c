#include "m2c_macros.h"

s32 func_002C2FF0(M2C_UNK, M2C_UNK);                /* extern */
s32 func_002C3210();                                /* extern */

s32 func_002D0B08(void *arg0, void **arg1, s32 *arg2) {
    s32 temp_v1;

    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF00011C);
    }
    if (M2C_FIELD(arg0, s32 *, 0x78) != 0) {
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x108);
        *arg1 = arg0 + 0x10C;
        *arg2 = temp_v1;
    } else {
        *arg1 = NULL;
        *arg2 = 0;
    }
    return 0;
}
