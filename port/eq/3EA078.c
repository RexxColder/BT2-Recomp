#include "common.h"

extern u8 *D_004279D4 __attribute__((section(".data")));

s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
s32 ColorFade_IsInDone(void);
void BattleSetup_Finish(void);
void func_003E84B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_003E83D8(void);
void func_003E8900(void);
void func_003E8948(void);
void func_003E92C0(void);
void func_003E92E8(s32 *arg0);
void func_003E9F18(void);
s32 func_26EB60(u8 *arg0);
void func_101890(void);
void func_2437E8(void);
void func_243968(s32 arg0, s32 arg1, s32 arg2);
void func_2438E8(void);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x003EA078: sp[0] = 1; func_003E84B0(pass-through args); func_243968(0,0,0). Loop: the common update calls, then
 * if ColorFade_IsInDone() and G->0x2E8 == 0 (G = D_004279D4) and func_26EB60(G+0x10): G->0x2E8 = 1, func_003E83D8().
 * if ColorFade_IsFadingOut(): func_101890() and loop. If not IsOutDone(): if G->0x2EC == 0, func_003E92E8(sp); loop.
 * Else func_003E8900(), func_28B218(), return sp[0]. */
s32 func_003EA078(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];

    sp[0] = 1;
    func_003E84B0(arg0, arg1, arg2, arg3);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003E92C0();
        func_003E8948();
        BattleSetup_Finish();
        func_003E9F18();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0) {
            if (*(s32 *)(D_004279D4 + 0x2E8) == 0) {
                if (func_26EB60(D_004279D4 + 0x10) != 0) {
                    *(s32 *)(D_004279D4 + 0x2E8) = 1;
                    func_003E83D8();
                }
            }
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (*(s32 *)(D_004279D4 + 0x2EC) == 0) {
                func_003E92E8(sp);
            }
            continue;
        }
        func_003E8900();
        func_28B218();
        return sp[0];
    }
}
