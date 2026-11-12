#include "common.h"

extern u8 *D_0042A584 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003FA8F0(s32 arg0);
void func_003FACA8(void);
void func_003FAD28(void);
void func_003FAD88(void);
void func_003FB2D0(s32 *out);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x003FB470: menu loop on D = D_0042A584. In the in-done state the counter G->0x12C runs 0 -> 1 (func_2493C0 with
 * t0 = 4) and 2 -> 3 (func_2493C0 with t0 = 0x2C). Bit 0x1 of G->0x124 picks the out-done exit or func_243A80 /
 * func_003FB2D0. */
s32 func_003FB470(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003FA8F0(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        if (ColorFade_IsInDone() != 0) {
            v = *(s32 *)(D_0042A584 + 0x12C);
            if (v == 0) {
                *(s32 *)(D_0042A584 + 0x12C) = 1;
                func_2493C0(*(s32 *)(D_0042A584 + 0xC), 0x37A6, 0x3BBF, 0, 4);
            } else if (v == 2) {
                func_2493C0(*(s32 *)(D_0042A584 + 0xC), 0x37A6, 0x3BBF, 0, 0x2C);
                *(s32 *)(D_0042A584 + 0x12C) = *(s32 *)(D_0042A584 + 0x12C) + 1;
            }
        }
        func_003FAD28();
        func_003FAD88();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsFadingOut() != 0 && (*(s32 *)(D_0042A584 + 0x124) & 1)) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() != 0 && (*(s32 *)(D_0042A584 + 0x124) & 1)) {
            break;
        }
        if (*(s32 *)(D_0042A584 + 0x124) & 1) {
            func_243A80(0, 0, 0);
        } else {
            func_003FB2D0(sp);
        }
    }
    func_003FACA8();
    func_28B218();
    return sp[0];
}
