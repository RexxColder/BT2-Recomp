#include "m2c_macros.h"

extern void *D_00387920;

void func_001F4288(s32 arg0) {
    if (D_00387920 != NULL) {
        M2C_FIELD(D_00387920, s32 *, 0x2C) = arg0;
    }
}
