#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_001DBF28();
s32 func_0020B3D0(s32 arg0);

void func_00161B78(u8 *arg0) {
    u8 sp[0x60];
    u8 *temp_s0;
    s32 *temp_s1;
    s64 a1v;
    s64 a2v;
    s64 a3v;
    s64 t0v;
    s64 v1v;
    s64 v0v;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    temp_s1 = *(s32 **)(temp_s0 + 0x70);
    if (EftShot_TestBits(func_0020B3D0(*temp_s1), 0x40) != 0) {
        *(f32 *)(sp + 0x30) = *(f32 *)(temp_s0 + 0x40);
        *(f32 *)(sp + 0x34) = *(f32 *)(temp_s0 + 0x44);
        *(f32 *)(sp + 0x38) = *(f32 *)(temp_s0 + 0x48);
        *(f32 *)(sp + 0x3C) = 1.0f;
        *(s32 *)(sp + 0x44) = 0x47;
        *(s32 *)(sp + 0x40) = *temp_s1;
        *(s32 *)(sp + 0x4C) = 1;
        *(s32 *)(sp + 0x48) = 1;
        *(s32 *)(sp + 0x50) = 0;
        t0v = *(s64 *)(sp + 0x58);
        v1v = *(s64 *)(sp + 0x38);
        v0v = *(s64 *)(sp + 0x50);
        a1v = *(s64 *)(sp + 0x40);
        a2v = *(s64 *)(sp + 0x48);
        a3v = *(s64 *)(sp + 0x30);
        *(s64 *)(sp + 0x20) = v0v;
        *(s64 *)(sp + 0) = a3v;
        *(s64 *)(sp + 8) = v1v;
        *(s64 *)(sp + 0x10) = a1v;
        *(s64 *)(sp + 0x18) = a2v;
        *(s64 *)(sp + 0x28) = t0v;
        *(s32 *)(sp + 0x20) = 0;
        func_001DBF28(sp, a1v, a2v, a3v, t0v);
        *(s32 *)(sp + 0x20) = 3;
        func_001DBF28(sp);
        *(s32 *)(sp + 0x20) = 0xA;
        func_001DBF28(sp);
        *(s32 *)(sp + 0x20) = 0xE;
        func_001DBF28(sp);
        *(s32 *)(sp + 0x20) = 0x15;
        func_001DBF28(sp);
    }
}
