#include "common.h"

extern u8 *D_00346C20 __attribute__((section(".data")));

s32 func_002C3210(s32 arg0) {
    s32 r = -1;

    if (arg0 != 0) {
        if (*(s32 *)(arg0 + 0x48) != 0) {
            r = 0;
            D_00346C20 = (u8 *)arg0;
        }
    }
    return r;
}
