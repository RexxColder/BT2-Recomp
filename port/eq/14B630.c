#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FL(p, o) (*(f32 *)((u8 *)(p) + (o)))

s32 func_0020B3D0(s32 arg0);
s32 func_00191728(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_0012D3A0(s32 arg0, s32 arg1, s32 arg2);
void func_0014B208(void *arg0);
void EftTechEvt_RequestRestart(s32 arg0);
void func_0012A360(void *arg0, void *arg1, void *arg2, f32 farg0);
void func_001917B0(s32 arg0, s32 arg1, void *arg2);
void func_0014B5A8(void *arg0);
void func_00191960(s32 arg0, s32 arg1);
void func_00147FB8(s32 arg0);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1);
void func_00191838(s32 arg0, void *arg1);
void func_00191A18(f32 farg0, s32 arg1);

s32 func_0014B630(void *arg0) {
    u8 sp[0x30];
    u8 *s3;
    u8 *s0;
    s32 *s4;
    s32 s2;
    s32 s5;
    s32 s6;
    s32 s7;
    s32 v0;
    s32 v1;
    s32 i;
    f32 f20;
    f32 f12;

    s3 = *(u8 **)((u8 *)arg0 + 0x38);
    s4 = *(s32 **)(s3 + 0xB0);
    s6 = 1;
    s7 = 0;
    s5 = func_0020B3D0(*s4);

    s0 = s3 + 0xAB0;
    for (s2 = 7; s2 >= 0; s2--, s0 += 0x40) {
        if (func_00191728(W(s0, 4)) == 0) {
            W(s0, 4) = 0;
        } else {
            s7 = 1;
        }
    }

    v1 = W(s3, 0);
    if (!(v1 & 0x200)) {
        if (!(v1 & 1) && EftShot_TestBits(*s4, 4) != 0) {
            W(s3, 0x10) = W(s3, 0x10) + 1;
            func_0012D3A0((s32)(s3 + 0x30), (s32)(s3 + 0x70), *s4);
            func_0014B208(arg0);
            EftTechEvt_RequestRestart(*s4);
        }

        s0 = s3;
        for (s2 = 7; s2 >= 0; s2--, s0 += 0x40) {
            if (W(s0, 0xAB4) != 0) {
                if (!(W(s0, 0xAB0) & 2)) {
                    func_0012A360(sp, s0 + 0xAD0, s3 + 0x70,
                                  FL(s0, 0xAE4) / FL(s0, 0xAE8));
                    func_001917B0(W(s0, 0xAB4), 1, sp);
                    FL(s0, 0xAE4) = FL(s0, 0xAE4) + 1.0f;
                    if (FL(s0, 0xAE8) < FL(s0, 0xAE4)) {
                        W(s0, 0xAB0) = W(s0, 0xAB0) | 2;
                    }
                } else {
                    func_0014B5A8(s0 + 0xAB0);
                }
            } else {
                v0 = W(s0, 0xAB0);
                if (v0 & 1) {
                    W(s0, 0xAB0) = v0 | 2;
                }
            }
        }

        v0 = W(s3, 0xAB0);
        s2 = 0;
        for (;;) {
            if (!(v0 & 2)) {
                s6 = 0;
                break;
            }
            s2++;
            if (s2 >= 8) {
                break;
            }
            v0 = W(s3 + (s2 << 6), 0xAB0);
        }

        if (s6 != 0) {
            s0 = s3 + 0xAB4;
            for (s2 = 7; s2 >= 0; s2--, s0 += 0x40) {
                v0 = W(s0, 0);
                if (v0 != 0) {
                    func_00191960(v0, 0);
                }
            }
            func_00147FB8(*s4);
            v0 = W(s3, 0) | 0x200;
            W(s3, 0) = v0;
        }
    } else {
        if (!(v1 & 0x800)) {
            s0 = s3 + 0xAB0;
            for (s2 = 7; s2 >= 0; s2--, s0 += 0x40) {
                if (W(s0, 4) != 0) {
                    func_0014B5A8(s0);
                }
            }
        }
        if (EftShot_TestBits(*s4, 0x40) != 0) {
            func_00208DE8(s5, sp + 0x20, 0x11);
            f20 = 0.0f;
            s0 = s3;
            for (s2 = 7; s2 >= 0; s2--, s0 += 0x40) {
                if (W(s0, 0xAB4) != 0) {
                    func_001917B0(W(s0, 0xAB4), 0, 0);
                    Vec3_Sub(sp + 0x10, sp + 0x20, s0 + 0xAC0);
                    Vec3_Normalize(sp + 0x10, sp + 0x10);
                    func_00191838(W(s0, 0xAB4), sp + 0x10);
                    f12 = f20;
                    f20 = f20 + 1.0f;
                    func_00191A18(f12, W(s0, 0xAB4));
                }
            }
            v0 = W(s3, 0) | 0x800;
            W(s3, 0) = v0;
        }
    }

    s0 = s3 + 0xAB0;
    for (s2 = 7; s2 >= 0; s2--, s0 += 0x40) {
        if (func_00191728(W(s0, 4)) == 0) {
            W(s0, 4) = 0;
        } else {
            s7 = 1;
        }
    }
    return s7;
}
