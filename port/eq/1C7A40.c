#include "common.h"

void func_00129C28(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
f32 func_00129CD8(s32 arg0, s32 arg1);
void BtlTask_SetDead(s32 arg0);

void func_001C7A40(u8 *arg0) {
    s32 sp[4];
    u8 *s4;
    u8 *s5;
    u8 *s2;
    u8 *s0;
    u8 *s1;
    s32 s3;
    s32 n;
    s32 a0v;
    f32 f0;
    f32 f1;

    s4 = (u8 *)*(s32 *)(arg0 + 0x38);
    n = *(s32 *)(s4 + 0x394);
    s5 = s4 + 0x330;
    s3 = n - 1;
    *(s32 *)(s4 + 0x390) = n;

    if (s3 > 0) {
        s2 = s4 + s3 * 0x50;
        s0 = s2 - 0x40;
        do {
            s1 = s2 - 0x50;
            func_00129C28((s32)(s2 + 0x10), (s32)s0);
            s3 -= 1;
            func_00129BD0((s32)sp, (s32)s0, 1.0f);
            func_00129B28((s32)s2, (s32)s1, (s32)sp);
            s2 = s1;
            s0 = s2 - 0x40;
        } while (s3 > 0);
    }

    func_00129B58((s32)sp, (s32)(s5 + 0x10), (s32)s4);
    Vec3_Normalize((s32)sp, (s32)sp);

    f0 = *(f32 *)(s5 + 0x44);
    f1 = *(f32 *)(s4 + 0x3B0) + f0 / *(f32 *)(s4 + 0x3B4);
    *(f32 *)(s4 + 0x3B0) = f1;
    f0 = *(f32 *)(s5 + 0x44);
    if (f0 < f1) {
        *(f32 *)(s4 + 0x3B0) = f0;
    }

    s0 = s4 + 0x3A0;
    if (func_00129CD8((s32)s0, (s32)sp) > 0.0f) {
        func_00129BD0((s32)sp, (s32)sp, *(f32 *)(s4 + 0x3B0));
        func_00129B28((s32)s0, (s32)s0, (s32)sp);
    }
    Vec3_Normalize((s32)s0, (s32)s0);
    func_00129C28((s32)(s4 + 0x10), (s32)s0);
    func_00129BD0((s32)s0, (s32)s0, *(f32 *)(s5 + 0x40));
    func_00129B28((s32)s4, (s32)s4, (s32)s0);

    f1 = *(f32 *)(s4 + 0x3BC) - 1.0f;
    a0v = *(s32 *)(s4 + 0x398);
    n = *(s32 *)(s4 + 0x394) + 1;
    f0 = f1 / *(f32 *)(s4 + 0x3B8);
    *(f32 *)(s4 + 0x3BC) = f1;
    *(s32 *)(s4 + 0x394) = n;
    *(f32 *)(s4 + 0x3C0) = f0 * 128.0f;
    if (a0v < n) {
        *(s32 *)(s4 + 0x394) = a0v;
    }
    if (*(f32 *)(s4 + 0x3BC) < 0.0f) {
        BtlTask_SetDead((s32)arg0);
    }
}
