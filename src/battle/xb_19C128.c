#include "m2c_macros.h"

M2C_UNK func_001CC9E8(s32);                         /* extern */

void func_0019C128(void *arg0) {
    s32 *var_s0;
    s32 temp_a0;
    s32 var_s1;

    var_s1 = 1;
    var_s0 = (s32 *)((char *)M2C_FIELD(arg0, s32 *, 0x38) + 0x34);
    do {
        temp_a0 = *var_s0;
        var_s0 += 1;
        var_s1 -= 1;
        func_001CC9E8(temp_a0);
    } while (var_s1 >= 0);
}
