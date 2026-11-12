#include "m2c_macros.h"

M2C_UNK memcpy(s32, s32, s32);                      /* extern */

void func_002C9A08(void *arg0, void *arg1) {
    memcpy(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg1, s32 *, 0), M2C_FIELD(arg1, s32 *, 4));
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
}
