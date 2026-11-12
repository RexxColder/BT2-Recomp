#include "common.h"

extern void *gEftStruggle;
extern f32 D_00384EBC;
extern f32 D_00384EC0;
extern f32 D_00384EC4;

s32 BtlScene_IsTimeStopped(s32 arg0);
void EftChain2_SetPos(s32 arg0, s32 arg1);
void EftPtcl3_SetPos(s32 arg0, s32 arg1);
void Vec3_Normalize(s32 arg0, s32 arg1);
void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
void func_0018E1A8(s32 arg0, s32 arg1);
s32 func_001A83D8(s32 arg0);
void func_001CCAC8(s32 arg0, s32 arg1);
void func_001CCB20(s32 arg0, s32 arg1);
void func_001E70B0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_001E7178(s32 arg0);
void func_001E7208(s32 arg0, s32 arg1);
void func_001E72F8(s32 arg0, s32 arg1);
s32 rand(void);

void func_001A8A78(u8 *arg0) {
    u8 sp[0x40];
    u8 *s2;
    u8 *s3;
    u8 *s4;
    f32 *s6;
    u8 *ptr;
    u8 *a;
    s32 n;
    s32 k;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 t;

    s4 = (u8 *)gEftStruggle + 8;
    s2 = (u8 *)*(s32 *)(arg0 + 0x38);
    s6 = (f32 *)*(s32 *)s4;
    if (BtlScene_IsTimeStopped((s32)arg0) != 0) {
        return;
    }

    s3 = s2 + 0x364;
    s4 = s4 + *(s32 *)(s2 + 0x2C) * 0x620 + 8;
    func_00129C28((s32)sp, (s32)s2);
    func_0018E1A8(*(s32 *)(s2 + 0x360), (s32)sp);
    n = 3;
    do {
        func_00129C28((s32)sp, (s32)s2);
        n -= 1;
        EftPtcl3_SetPos(*(s32 *)s3, (s32)sp);
        s3 += 4;
    } while (n >= 0);

    if (*(s32 *)(s2 + 0x24) % 10 == 0) {
        f22 = D_00384EBC;
        k = func_001A83D8((s32)arg0);
        f20 = *s6 * *(f32 *)(s2 + 0x30);
        ptr = s2 + (k << 2);
        func_00129C28((s32)(sp + 0x10), (s32)s2);
        ptr += 0x374;
        func_001E70B0(f20, (s32)ptr, *(s32 *)(s4 + 0x3D8), 0, 0, 4, (s32)(sp + 0x10),
                      (s32)(s4 + 0x1C8), 0);
        f20 = D_00384EC0;
        f21 = D_00384EC4;
        func_00129B58((s32)(sp + 0x20), (s32)(s2 + 0x70), (s32)(s2 + 0x80));
        Vec3_Normalize((s32)(sp + 0x20), (s32)(sp + 0x20));
        t = (f32)rand();
        *(f32 *)(sp + 0x30) = *(f32 *)(sp + 0x20) + (((t / f22) * f21) - f20);
        t = (f32)rand();
        *(f32 *)(sp + 0x34) = *(f32 *)(sp + 0x24) + (((t / f22) * f21) - f20);
        t = (f32)rand();
        *(f32 *)(sp + 0x3C) = 1.0f;
        *(f32 *)(sp + 0x38) = *(f32 *)(sp + 0x28) + (((t / f22) * f21) - f20);
        Vec3_Normalize((s32)(sp + 0x30), (s32)(sp + 0x30));
        func_001E72F8((s32)ptr, (s32)(sp + 0x30));
        func_001E7208((s32)ptr, 2);
    }

    func_00129C28((s32)sp, (s32)s2);
    EftChain2_SetPos(*(s32 *)(s2 + 0x384), (s32)sp);
    ptr = s2 + 0x374;
    func_001CCAC8(*(s32 *)(s2 + 0x388), (s32)s2);
    func_001CCB20(*(s32 *)(s2 + 0x388), (s32)(s2 + 0x10));
    a = ptr;
    n = 3;
    do {
        ptr += 4;
        n -= 1;
        func_001E7178((s32)a);
        a = ptr;
    } while (n >= 0);
}
