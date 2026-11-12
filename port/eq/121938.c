#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
s32 func_0011E1C8(s32 arg0);
f32 func_00121648(s32 arg0, s32 arg1);
f32 func_00121610(s32 arg0, s32 arg1);
s32 func_00121740(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_00126040(s32 arg0);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0InterVector(s32 arg0, s32 arg1, s32 arg2, f32 farg0);

void func_00121938(s32 arg0) {
    u8 sp[0xB0];
    u8 *self;
    u8 *s1;
    u8 *s3;
    u8 *s4;
    u8 *s6;
    u8 *s0p;
    s32 off;
    s32 s2;
    s32 fp;
    s32 v;
    s32 tail;
    s32 p;
    f32 f20;
    f32 f0;

    self = (u8 *)arg0;
    s4 = self + 0xFE0;
    s6 = self + 0xBE0;
    p = BtlChar_GetPos(func_00126040(arg0));
    func_003126C8((s32)(sp + 0x10), p);
    s2 = func_00121740(arg0, (s32)(sp + 0x10), (s32)sp, (s32)(sp + 0x40),
                       (s32)(self + 0xFE4), (s32)(self + 0xFE5));
    fp = s2;
    func_00121648((s32)sp, (s32)(sp + 0x10));
    s3 = self + 0x1050;
    tail = 0;

    if (s2 > 0) {
        off = s2 * 16;
        f20 = func_00121648((s32)(s6 + off + 0x10), (s32)(s6 + off + 0x20)) * *(f32 *)(sp + 0x40) + 20.0f;
        for (;;) {
            s0p = s6 + off + 0x10;
            s1 = s6 + off + 0x20;
            f0 = func_00121648((s32)s0p, (s32)s1);
            s3 = s4 + 0x70;
            if (f20 < f0) {
                sceVu0InterVector((s32)s3, (s32)s0p, (s32)s1, f20 / f0);
                s1 = s6 + 0x20;
                break;
            }
            s2 -= 1;
            f20 = f20 - f0;
            off = s2 * 16;
            if (s2 <= 0) {
                s1 = s6 + 0x20;
                tail = 1;
                break;
            }
        }
    } else {
        s1 = s6 + 0x20;
        tail = 1;
    }
    if (tail != 0) {
        s2 = 1;
        func_003126C8((s32)s3, (s32)(s6 + 0x20));
    }

    p = BtlChar_GetPos(func_00126040(arg0));
    func_003126C8((s32)(sp + 0x20), p);
    func_003126C8((s32)(sp + 0x30), (s32)s3);
    *(f32 *)(sp + 0x24) = *(f32 *)(sp + 0x24) - 5.0f;
    *(f32 *)(sp + 0x3C) = 1.0f;
    *(f32 *)(sp + 0x2C) = 1.0f;
    if (func_0011E1C8((s32)(sp + 0x20)) == 0) {
        *(s32 *)(s4 + 0x4C) = 0;
    } else {
        *(s32 *)(s4 + 0x4C) = *(s32 *)(s4 + 0x4C) + 1;
    }
    v = *(s32 *)(s4 + 0x8);
    *(s32 *)(s4 + 0x8) = fp;
    *(s32 *)(s4 + 0x10) = v;
    *(f32 *)(s4 + 0xC) = *(f32 *)(sp + 0x40);
    *(s32 *)(s4 + 0x14) = s2;
    func_003126C8((s32)(s4 + 0x60), (s32)sp);
    f0 = func_00121610((s32)s1, (s32)(sp + 0x10));
    *(f32 *)(s4 + 0x50) = f0;
    *(f32 *)(s4 + 0x7C) = 1.0f;
}
