#include "common.h"

s32 func_002DDD70(s32 arg0, s32 arg1);
s32 func_002E0750(s32 arg0);
extern u8 D_00399DA8[] __attribute__((section(".data")));

s32 func_002E06C0(s32 arg0, s32 arg1, s32 *arg2) {
    u8 *base;

    if (arg0 == 0) {
        base = D_00399DA8;
    } else {
        if (func_002E0750(arg0) != 0) {
            return func_002DDD70(0, 0xFF030210);
        }
        base = (u8 *)(arg0 + 0x190);
    }
    *arg2 = *(s32 *)(base + arg1 * 4);
    return 0;
}
