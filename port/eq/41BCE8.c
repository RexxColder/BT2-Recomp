#include "common.h"

extern u8 *D_0042BB84 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_0041A988(s32 arg0);
void func_0041ADE0(void);
void func_0041AE58(void);
void func_0041B6A8(void);
void func_0041B7D8(s32 *out);
s32 func_28C4B8(s32 a0);
void func_101498(void);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_26EB60(u8 *p);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x0041BCE8: menu main loop on G = D_0042BB84 with input block IN = D_003B0B00. Flag 8 of G->0xF0 toggles through
 * func_28C4B8(1) when IN->0x284 == 1. In-done arms G->0x104 and calls func_2493C0(G->8, 0x36A3, 0x3ABC, 0, G->0xF8).
 * Out-done path counts G->0x100 for bit 2 of G->0xF0 and copies G->0xF4 / G->0xFC into P->0x458 / P->0x464 (P =
 * D_3876A4). */
s32 func_0041BCE8(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_0041A988(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        if (*(s32 *)(D_0042BB84 + 0xF0) & 0x8) {
            if (*(s32 *)(D_003B0B00 + 0x284) == 1) {
                if (func_28C4B8(1) == 0) {
                    *(s32 *)(D_0042BB84 + 0xF0) = *(s32 *)(D_0042BB84 + 0xF0) ^ 0x8;
                }
            }
        }
        func_0041B6A8();
        func_0041AE58();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_0042BB84 + 0x104) == 0 &&
            func_26EB60(D_0042BB84 + 0x38) != 0) {
            *(s32 *)(D_0042BB84 + 0x104) = 1;
            func_2493C0(*(s32 *)(D_0042BB84 + 0x8), 0x36A3, 0x3ABC, 0, *(s32 *)(D_0042BB84 + 0xF8));
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            if (sp[0] == 0) {
                func_101498();
            }
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (*(s32 *)(D_0042BB84 + 0xF0) & 2) {
                v = *(s32 *)(D_0042BB84 + 0x100) - 1;
                *(s32 *)(D_0042BB84 + 0x100) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                    *(s32 *)(D_3876A4 + 0x458) = *(s32 *)(D_0042BB84 + 0xF4);
                    *(s32 *)(D_3876A4 + 0x464) = *(s32 *)(D_0042BB84 + 0xFC);
                }
            } else {
                func_0041B7D8(sp);
            }
            continue;
        }
        break;
    }
    func_0041ADE0();
    func_28B218();
    return sp[0];
}
