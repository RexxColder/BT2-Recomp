#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FLD16(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define FLD8(p, off) (*(s8 *)((u8 *)(p) + (off)))
#define FLDU8(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define FLDF(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define CVT_W_S(x) ((s32)(x)) /* cvt.w.s del R5900 trunca hacia cero */

extern s32 D_00387848;
extern f32 D_00384EE8;
extern f32 D_00384EEC;
extern f32 D_00384EF0;

s32 func_0020A540(s32 arg0);
s32 func_00126528(void);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_0012D5D8(f32 farg0, f32 farg1, void *arg0, void *arg1, void *arg2, s32 arg3);
void func_00129C28(void *arg0, void *arg1);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
void BtlTask_SetDead(void *arg0);
void func_001AA638(void *arg0);
void func_001AA740(void *arg0);
void func_001AA928(void *arg0);
void func_001E7178(void *arg0);
void func_001E7238(void *arg0, void *arg1);
void EftChain2_SetPos(s32 arg0, void *arg1);
void EftMod1CB_SetPos(s32 arg0, void *arg1);
void EftRibbon_SetEnd(s32 arg0, void *arg1, s32 arg2);
void func_0018E1A8(s32 arg0, void *arg1);
void func_0018E2F8(s32 arg0, void *arg1);
void EftPtcl3_SetPos(s32 arg0, void *arg1);
void EftPtcl3_SetDir(s32 arg0, void *arg1);
s32 EftPtcl3_IsAlive(s32 arg0);
s32 EftChain2_IsAlive(s32 arg0);
s32 func_0018E558(s32 arg0);
s32 func_001CCA88(s32 arg0);

void func_001AB510(void *arg0) {
    u8 spb[0x30];
    u8 *sp = spb;
    u8 *E = (u8 *)arg0;
    u8 *O;
    u8 *P;
    u8 *s5;
    u8 *s0p;
    s32 v1;
    s32 a2;
    s32 q;
    s32 r;
    s32 t;
    f32 f0;
    f32 f1;
    f32 f2;

    s5 = (u8 *)(D_00387848 + 8);
    O = (u8 *)FLD(E, 0x38);
    P = O + 0x40;
    if (func_0020A540(FLD16(P, 0x12)) != 0) {
        FLD(O, 0) = FLD(O, 0) | 0x400;
    }
    v1 = FLD(O, 0);
    if (v1 & 0x400) {
        FLD(O, 0) = v1 | 0x40;
        BtlTask_SetDead(E);
        return;
    }
    if (func_00126528() != 0) {
        goto final;
    }
    if (FLDU8(P, 0x36) != 0) {
        func_00208DE8(FLD16(P, 0x12), O + 0x80, FLD16(P, 0x14));
    }
    v1 = FLD(O, 0);
    if (!(v1 & 0x10)) {
        f1 = FLDF(O, 0x30);
        if (f1 < 1.0f) {
            f0 = f1 + D_00384EE8;
            FLDF(O, 0x30) = f0;
            if (1.0f < f0) {
                FLDF(O, 0x30) = 1.0f;
            }
        }
        f1 = FLDF(O, 0x34);
        if (f1 < 1.0f) {
            f0 = f1 + D_00384EEC;
            FLDF(O, 0x34) = f0;
            if (1.0f < f0) {
                FLDF(O, 0x34) = 1.0f;
            }
        }
    }
    if (!(v1 & 0x100)) {
        if (v1 & 4) {
            func_0012D5D8(FLDF(P, 0x20), FLDF(P, 0x24), sp, O + 0x90, O + 0xB0, FLD16(P, 0x12));
            func_00129C28(O + 0xB0, sp);
        }
        a2 = FLD(O, 0);
        if (a2 & 1) {
            if (a2 & 2) {
                func_00129C28(O + 0xA0, O + 0x90);
            }
            s0p = sp + 0x10;
            func_00129BD0(s0p, O + 0xB0, FLDF(P, 0x20));
            Vec3_Add(O + 0x90, O + 0x90, s0p);
            FLD(O, 0) = FLD(O, 0) | 2;
        }
        FLD(O, 0) = FLD(O, 0) | 1;
    }

    /* L6D4 */
    f1 = FLDF(O, 0x28) + 1.0f;
    FLDF(O, 0x28) = f1;
    f0 = *(f32 *)(FLD(s5, 0));
    if (f0 <= f1) {
        FLDF(O, 0x28) = 0.0f;
        t = FLD(O, 0x20) + 1;
        FLD(O, 0x20) = (t < 8) ? t : 0;
    }
    v1 = FLD(O, 0x20);
    a2 = FLD(O, 0) & 0x80;

    q = (v1 < 0) ? (v1 + 3) : v1;
    q = q >> 2;
    r = v1 - (q << 2);
    f0 = (f32)q * 0.5f;
    f1 = (f32)r * 0.25f;
    f2 = f0 + 0.5f;
    FLDF(O, 0xC4) = f0;
    FLDF(O, 0xC0) = f1;
    FLDF(O, 0xCC) = f2;
    FLDF(O, 0xC8) = f1 + 0.25f;

    if (a2 != 0) {
        func_001E7178(O + 4 * FLD(O, 8) + 0xE8);
        func_001E7238(O + 4 * FLD(O, 8) + 0xE8, O + 0x90);
        EftChain2_SetPos(FLD(O, 0xEC), O + 0x90);
    } else {
        if (FLD(O, 0xD0) != 0) {
            EftMod1CB_SetPos(FLD(O, 0xD0), O + 0x80);
        }
        if (FLD(O, 0xD4) != 0) {
            EftRibbon_SetEnd(FLD(O, 0xD4), O + 0x90, 0);
        }
        if (FLD(O, 0xE4) != 0) {
            EftMod1CB_SetPos(FLD(O, 0xE4), O + 0x80);
        }
    }
    v1 = FLD(O, 4);

    /* L800 */
    if (v1 & 1) {
        func_0018E1A8(FLD(O, 0xD8), O + 0x90);
        func_0018E2F8(FLD(O, 0xD8), O + 0xB0);
        v1 = FLD(O, 4);
    }
    if (v1 & 2) {
        EftPtcl3_SetPos(FLD(O, 0xDC), O + 0x90);
        func_00129BD0(sp + 0x20, O + 0xB0, -1.0f);
        FLDF(sp, 0x2C) = 1.0f;
        EftPtcl3_SetDir(FLD(O, 0xDC), sp + 0x20);
    }

    /* L870 */
    f0 = (f32)FLD(O, 0xC) - 1.0f;
    t = CVT_W_S(f0);
    FLD(O, 0xC) = t;
    if (t <= 0) {
        FLD(O, 0) = FLD(O, 0) | 0x10;
    }

    /* L8A0 */
    if (EftPtcl3_IsAlive(FLD(O, 0xE0)) == 0) {
        FLD(O, 0xE0) = 0;
    }
    if (EftPtcl3_IsAlive(FLD(O, 0xDC)) == 0) {
        FLD(O, 0xDC) = 0;
    }
    if (func_0018E558(FLD(O, 0xD8)) == 0) {
        FLD(O, 0xD8) = 0;
    }
    if (EftChain2_IsAlive(FLD(O, 0xEC)) == 0) {
        FLD(O, 0xEC) = 0;
    }
    if (func_001CCA88(FLD(O, 0xE4)) == 0) {
        FLD(O, 0xE4) = 0;
    }

    /* L8F0 */
    a2 = FLD(O, 0);
    if (a2 & 0x10) {
        if (!(a2 & 0x20)) {
            func_001AA928(E);
            FLD(O, 0) = FLD(O, 0) | 0x20;
        }
        f0 = FLDF(O, 0x24);
        if (f0 <= 0.0f) {
            f0 = FLDF(O, 0x34);
            f1 = f0 - D_00384EF0;
            FLDF(O, 0x34) = f1;
            if (f1 <= 0.0f) {
                FLDF(O, 0x34) = 0.0f;
                FLD(O, 0) = FLD(O, 0) | 0x40;
            }
        } else {
            FLDF(O, 0x24) = f0 - 1.0f;
        }
    } else {
        if (FLDU8(P, 0x35) != 0) {
            func_001AA740(E);
        }
    }

final:
    if (FLD(O, 0) & 0x40) {
        BtlTask_SetDead(E);
    } else {
        func_001AA638(E);
    }
    return;
}
