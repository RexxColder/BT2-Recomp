#include "m2c_macros.h"

extern s32 D_00387F2C;

s32 func_002A80B0(s32 arg0) {
    s32 var_a0;
    s32 var_v1;
    void *temp_v0;

    if (arg0 == 0) {
        var_a0 = 0x24C0;
        var_v1 = 6;
        do {
            var_v1 -= 1;
            temp_v0 = D_00387F2C + var_a0;
            var_a0 += 4;
            M2C_FIELD(temp_v0, s16 *, 2) = 0;
        } while (var_v1 >= 0);
    }
    return 1;
}
