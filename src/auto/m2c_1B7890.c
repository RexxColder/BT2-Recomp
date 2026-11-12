#include "m2c_macros.h"

void func_001B7890(void *arg0) {
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, void **, 0x70);
    if (!(M2C_FIELD(temp_v1, u8 *, 0) & 1 & 0xFF)) {
        temp_v1_2 = M2C_FIELD(temp_v1, void **, 0x38);
        M2C_FIELD(temp_v1_2, s32 *, 0x60) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x60) | 1);
    }
}
