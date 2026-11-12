#include "common.h"

extern u8 *D_004279D0 __attribute__((section(".data")));

s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void BattleSetup_Finish(void);
void func_003E68D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_003E6848(void);
void func_003E6DC8(void);
void func_003E6E10(void);
void func_003E7610(void);
void func_003E7738(s32 *arg0);
void func_003E8110(void);
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

/* 0x003E8270: sp[0] = 1; func_003E68D0(pass-through args); func_243968(0,0,0). Loop: the common update calls
 * (func_003E7610, func_003E6E10, func_003E8110 among them), then if ColorFade_IsInDone() and G->0x318 == 0 and
 * func_26EB60(G+0x10) (G = D_004279D0): G->0x318 = 1, func_003E6848(). If ColorFade_IsFadingOut(): func_101890(),
 * loop. If IsOutDone() and (G->0xF0 & 1): func_003E6DC8(), func_28B218(), return sp[0]. Else if G->0x31C == 0,
 * func_003E7738(sp); loop. */
s32 func_003E8270(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];

    sp[0] = 1;
    func_003E68D0(arg0, arg1, arg2, arg3);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003E7610();
        func_003E6E10();
        BattleSetup_Finish();
        func_003E8110();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0) {
            if (*(s32 *)(D_004279D0 + 0x318) == 0) {
                if (func_26EB60(D_004279D0 + 0x10) != 0) {
                    *(s32 *)(D_004279D0 + 0x318) = 1;
                    func_003E6848();
                }
            }
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() != 0) {
            if (*(s32 *)(D_004279D0 + 0xF0) & 0x1) {
                func_003E6DC8();
                func_28B218();
                return sp[0];
            }
        }
        if (*(s32 *)(D_004279D0 + 0x31C) == 0) {
            func_003E7738(sp);
        }
    }
}
