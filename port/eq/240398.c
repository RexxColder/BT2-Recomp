#include "common.h"

u8 *BtlKiBlast_Get(s32 arg0);
s32 func_00203C58(s32 arg0, s64 arg1);

s32 func_00240398(s32 arg0) {
    s32 s = *(s32 *)(BtlKiBlast_Get(arg0) + 0xC);

    if (func_00203C58(arg0, 0x200) != 0) {
        s = s / 2;
    }
    return s;
}
