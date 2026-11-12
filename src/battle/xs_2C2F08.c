#include "m2c_macros.h"

/* Clears the two words at +0x1FC and +0x200 of the object. */
void func_002C2F08(void *arg0) {
    void *temp_a0;

    temp_a0 = arg0 + 0x1FC;
    M2C_FIELD(temp_a0, s32 *, 0) = 0;
    M2C_FIELD(temp_a0, s32 *, 4) = 0;
}
