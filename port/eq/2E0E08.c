#include "m2c_macros.h"

extern s32 D_00347A30 __attribute__((section(".data")));

void func_002E0E08(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0;
        D_00347A30 -= 1;
    }
}
