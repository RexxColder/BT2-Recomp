#include "common.h"

extern u8 *D_0042FD70 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));

s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void BattleSetup_Finish(void);
void func_0041C1B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0041C460(u8 *arg0);
void func_0041C4A0(void);
void func_0041C530(void);
void func_0041C6E0(void);
void func_0041C708(s32 *arg0);
void func_101498(void);
void func_101890(void);
void func_2437E8(void);
void func_243968(s32 arg0, s32 arg1, s32 arg2);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_2438E8(void);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x0041C788: sp[0] = 1; func_0041C1B8(pass-through args); func_243968(0,0,0). Loop: the common update calls, then if
 * ColorFade_IsFadingOut(): func_101890(), func_101498(), loop. If not IsOutDone(): if G->0x74 & 2 { if --G->0x80 == -1,
 * func_243A80(0,0,0) } else func_0041C708(sp) (G = D_0042FD70); loop. Else func_0041C460(*D_003876A4) after
 * setting its +0x2C |= 0x2000000, func_28B218(), return sp[0]. */
s32 func_0041C788(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];

    sp[0] = 1;
    func_0041C1B8(arg0, arg1, arg2, arg3);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_0041C530();
        func_0041C6E0();
        func_0041C4A0();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            func_101498();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (*(s32 *)(D_0042FD70 + 0x74) & 0x2) {
                *(s32 *)(D_0042FD70 + 0x80) = *(s32 *)(D_0042FD70 + 0x80) - 1;
                if (*(s32 *)(D_0042FD70 + 0x80) == -1) {
                    func_243A80(0, 0, 0);
                }
            } else {
                func_0041C708(sp);
            }
            continue;
        }
        *(s32 *)(D_003876A4 + 0x2C) = *(s32 *)(D_003876A4 + 0x2C) | 0x2000000;
        func_0041C460(D_003876A4);
        func_28B218();
        return sp[0];
    }
}
