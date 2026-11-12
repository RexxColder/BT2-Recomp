#include "m2c_macros.h"

extern void *D_003876A0;

s32 func_00126560(void) {
    return (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 3) == 0;
}
