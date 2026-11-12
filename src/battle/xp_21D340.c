#include "m2c_macros.h"

M2C_UNK BattleSide_SetChara(void *, M2C_UNK);       /* extern */
s32 func_00217490();                                /* extern */
void func_00217CB8(void *);                      /* extern */

void func_0021D340(void *arg0) {
    if (func_00217490(arg0) == 0x1B) {
        BattleSide_SetChara(arg0, 0x54);
    } else {
        BattleSide_SetChara(arg0, 0x53);
    }
    func_00217CB8(arg0);
    M2C_FIELD(arg0, s32 *, 0x149C) = (s32) (M2C_FIELD(arg0, s32 *, 0x149C) + 1);
}
