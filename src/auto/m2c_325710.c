#include "m2c_macros.h"

M2C_UNK __sigtramp_r(s32, s32);                     /* extern */
extern s32 D_0036A600 __attribute__((section(".data")));

void func_00325710(s32 arg0) {
    __sigtramp_r(D_0036A600, arg0);
}
