#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_002612B8(s32, s32);                    /* extern */

s32 func_002A6518(s32 arg0) {
    s32 temp_s0;

    if (arg0 == 0) {
        temp_s0 = Gsc_GetInt() & 0xFFFF;
        func_002612B8(temp_s0, Gsc_GetInt());
    }
    return 1;
}
