#include "m2c_macros.h"

s32 func_00300640(s32);                             /* extern */

void func_002BB3E8(void *arg0, s32 *arg1) {
    *arg1 = func_00300640(M2C_FIELD(arg0, s32 *, 0x48));
}
