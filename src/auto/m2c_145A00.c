#include "m2c_macros.h"

extern void *gEftBound;

void func_00145A00(void) {
    if (gEftBound != NULL) {
        M2C_FIELD(gEftBound, s8 *, 1) = 1;
    }
}
