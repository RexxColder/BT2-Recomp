#include "m2c_macros.h"

void BattleSide_SetChara(void *, M2C_UNK);       /* extern */
void func_0020FC38(void *, M2C_UNK);             /* extern */
s32 func_00217490();                                /* extern */
void func_00217CB8(void *);                      /* extern */

void func_00219F58(void *arg0) {
    if (func_00217490(arg0) == 0x1B) {
        BattleSide_SetChara(arg0, 0x4E);
    } else {
        BattleSide_SetChara(arg0, 0x4D);
    }
    func_00217CB8(arg0);
    func_0020FC38(arg0, 0x2E);
    M2C_FIELD(arg0, s32 *, 0x149C) = (s32) (M2C_FIELD(arg0, s32 *, 0x149C) + 1);
}
