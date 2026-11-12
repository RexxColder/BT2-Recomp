#include "m2c_macros.h"

M2C_UNK func_00306208(s32, s32);                    /* extern */
M2C_UNK memset(s32, M2C_UNK, s32);                  /* extern */
M2C_UNK strncpy(s32, M2C_UNK, M2C_UNK);             /* extern */

void func_00306350(void *arg0, M2C_UNK arg1) {
    memset(M2C_FIELD(arg0, s32 *, 0), 0, M2C_FIELD(arg0, s32 *, 4));
    strncpy(M2C_FIELD(arg0, s32 *, 0), arg1, 7);
    func_00306208(M2C_FIELD(arg0, s32 *, 4) - 0x10, M2C_FIELD(arg0, s32 *, 0) + 8);
}
