#include "common.h"

s32 func_001C4FD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001A64B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

s32 func_001C6CF8(u8 *arg0, u8 *arg1) {
    u8 *s0;
    u8 *t1;
    s32 a3v;
    s32 a3b;
    s32 r;
    f32 f1;

    s0 = *(u8 **)(arg0 + 0x38);
    memset(s0, 0, 0x170);
    a3v = *(s32 *)(s0 + 0x50);
    *(s64 *)(s0 + 0x10) = *(s64 *)(arg1 + 0x00);
    *(s64 *)(s0 + 0x18) = *(s64 *)(arg1 + 0x08);
    *(s64 *)(s0 + 0x20) = *(s64 *)(arg1 + 0x10);
    *(s64 *)(s0 + 0x28) = *(s64 *)(arg1 + 0x18);
    *(s64 *)(s0 + 0x30) = *(s64 *)(arg1 + 0x20);
    *(s64 *)(s0 + 0x38) = *(s64 *)(arg1 + 0x28);
    *(s64 *)(s0 + 0x40) = *(s64 *)(arg1 + 0x30);
    *(s64 *)(s0 + 0x48) = *(s64 *)(arg1 + 0x38);
    t1 = *(u8 **)(arg1 + 0x38);
    a3b = *(s32 *)(arg1 + 0x3C);
    *(s32 *)(s0 + 0x50) = a3v | 1;
    *(s32 *)(s0 + 0x54) = *(u8 *)(t1 + 1);
    *(s32 *)(s0 + 0x58) = *(s32 *)(arg1 + 0x30);
    f1 = *(f32 *)(arg1 + 0x08);
    if (f1 <= 0.0f) {
        *(s32 *)(s0 + 0x50) = a3v | 9;
    } else {
        *(f32 *)(s0 + 0x68) = f1 * 30.0f;
    }
    *(f32 *)(s0 + 0x6C) = 5.0f;
    if (*(s32 *)(s0 + 0x54) != 2) {
        return func_001C4FD0((s32)s0, (s32)arg1, (s32)(s0 + 0x20), a3b);
    }
    r = func_001A64B0((s32)*(u8 *)arg1, *(s32 *)(arg1 + 0x04), (s32)(s0 + 0x20), a3b,
                      *(s32 *)(arg1 + 0x34), *(f32 *)(t1 + 0x04) * *(f32 *)(arg1 + 0x0C));
    *(s32 *)(s0 + 0x168) = r;
    return r;
}
