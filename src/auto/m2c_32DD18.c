#include "m2c_macros.h"

double _strtod_r(s32, s32, M2C_UNK);               /* extern */
extern s32 D_0036A600 __attribute__((section(".data")));

/* strtod(s, end): tail call, the double result stays in f0. */
double func_0032DD18(s32 arg0, M2C_UNK arg1) {
    return _strtod_r(D_0036A600, arg0, arg1);
}
