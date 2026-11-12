#include "m2c_macros.h"

M2C_UNK _raise_r(s32, s32);                         /* extern */
extern s32 D_0036A600 __attribute__((section(".data")));

void func_003256A8(s32 arg0) {
    _raise_r(D_0036A600, arg0);
}
