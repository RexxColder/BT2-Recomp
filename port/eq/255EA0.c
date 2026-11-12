#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern u8 *D_003876A0;
extern u8 *D_003876A4;
extern u8 *D_003879D0;
extern s32 D_00387F2C;

s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void BattleSetup_Finish(void);
void func_00101498(void);
void func_00101A10(void);
void func_00101AB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00101A88(s32 arg0, s32 arg1);
void func_00101AF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s64 arg14,
                   s32 arg15, s32 arg16, s32 arg17);
void func_00101A60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void *func_002AD630(s32 arg0);
s64 func_0024B010(s32 arg0, s32 arg1, void *arg2, void *arg3, s32 arg4);
s32 func_0024B7F0(s32 arg0);
void func_00255580(void *arg0);
void func_00243968(s32 arg0, s32 arg1, s32 arg2);
void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
void func_00255C98(void);
void func_002542F0(void);
void func_002711A0(void);
void func_00253EC8(void);
void func_0028B090(void);
void func_0028BDA0(void);
void func_00297978(void);
void func_002438E8(void);
void func_002554E8(void);
void func_00254BD0(void);
void func_002437E8(void);
void func_00271240(void);
void func_00254B28(void);
void func_0028B218(void);
void func_001012D0(void);

s32 func_00255EA0(void) {
    s32 out[8];
    s16 sp70[16];
    s32 sp90;
    s32 sp94;
    s32 sp9C;
    s32 spA0;
    s32 spA4;
    s32 spA8;
    s32 s5;
    s32 s3;
    s32 s7;
    s32 fp;
    s32 s2;
    s32 s0;
    s32 j;
    s32 k;
    s32 ret;
    s64 s4;
    u8 *s6;
    u8 *t2;
    u8 *v1p;
    u8 *p3;
    s32 v1x;
    s32 a0v;
    s32 a3val;
    s32 t0v;
    s32 t1v;
    s32 v1val;

    sp90 = 1;
    func_002542F0();
    func_00243968(0, 0, 0);
    goto loop_6;

loop_6:
    func_002711A0();
    func_00253EC8();
    func_0028B090();
    func_0028BDA0();
    func_00297978();
    func_002438E8();
    func_002554E8();
    func_00254BD0();
    BattleSetup_Finish();
    func_002437E8();
    func_00271240();
    if (FLD(D_003879D0, 0x15C) & 0x40) {
        if (FLD(D_003879D0, 0x294) == 4) {
            func_00255C98();
        }
        goto loop_6;
    }
    if (ColorFade_IsFadingOut() != 0) {
        func_00101498();
        goto loop_6;
    }
    if (ColorFade_IsOutDone() == 0) {
        if (FLD(D_003879D0, 0x15C) & 2) {
            s32 t = FLD(D_003879D0, 0x170) - 1;
            FLD(D_003879D0, 0x170) = t;
            if (t == -1) {
                func_00243A80(0, 0, 0);
            }
        } else {
            func_00255580(&sp90);
        }
        goto loop_6;
    }

    if (sp90 != 0) {
        spA8 = 0;
        s5 = 0;
        s6 = (u8 *)FLD(D_003876A0, 0x74);
        func_00101A10();
        func_00101AB0(0, FLD(D_003879D0, 0x268), 0, 0);
        func_00101AB0(1, FLD(D_003879D0, 0x26C), 1, 0);
        do {
            sp94 = 0;
            if (FLD(D_003879D0, 0x268 + s5 * 4) > 0) {
                sp9C = 0;
                spA0 = 0;
                spA4 = 0x204;
                s3 = (s5 << 6) + spA8 + 0x1A0;
                fp = 0;
                s7 = 0x1A0;
                do {
                    if (s5 != 0) {
                        for (j = 0; j < 7; j++) {
                            u8 *addr;
                            k = FLD(D_003876A4, 0x38);
                            addr = (u8 *)(FLD(D_003879D0, 0x2A8) + fp) + ((k * 7 + j) * 4) + 0x20;
                            if (*(s32 *)addr >= 0) {
                                sp70[2 * j] = (s16)(*(u16 *)addr + 1);
                            } else {
                                sp70[2 * j] = 0;
                            }
                        }
                        s4 = func_0024B010(FLD(D_003879D0, 0x288), FLD(D_003879D0, 0x28C), sp70, out, 0x7D);
                        s2 = FLD(s6 + 16 * FLD(D_003879D0, spA4), 0) + func_0024B7F0(out[0]);
                    } else {
                        s32 v1k = FLD(D_003879D0, s7 + 8);
                        s32 a2v = D_00387F2C + v1k * 0x22 + 0x1408;
                        s4 = func_0024B010(FLD(D_003879D0, 0x288), FLD(D_003879D0, 0x28C), (void *)a2v, out, 0x14);
                        s2 = FLD(s6 + 16 * FLD(D_003879D0, s7), 0) + func_0024B7F0(out[0]);
                    }

                    p3 = D_003879D0 + s3;
                    v1x = FLD(p3, 0);
                    s0 = v1x * 9 + FLD(p3, 0xC);
                    sp94 += 1;
                    spA4 += 0x14;
                    ret = func_00101A88(s5, sp94);
                    a0v = ret + spA0 + 8;
                    t2 = (u8 *)(FLD(D_003879D0, 0x2A8) + sp9C);
                    v1p = t2 + 4;
                    a3val = FLD(v1p, 4 * FLD(D_003876A4, 0x38) + 0x10);
                    t0v = FLD(v1p, 0);
                    t1v = *(u8 *)(t2 + 8);
                    v1val = FLD(s6 + 16 * v1x, 4);

                    spA0 += 0x58;
                    sp9C += 0x78;
                    fp += 0x78;
                    s3 += 0x14;
                    s7 += 0x14;

                    func_00101AF8(a0v, s0, 0, a3val, t0v, t1v, out[0], out[1],
                                  out[2], out[3], out[4], out[5], out[6], out[7],
                                  s4, s2, s2, v1val);
                } while (sp94 < FLD(D_003879D0, 0x268 + s5 * 4));
            }
            s5 += 1;
            spA8 += 0x24;
        } while (s5 < 2);

        {
            u8 *v6 = (u8 *)func_002AD630(spA8);
            func_00101A60(1, FLD(v6, 4), FLD(v6, 8), 0, FLD(v6, 0xC), FLD(v6, 0));
            FLD(D_003876A4, 0x3C) = FLD(D_003879D0, 0x27C);
        }
    }

    func_00254B28();
    func_0028B218();
    func_001012D0();
    return sp90;
}
