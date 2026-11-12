#include "m2c_macros.h"

void func_001AE578(void *arg0, s32 arg1) {
    void *temp_v1;

    if (arg0 != NULL) {
        temp_v1 = M2C_FIELD(arg0, void **, 0x38);
        M2C_FIELD(temp_v1, s32 *, 0x78) = arg1;
        M2C_FIELD(temp_v1, s32 *, 0x60) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x60) | 1);
    }
}
