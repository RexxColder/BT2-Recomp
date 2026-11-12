#include "common.h"

extern u8 *D_00421CF4 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));
extern s32 D_003B0AA8 __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));
extern u8 gMcCardPort[] __attribute__((section(".data")));

void func_29C7C0(s32 arg0);
void func_29C800(s32 arg0);
void func_29C1E8(s32 arg0);
s32 func_29C640(s32 arg0);
s32 func_29C830(void);
void func_29C820(s32 arg0);
void func_29C550(s32 arg0);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_288348(void);
s32 func_00289C98(s32 port, u8 *path);
s32 func_0028A578(s32 arg0, s32 arg1);
extern s32 func_0028A790();
extern s32 McCard_GetInfo();
extern s32 McCard_IsFatalError();
extern s32 McCard_Probe();
extern s32 McCard_Format();
extern s32 McCard_CreateSave();
extern s32 McCard_Checksum();
extern s32 McCard_WriteSave();

#define G (D_00421CF4)
#define W(off) (*(s32 *)(G + (off)))
#define PORT(off) (*(s32 *)(gMcCardPort + (off)))

/* 0x003C5710: memory-card flow state machine. state = G[0x218] (0 = idle, 4..24 jump table), G[0x214] = message id for
 * func_29C800, G[0x21C] = countdown, G[0x1C4] = pending-op flag. All paths end with func_29C800(G[0x214]); func_29C1E8(1). */
void func_003C5710(void) {
    s32 st, t, c, r, v1;

    st = W(0x218);
    if (st == 0) return;
    if ((u32)(st - 4) > 0x14) goto fin;

    switch (st) {
    case 4:
        func_29C7C0(0);
        v1 = 5;
        goto L5F1C;
    case 5:
        func_29C7C0(0);
        v1 = 0x10;
        goto L5F1C;
    case 16:
        func_29C7C0(0);
        v1 = 0x1F;
        goto L5F1C;
    case 20:
        func_29C7C0(0);
        v1 = 0xF;
        goto L5F1C;
    case 6:
        goto fin;
    case 7:
        func_29C7C0(0);
        W(0x214) = 0x22;
        r = func_0028A578(0, 1);
        if (r == 0) {
            if (McCard_IsFatalError(D_003B0AA8) == 0) goto fin;
            v1 = 4;
            goto L6108;
        }
        W(0x218) = 0xD;
        W(0x21C) = 0x78;
        goto fin;
    case 8:
        func_29C7C0(0);
        func_29C550(1);
        W(0x218) = 9;
        goto fin;
    case 9:
        func_29C7C0(0);
        func_29C640(0);
        if (func_29C830() == 0) goto fin;
        W(0x218) = 0;
        W(0x1FC) = W(0x1FC) | 1;
        W(0x1FC) = W(0x1FC) | 2;
        W(0x200) = 0xF;
        goto fin;
    case 10:
        func_29C7C0(1);
        W(0x214) = 0x1C;
        c = W(0x1C4);
        if (c <= 0) goto L61D8;
        t = W(0x21C) - 1;
        W(0x21C) = t;
        if (t >= 0) goto fin;
        W(0x218) = 0xB;
        W(0x21C) = 0x78;
        goto L5FC0;
    case 11:
        func_29C7C0(0);
        t = W(0x21C) - 1;
        W(0x21C) = t;
        if (t < 0) {
            W(0x214) = 0x22;
            r = func_00289C98(0, G + 0x220);
            if (r != 0) {
                func_288348();
                W(0x218) = 0x17;
                goto fin;
            }
            if (PORT(0xC) != 2) {
                v1 = 4;
                goto L5D3C;
            }
            if (PORT(0x14) == 0) goto L60B0;
            if (McCard_IsFatalError(PORT(8)) != 0) {
                v1 = 4;
                goto L5D3C;
            }
            if (PORT(8) >= 0) goto fin;
            if (PORT(0x10) < 0x4B) {
                v1 = 5;
                goto L5D3C;
            }
            W(0x218) = 7;
            goto fin;
        }
        W(0x214) = 0x22;
        r = McCard_GetInfo(0);
        if (r == 0) goto fin;
        if (W(0x21C) > 0) goto fin;
        if (PORT(0xC) != 2) {
            W(0x218) = 4;
            W(0x21C) = 0xB4;
            goto fin;
        }
        if (McCard_IsFatalError(PORT(8)) != 0) {
            v1 = 4;
            goto L5D3C;
        }
        if (PORT(8) != 0) {
            if (*(s32 *)(D_3876A4 + 0x18) & 4) {
                *(s32 *)(D_3876A4 + 0x18) = *(s32 *)(D_3876A4 + 0x18) ^ 4;
                goto fin;
            }
            McCard_Probe(0);
            if (McCard_IsFatalError(PORT(8)) != 0) {
                v1 = 4;
                goto L5D3C;
            }
            func_29C820(1);
            W(0x218) = 0x15;
            goto fin;
        }
        if (PORT(0x14) != 0) goto fin;
    L60B0:
        func_29C820(1);
        W(0x218) = 0x11;
        goto fin;
    case 12:
        func_29C7C0(1);
        W(0x214) = 0x15;
        McCard_Probe(0);
        if (McCard_IsFatalError(D_003B0AA8) != 0) {
            v1 = 4;
            c = 0xB4;
            goto L61BC;
        }
        c = W(0x1C4);
        if (c <= 0) goto L61D8;
        t = W(0x21C) - 1;
        W(0x21C) = t;
        if (t >= 0) goto fin;
        v1 = 0xE;
        goto L61B8;
    case 13:
        func_29C7C0(0);
        t = W(0x21C) - 1;
        W(0x21C) = t;
        if (t < 0) {
            W(0x214) = 0x1D;
            r = McCard_CreateSave(0, G + 0x220);
            if (r != 0) {
                W(0x218) = 0xE;
                goto fin;
            }
            if (D_003B0AA8 >= 0) goto fin;
            v1 = 0x10;
            goto L6108;
        }
        W(0x214) = 0x1D;
        r = McCard_GetInfo(0);
        if (r == 0) goto fin;
        if (W(0x21C) > 0) goto fin;
        if (McCard_IsFatalError(D_003B0AA8) == 0) goto fin;
        v1 = 0x10;
        goto L6108;
    case 14:
        func_29C7C0(0);
        t = W(0x21C) - 1;
        W(0x21C) = t;
        if (t < 0) {
            W(0x214) = 0x1D;
            McCard_Checksum(D_387F2C, 0x4000, 1);
            r = McCard_WriteSave(0, D_387F2C, 0x4000, G + 0x220);
            if (r != 0) {
                func_297FE0(0, 6, 0x40, 0x40, 1);
                v1 = 0xF;
                goto L5D3C;
            }
            if (D_003B0AA8 >= 0) goto fin;
            v1 = 0x10;
            goto L5D3C;
        }
        W(0x214) = 0x1D;
        r = McCard_GetInfo(0);
        if (r == 0) goto fin;
        if (W(0x21C) > 0) goto fin;
        if (McCard_IsFatalError(D_003B0AA8) == 0) goto fin;
        v1 = 0x10;
        goto L5D3C;
    case 15:
        func_29C7C0(0);
        *(s32 *)(D_3876A4 + 0x18) = *(s32 *)(D_3876A4 + 0x18) & -2;
        W(0x214) = 0x1E;
        if ((D_003B0C34 & 0x4008) == 0) goto fin;
        func_297FE0(0, 1, 0x40, 0x40, 1);
        W(0x218) = 8;
        goto fin;
    case 17:
        func_29C7C0(1);
        W(0x214) = 0xD;
        McCard_Probe(0);
        if (McCard_IsFatalError(D_003B0AA8) != 0) {
            func_29C7C0(0);
            W(0x214) = 5;
            W(0x218) = 4;
            W(0x21C) = 0xB4;
            W(0x1C4) = 0;
            goto fin;
        }
        c = W(0x1C4);
        if (c <= 0) goto L61D8;
        t = W(0x21C) - 1;
        W(0x21C) = t;
        if (t >= 0) goto fin;
        v1 = 0x12;
        goto L61B8;
    case 18:
        func_29C7C0(0);
        t = W(0x21C) - 1;
        W(0x21C) = t;
        if (t < 0) {
            W(0x214) = 0xC;
            r = McCard_Format(0);
            if (r != 0) {
                v1 = 0x13;
                goto L6108;
            }
            if (D_003B0AA8 >= 0) goto fin;
            v1 = 0x14;
            goto L6108;
        }
        W(0x214) = 0xC;
        r = McCard_GetInfo(0);
        if (r == 0) goto fin;
        if (W(0x21C) > 0) goto fin;
        if (McCard_IsFatalError(D_003B0AA8) == 0) goto fin;
        v1 = 0x14;
        goto L6108;
    case 19:
        func_29C7C0(0);
        McCard_Probe(0);
        if (McCard_IsFatalError(D_003B0AA8) != 0) {
            W(0x218) = 4;
            W(0x21C) = 0xB4;
            W(0x1C4) = 0;
            goto fin;
        }
        t = W(0x21C) - 1;
        W(0x21C) = t;
        if (t < 0) {
            W(0x218) = 0xD;
            W(0x21C) = 0x78;
            goto fin;
        }
        W(0x214) = 0xE;
        goto fin;
    case 21:
        func_29C7C0(1);
        W(0x214) = 0x18;
        c = W(0x1C4);
        if (c > 0) {
            t = W(0x21C) - 1;
            W(0x21C) = t;
            if (t >= 0) goto fin;
            W(0x218) = 0xB;
            W(0x21C) = 0x78;
            W(0x1C4) = 0;
            McCard_Probe(0);
            goto fin;
        }
        if (c < -1) goto L61E0;
        goto L6200;
    case 22:
        func_29C7C0(1);
        W(0x214) = 0x2F;
        c = W(0x1C4);
        if (c > 0) {
            t = W(0x21C) - 1;
            W(0x21C) = t;
            if (t >= 0) goto fin;
            W(0x218) = 8;
            W(0x1C4) = 0;
            goto fin;
        }
        if (!(c < -1)) goto L6200;
        W(0x218) = 0xA;
        W(0x21C) = 0x78;
        goto L5FC0;
    case 23:
        func_29C7C0(0);
        W(0x214) = 0x22;
        r = func_0028A790(0, G + 0x220);
        if (r != 0) {
            c = PORT(0x1C);
            if (c <= 0) {
                v1 = 0xC;
            } else if (PORT(0x10) >= c) {
                v1 = 0x18;
            } else {
                v1 = 5;
                goto L6108;
            }
            W(0x218) = v1;
            W(0x21C) = 0x78;
            func_29C820(1);
            goto fin;
        }
        if (PORT(0xC) != 2) {
            v1 = 4;
            goto L6108;
        }
        if (PORT(0x14) == 0) {
            func_29C820(1);
            W(0x218) = 0x11;
            goto fin;
        }
        if (McCard_IsFatalError(PORT(8)) == 0) goto fin;
        v1 = 4;
        goto L6108;
    case 24:
        func_29C7C0(1);
        W(0x214) = 0x15;
        McCard_Probe(0);
        if (McCard_IsFatalError(D_003B0AA8) != 0) {
            v1 = 4;
            c = 0xB4;
            goto L61BC;
        }
        c = W(0x1C4);
        if (c <= 0) goto L61D8;
        t = W(0x21C) - 1;
        W(0x21C) = t;
        if (t >= 0) goto fin;
        v1 = 0xD;
        goto L61B8;
    default:
        goto fin;
    }

L5F1C:
    W(0x214) = v1;
    if ((D_003B0C34 & 0x4008) == 0) goto fin;
    func_297FE0(0, 1, 0x40, 0x40, 1);
    func_29C820(1);
    W(0x218) = 0x16;
    goto fin;
L5D3C:
L6108:
    W(0x218) = v1;
    W(0x21C) = 0xB4;
    goto fin;
L61B8:
    c = 0x78;
L61BC:
    W(0x218) = v1;
    W(0x21C) = c;
    W(0x1C4) = 0;
    goto fin;
L61D8:
    if (c >= 0) goto L6200;
L61E0:
    func_29C820(1);
    W(0x218) = 0x16;
    W(0x1C4) = 0;
    goto fin;
L6200:
    r = func_29C640(0);
    W(0x1C4) = r;
    W(0x21C) = 0xC;
    goto fin;
L5FC0:
    W(0x1C4) = 0;
    func_288348();
fin:
    func_29C800(W(0x214));
    func_29C1E8(1);
}
