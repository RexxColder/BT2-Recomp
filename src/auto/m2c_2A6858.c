#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_00261558(s32, M2C_UNK);                /* extern */

s32 func_002A6858(s32 arg0) {
    if (arg0 == 0) {
        func_00261558(Gsc_GetInt() & 0xFFFF, 0);
    }
    return 1;
}
