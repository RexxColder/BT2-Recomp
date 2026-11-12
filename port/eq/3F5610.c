#include "common.h"

extern u8 *D_0042A574 __attribute__((section(".data")));

s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void BattleSetup_Finish(void);
void func_003F4318(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_003F4800(s32 arg0);
void func_003F4878(void);
void func_003F48D8(s32 *arg0);
void func_003F5180(void);
void func_003F55E8(s32 *arg0);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 arg0, s32 arg1, s32 arg2);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x003F5610: sp[0] = 1; func_003F4318(args); func_243968(0,0,0). Loop: the common update calls (func_003F48D8(sp)
 * among them), then if ColorFade_IsFadingOut() and (G->0x114 & 1) (G = D_0042A574) func_101890() and loop; else if not
 * ColorFade_IsOutDone(): flag ? func_243A80(0,0,0) : func_003F55E8(sp), loop. When out is done: flag == 0 ->
 * func_243968(0,0,0) and the same branch; else func_003F4800(0), func_28B218(), return sp[0]. */
s32 func_003F5610(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];

    sp[0] = 1;
    func_003F4318(arg0, arg1, arg2, arg3);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003F48D8(sp);
        func_003F4878();
        func_003F5180();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsFadingOut() != 0 && (*(s32 *)(D_0042A574 + 0x114) & 1)) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (*(s32 *)(D_0042A574 + 0x114) & 1) {
                func_243A80(0, 0, 0);
            } else {
                func_003F55E8(sp);
            }
            continue;
        }
        if (!(*(s32 *)(D_0042A574 + 0x114) & 1)) {
            func_243968(0, 0, 0);
            if (*(s32 *)(D_0042A574 + 0x114) & 1) {
                func_243A80(0, 0, 0);
            } else {
                func_003F55E8(sp);
            }
            continue;
        }
        func_003F4800(0);
        func_28B218();
        return sp[0];
    }
}
