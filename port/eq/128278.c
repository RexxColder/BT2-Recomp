#include "common.h"

s32 func_00129C28(s32 arg0, s32 arg1);
s32 func_00181ED0(s32 arg0);
void func_0019F370(s32 arg0, s32 arg1);
void func_0019F3B0(s32 arg0, s32 arg1);
void *memset(void *s, s32 c, u32 n);

void func_00128278(u8 *arg0) {
    u8 buf[0x90];
    u8 *p60;
    u8 *s0;

    p60 = *(u8 **)(arg0 + 0x60);
    *(f32 *)(p60 + 0x1C) = 1.0f;
    s0 = *(u8 **)(arg0 + 0x68);

    switch (s0[0x1A]) {
    case 0:
        func_0019F370((s32)(p60 + 0x10), *(s32 *)(arg0 + 4));
        return;
    case 0x12:
        if (*(s32 *)(p60 + 4) & 3) {
            func_0019F3B0((s32)(p60 + 0x10), *(s32 *)(arg0 + 4));
            return;
        }
        memset(buf, 0, 0x50);
        *(s64 *)(buf + 0x00) = *(s64 *)(s0 + 0x00);
        *(s64 *)(buf + 0x08) = *(s64 *)(s0 + 0x08);
        *(s64 *)(buf + 0x10) = *(s64 *)(s0 + 0x10);
        *(s64 *)(buf + 0x18) = *(s64 *)(s0 + 0x18);
        *(s64 *)(buf + 0x20) = *(s64 *)(s0 + 0x20);
        *(s64 *)(buf + 0x28) = *(s64 *)(s0 + 0x28);
        *(s64 *)(buf + 0x30) = *(s64 *)(s0 + 0x30);
        *(s64 *)(buf + 0x38) = *(s64 *)(s0 + 0x38);
        func_00129C28((s32)(buf + 0x40), (s32)(p60 + 0x10));
        if (func_00181ED0((s32)buf) == 0) {
            func_0019F3B0((s32)(p60 + 0x10), *(s32 *)(arg0 + 4));
        }
        return;
    default:
        func_0019F3B0((s32)(p60 + 0x10), *(s32 *)(arg0 + 4));
        return;
    }
}
