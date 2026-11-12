#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_002615F0(s32, s32);                    /* extern */

s32 func_002A66B8(s32 arg0) {
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt();
        if (temp_v0 >= 0) {
            func_002615F0(temp_v0 & 0xFFFF, Gsc_GetInt());
        }
    }
    return 1;
}
