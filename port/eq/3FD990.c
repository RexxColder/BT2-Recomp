#include "common.h"

extern u8 *D_0042A588 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_3876A0 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));
extern u8 D_0042B850[];

extern s32 func_003FBC08();
void func_00243968(s32 arg0, s32 arg1, s32 arg2);
extern void func_002711A0(void);
void func_0028B090(void);
void func_0028BDA0(void);
void func_00297978(s32 arg0, s32 arg1);
void func_002438E8(void);
void func_003FD610(void);
extern void func_003FC8B8(void);
extern s32 BattleSetup_Finish();
void func_003FD7C0(s32 *arg0);
void func_002437E8(void);
void func_00271240(void);
extern s32 ColorFade_IsInDone();
extern s32 ColorFade_IsFadingOut();
extern s32 ColorFade_IsOutDone();
s32 func_0026EB60(u8 *arg0);
void func_0026EB78(u8 *arg0, s32 arg1);
void func_002493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00101890(void);
void func_00101498(void);
void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
void func_003FD328(s32 *arg0);
void func_00101A10(void);
void func_00101AB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00101A88(s32 arg0);
void func_00101AF8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                   s32 s0, s32 s1, s32 s2, s32 s3, s32 s4, s32 s5, s64 s6, s32 s7, s32 s8, s32 s9);
u64 func_0024B010(u8 *arg0, u8 *arg1, u8 *arg2, s32 *arg3, s32 arg4);
u64 func_0024B110(u8 *arg0, u8 *arg1, u8 *arg2, s32 *arg3, s32 arg4);
s32 func_0024B7F0(s32 arg0);
s32 func_0024B210(s32 *arg0);
s32 func_0024AF50(s32 arg0);
void func_00101A60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void func_003FC848();
void func_0028B218(void);

#define W(p, o) (*(s32 *)((p) + (o)))
#define P(p, o) (*(u8 **)((p) + (o)))

s32 func_003FD990(s32 arg0) {
    s32 sp70;
    s32 buf[8];
    u8 *sp78;
    s32 sp74;
    u8 *s5, *A, *obj, *s0;
    s32 i, s2, s1, s6, s7, fp, s4off, soff;
    s64 s3;
    s32 v;

    sp70 = 1;
    func_003FBC08(arg0);
    func_00243968(0, 0, 0);
    for (;;) {
        func_002711A0();
        func_0028B090();
        func_0028BDA0();
        func_00297978(0, 0);
        func_002438E8();
        func_003FD610();
        func_003FC8B8();
        BattleSetup_Finish();
        func_003FD7C0(&sp70);
        func_002437E8();
        func_00271240();
        if (ColorFade_IsInDone()) {
            obj = D_0042A588;
            if (W(obj, 0x110) == 0) {
                if (func_0026EB60(obj + 0x60)) {
                    W(D_0042A588, 0x110) = 1;
                    obj = D_0042A588;
                    func_002493C0(W(obj, 8), 0x37A6, 0x3BBF, 0, W(obj, 0x104));
                    obj = D_0042A588;
                    if (W(obj, 0xFC) & 0x100) {
                        func_0026EB78(obj + 0x60, (s32)D_0042B850);
                    }
                }
            }
        }
        if (ColorFade_IsFadingOut()) {
            func_00101890();
            if (sp70 != 0) {
                func_00101498();
            }
            continue;
        }
        if (ColorFade_IsOutDone()) break;
        obj = D_0042A588;
        if (W(obj, 0xFC) & 2) {
            v = W(obj, 0x10C) - 1;
            W(obj, 0x10C) = v;
            if (v == -1) {
                func_00243A80(0, 0, 0);
            }
        } else {
            if (W(obj, 0x114) != 0) continue;
            if (W(obj, 0x23C) != 0) continue;
            func_003FD328(&sp70);
        }
    }

    if (sp70 == 0) {
        obj = D_0042A588;
        A = D_3876A4;
        W(A, 0x60) = W(A, 0x60) + W(obj, 0x184) / 100;
        obj = D_0042A588;
        A = D_3876A4;
        W(A, 0x80) = W(obj, 0x184) / 100;
        A = D_3876A4;
        W(A, 0x40) = W(A, 0x40) & 0xFFFF7FFF;
    } else {
        sp74 = 0;
        A = D_3876A4;
        obj = D_0042A588;
        s5 = P(D_3876A0, 0x74);
        sp78 = P(obj, 0x254) + ((W(A, 0x64) * 9 + W(A, 0x6C)) << 5);
        func_00101A10();
        *(s64 *)(D_3876A0 + 0x4D8) = 0;
        func_00101AB0(0, W(D_3876A4, 0x68), 0, 0);
        func_00101AB0(1, W(sp78, 0), 1, 0);
        do {
            if (sp74 == 0) {
                A = D_3876A4;
                if (sp74 < W(A, 0x68)) {
                    s6 = 0;
                    fp = 0;
                    soff = 0x40;
                    s7 = 0;
                    do {
                        A = D_3876A4;
                        if (W(A, 0x40) & (1 << s6)) {
                            v = W(A + soff, 0xC);
                            obj = D_0042A588;
                            s3 = func_0024B010(P(obj, 0x24C), P(obj, 0x250),
                                               D_387F2C + v * 34 + 0x1408, buf, 0x14);
                            v = func_0024B7F0(buf[0]);
                            s2 = W(s5, W(D_3876A4 + soff, 4) << 4) + v;
                        } else {
                            s3 = 0;
                            for (i = 0; i < 8; i++) buf[i] = 1;
                            s2 = W(s5, W(D_3876A4 + soff, 4) << 4);
                        }
                        A = D_3876A4;
                        s6 += 1;
                        v = W(A + soff, 4);
                        s1 = v * 9 + W(A + s7, 0x70);
                        s7 += 4;
                        v = func_00101A88(0);
                        {
                            s32 a0v = v + fp + 8;
                            u8 *e = D_3876A4 + soff;
                            fp += 0x58;
                            soff += 4;
                            func_00101AF8(a0v, s1, 0, 0, 0, 0, buf[0], buf[1],
                                          buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
                                          s3, s2, s2, W(s5, (W(e, 4) << 4) + 4));
                        }
                        A = D_3876A4;
                    } while (s6 < W(A, 0x68));
                }
            } else {
                obj = D_0042A588;
                W(obj, 0x120) = 0;
                if (W(sp78, 0) > 0) {
                    s6 = 0;
                    s7 = 0;
                    s4off = 4;
                    A = D_3876A4;
                    do {
                        s32 e = W(sp78, s4off);
                        s4off += 4;
                        obj = D_0042A588;
                        s0 = P(obj, 0x258) + e * 120;
                        s6 += 1;
                        s3 = func_0024B110(P(obj, 0x24C), P(obj, 0x250),
                                           s0 + W(A, 0x58) * 36 + 0x14, buf, 0x7D);
                        v = func_0024B7F0(buf[0]);
                        s2 = W(s5, W(s0, 0) << 4) + v;
                        v = func_0024B210(buf);
                        obj = D_0042A588;
                        W(obj, 0x120) = W(obj, 0x120) + v;
                        s1 = W(s0, 0) * 9 + W(s0, 8);
                        v = func_00101A88(1);
                        A = D_3876A4;
                        {
                            u8 *q = s0 + W(A, 0x58) * 36;
                            func_00101AF8(v + s7 + 8, s1, 0, W(q, 0xC), W(q, 0x10), W(s0, 4),
                                          buf[0], buf[1],
                                          buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
                                          s3, s2, s2, W(s5, (W(s0, 0) << 4) + 4));
                        }
                        s7 += 0x58;
                        A = D_3876A4;
                    } while (s6 < W(sp78, 0));
                }
            }
            sp74 += 1;
        } while (sp74 < 2);

        v = func_0024AF50(W(sp78, 0x1C));
        A = D_3876A4;
        obj = D_0042A588;
        {
            u8 *t = P(obj, 0x264);
            s32 t0 = (W(t + W(A, 0x64) * 56, 0xC) == 1) ? 2 : 0;
            func_00101A60(2, W(sp78, 0x18) - 1, 0, 1, t0, v);
        }
        A = D_3876A4;
        W(A, 0x40) = W(A, 0x40) | 0x8000;
        W(A, 0x84) = W(D_0042A588, 0x120);
    }
    func_003FC848();
    func_0028B218();
    return sp70;
}
