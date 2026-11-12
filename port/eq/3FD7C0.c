#include "common.h"

extern u8 *D_0042A588 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void func_243A80(s32 a0, s32 a1, s32 a2);
void func_29C1E8(s32 a0);
void func_29C550();
s32 func_29C640(s32 a0);
void func_29C7C0(s32 a0);
void func_29C800(s32 a0);
void func_29C820(s32 a0);
s32 func_29C830(void);

/* 0x003FD7C0: state machine on G->0x23C (G = D_0042A588). 1 -> func_29C550(0), func_29C820(0), state 2, G->0x248 = 0x8A
 * and falls into 2: func_29C7C0(1), then G->0x244 > 0 (state 3) or < 0 (state 4) sets state, zeroes G->0x244 and
 * calls func_29C550(1, G); G->0x244 == 0 stores func_29C640(0). 3: func_29C830() != 0 -> state 0, G->0xFC |= 3,
 * G->0x10C = 0. 4: func_29C830() != 0 -> state 0, func_243A80(0,0,0), *arg0 = 0, P->0x1C = 0x14. Every path that
 * reaches the end calls func_29C800(G->0x248) and tail-calls func_29C1E8(1). */
void func_003FD7C0(s32 *arg0) {
    s32 st;
    s32 v0;
    s32 v;

    st = *(s32 *)(D_0042A588 + 0x23C);
    if (st == 0) {
        return;
    }
    if (st == 1) {
        func_29C550(0);
        func_29C820(0);
        *(s32 *)(D_0042A588 + 0x23C) = 2;
        *(s32 *)(D_0042A588 + 0x248) = 0x8A;
        st = 2;
    }
    if (st == 2) {
        func_29C7C0(1);
        v0 = *(s32 *)(D_0042A588 + 0x244);
        if (v0 != 0) {
            v = (v0 > 0) ? 3 : 4;
            *(s32 *)(D_0042A588 + 0x23C) = v;
            *(s32 *)(D_0042A588 + 0x244) = 0;
            func_29C550(1, D_0042A588);
        } else {
            *(s32 *)(D_0042A588 + 0x244) = func_29C640(0);
        }
    } else if (st == 3) {
        func_29C640(0);
        if (func_29C830() != 0) {
            *(s32 *)(D_0042A588 + 0x23C) = 0;
            *(s32 *)(D_0042A588 + 0xFC) = *(s32 *)(D_0042A588 + 0xFC) | 1;
            *(s32 *)(D_0042A588 + 0xFC) = *(s32 *)(D_0042A588 + 0xFC) | 2;
            *(s32 *)(D_0042A588 + 0x10C) = 0;
        }
    } else if (st == 4) {
        func_29C640(0);
        if (func_29C830() != 0) {
            *(s32 *)(D_0042A588 + 0x23C) = 0;
            func_243A80(0, 0, 0);
            *arg0 = 0;
            *(s32 *)(D_3876A4 + 0x1C) = 0x14;
        }
    }
    func_29C800(*(s32 *)(D_0042A588 + 0x248));
    func_29C1E8(1);
}
