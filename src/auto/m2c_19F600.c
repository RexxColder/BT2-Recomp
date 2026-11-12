#include "m2c_macros.h"

f32 EftVolleyAim_GetFighterDistSq();                /* extern */
M2C_UNK func_0019F3F0(s32, M2C_UNK);                /* extern */
M2C_UNK func_0019F4A0(s32, M2C_UNK);                /* extern */
M2C_UNK func_0019F550(s32, M2C_UNK);                /* extern */
extern f32 D_00384E00;
extern f32 D_00384E04;

void func_0019F600(s32 arg0, M2C_UNK arg1) {
    f32 temp_f0;

    temp_f0 = EftVolleyAim_GetFighterDistSq();
    if (temp_f0 < D_00384E00) {
        func_0019F3F0(arg0, arg1);
        return;
    }
    if (temp_f0 < D_00384E04) {
        func_0019F4A0(arg0, arg1);
        return;
    }
    func_0019F550(arg0, arg1);
}
