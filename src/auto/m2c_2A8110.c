#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_002AA0D0();                            /* extern */
M2C_UNK func_002AA0E8();                            /* extern */

s32 func_002A8110(s32 arg0) {
    if (arg0 == 0) {
        if (Gsc_GetInt() != 0) {
            func_002AA0E8();
        } else {
            func_002AA0D0();
        }
    }
    return 1;
}
