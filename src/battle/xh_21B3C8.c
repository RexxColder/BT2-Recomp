#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

void *BtlChar_GetPos(s32);                          /* extern */
M2C_UNK func_00217CB8(s32);                         /* extern */
extern f32 D_00385C8C;

// Battle char setup: SetChara 0x53, func_00217CB8, stores float D_00385C8C into BtlChar_GetPos field 0xC0.
void func_0021B3C8(s32 arg0) {
    BattleSide_SetChara(arg0, 0x53);
    func_00217CB8(arg0);
    M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC0) = (f32) D_00385C8C;
}
