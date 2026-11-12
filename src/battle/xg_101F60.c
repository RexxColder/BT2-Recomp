#include "m2c_macros.h"

s32 *func_00101A88(s32);                            /* extern */

/* For two slots from func_00101A88: copies word +4 to word +0 of each 0x58-byte record at +0x54, count = slot count. */
void func_00101F60(void) {
    s32 *temp_v0;
    u8 *var_v1;
    s32 temp_v1;
    s32 var_a1;
    s32 var_s0;

    var_s0 = 0;
    do {
        temp_v0 = func_00101A88(var_s0);
        temp_v1 = *temp_v0;
        if (temp_v1 >= 2) {
            var_a1 = 0;
            if (temp_v1 > 0) {
                var_v1 = (u8 *) temp_v0 + 0x54;
                do {
                    var_a1 += 1;
                    M2C_FIELD(var_v1, s32 *, 0) = M2C_FIELD(var_v1, s32 *, 4);
                    var_v1 += 0x58;
                } while (var_a1 < *temp_v0);
            }
        }
        var_s0 += 1;
    } while (var_s0 < 2);
}
