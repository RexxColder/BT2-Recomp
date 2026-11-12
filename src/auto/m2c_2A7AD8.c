#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_001018E8(s32, M2C_UNK);                /* extern */

s32 func_002A7AD8(s32 arg0) {
    if (arg0 == 0) {
        func_001018E8(Gsc_GetInt(), 0);
    }
    return 1;
}
