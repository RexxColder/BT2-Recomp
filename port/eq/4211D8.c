#include "common.h"

extern u8 *D_0042FD78 __attribute__((section(".data")));

void func_004206F8(s32 arg0);
void func_243968(s32 arg0, s32 arg1, s32 arg2);
void func_00421158(s32 *arg0);
void func_00420A40(void);
void func_00420F10(void);
void func_00420968(void);
void func_2711A0(void);
void func_28B090(void);
void func_28BDA0(void);
void func_297978(void);
void func_2438E8(void);
void BattleSetup_Finish(void);
void func_2437E8(void);
void func_271240(void);
void func_101890(void);
void func_101498(void);
void func_28B218(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
s32 func_26EB70(u8 *arg0);
void func_26EAE0(u8 *arg0, s32 arg1);

/* 0x004211D8: sp[0] = 1; func_004206F8(); func_243968(0,0,0). Loop: the common update calls; if ColorFade_IsInDone() and
 * func_26EB70(G+0x40) has no bit 0 then func_26EAE0(G+0x40, 0x3C) (G = D_0042FD78); if ColorFade_IsFadingOut(): func_101890,
 * func_101498 and repeat; if not ColorFade_IsOutDone(): func_00421158(sp) and repeat. Then func_00420968(), func_28B218(),
 * return sp[0]. */
s32 func_004211D8(s32 arg0) {
    s32 sp[4];

    sp[0] = 1;
    func_004206F8(arg0);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_00420A40();
        func_00420F10();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();

        if (ColorFade_IsInDone() != 0) {
            if (!(func_26EB70(D_0042FD78 + 0x40) & 1)) {
                func_26EAE0(D_0042FD78 + 0x40, 0x3C);
            }
        }

        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            func_101498();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            func_00421158(sp);
            continue;
        }
        break;
    }

    func_00420968();
    func_28B218();
    return sp[0];
}
