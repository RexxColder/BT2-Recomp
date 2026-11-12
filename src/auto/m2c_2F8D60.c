#include "m2c_macros.h"

void func_002F8D60(void *arg0, void *arg1, void *arg2) {
    M2C_FIELD(arg0, u16 *, 0x28) = (u16) M2C_FIELD(arg1, u16 *, 0);
    M2C_FIELD(arg0, u16 *, 0x2A) = (u16) M2C_FIELD(arg2, u16 *, 0);
    M2C_FIELD(arg0, u16 *, 0x2C) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(arg2, u16 *, 2);
}
