#include "m2c_macros.h"

void *func_00202DC0();                              /* extern */

void func_00203C88(s32 unused0, s64 arg1) {
    void *temp_v0;

    temp_v0 = func_00202DC0(unused0);
    M2C_FIELD(temp_v0, s64 *, 0x28) = (s64) (M2C_FIELD(temp_v0, s64 *, 0x28) & ~arg1);
}
