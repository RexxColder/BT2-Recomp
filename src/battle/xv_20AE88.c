#include "common.h"
s32 func_00202E60(s32 arg0, s32 arg1);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

s32 func_0020AE88(u32 arg0) {
    s32 i;
    s32 o;
    s32 r;
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        r = 1;
        o = func_00211288(arg0);
        for (i = 0; i < *(s32 *)((u8 *)o + 0x1184); i++) {
            if (*(s32 *)func_00202E60(o, i) > 0) {
                r = 0;
                break;
            }
        }
        return r;
    }
    return 0;
}
