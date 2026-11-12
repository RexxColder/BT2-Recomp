#include "common.h"

s32 BtlChar_GetPos(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00218838(s32 arg0, s32 arg1);
f32 func_0029DFD0(s32 arg0);
extern f32 D_00386368;

s32 func_00227DA0(s32 arg0) {
    s32 s1;
    s32 a1v;
    s32 p;

    s1 = func_00218838(arg0, 0);
    a1v = (s1 == 0) ? 0xE8 : 0xE9;
    if (func_00211310(arg0, 0, 0x100) != 0) {
        return a1v;
    }
    p = BtlChar_GetPos(arg0, a1v);
    if (D_00386368 < func_0029DFD0(p + 0x50)) {
        return (s1 == 0) ? 0xE3 : 0xE4;
    }
    return (s1 == 0) ? 0xE6 : 0xE7;
}
