#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_002619C8(s32);                         /* extern */

s32 func_002A6598(s32 arg0) {
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt();
        if (temp_v0 >= 0) {
            func_002619C8(temp_v0 & 0xFFFF);
        }
    }
    return 1;
}
