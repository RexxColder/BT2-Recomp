#include "common.h"

extern u8 *D_00421C94 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003BE778(s32 arg0);
void func_003BEC20(s32 a0);
void func_003BEC90(void);
void func_003BED00(void);
void func_003BF210(void);
void func_003BF270(s32 *out);
void func_003BF748(void);
void func_003C0370(void);
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

/* 0x003C0518: menu main loop on G = D_00421C94 (the sibling-style loop of 0x3C0370). In-done with G->0x52C bit 8 clear:
 * set it, G->0x534 = 0xB and func_2493C0(G->0xC, 0x33E9, 0x3802, 0, 0xB). Bit 0x80 runs func_003C0370. Fading out with
 * bit 2 runs func_101890. Out-done with bit 2 clear re-runs func_243968 before the bit-2 countdown block; with bit 2
 * set it leaves through func_003BEC20(0). */
s32 func_003C0518(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003BE778(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003BEC90();
        func_003BED00();
        func_003BF748();
        func_003BF210();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0) {
            if (!(*(s32 *)(D_00421C94 + 0x52C) & 8)) {
                *(s32 *)(D_00421C94 + 0x52C) = *(s32 *)(D_00421C94 + 0x52C) | 8;
                *(s32 *)(D_00421C94 + 0x534) = 0xB;
                func_2493C0(*(s32 *)(D_00421C94 + 0xC), 0x33E9, 0x3802, 0, *(s32 *)(D_00421C94 + 0x534));
            }
        }
        if (*(s32 *)(D_00421C94 + 0x52C) & 0x80) {
            func_003C0370();
            continue;
        }
        if (ColorFade_IsFadingOut() != 0 && (*(s32 *)(D_00421C94 + 0x52C) & 2)) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (*(s32 *)(D_00421C94 + 0x52C) & 2) {
                v = *(s32 *)(D_00421C94 + 0x530) - 1;
                *(s32 *)(D_00421C94 + 0x530) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                }
            } else {
                func_003BF270(sp);
            }
            continue;
        }
        if (!(*(s32 *)(D_00421C94 + 0x52C) & 2)) {
            func_243968(0, 0, 0);
            func_003BF270(sp);
            continue;
        }
        break;
    }
    func_003BEC20(0);
    func_28B218();
    return sp[0];
}
