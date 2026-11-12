#include "common.h"

s32 func_002DDD70(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E0750(s32 arg0);
extern u8 D_00347608[] __attribute__((section(".data")));

s32 func_002DDC20(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *p;

    if (arg0 == NULL) {
        p = D_00347608;
        *(s32 *)(p + 4) = arg2;
        *(s32 *)(p + 0) = arg1;
        return 0;
    }
    if (func_002E0750((s32)arg0) != 0) {
        return func_002DDD70(0, (s32)0xFF030203, arg2);
    }
    p = arg0 + 0x250;
    *(s32 *)(p + 4) = arg2;
    *(s32 *)(p + 0) = arg1;
    return 0;
}
