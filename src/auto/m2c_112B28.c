#include "m2c_macros.h"

void func_00112B28(void *arg0) {
    s32 temp_v1;
    u32 var_a1;

    var_a1 = 0;
    if (M2C_FIELD(arg0, u32 *, 0) != 0) {
        do {
            temp_v1 = var_a1 << 6;
            var_a1 += 1;
            M2C_FIELD((temp_v1 + M2C_FIELD(arg0, s32 *, 0x10)), s32 *, 0x28) = 0;
        } while (var_a1 < (u32) M2C_FIELD(arg0, u32 *, 0));
    }
}
