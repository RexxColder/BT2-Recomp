#include "common.h"

extern u8 *gBtlStage;
extern u8 *D_00387AB4;
extern f32 D_00386FC4;

u8 *Vu1Pkt_LoadProg8(void);
void Vu0Screen_StoreMtx(s32 arg0);
void Vu0Clip_StoreMtx(s32 arg0);
void func_00276150(void);
s32 func_00271FA8(void *arg0);
u8 *StgOfsTable_Get(void *arg0, s32 arg1);
void EftShotFx_UpdateLines(s32 arg0);
s32 func_002745F8(s32 arg0);
void func_0029D2D8(void *arg0, void *arg1);
void Vu0Cur_StoreMtx(void *arg0);
void func_0029EA78(void *arg0, void *arg1, void *arg2, f32 farg0);
s32 func_00272510(void *arg0, void *arg1);
void func_00286D08(void *arg0, s32 arg1, s32 arg2);
void Vu1Node_Draw(void *arg0);

/* 0x002729D0: VU1 draw pass over the stage table (per 3-stride group, per record matching the group id). */
void func_002729D0(void) {
    u8 fr[0x60];   /* tamano de locales del original (antes 0x50) */
    u8 *pkt;
    u8 *t0;
    u8 *t1;
    u8 *t2;
    u8 *s0p;
    u8 *s1p;
    u8 *s2p;
    u8 *fpp;
    u8 *s3p;
    u8 *s6p;
    s32 s5;
    s32 s4;
    s32 s7;
    s32 var54;
    s32 cnt58;
    s32 cnt16;
    s32 v;
    s32 vv;
    u32 a2;
    u32 w4;
    f32 f20;
    f32 f21;
    f32 f0;
    f32 f1;
    f32 f2;

    if (D_00387AB4 == NULL) {
        return;
    }
    s5 = 0;
    pkt = Vu1Pkt_LoadProg8();
    var54 = 1;
    Vu0Screen_StoreMtx((s32)(pkt + 0xB0));
    Vu0Clip_StoreMtx((s32)(pkt + 0xF0));
    func_00276150();
    cnt58 = func_00271FA8(D_00387AB4);
    s3p = *(u8 **)(gBtlStage + 4);
    if (cnt58 <= 0) {
        return;
    }
    f20 = D_00386FC4;
    f21 = 180.0f;

    for (; s5 < cnt58; s5 += 3) {
        s7 = 0;
        t0 = StgOfsTable_Get(D_00387AB4, s5);
        t1 = StgOfsTable_Get(D_00387AB4, s5 + 1);
        a2 = (*(u32 *)t1) & ~3u;
        w4 = (*(u32 *)(t1 + 4)) & ~3u;
        s2p = t1 + (s32)a2;
        fpp = t1 + (s32)w4;
        s6p = StgOfsTable_Get(D_00387AB4, s5 + 2);

        cnt16 = *(u16 *)(s3p + 6);
        if (cnt16 != 0) {
            s1p = s3p + ((*(s32 *)(s3p + 0xC)) << 2);
            for (s4 = 0; s4 < cnt16; s4++) {
                if (*(s32 *)(s1p + 8) != var54) {
                    s1p += 0x10;
                    continue;
                }
                if ((*(u32 *)(s1p + 4) & 0x40000000u) == 0) {
                    if (func_002745F8(s4) != 0) {
                        s1p += 0x10;
                        continue;
                    }
                }

                v = *(s32 *)(s1p + 0xC);
                vv = (v < 0) ? v + 3 : v;
                vv = (vv >> 2) << 2;
                s0p = s3p + vv;

                f0 = *(f32 *)(s0p + 0x10) / f21 * f20;
                *(f32 *)(fr + 0x40) = f0;
                f1 = *(f32 *)(s0p + 0x14) / f21 * f20;
                *(f32 *)(fr + 0x44) = f1;
                f2 = 1.0f;
                *(f32 *)(fr + 0x4C) = f2;
                f0 = *(f32 *)(s0p + 0x18) / f21 * f20;
                *(f32 *)(fr + 0x48) = f0;

                EftShotFx_UpdateLines(v + 3);
                func_0029D2D8(s0p, fr + 0x40);
                Vu0Cur_StoreMtx(fr);
                func_0029EA78(s2p, s6p, fr, *(f32 *)(s0p + 0x20));
                if (func_00272510(s2p, fpp) == 0) {
                    if (s7 == 0) {
                        func_00286D08(t0, 0x3480, 0x3700);
                        s7 = 1;
                    }
                    Vu1Node_Draw(s2p);
                }
                s1p += 0x10;
            }
        }
        var54 += 1;
    }
}
