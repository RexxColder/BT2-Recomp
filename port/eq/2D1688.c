#include "common.h"

s32 func_002D1800(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00346DE0 __attribute__((section(".data")));

s32 func_002D1688(u8 *arg0, s32 *arg1, s32 *arg2) {
    s32 v0;

    v0 = func_002D1800((s32)arg0, (s32)arg1, (s32)arg2);
    if (v0 != 0) {
        *arg1 = *(s32 *)(arg0 + 0xD30 + 0x2A8);
        *arg2 = D_00346DE0;
        return 0;
    }
    return v0;
}
