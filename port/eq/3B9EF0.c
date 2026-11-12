#include "common.h"

void *memcpy(void *, const void *, unsigned long);

extern u8 *D_004213B0;
extern u8 *D_003876A4;
extern u8 *D_00387F2C;
extern u8 gMcCardPort[] __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));
extern s32 func_0029C7C0();
extern s32 func_0029C640();
extern s32 func_0029C800();
extern s32 func_0029C1E8();
extern s32 func_0029C550();
extern s32 func_0029C830();
extern s32 func_0029C820();
extern s32 func_00289C98();
extern s32 func_0028A578();
extern s32 func_0028A790();
extern s32 func_00288348();
extern s32 func_00297FE0();
extern s32 func_0024B4C8();
extern s32 func_00102360();
extern s32 func_003B9D58();
extern s32 McCard_GetInfo();
extern s32 McCard_Probe();
extern s32 McCard_Format();
extern s32 McCard_CreateSave();
extern s32 McCard_WriteSave();
extern s32 McCard_IsFatalError();
extern s32 McCard_ReadFile();
extern s32 McCard_Checksum();

#define S D_004213B0
#define W(o) (*(s32 *)(S + (o)))
#define P(o) (*(s32 *)(gMcCardPort + (o)))
#define BTN (D_003B0C34 & 0x4008)
#define PAD() func_00297FE0(0, 1, 0x40, 0x40, 1)

/* Menu/memcard save-load state machine: state W(0xE8) (1..32), draw id W(0xEC), timer W(0xF0), W(0xF4) = wait flag.
   Every state ends with func_0029C800(W(0xEC)) and a tail call func_0029C1E8(1). */
s32 func_003B9EF0(void) {
    s32 v, t, st, tm;

    W(0xEC) = -1;
    t = W(0xE8) - 1;
    if ((u32)t >= 0x20) goto END;
    switch (t + 1) {
    case 1: /* BABE0 */
        func_0029C7C0(0);
        W(0xEC) = 5;
        if (!BTN) goto END;
        PAD();
        goto START16;
    case 2: /* BAC28 */
        func_0029C7C0(0);
        W(0xEC) = 7;
        if (!BTN) goto END;
        PAD();
        W(0xE8) = 0xD;
        goto END;
    case 3: /* BA5E0 */
        func_0029C7C0(0);
        W(0xEC) = 0x10;
        if (!BTN) goto END;
        PAD();
        func_0029C820(1);
        W(0xE8) = 0x10;
        goto SETF4;
    case 4: /* BA760 */
        func_0029C7C0(0);
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v < 0) {
            W(0xEC) = 0x22;
            if (func_00289C98(0, S + 0x40F8) != 0) {
                W(0xF0) = 0x78;
                W(0xE8) = 8;
                goto END;
            }
            if (P(0xC) != 2) goto ST1;
            if (McCard_IsFatalError(P(8)) != 0) goto ST1;
            if (P(8) >= 0) goto END;
            W(0xE8) = 6;
            goto END;
        }
        W(0xEC) = 0x22;
        if (McCard_GetInfo(0) == 0) goto END;
        if (W(0xF0) > 0) goto END;
        if (P(0xC) != 2) {
            W(0xE8) = 1;
            W(0xF0) = 0xB4;
            goto END;
        }
        if (McCard_IsFatalError(P(8)) == 0) goto END;
        goto ST1;
    case 5:
        goto END;
    case 6: /* BA890 */
        func_0029C7C0(0);
        W(0xEC) = 0x22;
        if (func_0028A578(0, 1) == 0) {
            if (McCard_IsFatalError(P(8)) == 0) goto END;
            st = 1; tm = 0xB4;
            goto SET;
        }
        st = (P(8) == 1) ? 0xB : 2;
        tm = 0xB4;
        goto SET;
    case 7: /* B9F48 */
        func_0029C7C0(1);
        W(0xEC) = 3;
        v = W(0xF4);
        if (v > 0) {
            v = W(0xF0) - 1;
            W(0xF0) = v;
            if (v >= 0) goto END;
            W(0xE8) = 0x12;
            W(0xF0) = 0x78;
            W(0xF4) = 0;
            func_0029C820(1);
            goto END;
        }
        goto CHKD;
    case 8: /* BA8F8 */
        func_0029C7C0(0);
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v >= 0) {
            W(0xEC) = 8;
            if (McCard_GetInfo(0) == 0) goto END;
            if (McCard_IsFatalError(P(8)) == 0) goto END;
            st = 0xA; tm = 0xB4;
            goto SET;
        }
        W(0xEC) = 8;
        if (McCard_ReadFile(0, S + 0xF8, 0x4000, S + 0x40F8) == 0) {
            if (P(8) >= 0) goto END;
            st = 0xA; tm = 0xB4;
            goto SET;
        }
        if (P(0) & 1) { st = 0xB; tm = 0xB4; goto SET; }
        if (McCard_Checksum(S + 0xF8, 0x4000, 0) != 0) { st = 0xB; tm = 0xB4; goto SET; }
        memcpy(D_00387F2C, S + 0xF8, 0x4000);
        func_0024B4C8();
        func_00102360();
        st = 9; tm = 0xB4;
        goto SET;
    case 9: /* BAAC0 */
        func_0029C7C0(0);
        W(0xEC) = 0xA;
        if (BTN) PAD();
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v > 0) {
            if (!BTN) goto END;
        }
        W(0xE8) = 0xD;
        goto CC80;
    case 10: /* BAB40 */
        func_0029C7C0(0);
        W(0xEC) = 9;
        if (!BTN) goto END;
        PAD();
        W(0xE8) = 0xD;
        goto END;
    case 11: /* BAB90 */
        func_0029C7C0(0);
        W(0xEC) = 0x19;
        if (!BTN) goto END;
        PAD();
        W(0xE8) = 0xD;
        goto END;
    case 12: /* BA6F0 */
        func_0029C7C0(1);
        W(0xEC) = 4;
        v = W(0xF4);
        if (v > 0) {
            v = W(0xF0) - 1;
            W(0xF0) = v;
            if (v >= 0) goto END;
            W(0xE8) = 4;
            W(0xF0) = 0x78;
            goto A73C;
        }
        goto CHKD;
    case 13: /* BACA8 */
        func_0029C7C0(0);
        func_0029C550(1);
        func_0029C640(0);
        W(0xE8) = 0xF;
        goto END;
    case 14:
        goto END;
    case 15: /* BACD0 */
        func_0029C7C0(0);
        func_0029C640(0);
        if (func_0029C830() == 0) goto END;
        W(0xE8) = 0;
        if ((W(0xCC) & 0x80) == 0) goto END;
        W(0xCC) |= 1;
        W(0xCC) |= 2;
        W(0xDC) = 0;
        goto END;
    case 16: /* B9FC0 */
        func_0029C7C0(1);
        W(0xEC) = 0x24;
        v = W(0xF4);
        if (v > 0) {
            v = W(0xF0) - 1;
            W(0xF0) = v;
            if (v >= 0) goto END;
            st = 0x11;
            goto A340;
        }
        goto CHKD;
    case 17: /* BAC78 */
        func_0029C7C0(0);
        W(0xE8) = 0xD;
        goto CC80;
    case 18: /* BA018 */
        func_0029C7C0(1);
        W(0xEC) = 0xB;
        v = W(0xF4);
        if (v > 0) {
            v = W(0xF0) - 1;
            W(0xF0) = v;
            if (v >= 0) goto END;
            W(0xE8) = 0x13;
            W(0xF0) = 0x78;
            goto A73C;
        }
        goto CHKB;
    case 19: /* BA070 */
        func_0029C7C0(0);
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v >= 0) {
            W(0xEC) = 0x22;
            if (McCard_GetInfo(0) == 0) goto END;
            if (W(0xF0) > 0) goto END;
            if (P(0xC) != 2) {
                W(0xE8) = 1;
                W(0xF0) = 0xB4;
                goto END;
            }
            if (McCard_IsFatalError(P(8)) != 0) goto ST1;
            if (P(0x14) != 0) goto END;
            goto BAD90;
        }
        W(0xEC) = 0x22;
        if (func_00289C98(0, S + 0x40F8) != 0) {
            func_00288348();
            W(0xE8) = 0x1E;
            goto END;
        }
        if (P(0xC) != 2) goto ST1;
        if (P(0x14) == 0) goto BAD90;
        if (McCard_IsFatalError(P(8)) != 0) goto ST1;
        if (P(8) >= 0) goto END;
        if (P(0x10) < 0x4B) { st = 3; tm = 0xB4; goto SET; }
        W(0xE8) = 0x14;
        goto END;
    case 20: /* BA480 */
        func_0029C7C0(0);
        W(0xEC) = 0x22;
        if (func_0028A578(0, 1) == 0) {
            if (McCard_IsFatalError(P(8)) == 0) goto END;
            st = 1; tm = 0xB4;
            goto SET;
        }
        st = 0x16; tm = 0x78;
        goto SET;
    case 21: /* BA2D8 */
        func_0029C7C0(1);
        W(0xEC) = 0x15;
        McCard_Probe(0);
        if (McCard_IsFatalError(P(8)) != 0) { st = 1; tm = 0xB4; goto SET; }
        v = W(0xF4);
        if (v <= 0) goto CHKB;
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v >= 0) goto END;
        st = 0x17;
        goto A340;
    case 22: /* BA368 */
        func_0029C7C0(0);
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v >= 0) {
            W(0xEC) = 0x12;
            if (McCard_GetInfo(0) == 0) goto END;
            if (W(0xF0) > 0) goto END;
            if (McCard_IsFatalError(P(8)) == 0) goto END;
            goto ST19;
        }
        W(0xEC) = 0x12;
        goto CREATE;
    case 23: /* BA3E0 */
        func_0029C7C0(0);
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v >= 0) {
            W(0xEC) = 0x1D;
            if (McCard_GetInfo(0) == 0) goto END;
            if (W(0xF0) > 0) goto END;
            if (McCard_IsFatalError(P(8)) == 0) goto END;
            goto ST19;
        }
        W(0xEC) = 0x1D;
        if (McCard_WriteSave(0, S + 0xF8, 0x4000, S + 0x40F8) == 0) goto F7C;
        st = 0x18; tm = 0xB4;
        goto SET;
    case 24: /* BA4F8 */
        func_0029C7C0(0);
        W(0xEC) = 0x1E;
        if (BTN) PAD();
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v > 0) {
            if (!BTN) goto END;
        }
        W(0xE8) = 0xD;
        *(s32 *)(D_003876A4 + 0x18) |= 0x400;
        W(0xCC) |= 0x80;
        goto END;
    case 25: /* BA598 */
        func_0029C7C0(0);
        W(0xEC) = 0x1F;
        if (!BTN) goto END;
        PAD();
        goto START16;
    case 26: /* BA1A0 */
        func_0029C7C0(1);
        W(0xEC) = 0xD;
        McCard_Probe(0);
        if (McCard_IsFatalError(P(8)) != 0) {
            func_0029C7C0(0);
            W(0xEC) = 5;
            W(0xE8) = 1;
            W(0xF0) = 0xB4;
            goto END;
        }
        v = W(0xF4);
        if (v <= 0) goto CHKB;
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v >= 0) goto END;
        st = 0x1B; tm = 0x78;
        goto SET0;
    case 27: /* BA230 */
        func_0029C7C0(0);
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v >= 0) {
            W(0xEC) = 0xC;
            if (McCard_GetInfo(0) == 0) goto END;
            if (W(0xF0) > 0) goto END;
            if (McCard_IsFatalError(P(8)) == 0) goto END;
            st = 0x1D; tm = 0xB4;
            goto SET;
        }
        W(0xEC) = 0xC;
        if (McCard_Format(0) != 0) { st = 0x1C; tm = 0xB4; goto SET; }
        if (P(8) >= 0) goto END;
        st = 0x1D; tm = 0xB4;
        goto SET;
    case 28: /* BA638 */
        func_0029C7C0(0);
        McCard_Probe(0);
        if (McCard_IsFatalError(P(8)) != 0) { st = 1; tm = 0xB4; goto SET; }
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v >= 0) {
            W(0xEC) = 0xE;
            goto END;
        }
        W(0xE8) = 0x16;
        W(0xF0) = 0x78;
        goto END;
    case 29: /* BA6A8 */
        func_0029C7C0(0);
        W(0xEC) = 0xF;
        if (!BTN) goto END;
        PAD();
        goto START16;
    case 30: /* BAD30 */
        func_0029C7C0(0);
        W(0xEC) = 0x22;
        if (func_0028A790(0, S + 0x40F8) != 0) {
            v = P(0x1C);
            if (v <= 0) {
                st = 0x15;
            } else if (P(0x10) < v) {
                st = 3; tm = 0xB4;
                goto SET;
            } else {
                st = 0x1F;
            }
            W(0xE8) = st;
            W(0xF0) = 0x78;
            func_0029C820(1);
            goto END;
        }
        if (P(0xC) != 2) { st = 1; tm = 0xB4; goto SET; }
        if (P(0x14) == 0) goto BAD90;
        if (McCard_IsFatalError(P(8)) == 0) goto END;
        st = 1; tm = 0xB4;
        goto SET;
    case 31: /* BAE20 */
        func_0029C7C0(1);
        W(0xEC) = 0x15;
        McCard_Probe(0);
        if (McCard_IsFatalError(P(8)) != 0) { st = 1; tm = 0xB4; goto SET0; }
        v = W(0xF4);
        if (v <= 0) goto CHKB;
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v >= 0) goto END;
        st = 0x20; tm = 0x78;
        goto SET0;
    case 32: /* BAEF0 */
        func_0029C7C0(0);
        v = W(0xF0) - 1;
        W(0xF0) = v;
        if (v >= 0) {
            W(0xEC) = 0x1D;
            if (McCard_GetInfo(0) == 0) goto END;
            if (W(0xF0) > 0) goto END;
            if (McCard_IsFatalError(P(8)) == 0) goto END;
            goto ST19;
        }
        W(0xEC) = 0x1D;
        goto CREATE;
    }
    goto END;

CREATE: /* BAF60 */
    if (McCard_CreateSave(0, S + 0x40F8) != 0) {
        func_003B9D58();
        W(0xE8) = 0x17;
        goto END;
    }
F7C:
    if (P(8) >= 0) goto END;
ST19:
    st = 0x19; tm = 0xB4;
    goto SET;
ST1:
    st = 1; tm = 0xB4;
SET:
    W(0xE8) = st;
    W(0xF0) = tm;
    goto END;
SET0:
    W(0xE8) = st;
    W(0xF0) = tm;
    W(0xF4) = 0;
    goto END;
SETF4:
    W(0xF4) = 0;
    goto END;
A340: /* E8 = st, timer 0x78, F4 = 0, then func_003B9D58 */
    W(0xE8) = st;
    W(0xF0) = 0x78;
    W(0xF4) = 0;
    func_003B9D58();
    goto END;
A73C:
    W(0xF4) = 0;
    func_00288348();
    goto END;
BAD90:
    W(0xE8) = 0x1A;
    func_0029C820(1);
    goto END;
CC80:
    W(0xCC) |= 0x80;
    goto END;
CHKD: /* F4 <= 0 here (value in v) */
    if (v >= 0) goto TMR;
    W(0xE8) = 0xD;
    goto SETF4;
CHKB:
    if (v >= 0) goto TMR;
START16:
    func_0029C820(1);
    W(0xE8) = 0x10;
    W(0xF4) = 0;
    goto END;
TMR:
    W(0xF4) = func_0029C640(0);
    W(0xF0) = 0xC;
END:
    func_0029C800(W(0xEC));
    return func_0029C1E8(1);
}
