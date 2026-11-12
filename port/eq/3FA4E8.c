#include "common.h"

extern u8 *D_0042A580 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003F9608(s32 arg0);
void func_003F9B10(void);
void func_003F9B80(void);
void func_003F9F38(void);
void func_003FA268(s32 *out);
void func_003FA430(void);
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

/* 0x003FA4E8: sibling of 0x3E09A0 on D = D_0042A580 (0xE4 armed flag with 0xD8 cleared and passed as t0, 0xD0 bit 2,
 * 0xE8 gate for the input handler 0x3FA268, 0xE0 countdown; on -1: P->0x54 = G->0xD4 with P = D_3876A4). */
s32 func_003FA4E8(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003F9608(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003FA430();
        func_003F9F38();
        func_003F9B80();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_0042A580 + 0xE4) == 0 &&
            func_26EB60(D_0042A580 + 0x64) != 0) {
            *(s32 *)(D_0042A580 + 0xE4) = 1;
            *(s32 *)(D_0042A580 + 0xD8) = 0;
            func_2493C0(*(s32 *)(D_0042A580 + 0xC), 0x37A6, 0x3BBF, 0, *(s32 *)(D_0042A580 + 0xD8));
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            if (sp[0] == 0) {
                func_101498();
            }
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (!(*(s32 *)(D_0042A580 + 0xD0) & 2)) {
                if (*(s32 *)(D_0042A580 + 0xE8) == 0) {
                    func_003FA268(sp);
                }
            } else {
                v = *(s32 *)(D_0042A580 + 0xE0) - 1;
                *(s32 *)(D_0042A580 + 0xE0) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                    *(s32 *)(D_3876A4 + 0x54) = *(s32 *)(D_0042A580 + 0xD4);
                }
            }
            continue;
        }
        break;
    }
    func_003F9B10();
    func_28B218();
    return sp[0];
}
