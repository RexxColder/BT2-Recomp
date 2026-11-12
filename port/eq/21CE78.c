#include "common.h"

extern f32 D_00385DA4;
s32 func_00217490(u8 *arg0);
void BattleSide_SetChara(u8 *arg0, s32 arg1);
void func_00217CB8(u8 *arg0);
void BtlAnim_SetBlend(u8 *arg0, f32 farg0);

void func_0021CE78(u8 *arg0) {
    if (func_00217490(arg0) == 0x1B) {
        BattleSide_SetChara(arg0, 0x9D);
    } else {
        BattleSide_SetChara(arg0, 0x9C);
    }
    func_00217CB8(arg0);
    BtlAnim_SetBlend(arg0, D_00385DA4);
    *(s32 *)(arg0 + 0x149C) += 1;
}
