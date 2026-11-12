#include "common.h"

#define PF32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define PS32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern f32 D_00385A74;
extern f32 D_00385A78;

u8 *BtlChar_GetPos(void *arg0);
s32 BtlPad_Test48(void *arg0, s32 arg1);
void BtlOpp_GetDelta(void *arg0, void *arg1);
f32 BtlOpp_GetHalfHeightDiff(void *arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
f32 fabsf(f32 farg0);
f32 func_00207E80(void *arg0);
f32 func_00207E88(void *arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_00210868(void *arg0, void *arg1);
void func_00210970(void *arg0, void *arg1);
void func_003126C8(void *arg0, void *arg1);
f32 func_0029DFD0(void *arg0);
f32 func_002086B0(void *arg0);
f32 func_00210D10(void *arg0);
void sceVu0Normalize(void *arg0, void *arg1);
f32 sceVu0InnerProduct(void *arg0, void *arg1);
f32 Mathf_Asin(f32 farg0);

/* 0x00215068: per-actor angle update, switched on a1 (0..8: target angle source, pos+0xB4), then turns pos+0x14
   toward it with a speed limit of |angle delta| * fScale (clamped to fMax), and finally sets pos+0xB0 / 0xB8 / 0xBC
   from a2 (9..11 also work out a tilt from the actor geometry). */
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 fMax, f32 fScale) {
    u8 sp[0x120];
    u8 *pos;
    u8 *pp;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 w;
    f32 fLim;
    f32 hh;
    f32 k0;
    f32 r2;
    f32 t;
    f32 d;
    f32 r;
    f32 asinv;
    f32 ff;

    f23 = fMax;
    f24 = fScale;

    pos = BtlChar_GetPos(a0);
    switch (a1) {
    case 0:
        if (BtlPad_Test48(a0, 8) != 0) {
            f22 = func_00207E80(a0);
            f21 = -func_00207E88(a0);
            if (func_00211310(a0, 0, 1) != 0) {
                BtlOpp_GetDelta(a0, sp);
                f20 = atan2f(PF32(sp, 0x0), PF32(sp, 0x8));
            } else {
                f20 = PF32(a0, 0x150);
            }
            PF32(pos, 0xB4) = BtlUtil_WrapAngle(atan2f(f22, f21) + f20);
        }
        break;
    case 1:
        if (func_00211310(a0, 0, 1) != 0) {
            BtlOpp_GetDelta(a0, sp + 0x10);
            PF32(pos, 0xB4) = atan2f(PF32(sp, 0x10), PF32(sp, 0x18));
        }
        break;
    case 2:
        if (func_00211310(a0, 0, 1) != 0) {
            BtlOpp_GetDelta(a0, sp + 0x30);
            PF32(pos, 0xB4) = atan2f(-PF32(sp, 0x30), -PF32(sp, 0x38));
        }
        break;
    case 3:
        if (func_00211310(a0, 0, 1) != 0) {
            BtlOpp_GetDelta(a0, sp + 0x20);
            PF32(pos, 0xB4) = BtlUtil_WrapAngle(atan2f(PF32(sp, 0x20), PF32(sp, 0x28)) + PF32(a0, 0xA48));
        }
        break;
    case 4:
        PF32(pos, 0xB4) = PF32(a0, 0xB5C);
        break;
    case 5:
        break;
    case 6:
        PF32(pos, 0xB4) = atan2f(-PF32(pos, 0x0), -PF32(pos, 0x8));
        break;
    case 7:
        PF32(pos, 0xB4) = atan2f(PF32(pos, 0x0), PF32(pos, 0x8));
        break;
    case 8:
        if (func_00211310(a0, 0, 1) != 0) {
            func_00210868(a0, sp + 0x40);
            PF32(pos, 0xB4) = PF32(sp, 0x44);
        }
        break;
    default:
        break;
    }

    w = BtlUtil_WrapAngle(PF32(pos, 0xB4) - PF32(pos, 0x14));
    fLim = fabsf(w) * f24;
    if (fLim < D_00385A74) {
        fLim = D_00385A74;
    }
    if (f23 < fLim) {
        fLim = f23;
    }
    if (w < -fLim) {
        PF32(pos, 0x14) = BtlUtil_WrapAngle(PF32(pos, 0x14) - fLim);
    } else if (fLim < w) {
        PF32(pos, 0x14) = BtlUtil_WrapAngle(PF32(pos, 0x14) + fLim);
    } else {
        PF32(pos, 0x14) = PF32(pos, 0xB4);
    }

    if (a2 == 12) {
        PS32(pos, 0xB0) = 0;
        PS32(pos, 0xBC) = 0;
    } else if (a2 < 9 || a2 >= 13) {
        PS32(pos, 0xBC) = 0;
    } else {
        if (func_00211310(a0, 0, 1) != 0) {
            BtlOpp_GetDelta(a0, sp + 0x50);
            if (a2 == 11) {
                PF32(sp, 0x54) = PF32(sp, 0x54) + PF32(sp, 0x54);
            }
            f24 = D_00385A78;
            hh = BtlOpp_GetHalfHeightDiff(a0);
            PF32(sp, 0x54) = PF32(sp, 0x54) + hh;
            pp = BtlChar_GetPos(a0);
            func_003126C8(sp + 0x60, pp + 0x40);
            func_00210970(a0, sp + 0x70);
            f23 = func_0029DFD0(sp + 0x60);
            f22 = func_0029DFD0(sp + 0x70);
            if (f24 < f23) {
                if (f24 < f22) {
                    sceVu0Normalize(sp + 0x80, sp + 0x60);
                    sceVu0Normalize(sp + 0x90, sp + 0x70);
                    sceVu0Normalize(sp + 0xA0, sp + 0x50);
                    f20 = func_0029DFD0(sp + 0x50);
                    k0 = func_002086B0(*(u8 **)(a0 + 0x1534));
                    t = (1.0f - fabsf(PF32(sp, 0xA4))) * k0;
                    r2 = func_00210D10(a0);
                    f20 = f20 - t;
                    f20 = f20 - (1.0f - fabsf(PF32(sp, 0xA4))) * r2;
                    if (f20 < 0.0f) {
                        f20 = 0.0f;
                    }
                    d = sceVu0InnerProduct(sp + 0x80, sp + 0x90);
                    t = f23 - f22 * d;
                    if (f24 < t) {
                        r = f20 / t;
                        if (r < 1.0f) {
                            PF32(sp, 0x54) = PF32(sp, 0x54) * r;
                        }
                    }
                }
            }
            sceVu0Normalize(sp + 0x50, sp + 0x50);
            if (PF32(sp, 0x54) < -1.0f) {
                PF32(sp, 0x54) = -1.0f;
            }
            if (1.0f < PF32(sp, 0x54)) {
                PF32(sp, 0x54) = 1.0f;
            }
            asinv = Mathf_Asin(PF32(sp, 0x54));
            PF32(pos, 0xB0) = -asinv;
            if (a2 == 10) {
                ff = -func_00207E88(a0);
                if (ff < 0.0f) {
                    ff = 0.0f;
                }
                PF32(pos, 0xB0) = PF32(pos, 0xB0) * ff;
            }
        }
        PS32(pos, 0xBC) = 0;
    }
    PS32(pos, 0xB8) = 0;
}
