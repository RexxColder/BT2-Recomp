#include "common.h"

s32 func_001F3758(s32 arg0);
void func_0014EEF8(s32 arg0, s32 arg1);
s32 func_00147FB8(s32 arg0);

s32 func_0016C3C0(u8 *arg0) {
    s32 v0 = func_001F3758((s32)arg0);
    s32 v1 = *(s32 *)((u8 *)v0 + 0x38);
    s32 s0;
    s32 a;

    a = *(u8 *)(v1 + 0x1E80);
    s0 = *(s32 *)((u8 *)(*(s32 *)(arg0 + 0x38)) + 0xB0);
    if (a != 0) {
        func_0014EEF8(v1, *(s32 *)(arg0 + 0x38) + 0xB4);
    }
    return func_00147FB8(*(s32 *)((u8 *)s0));
}
