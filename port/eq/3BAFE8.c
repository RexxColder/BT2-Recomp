#include "common.h"

extern u8 *D_004213B0 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

s32 rand(void);
void func_003B84B8(s32 a0);
void func_003B8C78(void);
void func_003B8CE8(void);
void func_003B8E88(void);
void func_003B9EF0(void);
void func_003B9710(s32 *a0);
void func_101890(void);
void func_101498(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_271240(void);
void func_2711A0(void);
void func_278A40(s32 a0, s32 a1);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);
s32 func_26EB60(u8 *a0);
s32 func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);

/* 0x003BAFE8: two-phase menu step on O = D_004213B0. Phase 1 (fade-in wait, at most 0x79 frames) sets O->0xE4's
 * fields; phase 2 runs until the fade-out ends, sets O->0xE0 once, picks O->0xD8 = (rand % 3) * 2 + 2 and calls
 * func_2493C0; the exit clears D_3876A4 flags when fr[0] is 0. Returns fr[0]. */
s32 func_003BAFE8(s32 a0) {
    u8 *O;
    u8 *Q;
    s32 fr[4];
    s32 s0 = 0;

    fr[0] = 1;
    func_003B84B8(a0);
    O = D_004213B0;
    Q = *(u8 **)(O + 0xE4);
    *(s32 *)(Q + 0x34) = 0x80;
    *(s32 *)(Q + 0x8) = 0x60;
    *(s32 *)(Q + 0x10) = *(s32 *)(Q + 0x8) + 0x100;
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        O = D_004213B0;
        func_278A40(*(s32 *)(O + 0xC8), *(s32 *)(O + 0xE4));
        func_2437E8();
        func_271240();
        if (ColorFade_IsFadingOut() != 0) {
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            s0 += 1;
            if (s0 >= 0x79) {
                func_243A80(0, 0, 0);
            }
            continue;
        }
        break;
    }

    O = D_004213B0;
    Q = *(u8 **)(O + 0xE4);
    *(s32 *)(Q + 0x34) = 0;
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003B8CE8();
        func_003B8E88();
        func_003B9EF0();
        func_2437E8();
        func_271240();
        O = D_004213B0;
        if (ColorFade_IsInDone() != 0 && *(s32 *)(O + 0xE0) == 0 && func_26EB60(O + 0x38) != 0) {
            *(s32 *)(O + 0xE0) = 1;
            *(s32 *)(O + 0xD8) = (rand() % 3) * 2 + 2;
            func_2493C0(0, 0x36DC, 0x3AF5, 0, *(s32 *)(O + 0xD8));
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            func_101498();
            continue;
        }
        if (ColorFade_IsOutDone() != 0) {
            break;
        }
        O = D_004213B0;
        if ((*(s32 *)(O + 0xCC) & 2) != 0) {
            *(s32 *)(O + 0xDC) = *(s32 *)(O + 0xDC) - 1;
            if (*(s32 *)(O + 0xDC) == -1) {
                func_243A80(0, 0, 0);
            }
        } else {
            if (*(s32 *)(O + 0xE8) == 0) {
                func_003B9710(fr);
            }
        }
    }

    if (fr[0] == 0) {
        *(s32 *)(D_3876A4 + 0x18) = *(s32 *)(D_3876A4 + 0x18) | 0x8;
        *(s32 *)(D_3876A4 + 0x24) = 0;
    }
    func_003B8C78();
    func_28B218();
    return fr[0];
}
