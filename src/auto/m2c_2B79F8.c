#include "m2c_macros.h"

void *sceDmaGetChan(M2C_UNK);                       /* extern */
M2C_UNK sceDmaRecvN(void *, s32, s32);              /* extern */

s32 func_002B79F8(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    void *temp_v0;

    var_s0 = arg1;
    var_s1 = arg0;
    var_s2 = arg2;
    temp_v0 = sceDmaGetChan(8);
    M2C_FIELD(temp_v0, s32 *, 0x80) = var_s1;
    var_s0 = (var_s0 < 0) ? (var_s0 + 0xF) : var_s0;
    sceDmaRecvN(temp_v0, var_s2, var_s0 >> 4);
    return 0;
}
