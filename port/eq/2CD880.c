#include "common.h"

s32 func_002CD960(s32 arg0);
s32 func_002CDA00(s32 arg0);
s32 func_002CDAB8(s32 arg0);
s32 func_002D07B0(s32 arg0, s32 arg1);
void func_002D1510(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D1908(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);

s32 func_002CD880(s32 arg0) {
    s32 out[2];
    s32 s0;
    s32 s1;

    if (func_002CD960(arg0) != 0) {
        return 1;
    }
    if (func_002D07B0(arg0, 5) == 1 && func_002CDA00(arg0) != 0) {
        return 1;
    }
    if (func_002D07B0(arg0, 6) == 1 && func_002CDAB8(arg0) != 0) {
        return 1;
    }
    func_002D1510(arg0, (s32)&out[0], (s32)&out[1]);
    s0 = *(s32 *)(arg0 + 0xD30 + 0x288);
    s1 = *(s32 *)(arg0 + 0xD30 + 0x284);
    s1 = s1 - func_002E0A98(func_002D07B0(arg0, 0x45), s0, 1000000);
    return func_002D1908(out[0], out[1], s1, s0) != 0;
}
