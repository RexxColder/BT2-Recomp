#include "m2c_macros.h"

M2C_UNK BattleSide_SetChara(s32, M2C_UNK);          /* extern */
void *BtlChar_GetPos(s32);                          /* extern */
s32 func_00217488();                                /* extern */
M2C_UNK func_00217CB8(s32);                         /* extern */
extern f32 D_00385C54;

void func_0021AE38(s32 arg0) {
    M2C_UNK var_a1;
    s32 temp_v0;

    temp_v0 = func_00217488(arg0);
    var_a1 = 0x5F;
    switch (temp_v0) {
    case 0x5B:
        var_a1 = 0x5F;
        break;
    case 0x5C:
        var_a1 = 0x5C;
        break;
    case 0x76:
        var_a1 = 0x5E;
        break;
    case 0x77:
        var_a1 = 0x61;
        break;
    case 0x7B:
        var_a1 = 0x65;
        break;
    case 0x7C:
        var_a1 = 0x62;
        break;
    case 0x5D:
    case 0x7D:
        var_a1 = 0x59;
        break;
    }
    BattleSide_SetChara(arg0, var_a1);
    func_00217CB8(arg0);
    M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC0) = (f32) D_00385C54;
}
