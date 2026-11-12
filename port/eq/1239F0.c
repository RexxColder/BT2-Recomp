#include "common.h"

s32 func_002745F8(s32 arg0, s32 arg1);

f32 func_001239F0(s32 arg0, s32 arg1) {
    s32 a1 = arg1 * 2;
    s8 b = *(s8 *)(*(s32 *)(arg0 + 0x64) + arg1);
    s16 v;

    if (b >= 0 && func_002745F8(b, a1) != 0) {
        v = *(s16 *)(*(s32 *)(arg0 + 0x58) + a1);
    } else {
        v = *(s16 *)(*(s32 *)(arg0 + 0x54) + a1);
    }
    return (f32)v;
}
