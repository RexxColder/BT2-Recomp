#include "m2c_macros.h"

M2C_UNK BtlFacade_ShakeCamera_25B990(f32);          /* extern */
f32 Gsc_GetFloat();                                 /* extern */

s32 func_002A5EB8(s32 arg0) {
    if (arg0 == 0) {
        BtlFacade_ShakeCamera_25B990(Gsc_GetFloat());
    }
    return 1;
}
