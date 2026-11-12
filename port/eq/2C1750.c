#include "common.h"

s32 func_002C1808(s32 arg0, s32 arg1, s32 arg2);
void func_002C1988(s32 arg0, s32 arg1, s32 arg2);
void func_002C1AC8(s32 arg0, s32 arg1, s32 arg2);
void func_002C2150(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_0037A258 __attribute__((section(".data")));

s32 func_002C1750(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 r;
    u8 *p;

    p = (u8 *)arg2;
    r = func_002C1808(arg0, arg1, (s32)sp);
    if (r == 0) {
        return 0;
    }
    *(s32 *)(p + 0x10) = r;
    if (r == -1) {
        return 1;
    }
    if (sp[0] > 0) {
        *(s32 *)(p + 0x1C) = sp[0] * 0x32;
    }
    *(s32 *)(p + 4) = (s32)&D_0037A258;
    func_002C1988(arg0, arg1, arg2);
    func_002C1AC8(arg0, arg1, arg2);
    func_002C2150(arg0, arg1, arg2);
    return 1;
}
