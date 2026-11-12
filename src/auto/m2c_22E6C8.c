#include "m2c_macros.h"

M2C_UNK BattleSide_SetChara(s32, s32);              /* extern */
s32 BtlObjXf_Update();                              /* extern */
s32 func_00211310(s32, M2C_UNK, M2C_UNK);           /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
s32 func_00227DA0(s32, s32);                        /* extern */

void func_0022E6C8(s32 arg0) {
    BattleSide_SetChara(arg0, func_00227DA0(arg0, BtlObjXf_Update(arg0)));
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
        return;
    }
    func_002113C0(arg0, 0, 2, 0);
}
