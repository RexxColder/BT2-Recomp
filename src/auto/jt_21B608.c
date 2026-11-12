#include "m2c_macros.h"

M2C_UNK BattleSide_SetChara(s32, M2C_UNK);          /* extern */
M2C_UNK func_0020FC38(s32, M2C_UNK);                /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
s32 func_00217488();                                /* extern */

void func_0021B608(s32 arg0) {
    M2C_UNK var_a1;
    s32 temp_v0;

    temp_v0 = func_00217488(arg0);
    var_a1 = 0x68;
    switch (temp_v0) {
    case 0x5E:
        var_a1 = 0x71;
        break;
    case 0x5F:
        var_a1 = 0x74;
        break;
    case 0x60:
        var_a1 = 0x6B;
        break;
    case 0x61:
        var_a1 = 0x6E;
        break;
    case 0x62:
        var_a1 = 0x68;
        break;
    }
    BattleSide_SetChara(arg0, var_a1);
    func_002113C0(arg0, 0, 2, 1);
    func_0020FC38(arg0, 0x2E);
}
