#include "m2c_macros.h"

M2C_UNK func_0032EC80(s32);                         /* extern */
M2C_UNK func_0032ECA0(s32);                         /* extern */

void func_002CB678(void *arg0, s32 arg1) {
    func_0032ECA0(M2C_FIELD(arg0, s32 *, 0x40));
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) + arg1);
    M2C_FIELD(arg0, s64 *, 0x48) = (s64) (arg1 + M2C_FIELD(arg0, s64 *, 0x48));
    func_0032EC80(M2C_FIELD(arg0, s32 *, 0x40));
}
