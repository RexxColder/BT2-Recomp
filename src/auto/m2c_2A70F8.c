#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_002A3A98(s32);                         /* extern */

s32 func_002A70F8(s32 arg0) {
    if (arg0 == 0) {
        func_002A3A98(Gsc_GetInt());
    }
    return 1;
}
