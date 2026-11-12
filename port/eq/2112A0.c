#include "common.h"

extern u8 *D_00387930;

s32 func_002112A0(s32 arg0) {
    s32 b;

    b = (*(s32 *)(D_00387930 + 8) & 1) ? (arg0 == 0) : arg0;
    return *(s32 *)D_00387930 + b * 0x1550;
}
