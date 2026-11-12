#include "common.h"

void Mtx_StoreIdentity(u8 *arg0);
void Vec3_Cross(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
void Vec3_Set(u8 *arg0, f32 farg0, f32 farg1, f32 farg2);
void func_00129B28(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00129B58(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00129BB8(f32 farg0, u8 *arg1, u8 *arg2);
f32 func_00129CD8(u8 *arg0, u8 *arg1);
extern f32 D_00384D44;
extern f32 D_00384D48;
extern u8 *gBtlCamView;

void func_001993D0(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 sp[0x50];
    u8 *s1;
    u8 *cam;
    f32 temp;
    f32 f20;

    cam = gBtlCamView;
    *(f32 *)(sp + 0x30) = *(f32 *)(cam + 0x8);
    *(f32 *)(sp + 0x34) = *(f32 *)(cam + 0x18);
    *(f32 *)(sp + 0x3C) = 1.0f;
    *(f32 *)(sp + 0x38) = *(f32 *)(cam + 0x28);
    temp = func_00129CD8(sp + 0x30, arg1);
    s1 = sp + 0x40;
    if (temp < 0.0f) {
        f20 = -temp * D_00384D44;
        Vec3_Set(s1, -*(f32 *)(sp + 0x30), -*(f32 *)(sp + 0x34), -*(f32 *)(sp + 0x38));
    } else {
        f20 = temp * D_00384D48;
        Vec3_Set(s1, *(f32 *)(sp + 0x30), *(f32 *)(sp + 0x34), *(f32 *)(sp + 0x38));
    }
    func_00129B58(s1, arg1, s1);
    Vec3_Normalize(s1, s1);
    func_00129BB8(f20, s1, s1);
    func_00129B28(sp + 0x20, arg1, s1);
    Vec3_Normalize(sp + 0x20, sp + 0x20);
    Vec3_Cross(sp, sp + 0x30, sp + 0x20);
    Vec3_Normalize(sp, sp);
    Vec3_Cross(sp + 0x10, sp + 0x20, sp);
    Vec3_Normalize(sp + 0x10, sp + 0x10);
    Mtx_StoreIdentity(arg0);
    *(f32 *)(arg0 + 0x0) = *(f32 *)(sp + 0x0);
    *(f32 *)(arg0 + 0x10) = *(f32 *)(sp + 0x10);
    *(f32 *)(arg0 + 0x20) = *(f32 *)(sp + 0x20);
    *(f32 *)(arg0 + 0x4) = *(f32 *)(sp + 0x4);
    *(f32 *)(arg0 + 0x14) = *(f32 *)(sp + 0x14);
    *(f32 *)(arg0 + 0x24) = *(f32 *)(sp + 0x24);
    *(f32 *)(arg0 + 0x8) = *(f32 *)(sp + 0x8);
    *(f32 *)(arg0 + 0x18) = *(f32 *)(sp + 0x18);
    *(f32 *)(arg0 + 0x28) = *(f32 *)(sp + 0x28);
    *(f32 *)(arg0 + 0x30) = *(f32 *)(arg2 + 0x0);
    *(f32 *)(arg0 + 0x34) = *(f32 *)(arg2 + 0x4);
    *(f32 *)(arg0 + 0x38) = *(f32 *)(arg2 + 0x8);
}
