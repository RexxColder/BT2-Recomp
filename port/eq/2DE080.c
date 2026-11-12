#include "common.h"

void *memcpy(void *, const void *, unsigned int);
s32 func_002E0750(s32 arg0);
s32 func_002DDD70(s32 arg0, s32 arg1);

/* 0x002DE080: if func_002E0750(arg0) is non-zero, returns func_002DDD70(0, 0xFF03020C). Otherwise copies 0x80 bytes
 * from arg0+0x1D0 to arg1 and returns 0. */
s32 func_002DE080(u8 *arg0, u8 *arg1) {
    if (func_002E0750((s32)arg0) != 0) {
        return func_002DDD70(0, (s32)0xFF03020C);
    }
    memcpy(arg1, arg0 + 0x1D0, 0x80);
    return 0;
}
