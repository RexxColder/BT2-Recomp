#include "m2c_macros.h"

void func_002F8D88(void *arg0, void *arg1, void *arg2) {
    M2C_FIELD(arg1, u16 *, 0) = (u16) M2C_FIELD(arg0, u16 *, 0x28);
    M2C_FIELD(arg2, u16 *, 0) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 0x2C);
    M2C_FIELD(arg2, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
}
