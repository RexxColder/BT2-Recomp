#include "m2c_macros.h"

extern s32 D_00354F1C __attribute__((section(".data")));

s32 func_002F8178(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_00354F1C;
    D_00354F1C = arg0;
    return temp_v0;
}
