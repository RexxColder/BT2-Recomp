#include "m2c_macros.h"

void func_00181DB8(void *arg0) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x38);
    if (M2C_FIELD(arg0, s32 *, 4) & 3) {
        M2C_FIELD(temp_a0, s32 *, 0x98) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x98) & ~1);
    }
}
