#include "m2c_macros.h"

s32 func_002CB6C8(s32, s32);                        /* extern */
s32 func_002CBE18();                                /* extern */

s32 func_002CC448(void *arg0, s32 arg1) {
    if (func_002CBE18(arg0) == 0) {
        return arg1;
    }
    return func_002CB6C8(M2C_FIELD(arg0, s32 *, 0x1FC0) + 0x1198, arg1);
}
