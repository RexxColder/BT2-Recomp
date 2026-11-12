#include "m2c_macros.h"

void func_002D3220(void *arg0, s32 arg1) {
    if (arg1 > 0) {
        M2C_FIELD(arg0, s32 *, 0x10) = arg1;
    }
}
