#include "m2c_macros.h"

extern s32 D_003877BC;

void func_001909A0(void *arg0, s32 arg1) {
    void *temp_a0;

    if ((D_003877BC != 0) && (arg0 != NULL)) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        if ((temp_a0 != NULL) && (M2C_FIELD(temp_a0, u16 *, 0x44) & 2)) {
            M2C_FIELD(temp_a0, f32 *, 0x40) = (f32) arg1;
        }
    }
}
