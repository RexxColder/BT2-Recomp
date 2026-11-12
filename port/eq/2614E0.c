#include "common.h"

s32 func_0025FED8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0);
s32 func_00261060(s32 arg0, s32 arg1);
extern s32 D_003B2654 __attribute__((section(".data")));

s32 func_002614E0(s32 arg0, s32 arg1, s32 arg2) {
    s32 f = D_003B2654 & 0x100;

    if (f != 0) {
        return f;
    }
    return func_0025FED8(func_00261060(arg0 & 0xFFFF, arg1), arg1, arg2, 1, 1);
}
