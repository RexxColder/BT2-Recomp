#include "common.h"

f32 func_00209110(s32, void *);
f32 BtlCharApi_GetHeight(s32);
f32 Mathf_Cos(f32);
f32 func_0012A3F8(f32);
void Vec3_Normalize(void *, void *);
void Vec3_Cross(void *, void *, void *);
void func_00129BB8(f32, void *, void *);
void func_00129B28(void *, void *, void *);
void func_00129B58(void *, void *, void *);
void func_00208DE8(s32, void *, void *);
void func_001779E0(f32, f32, f32, s32, void *, void *, void *);
s32 rand(void);
extern u8 D_0036E840[] __attribute__((section(".data")));
extern f32 D_00384958;
extern f32 D_0038495C;
extern f32 D_00384960;
extern f32 D_00384964;
extern f32 D_00384968;
extern f32 D_0038496C;
extern f32 D_00384970;
extern f32 D_00384974;
extern f32 D_00384978;
extern s32 D_00387E94;

/* f13 (farg0) and f14 (farg1) are the function's own float parameters: the asm keeps them to the end */
s32 func_001770B8(s32 arg0, void *arg1, void *arg2, s32 arg3, f32 farg0, f32 farg1) {
    u8 sp[0x70];
    u8 *s0;
    u8 *s1;
    u8 *s4;
    u8 *fp;
    u8 *s5;
    u8 *s6;
    s32 s3;
    s32 v0;
    s32 r;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 f13v;
    f32 h;

    s3 = arg3;
    v0 = 0;
    if (D_00387E94 == 0) {
        return v0;
    }
    f20 = D_00384958;
    s0 = sp + 0x20;
    f23 = func_00209110(arg0, arg2) * D_0038495C;
    if (f23 < f20) {
        h = BtlCharApi_GetHeight(arg0);
        f23 = h * D_00384960 * f20;
    }

    func_00129BB8(-1.0f, s0, arg1);
    Vec3_Normalize(s0, s0);
    s5 = sp + 0x60;
    Vec3_Cross(s5, s0, sp + 0x40);
    Vec3_Normalize(s5, s5);
    s6 = sp + 0x50;
    Vec3_Cross(s6, s0, s5);
    Vec3_Normalize(s6, s6);

    v0 = 1;
    if (s3 <= 0) {
        return v0;
    }
    f24 = D_00384964;
    s4 = s0;
    s1 = sp + 0x30;
    fp = sp + 0x10;
    do {
        func_00208DE8(arg0, sp, arg2);
        s3 -= 1;
        f22 = ((f32)rand() / f24) * D_00384968;
        f20 = ((f32)rand() / f24) * D_0038496C + D_00384970;
        f20 = f20 * f23;
        f21 = (f32)rand() / f24;
        f21 = (f21 + f21) + 1.5f;
        func_00129BB8(Mathf_Cos(f22) * f20, s1, s5);
        func_00129B28(sp, sp, s1);
        f21 = f21 * f23;
        func_00129BB8(func_0012A3F8(f22) * f20, s1, s6);
        func_00129B28(sp, sp, s1);
        func_00129BB8(f21, s1, s4);
        func_00129B58(sp, sp, s1);
        func_00129BB8((((f32)rand() / f24) * 3.0f + 2.0f) * f23, s1, s4);
        func_00129B28(fp, sp, s1);
        r = rand();
        f20 = (f32)r;
        h = BtlCharApi_GetHeight(arg0);
        f20 = f20 / f24;
        f20 = (f20 + f20) + 0.5f;
        r = rand();
        f20 = f20 * (h * D_00384974);
        f13v = ((f32)r / f24) * farg1 + farg0;
        func_001779E0(f20, f13v, D_00384978, arg0, sp, fp, s4);
    } while (s3 != 0);
    return 1;
}
