#include "m2c_macros.h"

extern s32 D_00368074 __attribute__((section(".data")));
extern s32 D_00368078 __attribute__((section(".data")));

void func_0030BFA0(s32 arg0, s32 arg1) {
    D_00368074 = arg0;
    D_00368078 = arg1;
}
