#include "common.h"

/* 0x00217518: merge of two 16-bit handles where -1 means none: both -1 -> -1; equal -> that value; one -1 -> the
 * other; otherwise (a0 & 0xFFFF) | (a1 << 16). */
s32 func_00217518(s32 arg0, s32 arg1) {
    s32 res;

    res = -1;
    if (arg0 == -1 && arg1 == -1) {
        return res;
    }
    res = arg1;
    if (arg0 == arg1) {
        return res;
    }
    if (arg0 == -1) {
        return res;
    }
    if (arg1 == -1) {
        return arg0;
    }
    return (arg0 & 0xFFFF) | (s32)((u32)arg1 << 16);
}
