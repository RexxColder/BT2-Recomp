#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_001F4308(s32, s32);                    /* extern */

s32 func_002A6950(s32 arg0) {
    s32 temp_s0;

    if (arg0 == 0) {
        temp_s0 = Gsc_GetInt();
        func_001F4308(Gsc_GetInt(), temp_s0);
    }
    return 1;
}
