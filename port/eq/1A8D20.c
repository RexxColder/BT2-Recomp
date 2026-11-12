#include "common.h"

extern u8 *gEftStruggle;
extern f32 D_00384EC8;
extern f32 D_00384ECC;
extern f32 D_00384ED0;
extern s64 D_0036EAA0[] __attribute__((section(".data")));

s32 BtlScene_IsTimeStopped(void);
void func_00129C28(void *arg0, void *arg1);
void func_0018E1A8(s32 arg0, void *arg1);
void EftPtcl3_SetPos(s32 arg0, void *arg1);
s32 func_001A83D8(void *arg0);
s32 func_001E70B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0);
void func_00129B58(void *arg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1);
s32 rand(void);
s32 func_001E72F8(void *arg0, void *arg1);
void func_001E72C8(void *arg0, void *arg1);
void func_001E7208(void *arg0, s32 arg1);
void EftChain2_SetPos(s32 arg0, void *arg1);
void func_001CCAC8(s32 arg0, void *arg1);
void func_001CCB20(s32 arg0, void *arg1);
s32 func_001E7178(void *arg0);

void func_001A8D20(u8 *arg0) {
    u8 fr[0x50];
    u8 *s3;
    u8 *s4;
    u8 *s6;
    u8 *s0;
    u8 *s2;
    u8 *p1;
    u8 *a0p;
    s32 cnt;
    s32 r;
    s32 v;
    f32 f0;
    f32 f1;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;

    s4 = gEftStruggle + 8;
    s3 = *(u8 **)(arg0 + 0x38);
    s6 = *(u8 **)s4;
    if (BtlScene_IsTimeStopped() != 0) {
        return;
    }

    v = *(s32 *)(s3 + 0x2C);
    s4 = gEftStruggle + 8 + 8 + (u32)v * 1568;
    s0 = s3 + 0x360;
    func_00129C28(fr, s3);
    func_0018E1A8(*(s32 *)s0, fr);

    s2 = s3 + 0x364;
    cnt = 3;
    do {
        func_00129C28(fr, s3);
        EftPtcl3_SetPos(*(s32 *)s2, fr);
        cnt -= 1;
        s2 += 4;
    } while (cnt >= 0);

    if (*(s32 *)(s3 + 0x24) % 6 != 0) {
        goto l8f74;
    }

    f23 = D_00384EC8;
    r = func_001A83D8(arg0);
    f20 = *(f32 *)s6;
    f0 = *(f32 *)(s3 + 0x30);
    p1 = s3 + ((u32)r << 2) + 0x374;
    f20 = f20 * f0;
    f21 = D_00384ECC;
    f22 = D_00384ED0;
    f20 = f20 * 3.0f;
    func_00129C28(fr + 0x10, s3);
    func_001E70B0((s32)p1, *(s32 *)(s4 + 0x3D8), 0, 0, 5, (s32)(fr + 0x10), (s32)(s4 + 0x1C8), 0, f20);
    func_00129B58(fr + 0x20, s3 + 0x70, s3 + 0x80);
    Vec3_Normalize(fr + 0x20, fr + 0x20);

    r = rand();
    f0 = (((f32)r / f23) * f21) - f22;
    f1 = *(f32 *)(fr + 0x20) + f0;
    *(f32 *)(fr + 0x30) = f1;

    r = rand();
    f0 = (((f32)r / f23) * f21) - f22;
    f1 = *(f32 *)(fr + 0x24) + f0;
    *(f32 *)(fr + 0x34) = f1;

    r = rand();
    f0 = (((f32)r / f23) * f21) - f22;
    f1 = *(f32 *)(fr + 0x28) + f0;
    *(f32 *)(fr + 0x38) = f1;
    *(f32 *)(fr + 0x3C) = 1.0f;
    Vec3_Normalize(fr + 0x30, fr + 0x30);

    func_001E72F8(p1, fr + 0x30);
    *(s64 *)(fr + 0x40) = D_0036EAA0[0];
    *(s64 *)(fr + 0x48) = D_0036EAA0[1];
    func_001E72C8(p1, fr + 0x40);
    func_001E7208(p1, 2);

l8f74:
    func_00129C28(fr, s3);
    EftChain2_SetPos(*(s32 *)(s3 + 0x384), fr);
    s0 = s3 + 0x374;
    func_001CCAC8(*(s32 *)(s3 + 0x388), s3);
    cnt = 3;
    func_001CCB20(*(s32 *)(s3 + 0x388), s3 + 0x10);
    a0p = s0;
    do {
        s0 += 4;
        func_001E7178(a0p);
        cnt -= 1;
        a0p = s0;
    } while (cnt >= 0);
}
