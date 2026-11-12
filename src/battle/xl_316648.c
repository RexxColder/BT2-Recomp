#include "m2c_macros.h"

// Clears two fields of the object at +0x40 (a 64-bit word at 0x90, a 32-bit word at 0x8C); returns 1.
s32 func_00316648(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x40);
    M2C_FIELD(temp_v1, s32 *, 0x8C) = 0;
    M2C_FIELD(temp_v1, s64 *, 0x90) = 0;
    return 1;
}
