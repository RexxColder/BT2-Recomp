#include "common.h"

extern u8 *D_3876A4 __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));
extern u8 D_00425128[] __attribute__((section(".data")));
extern u8 D_00425138[] __attribute__((section(".data")));

extern s32 func_26EB70();
extern void func_26EAE0();
extern void func_26EA88();
extern void func_26EB78();
extern void func_297FE0();
extern void func_2493C0();
extern s32 func_1018B8();
extern void func_101890();
extern void func_003D1928();
extern s32 func_003D83D0();
extern s32 func_003D8458();
extern void EftShotFx_Update_2494A0();
extern s32 rand();

#define W(off) (*(s32 *)(o + (off)))
#define ST 0x3310
#define CTR 0x2C0
#define FLG 0x2BC
#define U16(p) (*(u16 *)(p))
#define CALL(a0, t0) func_2493C0((a0), sp[0], sp[1], 0, (t0))

/* 0x003D1BB0: animation/phase state machine on object o (state = o[0x3310], 1..302) */
void func_003D1BB0(u8 *o) {
    s32 sp[2];
    s32 st, v, a0, t0, idx;

    st = W(ST);
    if (st == 0) return;
    sp[0] = 0x3440;
    sp[1] = 0x3859;
    if ((u32)(st - 1) >= 0x12E) {
        func_101890(0);
        return;
    }

    switch (st) {
    case 1:
        if ((func_26EB70(o + 0x120) & 8) == 0) return;
        func_297FE0(2, 1, 0x40, 0x40, 1);
        goto inc;
    case 2:
        if ((func_26EB70(o + 0x120) & 0x200) == 0) return;
        func_26EAE0(o + 0xA8, 0x3C);
        func_26EA88(o + 0xA8);
        goto inc;
    case 3:
        W(FLG) = W(FLG) | 8;
        if (*(s32 *)(D_3876A4 + 0x18) & 0x20) {
            W(ST) = 9;
            return;
        }
        if (func_003D83D0(o)) {
            W(CTR) = 0x22;
            CALL(0, 0x22);
        } else if (func_003D8458(o)) {
            W(CTR) = 0x20;
            CALL(0, 0x20);
        } else {
            t0 = W(0x3320) * 2 + 0x1A;
            W(CTR) = t0;
            CALL(0, t0);
        }
        W(ST) = W(ST) + 1;
        goto tailA;
    case 4:
    case 8:
    case 10:
    case 12:
    case 14:
        if (func_1018B8() == 5) W(ST) = W(ST) + 1;
        goto tailA;
    case 5:
    case 7:
        W(CTR) = W(CTR) + 1;
        CALL(0, W(CTR));
        W(ST) = W(ST) + 1;
        goto tailA;
    case 6:
        if (func_1018B8() == 5) {
            if (func_003D83D0(o)) W(ST) = W(ST) + 1;
            else W(ST) = W(ST) + 3;
        }
        goto tailA;
    case 9:
        idx = U16(o + (W(0x3324) << 4) + 0x353E);
        func_003D1928(U16(o + (idx << 5) + 0x333E), &sp[0], &sp[1], o + CTR);
        CALL(0, W(CTR));
        W(ST) = W(ST) + 1;
        goto tailA;
    case 11:
        idx = U16(o + (W(0x3324) << 4) + 0x3540);
        func_003D1928(U16(o + (idx << 5) + 0x333E), &sp[0], &sp[1], o + CTR);
        t0 = W(CTR) + 1;
        CALL(0, t0);
        W(ST) = W(ST) + 1;
        goto tailA;
    case 13:
        if (func_003D83D0(o)) {
            W(CTR) = 0x25;
            CALL(0, 0x25);
        } else {
            v = rand();
            t0 = v % 14 + 0x26;
            W(CTR) = t0;
            CALL(0, t0);
        }
        W(ST) = W(ST) + 1;
        goto tailA;
    case 15:
        W(0x3308) = 0;
        W(FLG) = (W(FLG) & -9) | 2;
        W(CTR) = -1;
        W(ST) = 0;
        *(s32 *)(D_3876A4 + 0x18) = *(s32 *)(D_3876A4 + 0x18) | 0x20;
        return;
    case 51:
        W(FLG) = W(FLG) & -9;
        v = rand();
        t0 = (v & 1) + 3;
        W(CTR) = t0;
        CALL(W(0x1C), t0);
        W(ST) = W(ST) + 1;
        if ((D_003B0C34 & 0x4000) == 0) return;
        st = 0x35;
        goto L2684;
    case 52:
        if (func_1018B8() == 5) W(ST) = W(ST) + 1;
        if ((D_003B0C34 & 0x4000) == 0) return;
        st = 0x35;
        goto L2684;
    case 53:
        func_26EB78(o + 0xF8, D_00425128);
        func_26EAE0(o + 0x30, 0x3C);
        W(ST) = 0x65;
        return;
    case 101:
        W(FLG) = (W(FLG) & -9) | 0x100;
        if (func_003D8458(o)) {
            W(CTR) = 0x12;
            CALL(W(0x1C), 0x12);
        } else if (func_003D83D0(o)) {
            W(CTR) = 0x15;
            CALL(W(0x1C), 0x15);
        } else {
            v = W(0x3320);
            if (v == 0) {
                s32 m = *(s32 *)(D_3876A4 + 0x90);
                if (m == 1) {
                    W(CTR) = 7;
                } else if (m < 2) {
                    if (m == 0) W(CTR) = 5;
                } else if (m < 4) {
                    W(CTR) = 9;
                }
                CALL(W(0x1C), W(CTR));
            } else {
                t0 = v * 2 + v + 9;
                W(CTR) = t0;
                CALL(W(0x1C), t0);
            }
        }
        W(ST) = W(ST) + 1;
        if ((D_003B0C34 & 0x4000) == 0) return;
        st = 0x67;
        goto L2684;
    case 102:
        if (func_1018B8() == 5) goto inc;
        if ((D_003B0C34 & 0x4000) == 0) return;
        W(ST) = W(ST) + 1;
        func_297FE0(0, 1, 0x40, 0x40, 1);
        return;
    case 103:
        if (W(0x3320) == 0) {
            s32 c = W(CTR);
            W(CTR) = c + 1;
            if (*(s32 *)(D_3876A4 + 0x90) == 3) W(CTR) = c + 2;
        } else {
            v = rand();
            W(CTR) = W(CTR) + (v & 1) + 1;
        }
        CALL(W(0x1C), W(CTR));
        goto inc;
    case 104:
        if (func_1018B8() == 5) {
            W(ST) = 0;
            W(FLG) = W(FLG) & -0x101;
        }
        if ((D_003B0C34 & 0x4000) == 0) return;
        W(ST) = 0;
        func_297FE0(0, 1, 0x40, 0x40, 1);
        EftShotFx_Update_2494A0();
        W(FLG) = W(FLG) & -0x101;
        W(CTR) = -1;
        return;
    case 151:
        W(FLG) = W(FLG) | 8;
        W(CTR) = 0x18;
        CALL(0, 0x18);
        goto inc;
    case 152:
    case 154:
        if (func_1018B8() != 5) return;
        goto inc;
    case 153:
        idx = U16(o + (((W(0x3324) << 3) + W(0x2C8)) << 1) + 0x353E);
        func_003D1928(U16(o + (idx << 5) + 0x333E), &sp[0], &sp[1], o + CTR);
        t0 = W(CTR) + 1;
        CALL(W(0x1C), t0);
        goto inc;
    case 155:
        v = W(FLG);
        W(CTR) = -1;
        W(FLG) = v & -9;
        if (v & 0x10) W(FLG) = (v & -9) ^ 0x10;
        W(ST) = 0;
        if (W(FLG) & 0x4000) return;
        func_26EB78(o + 0x148, D_00425138);
        func_26EB78(o + 0xA8, D_00425138);
        func_26EAE0(o + 0xF8, 0x3C);
        func_26EAE0(o + 0x30, 0x3C);
        return;
    case 251:
        W(FLG) = W(FLG) & -9;
        W(CTR) = 0x34;
        CALL(W(0x1C), 0x34);
        W(ST) = W(ST) + 1;
        goto tailFD;
    case 252:
        if (func_1018B8() == 5) W(ST) = W(ST) + 1;
    tailFD:
        if ((D_003B0C34 & 0x4000) == 0) return;
        st = 0xFD;
        goto L2684;
    case 253:
        t0 = W(CTR) + 1;
        W(CTR) = t0;
        CALL(W(0x1C), t0);
        goto inc;
    case 254:
    case 302:
        if (D_003B0C34 & 0x4000) {
            func_297FE0(0, 1, 0x40, 0x40, 1);
        } else if (func_1018B8() != 5) {
            return;
        }
        W(ST) = 0;
        W(0x3308) = 0;
        return;
    case 301:
        W(FLG) = W(FLG) & -9;
        W(CTR) = 0x34;
        CALL(W(0x1C), 0x34);
        goto inc;
    default:
        func_101890(1);
        return;
    }

tailA:
    if ((D_003B0C34 & 0x4000) == 0) return;
    if ((W(FLG) & 0x200) == 0) return;
    st = 0xF;
L2684:
    W(ST) = st;
    func_297FE0(0, 1, 0x40, 0x40, 1);
    return;
inc:
    W(ST) = W(ST) + 1;
}
