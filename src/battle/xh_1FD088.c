#include "m2c_macros.h"

M2C_UNK func_00211418();                /* extern */

// Battle effect setup: calls func_00211418 with a flag mask chosen by ranges of arg1 (arg0 = object).
void func_001FD088(s32 arg0, u32 arg1) {
    if (arg1 < 0xAU) {
        func_00211418(arg0, 0x400);
    }
    if ((u32) (arg1 - 0x11) < 0x15U) {
        func_00211418(arg0, 0x1000);
    }
    if ((u32) (arg1 - 0x33) < 5U) {
        func_00211418(arg0, 0x4000);
    }
    if ((u32) (arg1 - 0x47) < 2U) {
        func_00211418(arg0, 0x20000);
    }
    if (arg1 == 0x4A) {
        func_00211418(arg0, 0x800);
    }
}
