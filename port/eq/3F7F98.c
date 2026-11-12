#include "common.h"

extern u8 *D_0042A578 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003F5F00(s32 arg0);
void func_003F66F8(void);
void func_003F6778(void);
void func_003F7710(void);
void func_003F7840(void);
void func_003F7CA8(s32 *out);
void func_003F7F38(void);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
s32 func_26EB60(u8 *p);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x003F7F98: sibling of 0x3E09A0 on D = D_0042A578 (0x190 armed flag with 0x1B0 = 1, 0x194 gate, 0x13C bit 2,
 * 0x18C countdown). On the countdown's -1: P->0x64 = G[0x14C + 4 * G->0x140], P->0x58 = G->0x144, P = D_3876A4. */
s32 func_003F7F98(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003F5F00(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003F7710();
        func_003F7840();
        func_003F7F38();
        func_003F6778();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_0042A578 + 0x190) == 0 &&
            func_26EB60(D_0042A578 + 0x88) != 0) {
            *(s32 *)(D_0042A578 + 0x190) = 1;
            *(s32 *)(D_0042A578 + 0x1B0) = 1;
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (!(*(s32 *)(D_0042A578 + 0x13C) & 2)) {
                if (*(s32 *)(D_0042A578 + 0x194) == 0) {
                    func_003F7CA8(sp);
                }
            } else {
                v = *(s32 *)(D_0042A578 + 0x18C) - 1;
                *(s32 *)(D_0042A578 + 0x18C) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                    *(s32 *)(D_3876A4 + 0x64) =
                        *(s32 *)(D_0042A578 + (*(s32 *)(D_0042A578 + 0x140) << 2) + 0x14C);
                    *(s32 *)(D_3876A4 + 0x58) = *(s32 *)(D_0042A578 + 0x144);
                }
            }
            continue;
        }
        break;
    }
    func_003F66F8();
    func_28B218();
    return sp[0];
}
