#include "m2c_macros.h"

extern void *D_003876A0;

s32 func_00101E58(void) {
    return ((s32) M2C_FIELD(D_003876A0, s32 *, 0x480) >> 3) & 1;
}
