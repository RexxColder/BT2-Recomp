#include "common.h"

extern s32 D_00348C40 __attribute__((section(".data")));
extern s32 D_00348C48 __attribute__((section(".data")));

void func_002E9360(void) {
    D_00348C48 += 1;
    if (D_00348C48 == 1) {
        D_00348C40 = 0;
    }
}
