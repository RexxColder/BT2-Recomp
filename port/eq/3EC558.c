#include "common.h"

extern u8 *D_00428F48 __attribute__((section(".data")));

void func_003EABC0(s32 arg0);
void func_243968(s32 arg0, s32 arg1, s32 arg2);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_2711A0(void);
void func_003EA1C8(void);
void func_28B090(void);
void func_28BDA0(void);
void func_297978(void);
void func_2438E8(void);
void func_003EB118(void);
void func_003EB9D0(s32 *arg0);
void func_003EB218(void);
void BattleSetup_Finish(void);
void func_2437E8(void);
void func_271240(void);
s32 ColorFade_IsFadingOut(s32 arg0);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_101890(void);
void func_003EB090(s32 arg0);
void func_28B218(void);

/* 0x003EC558: sp[0] = 1; func_003EABC0(); func_243968(0,0,0). Loop: the common update calls (func_003EB9D0(sp) among them).
 * While ColorFade_IsOutDone() == 0: if ColorFade_IsFadingOut(4) call func_101890; else { if sp[0] == 0 and
 * ColorFade_IsInDone(), func_243A80(0,0,0); if G->0x198 >= 0x32 (G = D_00428F48), func_243A80(0,0,0) }. When done and
 * G->0x1B8 == 4 (else loop again): func_003EB090(4), func_28B218(), return sp[0]. */
s32 func_003EC558(s32 arg0) {
    s32 sp[4];

    sp[0] = 1;
    func_003EABC0(arg0);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_003EA1C8();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003EB118();
        func_003EB9D0(sp);
        func_003EB218();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();

        if (ColorFade_IsOutDone() == 0) {
            if (ColorFade_IsFadingOut(4) != 0) {
                func_101890();
            } else {
                if (sp[0] == 0 && ColorFade_IsInDone() != 0) {
                    func_243A80(0, 0, 0);
                }
                if (*(s32 *)(D_00428F48 + 0x198) >= 0x32) {
                    func_243A80(0, 0, 0);
                }
            }
            continue;
        }
        if (*(s32 *)(D_00428F48 + 0x1B8) == 4) {
            break;
        }
    }

    func_003EB090(4);
    func_28B218();
    return sp[0];
}
