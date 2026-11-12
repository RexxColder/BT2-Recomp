#include "m2c_macros.h"

extern s32 D_003A0368[2] __attribute__((section(".data")));

// Stores its two arguments into a 2-word global pair (arg0 at +0, arg1 at +4).
void func_003077F0(s32 arg0, s32 arg1) {
    D_003A0368[0] = arg0;
    D_003A0368[1] = arg1;
}
