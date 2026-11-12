#include "common.h"

extern u8 *D_00427334 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003DFBB0(s32 arg0);
void func_003DFFC8(void);
void func_003E0040(void);
void func_003E06A0(void);
void func_003E07A8(s32 *out);
void func_101498(void);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_26EB60(u8 *p);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x003E09A0: sibling of 0x405360 on D = D_00427334 (fields 0xA8 armed flag, 0xA4 countdown, 0x98 bits, 0x9C copied
 * to P->0x4C4 with P = D_3876A4 when the countdown hits -1). Fading-out calls func_101498 unless sp[0] was set. */
s32 func_003E09A0(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003DFBB0(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003E06A0();
        func_003E0040();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_00427334 + 0xA8) == 0 &&
            func_26EB60(D_00427334 + 0x38) != 0) {
            *(s32 *)(D_00427334 + 0xA8) = 1;
            func_2493C0(*(s32 *)(D_00427334 + 0xC), 0x3422, 0x383B, 0, *(s32 *)(D_00427334 + 0xA0));
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            if (sp[0] == 0) {
                func_101498();
            }
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (*(s32 *)(D_00427334 + 0x98) & 2) {
                v = *(s32 *)(D_00427334 + 0xA4) - 1;
                *(s32 *)(D_00427334 + 0xA4) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                    *(s32 *)(D_3876A4 + 0x4C4) = *(s32 *)(D_00427334 + 0x9C);
                }
            } else {
                func_003E07A8(sp);
            }
            continue;
        }
        break;
    }
    func_003DFFC8();
    func_28B218();
    return sp[0];
}
