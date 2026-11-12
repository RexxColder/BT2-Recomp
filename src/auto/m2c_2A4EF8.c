#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_0025B860(s32);                         /* extern */

s32 func_002A4EF8(s32 arg0) {
    if (arg0 == 0) {
        func_0025B860(Gsc_GetInt() & 0xFFFF);
    }
    return 1;
}
