#include "m2c_macros.h"

M2C_UNK EftPtcl3_Stop(s32);                         /* extern */

void func_0019B150(void *arg0) {
    s32 *var_s0;
    s32 temp_a0;
    s32 var_s1;

    var_s1 = 2;
    var_s0 = (s32 *)((char *)M2C_FIELD(arg0, s32 *, 0x38) + 0x10);
    do {
        temp_a0 = *var_s0;
        var_s0 += 1;
        var_s1 -= 1;
        EftPtcl3_Stop(temp_a0);
    } while (var_s1 >= 0);
}
