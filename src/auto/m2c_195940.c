#include "m2c_macros.h"

s32 func_00195A58();                                /* extern */

s32 func_00195940(void *arg0) {
    s32 var_v0;

    var_v0 = func_00195A58(arg0);
    if (var_v0 != 0) {
        var_v0 = ((s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 *, 0xB70) >> 0xB) & 1;
    }
    return var_v0;
}
