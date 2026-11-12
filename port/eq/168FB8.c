#include "common.h"

#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define S32(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern f32 D_003847E0;
extern f32 D_003847E4;
extern f32 D_003847E8;
extern f32 D_003847EC;
extern f32 D_003847F0;
extern f32 D_003847F4;
extern f32 D_003847F8;
extern f32 D_003847FC;
extern f32 D_00384800;
extern f32 D_00384804;
extern f32 D_00384808;
extern f32 D_0038480C;
extern f32 D_00384810;

void Mtx_RotateY(f32 f12, void *a0, void *a1);
void Mtx_StoreIdentity(void *a0);
void Vec4_Set(void *a0, f32 f12, f32 f13, f32 f14, f32 f15);
void func_00129C28(void *a0, void *a1);
void func_00129C50(void *a0, void *a1, void *a2);
s32 rand(void);

void func_00168FB8(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 sp[16];
    u8 *s0;
    u8 *s2;
    s32 s4;
    s32 r;
    f32 f20;
    f32 f22;
    f32 f21;
    f32 f23;
    f32 f24;
    f32 f25;
    f32 t;

    t = (f32)arg2 / 7.0f;
    f20 = t * D_003847E0;
    f24 = D_003847E4;
    if (f24 < f20) {
        f20 = f20 - D_003847E0;
    }
    s2 = *(u8 **)(arg0 + 0x38);
    f23 = D_003847E8;
    f25 = 4.0f;
    s4 = arg2 & 3;

    Mtx_StoreIdentity(sp);
    Mtx_RotateY(f20, sp, sp);
    func_00129C28(arg1 + 0x60, s2 + 0x40);
    s0 = arg1 + 0x70;

    /* first rand: f20 = ((R/D) * 8 + 3) * s2.1C */
    f20 = (f32)rand() / f23;
    f20 = f20 * 8.0f;
    f20 = f20 + 3.0f;
    f22 = 0.0f;
    f21 = D_003847EC;
    f20 = f20 * F32(s2, 0x1C);

    /* second rand: Vec4_Set(s0, 0, f20, ((R/D)*4 + 6) * s2.1C, 1) */
    {
        f32 f14;
        f14 = (f32)rand() / f23;
        f14 = f14 * f25;
        f14 = f14 + 6.0f;
        f14 = f14 * F32(s2, 0x1C);
        Vec4_Set(s0, 0.0f, f20, f14, 1.0f);
    }
    func_00129C50(s0, sp, s0);
    Vec4_Set(arg1 + 0x80, 0.0f, 0.0f, 0.0f, 0.0f);

    /* rand chain: each delay-slot store runs before the next call */
    {
        f32 rA;
        f32 rB;
        f32 rC;
        f32 rD;
        f32 rE;
        f32 rF;
        rA = (f32)rand();
        F32(arg1, 0x90) = (rA / f23) * D_003847E4;
        F32(arg1, 0x98) = 0.0f;
        rB = (f32)rand();
        F32(arg1, 0x94) = (rB / f23) * D_003847E4;
        rC = (f32)rand();
        rD = (f32)rand();
        F32(arg1, 0xA0) = ((rC / f23) - (rD / f23)) * f21 * D_003847E4;
        rE = (f32)rand();
        rF = (f32)rand();
        F32(arg1, 0xA8) = 0.0f;
        F32(arg1, 0xA4) = ((rE / f23) - (rF / f23)) * f21 * D_003847E4;
    }

    if (s4 != 0) {
        f32 rG = (f32)rand();
        F32(arg1, 0x38) = (rG / f23) * f25;
    } else {
        F32(arg1, 0x38) = 0.0f;
    }

    if (s4 != 0) {
        f32 rH = (f32)rand();
        F32(arg1, 0x3C) = (rH / D_003847F0) * 3.0f;
    } else {
        S32(arg1, 0x3C) = 0;
    }

    if ((arg2 & 1) == 0) {
        f32 rI = (f32)rand();
        F32(arg1, 0x40) = (rI / D_003847F4) * D_003847F8 + 0.5f;
    } else {
        f32 rJ = (f32)rand();
        F32(arg1, 0x40) = (rJ / D_003847FC) * 0.25f + 0.25f;
    }

    {
        f32 rK;
        f32 rL;
        f32 rM;
        f32 rN;
        f32 f1;
        rK = (f32)rand();
        f1 = D_00384800;
        f20 = D_00384804;
        f22 = D_00384808;
        f21 = D_0038480C;
        F32(arg1, 0x44) = (rK / f20) * f22 + f1;
        rL = (f32)rand();
        F32(arg1, 0x48) = (rL / f20) * f21;
        rM = (f32)rand();
        f1 = D_00384810;
        F32(arg1, 0x4C) = (((rM / f20) * f1) + f1) * f21;
        rN = (f32)rand();
        F32(arg1, 0x54) = 1.0f;
        F32(arg1, 0x50) = ((rN / f20) * 0.5f + 1.0f) * f22;
    }
}
