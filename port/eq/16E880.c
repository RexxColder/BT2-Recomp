#include "common.h"

void func_0014EEF8(s32 arg0, s32 arg1);
void func_00147FB8(s32 arg0);
s32 func_001F3758(s32 arg0);

void func_0016E880(u8 *arg0) {
    u8 *r = (u8 *)func_001F3758((s32)arg0);
    u8 *a1 = *(u8 **)(arg0 + 0x38);
    s32 a0v = *(s32 *)(r + 0x38);
    u8 *s0 = *(u8 **)(a1 + 0xB0);

    func_0014EEF8(a0v, (s32)(a1 + 0xB4));
    func_00147FB8(*(s32 *)s0);
}
