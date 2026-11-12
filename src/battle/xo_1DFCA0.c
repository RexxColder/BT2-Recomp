#include "m2c_macros.h"

void func_001E1258(f32, void *, s32, s32);       /* extern */

/* Calls func_001E1258 once per entry (count at +0x21CC) when the flag at +0x21DA is set. */
void func_001DFCA0(void *arg0, s32 arg1, s32 arg2) {
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    void *var_s0;
    void *var_s1;
    u8 temp_v0;

    var_s0 = arg0;
    var_s3 = arg2 & 0xFF;
    var_s4 = arg1;
    if (M2C_FIELD(var_s0, u8 *, 0x21DA) != 0) {
        var_s2 = 0;
        if (M2C_FIELD(var_s0, u8 *, 0x21CC) != 0) {
            var_s1 = var_s0;
            do {
                func_001E1258(M2C_FIELD(var_s0, f32 *, 0x21D0), var_s1, var_s4, var_s3);
                var_s2 += 1;
                var_s1 += 0x1B0;
                temp_v0 = M2C_FIELD(var_s0, u8 *, 0x21CC);
            } while (var_s2 < temp_v0);
        }
    }
}
