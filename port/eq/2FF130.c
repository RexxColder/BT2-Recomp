#include "common.h"

void *memset(void *dst, s32 c, u32 n);
void func_002FED70(s32 arg0, s32 arg1);
void func_002FC550(s32 arg0);
s32 func_002FC860(s32 arg0, s32 arg1);
s64 func_002FC730(s32 arg0, s64 arg1, s32 arg2);
s32 func_002FC920(s32 arg0, s32 arg1, s64 arg2);
void func_002FC8C8(s32 arg0);

s32 func_002FF130(s32 arg0, s32 arg1) {
    s32 sp[64];
    s32 s2;
    s64 s1;
    s64 s0;
    s32 t;

    memset(sp, 0, 0x100);
    func_002FED70(arg0, (s32)sp);
    func_002FC550(0x6000);
    s2 = func_002FC860((s32)sp, 1);
    func_002FC550(0x6001);
    if (s2 < 0) {
        return 0;
    }
    func_002FC550(0x6100);
    s1 = func_002FC730(s2, 0, 2);
    func_002FC550(0x6101);
    if (s1 < 0) {
        return 0;
    }
    func_002FC550(0x6200);
    s0 = (s64)(s32)func_002FC730(s2, 0, 0);
    func_002FC550(0x6201);
    s1 = (s1 >= 0x1001) ? 0x1000 : s1;
    if (s0 < 0) {
        return 0;
    }
    func_002FC550(0x6300);
    t = func_002FC920(s2, arg1, (s64)(s32)s1);
    func_002FC550(0x6301);
    if (t < 0) {
        func_002FC550(0x6500);
        func_002FC8C8(s2);
        func_002FC550(0x6501);
        return 0;
    }
    func_002FC550(0x6400);
    func_002FC8C8(s2);
    func_002FC550(0x6401);
    return 1;
}
