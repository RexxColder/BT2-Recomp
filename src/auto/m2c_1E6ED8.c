#include "m2c_macros.h"

extern s32 *D_003878E8;

void func_001E6ED8(void *arg0) {
    *M2C_FIELD(arg0, s32 **, 0x38) = 0;
    *D_003878E8 -= 1;
}
