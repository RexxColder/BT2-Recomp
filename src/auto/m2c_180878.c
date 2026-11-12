#include "m2c_macros.h"

void func_00180878(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x38);
    M2C_FIELD(temp_a1, s32 *, 0x48) = (s32) (M2C_FIELD(temp_a1, s32 *, 0x48) & ~1);
}
