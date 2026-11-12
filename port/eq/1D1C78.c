#include "common.h"

extern u8 *D_00387E9C;
extern f32 D_003853FC;
extern f32 D_00385400;
extern f32 D_00385404;
extern f32 D_00385408;
extern f32 D_0038540C;
extern f32 D_00385410;
extern f32 D_00385414;
extern f32 D_00385418;
extern f32 D_0038541C;
extern f32 D_00385420;
extern f32 D_00385424;
extern f32 D_00385428;
extern f32 D_0038542C;
extern f32 D_00385430;
extern f32 D_00385434;
extern f32 D_00385438;
extern f32 D_0038543C;
extern f32 D_00385440;
extern f32 D_00385444;
extern f32 D_00385448;

s32 rand(void);
f32 EftMath_WrapAngle(f32 arg0);
f32 func_0012A3F8(f32 arg0);
f32 Mathf_Cos(f32 arg0);
void Vec4_Set(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void Vec3_Normalize(void *arg0, void *arg1);
void func_00129BB8(f32 farg0, void *arg0, void *arg1);
void func_00129B28(void *arg0, void *arg1, void *arg2);
void func_00129C28(void *arg0, void *arg1);
f32 BtlCharApi_GetHeight(s32 arg0);
void func_001D7778(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   f32 stk0, s32 pad0, f32 stk1, s32 pad1);
void func_001D4678(s32 arg0, void *arg1, void *arg2, void *arg3, void *arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   f32 stk0, s32 pad0, f32 stk1, s32 pad1, f32 stk2, s32 pad2, f32 stk3, s32 pad3);

#define SP_F32(o) (*(f32 *)(sp + (o)))

/* Sibling of func_001CFF30 (same two passes, other constants); its float parameter (f12) is kept at sp+0x70. */
s32 func_001D1C78(void *arg0, void *arg1, s32 arg2, f32 farg0) {
    s64 spbuf[0x120 / 8];
    u8 *sp = (u8 *)spbuf;
    u8 *s0;
    u8 *s3;
    u8 *s5;
    u8 *s6;
    s32 s2;
    s32 r;
    s32 m;
    f32 f0;
    f32 f1;
    f32 f12;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 f25;
    f32 f26;
    f32 f27;
    f32 f28;
    f32 f29;
    f32 f30;
    f32 f31;
    f32 h;
    f32 cosv;

    SP_F32(0x70) = farg0;
    if (*(u8 *)(D_00387E9C + 0x1491) == 0) {
        return 0;
    }

    /* block 1: four iterations */
    s2 = 0;
    r = rand();
    f0 = D_003853FC;
    f1 = (f32)r;
    f25 = 0.0f;
    f24 = f0;
    SP_F32(0x78) = D_00385404;
    f1 = f1 / f0;
    f27 = 2.0f;
    f26 = D_00385408;
    s6 = sp + 0x30;
    s0 = s6;
    s3 = sp + 0x40;
    SP_F32(0x74) = f1 * D_00385400;

    do {
        f12 = (f32)s2;
        s2 += 1;
        f12 = SP_F32(0x78) * f12;
        f12 = SP_F32(0x74) + f12;
        f29 = 3.0f;
        f21 = EftMath_WrapAngle(f12);
        f20 = func_0012A3F8(f21); /* f20 is this return: the delay slot of jal Mathf_Cos runs first */
        cosv = Mathf_Cos(f21);
        Vec4_Set(s0, f20, f25, cosv, 1.0f);
        Vec3_Normalize(s0, s0);
        func_00129BB8(f27, s3, s0);
        func_00129B28(sp + 0x20, arg0, s3);

        r = rand();
        f23 = (f32)r;
        r = rand();
        f23 = f23 / f24;
        f23 = f23 * f29;
        f23 = f23 + f27;
        f22 = (f32)r;
        r = rand();
        f22 = f22 / f24;
        f22 = f22 * 6.0f;
        f22 = f22 + 18.0f;
        f21 = (f32)r;
        r = rand();
        f21 = f21 / f24;
        f21 = f21 * 32.0f;
        f21 = f21 + 148.0f;
        f20 = (f32)r;
        f20 = f20 / f24;
        f20 = f20 * D_0038540C;
        f20 = f20 + D_00385410;
        h = BtlCharApi_GetHeight(arg2);
        f0 = h * f26;
        h = BtlCharApi_GetHeight(arg2);
        f23 = f23 * f0;
        f0 = h * f26;
        r = rand();
        f22 = f22 * f0;
        f12 = (f32)r;
        f12 = f12 / f24;
        f12 = f12 * D_00385414;
        f12 = f12 + D_00385418;
        func_001D7778(sp + 0x20, arg1, s0, 0x80, 0x80, 0x80, 8, 0, f12, f23, f22, -3.5f, f21, f20,
                      D_0038541C, D_00385420, f25, 0, farg0, 0);
    } while (s2 < 4);

    /* block 2: eight iterations */
    r = rand();
    f31 = f25;
    f0 = D_00385424;
    f1 = (f32)r;
    f30 = 128.0f;
    f28 = f0;
    SP_F32(0x78) = D_0038542C;
    s2 = 0;
    f1 = f1 / f0;
    f27 = D_00385430;
    s5 = sp + 0x50;
    s3 = sp + 0x60;
    s0 = s6;
    SP_F32(0x74) = f1 * D_00385428;

    do {
        Vec4_Set(s5, f30, f30, 168.0f, f31);
        r = rand();
        m = (r < 0 ? r + 15 : r) >> 4 << 4;
        m = r - m;
        Vec4_Set(s3, f30, f30, f30, (f32)(168 - m));
        func_00129C28(sp + 0x20, arg0);
        SP_F32(0x24) = SP_F32(0x24) - 6.0f;
        r = rand();
        f26 = ((f32)r / f28) * 3.0f + 4.5f;
        r = rand();
        f25 = ((f32)r / f28) * 3.0f + 4.0f;
        r = rand();
        f24 = ((f32)r / f28) * 3.0f + 4.0f;
        r = rand();
        f23 = ((f32)r / f28) * 7.0f + 23.0f;
        r = rand();
        f22 = ((f32)r / f28) * D_00385434 + D_00385438;
        r = rand();
        f29 = ((f32)r / f28) * D_0038543C + D_00385440;
        h = BtlCharApi_GetHeight(arg2);
        f0 = h * f27;
        f26 = f26 * f0;
        h = BtlCharApi_GetHeight(arg2);
        f0 = h * f27;
        f25 = f25 * f0;
        h = BtlCharApi_GetHeight(arg2);
        f0 = h * f27;
        f24 = f24 * f0;
        h = BtlCharApi_GetHeight(arg2);
        f0 = h * f27;
        f23 = f23 * f0;
        h = BtlCharApi_GetHeight(arg2);
        f0 = h * f27;
        f22 = f22 * f0;

        f12 = (f32)s2 * SP_F32(0x78);
        f12 = SP_F32(0x74) + f12;
        f21 = EftMath_WrapAngle(f12);
        f20 = func_0012A3F8(f21);
        cosv = Mathf_Cos(f21);
        Vec4_Set(s0, f20, f31, cosv, 1.0f);
        Vec3_Normalize(s0, s0);

        r = rand();
        {
            f32 f18 = ((r & 1) != 0) ? D_00385444 : D_00385448;
            f32 f19 = -f22;
            func_001D4678(0, sp + 0x20, s6, s5, s3, 0, 0xB, 0, f26, -4.5f, f25, f24, f23, f31, f18, f19,
                          f31, 0, f29, 0, f27, 0, farg0, 0);
        }
        s2 += 1;
    } while (s2 < 8);

    return 1;
}
