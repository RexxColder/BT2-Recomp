#include "m2c_macros.h"

void BattleSide_SetChara(void *, s32);               /* extern */
void func_0020FC38(void *, s32);             /* extern */
void func_002113C0(void *, s32, s32, s32); /* extern */

void func_0021BCD8(void *arg0) {
    BattleSide_SetChara(arg0, 0x77);
    func_002113C0(arg0, 0, 2, 1);
    func_0020FC38(arg0, 0x2E);
    M2C_FIELD(arg0, s32 *, 0x149C) = (s32) (M2C_FIELD(arg0, s32 *, 0x149C) + 1);
}
