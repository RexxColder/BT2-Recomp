#include "common.h"

void func_002C1230(s32 arg0, s32 arg1);
s32 func_002C6F80(s32 arg0);
s32 func_002C6FE0(s32 arg0);
s32 func_002CBE18(s32 arg0);
s32 func_002CC778(s32 arg0);
s32 func_002D07B0(s32 arg0, s32 arg1);
void func_002D0DD8(s32 arg0, s32 arg1);

s32 func_002C6EB0(s32 arg0) {
    u8 *s1;
    u8 *s2;
    s32 a1;
    s32 v0;

    s1 = (u8 *)arg0 + 0xD30;
    s2 = (u8 *)*(s32 *)((u8 *)arg0 + 0x1FC0);
    if (func_002D07B0(arg0, 6) == 0) {
        a1 = func_002C6F80(arg0);
    } else {
        a1 = func_002C6FE0(arg0);
        if (a1 < 0) {
            return -1;
        }
    }
    if (a1 > 0) {
        func_002C1230(arg0, a1);
        *(s32 *)(s2 + 0x88) = *(s32 *)(s2 + 0x88) + 1;
        if (func_002CBE18(arg0) != 0) {
            *(s32 *)(s1 + 0x160) = func_002CC778(arg0) + 1;
        }
    }
    func_002D0DD8((s32)(s1 + 0x3C), 0x7FFFFFFF);
    func_002D0DD8((s32)(s1 + 0x68), -1);
    *(s32 *)(s2 + 0x78) = 0xC0;
    v0 = 0;
    return v0;
}
