#include "common.h"

extern u8 *D_00423118 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003CB420(s32 arg0);
void func_003CBDE8(void);
void func_003CBE58(void);
void func_003CCEE0(void);
void func_003CD200(s32 *out);
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

/* 0x003CD778: menu main loop on D = D_00423118 (0x158 armed with func_2493C0(G->8, 0x342E, 0x3847, 0, G->0x144); the
 * fading-out path always calls func_101890 and func_101498; 0x134 bit 2 / bit 0x4000 countdown on 0x154 that copies
 * G->0x138 / 0x13C / 0x140 into P->0x8C / 0x90 / 0x94 (P = D_3876A4); out-done with sp[0] set toggles P->0x18 bits
 * 0x1000 and ~0x2000). */
s32 func_003CD778(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003CB420(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003CCEE0();
        func_003CBE58();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_00423118 + 0x158) == 0 &&
            func_26EB60(D_00423118 + 0x88) != 0) {
            *(s32 *)(D_00423118 + 0x158) = 1;
            func_2493C0(*(s32 *)(D_00423118 + 0x8), 0x342E, 0x3847, 0, *(s32 *)(D_00423118 + 0x144));
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            func_101498();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (!(*(s32 *)(D_00423118 + 0x134) & 2)) {
                if (*(s32 *)(D_00423118 + 0x148) == 0) {
                    func_003CD200(sp);
                }
            } else if (*(s32 *)(D_00423118 + 0x134) & 0x4000) {
                v = *(s32 *)(D_00423118 + 0x154) - 1;
                *(s32 *)(D_00423118 + 0x154) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                    *(s32 *)(D_3876A4 + 0x8C) = *(s32 *)(D_00423118 + 0x138);
                    *(s32 *)(D_3876A4 + 0x90) = *(s32 *)(D_00423118 + 0x13C);
                    *(s32 *)(D_3876A4 + 0x94) = *(s32 *)(D_00423118 + 0x140);
                }
            }
            continue;
        }
        break;
    }
    if (sp[0] != 0) {
        *(s32 *)(D_3876A4 + 0x18) = *(s32 *)(D_3876A4 + 0x18) | 0x1000;
        *(s32 *)(D_3876A4 + 0x18) = *(s32 *)(D_3876A4 + 0x18) & ~0x2000;
    }
    func_003CBDE8();
    func_28B218();
    return sp[0];
}
