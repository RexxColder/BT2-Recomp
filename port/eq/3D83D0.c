#include "m2c_macros.h"

extern void *D_003876A4 __attribute__((section(".data")));

s32 func_003D83D0(void *arg0) {
    s32 m;
    s32 s;

    m = M2C_FIELD(D_003876A4, s32 *, 0x90);
    s = M2C_FIELD(arg0, s32 *, 0x3320);
    switch (m) {
        case 0:
            return s == 2;
        case 1:
            return s == 3;
        case 2:
        case 3:
            return s == 4;
        default:
            return 0;
    }
}
