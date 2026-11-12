#include "common.h"

s32 func_001F3758(s32 arg0);
void func_0014EEF8(s32 arg0, s32 arg1);
void func_0015F2C0(s32 arg0);
s32 func_00147FB8(s32 arg0);

s32 func_0015F998(u8 *arg0) {
    s32 v0 = func_001F3758((s32)arg0);
    s32 v1 = *(s32 *)(arg0 + 0x38);
    s32 s1 = *(s32 *)((u8 *)v1 + 0xF0);

    func_0014EEF8(*(s32 *)((u8 *)v0 + 0x38), v1 + 0xF4);
    func_0015F2C0((s32)arg0);
    return func_00147FB8(*(s32 *)((u8 *)s1));
}
