#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217488(s32 arg0);

void func_00236438(s32 arg0) {
    s32 temp_v0;
    s32 temp_a2;
    s32 var_a1;

    temp_v0 = func_00217488(arg0);
    temp_a2 = temp_v0 < 0xC9;
    var_a1 = 0;
    if (temp_v0 == 0xC8) {
        var_a1 = 0x15F;
    } else if (temp_a2 != 0) {
        if (temp_v0 == 0xC7) {
            var_a1 = 0x13D;
        }
    } else if (temp_v0 == 0xC9) {
        var_a1 = 0x181;
    }
    BattleSide_SetChara(arg0, var_a1, temp_a2);
}
