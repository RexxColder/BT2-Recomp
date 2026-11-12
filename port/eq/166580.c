#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FL(p, o) (*(f32 *)((u8 *)(p) + (o)))

s32 func_0020B3D0(s32 arg0);
s32 func_00191728(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_0012D488(void *arg0, void *arg1, void *arg2, s32 arg3);
void func_001660F0(void *arg0);
void EftTechEvt_RequestRestart(s32 arg0);
void func_0012A360(void *arg0, void *arg1, void *arg2, f32 farg0);
void func_001917B0(s32 arg0, s32 arg1, void *arg2);
void func_001664F8(void *arg0);
void func_00191960(s32 arg0, s32 arg1);
void func_00147FB8(s32 arg0);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1);
void func_00191838(s32 arg0, void *arg1);
void func_00191A18(s32 arg0, f32 farg0);

s32 func_00166580(u8 *arg0) {
    u8 sp[0x30];
    u8 *s3;
    u8 *s4;
    u8 *s0;
    s32 s2;
    s32 s5;
    s32 s6;
    s32 s7;
    s32 v0;
    s32 v1;
    f32 f0;
    f32 f20;
    f32 f21;

    s2 = 9;
    s6 = 1;
    s7 = 0;
    s3 = *(u8 **)(arg0 + 0x38);
    s4 = *(u8 **)(s3 + 0xB0);
    s0 = s3 + 0xAB0;
    s5 = func_0020B3D0(W(s4, 0));

    do {
        if (func_00191728(W(s0, 4)) == 0) {
            W(s0, 4) = 0;
        } else {
            s7 = 1;
        }
        s2 -= 1;
        s0 += 0x40;
    } while (s2 >= 0);

    v1 = W(s3, 0);
    if (!(v1 & 0x200)) {
        if (!(v1 & 1) && EftShot_TestBits(W(s4, 0), 4) != 0) {
            W(s3, 0x10) = W(s3, 0x10) + 1;
            func_0012D488(s4, s3 + 0x30, s3 + 0x70, W(s4, 0));
            func_001660F0(arg0);
            EftTechEvt_RequestRestart(W(s4, 0));
        }

        f20 = 1.0f;
        s0 = s3;
        s2 = 9;
        do {
            if (W(s0, 0xAB4) != 0) {
                if (!(W(s0, 0xAB0) & 2)) {
                    func_0012A360(sp, s0 + 0xAD0, s3 + 0x70, FL(s0, 0xAE4) / FL(s0, 0xAE8));
                    func_001917B0(W(s0, 0xAB4), 1, sp);
                    f0 = FL(s0, 0xAE4) + f20;
                    FL(s0, 0xAE4) = f0;
                    if (FL(s0, 0xAE8) < f0) {
                        W(s0, 0xAB0) = W(s0, 0xAB0) | 2;
                    }
                } else {
                    func_001664F8(s0 + 0xAB0);
                }
            } else {
                v0 = W(s0, 0xAB0);
                if (v0 & 1) {
                    W(s0, 0xAB0) = v0 | 2;
                }
            }
            s2 -= 1;
            s0 += 0x40;
        } while (s2 >= 0);

        v0 = W(s3, 0xAB0);
        s2 = 0;
        for (;;) {
            s2 += 1;
            if (!(v0 & 2)) {
                s6 = 0;
                break;
            }
            if (s2 >= 10) {
                break;
            }
            v0 = W(s3 + (s2 << 6), 0xAB0);
        }

        if (s6 != 0) {
            s0 = s3 + 0xAB4;
            s2 = 9;
            do {
                v0 = W(s0, 0);
                s0 += 0x40;
                if (v0 != 0) {
                    func_00191960(v0, 0);
                }
                s2 -= 1;
            } while (s2 >= 0);
            func_00147FB8(W(s4, 0));
            v0 = W(s3, 0) | 0x200;
            W(s3, 0) = v0;
        }
    } else {
        if (!(v1 & 0x800)) {
            s0 = s3 + 0xAB0;
            s2 = 9;
            do {
                if (W(s0, 4) != 0) {
                    func_001664F8(s0);
                }
                s2 -= 1;
                s0 += 0x40;
            } while (s2 >= 0);
        }
        if (EftShot_TestBits(W(s4, 0), 0x40) != 0) {
            func_00208DE8(s5, sp + 0x20, 0x11);
            f20 = 0.0f;
            f21 = 1.0f;
            s0 = s3;
            s2 = 9;
            do {
                v0 = W(s0, 0xAB4);
                if (v0 != 0) {
                    func_001917B0(v0, 0, NULL);
                    Vec3_Sub(sp + 0x10, sp + 0x20, s0 + 0xAC0);
                    Vec3_Normalize(sp + 0x10, sp + 0x10);
                    func_00191838(W(s0, 0xAB4), sp + 0x10);
                    func_00191A18(W(s0, 0xAB4), f20);
                    f20 = f20 + f21;
                }
                s2 -= 1;
                s0 += 0x40;
            } while (s2 >= 0);
            W(s3, 0) = W(s3, 0) | 0x800;
        }
    }

    s0 = s3 + 0xAB0;
    s2 = 9;
    do {
        if (func_00191728(W(s0, 4)) == 0) {
            W(s0, 4) = 0;
        } else {
            s7 = 1;
        }
        s2 -= 1;
        s0 += 0x40;
    } while (s2 >= 0);
    return s7;
}
