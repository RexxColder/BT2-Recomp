#include "common.h"

s32 func_00241020(s32 arg0, s32 arg1);

s32 func_00241DD0(u8 *arg0, s32 arg1) {
    u8 *tab;
    s32 s0;
    s32 n;
    s32 ret;

    tab = *(u8 **)(*(u8 **)(arg0 + 0x1530) + 0x984);
    s0 = *(s32 *)(tab + (arg1 != 0) * 4 + 0x48);
    n = func_00241020((s32)arg0, arg1);
    ret = s0;
    if (n >= 2) {
        ret = s0 / n;
    }
    return ret;
}
