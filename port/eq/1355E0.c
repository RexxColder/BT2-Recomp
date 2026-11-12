#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))

extern s32 D_00388724;
extern u8 *D_003876A0;
extern u8 *gEftBurst;
extern f32 D_003842A8;
extern f32 D_003842AC;
extern f32 D_003842B0;

extern void BtlTask_SetDead();
extern void EftCam_StopIfRunning(void);
extern u8 *EftBurst_AllocPtcl(void);
extern void func_00133280(u8 *p);
extern void func_001331E8(u8 *p);
extern void func_00132F18(u8 *p);
extern void func_00133328(u8 *p);
extern void func_00132D78(u8 *p, s32 i);
extern void EftBurst_InitDebris(u8 *p);
extern s32 rand(void);
extern f32 sinf(f32 x);
extern s32 func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* Per-frame update of the burst effect (gEftBurst): spawns particle groups on fixed frames (0, 7, 10, 30, >=9
   periodic), advances the sin-sum wobble value, runs the 350 particle callbacks and plays the sound cues. */
void func_001355E0(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    u8 *g;
    u8 *p;
    s32 i;
    f32 sum;
    f32 a;

    if (D_00388724 != 0) {
        BtlTask_SetDead(r_a0);
        EftCam_StopIfRunning();
        return;
    }
    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }
    g = gEftBurst;
    if (W(g, 4) == 0) {
        p = EftBurst_AllocPtcl();
        if (p != NULL) {
            func_00133280(p);
            W(p, 0x60) = 0x20;
            W(p, 0x50) = W(p, 0x50) | 0x10;
            F(p, 0x68) = 70.0f;
        }
        p = EftBurst_AllocPtcl();
        g = gEftBurst;
        if (p != NULL) {
            func_00133280(p);
            W(p, 0x60) = 0x40;
            W(p, 0x50) = W(p, 0x50) | 0x10;
            F(p, 0x68) = 50.0f;
            g = gEftBurst;
        }
    }
    if (W(g, 4) == 7) {
        p = EftBurst_AllocPtcl();
        g = gEftBurst;
        if (p != NULL) {
            func_001331E8(p);
            W(p, 0x60) = 0x45;
            g = gEftBurst;
        }
    }
    if (W(g, 4) == 10) {
        for (i = 0xEF; i >= 0; i--) {
            p = EftBurst_AllocPtcl();
            if (p != NULL) {
                func_00132F18(p);
            }
        }
        g = gEftBurst;
    }
    if (W(g, 4) == 30) {
        p = EftBurst_AllocPtcl();
        g = gEftBurst;
        if (p != NULL) {
            func_001331E8(p);
            W(p, 0x60) = 0x20;
            g = gEftBurst;
        }
    }
    if (W(g, 4) >= 9) {
        if (W(g, 0) == 0) {
            p = EftBurst_AllocPtcl();
            if (p != NULL) {
                func_00133328(p);
            }
            W(gEftBurst, 0) = (rand() & 3) + 5;
        } else {
            W(g, 0) = W(g, 0) - 1;
        }
        g = gEftBurst;
    }
    if (W(g, 4) == 10) {
        for (i = 0; i < 0x20; i++) {
            p = EftBurst_AllocPtcl();
            if (p != NULL) {
                func_00132D78(p, i);
            }
        }
        for (i = 0xF; i >= 0; i--) {
            p = EftBurst_AllocPtcl();
            if (p != NULL) {
                EftBurst_InitDebris(p);
            }
        }
        g = gEftBurst;
    }
    if (W(g, 4) >= 11) {
        p = EftBurst_AllocPtcl();
        if (p != NULL) {
            func_00132D78(p, 0);
        }
        p = EftBurst_AllocPtcl();
        g = gEftBurst;
        if (p != NULL) {
            EftBurst_InitDebris(p);
            g = gEftBurst;
        }
    }
    if (W(g, 4) < 0x97) {
        W(g, 4) = W(g, 4) + 1;
        g = gEftBurst;
    }
    if (F(g, 8) < 50.0f) {
        F(g, 8) = F(g, 8) + D_003842A8;
        g = gEftBurst;
    }
    F(g, 0xC) = F(g, 0xC) * D_003842AC;
    W(gEftBurst, 0x14) = W(gEftBurst, 0x14) + (rand() & 7) + 3;
    g = gEftBurst;
    if (W(g, 0x14) >= 0x169) {
        W(g, 0x14) = W(g, 0x14) - 0x168;
        g = gEftBurst;
    }
    sum = sinf((f32)W(g, 0x14) * D_003842B0 / 180.0f);
    for (i = 2; i <= 6; i++) {
        s32 ang = (W(gEftBurst, 0x14) * i) % 0x168;

        sum = sum + sinf((f32)ang * D_003842B0 / 180.0f);
    }
    F(g, 0x10) = sum / 6.0f;

    p = gEftBurst + 0x240;
    for (i = 0x15D; i >= 0; i--, p += 0x70) {
        s32 (*cb)(u8 *) = *(s32 (**)(u8 *))(p + 0x54);

        W(p, 0x64) = 0;
        if (cb != NULL && cb(p)) {
            W(p, 0x64) = 1;
        }
    }
    g = gEftBurst;
    if (W(g, 4) == 7) {
        func_00297FE0(1, 0x4A, 0x7F, 0x40, -0x352);
        g = gEftBurst;
    }
    if (W(g, 4) == 30) {
        func_00297FE0(1, 0x4A, 0x7F, 0x40, -0x352);
        g = gEftBurst;
    }
    if (W(g, 4) < 0x1F) {
        return;
    }
    if (W(g, 4) % 0x3C == 0) {
        if (rand() % 100 < 0x14) {
            func_00297FE0(1, 0x47, 0x7F, 0x40, -0x1F4);
        }
        g = gEftBurst;
    }
    W(g, 0x9B60) = W(g, 0x9B60) - 1;
    if (W(gEftBurst, 0x9B60) <= 0) {
        func_00297FE0(1, 0x4A, 0x7F, 0x40, -0x352);
        W(gEftBurst, 0x9B60) = rand() % 0x50 + 0x3C;
    }
}
