#include "common.h"

s32 func_00203C58(s32 arg0, s64 arg1);
u8 *func_0023FFD8(s32 arg0, s32 arg1);

s32 func_00240438(s32 arg0, s32 arg1) {
    s32 s = *(s32 *)(func_0023FFD8(arg0, arg1) + 0xC);

    if (func_00203C58(arg0, 0x200) != 0) {
        s = s / 2;
    }
    return s;
}
