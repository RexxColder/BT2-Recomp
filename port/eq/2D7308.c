#include "common.h"

extern s32 D_00347368 __attribute__((section(".data")));

void func_002D7308(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = 0;
        D_00347368 -= 1;
    }
}
