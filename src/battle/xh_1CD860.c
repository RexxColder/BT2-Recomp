#include "m2c_macros.h"

s32 EftPtcl3_IsAlive(s32);                          /* extern */

// Scans 2 groups from field 0x38 (8-byte group stride, 4-byte slots at +0x10): clears dead slots via EftPtcl3_IsAlive; returns 1 if any alive.
s32 func_001CD860(void *arg0) {
    s32 *var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;

    var_s3 = 0;
    var_s4 = 0;
    var_s2 = M2C_FIELD(arg0, s32 *, 0x38);
    do {
        var_s0 = var_s2 + 0x10;
        var_s1 = 1;
loop_2:
        if (EftPtcl3_IsAlive(*var_s0) != 0) {
            var_s4 = 1;
        } else {
            *var_s0 = 0;
        }
        var_s1 -= 1;
        var_s0 = (s32 *) ((s32) var_s0 + 4);
        if (var_s1 >= 0) {
            goto loop_2;
        }
        var_s3 += 1;
        var_s2 += 8;
    } while (var_s3 < 2);
    return var_s4;
}
