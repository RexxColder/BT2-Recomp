#include "common.h"

extern u8 *D_004263EC __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003DB828(s32 arg0);
void func_003DBBC0(void);
void func_003DBC08(void);
void func_003DC098(void);
void func_003DC280(void);
void func_003DC320(s32 *out);
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

/* 0x003DC5E0: sibling of 0x3E09A0 on D = D_004263EC (0x74 armed flag, 0x68 cleared and passed as t0, 0x60 bit 2,
 * 0x78 and 0x70 countdown, P->0x490 = G->0x64 with P = D_3876A4 when the countdown hits -1). */
s32 func_003DC5E0(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003DB828(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003DC098();
        func_003DC280();
        func_003DBC08();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_004263EC + 0x74) == 0 &&
            func_26EB60(D_004263EC + 0x10) != 0) {
            *(s32 *)(D_004263EC + 0x74) = 1;
            *(s32 *)(D_004263EC + 0x68) = 0;
            func_2493C0(*(s32 *)(D_004263EC + 0xC), 0x36B2, 0x3ACB, 0, *(s32 *)(D_004263EC + 0x68));
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            if (sp[0] == 0) {
                func_101498();
            }
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (!(*(s32 *)(D_004263EC + 0x60) & 2)) {
                if (*(s32 *)(D_004263EC + 0x78) == 0) {
                    func_003DC320(sp);
                }
            } else {
                v = *(s32 *)(D_004263EC + 0x70) - 1;
                *(s32 *)(D_004263EC + 0x70) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                    *(s32 *)(D_3876A4 + 0x490) = *(s32 *)(D_004263EC + 0x64);
                }
            }
            continue;
        }
        break;
    }
    func_003DBBC0();
    func_28B218();
    return sp[0];
}
