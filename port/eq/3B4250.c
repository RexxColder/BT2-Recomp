#include "common.h"

extern u8 *D_00421380 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));

s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void BattleSetup_Finish(void);
void MainMenu_StartBallLoops(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_003B37A8(void);
void func_003B3738(void);
void func_003B3E50(void);
void func_003B3F38(s32 *arg0);
void func_101498(void);
void func_101890(void);
void func_243968(s32 arg0, s32 arg1, s32 arg2);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_2437E8(void);
void func_2438E8(void);
void func_271240(void);
void func_2711A0(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);
s32 func_26EB60(u8 *arg0);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x003B4250 (G = D_00421380): sp[0] = 1; MainMenu_StartBallLoops(pass-through); func_243968(0,0,0). Loop: the common
 * update calls, then if ColorFade_IsInDone() and G->0xFC == 0 and func_26EB60(G+0x38): G->0xFC = 1, func_2493C0(G->0xC,
 * 0x36DC, 0x3AF5, 0, G->0xEC). If ColorFade_IsFadingOut(): func_101890(), func_101498(), loop. If IsOutDone(): func_003B3738(),
 * func_28B218(), return sp[0]. Else if !(G->0xE4 & 2): func_003B3F38(sp); else G->0xF8--, at -1: func_243A80(0,0,0) and
 * D_003876A4->0x28 = G->0xE8. Loop. */
s32 func_003B4250(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];

    sp[0] = 1;
    MainMenu_StartBallLoops(arg0, arg1, arg2, arg3);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003B3E50();
        func_003B37A8();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0) {
            if (*(s32 *)(D_00421380 + 0xFC) == 0) {
                if (func_26EB60(D_00421380 + 0x38) != 0) {
                    *(s32 *)(D_00421380 + 0xFC) = 1;
                    func_2493C0(*(s32 *)(D_00421380 + 0xC), 0x36DC, 0x3AF5, 0, *(s32 *)(D_00421380 + 0xEC));
                }
            }
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            func_101498();
            continue;
        }
        if (ColorFade_IsOutDone() != 0) {
            func_003B3738();
            func_28B218();
            return sp[0];
        }
        if (!(*(s32 *)(D_00421380 + 0xE4) & 0x2)) {
            func_003B3F38(sp);
            continue;
        }
        *(s32 *)(D_00421380 + 0xF8) = *(s32 *)(D_00421380 + 0xF8) - 1;
        if (*(s32 *)(D_00421380 + 0xF8) == -1) {
            func_243A80(0, 0, 0);
            *(s32 *)(D_003876A4 + 0x28) = *(s32 *)(D_00421380 + 0xE8);
        }
    }
}
