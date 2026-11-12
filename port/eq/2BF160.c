#include "common.h"

void func_002D20E8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);

void func_002BF160(s32 arg0, u8 *arg1, s32 arg2) {
    s32 loc[2];
    s32 r;

    func_002D20E8(arg0, (s32)&loc[0], (s32)&loc[1]);
    r = func_002E0A98(arg2, loc[0], loc[1]);
    *(s32 *)arg1 = r;
}
