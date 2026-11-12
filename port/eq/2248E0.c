#include "common.h"

void BattleSide_SetChara(u8 *arg0, s32 arg1);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
void func_00212DD8(u8 *arg0, s32 arg1);

void func_002248E0(u8 *arg0) {
    BattleSide_SetChara(arg0, 0xFF);
    if (func_00211310(arg0, 0, 1) != 0) {
        if (func_00211310(arg0, 1, 1) != 0) {
            func_00212DD8(arg0, 0x1E);
        }
    }
}
