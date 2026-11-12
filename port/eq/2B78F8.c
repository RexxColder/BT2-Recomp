#include "m2c_macros.h"

s32 func_002B78D8(s32 arg0);
extern void (*D_00346BE4)(s32, s32) __attribute__((section(".data")));

void func_002B78F8(s32 arg0) {
    s32 temp;

    temp = func_002B78D8(arg0);
    if (D_00346BE4 != NULL) {
        D_00346BE4(arg0, temp);
    }
}
