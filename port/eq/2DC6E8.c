#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002DCC38(s32 a0, s32 a1, s32 a2, void *a3, void *t0);
s32 func_002DCA68(s32 a0, s32 a1);

s32 func_002DC6E8(s32 arg0, void *arg1, s32 arg2, void *arg3, void *arg4) {
    u8 *s0;

    if (func_002DCC38(arg0, (s32)(long)arg1, arg2, arg3, arg4) != 0) {
        /* the later arguments are clobbered by the call above: only the first two are passed on. */
        return func_002DCA68(0, (s32)0xFF020202);
    }
    s0 = (u8 *)(long)arg0 + (arg2 << 5);
    memcpy(arg1, s0 + 0x48, 0x20);
    return 0;
}
