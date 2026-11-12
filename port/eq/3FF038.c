#include "common.h"

extern u8 *D_0042A58C __attribute__((section(".data")));

void func_003FE0C0(s32 arg0);
void func_243968(s32 arg0, s32 arg1, s32 arg2);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_2711A0(void);
void func_28B090(void);
void func_28BDA0(void);
void func_297978(void);
void func_2438E8(void);
void func_003FE428(void);
void func_003FE3B0(void);
void BattleSetup_Finish(void);
void func_003FE450(void);
void func_2437E8(void);
void func_271240(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_101890(void);
void func_003FE368(void);
void func_28B218(void);

/* 0x003FF038: func_003FE0C0(); func_243968(0,0,0); then loop: the common update calls, then while ColorFade_IsFadingOut()
 * call func_101890 and repeat. When ColorFade_IsOutDone() == 0: if G->0x48 has bit 2, G->0x4C -= 1 and at -1 call
 * func_243A80(0,0,0); repeat. Once done: func_003FE368(), func_28B218(), return 1. (G = D_0042A58C.) */
s32 func_003FF038(s32 arg0) {
    u8 *g;
    s32 v;

    func_003FE0C0(arg0);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003FE428();
        func_003FE3B0();
        BattleSetup_Finish();
        func_003FE450();
        func_2437E8();
        func_271240();

        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            g = D_0042A58C;
            if (*(s32 *)(g + 0x48) & 2) {
                v = *(s32 *)(g + 0x4C) - 1;
                *(s32 *)(g + 0x4C) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                }
            }
            continue;
        }
        break;
    }

    func_003FE368();
    func_28B218();
    return 1;
}
