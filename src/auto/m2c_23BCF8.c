#include "m2c_macros.h"

M2C_UNK BtlAnim_SetBlend(f32);                      /* extern */
M2C_UNK func_0023C710(s32);                         /* extern */
extern f32 D_00386C2C;

void func_0023BCF8(s32 arg0) {
    BtlAnim_SetBlend(D_00386C2C);
    func_0023C710(arg0);
}
