#include "m2c_macros.h"

s32 func_002FA020(s32);                             /* extern */

void func_002F2EE8(void *arg0, s32 *arg1) {
    *arg1 = func_002FA020(M2C_FIELD(arg0, s32 *, 8));
}
