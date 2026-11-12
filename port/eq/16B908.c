#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 func_0020B3D0(s32 arg0);
void func_0019F8D0(u8 *arg0, s64 arg1, s64 arg2, u8 *arg3);
extern u8 D_0036E5F0[] __attribute__((section(".data")));

void func_0016B908(u8 *arg0) {
    s64 spd[4];
    u8 *sp;
    u8 *s0;

    sp = (u8 *)spd;
    s0 = *(u8 **)(arg0 + 0x38);
    if (EftShot_TestBits(func_0020B3D0(*(s32 *)*(u8 **)(s0 + 0xB0)), 0x40) != 0) {
        spd[0] = *(s64 *)(D_0036E5F0 + 0x00);
        spd[1] = *(s64 *)(D_0036E5F0 + 0x08);
        spd[2] = *(s64 *)(D_0036E5F0 + 0x10);
        spd[3] = *(s64 *)(D_0036E5F0 + 0x18);
        if (*(s32 *)s0 & 0x8000) {
            *(f32 *)(sp + 0x10) = 1.0f;
            *(s32 *)(sp + 0x14) = 0;
            *(s32 *)(sp + 0x18) = 0;
        }
        func_0019F8D0(sp, *(s64 *)(D_0036E5F0 + 0x00), *(s64 *)(D_0036E5F0 + 0x08), D_0036E5F0);
    }
}
