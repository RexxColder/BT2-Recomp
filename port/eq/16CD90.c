#include "common.h"

void Mtx_InverseRT(s32 arg0, s32 arg1);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129C28(s32 arg0, s32 arg1);
void func_0016CA38(s32 arg0);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
s32 func_0020B3D0(s32 arg0);
extern s32 gBtlCamView;

void func_0016CD90(void *arg0) {
    u8 *s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 sp[16];
    f32 v40[4];
    f32 v50[4];
    f32 v60[4];

    s0 = *(u8 **)((u8 *)arg0 + 0x38);
    s1 = *(s32 *)(s0 + 0xB0);
    s3 = (s32)(s0 + 0x80);
    s2 = func_0020B3D0(*(s32 *)s1);
    func_0016CA38(s2);
    func_0016CA38(*(s32 *)s1);
    Mtx_InverseRT((s32)sp, gBtlCamView);
    if (*(s32 *)(s0 + 0x10) == 0) {
        func_00208DE8(*(s32 *)s1, (s32)(s0 + 0x50), *(s32 *)(s0 + 8));
        func_00129C28((s32)(s0 + 0x90), s3);
        Vec3_Add(s3, s3, (s32)(s0 + 0xA0));
        func_00208DE8(s2, (s32)v50, 0x11);
        func_00208DE8(*(s32 *)s1, (s32)v60, 0x11);
        Vec3_Sub((s32)v40, (s32)v60, (s32)v50);
        Vec3_Normalize((s32)v40, (s32)v40);
        func_00129BD0((s32)v40, (s32)v40, 0.0f);
        Vec3_Add((s32)v50, (s32)v50, (s32)v40);
        func_00129C28(s3, (s32)v50);
    }
}
