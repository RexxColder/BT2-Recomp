#include "m2c_macros.h"

void func_00182AB8(s32);

// Frees the table of up to count entries at +0xAB0 of the object at arg0+0x38 (count at +0xB14), then clears the count and the field at +0xB10.
void func_0014C508(void *arg0) {
    s32 *var_s0;
    s32 temp_v0;
    s32 var_s2;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    var_s2 = 0;
    if (M2C_FIELD(temp_s1, s32 *, 0xB14) > 0) {
        var_s0 = (s32 *) ((u8 *) temp_s1 + 0xAB0);
        do {
            temp_v0 = *var_s0;
            if (temp_v0 != 0) {
                func_00182AB8(temp_v0);
                *var_s0 = 0;
            }
            var_s2 += 1;
            var_s0 += 1;
        } while (var_s2 < M2C_FIELD(temp_s1, s32 *, 0xB14));
    }
    M2C_FIELD(temp_s1, s32 *, 0xB10) = 0;
    M2C_FIELD(temp_s1, s32 *, 0xB14) = 0;
}
