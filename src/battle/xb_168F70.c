#include "m2c_macros.h"

M2C_UNK func_001EDBA8(s32);                         /* extern */

void func_00168F70(void *arg0) {
    s32 *var_s0;
    s32 temp_a0;
    s32 var_s1;

    var_s1 = 6;
    var_s0 = (s32 *)((char *)M2C_FIELD(arg0, s32 *, 0x38) + 0xAE0);
    do {
        temp_a0 = *var_s0;
        var_s0 += 0xF0 / 4;
        var_s1 -= 1;
        func_001EDBA8(temp_a0);
    } while (var_s1 >= 0);
}
