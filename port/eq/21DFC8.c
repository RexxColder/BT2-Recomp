#include "common.h"

s32 func_00217490(s32 arg0);
s32 BtlChar_FrameMod(s32 arg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_00217CB8(s32 arg0);

/* 0x0021DFC8: per-character frame step on the object arg0. Unless func_00217490(arg0) == 0x6F, the counter at
 * +0x99C is cleared, +0x9B8 is cleared and +0x9BC = BtlChar_FrameMod(2). The counter is then normalized (negative
 * -> 0, 4 -> 5, 9 -> 0); the code for BattleSide_SetChara is 0x43 for 0 and 4, 0x44..0x46 for 1..3, 0x48..0x4B for
 * 5..8 (0x43 for other values); BattleSide_SetChara(arg0, code) is called, the counter is incremented, and
 * func_00217CB8(arg0) is returned. */
void func_0021DFC8(u8 *arg0) {
    s32 code = 0x43;
    s32 v1;

    if (func_00217490((s32)arg0) != 0x6F) {
        *(s32 *)(arg0 + 0x99C) = 0;
        *(s32 *)(arg0 + 0x9B8) = 0;
        *(s32 *)(arg0 + 0x9BC) = BtlChar_FrameMod(2);
    }
    v1 = *(s32 *)(arg0 + 0x99C);
    if (v1 < 0) {
        *(s32 *)(arg0 + 0x99C) = 0;
        v1 = 0;
    }
    if (v1 == 4) {
        *(s32 *)(arg0 + 0x99C) = 5;
        v1 = 5;
    }
    if (v1 == 9) {
        *(s32 *)(arg0 + 0x99C) = 0;
        v1 = 0;
    }
    if ((u32)v1 < 9) {
        switch (v1) {
            case 0:
                code = 0x43;
                break;
            case 1:
                code = 0x44;
                break;
            case 2:
                code = 0x45;
                break;
            case 3:
                code = 0x46;
                break;
            case 4:
                break;
            case 5:
                code = 0x48;
                break;
            case 6:
                code = 0x49;
                break;
            case 7:
                code = 0x4A;
                break;
            case 8:
                code = 0x4B;
                break;
        }
    }
    BattleSide_SetChara((s32)arg0, code);
    *(s32 *)(arg0 + 0x99C) += 1;
    func_00217CB8((s32)arg0);
}
