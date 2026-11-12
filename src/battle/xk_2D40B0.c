#include "m2c_macros.h"

s32 func_002D07B0(void *, M2C_UNK);                         /* extern */
M2C_UNK func_002D4108(s32);                         /* extern */
M2C_UNK func_002D41D0(s32);                         /* extern */
s32 func_002D4258(s32);                             /* extern */

s32 func_002D40B0(s32 arg0) {
    s32 temp_s0;
    s32 var_v0;

    var_v0 = func_002D07B0(arg0, 5);
    if (var_v0 != 0) {
        func_002D4108(arg0);
        temp_s0 = func_002D4258(arg0);
        func_002D41D0(arg0);
        var_v0 = temp_s0;
    }
    return var_v0;
}
