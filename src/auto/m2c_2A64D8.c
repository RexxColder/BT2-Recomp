#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_00261250(s32, s32);                    /* extern */

s32 func_002A64D8(s32 arg0) {
    s32 temp_s0;

    if (arg0 == 0) {
        temp_s0 = Gsc_GetInt() & 0xFFFF;
        func_00261250(temp_s0, Gsc_GetInt() & 0xFF);
    }
    return 1;
}
