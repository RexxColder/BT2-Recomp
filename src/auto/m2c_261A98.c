#include "m2c_macros.h"

extern void *D_00387A40;

s32 func_00261A98(s32 arg0, s32 *arg1, f32 *arg2) {
    void *temp_a0;
    void *temp_v0;

    temp_v0 = M2C_FIELD(D_00387A40, s32 *, 8) + ((arg0 & 0xFFFF) * 0x1520);
    temp_a0 = temp_v0 + 0xBD0;
    if (M2C_FIELD(temp_v0, s32 *, 0xBD0) == 1) {
        *arg1 = (s32) M2C_FIELD(temp_a0, u16 *, 4);
        *arg2 = M2C_FIELD(temp_a0, f32 *, 0x10);
        return 1;
    }
    return 0;
}
