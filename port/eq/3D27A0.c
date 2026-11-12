#include "common.h"

extern s32 func_003D83D0(u8 *arg0);
extern s32 func_003D8458(u8 *arg0);
extern void func_003D1928(s32 idx, s32 *o1, s32 *o2, s32 *o3);
extern s32 func_002493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 func_001018B8(void);
extern s32 func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_0026EAE0(s32 arg0, s32 arg1);
extern void func_0026EB78(s32 arg0, s32 arg1);
extern s32 rand(void);
extern void EftShotFx_Update_2494A0(void);
extern void func_00101890(void);

extern u8 *D_3876A4 __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));
extern u8 D_00425138[];

#define W(p, o) (*(s32 *)((p) + (o)))
#define H(p, o) (*(u16 *)((p) + (o)))

/* shared tails */
static void fade_to(u8 *S, s32 st) {
    W(S, 0x3310) = st;
    func_00297FE0(0, 1, 0x40, 0x40, 1);
}

/* states 1..10: A-button + flag 0x200 -> state 0xB with fade */
static void tailA(u8 *S) {
    if (!(D_003B0C34 & 0x4000)) return;
    if (!(W(S, 0x2BC) & 0x200)) return;
    fade_to(S, 0xB);
}

static void tailB(u8 *S, s32 st) {
    if (!(D_003B0C34 & 0x4000)) return;
    fade_to(S, st);
}

void func_003D27A0(u8 *S) {
    u8 sp[0x30];
    s32 st, t0, r, v, m;

    st = W(S, 0x3310);
    if (st == 0) return;
    W(sp, 0) = 0x35B4;
    W(sp, 4) = 0x39CD;
    if ((u32)(st - 1) >= 0x12E) {
        func_00101890();
        return;
    }
    switch (st) {
    case 1:
        W(S, 0x2BC) |= 8;
        if (W(D_3876A4, 0x18) & 0x20) {
            W(S, 0x3310) = 5;
            return;
        }
        if (func_003D83D0(S)) {
            W(S, 0x2C0) = 0x25;
            func_002493C0(0, W(sp, 0), W(sp, 4), 0, 0x25);
        } else if (func_003D8458(S)) {
            W(S, 0x2C0) = 0x23;
            func_002493C0(0, W(sp, 0), W(sp, 4), 0, 0x23);
        } else {
            t0 = W(S, 0x3320) * 2 + 0x1D;
            W(S, 0x2C0) = t0;
            func_002493C0(0, W(sp, 0), W(sp, 4), 0, t0);
        }
        W(S, 0x3310) = W(S, 0x3310) + 1;
        tailA(S);
        return;
    case 2:
    case 4:
    case 6:
    case 8:
    case 10:
        if (func_001018B8() == 5) W(S, 0x3310) = W(S, 0x3310) + 1;
        tailA(S);
        return;
    case 3:
        t0 = W(S, 0x2C0) + 1;
        W(S, 0x2C0) = t0;
        func_002493C0(0, W(sp, 0), W(sp, 4), 0, t0);
        W(S, 0x3310) = W(S, 0x3310) + 1;
        tailA(S);
        return;
    case 5:
        func_003D1928(H(S + (H(S, (W(S, 0x3324) << 4) + 0x353E) << 5), 0x333E), (s32 *)sp, (s32 *)(sp + 4),
                      (s32 *)(S + 0x2C0));
        func_002493C0(0, W(sp, 0), W(sp, 4), 0, W(S, 0x2C0));
        W(S, 0x3310) = W(S, 0x3310) + 1;
        tailA(S);
        return;
    case 7:
        func_003D1928(H(S + (H(S, (W(S, 0x3324) << 4) + 0x3540) << 5), 0x333E), (s32 *)sp, (s32 *)(sp + 4),
                      (s32 *)(S + 0x2C0));
        func_002493C0(0, W(sp, 0), W(sp, 4), 0, W(S, 0x2C0) + 1);
        W(S, 0x3310) = W(S, 0x3310) + 1;
        tailA(S);
        return;
    case 9:
        if (func_003D83D0(S)) {
            W(S, 0x2C0) = 0x27;
            func_002493C0(0, W(sp, 0), W(sp, 4), 0, 0x27);
        } else {
            r = rand();
            r = r % 16;
            t0 = r + 0x28;
            W(S, 0x2C0) = t0;
            if (t0 < 0x36) {
                func_002493C0(0, W(sp, 0), W(sp, 4), 0, t0);
            } else {
                t0 = r - 12;
                W(S, 0x2C0) = t0;
                func_002493C0(0, 0x3672, 0x3A8B, 0, t0);
            }
        }
        W(S, 0x3310) = W(S, 0x3310) + 1;
        tailA(S);
        return;
    case 11:
        W(S, 0x3308) = 0;
        W(S, 0x2C0) = -1;
        W(S, 0x3310) = 0;
        W(S, 0x2BC) = (W(S, 0x2BC) & ~8) | 2;
        W(D_3876A4, 0x18) |= 0x20;
        return;
    case 51:
        W(S, 0x2BC) &= ~8;
        r = rand();
        if (r & 1) {
            W(S, 0x2C0) = 2;
            W(S, 0x3310) = W(S, 0x3310) + 1;
        } else {
            W(S, 0x2C0) = 4;
            W(S, 0x3310) = 0x36;
        }
        func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, W(S, 0x2C0));
        tailB(S, 0x37);
        return;
    case 52:
    case 54:
        if (func_001018B8() == 5) W(S, 0x3310) = W(S, 0x3310) + 1;
        tailB(S, 0x37);
        return;
    case 53:
        t0 = W(S, 0x2C0) + 1;
        W(S, 0x2C0) = t0;
        func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, t0);
        W(S, 0x3310) = W(S, 0x3310) + 1;
        tailB(S, 0x37);
        return;
    case 55:
        func_0026EAE0((s32)(S + 0x30), 0x3C);
        W(S, 0x3310) = 0x65;
        return;
    case 101:
        W(S, 0x2BC) = (W(S, 0x2BC) & ~8) | 0x100;
        if (func_003D8458(S)) {
            W(S, 0x2C0) = 0x12;
            func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, 0x12);
        } else if (func_003D83D0(S)) {
            W(S, 0x2C0) = 0x15;
            func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, 0x15);
        } else {
            v = W(S, 0x3320);
            if (v == 0) {
                m = W(D_3876A4, 0x90);
                if (m == 1) {
                    W(S, 0x2C0) = 7;
                } else if (m < 2) {
                    if (m == 0) W(S, 0x2C0) = 5;
                } else if (m < 4) {
                    W(S, 0x2C0) = 9;
                }
                func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, W(S, 0x2C0));
            } else {
                t0 = v * 3 + 9;
                W(S, 0x2C0) = t0;
                func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, t0);
            }
        }
        W(S, 0x3310) = W(S, 0x3310) + 1;
        tailB(S, 0x67);
        return;
    case 102:
        if (func_001018B8() == 5) {
            W(S, 0x3310) = W(S, 0x3310) + 1;
            return;
        }
        if (!(D_003B0C34 & 0x4000)) return;
        W(S, 0x3310) = W(S, 0x3310) + 1;
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        return;
    case 103:
        if (W(S, 0x3320) == 0) {
            m = W(S, 0x2C0);
            W(S, 0x2C0) = m + 1;
            if (W(D_3876A4, 0x90) == 3) W(S, 0x2C0) = m + 2;
        } else {
            r = rand();
            W(S, 0x2C0) = W(S, 0x2C0) + (r & 1) + 1;
        }
        func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, W(S, 0x2C0));
        W(S, 0x3310) = W(S, 0x3310) + 1;
        return;
    case 104:
        if (func_001018B8() == 5) {
            W(S, 0x3310) = 0;
            W(S, 0x2BC) &= ~0x100;
        }
        if (!(D_003B0C34 & 0x4000)) return;
        W(S, 0x3310) = 0;
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        EftShotFx_Update_2494A0();
        W(S, 0x2BC) &= ~0x100;
        W(S, 0x2C0) = -1;
        return;
    case 151:
        W(S, 0x2C0) = 0x18;
        W(S, 0x2BC) |= 8;
        func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, 0x18);
        W(S, 0x3310) = W(S, 0x3310) + 1;
        return;
    case 152:
    case 154:
        if (func_001018B8() == 5) W(S, 0x3310) = W(S, 0x3310) + 1;
        return;
    case 153:
        func_003D1928(H(S + (H(S, ((W(S, 0x3324) * 8 + W(S, 0x2C8)) << 1) + 0x353E) << 5), 0x333E), (s32 *)sp,
                      (s32 *)(sp + 4), (s32 *)(S + 0x2C0));
        func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, W(S, 0x2C0) + 1);
        W(S, 0x3310) = W(S, 0x3310) + 1;
        return;
    case 155:
        v = W(S, 0x2BC);
        W(S, 0x2C0) = -1;
        W(S, 0x2BC) = v & ~8;
        if (v & 0x10) W(S, 0x2BC) = (v & ~8) ^ 0x10;
        W(S, 0x3310) = 0;
        if (W(S, 0x2BC) & 0x4000) return;
        func_0026EB78((s32)(S + 0x148), (s32)D_00425138);
        func_0026EB78((s32)(S + 0xA8), (s32)D_00425138);
        func_0026EAE0((s32)(S + 0xF8), 0x3C);
        func_0026EAE0((s32)(S + 0x30), 0x3C);
        return;
    case 251:
        W(S, 0x2BC) &= ~8;
        W(S, 0x2C0) = 0x36;
        func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, 0x36);
        W(S, 0x3310) = W(S, 0x3310) + 1;
        tailB(S, 0xFD);
        return;
    case 252:
        if (func_001018B8() == 5) W(S, 0x3310) = W(S, 0x3310) + 1;
        tailB(S, 0xFD);
        return;
    case 253:
        t0 = W(S, 0x2C0) + 1;
        W(S, 0x2C0) = t0;
        func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, t0);
        W(S, 0x3310) = W(S, 0x3310) + 1;
        return;
    case 254:
    case 302:
        if (D_003B0C34 & 0x4000) {
            func_00297FE0(0, 1, 0x40, 0x40, 1);
        } else if (func_001018B8() != 5) {
            return;
        }
        W(S, 0x3310) = 0;
        W(S, 0x3308) = 0;
        return;
    case 301:
        W(S, 0x2BC) &= ~8;
        W(S, 0x2C0) = 0x36;
        func_002493C0(W(S, 0x1C), W(sp, 0), W(sp, 4), 0, 0x36);
        W(S, 0x3310) = W(S, 0x3310) + 1;
        return;
    default:
        func_00101890();
        return;
    }
}
