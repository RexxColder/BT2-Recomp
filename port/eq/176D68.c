#include "common.h"

extern s32 D_00387E94;
extern s64 D_0036E830[2] __attribute__((section(".data")));
extern f32 D_0038492C;
extern f32 D_00384930;
extern f32 D_00384934;
extern f32 D_00384938;
extern f32 D_0038493C;
extern f32 D_00384940;
extern f32 D_00384944;
extern f32 D_00384948;
extern f32 D_0038494C;
extern f32 D_00384950;
extern f32 D_00384954;

f32 func_00209110(s32 arg0, s32 arg1);
f32 BtlCharApi_GetHeight(s32 arg0);
void func_00129BB8(void *arg0, void *arg1, f32 farg0);
void Vec3_Normalize(void *arg0, void *arg1);
void Vec3_Cross(void *arg0, void *arg1, void *arg2);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
f32 Mathf_Cos(f32 farg0);
void func_00129B28(void *arg0, void *arg1, void *arg2);
f32 func_0012A3F8(f32 farg0);
void func_00129B58(void *arg0, void *arg1, void *arg2);
s32 rand(void);
void func_001779E0(s32 arg0, void *arg1, void *arg2, void *arg3, f32 farg0, f32 farg1, f32 farg2);

s32 func_00176D68(s32 arg0, void *arg1, s32 arg2) {
    u8 sp[0x70];
    u8 *s0;
    u8 *s4;
    s32 s3;
    s32 r;
    f32 h;
    f32 f0;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 f25;
    f32 f13;

    *(s64 *)(sp + 0x40) = D_0036E830[0];
    *(s64 *)(sp + 0x48) = D_0036E830[1];
    if (D_00387E94 == 0) {
        return 0;
    }

    f20 = D_0038492C;
    f23 = func_00209110(arg0, arg2) * D_00384930;
    if (f23 < f20) {
        f23 = BtlCharApi_GetHeight(arg0) * D_00384934 * f20;
    }
    s0 = sp + 0x20;
    func_00129BB8(s0, arg1, -1.0f);
    f24 = D_00384938;
    Vec3_Normalize(s0, s0);
    Vec3_Cross(sp + 0x60, s0, sp + 0x40);
    Vec3_Normalize(sp + 0x60, sp + 0x60);
    s4 = s0;
    Vec3_Cross(sp + 0x50, s0, sp + 0x60);
    Vec3_Normalize(sp + 0x50, sp + 0x50);
    f25 = 3.0f;

    s3 = 14;
    do {
        s3 -= 1;
        func_00208DE8(arg0, sp, arg2);

        r = rand();
        f22 = ((f32)r / f24) * D_0038493C;
        r = rand();
        f20 = ((f32)r / f24) * D_00384940;
        f20 = f20 + D_00384944;
        r = rand();
        f20 = f20 * f23;
        f21 = (f32)r / f24;
        f21 = f21 + f21;
        f0 = Mathf_Cos(f22);
        f21 = f21 + 1.5f;
        func_00129BB8(sp + 0x30, sp + 0x60, f0 * f20);
        f21 = f21 * f23;
        func_00129B28(sp, sp, sp + 0x30);

        f0 = func_0012A3F8(f22);
        func_00129BB8(sp + 0x30, sp + 0x50, f0 * f20);
        func_00129B28(sp, sp, sp + 0x30);

        func_00129BB8(sp + 0x30, s4, f21);
        func_00129B58(sp, sp, sp + 0x30);

        r = rand();
        f0 = ((((f32)r / f24) * f25) + f25) * f23;
        func_00129BB8(sp + 0x30, s4, f0);
        func_00129B28(sp + 0x10, sp, sp + 0x30);

        r = rand();
        f20 = (f32)r;
        h = BtlCharApi_GetHeight(arg0);
        f0 = h * D_00384948;
        f20 = f20 / f24;
        f20 = f20 + f20;
        f20 = f20 + 1.0f;
        r = rand();
        f20 = f20 * f0;

        f13 = (((f32)r / f24) * D_0038494C) + D_00384950;
        func_001779E0(arg0, sp, sp + 0x10, s4, f20, f13, D_00384954);
    } while (s3 >= 0);

    return 1;
}
