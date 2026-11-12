#include "common.h"

extern u8 D_003B0C14[] __attribute__((section(".data")));

s32  func_0028C520(s32 arg0, s32 arg1) {
    s32 idx;

    if (arg1 == 0x20000) {
        idx = 3;
    } else if (arg1 > 0x20000) {
        if (arg1 == 0x40000) {
            idx = 4;
        } else if (arg1 == 0x80000) {
            idx = 5;
        } else {
            return (u8)(0);
        }
    } else {
        if (arg1 != 0x10000) {
            return (u8)(0);
        }
        idx = 2;
    }
    return (u8)(D_003B0C14[arg0 * 0x180 + idx]);
}
