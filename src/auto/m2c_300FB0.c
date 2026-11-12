#include "m2c_macros.h"

extern s32 D_0035B814 __attribute__((section(".data")));
extern s32 D_0035B818 __attribute__((section(".data")));

void func_00300FB0(s32 arg0, s32 arg1) {
    D_0035B814 = arg0;
    D_0035B818 = arg1;
}
