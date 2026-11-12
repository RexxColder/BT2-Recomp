#include "m2c_macros.h"

M2C_UNK func_003083F8(s32, s32);                    /* extern */
M2C_UNK func_003085E0(s32);                         /* extern */

void func_002F0390(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    func_003085E0(M2C_FIELD(arg0, s32 *, 4));
    func_003083F8(M2C_FIELD(arg0, s32 *, 4), arg1);
}
