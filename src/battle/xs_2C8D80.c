#include "m2c_macros.h"

/* Copies two words of the sub-object at +0xA0C out through the pointers arg2 (+0xA8) and arg3 (+0xAC). */
void func_002C8D80(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    void *temp_a0;

    temp_a0 = arg0 + 0xA0C;
    *arg3 = M2C_FIELD(temp_a0, s32 *, 0xAC);
    *arg2 = M2C_FIELD(temp_a0, s32 *, 0xA8);
}
