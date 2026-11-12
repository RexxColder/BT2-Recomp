#include "m2c_macros.h"

M2C_UNK memset(s32, M2C_UNK, s32);                  /* extern */

void func_0026F770(void *arg0) {
    memset(M2C_FIELD(arg0, s32 *, 0), 0, M2C_FIELD(arg0, s32 *, 4) * 0x38);
}
