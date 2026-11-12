#include "common.h"

extern f32 D_00384888;
extern f32 D_0038488C;

s32 func_0020B3D0(s32 arg0);
s32 func_0016CA38(s32 arg0);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129C28(s32 arg0, s32 arg1);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);

void func_0016CEA0(u8 *arg0) {
    u8 sp[0x30];
    f32 f20;
    u8 *s3;
    u8 *s0;
    s32 s4;
    s32 s5;
    s32 s6;
    s32 s2;
    f32 f0;

    f20 = D_00384888;
    s3 = *(u8 **)(arg0 + 0x38);
    s0 = *(u8 **)(s3 + 0xB0);
    s4 = func_0020B3D0(*(s32 *)s0);
    if (**(s32 **)(s0 + 0x20) == 0x161) {
        f20 = 30.0f;
    }
    s6 = func_0016CA38(s4);
    s5 = func_0016CA38(*(s32 *)s0);
    s2 = *(s32 *)(s3 + 0x10);
    if (s2 == 1) {
        func_00208DE8(s4, (s32)(sp + 0x10), 0x11);
        func_00208DE8(*(s32 *)s0, (s32)(sp + 0x20), 0x11);
        Vec3_Sub((s32)sp, (s32)(sp + 0x20), (s32)(sp + 0x10));
        Vec3_Normalize((s32)sp, (s32)sp);
        func_00129BD0((s32)sp, (s32)sp, f20);
        Vec3_Add((s32)(sp + 0x10), (s32)(sp + 0x10), (s32)sp);
        func_00129C28((s32)(s3 + 0x80), (s32)(sp + 0x10));
        *(s32 *)(s3 + 0x10) = s2;
        if (s5 & 0x20) {
            *(s32 *)s3 = *(s32 *)s3 | 0x200;
        }
        s6 = s6 & 0x40;
        if (*(s32 *)s3 & 0x200) {
            f0 = *(f32 *)(s3 + 0x20) + D_0038488C;
            *(f32 *)(s3 + 0x20) = f0;
            if (f0 > 2.0f) {
                *(f32 *)(s3 + 0x20) = 2.0f;
            }
        }
        if (s6 != 0) {
            *(s32 *)(s3 + 0x10) = 2;
        }
        return;
    }
    if (s2 != 0) {
        return;
    }
    func_00208DE8(*(s32 *)s0, (s32)(s3 + 0x50), *(s32 *)(s3 + 8));
    func_00129C28((s32)(s3 + 0x90), (s32)(s3 + 0x80));
    Vec3_Add((s32)(s3 + 0x80), (s32)(s3 + 0x80), (s32)(s3 + 0xA0));
    func_00208DE8(s4, (s32)(sp + 0x10), 0x11);
    func_00208DE8(*(s32 *)s0, (s32)(sp + 0x20), 0x11);
    Vec3_Sub((s32)sp, (s32)(sp + 0x20), (s32)(sp + 0x10));
    Vec3_Normalize((s32)sp, (s32)sp);
    func_00129BD0((s32)sp, (s32)sp, f20);
    Vec3_Add((s32)(sp + 0x10), (s32)(sp + 0x10), (s32)sp);
    func_00129C28((s32)(s3 + 0x80), (s32)(sp + 0x10));
    *(s32 *)(s3 + 0x10) = 1;
}
