#include "m2c_macros.h"

void func_002F8EB8(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xC) == 0) {
        M2C_FIELD(arg0, s32 *, 0x10) = 0;
        M2C_FIELD(arg0, s32 *, 0xC) = 1;
    }
}
