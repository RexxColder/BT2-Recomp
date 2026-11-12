#include "common.h"
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

s32 func_0020A658(u32 arg0) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        s32 n = *(s32 *)((u8 *)func_00211288(arg0) + 0x984);
        if (n > 0) { return 1; }
    }
    return 0;
}
