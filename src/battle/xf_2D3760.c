#include "m2c_macros.h"

s32 func_002D37C0(void *);                          /* extern */

void func_002D3760(void *arg0, s32 arg1) {
    s32 *var_v1;
    s32 var_a0;

    var_a0 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x10) > 0) {
        var_v1 = arg0 + 0x18;
        do {
            var_a0 += 1;
            *var_v1 -= arg1;
            var_v1 += 1;
        } while (var_a0 < M2C_FIELD(arg0, s32 *, 0x10));
    }
    M2C_FIELD(arg0, s32 *, 0x1A8) = func_002D37C0(arg0);
}
