#include "m2c_macros.h"

void *func_00105A88();                              /* extern */

s32 func_00105EE0(void) {
    return ((s32) M2C_FIELD(func_00105A88(), s32 *, 4) >> 3) & 1;
}
