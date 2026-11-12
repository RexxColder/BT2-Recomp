#include "m2c_macros.h"

extern void *D_00387ED0;

void func_002980A8(s32 arg0, s32 arg1) {
    M2C_FIELD(D_00387ED0, s32 *, 0x64) = arg0;
    M2C_FIELD(D_00387ED0, s32 *, 0x68) = arg1;
}
