#include "common.h"

s32 func_0020C5E8(s32 arg0);
extern s32 D_003876A0;

s32 func_00103168(s32 arg0) {
    s32 base = D_003876A0 + arg0 * 0x1D0;
    s32 temp;
    s32 count;

    temp = func_0020C5E8(arg0);
    count = *(s32 *)(base + 0xE0);
    if (temp >= count) {
        return 0;
    }
    if (temp < 0) {
        return 0;
    }
    return base + 0xE0 + temp * 0x58 + 8;
}
