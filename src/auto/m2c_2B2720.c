#include "m2c_macros.h"

extern s32 D_0034520C __attribute__((section(".data")));
extern s32 D_00345210 __attribute__((section(".data")));

s32 func_002B2720(s32 arg0, s32 arg1) {
    D_0034520C = arg0;
    D_00345210 = arg1;
    return 0;
}
