#include "common.h"

extern u8 *D_004279CC __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003E3D38(s32 arg0);
void func_003E41A0(u8 *p);
void func_003E4218(void);
void func_003E4B80(void);
void func_003E4CF8(s32 *out);
void func_003E51F8(void);
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

/* 0x003E6658: menu main loop on D = D_004279CC (0x110 selects func_003E51F8 each frame, 0xD8 / 0xEC gate the in-done
 * call with t0 = G->0xD8, 0xD0 & 3 == 3 counts down 0xE8 and copies G->0xD4 to P->0x4C0, else func_003E4CF8(sp)).
 * Out-done: clears P->0x18 bit 0 when sp[0] is 0, then func_003E41A0(P). */
s32 func_003E6658(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003E3D38(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003E4B80();
        func_003E4218();
        BattleSetup_Finish();
        if (*(s32 *)(D_004279CC + 0x110) != 0) {
            func_003E51F8();
        }
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_004279CC + 0xD8) == 0 &&
            *(s32 *)(D_004279CC + 0xEC) == 0 && func_26EB60(D_004279CC + 0x3C) != 0) {
            *(s32 *)(D_004279CC + 0xEC) = 1;
            func_2493C0(*(s32 *)(D_004279CC + 0x8), 0x36EF, 0x3B08, 0, *(s32 *)(D_004279CC + 0xD8));
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if ((*(s32 *)(D_004279CC + 0xD0) & 3) != 3) {
                if (*(s32 *)(D_004279CC + 0x110) == 0) {
                    func_003E4CF8(sp);
                }
            } else {
                v = *(s32 *)(D_004279CC + 0xE8) - 1;
                *(s32 *)(D_004279CC + 0xE8) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                    *(s32 *)(D_3876A4 + 0x4C0) = *(s32 *)(D_004279CC + 0xD4);
                }
            }
            continue;
        }
        break;
    }
    if (sp[0] == 0) {
        *(s32 *)(D_3876A4 + 0x18) = *(s32 *)(D_3876A4 + 0x18) & ~1;
    }
    func_003E41A0(D_3876A4);
    func_28B218();
    return sp[0];
}
