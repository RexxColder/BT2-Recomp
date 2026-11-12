#include "common.h"

s32 func_00211288(s32 arg0);
extern s32 D_00387930;

/* 1 when D_00387930 is set, arg0 < 2 and the s32 at +0xB74 of func_00211288(arg0) is positive, else 0 */
s32 func_0020B070(u32 arg0) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        s32 n = *(s32 *)((u8 *)func_00211288(arg0) + 0xB74);
        if (n > 0) { return 1; }
    }
    return 0;
}
