#include "m2c_macros.h"

void Res_RelocateOffsets(void **arg0, s32 arg1, void *arg2) {
    s32 temp_a1;
    u32 var_a3;
    void *temp_a0;
    void *temp_a1_2;

    *arg0 = arg2;
    M2C_FIELD(arg2, s32 *, 0x10) = (s32) (arg1 + (M2C_FIELD(arg2, s32 *, 4) * 4));
    var_a3 = 0;
    if (M2C_FIELD(*arg0, u32 *, 0) != 0) {
        do {
            temp_a1 = var_a3 << 6;
            var_a3 += 1;
            temp_a0 = temp_a1 + M2C_FIELD(*arg0, s32 *, 0x10);
            M2C_FIELD(temp_a0, s32 *, 0x38) = (s32) (arg1 + (M2C_FIELD(temp_a0, s32 *, 0) * 4));
            temp_a1_2 = temp_a1 + M2C_FIELD(*arg0, s32 *, 0x10);
            M2C_FIELD(temp_a1_2, s32 *, 0x3C) = (s32) (arg1 + (M2C_FIELD(temp_a1_2, s32 *, 4) * 4));
        } while (var_a3 < (u32) M2C_FIELD(*arg0, u32 *, 0));
    }
}
