#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_002A3CE0(s32);                         /* extern */

s32 func_002A6918(s32 arg0) {
    if (arg0 == 0) {
        func_002A3CE0(Gsc_GetInt());
    }
    return 1;
}
