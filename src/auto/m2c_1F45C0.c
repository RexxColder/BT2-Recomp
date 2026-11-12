#include "m2c_macros.h"

extern void *D_00387920;

void func_001F45C0(f32 arg0) {
    if (D_00387920 != NULL) {
        M2C_FIELD(D_00387920, f32 *, 0x48) = arg0;
    }
}
