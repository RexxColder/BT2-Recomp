#include "m2c_macros.h"

M2C_UNK func_00270270(s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK memset(M2C_UNK, M2C_UNK, M2C_UNK);          /* extern */

void func_0026EBC0(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    memset(arg2, 0, 8);
    func_00270270(M2C_FIELD(arg0, s32 *, 0x1C), arg1, arg2);
}
