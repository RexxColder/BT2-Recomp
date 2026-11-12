#include "m2c_macros.h"

void BattleSide_SetChara(void *, M2C_UNK);       /* extern */
void BtlAnim_SetBlend(f32, void *);              /* extern */
s32 func_00217490();                                /* extern */
void func_00217CB8(void *);                      /* extern */
extern f32 D_00385DA4;

void func_0021CE78(void *arg0) {
    if (func_00217490(arg0) == 0x1B) {
        BattleSide_SetChara(arg0, 0x9D);
    } else {
        BattleSide_SetChara(arg0, 0x9C);
    }
    func_00217CB8(arg0);
    BtlAnim_SetBlend(D_00385DA4, arg0);
    M2C_FIELD(arg0, s32 *, 0x149C) = (s32) (M2C_FIELD(arg0, s32 *, 0x149C) + 1);
}
