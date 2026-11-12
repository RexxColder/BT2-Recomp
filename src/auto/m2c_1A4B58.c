#include "m2c_macros.h"

extern void *D_00387824;

void func_001A4B58(s32 arg0, s32 arg1, s32 arg2) {
    if (D_00387824 != NULL) {
        M2C_FIELD(D_00387824, s32 *, 4) = arg0;
        M2C_FIELD(D_00387824, s32 *, 0) = arg1;
        M2C_FIELD(D_00387824, s32 *, 8) = arg2;
    }
}
