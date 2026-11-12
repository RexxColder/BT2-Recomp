#include "common.h"

extern u8 *D_00428F4C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003ECF28(s32 arg0);
void func_003ECCA0(void);
void func_003ED9C0(void);
void func_003EDA48(void);
void func_003EE958(void);
void func_003EF038(s32 *out);
void func_003EFE18(s32 *out);
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

/* 0x003F0510: menu main loop on G = D_00428F4C (in-done arms G->0x1A0 and calls func_2493C0(G->0xC, 0x3711, 0x3B2A, 0,
 * 0); fading out calls func_101498 when sp[0] is 0 or P->0x1C is 0x3F, P = D_3876A4). Out-done with G->0x1EC == 4
 * copies G->0x184 / G->0x178 into P->0x47C / P->0x480 when G->0x174 bit 0 is set, then exits. Otherwise the countdown
 * G->0x19C on G->0x174 bit 2, or func_003EFE18(sp) when G->0x194 and G->0x198 are 0. */
s32 func_003F0510(s32 arg0) {
    s32 sp[4];

    sp[0] = 1;
    func_003ECF28(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_003ECCA0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003EE958();
        func_003EF038(sp);
        func_003EDA48();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_00428F4C + 0x1A0) == 0 &&
            func_26EB60(D_00428F4C + 0xA0) != 0) {
            *(s32 *)(D_00428F4C + 0x1A0) = 1;
            *(s32 *)(D_00428F4C + 0x17C) = 0;
            *(s32 *)(D_00428F4C + 0x190) = 0;
            func_2493C0(*(s32 *)(D_00428F4C + 0xC), 0x3711, 0x3B2A, 0, 0);
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            if (sp[0] == 0 || *(s32 *)(D_3876A4 + 0x1C) == 0x3F) {
                func_101498();
            }
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (!(*(s32 *)(D_00428F4C + 0x174) & 2)) {
                if (*(s32 *)(D_00428F4C + 0x194) != 0) {
                    continue;
                }
                if (*(s32 *)(D_00428F4C + 0x198) != 0) {
                    continue;
                }
                func_003EFE18(sp);
                continue;
            }
            *(s32 *)(D_00428F4C + 0x19C) = *(s32 *)(D_00428F4C + 0x19C) - 1;
            if (*(s32 *)(D_00428F4C + 0x19C) == -1) {
                func_243A80(0, 0, 0);
            }
            continue;
        }
        if (*(s32 *)(D_00428F4C + 0x1EC) != 4) {
            continue;
        }
        if (*(s32 *)(D_00428F4C + 0x174) & 1) {
            *(s32 *)(D_3876A4 + 0x47C) = *(s32 *)(D_00428F4C + 0x184);
            *(s32 *)(D_3876A4 + 0x480) = *(s32 *)(D_00428F4C + 0x178);
        }
        break;
    }
    func_003ED9C0();
    func_28B218();
    return sp[0];
}
