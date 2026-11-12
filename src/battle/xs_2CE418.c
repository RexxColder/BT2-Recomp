#include "m2c_macros.h"

M2C_UNK (*func_002D07B0(void *, s32))(void *, s32, s32); /* extern */

void func_002CE418(void *arg0, s32 arg1, s32 arg2) {
    M2C_UNK (*temp_v0)(void *, s32, s32);
    s32 var_s0;
    s32 var_s2;
    void *var_s1;

    var_s1 = arg0;
    var_s2 = arg2;
    var_s0 = var_s1 + 0x950;
    M2C_FIELD(var_s1, s32 *, 0x950) = (s32) (M2C_FIELD(var_s1, s32 *, 0x950) + arg1);
    temp_v0 = func_002D07B0(arg0, 0x24);
    if (temp_v0 != NULL) {
        temp_v0(var_s1, var_s2, var_s0);
    }
}
