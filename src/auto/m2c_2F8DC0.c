#include "m2c_macros.h"

void func_002F8DC0(void *arg0, u16 *arg1, u16 *arg2, u16 *arg3) {
    *arg1 = M2C_FIELD(arg0, u16 *, 0x34);
    *arg2 = M2C_FIELD(arg0, u16 *, 0x36);
    *arg3 = M2C_FIELD(arg0, u16 *, 0x38);
}
