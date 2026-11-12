#include "common.h"

#define F32AT(p, o) (*(f32 *)((u8 *)(p) + (o)))

void func_00312650(void *, void *, void *);
void func_003126C8(void *, void *);
f32 sceVu0InnerProduct(void *, void *);
void ColSeg_NearestOnLine(f32, f32, void *, void *, void *, s32, void *, void *);
void ColSeg_NearestParallel(f32, f32, void *, void *, void *, void *, s32, void *, void *);
void ColSeg_AdjustNearest(f32, f32, f32, void *, void *, void *, void *, void *, void *);
extern f32 D_003871A4;
extern f32 D_003871A8;
extern f32 D_003871AC;

/* f13 reaches the callees untouched (it is an incoming register), but ColSeg_NearestOnLine / ColSeg_NearestParallel never read it (nor does any caller set it), so it is a dead slot: passed as 0.0f and not a parameter. */
s32 ColSeg_Nearest(void *arg0, void *arg1, void *arg2, void *arg3) {
    u8 sp[0x60];
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f24;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    f32 f7;
    f32 f14;
    f32 f13;
    f32 dAC;
    f32 dBC;
    f32 num;
    f32 sdot;
    f32 ac;
    s32 v;

    func_00312650(sp, (u8 *)arg0 + 0x10, arg0);
    func_00312650(sp + 0x10, (u8 *)arg1 + 0x10, arg1);
    f22 = D_003871A4;
    f21 = sceVu0InnerProduct(sp, sp);
    f24 = D_003871A8;
    f20 = sceVu0InnerProduct(sp + 0x10, sp + 0x10);

    if (f21 < f22) {
        func_003126C8(arg2, arg0);
        ColSeg_NearestOnLine(f24, 0.0f, arg1, sp + 0x10, arg0, 0, arg3, sp + 0x50);
    } else if (f20 < f22) {
        func_003126C8(arg3, arg1);
        ColSeg_NearestOnLine(f24, 0.0f, arg0, sp, arg1, 0, arg2, sp + 0x50);
    } else {
        func_00312650(sp + 0x20, arg1, arg0);
        /* f7 = -(A.B) with A = sp, B = sp+0x10 */
        f0 = -F32AT(sp, 0x0) * F32AT(sp, 0x10);
        f0 = f0 - F32AT(sp, 0x4) * F32AT(sp, 0x14);
        f7 = f0 - F32AT(sp, 0x8) * F32AT(sp, 0x18);
        f14 = (f21 * f20) - f7 * f7;
        if (!(((f14 < 0.0f) ? -f14 : f14) < f24)) {
            /* non-parallel: closest points on the two segments */
            ac = F32AT(sp, 0x0) * F32AT(sp, 0x20) + F32AT(sp, 0x4) * F32AT(sp, 0x24) +
                 F32AT(sp, 0x8) * F32AT(sp, 0x28);
            dBC = -(F32AT(sp, 0x10) * F32AT(sp, 0x20)) - F32AT(sp, 0x14) * F32AT(sp, 0x24);
            dBC = dBC - F32AT(sp, 0x18) * F32AT(sp, 0x28);
            num = (f21 * dBC) - ac * f7;
            f14 = num / f14;
            f13 = (ac - f7 * f14) / f21;
            F32AT(arg2, 0x0) = F32AT(arg0, 0x0) + f13 * F32AT(sp, 0x0);
            F32AT(arg2, 0x4) = F32AT(arg0, 0x4) + f13 * F32AT(sp, 0x4);
            F32AT(arg2, 0x8) = F32AT(arg0, 0x8) + f13 * F32AT(sp, 0x8);
            F32AT(arg3, 0x0) = F32AT(arg1, 0x0) + f14 * F32AT(sp, 0x10);
            F32AT(arg3, 0x4) = F32AT(arg1, 0x4) + f14 * F32AT(sp, 0x14);
            F32AT(arg3, 0x8) = F32AT(arg1, 0x8) + f14 * F32AT(sp, 0x18);
            if (f13 < 0.0f || f13 > 1.0f || f14 < 0.0f || f14 > 1.0f) {
                ColSeg_AdjustNearest(D_003871AC, f13, f14, arg0, sp, arg1, sp + 0x10, arg2, arg3);
            }
        } else {
            ColSeg_NearestParallel(f24, 0.0f, arg0, sp, arg1, sp + 0x10, 0, arg2, arg3);
        }
    }

    /* tail: the two points' midpoints and the distance test */
    v = 1;
    f0 = F32AT(arg3, 0x0) - F32AT(arg2, 0x0);
    f6 = F32AT(arg3, 0x4) - F32AT(arg2, 0x4);
    f5 = F32AT(arg3, 0x8) - F32AT(arg2, 0x8);
    sdot = ((f0 < 0.0f) ? -f0 : f0) + ((f6 < 0.0f) ? -f6 : f6);
    sdot = sdot + ((f5 < 0.0f) ? -f5 : f5);
    F32AT(sp, 0x30) = (F32AT(arg2, 0x0) + F32AT(arg3, 0x0)) * 0.5f;
    F32AT(sp, 0x34) = (F32AT(arg2, 0x4) + F32AT(arg3, 0x4)) * 0.5f;
    F32AT(sp, 0x38) = (F32AT(arg2, 0x8) + F32AT(arg3, 0x8)) * 0.5f;
    if (!(sdot < f24)) {
        v = 0;
    }
    return v;
}
