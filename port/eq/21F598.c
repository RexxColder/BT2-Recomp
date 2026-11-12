#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217488(s32 arg0);
void func_00217CB8(s32 arg0);
void func_0020FC38(s32 arg0, s32 arg1);

void func_0021F598(s32 arg0) {
    s32 temp_v0;
    s32 var_a1;

    temp_v0 = func_00217488(arg0);
    var_a1 = 0;
    if (temp_v0 == 0x74) {
        var_a1 = 0x62;
    } else if (temp_v0 == 0x75) {
        var_a1 = 0x65;
    }
    BattleSide_SetChara(arg0, var_a1, 0x75);
    func_00217CB8(arg0);
    func_0020FC38(arg0, 0x2E);
    *(s32 *)(arg0 + 0x149C) = *(s32 *)(arg0 + 0x149C) + 1;
}
