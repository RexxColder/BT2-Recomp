#include "common.h"

extern u8 *D_004263E8 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003D8988(s32 arg0);
void func_003D8ED0(u8 *g);
void func_003D8F48(void);
void func_003D9098(void);
void func_003DA768(s32 *out);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_250DC0(s32 a0, s32 a1, u8 *a2);
s32 func_26EB60(u8 *p);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x003DB4E0: menu main loop, sibling of 0x3E09A0 / 0x405360. Before the in-done check it calls
 * func_250DC0(*(G+0xC+12*i+0x170 ...), i * 0x1B24, G+0xC) with i = G->0x158 (the entries at G+0xC + 4*i + 0x150).
 * In-done with G->0x6E38 == 0x10, G->0x6E3C == 0 and func_26EB60(G+0x1C) arms G->0x6E3C and calls func_2493C0.
 * Out-done ends with func_003D8ED0(G). */
s32 func_003DB4E0(s32 arg0) {
    s32 sp[4];
    s32 idx;
    s32 scaled;
    s32 k;
    u8 *base;

    sp[0] = 1;
    func_003D8988(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003D8F48();
        func_003D9098();
        BattleSetup_Finish();

        base = D_004263E8 + 0xC;
        idx = *(s32 *)(D_004263E8 + 0x158);
        scaled = idx * 0x1B24;
        k = *(s32 *)(base + idx * 4 + 0x150);
        func_250DC0(*(s32 *)(base + k * 12 + scaled + 0x170), scaled, base);
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_004263E8 + 0x6E38) == 0x10 &&
            *(s32 *)(D_004263E8 + 0x6E3C) == 0 && func_26EB60(D_004263E8 + 0x1C) != 0) {
            *(s32 *)(D_004263E8 + 0x6E3C) = 1;
            func_2493C0(*(s32 *)(D_004263E8 + 0xC), 0x36B2, 0x3ACB, 0, *(s32 *)(D_004263E8 + 0x6E38));
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (*(s32 *)(D_004263E8 + 0x154) & 2) {
                idx = *(s32 *)(D_004263E8 + 0x6E40) - 1;
                *(s32 *)(D_004263E8 + 0x6E40) = idx;
                if (idx == -1) {
                    func_243A80(0, 0, 0);
                }
            } else {
                func_003DA768(sp);
            }
            continue;
        }
        break;
    }
    func_003D8ED0(D_004263E8);
    func_28B218();
    return sp[0];
}
