#include "m2c_macros.h"

M2C_UNK func_002D0E20(s32);                         /* extern */

void func_002D0DD8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    func_002D0E20(arg0 + 4);
    M2C_FIELD(arg0, s32 *, 0x24) = arg1;
    M2C_FIELD(arg0, s32 *, 0x28) = 1;
}
