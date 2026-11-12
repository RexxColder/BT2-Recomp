#include "m2c_macros.h"

s32 func_00240FF0(void *, M2C_UNK);                 /* extern */
s32 func_00241020(void *, M2C_UNK);                 /* extern */
s32 func_002411A0();                                /* extern */
extern f32 D_00386D10;

f32 func_002415A0(void *arg0, M2C_UNK arg1) {
    f32 var_f20;
    s32 temp_v0;
    s32 temp_v0_2;

    var_f20 = M2C_FIELD(((func_002411A0(arg0, arg1) * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x980)), f32 *, 0x78);
    temp_v0 = func_00240FF0(arg0, arg1);
    if (temp_v0 >= 2) {
        var_f20 /= (f32) temp_v0;
    }
    temp_v0_2 = func_00241020(arg0, arg1);
    if (temp_v0_2 >= 2) {
        var_f20 /= (f32) temp_v0_2;
    }
    return var_f20 * 10.0f * D_00386D10;
}
