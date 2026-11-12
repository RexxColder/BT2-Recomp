#include "m2c_macros.h"

void func_001817D0(void **arg0) {
    void *temp_a0;
    void *temp_v1;

    temp_a0 = *arg0;
    if (temp_a0 != NULL) {
        temp_v1 = M2C_FIELD(temp_a0, void **, 0x38);
        M2C_FIELD(temp_v1, s32 *, 0xB8) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xB8) | 4);
    }
}
