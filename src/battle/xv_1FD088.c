#include "common.h"

void func_00211418(s32 arg0, s32 arg1);

/* sets the flag bits of arg1's range on arg0 (0x400, 0x1000, 0x4000, 0x20000, and 0x800 for arg1 == 0x4A) */
void func_001FD088(s32 arg0, u32 arg1) {
    if (arg1 < 0xAU) {
        func_00211418(arg0, 0x400);
    }
    if ((u32)(arg1 - 0x11) < 0x15U) {
        func_00211418(arg0, 0x1000);
    }
    if ((u32)(arg1 - 0x33) < 5U) {
        func_00211418(arg0, 0x4000);
    }
    if ((u32)(arg1 - 0x47) < 2U) {
        func_00211418(arg0, 0x20000);
    }
    if (arg1 == 0x4A) {
        func_00211418(arg0, 0x800);
    }
}
