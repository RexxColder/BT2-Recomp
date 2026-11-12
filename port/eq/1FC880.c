#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FLDF(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define FLDU16(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define CVT_W_S(x) ((s32)(x))

extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_00385858;

void func_00210868(void *arg0, void *arg1);
f32 func_00210D50(void *arg0);
void *BtlChar_GetPos(void *arg0);
f32 BtlCharApi_GetHeight(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
void func_00210F30(void *arg0, void *arg1, s32 arg2);
void func_00312650(void *arg0, void *arg1, void *arg2);
void func_003126C8(void *arg0, void *arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_001FC3B0(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5,
                   void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12);

void func_001FC880(void *arg0, s32 arg1) {
    u8 spb[0x110];
    u8 *sp = spb;
    u8 *P = (u8 *)arg0;
    u8 *Y;
    s32 OFF;
    u16 s3;
    s32 fp;
    s32 sp90;
    s32 s7;
    s32 s3w;
    s32 v1;
    s32 t4;
    f32 f22;
    f32 f23;
    f32 f12;
    f32 f13;
    f32 f14;
    f32 f15;
    f32 f16;
    f32 f17;
    f32 ftmp;

    OFF = arg1 * 0x24;
    Y = (u8 *)FLD(FLD(P, 0x1530), 0x988);
    s3 = FLDU16(Y + OFF, 0x22);

    if (s3 & 2) {
        func_00210868(P, sp + 0x70);
        f23 = FLDF(sp, 0x74);
        f22 = func_00210D50(P);
        if (s3 & 1) {
            func_003126C8(sp + 0x30, D_002C3630);
            func_003126C8(sp + 0x40, D_002C3630);
            fp = Y[OFF] | 0x40000000;
            sp90 = Y[OFF + 1] | 0x40000000;
        } else {
            sp90 = -1;
            func_00210F30(P, sp + 0x30, Y[OFF]);
            func_00210F30(P, sp + 0x80, Y[OFF + 1]);
            func_00312650(sp + 0x40, sp + 0x80, sp + 0x30);
            fp = -1;
        }
    } else {
        f23 = FLDF(BtlChar_GetPos(P), 0xB4);
        f22 = BtlCharApi_GetHeight(FLD(P, 0x1534));
        if (s3 & 1) {
            func_003126C8(sp + 0x30, D_002C3630);
            func_003126C8(sp + 0x40, D_002C3630);
            fp = Y[OFF];
            sp90 = Y[OFF + 1];
        } else {
            sp90 = -1;
            func_00208DE8(FLD(P, 0x1534), sp + 0x30, Y[OFF]);
            func_00208DE8(FLD(P, 0x1534), sp + 0x80, Y[OFF + 1]);
            fp = -1;
            func_00312650(sp + 0x40, sp + 0x80, sp + 0x30);
        }
    }

    if (s3 & 8) {
        if (s3 & 4) {
            func_003126C8(sp + 0x50, D_002C3630);
            s7 = Y[OFF + 2] | 0x40000000;
        } else {
            func_00210F30(P, sp + 0x50, Y[OFF + 2]);
            s7 = -1;
        }
    } else {
        if (s3 & 4) {
            func_003126C8(sp + 0x50, D_002C3630);
            s7 = Y[OFF + 2];
        } else {
            func_00208DE8(FLD(P, 0x1534), sp + 0x50, Y[OFF + 2]);
            s7 = -1;
        }
    }

    if (s3 & 0x20) {
        if (s3 & 0x10) {
            func_003126C8(sp + 0x60, D_002C3630);
            s3w = Y[OFF + 3] | 0x40000000;
        } else {
            func_00210F30(P, sp + 0x80, Y[OFF + 3]);
            s3w = -1;
            func_00312650(sp + 0x60, sp + 0x80, sp + 0x50);
        }
    } else {
        if (s3 & 0x10) {
            func_003126C8(sp + 0x60, D_002C3630);
            s3w = Y[OFF + 3];
        } else {
            func_00208DE8(FLD(P, 0x1534), sp + 0x80, Y[OFF + 3]);
            s3w = -1;
            func_00312650(sp + 0x60, sp + 0x80, sp + 0x50);
        }
    }

    /* angle, scaled vectors and the call */
    f12 = BtlUtil_WrapAngle(f23 + (FLDF(Y, 4 + OFF) / 180.0f) * D_00385858);
    f13 = (FLDF(Y, 8 + OFF) / 180.0f) * D_00385858;
    f14 = (FLDF(Y, 0xC + OFF) / 180.0f) * D_00385858;
    f15 = (FLDF(Y, 0x10 + OFF) / 180.0f) * D_00385858;
    f16 = FLDF(Y, 0x14 + OFF) * f22;
    f17 = FLDF(Y, 0x18 + OFF) * f22;
    ftmp = FLDF(Y, 0x1C + OFF) * 30.0f;
    v1 = CVT_W_S(ftmp);
    if (!(0 < v1)) {
        v1 = 1;
    }
    t4 = FLDU16(Y, OFF + 0x20);
    func_001FC3B0(f12, f13, f14, f15, f16, f17, P, sp + 0x30, sp + 0x40,
                  (s32)D_002C3630, (s32)D_002C3630, (s32)(sp + 0x50), (s32)(sp + 0x60), fp,
                  sp90, s7, s3w, v1, t4);
    return;
}
