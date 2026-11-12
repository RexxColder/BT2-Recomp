#include "m2c_macros.h"

extern s32 D_00356EA8 __attribute__((section(".data")));

void func_002FF838(s32 arg0) {
    if (arg0 != 0) {
        if (arg0 == 1) {
            D_00356EA8 = arg0;
            return;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        D_00356EA8 = 0x8001;
        return;
    }
    D_00356EA8 = 0x8001;
}
