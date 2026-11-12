#include "common.h"

s32 func_002DDD70(s32 arg0, s32 arg1);
void func_002E0598(s32 arg0, s32 arg1);
s32 func_002E0750(s32 arg0);
void func_002E07F0(s32 arg0, s32 arg1);

s32 func_002E0528(s32 arg0) {
    if (func_002E0750(arg0) != 0) {
        return func_002DDD70(0, 0xFF030201);
    }
    func_002E07F0(arg0, 0xFF030201);
    func_002E0598(arg0, 0x40C);
    *(s32 *)((u8 *)arg0 + 0x188) = 1;
    return 0;
}
