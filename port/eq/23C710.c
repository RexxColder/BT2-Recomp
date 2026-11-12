#include "common.h"

s32 func_0023BDA8(s32 arg0, s32 arg1);
s32 func_0023F410(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

/* 0x0023C710(obj): func_0023F410(obj); mode = func_00211310(obj, 0, 4) != 0 ? 0x70200A1 : 0x7000081;
 * r = func_0023BDA8(obj, mode); returns 6 when r == -1, else r. */
s32 func_0023C710(s32 arg0) {
    s32 mode = 0x7000081;
    s32 r;

    func_0023F410(arg0);
    r = func_00211310(arg0, 0, 4);
    if (r != 0) {
        mode = 0x70200A1;
    }
    r = func_0023BDA8(arg0, mode);
    if (r == -1) {
        r = 6;
    }
    return r;
}
