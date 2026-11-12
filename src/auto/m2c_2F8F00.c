#include "m2c_macros.h"

void func_002F8F00(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xC) == 3) {
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
    }
}
