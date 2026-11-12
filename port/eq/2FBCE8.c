#include "common.h"

extern s32 D_0035538C __attribute__((section(".data")));
extern s32 D_00355390 __attribute__((section(".data")));
extern s32 D_00355394 __attribute__((section(".data")));
extern u8 D_003553C4 __attribute__((section(".data")));
extern s32 D_003553C0 __attribute__((section(".data")));
extern u8 D_0037DEE8[] __attribute__((section(".data")));

s32 func_002FC550(s32 arg0);
s32 func_002FBB88(u8 *arg0);
s32 func_00331710(void *arg0, s32 arg1);
s32 sceCdBreak(void);
s32 sceCdSync(s32 arg0);
s32 sceCdRead(s32 arg0, s32 arg1, s32 arg2, void *arg3);

/* 0x002FBCE8: CD read state machine. Runs only while *(s32 *)(arg0+4) == 1 and the byte at +2 is a
 * state (0..9, cases 2 and 1/3/9 differ); then the tail acts on state 1 (read) and 2 (sync). */
void func_002FBCE8(u8 *arg0) {
    u8 *s1;
    s32 a1;
    s32 st;
    s32 s0;
    s32 v;

    s1 = arg0;
    a1 = *(u8 *)(s1 + 2);
    if (*(s32 *)(s1 + 4) == 1) {
        st = *(s8 *)(s1 + 2);
        if ((u32)st < 10) {
            switch (st) {
            case 2:
                func_002FC550(0x1600);
                s0 = sceCdBreak();
                func_002FC550(0x1601);
                if (s0 == 0) {
                    func_00331710(D_0037DEE8, D_0035538C);
                }
                func_002FC550(0x1700);
                sceCdSync(0);
                func_002FC550(0x1701);
                *(u8 *)(s1 + 2) = 0;
                a1 = 0;
                D_00355394 = D_00355394 + 1;
                *(s32 *)(s1 + 4) = 0;
                break;
            case 1:
            case 3:
            case 9:
                *(u8 *)(s1 + 2) = 0;
                a1 = 0;
                *(s32 *)(s1 + 4) = 0;
                break;
            default:
                *(s32 *)(s1 + 4) = 0;
                break;
            }
        } else {
            *(s32 *)(s1 + 4) = 0;
        }
    }

    if (a1 == 1) {
        func_002FC550(0x1800);
        if (D_003553C0 == 1) {
            *(u8 *)(s1 + 0x15) = D_003553C4;
        }
        s0 = sceCdRead(*(s32 *)(s1 + 8), *(s32 *)(s1 + 0xC), *(s32 *)(s1 + 0x10), s1 + 0x14);
        func_002FC550(0x1801);
        if (s0 != 1) {
            *(u8 *)(s1 + 2) = 9;
            a1 = 9;
            *(s32 *)(s1 + 0x34) = -1;
        } else {
            D_00355390 = D_00355390 + 1;
            *(u8 *)(s1 + 2) = 2;
            a1 = 2;
        }
    }

    if (a1 != 2) {
        return;
    }
    func_002FC550(0x1900);
    sceCdSync(1);
    s0 = func_002FC550(0x1901);
    v = func_002FBB88(s1);
    if (s0 == 0) {
        *(u8 *)(s1 + 2) = (v == 1) ? 9 : 3;
        D_00355394 = D_00355394 + 1;
    }
}
