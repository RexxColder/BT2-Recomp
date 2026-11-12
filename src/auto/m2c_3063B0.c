#include "m2c_macros.h"

s32 func_003062A0(s32, s32);                             /* extern */

void func_003063B0(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = (s32) (arg0 + 0x10);
    M2C_FIELD(arg1, s32 *, 4) = func_003062A0(arg0 + 8, arg1);
}
