#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_00211418(s32 arg0, s32 arg1);
s32 func_00217488(s32 arg0);
s32 func_00240FA0(s32 arg0, s32 arg1, s32 arg2);

void func_0022FF18(s32 arg0) {
    s32 var_a1;
    s32 var_s1;
    s32 temp_a2;
    s32 temp_v0;

    var_s1 = 0;
    temp_v0 = func_00217488(arg0);
    temp_a2 = temp_v0 < 0xE2;
    var_a1 = 2;
    if (temp_v0 != 0xE1) {
        if (temp_a2 != 0) {
            if (temp_v0 == 0xE0) {
                var_s1 = 0x11F;
            }
        } else if (temp_v0 == 0xE2) {
            var_s1 = 0x163;
            var_a1 = 4;
        }
    } else {
        var_s1 = 0x141;
        var_a1 = 3;
    }
    BattleSide_SetChara(arg0, ((func_00240FA0(arg0, var_a1, temp_a2) ^ 1) != 0) ? var_s1 : 0x183);
    func_00211418(arg0, 0x400000);
}
