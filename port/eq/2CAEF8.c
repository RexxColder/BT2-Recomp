#include "common.h"

void func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(u8 *arg0);
s32 func_002CAF88(u8 *arg0, s32 arg1);

s32 func_002CAEF8(u8 *arg0) {
    s32 t;
    s32 r;

    t = func_002C3210(arg0);
    if (t != 0) {
        func_002C2FF0(0, 0xFF000187);
        return 0;
    }
    r = func_002CAF88(arg0, 0xFF000187);
    if (*(s32 *)(arg0 + 0x58) == 1) {
        if (*(s32 *)(arg0 + 0x96C) < *(s32 *)(arg0 + 0x968)) {
            r = r - (t < r);
        }
    }
    return r;
}
