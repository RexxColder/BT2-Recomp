#include "m2c_macros.h"

extern void *gBtlStage;

void func_00273268(void) {
    s32 *var_a0;
    u32 var_a2;

    var_a2 = 0;
    var_a0 = M2C_FIELD(gBtlStage, s32 *, 0x5C) + (M2C_FIELD(gBtlStage, s32 *, 0x3C) * 4);
    if (M2C_FIELD(gBtlStage, u32 *, 0x38) != 0) {
        do {
            *var_a0 = 0;
            var_a2 += 1;
            var_a0 += 16;
        } while (var_a2 < (u32) M2C_FIELD(gBtlStage, u32 *, 0x38));
    }
}
