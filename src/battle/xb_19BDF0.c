#include "m2c_macros.h"

s32 EftPtcl3_IsAlive(s32);                          /* extern */

// Three rows (base obj->0x38 + 4*row) of two 12-byte slots starting at +0x10; word 0 of a slot is a particle handle.
// Clears the handle of each dead slot; returns 1 if any slot is still alive.
s32 func_0019BDF0(void *arg0) {
    s32 *var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;

    var_s3 = 0;
    var_s4 = 0;
    var_s2 = M2C_FIELD(arg0, s32 *, 0x38);
    do {
        var_s0 = (s32 *) (var_s2 + 0x10);
        var_s1 = 1;
        do {
            if (EftPtcl3_IsAlive(*var_s0) != 0) {
                var_s4 = 1;
            } else {
                *var_s0 = 0;
            }
            var_s1 -= 1;
            var_s0 += 3;
        } while (var_s1 >= 0);
        var_s3 += 1;
        var_s2 += 4;
    } while (var_s3 < 3);
    return var_s4;
}
