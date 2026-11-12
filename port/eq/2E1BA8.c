#include "common.h"

s32 func_002E1A38(u8 *arg0, s32 arg1, s32 arg2);
s32 func_002E1C98(u8 *arg0, s32 arg1);

s32 func_002E1BA8(u8 *arg0, s32 arg1, s32 arg2) {
    if (func_002E1A38(arg0, arg1, arg2) != 0) {
        return func_002E1C98(NULL, (s32)0xFF030203);
    }
    *(s32 *)(arg0 + 8) = arg2;
    *(s32 *)(arg0 + 4) = arg1;
    return 0;
}
