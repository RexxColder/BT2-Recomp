#include "common.h"

extern s32 func_00211418(s32 arg0, s32 arg1);

s32 func_001FD088(s32 arg0, u32 arg1) {
    if (arg1 < 0xA) {
        func_00211418(arg0, 0x400);
    }
    if ((u32)(arg1 - 0x11) < 0x15) {
        func_00211418(arg0, 0x1000);
    }
    if ((u32)(arg1 - 0x33) < 5) {
        func_00211418(arg0, 0x4000);
    }
    if ((u32)(arg1 - 0x47) < 2) {
        func_00211418(arg0, 0x20000);
    }
    if (arg1 == 0x4A) {
        return func_00211418(arg0, 0x800);
    }
}
