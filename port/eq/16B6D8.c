#include "common.h"

s32 func_0020B3D0(s32 arg0);
s32 func_0016CA20(s32 arg0, s32 arg1, s32 arg2);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
void func_0012D3A0(s32 arg0, s32 arg1, s32 arg2);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);

void func_0016B6D8(u8 *arg0) {
    s32 sp[4];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    s32 s5;
    s32 v;
    s32 a;

    s3 = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)(s3 + 0xB0);
    s0 = s3 + 0x50;
    s1 = s3 + 0x70;
    s4 = s3 + 0x80;
    s5 = func_0020B3D0(*(s32 *)s2);
    v = func_0016CA20(*(s32 *)s2, 4, (s32)s2);
    *(s32 *)(s3 + 8) = v;
    func_00208DE8(*(s32 *)s2, (s32)s0, v);
    func_00129C28((s32)s1, (s32)s0);
    func_00129C28((s32)s4, (s32)s1);
    func_00129C28((s32)(s3 + 0x90), (s32)s4);
    a = *(s32 *)*(u8 **)(s2 + 0x20);
    switch (a) {
        case 0x165:
        case 0x132:
        case 0x84:
            s0 = s3 + 0x30;
            func_0012D3A0((s32)s0, (s32)s4, *(s32 *)s2);
            break;
        case 0x97:
            s0 = s3 + 0x30;
            func_00208DE8(*(s32 *)s2, (s32)s0, 0x22);
            func_00208DE8(*(s32 *)s2, (s32)sp, 0x23);
            Vec3_Sub((s32)s0, (s32)sp, (s32)s0);
            *(f32 *)(s3 + 0x3C) = 1.0f;
            Vec3_Normalize((s32)s0, (s32)s0);
            break;
        case 0xA3:
            s0 = s3 + 0x30;
            func_00208DE8(*(s32 *)s2, (s32)s0, 0x14);
            func_00208DE8(*(s32 *)s2, (s32)sp, 0x15);
            Vec3_Sub((s32)s0, (s32)sp, (s32)s0);
            *(f32 *)(s3 + 0x3C) = 1.0f;
            Vec3_Normalize((s32)s0, (s32)s0);
            break;
        case 0x134:
            s0 = s3 + 0x30;
            func_00208DE8(*(s32 *)s2, (s32)s0, 0x2E);
            func_00208DE8(*(s32 *)s2, (s32)sp, 3);
            Vec3_Sub((s32)s0, (s32)sp, (s32)s0);
            *(f32 *)(s3 + 0x3C) = 1.0f;
            Vec3_Normalize((s32)s0, (s32)s0);
            break;
        default:
            s0 = s3 + 0x30;
            func_00208DE8(s5, (s32)sp, 3);
            Vec3_Sub((s32)s0, (s32)sp, (s32)s4);
            *(f32 *)(s3 + 0x3C) = 1.0f;
            Vec3_Normalize((s32)s0, (s32)s0);
            break;
    }
    func_00129BD0((s32)(s3 + 0xA0), (s32)s0, *(f32 *)(s3 + 0x1C));
    *(s32 *)s3 = *(s32 *)s3 | 0x100;
}
