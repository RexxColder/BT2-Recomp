#include "m2c_macros.h"

s32 BtlScene_GetPackEntry(s32, s32);                /* extern */

void BtlScene_FillPackEntries(void *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 *var_s1;
    s32 temp_a1;
    s32 var_s0;
    s32 var_s2;

    var_s2 = arg3;
    if (arg2 > 0) {
        var_s1 = arg1;
        var_s0 = arg2;
        do {
            temp_a1 = var_s2;
            var_s0 -= 1;
            var_s2 += 1;
            *var_s1 = BtlScene_GetPackEntry(M2C_FIELD(arg0, s32 *, 0x1C), temp_a1);
            var_s1 += 1;
        } while (var_s0 != 0);
    }
}
