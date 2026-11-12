#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FLDF(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern f32 D_00384D14;
extern f32 D_00384D18;
extern f32 D_00384D1C;
extern f32 D_00384D20;
extern f32 D_00384D24;
extern f32 D_00384D28;
extern f32 D_00384D2C;
extern u8 *gEftGlowCfg;

s32 rand(void);
void Vec3_Set(f32 farg0, f32 farg1, f32 farg2, void *arg0);
void Vec3_Normalize(void *arg0, void *arg1);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
s32 EftGlow_SpawnPart(f32 farg0, void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4);
void EftGlow_PairPart(void *arg0, s32 arg1, s32 arg2);

void EftGlow_SpawnNext(void *arg0, s32 arg1) {
    u8 spb[0x20];
    u8 *sp = spb;
    u8 *E = (u8 *)arg0;
    s32 v1t;
    s32 s0t;
    s32 e14;
    s32 e18;
    s32 a0v;
    s32 bit;
    s32 varv0;
    s32 varv1;
    s32 a3v;
    s32 s2;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 s0;
    s32 v1;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f5;
    f32 f20;
    f32 f21;

    v1t = FLD(E, 0x14);
    s0t = FLD(E, 0x18);
    if (v1t == 3) {
        f1 = (f32)s0t;
        f0 = (f32)rand();
        f3 = D_00384D14;
        f5 = -25.0f;
        f2 = -40.0f;
        f21 = ((f1 * f5) + f2) + ((f0 / f3) * f5);
        if (f21 <= -180.0f) {
            f21 += 360.0f;
        }
    } else if (v1t == 4) {
        f1 = (f32)s0t;
        f0 = (f32)rand();
        f3 = D_00384D18;
        f5 = 25.0f;
        f2 = 40.0f;
        f21 = ((f1 * f5) + f2) + ((f0 / f3) * f5);
        if (f21 >= 180.0f) {
            f21 -= 360.0f;
        }
    } else if (v1t == 6 || v1t == 8) {
        f1 = (f32)s0t;
        f0 = (f32)rand();
        f3 = D_00384D1C;
        f5 = -35.0f;
        f2 = -20.0f;
        f21 = ((f1 * f5) + f2) + ((f0 / f3) * f5);
        if (f21 <= -180.0f) {
            f21 += 360.0f;
        }
    } else if (v1t == 7 || v1t == 9) {
        f1 = (f32)s0t;
        f0 = (f32)rand();
        f3 = D_00384D20;
        f5 = 35.0f;
        f2 = 20.0f;
        f21 = ((f1 * f5) + f2) + ((f0 / f3) * f5);
        if (f21 >= 180.0f) {
            f21 -= 360.0f;
        }
    } else {
        f1 = (f32)s0t;
        f0 = (f32)rand();
        f3 = D_00384D24;
        f5 = 25.0f;
        f2 = -25.0f;
        f1 = f1 * f5;
        f1 = f1 + f2;
        f0 = f0 / f3;
        f0 = f0 * f5;
        f21 = f1 + f0;
        if (s0t >= 2) {
            f21 += 130.0f;
        }
        if (f21 >= 180.0f) {
            f21 -= 360.0f;
        }
    }

    Vec3_Set(0.0f, 1.0f, D_00384D28, sp + 0x10);
    Vec3_Normalize(sp + 0x10, sp + 0x10);
    func_00129BD0(sp, E + 0x250, FLDF(E, 0x48));
    FLDF(sp, 0xC) = 1.0f;

    bit = 1 << (FLD(E, 0x14) & 31);
    a0v = FLD(E, 4);
    if (a0v & bit) {
        varv1 = 1;
        varv0 = a0v & ~bit;
    } else {
        varv0 = a0v | bit;
        varv1 = 0;
    }
    FLD(E, 4) = varv0;
    a3v = 0;
    if ((FLD(E, 0) & 2) == 0) {
        a3v = varv1;
    }
    s2 = EftGlow_SpawnPart(f21, E, arg1, sp, a3v, 0);
    if (s2 != 0) {
        s0 = 0;
        if (FLD(E, 0x30) < 0x41) {
            v1 = FLD(E, 0);
            if (v1 & 2) {
                s0 = 1;
            } else if (!(v1 & 8)) {
                if (FLD(E, 0x18) >= 3) {
                    s0 = 1;
                } else if (!(rand() & 1)) {
                    s0 = 1;
                }
            } else {
                s0 = (rand() % 5) == 0;
            }
            if (s0 != 0) {
                r2 = EftGlow_SpawnPart(f21, E, arg1, sp, 0, 1);
                if (r2 != 0) {
                    v1 = FLD(E, 0) | 8;
                    FLD(E, 0) = v1;
                    if (v1 & 2) {
                        EftGlow_PairPart(E, r2, s2);
                    }
                }
            }
        }
        e18 = FLD(E, 0x18) + 1;
        FLD(E, 0x18) = e18;
        if (e18 >= 4) {
            a0v = FLD(E, 0);
            FLD(E, 0x18) = 0;
            if (a0v & 2) {
                e14 = FLD(E, 0x14) - 1;
                FLD(E, 0x14) = e14;
                if (e14 < 0) {
                    FLD(E, 0x14) = 7;
                }
            } else {
                e14 = FLD(E, 0x14) + 1;
                FLD(E, 0) = a0v & ~8;
                FLD(E, 0x14) = e14;
                if (e14 >= 10) {
                    f20 = D_00384D2C;
                    FLD(E, 0x14) = 0;
                    r1 = rand();
                    r2 = rand();
                    FLDF(E, 0x250) = FLDF(gEftGlowCfg, 0x1B0) * (((f32)r1 / f20) - ((f32)r2 / f20));
                    r3 = rand();
                    r4 = rand();
                    FLDF(E, 0x254) = FLDF(gEftGlowCfg, 0x1B4) * (((f32)r3 / f20) - ((f32)r4 / f20));
                }
            }
        }
    }
    return;
}
