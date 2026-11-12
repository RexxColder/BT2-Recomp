#include "common.h"

s32 func_001F3758(s32 arg0);
void func_00147FB8(s32 arg0);
void func_00147FD0(s32 arg0);
void func_0014EEF8(s32 arg0, s32 arg1);

void func_0014B9E8(s32 arg0) {
    s32 ret;
    s32 s0;
    s32 s1;

    ret = func_001F3758(arg0);
    s0 = *(s32 *)(arg0 + 0x38);
    func_0014EEF8(*(s32 *)(ret + 0x38), s0 + 0xB4);
    s1 = *(s32 *)(s0 + 0xB0);
    if (!(*(s32 *)s0 & 0x200)) {
        func_00147FB8(*(s32 *)s1);
    }
    if (*(s32 *)(*(s32 *)(s1 + 0x20) + 4) != 0) {
        func_00147FD0(*(s32 *)s1);
    }
}
