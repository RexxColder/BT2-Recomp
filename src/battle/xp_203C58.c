#include "m2c_macros.h"

void *func_00202DC0();                              /* extern */

s32 func_00203C58(s32 unused0, s64 arg1) {
    return (M2C_FIELD(func_00202DC0(unused0), s64 *, 0x28) & arg1) != 0;
}
