#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_0025B910(s32);                         /* extern */

s32 func_002A5E88(s32 arg0) {
    if (arg0 == 0) {
        func_0025B910(Gsc_GetInt() & 0xFFFF);
    }
    return 1;
}
