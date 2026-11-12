#include "m2c_macros.h"

extern void *D_003876A0;

s32 func_00109BC8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(D_003876A0, s64 *, 0x4D8) = (s64) (M2C_FIELD(D_003876A0, s64 *, 0x4D8) | 0x200);
    return 1;
}
