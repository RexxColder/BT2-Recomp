#include "common.h"

extern u8 *D_00421C00 __attribute__((section(".data")));

s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void BattleSetup_Finish(void);
void func_003BB2A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_003BB438(void);
void func_003BB480(void);
void func_243968(s32 arg0, s32 arg1, s32 arg2);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_2437E8(void);
void func_2438E8(void);
void func_271240(void);
void func_2711A0(void);
void func_288348(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);
void func_29C550(s32 arg0);
void func_29C7E0(s32 arg0);
void func_29C810(s32 arg0);
void func_29C820(s32 arg0);

/* 0x003BBD98: func_003BB2A8(pass-through args); func_243968(0,0,0). Loop: the common update calls, then if
 * ColorFade_IsInDone() and G->0x14 == 0 (G = D_00421C00): G->0x14 = 1, G->0x24 = 0xC, func_29C550(0), func_29C820(1),
 * func_29C7E0(1), func_29C810(0), func_288348(), G->0x28 = 0x78. Loop until ColorFade_IsOutDone(); in the loop body
 * (before the test) G->0xC & 2 gates --G->0x10 == -1 -> func_243A80(0,0,0). Then func_003BB438(), func_28B218(),
 * return 1. */
s32 func_003BBD98(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_003BB2A8(arg0, arg1, arg2, arg3);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003BB480();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0) {
            if (*(s32 *)(D_00421C00 + 0x14) == 0) {
                *(s32 *)(D_00421C00 + 0x14) = 1;
                *(s32 *)(D_00421C00 + 0x24) = 0xC;
                func_29C550(0);
                func_29C820(1);
                func_29C7E0(1);
                func_29C810(0);
                func_288348();
                *(s32 *)(D_00421C00 + 0x28) = 0x78;
            }
        }
        if (ColorFade_IsOutDone() != 0) {
            break;
        }
        if (*(s32 *)(D_00421C00 + 0xC) & 0x2) {
            *(s32 *)(D_00421C00 + 0x10) = *(s32 *)(D_00421C00 + 0x10) - 1;
            if (*(s32 *)(D_00421C00 + 0x10) == -1) {
                func_243A80(0, 0, 0);
            }
        }
    }
    func_003BB438();
    func_28B218();
    return 1;
}
