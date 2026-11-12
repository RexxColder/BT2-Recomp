#include "common.h"

extern f32 D_00384A14;
extern f32 D_00384A18;
extern f32 D_00384A1C;
extern f32 D_00384A20;
extern u8 *D_0038777C;

s32 EftAura_SpawnFlames(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0017ACA0(s32 arg0, s32 arg1, f32 farg);

#define W32(off) (*(s32 *)(p + (off)))
#define F32F(off) (*(f32 *)(p + (off)))
#define GW(off) (*(f32 *)(D_0038777C + (off)))

void EftAura_UpdateState(s32 arg0, s32 arg1) {
    u8 *p = (u8 *)arg0;
    s32 count;
    s32 mode;
    s32 mode2;
    f32 f2v;
    f32 t;
    f32 t1;
    f32 t2;

    count = W32(0x28);
    if (count < 0xA) {
        do {
            EftAura_SpawnFlames(arg0, arg1, count, 0);
            count = W32(0x28) + 1;
            W32(0x28) = count;
        } while (count < 0xA);
    }

    mode = W32(0x30);
    if (mode == 0) {
        f2v = F32F(0x50);
    } else if (mode == 1) {
        f2v = F32F(0x50) + D_00384A14;
        F32F(0x48) = D_00384A18;
        F32F(0x50) = f2v;
        if (1.0f <= f2v) {
            F32F(0x50) = 1.0f;
            f2v = 1.0f;
        }
    } else if (mode == 2) {
        f2v = 1.0f;
        F32F(0x50) = 1.0f;
        t = F32F(0x44) + 1.0f;
        F32F(0x44) = t;
        if (GW(0x19C) <= t) {
            W32(0xC) = 1;
            W32(0x30) = 3;
            F32F(0x44) = 0.0f;
            W32(8) = 1;
        }
    } else {
        t = F32F(0x50) - D_00384A1C;
        F32F(0x50) = t;
        if (t <= 0.0f) {
            t1 = F32F(0x48) - D_00384A20;
            F32F(0x50) = 0.0f;
            F32F(0x48) = t1;
            if (t1 <= 1.0f) {
                F32F(0x48) = 1.0f;
            }
        }
        f2v = F32F(0x50);
        if (F32F(0x48) <= 1.0f) {
            if (f2v <= 0.0f) {
                W32(0x30) = 0;
            }
        }
    }

    F32F(0x40) = GW(0x1A4) * f2v;

    if (W32(8) == 1) {
        t = F32F(0x54);
        if (0.0f < t) {
            t2 = t - (1.0f / GW(0x1B4));
            F32F(0x54) = t2;
            if (t2 <= 0.0f) {
                F32F(0x58) = 0.0f;
                F32F(0x54) = 0.0f;
                W32(8) = 0;
            }
        }
    } else {
        t = F32F(0x54);
        if (t < 1.0f) {
            t1 = F32F(0x58) + (1.0f / GW(0x1B0));
            t2 = t + t1;
            F32F(0x58) = t1;
            F32F(0x54) = t2;
            if (1.0f <= t2) {
                F32F(0x54) = 1.0f;
                F32F(0x58) = 0.0f;
            }
        }
    }

    if (W32(0xC) != 1) {
        t = F32F(0x5C);
        if (t < 1.0f) {
            t1 = F32F(0x60) + (1.0f / GW(0x1A8));
            t2 = t + t1;
            F32F(0x60) = t1;
            F32F(0x5C) = t2;
            if (1.0f <= t2) {
                F32F(0x5C) = 1.0f;
                F32F(0x60) = 0.0f;
            }
        }
    } else {
        t = F32F(0x5C);
        if (0.0f < t) {
            t2 = t - (1.0f / GW(0x1AC));
            F32F(0x5C) = t2;
            if (t2 <= 0.0f) {
                F32F(0x60) = 0.0f;
                F32F(0x5C) = 0.0f;
                W32(0xC) = 0;
            }
        }
    }

    mode2 = W32(0x2C);
    if (mode2 != 0) {
        if (mode2 == 1) {
            t = F32F(0x3C) + (1.0f / GW(0x194));
            F32F(0x3C) = t;
            if (1.0f <= t) {
                F32F(0x3C) = 1.0f;
                W32(0x2C) = 0;
            }
        } else {
            t = F32F(0x3C) - (1.0f / GW(0x198));
            F32F(0x3C) = t;
            if (t <= 0.0f) {
                if (mode2 == 3) {
                    W32(0) = W32(0) | 2;
                }
                F32F(0x3C) = 0.0f;
                W32(0x2C) = 0;
            }
        }
    }

    func_0017ACA0(arg0, arg1, 0.0f); /* f12 is a dead pass-through slot (func_00129C28 ignores it); a2 is not read */
}
