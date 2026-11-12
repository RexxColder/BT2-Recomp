#include "m2c_macros.h"

M2C_UNK func_002C5D88(void *);                      /* extern */
M2C_UNK func_002C5DF8(void *);                      /* extern */
s32 func_002C5E98(void *);                          /* extern */
M2C_UNK func_002C5EB0(void *);                      /* extern */
M2C_UNK func_002C6138(void *);                      /* extern */
s32 func_002C6250(void *);                          /* extern */
s32 func_002D07B0(void *, s32);                       /* extern */

s32 func_002C5CF0(void *arg0) {
    s32 temp_s0;
    s32 var_v0;

    var_v0 = func_002D07B0(arg0, 5);
    if (var_v0 != 0) {
        if (func_002C5E98(arg0) == 1) {
            return 0;
        }
        func_002C5D88(arg0);
        if (M2C_FIELD(arg0, s32 *, 0x48) == 2) {
            func_002C5DF8(arg0);
        }
        temp_s0 = func_002C6250(arg0);
        func_002C5EB0(arg0);
        func_002C6138(arg0);
        var_v0 = temp_s0;
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
