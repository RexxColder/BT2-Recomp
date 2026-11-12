#include "common.h"

extern u8 *D_00387930;
s32 func_001F9530(s32 arg0);

s32 func_001F9758(s32 arg0) {
    s32 r = func_001F9530(arg0);
    u8 *base = (u8 *)*(s32 *)(D_00387930 + 0x1C);
    s32 v = *(s16 *)(base + (0x31 - r) * 2);

    return v / 30;
}
