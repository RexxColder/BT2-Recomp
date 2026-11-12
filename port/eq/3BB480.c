#include "common.h"
void *memcpy(void *, const void *, unsigned long);

extern u8 *D_00421C00;
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
extern s32 func_00289C98();
extern s32 func_0028A578();
extern s32 func_00288348();
extern s32 func_00297FE0();
extern s32 func_0024B4C8();
extern s32 McCard_GetInfo();
extern s32 McCard_IsFatalError();
extern s32 McCard_ReadFile();
extern s32 McCard_Checksum();

#define S D_00421C00
#define W(o) (*(s32 *)(S + (o)))
#define P(o) (*(s32 *)(gMcCardPort + (o)))

/* menu/memcard state machine on D_00421C00->0x24 (1..13); each state ends by calling func_0029C800(S->0x20)
   and tail-calling func_0029C1E8(1) */
s32 func_003BB480(void) {
    s32 v, a1, r;
    u8 *a0;

    if (W(0x24) == 0) return 0;
    if ((u32)(W(0x24) - 1) >= 13) goto L58;
    switch (W(0x24)) {
    case 12: /* L4D0 */
        func_0029C7C0(0);
        W(0x20) = 0x22;
        func_0029C640(0);
        v = W(0x28) - 1;
        W(0x28) = v;
        if (v < 0) goto L548;
        if (McCard_GetInfo(0) == 0) goto L58;
        if (W(0x28) > 0) goto L58;
        if (P(0xC) == 2) { a1 = P(8); goto L8AC; }
        W(0x24) = 1;
        goto L54;
    case 1: /* L5A8 */
        func_0029C7C0(1);
        W(0x20) = 6;
        v = W(0x2C);
        if (v > 0) {
            v = W(0x28) - 1;
            W(0x28) = v;
            if (v >= 0) goto L54;
            W(0x24) = 9;
            *(s32 *)(D_003876A4 + 0x18) |= 4;
            goto L54;
        } else if (v < 0) {
            W(0x2C) = 0;
        } else {
            W(0x2C) = func_0029C640(0);
            W(0x28) = 0xC;
        }
        if (McCard_GetInfo(0) == 0) goto L58;
        func_00288348();
        if (P(0xC) != 2) {
            W(0x18) = 1;
            P(0x10) = 0;
            P(0xC) = 0;
            goto L54;
        }
        if (P(0x14) == 0) { W(0x24) = 9; goto L54; }
        if (P(8) != -1) goto L58;
        W(0x28) = 0x78;
        W(0x24) = 3;
        goto L54;
    case 2: /* L6C0 */
        func_0029C7C0(1);
        W(0x20) = 0x11;
        v = W(0x2C);
        if (v > 0) {
            v = W(0x28) - 1;
            W(0x28) = v;
            if (v >= 0) goto L54;
            goto L70;
        } else if (v < 0) {
            W(0x2C) = 0;
        } else {
            W(0x2C) = func_0029C640(0);
            W(0x28) = 0xC;
        }
        if (McCard_GetInfo(0) == 0) goto L58;
        func_00288348();
        if (W(0x18) == 1) { W(0x24) = 1; goto L54; }
        if (P(0xC) != 2) {
            W(0x18) = 1;
            P(0x10) = 0;
            P(0xC) = 0;
            goto L54;
        }
        if (P(0x14) == 0) { W(0x24) = 9; goto L54; }
        if (P(8) != -1) goto L58;
        W(0x28) = 0x78;
        W(0x24) = 3;
        goto L54;
    case 3: /* L7D0 */
        func_0029C7C0(0);
        W(0x20) = 0x22;
        v = W(0x28) - 1;
        W(0x28) = v;
        if (v < 0) goto L818;
        if (McCard_GetInfo(0) == 0) goto L54;
        a1 = P(8);
        goto L8AC;
    case 4: /* L878 */
        func_0029C7C0(0);
        W(0x20) = 0x22;
        if (func_0028A578(0, 1) == 0) { a1 = P(8); goto L8AC; }
        if (P(8) == 1) {
            W(0x24) = 8;
            W(0x28) = 0x78;
            if (P(0x10) >= 0x4B) goto L58;
            W(0x18) = 4;
            a1 = 2;
            goto LD0;
        }
        W(0x24) = 1;
        if (P(0x10) >= 0x4B) goto L70;
        W(0x18) = 4;
        a1 = 2;
        goto LD0;
    case 5: /* L950 */
        func_0029C7C0(0);
        W(0x20) = 8;
        v = W(0x28) - 1;
        W(0x28) = v;
        if (v < 0) goto L9A8;
        if (McCard_GetInfo(0) == 0) goto L54;
        if (McCard_IsFatalError(P(8)) == 0) goto L58;
        goto L9DC;
    case 6: /* LB18 */
        func_0029C7C0(0);
        *(s32 *)(D_003876A4 + 0x18) |= 0x400;
        *(s32 *)(D_003876A4 + 0x18) |= 0x800;
        W(0x20) = 0xA;
        v = W(0x28) - 1;
        W(0x28) = v;
        if (v >= 0) goto L54;
        goto L70;
    case 7: /* LB80 */
        func_0029C7C0(0);
        W(0x20) = 9;
        if ((D_003B0C34 & 0x4008) == 0) goto L54;
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        W(0x28) = 0x78;
        a1 = 0xC;
        goto LD0;
    case 8: /* LBE0 */
        func_0029C7C0(0);
        W(0x20) = 0x19;
        if ((D_003B0C34 & 0x4008) == 0) goto L54;
        func_00297FE0(0, 1, 0x40, 0x40, 1);
        W(0x24) = 0xD;
        goto L54;
    case 9: /* LC30 */
        func_0029C7C0(0);
        func_0029C550(1);
        W(0x24) = 0xB;
        goto L54;
    case 10: /* LD54 */
        goto L54;
    case 11: /* LC50 */
        func_0029C7C0(0);
        func_0029C640(0);
        if (func_0029C830() == 0) goto L54;
        W(0xC) |= 1;
        W(0xC) |= 2;
        W(0x10) = 0xF;
        W(0x24) = 0;
        func_00288348();
        goto L58;
    case 13: /* LCB0 */
        func_0029C7C0(1);
        W(0x20) = 0x30;
        v = W(0x2C);
        if (v > 0) {
            W(0x24) = 9;
            W(0x2C) = 0;
            goto L54;
        }
        if (v >= 0) {
            W(0x2C) = func_0029C640(0);
            W(0x28) = 0xC;
            goto L54;
        }
        v = W(0x28) - 1;
        W(0x28) = v;
        if (v >= 0) goto L54;
        W(0x24) = 0xC;
        W(0x28) = 0x78;
        W(0x2C) = 0;
        func_00288348();
        goto L58;
    }
    goto L58;

L548:
    if (P(0x14) == 0) goto L70;
    if (func_00289C98(0, S + 0x30) != 0) goto L598;
    if (McCard_IsFatalError(P(8)) == 0) goto L84C;
    goto L8C0;
L598:
    a0 = S;
    *(s32 *)(a0 + 0x28) = 0x78;
    a1 = 5;
    goto LD0;
L818:
    if (func_00289C98(0, S + 0x30) != 0) goto L868;
    if (McCard_IsFatalError(P(8)) != 0) goto L8C0;
L84C:
    if (P(8) >= 0) goto L58;
    W(0x24) = 4;
    goto L54;
L868:
    a0 = S;
    *(s32 *)(a0 + 0x28) = 0x78;
    a1 = 5;
    goto LD0;
L8AC:
    if (McCard_IsFatalError(a1) == 0) goto L58;
L8C0:
    W(0x24) = 1;
    goto L54;
L9A8:
    a0 = S;
    r = McCard_ReadFile(0, a0 + 0x450, 0x4000, a0 + 0x30);
    if (r != 0) goto L9F8;
    if (P(8) >= 0) goto L58;
L9DC:
    W(0x24) = 7;
    W(0x28) = 0x78;
    goto L54;
L9F8:
    if ((P(0) & 1) == 0) {
        if (McCard_Checksum(S + 0x450, 0x4000, 0) == 0) {
            memcpy(D_00387F2C, S + 0x450, 0x4000);
            func_0024B4C8();
            W(0x24) = 6;
            W(0x28) = 0x78;
            goto L54;
        }
    }
    W(0x24) = 8;
    W(0x28) = 0x78;
    goto L54;
L70:
    v = 9;
    W(0x24) = v;
    goto L54;
LD0:
    W(0x24) = a1;
L54:
L58:
    func_0029C800(W(0x20));
    return func_0029C1E8(1);
}
