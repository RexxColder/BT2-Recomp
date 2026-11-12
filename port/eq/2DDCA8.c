#include "common.h"

extern u8 D_00347608[] __attribute__((section(".data")));

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002E0750(u8 *arg0);
s32 func_002DDD70(s32 arg0, s32 arg1);

s32 func_002DDCA8(u8 *arg0, u8 *arg1) {
    if (arg0 == NULL) {
        memcpy(arg1, D_00347608, 0x14);
        return 0;
    }
    if (func_002E0750(arg0) == 0) {
        memcpy(arg1, arg0 + 0x250, 0x14);
        return 0;
    }
    return func_002DDD70(0, (s32)0xFF030204);
}
