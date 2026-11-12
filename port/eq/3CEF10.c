#include "common.h"

extern u8 *D_0042311C __attribute__((section(".data")));
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
void func_29C810(s32 arg0);
void func_29C7E0(s32 arg0);
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
extern s32 McCard_WriteSave();

#define G (D_0042311C)
#define W(off) (*(s32 *)(G + (off)))
#define PORT(off) (*(s32 *)(gMcCardPort + (off)))
#define O_ST 0x150
#define O_CNT 0x154
#define O_MSG 0x158
#define O_TMR 0x15C
#define O_BUF 0x160
#define O_FLG 0x118
#define O_X 0x124

/* 0x003CEF10: memory-card flow state machine. state = G[O_ST] (0 = idle), G[O_MSG] = message id for func_29C800 */
void func_003CEF10(void) {
    s32 st, t, r, v1, x;

    st = W(O_ST);
    if (st == 0) return;
    if ((u32)(st - 1) >= 0x17) goto fin;

    switch (st) {
    case 1:
        func_29C7C0(0);
        v1 = 5;
        goto L79C;
    case 2:
        func_29C7C0(0);
        v1 = 7;
        goto L79C;
    case 3:
        func_29C7C0(0);
        v1 = 0x10;
        goto L79C;
    case 4:
        goto fin;
    case 5:
        func_29C7C0(0);
        W(O_MSG) = 0x22;
        r = func_0028A578(0, 1);
        if (r == 0) {
            if (McCard_IsFatalError(D_003B0AA8) == 0) goto fin;
            v1 = 1;
            goto L998;
        }
        v1 = 0xC;
        goto L998;
    case 6:
        func_29C7C0(0);
        func_29C550(1);
        W(O_ST) = 7;
        goto fin;
    case 7:
        func_29C7C0(0);
        func_29C640(0);
        r = func_29C830();
        if (r == 0) goto fin;
        W(O_ST) = 0;
        W(O_FLG) = W(O_FLG) | 1;
        W(O_FLG) = W(O_FLG) | 2;
        W(O_X) = 0xF;
        goto fin;
    case 8:
        func_29C550(0);
        func_29C820(1);
        func_29C7E0(1);
        func_29C810(0);
        W(O_TMR) = 0;
        W(O_ST) = 9;
        goto fin;
    case 9:
        func_29C7C0(1);
        W(O_MSG) = 0x1C;
        x = W(O_TMR);
        if (x > 0) {
            t = W(O_CNT) - 1;
            W(O_CNT) = t;
            if (t >= 0) goto fin;
            v1 = 0xA;
            goto L8B8;
        }
        if (x >= 0) goto LA98;
        goto L768;
    case 10:
        func_29C7C0(0);
        t = W(O_CNT) - 1;
        W(O_CNT) = t;
        if (t < 0) goto LF0F8;
        W(O_MSG) = 0x22;
        r = McCard_GetInfo(0);
        if (r == 0) goto fin;
        if (W(O_CNT) > 0) goto fin;
        if (PORT(0xC) != 2) {
            W(O_ST) = 1;
            W(O_CNT) = 0x78;
            goto fin;
        }
        if (McCard_IsFatalError(PORT(8)) != 0) {
            v1 = 1;
            goto L998;
        }
        if (PORT(8) != 0) {
            u8 *p = D_3876A4;
            x = *(s32 *)(p + 0x18);
            if (x & 4) {
                *(s32 *)(p + 0x18) = x ^ 4;
                goto fin;
            }
            McCard_Probe(0);
            if (McCard_IsFatalError(PORT(8)) == 0) {
                r = 0x14;
                goto L944;
            }
            v1 = 1;
            goto L998;
        }
        if (PORT(0x14) != 0) goto fin;
        goto L940;
    case 11:
        func_29C7C0(1);
        W(O_MSG) = 0x15;
        McCard_Probe(0);
        if (McCard_IsFatalError(D_003B0AA8) != 0) {
            W(O_ST) = 1;
            W(O_CNT) = 0x78;
            goto LA88;
        }
        x = W(O_TMR);
        if (x <= 0) goto LA70;
        t = W(O_CNT) - 1;
        W(O_CNT) = t;
        if (t >= 0) goto fin;
        W(O_ST) = 0xD;
        W(O_CNT) = 0x78;
        goto LA88;
    case 12:
        func_29C7C0(0);
        t = W(O_CNT) - 1;
        W(O_CNT) = t;
        if (t < 0) {
            W(O_MSG) = 0x1D;
            r = McCard_CreateSave(0, G + O_BUF);
            if (r != 0) {
                W(O_ST) = 0xD;
                goto fin;
            }
            if (D_003B0AA8 >= 0) goto fin;
            v1 = 0xF;
            goto L998;
        }
        W(O_MSG) = 0x1D;
        r = McCard_GetInfo(0);
        if (r == 0) goto fin;
        if (W(O_CNT) > 0) goto fin;
        if (McCard_IsFatalError(D_003B0AA8) == 0) goto fin;
        v1 = 0xF;
        goto L998;
    case 13:
        func_29C7C0(0);
        t = W(O_CNT) - 1;
        W(O_CNT) = t;
        if (t < 0) {
            W(O_MSG) = 0x1D;
            r = McCard_WriteSave(0, D_387F2C, 0x4000, G + O_BUF);
            if (r != 0) {
                v1 = 0xE;
                goto L998;
            }
            if (D_003B0AA8 >= 0) goto fin;
            v1 = 0xF;
            goto L998;
        }
        W(O_MSG) = 0x1D;
        r = McCard_GetInfo(0);
        if (r == 0) goto fin;
        if (W(O_CNT) > 0) goto fin;
        if (McCard_IsFatalError(D_003B0AA8) == 0) goto fin;
        v1 = 0xF;
        goto L998;
    case 14:
        func_29C7C0(0);
        t = W(O_CNT) - 1;
        W(O_CNT) = t;
        if (t < 0) {
            W(O_ST) = 6;
            goto fin;
        }
        W(O_MSG) = 0x1E;
        goto fin;
    case 15:
        func_29C7C0(0);
        v1 = 0x1F;
        goto L79C;
    case 16:
        func_29C7C0(1);
        W(O_MSG) = 0xD;
        McCard_Probe(0);
        if (McCard_IsFatalError(D_003B0AA8) != 0) {
            func_29C7C0(0);
            W(O_MSG) = 5;
            W(O_ST) = 1;
            W(O_CNT) = 0x78;
            W(O_TMR) = 0;
            goto fin;
        }
        x = W(O_TMR);
        if (x > 0) {
            t = W(O_CNT) - 1;
            W(O_CNT) = t;
            if (t >= 0) goto fin;
            W(O_ST) = 0x11;
            W(O_CNT) = 0x78;
            goto LA88;
        }
        if (x >= 0) goto LA98;
        goto L768;
    case 17:
        func_29C7C0(0);
        t = W(O_CNT) - 1;
        W(O_CNT) = t;
        if (t < 0) {
            W(O_MSG) = 0xC;
            r = McCard_Format(0);
            if (r != 0) {
                v1 = 0x12;
                goto L998;
            }
            if (D_003B0AA8 >= 0) goto fin;
            v1 = 0x13;
            goto L998;
        }
        W(O_MSG) = 0xC;
        r = McCard_GetInfo(0);
        if (r == 0) goto fin;
        if (W(O_CNT) > 0) goto fin;
        if (McCard_IsFatalError(D_003B0AA8) == 0) goto fin;
        v1 = 0x13;
        goto L998;
    case 18:
        func_29C7C0(0);
        McCard_Probe(0);
        if (McCard_IsFatalError(D_003B0AA8) != 0) {
            W(O_ST) = 1;
            W(O_CNT) = 0x78;
            W(O_TMR) = 0;
            goto fin;
        }
        t = W(O_CNT) - 1;
        W(O_CNT) = t;
        if (t < 0) {
            W(O_ST) = 0xC;
            W(O_CNT) = 0x78;
            goto fin;
        }
        W(O_MSG) = 0xE;
        goto fin;
    case 19:
        func_29C7C0(0);
        v1 = 0xF;
        goto L79C;
    case 20:
        func_29C7C0(1);
        W(O_MSG) = 0x18;
        x = W(O_TMR);
        if (x > 0) {
            t = W(O_CNT) - 1;
            W(O_CNT) = t;
            if (t >= 0) goto fin;
            W(O_ST) = 0xA;
            W(O_CNT) = 0x78;
            W(O_TMR) = 0;
            McCard_Probe(0);
            goto fin;
        }
        if (x < -1) goto L768;
        goto LA98;
    case 21:
        func_29C7C0(1);
        W(O_MSG) = 0x2F;
        x = W(O_TMR);
        if (x > 0) {
            W(O_ST) = 6;
            goto LA88;
        }
        if (x >= 0) goto LA98;
        t = W(O_CNT) - 1;
        W(O_CNT) = t;
        if (t >= 0) goto fin;
        func_29C820(1);
        v1 = 9;
        goto L8B8;
    case 22:
        func_29C7C0(0);
        W(O_MSG) = 0x22;
        r = func_0028A790(0, G + O_BUF);
        if (r != 0) {
            x = PORT(0x1C);
            if (x <= 0) {
                v1 = 0xB;
                goto LF9BC;
            }
            if (PORT(0x10) >= x) {
                v1 = 0x17;
                goto LF9BC;
            }
            v1 = 3;
            goto L998;
        }
        if (PORT(0xC) != 2) {
            v1 = 1;
            goto L998;
        }
        if (PORT(0x14) == 0) goto L940;
        if (McCard_IsFatalError(PORT(8)) == 0) goto fin;
        v1 = 1;
        goto L998;
    case 23:
        func_29C7C0(1);
        W(O_MSG) = 0x15;
        McCard_Probe(0);
        if (McCard_IsFatalError(D_003B0AA8) != 0) {
            W(O_ST) = 1;
            W(O_CNT) = 0x78;
            goto LA88;
        }
        x = W(O_TMR);
        if (x <= 0) goto LA70;
        t = W(O_CNT) - 1;
        W(O_CNT) = t;
        if (t >= 0) goto fin;
        W(O_ST) = 0xC;
        W(O_CNT) = 0x78;
        goto LA88;
    }
    goto fin;

LF0F8:
    W(O_MSG) = 0x22;
    r = func_00289C98(0, G + O_BUF);
    if (r != 0) {
        func_288348();
        W(O_ST) = 0x16;
        goto fin;
    }
    if (PORT(0xC) != 2) {
        v1 = 1;
        goto L998;
    }
    if (PORT(0x14) == 0) goto L940;
    if (McCard_IsFatalError(PORT(8)) != 0) {
        v1 = 1;
        goto L998;
    }
    if (PORT(8) >= 0) goto fin;
    if (PORT(0x10) >= 0x4B) {
        W(O_ST) = 5;
        goto fin;
    }
    v1 = 3;
    goto L998;

LA70:
    if (x >= 0) goto LA98;
    func_29C820(1);
    W(O_ST) = 0x15;
LA88:
    W(O_TMR) = 0;
    goto fin;

LA98:
    W(O_TMR) = func_29C640(0);
    W(O_CNT) = 0xC;
    goto fin;

L79C:
    W(O_MSG) = v1;
    if ((D_003B0C34 & 0x4008) == 0) goto fin;
    func_297FE0(0, 1, 0x40, 0x40, 1);
L768:
    func_29C820(1);
    W(O_ST) = 0x15;
    W(O_TMR) = 0;
    goto fin;

L8B8:
    W(O_ST) = v1;
    W(O_CNT) = 0x78;
    W(O_TMR) = 0;
    func_288348();
    goto fin;

L940:
    r = 0x10;
L944:
    W(O_ST) = r;
    func_29C820(1);
    goto fin;

L998:
    W(O_ST) = v1;
    W(O_CNT) = 0x78;
    goto fin;

LF9BC:
    W(O_ST) = v1;
    W(O_CNT) = 0x78;
    func_29C820(1);

fin:
    func_29C800(W(O_MSG));
    func_29C1E8(1);
}
