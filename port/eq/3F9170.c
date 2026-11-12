#include "common.h"

extern u8 *D_0042A57C __attribute__((section(".data")));

s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void BattleSetup_Finish(void);
void func_003F8160(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_003F89B0(void);
void func_003F8930(void);
void func_003F8FB8(s32 *arg0);
void func_003F90B0(void);
void func_101890(void);
void func_243968(s32 arg0, s32 arg1, s32 arg2);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_249510(s32 arg0, s32 arg1);
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

/* 0x003F9170 (G = D_0042A57C): sp[0] = 1; func_003F8160(pass-through args); func_243968(0,0,0). Loop: the common update
 * calls, then if ColorFade_IsInDone() and G->0xCC == 0 and func_26EB60(G+0x40): G->0xCC = 1, func_2493C0(G->0xC, 0x37A6,
 * 0x3BBF, 0, 0x1B), and if G->0xB4 & 0xC: func_249510(8, -0x50). If ColorFade_IsFadingOut(): func_101890(), loop.
 * If IsOutDone(): func_003F8930(), func_28B218(), return sp[0]. Else if G->0xB4 & 2: G->0xC8--, at -1 func_243A80(0,0,0);
 * otherwise func_003F8FB8(sp); loop. */
s32 func_003F9170(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];

    sp[0] = 1;
    func_003F8160(arg0, arg1, arg2, arg3);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003F90B0();
        func_003F89B0();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0) {
            if (*(s32 *)(D_0042A57C + 0xCC) == 0) {
                if (func_26EB60(D_0042A57C + 0x40) != 0) {
                    *(s32 *)(D_0042A57C + 0xCC) = 1;
                    func_2493C0(*(s32 *)(D_0042A57C + 0xC), 0x37A6, 0x3BBF, 0, 0x1B);
                    if (*(s32 *)(D_0042A57C + 0xB4) & 0xC) {
                        func_249510(8, -0x50);
                    }
                }
            }
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() != 0) {
            func_003F8930();
            func_28B218();
            return sp[0];
        }
        if (*(s32 *)(D_0042A57C + 0xB4) & 0x2) {
            *(s32 *)(D_0042A57C + 0xC8) = *(s32 *)(D_0042A57C + 0xC8) - 1;
            if (*(s32 *)(D_0042A57C + 0xC8) == -1) {
                func_243A80(0, 0, 0);
            }
        } else {
            func_003F8FB8(sp);
        }
    }
}
