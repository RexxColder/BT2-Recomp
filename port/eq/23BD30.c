#include "m2c_macros.h"

extern s32 func_00203118(s32 arg0);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern void *D_003876A0;

s32 func_0023BD30(s32 arg0) {
    if (*(s32 *)((u8 *)D_003876A0 + 0xD8) & 1) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x1188) <= 0x1869F) {
        return 0;
    }
    if (func_00211310(arg0, 0xA, 0x10) != 0) {
        return 0;
    }
    return func_00203118(arg0) >= 2;
}
