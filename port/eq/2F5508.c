#include "common.h"

extern u8 D_0039D6D8[];
void func_002E9CE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

s32 func_002F5508(s32 arg0) {
    s32 loc[8];

    func_002E9CE0(arg0, 0x800, (s32)&loc[5], (s32)D_0039D6D8, (s32)&loc[4], (s32)&loc[0]);
    if (loc[5] != 0) {
        return (s32)D_0039D6D8;
    }
    return 0;
}
