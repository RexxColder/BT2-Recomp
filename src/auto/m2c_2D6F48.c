#include "m2c_macros.h"

M2C_UNK func_002D6DD0(void *, M2C_UNK);             /* extern */
M2C_UNK func_002E0F30(s32, s32, s32, s32);          /* extern */

void func_002D6F48(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002E0F30(M2C_FIELD(arg0, s32 *, 0x30), arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF);
    func_002D6DD0(arg0, 0);
}
