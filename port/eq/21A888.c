#include "common.h"

s32 func_00217490(u8 *arg0);
void BattleSide_SetChara(u8 *arg0, s32 arg1);
void func_00217CB8(u8 *arg0);

void func_0021A888(u8 *arg0) {
    s32 x;

    if (func_00217490(arg0) != 0x59) {
        *(s32 *)(arg0 + 0x99C) = 0;
    }
    x = *(s32 *)(arg0 + 0x99C);
    if (x < 0) {
        *(s32 *)(arg0 + 0x99C) = 0;
        x = 0;
    }
    if (x >= 5) {
        *(s32 *)(arg0 + 0x99C) = 4;
        x = 4;
    }
    BattleSide_SetChara(arg0, 0x48 + x);
    *(s32 *)(arg0 + 0x99C) = *(s32 *)(arg0 + 0x99C) + 1;
    func_00217CB8(arg0);
    *(s32 *)(arg0 + 0x1454) = *(s32 *)(arg0 + 0x1454) + 1;
}
