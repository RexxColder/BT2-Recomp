#include "m2c_macros.h"

s32 func_002B4BB0(s32 arg0, s32 arg1) {
    s32 var_a2;
    u32 temp_v1;
    void *temp_a0;

    temp_a0 = arg0 + 0x1EC;
    temp_v1 = M2C_FIELD(temp_a0, u32 *, 0xC) + arg1;
    var_a2 = 0;
    if ((u32) M2C_FIELD(temp_a0, u32 *, 4) >= temp_v1) {
        var_a2 = M2C_FIELD(temp_a0, s32 *, 8);
        M2C_FIELD(temp_a0, u32 *, 0xC) = temp_v1;
        M2C_FIELD(temp_a0, s32 *, 8) = (s32) (var_a2 + arg1);
    }
    return var_a2;
}
