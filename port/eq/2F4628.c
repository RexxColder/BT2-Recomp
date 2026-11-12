#include "common.h"

extern s32 D_00354EC8 __attribute__((section(".data")));
extern s32 D_00354F14 __attribute__((section(".data")));

void func_002F4628(s32 arg0) {
    if (arg0 == 1) {
        D_00354F14 = 0x176A;
    } else if (arg0 == 2) {
        D_00354F14 = 0x1388;
    }
    D_00354EC8 = arg0;
}
