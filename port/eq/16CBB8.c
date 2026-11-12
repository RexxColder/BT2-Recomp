#include "common.h"

s32 func_0020B3D0(s32 arg0);
s32 func_0016CA38(s32 arg0);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_00129BD0(u8 *arg1, u8 *arg2, f32 farg0);
void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Sub(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
extern f32 D_00384880;
extern f32 D_00384884;

void func_0016CBB8(u8 *arg0) {
    u8 sp[0x30];
    u8 *s0;
    u8 *s1;
    u8 *s3;
    s32 s2;
    s32 s4;
    s32 s5;
    s32 state;

    s1 = *(u8 **)(arg0 + 0x38);
    s0 = *(u8 **)(s1 + 0xB0);
    s2 = func_0020B3D0(*(s32 *)s0);
    s5 = func_0016CA38(s2);
    s4 = func_0016CA38(*(s32 *)s0);
    state = *(s32 *)(s1 + 0x10);
    s3 = sp + 0x10;

    switch (state) {
    case 0:
        s3 = s1 + 0x80;
        func_00208DE8(*(s32 *)s0, s1 + 0x50, *(s32 *)(s1 + 0x8));
        func_00129C28(s1 + 0x90, s3);
        Vec3_Add(s3, s3, s1 + 0xA0);
        if (s4 & 0x10) {
            func_00208DE8(s2, sp + 0x10, 0x11);
            func_00208DE8(*(s32 *)s0, sp + 0x20, 0x11);
            Vec3_Sub(sp, sp + 0x20, sp + 0x10);
            Vec3_Normalize(sp, sp);
            func_00129BD0(sp, sp, D_00384880);
            Vec3_Add(sp + 0x10, sp + 0x10, sp);
            func_00129C28(s3, sp + 0x10);
            *(s32 *)(s1 + 0x10) = 1;
        }
        break;
    case 1:
        func_00208DE8(s2, sp + 0x10, 0x11);
        func_00208DE8(*(s32 *)s0, sp + 0x20, 0x11);
        Vec3_Sub(sp, sp + 0x20, sp + 0x10);
        Vec3_Normalize(sp, sp);
        func_00129BD0(sp, sp, D_00384884);
        Vec3_Add(sp + 0x10, sp + 0x10, sp);
        func_00129C28(s1 + 0x80, sp + 0x10);
        if (s5 & 0x40) {
            *(s32 *)(s1 + 0x10) = 2;
        }
        break;
    default:
        break;
    }
}
