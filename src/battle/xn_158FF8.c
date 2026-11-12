#include "m2c_macros.h"

M2C_UNK func_00182AB8(s32);                         /* extern */

void func_00158FF8(void *arg0) {
    s32 *var_s0;
    s32 temp_v0;
    s32 var_s2;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    var_s2 = 0;
    if (M2C_FIELD(temp_s1, s32 *, 0x14) > 0) {
        var_s0 = temp_s1 + 0xC;
        do {
            temp_v0 = *var_s0;
            if (temp_v0 != 0) {
                func_00182AB8(temp_v0);
                *var_s0 = 0;
            }
            var_s2 += 1;
            var_s0 += 1;
        } while (var_s2 < M2C_FIELD(temp_s1, s32 *, 0x14));
    }
    M2C_FIELD(temp_s1, s32 *, 0x10) = 0;
    M2C_FIELD(temp_s1, s32 *, 0x14) = 0;
}
