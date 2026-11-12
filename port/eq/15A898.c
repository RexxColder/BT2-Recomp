#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void BtlTask_SetDead(u8 *arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00129BD0(u8 *arg1, u8 *arg2, f32 farg0);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_0012D488(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_0012D5D8(f32 farg0, u8 *arg1, u8 *arg2, u8 *arg3, s32 arg4, f32 farg1);
void func_00151FB0(u8 *arg0);
s32 func_00152200(s32 arg0, u8 *arg1);
void func_00152530(u8 *arg0, u8 *arg1);
void func_00152930(s32 arg0, u8 *arg1, s32 arg2);
void func_00152960(s32 arg0, u8 *arg1);
void func_0015A370(u8 *arg0);
void func_0015A468(s32 arg0, s32 arg1, u8 *arg2, s32 arg3);
void func_001A1210(s32 arg0);
void func_001A12D8(f32 farg0, s32 arg1);
f32 func_001A1348(s32 arg0);
void func_001A1378(s32 arg0, u8 *arg1);
u8 *func_001F3758(void *arg0);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
f32 func_00209D20(s32 arg0);

void func_0015A898(u8 *arg0) {
    u8 *s0;
    u8 *s1;
    u8 *s3;
    u8 *s4;
    u8 *p70;
    u8 *v1;
    s32 s5;
    s32 flag;
    s32 a2;
    f32 ft;

    flag = 0;
    s1 = *(u8 **)(arg0 + 0x38);
    s5 = *(s32 *)(func_001F3758(arg0) + 0x38);
    s3 = *(u8 **)(s1 + 0x80);
    if (BtlScene_IsCharStopped(*(s32 *)s3) != 0) {
        return;
    }
    if (*(s32 *)(*(u8 **)(s3 + 0x20)) == 0xD2) {
        s0 = s1 + 0x84;
        func_00152960(*(s32 *)s3, s3);
        ft = func_00209D20(*(s32 *)(*(u8 **)(s1 + 0x80)));
        *(f32 *)(s1 + 4) = ft;
        func_001A12D8(ft, *(s32 *)(*(u8 **)(s1 + 0x80)));
        *(f32 *)(s1 + 0x10) = func_001A1348(*(s32 *)s3);
        func_001A1378(*(s32 *)s3, s1 + 0x30);
        func_00152530(s3, s1 + 0x830);
        func_00151FB0(s0);
        func_0015A468(0, *(s32 *)s3, arg0, s5);
        flag = func_00152200(s5, s0) != 0;
    } else {
        s4 = s1 + 0x50;
        if (*(s32 *)s1 & 8) {
            func_00129C28(s1 + 0x60, s4);
            v1 = *(u8 **)(*(u8 **)(s1 + 0x80) + 0x20);
            if (!(*(s32 *)(v1 + 0x30) & 2) && !(*(s32 *)s1 & 0x20)) {
                p70 = s1 + 0x70;
                if (0.0f < *(f32 *)(v1 + 0x18)) {
                    s0 = s1 + 0x20;
                    func_0012D5D8(*(f32 *)(s1 + 8), s0, s4, s0, *(s32 *)s3, *(f32 *)(v1 + 0x18));
                    func_00129BD0(p70, s0, *(f32 *)(s1 + 8));
                }
                Vec3_Add(s4, s4, p70);
            }
        }
        if (EftShot_TestBits(*(s32 *)s3, 4) != 0) {
            s0 = s1 + 0x20;
            func_001A1210(*(s32 *)s3);
            func_00208DE8(*(s32 *)s3, s1 + 0x60, 0x11);
            func_0012D488(s3, s0, s1 + 0x50, *(s32 *)s3);
            func_00129BD0(s1 + 0x70, s0, *(f32 *)(s1 + 8));
            *(s32 *)s1 |= 8;
        }
        s0 = s1 + 0x84;
        func_00152530(s3, s1 + 0x830);
        func_00151FB0(s0);
        func_0015A468(1, *(s32 *)s3, arg0, s5);
        flag = func_00152200(s5, s0) != 0;
    }

    if (EftShot_TestBits(*(s32 *)s3, 8) != 0) {
        *(s32 *)s1 |= 1;
    }
    if (EftShot_TestBits(*(s32 *)s3, 0x80) != 0) {
        *(s32 *)s1 |= 5;
    }
    a2 = *(s32 *)s1;
    if (flag == 0 && (a2 & 2)) {
        BtlTask_SetDead(arg0);
        return;
    }
    if (a2 & 1) {
        *(s32 *)s1 = a2 | 2;
        return;
    }
    if (*(s32 *)(*(u8 **)(s3 + 0x20)) == 0x85 && (a2 & 8)) {
        func_00152930(s5, s0, a2);
        func_0015A370(arg0);
    }
}
