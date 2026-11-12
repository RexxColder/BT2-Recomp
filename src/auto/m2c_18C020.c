#include "m2c_macros.h"

extern s32 D_003877B4;

void func_0018C020(void *arg0, s32 arg1) {
    void *temp_a0;

    if ((D_003877B4 != 0) && (arg0 != NULL)) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        if ((temp_a0 != NULL) && (M2C_FIELD(temp_a0, s32 *, 0x1D8) & 2)) {
            M2C_FIELD(temp_a0, f32 *, 0xCC) = (f32) arg1;
        }
    }
}
