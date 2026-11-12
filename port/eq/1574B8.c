#include "common.h"

s32 EftShot_TestBits();
void func_00156CD0(u8 *arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2);
void func_001DBF28(u8 *arg0);
s32 func_0020B3D0(s32 arg0);
extern f32 D_003846B0;
extern f32 D_003846B4;

void func_001574B8(u8 *arg0) {
    u8 sp[0x60];
    u8 *s0;
    u8 *s1;
    s32 s4;

    s0 = *(u8 **)(arg0 + 0x38);
    s1 = *(u8 **)(s0 + 0xB0);
    s4 = func_0020B3D0(*(s32 *)s1);
    *(f32 *)(sp + 0x30) = *(f32 *)(s0 + 0x80);
    *(f32 *)(sp + 0x34) = *(f32 *)(s0 + 0x84);
    *(f32 *)(sp + 0x3C) = 1.0f;
    *(f32 *)(sp + 0x38) = *(f32 *)(s0 + 0x88);
    *(s32 *)(sp + 0x44) = 0;
    *(s32 *)(sp + 0x40) = *(s32 *)s1;
    *(s32 *)(sp + 0x48) = 1;
    *(s32 *)(sp + 0x4C) = 1;
    *(s32 *)(sp + 0x50) = 0;
    /* the frame words at 0x00..0x30 are raw 8-byte copies of 0x30..0x58 (sp+0x58 is never written here) */
    *(s64 *)(sp + 0x00) = *(s64 *)(sp + 0x30);
    *(s64 *)(sp + 0x08) = *(s64 *)(sp + 0x38);
    *(s64 *)(sp + 0x10) = *(s64 *)(sp + 0x40);
    *(s64 *)(sp + 0x18) = *(s64 *)(sp + 0x48);
    *(s64 *)(sp + 0x20) = *(s64 *)(sp + 0x50);
    *(s64 *)(sp + 0x28) = *(s64 *)(sp + 0x58);

    if (EftShot_TestBits(*(s32 *)s1, 2, *(s64 *)(sp + 0x50), *(s64 *)(sp + 0x30), *(s64 *)(sp + 0x58)) != 0) {
        *(s32 *)(sp + 0x14) = 0x37;
        func_001DBF28(sp);
    }
    if (EftShot_TestBits(*(s32 *)s1, 0x10) != 0) {
        *(s32 *)(sp + 0x14) = 0x4A;
        func_001DBF28(sp);
    }
    if (EftShot_TestBits(*(s32 *)s1, 4) != 0) {
        *(s32 *)(sp + 0x14) = 0x52;
        func_001DBF28(sp);
        *(s32 *)(sp + 0x14) = 0x1C;
        *(s32 *)(sp + 0x18) = 1;
        *(s32 *)(sp + 0x1C) = 1;
        *(s32 *)(sp + 0x20) = 0x5D;
        func_001DBF28(sp);
    }
    if (EftShot_TestBits(*(s32 *)s1, 0x40) != 0) {
        func_00156CD0(arg0, 0, D_003846B0, 0.0f, D_003846B4);
    }
    if (EftShot_TestBits(*(s32 *)s1, 0x20) != 0) {
        *(s32 *)(sp + 0x14) = 0x36;
        *(s32 *)(sp + 0x18) = 3;
        *(s32 *)(sp + 0x1C) = 4;
        func_001DBF28(sp);
    }
    if (EftShot_TestBits(s4, 0x40) != 0) {
        func_00156CD0(arg0, 1, 0.5f, 0.0f, 1.0f);
    }
}
