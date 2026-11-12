#include "m2c_macros.h"

s32 func_001F94A0(s32, M2C_UNK);                    /* extern */
void *func_00202DC0();                              /* extern */

s32 func_001F9618(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s1 = arg0;
    var_s0 = M2C_FIELD(func_00202DC0(arg0), s32 *, 0x18);
    var_s0 += func_001F94A0(var_s1, 2);
    var_s0 = (var_s0 >= 0x32) ? 0x31 : var_s0;
    return (var_s0 >= 0) ? var_s0 : 0;
}
