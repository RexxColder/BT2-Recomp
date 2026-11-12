#include "common.h"

extern u8 *D_0042A590 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_3876A0 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));

extern s32 func_003FFD60();
extern s32 func_00243968();
extern s32 func_002711A0();
extern s32 func_003FF9C0();
extern s32 func_0028B090();
extern s32 func_0028BDA0();
extern s32 func_00297978();
extern s32 func_002438E8();
extern s32 func_00401CE0();
extern s32 func_00401C28();
extern s32 func_00400AC0();
extern s32 BattleSetup_Finish();
extern s32 func_004019C8();
extern s32 func_002437E8();
extern s32 func_00271240();
extern s32 ColorFade_IsInDone();
extern s32 func_0026EB60();
extern s32 ColorFade_IsFadingOut();
extern s32 func_00101890();
extern s32 func_00101498();
extern s32 ColorFade_IsOutDone();
extern s32 func_00243A80();
extern s32 func_00401BC0();
extern s32 func_00101A10();
extern s32 func_00101AB0();
extern s64 func_0024B010();
extern s64 func_0024B110();
extern s32 func_0024B7F0();
extern s32 func_0024B210();
extern s32 func_00101A88();
extern s32 func_00101AF8();
extern s32 func_0024AF50();
extern s32 func_00101A60();
extern s32 func_004009F8();
extern s32 func_0028B218();

s32 func_004027B0(s32 arg0) {
    s32 flag;
    s32 st[8];
    s32 idx;
    u8 *tbl;
    u8 *D;
    u8 *s5;
    s32 i;

    flag = 1;
    func_003FFD60(arg0);
    func_00243968(0, 0, 0);
    for (;;) {
        func_002711A0();
        func_003FF9C0();
        func_0028B090();
        func_0028BDA0();
        func_00297978();
        func_002438E8();
        func_00401CE0(&flag);
        func_00401C28();
        func_00400AC0();
        BattleSetup_Finish();
        func_004019C8();
        func_002437E8();
        func_00271240();
        if (ColorFade_IsInDone()) {
            D = D_0042A590;
            if (*(s32 *)(D + 0x218) == 0) {
                if (func_0026EB60(D + 0xCC)) {
                    *(s32 *)(D_0042A590 + 0x218) = 1;
                }
            }
        }
        if (ColorFade_IsFadingOut()) {
            func_00101890();
            if (flag != 0) {
                func_00101498();
            }
            continue;
        }
        if (ColorFade_IsOutDone()) {
            if (*(s32 *)(D_0042A590 + 0x228) == 4) {
                break;
            }
            continue;
        }
        D = D_0042A590;
        if (*(s32 *)(D + 0x208) & 2) {
            if (*(s32 *)(D + 0x228) == 4) {
                s32 v = *(s32 *)(D + 0x214) - 1;
                *(s32 *)(D + 0x214) = v;
                if (v == -1) {
                    func_00243A80(0, 0, 0);
                    *(s32 *)(D_3876A4 + 0x5C) = *(s32 *)(D_0042A590 + 0x23C);
                }
            }
        } else if (*(s32 *)(D + 0x220) == 0) {
            func_00401BC0(&flag);
        }
    }

    if (flag != 0) {
        D = D_0042A590;
        idx = 0;
        tbl = *(u8 **)(D + 0x27C) + ((*(s32 *)(D_3876A4 + 0x64) * 9 + *(s32 *)(D + 0x234)) << 5);
        s5 = *(u8 **)(D_3876A0 + 0x74);
        func_00101A10(D_3876A0, *(s32 *)(D + 0x234), tbl);
        *(s64 *)(D_3876A0 + 0x4D8) = 0;
        func_00101AB0(0, *(s32 *)(D_3876A4 + 0x68), 0, 0);
        func_00101AB0(1, *(s32 *)tbl, 1, 0);
        while (idx < 2) {
            if (idx != 0) {
                s32 j = 0;
                s32 off = 0;
                s32 k;
                s32 *sp4;
                *(s32 *)(D_0042A590 + 0x238) = 0;
                if (*(s32 *)tbl > 0) {
                    sp4 = (s32 *)(tbl + 4);
                    do {
                        u8 *e;
                        s64 s3;
                        s32 s2, s1, t;
                        u8 *a;
                        u8 *kk;
                        u8 *Dd;
                        e = *(u8 **)D_3876A4;
                        (void)e;
                        k = *sp4++;
                        Dd = D_0042A590;
                        kk = *(u8 **)(Dd + 0x280) + k * 120;
                        j++;
                        s3 = func_0024B110(*(u8 **)(Dd + 0x26C), *(u8 **)(Dd + 0x270),
                                           kk + *(s32 *)(D_3876A4 + 0x58) * 36 + 0x14, st, 0x7D);
                        s2 = *(s32 *)(s5 + (*(s32 *)kk << 4)) + func_0024B7F0(st[0]);
                        t = func_0024B210(st);
                        *(s32 *)(D_0042A590 + 0x238) += t;
                        s1 = *(s32 *)kk * 9 + *(s32 *)(kk + 8);
                        a = (u8 *)(func_00101A88(1) + off);
                        off += 0x58;
                        {
                            u8 *q = kk + *(s32 *)(D_3876A4 + 0x58) * 36;
                            func_00101AF8(a + 8, s1, 0, *(s32 *)(q + 0xC), *(s32 *)(q + 0x10), *(s32 *)(kk + 4),
                                          st[0], st[1], st[2], st[3], st[4], st[5], st[6], st[7], s3, s2, s2,
                                          *(s32 *)(s5 + (*(s32 *)kk << 4) + 4));
                        }
                    } while (j < *(s32 *)tbl);
                }
            } else {
                s32 j = 0;
                s32 fp = 0;
                s32 s7 = 0;
                s32 s0 = 0x40;
                if (idx < *(s32 *)(D_3876A4 + 0x68)) {
                    do {
                        u8 *e = D_3876A4;
                        s64 s3;
                        s32 s2, s1;
                        u8 *a;
                        if (*(s32 *)(e + 0x40) & (1 << j)) {
                            s32 v1 = *(s32 *)(e + s0 + 0xC);
                            s3 = func_0024B010(*(u8 **)(D_0042A590 + 0x26C), *(u8 **)(D_0042A590 + 0x270),
                                               D_387F2C + v1 * 34 + 0x1408, st, 0x14);
                            s2 = *(s32 *)(s5 + (*(s32 *)(D_3876A4 + s0 + 4) << 4)) + func_0024B7F0(st[0]);
                        } else {
                            s32 n;
                            s3 = 0;
                            for (n = 0; n < 8; n++) {
                                st[n] = 1;
                            }
                            s2 = *(s32 *)(s5 + (*(s32 *)(D_3876A4 + s0 + 4) << 4));
                        }
                        e = D_3876A4;
                        j++;
                        s1 = *(s32 *)(e + s0 + 4) * 9 + *(s32 *)(e + s7 + 0x70);
                        s7 += 4;
                        a = (u8 *)(func_00101A88(0) + fp);
                        fp += 0x58;
                        func_00101AF8(a + 8, s1, 0, 0, 0, 0, st[0], st[1], st[2], st[3], st[4], st[5], st[6], st[7], s3,
                                      s2, s2, *(s32 *)(s5 + (*(s32 *)(D_3876A4 + s0 + 4) << 4) + 4));
                        s0 += 4;
                    } while (j < *(s32 *)(D_3876A4 + 0x68));
                }
            }
            idx++;
        }
        {
            s32 t1 = func_0024AF50(*(s32 *)(tbl + 0x1C));
            s32 t0 = 2;
            s32 v = *(s32 *)(*(u8 **)(D_0042A590 + 0x274) + *(s32 *)(D_3876A4 + 0x64) * 56 + 0xC) ^ 1;
            if (v != 0) {
                t0 = 0;
            }
            func_00101A60(2, *(s32 *)(tbl + 0x18) - 1, 0, 1, t0, t1);
        }
        *(s32 *)(D_3876A4 + 0x84) = *(s32 *)(D_0042A590 + 0x238);
    }
    func_004009F8();
    func_0028B218();
    return flag;
}
