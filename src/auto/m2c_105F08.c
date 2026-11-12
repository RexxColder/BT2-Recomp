#include "m2c_macros.h"

void *func_00105A88();                              /* extern */

s32 func_00105F08(void) {
    return (M2C_FIELD(func_00105A88(), s32 *, 4) & 0xC0) != 0;
}
